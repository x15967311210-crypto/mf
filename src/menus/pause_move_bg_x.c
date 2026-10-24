#include "globals.h"

/**
 * @brief 77318 | 6c | Moves a pause-screen background to a target X position
 *
 * Ported from the decomp.me scratch dcBtA by biosp4rk (100% match).
 * The horizontal step is the pause timer plus 4 frames, clamped to 32 pixels;
 * the direction is the sign of (current - target).  The completion test is
 * unsigned while rising and signed while falling, so the cast through s16 for
 * `xPosition` is part of the decompiled behavior, not a stylistic choice.
 */
bools32 PauseScreenMoveBackgroundToXPosition(u8 bg, u16 target)
{
    bools32 result;
    s32 direction;
    s32 timer;
    s32 xPosition;

    result = FALSE;

    if (gBackgroundPositions.bg[bg].x > target)
        direction = -1;
    else
        direction = 1;

    if (PAUSE_SCREEN_DATA.timer + 4 < 32)
    {
        timer = PAUSE_SCREEN_DATA.timer + 4;
        gBackgroundPositions.bg[bg].x += direction * timer;
    }
    else
        gBackgroundPositions.bg[bg].x += direction * 32;

    if (direction > 0)
    {
        if (gBackgroundPositions.bg[bg].x >= target)
        {
            gBackgroundPositions.bg[bg].x = target;
            result = TRUE;
        }
    }
    else
    {
        xPosition = (s16)gBackgroundPositions.bg[bg].x;
        if (xPosition <= target)
        {
            direction = target;
            gBackgroundPositions.bg[bg].x += direction - xPosition;
            result = TRUE;
        }
    }

    return result;
}
