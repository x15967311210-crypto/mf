#include "globals.h"

#include "gba/keys.h"
#include "gba/memory.h"

/**
 * @brief 77270 | a8 | Moves the pause-screen debug cursor one tile per input
 *
 * Ported from the decomp.me scratch b4DeC by biosp4rk (100% match).
 * The cursor only moves while the debug value is not being edited and the A
 * button is not held; the direction checks are per axis, so up/down and
 * left/right can arrive in the same frame.
 */
void PauseScreenMoveDebugCursor(void)
{
    bools32 notEditing;

    notEditing = !(gButtonInput & KEY_A) && !PAUSE_SCREEN_DATA.pauseDebugEditingValue;

    if (notEditing)
    {
        if (gChangedInput & KEY_UP)
        {
            if (PAUSE_SCREEN_DATA.oam[0].yPosition != 0)
                PAUSE_SCREEN_DATA.oam[0].yPosition -= TILE_DIM;
        }
        else if (gChangedInput & KEY_DOWN)
        {
            if (PAUSE_SCREEN_DATA.oam[0].yPosition < 18 * TILE_DIM)
                PAUSE_SCREEN_DATA.oam[0].yPosition += TILE_DIM;
        }

        if (gChangedInput & KEY_RIGHT)
        {
            if (PAUSE_SCREEN_DATA.oam[0].xPosition < 29 * TILE_DIM)
                PAUSE_SCREEN_DATA.oam[0].xPosition += TILE_DIM;
        }
        else if (gChangedInput & KEY_LEFT)
        {
            if (PAUSE_SCREEN_DATA.oam[0].xPosition != 0)
                PAUSE_SCREEN_DATA.oam[0].xPosition -= TILE_DIM;
        }
    }
}
