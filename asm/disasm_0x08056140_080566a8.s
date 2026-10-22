    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start GunshipEndStartingEngine1
GunshipEndStartingEngine1: @ 0x080566A8
	push {r4, r5, r6, lr}
	ldr r4, _08056718 @ =gCurrentSprite
	adds r6, r4, #0
	adds r6, #0x31
	ldrb r5, [r6]
	bl SpriteUtilHasCurrentAnimationEnded
	cmp r0, #0
	beq _08056712
	adds r1, r4, #0
	adds r1, #0x24
	movs r3, #0
	movs r0, #0x3a
	strb r0, [r1]
	ldr r0, _0805671C @ =0x0839EC68 (sBlob_39aa34_39f4b0+0x4234)
	str r0, [r4, #0x18]
	strb r3, [r4, #0x1c]
	movs r2, #0
	strh r3, [r4, #0x16]
	adds r1, #0xa
	movs r0, #0x3c
	strb r0, [r1]
	adds r0, r4, #0
	adds r0, #0x2f
	strb r2, [r0]
	strb r2, [r6]
	ldrh r0, [r4]
	movs r1, #8
	orrs r0, r1
	strh r0, [r4]
	movs r0, #0x80
	lsls r0, r0, #1
	strh r0, [r4, #0x12]
	adds r0, r4, #0
	adds r0, #0x2b
	strb r2, [r0]
	ldr r1, _08056720 @ =gSpriteData
	lsls r0, r5, #3
	subs r0, r0, r5
	lsls r0, r0, #3
	adds r0, r0, r1
	strh r3, [r0]
	ldr r0, _08056724 @ =0x082F474E (sGunshipBeamOam_Idle_Frame2+0x6C)
	ldr r1, _08056728 @ =0x040000D4
	str r0, [r1]
	ldr r0, _0805672C @ =0x05000336
	str r0, [r1, #4]
	ldr r0, _08056730 @ =0x80000005
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _08056734 @ =0x0000024A
	bl SoundPlay_3b1c
_08056712:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08056718: .4byte gCurrentSprite
_0805671C: .4byte sOmegaMetroidPartOam_LeftLeg_Swiping+0x4264
_08056720: .4byte gSpriteData
_08056724: .4byte sGunshipFlashingPal+0x16
_08056728: .4byte 0x040000D4
_0805672C: .4byte 0x05000336
_08056730: .4byte 0x80000005
_08056734: .4byte 0x0000024A

	thumb_func_start GunshipEndStartingEngine2
GunshipEndStartingEngine2: @ 0x08056738
	push {r4, r5, r6, lr}
	ldr r2, _08056794 @ =gCurrentSprite
	movs r0, #0x31
	adds r0, r0, r2
	mov ip, r0
	ldrb r3, [r0]
	ldr r5, _08056798 @ =0x0839ABC4 (sBlob_39aa34_39f4b0+0x190)
	lsls r0, r3, #1
	adds r0, r0, r5
	ldrh r4, [r0]
	movs r6, #0
	ldrsh r1, [r0, r6]
	ldr r0, _0805679C @ =0x00007FFF
	cmp r1, r0
	bne _0805675A
	ldrh r4, [r5]
	movs r3, #0
_0805675A:
	adds r0, r3, #1
	mov r1, ip
	strb r0, [r1]
	ldrh r0, [r2, #2]
	adds r0, r0, r4
	movs r4, #0
	strh r0, [r2, #2]
	adds r5, r2, #0
	adds r5, #0x2f
	ldrb r1, [r5]
	cmp r1, #0
	bne _080567A4
	adds r3, r2, #0
	adds r3, #0x2e
	ldrb r0, [r3]
	subs r0, #1
	strb r0, [r3]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080567FE
	ldr r0, _080567A0 @ =0x0839EC08 (sBlob_39aa34_39f4b0+0x41D4)
	str r0, [r2, #0x18]
	strb r4, [r2, #0x1c]
	strh r1, [r2, #0x16]
	movs r0, #0x3c
	strb r0, [r3]
	movs r0, #1
	strb r0, [r5]
	b _080567FE
	.align 2, 0
_08056794: .4byte gCurrentSprite
_08056798: .4byte sOmegaMetroidPartOam_LeftLeg_Swiping+0x1C0
_0805679C: .4byte 0x00007FFF
_080567A0: .4byte sOmegaMetroidPartOam_LeftLeg_Swiping+0x4204
_080567A4:
	cmp r1, #1
	bne _080567D0
	adds r3, r2, #0
	adds r3, #0x2e
	ldrb r0, [r3]
	subs r0, #1
	strb r0, [r3]
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0
	bne _080567FE
	ldr r0, _080567CC @ =0x0839EC78 (sBlob_39aa34_39f4b0+0x4244)
	str r0, [r2, #0x18]
	strb r4, [r2, #0x1c]
	strh r1, [r2, #0x16]
	movs r0, #0x5a
	strb r0, [r3]
	movs r0, #2
	strb r0, [r5]
	b _080567FE
	.align 2, 0
_080567CC: .4byte sOmegaMetroidPartOam_LeftLeg_Swiping+0x4274
_080567D0:
	adds r3, r2, #0
	adds r3, #0x2e
	ldrb r0, [r3]
	subs r0, #1
	strb r0, [r3]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080567FE
	adds r1, r2, #0
	adds r1, #0x24
	movs r0, #0x3b
	strb r0, [r1]
	strb r4, [r3]
	strb r4, [r5]
	adds r0, r2, #0
	adds r0, #0x30
	strb r4, [r0]
	ldrh r0, [r2]
	movs r3, #0x80
	lsls r3, r3, #7
	adds r1, r3, #0
	orrs r0, r1
	strh r0, [r2]
_080567FE:
	pop {r4, r5, r6}
	pop {r0}
	bx r0

	thumb_func_start GunshipEndTakingOff
GunshipEndTakingOff: @ 0x08056804
	push {lr}
	ldr r1, _08056828 @ =gCurrentSprite
	adds r3, r1, #0
	adds r3, #0x2e
	ldrb r2, [r3]
	adds r0, r2, #0
	cmp r0, #0x3f
	bls _0805682C
	ldrh r0, [r1, #2]
	subs r0, #8
	strh r0, [r1, #2]
	adds r1, #0x24
	movs r0, #0x3c
	strb r0, [r1]
	bl ColorFadingStartFinalEscape
	b _0805685A
	.align 2, 0
_08056828: .4byte gCurrentSprite
_0805682C:
	cmp r0, #0x37
	bls _0805683A
	ldrh r0, [r1, #2]
	subs r0, #8
	strh r0, [r1, #2]
	adds r0, r2, #4
	b _08056858
_0805683A:
	cmp r0, #0x2f
	bls _08056848
	ldrh r0, [r1, #2]
	subs r0, #2
	strh r0, [r1, #2]
	adds r0, r2, #4
	b _08056858
_08056848:
	cmp r0, #0x1f
	bls _08056856
	ldrh r0, [r1, #2]
	subs r0, #1
	strh r0, [r1, #2]
	adds r0, r2, #2
	b _08056858
_08056856:
	adds r0, r2, #1
_08056858:
	strb r0, [r3]
_0805685A:
	ldr r3, _0805688C @ =gCurrentSprite
	ldr r1, _08056890 @ =0x0839ACD0 (sBlob_39aa34_39f4b0+0x29C)
	adds r2, r3, #0
	adds r2, #0x2e
	ldrb r0, [r2]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r0, [r0]
	strh r0, [r3, #0x12]
	ldrb r0, [r2]
	cmp r0, #0x1f
	bls _08056886
	subs r0, #0x20
	asrs r0, r0, #2
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldr r1, _08056894 @ =0x0839AC84 (sBlob_39aa34_39f4b0+0x250)
	adds r0, r0, r1
	ldrb r1, [r0]
	adds r0, r3, #0
	adds r0, #0x2b
	strb r1, [r0]
_08056886:
	pop {r0}
	bx r0
	.align 2, 0
_0805688C: .4byte gCurrentSprite
_08056890: .4byte sOmegaMetroidPartOam_LeftLeg_Swiping+0x2CC
_08056894: .4byte sOmegaMetroidPartOam_LeftLeg_Swiping+0x280

	thumb_func_start GunshipEndDone
GunshipEndDone: @ 0x08056898
	bx lr
	.align 2, 0

	thumb_func_start GunshipEndBottomIdle
GunshipEndBottomIdle: @ 0x0805689C
	push {lr}
	ldr r2, _080568E0 @ =gCurrentSprite
	adds r0, r2, #0
	adds r0, #0x30
	ldrb r1, [r0]
	adds r1, #1
	strb r1, [r0]
	movs r0, #7
	ands r1, r0
	cmp r1, #0
	bne _0805690C
	adds r3, r2, #0
	adds r3, #0x2e
	ldrb r0, [r3]
	lsls r0, r0, #5
	ldr r1, _080568E4 @ =0x082F474E (sGunshipBeamOam_Idle_Frame2+0x6C)
	adds r0, r0, r1
	ldr r1, _080568E8 @ =0x040000D4
	str r0, [r1]
	ldr r0, _080568EC @ =0x05000336
	str r0, [r1, #4]
	ldr r0, _080568F0 @ =0x80000005
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	adds r2, #0x2f
	ldrb r0, [r2]
	cmp r0, #0
	beq _080568FA
	ldrb r0, [r3]
	adds r1, r0, #0
	cmp r1, #0
	beq _080568F4
	subs r0, #1
	b _0805690A
	.align 2, 0
_080568E0: .4byte gCurrentSprite
_080568E4: .4byte sGunshipFlashingPal+0x16
_080568E8: .4byte 0x040000D4
_080568EC: .4byte 0x05000336
_080568F0: .4byte 0x80000005
_080568F4:
	strb r1, [r2]
	movs r0, #1
	b _0805690A
_080568FA:
	ldrb r0, [r3]
	cmp r0, #5
	bls _08056908
	movs r0, #1
	strb r0, [r2]
	movs r0, #5
	b _0805690A
_08056908:
	adds r0, #1
_0805690A:
	strb r0, [r3]
_0805690C:
	pop {r0}
	bx r0

	thumb_func_start GunshiEndpBeamInit
GunshiEndpBeamInit: @ 0x08056910
	push {r4, lr}
	ldr r0, _08056974 @ =gCurrentSprite
	mov ip, r0
	ldrh r1, [r0]
	ldr r0, _08056978 @ =0x0000FFFB
	ands r0, r1
	movs r3, #0
	movs r4, #0
	mov r1, ip
	strh r0, [r1]
	mov r2, ip
	adds r2, #0x34
	ldrb r1, [r2]
	movs r0, #1
	orrs r0, r1
	strb r0, [r2]
	mov r0, ip
	adds r0, #0x25
	strb r3, [r0]
	adds r0, #2
	movs r1, #4
	strb r1, [r0]
	adds r0, #1
	strb r1, [r0]
	subs r2, #0xb
	movs r0, #0x10
	strb r0, [r2]
	ldr r0, _0805697C @ =0x0000FFFC
	mov r2, ip
	strh r0, [r2, #0xa]
	strh r1, [r2, #0xc]
	strh r0, [r2, #0xe]
	strh r1, [r2, #0x10]
	ldr r0, _08056980 @ =0x0839EBB8 (sBlob_39aa34_39f4b0+0x4184)
	str r0, [r2, #0x18]
	strb r3, [r2, #0x1c]
	strh r4, [r2, #0x16]
	mov r1, ip
	adds r1, #0x24
	movs r0, #2
	strb r0, [r1]
	subs r1, #2
	movs r0, #0xd
	strb r0, [r1]
	adds r1, #0xc
	movs r0, #9
	strb r0, [r1]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08056974: .4byte gCurrentSprite
_08056978: .4byte 0x0000FFFB
_0805697C: .4byte 0x0000FFFC
_08056980: .4byte sOmegaMetroidPartOam_LeftLeg_Swiping+0x41B4

	thumb_func_start GunshipEndBeamMovingDown
GunshipEndBeamMovingDown: @ 0x08056984
	push {lr}
	ldr r1, _080569A4 @ =gCurrentSprite
	adds r0, r1, #0
	adds r0, #0x23
	ldrb r3, [r0]
	ldrb r0, [r1, #0x1e]
	adds r2, r1, #0
	cmp r0, #0
	beq _080569A8
	subs r0, #1
	strb r0, [r2, #0x1e]
	ldrh r0, [r2, #2]
	adds r0, #4
	strh r0, [r2, #2]
	b _080569EA
	.align 2, 0
_080569A4: .4byte gCurrentSprite
_080569A8:
	adds r1, r2, #0
	adds r1, #0x2e
	ldrb r0, [r1]
	subs r0, #1
	strb r0, [r1]
	lsls r0, r0, #0x18
	cmp r0, #0
	beq _080569C0
	ldrh r0, [r2, #2]
	adds r0, #4
	strh r0, [r2, #2]
	b _080569CA
_080569C0:
	ldrh r0, [r2, #2]
	subs r0, #0x20
	strh r0, [r2, #2]
	movs r0, #9
	strb r0, [r1]
_080569CA:
	ldr r0, _080569F0 @ =gSpriteData
	lsls r1, r3, #3
	subs r1, r1, r3
	lsls r1, r1, #3
	adds r1, r1, r0
	adds r1, #0x24
	ldrb r0, [r1]
	cmp r0, #0x37
	bne _080569EA
	adds r1, r2, #0
	adds r1, #0x24
	movs r0, #0x18
	strb r0, [r1]
	subs r1, #2
	movs r0, #5
	strb r0, [r1]
_080569EA:
	pop {r0}
	bx r0
	.align 2, 0
_080569F0: .4byte gSpriteData

	thumb_func_start GunshipEndBeamMovingUp
GunshipEndBeamMovingUp: @ 0x080569F4
	push {r4, lr}
	ldr r1, _08056A1C @ =gCurrentSprite
	adds r0, r1, #0
	adds r0, #0x23
	ldrb r4, [r0]
	adds r2, r1, #0
	adds r2, #0x2e
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r3, r1, #0
	cmp r0, #8
	bls _08056A20
	movs r0, #0
	strb r0, [r2]
	ldrh r0, [r3, #2]
	adds r0, #0x20
	b _08056A24
	.align 2, 0
_08056A1C: .4byte gCurrentSprite
_08056A20:
	ldrh r0, [r3, #2]
	subs r0, #4
_08056A24:
	strh r0, [r3, #2]
	ldr r0, _08056A44 @ =gSpriteData
	lsls r1, r4, #3
	subs r1, r1, r4
	lsls r1, r1, #3
	adds r1, r1, r0
	adds r1, #0x24
	ldrb r0, [r1]
	cmp r0, #0x39
	bne _08056A3C
	movs r0, #0
	strh r0, [r3]
_08056A3C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08056A44: .4byte gSpriteData

	thumb_func_start GunshipEnd
GunshipEnd: @ 0x08056A48
	push {lr}
	ldr r0, _08056A68 @ =gCurrentSprite
	adds r2, r0, #0
	adds r2, #0x26
	movs r1, #1
	strb r1, [r2]
	adds r0, #0x24
	ldrb r0, [r0]
	cmp r0, #0x3c
	bls _08056A5E
	b _08056BAA
_08056A5E:
	lsls r0, r0, #2
	ldr r1, _08056A6C @ =_08056A70
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08056A68: .4byte gCurrentSprite
_08056A6C: .4byte _08056A70
_08056A70: @ jump table
	.4byte _08056B64 @ case 0
	.4byte _08056B6A @ case 1
	.4byte _08056B70 @ case 2
	.4byte _08056BAA @ case 3
	.4byte _08056BAA @ case 4
	.4byte _08056BAA @ case 5
	.4byte _08056BAA @ case 6
	.4byte _08056BAA @ case 7
	.4byte _08056BAA @ case 8
	.4byte _08056BAA @ case 9
	.4byte _08056BAA @ case 10
	.4byte _08056BAA @ case 11
	.4byte _08056BAA @ case 12
	.4byte _08056BAA @ case 13
	.4byte _08056BAA @ case 14
	.4byte _08056BAA @ case 15
	.4byte _08056BAA @ case 16
	.4byte _08056BAA @ case 17
	.4byte _08056BAA @ case 18
	.4byte _08056BAA @ case 19
	.4byte _08056BAA @ case 20
	.4byte _08056BAA @ case 21
	.4byte _08056BAA @ case 22
	.4byte _08056B76 @ case 23
	.4byte _08056B7C @ case 24
	.4byte _08056BAA @ case 25
	.4byte _08056B82 @ case 26
	.4byte _08056BAA @ case 27
	.4byte _08056BAA @ case 28
	.4byte _08056BAA @ case 29
	.4byte _08056BAA @ case 30
	.4byte _08056BAA @ case 31
	.4byte _08056BAA @ case 32
	.4byte _08056BAA @ case 33
	.4byte _08056BAA @ case 34
	.4byte _08056BAA @ case 35
	.4byte _08056BAA @ case 36
	.4byte _08056BAA @ case 37
	.4byte _08056BAA @ case 38
	.4byte _08056BAA @ case 39
	.4byte _08056BAA @ case 40
	.4byte _08056BAA @ case 41
	.4byte _08056BAA @ case 42
	.4byte _08056BAA @ case 43
	.4byte _08056BAA @ case 44
	.4byte _08056BAA @ case 45
	.4byte _08056BAA @ case 46
	.4byte _08056BAA @ case 47
	.4byte _08056BAA @ case 48
	.4byte _08056BAA @ case 49
	.4byte _08056BAA @ case 50
	.4byte _08056BAA @ case 51
	.4byte _08056BAA @ case 52
	.4byte _08056BAA @ case 53
	.4byte _08056BAA @ case 54
	.4byte _08056B88 @ case 55
	.4byte _08056B8E @ case 56
	.4byte _08056B94 @ case 57
	.4byte _08056B9A @ case 58
	.4byte _08056BA0 @ case 59
	.4byte _08056BA6 @ case 60
_08056B64:
	bl GunshipEndInit
	b _08056BAA
_08056B6A:
	bl GunshipEndWaiting
	b _08056BAA
_08056B70:
	bl GunshipEndMovingUp
	b _08056BAA
_08056B76:
	bl GunshipEndWaitingToEnter
	b _08056BAA
_08056B7C:
	bl GunshipEndEntering
	b _08056BAA
_08056B82:
	bl GunshipEndWaitingForSamus
	b _08056BAA
_08056B88:
	bl GunshipEndLockingSamus
	b _08056BAA
_08056B8E:
	bl GunshipEndMovingSamusUp
	b _08056BAA
_08056B94:
	bl GunshipEndStartingEngine1
	b _08056BAA
_08056B9A:
	bl GunshipEndStartingEngine2
	b _08056BAA
_08056BA0:
	bl GunshipEndTakingOff
	b _08056BAA
_08056BA6:
	bl GunshipEndDone
_08056BAA:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start GunshipEndBottom
GunshipEndBottom: @ 0x08056BB0
	push {lr}
	ldr r0, _08056BCC @ =gCurrentSprite
	adds r2, r0, #0
	adds r2, #0x26
	movs r1, #1
	strb r1, [r2]
	adds r0, #0x24
	ldrb r0, [r0]
	cmp r0, #2
	bne _08056BC8
	bl GunshipEndBottomIdle
_08056BC8:
	pop {r0}
	bx r0
	.align 2, 0
_08056BCC: .4byte gCurrentSprite

	thumb_func_start GunshipEndBeam
GunshipEndBeam: @ 0x08056BD0
	push {lr}
	ldr r0, _08056BF0 @ =gCurrentSprite
	adds r2, r0, #0
	adds r2, #0x26
	movs r1, #1
	strb r1, [r2]
	adds r0, #0x24
	ldrb r0, [r0]
	cmp r0, #2
	beq _08056BFE
	cmp r0, #2
	bgt _08056BF4
	cmp r0, #0
	beq _08056BFA
	b _08056C08
	.align 2, 0
_08056BF0: .4byte gCurrentSprite
_08056BF4:
	cmp r0, #0x18
	beq _08056C04
	b _08056C08
_08056BFA:
	bl GunshiEndpBeamInit
_08056BFE:
	bl GunshipEndBeamMovingDown
	b _08056C08
_08056C04:
	bl GunshipEndBeamMovingUp
_08056C08:
	ldr r1, _08056C20 @ =gCurrentSprite
	ldrb r0, [r1, #0x1e]
	cmp r0, #0
	bne _08056C1C
	ldrh r0, [r1]
	cmp r0, #0
	bne _08056C1C
	movs r0, #0xfd
	bl SoundStop
_08056C1C:
	pop {r0}
	bx r0
	.align 2, 0
_08056C20: .4byte gCurrentSprite
