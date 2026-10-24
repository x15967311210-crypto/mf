#include "globals.h"

#include "data/event_data.h"
#include "text.h"

/* Navigation-conversation target and OAM setters, still assembly in this tree
   (asm/disasm_0x08079afc_0807a3a4_0807b8d4.s). */
void NavigationConversationUpdateTarget(u8 target);
void NavigationConversationSetupOam(void);

/**
 * @brief 7a2dc | c8 | Loads the current navigation conversation for the pause screen
 *
 * Walks sEventLocationAndNavigationInfo backwards from gEventCounter to the
 * newest event that has a navConversation, stores its conversation number, and
 * flags a repeat when it is the same as gPreviousNavigationConversation.  Then
 * it clears the text graphics, re-targets the navigation map and rebuilds the
 * pop-up OAM before resetting the conversation state bytes.
 *
 * Ported from the decomp.me scratch B5vvr by biosp4rk (100% match).
 */
void NavigationConversationGetCurrentConversation(void)
{
    s32 event;
    u8 navConversation;

    for (event = gEventCounter; event > 0; event--)
    {
        if (sEventLocationAndNavigationInfo[event].navConversation != 0)
            break;
    }

    navConversation = sEventLocationAndNavigationInfo[event].navConversation;
    PAUSE_SCREEN_DATA.conversationNumber = navConversation;

    if (navConversation == gPreviousNavigationConversation)
        PAUSE_SCREEN_DATA.conversationOnRepeat = TRUE;
    else
        PAUSE_SCREEN_DATA.conversationOnRepeat = FALSE;

    TextClearGraphics(0);
    NavigationConversationUpdateTarget(1);
    NavigationConversationSetupOam();

    PAUSE_SCREEN_DATA.unk_238 = 0;
    PAUSE_SCREEN_DATA.unk_239 = 0;
    PAUSE_SCREEN_DATA.unk_23C = 0;
    PAUSE_SCREEN_DATA.unk_23D = 0;
    PAUSE_SCREEN_DATA.unk_250 = 0;
    PAUSE_SCREEN_DATA.unk_251 = 0;
    PAUSE_SCREEN_DATA.unk_252 = 0;
}
