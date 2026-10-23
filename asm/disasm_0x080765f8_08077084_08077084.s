    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start GetMinimapData
GetMinimapData: @ 0x08077084
	push {lr}
	adds r2, r1, #0
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _0807709A
	ldr r0, _080770AC @ =gEventCounter
	ldrb r0, [r0]
	cmp r0, #0x5d
	bls _0807709A
	movs r1, #9
_0807709A:
	ldr r0, _080770B0 @ =0x0879BE5C (sUnk_79be5c)
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r0, [r1]
	adds r1, r2, #0
	bl CallLZ77UncompVram
	pop {r0}
	bx r0
	.align 2, 0
_080770AC: .4byte gEventCounter
_080770B0: .4byte sExploredMinimapBitFlags+0x80
