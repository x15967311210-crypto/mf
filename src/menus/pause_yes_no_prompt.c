#include "globals.h"

#include "macros.h"
#include "new_file_intro.h"
#include "text.h"

#include "constants/text.h"

/* Text-stream control codes and layout constants the shared headers do not
   name yet (see include/constants/text.h). */
#define CHAR_SPACE          0x40
#define TEXT_LINE_WIDTH     0xE0
#define KEY_ADVANCE_TEXT    (KEY_A | KEY_B | KEY_DOWN)

/* music_wrappers.h declares this with a u8 first parameter, but the baseline
   passes the whole u16 character code without truncating it. */
void PlayCharacterAppearingSound(u16 character, u8 speaker);

/**
 * @brief 7a0fc | 1e0 | Processes the current yes/no prompt text
 *
 * Walks the message text for prompt `arg0` (sMessageTextPointers entry
 * 43 + arg0) one character at a time, handling newline, width and indent
 * control codes, the per-character reveal delay (8 frames, skipped while
 * KEY_ADVANCE_TEXT is held), and drawing each glyph into VRAM at
 * 0x06007000 (+0x800 for the second line).  Returns TRUE once the text
 * terminator has been reached.
 *
 * Ported from the decomp.me scratch 9kD14 by biosp4rk (100% match).
 */
u8 unk_7a0fc(u8 arg0)
{
    u8 ended;
    u8 secondLine;
    u8* dst;
    u16* pText;
    u16 charControl;
    s32 indent;
    s32 pixel;

    if (!(PAUSE_SCREEN_DATA.typeFlags & 8))
        return FALSE;

    ended = FALSE;
    secondLine = FALSE;

    while (TRUE)
    {
        pText = sMessageTextPointers[gLanguage][43 + arg0];
        dst = VRAM_BASE + 0x7000;
        pText += PAUSE_SCREEN_DATA.unk_21;

        if (*pText == CHAR_NEW_LINE)
        {
            PAUSE_SCREEN_DATA.unk_20 = 0;
            PAUSE_SCREEN_DATA.navConvTextIndent = TEXT_LINE_WIDTH;
            PAUSE_SCREEN_DATA.unk_21++;
            continue;
        }

        charControl = *pText & CHAR_MASK;

        if (charControl == CHAR_WIDTH_MASK)
        {
            PAUSE_SCREEN_DATA.unk_20 = 0;
            PAUSE_SCREEN_DATA.navConvTextIndent += LOW_BYTE(*pText);
            PAUSE_SCREEN_DATA.unk_21++;
            continue;
        }

        if (charControl == CHAR_INDENT_MASK)
        {
            PAUSE_SCREEN_DATA.unk_20 = 0;

            if (PAUSE_SCREEN_DATA.navConvTextIndent >= TEXT_LINE_WIDTH)
                PAUSE_SCREEN_DATA.navConvTextIndent = TEXT_LINE_WIDTH;
            else
                PAUSE_SCREEN_DATA.navConvTextIndent = 0;

            PAUSE_SCREEN_DATA.navConvTextIndent += LOW_BYTE(*pText);

            if (*pText == (CHAR_INDENT_MASK | 0xA0))
                PAUSE_SCREEN_DATA.navConvTextIndent -= 16;

            PAUSE_SCREEN_DATA.unk_21++;
            continue;
        }

        if (!secondLine)
        {
            if (*pText != CHAR_SPACE && PAUSE_SCREEN_DATA.navConvTextIndent < TEXT_LINE_WIDTH)
            {
                if (PAUSE_SCREEN_DATA.unk_1A && !(gButtonInput & KEY_ADVANCE_TEXT))
                    PAUSE_SCREEN_DATA.unk_1A = FALSE;

                PAUSE_SCREEN_DATA.unk_20++;
                if ((!(gButtonInput & KEY_ADVANCE_TEXT) || PAUSE_SCREEN_DATA.unk_1A) &&
                    PAUSE_SCREEN_DATA.unk_20 < 8)
                {
                    break;
                }
            }

            PAUSE_SCREEN_DATA.unk_20 = 0;
        }

        PAUSE_SCREEN_DATA.navConvCharacterWidth = TextGetCharacterWidth(*pText);

        if (PAUSE_SCREEN_DATA.navConvTextIndent + PAUSE_SCREEN_DATA.navConvCharacterWidth > TEXT_LINE_WIDTH &&
            PAUSE_SCREEN_DATA.navConvTextIndent < TEXT_LINE_WIDTH)
        {
            PAUSE_SCREEN_DATA.navConvTextIndent = TEXT_LINE_WIDTH;
        }

        // This code accomplishes nothing
        if (PAUSE_SCREEN_DATA.navConvTextIndent == 0)
            PAUSE_SCREEN_DATA.navConvTextIndent = 0;
        else if (PAUSE_SCREEN_DATA.navConvTextIndent == TEXT_LINE_WIDTH)
            PAUSE_SCREEN_DATA.navConvTextIndent = TEXT_LINE_WIDTH;

        if (*pText != CHAR_SPACE)
        {
            PlayCharacterAppearingSound(*pText, 1);
            indent = PAUSE_SCREEN_DATA.navConvTextIndent;

            if (PAUSE_SCREEN_DATA.navConvTextIndent >= TEXT_LINE_WIDTH)
            {
                secondLine = TRUE;
                dst += 0x800;
                indent -= TEXT_LINE_WIDTH;
            }

            dst += DIV_SHIFT(indent, TILE_DIM) * TILE_SIZE;
            // TODO: Variable isn't used, try getting match without this
            pixel = MOD_AND(PAUSE_SCREEN_DATA.navConvTextIndent, TILE_DIM);
            TextDrawCharacter(*pText, (u32*)dst, PAUSE_SCREEN_DATA.navConvCharacterWidth,
                MOD_AND(PAUSE_SCREEN_DATA.navConvTextIndent, TILE_DIM), 0);
        }

        PAUSE_SCREEN_DATA.navConvTextIndent += PAUSE_SCREEN_DATA.navConvCharacterWidth;
        PAUSE_SCREEN_DATA.unk_21++;

        if (pText[1] == CHAR_TERMINATOR)
            ended = TRUE;

        if (!secondLine || ended)
            break;
    }

    return ended;
}
