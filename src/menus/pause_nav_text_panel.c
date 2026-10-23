#include "globals.h"

#include "audio_wrappers.h"

#include "constants/audio.h"

/**
 * @brief 78ba4 | a0 | Sets the navigation text panel OAM for the pause screen
 *
 * Ported from the decomp.me scratch Fd37k by biosp4rk (100% match).
 * The two panels reuse the ids/positions of the neighbouring pause screen OAM
 * entries, so only the two OAM ids and the shared position are touched here.
 */
void PauseScreenSetNavigationTextPanelOam(u8 arg0)
{
    if (arg0 == 1)
    {
        PAUSE_SCREEN_DATA.oam[4].oamId = 0x44;
        PAUSE_SCREEN_DATA.oam[5].oamId = 0x47;
    }
    else if (arg0 == 2)
    {
        PAUSE_SCREEN_DATA.oam[4].oamId = 0x43;
        PAUSE_SCREEN_DATA.oam[5].oamId = 0x46;
        SoundPlay(SOUND_20A);
    }
    else if (arg0 == 3)
    {
        PAUSE_SCREEN_DATA.oam[4].oamId = 0x45;
        PAUSE_SCREEN_DATA.oam[5].oamId = 0x48;
        SoundPlay(SOUND_20B);
    }

    if (arg0 != 0)
    {
        PAUSE_SCREEN_DATA.oam[4].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[4].currentAnimationFrame = 0;

        PAUSE_SCREEN_DATA.oam[5].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[5].currentAnimationFrame = 0;
    }

    PAUSE_SCREEN_DATA.oam[5].xPosition = PAUSE_SCREEN_DATA.oam[4].xPosition;
    PAUSE_SCREEN_DATA.oam[5].yPosition = PAUSE_SCREEN_DATA.oam[4].yPosition;

    PAUSE_SCREEN_DATA.oam[3].xPosition = PAUSE_SCREEN_DATA.oam[4].xPosition;
    PAUSE_SCREEN_DATA.oam[3].yPosition = PAUSE_SCREEN_DATA.oam[4].yPosition;
}
