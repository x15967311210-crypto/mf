#include "globals.h"

#include "audio_wrappers.h"

/* Pause-screen helpers that are still assembly; they have no C header yet. */
u32 PauseScreenMoveBackgroundToYPosition(u8 bg, u16 y);
void PauseScreenSetPauseDebugWindow(void);
void unk_77840(u32 action);

/**
 * @brief 774a0 | 60 | Handles the debug menu window disappearing
 *
 * Ported from the decomp.me scratch AjzV0 by biosp4rk (100% match).
 */
bools32 PauseDebugWindowDisappearing(void)
{
    bools32 result;

    result = FALSE;

    switch (PAUSE_SCREEN_DATA.pauseDebugEditingValue)
    {
        case 0:
            SoundPlay(0x201);
            unk_77840(4);
            PAUSE_SCREEN_DATA.pauseDebugEditingValue = 2;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 1:
            if (PAUSE_SCREEN_DATA.timer > 4)
            {
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 2;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case 2:
            if (PauseScreenMoveBackgroundToYPosition(1, 0x100))
                result = TRUE;

            PauseScreenSetPauseDebugWindow();
            break;
    }

    return result;
}
