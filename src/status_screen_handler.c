#include "globals.h"

#include "gba.h"

/**
 * @brief 7e678 | 34 | Status screen debug/pause input handler
 *
 * Opens the pause debug editor when B+L+R are pressed together, unless a debug
 * value is already being edited.
 */
void StatusScreenHandler(void)
{
    if ((gChangedInput & (KEY_B | KEY_L | KEY_R)) != 0 && PAUSE_SCREEN_DATA.pauseDebugEditingValue == 0)
    {
        PAUSE_SCREEN_DATA.unk_28 = 7;
        PAUSE_SCREEN_DATA.timer = 0;
        PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0;
    }
}
