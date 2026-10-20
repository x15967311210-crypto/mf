/*
 * mf_bizhawk_dll - drive BizHawk's native mgba.dll without EmuHawk.
 *
 * This is the "movie-native" harness: it loads the exact BizHawk 2.3.0.1
 * mgba.dll (SHA1 4109E161..., mGBA 0.6) and calls the same BizCreate /
 * BizAdvance entry points that MGBAHawk uses. It is Windows-only and exists
 * to validate full .bk2 parity against the recording environment.
 *
 * Build (MSYS2):
 *   cc -O2 -std=gnu99 -o mf_bizhawk_dll.exe tools/headless/mf_bizhawk_dll.c -lz
 *
 * Usage:
 *   mf_bizhawk_dll --dll ...\BizHawk-2.3\dll\mgba.dll \
 *     --rom mf_us.gba --bios gba_bios.bin --movie tas.bk2 \
 *     --frames 339001 --checkpoint 300,600,...,339001 \
 *     --dump-dir out --prefix normal
 */

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <zlib.h>

#define POWER_KEY (1u << 31)
#define MAX_CHECKPOINTS 64

typedef struct {
    char* data;
    size_t size;
} Blob;

typedef struct {
    uint32_t keys;
    int16_t tiltX;
    int16_t tiltY;
    int16_t tiltZ;
    uint8_t light;
} FrameInput;

typedef struct {
    FrameInput* frames;
    size_t count;
    size_t capacity;
    char sha1[64];
    char biosSha1[64];
    char core[32];
    char gameName[128];
} Movie;

typedef struct {
    void* bios;
    void* wram;
    void* iwram;
    void* mmio;
    void* palram;
    void* vram;
    void* oam;
    void* rom;
    void* sram;
    int sramSize;
} MemoryAreas;

typedef void* (__cdecl* BizCreateFn)(const void* bios, const void* rom, int length, const void* dbinfo, int skipbios);
typedef void (__cdecl* BizResetFn)(void* ctx);
typedef int (__cdecl* BizAdvanceFn)(void* ctx, uint16_t keys, uint32_t* vbuff, int* nsamp, int16_t* sbuff,
    int64_t time, int16_t gyrox, int16_t gyroy, int16_t gyroz, uint8_t luma);
typedef void (__cdecl* BizDestroyFn)(void* ctx);
typedef void (__cdecl* BizGetMemoryAreasFn)(void* ctx, MemoryAreas* dst);
typedef void (__cdecl* BizPutSaveRamFn)(void* ctx, const void* data, int size);
typedef void (__cdecl* BizGetRegistersFn)(void* ctx, int* dest);
typedef uint8_t (__cdecl* BizReadBusFn)(void* ctx, uint32_t addr);
/* mGBA 0.6 bizinterface.c: BizStartGetState serializes the core into a
 * VFileMemChunk, BizFinishGetState copies it out and closes the chunk, and
 * BizPutState loads a state with SAVESTATE_SAVEDATA. */
typedef int (__cdecl* BizStartGetStateFn)(void* ctx, void** vfile, int* size);
typedef void (__cdecl* BizFinishGetStateFn)(void* vfile, void* data, int size);
typedef int (__cdecl* BizPutStateFn)(void* ctx, const void* data, int size);

typedef struct {
    const void* a;
    const void* b;
    size_t size;
    const char* name;
} DiffRegion;

/* First differing byte across the compared regions. With --settle this is
 * re-scanned every frame until the regions agree for a full settle window. */
typedef struct {
    bool found;
    size_t region;
    long offset;
    uint8_t a;
    uint8_t b;
} RegionDiff;

/* A diff that is being given --settle frames to disappear. `first*` is the
 * original observation and is what a durable failure reports; `last*` is the
 * most recent signature and drives window extensions. */
typedef struct {
    bool active;
    long firstFrame;
    size_t firstRegion;
    long firstOffset;
    uint8_t firstA;
    uint8_t firstB;
    size_t lastRegion;
    long lastOffset;
    uint8_t lastA;
    uint8_t lastB;
    long deadline;
} PendingDiff;

typedef struct {
    long frame;
    uint32_t keys;
    uint8_t light;
    int16_t tiltX;
    int16_t tiltY;
    int16_t tiltZ;
    uint16_t disp;
    uint16_t mainMode;
    uint16_t sub1;
    uint16_t sub2;
    uint8_t event;
    uint8_t area;
    uint8_t room;
    uint8_t nav;
    uint32_t crc[5];
    uint32_t pc;
    uint32_t lr;
    uint32_t sp;
    uint32_t cpsr;
} HistoryEntry;

typedef struct {
    HistoryEntry* entries;
    size_t capacity;
    size_t count;
    size_t next;
} History;

typedef struct {
    uint32_t addr;
    char name[128];
} Symbol;

typedef struct {
    Symbol* symbols;
    size_t count;
} SymbolTable;

typedef struct {
    const char* dll;
    const char* rom;
    const char* bios;
    const char* movie;
    const char* save;
    const char* diffRom;
    const char* diffSave;
    const char* dumpDir;
    const char* prefix;
    const char* map;
    const char* diffMap;
    const char* stateIn;
    const char* diffStateIn;
    const char* stateOut;
    const char* diffStateOut;
    long startFrame;
    long frames;
    int history;
    int settle;
    bool settleSet;
    bool diff;
    bool includeIwram;
    bool stackScan;
    size_t stackDepth;
    bool diffOam;
    bool diffPal;
    bool diffVram;
    bool diffIo;
    bool diffEwram;
    size_t ioSize;
    int checkpoints[MAX_CHECKPOINTS];
    int checkpointCount;
} Options;

static uint16_t rd16(const uint8_t* p) {
    return (uint16_t) (p[0] | (p[1] << 8));
}

static uint32_t rd32(const uint8_t* p) {
    return (uint32_t) p[0] | ((uint32_t) p[1] << 8) | ((uint32_t) p[2] << 16) | ((uint32_t) p[3] << 24);
}

static bool readFile(const char* path, uint8_t** out, size_t* outSize) {
    FILE* f = fopen(path, "rb");
    if (!f) {
        fprintf(stderr, "error: cannot open %s\n", path);
        return false;
    }
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    fseek(f, 0, SEEK_SET);
    uint8_t* data = malloc((size_t) size ? (size_t) size : 1);
    if (!data || (size && fread(data, 1, (size_t) size, f) != (size_t) size)) {
        free(data);
        fclose(f);
        return false;
    }
    fclose(f);
    *out = data;
    *outSize = (size_t) size;
    return true;
}

static bool zipExtract(const uint8_t* zip, size_t zipSize, const char* wanted, Blob* out) {
    if (zipSize < 22) return false;
    size_t eocd = SIZE_MAX;
    for (size_t i = zipSize - 21; i-- > 0;) {
        if (rd32(zip + i) == 0x06054b50) { eocd = i; break; }
    }
    if (eocd == SIZE_MAX || eocd + 22 > zipSize) return false;
    uint16_t entries = rd16(zip + eocd + 10);
    uint32_t cdSize = rd32(zip + eocd + 12);
    uint32_t cdOffset = rd32(zip + eocd + 16);
    if ((size_t) cdOffset + cdSize > zipSize) return false;
    size_t p = cdOffset;
    for (uint16_t i = 0; i < entries; ++i) {
        if (p + 46 > zipSize || rd32(zip + p) != 0x02014b50) return false;
        uint16_t method = rd16(zip + p + 10);
        uint32_t compSize = rd32(zip + p + 20);
        uint32_t uncompSize = rd32(zip + p + 24);
        uint16_t nameLen = rd16(zip + p + 28);
        uint16_t extraLen = rd16(zip + p + 30);
        uint16_t commentLen = rd16(zip + p + 32);
        uint32_t localOffset = rd32(zip + p + 42);
        if (p + 46 + nameLen > zipSize) return false;
        const char* name = (const char*) (zip + p + 46);
        if (strlen(wanted) == nameLen && memcmp(name, wanted, nameLen) == 0) {
            if ((size_t) localOffset + 30 > zipSize || rd32(zip + localOffset) != 0x04034b50) return false;
            uint16_t lname = rd16(zip + localOffset + 26);
            uint16_t lextra = rd16(zip + localOffset + 28);
            size_t dataOffset = (size_t) localOffset + 30 + lname + lextra;
            if (dataOffset + compSize > zipSize) return false;
            uint8_t* data = malloc((size_t) uncompSize + 1);
            if (!data) return false;
            if (method == 0) {
                if (compSize != uncompSize) { free(data); return false; }
                memcpy(data, zip + dataOffset, uncompSize);
            } else if (method == 8) {
                z_stream zs;
                memset(&zs, 0, sizeof(zs));
                if (inflateInit2(&zs, -MAX_WBITS) != Z_OK) { free(data); return false; }
                zs.next_in = (Bytef*) (zip + dataOffset);
                zs.avail_in = compSize;
                zs.next_out = data;
                zs.avail_out = uncompSize;
                int ret = inflate(&zs, Z_FINISH);
                inflateEnd(&zs);
                if (ret != Z_STREAM_END) { free(data); return false; }
            } else {
                free(data);
                return false;
            }
            data[uncompSize] = '\0';
            out->data = (char*) data;
            out->size = uncompSize;
            return true;
        }
        p += 46 + nameLen + extraLen + commentLen;
    }
    return false;
}

static void copyValue(char* dst, size_t dstSize, const char* src, size_t len) {
    if (len >= dstSize) len = dstSize - 1;
    memcpy(dst, src, len);
    dst[len] = '\0';
}

static void parseHeader(const char* text, Movie* movie) {
    const char* p = text;
    while (*p) {
        const char* e = strchr(p, '\n');
        size_t len = e ? (size_t) (e - p) : strlen(p);
        size_t vlen = len;
        while (vlen && (p[vlen - 1] == '\r' || p[vlen - 1] == '\n')) --vlen;
        if (len > 5 && memcmp(p, "SHA1 ", 5) == 0) {
            copyValue(movie->sha1, sizeof(movie->sha1), p + 5, vlen - 5);
        } else if (len > 18 && memcmp(p, "GBA_Firmware_Bios ", 18) == 0) {
            copyValue(movie->biosSha1, sizeof(movie->biosSha1), p + 18, vlen - 18);
        } else if (len > 5 && memcmp(p, "Core ", 5) == 0) {
            copyValue(movie->core, sizeof(movie->core), p + 5, vlen - 5);
        } else if (len > 9 && memcmp(p, "GameName ", 9) == 0) {
            copyValue(movie->gameName, sizeof(movie->gameName), p + 9, vlen - 9);
        }
        if (!e) break;
        p = e + 1;
    }
}

static bool appendFrame(Movie* movie, const FrameInput* frame) {
    if (movie->count == movie->capacity) {
        size_t next = movie->capacity ? movie->capacity * 2 : 4096;
        FrameInput* grown = realloc(movie->frames, next * sizeof(*grown));
        if (!grown) return false;
        movie->frames = grown;
        movie->capacity = next;
    }
    movie->frames[movie->count++] = *frame;
    return true;
}

static void parseInputLog(const char* text, Movie* movie) {
    const char* p = text;
    while (*p) {
        const char* e = strchr(p, '\n');
        size_t len = e ? (size_t) (e - p) : strlen(p);
        if (len && p[0] == '|') {
            size_t comma = SIZE_MAX;
            for (size_t i = 0; i < len; ++i) {
                if (p[i] == ',') comma = i;
            }
            if (comma != SIZE_MAX && comma + 1 < len) {
                int32_t analog[4] = {0, 0, 0, 100};
                char analogBuf[128];
                size_t analogLen = comma - 1;
                if (analogLen >= sizeof(analogBuf)) analogLen = sizeof(analogBuf) - 1;
                memcpy(analogBuf, p + 1, analogLen);
                analogBuf[analogLen] = '\0';
                char* q = analogBuf;
                for (int a = 0; a < 4; ++a) {
                    char* end = NULL;
                    long value = strtol(q, &end, 10);
                    if (end == q) break;
                    analog[a] = (int32_t) value;
                    q = end;
                    if (*q == ',') ++q;
                }

                char buttons[16];
                memset(buttons, '.', sizeof(buttons));
                size_t b = comma + 1;
                size_t n = 0;
                while (b < len && n < 11) {
                    char c = p[b++];
                    if (c == '|' || c == ' ' || c == '\r') continue;
                    buttons[n++] = c;
                }
                FrameInput frame;
                memset(&frame, 0, sizeof(frame));
                frame.tiltX = (int16_t) analog[0];
                frame.tiltY = (int16_t) analog[1];
                frame.tiltZ = (int16_t) analog[2];
                frame.light = (uint8_t) analog[3];
                /* LibVBANext.Buttons: A=1 B=2 Select=4 Start=8 Right=16
                 * Left=32 Up=64 Down=128 R=256 L=512. */
                if (n > 0 && buttons[0] != '.') frame.keys |= 64;   /* Up */
                if (n > 1 && buttons[1] != '.') frame.keys |= 128;  /* Down */
                if (n > 2 && buttons[2] != '.') frame.keys |= 32;   /* Left */
                if (n > 3 && buttons[3] != '.') frame.keys |= 16;   /* Right */
                if (n > 4 && buttons[4] != '.') frame.keys |= 8;    /* Start */
                if (n > 5 && buttons[5] != '.') frame.keys |= 4;    /* Select */
                if (n > 6 && buttons[6] != '.') frame.keys |= 2;    /* B */
                if (n > 7 && buttons[7] != '.') frame.keys |= 1;    /* A */
                if (n > 8 && buttons[8] != '.') frame.keys |= 512;  /* L */
                if (n > 9 && buttons[9] != '.') frame.keys |= 256;  /* R */
                if (n > 10 && buttons[10] != '.') frame.keys |= POWER_KEY;
                if (!appendFrame(movie, &frame)) {
                    fprintf(stderr, "error: out of memory reading input log\n");
                    return;
                }
            }
        }
        if (!e) break;
        p = e + 1;
    }
}

static bool loadMovie(const char* path, Movie* movie) {
    memset(movie, 0, sizeof(*movie));
    uint8_t* zip = NULL;
    size_t zipSize = 0;
    if (!readFile(path, &zip, &zipSize)) return false;
    Blob header = {0};
    Blob input = {0};
    bool ok = zipExtract(zip, zipSize, "Header.txt", &header) &&
              zipExtract(zip, zipSize, "Input Log.txt", &input);
    if (ok) {
        parseHeader(header.data, movie);
        parseInputLog(input.data, movie);
    }
    free(header.data);
    free(input.data);
    free(zip);
    if (!ok || !movie->count) {
        fprintf(stderr, "error: %s does not contain a usable BizHawk input log\n", path);
        return false;
    }
    return true;
}

static bool parseCheckpoints(Options* opt, const char* list) {
    char* copy = strdup(list);
    if (!copy) return false;
    for (char* tok = strtok(copy, ","); tok; tok = strtok(NULL, ",")) {
        if (opt->checkpointCount >= MAX_CHECKPOINTS) { free(copy); return false; }
        opt->checkpoints[opt->checkpointCount++] = atoi(tok);
    }
    free(copy);
    return true;
}

static void usage(const char* argv0) {
    fprintf(stderr,
        "usage: %s --dll mgba.dll --rom FILE --bios FILE --movie FILE [options]\n"
        "  --save FILE          initial 128 KiB SaveRAM (0xFF padded)\n"
        "  --frames N           movie frames to process, starting at --start-frame\n"
        "                       (default: all remaining movie frames)\n"
        "  --start-frame N      skip the first N movie input entries; the first\n"
        "                       processed input is index N (frame N+1)\n"
        "  --state-in FILE      load the A/normal savestate before the loop\n"
        "  --diff-state-in FILE load the B/candidate savestate before the loop (--diff)\n"
        "  --state-out FILE     save the A/normal savestate after the final frame\n"
        "  --diff-state-out FILE save the B/candidate savestate after the final frame\n"
        "                       (--diff). A state saved at the end of --frames N\n"
        "                       resumes with --start-frame N.\n"
        "  --checkpoint LIST    comma separated frame numbers to dump\n"
        "  --dump-dir DIR       output directory\n"
        "  --prefix NAME        log/dump prefix (default: normal)\n"
        "  --map FILE           linker map for PC/LR symbolization\n"
        "  --diff-map FILE      candidate linker map for --diff\n"
        "  --history N          keep the last N frames in a CRC/state ring buffer\n"
        "  --stack-scan         print heuristic stack return-address candidates at first diff\n"
        "  --stack-depth N      bytes to scan above SP (default 0x400)\n"
        "  --diff               run normal + candidate cores in lockstep and stop at first diff\n"
        "  --settle N           with --diff: give a diff N frames to disappear before failing\n"
        "                       (default 0 = fail on the first differing frame)\n"
        "  --diff-rom FILE      candidate ROM for --diff\n"
        "  --diff-save FILE     candidate SaveRAM for --diff (default: same as --save)\n"
        "  --include-iwram      also compare/dump IWRAM in --diff mode\n"
        "  --diff-regions LIST  comma list: OAM,PAL,VRAM,IO,EWRAM (default all)\n"
        "  --io-full            dump 0x400 bytes of I/O instead of 0x100\n", argv0);
}

static bool parseArgs(int argc, char** argv, Options* opt) {
    memset(opt, 0, sizeof(*opt));
    opt->prefix = "normal";
    opt->frames = -1;
    opt->ioSize = 0x100;
    opt->stackDepth = 0x400;
    opt->diffOam = true;
    opt->diffPal = true;
    opt->diffVram = true;
    opt->diffIo = true;
    opt->diffEwram = true;
    for (int i = 1; i < argc; ++i) {
        const char* a = argv[i];
        const char* v = i + 1 < argc ? argv[i + 1] : NULL;
        if (!strcmp(a, "--dll") && v) { opt->dll = v; ++i; }
        else if (!strcmp(a, "--rom") && v) { opt->rom = v; ++i; }
        else if (!strcmp(a, "--bios") && v) { opt->bios = v; ++i; }
        else if (!strcmp(a, "--movie") && v) { opt->movie = v; ++i; }
        else if (!strcmp(a, "--save") && v) { opt->save = v; ++i; }
        else if (!strcmp(a, "--diff")) { opt->diff = true; }
        else if (!strcmp(a, "--diff-rom") && v) { opt->diffRom = v; ++i; }
        else if (!strcmp(a, "--diff-save") && v) { opt->diffSave = v; ++i; }
        else if (!strcmp(a, "--include-iwram")) { opt->includeIwram = true; }
        else if (!strcmp(a, "--diff-regions") && v) {
            opt->diffOam = strstr(v, "OAM") != NULL;
            opt->diffPal = strstr(v, "PAL") != NULL;
            opt->diffVram = strstr(v, "VRAM") != NULL;
            opt->diffIo = strstr(v, "IO") != NULL;
            opt->diffEwram = strstr(v, "EWRAM") != NULL;
            ++i;
        }
        else if (!strcmp(a, "--io-full")) { opt->ioSize = 0x400; }
        else if (!strcmp(a, "--dump-dir") && v) { opt->dumpDir = v; ++i; }
        else if (!strcmp(a, "--prefix") && v) { opt->prefix = v; ++i; }
        else if (!strcmp(a, "--map") && v) { opt->map = v; ++i; }
        else if (!strcmp(a, "--diff-map") && v) { opt->diffMap = v; ++i; }
        else if (!strcmp(a, "--history") && v) { opt->history = atoi(v); ++i; }
        else if (!strcmp(a, "--stack-scan")) { opt->stackScan = true; }
        else if (!strcmp(a, "--stack-depth") && v) { opt->stackDepth = (size_t) strtoul(v, NULL, 0); ++i; }
        else if (!strcmp(a, "--frames") && v) { opt->frames = atol(v); ++i; }
        else if (!strcmp(a, "--settle") && v) {
            char* end = NULL;
            long value = strtol(v, &end, 0);
            if (end == v || *end || value < 0 || value > 100000) {
                fprintf(stderr, "error: invalid --settle '%s' (expected 0..100000 frames)\n", v);
                return false;
            }
            opt->settle = (int) value;
            opt->settleSet = true;
            ++i;
        }
        else if (!strcmp(a, "--start-frame") && v) {
            char* end = NULL;
            long value = strtol(v, &end, 0);
            if (end == v || *end || value < 0) {
                fprintf(stderr, "error: invalid --start-frame '%s' (expected a non-negative integer)\n", v);
                return false;
            }
            opt->startFrame = value;
            ++i;
        }
        else if (!strcmp(a, "--state-in") && v) { opt->stateIn = v; ++i; }
        else if (!strcmp(a, "--diff-state-in") && v) { opt->diffStateIn = v; ++i; }
        else if (!strcmp(a, "--state-out") && v) { opt->stateOut = v; ++i; }
        else if (!strcmp(a, "--diff-state-out") && v) { opt->diffStateOut = v; ++i; }
        else if (!strcmp(a, "--checkpoint") && v) { if (!parseCheckpoints(opt, v)) return false; ++i; }
        else if (!strcmp(a, "--help") || !strcmp(a, "-h")) { usage(argv[0]); return false; }
        else { fprintf(stderr, "error: unknown argument %s\n", a); return false; }
    }
    if (!opt->dll || !opt->rom || !opt->bios || !opt->movie) {
        usage(argv[0]);
        return false;
    }
    if (opt->settleSet && !opt->diff) {
        fprintf(stderr, "error: --settle requires --diff\n");
        return false;
    }
    if (opt->diff && !opt->diffRom) {
        fprintf(stderr, "error: --diff requires --diff-rom\n");
        return false;
    }
    if (opt->diff) {
        bool haveA = opt->stateIn != NULL;
        bool haveB = opt->diffStateIn != NULL;
        if (haveA != haveB) {
            fprintf(stderr, "error: --diff resume needs both --state-in (A/normal) and "
                "--diff-state-in (B/candidate); got only %s\n",
                haveA ? "--state-in" : "--diff-state-in");
            return false;
        }
        if (opt->startFrame > 0 && !haveA) {
            fprintf(stderr, "warning: --diff --start-frame %ld without state inputs; "
                "both cores start from reset while the movie timeline is shifted\n",
                opt->startFrame);
        }
    } else if (opt->diffStateIn || opt->diffStateOut) {
        fprintf(stderr, "error: --diff-state-in/--diff-state-out require --diff "
            "(use --state-in/--state-out for a single core)\n");
        return false;
    }
    if (opt->stateIn && opt->startFrame == 0) {
        fprintf(stderr, "warning: --state-in without --start-frame; the movie timeline "
            "may not match the loaded state\n");
    }
    return true;
}

static bool writeBlob(const char* path, const void* data, size_t size) {
    FILE* f = fopen(path, "wb");
    if (!f) {
        fprintf(stderr, "error: cannot write %s\n", path);
        return false;
    }
    bool ok = fwrite(data, 1, size, f) == size;
    fclose(f);
    if (!ok) fprintf(stderr, "error: short write to %s\n", path);
    return ok;
}

/* Serialize one core with BizStartGetState/BizFinishGetState (internally
 * mCoreSaveStateNamed(..., SAVESTATE_SAVEDATA)) and write it to path. */
static bool saveStateFile(void* ctx, const char* path, const char* label, long frame,
    BizStartGetStateFn startGetState, BizFinishGetStateFn finishGetState) {
    void* vf = NULL;
    int size = 0;
    if (!startGetState(ctx, &vf, &size) || !vf || size <= 0) {
        fprintf(stderr, "error: cannot serialize %s savestate\n", label);
        return false;
    }
    uint8_t* data = malloc((size_t) size);
    if (!data) {
        fprintf(stderr, "error: out of memory saving %s savestate\n", label);
        return false;
    }
    finishGetState(vf, data, size);
    bool ok = writeBlob(path, data, (size_t) size);
    free(data);
    if (ok) {
        fprintf(stderr, "saved %s state at frame %ld: %s (%d bytes)\n",
            label, frame, path, size);
    }
    return ok;
}

/* Load a savestate with BizPutState (mCoreLoadStateNamed(...)). */
static bool loadStateFile(void* ctx, const char* path, const char* label, BizPutStateFn putState) {
    uint8_t* data = NULL;
    size_t size = 0;
    if (!readFile(path, &data, &size)) {
        fprintf(stderr, "error: cannot read %s savestate %s\n", label, path);
        return false;
    }
    if (size == 0) {
        free(data);
        fprintf(stderr, "error: %s savestate %s is empty\n", label, path);
        return false;
    }
    if (size > INT32_MAX) {
        free(data);
        fprintf(stderr, "error: %s savestate %s is too large (%zu bytes)\n", label, path, size);
        return false;
    }
    int ok = putState(ctx, data, (int) size);
    free(data);
    if (!ok) {
        fprintf(stderr, "error: %s savestate %s is corrupt or incompatible with this ROM/core\n",
            label, path);
        return false;
    }
    fprintf(stderr, "loaded %s state: %s (%zu bytes)\n", label, path, size);
    return true;
}

static void logState(const MemoryAreas* mem, FILE* log, int frame) {
    const uint8_t* mmio = (const uint8_t*) mem->mmio;
    const uint8_t* iwram = (const uint8_t*) mem->iwram;
    uint16_t disp = (uint16_t) (mmio[0] | (mmio[1] << 8));
    uint16_t mainMode = (uint16_t) (iwram[0xBDE] | (iwram[0xBDF] << 8));
    uint16_t sub1 = (uint16_t) (iwram[0xBE0] | (iwram[0xBE1] << 8));
    uint16_t sub2 = (uint16_t) (iwram[0xBE2] | (iwram[0xBE3] << 8));
    uint8_t event = iwram[0xB87];
    uint8_t area = iwram[0x2C];
    uint8_t room = iwram[0x2D];
    uint8_t nav = iwram[0x48];
    fprintf(log, "%d %04X %04X %04X %04X %d %d %d %d\n",
        frame, disp, mainMode, sub1, sub2, event, area, room, nav);
    fflush(log);
}

static bool dumpRegions(const MemoryAreas* mem, const Options* opt, const char* prefix, int frame) {
    if (!opt->dumpDir) return true;
    char path[1024];
    struct { const void* ptr; size_t size; const char* suffix; } regions[] = {
        {mem->oam, 0x400, "oam"},
        {mem->palram, 0x400, "pal"},
        {mem->vram, 0x18000, "vram"},
        {mem->mmio, opt->ioSize, "io"},
        {mem->iwram, 0x8000, "iwram"},
        {mem->wram, 0x40000, "ewram"},
    };
    for (size_t i = 0; i < sizeof(regions) / sizeof(regions[0]); ++i) {
        snprintf(path, sizeof(path), "%s/%s_%06d_%s.bin",
            opt->dumpDir, prefix, frame, regions[i].suffix);
        if (!writeBlob(path, regions[i].ptr, regions[i].size)) return false;
    }
    return true;
}

static bool dumpCheckpoint(const MemoryAreas* mem, const Options* opt, FILE* log, int frame) {
    logState(mem, log, frame);
    return dumpRegions(mem, opt, opt->prefix, frame);
}

static long firstDiff(const void* a, const void* b, size_t size) {
    const uint8_t* pa = (const uint8_t*) a;
    const uint8_t* pb = (const uint8_t*) b;
    for (size_t i = 0; i < size; ++i) {
        if (pa[i] != pb[i]) return (long) i;
    }
    return -1;
}

static RegionDiff scanRegions(const DiffRegion* regions, size_t count) {
    RegionDiff diff;
    memset(&diff, 0, sizeof(diff));
    diff.offset = -1;
    for (size_t r = 0; r < count; ++r) {
        long off = firstDiff(regions[r].a, regions[r].b, regions[r].size);
        if (off < 0) continue;
        diff.found = true;
        diff.region = r;
        diff.offset = off;
        diff.a = ((const uint8_t*) regions[r].a)[off];
        diff.b = ((const uint8_t*) regions[r].b)[off];
        return diff;
    }
    return diff;
}

static int symbolCompare(const void* a, const void* b) {
    const Symbol* sa = (const Symbol*) a;
    const Symbol* sb = (const Symbol*) b;
    if (sa->addr < sb->addr) return -1;
    if (sa->addr > sb->addr) return 1;
    return 0;
}

static bool loadMap(const char* path, SymbolTable* table) {
    memset(table, 0, sizeof(*table));
    if (!path) return true;
    FILE* f = fopen(path, "r");
    if (!f) {
        fprintf(stderr, "warning: cannot open map %s\n", path);
        return false;
    }
    size_t capacity = 0;
    char line[1024];
    while (fgets(line, sizeof(line), f)) {
        char* p = line;
        while (*p && isspace((unsigned char) *p)) ++p;
        if (p[0] != '0' || (p[1] != 'x' && p[1] != 'X')) continue;
        char* end = NULL;
        unsigned long addr = strtoul(p, &end, 16);
        if (end == p) continue;
        p = end;
        while (*p && isspace((unsigned char) *p)) ++p;
        char name[128];
        size_t n = 0;
        while (*p && !isspace((unsigned char) *p) && *p != '=' && n + 1 < sizeof(name)) {
            name[n++] = *p++;
        }
        name[n] = '\0';
        if (!n || !strcmp(name, ".") || !strcmp(name, "*fill*")) continue;
        /* Ignore linker-script constants (e.g. gNumMusicPlayers = 0x8);
         * only keep addresses that can be real CPU/bus targets. */
        bool valid = (addr >= 0x02000000 && addr < 0x02040000) ||
                     (addr >= 0x03000000 && addr < 0x03008000) ||
                     (addr >= 0x04000000 && addr < 0x04000400) ||
                     (addr >= 0x05000000 && addr < 0x05000400) ||
                     (addr >= 0x06000000 && addr < 0x06018000) ||
                     (addr >= 0x07000000 && addr < 0x07000400) ||
                     (addr >= 0x08000000 && addr < 0x0A000000);
        if (!valid) continue;
        if (table->count == capacity) {
            capacity = capacity ? capacity * 2 : 4096;
            Symbol* grown = realloc(table->symbols, capacity * sizeof(*grown));
            if (!grown) {
                fclose(f);
                return false;
            }
            table->symbols = grown;
        }
        table->symbols[table->count].addr = (uint32_t) addr;
        snprintf(table->symbols[table->count].name,
            sizeof(table->symbols[table->count].name), "%s", name);
        ++table->count;
    }
    fclose(f);
    qsort(table->symbols, table->count, sizeof(*table->symbols), symbolCompare);
    return true;
}

static void formatSymbol(const SymbolTable* table, uint32_t value, char* out, size_t outSize) {
    uint32_t lookup = value & ~1u;
    if (!table || !table->count) {
        snprintf(out, outSize, "%08X", value);
        return;
    }
    size_t lo = 0;
    size_t hi = table->count;
    while (lo < hi) {
        size_t mid = (lo + hi) / 2;
        if (table->symbols[mid].addr <= lookup) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }
    if (lo == 0) {
        snprintf(out, outSize, "%08X", value);
        return;
    }
    const Symbol* sym = &table->symbols[lo - 1];
    snprintf(out, outSize, "%s+0x%X", sym->name, lookup - sym->addr);
}

static void printRegs(const char* label, void* ctx, BizGetRegistersFn getRegisters,
    const SymbolTable* map) {
    int regs[18] = {0};
    getRegisters(ctx, regs);
    char pc[192];
    char lr[192];
    formatSymbol(map, (uint32_t) regs[15], pc, sizeof(pc));
    formatSymbol(map, (uint32_t) regs[14], lr, sizeof(lr));
    fprintf(stderr, "%s PC=%08X (%s) LR=%08X (%s) SP=%08X CPSR=%08X\n",
        label, (uint32_t) regs[15], pc, (uint32_t) regs[14], lr,
        (uint32_t) regs[13], (uint32_t) regs[16]);
}

static void stackScan(const char* label, void* ctx, BizReadBusFn readBus,
    const SymbolTable* map, uint32_t sp, size_t depth) {
    if (!readBus || sp < 0x02000000 || sp >= 0x03008000) return;
    fprintf(stderr, "%s stack candidates (SP=%08X, depth=0x%X):\n",
        label, sp, (unsigned) depth);
    uint32_t last = 0;
    unsigned printed = 0;
    for (size_t off = 0; off + 4 <= depth; off += 4) {
        uint32_t addr = sp + (uint32_t) off;
        uint32_t value = (uint32_t) readBus(ctx, addr) |
            ((uint32_t) readBus(ctx, addr + 1) << 8) |
            ((uint32_t) readBus(ctx, addr + 2) << 16) |
            ((uint32_t) readBus(ctx, addr + 3) << 24);
        uint32_t code = value & ~1u;
        bool valid = (code >= 0x02000000 && code < 0x02040000) ||
                     (code >= 0x03000000 && code < 0x03008000) ||
                     (code >= 0x08000000 && code < 0x0A000000);
        if (!valid || code == last) continue;

        bool call = false;
        if (code >= 2) {
            uint16_t hw = (uint16_t) (readBus(ctx, code - 2) |
                (readBus(ctx, code - 1) << 8));
            /* Thumb BL/BLX return address: second halfword starts 11111. */
            call = (hw & 0xF800) == 0xF800;
        }
        if (!call && code >= 4) {
            uint32_t prev = (uint32_t) readBus(ctx, code - 4) |
                ((uint32_t) readBus(ctx, code - 3) << 8) |
                ((uint32_t) readBus(ctx, code - 2) << 16) |
                ((uint32_t) readBus(ctx, code - 1) << 24);
            uint8_t op = (uint8_t) (prev >> 24);
            call = op == 0x0B || op == 0x0A; /* ARM BL / BLX */
        }

        char sym[192];
        formatSymbol(map, code, sym, sizeof(sym));
        fprintf(stderr, "  [SP+0x%03X] %08X %-40s %s\n",
            (unsigned) off, value, sym, call ? "(call)" : "(candidate)");
        last = code;
        if (++printed >= 32) break;
    }
}

static bool historyInit(History* history, size_t capacity) {
    memset(history, 0, sizeof(*history));
    if (!capacity) return true;
    history->entries = calloc(capacity, sizeof(*history->entries));
    if (!history->entries) return false;
    history->capacity = capacity;
    return true;
}

static void historyRecord(History* history, const MemoryAreas* mem, const FrameInput* in,
    long frame, void* ctx, BizGetRegistersFn getRegisters, const Options* opt) {
    if (!history->capacity) return;
    HistoryEntry* e = &history->entries[history->next];
    memset(e, 0, sizeof(*e));
    e->frame = frame;
    e->keys = in->keys & 0x3FF;
    e->light = in->light;
    e->tiltX = in->tiltX;
    e->tiltY = in->tiltY;
    e->tiltZ = in->tiltZ;
    const uint8_t* mmio = (const uint8_t*) mem->mmio;
    const uint8_t* iwram = (const uint8_t*) mem->iwram;
    e->disp = (uint16_t) (mmio[0] | (mmio[1] << 8));
    e->mainMode = (uint16_t) (iwram[0xBDE] | (iwram[0xBDF] << 8));
    e->sub1 = (uint16_t) (iwram[0xBE0] | (iwram[0xBE1] << 8));
    e->sub2 = (uint16_t) (iwram[0xBE2] | (iwram[0xBE3] << 8));
    e->event = iwram[0xB87];
    e->area = iwram[0x2C];
    e->room = iwram[0x2D];
    e->nav = iwram[0x48];
    e->crc[0] = (uint32_t) crc32(0, (const Bytef*) mem->oam, 0x400);
    e->crc[1] = (uint32_t) crc32(0, (const Bytef*) mem->palram, 0x400);
    e->crc[2] = (uint32_t) crc32(0, (const Bytef*) mem->vram, 0x18000);
    e->crc[3] = (uint32_t) crc32(0, (const Bytef*) mem->mmio, opt->ioSize);
    e->crc[4] = (uint32_t) crc32(0, (const Bytef*) mem->wram, 0x40000);
    if (getRegisters) {
        int regs[18] = {0};
        getRegisters(ctx, regs);
        e->pc = (uint32_t) regs[15];
        e->lr = (uint32_t) regs[14];
        e->sp = (uint32_t) regs[13];
        e->cpsr = (uint32_t) regs[16];
    }
    history->next = (history->next + 1) % history->capacity;
    if (history->count < history->capacity) ++history->count;
}

static bool historyWrite(const History* history, const Options* opt, const char* prefix,
    const SymbolTable* map) {
    if (!history->count) return true;
    const char* dir = opt->dumpDir ? opt->dumpDir : ".";
    char path[1024];
    snprintf(path, sizeof(path), "%s/%s_history.csv", dir, prefix);
    FILE* f = fopen(path, "w");
    if (!f) {
        fprintf(stderr, "warning: cannot write %s\n", path);
        return false;
    }
    fprintf(f, "frame,keys,light,tiltX,tiltY,tiltZ,disp,main,s1,s2,event,area,room,nav,"
               "crc_oam,crc_pal,crc_vram,crc_io,crc_ewram,pc,pc_sym,lr,lr_sym,sp,cpsr\n");
    size_t start = (history->next + history->capacity - history->count) % history->capacity;
    for (size_t i = 0; i < history->count; ++i) {
        const HistoryEntry* e = &history->entries[(start + i) % history->capacity];
        char pc[192];
        char lr[192];
        formatSymbol(map, e->pc, pc, sizeof(pc));
        formatSymbol(map, e->lr, lr, sizeof(lr));
        fprintf(f, "%ld,%08X,%u,%d,%d,%d,%04X,%04X,%04X,%04X,%u,%u,%u,%u,"
                   "%08X,%08X,%08X,%08X,%08X,%08X,%s,%08X,%s,%08X,%08X\n",
            e->frame, e->keys, e->light, e->tiltX, e->tiltY, e->tiltZ,
            e->disp, e->mainMode, e->sub1, e->sub2, e->event, e->area, e->room, e->nav,
            e->crc[0], e->crc[1], e->crc[2], e->crc[3], e->crc[4],
            e->pc, pc, e->lr, lr, e->sp, e->cpsr);
    }
    fclose(f);
    return true;
}

/* Print and dump one diff observation: the first differing byte, both cores'
 * state, registers and (optionally) stack candidates, plus full region dumps
 * and history. Used for an immediate first diff and for a durable diff after
 * the settle window. Returns false on a dump/IO error. */
static bool reportDiff(const Options* opt, const char* label, long frame,
    const DiffRegion* regions, const RegionDiff* diff,
    const MemoryAreas* memA, const MemoryAreas* memB, void* ctxA, void* ctxB,
    BizGetRegistersFn getRegisters, BizReadBusFn readBus,
    const SymbolTable* mapA, const SymbolTable* mapB,
    History* historyA, History* historyB,
    const char* prefixA, const char* prefixB) {
    fprintf(stderr, "%s: frame=%ld region=%s offset=0x%lX a=%02X b=%02X\n",
        label, frame, regions[diff->region].name, diff->offset, diff->a, diff->b);
    logState(memA, stderr, (int) frame);
    logState(memB, stderr, (int) frame);
    printRegs("A normal", ctxA, getRegisters, mapA);
    printRegs("B candidate", ctxB, getRegisters, mapB);
    if (opt->stackScan) {
        int regsA[18] = {0};
        int regsB[18] = {0};
        getRegisters(ctxA, regsA);
        getRegisters(ctxB, regsB);
        stackScan("A normal", ctxA, readBus, mapA, (uint32_t) regsA[13], opt->stackDepth);
        stackScan("B candidate", ctxB, readBus, mapB, (uint32_t) regsB[13], opt->stackDepth);
    }
    if (!dumpRegions(memA, opt, prefixA, (int) frame) ||
        !dumpRegions(memB, opt, prefixB, (int) frame)) {
        return false;
    }
    historyWrite(historyA, opt, prefixA, mapA);
    historyWrite(historyB, opt, prefixB, mapB);
    return true;
}

int main(int argc, char** argv) {
    Options opt;
    if (!parseArgs(argc, argv, &opt)) return 1;
    Movie movie;
    if (!loadMovie(opt.movie, &movie)) return 1;

    uint8_t* rom = NULL;
    size_t romSize = 0;
    uint8_t* bios = NULL;
    size_t biosSize = 0;
    if (!readFile(opt.rom, &rom, &romSize) || !readFile(opt.bios, &bios, &biosSize)) return 1;
    if (biosSize != 16384) {
        fprintf(stderr, "error: BIOS must be 16384 bytes\n");
        return 1;
    }

    if (opt.startFrame > (long) movie.count) {
        fprintf(stderr, "error: --start-frame %ld is past the end of the movie (%zu inputs)\n",
            opt.startFrame, movie.count);
        return 1;
    }
    {
        long available = (long) movie.count - opt.startFrame;
        if (opt.frames < 0) {
            opt.frames = available;
        } else if (opt.frames > available) {
            fprintf(stderr, "warning: --frames %ld exceeds %ld remaining movie inputs; "
                "clamping\n", opt.frames, available);
            opt.frames = available;
        }
    }

    HMODULE dll = LoadLibraryA(opt.dll);
    if (!dll) {
        fprintf(stderr, "error: cannot load %s (error %lu)\n", opt.dll, GetLastError());
        return 1;
    }
    BizCreateFn BizCreate = (BizCreateFn) GetProcAddress(dll, "BizCreate");
    BizResetFn BizReset = (BizResetFn) GetProcAddress(dll, "BizReset");
    BizAdvanceFn BizAdvance = (BizAdvanceFn) GetProcAddress(dll, "BizAdvance");
    BizDestroyFn BizDestroy = (BizDestroyFn) GetProcAddress(dll, "BizDestroy");
    BizGetMemoryAreasFn BizGetMemoryAreas = (BizGetMemoryAreasFn) GetProcAddress(dll, "BizGetMemoryAreas");
    BizPutSaveRamFn BizPutSaveRam = (BizPutSaveRamFn) GetProcAddress(dll, "BizPutSaveRam");
    BizGetRegistersFn BizGetRegisters = (BizGetRegistersFn) GetProcAddress(dll, "BizGetRegisters");
    BizReadBusFn BizReadBus = (BizReadBusFn) GetProcAddress(dll, "BizReadBus");
    BizStartGetStateFn BizStartGetState = (BizStartGetStateFn) GetProcAddress(dll, "BizStartGetState");
    BizFinishGetStateFn BizFinishGetState = (BizFinishGetStateFn) GetProcAddress(dll, "BizFinishGetState");
    BizPutStateFn BizPutState = (BizPutStateFn) GetProcAddress(dll, "BizPutState");
    bool needsState = opt.stateIn || opt.diffStateIn || opt.stateOut || opt.diffStateOut;
    bool haveState = BizStartGetState && BizFinishGetState && BizPutState;
    if (!BizCreate || !BizReset || !BizAdvance || !BizDestroy || !BizGetMemoryAreas ||
        !BizPutSaveRam || (opt.diff && !BizGetRegisters) ||
        (opt.stackScan && !BizReadBus)) {
        fprintf(stderr, "error: mgba.dll is missing Biz* exports\n");
        return 1;
    }
    if (needsState && !haveState) {
        fprintf(stderr, "error: state I/O requested but the core is missing "
            "BizStartGetState/BizFinishGetState/BizPutState\n");
        return 1;
    }

    void* ctx = BizCreate(bios, rom, (int) romSize, NULL, 0);
    if (!ctx) {
        fprintf(stderr, "error: BizCreate failed\n");
        return 1;
    }

    static uint8_t saveRam[128 * 1024];
    memset(saveRam, 0xFF, sizeof(saveRam));
    if (opt.save) {
        uint8_t* fileSave = NULL;
        size_t fileSaveSize = 0;
        if (!readFile(opt.save, &fileSave, &fileSaveSize)) return 1;
        memcpy(saveRam, fileSave, fileSaveSize < sizeof(saveRam) ? fileSaveSize : sizeof(saveRam));
        free(fileSave);
    }
    BizPutSaveRam(ctx, saveRam, sizeof(saveRam));
    if (opt.dumpDir) {
        CreateDirectoryA(opt.dumpDir, NULL);
    }

    if (opt.diff) {
        uint8_t* romB = NULL;
        size_t romBSize = 0;
        if (!readFile(opt.diffRom, &romB, &romBSize)) return 1;
        void* ctxB = BizCreate(bios, romB, (int) romBSize, NULL, 0);
        if (!ctxB) {
            fprintf(stderr, "error: BizCreate failed for candidate ROM\n");
            return 1;
        }

        static uint8_t diffSaveRam[128 * 1024];
        memcpy(diffSaveRam, saveRam, sizeof(diffSaveRam));
        if (opt.diffSave) {
            uint8_t* fileSave = NULL;
            size_t fileSaveSize = 0;
            if (!readFile(opt.diffSave, &fileSave, &fileSaveSize)) return 1;
            memcpy(diffSaveRam, fileSave,
                fileSaveSize < sizeof(diffSaveRam) ? fileSaveSize : sizeof(diffSaveRam));
            free(fileSave);
        }
        BizPutSaveRam(ctxB, diffSaveRam, sizeof(diffSaveRam));

        if (opt.stateIn && opt.diffStateIn) {
            if (!loadStateFile(ctx, opt.stateIn, "A/normal", BizPutState) ||
                !loadStateFile(ctxB, opt.diffStateIn, "B/candidate", BizPutState)) {
                return 1;
            }
        }

        MemoryAreas memA;
        MemoryAreas memB;
        BizGetMemoryAreas(ctx, &memA);
        BizGetMemoryAreas(ctxB, &memB);

        SymbolTable mapA;
        SymbolTable mapB;
        loadMap(opt.map, &mapA);
        loadMap(opt.diffMap ? opt.diffMap : opt.map, &mapB);
        History historyA;
        History historyB;
        if (!historyInit(&historyA, (size_t) opt.history) ||
            !historyInit(&historyB, (size_t) opt.history)) {
            fprintf(stderr, "error: cannot allocate history ring buffer\n");
            return 1;
        }

        uint32_t* vbuffA = calloc(256 * 256, sizeof(uint32_t));
        uint32_t* vbuffB = calloc(256 * 256, sizeof(uint32_t));
        int16_t* sbuffA = calloc(2048, sizeof(int16_t));
        int16_t* sbuffB = calloc(2048, sizeof(int16_t));
        if (!vbuffA || !vbuffB || !sbuffA || !sbuffB) return 1;

        char prefixA[512];
        char prefixB[512];
        snprintf(prefixA, sizeof(prefixA), "%s_a", opt.prefix);
        snprintf(prefixB, sizeof(prefixB), "%s_b", opt.prefix);

        bool failed = false;
        long lastFrame = opt.startFrame;
        long endFrame = opt.startFrame + opt.frames;
        long transientCount = 0;
        PendingDiff pending;
        memset(&pending, 0, sizeof(pending));
        clock_t started = clock();
        for (long i = opt.startFrame; i < opt.startFrame + opt.frames; ++i) {
            FrameInput* in = &movie.frames[i];
            long frame = i + 1;
            lastFrame = frame;
            uint32_t keys = in->keys & 0x3FF;
            if (in->keys & POWER_KEY) {
                BizReset(ctx);
                BizReset(ctxB);
                BizGetMemoryAreas(ctx, &memA);
                BizGetMemoryAreas(ctxB, &memB);
            }
            int nsampA = 0;
            int nsampB = 0;
            int64_t rtc = 1262304000LL + ((int64_t) frame * 4389 >> 18);
            uint8_t luma = (uint8_t) (255 - in->light);
            BizAdvance(ctx, (int) keys, vbuffA, &nsampA, sbuffA, rtc,
                in->tiltX, in->tiltY, in->tiltZ, luma);
            BizAdvance(ctxB, (int) keys, vbuffB, &nsampB, sbuffB, rtc,
                in->tiltX, in->tiltY, in->tiltZ, luma);

            historyRecord(&historyA, &memA, in, frame, ctx, BizGetRegisters, &opt);
            historyRecord(&historyB, &memB, in, frame, ctxB, BizGetRegisters, &opt);

            DiffRegion regions[6];
            size_t nregions = 0;
            if (opt.diffOam) regions[nregions++] = (DiffRegion) {memA.oam, memB.oam, 0x400, "OAM"};
            if (opt.diffPal) regions[nregions++] = (DiffRegion) {memA.palram, memB.palram, 0x400, "PAL"};
            if (opt.diffVram) regions[nregions++] = (DiffRegion) {memA.vram, memB.vram, 0x18000, "VRAM"};
            if (opt.diffIo) regions[nregions++] = (DiffRegion) {memA.mmio, memB.mmio, opt.ioSize, "IO"};
            if (opt.diffEwram) regions[nregions++] = (DiffRegion) {memA.wram, memB.wram, 0x40000, "EWRAM"};
            if (opt.includeIwram) {
                regions[nregions++] = (DiffRegion) {memA.iwram, memB.iwram, 0x8000, "IWRAM"};
            }

            RegionDiff diff = scanRegions(regions, nregions);
            if (!pending.active) {
                if (!diff.found) continue;
                if (opt.settle <= 0) {
                    failed = true;
                    if (!reportDiff(&opt, "first diff", frame, regions, &diff,
                            &memA, &memB, ctx, ctxB, BizGetRegisters, BizReadBus,
                            &mapA, &mapB, &historyA, &historyB, prefixA, prefixB)) {
                        return 1;
                    }
                    break;
                }
                /* Record the observation, then keep both cores running so a
                 * mid-frame copy can finish on the slower timeline. */
                pending.active = true;
                pending.firstFrame = frame;
                pending.firstRegion = diff.region;
                pending.firstOffset = diff.offset;
                pending.firstA = diff.a;
                pending.firstB = diff.b;
                pending.lastRegion = diff.region;
                pending.lastOffset = diff.offset;
                pending.lastA = diff.a;
                pending.lastB = diff.b;
                pending.deadline = frame + opt.settle;
                if (pending.deadline > endFrame) pending.deadline = endFrame;
                if (frame >= pending.deadline) {
                    /* The window is already over: only possible when the diff
                     * lands on the last processed frame. Treat as durable. */
                    failed = true;
                    fprintf(stderr, "settle: window exhausted at frame=%ld with diffs still "
                        "present; reporting durable diff\n", frame);
                    fprintf(stderr, "first diff: frame=%ld region=%s offset=0x%lX a=%02X b=%02X\n",
                        pending.firstFrame, regions[pending.firstRegion].name,
                        pending.firstOffset, pending.firstA, pending.firstB);
                    if (!reportDiff(&opt, "durable diff", frame, regions, &diff,
                            &memA, &memB, ctx, ctxB, BizGetRegisters, BizReadBus,
                            &mapA, &mapB, &historyA, &historyB, prefixA, prefixB)) {
                        return 1;
                    }
                    break;
                }
                fprintf(stderr, "settle: diff at frame=%ld region=%s offset=0x%lX a=%02X b=%02X; "
                    "waiting %ld frame(s)\n", frame, regions[diff.region].name,
                    diff.offset, diff.a, diff.b, pending.deadline - frame);
                continue;
            }

            if (!diff.found) {
                if (frame >= pending.deadline) {
                    fprintf(stderr, "TRANSIENT diff at frame %ld settled after %ld frames\n",
                        pending.firstFrame, frame - pending.firstFrame);
                    ++transientCount;
                    pending.active = false;
                }
                continue;
            }

            bool newSignature = diff.region != pending.lastRegion ||
                diff.offset != pending.lastOffset ||
                diff.a != pending.lastA || diff.b != pending.lastB;
            if (newSignature) {
                /* A different byte pair is diverging while we wait: restart
                 * the window from this frame, bounded by the run end. */
                pending.lastRegion = diff.region;
                pending.lastOffset = diff.offset;
                pending.lastA = diff.a;
                pending.lastB = diff.b;
                pending.deadline = frame + opt.settle;
                if (pending.deadline > endFrame) pending.deadline = endFrame;
                fprintf(stderr, "settle: new diff at frame=%ld region=%s offset=0x%lX "
                    "a=%02X b=%02X; extending window to frame %ld\n",
                    frame, regions[diff.region].name, diff.offset, diff.a, diff.b,
                    pending.deadline);
            }
            if (frame >= pending.deadline) {
                failed = true;
                fprintf(stderr, "settle: window exhausted at frame=%ld with diffs still "
                    "present (first observed at frame=%ld); reporting durable diff\n",
                    frame, pending.firstFrame);
                fprintf(stderr, "first diff: frame=%ld region=%s offset=0x%lX a=%02X b=%02X\n",
                    pending.firstFrame, regions[pending.firstRegion].name,
                    pending.firstOffset, pending.firstA, pending.firstB);
                if (!reportDiff(&opt, "durable diff", frame, regions, &diff,
                        &memA, &memB, ctx, ctxB, BizGetRegisters, BizReadBus,
                        &mapA, &mapB, &historyA, &historyB, prefixA, prefixB)) {
                    return 1;
                }
                break;
            }
        }

        double seconds = (double) (clock() - started) / CLOCKS_PER_SEC;
        fprintf(stderr, "diff ran %ld frames in %.3f s (%.1f fps)\n",
            opt.frames, seconds, seconds > 0 ? opt.frames / seconds : 0.0);
        if (transientCount) {
            fprintf(stderr, "settle: %ld transient diff(s) ignored\n", transientCount);
        }
        if (failed) {
            fprintf(stderr, "PARITY: FAIL\n");
        } else {
            fprintf(stderr, "PARITY: PASS (%ld frames)\n", opt.frames);
        }

        if (opt.stateOut && !saveStateFile(ctx, opt.stateOut, "A/normal", lastFrame,
                BizStartGetState, BizFinishGetState)) {
            return 1;
        }
        if (opt.diffStateOut && !saveStateFile(ctxB, opt.diffStateOut, "B/candidate", lastFrame,
                BizStartGetState, BizFinishGetState)) {
            return 1;
        }

        free(vbuffA);
        free(vbuffB);
        free(sbuffA);
        free(sbuffB);
        free(historyA.entries);
        free(historyB.entries);
        free(mapA.symbols);
        free(mapB.symbols);
        BizDestroy(ctx);
        BizDestroy(ctxB);
        free(rom);
        free(romB);
        free(bios);
        free(movie.frames);
        FreeLibrary(dll);
        return failed ? 1 : 0;
    }

    MemoryAreas mem;
    if (opt.stateIn && !loadStateFile(ctx, opt.stateIn, "A/normal", BizPutState)) return 1;
    BizGetMemoryAreas(ctx, &mem);
    SymbolTable map;
    loadMap(opt.map, &map);
    History history;
    if (!historyInit(&history, (size_t) opt.history)) {
        fprintf(stderr, "error: cannot allocate history ring buffer\n");
        return 1;
    }

    FILE* log = NULL;
    if (opt.dumpDir) {
        CreateDirectoryA(opt.dumpDir, NULL);
        char path[1024];
        snprintf(path, sizeof(path), "%s/%s_log.txt", opt.dumpDir, opt.prefix);
        log = fopen(path, "w");
        if (!log) {
            fprintf(stderr, "error: cannot write %s\n", path);
            return 1;
        }
        fprintf(log, "# frame disp main s1 s2 event area room nav\n");
        fflush(log);
    }

    uint32_t* vbuff = calloc(256 * 256, sizeof(uint32_t));
    int16_t* sbuff = calloc(2048, sizeof(int16_t));
    if (!vbuff || !sbuff) return 1;

    clock_t started = clock();
    long lastFrame = opt.startFrame;
    for (long i = opt.startFrame; i < opt.startFrame + opt.frames; ++i) {
        FrameInput* in = &movie.frames[i];
        long frame = i + 1;
        lastFrame = frame;
        uint32_t keys = in->keys & 0x3FF;
        if (in->keys & POWER_KEY) {
            BizReset(ctx);
            BizGetMemoryAreas(ctx, &mem);
        }
        int nsamp = 0;
        int64_t rtc = 1262304000LL + ((int64_t) frame * 4389 >> 18);
        uint8_t luma = (uint8_t) (255 - in->light);
        BizAdvance(ctx, (int) keys, vbuff, &nsamp, sbuff, rtc,
            in->tiltX, in->tiltY, in->tiltZ, luma);
        historyRecord(&history, &mem, in, frame, ctx, BizGetRegisters, &opt);
        for (int c = 0; c < opt.checkpointCount; ++c) {
            if (frame == opt.checkpoints[c]) {
                if (!dumpCheckpoint(&mem, &opt, log, (int) frame)) return 1;
            }
        }
    }

    double seconds = (double) (clock() - started) / CLOCKS_PER_SEC;
    fprintf(stderr, "ran %ld frames in %.3f s (%.1f fps)\n",
        opt.frames, seconds, seconds > 0 ? opt.frames / seconds : 0.0);

    if (opt.stateOut && !saveStateFile(ctx, opt.stateOut, "A/normal", lastFrame,
            BizStartGetState, BizFinishGetState)) {
        return 1;
    }

    if (history.count) {
        historyWrite(&history, &opt, opt.prefix, &map);
    }
    if (log) fclose(log);
    free(history.entries);
    free(map.symbols);
    free(vbuff);
    free(sbuff);
    BizDestroy(ctx);
    free(rom);
    free(bios);
    free(movie.frames);
    FreeLibrary(dll);
    return 0;
}
