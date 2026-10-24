#include "globals.h"

#include "gba.h"

#include "data/menus/pause_debug.h"

/* Status-screen section info table {top, bottom, left, right, section} at
   0x0858217C.  The bytes are one byte into sBlob_58217b_58225c, the blob that
   follows sDebugSectionInfo in src/data/menus/pause_debug.c; linker.ld names
   this view relative to that data, so the port never spells out a ROM
   address. */
extern const u8 sStatusScreenSectionInfo[][5];

/**
 * @brief 7e754 | e0 | Draws a numeric status screen value into the BG tilemap
 *
 * @param section Status screen section
 * @param value Value to draw
 * @param palette Palette row
 * @param onEdge Whether the section is right-aligned on the screen edge
 *
 * Ported from the decomp.me scratch FVMeb by eilene-ftf (100% match).
 */
void StatusScreenDrawNumber(u8 section, u16 value, u8 palette, u8 onEdge)
{
    s32 ctr;
    s32 divisor;
    s32 n_digits;
    u8 seen;
    u16* mem_loc;
    u32 position;
    s32 tile;

    mem_loc = VRAM_BASE + 0xC800;
    position = sStatusScreenSectionInfo[section][0] * HALF_BLOCK_SIZE + sStatusScreenSectionInfo[section][2];
    mem_loc = &mem_loc[position];
    n_digits = sStatusScreenSectionInfo[section][3] - sStatusScreenSectionInfo[section][2];
    divisor = sPauseDebugNumbersIncrementValues[n_digits];
    n_digits++;
    seen = FALSE;
    ctr = 0;

    while (divisor > 0)
    {
        tile = value / divisor % 10;
        if (tile == 0)
        {
            if (!seen)
            {
                tile = 140;
                if (onEdge)
                    tile = 0;
            }
            else
                tile = 128;
        }
        else
        {
            seen = TRUE;
            tile += 128;
        }

        if (tile != 0)
            mem_loc[ctr] = (palette * 4096) | tile;
        else
            ctr--;

        divisor /= 10;
        ctr++;
    }

    while (n_digits != ctr)
    {
        mem_loc[ctr] = (palette * 4096) | 140;
        ctr++;
    }
}
