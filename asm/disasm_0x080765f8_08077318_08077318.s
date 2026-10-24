    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start PauseScreenMoveBackgroundToXPosition
PauseScreenMoveBackgroundToXPosition: @ 0x08077318
	push {r4, r5, r6, r7, lr}
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	lsls r1, r1, #0x10
	lsrs r4, r1, #0x10
	movs r7, #0
	ldr r1, _08077344 @ =gBackgroundPositions
	lsls r0, r5, #2
	adds r3, r0, r1
	ldrh r2, [r3]
	movs r6, #1
	cmp r2, r4
	bls _08077334
	subs r6, #2
_08077334:
	ldr r0, _08077348 @ =gNonGameplayRam
	ldrb r0, [r0, #6]
	adds r0, #4
	cmp r0, #0x1f
	bgt _0807734C
	muls r0, r6, r0
	b _0807734E
	.align 2, 0
_08077344: .4byte gBackgroundPositions
_08077348: .4byte gNonGameplayRam
_0807734C:
	lsls r0, r6, #5
_0807734E:
	adds r0, r2, r0
	strh r0, [r3]
	cmp r6, #0
	ble _08077364
	lsls r0, r5, #2
	adds r1, r0, r1
	ldrh r0, [r1]
	cmp r0, r4
	blo _0807737A
	strh r4, [r1]
	b _08077378
_08077364:
	lsls r0, r5, #2
	adds r1, r0, r1
	movs r2, #0
	ldrsh r0, [r1, r2]
	cmp r0, r4
	bgt _0807737A
	subs r0, r4, r0
	ldrh r2, [r1]
	adds r0, r0, r2
	strh r0, [r1]
_08077378:
	movs r7, #1
_0807737A:
	adds r0, r7, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
