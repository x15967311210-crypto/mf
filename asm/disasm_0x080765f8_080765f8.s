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

	thumb_func_start PauseScreenVBLank_Unused
PauseScreenVBLank_Unused: @ 0x08076928
	push {lr}
	ldr r0, _08076968 @ =0x0400001C
	movs r2, #0
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	movs r1, #0x80
	lsls r1, r1, #0x13
	ldr r0, _0807696C @ =gNonGameplayRam
	movs r3, #0x9a
	lsls r3, r3, #2
	adds r0, r0, r3
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r3, _08076970 @ =0x0300000A
	ldrh r1, [r3]
	cmp r1, #0
	beq _08076952
	ldr r0, _08076974 @ =0x0400000E
	strh r1, [r0]
	strh r2, [r3]
_08076952:
	ldr r2, _08076978 @ =0x04000052
	ldr r0, _0807697C @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08076980 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	pop {r0}
	bx r0
	.align 2, 0
_08076968: .4byte 0x0400001C
_0807696C: .4byte gNonGameplayRam
_08076970: .4byte 0x0300000A
_08076974: .4byte 0x0400000E
_08076978: .4byte 0x04000052
_0807697C: .4byte gWrittenToBldalpha_Evb
_08076980: .4byte gWrittenToBldalpha_Eva

	thumb_func_start PauseScreenInitVBlank
PauseScreenInitVBlank: @ 0x08076984
	push {lr}
	bl UpdateAudio
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start PauseScreenInit
PauseScreenInit: @ 0x08076990
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #8
	ldr r0, _08076A50 @ =PauseScreenInitVBlank
	bl CallbackSetVBlank
	movs r0, #1
	mov sb, r0
	ldr r1, _08076A54 @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
	ldr r2, _08076A58 @ =0x04000054
	ldr r1, _08076A5C @ =gWrittenToBldy
	movs r0, #0x10
	strh r0, [r1]
	strh r0, [r2]
	movs r0, #0x80
	lsls r0, r0, #0x13
	movs r5, #0
	strh r5, [r0]
	ldr r4, _08076A60 @ =gNonGameplayRam
	movs r2, #0x9a
	lsls r2, r2, #2
	adds r1, r4, r2
	movs r0, #0
	strh r0, [r1]
	ldr r0, _08076A64 @ =gNextOamSlot
	strb r5, [r0]
	movs r3, #0xa8
	lsls r3, r3, #3
	movs r0, #0x20
	str r0, [sp]
	movs r0, #3
	movs r1, #0
	adds r2, r4, #0
	bl BitFill
	bl ResetFreeOam
	ldr r1, _08076A68 @ =0x040000D4
	ldr r0, _08076A6C @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08076A70 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r6, _08076A74 @ =gPauseScreenFlag
	movs r0, #0
	ldrsb r0, [r6, r0]
	cmp r0, #4
	beq _08076A10
	ldr r1, _08076A78 @ =0x06010000
	ldr r2, _08076A7C @ =0x0201C000
	movs r3, #0x80
	lsls r3, r3, #8
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
_08076A10:
	ldr r0, _08076A80 @ =gCurrentArea
	ldrb r2, [r0]
	ldr r3, _08076A84 @ =0x00000212
	adds r0, r4, r3
	strb r2, [r0]
	ldr r0, _08076A88 @ =0x03000031
	ldrb r1, [r0]
	subs r3, #2
	adds r0, r4, r3
	strb r1, [r0]
	ldr r0, _08076A8C @ =0x03000032
	ldrb r1, [r0]
	adds r3, #1
	adds r0, r4, r3
	strb r1, [r0]
	strb r5, [r4, #2]
	mov r0, sb
	strb r0, [r4]
	movs r0, #0
	ldrsb r0, [r6, r0]
	cmp r0, #3
	bne _08076A94
	lsls r0, r2, #0x18
	cmp r0, #0
	bne _08076AA8
	ldr r0, _08076A90 @ =gCurrentRoom
	ldrb r0, [r0]
	cmp r0, #0
	bne _08076AA8
	movs r0, #2
	strb r0, [r4]
	b _08076AA8
	.align 2, 0
_08076A50: .4byte PauseScreenInitVBlank
_08076A54: .4byte 0x04000050
_08076A58: .4byte 0x04000054
_08076A5C: .4byte gWrittenToBldy
_08076A60: .4byte gNonGameplayRam
_08076A64: .4byte gNextOamSlot
_08076A68: .4byte 0x040000D4
_08076A6C: .4byte gOamData
_08076A70: .4byte 0x84000100
_08076A74: .4byte gPauseScreenFlag
_08076A78: .4byte 0x06010000
_08076A7C: .4byte 0x0201C000
_08076A80: .4byte gCurrentArea
_08076A84: .4byte 0x00000212
_08076A88: .4byte 0x03000031
_08076A8C: .4byte 0x03000032
_08076A90: .4byte gCurrentRoom
_08076A94:
	cmp r0, #1
	bne _08076AA2
	movs r0, #2
	strb r0, [r4]
	bl unk_36c4
	b _08076AA8
_08076AA2:
	cmp r0, #4
	beq _08076AA8
	strb r5, [r4]
_08076AA8:
	ldr r4, _08076B04 @ =0x040000D4
	ldr r0, _08076B08 @ =0x085657A8 (sBlob_5657a8_575a60)
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	ldr r0, _08076B0C @ =0x80000030
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08076B10 @ =0x0856F71C (sBlob_5657a8_575a60+0x9F74)
	ldr r1, _08076B14 @ =0x06010000
	bl CallLZ77UncompVram
	ldr r1, _08076B18 @ =0x08561FA8 (sMinimapTilesGfx)
	ldr r2, _08076B1C @ =0x06008000
	movs r3, #0xe0
	lsls r3, r3, #6
	movs r5, #0x10
	str r5, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r0, _08076B20 @ =0x08565B48 (sBlob_5657a8_575a60+0x3A0)
	str r0, [r4]
	ldr r0, _08076B24 @ =0x05000200
	str r0, [r4, #4]
	ldr r0, _08076B28 @ =0x80000100
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08076B2C @ =gNonGameplayRam
	ldrb r0, [r0]
	cmp r0, #0
	bne _08076B40
	ldr r0, _08076B30 @ =0x0856A254 (sBlob_5657a8_575a60+0x4AAC)
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl CallLZ77UncompVram
	ldr r0, _08076B34 @ =0x08565808 (sBlob_5657a8_575a60+0x60)
	str r0, [r4]
	ldr r0, _08076B38 @ =0x05000060
	str r0, [r4, #4]
	ldr r0, _08076B3C @ =0x800000D0
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	b _08076BAA
	.align 2, 0
_08076B04: .4byte 0x040000D4
_08076B08: .4byte sMinimapTilesGfx+0x3800
_08076B0C: .4byte 0x80000030
_08076B10: .4byte sMinimapTilesGfx+0xD774
_08076B14: .4byte 0x06010000
_08076B18: .4byte sMinimapTilesGfx
_08076B1C: .4byte 0x06008000
_08076B20: .4byte sMinimapTilesGfx+0x3BA0
_08076B24: .4byte 0x05000200
_08076B28: .4byte 0x80000100
_08076B2C: .4byte gNonGameplayRam
_08076B30: .4byte sMinimapTilesGfx+0x82AC
_08076B34: .4byte sMinimapTilesGfx+0x3860
_08076B38: .4byte 0x05000060
_08076B3C: .4byte 0x800000D0
_08076B40:
	cmp r0, #1
	bne _08076BA0
	ldr r0, _08076B60 @ =0x0856C868 (sBlob_5657a8_575a60+0x70C0)
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl CallLZ77UncompVram
	ldr r0, _08076B64 @ =gEquipment
	ldrb r1, [r0, #0xc]
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _08076B68
	movs r3, #2
	b _08076B78
	.align 2, 0
_08076B60: .4byte sMinimapTilesGfx+0xA8C0
_08076B64: .4byte gEquipment
_08076B68:
	adds r0, r5, #0
	ands r0, r1
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	rsbs r0, r0, #0
	lsrs r3, r0, #0x1f
	cmp r3, #0
	beq _08076BAA
_08076B78:
	ldr r2, _08076B90 @ =0x040000D4
	lsls r0, r3, #5
	ldr r1, _08076B94 @ =0x08565D48 (sBlob_5657a8_575a60+0x5A0)
	adds r0, r0, r1
	str r0, [r2]
	ldr r0, _08076B98 @ =0x05000200
	str r0, [r2, #4]
	ldr r0, _08076B9C @ =0x80000010
	str r0, [r2, #8]
	ldr r0, [r2, #8]
	b _08076BAA
	.align 2, 0
_08076B90: .4byte 0x040000D4
_08076B94: .4byte sMinimapTilesGfx+0x3DA0
_08076B98: .4byte 0x05000200
_08076B9C: .4byte 0x80000010
_08076BA0:
	ldr r0, _08076C44 @ =0x0856DE80 (sBlob_5657a8_575a60+0x86D8)
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl CallLZ77UncompVram
_08076BAA:
	ldr r1, _08076C48 @ =gNonGameplayRam
	mov r8, r1
	ldrb r0, [r1]
	cmp r0, #0
	beq _08076BD2
	ldr r1, _08076C4C @ =0x040000D4
	ldr r0, _08076C50 @ =0x06009800
	str r0, [r1]
	ldr r0, _08076C54 @ =0x06009400
	str r0, [r1, #4]
	ldr r0, _08076C58 @ =0x80000200
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _08076C5C @ =0x085659A8 (sBlob_5657a8_575a60+0x200)
	str r0, [r1]
	ldr r0, _08076C60 @ =0x05000060
	str r0, [r1, #4]
	ldr r0, _08076C64 @ =0x800000D0
	str r0, [r1, #8]
	ldr r0, [r1, #8]
_08076BD2:
	movs r1, #0xa0
	lsls r1, r1, #0x13
	movs r0, #0
	strh r0, [r1]
	ldr r6, _08076C68 @ =0x02034800
	movs r0, #0xa
	adds r1, r6, #0
	bl GetMinimapData
	ldr r5, _08076C4C @ =0x040000D4
	str r6, [r5]
	ldr r0, _08076C6C @ =0x0600E800
	str r0, [r5, #4]
	ldr r7, _08076C70 @ =0x80000400
	str r7, [r5, #8]
	ldr r0, [r5, #8]
	str r6, [r5]
	ldr r0, _08076C74 @ =0x0600F000
	str r0, [r5, #4]
	str r7, [r5, #8]
	ldr r0, [r5, #8]
	str r6, [r5]
	ldr r0, _08076C78 @ =0x0600F800
	str r0, [r5, #4]
	str r7, [r5, #8]
	ldr r0, [r5, #8]
	ldr r0, _08076C7C @ =gCurrentArea
	ldrb r3, [r0]
	ldr r0, _08076C80 @ =0x02034000
	str r0, [r5]
	ldr r0, _08076C84 @ =0x0600E000
	str r0, [r5, #4]
	str r7, [r5, #8]
	ldr r0, [r5, #8]
	ldr r0, _08076C88 @ =0x085742E8 (sBlob_5657a8_575a60+0xEB40)
	ldr r4, _08076C8C @ =0x0200F800
	adds r1, r4, #0
	bl CallLZ77UncompVram
	str r4, [r5]
	ldr r0, _08076C90 @ =0x0600C000
	str r0, [r5, #4]
	str r7, [r5, #8]
	ldr r0, [r5, #8]
	mov r2, r8
	ldrb r0, [r2]
	cmp r0, #0
	bne _08076CC8
	ldrb r0, [r2, #2]
	cmp r0, #0
	beq _08076C98
	ldr r0, _08076C94 @ =0x08573EA0 (sBlob_5657a8_575a60+0xE6F8)
	adds r1, r6, #0
	bl CallLZ77UncompVram
	b _08076CA0
	.align 2, 0
_08076C44: .4byte sMinimapTilesGfx+0xBED8
_08076C48: .4byte gNonGameplayRam
_08076C4C: .4byte 0x040000D4
_08076C50: .4byte 0x06009800
_08076C54: .4byte 0x06009400
_08076C58: .4byte 0x80000200
_08076C5C: .4byte sMinimapTilesGfx+0x3A00
_08076C60: .4byte 0x05000060
_08076C64: .4byte 0x800000D0
_08076C68: .4byte 0x02034800
_08076C6C: .4byte 0x0600E800
_08076C70: .4byte 0x80000400
_08076C74: .4byte 0x0600F000
_08076C78: .4byte 0x0600F800
_08076C7C: .4byte gCurrentArea
_08076C80: .4byte 0x02034000
_08076C84: .4byte 0x0600E000
_08076C88: .4byte sMinimapTilesGfx+0x12340
_08076C8C: .4byte 0x0200F800
_08076C90: .4byte 0x0600C000
_08076C94: .4byte sMinimapTilesGfx+0x11EF8
_08076C98:
	ldr r0, _08076CB4 @ =0x085748AC (sBlob_5657a8_575a60+0xF104)
	adds r1, r6, #0
	bl CallLZ77UncompVram
_08076CA0:
	ldr r1, _08076CB8 @ =0x040000D4
	ldr r0, _08076CBC @ =0x02034800
	str r0, [r1]
	ldr r0, _08076CC0 @ =0x0600C800
	str r0, [r1, #4]
	ldr r0, _08076CC4 @ =0x80000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _08076CE6
	.align 2, 0
_08076CB4: .4byte sMinimapTilesGfx+0x12904
_08076CB8: .4byte 0x040000D4
_08076CBC: .4byte 0x02034800
_08076CC0: .4byte 0x0600C800
_08076CC4: .4byte 0x80000400
_08076CC8:
	cmp r0, #1
	bne _08076CD4
	ldr r0, _08076CD0 @ =0x08574D48 (sBlob_5657a8_575a60+0xF5A0)
	b _08076CD6
	.align 2, 0
_08076CD0: .4byte sMinimapTilesGfx+0x12DA0
_08076CD4:
	ldr r0, _08076D10 @ =0x085753E8 (sBlob_5657a8_575a60+0xFC40)
_08076CD6:
	adds r1, r6, #0
	bl CallLZ77UncompVram
	str r6, [r5]
	ldr r0, _08076D14 @ =0x0600D800
	str r0, [r5, #4]
	str r7, [r5, #8]
	ldr r0, [r5, #8]
_08076CE6:
	ldr r0, _08076D18 @ =gNonGameplayRam
	ldrb r0, [r0]
	cmp r0, #0
	bne _08076D38
	ldr r0, _08076D1C @ =0x085740FC (sBlob_5657a8_575a60+0xE954)
	ldr r4, _08076D20 @ =0x02034800
	adds r1, r4, #0
	bl CallLZ77UncompVram
	ldr r1, _08076D24 @ =0x040000D4
	str r4, [r1]
	ldr r0, _08076D28 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _08076D2C @ =0x80000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _08076D30 @ =0x085745A8 (sBlob_5657a8_575a60+0xEE00)
	ldr r1, _08076D34 @ =0x02010000
	bl CallLZ77UncompVram
	b _08076D74
	.align 2, 0
_08076D10: .4byte sMinimapTilesGfx+0x13440
_08076D14: .4byte 0x0600D800
_08076D18: .4byte gNonGameplayRam
_08076D1C: .4byte sMinimapTilesGfx+0x12154
_08076D20: .4byte 0x02034800
_08076D24: .4byte 0x040000D4
_08076D28: .4byte 0x0600D000
_08076D2C: .4byte 0x80000400
_08076D30: .4byte sMinimapTilesGfx+0x12600
_08076D34: .4byte 0x02010000
_08076D38:
	ldr r0, _08076D50 @ =gPauseScreenFlag
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	beq _08076D5C
	ldr r0, _08076D54 @ =0x08573DA4 (sBlob_5657a8_575a60+0xE5FC)
	ldr r1, _08076D58 @ =0x02034800
	bl CallLZ77UncompVram
	b _08076D64
	.align 2, 0
_08076D50: .4byte gPauseScreenFlag
_08076D54: .4byte sMinimapTilesGfx+0x11DFC
_08076D58: .4byte 0x02034800
_08076D5C:
	ldr r0, _08076DBC @ =0x08573DA4 (sBlob_5657a8_575a60+0xE5FC)
	ldr r1, _08076DC0 @ =0x02034800
	bl CallLZ77UncompVram
_08076D64:
	ldr r1, _08076DC4 @ =0x040000D4
	ldr r0, _08076DC0 @ =0x02034800
	str r0, [r1]
	ldr r0, _08076DC8 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _08076DCC @ =0x80000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
_08076D74:
	ldr r0, _08076DD0 @ =gCurrentArea
	ldrb r0, [r0]
	ldr r1, _08076DC0 @ =0x02034800
	bl GetMinimapData
	movs r1, #0
	ldr r2, _08076DD4 @ =gBackgroundPositions
	adds r0, r2, #0
	movs r3, #3
_08076D86:
	strh r1, [r0]
	strh r1, [r0, #2]
	adds r0, #4
	subs r3, #1
	cmp r3, #0
	bge _08076D86
	ldr r1, _08076DD8 @ =gNonGameplayRam
	movs r0, #0
	strb r0, [r1, #7]
	strb r0, [r1, #9]
	strb r0, [r1, #6]
	strb r0, [r1, #8]
	ldr r0, _08076DDC @ =0x0879BE88 (sUnk_79be88)
	ldr r0, [r0]
	str r0, [r1, #0x28]
	movs r0, #0x80
	lsls r0, r0, #1
	strh r0, [r2, #6]
	movs r0, #3
	strb r0, [r1, #1]
	ldrb r0, [r1]
	adds r5, r1, #0
	cmp r0, #0
	beq _08076DE0
	movs r0, #1
	b _08076DF6
	.align 2, 0
_08076DBC: .4byte sMinimapTilesGfx+0x11DFC
_08076DC0: .4byte 0x02034800
_08076DC4: .4byte 0x040000D4
_08076DC8: .4byte 0x0600D000
_08076DCC: .4byte 0x80000400
_08076DD0: .4byte gCurrentArea
_08076DD4: .4byte gBackgroundPositions
_08076DD8: .4byte gNonGameplayRam
_08076DDC: .4byte sExploredMinimapBitFlags+0xAC
_08076DE0:
	ldr r0, _08076DF0 @ =gPauseScreenFlag
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #2
	bne _08076DF4
	movs r0, #0
	b _08076DF6
	.align 2, 0
_08076DF0: .4byte gPauseScreenFlag
_08076DF4:
	movs r0, #2
_08076DF6:
	strb r0, [r5, #1]
	ldrb r0, [r5]
	cmp r0, #0
	beq _08076E4C
	bl EventCheckSetNavigationRoomEvent
	cmp r0, #0
	beq _08076E28
	adds r1, r5, #0
	adds r1, #0x28
	movs r0, #4
	strb r0, [r1]
	ldr r4, _08076E20 @ =gCurrentArea
	ldrb r0, [r4]
	ldr r1, _08076E24 @ =0x02034000
	bl GetMinimapData
	ldrb r0, [r4]
	bl MinimapSetVisitedTilesAndCollectedItems
	b _08076E30
	.align 2, 0
_08076E20: .4byte gCurrentArea
_08076E24: .4byte 0x02034000
_08076E28:
	adds r1, r5, #0
	adds r1, #0x28
	movs r0, #0xa
	strb r0, [r1]
_08076E30:
	ldr r0, _08076E5C @ =gEventCounter
	ldrb r0, [r0]
	cmp r0, #0x5b
	bhi _08076E4C
	movs r0, #0
	str r0, [sp, #4]
	ldr r1, _08076E60 @ =0x040000D4
	add r3, sp, #4
	str r3, [r1]
	ldr r0, _08076E64 @ =0x06017C00
	str r0, [r1, #4]
	ldr r0, _08076E68 @ =0x85000010
	str r0, [r1, #8]
	ldr r0, [r1, #8]
_08076E4C:
	ldr r0, _08076E6C @ =gNonGameplayRam
	ldrb r0, [r0, #2]
	cmp r0, #0
	beq _08076E70
	bl PauseDebugDrawEverything
	b _08076E74
	.align 2, 0
_08076E5C: .4byte gEventCounter
_08076E60: .4byte 0x040000D4
_08076E64: .4byte 0x06017C00
_08076E68: .4byte 0x85000010
_08076E6C: .4byte gNonGameplayRam
_08076E70:
	bl StatusScreenDrawEverything
_08076E74:
	movs r0, #0
	bl unk_75988
	bl ProcessPauseScreenText
	bl ProcessEasySleepText
	bl PauseScreenSetupOam
	bl NavigationConversationGetCurrentConversation
	bl NavigationConversationLoadPopUpGraphics
	bl NavigationConversationLoadSpecialGraphics
	movs r0, #0xff
	bl unk_77840
	bl unk_7ce6c
	ldr r2, _08076EF8 @ =0x04000010
	ldr r1, _08076EFC @ =gBackgroundPositions
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
	ldr r5, _08076F00 @ =gWrittenToBldy
	movs r1, #0
	strh r1, [r5]
	ldr r4, _08076F04 @ =gWrittenToBldalpha_Evb
	strh r1, [r4]
	ldr r3, _08076F08 @ =gWrittenToBldalpha_Eva
	movs r2, #0x10
	strh r2, [r3]
	ldr r0, _08076F0C @ =gNonGameplayRam
	ldrb r0, [r0]
	cmp r0, #0
	beq _08076F18
	strh r1, [r4]
	strh r1, [r3]
	ldr r1, _08076F10 @ =0x04000050
	ldr r4, _08076F14 @ =0x00003F7F
	adds r0, r4, #0
	strh r0, [r1]
	adds r1, #2
	movs r0, #0
	b _08076F1E
	.align 2, 0
_08076EF8: .4byte 0x04000010
_08076EFC: .4byte gBackgroundPositions
_08076F00: .4byte gWrittenToBldy
_08076F04: .4byte gWrittenToBldalpha_Evb
_08076F08: .4byte gWrittenToBldalpha_Eva
_08076F0C: .4byte gNonGameplayRam
_08076F10: .4byte 0x04000050
_08076F14: .4byte 0x00003F7F
_08076F18:
	strh r2, [r5]
	ldr r1, _08076F3C @ =0x04000050
	movs r0, #0xff
_08076F1E:
	strh r0, [r1]
	ldr r1, _08076F40 @ =0x04000040
	movs r0, #0xf0
	strh r0, [r1]
	ldr r0, _08076F44 @ =gNonGameplayRam
	ldrb r1, [r0]
	adds r5, r0, #0
	cmp r1, #0
	beq _08076F4C
	ldr r1, _08076F48 @ =0x0400004A
	movs r0, #0x37
	strb r0, [r1]
	subs r1, #1
	movs r0, #0x3f
	b _08076F56
	.align 2, 0
_08076F3C: .4byte 0x04000050
_08076F40: .4byte 0x04000040
_08076F44: .4byte gNonGameplayRam
_08076F48: .4byte 0x0400004A
_08076F4C:
	ldr r1, _08076FDC @ =0x0400004A
	movs r0, #0x35
	strb r0, [r1]
	subs r1, #1
	movs r0, #0x3d
_08076F56:
	strb r0, [r1]
	ldr r1, _08076FE0 @ =0x04000048
	movs r0, #0x3f
	strb r0, [r1]
	adds r4, r5, #0
	adds r0, r4, #0
	adds r0, #0x28
	ldrb r0, [r0]
	movs r3, #0
	cmp r0, #1
	beq _08076F6E
	movs r3, #0xa0
_08076F6E:
	ldr r1, _08076FE4 @ =0x04000044
	lsls r0, r3, #8
	movs r2, #0xa0
	orrs r0, r2
	strh r0, [r1]
	subs r1, #2
	movs r0, #0xf0
	strh r0, [r1]
	ldr r0, _08076FE8 @ =0x04000046
	strh r2, [r0]
	ldr r0, _08076FEC @ =gWrittenToMosaic_L
	movs r1, #0
	strh r1, [r0]
	ldr r0, _08076FF0 @ =0x0400004C
	strh r1, [r0]
	ldrb r0, [r4]
	cmp r0, #0
	beq _08077018
	ldr r1, _08076FF4 @ =0x0400000A
	ldr r2, _08076FF8 @ =0x00001B03
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #4
	ldr r3, _08076FFC @ =0x0000DC49
	adds r0, r3, #0
	strh r0, [r1]
	subs r1, #6
	movs r2, #0xc0
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r3, r4, r0
	movs r2, #0xbe
	lsls r2, r2, #7
	strh r2, [r3]
	ldr r0, _08077000 @ =gPauseScreenFlag
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	bne _08077008
	adds r1, #4
	ldr r4, _08077004 @ =0x00001A0A
	adds r0, r4, #0
	strh r0, [r1]
	movs r0, #0x80
	lsls r0, r0, #4
	adds r1, r0, #0
	adds r0, r2, #0
	eors r0, r1
	strh r0, [r3]
	b _08077046
	.align 2, 0
_08076FDC: .4byte 0x0400004A
_08076FE0: .4byte 0x04000048
_08076FE4: .4byte 0x04000044
_08076FE8: .4byte 0x04000046
_08076FEC: .4byte gWrittenToMosaic_L
_08076FF0: .4byte 0x0400004C
_08076FF4: .4byte 0x0400000A
_08076FF8: .4byte 0x00001B03
_08076FFC: .4byte 0x0000DC49
_08077000: .4byte gPauseScreenFlag
_08077004: .4byte 0x00001A0A
_08077008:
	ldr r1, _08077010 @ =0x0400000C
	ldr r2, _08077014 @ =0x00001A0A
	adds r0, r2, #0
	b _08077044
	.align 2, 0
_08077010: .4byte 0x0400000C
_08077014: .4byte 0x00001A0A
_08077018:
	ldr r1, _0807706C @ =0x0400000E
	ldr r3, _08077070 @ =0x0000DC4B
	adds r0, r3, #0
	strh r0, [r1]
	subs r1, #2
	ldr r4, _08077074 @ =0x00001A02
	adds r0, r4, #0
	strh r0, [r1]
	subs r1, #4
	ldr r2, _08077078 @ =0x00001801
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	movs r3, #0xc8
	lsls r3, r3, #5
	adds r0, r3, #0
	strh r0, [r1]
	movs r4, #0x9a
	lsls r4, r4, #2
	adds r1, r5, r4
	movs r0, #0xfc
	lsls r0, r0, #7
_08077044:
	strh r0, [r1]
_08077046:
	ldr r0, _0807707C @ =PauseScreenVBLank
	bl CallbackSetVBlank
	movs r1, #0x80
	lsls r1, r1, #0x13
	ldr r0, _08077080 @ =gNonGameplayRam
	movs r2, #0x9a
	lsls r2, r2, #2
	adds r0, r0, r2
	ldrh r0, [r0]
	strh r0, [r1]
	mov r0, sb
	add sp, #8
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0807706C: .4byte 0x0400000E
_08077070: .4byte 0x0000DC4B
_08077074: .4byte 0x00001A02
_08077078: .4byte 0x00001801
_0807707C: .4byte PauseScreenVBLank
_08077080: .4byte gNonGameplayRam

