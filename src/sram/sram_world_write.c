#include "globals.h"

#include "dma.h"
#include "gba.h"

#include "data/sram_pointers.h"
#include "structs/save_file.h"
#include "structs/block.h"
#include "structs/bg_clip.h"

#define gUnk_2036000 ((u8*)EWRAM_BASE + 0x36000)
#define gUnk_2037200 ((u8*)EWRAM_BASE + 0x37200)
#define gUnk_2037C00 ((u8*)EWRAM_BASE + 0x37C00)

void SramWrite_WorldData(void)
{
    void* dst = (void*)sUnk_582274[gMostRecentSaveFile];
    u32 ofs;
    u32 size;
    u32 idx;
    s32 i;
    s32 j;

    DmaTransfer(3, gUnk_2037C00, dst, 0x380, 0x10);
    ofs = 0x380;

    for (i = 0; i < 8; i++)
    {
        size = gNumberOfNeverReformBlocks[i] * 3;

        if ((size & 3) != 0)
        {
            size &= 0xFFFC;
            size += 4;
        }

        if (size != 0)
        {
            idx = (i != 0 ? i + 1 : i);
            DmaTransfer(3, gUnk_2036000 + (idx << 9), dst + ofs, size, 0x10);
            ofs += size;
        }
    }

    ofs = 0xC80;

    for (i = 0; i < 8; )
    {
        size = gNumberOfCollectedTanks[i] * 4;
        j = i + 1;

        if (size != 0)
        {
            idx = i;
            // Keep idx in its own register: without this barrier agbcc CSEs
            // the copy back to i and compares r5, while the baseline tests r1.
            asm("" : "+r" (idx));
            if (idx != 0)
                idx = j;
            DmaTransfer(3, gUnk_2037200 + (idx << 8), dst + ofs, size, 0x10);
            ofs += size;
        }
        i = j;
    }
}
