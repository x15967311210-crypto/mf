#include "globals.h"

#include "dma.h"
#include "oam_id.h"

/* Pause-screen helper that is still assembly; it has no C header yet. */
void unk_77840(u32 action);

/**
 * @brief 77720 | 120 | Finishes the pause screen's sleep-mode fade-out
 *
 * Ported from the decomp.me scratch B5CZs by biosp4rk (100% match).
 */
bools32 EasySleepMenuQuit(void)
{
    bools32 result;
    bools32 update;

    result = FALSE;

    switch (PAUSE_SCREEN_DATA.pauseDebugEditingValue)
    {
        case 0:
            gDisableSoftReset = 0;
            update = TRUE;
            break;

        case 1:
            if (PAUSE_SCREEN_DATA.timer > 1)
            {
                PAUSE_SCREEN_DATA.timer = 0;

                if (gWrittenToBldy != 0)
                {
                    gWrittenToBldy--;
                    if (gWrittenToBldy == 6)
                    {
                        PAUSE_SCREEN_DATA.dispcnt &= ~DCNT_BG0;
                        UpdateMenuOamDataId(1, 0);
                        PAUSE_SCREEN_DATA.oam[1].objMode = 0;
                    }
                    break;
                }

                update = TRUE;
            }
            break;

        case 2:
            update = TRUE;
            break;

        case 3:
            BitFill(3, 0, (void *)0x06006000, 0x1000, 0x20);
            update = TRUE;
            break;

        case 4:
            DMA3_COPY_16(EWRAM_BASE + 0xF800, VRAM_BASE + 0xC000, 0x400);
            update = TRUE;
            break;

        case 5:
            WRITE_16(REG_BLDCNT, 0x3F00);
            WRITE_16(REG_BLDALPHA, 0x40C);
            unk_77840(4);
            update = TRUE;
            break;

        case 6:
            result = TRUE;
            PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0;
            PAUSE_SCREEN_DATA.timer = 0;
            break;
    }

    if (update)
    {
        PAUSE_SCREEN_DATA.pauseDebugEditingValue++;
        PAUSE_SCREEN_DATA.timer = 0;
    }

    return result;
}
