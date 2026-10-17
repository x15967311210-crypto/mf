/*
 * Headless mGBA harness.
 *
 * This is the dynamic half of SHIFT-001.  It loads a ROM, runs a fixed number
 * of frames, and reads fixed IWRAM addresses from linker.ld.  It deliberately
 * contains no ROM data and no game assets; the ROM is a runtime argument.
 *
 * Build with tests/emulator/build_harness.sh against an mGBA source/build tree.
 *
 * Scenarios:
 *   boot_smoke  (default)  run N frames, prove the main loop is alive.
 *   start                  press Start on the title screen, prove the
 *                          file-select/intro transition leaves the display on.
 *   input                  replay a `frame keys` input file (QA-002).  The
 *                          format is one `frame keys` pair per line; keys is
 *                          the GBA key bitmask (1=A, 2=B, 4=Select, 8=Start,
 *                          16=Right, 32=Left, 64=Up, 128=Down, 256=R, 512=L).
 *                          Lines starting with `#` are comments.
 *
 * The legacy form `harness rom.gba [frames]` keeps the boot-smoke output and
 * exit semantics unchanged.
 */
#include <mgba/core/config.h>
#include <mgba/core/core.h>
#include <mgba/gba/core.h>
#include <mgba/internal/gba/gba.h>
#include <mgba/internal/gba/input.h>
#include <mgba/internal/gba/memory.h>

#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define IWRAM_FRAME_COUNTER 0x03000002
#define IWRAM_CURRENT_AREA 0x0300002C
#define IWRAM_MAIN_MODE 0x03000BDE
#define IWRAM_SUB_MODE 0x03000BE0
#define IWRAM_SUB_MODE1 0x03000BE0
#define IWRAM_SUB_MODE2 0x03000BE2
#define REG_DISPCNT 0x04000000

#define BOOT_SMOKE_FRAMES 600
#define START_FRAMES 1200
#define START_FIRST_FRAME 600
#define START_PERIOD 60
#define START_HOLD 6

#define INPUT_LINE_MAX 4096

typedef struct {
    uint32_t frame;
    uint16_t keys;
} InputEntry;

typedef struct {
    InputEntry* entries;
    size_t count;
    size_t capacity;
    long header_frames;
} InputReplay;

typedef struct {
    size_t frame;
    uint16_t disp;
    uint16_t main_mode;
    uint16_t sub1;
    uint16_t sub2;
} InputExpect;

typedef struct {
    InputExpect* entries;
    size_t count;
    size_t capacity;
} InputExpectations;

typedef struct {
    uint16_t disp;
    uint16_t main_mode;
    uint16_t sub1;
    uint16_t sub2;
} InputState;

static const size_t INPUT_CHECKPOINTS[] = {300, 600, 900, 4000};
#define INPUT_CHECKPOINT_COUNT \
    (sizeof(INPUT_CHECKPOINTS) / sizeof(INPUT_CHECKPOINTS[0]))

static void usage(const char* argv0) {
    fprintf(
        stderr,
        "usage: %s rom.gba [frames]\n"
        "       %s rom.gba --scenario boot_smoke|start [--frames N]\n"
        "       %s rom.gba --input FILE [--frames N] [--expect FILE]\n"
        "       %s rom.gba --scenario input --input FILE [--frames N] "
        "[--expect FILE]\n",
        argv0, argv0, argv0, argv0
    );
}

static int run_boot(struct mCore* core, int frames) {
    struct GBA* gba = core->board;
    uint16_t counter = GBAView16(gba->cpu, IWRAM_FRAME_COUNTER);
    uint8_t area = GBAView8(gba->cpu, IWRAM_CURRENT_AREA);
    uint8_t main_mode = GBAView8(gba->cpu, IWRAM_MAIN_MODE);
    uint16_t sub_mode = GBAView16(gba->cpu, IWRAM_SUB_MODE);

    printf(
        "BOOT frames=%d frame_counter=%u area=%u main_mode=%u sub_mode=0x%04X\n",
        frames, counter, area, main_mode, sub_mode
    );

    int min_counter = frames * 3 / 4;
    if (counter < min_counter) {
        printf(
            "FAIL: frame counter %u is below the %d-frame liveness floor\n",
            counter, min_counter
        );
        return 1;
    }
    printf("PASS: boot smoke\n");
    return 0;
}

/*
 * QA-001: hold Start for 6 frames every 60 frames starting at frame 600, then
 * verify the file-select/intro transition brought the display back up.
 *
 * Success latches at the first frame after the first Start where
 * DISPCNT != 0 && gMainGameMode == 7 && gSubGameMode1 >= 1.  Requiring the
 * verdict at the final frame would be wrong: a healthy run has a transient
 * DISPCNT=0000 during a later mode change (frame 1020 in the reference).
 */
static int run_start(struct mCore* core, int frames) {
    struct GBA* gba = core->board;
    int latched = 0;
    int latch_frame = -1;

    for (int i = 0; i < frames; ++i) {
        int pressed = i >= START_FIRST_FRAME
            && ((i - START_FIRST_FRAME) % START_PERIOD) < START_HOLD;
        core->setKeys(core, pressed ? (1u << GBA_KEY_START) : 0);
        core->runFrame(core);

        if (i >= START_FIRST_FRAME && !latched) {
            uint16_t dispcnt = GBAView16(gba->cpu, REG_DISPCNT);
            uint16_t main_mode = GBAView16(gba->cpu, IWRAM_MAIN_MODE);
            uint16_t sub1 = GBAView16(gba->cpu, IWRAM_SUB_MODE1);
            if (dispcnt != 0 && main_mode == 7 && sub1 >= 1) {
                latched = 1;
                latch_frame = i;
            }
        }
    }

    uint16_t dispcnt = GBAView16(gba->cpu, REG_DISPCNT);
    uint16_t main_mode = GBAView16(gba->cpu, IWRAM_MAIN_MODE);
    uint16_t sub1 = GBAView16(gba->cpu, IWRAM_SUB_MODE1);
    uint16_t sub2 = GBAView16(gba->cpu, IWRAM_SUB_MODE2);

    printf(
        "START frames=%d dispcnt=0x%04X main=%u sub1=%u sub2=%u "
        "latched=%d latch_frame=%d\n",
        frames, dispcnt, main_mode, sub1, sub2, latched, latch_frame
    );

    if (!latched) {
        printf(
            "FAIL: start/file-select: no frame after Start had "
            "DISPCNT != 0 && main == 7 && sub1 >= 1\n"
        );
        return 1;
    }
    printf("PASS: start/file-select\n");
    return 0;
}

static char* trim(char* text) {
    while (*text && isspace((unsigned char)*text)) {
        ++text;
    }
    size_t length = strlen(text);
    while (length > 0 && isspace((unsigned char)text[length - 1])) {
        text[--length] = '\0';
    }
    return text;
}

static void input_replay_free(InputReplay* replay) {
    free(replay->entries);
    replay->entries = NULL;
    replay->count = 0;
    replay->capacity = 0;
}

/*
 * Parse a `frame keys` input file.  Frame numbers must increase so a truncated
 * or spliced file is rejected instead of silently replaying the wrong length.
 * The replay itself is line-ordered: one line = one emulated frame.
 */
static int input_replay_load(const char* path, InputReplay* replay) {
    memset(replay, 0, sizeof(*replay));
    replay->header_frames = -1;

    FILE* file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "FAIL: could not open input file %s: %s\n",
                path, strerror(errno));
        return -1;
    }

    char line[INPUT_LINE_MAX];
    unsigned long line_number = 0;
    int have_last = 0;
    uint32_t last_frame = 0;
    int status = 0;

    while (fgets(line, sizeof(line), file)) {
        ++line_number;
        char* text = trim(line);
        if (*text == '\0') {
            continue;
        }
        if (*text == '#') {
            const char* header = strstr(text, "frames=");
            if (header) {
                char* end = NULL;
                long value = strtol(header + strlen("frames="), &end, 10);
                if (end != header + strlen("frames=") && value >= 0) {
                    replay->header_frames = value;
                }
            }
            continue;
        }

        char* comment = strchr(text, '#');
        if (comment) {
            *comment = '\0';
            text = trim(text);
            if (*text == '\0') {
                continue;
            }
        }

        errno = 0;
        char* end = NULL;
        unsigned long frame = strtoul(text, &end, 0);
        if (end == text || errno != 0) {
            fprintf(stderr, "FAIL: %s:%lu: expected `frame keys`\n",
                    path, line_number);
            status = -1;
            break;
        }
        while (*end && isspace((unsigned char)*end)) {
            ++end;
        }
        if (*end == '\0') {
            fprintf(stderr, "FAIL: %s:%lu: missing key bitmask\n",
                    path, line_number);
            status = -1;
            break;
        }
        errno = 0;
        char* keys_end = NULL;
        unsigned long keys = strtoul(end, &keys_end, 0);
        if (keys_end == end || errno != 0) {
            fprintf(stderr, "FAIL: %s:%lu: invalid key bitmask\n",
                    path, line_number);
            status = -1;
            break;
        }
        keys_end = trim(keys_end);
        if (*keys_end != '\0') {
            fprintf(stderr, "FAIL: %s:%lu: trailing input %s\n",
                    path, line_number, keys_end);
            status = -1;
            break;
        }
        if (frame > UINT32_MAX) {
            fprintf(stderr, "FAIL: %s:%lu: frame %lu out of range\n",
                    path, line_number, frame);
            status = -1;
            break;
        }
        if (keys > UINT16_MAX) {
            fprintf(stderr,
                    "FAIL: %s:%lu: keys 0x%lX do not fit the GBA bitmask\n",
                    path, line_number, keys);
            status = -1;
            break;
        }
        if (have_last && (uint32_t)frame <= last_frame) {
            fprintf(stderr,
                    "FAIL: %s:%lu: frame %lu is not after frame %u\n",
                    path, line_number, frame, last_frame);
            status = -1;
            break;
        }

        if (replay->count == replay->capacity) {
            size_t capacity = replay->capacity ? replay->capacity * 2 : 1024;
            InputEntry* entries = realloc(
                replay->entries, capacity * sizeof(*entries)
            );
            if (!entries) {
                fprintf(stderr, "FAIL: out of memory reading %s\n", path);
                status = -1;
                break;
            }
            replay->entries = entries;
            replay->capacity = capacity;
        }
        replay->entries[replay->count].frame = (uint32_t)frame;
        replay->entries[replay->count].keys = (uint16_t)keys;
        ++replay->count;
        last_frame = (uint32_t)frame;
        have_last = 1;
    }

    if (ferror(file)) {
        fprintf(stderr, "FAIL: read error on %s: %s\n", path, strerror(errno));
        status = -1;
    }
    fclose(file);
    if (status != 0) {
        input_replay_free(replay);
        return -1;
    }
    if (replay->count == 0) {
        fprintf(stderr, "FAIL: input file %s has no `frame keys` lines\n", path);
        input_replay_free(replay);
        return -1;
    }
    return 0;
}

static void input_expectations_free(InputExpectations* expect) {
    free(expect->entries);
    expect->entries = NULL;
    expect->count = 0;
    expect->capacity = 0;
}

static int parse_unsigned_field(char** cursor, unsigned long* value) {
    while (**cursor && isspace((unsigned char)**cursor)) {
        ++*cursor;
    }
    if (**cursor == '\0') {
        return -1;
    }
    errno = 0;
    char* end = NULL;
    unsigned long parsed = strtoul(*cursor, &end, 0);
    if (end == *cursor || errno != 0) {
        return -1;
    }
    *value = parsed;
    *cursor = end;
    return 0;
}

/*
 * Optional expected checkpoints: `frame disp main s1 s2` per line (hex or
 * decimal), one per checkpoint.  This is a normal-fixture regression check,
 * not a BizHawk parity check; only supplied frames are asserted.
 */
static int input_expectations_load(
    const char* path,
    InputExpectations* expect
) {
    memset(expect, 0, sizeof(*expect));
    FILE* file = fopen(path, "r");
    if (!file) {
        fprintf(stderr, "FAIL: could not open expectation file %s: %s\n",
                path, strerror(errno));
        return -1;
    }

    char line[INPUT_LINE_MAX];
    unsigned long line_number = 0;
    int status = 0;
    while (fgets(line, sizeof(line), file)) {
        ++line_number;
        char* text = trim(line);
        if (*text == '\0' || *text == '#') {
            continue;
        }
        char* comment = strchr(text, '#');
        if (comment) {
            *comment = '\0';
            text = trim(text);
            if (*text == '\0') {
                continue;
            }
        }

        unsigned long frame = 0;
        unsigned long disp = 0;
        unsigned long main_mode = 0;
        unsigned long sub1 = 0;
        unsigned long sub2 = 0;
        char* cursor = text;
        if (parse_unsigned_field(&cursor, &frame) != 0
            || parse_unsigned_field(&cursor, &disp) != 0
            || parse_unsigned_field(&cursor, &main_mode) != 0
            || parse_unsigned_field(&cursor, &sub1) != 0
            || parse_unsigned_field(&cursor, &sub2) != 0) {
            fprintf(stderr,
                    "FAIL: %s:%lu: expected `frame disp main s1 s2`\n",
                    path, line_number);
            status = -1;
            break;
        }
        cursor = trim(cursor);
        if (*cursor != '\0') {
            fprintf(stderr, "FAIL: %s:%lu: trailing input %s\n",
                    path, line_number, cursor);
            status = -1;
            break;
        }
        if (disp > UINT16_MAX || main_mode > UINT16_MAX
            || sub1 > UINT16_MAX || sub2 > UINT16_MAX) {
            fprintf(stderr, "FAIL: %s:%lu: state value out of range\n",
                    path, line_number);
            status = -1;
            break;
        }

        if (expect->count == expect->capacity) {
            size_t capacity = expect->capacity ? expect->capacity * 2 : 8;
            InputExpect* entries = realloc(
                expect->entries, capacity * sizeof(*entries)
            );
            if (!entries) {
                fprintf(stderr, "FAIL: out of memory reading %s\n", path);
                status = -1;
                break;
            }
            expect->entries = entries;
            expect->capacity = capacity;
        }
        expect->entries[expect->count].frame = (size_t)frame;
        expect->entries[expect->count].disp = (uint16_t)disp;
        expect->entries[expect->count].main_mode = (uint16_t)main_mode;
        expect->entries[expect->count].sub1 = (uint16_t)sub1;
        expect->entries[expect->count].sub2 = (uint16_t)sub2;
        ++expect->count;
    }

    if (ferror(file)) {
        fprintf(stderr, "FAIL: read error on %s: %s\n", path, strerror(errno));
        status = -1;
    }
    fclose(file);
    if (status != 0) {
        input_expectations_free(expect);
        return -1;
    }
    return 0;
}

static const InputExpect* input_expect_find(
    const InputExpectations* expect,
    size_t frame
) {
    if (!expect) {
        return NULL;
    }
    for (size_t i = 0; i < expect->count; ++i) {
        if (expect->entries[i].frame == frame) {
            return &expect->entries[i];
        }
    }
    return NULL;
}

static size_t input_expect_due(
    const InputExpectations* expect,
    size_t limit
) {
    if (!expect) {
        return 0;
    }
    size_t due = 0;
    for (size_t i = 0; i < expect->count; ++i) {
        if (expect->entries[i].frame <= limit) {
            ++due;
        }
    }
    return due;
}

static InputState input_read_state(struct GBA* gba) {
    InputState state;
    state.disp = GBAView16(gba->cpu, REG_DISPCNT);
    state.main_mode = GBAView16(gba->cpu, IWRAM_MAIN_MODE);
    state.sub1 = GBAView16(gba->cpu, IWRAM_SUB_MODE1);
    state.sub2 = GBAView16(gba->cpu, IWRAM_SUB_MODE2);
    return state;
}

static void input_print_state(
    struct GBA* gba,
    size_t frame,
    uint16_t keys,
    const char* prefix
) {
    InputState state = input_read_state(gba);
    printf(
        "%s frame=%zu keys=%u disp=0x%04X main=%u s1=%u s2=%u\n",
        prefix, frame, keys,
        state.disp, state.main_mode, state.sub1, state.sub2
    );
}

static int input_check_expect(
    const InputExpectations* expect,
    size_t frame,
    InputState state,
    size_t* checked
) {
    const InputExpect* expected = input_expect_find(expect, frame);
    if (!expected) {
        return 0;
    }
    ++*checked;
    int ok = state.disp == expected->disp
        && state.main_mode == expected->main_mode
        && state.sub1 == expected->sub1
        && state.sub2 == expected->sub2;
    if (ok) {
        printf("INPUT_CHECK frame=%zu status=pass\n", frame);
        return 0;
    }
    printf(
        "INPUT_CHECK frame=%zu status=fail "
        "disp=0x%04X expected_disp=0x%04X "
        "main=%u expected_main=%u "
        "s1=%u expected_s1=%u "
        "s2=%u expected_s2=%u\n",
        frame,
        state.disp, expected->disp,
        state.main_mode, expected->main_mode,
        state.sub1, expected->sub1,
        state.sub2, expected->sub2
    );
    return 1;
}

static int input_is_checkpoint(size_t frame) {
    for (size_t i = 0; i < INPUT_CHECKPOINT_COUNT; ++i) {
        if (INPUT_CHECKPOINTS[i] == frame) {
            return 1;
        }
    }
    return 0;
}

/*
 * QA-002: replay `frame keys` lines in order.  setKeys is called before
 * runFrame, so line 0 is the first emulated frame.  Checkpoints are reported
 * after 300/600/900/4000 completed frames (matching the BizHawk frame-count
 * convention).  The verdict only covers the replay itself: a differing
 * checkpoint value is data for the differential gate, not a harness failure.
 */
static int run_input(
    struct mCore* core,
    const InputReplay* replay,
    const InputExpectations* expect,
    int frames,
    int frames_set
) {
    struct GBA* gba = core->board;
    size_t limit = replay->count;
    if (frames_set && (size_t)frames < limit) {
        limit = (size_t)frames;
    }
    if (limit == 0) {
        printf("FAIL: input replay has zero frames\n");
        return 1;
    }

    printf(
        "INPUT_START lines=%zu header_frames=%ld replay=%zu%s\n",
        replay->count, replay->header_frames, limit,
        frames_set && limit < replay->count ? " capped" : ""
    );

    size_t expected_checked = 0;
    int expected_failed = 0;
    uint16_t last_keys = 0;
    for (size_t i = 0; i < limit; ++i) {
        uint16_t keys = replay->entries[i].keys;
        last_keys = keys;
        core->setKeys(core, keys);
        core->runFrame(core);
        size_t completed = i + 1;
        if (input_is_checkpoint(completed)) {
            input_print_state(gba, completed, keys, "INPUT");
            InputState state = input_read_state(gba);
            if (input_check_expect(expect, completed, state,
                                   &expected_checked)) {
                expected_failed = 1;
            }
        }
    }

    uint16_t counter = GBAView16(gba->cpu, IWRAM_FRAME_COUNTER);
    InputState state = input_read_state(gba);
    printf(
        "INPUT_FINAL frames=%zu frame_counter=%u keys=%u disp=0x%04X "
        "main=%u s1=%u s2=%u\n",
        limit, counter, last_keys,
        state.disp, state.main_mode, state.sub1, state.sub2
    );

    int failed = 0;
    int min_counter = (int)(limit * 3 / 4);
    if (counter < min_counter) {
        printf(
            "FAIL: input replay frame counter %u is below the %d-frame "
            "liveness floor\n",
            counter, min_counter
        );
        failed = 1;
    }

    if (expect) {
        size_t due = input_expect_due(expect, limit);
        printf(
            "INPUT_CHECK summary checked=%zu due=%zu failed=%d\n",
            expected_checked, due, expected_failed
        );
        if (expected_failed) {
            printf("FAIL: input checkpoint mismatch\n");
            failed = 1;
        }
        if (expected_checked != due) {
            printf(
                "FAIL: expected checkpoints were not reached "
                "(checked=%zu due=%zu)\n",
                expected_checked, due
            );
            failed = 1;
        }
    }

    if (failed) {
        return 1;
    }
    printf("PASS: input replay\n");
    return 0;
}

int main(int argc, char** argv) {
    const char* rom = NULL;
    const char* scenario = "boot_smoke";
    const char* input_path = NULL;
    const char* expect_path = NULL;
    int scenario_set = 0;
    int frames = 0;
    int frames_set = 0;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--scenario") == 0) {
            if (++i >= argc) {
                usage(argv[0]);
                return 2;
            }
            scenario = argv[i];
            scenario_set = 1;
        } else if (strcmp(argv[i], "--input") == 0) {
            if (++i >= argc) {
                usage(argv[0]);
                return 2;
            }
            input_path = argv[i];
            scenario = "input";
        } else if (strcmp(argv[i], "--expect") == 0) {
            if (++i >= argc) {
                usage(argv[0]);
                return 2;
            }
            expect_path = argv[i];
        } else if (strcmp(argv[i], "--frames") == 0) {
            if (++i >= argc) {
                usage(argv[0]);
                return 2;
            }
            frames = atoi(argv[i]);
            frames_set = 1;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            usage(argv[0]);
            return 0;
        } else if (!rom) {
            rom = argv[i];
        } else if (!frames_set) {
            /* Legacy positional frame count: harness rom.gba [frames]. */
            frames = atoi(argv[i]);
            frames_set = 1;
        } else {
            usage(argv[0]);
            return 2;
        }
    }
    if (!rom) {
        usage(argv[0]);
        return 2;
    }
    if (scenario_set && input_path && strcmp(scenario, "input") != 0) {
        fprintf(stderr,
                "FAIL: --input selects the input scenario; "
                "do not combine it with --scenario %s\n", scenario);
        return 2;
    }
    if (input_path) {
        scenario = "input";
    }
    if (strcmp(scenario, "input") == 0 && !input_path) {
        fprintf(stderr, "FAIL: --scenario input requires --input FILE\n");
        return 2;
    }
    if (expect_path && strcmp(scenario, "input") != 0) {
        fprintf(stderr, "FAIL: --expect is only valid with --input FILE\n");
        return 2;
    }
    if (!frames_set && strcmp(scenario, "input") != 0) {
        frames = strcmp(scenario, "start") == 0
            ? START_FRAMES
            : BOOT_SMOKE_FRAMES;
    }
    if (frames_set && frames <= 0) {
        fprintf(stderr, "FAIL: invalid frame count %d\n", frames);
        return 2;
    }

    InputReplay replay;
    InputExpectations expect;
    memset(&replay, 0, sizeof(replay));
    memset(&expect, 0, sizeof(expect));
    if (input_path && input_replay_load(input_path, &replay) != 0) {
        return 2;
    }
    if (expect_path && input_expectations_load(expect_path, &expect) != 0) {
        input_replay_free(&replay);
        return 2;
    }

    struct mCore* core = GBACoreCreate();
    if (!core || !core->init(core)) {
        fprintf(stderr, "FAIL: mGBA core init\n");
        input_expectations_free(&expect);
        input_replay_free(&replay);
        return 1;
    }
    mCoreInitConfig(core, NULL);
    mCoreConfigSetDefaultIntValue(&core->config, "logToStdout", 0);
    if (!mCoreLoadFile(core, rom)) {
        fprintf(stderr, "FAIL: could not load %s\n", rom);
        core->deinit(core);
        input_expectations_free(&expect);
        input_replay_free(&replay);
        return 1;
    }
    core->reset(core);

    int rc;
    if (strcmp(scenario, "boot_smoke") == 0) {
        for (int i = 0; i < frames; ++i) {
            core->runFrame(core);
        }
        rc = run_boot(core, frames);
    } else if (strcmp(scenario, "start") == 0) {
        rc = run_start(core, frames);
    } else if (strcmp(scenario, "input") == 0) {
        rc = run_input(
            core, &replay, expect_path ? &expect : NULL, frames, frames_set
        );
    } else {
        fprintf(stderr, "FAIL: unknown scenario '%s'\n", scenario);
        rc = 2;
    }

    input_expectations_free(&expect);
    input_replay_free(&replay);
    mCoreConfigDeinit(&core->config);
    core->deinit(core);
    return rc;
}
