#include "globals.h"

#include "gba.h"
#include "macros.h"

/**
 * @brief 773f8 | 28 | Sets the pause debug window to the background vertical position
 *
 * Ported from the decomp.me scratch nM76W by biosp4rk (100% match).
 */
void PauseScreenSetPauseDebugWindow(void)
{
    s32 yPosition;

    yPosition = 0x200 - gBackgroundPositions.bg[1].y;
    if (yPosition > SCREEN_SIZE_Y)
        yPosition = SCREEN_SIZE_Y;

    WRITE_16(REG_WIN0V, C_16_2_8(yPosition, SCREEN_SIZE_Y));
}
