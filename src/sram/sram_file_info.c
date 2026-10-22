#include "sram/sram.h"

#include "gba.h"
#include "macros.h"

#include "data/sram_pointers.h"

/* File-info table in IWRAM: one 0x14-byte slot per save file. */
#define SRAM_FILE_INFO ((u8*)IWRAM_BASE + 0xB94)

/* Copy the save-file metadata into each IWRAM slot, clearing empty slots. */
void Sram_WriteFileInfo(void)
{
    s32 i = 0;
    u16 zero = 0;
    volatile u8* dst = SRAM_FILE_INFO;
    u8* src;

    for (; i < 3; i++)
    {
        u32 ofs = i * 4;

        if (dst[0] == 1)
        {
            /* Raw save-slot pointer table entry (one pointer per file). */
            src = (u8*)*(const void* const*)((const u8*)sSaveDataEwramPointers + ofs);
            dst[2] = src[0x1D];
            dst[3] = src[0x21];
            *(u16*)(dst + 4) = *(u16*)(src + 0xC4);
            *(u16*)(dst + 6) = *(u16*)(src + 0xC6);
            *(u16*)(dst + 8) = *(u16*)(src + 0xC8);
            *(u16*)(dst + 0xA) = *(u16*)(src + 0xCA);
            dst[0xC] = src[0xCF];
            dst[0xD] = src[0xE4];
            dst[0xE] = src[0xE5];
            dst[0xF] = src[0x1C];
            dst[0x10] = src[0x18];
            dst[0x11] = src[0x19];
        }

        if (dst[0] == 0 || dst[0xF] == 0)
        {
            dst[0] = zero;
            dst[2] = zero;
            dst[3] = zero;
            *(u16*)(dst + 4) = zero;
            *(u16*)(dst + 6) = zero;
            *(u16*)(dst + 8) = zero;
            *(u16*)(dst + 0xA) = zero;
            dst[0xC] = zero;
            dst[0xD] = zero;
            dst[0xE] = zero;
        }

        dst += 0x14;
    }
}
