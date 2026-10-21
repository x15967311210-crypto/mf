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

	thumb_func_start StatusScreenDrawNumber
StatusScreenDrawNumber: @ 0x0807E754
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	str r1, [sp]
	lsls r2, r2, #0x18
	lsrs r2, r2, #0x18
	mov r8, r2
	lsls r3, r3, #0x18
	lsrs r3, r3, #0x18
	mov sl, r3
	ldr r3, _0807E7D0 @ =0x0858217C (sBlob_58217b_58225c+0x1)
	lsls r2, r0, #2
	adds r2, r2, r0
	adds r0, r2, r3
	ldrb r1, [r0]
	lsls r1, r1, #5
	adds r0, r3, #2
	adds r0, r2, r0
	ldrb r4, [r0]
	adds r1, r1, r4
	lsls r1, r1, #1
	ldr r0, _0807E7D4 @ =0x0600C800
	adds r0, r0, r1
	mov sb, r0
	adds r3, #3
	adds r2, r2, r3
	ldrb r0, [r2]
	subs r6, r0, r4
	ldr r1, _0807E7D8 @ =0x08576180 (sPauseDebugNumbersIncrementValues)
	lsls r0, r6, #1
	adds r0, r0, r1
	ldrh r4, [r0]
	adds r6, #1
	movs r7, #0
	movs r5, #0
	cmp r4, #0
	ble _0807E808
_0807E7AC:
	ldr r0, [sp]
	adds r1, r4, #0
	bl __divsi3
	movs r1, #0xa
	bl __modsi3
	adds r2, r0, #0
	cmp r2, #0
	bne _0807E7E0
	cmp r7, #0
	bne _0807E7DC
	movs r2, #0x8c
	mov r3, sl
	cmp r3, #0
	beq _0807E7E4
	b _0807E7F6
	.align 2, 0
_0807E7D0: .4byte sDebugSectionInfo+0x60
_0807E7D4: .4byte 0x0600C800
_0807E7D8: .4byte sPauseDebugNumbersIncrementValues
_0807E7DC:
	movs r2, #0x80
	b _0807E7E8
_0807E7E0:
	movs r7, #1
	adds r2, #0x80
_0807E7E4:
	cmp r2, #0
	beq _0807E7F6
_0807E7E8:
	lsls r1, r5, #1
	add r1, sb
	mov r3, r8
	lsls r0, r3, #0xc
	orrs r0, r2
	strh r0, [r1]
	b _0807E7F8
_0807E7F6:
	subs r5, #1
_0807E7F8:
	adds r0, r4, #0
	movs r1, #0xa
	bl __divsi3
	adds r4, r0, #0
	adds r5, #1
	cmp r4, #0
	bgt _0807E7AC
_0807E808:
	cmp r6, r5
	beq _0807E822
	mov r0, r8
	lsls r2, r0, #0xc
	movs r0, #0x8c
	orrs r2, r0
	lsls r0, r5, #1
	add r0, sb
_0807E818:
	strh r2, [r0]
	adds r0, #2
	adds r5, #1
	cmp r6, r5
	bne _0807E818
_0807E822:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start StatusScreenDrawBeamOrSuit
StatusScreenDrawBeamOrSuit: @ 0x0807E834
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x18
	lsls r0, r0, #0x18
	lsrs r7, r0, #0x18
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	str r1, [sp]
	movs r0, #0
	mov sb, r0
	movs r2, #0
	ldr r0, _0807E964 @ =0x0857617A (sStatusScreenSectionSizes)
	adds r1, r7, r0
	ldrb r1, [r1]
	cmp sb, r1
	bge _0807E8F8
	ldr r1, _0807E968 @ =0x0858217C (sBlob_58217b_58225c+0x1)
	lsls r3, r7, #2
	mov sl, r3
	adds r5, r3, r7
	ldr r0, _0807E96C @ =0x085821B3 (sBlob_58217b_58225c+0x38)
	adds r0, #2
	adds r0, r5, r0
	ldrb r0, [r0]
	str r0, [sp, #8]
	adds r0, r1, #3
	adds r6, r5, r0
	str r6, [sp, #0x14]
	adds r0, r5, r1
	ldrb r0, [r0]
	adds r0, #1
	str r0, [sp, #4]
	adds r1, #2
	adds r1, r5, r1
	ldrb r0, [r1]
	mov r8, r0
	str r5, [sp, #0xc]
	str r1, [sp, #0x10]
_0807E886:
	ldr r1, [sp, #4]
	adds r0, r1, r2
	lsls r0, r0, #5
	add r0, r8
	mov ip, r0
	ldr r3, _0807E96C @ =0x085821B3 (sBlob_58217b_58225c+0x38)
	adds r0, r5, r3
	ldrb r0, [r0]
	adds r0, #1
	adds r0, r0, r2
	lsls r0, r0, #5
	ldr r1, [sp, #8]
	adds r6, r0, r1
	ldr r0, _0807E970 @ =0x0879BEA8 (sUnk_79bea8)
	add r0, sl
	ldr r0, [r0]
	adds r0, r0, r2
	ldrb r0, [r0]
	ldr r3, [sp]
	ands r0, r3
	adds r2, #1
	cmp r0, #0
	beq _0807E8EE
	mov sb, r2
	ldr r1, [sp, #0x14]
	ldrb r0, [r1]
	mov r2, r8
	subs r0, r0, r2
	mov r2, sb
	cmp r0, #0
	blt _0807E8EE
	ldr r3, [sp, #0xc]
	ldr r1, _0807E974 @ =0x0858217F (sBlob_58217b_58225c+0x4)
	adds r0, r3, r1
	ldrb r1, [r0]
	ldr r3, [sp, #0x10]
	ldrb r0, [r3]
	subs r1, r1, r0
	lsls r0, r6, #1
	ldr r6, _0807E978 @ =0x0600C800
	adds r4, r0, r6
	mov r3, ip
	lsls r0, r3, #1
	adds r3, r0, r6
	adds r1, #1
_0807E8E0:
	ldrh r0, [r4]
	strh r0, [r3]
	adds r4, #2
	adds r3, #2
	subs r1, #1
	cmp r1, #0
	bne _0807E8E0
_0807E8EE:
	ldr r6, _0807E964 @ =0x0857617A (sStatusScreenSectionSizes)
	adds r0, r7, r6
	ldrb r0, [r0]
	cmp r2, r0
	blt _0807E886
_0807E8F8:
	mov r0, sb
	cmp r0, #0
	beq _0807E954
	ldr r3, _0807E968 @ =0x0858217C (sBlob_58217b_58225c+0x1)
	lsls r2, r7, #2
	adds r2, r2, r7
	adds r0, r2, r3
	mov r1, sb
	adds r1, #1
	ldrb r0, [r0]
	adds r1, r1, r0
	lsls r1, r1, #5
	adds r0, r3, #2
	adds r0, r2, r0
	ldrb r4, [r0]
	adds r1, r1, r4
	mov ip, r1
	ldr r1, _0807E96C @ =0x085821B3 (sBlob_58217b_58225c+0x38)
	adds r0, r1, #1
	adds r0, r2, r0
	ldrb r0, [r0]
	adds r1, #2
	adds r1, r2, r1
	lsls r0, r0, #5
	ldrb r1, [r1]
	adds r6, r0, r1
	adds r3, #3
	adds r2, r2, r3
	ldrb r0, [r2]
	subs r1, r0, r4
	cmp r1, #0
	blt _0807E954
	lsls r0, r6, #1
	ldr r2, _0807E978 @ =0x0600C800
	adds r4, r0, r2
	mov r3, ip
	lsls r0, r3, #1
	adds r3, r0, r2
	adds r1, #1
_0807E946:
	ldrh r0, [r4]
	strh r0, [r3]
	adds r4, #2
	adds r3, #2
	subs r1, #1
	cmp r1, #0
	bne _0807E946
_0807E954:
	add sp, #0x18
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807E964: .4byte sStatusScreenSectionSizes
_0807E968: .4byte sDebugSectionInfo+0x60
_0807E96C: .4byte sDebugSectionInfo+0x97
_0807E970: .4byte sExploredMinimapBitFlags+0xCC
_0807E974: .4byte sDebugSectionInfo+0x63
_0807E978: .4byte 0x0600C800

	thumb_func_start StatusScreenDrawMissileOrBomb
StatusScreenDrawMissileOrBomb: @ 0x0807E97C
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x18
	lsls r0, r0, #0x18
	lsrs r7, r0, #0x18
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	str r1, [sp]
	movs r0, #1
	rsbs r0, r0, #0
	str r0, [sp, #4]
	movs r2, #0
	ldr r0, _0807EA30 @ =0x0857617A (sStatusScreenSectionSizes)
	adds r1, r7, r0
	ldrb r1, [r1]
	cmp r2, r1
	bge _0807EA5C
	ldr r1, _0807EA34 @ =0x0858217C (sBlob_58217b_58225c+0x1)
	lsls r3, r7, #2
	mov sl, r3
	adds r5, r3, r7
	ldr r0, _0807EA38 @ =0x085821B3 (sBlob_58217b_58225c+0x38)
	adds r0, #2
	adds r0, r5, r0
	ldrb r0, [r0]
	str r0, [sp, #8]
	adds r0, r1, #3
	adds r0, r5, r0
	str r0, [sp, #0x14]
	adds r0, r5, r1
	ldrb r0, [r0]
	adds r1, #2
	adds r1, r5, r1
	ldrb r6, [r1]
	mov sb, r6
	str r5, [sp, #0xc]
	str r1, [sp, #0x10]
	lsls r0, r0, #5
	mov ip, r0
_0807E9D0:
	mov r0, ip
	add r0, sb
	mov r8, r0
	ldr r1, _0807EA38 @ =0x085821B3 (sBlob_58217b_58225c+0x38)
	adds r0, r5, r1
	ldrb r0, [r0]
	adds r0, r0, r2
	lsls r0, r0, #5
	ldr r3, [sp, #8]
	adds r6, r0, r3
	ldr r0, _0807EA3C @ =0x0879BEA8 (sUnk_79bea8)
	add r0, sl
	ldr r0, [r0]
	adds r0, r0, r2
	ldrb r0, [r0]
	ldr r1, [sp]
	ands r0, r1
	cmp r0, #0
	beq _0807EA48
	str r2, [sp, #4]
	ldr r3, [sp, #0x14]
	ldrb r0, [r3]
	mov r1, sb
	subs r0, r0, r1
	cmp r0, #0
	blt _0807EA4C
	ldr r0, _0807EA40 @ =0x0858217F (sBlob_58217b_58225c+0x4)
	ldr r3, [sp, #0xc]
	adds r0, r3, r0
	ldrb r1, [r0]
	ldr r3, [sp, #0x10]
	ldrb r0, [r3]
	subs r1, r1, r0
	lsls r0, r6, #1
	ldr r6, _0807EA44 @ =0x0600C800
	adds r4, r0, r6
	mov r3, r8
	lsls r0, r3, #1
	adds r3, r0, r6
	adds r1, #1
_0807EA20:
	ldrh r0, [r4]
	strh r0, [r3]
	adds r4, #2
	adds r3, #2
	subs r1, #1
	cmp r1, #0
	bne _0807EA20
	b _0807EA4C
	.align 2, 0
_0807EA30: .4byte sStatusScreenSectionSizes
_0807EA34: .4byte sDebugSectionInfo+0x60
_0807EA38: .4byte sDebugSectionInfo+0x97
_0807EA3C: .4byte sExploredMinimapBitFlags+0xCC
_0807EA40: .4byte sDebugSectionInfo+0x63
_0807EA44: .4byte 0x0600C800
_0807EA48:
	cmp r2, #0
	beq _0807EAB8
_0807EA4C:
	movs r6, #0x20
	add ip, r6
	adds r2, #1
	ldr r1, _0807EAC8 @ =0x0857617A (sStatusScreenSectionSizes)
	adds r0, r7, r1
	ldrb r0, [r0]
	cmp r2, r0
	blt _0807E9D0
_0807EA5C:
	ldr r2, [sp, #4]
	cmp r2, #0
	blt _0807EAB8
	ldr r3, _0807EACC @ =0x0858217C (sBlob_58217b_58225c+0x1)
	lsls r2, r7, #2
	adds r2, r2, r7
	adds r0, r2, r3
	ldr r1, [sp, #4]
	adds r1, #1
	ldrb r0, [r0]
	adds r1, r1, r0
	lsls r1, r1, #5
	adds r0, r3, #2
	adds r0, r2, r0
	ldrb r4, [r0]
	adds r1, r1, r4
	mov r8, r1
	ldr r1, _0807EAD0 @ =0x085821B3 (sBlob_58217b_58225c+0x38)
	adds r0, r1, #1
	adds r0, r2, r0
	ldrb r0, [r0]
	adds r1, #2
	adds r1, r2, r1
	lsls r0, r0, #5
	ldrb r1, [r1]
	adds r6, r0, r1
	adds r3, #3
	adds r2, r2, r3
	ldrb r0, [r2]
	subs r1, r0, r4
	cmp r1, #0
	blt _0807EAB8
	lsls r0, r6, #1
	ldr r3, _0807EAD4 @ =0x0600C800
	adds r4, r0, r3
	mov r6, r8
	lsls r0, r6, #1
	adds r3, r0, r3
	adds r1, #1
_0807EAAA:
	ldrh r0, [r4]
	strh r0, [r3]
	adds r4, #2
	adds r3, #2
	subs r1, #1
	cmp r1, #0
	bne _0807EAAA
_0807EAB8:
	add sp, #0x18
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807EAC8: .4byte sStatusScreenSectionSizes
_0807EACC: .4byte sDebugSectionInfo+0x60
_0807EAD0: .4byte sDebugSectionInfo+0x97
_0807EAD4: .4byte 0x0600C800

	thumb_func_start StatusScreenDrawMisc
StatusScreenDrawMisc: @ 0x0807EAD8
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x24
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	mov r8, r0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	str r1, [sp]
	movs r0, #0
	str r0, [sp, #4]
	movs r4, #0
	ldr r0, _0807EBF8 @ =0x0857617A (sStatusScreenSectionSizes)
	mov r2, r8
	adds r1, r2, r0
	ldrb r1, [r1]
	cmp r4, r1
	bge _0807EB9C
	ldr r1, _0807EBFC @ =0x0858217C (sBlob_58217b_58225c+0x1)
	lsls r2, r2, #2
	mov sb, r2
	add r2, r8
	ldr r3, _0807EC00 @ =0x085821B3 (sBlob_58217b_58225c+0x38)
	mov sl, r3
	mov r0, sl
	adds r0, #2
	adds r0, r2, r0
	ldrb r0, [r0]
	str r0, [sp, #0xc]
	adds r0, r1, #3
	adds r6, r2, r0
	str r6, [sp, #0x1c]
	adds r0, r2, r1
	ldrb r0, [r0]
	adds r0, #1
	str r0, [sp, #8]
	adds r1, #2
	adds r1, r2, r1
	ldrb r7, [r1]
	str r2, [sp, #0x10]
	mov ip, r1
_0807EB30:
	ldr r1, [sp, #8]
	adds r0, r1, r4
	lsls r0, r0, #5
	adds r6, r0, r7
	mov r3, sl
	adds r0, r2, r3
	ldrb r0, [r0]
	adds r0, #1
	adds r0, r0, r4
	lsls r0, r0, #5
	ldr r1, [sp, #0xc]
	adds r3, r0, r1
	ldr r0, _0807EC04 @ =0x0879BEA8 (sUnk_79bea8)
	add r0, sb
	ldr r0, [r0]
	adds r0, r0, r4
	ldrb r0, [r0]
	ldr r1, [sp]
	ands r0, r1
	adds r5, r4, #1
	cmp r0, #0
	beq _0807EB90
	str r5, [sp, #4]
	ldr r4, [sp, #0x1c]
	ldrb r0, [r4]
	subs r0, r0, r7
	cmp r0, #0
	blt _0807EB90
	ldr r1, [sp, #0x10]
	ldr r4, _0807EC08 @ =0x0858217F (sBlob_58217b_58225c+0x4)
	adds r0, r1, r4
	ldrb r1, [r0]
	mov r4, ip
	ldrb r0, [r4]
	subs r1, r1, r0
	lsls r0, r3, #1
	ldr r3, _0807EC0C @ =0x0600C800
	adds r4, r0, r3
	lsls r0, r6, #1
	adds r3, r0, r3
	adds r1, #1
_0807EB82:
	ldrh r0, [r4]
	strh r0, [r3]
	adds r4, #2
	adds r3, #2
	subs r1, #1
	cmp r1, #0
	bne _0807EB82
_0807EB90:
	adds r4, r5, #0
	ldr r0, _0807EBF8 @ =0x0857617A (sStatusScreenSectionSizes)
	add r0, r8
	ldrb r0, [r0]
	cmp r4, r0
	blt _0807EB30
_0807EB9C:
	ldr r4, [sp, #4]
	cmp r4, #0
	beq _0807EC6C
	movs r4, #0
	ldr r1, _0807EBFC @ =0x0858217C (sBlob_58217b_58225c+0x1)
	mov r6, r8
	lsls r6, r6, #2
	str r6, [sp, #0x14]
	adds r7, r6, #0
	add r7, r8
	adds r2, r1, #2
	adds r0, r7, r2
	mov ip, r0
	ldr r0, _0807EC00 @ =0x085821B3 (sBlob_58217b_58225c+0x38)
	adds r0, #2
	adds r0, r0, r7
	mov sl, r0
	adds r2, r7, r1
	mov sb, r2
	ldr r0, _0807EC00 @ =0x085821B3 (sBlob_58217b_58225c+0x38)
	adds r0, #1
	adds r0, r7, r0
	str r0, [sp, #0x18]
	ldr r3, _0807EC08 @ =0x0858217F (sBlob_58217b_58225c+0x4)
	adds r3, r7, r3
	str r3, [sp, #0x20]
_0807EBD0:
	cmp r4, #0
	bne _0807EC10
	ldr r6, [sp, #4]
	adds r6, #1
	str r6, [sp, #4]
	mov r1, sb
	ldrb r0, [r1]
	adds r0, r0, r6
	lsls r0, r0, #5
	mov r2, ip
	ldrb r2, [r2]
	adds r6, r0, r2
	ldr r3, [sp, #0x18]
	ldrb r0, [r3]
	lsls r0, r0, #5
	mov r1, sl
	ldrb r1, [r1]
	adds r3, r0, r1
	b _0807EC2A
	.align 2, 0
_0807EBF8: .4byte sStatusScreenSectionSizes
_0807EBFC: .4byte sDebugSectionInfo+0x60
_0807EC00: .4byte sDebugSectionInfo+0x97
_0807EC04: .4byte sExploredMinimapBitFlags+0xCC
_0807EC08: .4byte sDebugSectionInfo+0x63
_0807EC0C: .4byte 0x0600C800
_0807EC10:
	mov r2, sb
	ldrb r0, [r2]
	lsls r0, r0, #5
	mov r3, ip
	ldrb r3, [r3]
	adds r6, r0, r3
	ldr r1, _0807EC7C @ =0x085821B3 (sBlob_58217b_58225c+0x38)
	adds r0, r7, r1
	ldrb r0, [r0]
	lsls r0, r0, #5
	mov r2, sl
	ldrb r2, [r2]
	adds r3, r0, r2
_0807EC2A:
	ldr r0, [sp, #0x20]
	ldrb r1, [r0]
	mov r2, ip
	ldrb r0, [r2]
	subs r1, r1, r0
	adds r5, r4, #1
	cmp r1, #0
	blt _0807EC66
	ldr r1, [sp, #0x14]
	add r1, r8
	ldr r4, _0807EC80 @ =0x0858217F (sBlob_58217b_58225c+0x4)
	adds r0, r1, r4
	ldrb r2, [r0]
	ldr r0, _0807EC84 @ =0x0858217E (sBlob_58217b_58225c+0x3)
	adds r1, r1, r0
	ldrb r0, [r1]
	subs r2, r2, r0
	lsls r0, r3, #1
	ldr r1, _0807EC88 @ =0x0600C800
	adds r4, r0, r1
	lsls r0, r6, #1
	adds r3, r0, r1
	adds r1, r2, #1
_0807EC58:
	ldrh r0, [r4]
	strh r0, [r3]
	adds r4, #2
	adds r3, #2
	subs r1, #1
	cmp r1, #0
	bne _0807EC58
_0807EC66:
	adds r4, r5, #0
	cmp r4, #1
	ble _0807EBD0
_0807EC6C:
	add sp, #0x24
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807EC7C: .4byte sDebugSectionInfo+0x97
_0807EC80: .4byte sDebugSectionInfo+0x63
_0807EC84: .4byte sDebugSectionInfo+0x62
_0807EC88: .4byte 0x0600C800

	thumb_func_start StatusScreenRemoveAmmoHeader
StatusScreenRemoveAmmoHeader: @ 0x0807EC8C
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _0807ECA2
	movs r1, #1
	b _0807ECA8
_0807ECA2:
	cmp r0, #2
	bne _0807ED0A
	movs r1, #2
_0807ECA8:
	ldr r0, _0807ED18 @ =0x0600C800
	mov r8, r0
	movs r3, #0
	lsls r1, r1, #2
	ldr r5, _0807ED1C @ =0x085821D6 (sBlob_58217b_58225c+0x5B)
	adds r0, r1, r5
	ldrb r0, [r0]
	mov sl, r0
	ldrb r7, [r5, #2]
	ldrb r0, [r5, #3]
	subs r0, r0, r7
	mov sb, r0
	adds r0, r5, #2
	adds r1, r1, r0
	ldrb r1, [r1]
	mov ip, r1
_0807ECC8:
	mov r1, sl
	adds r0, r1, r3
	lsls r0, r0, #5
	mov r2, ip
	adds r4, r0, r2
	ldrb r0, [r5]
	adds r0, r0, r3
	lsls r0, r0, #5
	adds r2, r0, r7
	adds r6, r3, #1
	mov r0, sb
	cmp r0, #0
	blt _0807ED04
	ldrb r1, [r5, #3]
	ldrb r0, [r5, #2]
	subs r1, r1, r0
	lsls r0, r2, #1
	ldr r2, _0807ED18 @ =0x0600C800
	adds r3, r0, r2
	lsls r0, r4, #1
	mov r4, r8
	adds r2, r0, r4
	adds r1, #1
_0807ECF6:
	ldrh r0, [r3]
	strh r0, [r2]
	adds r3, #2
	adds r2, #2
	subs r1, #1
	cmp r1, #0
	bne _0807ECF6
_0807ED04:
	adds r3, r6, #0
	cmp r3, #1
	ble _0807ECC8
_0807ED0A:
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807ED18: .4byte 0x0600C800
_0807ED1C: .4byte sDebugSectionInfo+0xBA

	thumb_func_start EasySleepMenuHandler
EasySleepMenuHandler: @ 0x0807ED20
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	movs r7, #0
	ldr r0, _0807ED40 @ =gNonGameplayRam
	ldrb r1, [r0, #7]
	adds r3, r0, #0
	cmp r1, #5
	bls _0807ED36
	b _0807EE82
_0807ED36:
	lsls r0, r1, #2
	ldr r1, _0807ED44 @ =_0807ED48
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807ED40: .4byte gNonGameplayRam
_0807ED44: .4byte _0807ED48
_0807ED48: @ jump table
	.4byte _0807ED60 @ case 0
	.4byte _0807ED90 @ case 1
	.4byte _0807EDE4 @ case 2
	.4byte _0807EDFE @ case 3
	.4byte _0807EE12 @ case 4
	.4byte _0807EE78 @ case 5
_0807ED60:
	ldr r0, _0807ED78 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _0807ED80
	ldr r0, _0807ED7C @ =0x000001FB
	bl SoundPlay
	movs r7, #1
	b _0807EE86
	.align 2, 0
_0807ED78: .4byte gChangedInput
_0807ED7C: .4byte 0x000001FB
_0807ED80:
	movs r0, #0x20
	ands r0, r1
	cmp r0, #0
	beq _0807EDD4
	movs r0, #1
	strb r0, [r3, #7]
	movs r0, #0x3c
	b _0807EDC8
_0807ED90:
	ldr r0, _0807EDB0 @ =gChangedInput
	ldrh r1, [r0]
	movs r2, #1
	ands r2, r1
	cmp r2, #0
	beq _0807EDBC
	ldr r0, _0807EDB4 @ =0x000001FB
	bl SoundPlay
	ldr r1, _0807EDB8 @ =gNonGameplayRam
	movs r2, #0
	movs r0, #2
	strb r0, [r1, #7]
	strb r2, [r1, #6]
	b _0807EE82
	.align 2, 0
_0807EDB0: .4byte gChangedInput
_0807EDB4: .4byte 0x000001FB
_0807EDB8: .4byte gNonGameplayRam
_0807EDBC:
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0807EDD4
	strb r2, [r3, #7]
	movs r0, #0x8c
_0807EDC8:
	strh r0, [r3, #0x3a]
	movs r0, #0xfd
	lsls r0, r0, #1
	bl SoundPlay
	b _0807EE82
_0807EDD4:
	ldr r0, _0807EDE0 @ =0x00000302
	ands r0, r1
	cmp r0, #0
	beq _0807EE82
	movs r7, #1
	b _0807EE86
	.align 2, 0
_0807EDE0: .4byte 0x00000302
_0807EDE4:
	ldrb r0, [r3, #6]
	adds r0, #1
	strb r0, [r3, #6]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x1e
	bls _0807EE82
	ldrb r0, [r3, #7]
	adds r0, #1
	strb r0, [r3, #7]
	movs r0, #0
	strb r0, [r3, #6]
	b _0807EE82
_0807EDFE:
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r3, r0
	ldrh r0, [r2]
	movs r1, #0x80
	eors r0, r1
	strh r0, [r2]
	ldrb r0, [r3, #7]
	adds r0, #1
	b _0807EE80
_0807EE12:
	ldr r1, _0807EE64 @ =0x04000132
	ldr r2, _0807EE68 @ =0x0000C304
	adds r0, r2, #0
	strh r0, [r1]
	ldr r6, _0807EE6C @ =0x04000208
	movs r0, #0
	mov sb, r0
	strh r0, [r6]
	ldr r5, _0807EE70 @ =0x04000200
	ldrh r4, [r5]
	movs r1, #0xc0
	lsls r1, r1, #6
	adds r0, r1, #0
	strh r0, [r5]
	movs r2, #1
	mov r8, r2
	strh r2, [r6]
	bl SoundBias0
	svc #3
	bl SoundBias1
	mov r0, sb
	strh r0, [r6]
	strh r4, [r5]
	mov r1, r8
	strh r1, [r6]
	ldr r2, _0807EE74 @ =gNonGameplayRam
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r3, r2, r0
	ldrh r0, [r3]
	movs r1, #0x80
	eors r0, r1
	strh r0, [r3]
	movs r0, #0x8c
	strh r0, [r2, #0x3a]
	ldrb r0, [r2, #7]
	adds r0, #1
	strb r0, [r2, #7]
	b _0807EE82
	.align 2, 0
_0807EE64: .4byte 0x04000132
_0807EE68: .4byte 0x0000C304
_0807EE6C: .4byte 0x04000208
_0807EE70: .4byte 0x04000200
_0807EE74: .4byte gNonGameplayRam
_0807EE78:
	ldr r0, _0807EE9C @ =gButtonInput
	ldrh r0, [r0]
	cmp r0, #0
	bne _0807EE82
_0807EE80:
	strb r0, [r3, #7]
_0807EE82:
	cmp r7, #0
	beq _0807EE8E
_0807EE86:
	ldr r1, _0807EEA0 @ =gNonGameplayRam
	movs r0, #0
	strb r0, [r1, #7]
	strb r0, [r1, #6]
_0807EE8E:
	adds r0, r7, #0
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0807EE9C: .4byte gButtonInput
_0807EEA0: .4byte gNonGameplayRam

