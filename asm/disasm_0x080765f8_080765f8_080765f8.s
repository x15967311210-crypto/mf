    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start PauseScreenHandler
PauseScreenHandler: @ 0x080765F8
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	ldr r0, _0807661C @ =gNextOamSlot
	movs r1, #0
	strb r1, [r0]
	movs r7, #0
	ldr r0, _08076620 @ =0x03000B85
	ldrb r1, [r0]
	adds r5, r0, #0
	cmp r1, #4
	bls _08076610
	b _08076872
_08076610:
	lsls r0, r1, #2
	ldr r1, _08076624 @ =_08076628
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807661C: .4byte gNextOamSlot
_08076620: .4byte 0x03000B85
_08076624: .4byte _08076628
_08076628: @ jump table
	.4byte _0807663C @ case 0
	.4byte _08076644 @ case 1
	.4byte _08076720 @ case 2
	.4byte _080767A0 @ case 3
	.4byte _08076834 @ case 4
_0807663C:
	bl PauseScreenInit
	strb r0, [r5]
	b _08076872
_08076644:
	ldr r0, _08076678 @ =gNonGameplayRam
	ldrb r3, [r0]
	cmp r3, #0
	beq _080766E0
	ldr r0, _0807667C @ =gPauseScreenFlag
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	bne _08076688
	ldr r3, _08076680 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r3]
	lsls r0, r0, #8
	ldr r2, _08076684 @ =gWrittenToBldalpha_Eva
	ldrh r4, [r2]
	orrs r0, r4
	movs r1, #0xa1
	lsls r1, r1, #3
	adds r6, r3, #0
	cmp r0, r1
	beq _080766C8
	cmp r4, #8
	beq _080766B2
	adds r0, r4, #1
	b _080766A4
	.align 2, 0
_08076678: .4byte gNonGameplayRam
_0807667C: .4byte gPauseScreenFlag
_08076680: .4byte gWrittenToBldalpha_Evb
_08076684: .4byte gWrittenToBldalpha_Eva
_08076688:
	ldr r3, _080766C0 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r3]
	lsls r0, r0, #8
	ldr r2, _080766C4 @ =gWrittenToBldalpha_Eva
	ldrh r4, [r2]
	orrs r0, r4
	movs r1, #0xa1
	lsls r1, r1, #3
	adds r6, r3, #0
	cmp r0, r1
	beq _080766C8
	cmp r4, #8
	beq _080766B2
	adds r0, r4, #2
_080766A4:
	strh r0, [r2]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #8
	bls _080766B2
	movs r0, #8
	strh r0, [r2]
_080766B2:
	ldrh r0, [r6]
	cmp r0, #5
	bne _080766BA
	b _080767FA
_080766BA:
	adds r0, #1
	strh r0, [r6]
	b _080767FA
	.align 2, 0
_080766C0: .4byte gWrittenToBldalpha_Evb
_080766C4: .4byte gWrittenToBldalpha_Eva
_080766C8:
	ldrb r0, [r5]
	adds r0, #1
	strb r0, [r5]
	ldr r1, _080766D8 @ =0x04000050
	ldr r3, _080766DC @ =0x00003F44
	adds r0, r3, #0
	strh r0, [r1]
	b _080767FA
	.align 2, 0
_080766D8: .4byte 0x04000050
_080766DC: .4byte 0x00003F44
_080766E0:
	ldr r2, _080766F4 @ =gWrittenToBldy
	ldrh r0, [r2]
	adds r1, r0, #0
	cmp r1, #0
	beq _080766FC
	cmp r1, #4
	bls _080766F8
	subs r0, #4
	strh r0, [r2]
	b _08076872
	.align 2, 0
_080766F4: .4byte gWrittenToBldy
_080766F8:
	strh r3, [r2]
	b _08076872
_080766FC:
	ldrb r0, [r5]
	adds r0, #1
	strb r0, [r5]
	ldr r1, _08076718 @ =0x04000050
	movs r2, #0xfc
	lsls r2, r2, #6
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	ldr r3, _0807671C @ =0x0000040C
	adds r0, r3, #0
	strh r0, [r1]
	b _08076872
	.align 2, 0
_08076718: .4byte 0x04000050
_0807671C: .4byte 0x0000040C
_08076720:
	bl PauseScreenCallCurrentHandler
	cmp r0, #0
	beq _08076776
	ldr r0, _0807674C @ =gNonGameplayRam
	ldrb r1, [r0]
	cmp r1, #0
	beq _08076764
	ldr r1, _08076750 @ =0x04000050
	ldr r2, _08076754 @ =0x00003F7F
	adds r0, r2, #0
	strh r0, [r1]
	ldr r3, _08076758 @ =gWrittenToBldalpha_Eva
	ldr r0, _0807675C @ =0x04000052
	ldrh r2, [r0]
	ldr r1, _08076760 @ =gWrittenToBldalpha_Evb
	lsrs r0, r2, #8
	strh r0, [r1]
	movs r0, #0xff
	ands r0, r2
	strh r0, [r3]
	b _0807676E
	.align 2, 0
_0807674C: .4byte gNonGameplayRam
_08076750: .4byte 0x04000050
_08076754: .4byte 0x00003F7F
_08076758: .4byte gWrittenToBldalpha_Eva
_0807675C: .4byte 0x04000052
_08076760: .4byte gWrittenToBldalpha_Evb
_08076764:
	ldr r0, _08076790 @ =gWrittenToBldy
	strh r1, [r0]
	ldr r1, _08076794 @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
_0807676E:
	ldr r1, _08076798 @ =0x03000B85
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
_08076776:
	ldr r0, _0807679C @ =gNonGameplayRam
	movs r3, #0x99
	lsls r3, r3, #2
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _08076872
	bl unk_7c440
	bl unk_7cfb0
	b _08076872
	.align 2, 0
_08076790: .4byte gWrittenToBldy
_08076794: .4byte 0x04000050
_08076798: .4byte 0x03000B85
_0807679C: .4byte gNonGameplayRam
_080767A0:
	ldr r0, _080767D4 @ =gNonGameplayRam
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807680C
	ldr r0, _080767D8 @ =gPauseScreenFlag
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	movs r4, #2
	cmp r0, #4
	bne _080767B8
	movs r4, #1
_080767B8:
	ldr r2, _080767DC @ =gWrittenToBldalpha_Evb
	ldr r3, _080767E0 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r2]
	ldrh r0, [r3]
	orrs r0, r1
	adds r6, r2, #0
	adds r2, r3, #0
	cmp r0, #0
	beq _080767F4
	ldrh r0, [r2]
	cmp r0, r4
	blt _080767E4
	subs r0, r0, r4
	b _080767E6
	.align 2, 0
_080767D4: .4byte gNonGameplayRam
_080767D8: .4byte gPauseScreenFlag
_080767DC: .4byte gWrittenToBldalpha_Evb
_080767E0: .4byte gWrittenToBldalpha_Eva
_080767E4:
	movs r0, #0
_080767E6:
	strh r0, [r2]
	ldrh r0, [r6]
	cmp r0, #0
	beq _080767FA
	subs r0, #1
	strh r0, [r6]
	b _080767FA
_080767F4:
	ldrb r0, [r5]
	adds r0, #1
	strb r0, [r5]
_080767FA:
	ldr r0, _08076808 @ =0x04000052
	ldrh r1, [r6]
	lsls r1, r1, #8
	ldrh r2, [r2]
	orrs r1, r2
	strh r1, [r0]
	b _08076872
	.align 2, 0
_08076808: .4byte 0x04000052
_0807680C:
	ldr r1, _08076828 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _0807682C
	adds r0, #4
	strh r0, [r1]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x10
	bls _08076872
	movs r0, #0x10
	strh r0, [r1]
	b _08076872
	.align 2, 0
_08076828: .4byte gWrittenToBldy
_0807682C:
	ldrb r0, [r5]
	adds r0, #1
	strb r0, [r5]
	b _08076872
_08076834:
	ldr r1, _08076888 @ =gPauseScreenFlag
	movs r0, #0
	ldrsb r0, [r1, r0]
	cmp r0, #3
	bne _0807686A
	ldr r0, _0807688C @ =gEventCounter
	ldrb r0, [r0]
	cmp r0, #0x61
	bne _0807686A
	ldr r0, _08076890 @ =gPreviousCutscene
	ldrb r0, [r0]
	cmp r0, #7
	beq _0807686A
	movs r0, #5
	strb r0, [r1]
	ldr r1, _08076894 @ =gCurrentCutscene
	movs r0, #7
	strb r0, [r1]
	ldr r1, _08076898 @ =0x0201C000
	ldr r2, _0807689C @ =0x06010000
	movs r3, #0x80
	lsls r3, r3, #8
	movs r0, #0x20
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
_0807686A:
	movs r7, #1
	ldr r1, _080768A0 @ =0x03000B85
	movs r0, #0
	strb r0, [r1]
_08076872:
	bl MapScreenUpdateArrowsAndBlinkingSquare
	bl PauseScreenProcessOam
	bl ResetFreeOam
	adds r0, r7, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08076888: .4byte gPauseScreenFlag
_0807688C: .4byte gEventCounter
_08076890: .4byte gPreviousCutscene
_08076894: .4byte gCurrentCutscene
_08076898: .4byte 0x0201C000
_0807689C: .4byte 0x06010000
_080768A0: .4byte 0x03000B85

	thumb_func_start PauseScreenVBLank
PauseScreenVBLank: @ 0x080768A4
	ldr r1, _08076908 @ =0x040000D4
	ldr r0, _0807690C @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08076910 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	subs r1, #0xd4
	ldr r0, _08076914 @ =gNonGameplayRam
	movs r2, #0x9a
	lsls r2, r2, #2
	adds r0, r0, r2
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #0x54
	ldr r0, _08076918 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #8
	ldr r0, _0807691C @ =gWrittenToMosaic_L
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r2, _08076920 @ =0x04000010
	ldr r1, _08076924 @ =gBackgroundPositions
	ldrh r0, [r1]
	strh r0, [r2]
	adds r2, #2
	ldrh r0, [r1, #2]
	strh r0, [r2]
	adds r2, #2
	ldrh r0, [r1, #4]
	strh r0, [r2]
	adds r2, #2
	ldrh r0, [r1, #6]
	strh r0, [r2]
	adds r2, #2
	ldrh r0, [r1, #8]
	strh r0, [r2]
	adds r2, #2
	ldrh r0, [r1, #0xa]
	strh r0, [r2]
	adds r2, #2
	ldrh r0, [r1, #0xc]
	strh r0, [r2]
	adds r2, #2
	ldrh r0, [r1, #0xe]
	strh r0, [r2]
	bx lr
	.align 2, 0
_08076908: .4byte 0x040000D4
_0807690C: .4byte gOamData
_08076910: .4byte 0x84000100
_08076914: .4byte gNonGameplayRam
_08076918: .4byte gWrittenToBldy
_0807691C: .4byte gWrittenToMosaic_L
_08076920: .4byte 0x04000010
_08076924: .4byte gBackgroundPositions
