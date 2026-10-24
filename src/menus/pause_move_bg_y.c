#include "globals.h"

/**
 * @brief 77384 | 74 | Moves pause-screen background 0/1 to a target Y position
 *
 * Ported from the decomp.me scratch ebAfU by biosp4rk (100% match).
 * The vertical step is the pause timer plus 4 frames, clamped to 32 pixels; the
 * direction is the sign of (current - target).  The completion test is
 * unsigned while rising and signed while falling, so the cast through s16 for
 * `yPosition` is part of the decompiled behavior, not a stylistic choice.
 */
bools32 PauseScreenMoveBackgroundToYPosition(u8 bg, u16 target)
{
    bools32 result;
    s32 direction;
    s32 yPosition;

    result = FALSE;

    if (gBackgroundPositions.bg[bg].y > target)
        direction = -1;
    else
        direction = 1;

    if (PAUSE_SCREEN_DATA.timer + 4 < 32)
        gBackgroundPositions.bg[bg].y += direction * (PAUSE_SCREEN_DATA.timer + 4);
    else
        gBackgroundPositions.bg[bg].y += direction * 32;

    if (direction > 0)
    {
        if (gBackgroundPositions.bg[bg].y >= target)
            result = TRUE;
    }
    else
    {
        yPosition = (s16)gBackgroundPositions.bg[bg].y;
        if (yPosition <= target)
            result = TRUE;
    }

    if (result)
        gBackgroundPositions.bg[bg].y = target;

    return result;
}
