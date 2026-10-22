    .include "asm/macros.inc"

    .syntax unified


	thumb_func_start SramWrite_MostRecentSaveFile
SramWrite_MostRecentSaveFile: @ 0x08080068
	push {r4, r5, lr}
	ldr r5, _080800E4 @ =0x0203F000
	adds r3, r5, #0
	movs r1, #0
	movs r0, #0x1e
	strb r0, [r5]
	ldrb r0, [r5, #1]
	adds r0, #1
	strb r0, [r5, #1]
	strh r1, [r5, #2]
	ldr r0, _080800E8 @ =0x0000FFFF
	strh r0, [r5, #4]
	ldr r0, _080800EC @ =0x03000B8D
	ldrb r0, [r0]
	strb r0, [r5, #0x16]
	ldr r2, _080800F0 @ =0x08582288 (sBlob_582288_58b3cc)
	adds r1, r5, #6
	movs r4, #0xf
_0808008C:
	ldrb r0, [r2]
	strb r0, [r1]
	ldrb r0, [r2, #0x10]
	strb r0, [r1, #0x11]
	adds r2, #1
	adds r1, #1
	subs r4, #1
	cmp r4, #0
	bge _0808008C
	movs r1, #0
	movs r4, #7
_080800A2:
	ldrh r0, [r3]
	adds r0, r1, r0
	lsls r0, r0, #0x10
	adds r3, #2
	lsrs r0, r0, #0x10
	ldrh r1, [r3]
	adds r0, r0, r1
	lsls r0, r0, #0x10
	adds r3, #2
	lsrs r0, r0, #0x10
	ldrh r2, [r3]
	adds r0, r0, r2
	lsls r0, r0, #0x10
	adds r3, #2
	lsrs r0, r0, #0x10
	ldrh r1, [r3]
	adds r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	adds r3, #2
	subs r4, #1
	cmp r4, #0
	bge _080800A2
	strh r1, [r5, #2]
	ldr r2, _080800E8 @ =0x0000FFFF
	adds r0, r2, #0
	subs r0, r0, r1
	strh r0, [r5, #4]
	bl unk_dd4
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080800E4: .4byte 0x0203F000
_080800E8: .4byte 0x0000FFFF
_080800EC: .4byte 0x03000B8D
_080800F0: .4byte sUnk_582280+0x8

	thumb_func_start SramRead_MostRecentSaveFile
SramRead_MostRecentSaveFile: @ 0x080800F4
	push {r4, r5, r6, lr}
	sub sp, #4
	ldr r0, _08080194 @ =0x0203F000
	mov ip, r0
	ldrb r0, [r0]
	movs r1, #0x1e
	eors r0, r1
	rsbs r1, r0, #0
	orrs r1, r0
	lsrs r4, r1, #0x1f
	ldr r6, _08080198 @ =0x03000B8D
	cmp r4, #0
	bne _080801A0
	mov r1, ip
	movs r3, #0
	ldrh r5, [r1, #2]
	movs r2, #7
_08080116:
	ldrh r0, [r1]
	adds r0, r3, r0
	lsls r0, r0, #0x10
	adds r1, #2
	lsrs r0, r0, #0x10
	ldrh r3, [r1]
	adds r0, r0, r3
	lsls r0, r0, #0x10
	adds r1, #2
	lsrs r0, r0, #0x10
	ldrh r3, [r1]
	adds r0, r0, r3
	lsls r0, r0, #0x10
	adds r1, #2
	lsrs r0, r0, #0x10
	ldrh r3, [r1]
	adds r0, r0, r3
	lsls r0, r0, #0x10
	lsrs r3, r0, #0x10
	adds r1, #2
	subs r2, #1
	cmp r2, #0
	bge _08080116
	cmp r5, r3
	beq _0808014A
	movs r4, #2
_0808014A:
	cmp r4, #0
	bne _080801A0
	movs r2, #0
	ldr r0, _0808019C @ =0x08582288 (sBlob_582288_58b3cc)
	mov r3, ip
	ldrb r1, [r3, #6]
	adds r3, r0, #0
	ldrb r0, [r3]
	cmp r1, r0
	bne _080801A0
_0808015E:
	mov r0, ip
	adds r0, #0x17
	adds r0, r0, r2
	adds r1, r3, #0
	adds r1, #0x10
	adds r1, r2, r1
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	bne _080801A0
	adds r2, #1
	cmp r2, #0xf
	bgt _0808018A
	mov r0, ip
	adds r0, #6
	adds r0, r0, r2
	adds r1, r2, r3
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	beq _0808015E
	movs r4, #3
_0808018A:
	cmp r4, #0
	bne _080801A0
	mov r1, ip
	ldrb r0, [r1, #0x16]
	b _080801BA
	.align 2, 0
_08080194: .4byte 0x0203F000
_08080198: .4byte 0x03000B8D
_0808019C: .4byte sUnk_582280+0x8
_080801A0:
	mov r1, sp
	ldr r2, _080801C4 @ =0x0000FFFF
	adds r0, r2, #0
	strh r0, [r1]
	ldr r1, _080801C8 @ =0x040000D4
	mov r3, sp
	str r3, [r1]
	ldr r0, _080801CC @ =0x0203F000
	str r0, [r1, #4]
	ldr r0, _080801D0 @ =0x81000020
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r0, #0
_080801BA:
	strb r0, [r6]
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080801C4: .4byte 0x0000FFFF
_080801C8: .4byte 0x040000D4
_080801CC: .4byte 0x0203F000
_080801D0: .4byte 0x81000020

	thumb_func_start SramWrite_Language
SramWrite_Language: @ 0x080801D4
	push {r4, r5, lr}
	ldr r5, _08080254 @ =0x0203F040
	adds r3, r5, #0
	movs r1, #0
	movs r0, #0x1f
	strb r0, [r5]
	ldrb r0, [r5, #1]
	adds r0, #1
	strb r0, [r5, #1]
	strh r1, [r5, #2]
	ldr r0, _08080258 @ =0x0000FFFF
	strh r0, [r5, #4]
	ldr r0, _0808025C @ =0x03000011
	ldrb r0, [r0]
	strb r0, [r5, #0x16]
	ldr r2, _08080260 @ =0x085822A8 (sBlob_582288_58b3cc+0x20)
	adds r1, r5, #6
	movs r4, #0xf
_080801F8:
	ldrb r0, [r2]
	strb r0, [r1]
	ldrb r0, [r2, #0x10]
	strb r0, [r1, #0x11]
	adds r2, #1
	adds r1, #1
	subs r4, #1
	cmp r4, #0
	bge _080801F8
	movs r1, #0
	movs r4, #7
_0808020E:
	ldrh r0, [r3]
	adds r0, r1, r0
	lsls r0, r0, #0x10
	adds r3, #2
	lsrs r0, r0, #0x10
	ldrh r1, [r3]
	adds r0, r0, r1
	lsls r0, r0, #0x10
	adds r3, #2
	lsrs r0, r0, #0x10
	ldrh r2, [r3]
	adds r0, r0, r2
	lsls r0, r0, #0x10
	adds r3, #2
	lsrs r0, r0, #0x10
	ldrh r1, [r3]
	adds r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	adds r3, #2
	subs r4, #1
	cmp r4, #0
	bge _0808020E
	strh r1, [r5, #2]
	ldr r2, _08080258 @ =0x0000FFFF
	adds r0, r2, #0
	subs r0, r0, r1
	strh r0, [r5, #4]
	movs r0, #0
	bl unk_dec
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08080254: .4byte 0x0203F040
_08080258: .4byte 0x0000FFFF
_0808025C: .4byte 0x03000011
_08080260: .4byte sUnk_582280+0x28

	thumb_func_start SramRead_Language
SramRead_Language: @ 0x08080264
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	movs r0, #0
	mov r8, r0
	ldr r1, _080802E8 @ =0x08582280 (sUnk_582280)
	mov sb, r1
	ldr r6, _080802EC @ =0x040000D4
	ldr r2, _080802F0 @ =0x81000020
	mov sl, r2
_0808027E:
	mov r1, r8
	lsls r0, r1, #2
	add r0, sb
	ldr r5, [r0]
	adds r2, r5, #0
	ldrb r1, [r5]
	movs r0, #0x1f
	eors r1, r0
	rsbs r0, r1, #0
	orrs r0, r1
	lsrs r4, r0, #0x1f
	cmp r4, #0
	bne _08080326
	movs r1, #0
	ldrh r7, [r5, #2]
	movs r3, #7
_0808029E:
	ldrh r0, [r2]
	adds r0, r1, r0
	lsls r0, r0, #0x10
	adds r2, #2
	lsrs r0, r0, #0x10
	ldrh r1, [r2]
	adds r0, r0, r1
	lsls r0, r0, #0x10
	adds r2, #2
	lsrs r0, r0, #0x10
	ldrh r1, [r2]
	adds r0, r0, r1
	lsls r0, r0, #0x10
	adds r2, #2
	lsrs r0, r0, #0x10
	ldrh r1, [r2]
	adds r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	adds r2, #2
	subs r3, #1
	cmp r3, #0
	bge _0808029E
	cmp r7, r1
	beq _080802D2
	movs r4, #2
_080802D2:
	cmp r4, #0
	bne _08080326
	movs r3, #0
	ldr r0, _080802F4 @ =0x085822A8 (sBlob_582288_58b3cc+0x20)
	ldrb r1, [r5, #6]
	adds r2, r0, #0
	ldrb r0, [r2]
	cmp r1, r0
	beq _080802FC
	b _08080324
	.align 2, 0
_080802E8: .4byte sUnk_582280
_080802EC: .4byte 0x040000D4
_080802F0: .4byte 0x81000020
_080802F4: .4byte sUnk_582280+0x28
_080802F8:
	movs r4, #4
	b _08080326
_080802FC:
	adds r0, r5, #0
	adds r0, #0x17
	adds r0, r0, r3
	adds r1, r2, #0
	adds r1, #0x10
	adds r1, r3, r1
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	bne _080802F8
	adds r3, #1
	cmp r3, #0xf
	bgt _08080326
	adds r0, r5, #6
	adds r0, r0, r3
	adds r1, r3, r2
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	beq _080802FC
_08080324:
	movs r4, #3
_08080326:
	mov r1, r8
	cmp r1, #0
	bne _0808034C
	cmp r4, #0
	bne _08080384
	mov r2, sb
	ldr r0, [r2]
	str r0, [r6]
	ldr r0, [r2, #4]
	str r0, [r6, #4]
	ldr r0, _08080348 @ =0x80000020
	str r0, [r6, #8]
	ldr r0, [r6, #8]
	movs r0, #1
	bl unk_dec
	b _08080390
	.align 2, 0
_08080348: .4byte 0x80000020
_0808034C:
	cmp r4, #0
	beq _080803A0
	mov r0, sp
	movs r1, #0
	strh r1, [r0]
	str r0, [r6]
	mov r2, sb
	ldr r0, [r2]
	str r0, [r6, #4]
	mov r0, sl
	str r0, [r6, #8]
	ldr r0, [r6, #8]
	movs r0, #0
	bl unk_dec
	mov r0, sp
	movs r1, #0
	strh r1, [r0]
	str r0, [r6]
	mov r2, sb
	ldr r0, [r2, #4]
	str r0, [r6, #4]
	mov r0, sl
	str r0, [r6, #8]
	ldr r0, [r6, #8]
	movs r0, #1
	bl unk_dec
_08080384:
	movs r1, #1
	add r8, r1
	mov r2, r8
	cmp r2, #1
	bgt _08080390
	b _0808027E
_08080390:
	cmp r4, #0
	bne _080803C8
	ldr r1, _0808039C @ =0x03000011
	ldrb r0, [r5, #0x16]
	b _080803CC
	.align 2, 0
_0808039C: .4byte 0x03000011
_080803A0:
	ldr r1, _080803BC @ =0x040000D4
	ldr r2, _080803C0 @ =0x08582280 (sUnk_582280)
	ldr r0, [r2, #4]
	str r0, [r1]
	ldr r0, [r2]
	str r0, [r1, #4]
	ldr r0, _080803C4 @ =0x80000020
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r0, #0
	bl unk_dec
	b _08080390
	.align 2, 0
_080803BC: .4byte 0x040000D4
_080803C0: .4byte sUnk_582280
_080803C4: .4byte 0x80000020
_080803C8:
	ldr r1, _080803E0 @ =0x03000011
	movs r0, #0
_080803CC:
	strb r0, [r1]
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080803E0: .4byte 0x03000011

	thumb_func_start Sram_InitSaveFile
Sram_InitSaveFile: @ 0x080803E4
	push {r4, r5, r6, lr}
	sub sp, #4
	ldr r2, _080804C8 @ =0x02037C00
	movs r3, #0xe0
	lsls r3, r3, #2
	movs r4, #0x10
	str r4, [sp]
	movs r0, #3
	movs r1, #0
	bl BitFill
	ldr r5, _080804CC @ =0x0000FFFF
	ldr r2, _080804D0 @ =0x02036000
	movs r3, #0x90
	lsls r3, r3, #5
	str r4, [sp]
	movs r0, #3
	adds r1, r5, #0
	bl BitFill
	ldr r2, _080804D4 @ =0x02037200
	movs r3, #0x90
	lsls r3, r3, #4
	str r4, [sp]
	movs r0, #3
	adds r1, r5, #0
	bl BitFill
	movs r1, #0
	ldr r4, _080804D8 @ =0x03000033
	movs r2, #0
	ldr r3, _080804DC @ =0x0300003B
_08080424:
	adds r0, r1, r4
	strb r2, [r0]
	adds r0, r1, r3
	strb r2, [r0]
	adds r1, #1
	cmp r1, #7
	ble _08080424
	ldr r1, _080804E0 @ =gInGameTimer
	ldr r0, _080804E4 @ =0x085822D4 (sBlob_582288_58b3cc+0x4C)
	ldr r0, [r0]
	str r0, [r1]
	ldr r1, _080804E8 @ =gDisableDrawingSamusAndScrollingFlag
	movs r0, #1
	strb r0, [r1]
	movs r0, #0
	bl EventSet
	ldr r0, _080804EC @ =gPreviousNavigationConversation
	movs r3, #0xff
	strb r3, [r0]
	ldr r0, _080804F0 @ =gPreviousSoundEvent
	movs r1, #0xff
	strh r1, [r0]
	ldr r2, _080804F4 @ =gEquipment
	ldrb r0, [r2, #0xd]
	orrs r0, r3
	strb r0, [r2, #0xd]
	ldr r0, _080804F8 @ =gSecurityHatchLevel
	strb r1, [r0]
	ldr r0, _080804FC @ =gSecurityHatchLevelBackup
	strb r1, [r0]
	movs r1, #0
	strb r1, [r2, #0xe]
	ldr r0, _08080500 @ =gAbilityCount
	strb r1, [r0]
	ldr r0, _08080504 @ =gCurrentArea
	strb r1, [r0]
	ldr r0, _08080508 @ =gPreviousArea
	strb r1, [r0]
	ldr r0, _0808050C @ =gCurrentRoom
	strb r1, [r0]
	ldr r0, _08080510 @ =gLastDoorUsed
	strb r1, [r0]
	ldr r0, _08080514 @ =0x0300004C
	strb r1, [r0]
	ldr r0, _08080518 @ =0x0300004D
	strb r1, [r0]
	ldr r0, _0808051C @ =0x0879B894 (sAreaDoorPointers)
	ldr r2, [r0]
	ldrb r0, [r2, #2]
	movs r6, #7
	ldrsb r6, [r2, r6]
	ldr r3, _08080520 @ =gPreviousXPosition
	ldr r4, _08080524 @ =gSamusData
	lsls r1, r0, #6
	adds r0, r6, #0
	adds r0, #8
	lsls r0, r0, #2
	adds r1, r1, r0
	movs r5, #0
	strh r1, [r4, #0x16]
	strh r1, [r3]
	ldrb r0, [r2, #5]
	adds r0, #1
	movs r6, #8
	ldrsb r6, [r2, r6]
	ldr r2, _08080528 @ =gPreviousYPosition
	lsls r0, r0, #6
	lsls r1, r6, #2
	adds r0, r0, r1
	subs r0, #1
	strh r0, [r4, #0x18]
	strh r0, [r2]
	bl MinimapLoadInitial
	ldr r0, _0808052C @ =gIsLoadingFile
	strb r5, [r0]
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080804C8: .4byte 0x02037C00
_080804CC: .4byte 0x0000FFFF
_080804D0: .4byte 0x02036000
_080804D4: .4byte 0x02037200
_080804D8: .4byte 0x03000033
_080804DC: .4byte 0x0300003B
_080804E0: .4byte gInGameTimer
_080804E4: .4byte sUnk_582280+0x54
_080804E8: .4byte gDisableDrawingSamusAndScrollingFlag
_080804EC: .4byte gPreviousNavigationConversation
_080804F0: .4byte gPreviousSoundEvent
_080804F4: .4byte gEquipment
_080804F8: .4byte gSecurityHatchLevel
_080804FC: .4byte gSecurityHatchLevelBackup
_08080500: .4byte gAbilityCount
_08080504: .4byte gCurrentArea
_08080508: .4byte gPreviousArea
_0808050C: .4byte gCurrentRoom
_08080510: .4byte gLastDoorUsed
_08080514: .4byte 0x0300004C
_08080518: .4byte 0x0300004D
_0808051C: .4byte sAreaDoorPointers
_08080520: .4byte gPreviousXPosition
_08080524: .4byte gSamusData
_08080528: .4byte gPreviousYPosition
_0808052C: .4byte gIsLoadingFile

	thumb_func_start Sram_ResetForDemo
Sram_ResetForDemo: @ 0x08080530
	push {r4, r5, lr}
	sub sp, #4
	ldr r1, _080805F0 @ =gBootDebugOptions
	ldr r0, _080805F4 @ =0x085822E4 (sBlob_582288_58b3cc+0x5C)
	ldm r0!, {r2, r3, r4}
	stm r1!, {r2, r3, r4}
	ldr r2, _080805F8 @ =gButtonAssignments
	ldr r0, _080805FC @ =0x085822C8 (sBlob_582288_58b3cc+0x40)
	ldr r1, [r0, #4]
	ldr r0, [r0]
	str r0, [r2]
	str r1, [r2, #4]
	ldr r5, _08080600 @ =0x0000FFFF
	ldr r2, _08080604 @ =0x02037C00
	movs r3, #0xe0
	lsls r3, r3, #2
	movs r4, #0x10
	str r4, [sp]
	movs r0, #3
	adds r1, r5, #0
	bl BitFill
	ldr r2, _08080608 @ =0x02036000
	movs r3, #0x90
	lsls r3, r3, #5
	str r4, [sp]
	movs r0, #3
	adds r1, r5, #0
	bl BitFill
	ldr r2, _0808060C @ =0x02037200
	movs r3, #0x90
	lsls r3, r3, #4
	str r4, [sp]
	movs r0, #3
	adds r1, r5, #0
	bl BitFill
	movs r1, #0
	ldr r4, _08080610 @ =0x03000033
	movs r2, #0
	ldr r3, _08080614 @ =0x0300003B
_08080584:
	adds r0, r1, r4
	strb r2, [r0]
	adds r0, r1, r3
	strb r2, [r0]
	adds r1, #1
	cmp r1, #7
	ble _08080584
	ldr r1, _08080618 @ =gInGameTimer
	ldr r0, _0808061C @ =0x085822D4 (sBlob_582288_58b3cc+0x4C)
	ldr r0, [r0]
	str r0, [r1]
	ldr r0, _08080620 @ =gDisableDrawingSamusAndScrollingFlag
	movs r1, #0
	strb r1, [r0]
	ldr r2, _08080624 @ =gPreviousNavigationConversation
	movs r0, #0xff
	strb r0, [r2]
	ldr r2, _08080628 @ =gPreviousSoundEvent
	movs r0, #0xff
	strh r0, [r2]
	ldr r0, _0808062C @ =0x0300004C
	strb r1, [r0]
	ldr r0, _08080630 @ =0x0300004D
	strb r1, [r0]
	ldr r0, _08080634 @ =gIsLoadingFile
	strb r1, [r0]
	ldr r0, _08080638 @ =gUnk_3000be3
	strb r1, [r0]
	ldr r0, _0808063C @ =0x03000018
	strb r1, [r0]
	ldr r0, _08080640 @ =gDisableSoftReset
	strb r1, [r0]
	ldr r2, _08080644 @ =gMaxInGameTimeFlag
	movs r0, #1
	strb r0, [r2]
	ldr r0, _08080648 @ =0x03000022
	strb r1, [r0]
	ldr r0, _0808064C @ =gSkipDoorTransition
	strb r1, [r0]
	ldr r0, _08080650 @ =gPauseScreenFlag
	strb r1, [r0]
	ldr r0, _08080654 @ =0x03000B85
	strb r1, [r0]
	ldr r0, _08080658 @ =0x0300002B
	strb r1, [r0]
	ldr r0, _0808065C @ =gSamusDoorPositionOffset
	movs r1, #0
	strh r1, [r0]
	ldr r0, _08080660 @ =gDebugFlag
	strb r1, [r0]
	add sp, #4
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080805F0: .4byte gBootDebugOptions
_080805F4: .4byte sUnk_582280+0x64
_080805F8: .4byte gButtonAssignments
_080805FC: .4byte sUnk_582280+0x48
_08080600: .4byte 0x0000FFFF
_08080604: .4byte 0x02037C00
_08080608: .4byte 0x02036000
_0808060C: .4byte 0x02037200
_08080610: .4byte 0x03000033
_08080614: .4byte 0x0300003B
_08080618: .4byte gInGameTimer
_0808061C: .4byte sUnk_582280+0x54
_08080620: .4byte gDisableDrawingSamusAndScrollingFlag
_08080624: .4byte gPreviousNavigationConversation
_08080628: .4byte gPreviousSoundEvent
_0808062C: .4byte 0x0300004C
_08080630: .4byte 0x0300004D
_08080634: .4byte gIsLoadingFile
_08080638: .4byte gUnk_3000be3
_0808063C: .4byte 0x03000018
_08080640: .4byte gDisableSoftReset
_08080644: .4byte gMaxInGameTimeFlag
_08080648: .4byte 0x03000022
_0808064C: .4byte gSkipDoorTransition
_08080650: .4byte gPauseScreenFlag
_08080654: .4byte 0x03000B85
_08080658: .4byte 0x0300002B
_0808065C: .4byte gSamusDoorPositionOffset
_08080660: .4byte gDebugFlag

