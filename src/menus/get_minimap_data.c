#include "globals.h"

#include "syscall_wrappers.h"

#include "constants/event.h"

#include "structs/event.h"

/* Indexes into sUnk_79be5c, the table of LZ77-compressed minimap tile data.
   Only the two entries this function can select are named here. */
enum MinimapDataIndex {
    MINIMAP_MAIN_DECK = 0,
    /* 1-8: sector and debug-area variants */
    MINIMAP_MAIN_DECK_NO_LAB = 9,
};

/* The 11-entry table is the static sUnk_79be5c array defined at the head of
   src/menus/pause_screen_map.c's .data; linker.ld exports this view of it at
   sExploredMinimapBitFlags + 0x80 (0x79BE5C), the same address the original
   literal pool entry spells out. */
extern u8* sUnk_79be5c[11];

/**
 * @brief 77084 | 30 | Decompresses the minimap tile data for an area
 *
 * Ported from the decomp.me scratch jPgTL by biosp4rk (100% match).
 * The Minimap data for the Main Deck changes once the restricted laboratory
 * has been escaped (and thus detached).
 */
void GetMinimapData(u8 index, void* dst)
{
    if (index == MINIMAP_MAIN_DECK && gEventCounter >= EVENT_ESCAPED_RESTRICTED_LABORATORY)
        index = MINIMAP_MAIN_DECK_NO_LAB;

    CallLZ77UncompVram(sUnk_79be5c[index], dst);
}
