/* m2c context for the SramWrite_MostRecentSaveFile pilot (TECH-009).
 *
 * This is deliberately small: it only names the types, globals and callee the
 * one function touches.  It is NOT a project-wide context and must not grow
 * into one -- a full context is a separate task.
 *
 *   tools/decomp/m2c/run.sh --asm asm/disasm_0x0807e678_0807eea4_08080068.s \
 *       --function SramWrite_MostRecentSaveFile \
 *       --context tools/decomp/m2c/context/sram_write_recent.c
 *
 * run.sh preprocesses this file (`cpp -nostdinc -I include`) before handing it
 * to `m2c --context`, because m2c requires an already-preprocessed file.
 */

#include "types.h"

/* m2c emits (s64)/(u64) casts for widening 64-bit arithmetic.  include/types.h
 * stops at 32 bits, so the context supplies the two 64-bit typedefs. */
typedef long long s64;
typedef unsigned long long u64;

/* Save header written to the EWRAM save buffer at 0x0203F000.
 *
 * Field offsets come from the store instructions in this one function:
 *   strb [r5]       0x00  magic (0x1e)
 *   strb [r5, #1]   0x01  counter, incremented every write
 *   strh [r5, #2]   0x02  checksum over the body
 *   strh [r5, #4]   0x04  ~checksum
 *   byte copy A     0x06..0x15
 *   strb [r5, #16]  0x16  most recent save file index
 *   byte copy B     0x17..0x26  (the second store is [r5+6+0x11])
 * Everything else in the real header is padding for this pilot. */
struct SramSave {
    u8 unk_00;               /* 0x00 magic, written as 0x1e */
    u8 counter;              /* 0x01 */
    u16 checksum;            /* 0x02 */
    u16 checksumComplement;  /* 0x04 */
    u8 copy0[0x10];          /* 0x06 */
    u8 mostRecentFile;       /* 0x16 */
    u8 copy1[0x10];          /* 0x17 */
};

/* Placeholder for the raw EWRAM address 0x0203F000.  The project has no C
 * symbol for that buffer yet (src/sram/* works on the SRAM copies), so
 * symbols/sram.syms rewrites the literal to this name. */
extern struct SramSave gSramMostRecent;

/* src: IWRAM byte at 0x03000B8D, declared in include/structs/save_file.h. */
extern u8 gMostRecentSaveFile;

/* src: ROM tables at 0x08582274/0x08582280 (include/data/sram_pointers.h).
 * 0x08582288 is the blob right after sUnk_582280; extract.py maps the
 * `sUnk_582280+0x8` literal to sBlob_582288 so m2c sees a plain symbol. */
extern const void* const sUnk_582280[2];
extern const u8 sBlob_582288[];

/* src: SRAM helper in include/sram_misc.h (the function ends with `bl unk_dd4`). */
void unk_dd4(void);
