#include "globals.h"

/* Pause-screen typeFlags/transition state machine.  The typeFlags bitfield at
   PAUSE_SCREEN_DATA.typeFlags (offset 4) drives the navigation-conversation
   pop-up sequence; unk_23C/unk_23D are its state and timer bytes. */

/* Navigation-conversation pop-up Y position table at 0x5766E0.  The bytes are
   the head of the sBlob_5766D4_prefix blob that follows the exported
   sCharacterWidths array in src/data/menus/pause_debug.c; linker.ld names this
   view relative to sCharacterWidths, so this file never spells out a ROM
   address. */
extern const u8 sUnk_5766e0[];

/* Both neighbours are C files in this directory; the pause-screen dispatcher
   reaches them through the same prototypes. */
void unk_78af0(u8 arg0);
void MapScreenDrawSpecialOam(u8 arg0);

/**
 * @brief 78c44 | 260 | Runs the pause-screen navigation conversation transition
 *
 * Ported from the decomp.me scratch liWnT by biosp4rk (100% match).
 */
void unk_78c44(void)
{
    if (!(PAUSE_SCREEN_DATA.typeFlags & 6))
    {
        PAUSE_SCREEN_DATA.unk_23C = 0;
        PAUSE_SCREEN_DATA.unk_23D = 0;
        return;
    }

    PAUSE_SCREEN_DATA.unk_23D++;

    switch (PAUSE_SCREEN_DATA.unk_23C)
    {
        case 0:
            if (PAUSE_SCREEN_DATA.unk_23D > 0x10)
            {
                PAUSE_SCREEN_DATA.unk_23C++;
                PAUSE_SCREEN_DATA.unk_23D = 0;
            }
            break;

        case 1:
            PAUSE_SCREEN_DATA.oam[8].xPosition = 0x74;
            PAUSE_SCREEN_DATA.oam[8].yPosition = 0x1C;
            unk_78af0(2);
            MapScreenDrawSpecialOam(2);
            PAUSE_SCREEN_DATA.unk_23C++;
            PAUSE_SCREEN_DATA.unk_23D = 0;
            break;

        case 2:
            if (PAUSE_SCREEN_DATA.oam[8].ended && PAUSE_SCREEN_DATA.oam[9].ended)
            {
                PAUSE_SCREEN_DATA.unk_23C++;
                PAUSE_SCREEN_DATA.unk_23D = 0;
            }
            break;

        case 3:
            if (PAUSE_SCREEN_DATA.unk_23D > 0x10)
            {
                PAUSE_SCREEN_DATA.typeFlags |= 0x10;
                PAUSE_SCREEN_DATA.oam[2].xPosition = 8;
                PAUSE_SCREEN_DATA.oam[2].yPosition = sUnk_5766e0[2];
                PAUSE_SCREEN_DATA.oam[2].oamId = 0xB;
                PAUSE_SCREEN_DATA.oam[2].animationDurationCounter = 0;
                PAUSE_SCREEN_DATA.oam[2].currentAnimationFrame = 0;
                PAUSE_SCREEN_DATA.unk_23C++;
                PAUSE_SCREEN_DATA.unk_23D = 0;
            }
            break;

        case 4:
            if (!(PAUSE_SCREEN_DATA.typeFlags & 0x10))
            {
                PAUSE_SCREEN_DATA.unk_23C++;
                PAUSE_SCREEN_DATA.unk_23D = 0;
            }
            break;

        case 5:
            unk_78af0(3);
            PAUSE_SCREEN_DATA.oam[2].oamId = 0;
            PAUSE_SCREEN_DATA.oam[6].oamId = 0;
            PAUSE_SCREEN_DATA.unk_23C++;
            PAUSE_SCREEN_DATA.unk_23D = 0;
            break;

        case 6:
            if (PAUSE_SCREEN_DATA.oam[8].oamId == 0 && PAUSE_SCREEN_DATA.oam[9].oamId == 0)
            {
                PAUSE_SCREEN_DATA.unk_23C++;
                PAUSE_SCREEN_DATA.unk_23D = 0;
                MapScreenDrawSpecialOam(1);
            }
            break;

        case 7:
            if (PAUSE_SCREEN_DATA.unk_23D > 0x10)
            {
                PAUSE_SCREEN_DATA.unk_23C++;
                PAUSE_SCREEN_DATA.unk_23D = 0;

                if (PAUSE_SCREEN_DATA.typeFlags & 2)
                    PAUSE_SCREEN_DATA.typeFlags ^= 2;
                else if (PAUSE_SCREEN_DATA.typeFlags & 4)
                    PAUSE_SCREEN_DATA.typeFlags ^= 4;
            }
            break;

        case 8:
            break;
    }

    if (PAUSE_SCREEN_DATA.unk_1B > 1 && PAUSE_SCREEN_DATA.oam[7].oamId == 0x64)
    {
        PAUSE_SCREEN_DATA.oam[7].oamId++;
        PAUSE_SCREEN_DATA.oam[7].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[7].currentAnimationFrame = 0;
    }
}
