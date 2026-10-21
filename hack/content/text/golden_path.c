/*
 * HACK-008b text pipeline example.
 *
 * This is a content source, not a directly compiled translation unit:
 * tools/preproc/preproc rewrites the INCTEXT call into a u16 initializer using
 * the repository charmap.txt, exactly like the ROM build does for every C file.
 *
 * The dialogue is intentionally letters, spaces and {NEW_LINE} only.  Digits
 * and punctuation are not in the proven charmap, and an unknown character is a
 * preproc error rather than a guessed glyph.
 *
 * Not yet referenced by a room, event or message table; HACK-008d wires the
 * first real dialogue block into the game.  The text ID stays unallocated in
 * hack/content/ids.yaml for the same reason.
 */

#include "constants/text.h"

const u16 sGoldenPathText[] = INCTEXT(
    "ENTRY LEDGE{NEW_LINE}"
    "THE SIGNAL IS WEAK"
);
