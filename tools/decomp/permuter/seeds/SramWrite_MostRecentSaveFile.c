// TECH-007 reference seed for decomp-permuter: SramWrite_MostRecentSaveFile.
//
// This is the hand-tightened "435" shape for the TECH-007 pilot: the zero and
// 0xFFFF values are written as inline literals (no `zero`/`magic` locals), the
// save-file counter is read through the `gMostRecentSaveFile` symbol, and the
// two loops keep their explicit `u16*` / `u8*` pointers.  It is a permuter
// input, not a proposed port: do not copy it into src/ without a scratch build
// and compare_text.py pass (docs/howto/decomp-permuter.md).
//
// It compiles through tools/decomp/permuter/run.sh with the normal ROM flags:
//   cpp -nostdinc -Iinclude -DREGION_US
//     | tools/agbcc/bin/agbcc -O1 -mthumb-interwork -fhex-asm

#include "globals.h"

#include "gba.h"
#include "sram_misc.h"

#include "data/sram_pointers.h"
#include "structs/save_file.h"

#define gSramHeader ((u8*)EWRAM_BASE + 0x3F000)
#define sMostRecentFileBlob ((const u8*)sUnk_582280 + 8)

void SramWrite_MostRecentSaveFile(void)
{
    u8* header = gSramHeader;
    u16* ptr = (u16*)header;
    const u8* src;
    u8* dst;
    u16 checksum;
    s32 i;

    header[0] = 0x1E;
    header[1]++;
    *(u16*)(header + 2) = 0;
    *(u16*)(header + 4) = 0xFFFF;
    header[0x16] = gMostRecentSaveFile;

    src = sMostRecentFileBlob;
    dst = header + 6;

    for (i = 0xF; i >= 0; i--)
    {
        *dst = *src;
        dst[0x11] = src[0x10];
        src++;
        dst++;
    }

    checksum = 0;

    for (i = 7; i >= 0; i--)
    {
        checksum += *ptr++;
        checksum += *ptr++;
        checksum += *ptr++;
        checksum += *ptr++;
    }

    *(u16*)(header + 2) = checksum;
    *(u16*)(header + 4) = 0xFFFF - checksum;

    unk_dd4();
}
