#include "globals.h"

#include "oam_id.h"

/* Navigation-conversation pop-up Y position table at 0x5766E0.  The bytes are
   the head of the sBlob_5766D4_prefix blob that follows the exported
   sCharacterWidths array in src/data/menus/pause_debug.c; linker.ld names this
   view relative to sCharacterWidths, so this file never spells out a ROM
   address. */
extern const u8 sUnk_5766e0[];

/* Pause-screen navigation text panel OAM setter from pause_nav_text_panel.c. */
void PauseScreenSetNavigationTextPanelOam(u8 arg0);

/**
 * @brief 78ea4 | 274 | Runs the pause-screen navigation conversation panel sequence
 *
 * Ported from the decomp.me scratch aOOBj by biosp4rk (100% match).
 */
void NavigationConversationUpdatePanel(void)
{
    if (!(PAUSE_SCREEN_DATA.typeFlags & 1))
    {
        PAUSE_SCREEN_DATA.unk_238 = 0;
        PAUSE_SCREEN_DATA.unk_239 = 0;
        return;
    }

    PAUSE_SCREEN_DATA.unk_239++;

    switch (PAUSE_SCREEN_DATA.unk_238)
    {
        case 0:
            if (PAUSE_SCREEN_DATA.oam[4].yPosition == 0x7C)
            {
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            else
            {
                PAUSE_SCREEN_DATA.oam[4].yPosition -= 8;
                PauseScreenSetNavigationTextPanelOam(0);
            }
            break;

        case 1:
            if (PAUSE_SCREEN_DATA.unk_239 > 8)
            {
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            break;

        case 2:
            PauseScreenSetNavigationTextPanelOam(2);
            PAUSE_SCREEN_DATA.unk_238++;
            PAUSE_SCREEN_DATA.unk_239 = 0;
            break;

        case 3:
            if (PAUSE_SCREEN_DATA.oam[4].ended)
            {
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            break;

        case 4:
            UpdateMenuOamDataId(3, 0x49);
            PAUSE_SCREEN_DATA.unk_238++;
            PAUSE_SCREEN_DATA.unk_239 = 0;
            break;

        case 5:
            if (PAUSE_SCREEN_DATA.oam[3].ended)
            {
                PAUSE_SCREEN_DATA.typeFlags |= 8;
                PAUSE_SCREEN_DATA.oam[1].xPosition = 8;
                PAUSE_SCREEN_DATA.oam[1].yPosition = sUnk_5766e0[0];
                PAUSE_SCREEN_DATA.oam[1].animationDurationCounter = 0;
                PAUSE_SCREEN_DATA.oam[1].currentAnimationFrame = 0;

                if (PAUSE_SCREEN_DATA.unk_1C != 5)
                    PAUSE_SCREEN_DATA.oam[1].oamId = 0xB;

                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            break;

        case 6:
            if (!(PAUSE_SCREEN_DATA.typeFlags & 8))
            {
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            else if (PAUSE_SCREEN_DATA.unk_239 == 0x10)
            {
                UpdateMenuOamDataId(3, 0x4C);
            }

            if (PAUSE_SCREEN_DATA.unk_239 > 0x3C)
                PAUSE_SCREEN_DATA.unk_239 = 0x3C;
            break;

        case 7:
            UpdateMenuOamDataId(3, 0x4A);
            PAUSE_SCREEN_DATA.unk_238++;
            PAUSE_SCREEN_DATA.unk_239 = 0;
            break;

        case 8:
            if (PAUSE_SCREEN_DATA.oam[3].ended)
            {
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            break;

        case 9:
            PAUSE_SCREEN_DATA.oam[1].oamId = 0;
            PauseScreenSetNavigationTextPanelOam(3);
            PAUSE_SCREEN_DATA.unk_238++;
            PAUSE_SCREEN_DATA.unk_239 = 0;
            break;

        case 10:
            if (PAUSE_SCREEN_DATA.oam[4].ended)
            {
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            break;

        case 11:
            if (PAUSE_SCREEN_DATA.oam[4].yPosition != 0xCC)
            {
                PAUSE_SCREEN_DATA.oam[4].yPosition += 8;
                PauseScreenSetNavigationTextPanelOam(0);
            }
            else
            {
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            break;

        case 12:
            if (PAUSE_SCREEN_DATA.unk_239 > 8)
            {
                PAUSE_SCREEN_DATA.typeFlags ^= 1;
                PAUSE_SCREEN_DATA.unk_238++;
                PAUSE_SCREEN_DATA.unk_239 = 0;
            }
            break;

        case 13:
            break;
    }
}
