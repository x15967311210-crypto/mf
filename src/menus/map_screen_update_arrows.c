#include "globals.h"

/* Pause-screen arrow table in the trailing event-data blob: the four
   [OAM slot, OAM id, x position, y position] rows at 0x576158.  linker.ld
   names it relative to the exported sSecurityUnlockEvents symbol, so this
   file never spells out a ROM address. */
extern const u8 sUnk_576158[][4];

/**
 * @brief 77c7c | 1c4 | Positions the map-screen arrows and blinking square
 *
 * Ported from the decomp.me scratch FePAn by biosp4rk (100% match).
 */
void MapScreenUpdateArrowsAndBlinkingSquare(void)
{
    s32 var_r1;
    u8 tmp;

    PAUSE_SCREEN_DATA.oam[0x20].xPosition = PAUSE_SCREEN_DATA.mapX * 8 - gBackgroundPositions.bg[3].x;
    PAUSE_SCREEN_DATA.oam[0x20].yPosition = PAUSE_SCREEN_DATA.mapY * 8 - gBackgroundPositions.bg[3].y;

    var_r1 = TRUE;

    tmp = PAUSE_SCREEN_DATA.oam[0x1F].oamId;
    if (tmp != 0x12 && PAUSE_SCREEN_DATA.oam[0x1F].oamId != 0x13 &&
        PAUSE_SCREEN_DATA.oam[0x1F].oamId != 0x14 && PAUSE_SCREEN_DATA.oam[0x1F].oamId != 0x15 &&
        PAUSE_SCREEN_DATA.oam[0x1F].oamId != 0xE && PAUSE_SCREEN_DATA.oam[0x1F].oamId != 0xF)
    {
        var_r1 = FALSE;
    }

    if (var_r1)
    {
        PAUSE_SCREEN_DATA.oam[0x1F].xPosition = PAUSE_SCREEN_DATA.navTargetX * 8 - gBackgroundPositions.bg[3].x;
        PAUSE_SCREEN_DATA.oam[0x1F].yPosition = PAUSE_SCREEN_DATA.navTargetY * 8 - gBackgroundPositions.bg[3].y;
    }

    if (gPauseScreenFlag != 2)
        return;

    if (PAUSE_SCREEN_DATA.unk_28 != 0)
    {
        PAUSE_SCREEN_DATA.oam[sUnk_576158[0][0]].xPosition = 0x100;
        PAUSE_SCREEN_DATA.oam[sUnk_576158[1][0]].xPosition = 0x100;
        PAUSE_SCREEN_DATA.oam[sUnk_576158[2][0]].xPosition = 0x100;
        PAUSE_SCREEN_DATA.oam[sUnk_576158[3][0]].xPosition = 0x100;
        return;
    }

    PAUSE_SCREEN_DATA.oam[sUnk_576158[0][0]].xPosition =
        PAUSE_SCREEN_DATA.unk_25A - PAUSE_SCREEN_DATA.mapViewX > 0xD ?
        sUnk_576158[0][2] : 0x100;

    PAUSE_SCREEN_DATA.oam[sUnk_576158[1][0]].xPosition =
        PAUSE_SCREEN_DATA.mapViewX - PAUSE_SCREEN_DATA.unk_25B > 0xE ?
        sUnk_576158[1][2] : 0x100;

    PAUSE_SCREEN_DATA.oam[sUnk_576158[2][0]].xPosition =
        PAUSE_SCREEN_DATA.mapViewY - PAUSE_SCREEN_DATA.unk_25C > 8 ?
        sUnk_576158[2][2] : 0x100;

    PAUSE_SCREEN_DATA.oam[sUnk_576158[3][0]].xPosition =
        PAUSE_SCREEN_DATA.unk_25D - PAUSE_SCREEN_DATA.mapViewY > 8 ?
        sUnk_576158[3][2] : 0x100;
}
