#include "globals.h"

#include "audio_wrappers.h"
#include "dma.h"
#include "oam_id.h"

/* Pause-screen helper that is still assembly; it has no C header yet. */
void unk_77840(u32 action);

/**
 * @brief 77500 | 220 | Fades the pause screen into the debug menu's sleep mode
 *
 * Ported from the decomp.me scratch jAmJo by biosp4rk (100% match).
 */
bools32 EasySleepMenuInit(void)
{
    bools32 result;
    bools32 update;

    result = FALSE;
    update = FALSE;

    switch (PAUSE_SCREEN_DATA.pauseDebugEditingValue)
    {
        case 0:
            SoundPlay(0x202);
            UpdateMenuOamDataId(0x11, 0x2B);
            unk_77840(3);
            update = TRUE;
            break;

        case 1:
            DMA3_COPY_16(EWRAM_BASE + 0x10000, VRAM_BASE + 0xC000, 0x400);
            update = TRUE;
            break;

        case 2:
            WRITE_16(REG_BLDCNT, 0x3FFE);
            WRITE_16(REG_BLDALPHA, BLDALPHA_MAX_VALUE);
            update = TRUE;
            break;

        case 3:
            DMA3_COPY_16(EWRAM_BASE + 0xF000, EWRAM_BASE + 0xD380, 0x40);
            DMA3_COPY_16(EWRAM_BASE + 0xF400, EWRAM_BASE + 0xD780, 0x40);
            DMA3_COPY_16(EWRAM_BASE + 0xF080, EWRAM_BASE + 0xDB80, 0x40);
            DMA3_COPY_16(EWRAM_BASE + 0xF480, EWRAM_BASE + 0xDF80, 0x40);
            update = TRUE;
            break;

        case 4:
            DMA3_COPY_16(EWRAM_BASE + 0xF1C0, EWRAM_BASE + 0xE380, 0x40);
            DMA3_COPY_16(EWRAM_BASE + 0xF5C0, EWRAM_BASE + 0xE780, 0x40);
            DMA3_COPY_16(EWRAM_BASE + 0xF240, EWRAM_BASE + 0xEB80, 0x40);
            DMA3_COPY_16(EWRAM_BASE + 0xF640, EWRAM_BASE + 0xEF80, 0x40);
            update = TRUE;
            break;

        case 5:
            DmaTransfer(3, EWRAM_BASE + 0xD000, VRAM_BASE + 0x6000, 0x1000, 16);
            update = TRUE;
            break;

        case 6:
            DmaTransfer(3, EWRAM_BASE + 0xE000, VRAM_BASE + 0x7000, 0x1000, 16);
            update = TRUE;
            break;

        case 7:
            if (PAUSE_SCREEN_DATA.timer > 1)
            {
                PAUSE_SCREEN_DATA.timer = 0;

                if (gWrittenToBldy < 0xC)
                {
                    gWrittenToBldy++;
                    if (gWrittenToBldy == 6)
                    {
                        PAUSE_SCREEN_DATA.dispcnt |= DCNT_BG0;
                        UpdateMenuOamDataId(1, 2);
                        PAUSE_SCREEN_DATA.oam[1].xPosition = 0x8C;
                        PAUSE_SCREEN_DATA.oam[1].yPosition = 0x44;
                        PAUSE_SCREEN_DATA.oam[1].objMode = 1;
                    }
                }
                else
                {
                    UpdateMenuOamDataId(0x10, 0x28);
                    UpdateMenuOamDataId(0x11, 0x2A);
                    update = TRUE;
                }
            }
            break;

        case 8:
            gDisableSoftReset = 1;
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
