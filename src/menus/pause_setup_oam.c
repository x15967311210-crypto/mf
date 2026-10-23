#include "globals.h"

#include "data/event_data.h"

#include "menus/pause_debug.h"

#include "oam_id.h"
#include "room.h"

#include "structs/connection.h"

/* Pause screen OAM tables that live inside the trailing event-data blob: the
   per-area [unused, OAM id] pairs at 0x576142 and the four
   [OAM slot, OAM id, unused, y position] rows at 0x576158.  The blob's own
   label is file-local in src/data/event_data.c, so linker.ld names both
   arrays relative to the exported sSecurityUnlockEvents symbol that precedes
   the blob; neither file spells out a ROM address. */
extern const u8 sUnk_576142[][2];
extern const u8 sUnk_576158[][4];

/* Still assembly (asm/disasm_0x080765f8_08077084_08077420.s): the map screen
   helpers this routine drives.  Their headers do not declare them yet. */
void MapScreenUpdateArrowsAndBlinkingSquare(void);
void MapScreenDrawSpecialOam(u8 arg0);

/**
 * @brief 7810c | 2e4 | Clears the pause screen OAM and sets up the map, status
 *                     and debug slots
 *
 * Ported from the decomp.me scratch 4I24u by biosp4rk (100% match).
 */
void PauseScreenSetupOam(void)
{
    s32 i;

    PAUSE_SCREEN_DATA.unk_C = 0;
    PAUSE_SCREEN_DATA.unk_E[0] = 0;
    PAUSE_SCREEN_DATA.unk_E[1] = 0;
    PAUSE_SCREEN_DATA.unk_E[2] = 0;
    PAUSE_SCREEN_DATA.unk_E[3] = 0;
    PAUSE_SCREEN_DATA.unk_17 = 0;
    PAUSE_SCREEN_DATA.unk_18 = 0;

    for (i = 0; i < 0x28; i++)
    {
        PAUSE_SCREEN_DATA.oam[i].oamId = 0;
        PAUSE_SCREEN_DATA.oam[i].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame = 0;
        PAUSE_SCREEN_DATA.oam[i].xPosition = 0;
        PAUSE_SCREEN_DATA.oam[i].yPosition = 0;
        PAUSE_SCREEN_DATA.oam[i].priority = 0;
        PAUSE_SCREEN_DATA.oam[i].objMode = 0;
    }

    if (PAUSE_SCREEN_DATA.unk_28 != 4 && gPauseScreenFlag != 4)
        PAUSE_SCREEN_DATA.oam[0x20].oamId = 1;

    if (PAUSE_SCREEN_DATA.unk_0 != 0)
    {
        PAUSE_SCREEN_DATA.oam[0x20].priority = 1;
        PAUSE_SCREEN_DATA.oam[0x1F].priority = 1;
    }
    else
    {
        PAUSE_SCREEN_DATA.oam[0x20].priority = 3;
        PAUSE_SCREEN_DATA.oam[0x1F].priority = 3;
    }

    MapScreenUpdateArrowsAndBlinkingSquare();

    if (PAUSE_SCREEN_DATA.unk_28 == 1)
    {
        if (PAUSE_SCREEN_DATA.enableDebug != 0)
            PauseDebugSetupCursor();
    }
    else
    {
        PAUSE_SCREEN_DATA.oam[0].oamId = 0;
        PAUSE_SCREEN_DATA.oam[0].yPosition = 0;
        PAUSE_SCREEN_DATA.oam[0].xPosition = 0;
    }

    if (PAUSE_SCREEN_DATA.unk_0 == 0)
    {
        PAUSE_SCREEN_DATA.oam[0x10].oamId = 0x28;
        PAUSE_SCREEN_DATA.oam[0x10].yPosition = 2;
        PAUSE_SCREEN_DATA.oam[0x10].xPosition = 0xD6;
        PAUSE_SCREEN_DATA.oam[0x10].priority = 2;

        PAUSE_SCREEN_DATA.oam[0x11].oamId = 0x2A;
        PAUSE_SCREEN_DATA.oam[0x11].yPosition = 2;
        PAUSE_SCREEN_DATA.oam[0x11].xPosition = 0x12;
        PAUSE_SCREEN_DATA.oam[0x11].priority = 2;

        if (gCurrentArea < 7)
            UpdateMenuOamDataId(0x12, sUnk_576142[gCurrentArea][1]);
        else
            UpdateMenuOamDataId(0x12, 0);

        PAUSE_SCREEN_DATA.oam[0x12].yPosition = 0;
        PAUSE_SCREEN_DATA.oam[0x12].xPosition = 0x74;
        PAUSE_SCREEN_DATA.oam[0x12].priority = 2;
    }

    MapScreenDrawSpecialOam(0);

    PAUSE_SCREEN_DATA.oam[0xF].yPosition = 0x20;
    PAUSE_SCREEN_DATA.oam[0xF].xPosition = 0xC0;
    PAUSE_SCREEN_DATA.oam[0xF].oamId = 0;

    for (i = 4; i > 0;)
    {
        i--;

        if (PAUSE_SCREEN_DATA.unk_0 == 0)
            PAUSE_SCREEN_DATA.oam[sUnk_576158[i][0]].oamId = sUnk_576158[i][1];

        PAUSE_SCREEN_DATA.oam[sUnk_576158[i][0]].xPosition = 0x100;
        PAUSE_SCREEN_DATA.oam[sUnk_576158[i][0]].yPosition = sUnk_576158[i][3];
        PAUSE_SCREEN_DATA.oam[sUnk_576158[i][0]].priority = 2;
    }

    if (PAUSE_SCREEN_DATA.unk_0 == 1)
    {
        PAUSE_SCREEN_DATA.oam[0x25].yPosition = 0x7C;
        PAUSE_SCREEN_DATA.oam[0x25].xPosition = 0x74;
        PAUSE_SCREEN_DATA.oam[0x25].oamId = 0x3E;
        PAUSE_SCREEN_DATA.oam[0x25].priority = 3;

        i = RoomGetClosedNavigationHatches();

        if (gPauseScreenFlag == 4)
        {
            i = 3;
            PAUSE_SCREEN_DATA.oam[0x25].oamId = 0x3D;
        }

        if (i & 2)
        {
            PAUSE_SCREEN_DATA.oam[0x26].yPosition = 0x4C;
            PAUSE_SCREEN_DATA.oam[0x26].xPosition = 0x18;
            PAUSE_SCREEN_DATA.oam[0x26].oamId = 0x3F;
            PAUSE_SCREEN_DATA.oam[0x26].priority = 3;
        }

        if (i & 1)
        {
            PAUSE_SCREEN_DATA.oam[0x27].yPosition = 0x4C;
            PAUSE_SCREEN_DATA.oam[0x27].xPosition = 0xD0;
            PAUSE_SCREEN_DATA.oam[0x27].oamId = 0x40;
            PAUSE_SCREEN_DATA.oam[0x27].priority = 3;
        }
    }
}
