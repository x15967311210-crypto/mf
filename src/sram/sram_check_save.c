#include "globals.h"

#include "gba.h"
#include "macros.h"

#include "data/sram_pointers.h"
#include "structs/connection.h"
#include "structs/event.h"
#include "structs/menus/boot_debug.h"
#include "structs/save_file.h"

/* One 0x14-byte per-file info slot in IWRAM (symbol from linker.ld).  The
   struct only names the bytes this function touches; the rest is padding, so
   sizeof == 0x14 and the baseline's `sel * 5 << 2` scaling is preserved. */
struct SramFileInfoSlot {
    u8 loading;         /* 0x00 */
    u8 unk_01[0x0F];
    u8 completion0;     /* 0x10 */
    u8 completion1;     /* 0x11 */
    u8 unk_12[2];
};

extern struct SramFileInfoSlot gSramFileInfo[3];
/* ROM alias for the boot-debug block at sUnk_582280 + 0x64 (linker.ld). */
extern const u8 gBootOptionsSrc[];

void Sram_InitSaveFile(void);
void SramLoad_CurrentSave(void);

void Sram_CheckLoadSaveFile(void)
{
    /* s32, not s8: the baseline keeps the sign-extended byte
       (lsls/asrs r5) for both the zero test and the completion store.  With an
       s8 local agbcc folds the test into the load and drops the `asrs`. */
    s32 loading;

    gButtonAssignments = *(const struct ButtonAssignments*)((const u8*)sUnk_582280 + 0x48);
    gBootDebugOptions = *(const struct BootDebugOptions*)gBootOptionsSrc;

    loading = gIsLoadingFile = gSramFileInfo[gMostRecentSaveFile].loading;

    if (loading == 0)
    {
        u8* completion;

        Sram_InitSaveFile();
        completion = (u8*)&gGameCompletion;
        completion[0] = gSramFileInfo[gMostRecentSaveFile].completion0;
        completion[1] = gSramFileInfo[gMostRecentSaveFile].completion1;
        completion[2] = loading;
    }
    else
    {
        SramLoad_CurrentSave();
    }

    gUnk_3000be3 = 0;
    gMonochromeFading = 0;
    gDisableSoftReset = 0;
    gMaxInGameTimeFlag = 0;
    gDisableMusicFlag = 0;
    gSkipDoorTransition = 0;
    gPauseScreenFlag = 0;
    gUnk_3000b85 = 0;
    gDisablePauseFlag = 0;
    gSamusDoorPositionOffset = 0;
    gDebugFlag = 0;
}
