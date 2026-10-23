/*
 * Host-side unit tests for Sram_CheckLoadSaveFile in
 * src/sram/sram_check_save.c.
 *
 * The real engine function is linked in by the Makefile's host-test target:
 *
 *   cc ... tests/host/save_test.c src/sram/sram_check_save.c -Wl,--gc-sections
 *
 * Sram_InitSaveFile and SramLoad_CurrentSave are the two low-level SRAM
 * routines that the real function calls; they are GBA/ROM-bound, so they are
 * stubbed here with call counters.  Everything else is the real C control
 * flow: the loading-byte branch, the per-file completion copy, the copy of the
 * button/boot-debug blocks, and the flag clearing.
 *
 * The checksum for the most recent header lives in
 * SramWrite_MostRecentSaveFile (still asm, TECH-003f) and is deliberately not
 * duplicated here.
 */

#include "test.h"

#include "globals.h"
#include "structs/connection.h"
#include "structs/event.h"
#include "structs/menus/boot_debug.h"
#include "structs/save_file.h"

/* ------------------------------------------------------------------ */
/* Fixture globals.  Only the data Sram_CheckLoadSaveFile references.  */
/* ------------------------------------------------------------------ */

/* Mirror of the per-file slot layout in src/sram/sram_check_save.c.  The
 * engine declares this struct privately; main() asserts that this fixture
 * keeps the baseline's 0x14-byte scaling. */
struct SramFileInfoFixture {
    u8 loading;         /* 0x00 */
    u8 unk_01[0x0F];
    u8 completion0;     /* 0x10 */
    u8 completion1;     /* 0x11 */
    u8 unk_12[2];
};

struct SramFileInfoFixture gSramFileInfo[3];

/* The engine reads the button assignments from sUnk_582280 + 0x48.  In the
 * real ROM that symbol is an array of pointers into the boot area; here it is
 * plain storage with the same offset so the copy is exercised for real. */
struct SramPointersFixture {
    u8 pad[0x48];
    struct ButtonAssignments assignments;
};

struct SramPointersFixture sUnk_582280;

/* ROM alias for the boot-debug block; the engine reads it as a struct. */
struct BootDebugOptions gBootOptionsSrc;

/* The engine writes completion[0..2] through a u8 pointer even though
 * struct GameCompletion is two bytes (the third byte zeroes the adjacent
 * byte in the baseline).  Back the symbol with at least three bytes so the
 * write stays in-bounds and observable here. */
u8 gGameCompletionStorage[4];
extern struct GameCompletion gGameCompletion
    __attribute__((alias("gGameCompletionStorage")));

struct ButtonAssignments gButtonAssignments;
struct BootDebugOptions gBootDebugOptions;
u8 gMostRecentSaveFile;
s8 gIsLoadingFile;

bools8 gUnk_3000be3;
s8 gPauseScreenFlag;
u8 gDebugFlag;
u8 gDisableSoftReset;
u8 gDisableMusicFlag;
s8 gDisablePauseFlag;
u8 gMaxInGameTimeFlag;
u8 gMonochromeFading;
u8 gSkipDoorTransition;
u8 gUnk_3000b85;
s16 gSamusDoorPositionOffset;

/* ------------------------------------------------------------------ */
/* Stubs for the hardware-bound low-level SRAM routines.               */
/* ------------------------------------------------------------------ */

static int sInitSaveFileCalls;
static int sLoadCurrentSaveCalls;

void Sram_InitSaveFile(void)
{
    sInitSaveFileCalls++;
}

void SramLoad_CurrentSave(void)
{
    sLoadCurrentSaveCalls++;
}

/* ------------------------------------------------------------------ */
/* Helpers                                                             */
/* ------------------------------------------------------------------ */

static void reset_fixtures(void)
{
    int i;
    u8* slot = (u8*)gSramFileInfo;

    for (i = 0; i < (int)sizeof(gSramFileInfo); i++)
        slot[i] = 0;

    gMostRecentSaveFile = 0;
    gIsLoadingFile = 0;

    sInitSaveFileCalls = 0;
    sLoadCurrentSaveCalls = 0;
}

static void dirty_flags(void)
{
    gUnk_3000be3 = 1;
    gMonochromeFading = 1;
    gDisableSoftReset = 1;
    gMaxInGameTimeFlag = 1;
    gDisableMusicFlag = 1;
    gSkipDoorTransition = 1;
    gPauseScreenFlag = 1;
    gUnk_3000b85 = 1;
    gDisablePauseFlag = 1;
    gSamusDoorPositionOffset = 0x0102;
    gDebugFlag = 1;
}

static void check_flags_cleared(void)
{
    CHECK_EQ(gUnk_3000be3, 0);
    CHECK_EQ(gMonochromeFading, 0);
    CHECK_EQ(gDisableSoftReset, 0);
    CHECK_EQ(gMaxInGameTimeFlag, 0);
    CHECK_EQ(gDisableMusicFlag, 0);
    CHECK_EQ(gSkipDoorTransition, 0);
    CHECK_EQ(gPauseScreenFlag, 0);
    CHECK_EQ(gUnk_3000b85, 0);
    CHECK_EQ(gDisablePauseFlag, 0);
    CHECK_EQ(gSamusDoorPositionOffset, 0);
    CHECK_EQ(gDebugFlag, 0);
}

static void set_source_blocks(u16 seed)
{
    sUnk_582280.assignments.armMissiles = seed + 1;
    sUnk_582280.assignments.diagonalAim = seed + 2;
    sUnk_582280.assignments.swapMissiles = seed + 3;
    sUnk_582280.assignments.pause = seed + 4;

    gBootOptionsSrc.bld.whole.cnt = seed + 0x10;
    gBootOptionsSrc.bld.whole.alpha = seed + 0x20;
    gBootOptionsSrc.bldalpha_evy = seed + 0x30;
    gBootOptionsSrc.frontWideCamera = 1;
    gBootOptionsSrc.sectionCursor = 2;
    gBootOptionsSrc.sectionSelector = 3;
    gBootOptionsSrc.downloadedMaps = 4;
    gBootOptionsSrc.securityHatchLevel = 5;
    gBootOptionsSrc.mapScanLRAndStereo = 6;
}

static void check_source_blocks_copied(void)
{
    CHECK_EQ(gButtonAssignments.armMissiles,
             sUnk_582280.assignments.armMissiles);
    CHECK_EQ(gButtonAssignments.diagonalAim,
             sUnk_582280.assignments.diagonalAim);
    CHECK_EQ(gButtonAssignments.swapMissiles,
             sUnk_582280.assignments.swapMissiles);
    CHECK_EQ(gButtonAssignments.pause, sUnk_582280.assignments.pause);
    CHECK_MEMEQ(&gBootDebugOptions, &gBootOptionsSrc, sizeof(gBootDebugOptions));
}

/* ------------------------------------------------------------------ */
/* loading == 0: initialise, copy completion, clear the trailing flags. */
/* ------------------------------------------------------------------ */

static void test_loading_zero_inits_and_copies_completion(void)
{
    reset_fixtures();

    gMostRecentSaveFile = 1;
    gSramFileInfo[1].loading = 0;
    gSramFileInfo[1].completion0 = 0x12;
    gSramFileInfo[1].completion1 = 0x34;

    /* Pre-fill so the copy is visible and the third byte is not just zero. */
    gGameCompletionStorage[0] = 0xFF;
    gGameCompletionStorage[1] = 0xFF;
    gGameCompletionStorage[2] = 0xFF;

    set_source_blocks(0x100);
    dirty_flags();

    Sram_CheckLoadSaveFile();

    CHECK_EQ(sInitSaveFileCalls, 1);
    CHECK_EQ(sLoadCurrentSaveCalls, 0);
    CHECK_EQ(gIsLoadingFile, 0);

    CHECK_EQ(gGameCompletionStorage[0], 0x12);
    CHECK_EQ(gGameCompletionStorage[1], 0x34);
    CHECK_EQ(gGameCompletionStorage[2], 0x00);

    check_source_blocks_copied();
    check_flags_cleared();
}

static void test_loading_zero_uses_most_recent_slot(void)
{
    reset_fixtures();

    gSramFileInfo[0].loading = 1;
    gSramFileInfo[0].completion0 = 0xAA;
    gSramFileInfo[0].completion1 = 0xAB;
    gSramFileInfo[1].loading = 1;
    gSramFileInfo[1].completion0 = 0xBA;
    gSramFileInfo[1].completion1 = 0xBB;
    gSramFileInfo[2].loading = 0;
    gSramFileInfo[2].completion0 = 0xCA;
    gSramFileInfo[2].completion1 = 0xCB;

    gMostRecentSaveFile = 2;
    gGameCompletionStorage[0] = 0;
    gGameCompletionStorage[1] = 0;
    gGameCompletionStorage[2] = 0;

    dirty_flags();
    Sram_CheckLoadSaveFile();

    CHECK_EQ(sInitSaveFileCalls, 1);
    CHECK_EQ(sLoadCurrentSaveCalls, 0);
    CHECK_EQ(gGameCompletionStorage[0], 0xCA);
    CHECK_EQ(gGameCompletionStorage[1], 0xCB);
    CHECK_EQ(gGameCompletionStorage[2], 0x00);
    check_flags_cleared();
}

/* ------------------------------------------------------------------ */
/* loading != 0: load path, completion bytes untouched.                */
/* ------------------------------------------------------------------ */

static void test_loading_nonzero_loads_without_touching_completion(void)
{
    reset_fixtures();

    gMostRecentSaveFile = 0;
    gSramFileInfo[0].loading = 1;
    gSramFileInfo[0].completion0 = 0x12;
    gSramFileInfo[0].completion1 = 0x34;

    gGameCompletionStorage[0] = 0xAA;
    gGameCompletionStorage[1] = 0xBB;
    gGameCompletionStorage[2] = 0xCC;

    set_source_blocks(0x200);
    dirty_flags();

    Sram_CheckLoadSaveFile();

    CHECK_EQ(sInitSaveFileCalls, 0);
    CHECK_EQ(sLoadCurrentSaveCalls, 1);
    CHECK_EQ(gIsLoadingFile, 1);

    CHECK_EQ(gGameCompletionStorage[0], 0xAA);
    CHECK_EQ(gGameCompletionStorage[1], 0xBB);
    CHECK_EQ(gGameCompletionStorage[2], 0xCC);

    check_source_blocks_copied();
    check_flags_cleared();
}

/* The loading byte is signed-extended into gIsLoadingFile; a high byte must
 * still take the load branch (the baseline tests the sign-extended value). */
static void test_loading_high_byte_still_loads(void)
{
    reset_fixtures();

    gMostRecentSaveFile = 2;
    gSramFileInfo[2].loading = 0x80;

    gGameCompletionStorage[0] = 0x11;
    gGameCompletionStorage[1] = 0x22;
    gGameCompletionStorage[2] = 0x33;

    dirty_flags();
    Sram_CheckLoadSaveFile();

    CHECK_EQ(sInitSaveFileCalls, 0);
    CHECK_EQ(sLoadCurrentSaveCalls, 1);
    CHECK_EQ((u8)gIsLoadingFile, 0x80);

    CHECK_EQ(gGameCompletionStorage[0], 0x11);
    CHECK_EQ(gGameCompletionStorage[1], 0x22);
    CHECK_EQ(gGameCompletionStorage[2], 0x33);
    check_flags_cleared();
}

/* Repeating the call does not latch the previous branch or counters. */
static void test_repeated_calls_follow_the_loading_byte(void)
{
    reset_fixtures();

    gSramFileInfo[0].loading = 0;
    gSramFileInfo[0].completion0 = 0x01;
    gSramFileInfo[0].completion1 = 0x02;

    Sram_CheckLoadSaveFile();
    CHECK_EQ(sInitSaveFileCalls, 1);
    CHECK_EQ(sLoadCurrentSaveCalls, 0);

    gSramFileInfo[0].loading = 1;
    Sram_CheckLoadSaveFile();
    CHECK_EQ(sInitSaveFileCalls, 1);
    CHECK_EQ(sLoadCurrentSaveCalls, 1);

    gSramFileInfo[0].loading = 0;
    gSramFileInfo[0].completion0 = 0x03;
    gSramFileInfo[0].completion1 = 0x04;
    Sram_CheckLoadSaveFile();
    CHECK_EQ(sInitSaveFileCalls, 2);
    CHECK_EQ(sLoadCurrentSaveCalls, 1);
    CHECK_EQ(gGameCompletionStorage[0], 0x03);
    CHECK_EQ(gGameCompletionStorage[1], 0x04);
    CHECK_EQ(gGameCompletionStorage[2], 0x00);
}

int main(void)
{
    /* The engine's slot arithmetic assumes a 0x14-byte per-file entry. */
    CHECK_EQ(sizeof(struct SramFileInfoFixture), 0x14);

    test_loading_zero_inits_and_copies_completion();
    test_loading_zero_uses_most_recent_slot();
    test_loading_nonzero_loads_without_touching_completion();
    test_loading_high_byte_still_loads();
    test_repeated_calls_follow_the_loading_byte();

    if (g_host_test_failures != 0)
        return host_test_finish();

    printf("save-test: %d/%d passed\n",
           g_host_test_checks, g_host_test_checks);
    return 0;
}
