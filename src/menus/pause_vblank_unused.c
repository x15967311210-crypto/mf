#include "globals.h"

#include "gba.h"
#include "macros.h"

/* 0x0300000A: BG3 control value the pause screen writes once.  The address is
   a linker symbol (linker.ld), not a literal in this file. */
extern u16 gUnk_300000a;

/**
 * @brief 76928 | 5c | Unused pause screen VBlank callback
 *
 * Ported from the decomp.me scratch 8gUMw by biosp4rk (100% match).
 */
void PauseScreenVBLank_Unused(void)
{
    WRITE_16(REG_BG3HOFS, 0);
    WRITE_16(REG_BG3VOFS, 0);

    WRITE_16(REG_DISPCNT, PAUSE_SCREEN_DATA.dispcnt);

    if (gUnk_300000a != 0)
    {
        WRITE_16(REG_BG3CNT, gUnk_300000a);
        gUnk_300000a = 0;
    }

    WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
}
