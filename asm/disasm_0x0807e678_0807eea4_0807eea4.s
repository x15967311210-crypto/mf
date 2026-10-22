    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start Sram_ReadAll
Sram_ReadAll: @ 0x0807EEA4
	push {lr}
	bl Sram_ReadHeader
	bl unk_7fb84
	bl SramRead_MostRecentSaveFile
	bl SramRead_Language
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start Sram_WriteHeader
Sram_WriteHeader: @ 0x0807EEBC
	push {r4, r5, lr}
	ldr r4, _0807EF1C @ =0x02038000
	movs r0, #0x30
	strb r0, [r4, #8]
	movs r0, #0x31
	strb r0, [r4, #9]
	ldr r0, _0807EF20 @ =0x03000010
	ldrb r0, [r0]
	strb r0, [r4, #0xa]
	movs r0, #2
	strb r0, [r4, #0xb]
	movs r2, #0
	adds r5, r4, #0
	adds r5, #0xc
	ldr r3, _0807EF24 @ =0x08582248 (sBlob_58217b_58225c+0xCD)
_0807EEDA:
	adds r0, r5, r2
	adds r1, r2, r3
	ldrb r1, [r1]
	strb r1, [r0]
	adds r2, #1
	cmp r2, #0x13
	ble _0807EEDA
	movs r0, #0
	str r0, [r4]
	subs r0, #1
	str r0, [r4, #4]
	ldr r3, _0807EF1C @ =0x02038000
	movs r1, #0
	movs r2, #7
_0807EEF6:
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	subs r2, #1
	cmp r2, #0
	bge _0807EEF6
	str r1, [r4]
	mvns r0, r1
	str r0, [r4, #4]
	bl unk_c98
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0807EF1C: .4byte 0x02038000
_0807EF20: .4byte 0x03000010
_0807EF24: .4byte sDebugSectionInfo+0x12C

	thumb_func_start Sram_ReadHeader
Sram_ReadHeader: @ 0x0807EF28
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #4
	bl SramTestFlash
	ldr r0, _0807EFA0 @ =0x03000B8E
	ldrb r0, [r0]
	cmp r0, #0
	bne _0807EF42
	bl ReadSramHeaderToEwram
_0807EF42:
	movs r0, #0
	bl Sram_VerifyHeader
	adds r6, r0, #0
	movs r0, #1
	bl Sram_VerifyHeader
	mov sb, r0
	movs r0, #2
	bl Sram_VerifyHeader
	mov r8, r0
	cmp r6, #0
	beq _0807F00C
	mov r0, sp
	ldr r1, _0807EFA4 @ =0x0000FFFF
	adds r2, r1, #0
	strh r2, [r0]
	ldr r4, _0807EFA8 @ =0x040000D4
	str r0, [r4]
	ldr r5, _0807EFAC @ =0x02038000
	str r5, [r4, #4]
	ldr r1, _0807EFB0 @ =0x81000040
	str r1, [r4, #8]
	ldr r0, [r4, #8]
	mov r0, r8
	cmp r0, #0
	beq _0807EFD8
	mov r0, sp
	strh r2, [r0]
	str r0, [r4]
	ldr r0, _0807EFB4 @ =0x0203F100
	str r0, [r4, #4]
	str r1, [r4, #8]
	ldr r0, [r4, #8]
	mov r0, sb
	cmp r0, #0
	beq _0807EFBC
	mov r0, sp
	strh r2, [r0]
	str r0, [r4]
	ldr r0, _0807EFB8 @ =0x02038080
	str r0, [r4, #4]
	str r1, [r4, #8]
	ldr r0, [r4, #8]
	b _0807F034
	.align 2, 0
_0807EFA0: .4byte 0x03000B8E
_0807EFA4: .4byte 0x0000FFFF
_0807EFA8: .4byte 0x040000D4
_0807EFAC: .4byte 0x02038000
_0807EFB0: .4byte 0x81000040
_0807EFB4: .4byte 0x0203F100
_0807EFB8: .4byte 0x02038080
_0807EFBC:
	ldr r0, _0807EFD0 @ =0x02038080
	str r0, [r4]
	str r5, [r4, #4]
	ldr r0, _0807EFD4 @ =0x80000040
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r6, #0
	bl unk_c98
	b _0807F034
	.align 2, 0
_0807EFD0: .4byte 0x02038080
_0807EFD4: .4byte 0x80000040
_0807EFD8:
	ldr r0, _0807F000 @ =0x0203F100
	str r0, [r4]
	str r5, [r4, #4]
	ldr r7, _0807F004 @ =0x80000040
	str r7, [r4, #8]
	ldr r0, [r4, #8]
	movs r6, #0
	bl unk_c98
	mov r1, sb
	cmp r1, #0
	beq _0807F034
	str r5, [r4]
	ldr r0, _0807F008 @ =0x02038080
	str r0, [r4, #4]
	str r7, [r4, #8]
	ldr r0, [r4, #8]
	bl unk_cd8
	b _0807F034
	.align 2, 0
_0807F000: .4byte 0x0203F100
_0807F004: .4byte 0x80000040
_0807F008: .4byte 0x02038080
_0807F00C:
	ldr r4, _0807F040 @ =0x040000D4
	ldr r7, _0807F044 @ =0x02038000
	str r7, [r4]
	ldr r0, _0807F048 @ =0x02038080
	str r0, [r4, #4]
	ldr r5, _0807F04C @ =0x80000040
	str r5, [r4, #8]
	ldr r0, [r4, #8]
	bl unk_cd8
	mov r0, r8
	cmp r0, #0
	beq _0807F034
	str r7, [r4]
	ldr r0, _0807F050 @ =0x0203F100
	str r0, [r4, #4]
	str r5, [r4, #8]
	ldr r0, [r4, #8]
	bl unk_cf0
_0807F034:
	cmp r6, #0
	bne _0807F058
	ldr r0, _0807F054 @ =0x03000010
	strb r6, [r0]
	b _0807F066
	.align 2, 0
_0807F040: .4byte 0x040000D4
_0807F044: .4byte 0x02038000
_0807F048: .4byte 0x02038080
_0807F04C: .4byte 0x80000040
_0807F050: .4byte 0x0203F100
_0807F054: .4byte 0x03000010
_0807F058:
	bl EraseSram
	ldr r1, _0807F074 @ =0x03000010
	movs r0, #0
	strb r0, [r1]
	bl Sram_WriteHeader
_0807F066:
	add sp, #4
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807F074: .4byte 0x03000010

	thumb_func_start Sram_VerifyHeader
Sram_VerifyHeader: @ 0x0807F078
	push {r4, r5, r6, r7, lr}
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	movs r4, #0
	ldr r1, _0807F0EC @ =0x0203F100
	cmp r0, #2
	beq _0807F08E
	ldr r1, _0807F0F0 @ =0x02038000
	cmp r0, #1
	bne _0807F08E
	adds r1, #0x80
_0807F08E:
	movs r2, #0
	ldr r7, [r1]
	adds r5, r1, #0
	adds r5, #0xc
	ldr r0, [r1, #4]
	mov ip, r0
	movs r3, #7
_0807F09C:
	ldm r1!, {r0}
	adds r2, r2, r0
	ldm r1!, {r0}
	adds r2, r2, r0
	ldm r1!, {r0}
	adds r2, r2, r0
	ldm r1!, {r0}
	adds r2, r2, r0
	subs r3, #1
	cmp r3, #0
	bge _0807F09C
	cmp r7, r2
	beq _0807F0BA
	movs r0, #1
	orrs r4, r0
_0807F0BA:
	movs r3, #0
	adds r2, r5, #0
	ldr r6, _0807F0F4 @ =0x08582248 (sBlob_58217b_58225c+0xCD)
	movs r5, #2
_0807F0C2:
	adds r0, r2, r3
	adds r1, r3, r6
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	beq _0807F0D0
	orrs r4, r5
_0807F0D0:
	adds r3, #1
	cmp r3, #0x13
	ble _0807F0C2
	mov r1, ip
	mvns r0, r1
	cmp r7, r0
	beq _0807F0E2
	movs r0, #4
	orrs r4, r0
_0807F0E2:
	adds r0, r4, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0807F0EC: .4byte 0x0203F100
_0807F0F0: .4byte 0x02038000
_0807F0F4: .4byte sDebugSectionInfo+0x12C

	thumb_func_start Sram_ProcessIntroSave
Sram_ProcessIntroSave: @ 0x0807F0F8
	push {r4, r5, r6, lr}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	adds r3, r1, #0
	ldr r6, _0807F128 @ =0x03000B94
	ldr r4, _0807F12C @ =0x03000B8D
	ldrb r0, [r4]
	lsls r2, r0, #2
	adds r0, r2, r0
	lsls r0, r0, #2
	adds r0, r0, r6
	ldrb r5, [r0, #0xf]
	cmp r5, #0
	beq _0807F17C
	cmp r1, #2
	bgt _0807F130
	cmp r1, #1
	blt _0807F120
	b _0807F222
_0807F120:
	cmp r1, #0
	beq _0807F136
	b _0807F21C
	.align 2, 0
_0807F128: .4byte 0x03000B94
_0807F12C: .4byte 0x03000B8D
_0807F130:
	cmp r1, #3
	beq _0807F158
	b _0807F21C
_0807F136:
	ldr r1, _0807F150 @ =gDisableSoftReset
	movs r0, #1
	strb r0, [r1]
	ldr r0, _0807F154 @ =0x03000014
	movs r2, #1
	strb r2, [r0, #1]
	ldrb r1, [r4]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r6
	strb r2, [r0, #0x11]
	b _0807F222
	.align 2, 0
_0807F150: .4byte gDisableSoftReset
_0807F154: .4byte 0x03000014
_0807F158:
	ldr r0, _0807F174 @ =0x0858225C (sSaveDataEwramPointers)
	adds r0, r2, r0
	ldr r1, [r0]
	ldr r0, _0807F178 @ =0x08582268 (sSaveDataEwramBackupPointers)
	adds r0, r2, r0
	ldr r2, [r0]
	movs r3, #0x90
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _0807F21C
	.align 2, 0
_0807F174: .4byte sSaveDataEwramPointers
_0807F178: .4byte sSaveDataEwramBackupPointers
_0807F17C:
	cmp r1, #1
	beq _0807F1E4
	cmp r1, #1
	bgt _0807F18A
	cmp r1, #0
	beq _0807F194
	b _0807F21C
_0807F18A:
	cmp r3, #2
	beq _0807F1EA
	cmp r3, #3
	beq _0807F1F0
	b _0807F21C
_0807F194:
	ldr r1, _0807F1D8 @ =gDisableSoftReset
	movs r0, #1
	strb r0, [r1]
	ldr r3, _0807F1DC @ =0x03000014
	movs r2, #1
	strb r2, [r3, #1]
	ldrb r1, [r4]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r6
	strb r2, [r0, #0x11]
	ldrb r1, [r4]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r6
	ldrb r0, [r0, #0x10]
	strb r0, [r3]
	ldr r1, _0807F1E0 @ =0x0858225C (sSaveDataEwramPointers)
	ldrb r0, [r4]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r2, [r0]
	movs r3, #0xc0
	lsls r3, r3, #2
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	movs r1, #0
	bl BitFill
	b _0807F222
	.align 2, 0
_0807F1D8: .4byte gDisableSoftReset
_0807F1DC: .4byte 0x03000014
_0807F1E0: .4byte sSaveDataEwramPointers
_0807F1E4:
	bl Sram_WriteHeaderAndGameInfo
	b _0807F222
_0807F1EA:
	bl WriteMostRecentFileToSram
	b _0807F222
_0807F1F0:
	ldr r0, _0807F210 @ =0x0858225C (sSaveDataEwramPointers)
	adds r0, r2, r0
	ldr r1, [r0]
	ldr r0, _0807F214 @ =0x08582268 (sSaveDataEwramBackupPointers)
	adds r0, r2, r0
	ldr r2, [r0]
	movs r3, #0x90
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r0, _0807F218 @ =gDisableSoftReset
	strb r5, [r0]
	b _0807F222
	.align 2, 0
_0807F210: .4byte sSaveDataEwramPointers
_0807F214: .4byte sSaveDataEwramBackupPointers
_0807F218: .4byte gDisableSoftReset
_0807F21C:
	ldr r1, _0807F22C @ =gDisableSoftReset
	movs r0, #0
	strb r0, [r1]
_0807F222:
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0807F22C: .4byte gDisableSoftReset

	thumb_func_start Sram_WriteHeaderAndGameInfo
Sram_WriteHeaderAndGameInfo: @ 0x0807F230
	push {r4, r5, r6, lr}
	ldr r5, _0807F2A0 @ =0x0858225C (sSaveDataEwramPointers)
	ldr r4, _0807F2A4 @ =0x03000B8D
	ldrb r0, [r4]
	lsls r0, r0, #2
	adds r0, r0, r5
	ldr r6, [r0]
	ldr r1, _0807F2A8 @ =0x08582200 (sBlob_58217b_58225c+0x85)
	adds r0, r6, #0
	bl Sram_StringCopy_MetroidEpisode4A
	movs r0, #0
	str r0, [r6, #0x10]
	subs r0, #1
	str r0, [r6, #0x14]
	ldr r1, _0807F2AC @ =0x03000014
	ldrb r0, [r1, #1]
	strb r0, [r6, #0x19]
	ldrb r0, [r1]
	strb r0, [r6, #0x18]
	adds r0, r6, #0
	adds r0, #0xf0
	ldr r1, _0807F2B0 @ =0x085821F8 (sBlob_58217b_58225c+0x7D)
	bl Sram_StringCopy_SAVE_END
	ldrb r0, [r4]
	lsls r0, r0, #2
	adds r0, r0, r5
	ldr r2, [r0]
	movs r1, #0
	movs r3, #0x8f
_0807F26E:
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	subs r3, #1
	cmp r3, #0
	bge _0807F26E
	str r1, [r6, #0x10]
	mvns r0, r1
	str r0, [r6, #0x14]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0807F2A0: .4byte sSaveDataEwramPointers
_0807F2A4: .4byte 0x03000B8D
_0807F2A8: .4byte sDebugSectionInfo+0xE4
_0807F2AC: .4byte 0x03000014
_0807F2B0: .4byte sDebugSectionInfo+0xDC

	thumb_func_start Sram_ProcessEndingSave
Sram_ProcessEndingSave: @ 0x0807F2B4
	push {lr}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #1
	beq _0807F2DA
	cmp r1, #1
	bgt _0807F2CA
	cmp r1, #0
	beq _0807F2D4
	b _0807F330
_0807F2CA:
	cmp r1, #2
	beq _0807F2E8
	cmp r1, #3
	beq _0807F310
	b _0807F330
_0807F2D4:
	bl ReadMostRecentFileToEwram
	b _0807F330
_0807F2DA:
	ldr r0, _0807F2E4 @ =0x03000014
	strb r1, [r0]
	bl Sram_CopyGameCompletion
	b _0807F330
	.align 2, 0
_0807F2E4: .4byte 0x03000014
_0807F2E8:
	bl WriteMostRecentFileToSram
	ldr r2, _0807F304 @ =0x03000B94
	ldr r0, _0807F308 @ =0x03000B8D
	ldrb r1, [r0]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r1, _0807F30C @ =0x03000014
	ldrb r1, [r1]
	strb r1, [r0, #0x10]
	b _0807F330
	.align 2, 0
_0807F304: .4byte 0x03000B94
_0807F308: .4byte 0x03000B8D
_0807F30C: .4byte 0x03000014
_0807F310:
	ldr r1, _0807F338 @ =0x0858225C (sSaveDataEwramPointers)
	ldr r0, _0807F33C @ =0x03000B8D
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r1, r0, r1
	ldr r1, [r1]
	ldr r2, _0807F340 @ =0x08582268 (sSaveDataEwramBackupPointers)
	adds r0, r0, r2
	ldr r2, [r0]
	movs r3, #0x90
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
_0807F330:
	add sp, #4
	pop {r0}
	bx r0
	.align 2, 0
_0807F338: .4byte sSaveDataEwramPointers
_0807F33C: .4byte 0x03000B8D
_0807F340: .4byte sSaveDataEwramBackupPointers

	thumb_func_start Sram_CopyGameCompletion
Sram_CopyGameCompletion: @ 0x0807F344
	push {r4, lr}
	ldr r2, _0807F3A0 @ =0x0858225C (sSaveDataEwramPointers)
	ldr r1, _0807F3A4 @ =0x03000B8D
	ldrb r0, [r1]
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r3, [r0]
	movs r0, #0
	str r0, [r3, #0x10]
	subs r0, #1
	str r0, [r3, #0x14]
	ldr r0, _0807F3A8 @ =0x03000014
	ldrb r0, [r0]
	strb r0, [r3, #0x18]
	ldrb r0, [r1]
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r2, [r0]
	movs r1, #0
	movs r4, #0x8f
_0807F36C:
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	subs r4, #1
	cmp r4, #0
	bge _0807F36C
	str r1, [r3, #0x10]
	mvns r0, r1
	str r0, [r3, #0x14]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0807F3A0: .4byte sSaveDataEwramPointers
_0807F3A4: .4byte 0x03000B8D
_0807F3A8: .4byte 0x03000014

	thumb_func_start Sram_QuickSave
Sram_QuickSave: @ 0x0807F3AC
	push {lr}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r1, r0, #0
	cmp r0, #1
	beq _0807F3E8
	cmp r0, #1
	bgt _0807F3C4
	cmp r0, #0
	beq _0807F3CE
	b _0807F434
_0807F3C4:
	cmp r1, #2
	beq _0807F3F2
	cmp r1, #3
	beq _0807F414
	b _0807F434
_0807F3CE:
	ldr r0, _0807F3E0 @ =gDisableSoftReset
	movs r1, #1
	strb r1, [r0]
	ldr r0, _0807F3E4 @ =0x03000B90
	strb r1, [r0]
	bl WriteMostRecentFileBackupToSram
	b _0807F43A
	.align 2, 0
_0807F3E0: .4byte gDisableSoftReset
_0807F3E4: .4byte 0x03000B90
_0807F3E8:
	bl SramWrite_WorldData
	bl SramWrite_ToEwram
	b _0807F43A
_0807F3F2:
	bl WriteMostRecentFileToSram
	ldr r2, _0807F40C @ =0x03000B94
	ldr r0, _0807F410 @ =0x03000B8D
	ldrb r1, [r0]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	movs r1, #1
	strb r1, [r0]
	b _0807F43A
	.align 2, 0
_0807F40C: .4byte 0x03000B94
_0807F410: .4byte 0x03000B8D
_0807F414:
	ldr r1, _0807F440 @ =0x0858225C (sSaveDataEwramPointers)
	ldr r0, _0807F444 @ =0x03000B8D
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r1, r0, r1
	ldr r1, [r1]
	ldr r2, _0807F448 @ =0x08582268 (sSaveDataEwramBackupPointers)
	adds r0, r0, r2
	ldr r2, [r0]
	movs r3, #0x90
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
_0807F434:
	ldr r1, _0807F44C @ =gDisableSoftReset
	movs r0, #0
	strb r0, [r1]
_0807F43A:
	add sp, #4
	pop {r0}
	bx r0
	.align 2, 0
_0807F440: .4byte sSaveDataEwramPointers
_0807F444: .4byte 0x03000B8D
_0807F448: .4byte sSaveDataEwramBackupPointers
_0807F44C: .4byte gDisableSoftReset

	thumb_func_start SramWrite_ToEwram
SramWrite_ToEwram: @ 0x0807F450
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x38
	ldr r4, _0807F6F8 @ =gMusicInfo
	ldrh r1, [r4, #0x1c]
	ldr r0, _0807F6FC @ =0xFFFF0000
	ands r0, r5
	orrs r0, r1
	ldrh r1, [r4, #0x1e]
	lsls r1, r1, #0x10
	ldr r3, _0807F700 @ =0x0000FFFF
	ands r0, r3
	adds r5, r0, #0
	orrs r5, r1
	adds r0, r4, #0
	adds r0, #0x20
	ldrb r0, [r0]
	ldr r2, _0807F704 @ =0xFFFFFF00
	ands r2, r6
	orrs r2, r0
	adds r0, r4, #0
	adds r0, #0x21
	ldrb r1, [r0]
	lsls r1, r1, #8
	ldr r0, _0807F708 @ =0xFFFF00FF
	ands r0, r2
	orrs r0, r1
	ldrh r1, [r4, #2]
	lsls r1, r1, #0x10
	ands r0, r3
	adds r6, r0, #0
	orrs r6, r1
	ldr r1, _0807F70C @ =0x0858225C (sSaveDataEwramPointers)
	ldr r0, _0807F710 @ =0x03000B8D
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r4, [r0]
	ldr r1, _0807F714 @ =0x08582200 (sBlob_58217b_58225c+0x85)
	adds r0, r4, #0
	bl Sram_StringCopy_MetroidEpisode4A
	movs r0, #0
	str r0, [r4, #0x10]
	subs r0, #1
	str r0, [r4, #0x14]
	ldr r0, _0807F718 @ =0x03000014
	ldr r0, [r0]
	str r0, [r4, #0x18]
	ldr r0, _0807F71C @ =0x03000B90
	ldrb r0, [r0]
	strb r0, [r4, #0x1c]
	ldr r0, _0807F720 @ =gCurrentArea
	ldrb r0, [r0]
	strb r0, [r4, #0x1d]
	ldr r0, _0807F724 @ =gCurrentRoom
	ldrb r0, [r0]
	strb r0, [r4, #0x1e]
	ldr r0, _0807F728 @ =gLastDoorUsed
	ldrb r0, [r0]
	strb r0, [r4, #0x1f]
	ldr r0, _0807F72C @ =gAbilityCount
	ldrb r1, [r0]
	adds r0, r4, #0
	adds r0, #0x20
	strb r1, [r0]
	ldr r0, _0807F730 @ =gEventCounter
	ldrb r0, [r0]
	adds r1, r4, #0
	adds r1, #0x21
	strb r0, [r1]
	ldr r0, _0807F734 @ =gPreviousNavigationConversation
	ldrb r0, [r0]
	adds r1, #1
	strb r0, [r1]
	ldr r0, _0807F738 @ =gPreviousCutscene
	ldrb r0, [r0]
	adds r1, #1
	strb r0, [r1]
	ldr r0, _0807F73C @ =0x03000031
	ldrb r1, [r0]
	adds r0, r4, #0
	adds r0, #0x24
	strb r1, [r0]
	ldr r0, _0807F740 @ =0x03000032
	ldrb r0, [r0]
	adds r1, r4, #0
	adds r1, #0x25
	strb r0, [r1]
	ldr r0, _0807F744 @ =gSoundEventCounter
	ldrh r0, [r0]
	strh r0, [r4, #0x26]
	ldr r0, _0807F748 @ =gPreviousSoundEvent
	ldrh r0, [r0]
	strh r0, [r4, #0x28]
	ldr r0, _0807F74C @ =0x0300004D
	ldrb r0, [r0]
	adds r1, #5
	strb r0, [r1]
	ldr r0, _0807F750 @ =gSecurityHatchLevelBackup
	ldrb r0, [r0]
	adds r1, #1
	strb r0, [r1]
	adds r1, #1
	ldr r0, _0807F754 @ =0x03000124
	ldm r0!, {r2, r3, r7}
	stm r1!, {r2, r3, r7}
	ldm r0!, {r2, r3}
	stm r1!, {r2, r3}
	ldr r0, _0807F758 @ =0x03001224
	ldrh r1, [r0]
	adds r0, r4, #0
	adds r0, #0x40
	strh r1, [r0]
	ldr r0, _0807F75C @ =0x03001226
	ldrh r0, [r0]
	adds r1, r4, #0
	adds r1, #0x42
	strh r0, [r1]
	ldr r0, _0807F760 @ =gBg1XPosition
	ldrh r1, [r0]
	adds r0, r4, #0
	adds r0, #0x44
	strh r1, [r0]
	ldr r0, _0807F764 @ =gBg1YPosition
	ldrh r0, [r0]
	adds r1, r4, #0
	adds r1, #0x46
	strh r0, [r1]
	ldr r0, _0807F768 @ =0x0300122C
	ldrh r1, [r0]
	adds r0, r4, #0
	adds r0, #0x48
	strh r1, [r0]
	ldr r0, _0807F76C @ =0x0300122E
	ldrh r0, [r0]
	adds r1, r4, #0
	adds r1, #0x4a
	strh r0, [r1]
	ldr r0, _0807F770 @ =0x03001230
	ldrh r1, [r0]
	adds r0, r4, #0
	adds r0, #0x4c
	strh r1, [r0]
	ldr r0, _0807F774 @ =0x03001232
	ldrh r0, [r0]
	adds r1, r4, #0
	adds r1, #0x4e
	strh r0, [r1]
	movs r3, #0
	adds r2, r4, #0
	adds r2, #0x50
	ldr r7, _0807F778 @ =0x03000033
_0807F588:
	adds r0, r2, r3
	adds r1, r3, r7
	ldrb r1, [r1]
	strb r1, [r0]
	adds r3, #1
	cmp r3, #7
	ble _0807F588
	movs r3, #0
	movs r7, #0x60
	adds r7, r7, r4
	mov ip, r7
	movs r0, #0x8c
	adds r0, r0, r4
	mov r8, r0
	movs r1, #0x98
	adds r1, r1, r4
	mov sb, r1
	movs r2, #0xa4
	adds r2, r2, r4
	mov sl, r2
	adds r7, r4, #0
	adds r7, #0xb4
	str r7, [sp]
	adds r0, r4, #0
	adds r0, #0xc4
	str r0, [sp, #4]
	adds r1, r4, #0
	adds r1, #0xd4
	str r1, [sp, #8]
	adds r2, r4, #0
	adds r2, #0xd6
	str r2, [sp, #0xc]
	adds r7, #0x24
	str r7, [sp, #0x10]
	adds r0, #0x16
	str r0, [sp, #0x14]
	adds r1, #8
	str r1, [sp, #0x18]
	adds r2, #8
	str r2, [sp, #0x1c]
	adds r7, #8
	str r7, [sp, #0x20]
	adds r0, #8
	str r0, [sp, #0x24]
	adds r1, #7
	str r1, [sp, #0x28]
	adds r2, #6
	str r2, [sp, #0x2c]
	adds r7, #8
	str r7, [sp, #0x30]
	adds r0, #0xe
	str r0, [sp, #0x34]
	subs r2, #0x8c
	ldr r7, _0807F77C @ =0x0300003B
_0807F5F4:
	adds r0, r2, r3
	adds r1, r3, r7
	ldrb r1, [r1]
	strb r1, [r0]
	adds r3, #1
	cmp r3, #7
	ble _0807F5F4
	mov r1, ip
	ldr r0, _0807F780 @ =gSamusData
	ldm r0!, {r2, r3, r7}
	stm r1!, {r2, r3, r7}
	ldm r0!, {r2, r3, r7}
	stm r1!, {r2, r3, r7}
	ldm r0!, {r2, r3, r7}
	stm r1!, {r2, r3, r7}
	ldm r0!, {r2, r3}
	stm r1!, {r2, r3}
	mov r1, r8
	ldr r0, _0807F784 @ =gSamusAnimationInfo
	ldm r0!, {r2, r3, r7}
	stm r1!, {r2, r3, r7}
	mov r1, sb
	ldr r0, _0807F788 @ =0x030012E4
	ldm r0!, {r2, r3, r7}
	stm r1!, {r2, r3, r7}
	mov r1, sl
	ldr r0, _0807F78C @ =0x030012F0
	ldm r0!, {r2, r3, r7}
	stm r1!, {r2, r3, r7}
	ldr r0, [r0]
	str r0, [r1]
	ldr r1, [sp]
	ldr r0, _0807F78C @ =0x030012F0
	adds r0, #0x10
	ldm r0!, {r2, r3, r7}
	stm r1!, {r2, r3, r7}
	ldr r0, [r0]
	str r0, [r1]
	ldr r1, [sp, #4]
	ldr r0, _0807F790 @ =gEquipment
	ldm r0!, {r2, r3, r7}
	stm r1!, {r2, r3, r7}
	ldr r0, [r0]
	str r0, [r1]
	ldr r7, _0807F794 @ =gPreventMovementTimer
	ldrh r0, [r7]
	ldr r1, [sp, #8]
	strh r0, [r1]
	ldr r2, _0807F798 @ =gDisableDrawingSamusAndScrollingFlag
	ldrb r0, [r2]
	ldr r3, [sp, #0xc]
	strb r0, [r3]
	ldr r7, _0807F79C @ =gAtmosphericStabilizersOnline
	ldrh r0, [r7]
	ldr r1, [sp, #0x10]
	strh r0, [r1]
	ldr r2, _0807F7A0 @ =gMissileGeronsDestroyed
	ldrh r0, [r2]
	ldr r3, [sp, #0x14]
	strh r0, [r3]
	ldr r7, _0807F7A4 @ =gSuperMissileGeronsDestroyed
	ldrh r0, [r7]
	ldr r1, [sp, #0x18]
	strh r0, [r1]
	ldr r2, _0807F7A8 @ =gPowerBombGeronsDestroyed
	ldrh r0, [r2]
	ldr r3, [sp, #0x1c]
	strh r0, [r3]
	ldr r7, _0807F7AC @ =gGadorasDestroyed
	ldrh r0, [r7]
	ldr r1, [sp, #0x20]
	strh r0, [r1]
	ldr r2, _0807F7B0 @ =gMissileHatchDestroyed
	ldrb r0, [r2]
	ldr r3, [sp, #0x24]
	strb r0, [r3]
	ldr r7, _0807F7B4 @ =gWaterLowered
	ldrb r0, [r7]
	ldr r1, [sp, #0x28]
	strb r0, [r1]
	ldr r2, _0807F7B8 @ =gInGameTimer
	ldr r0, [r2]
	ldr r3, [sp, #0x2c]
	str r0, [r3]
	ldr r7, [sp, #0x30]
	str r5, [r7]
	str r6, [r7, #4]
	ldr r0, [sp, #0x34]
	ldr r1, _0807F7BC @ =0x085821F8 (sBlob_58217b_58225c+0x7D)
	bl Sram_StringCopy_SAVE_END
	ldr r1, _0807F70C @ =0x0858225C (sSaveDataEwramPointers)
	ldr r0, _0807F710 @ =0x03000B8D
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r2, [r0]
	movs r1, #0
	movs r3, #0x8f
_0807F6BA:
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	ldm r2!, {r0}
	adds r1, r1, r0
	subs r3, #1
	cmp r3, #0
	bge _0807F6BA
	str r1, [r4, #0x10]
	mvns r0, r1
	str r0, [r4, #0x14]
	add sp, #0x38
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807F6F8: .4byte gMusicInfo
_0807F6FC: .4byte 0xFFFF0000
_0807F700: .4byte 0x0000FFFF
_0807F704: .4byte 0xFFFFFF00
_0807F708: .4byte 0xFFFF00FF
_0807F70C: .4byte sSaveDataEwramPointers
_0807F710: .4byte 0x03000B8D
_0807F714: .4byte sDebugSectionInfo+0xE4
_0807F718: .4byte 0x03000014
_0807F71C: .4byte 0x03000B90
_0807F720: .4byte gCurrentArea
_0807F724: .4byte gCurrentRoom
_0807F728: .4byte gLastDoorUsed
_0807F72C: .4byte gAbilityCount
_0807F730: .4byte gEventCounter
_0807F734: .4byte gPreviousNavigationConversation
_0807F738: .4byte gPreviousCutscene
_0807F73C: .4byte 0x03000031
_0807F740: .4byte 0x03000032
_0807F744: .4byte gSoundEventCounter
_0807F748: .4byte gPreviousSoundEvent
_0807F74C: .4byte 0x0300004D
_0807F750: .4byte gSecurityHatchLevelBackup
_0807F754: .4byte 0x03000124
_0807F758: .4byte 0x03001224
_0807F75C: .4byte 0x03001226
_0807F760: .4byte gBg1XPosition
_0807F764: .4byte gBg1YPosition
_0807F768: .4byte 0x0300122C
_0807F76C: .4byte 0x0300122E
_0807F770: .4byte 0x03001230
_0807F774: .4byte 0x03001232
_0807F778: .4byte 0x03000033
_0807F77C: .4byte 0x0300003B
_0807F780: .4byte gSamusData
_0807F784: .4byte gSamusAnimationInfo
_0807F788: .4byte 0x030012E4
_0807F78C: .4byte 0x030012F0
_0807F790: .4byte gEquipment
_0807F794: .4byte gPreventMovementTimer
_0807F798: .4byte gDisableDrawingSamusAndScrollingFlag
_0807F79C: .4byte gAtmosphericStabilizersOnline
_0807F7A0: .4byte gMissileGeronsDestroyed
_0807F7A4: .4byte gSuperMissileGeronsDestroyed
_0807F7A8: .4byte gPowerBombGeronsDestroyed
_0807F7AC: .4byte gGadorasDestroyed
_0807F7B0: .4byte gMissileHatchDestroyed
_0807F7B4: .4byte gWaterLowered
_0807F7B8: .4byte gInGameTimer
_0807F7BC: .4byte sDebugSectionInfo+0xDC

	thumb_func_start SramRead_FromEwram
SramRead_FromEwram: @ 0x0807F7C0
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x2c
	ldr r1, _0807F9F8 @ =0x0858225C (sSaveDataEwramPointers)
	ldr r0, _0807F9FC @ =0x03000B8D
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r2, [r0]
	ldr r1, _0807FA00 @ =0x03000014
	ldr r0, [r2, #0x18]
	str r0, [r1]
	ldr r1, _0807FA04 @ =0x03000B90
	ldrb r0, [r2, #0x1c]
	strb r0, [r1]
	ldr r1, _0807FA08 @ =gCurrentArea
	ldrb r0, [r2, #0x1d]
	strb r0, [r1]
	ldr r1, _0807FA0C @ =gCurrentRoom
	ldrb r0, [r2, #0x1e]
	strb r0, [r1]
	ldr r1, _0807FA10 @ =gLastDoorUsed
	ldrb r0, [r2, #0x1f]
	strb r0, [r1]
	ldr r1, _0807FA14 @ =gAbilityCount
	adds r0, r2, #0
	adds r0, #0x20
	ldrb r0, [r0]
	strb r0, [r1]
	ldr r1, _0807FA18 @ =gEventCounter
	adds r0, r2, #0
	adds r0, #0x21
	ldrb r0, [r0]
	strb r0, [r1]
	ldr r1, _0807FA1C @ =gPreviousNavigationConversation
	adds r0, r2, #0
	adds r0, #0x22
	ldrb r0, [r0]
	strb r0, [r1]
	ldr r1, _0807FA20 @ =gPreviousCutscene
	adds r0, r2, #0
	adds r0, #0x23
	ldrb r0, [r0]
	strb r0, [r1]
	ldr r1, _0807FA24 @ =0x03000031
	adds r0, r2, #0
	adds r0, #0x24
	ldrb r0, [r0]
	strb r0, [r1]
	ldr r1, _0807FA28 @ =0x03000032
	adds r0, r2, #0
	adds r0, #0x25
	ldrb r0, [r0]
	strb r0, [r1]
	ldr r1, _0807FA2C @ =gSoundEventCounter
	ldrh r0, [r2, #0x26]
	strh r0, [r1]
	ldr r1, _0807FA30 @ =gPreviousSoundEvent
	ldrh r0, [r2, #0x28]
	strh r0, [r1]
	ldr r1, _0807FA34 @ =0x0300004D
	adds r0, r2, #0
	adds r0, #0x2a
	ldrb r0, [r0]
	strb r0, [r1]
	ldr r1, _0807FA38 @ =gSecurityHatchLevelBackup
	adds r0, r2, #0
	adds r0, #0x2b
	ldrb r0, [r0]
	strb r0, [r1]
	ldr r1, _0807FA3C @ =0x03000124
	adds r0, r2, #0
	adds r0, #0x2c
	ldm r0!, {r3, r4, r5}
	stm r1!, {r3, r4, r5}
	ldm r0!, {r3, r4}
	stm r1!, {r3, r4}
	ldr r1, _0807FA40 @ =0x03001224
	adds r0, r2, #0
	adds r0, #0x40
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _0807FA44 @ =0x03001226
	adds r0, r2, #0
	adds r0, #0x42
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _0807FA48 @ =gBg1XPosition
	adds r0, r2, #0
	adds r0, #0x44
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _0807FA4C @ =gBg1YPosition
	adds r0, r2, #0
	adds r0, #0x46
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _0807FA50 @ =0x0300122C
	adds r0, r2, #0
	adds r0, #0x48
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _0807FA54 @ =0x0300122E
	adds r0, r2, #0
	adds r0, #0x4a
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _0807FA58 @ =0x03001230
	adds r0, r2, #0
	adds r0, #0x4c
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _0807FA5C @ =0x03001232
	adds r0, r2, #0
	adds r0, #0x4e
	ldrh r0, [r0]
	strh r0, [r1]
	movs r3, #0
	ldr r5, _0807FA60 @ =gMusicInfo
	mov ip, r5
	ldr r5, _0807FA64 @ =0x03000033
	adds r4, r2, #0
	adds r4, #0x50
_0807F8BC:
	adds r0, r3, r5
	adds r1, r4, r3
	ldrb r1, [r1]
	strb r1, [r0]
	adds r3, #1
	cmp r3, #7
	ble _0807F8BC
	movs r3, #0
	adds r5, r2, #0
	adds r5, #0x60
	adds r6, r2, #0
	adds r6, #0x8c
	adds r7, r2, #0
	adds r7, #0x98
	movs r0, #0xa4
	adds r0, r0, r2
	mov r8, r0
	movs r1, #0xb4
	adds r1, r1, r2
	mov sb, r1
	movs r4, #0xc4
	adds r4, r4, r2
	mov sl, r4
	adds r0, r2, #0
	adds r0, #0xd4
	str r0, [sp]
	adds r1, r2, #0
	adds r1, #0xd6
	str r1, [sp, #4]
	adds r4, r2, #0
	adds r4, #0xd8
	str r4, [sp, #8]
	adds r0, #6
	str r0, [sp, #0xc]
	adds r1, #6
	str r1, [sp, #0x10]
	adds r4, #6
	str r4, [sp, #0x14]
	adds r0, #6
	str r0, [sp, #0x18]
	adds r1, #6
	str r1, [sp, #0x1c]
	adds r4, #5
	str r4, [sp, #0x20]
	adds r0, #4
	str r0, [sp, #0x24]
	adds r1, #6
	str r1, [sp, #0x28]
	ldr r4, _0807FA68 @ =0x0300003B
	adds r2, #0x58
_0807F920:
	adds r0, r3, r4
	adds r1, r2, r3
	ldrb r1, [r1]
	strb r1, [r0]
	adds r3, #1
	cmp r3, #7
	ble _0807F920
	ldr r1, _0807FA6C @ =gSamusData
	adds r0, r5, #0
	ldm r0!, {r2, r3, r4}
	stm r1!, {r2, r3, r4}
	ldm r0!, {r2, r3, r5}
	stm r1!, {r2, r3, r5}
	ldm r0!, {r2, r4, r5}
	stm r1!, {r2, r4, r5}
	ldm r0!, {r3, r4}
	stm r1!, {r3, r4}
	ldr r1, _0807FA70 @ =gSamusAnimationInfo
	adds r0, r6, #0
	ldm r0!, {r2, r3, r5}
	stm r1!, {r2, r3, r5}
	ldr r1, _0807FA74 @ =0x030012E4
	adds r0, r7, #0
	ldm r0!, {r2, r4, r5}
	stm r1!, {r2, r4, r5}
	ldr r1, _0807FA78 @ =0x030012F0
	mov r0, r8
	ldm r0!, {r3, r4, r5}
	stm r1!, {r3, r4, r5}
	ldr r0, [r0]
	str r0, [r1]
	ldr r1, _0807FA78 @ =0x030012F0
	adds r1, #0x10
	mov r0, sb
	ldm r0!, {r2, r3, r4}
	stm r1!, {r2, r3, r4}
	ldr r0, [r0]
	str r0, [r1]
	ldr r1, _0807FA7C @ =gEquipment
	mov r0, sl
	ldm r0!, {r2, r3, r5}
	stm r1!, {r2, r3, r5}
	ldr r0, [r0]
	str r0, [r1]
	ldr r4, [sp]
	ldrh r0, [r4]
	ldr r5, _0807FA80 @ =gPreventMovementTimer
	strh r0, [r5]
	ldr r1, [sp, #4]
	ldrb r0, [r1]
	ldr r2, _0807FA84 @ =gDisableDrawingSamusAndScrollingFlag
	strb r0, [r2]
	ldr r3, [sp, #8]
	ldrh r0, [r3]
	ldr r4, _0807FA88 @ =gAtmosphericStabilizersOnline
	strh r0, [r4]
	ldr r5, [sp, #0xc]
	ldrh r0, [r5]
	ldr r1, _0807FA8C @ =gMissileGeronsDestroyed
	strh r0, [r1]
	ldr r2, [sp, #0x10]
	ldrh r0, [r2]
	ldr r3, _0807FA90 @ =gSuperMissileGeronsDestroyed
	strh r0, [r3]
	ldr r4, [sp, #0x14]
	ldrh r0, [r4]
	ldr r5, _0807FA94 @ =gPowerBombGeronsDestroyed
	strh r0, [r5]
	ldr r1, [sp, #0x18]
	ldrh r0, [r1]
	ldr r2, _0807FA98 @ =gGadorasDestroyed
	strh r0, [r2]
	ldr r3, [sp, #0x1c]
	ldrb r0, [r3]
	ldr r4, _0807FA9C @ =gMissileHatchDestroyed
	strb r0, [r4]
	ldr r5, [sp, #0x20]
	ldrb r0, [r5]
	ldr r1, _0807FAA0 @ =gWaterLowered
	strb r0, [r1]
	ldr r2, [sp, #0x24]
	ldr r0, [r2]
	ldr r3, _0807FAA4 @ =gInGameTimer
	str r0, [r3]
	ldr r4, [sp, #0x28]
	ldr r0, [r4]
	ldr r1, [r4, #4]
	mov r5, ip
	strh r0, [r5, #0x1c]
	lsrs r2, r0, #0x10
	strh r2, [r5, #0x1e]
	mov r2, ip
	adds r2, #0x20
	strb r1, [r2]
	lsrs r2, r1, #8
	mov r3, ip
	adds r3, #0x21
	strb r2, [r3]
	lsrs r0, r1, #0x10
	strh r0, [r5, #2]
	add sp, #0x2c
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807F9F8: .4byte sSaveDataEwramPointers
_0807F9FC: .4byte 0x03000B8D
_0807FA00: .4byte 0x03000014
_0807FA04: .4byte 0x03000B90
_0807FA08: .4byte gCurrentArea
_0807FA0C: .4byte gCurrentRoom
_0807FA10: .4byte gLastDoorUsed
_0807FA14: .4byte gAbilityCount
_0807FA18: .4byte gEventCounter
_0807FA1C: .4byte gPreviousNavigationConversation
_0807FA20: .4byte gPreviousCutscene
_0807FA24: .4byte 0x03000031
_0807FA28: .4byte 0x03000032
_0807FA2C: .4byte gSoundEventCounter
_0807FA30: .4byte gPreviousSoundEvent
_0807FA34: .4byte 0x0300004D
_0807FA38: .4byte gSecurityHatchLevelBackup
_0807FA3C: .4byte 0x03000124
_0807FA40: .4byte 0x03001224
_0807FA44: .4byte 0x03001226
_0807FA48: .4byte gBg1XPosition
_0807FA4C: .4byte gBg1YPosition
_0807FA50: .4byte 0x0300122C
_0807FA54: .4byte 0x0300122E
_0807FA58: .4byte 0x03001230
_0807FA5C: .4byte 0x03001232
_0807FA60: .4byte gMusicInfo
_0807FA64: .4byte 0x03000033
_0807FA68: .4byte 0x0300003B
_0807FA6C: .4byte gSamusData
_0807FA70: .4byte gSamusAnimationInfo
_0807FA74: .4byte 0x030012E4
_0807FA78: .4byte 0x030012F0
_0807FA7C: .4byte gEquipment
_0807FA80: .4byte gPreventMovementTimer
_0807FA84: .4byte gDisableDrawingSamusAndScrollingFlag
_0807FA88: .4byte gAtmosphericStabilizersOnline
_0807FA8C: .4byte gMissileGeronsDestroyed
_0807FA90: .4byte gSuperMissileGeronsDestroyed
_0807FA94: .4byte gPowerBombGeronsDestroyed
_0807FA98: .4byte gGadorasDestroyed
_0807FA9C: .4byte gMissileHatchDestroyed
_0807FAA0: .4byte gWaterLowered
_0807FAA4: .4byte gInGameTimer

	thumb_func_start Sram_StringCopy_MetroidEpisode4A
Sram_StringCopy_MetroidEpisode4A: @ 0x0807FAA8
	push {r4, lr}
	adds r4, r0, #0
	adds r3, r1, #0
	movs r2, #0
_0807FAB0:
	adds r0, r4, r2
	adds r1, r3, r2
	ldrb r1, [r1]
	strb r1, [r0]
	adds r2, #1
	cmp r2, #0xf
	ble _0807FAB0
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start Sram_StringCopy_SAVE_END
Sram_StringCopy_SAVE_END: @ 0x0807FAC4
	push {r4, lr}
	adds r4, r0, #0
	adds r3, r1, #0
	movs r2, #0
_0807FACC:
	adds r0, r4, r2
	adds r1, r3, r2
	ldrb r1, [r1]
	strb r1, [r0]
	adds r2, #1
	cmp r2, #7
	ble _0807FACC
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start SramTestFlash
SramTestFlash: @ 0x0807FAE0
	push {r4, r5, lr}
	sub sp, #0x10
	movs r5, #0
	ldr r0, _0807FB3C @ =0x03000B8E
	strb r5, [r0]
	ldr r0, _0807FB40 @ =0x085821E8 (sBlob_58217b_58225c+0x6D)
	ldr r4, _0807FB44 @ =0x0E007FE0
	adds r1, r4, #0
	movs r2, #0x10
	bl SramWriteChecked
	rsbs r1, r0, #0
	orrs r1, r0
	lsrs r5, r1, #0x1f
	adds r0, r4, #0
	mov r1, sp
	movs r2, #0x10
	bl SramWriteUnchecked
	movs r2, #0
_0807FB08:
	mov r0, sp
	adds r1, r0, r2
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	adds r2, #1
	cmp r2, #0xf
	ble _0807FB08
	ldr r1, _0807FB44 @ =0x0E007FE0
	mov r0, sp
	movs r2, #0x10
	bl SramWriteChecked
	cmp r0, #0
	beq _0807FB2A
	movs r0, #2
	orrs r5, r0
_0807FB2A:
	ldr r1, _0807FB3C @ =0x03000B8E
	rsbs r0, r5, #0
	orrs r0, r5
	lsrs r0, r0, #0x1f
	strb r0, [r1]
	add sp, #0x10
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0807FB3C: .4byte 0x03000B8E
_0807FB40: .4byte sDebugSectionInfo+0xCC
_0807FB44: .4byte 0x0E007FE0

	thumb_func_start Sram_BackupCurrentFile_Unused
Sram_BackupCurrentFile_Unused: @ 0x0807FB48
	push {lr}
	sub sp, #4
	ldr r1, _0807FB78 @ =0x0858225C (sSaveDataEwramPointers)
	ldr r0, _0807FB7C @ =0x03000B8D
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r1, r0, r1
	ldr r1, [r1]
	ldr r2, _0807FB80 @ =0x08582268 (sSaveDataEwramBackupPointers)
	adds r0, r0, r2
	ldr r2, [r0]
	movs r3, #0x90
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	bl WriteMostRecentFileBackupToSram
	add sp, #4
	pop {r0}
	bx r0
	.align 2, 0
_0807FB78: .4byte sSaveDataEwramPointers
_0807FB7C: .4byte 0x03000B8D
_0807FB80: .4byte sSaveDataEwramBackupPointers

	thumb_func_start unk_7fb84
unk_7fb84: @ 0x0807FB84
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x1c
	add r0, sp, #4
	movs r1, #0
	movs r2, #0x14
	bl memset
	ldr r2, _0807FC1C @ =0x03000B94
	movs r5, #2
_0807FB9E:
	adds r1, r2, #0
	add r0, sp, #4
	ldm r0!, {r3, r4, r6}
	stm r1!, {r3, r4, r6}
	ldm r0!, {r3, r4}
	stm r1!, {r3, r4}
	adds r2, #0x14
	subs r5, #1
	cmp r5, #0
	bge _0807FB9E
	ldr r4, _0807FC20 @ =0x03000B8D
	movs r1, #0
	strb r1, [r4]
	ldr r0, _0807FC24 @ =gIsLoadingFile
	strb r1, [r0]
	ldr r0, _0807FC28 @ =0x03000B8E
	ldrb r0, [r0]
	cmp r0, #0
	bne _0807FBC8
	bl ReadAllFilesToEwram
_0807FBC8:
	movs r5, #0
	adds r7, r4, #0
	movs r6, #0x10
	ldr r0, _0807FC1C @ =0x03000B94
	str r0, [sp, #0x18]
	ldr r1, _0807FC2C @ =0x0858225C (sSaveDataEwramPointers)
	mov sl, r1
	ldr r3, _0807FC30 @ =0x0000FFFF
	mov sb, r3
	movs r4, #0x90
	lsls r4, r4, #5
	mov r8, r4
_0807FBE0:
	strb r5, [r7]
	bl unk_7fd10
	ldrb r0, [r7]
	lsls r2, r0, #2
	adds r0, r2, r0
	lsls r0, r0, #2
	ldr r1, _0807FC1C @ =0x03000B94
	adds r0, r0, r1
	ldrb r4, [r0, #1]
	cmp r4, #0
	bne _0807FC38
	mov r3, sl
	adds r0, r2, r3
	ldr r1, [r0]
	ldr r4, _0807FC34 @ =0x08582268 (sSaveDataEwramBackupPointers)
	adds r0, r2, r4
	ldr r2, [r0]
	str r6, [sp]
	movs r0, #3
	movs r3, #0x90
	lsls r3, r3, #5
	bl DmaTransfer
	bl WriteMostRecentFileBackupToSram
	movs r0, #1
	ldr r1, [sp, #0x18]
	strb r0, [r1]
	b _0807FCE6
	.align 2, 0
_0807FC1C: .4byte 0x03000B94
_0807FC20: .4byte 0x03000B8D
_0807FC24: .4byte gIsLoadingFile
_0807FC28: .4byte 0x03000B8E
_0807FC2C: .4byte sSaveDataEwramPointers
_0807FC30: .4byte 0x0000FFFF
_0807FC34: .4byte sSaveDataEwramBackupPointers
_0807FC38:
	cmp r4, #1
	bne _0807FC60
	ldr r3, _0807FC5C @ =0x08582268 (sSaveDataEwramBackupPointers)
	adds r0, r2, r3
	ldr r1, [r0]
	mov r3, sl
	adds r0, r2, r3
	ldr r2, [r0]
	str r6, [sp]
	movs r0, #3
	movs r3, #0x90
	lsls r3, r3, #5
	bl DmaTransfer
	ldr r0, [sp, #0x18]
	strb r4, [r0]
	b _0807FCE6
	.align 2, 0
_0807FC5C: .4byte sSaveDataEwramBackupPointers
_0807FC60:
	cmp r4, #2
	bne _0807FC94
	mov r1, sl
	adds r0, r2, r1
	ldr r2, [r0]
	str r6, [sp]
	movs r0, #3
	mov r1, sb
	mov r3, r8
	bl BitFill
	ldrb r0, [r7]
	lsls r0, r0, #2
	ldr r3, _0807FC90 @ =0x08582268 (sSaveDataEwramBackupPointers)
	adds r0, r0, r3
	ldr r2, [r0]
	str r6, [sp]
	movs r0, #3
	mov r1, sb
	mov r3, r8
	bl BitFill
	b _0807FCE6
	.align 2, 0
_0807FC90: .4byte sSaveDataEwramBackupPointers
_0807FC94:
	cmp r4, #3
	bne _0807FCE4
	mov r4, sl
	adds r0, r2, r4
	ldr r2, [r0]
	str r6, [sp]
	movs r0, #3
	mov r1, sb
	mov r3, r8
	bl BitFill
	bl WriteMostRecentFileToSram
	ldrb r0, [r7]
	lsls r0, r0, #2
	ldr r1, _0807FCDC @ =0x08582268 (sSaveDataEwramBackupPointers)
	adds r0, r0, r1
	ldr r2, [r0]
	str r6, [sp]
	movs r0, #3
	mov r1, sb
	mov r3, r8
	bl BitFill
	bl WriteMostRecentFileBackupToSram
	ldrb r1, [r7]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	ldr r3, _0807FCE0 @ =0x03000B94
	adds r0, r0, r3
	movs r1, #0
	strb r1, [r0, #1]
	b _0807FCE6
	.align 2, 0
_0807FCDC: .4byte sSaveDataEwramBackupPointers
_0807FCE0: .4byte 0x03000B94
_0807FCE4:
	b _0807FCE4
_0807FCE6:
	ldr r4, [sp, #0x18]
	adds r4, #0x14
	str r4, [sp, #0x18]
	adds r5, #1
	cmp r5, #2
	bgt _0807FCF4
	b _0807FBE0
_0807FCF4:
	movs r1, #0
	ldr r0, _0807FD0C @ =0x03000B8D
	strb r1, [r0]
	add sp, #0x1c
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807FD0C: .4byte 0x03000B8D

	thumb_func_start unk_7fd10
unk_7fd10: @ 0x0807FD10
	push {r4, r5, lr}
	movs r0, #0
	bl unk_7fdb0
	adds r4, r0, #0
	movs r0, #1
	bl unk_7fdb0
	adds r2, r0, #0
	cmp r4, #0
	bne _0807FD40
	ldr r2, _0807FD38 @ =0x03000B94
	ldr r0, _0807FD3C @ =0x03000B8D
	ldrb r1, [r0]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	strb r4, [r0, #1]
	b _0807FDAA
	.align 2, 0
_0807FD38: .4byte 0x03000B94
_0807FD3C: .4byte 0x03000B8D
_0807FD40:
	cmp r4, #1
	bne _0807FD6C
	ldr r5, _0807FD64 @ =0x03000B94
	ldr r3, _0807FD68 @ =0x03000B8D
	ldrb r1, [r3]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	strb r4, [r0, #1]
	cmp r2, #0
	beq _0807FDAA
	ldrb r0, [r3]
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r5
	b _0807FDA6
	.align 2, 0
_0807FD64: .4byte 0x03000B94
_0807FD68: .4byte 0x03000B8D
_0807FD6C:
	ldr r4, _0807FD90 @ =0x03000B94
	ldr r3, _0807FD94 @ =0x03000B8D
	ldrb r0, [r3]
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
	movs r0, #3
	strb r0, [r1, #1]
	cmp r2, #0
	bne _0807FD98
	ldrb r0, [r3]
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
	movs r0, #1
	b _0807FDA8
	.align 2, 0
_0807FD90: .4byte 0x03000B94
_0807FD94: .4byte 0x03000B8D
_0807FD98:
	cmp r2, #1
	bne _0807FDAA
	ldrb r0, [r3]
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
_0807FDA6:
	movs r0, #2
_0807FDA8:
	strb r0, [r1, #1]
_0807FDAA:
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start unk_7fdb0
unk_7fdb0: @ 0x0807FDB0
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	lsls r0, r0, #0x18
	movs r5, #0
	movs r7, #0
	cmp r0, #0
	bne _0807FDC8
	ldr r1, _0807FDC4 @ =0x0858225C (sSaveDataEwramPointers)
	b _0807FDCA
	.align 2, 0
_0807FDC4: .4byte sSaveDataEwramPointers
_0807FDC8:
	ldr r1, _0807FE50 @ =0x08582268 (sSaveDataEwramBackupPointers)
_0807FDCA:
	ldr r0, _0807FE54 @ =0x03000B8D
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r4, [r0]
	adds r3, r4, #0
	movs r1, #0
	ldr r6, [r4, #0x10]
	movs r2, #0x8f
_0807FDDC:
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	ldm r3!, {r0}
	adds r1, r1, r0
	subs r2, #1
	cmp r2, #0
	bge _0807FDDC
	cmp r6, r1
	bne _0807FE0E
	ldr r0, [r4, #0x14]
	mvns r0, r0
	cmp r6, r0
	beq _0807FE12
_0807FE0E:
	movs r0, #1
	orrs r5, r0
_0807FE12:
	movs r2, #0
	ldr r6, _0807FE58 @ =0x08582200 (sBlob_58217b_58225c+0x85)
	movs r3, #1
_0807FE18:
	adds r0, r2, r6
	adds r1, r4, r2
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	beq _0807FE26
	orrs r7, r3
_0807FE26:
	adds r2, #1
	cmp r2, #0xf
	ble _0807FE18
	adds r0, r7, #0
	adds r5, r5, r0
	cmp r5, #1
	ble _0807FE46
	ldr r1, _0807FE5C @ =0x0000FFFF
	movs r3, #0x90
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	adds r2, r4, #0
	bl BitFill
_0807FE46:
	adds r0, r5, #0
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0807FE50: .4byte sSaveDataEwramBackupPointers
_0807FE54: .4byte 0x03000B8D
_0807FE58: .4byte sDebugSectionInfo+0xE4
_0807FE5C: .4byte 0x0000FFFF

	thumb_func_start SramLoad_CurrentSave
SramLoad_CurrentSave: @ 0x0807FE60
	push {lr}
	ldr r0, _0807FE8C @ =gIsLoadingFile
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #1
	bne _0807FE88
	bl SramRead_FromEwram
	bl SramRead_WorldData
	ldr r0, _0807FE90 @ =gSamusData
	movs r2, #0
	movs r1, #0x3d
	strb r1, [r0, #1]
	adds r1, r0, #0
	adds r1, #0x21
	strb r2, [r1]
	adds r0, #0x22
	strb r2, [r0]
_0807FE88:
	pop {r0}
	bx r0
	.align 2, 0
_0807FE8C: .4byte gIsLoadingFile
_0807FE90: .4byte gSamusData

	thumb_func_start SramLoad_CurrentSave_Unused
SramLoad_CurrentSave_Unused: @ 0x0807FE94
	push {lr}
	bl SramRead_FromEwram
	bl SramRead_WorldData
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start SramWrite_WorldData
SramWrite_WorldData: @ 0x0807FEA4
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #4
	ldr r1, _0807FF5C @ =0x08582274 (sUnk_582274)
	ldr r0, _0807FF60 @ =0x03000B8D
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	mov r8, r0
	ldr r1, _0807FF64 @ =0x02037C00
	movs r4, #0xe0
	lsls r4, r4, #2
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	mov r2, r8
	adds r3, r4, #0
	bl DmaTransfer
	adds r7, r4, #0
	movs r5, #0
_0807FED2:
	ldr r0, _0807FF68 @ =0x03000033
	adds r0, r5, r0
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r4, r0, r1
	movs r0, #3
	ands r0, r4
	cmp r0, #0
	beq _0807FEEA
	ldr r0, _0807FF6C @ =0x0000FFFC
	ands r4, r0
	adds r4, #4
_0807FEEA:
	cmp r4, #0
	beq _0807FF0E
	adds r1, r5, #0
	cmp r5, #0
	beq _0807FEF6
	adds r1, r5, #1
_0807FEF6:
	lsls r1, r1, #9
	ldr r0, _0807FF70 @ =0x02036000
	adds r1, r1, r0
	mov r0, r8
	adds r2, r0, r7
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	adds r3, r4, #0
	bl DmaTransfer
	adds r7, r7, r4
_0807FF0E:
	adds r5, #1
	cmp r5, #7
	ble _0807FED2
	movs r7, #0xc8
	lsls r7, r7, #4
	movs r5, #0
_0807FF1A:
	ldr r0, _0807FF74 @ =0x0300003B
	adds r0, r5, r0
	ldrb r0, [r0]
	lsls r4, r0, #2
	adds r6, r5, #1
	cmp r4, #0
	beq _0807FF48
	adds r1, r5, #0
	cmp r1, #0
	beq _0807FF30
	adds r1, r6, #0
_0807FF30:
	lsls r1, r1, #8
	ldr r0, _0807FF78 @ =0x02037200
	adds r1, r1, r0
	mov r0, r8
	adds r2, r0, r7
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	adds r3, r4, #0
	bl DmaTransfer
	adds r7, r7, r4
_0807FF48:
	adds r5, r6, #0
	cmp r5, #7
	ble _0807FF1A
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807FF5C: .4byte sUnk_582274
_0807FF60: .4byte 0x03000B8D
_0807FF64: .4byte 0x02037C00
_0807FF68: .4byte 0x03000033
_0807FF6C: .4byte 0x0000FFFC
_0807FF70: .4byte 0x02036000
_0807FF74: .4byte 0x0300003B
_0807FF78: .4byte 0x02037200
