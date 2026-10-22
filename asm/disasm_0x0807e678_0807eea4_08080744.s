    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start Sram_EraseFile
Sram_EraseFile: @ 0x08080744
	push {r4, r5, lr}
	sub sp, #0x18
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	adds r5, r4, #0
	add r0, sp, #4
	movs r1, #0
	movs r2, #0x14
	bl memset
	cmp r4, #0
	bne _08080798
	ldr r1, _08080784 @ =gDisableSoftReset
	movs r0, #1
	strb r0, [r1]
	ldr r2, _08080788 @ =0x03000B94
	ldr r3, _0808078C @ =0x03000B8D
	ldrb r0, [r3]
	lsls r1, r0, #2
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r2
	add r0, sp, #4
	ldm r0!, {r2, r4, r5}
	stm r1!, {r2, r4, r5}
	ldm r0!, {r2, r4}
	stm r1!, {r2, r4}
	ldr r1, _08080790 @ =0x0000FFFF
	ldr r2, _08080794 @ =0x0858225C (sSaveDataEwramPointers)
	ldrb r0, [r3]
	b _080807AE
	.align 2, 0
_08080784: .4byte gDisableSoftReset
_08080788: .4byte 0x03000B94
_0808078C: .4byte 0x03000B8D
_08080790: .4byte 0x0000FFFF
_08080794: .4byte sSaveDataEwramPointers
_08080798:
	cmp r4, #1
	bne _080807A2
	bl WriteMostRecentFileToSram
	b _080807DE
_080807A2:
	cmp r4, #2
	bne _080807D0
	ldr r1, _080807C4 @ =0x0000FFFF
	ldr r2, _080807C8 @ =0x08582268 (sSaveDataEwramBackupPointers)
	ldr r0, _080807CC @ =0x03000B8D
	ldrb r0, [r0]
_080807AE:
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r2, [r0]
	movs r3, #0x90
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl BitFill
	b _080807DE
	.align 2, 0
_080807C4: .4byte 0x0000FFFF
_080807C8: .4byte sSaveDataEwramBackupPointers
_080807CC: .4byte 0x03000B8D
_080807D0:
	cmp r5, #3
	bne _080807D8
	bl WriteMostRecentFileBackupToSram
_080807D8:
	ldr r1, _080807E8 @ =gDisableSoftReset
	movs r0, #0
	strb r0, [r1]
_080807DE:
	add sp, #0x18
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080807E8: .4byte gDisableSoftReset

	thumb_func_start Sram_CopyFile
Sram_CopyFile: @ 0x080807EC
	push {r4, r5, r6, lr}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	adds r2, r6, #0
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	adds r0, r1, #0
	cmp r1, #0
	bne _08080844
	ldr r1, _08080834 @ =gDisableSoftReset
	movs r0, #1
	strb r0, [r1]
	ldr r4, _08080838 @ =0x03000B94
	lsls r3, r6, #2
	adds r1, r3, r6
	lsls r1, r1, #2
	ldr r5, _0808083C @ =0x03000B8D
	ldrb r2, [r5]
	lsls r0, r2, #2
	adds r0, r0, r2
	lsls r0, r0, #2
	adds r1, r1, r4
	adds r0, r0, r4
	ldm r0!, {r2, r4, r6}
	stm r1!, {r2, r4, r6}
	ldm r0!, {r2, r4}
	stm r1!, {r2, r4}
	ldr r2, _08080840 @ =0x0858225C (sSaveDataEwramPointers)
	ldrb r0, [r5]
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r1, [r0]
	adds r3, r3, r2
	ldr r2, [r3]
	b _08080872
	.align 2, 0
_08080834: .4byte gDisableSoftReset
_08080838: .4byte 0x03000B94
_0808083C: .4byte 0x03000B8D
_08080840: .4byte sSaveDataEwramPointers
_08080844:
	cmp r1, #1
	bne _0808085C
	ldr r4, _08080858 @ =0x03000B8D
	ldrb r5, [r4]
	strb r6, [r4]
	bl WriteMostRecentFileToSram
	strb r5, [r4]
	b _080808A2
	.align 2, 0
_08080858: .4byte 0x03000B8D
_0808085C:
	cmp r1, #2
	bne _0808088C
	ldr r2, _08080884 @ =0x08582268 (sSaveDataEwramBackupPointers)
	ldr r0, _08080888 @ =0x03000B8D
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r1, [r0]
	lsls r0, r6, #2
	adds r0, r0, r2
	ldr r2, [r0]
_08080872:
	movs r3, #0x90
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _080808A2
	.align 2, 0
_08080884: .4byte sSaveDataEwramBackupPointers
_08080888: .4byte 0x03000B8D
_0808088C:
	cmp r0, #3
	bne _0808089C
	ldr r4, _080808AC @ =0x03000B8D
	ldrb r5, [r4]
	strb r2, [r4]
	bl WriteMostRecentFileBackupToSram
	strb r5, [r4]
_0808089C:
	ldr r1, _080808B0 @ =gDisableSoftReset
	movs r0, #0
	strb r0, [r1]
_080808A2:
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080808AC: .4byte 0x03000B8D
_080808B0: .4byte gDisableSoftReset

