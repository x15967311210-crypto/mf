    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start StatusScreenHandler
StatusScreenHandler: @ 0x0807E678
	push {lr}
	ldr r0, _0807E6A0 @ =gChangedInput
	ldrh r1, [r0]
	ldr r0, _0807E6A4 @ =0x00000302
	ands r0, r1
	cmp r0, #0
	beq _0807E69A
	ldr r3, _0807E6A8 @ =gNonGameplayRam
	ldrb r2, [r3, #7]
	cmp r2, #0
	bne _0807E69A
	adds r1, r3, #0
	adds r1, #0x28
	movs r0, #7
	strb r0, [r1]
	strb r2, [r3, #6]
	strb r2, [r3, #7]
_0807E69A:
	pop {r0}
	bx r0
	.align 2, 0
_0807E6A0: .4byte gChangedInput
_0807E6A4: .4byte 0x00000302
_0807E6A8: .4byte gNonGameplayRam

	thumb_func_start StatusScreenDrawEverything
StatusScreenDrawEverything: @ 0x0807E6AC
	push {r4, lr}
	ldr r4, _0807E714 @ =gEquipment
	ldrb r1, [r4, #0xa]
	movs r0, #0
	bl StatusScreenDrawBeamOrSuit
	ldrb r1, [r4, #0xb]
	movs r0, #1
	bl StatusScreenDrawMissileOrBomb
	ldrb r1, [r4, #0xc]
	movs r0, #3
	bl StatusScreenDrawBeamOrSuit
	ldrb r1, [r4, #0xb]
	movs r0, #2
	bl StatusScreenDrawMissileOrBomb
	ldrb r1, [r4, #0xc]
	movs r0, #4
	bl StatusScreenDrawMisc
	ldrh r1, [r4]
	movs r0, #5
	movs r2, #6
	movs r3, #0
	bl StatusScreenDrawNumber
	ldrh r1, [r4, #2]
	movs r0, #6
	movs r2, #3
	movs r3, #1
	bl StatusScreenDrawNumber
	ldrb r1, [r4, #0xb]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _0807E718
	ldrh r1, [r4, #4]
	movs r0, #7
	movs r2, #6
	movs r3, #0
	bl StatusScreenDrawNumber
	ldrh r1, [r4, #6]
	movs r0, #8
	movs r2, #3
	movs r3, #1
	bl StatusScreenDrawNumber
	b _0807E71E
	.align 2, 0
_0807E714: .4byte gEquipment
_0807E718:
	movs r0, #1
	bl StatusScreenRemoveAmmoHeader
_0807E71E:
	ldr r4, _0807E744 @ =gEquipment
	ldrb r1, [r4, #0xb]
	movs r0, #0x30
	ands r0, r1
	cmp r0, #0x30
	bne _0807E748
	ldrb r1, [r4, #8]
	movs r0, #9
	movs r2, #6
	movs r3, #0
	bl StatusScreenDrawNumber
	ldrb r1, [r4, #9]
	movs r0, #0xa
	movs r2, #3
	movs r3, #1
	bl StatusScreenDrawNumber
	b _0807E74E
	.align 2, 0
_0807E744: .4byte gEquipment
_0807E748:
	movs r0, #2
	bl StatusScreenRemoveAmmoHeader
_0807E74E:
	pop {r4}
	pop {r0}
	bx r0
