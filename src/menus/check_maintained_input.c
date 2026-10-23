#include "globals.h"

#include "gba/keys.h"
#include "macros.h"

/* 0x03005400: pause-screen maintained-input timing state.  Only the two bytes
   the routine touches are modelled; the address itself is a linker symbol
   (linker.ld), so this file never spells out the RAM address. */
struct MaintainedInputState {
    u8 delay;
    u8 set;
};

extern struct MaintainedInputState gUnk_3005400;

/* Defined in src/data/menus/pause_debug.c. */
extern const u8 sMaintainedInputDelays[7];

/* agbcc's libc headers are not on the -nostdinc include path, so the routine
   is declared here.  agbcc's size_t is `unsigned long`; spelling the length
   any narrower trips -Werror on the built-in declaration. */
void *memcpy(void *dest, const void *src, unsigned long size);

/**
 * @brief 78a74 | 7c | Maintains the held-direction repeat delays
 *
 * Ported from the decomp.me scratch YTFLV by biosp4rk (100% match).
 * A held direction counts up until it reaches the delay for the current
 * repeat step, then it is forwarded to gChangedInput and the step advances.
 */
void CheckForMaintainedInput(void)
{
    u8 inputDelays[ARRAY_SIZE(sMaintainedInputDelays)];

    memcpy(inputDelays, sMaintainedInputDelays, sizeof(sMaintainedInputDelays));

    if (gButtonInput & KEY_ALL_DIRECTIONS)
    {
        gUnk_3005400.delay++;
    }
    else
    {
        gUnk_3005400.delay = 0;
        gUnk_3005400.set = 0;
    }

    if (gUnk_3005400.delay >= inputDelays[gUnk_3005400.set])
    {
        gChangedInput |= gButtonInput & KEY_ALL_DIRECTIONS;
        gUnk_3005400.delay = 0;

        if (gUnk_3005400.set < ARRAY_SIZE(sMaintainedInputDelays) - 1)
            gUnk_3005400.set++;
    }
}
