#include "globals.h"

#include "gba.h"
#include "macros.h"
#include "oam.h"

/**
 * @brief 768a4 | 84 | Pause screen VBlank callback
 *
 * Ported from the decomp.me scratch dzWcG by biosp4rk (100% match).
 * Copies the OAM buffer with DMA3, then republishes the pause screen's
 * display control, brightness and mosaic values and the four background
 * scroll positions.
 */
void PauseScreenVBLank(void)
{
    DMA3_COPY_32(gOamData, OAM_BASE, OAM_SIZE / sizeof(u32));

    WRITE_16(REG_DISPCNT, PAUSE_SCREEN_DATA.dispcnt);
    WRITE_16(REG_BLDY, gWrittenToBldy);
    WRITE_16(REG_MOSAIC, gWrittenToMosaic_L);

    WRITE_16(REG_BG0HOFS, gBackgroundPositions.bg[0].x);
    WRITE_16(REG_BG0VOFS, gBackgroundPositions.bg[0].y);
    WRITE_16(REG_BG1HOFS, gBackgroundPositions.bg[1].x);
    WRITE_16(REG_BG1VOFS, gBackgroundPositions.bg[1].y);
    WRITE_16(REG_BG2HOFS, gBackgroundPositions.bg[2].x);
    WRITE_16(REG_BG2VOFS, gBackgroundPositions.bg[2].y);
    WRITE_16(REG_BG3HOFS, gBackgroundPositions.bg[3].x);
    WRITE_16(REG_BG3VOFS, gBackgroundPositions.bg[3].y);
}
