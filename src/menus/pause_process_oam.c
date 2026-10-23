#include "globals.h"

#include "audio_wrappers.h"
#include "oam.h"

#include "data/menus/pause_screen_map_data.h"

/**
 * @brief 783f0 | 684 | Animates every live pause-screen OAM entry and emits its
 *                     parts to the OAM buffer
 *
 * Ported from the decomp.me scratch GoKlR by biosp4rk (100% match).
 */
void PauseScreenProcessOam(void)
{
    s32 nextSlot;
    s32 currSlot;
    s16 yPosition;
    s16 xPosition;
    u16* dst;
    const u16* src;
    u16 part;
    const struct FrameData* pFrame;
    s32 i;
    u8 priority;
    u8 objMode;

    dst = (u16*)(&gOamData);
    dst += gNextOamSlot * 4;
    nextSlot = gNextOamSlot;
    currSlot = nextSlot;

    for (i = 0; i < 0x28; i++)
    {
        if (PAUSE_SCREEN_DATA.oam[i].oamId == 0)
            continue;

        PAUSE_SCREEN_DATA.oam[i].ended = 0;

        switch (PAUSE_SCREEN_DATA.oam[i].oamId)
        {
            case 0x8B:
            default:
                pFrame = sUnk_79bec0[PAUSE_SCREEN_DATA.oam[i].oamId];
                PAUSE_SCREEN_DATA.oam[i].animationDurationCounter = 0;
                break;

            case 0x0:
                break;

            case 0x1:
            case 0x2:
            case 0x3:
            case 0x4:
            case 0x5:
            case 0x6:
            case 0x7:
            case 0x8:
            case 0x9:
            case 0xB:
            case 0xC:
            case 0xE:
            case 0xF:
            case 0x16:
            case 0x17:
            case 0x18:
            case 0x19:
            case 0x28:
            case 0x29:
            case 0x2A:
            case 0x2B:
            case 0x3D:
            case 0x3E:
            case 0x4B:
            case 0x4C:
            case 0x60:
            case 0x67:
                pFrame = sUnk_79bec0[PAUSE_SCREEN_DATA.oam[i].oamId];

                if (PAUSE_SCREEN_DATA.oam[i].animationDurationCounter >=
                    pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer)
                {
                    PAUSE_SCREEN_DATA.oam[i].animationDurationCounter = 0;
                    PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame++;

                    if (pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer == 0)
                        PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame = 0;
                }
                break;

            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
                pFrame = sUnk_79bec0[PAUSE_SCREEN_DATA.oam[i].oamId];

                if (PAUSE_SCREEN_DATA.oam[i].animationDurationCounter >=
                    pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer)
                {
                    PAUSE_SCREEN_DATA.oam[i].animationDurationCounter = 0;
                    PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame++;

                    if (pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer == 0)
                    {
                        PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame = 0;

                        if (PAUSE_SCREEN_DATA.unk_28 != 1)
                        {
                            if (PAUSE_SCREEN_DATA.unk_0 != 0)
                                SoundPlay(0x11A);
                            else
                                SoundPlay(0x12B);
                        }
                    }
                }
                break;

            case 0x41:
            case 0x43:
            case 0x45:
            case 0x46:
            case 0x48:
            case 0x49:
            case 0x4A:
            case 0x4D:
            case 0x50:
            case 0x53:
            case 0x56:
            case 0x59:
            case 0x5C:
                pFrame = sUnk_79bec0[PAUSE_SCREEN_DATA.oam[i].oamId];

                if (pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame + 1].timer == 0)
                    PAUSE_SCREEN_DATA.oam[i].ended = TRUE;

                if (PAUSE_SCREEN_DATA.oam[i].animationDurationCounter >=
                    pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer)
                {
                    PAUSE_SCREEN_DATA.oam[i].animationDurationCounter = 0;
                    PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame++;

                    if (pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer == 0)
                        PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame--;
                }
                break;

            case 0x10:
            case 0x42:
            case 0x4F:
            case 0x52:
            case 0x55:
            case 0x58:
            case 0x5B:
            case 0x5E:
            case 0x62:
            case 0x66:
                pFrame = sUnk_79bec0[PAUSE_SCREEN_DATA.oam[i].oamId];

                if (PAUSE_SCREEN_DATA.oam[i].animationDurationCounter <
                    pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer)
                    break;

                PAUSE_SCREEN_DATA.oam[i].animationDurationCounter = 0;
                PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame++;

                if (pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer != 0)
                    break;

                PAUSE_SCREEN_DATA.oam[i].oamId = 0;
                PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame = 0;
                continue;

            case 0x5F:
                pFrame = sUnk_79bec0[PAUSE_SCREEN_DATA.oam[i].oamId];

                if (PAUSE_SCREEN_DATA.oam[i].animationDurationCounter >=
                    pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer)
                {
                    PAUSE_SCREEN_DATA.oam[i].animationDurationCounter = 0;
                    PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame++;

                    if (pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer == 0)
                    {
                        PAUSE_SCREEN_DATA.oam[i].oamId++;
                        pFrame = sUnk_79bec0[PAUSE_SCREEN_DATA.oam[i].oamId];
                        PAUSE_SCREEN_DATA.oam[i].animationDurationCounter = 0;
                        PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame = 0;
                    }
                }
                break;

            case 0x63:
                pFrame = sUnk_79bec0[PAUSE_SCREEN_DATA.oam[i].oamId];

                if (PAUSE_SCREEN_DATA.oam[i].animationDurationCounter >=
                    pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer)
                {
                    PAUSE_SCREEN_DATA.oam[i].animationDurationCounter = 0;
                    PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame++;

                    if (pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer == 0)
                    {
                        PAUSE_SCREEN_DATA.oam[i].oamId++;
                        pFrame = sUnk_79bec0[PAUSE_SCREEN_DATA.oam[i].oamId];
                        PAUSE_SCREEN_DATA.oam[i].animationDurationCounter = 0;
                        PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame = 0;

                        PAUSE_SCREEN_DATA.oam[6].oamId = 0x67;
                        PAUSE_SCREEN_DATA.oam[6].animationDurationCounter = 0;
                        PAUSE_SCREEN_DATA.oam[6].currentAnimationFrame = 0;
                    }
                }
                break;

            case 0x1B:
            case 0x1D:
            case 0x1F:
            case 0x21:
            case 0x23:
            case 0x25:
            case 0x27:
            case 0x35:
            case 0x65:
                pFrame = sUnk_79bec0[PAUSE_SCREEN_DATA.oam[i].oamId];

                if (PAUSE_SCREEN_DATA.oam[i].animationDurationCounter >=
                    pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer)
                {
                    PAUSE_SCREEN_DATA.oam[i].animationDurationCounter = 0;
                    PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame++;

                    if (pFrame[PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame].timer == 0)
                    {
                        PAUSE_SCREEN_DATA.oam[i].oamId--;
                        pFrame = sUnk_79bec0[PAUSE_SCREEN_DATA.oam[i].oamId];
                        PAUSE_SCREEN_DATA.oam[i].animationDurationCounter = 0;
                        PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame = 0;
                    }
                }
                break;
        }

        PAUSE_SCREEN_DATA.oam[i].animationDurationCounter++;

        yPosition = (u16)(PAUSE_SCREEN_DATA.oam[i].yPosition + 4);
        xPosition = (u16)(PAUSE_SCREEN_DATA.oam[i].xPosition + 4);

        // Offset by current frame
        pFrame += PAUSE_SCREEN_DATA.oam[i].currentAnimationFrame;

        // Get raw data pointer
        src = pFrame->pFrame;

        priority = PAUSE_SCREEN_DATA.oam[i].priority;
        objMode = PAUSE_SCREEN_DATA.oam[i].objMode;

        // Check for buffer overflow
        if (nextSlot + *src > 0x7F)
            break;

        // Add part count
        nextSlot += *src++;

        for (; currSlot < nextSlot; currSlot++)
        {
            // Copy raw contents and implement positions
            part = *src++;
            *dst++ = part;

            gOamData[currSlot].split.y = part + yPosition;

            part = *src++;
            *dst++ = part;

            gOamData[currSlot].split.x = (part + xPosition) & 0x1FF;
            *dst++ = *src++;

            // Write special parameters
            gOamData[currSlot].split.priority = priority;
            gOamData[currSlot].split.objMode = objMode;

            dst++;
        }
    }

    gNextOamSlot = nextSlot;
}
