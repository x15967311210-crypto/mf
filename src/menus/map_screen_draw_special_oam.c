#include "globals.h"

#include "menus/pause_screen_map.h"

#include "structs/samus.h"

/* The three OAM tables below live in the ROM data added by the shift work, so
   they are declared here but never defined: linker.ld places them.  Leave them
   non-const.  With a `const` qualifier agbcc keeps the row address in a
   register across the OAM stores and emits 0x28 bytes less than the original
   function; the 0x2CC baseline is only reproduced with the tables unqualified
   (and the ROM never writes them). */

/* Security-level OAM table in the trailing event-data blob: the four
   [OAM slot, OAM id] pairs at 0x576150.  linker.ld names it relative to the
   exported sSecurityUnlockEvents symbol, so this file never spells out a ROM
   address. */
extern u8 sUnk_576150[][2];

/* Completion/tank OAM tables: the four [OAM slot, OAM id, x position,
   y position] rows at 0x79be8c and the three at 0x79be9c.  The storage is the
   sUnk_79be88 array in src/menus/pause_screen_map.c; linker.ld names these
   views (offset 4 and 0x14 into that array) relative to the exported
   sExploredMinimapBitFlags symbol that precedes it in .data. */
extern u8 sUnk_79be8c[][4];
extern u8 sUnk_79be9c[][4];

/**
 * @brief 77e40 | 2cc | Draws the map screen's security-level and tank OAM
 *
 * Ported from the decomp.me scratch 5C5lg by biosp4rk (100% match).
 */
void MapScreenDrawSpecialOam(u8 arg0)
{
    s32 priority;
    u32 i;
    s32 securityLevel;
    u32 j;
    u8 index;

    if (gPauseScreenFlag == 4)
        return;

    switch (arg0)
    {
        case 0:
            priority = PAUSE_SCREEN_DATA.unk_0 != 0 ? 1 : 3;

            for (i = 0; i < 4; i++)
            {
                securityLevel = i + 1;
                j = gEquipment.securityHatchLevel != UCHAR_MAX &&
                    gEquipment.securityHatchLevel >= securityLevel ? 1 : 0;

                index = sUnk_576150[i][0];
                PAUSE_SCREEN_DATA.oam[index].oamId = sUnk_576150[i][1] + j;
                PAUSE_SCREEN_DATA.oam[index].yPosition = 0x24;
                PAUSE_SCREEN_DATA.oam[index].xPosition = 0xD4;
                PAUSE_SCREEN_DATA.oam[index].priority = priority;
            }
            break;

        case 1:
            for (i = 0; i < 4; i++)
            {
                securityLevel = i + 1;
                j = gEquipment.securityHatchLevel != UCHAR_MAX &&
                    gEquipment.securityHatchLevel >= securityLevel ? 1 : 0;

                PAUSE_SCREEN_DATA.oam[sUnk_576150[i][0]].oamId = sUnk_576150[i][1] + j;
            }
            break;

        case 2:
            for (i = 0; i < 4; i++)
            {
                PAUSE_SCREEN_DATA.oam[sUnk_576150[i][0]].oamId = 0;
            }
            break;
    }

    i = FALSE;

    if (gGameCompletion.completedGame == 0)
        i = TRUE;

    if (PAUSE_SCREEN_DATA.unk_0 != 0)
        i = TRUE;

    if (i)
    {
        PAUSE_SCREEN_DATA.unk_274 = 0;
        return;
    }

    if (arg0 != 0)
        return;

    i = PAUSE_SCREEN_DATA.unk_0 != 0 ? 1 : 3;

    PauseScreenMapCountTanks();
    PauseScreenMapDrawIgtAndTanks(0);

    for (j = 0; j < 4; j++)
    {
        PAUSE_SCREEN_DATA.oam[sUnk_79be8c[j][0]].oamId = sUnk_79be8c[j][1];
        PAUSE_SCREEN_DATA.oam[sUnk_79be8c[j][0]].priority = i;
        PAUSE_SCREEN_DATA.oam[sUnk_79be8c[j][0]].xPosition = sUnk_79be8c[j][2];
        PAUSE_SCREEN_DATA.oam[sUnk_79be8c[j][0]].yPosition = sUnk_79be8c[j][3];
    }

    for (j = 0; j < 3; j++)
    {
        PAUSE_SCREEN_DATA.oam[sUnk_79be9c[j][0]].priority = i;
        PAUSE_SCREEN_DATA.oam[sUnk_79be9c[j][0]].xPosition = sUnk_79be9c[j][2];
        PAUSE_SCREEN_DATA.oam[sUnk_79be9c[j][0]].yPosition = sUnk_79be9c[j][3];
    }

    if (PAUSE_SCREEN_DATA.maxEnergyTanks == PAUSE_SCREEN_DATA.currentEnergyTanks)
        PAUSE_SCREEN_DATA.oam[sUnk_79be9c[0][0]].oamId = sUnk_79be9c[0][1];

    if (PAUSE_SCREEN_DATA.maxMissileTanks == PAUSE_SCREEN_DATA.currentMissileTanks)
        PAUSE_SCREEN_DATA.oam[sUnk_79be9c[1][0]].oamId = sUnk_79be9c[1][1];

    if (PAUSE_SCREEN_DATA.maxPowerBombTanks == PAUSE_SCREEN_DATA.currentPowerBombTanks)
        PAUSE_SCREEN_DATA.oam[sUnk_79be9c[2][0]].oamId = sUnk_79be9c[2][1];
}
