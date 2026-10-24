#include "globals.h"

#include "gba.h"
#include "macros.h"

#include "constants/event.h"

#include "structs/event.h"

#include "dma.h"
#include "init_helpers.h"
#include "oam.h"

/* Still assembly: the pause screen's init/step driver and the two map-screen
   helpers it calls.  Their headers do not declare them yet. */
s32 PauseScreenInit(void);
s32 PauseScreenCallCurrentHandler(void);
void unk_7c440(void);
void unk_7cfb0(void);
void MapScreenUpdateArrowsAndBlinkingSquare(void);
void PauseScreenProcessOam(void);

/**
 * @brief 765f8 | 2ac | Pause screen main handler
 *
 * Ported from the decomp.me scratch EaoHi by biosp4rk (100% match).
 * Advances the pause screen state machine (init, fade in, per-menu update,
 * fade out, done), then rebuilds the map-screen OAM.
 */
s32 PauseScreenHandler(void)
{
    s32 done;
    s32 unk_0;
    s32 evaDiff;
    s32 tmp;

    gNextOamSlot = 0;
    done = FALSE;

    switch (gUnk_3000b85)
    {
        case 0:
            gUnk_3000b85 = PauseScreenInit();
            break;

        case 1:
            unk_0 = PAUSE_SCREEN_DATA.unk_0;
            if (unk_0 != 0)
            {
                if (gPauseScreenFlag == 4)
                {
                    if (C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva) != 0x508)
                    {
                        if (gWrittenToBldalpha_Eva != 8)
                        {
                            gWrittenToBldalpha_Eva++;
                            if (gWrittenToBldalpha_Eva > 8)
                                gWrittenToBldalpha_Eva = 8;
                        }

                        if (gWrittenToBldalpha_Evb != 5)
                            gWrittenToBldalpha_Evb++;
                    }
                    else
                    {
                        gUnk_3000b85++;
                        WRITE_16(REG_BLDCNT, 0x3F44);
                    }
                }
                else
                {
                    if (C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva) != 0x508)
                    {
                        if (gWrittenToBldalpha_Eva != 8)
                        {
                            gWrittenToBldalpha_Eva += 2;
                            if (gWrittenToBldalpha_Eva > 8)
                                gWrittenToBldalpha_Eva = 8;
                        }

                        if (gWrittenToBldalpha_Evb != 5)
                            gWrittenToBldalpha_Evb++;
                    }
                    else
                    {
                        gUnk_3000b85++;
                        WRITE_16(REG_BLDCNT, 0x3F44);
                    }
                }

                WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
            }
            else if (gWrittenToBldy != 0)
            {
                if (gWrittenToBldy > 4)
                    gWrittenToBldy -= 4;
                else
                    gWrittenToBldy = unk_0;
            }
            else
            {
                gUnk_3000b85++;
                WRITE_16(REG_BLDCNT, 0x3F00);
                WRITE_16(REG_BLDALPHA, 0x40C);
            }
            break;

        case 2:
            if (PauseScreenCallCurrentHandler() != 0)
            {
                if (PAUSE_SCREEN_DATA.unk_0 != 0)
                {
                    WRITE_16(REG_BLDCNT, 0x3F7F);
                    gWrittenToBldalpha_Eva = READ_16(REG_BLDALPHA);
                    gWrittenToBldalpha_Evb = HIGH_BYTE(gWrittenToBldalpha_Eva);
                    gWrittenToBldalpha_Eva = LOW_BYTE(gWrittenToBldalpha_Eva);
                }
                else
                {
                    gWrittenToBldy = 0;
                    WRITE_16(REG_BLDCNT, 0xFF);
                }

                gUnk_3000b85++;
            }

            if (PAUSE_SCREEN_DATA.unk_264 == 0)
            {
                unk_7c440();
                unk_7cfb0();
            }
            break;

        case 3:
            if (PAUSE_SCREEN_DATA.unk_0 != 0)
            {
                if (gPauseScreenFlag == 4)
                    evaDiff = 1;
                else
                    evaDiff = 2;

                if ((gWrittenToBldalpha_Evb | gWrittenToBldalpha_Eva) != 0)
                {
                    if (gWrittenToBldalpha_Eva >= evaDiff)
                        gWrittenToBldalpha_Eva -= evaDiff;
                    else
                        gWrittenToBldalpha_Eva = 0;

                    if (gWrittenToBldalpha_Evb != 0)
                        gWrittenToBldalpha_Evb--;
                }
                else
                {
                    gUnk_3000b85++;
                }

                WRITE_16(REG_BLDALPHA, C_16_2_8(gWrittenToBldalpha_Evb, gWrittenToBldalpha_Eva));
            }
            else if (gWrittenToBldy < BLDY_MAX_VALUE)
            {
                gWrittenToBldy += 4;
                if (gWrittenToBldy > BLDY_MAX_VALUE)
                    gWrittenToBldy = BLDY_MAX_VALUE;
            }
            else
            {
                gUnk_3000b85++;
            }
            break;

        case 4:
            if (gPauseScreenFlag == 3 && gEventCounter == EVENT_NAVIGATION_ROOM_LEAVING_SRX_2 &&
                gPreviousCutscene != CUTSCENE_MONOLOGUE_FEDERATION)
            {
                gPauseScreenFlag = 5;
                gCurrentCutscene = CUTSCENE_MONOLOGUE_FEDERATION;
                DmaTransfer(3, EWRAM_BASE + 0x1C000, VRAM_BASE + 0x10000, 0x8000, 32);
            }

            done = TRUE;
            gUnk_3000b85 = 0;
            break;
    }

    MapScreenUpdateArrowsAndBlinkingSquare();
    PauseScreenProcessOam();
    ResetFreeOam();

    return done;
}
