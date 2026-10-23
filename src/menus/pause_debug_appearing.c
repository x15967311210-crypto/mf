#include "globals.h"

#include "audio_wrappers.h"
#include "oam_id.h"

#include "menus/pause_debug.h"

/* Pause-screen helpers that are still assembly; they have no C header yet. */
u32 PauseScreenMoveBackgroundToYPosition(u8 bg, u16 y);
void PauseScreenSetPauseDebugWindow(void);
void unk_77840(u32 action);

/**
 * @brief 77420 | 80 | Handles the debug menu window appearing
 *
 * Ported from the decomp.me scratch ORNtH by biosp4rk (100% match).
 */
bools32 PauseDebugWindowAppearing(void)
{
    bools32 result;

    result = FALSE;

    switch (PAUSE_SCREEN_DATA.pauseDebugEditingValue)
    {
        case 0:
            SoundPlay(0x200);
            UpdateMenuOamDataId(0x10, 0x29);
            PAUSE_SCREEN_DATA.pauseDebugEditingValue = 2;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 1:
            if (PAUSE_SCREEN_DATA.timer > 0x10)
            {
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 2;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case 2:
            if (PauseScreenMoveBackgroundToYPosition(1, 0x200))
            {
                UpdateMenuOamDataId(0x10, 0x28);
                UpdateMenuOamDataId(0x11, 0x2A);
                unk_77840(3);

                if (PAUSE_SCREEN_DATA.enableDebug != 0)
                    PauseDebugSetupCursor();

                result = TRUE;
            }

            PauseScreenSetPauseDebugWindow();
            break;
    }

    return result;
}
