#include "globals.h"

#include "gba.h"
#include "gba/keys.h"
#include "macros.h"

#include "menus/pause_debug.h"
#include "menus/pause_screen_map.h"

#include "status_screen.h"

/* Pause-screen helpers that are still assembly; they have no C header yet. */
void CheckForMaintainedInput(void);
void PauseScreenMoveDebugCursor(void);
u32 PauseDebugWindowAppearing(void);
u32 PauseDebugWindowDisappearing(void);
u32 EasySleepMenuInit(void);
u32 EasySleepMenuQuit(void);
void NavigationConversationUpdatePopUp(void);
u32 NavigationConversationHandler(void);
u32 EasySleepMenuHandler(void);
void unk_7c630(void);
void unk_77840(u32 action);

// 0: Map screen
// 1: Status screen
// 2: ?
// 3: Navigation conversation
// 4: Map download
// 5: Easy sleep menu
// 6: Loading pause debug
// 7: Closing pause debug
// 8: ?
// 9: ?
// 10: ?
// 11: Start easy sleep?
// 12: Quit easy sleep?

/**
 * @brief 770b4 | 1bc | Calls the handler for the current pause screen menu
 *
 * Ported from the decomp.me scratch e4fR3 by biosp4rk (100% match).
 * PAUSE_SCREEN_DATA.unk_28 (the scratch's unk_28.unk_0) holds the menu id.
 */
bools32 PauseScreenCallCurrentHandler(void)
{
    bools32 close;

    close = FALSE;

    if (PAUSE_SCREEN_DATA.unk_28 != 2 && PAUSE_SCREEN_DATA.unk_28 != 3)
        CheckForMaintainedInput();

    APPLY_DELTA_TIME_INC(PAUSE_SCREEN_DATA.timer);

    switch (PAUSE_SCREEN_DATA.unk_28)
    {
        case 0:
            if (gChangedInput & (gButtonAssignments.pause | KEY_B))
                close = TRUE;
            else
                PauseScreenMapHandler();
            break;

        case 1:
            if (PAUSE_SCREEN_DATA.enableDebug)
            {
                PauseScreenMoveDebugCursor();
                PauseDebugHandler();
            }
            else
            {
                StatusScreenHandler();
            }
            break;

        case 2:
            close = TRUE;
            break;

        case 3:
            if (PAUSE_SCREEN_DATA.unk_264 != 0)
            {
                unk_7c630();
            }
            else
            {
                NavigationConversationUpdatePopUp();

                if (NavigationConversationHandler() != 0)
                    PAUSE_SCREEN_DATA.unk_28 = 9;
            }
            break;

        case 4:
            if (PauseScreenMapDownload() != 0)
                PAUSE_SCREEN_DATA.unk_28 = 8;
            break;

        case 5:
            if (EasySleepMenuHandler() != 0)
                PAUSE_SCREEN_DATA.unk_28 = 0xC;
            break;

        case 6:
            if (PauseDebugWindowAppearing() != 0)
            {
                PAUSE_SCREEN_DATA.unk_28 = 1;
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case 7:
            if (PauseDebugWindowDisappearing() != 0)
            {
                PAUSE_SCREEN_DATA.unk_28 = 0;
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case 8:
        case 10:
            PAUSE_SCREEN_DATA.unk_28 = 3;
            PAUSE_SCREEN_DATA.unk_C = 0;
            PAUSE_SCREEN_DATA.unk_E[0] = 0;
            PAUSE_SCREEN_DATA.unk_E[1] = 0;
            PAUSE_SCREEN_DATA.unk_E[2] = 0;
            PAUSE_SCREEN_DATA.unk_E[3] = 0;
            PAUSE_SCREEN_DATA.unk_8 = 0;
            PAUSE_SCREEN_DATA.unk_9 = 0;
            PAUSE_SCREEN_DATA.unk_A = 0;
            PAUSE_SCREEN_DATA.unk_B = 0;

            PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0;
            PAUSE_SCREEN_DATA.timer = 0;
            break;

        case 9:
            if (PAUSE_SCREEN_DATA.unk_0 != 0)
            {
                PAUSE_SCREEN_DATA.unk_28 = 2;
            }
            else
            {
                PAUSE_SCREEN_DATA.unk_28 = 0;
                unk_77840(4);
            }
            break;

        case 11:
            if (EasySleepMenuInit() != 0)
            {
                PAUSE_SCREEN_DATA.unk_28 = 5;
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;

        case 12:
            if (EasySleepMenuQuit() != 0)
            {
                PAUSE_SCREEN_DATA.unk_28 = 0;
                PAUSE_SCREEN_DATA.pauseDebugEditingValue = 0;
                PAUSE_SCREEN_DATA.timer = 0;
            }
            break;
    }

    return close;
}
