    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start Sram_LoadingfileVblank
Sram_LoadingfileVblank: @ 0x08080950
	sub sp, #4
	mov r1, sp
	movs r0, #0
	strb r0, [r1]
	add sp, #4
	bx lr

	thumb_func_start Sram_AfterLoadingFileVblank
Sram_AfterLoadingFileVblank: @ 0x0808095C
	push {lr}
	bl UpdateAudio
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start Sram_ChecLoadSaveFileWithBlank
Sram_ChecLoadSaveFileWithBlank: @ 0x08080968
	push {lr}
	ldr r0, _08080988 @ =Sram_AfterLoadingFileVblank
	bl CallbackSetVBlank
	bl Sram_CheckLoadSaveFile
	ldr r0, _0808098C @ =Sram_LoadingfileVblank
	bl CallbackSetVBlank
	ldr r0, _08080990 @ =gIsLoadingFile
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	pop {r1}
	bx r1
	.align 2, 0
_08080988: .4byte Sram_AfterLoadingFileVblank
_0808098C: .4byte Sram_LoadingfileVblank
_08080990: .4byte gIsLoadingFile

	thumb_func_start Sram_SetCurrentFile
Sram_SetCurrentFile: @ 0x08080994
	push {r4, lr}
	ldr r1, _080809B8 @ =0x03000B8D
	ldrb r4, [r1]
	strb r0, [r1]
	ldr r2, _080809BC @ =0x03000B94
	ldrb r1, [r1]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldrb r0, [r0, #1]
	cmp r0, #1
	beq _080809C0
	cmp r0, #1
	ble _080809CE
	cmp r0, #2
	beq _080809C6
	b _080809CE
	.align 2, 0
_080809B8: .4byte 0x03000B8D
_080809BC: .4byte 0x03000B94
_080809C0:
	bl WriteMostRecentFileToSram
	b _080809CE
_080809C6:
	bl WriteMostRecentFileToSram
	bl WriteMostRecentFileBackupToSram
_080809CE:
	ldr r3, _080809E8 @ =0x03000B94
	ldr r2, _080809EC @ =0x03000B8D
	ldrb r1, [r2]
	lsls r0, r1, #2
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r3
	movs r1, #0
	strb r1, [r0, #1]
	strb r4, [r2]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080809E8: .4byte 0x03000B94
_080809EC: .4byte 0x03000B8D

