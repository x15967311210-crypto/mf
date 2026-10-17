/*
 * Headless mGBA harness.
 *
 * This is the dynamic half of SHIFT-001.  It loads a ROM, runs a fixed number
 * of frames, and reads fixed IWRAM addresses from linker.ld.  It deliberately
 * contains no ROM data and no game assets; the ROM is a runtime argument.
 *
 * Build with tests/emulator/build_harness.sh against an mGBA source/build tree.
 */
#include <mgba/core/config.h>
#include <mgba/core/core.h>
#include <mgba/gba/core.h>
#include <mgba/internal/gba/gba.h>
#include <mgba/internal/gba/memory.h>

#include <stdio.h>
#include <stdlib.h>

#define IWRAM_FRAME_COUNTER 0x03000002
#define IWRAM_CURRENT_AREA 0x0300002C
#define IWRAM_MAIN_MODE 0x03000BDE
#define IWRAM_SUB_MODE 0x03000BE0

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "usage: %s rom.gba [frames]\n", argv[0]);
        return 2;
    }
    int frames = argc > 2 ? atoi(argv[2]) : 600;

    struct mCore* core = GBACoreCreate();
    if (!core || !core->init(core)) {
        fprintf(stderr, "FAIL: mGBA core init\n");
        return 1;
    }
    mCoreInitConfig(core, NULL);
    mCoreConfigSetDefaultIntValue(&core->config, "logToStdout", 0);
    if (!mCoreLoadFile(core, argv[1])) {
        fprintf(stderr, "FAIL: could not load %s\n", argv[1]);
        core->deinit(core);
        return 1;
    }
    core->reset(core);

    for (int i = 0; i < frames; ++i) {
        core->runFrame(core);
    }

    struct GBA* gba = core->board;
    uint16_t counter = GBAView16(gba->cpu, IWRAM_FRAME_COUNTER);
    uint8_t area = GBAView8(gba->cpu, IWRAM_CURRENT_AREA);
    uint8_t main_mode = GBAView8(gba->cpu, IWRAM_MAIN_MODE);
    uint16_t sub_mode = GBAView16(gba->cpu, IWRAM_SUB_MODE);

    printf(
        "BOOT frames=%d frame_counter=%u area=%u main_mode=%u sub_mode=0x%04X\n",
        frames, counter, area, main_mode, sub_mode
    );

    int rc = 0;
    if (counter == 0) {
        printf("FAIL: frame counter did not advance\n");
        rc = 1;
    }
    if (!rc) {
        printf("PASS: boot smoke\n");
    }

    mCoreConfigDeinit(&core->config);
    core->deinit(core);
    return rc;
}
