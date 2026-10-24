#include "globals.h"

#include "audio_wrappers.h"

/* Pause-screen navigation OAM id table at 0x5767F0: six [hidden icon,
   arrow, background] OAM id triplets.  The bytes are the 0x11C offset inside
   the sBlob_5766D4_prefix blob that follows the exported sCharacterWidths
   array in src/data/menus/pause_debug.c; linker.ld names this view relative
   to sCharacterWidths, so this file never spells out a ROM address. */
extern const u8 sUnk_5767f0[][3];

/**
 * @brief 78af0 | b4 | Updates the pause-screen navigation OAM ids and position
 *
 * Ported from the decomp.me scratch qEsyb by biosp4rk (100% match).
 */
void unk_78af0(u8 arg0)
{
    s32 index;
    s32 var_r5;

    if (arg0 != 0)
    {
        index = 0;
        if (PAUSE_SCREEN_DATA.typeFlags & 4)
            index = 3;

        if (arg0 == 1)
        {
            var_r5 = 0;
        }
        else if (arg0 == 2)
        {
            SoundPlay(0x20A);
            var_r5 = 1;
        }
        else if (arg0 == 3)
        {
            SoundPlay(0x20B);
            var_r5 = 2;
        }

        index += var_r5;
        PAUSE_SCREEN_DATA.oam[8].oamId = sUnk_5767f0[index][0];
        PAUSE_SCREEN_DATA.oam[9].oamId = sUnk_5767f0[index][1];
        PAUSE_SCREEN_DATA.oam[7].oamId = sUnk_5767f0[index][2];

        PAUSE_SCREEN_DATA.oam[8].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[8].currentAnimationFrame = 0;
        PAUSE_SCREEN_DATA.oam[9].animationDurationCounter = 0;
        PAUSE_SCREEN_DATA.oam[9].currentAnimationFrame = 0;
    }

    PAUSE_SCREEN_DATA.oam[9].xPosition = PAUSE_SCREEN_DATA.oam[8].xPosition;
    PAUSE_SCREEN_DATA.oam[9].yPosition = PAUSE_SCREEN_DATA.oam[8].yPosition;
}
