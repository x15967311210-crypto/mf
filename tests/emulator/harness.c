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

static void usage(const char* argv0) {
    fprintf(
        stderr,
        "usage: %s rom.gba [frames]\n"
        "       %s rom.gba --scenario boot_smoke|start [--frames N]\n",
        argv0, argv0
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

int main(int argc, char** argv) {
    const char* rom = NULL;
    const char* scenario = "boot_smoke";
    int frames = 0;
    int frames_set = 0;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--scenario") == 0) {
            if (++i >= argc) {
                usage(argv[0]);
                return 2;
            }
            scenario = argv[i];
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
    if (!frames_set) {
        frames = strcmp(scenario, "start") == 0
            ? START_FRAMES
            : BOOT_SMOKE_FRAMES;
    }
    if (frames <= 0) {
        fprintf(stderr, "FAIL: invalid frame count %d\n", frames);
        return 2;
    }

    struct mCore* core = GBACoreCreate();
    if (!core || !core->init(core)) {
        fprintf(stderr, "FAIL: mGBA core init\n");
        return 1;
    }
    mCoreInitConfig(core, NULL);
    mCoreConfigSetDefaultIntValue(&core->config, "logToStdout", 0);
    if (!mCoreLoadFile(core, rom)) {
        fprintf(stderr, "FAIL: could not load %s\n", rom);
        core->deinit(core);
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
    } else {
        fprintf(stderr, "FAIL: unknown scenario '%s'\n", scenario);
        rc = 2;
    }

    mCoreConfigDeinit(&core->config);
    core->deinit(core);
    return rc;
}
