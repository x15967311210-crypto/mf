    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start GunshipEndSpawnBeams
GunshipEndSpawnBeams: @ 0x08056140
	push {r4, r5, lr}
	sub sp, #0xc
	ldr r0, _08056170 @ =gCurrentSprite
	movs r2, #0x90
	lsls r2, r2, #1
	adds r1, r2, #0
	ldrh r2, [r0, #2]
	adds r1, r1, r2
	lsls r1, r1, #0x10
	lsrs r4, r1, #0x10
	ldrh r5, [r0, #4]
	adds r1, r0, #0
	adds r1, #0x2f
	ldrb r1, [r1]
	subs r1, #6
	adds r3, r0, #0
	cmp r1, #0xf
	bls _08056166
	b _08056270
_08056166:
	lsls r0, r1, #2
	ldr r1, _08056174 @ =_08056178
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08056170: .4byte gCurrentSprite
_08056174: .4byte _08056178
_08056178: @ jump table
	.4byte _080561B8 @ case 0
	.4byte _08056270 @ case 1
	.4byte _08056270 @ case 2
	.4byte _080561DC @ case 3
	.4byte _08056270 @ case 4
	.4byte _08056270 @ case 5
	.4byte _080561FA @ case 6
	.4byte _08056270 @ case 7
	.4byte _08056270 @ case 8
	.4byte _08056218 @ case 9
	.4byte _08056270 @ case 10
	.4byte _08056270 @ case 11
	.4byte _08056236 @ case 12
	.4byte _08056270 @ case 13
	.4byte _08056270 @ case 14
	.4byte _08056254 @ case 15
_080561B8:
	ldrb r2, [r3, #0x1f]
	adds r0, r3, #0
	adds r0, #0x23
	ldrb r3, [r0]
	adds r0, r4, #0
	subs r0, #0xcc
	str r0, [sp]
	str r5, [sp, #4]
	movs r0, #0
	str r0, [sp, #8]
	movs r0, #0x79
	movs r1, #0
	bl SpriteSpawnSecondary
	movs r0, #0xfd
	bl SoundPlay
	b _08056270
_080561DC:
	ldrb r2, [r3, #0x1f]
	adds r0, r3, #0
	adds r0, #0x23
	ldrb r3, [r0]
	adds r0, r4, #0
	subs r0, #0xb0
	str r0, [sp]
	str r5, [sp, #4]
	movs r0, #0
	str r0, [sp, #8]
	movs r0, #0x79
	movs r1, #1
	bl SpriteSpawnSecondary
	b _08056270
_080561FA:
	ldrb r2, [r3, #0x1f]
	adds r0, r3, #0
	adds r0, #0x23
	ldrb r3, [r0]
	adds r0, r4, #0
	subs r0, #0x98
	str r0, [sp]
	str r5, [sp, #4]
	movs r0, #0
	str r0, [sp, #8]
	movs r0, #0x79
	movs r1, #3
	bl SpriteSpawnSecondary
	b _08056270
_08056218:
	ldrb r2, [r3, #0x1f]
	adds r0, r3, #0
	adds r0, #0x23
	ldrb r3, [r0]
	adds r0, r4, #0
	subs r0, #0x80
	str r0, [sp]
	str r5, [sp, #4]
	movs r0, #0
	str r0, [sp, #8]
	movs r0, #0x79
	movs r1, #5
	bl SpriteSpawnSecondary
	b _08056270
_08056236:
	ldrb r2, [r3, #0x1f]
	adds r0, r3, #0
	adds r0, #0x23
	ldrb r3, [r0]
	adds r0, r4, #0
	subs r0, #0x68
	str r0, [sp]
	str r5, [sp, #4]
	movs r0, #0
	str r0, [sp, #8]
	movs r0, #0x79
	movs r1, #7
	bl SpriteSpawnSecondary
	b _08056270
_08056254:
	ldrb r2, [r3, #0x1f]
	adds r0, r3, #0
	adds r0, #0x23
	ldrb r3, [r0]
	adds r0, r4, #0
	subs r0, #0x50
	str r0, [sp]
	str r5, [sp, #4]
	movs r0, #0
	str r0, [sp, #8]
	movs r0, #0x79
	movs r1, #9
	bl SpriteSpawnSecondary
_08056270:
	add sp, #0xc
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start GunshipEndInit
GunshipEndInit: @ 0x08056278
	push {r4, lr}
	ldr r0, _080562F4 @ =gCurrentSprite
	mov ip, r0
	ldrh r0, [r0]
	ldr r1, _080562F8 @ =0x0000FFFB
	ands r1, r0
	movs r2, #0
	movs r3, #0
	mov r4, ip
	adds r4, #0x22
	movs r0, #0xc
	strb r0, [r4]
	subs r4, #1
	movs r0, #3
	strb r0, [r4]
	movs r0, #8
	orrs r1, r0
	mov r4, ip
	strh r1, [r4]
	movs r0, #0x90
	strh r0, [r4, #0x12]
	mov r0, ip
	adds r0, #0x2b
	strb r2, [r0]
	adds r0, #6
	strb r2, [r0]
	subs r0, #1
	strb r2, [r0]
	mov r1, ip
	adds r1, #0x2e
	movs r0, #0x3c
	strb r0, [r1]
	mov r0, ip
	adds r0, #0x25
	strb r2, [r0]
	subs r1, #7
	movs r0, #0x7f
	strb r0, [r1]
	adds r1, #1
	movs r0, #0x40
	strb r0, [r1]
	adds r1, #1
	movs r0, #0xb0
	strb r0, [r1]
	ldr r1, _080562FC @ =0x0000FFFC
	strh r1, [r4, #0xa]
	movs r0, #4
	strh r0, [r4, #0xc]
	strh r1, [r4, #0xe]
	strh r0, [r4, #0x10]
	mov r1, ip
	adds r1, #0x24
	movs r0, #1
	strb r0, [r1]
	ldr r0, _08056300 @ =0x0839EC68 (sBlob_39aa34_39f4b0+0x4234)
	str r0, [r4, #0x18]
	strb r2, [r4, #0x1c]
	strh r3, [r4, #0x16]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080562F4: .4byte gCurrentSprite
_080562F8: .4byte 0x0000FFFB
_080562FC: .4byte 0x0000FFFC
_08056300: .4byte sOmegaMetroidPartOam_LeftLeg_Swiping+0x4264

	thumb_func_start GunshipEndWaiting
GunshipEndWaiting: @ 0x08056304
	push {r4, lr}
	ldr r1, _08056334 @ =gCurrentSprite
	adds r4, r1, #0
	adds r4, #0x2e
	ldrb r0, [r4]
	subs r0, #1
	strb r0, [r4]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _0805632C
	adds r0, r1, #0
	adds r0, #0x24
	movs r1, #2
	strb r1, [r0]
	movs r0, #0x5b
	movs r1, #0xe
	bl PlayMusic
	movs r0, #0x1e
	strb r0, [r4]
_0805632C:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08056334: .4byte gCurrentSprite

	thumb_func_start GunshipEndMovingUp
GunshipEndMovingUp: @ 0x08056338
	push {r4, lr}
	ldr r0, _08056374 @ =gCurrentSprite
	adds r1, r0, #0
	adds r1, #0x2e
	ldrb r0, [r1]
	cmp r0, #0
	beq _08056356
	subs r0, #1
	strb r0, [r1]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08056356
	ldr r0, _08056378 @ =0x00000249
	bl SoundPlay_3b1c
_08056356:
	movs r4, #0
	ldr r3, _08056374 @ =gCurrentSprite
	ldrh r2, [r3, #4]
	lsrs r0, r2, #2
	ldr r1, _0805637C @ =gBg1XPosition
	ldrh r1, [r1]
	lsrs r1, r1, #2
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x6f
	bhi _08056380
	adds r0, r2, #1
	strh r0, [r3, #4]
	b _0805638C
	.align 2, 0
_08056374: .4byte gCurrentSprite
_08056378: .4byte 0x00000249
_0805637C: .4byte gBg1XPosition
_08056380:
	cmp r0, #0x80
	bls _0805638A
	subs r0, r2, #1
	strh r0, [r3, #4]
	b _0805638C
_0805638A:
	movs r4, #1
_0805638C:
	ldrh r2, [r3, #2]
	lsrs r0, r2, #2
	ldr r1, _080563A8 @ =gBg1YPosition
	ldrh r1, [r1]
	lsrs r1, r1, #2
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x2b
	bhi _080563AC
	adds r0, r2, #1
	strh r0, [r3, #2]
	b _080563BC
	.align 2, 0
_080563A8: .4byte gBg1YPosition
_080563AC:
	cmp r0, #0x3c
	bls _080563B6
	subs r0, r2, #1
	strh r0, [r3, #2]
	b _080563BC
_080563B6:
	adds r0, r4, #1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
_080563BC:
	cmp r4, #1
	bls _080563E0
	adds r1, r3, #0
	adds r1, #0x21
	movs r2, #0
	movs r0, #2
	strb r0, [r1]
	adds r1, #3
	movs r0, #0x17
	strb r0, [r1]
	adds r1, #0xa
	movs r0, #0x3c
	strb r0, [r1]
	adds r0, r3, #0
	adds r0, #0x31
	strb r2, [r0]
	subs r0, #1
	strb r2, [r0]
_080563E0:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start GunshipEndWaitingToEnter
GunshipEndWaitingToEnter: @ 0x080563E8
	push {r4, r5, r6, lr}
	ldr r3, _08056438 @ =gCurrentSprite
	movs r0, #0x31
	adds r0, r0, r3
	mov ip, r0
	ldrb r2, [r0]
	ldr r5, _0805643C @ =0x0839AAE0 (sBlob_39aa34_39f4b0+0xAC)
	lsls r0, r2, #1
	adds r0, r0, r5
	ldrh r4, [r0]
	movs r6, #0
	ldrsh r1, [r0, r6]
	ldr r0, _08056440 @ =0x00007FFF
	cmp r1, r0
	bne _0805640A
	ldrh r4, [r5]
	movs r2, #0
_0805640A:
	adds r0, r2, #1
	mov r1, ip
	strb r0, [r1]
	ldrh r0, [r3, #2]
	adds r0, r0, r4
	strh r0, [r3, #2]
	adds r2, r3, #0
	adds r2, #0x2e
	ldrb r0, [r2]
	subs r0, #1
	strb r0, [r2]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08056432
	adds r0, r3, #0
	adds r0, #0x24
	movs r1, #0x18
	strb r1, [r0]
	movs r0, #0
	strb r0, [r2]
_08056432:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08056438: .4byte gCurrentSprite
_0805643C: .4byte sOmegaMetroidPartOam_LeftLeg_Swiping+0xDC
_08056440: .4byte 0x00007FFF

	thumb_func_start GunshipEndEntering
GunshipEndEntering: @ 0x08056444
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #0xc
	ldr r0, _080564B0 @ =gCurrentSprite
	mov ip, r0
	movs r1, #0x31
	add r1, ip
	mov r8, r1
	ldrb r2, [r1]
	ldr r4, _080564B4 @ =0x0839AAE0 (sBlob_39aa34_39f4b0+0xAC)
	lsls r0, r2, #1
	adds r0, r0, r4
	ldrh r3, [r0]
	movs r5, #0
	ldrsh r1, [r0, r5]
	ldr r0, _080564B8 @ =0x00007FFF
	cmp r1, r0
	bne _0805646E
	ldrh r3, [r4]
	movs r2, #0
_0805646E:
	adds r0, r2, #1
	movs r7, #0
	mov r6, r8
	strb r0, [r6]
	mov r1, ip
	ldrh r0, [r1, #2]
	adds r4, r0, r3
	movs r5, #0
	strh r4, [r1, #2]
	ldr r2, _080564BC @ =0x0839AC90 (sBlob_39aa34_39f4b0+0x25C)
	mov r6, ip
	adds r6, #0x2e
	ldrb r3, [r6]
	lsls r1, r3, #0x18
	lsrs r0, r1, #0x1a
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	mov r2, ip
	strh r0, [r2, #0x12]
	lsrs r1, r1, #0x18
	cmp r1, #0x6f
	bhi _080564C0
	adds r0, r3, #1
	strb r0, [r6]
	movs r1, #1
	ands r0, r1
	cmp r0, #0
	beq _08056576
	adds r0, r4, #1
	strh r0, [r2, #2]
	b _08056576
	.align 2, 0
_080564B0: .4byte gCurrentSprite
_080564B4: .4byte sOmegaMetroidPartOam_LeftLeg_Swiping+0xDC
_080564B8: .4byte 0x00007FFF
_080564BC: .4byte sOmegaMetroidPartOam_LeftLeg_Swiping+0x28C
_080564C0:
	mov r3, ip
	ldrh r1, [r3]
	ldr r0, _08056584 @ =0x0000FFF7
	ands r0, r1
	strh r0, [r3]
	mov r1, ip
	adds r1, #0x24
	movs r0, #0x1a
	strb r0, [r1]
	ldr r0, _08056588 @ =0x0839EB48 (sBlob_39aa34_39f4b0+0x4114)
	str r0, [r3, #0x18]
	strb r5, [r3, #0x1c]
	strh r7, [r3, #0x16]
	mov r0, ip
	adds r0, #0x2f
	strb r5, [r0]
	adds r1, #0x10
	ldrb r0, [r1]
	movs r4, #1
	orrs r0, r4
	strb r0, [r1]
	ldrb r1, [r3, #0x1e]
	ldrb r2, [r3, #0x1f]
	mov r0, ip
	adds r0, #0x23
	ldrb r3, [r0]
	mov r6, ip
	ldrh r0, [r6, #2]
	str r0, [sp]
	ldrh r0, [r6, #4]
	str r0, [sp, #4]
	str r7, [sp, #8]
	movs r0, #0x7a
	bl SpriteSpawnSecondary
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	mov r1, r8
	strb r0, [r1]
	ldr r2, _0805658C @ =gSpriteData
	lsls r1, r0, #3
	subs r1, r1, r0
	lsls r1, r1, #3
	adds r3, r1, r2
	mov ip, r3
	ldrh r3, [r3]
	ldr r0, _08056590 @ =0x0000FFFB
	ands r0, r3
	mov r6, ip
	strh r0, [r6]
	adds r2, #0x18
	adds r1, r1, r2
	ldr r0, _08056594 @ =0x0839EC30 (sBlob_39aa34_39f4b0+0x41FC)
	str r0, [r1]
	strb r5, [r6, #0x1c]
	strh r7, [r6, #0x16]
	mov r1, ip
	adds r1, #0x34
	ldrb r0, [r1]
	orrs r0, r4
	strb r0, [r1]
	subs r1, #0x12
	movs r0, #0xe
	strb r0, [r1]
	mov r0, ip
	adds r0, #0x25
	strb r5, [r0]
	adds r0, #2
	movs r2, #4
	strb r2, [r0]
	adds r1, #6
	movs r0, #0x38
	strb r0, [r1]
	adds r1, #1
	movs r0, #0x30
	strb r0, [r1]
	ldr r0, _08056598 @ =0x0000FFFC
	strh r0, [r6, #0xa]
	strh r2, [r6, #0xc]
	strh r0, [r6, #0xe]
	strh r2, [r6, #0x10]
	subs r1, #5
	movs r0, #2
	strb r0, [r1]
	mov r0, ip
	adds r0, #0x2e
	strb r5, [r0]
	adds r0, #1
	strb r5, [r0]
	adds r0, #1
	strb r5, [r0]
_08056576:
	add sp, #0xc
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08056584: .4byte 0x0000FFF7
_08056588: .4byte sOmegaMetroidPartOam_LeftLeg_Swiping+0x4144
_0805658C: .4byte gSpriteData
_08056590: .4byte 0x0000FFFB
_08056594: .4byte sOmegaMetroidPartOam_LeftLeg_Swiping+0x422C
_08056598: .4byte 0x0000FFFC

	thumb_func_start GunshipEndWaitingForSamus
GunshipEndWaitingForSamus: @ 0x0805659C
	push {r4, r5, lr}
	ldr r4, _080565B4 @ =gCurrentSprite
	adds r1, r4, #0
	adds r1, #0x2f
	ldrb r0, [r1]
	cmp r0, #0x23
	bhi _080565B8
	adds r0, #1
	strb r0, [r1]
	bl GunshipEndSpawnBeams
	b _08056638
	.align 2, 0
_080565B4: .4byte gCurrentSprite
_080565B8:
	ldrh r2, [r4, #4]
	adds r0, r2, #0
	subs r0, #0x20
	ldr r5, _08056624 @ =gSamusData
	ldrh r1, [r5, #0x16]
	cmp r0, r1
	bge _08056630
	adds r0, #0x40
	cmp r0, r1
	ble _08056630
	ldrh r1, [r5, #0x18]
	ldr r0, _08056628 @ =0x000002BF
	cmp r1, r0
	bne _08056630
	bl SpriteUtilCheckSamusMorphed
	adds r1, r0, #0
	cmp r1, #0
	bne _08056630
	ldrb r0, [r5, #5]
	cmp r0, #0
	beq _080565E6
	strb r1, [r5, #5]
_080565E6:
	ldr r1, _0805662C @ =sSamusSetPoseFunctionPointer
	ldrb r0, [r5]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	movs r0, #0x20
	bl _call_via_r1
	movs r1, #0x90
	lsls r1, r1, #1
	adds r0, r1, #0
	ldrh r1, [r4, #2]
	adds r0, r0, r1
	strh r0, [r5, #0x18]
	ldrh r0, [r4, #4]
	strh r0, [r5, #0x16]
	adds r1, r4, #0
	adds r1, #0x24
	movs r0, #0x37
	strb r0, [r1]
	adds r1, #0xa
	movs r0, #0x1e
	strb r0, [r1]
	subs r1, #0xc
	movs r0, #4
	strb r0, [r1]
	movs r0, #0x6d
	bl EventCheckAdvance
	b _08056638
	.align 2, 0
_08056624: .4byte gSamusData
_08056628: .4byte 0x000002BF
_0805662C: .4byte sSamusSetPoseFunctionPointer
_08056630:
	ldr r0, _08056640 @ =gCurrentSprite
	adds r0, #0x22
	movs r1, #0xc
	strb r1, [r0]
_08056638:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08056640: .4byte gCurrentSprite

	thumb_func_start GunshipEndLockingSamus
GunshipEndLockingSamus: @ 0x08056644
	push {lr}
	ldr r1, _08056668 @ =gCurrentSprite
	adds r2, r1, #0
	adds r2, #0x2e
	ldrb r0, [r2]
	subs r0, #1
	strb r0, [r2]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08056664
	adds r0, r1, #0
	adds r0, #0x24
	movs r1, #0x38
	strb r1, [r0]
	movs r0, #0x3b
	strb r0, [r2]
_08056664:
	pop {r0}
	bx r0
	.align 2, 0
_08056668: .4byte gCurrentSprite

	thumb_func_start GunshipEndMovingSamusUp
GunshipEndMovingSamusUp: @ 0x0805666C
	push {lr}
	ldr r1, _08056690 @ =gCurrentSprite
	adds r2, r1, #0
	adds r2, #0x2e
	ldrb r0, [r2]
	subs r0, #1
	strb r0, [r2]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _08056698
	adds r1, #0x24
	movs r0, #0x39
	strb r0, [r1]
	ldr r1, _08056694 @ =gDisableDrawingSamusAndScrollingFlag
	movs r0, #1
	strb r0, [r1]
	b _080566A0
	.align 2, 0
_08056690: .4byte gCurrentSprite
_08056694: .4byte gDisableDrawingSamusAndScrollingFlag
_08056698:
	ldr r1, _080566A4 @ =gSamusData
	ldrh r0, [r1, #0x18]
	subs r0, #4
	strh r0, [r1, #0x18]
_080566A0:
	pop {r0}
	bx r0
	.align 2, 0
_080566A4: .4byte gSamusData

