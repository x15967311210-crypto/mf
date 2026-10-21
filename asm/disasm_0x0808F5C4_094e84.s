    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start EndingHandler
EndingHandler: @ 0x08094E84
	push {r4, r5, lr}
	sub sp, #4
	movs r5, #0
	ldr r4, _08094EA0 @ =gSubGameMode1
	movs r1, #0
	ldrsh r0, [r4, r1]
	cmp r0, #1
	beq _08094ED4
	cmp r0, #1
	bgt _08094EA4
	cmp r0, #0
	beq _08094EAE
	b _08094F6A
	.align 2, 0
_08094EA0: .4byte gSubGameMode1
_08094EA4:
	cmp r0, #2
	beq _08094EE2
	cmp r0, #3
	beq _08094F00
	b _08094F6A
_08094EAE:
	str r5, [sp]
	ldr r1, _08094EC8 @ =0x040000D4
	mov r0, sp
	str r0, [r1]
	ldr r0, _08094ECC @ =gNonGameplayRam
	str r0, [r1, #4]
	ldr r0, _08094ED0 @ =0x85000150
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r0, #1
	strh r0, [r4]
	b _08094F6A
	.align 2, 0
_08094EC8: .4byte 0x040000D4
_08094ECC: .4byte gNonGameplayRam
_08094ED0: .4byte 0x85000150
_08094ED4:
	bl EndingBslCrashing
	cmp r0, #0
	beq _08094F6A
	movs r0, #2
	strh r0, [r4]
	b _08094F6A
_08094EE2:
	bl EndingInShip
	cmp r0, #0
	beq _08094F6A
	ldr r0, _08094EF8 @ =gNonGameplayRam
	ldr r1, _08094EFC @ =0x0000020E
	adds r0, r0, r1
	strh r5, [r0]
	movs r0, #3
	strh r0, [r4]
	b _08094F6A
	.align 2, 0
_08094EF8: .4byte gNonGameplayRam
_08094EFC: .4byte 0x0000020E
_08094F00:
	ldr r0, _08094F24 @ =gNonGameplayRam
	ldr r1, _08094F28 @ =0x0000020E
	adds r4, r0, r1
	ldrh r0, [r4]
	adds r0, #1
	strh r0, [r4]
	ldr r2, _08094F2C @ =gWrittenToBldy
	ldrh r1, [r2]
	cmp r1, #0xf
	bhi _08094F30
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #1
	bne _08094F66
	strh r5, [r4]
	adds r0, r1, #1
	strh r0, [r2]
	b _08094F66
	.align 2, 0
_08094F24: .4byte gNonGameplayRam
_08094F28: .4byte 0x0000020E
_08094F2C: .4byte gWrittenToBldy
_08094F30:
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #1
	bne _08094F40
	movs r0, #0
	bl Sram_ProcessEndingSave
	b _08094F66
_08094F40:
	cmp r0, #2
	bne _08094F4C
	movs r0, #1
	bl Sram_ProcessEndingSave
	b _08094F66
_08094F4C:
	cmp r0, #3
	bne _08094F58
	movs r0, #2
	bl Sram_ProcessEndingSave
	b _08094F66
_08094F58:
	cmp r0, #4
	bne _08094F66
	movs r0, #3
	bl Sram_ProcessEndingSave
	strh r5, [r4]
	movs r5, #1
_08094F66:
	bl SpecialCutsceneDrawAllOam
_08094F6A:
	adds r0, r5, #0
	add sp, #4
	pop {r4, r5}
	pop {r1}
	bx r1

	thumb_func_start EndingBslCrashingInit
EndingBslCrashingInit: @ 0x08094F74
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	sub sp, #4
	ldr r3, _080950DC @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _080950E0 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _080950E4 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _080950E8 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _080950EC @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _080950F0 @ =unk_99940
	bl CallbackSetVBlank
	movs r5, #0
	str r5, [sp]
	ldr r4, _080950F4 @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r1, _080950F8 @ =gNonGameplayRam
	mov r8, r1
	str r1, [r4, #4]
	ldr r0, _080950FC @ =0x85000150
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095100 @ =0x086238F4 (sBlob_6131c8_63a19c+0x1072C)
	ldr r1, _08095104 @ =0x06010000
	bl LZ77UncompVram
	ldr r0, _08095108 @ =0x08636C38 (sBlob_6131c8_63a19c+0x23A70)
	str r0, [r4]
	ldr r0, _0809510C @ =0x05000200
	str r0, [r4, #4]
	ldr r6, _08095110 @ =0x84000080
	str r6, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095114 @ =0x0862B5F4 (sBlob_6131c8_63a19c+0x1842C)
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _08095118 @ =0x08638C14 (sBlob_6131c8_63a19c+0x25A4C)
	ldr r1, _0809511C @ =0x0600F000
	bl LZ77UncompVram
	ldr r0, _08095120 @ =0x08639BC4 (sBlob_6131c8_63a19c+0x269FC)
	ldr r1, _08095124 @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _08095128 @ =0x08637038 (sBlob_6131c8_63a19c+0x23E70)
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	str r6, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _0809512C @ =gBg1XPosition
	strh r5, [r0]
	ldr r0, _08095130 @ =gBg1YPosition
	movs r2, #8
	strh r2, [r0]
	ldr r0, _08095134 @ =0x0300122C
	strh r5, [r0]
	ldr r0, _08095138 @ =0x0300122E
	strh r5, [r0]
	ldr r0, _0809513C @ =0x03001230
	strh r5, [r0]
	ldr r0, _08095140 @ =0x03001232
	strh r5, [r0]
	ldr r0, _08095144 @ =0x04000010
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	ldr r1, _08095148 @ =0x04000008
	ldr r3, _0809514C @ =0x00001C08
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #2
	ldr r3, _08095150 @ =0x00001E01
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #4
	ldr r3, _08095154 @ =0x00001F03
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _08095158 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _0809515C @ =0x04000054
	strh r1, [r0]
	ldr r0, _08095160 @ =gWrittenToBldalpha_Eva
	strh r2, [r0]
	ldr r1, _08095164 @ =gWrittenToBldalpha_Evb
	movs r0, #0xe
	strh r0, [r1]
	movs r1, #0x28
	rsbs r1, r1, #0
	movs r0, #5
	movs r2, #0xc8
	movs r3, #0
	bl EndingBslCrashingSetupOam
	movs r0, #4
	movs r1, #0x80
	movs r2, #0x48
	movs r3, #1
	bl EndingBslCrashingSetupOam
	movs r0, #2
	movs r1, #0xa4
	movs r2, #0x28
	movs r3, #1
	bl EndingBslCrashingSetupOam
	movs r0, #1
	movs r1, #0xa4
	movs r2, #0x28
	movs r3, #1
	bl EndingBslCrashingSetupOam
	movs r0, #3
	movs r1, #0x86
	movs r2, #0x3c
	movs r3, #1
	bl EndingBslCrashingSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r0, _08095168 @ =0x0863A19C (sCutsceneTextNone)
	mov r1, r8
	str r0, [r1]
	str r5, [sp]
	mov r2, sp
	str r2, [r4]
	ldr r0, _0809516C @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _08095170 @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r3, #0xc0
	lsls r3, r3, #5
	adds r0, r3, #0
	strh r0, [r1]
	ldr r0, _08095174 @ =EndingBslCrashingVblank
	bl CallbackSetVBlank
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080950DC: .4byte 0x04000208
_080950E0: .4byte 0x04000004
_080950E4: .4byte 0x0000FFEF
_080950E8: .4byte 0x04000200
_080950EC: .4byte 0x0000FFFD
_080950F0: .4byte unk_99940
_080950F4: .4byte 0x040000D4
_080950F8: .4byte gNonGameplayRam
_080950FC: .4byte 0x85000150
_08095100: .4byte sNextPageArrowPal+0x1074C
_08095104: .4byte 0x06010000
_08095108: .4byte sNextPageArrowPal+0x23A90
_0809510C: .4byte 0x05000200
_08095110: .4byte 0x84000080
_08095114: .4byte sNextPageArrowPal+0x1844C
_08095118: .4byte sNextPageArrowPal+0x25A6C
_0809511C: .4byte 0x0600F000
_08095120: .4byte sNextPageArrowPal+0x26A1C
_08095124: .4byte 0x0600F800
_08095128: .4byte sNextPageArrowPal+0x23E90
_0809512C: .4byte gBg1XPosition
_08095130: .4byte gBg1YPosition
_08095134: .4byte 0x0300122C
_08095138: .4byte 0x0300122E
_0809513C: .4byte 0x03001230
_08095140: .4byte 0x03001232
_08095144: .4byte 0x04000010
_08095148: .4byte 0x04000008
_0809514C: .4byte 0x00001C08
_08095150: .4byte 0x00001E01
_08095154: .4byte 0x00001F03
_08095158: .4byte gWrittenToBldy
_0809515C: .4byte 0x04000054
_08095160: .4byte gWrittenToBldalpha_Eva
_08095164: .4byte gWrittenToBldalpha_Evb
_08095168: .4byte sCutsceneTextNone
_0809516C: .4byte 0x0600D000
_08095170: .4byte 0x85000400
_08095174: .4byte EndingBslCrashingVblank

	thumb_func_start EndingShipFrontViewInit
EndingShipFrontViewInit: @ 0x08095178
	push {r4, r5, r6, lr}
	sub sp, #8
	ldr r3, _080952D4 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _080952D8 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _080952DC @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _080952E0 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _080952E4 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _080952E8 @ =unk_99940
	bl CallbackSetVBlank
	movs r5, #0
	str r5, [sp]
	ldr r4, _080952EC @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r6, _080952F0 @ =0x030016A0
	str r6, [r4, #4]
	ldr r0, _080952F4 @ =0x850000B4
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	add r1, sp, #4
	strh r5, [r1]
	str r1, [r4]
	ldr r2, _080952F8 @ =0xFFFFFDF8
	adds r0, r6, r2
	str r0, [r4, #4]
	ldr r2, _080952FC @ =0x8100007E
	str r2, [r4, #8]
	ldr r0, [r4, #8]
	strh r5, [r1]
	str r1, [r4]
	ldr r1, _08095300 @ =0xFFFFFEF4
	adds r0, r6, r1
	str r0, [r4, #4]
	str r2, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095304 @ =0x08626738 (sBlob_6131c8_63a19c+0x13570)
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _08095308 @ =0x0863929C (sBlob_6131c8_63a19c+0x260D4)
	ldr r1, _0809530C @ =0x0600F000
	bl LZ77UncompVram
	ldr r0, _08095310 @ =0x086395B8 (sBlob_6131c8_63a19c+0x263F0)
	ldr r1, _08095314 @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _08095318 @ =0x08636E38 (sBlob_6131c8_63a19c+0x23C70)
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	ldr r0, _0809531C @ =0x84000080
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095320 @ =gBg1XPosition
	strh r5, [r0]
	ldr r0, _08095324 @ =gBg1YPosition
	strh r5, [r0]
	ldr r0, _08095328 @ =0x0300122C
	strh r5, [r0]
	ldr r3, _0809532C @ =0x0300122E
	ldr r2, _08095330 @ =0x0000FFE2
	adds r0, r2, #0
	strh r0, [r3]
	ldr r0, _08095334 @ =0x03001230
	strh r5, [r0]
	ldr r0, _08095338 @ =0x03001232
	strh r5, [r0]
	ldr r0, _0809533C @ =0x04000010
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	ldr r1, _08095340 @ =0x04000008
	ldr r2, _08095344 @ =0x00001C08
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #4
	ldr r2, _08095348 @ =0x00001E02
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _0809534C @ =0x00001F03
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xbf
	strh r0, [r1]
	ldr r0, _08095350 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08095354 @ =0x04000054
	strh r1, [r0]
	ldr r0, _08095358 @ =gWrittenToBldalpha_Eva
	strh r1, [r0]
	ldr r0, _0809535C @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	ldr r2, _08095360 @ =0x04000052
	lsls r0, r1, #8
	orrs r0, r1
	strh r0, [r2]
	movs r0, #0
	ldrsh r2, [r3, r0]
	movs r0, #0xc
	movs r1, #0
	movs r3, #0
	bl EndingBslCrashingSetupOam
	movs r0, #0xa
	movs r1, #0x78
	movs r2, #0x6a
	movs r3, #1
	bl EndingBslCrashingSetupOam
	movs r0, #0xb
	movs r1, #0x78
	movs r2, #0x40
	movs r3, #0
	bl EndingBslCrashingSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r1, _08095364 @ =0xFFFFFDE4
	adds r6, r6, r1
	ldr r0, _08095368 @ =0x0863A19C (sCutsceneTextNone)
	str r0, [r6]
	str r5, [sp]
	mov r2, sp
	str r2, [r4]
	ldr r0, _0809536C @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _08095370 @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0xe0
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08095374 @ =EndingShipFrontViewVblank
	bl CallbackSetVBlank
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080952D4: .4byte 0x04000208
_080952D8: .4byte 0x04000004
_080952DC: .4byte 0x0000FFEF
_080952E0: .4byte 0x04000200
_080952E4: .4byte 0x0000FFFD
_080952E8: .4byte unk_99940
_080952EC: .4byte 0x040000D4
_080952F0: .4byte 0x030016A0
_080952F4: .4byte 0x850000B4
_080952F8: .4byte 0xFFFFFDF8
_080952FC: .4byte 0x8100007E
_08095300: .4byte 0xFFFFFEF4
_08095304: .4byte sNextPageArrowPal+0x13590
_08095308: .4byte sNextPageArrowPal+0x260F4
_0809530C: .4byte 0x0600F000
_08095310: .4byte sNextPageArrowPal+0x26410
_08095314: .4byte 0x0600F800
_08095318: .4byte sNextPageArrowPal+0x23C90
_0809531C: .4byte 0x84000080
_08095320: .4byte gBg1XPosition
_08095324: .4byte gBg1YPosition
_08095328: .4byte 0x0300122C
_0809532C: .4byte 0x0300122E
_08095330: .4byte 0x0000FFE2
_08095334: .4byte 0x03001230
_08095338: .4byte 0x03001232
_0809533C: .4byte 0x04000010
_08095340: .4byte 0x04000008
_08095344: .4byte 0x00001C08
_08095348: .4byte 0x00001E02
_0809534C: .4byte 0x00001F03
_08095350: .4byte gWrittenToBldy
_08095354: .4byte 0x04000054
_08095358: .4byte gWrittenToBldalpha_Eva
_0809535C: .4byte gWrittenToBldalpha_Evb
_08095360: .4byte 0x04000052
_08095364: .4byte 0xFFFFFDE4
_08095368: .4byte sCutsceneTextNone
_0809536C: .4byte 0x0600D000
_08095370: .4byte 0x85000400
_08095374: .4byte EndingShipFrontViewVblank

	thumb_func_start EndingBslCrashingProcess
EndingBslCrashingProcess: @ 0x08095378
	push {r4, r5, r6, lr}
	movs r5, #0
	ldr r2, _080953A4 @ =gNonGameplayRam
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrh r1, [r0]
	adds r1, #1
	strh r1, [r0]
	movs r4, #0x85
	lsls r4, r4, #2
	adds r0, r2, r4
	ldrb r0, [r0]
	adds r3, r2, #0
	cmp r0, #9
	bls _0809539A
	b _08095634
_0809539A:
	lsls r0, r0, #2
	ldr r1, _080953A8 @ =_080953AC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080953A4: .4byte gNonGameplayRam
_080953A8: .4byte _080953AC
_080953AC: @ jump table
	.4byte _080953D4 @ case 0
	.4byte _08095418 @ case 1
	.4byte _08095424 @ case 2
	.4byte _0809548C @ case 3
	.4byte _080954E4 @ case 4
	.4byte _08095534 @ case 5
	.4byte _08095556 @ case 6
	.4byte _08095578 @ case 7
	.4byte _0809559C @ case 8
	.4byte _080955EC @ case 9
_080953D4:
	ldr r4, _080953F0 @ =gWrittenToBldy
	ldrh r2, [r4]
	cmp r2, #0
	beq _080953F8
	cmp r2, #0x10
	bne _080953E6
	ldr r0, _080953F4 @ =0x0000024B
	bl SoundPlay_3b1c
_080953E6:
	ldrh r0, [r4]
	subs r0, #1
	strh r0, [r4]
	b _080955DC
	.align 2, 0
_080953F0: .4byte gWrittenToBldy
_080953F4: .4byte 0x0000024B
_080953F8:
	ldr r1, _08095414 @ =0x04000050
	movs r6, #0xc4
	lsls r6, r6, #4
	adds r0, r6, #0
	strh r0, [r1]
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r3, r1
	strh r2, [r0]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #1
	b _080955DA
	.align 2, 0
_08095414: .4byte 0x04000050
_08095418:
	movs r4, #0x84
	lsls r4, r4, #2
	adds r1, r3, r4
	movs r0, #0
	strh r0, [r1]
	b _080955DC
_08095424:
	movs r6, #0x84
	lsls r6, r6, #2
	adds r4, r3, r6
	ldrh r2, [r4]
	cmp r2, #1
	bne _08095458
	ldr r0, _0809544C @ =gWrittenToBldalpha_Eva
	movs r1, #0xa
	strh r1, [r0]
	ldr r0, _08095450 @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	movs r1, #0x88
	lsls r1, r1, #1
	adds r0, r3, r1
	movs r1, #0
	strb r2, [r0]
	ldr r2, _08095454 @ =0x00000111
	adds r0, r3, r2
	strb r1, [r0]
	b _080955DC
	.align 2, 0
_0809544C: .4byte gWrittenToBldalpha_Eva
_08095450: .4byte gWrittenToBldalpha_Evb
_08095454: .4byte 0x00000111
_08095458:
	cmp r2, #2
	beq _0809545E
	b _080955DC
_0809545E:
	ldr r1, _08095484 @ =0x04000050
	ldr r6, _08095488 @ =0x00000842
	adds r0, r6, #0
	strh r0, [r1]
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r0, [r2]
	movs r6, #0x80
	lsls r6, r6, #2
	adds r1, r6, #0
	orrs r0, r1
	strh r0, [r2]
	movs r0, #0
	strh r0, [r4]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r0, #3
	b _080955DA
	.align 2, 0
_08095484: .4byte 0x04000050
_08095488: .4byte 0x00000842
_0809548C:
	ldr r1, _080954B8 @ =0x00000111
	adds r4, r3, r1
	ldrb r2, [r4]
	cmp r2, #0xe
	bhi _080954BC
	movs r6, #0x84
	lsls r6, r6, #2
	adds r1, r3, r6
	ldrh r0, [r1]
	cmp r0, #4
	beq _080954A4
	b _080955DC
_080954A4:
	movs r0, #0
	strh r0, [r1]
	movs r0, #0x88
	lsls r0, r0, #1
	adds r1, r3, r0
	movs r0, #1
	strb r0, [r1]
	adds r0, r2, #1
	strb r0, [r4]
	b _080955DC
	.align 2, 0
_080954B8: .4byte 0x00000111
_080954BC:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r1, r3, r2
	ldrh r0, [r1]
	cmp r0, #0x14
	beq _080954CA
	b _080955DC
_080954CA:
	movs r0, #0
	strh r0, [r1]
	ldr r1, _080954E0 @ =gWrittenToBldy
	movs r0, #0x10
	strh r0, [r1]
	movs r4, #0x85
	lsls r4, r4, #2
	adds r1, r3, r4
	movs r0, #4
	b _080955DA
	.align 2, 0
_080954E0: .4byte gWrittenToBldy
_080954E4:
	ldr r4, _0809550C @ =gWrittenToBldalpha_Eva
	ldrh r2, [r4]
	cmp r2, #0xf
	bhi _08095514
	movs r6, #0x84
	lsls r6, r6, #2
	adds r1, r3, r6
	ldrh r0, [r1]
	cmp r0, #6
	bne _080955DC
	movs r0, #0
	strh r0, [r1]
	adds r0, r2, #1
	strh r0, [r4]
	ldr r1, _08095510 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r1]
	adds r0, #1
	strh r0, [r1]
	b _080955DC
	.align 2, 0
_0809550C: .4byte gWrittenToBldalpha_Eva
_08095510: .4byte gWrittenToBldalpha_Evb
_08095514:
	ldr r1, _08095530 @ =0x04000050
	movs r0, #0xbf
	strh r0, [r1]
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r0, #0
	strh r0, [r1]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #5
	b _080955DA
	.align 2, 0
_08095530: .4byte 0x04000050
_08095534:
	movs r4, #0x84
	lsls r4, r4, #2
	adds r1, r3, r4
	ldrh r0, [r1]
	cmp r0, #0xa
	beq _08095542
	b _08095634
_08095542:
	movs r0, #0
	strh r0, [r1]
	movs r6, #0x85
	lsls r6, r6, #2
	adds r1, r3, r6
	movs r0, #6
	strb r0, [r1]
	bl EndingShipFrontViewInit
	b _08095634
_08095556:
	ldr r1, _08095574 @ =0x04000050
	movs r2, #0xc4
	lsls r2, r2, #4
	adds r0, r2, #0
	strh r0, [r1]
	movs r4, #0x84
	lsls r4, r4, #2
	adds r1, r3, r4
	movs r0, #0
	strh r0, [r1]
	movs r6, #0x85
	lsls r6, r6, #2
	adds r1, r3, r6
	movs r0, #7
	b _080955DA
	.align 2, 0
_08095574: .4byte 0x04000050
_08095578:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r3, r0
	ldrh r0, [r1]
	cmp r0, #0xa8
	bne _080955DC
	movs r0, #0
	strh r0, [r1]
	ldr r1, _08095598 @ =gWrittenToBldy
	movs r0, #2
	strh r0, [r1]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #8
	b _080955DA
	.align 2, 0
_08095598: .4byte gWrittenToBldy
_0809559C:
	movs r4, #0x84
	lsls r4, r4, #2
	adds r1, r3, r4
	ldrh r0, [r1]
	cmp r0, #1
	bne _080955DC
	movs r0, #0
	strh r0, [r1]
	ldr r1, _080955C8 @ =gWrittenToBldalpha_Eva
	ldrh r0, [r1]
	cmp r0, #0
	beq _080955CC
	subs r0, #1
	strh r0, [r1]
	lsls r0, r0, #0x10
	cmp r0, #0
	bne _080955DC
	movs r0, #0xa
	bl SpecialCutsceneDestroyOamOfType
	b _080955DC
	.align 2, 0
_080955C8: .4byte gWrittenToBldalpha_Eva
_080955CC:
	ldr r1, _080955E8 @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
	movs r6, #0x85
	lsls r6, r6, #2
	adds r1, r3, r6
	movs r0, #9
_080955DA:
	strb r0, [r1]
_080955DC:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	b _08095634
	.align 2, 0
_080955E8: .4byte 0x04000050
_080955EC:
	ldr r4, _0809560C @ =gWrittenToBldy
	ldrh r2, [r4]
	cmp r2, #0xf
	bhi _08095610
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r3, r0
	ldrh r0, [r1]
	cmp r0, #4
	bne _0809562C
	adds r0, r2, #1
	strh r0, [r4]
	movs r0, #0
	strh r0, [r1]
	b _0809562C
	.align 2, 0
_0809560C: .4byte gWrittenToBldy
_08095610:
	movs r1, #0x84
	lsls r1, r1, #2
	adds r2, r3, r1
	ldrh r0, [r2]
	cmp r0, #0x5a
	bne _0809562C
	movs r0, #0
	movs r1, #0
	strh r1, [r2]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	strb r0, [r1]
	movs r5, #1
_0809562C:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_08095634:
	adds r0, r5, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1

	thumb_func_start EndingBslCrashing
EndingBslCrashing: @ 0x0809563C
	push {r4, r5, lr}
	movs r5, #0
	ldr r4, _08095654 @ =gNonGameplayRam
	ldrh r0, [r4, #8]
	cmp r0, #1
	beq _08095668
	cmp r0, #1
	bgt _08095658
	cmp r0, #0
	beq _08095662
	b _080956BC
	.align 2, 0
_08095654: .4byte gNonGameplayRam
_08095658:
	cmp r0, #2
	beq _08095680
	cmp r0, #3
	beq _0809569C
	b _080956BC
_08095662:
	bl EndingBslCrashingInit
	b _08095674
_08095668:
	bl SpecialCutsceneFadeIn
	ldr r0, _0809567C @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0
	bne _080956BC
_08095674:
	movs r0, #2
	strh r0, [r4, #8]
	b _080956BC
	.align 2, 0
_0809567C: .4byte gWrittenToBldy
_08095680:
	bl EndingBslCrashingProcess
	cmp r0, #0
	beq _080956BC
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r4, r1
	strb r5, [r0]
	subs r1, #1
	adds r0, r4, r1
	strb r5, [r0]
	movs r0, #3
	strh r0, [r4, #8]
	b _080956BC
_0809569C:
	ldr r1, _080956AC @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _080956B0
	adds r0, #1
	strh r0, [r1]
	b _080956B4
	.align 2, 0
_080956AC: .4byte gWrittenToBldy
_080956B0:
	strh r5, [r4, #8]
	movs r5, #1
_080956B4:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_080956BC:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1

	thumb_func_start EndingProcessFallingBsl
EndingProcessFallingBsl: @ 0x080956C4
	push {r4, lr}
	adds r4, r0, #0
	ldrh r0, [r4, #0xa]
	adds r0, #1
	movs r2, #0
	strh r0, [r4, #0xa]
	ldrb r1, [r4, #0x14]
	cmp r1, #0
	bne _080956E6
	ldrh r0, [r4, #0xc]
	strh r0, [r4]
	ldrh r0, [r4, #0xe]
	strh r0, [r4, #2]
	strh r1, [r4, #0xa]
	movs r0, #1
	strb r0, [r4, #0x14]
	b _08095796
_080956E6:
	cmp r1, #1
	bne _08095744
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #0x12]
	cmp r0, r3
	bne _08095702
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _08095702
	strb r2, [r4, #0x12]
_08095702:
	ldrh r0, [r4, #0xa]
	movs r1, #5
	bl __udivsi3
	ldrh r1, [r4]
	subs r1, r1, r0
	strh r1, [r4, #0xc]
	ldrh r0, [r4, #0xa]
	movs r1, #5
	bl __udivsi3
	ldrh r1, [r4, #2]
	adds r1, r1, r0
	strh r1, [r4, #0xe]
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	cmp r1, #0x50
	ble _0809572E
	movs r0, #0
	strh r0, [r4, #0xa]
	movs r0, #2
	strb r0, [r4, #0x14]
_0809572E:
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _0809573C
	ldrh r0, [r4, #6]
	subs r0, #1
	strh r0, [r4, #6]
	b _08095796
_0809573C:
	ldrh r0, [r4, #6]
	subs r0, #2
	strh r0, [r4, #6]
	b _08095796
_08095744:
	cmp r1, #2
	bne _08095770
	movs r0, #3
	strb r0, [r4, #0x14]
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _0809578A
	ldr r0, _08095768 @ =0x086362B8 (sBlob_6131c8_63a19c+0x230F0)
	str r0, [r4, #0x1c]
	strb r2, [r4, #0x12]
	strb r2, [r4, #0x11]
	ldr r0, _0809576C @ =gNonGameplayRam
	movs r2, #0x85
	lsls r2, r2, #2
	adds r0, r0, r2
	strb r1, [r0]
	b _08095796
	.align 2, 0
_08095768: .4byte sNextPageArrowPal+0x23110
_0809576C: .4byte gNonGameplayRam
_08095770:
	cmp r1, #3
	bne _08095796
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #0x12]
	cmp r0, r3
	bne _08095796
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _08095796
_0809578A:
	strb r2, [r4, #0x10]
	ldrb r1, [r4, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r4, #0x18]
_08095796:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start unk_9579c
unk_9579c: @ 0x0809579C
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _080957C8
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _080957C8
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080957C8
	strb r1, [r2, #0x10]
	ldrb r1, [r2, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2, #0x18]
_080957C8:
	pop {r0}
	bx r0

	thumb_func_start EndingProcessLeavingSmallShip
EndingProcessLeavingSmallShip: @ 0x080957CC
	push {r4, r5, lr}
	adds r5, r0, #0
	ldrh r0, [r5, #0xa]
	adds r2, r0, #1
	strh r2, [r5, #0xa]
	ldrb r1, [r5, #0x14]
	cmp r1, #0
	bne _080957FC
	ldrh r0, [r5, #0xc]
	strh r0, [r5]
	ldrh r0, [r5, #0xe]
	strh r0, [r5, #2]
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x96
	bne _0809582A
	strh r1, [r5, #0xa]
	ldrb r0, [r5, #0x18]
	movs r1, #1
	orrs r0, r1
	strb r0, [r5, #0x18]
	movs r0, #1
	strb r0, [r5, #0x14]
	b _0809582A
_080957FC:
	cmp r1, #1
	bne _0809582A
	lsls r0, r2, #2
	ldrh r4, [r5]
	subs r4, r4, r0
	strh r4, [r5, #0xc]
	ldrh r0, [r5, #0xa]
	movs r1, #3
	bl __udivsi3
	ldrh r1, [r5, #2]
	adds r1, r1, r0
	strh r1, [r5, #0xe]
	lsls r4, r4, #0x10
	cmp r4, #0
	bge _0809582A
	movs r0, #0
	strb r0, [r5, #0x10]
	ldrb r1, [r5, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r5, #0x18]
_0809582A:
	pop {r4, r5}
	pop {r0}
	bx r0

	thumb_func_start EndingProcessLeavingBigShip
EndingProcessLeavingBigShip: @ 0x08095830
	push {lr}
	adds r3, r0, #0
	ldrh r0, [r3, #0xa]
	adds r2, r0, #1
	strh r2, [r3, #0xa]
	ldrb r1, [r3, #0x14]
	cmp r1, #0
	bne _08095860
	ldrh r0, [r3, #0xc]
	strh r0, [r3]
	ldrh r0, [r3, #0xe]
	strh r0, [r3, #2]
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xf0
	bne _08095890
	strh r1, [r3, #0xa]
	ldrb r0, [r3, #0x18]
	movs r1, #1
	orrs r0, r1
	strb r0, [r3, #0x18]
	movs r0, #1
	strb r0, [r3, #0x14]
	b _08095890
_08095860:
	cmp r1, #1
	bne _08095890
	lsls r2, r2, #2
	ldrh r0, [r3]
	adds r2, r2, r0
	strh r2, [r3, #0xc]
	ldrh r0, [r3, #0xa]
	lsls r1, r0, #1
	adds r1, r1, r0
	ldrh r0, [r3, #2]
	subs r0, r0, r1
	strh r0, [r3, #0xe]
	lsls r2, r2, #0x10
	movs r0, #0x8c
	lsls r0, r0, #0x11
	cmp r2, r0
	ble _08095890
	movs r0, #0
	strb r0, [r3, #0x10]
	ldrb r1, [r3, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r3, #0x18]
_08095890:
	pop {r0}
	bx r0

	thumb_func_start EndingProcessFrontFacingShipThrusters
EndingProcessFrontFacingShipThrusters: @ 0x08095894
	push {r4, r5, lr}
	sub sp, #4
	adds r5, r0, #0
	ldrb r0, [r5, #0x14]
	cmp r0, #0
	bne _080958A8
	ldrh r0, [r5, #0xe]
	strh r0, [r5, #2]
	movs r0, #1
	strb r0, [r5, #0x14]
_080958A8:
	mov r4, sp
	adds r4, #2
	movs r0, #0xc
	mov r1, sp
	adds r2, r4, #0
	bl EndingGetPositionAndSlotOfOamByType
	ldrh r0, [r5, #2]
	ldrh r1, [r4]
	subs r0, r0, r1
	strh r0, [r5, #0xe]
	add sp, #4
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start EndingProcessFrontFacingShip
EndingProcessFrontFacingShip: @ 0x080958C8
	push {r4, lr}
	adds r3, r0, #0
	ldrh r0, [r3, #0xa]
	adds r0, #1
	movs r4, #0
	strh r0, [r3, #0xa]
	ldrb r1, [r3, #0x14]
	cmp r1, #0
	bne _080958EA
	ldrh r0, [r3, #0xe]
	strh r0, [r3, #2]
	strh r4, [r3, #0xa]
	movs r0, #4
	strb r0, [r3, #0x13]
	movs r0, #1
	strb r0, [r3, #0x14]
	b _08095944
_080958EA:
	cmp r1, #1
	bne _0809591C
	ldrb r1, [r3, #0x13]
	adds r1, #1
	strb r1, [r3, #0x13]
	ldr r2, _08095918 @ =0x080A4FA4 (sSineTable)
	ldrb r0, [r3, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x13
	ldrh r2, [r3, #2]
	adds r0, r0, r2
	strh r0, [r3, #0xe]
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	cmp r1, #0x40
	bne _08095944
	movs r0, #2
	strb r0, [r3, #0x14]
	strh r4, [r3, #0xa]
	b _08095944
	.align 2, 0
_08095918: .4byte sSineTable
_0809591C:
	cmp r1, #2
	bne _08095944
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bne _08095930
	strh r4, [r3, #0xa]
	ldrb r0, [r3, #0x13]
	adds r0, #1
	strb r0, [r3, #0x13]
_08095930:
	ldr r1, _08095950 @ =0x080A4FA4 (sSineTable)
	ldrb r0, [r3, #0x13]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r0, [r0]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x13
	ldrh r1, [r3, #2]
	adds r0, r0, r1
	strh r0, [r3, #0xe]
_08095944:
	ldr r1, _08095954 @ =0x0300122E
	ldrh r0, [r3, #0xe]
	strh r0, [r1]
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08095950: .4byte sSineTable
_08095954: .4byte 0x0300122E

	thumb_func_start EndingBslCrashingSetupOam
EndingBslCrashingSetupOam: @ 0x08095958
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r6, r0, #0x18
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	mov r8, r1
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	mov sb, r2
	lsls r3, r3, #0x18
	cmp r3, #0
	bne _080959BC
	movs r2, #0
	ldr r1, _080959B8 @ =gNonGameplayRam
	movs r3, #0x8b
	lsls r3, r3, #2
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, #0
	beq _080959AA
	adds r4, r1, #0
_0809598A:
	lsls r0, r2, #0x18
	movs r1, #0x80
	lsls r1, r1, #0x11
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0x13
	bgt _080959FA
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _0809598A
_080959AA:
	lsls r0, r2, #0x18
	asrs r1, r0, #0x18
	adds r7, r0, #0
	cmp r1, #0x13
	ble _08095A04
	b _080959FA
	.align 2, 0
_080959B8: .4byte gNonGameplayRam
_080959BC:
	movs r2, #0x13
	ldr r1, _08095A00 @ =gNonGameplayRam
	movs r3, #0x9b
	lsls r3, r3, #3
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, #0
	beq _080959F2
	adds r4, r1, #0
	movs r3, #0x8b
	lsls r3, r3, #2
_080959D2:
	lsls r0, r2, #0x18
	movs r1, #0xff
	lsls r1, r1, #0x18
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0
	blt _080959FA
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _080959D2
_080959F2:
	lsls r0, r2, #0x18
	adds r7, r0, #0
	cmp r7, #0
	bge _08095A04
_080959FA:
	movs r0, #0x14
	b _08095C3E
	.align 2, 0
_08095A00: .4byte gNonGameplayRam
_08095A04:
	movs r0, #0
	str r0, [sp]
	ldr r2, _08095A94 @ =0x040000D4
	mov r3, sp
	str r3, [r2]
	asrs r1, r7, #0x18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r5, r0, #2
	ldr r0, _08095A98 @ =0x030016A0
	mov ip, r0
	adds r0, r5, r0
	str r0, [r2, #4]
	ldr r0, _08095A9C @ =0x85000009
	str r0, [r2, #8]
	ldr r0, [r2, #8]
	ldr r0, _08095AA0 @ =0xFFFFFDE4
	add r0, ip
	adds r2, r5, r0
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r0, r2, r1
	mov r3, r8
	strh r3, [r0]
	adds r1, #2
	adds r0, r2, r1
	mov r3, sb
	strh r3, [r0]
	adds r1, #2
	adds r0, r2, r1
	strb r6, [r0]
	movs r3, #0x8d
	lsls r3, r3, #2
	adds r4, r2, r3
	ldrb r1, [r4]
	movs r0, #1
	orrs r1, r0
	strb r1, [r4]
	cmp r6, #1
	bne _08095AB4
	ldr r0, _08095AA4 @ =0x00000222
	adds r1, r2, r0
	movs r0, #0x80
	lsls r0, r0, #1
	strh r0, [r1]
	ldr r1, _08095AA8 @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	ldrb r1, [r4]
	movs r0, #7
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095AAC @ =0x08636020 (sBlob_6131c8_63a19c+0x22E58)
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095AB0 @ =EndingProcessFallingBsl
	b _08095C3A
	.align 2, 0
_08095A94: .4byte 0x040000D4
_08095A98: .4byte 0x030016A0
_08095A9C: .4byte 0x85000009
_08095AA0: .4byte 0xFFFFFDE4
_08095AA4: .4byte 0x00000222
_08095AA8: .4byte 0x00000236
_08095AAC: .4byte sNextPageArrowPal+0x22E78
_08095AB0: .4byte EndingProcessFallingBsl
_08095AB4:
	cmp r6, #2
	bne _08095B14
	ldr r3, _08095B04 @ =0x00000222
	adds r1, r2, r3
	movs r0, #0x80
	lsls r0, r0, #2
	strh r0, [r1]
	ldrb r1, [r4]
	movs r0, #0x19
	rsbs r0, r0, #0
	ands r0, r1
	movs r3, #8
	orrs r0, r3
	strb r0, [r4]
	ldr r0, _08095B08 @ =0x00000236
	adds r2, r2, r0
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r3
	strb r0, [r2]
	ldrb r1, [r4]
	movs r0, #7
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095B0C @ =0x08636038 (sBlob_6131c8_63a19c+0x22E70)
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095B10 @ =EndingProcessFallingBsl
	b _08095C3A
	.align 2, 0
_08095B04: .4byte 0x00000222
_08095B08: .4byte 0x00000236
_08095B0C: .4byte sNextPageArrowPal+0x22E90
_08095B10: .4byte EndingProcessFallingBsl
_08095B14:
	cmp r6, #3
	bne _08095B4C
	ldr r1, _08095B40 @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095B44 @ =0x08636050 (sBlob_6131c8_63a19c+0x22E88)
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095B48 @ =unk_9579c
	b _08095C3A
	.align 2, 0
_08095B40: .4byte 0x00000236
_08095B44: .4byte sNextPageArrowPal+0x22EA8
_08095B48: .4byte unk_9579c
_08095B4C:
	cmp r6, #4
	bne _08095B88
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r4]
	ldr r3, _08095B7C @ =0x00000236
	adds r2, r2, r3
	ldrb r1, [r2]
	subs r0, #0xb
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095B80 @ =0x08636288 (sBlob_6131c8_63a19c+0x230C0)
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095B84 @ =EndingProcessLeavingSmallShip
	b _08095C3A
	.align 2, 0
_08095B7C: .4byte 0x00000236
_08095B80: .4byte sNextPageArrowPal+0x230E0
_08095B84: .4byte EndingProcessLeavingSmallShip
_08095B88:
	cmp r6, #5
	bne _08095BB0
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r4]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095BA8 @ =0x086362A0 (sBlob_6131c8_63a19c+0x230D8)
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095BAC @ =EndingProcessLeavingBigShip
	b _08095C3A
	.align 2, 0
_08095BA8: .4byte sNextPageArrowPal+0x230F8
_08095BAC: .4byte EndingProcessLeavingBigShip
_08095BB0:
	cmp r6, #0xa
	bne _08095BEC
	movs r0, #0x19
	rsbs r0, r0, #0
	ands r1, r0
	movs r0, #8
	orrs r1, r0
	strb r1, [r4]
	ldr r0, _08095BE0 @ =0x00000236
	adds r2, r2, r0
	ldrb r0, [r2]
	movs r1, #0xc
	orrs r0, r1
	strb r0, [r2]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095BE4 @ =0x086363A0 (sBlob_6131c8_63a19c+0x231D8)
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095BE8 @ =unk_95e20
	b _08095C3A
	.align 2, 0
_08095BE0: .4byte 0x00000236
_08095BE4: .4byte sNextPageArrowPal+0x231F8
_08095BE8: .4byte unk_95e20
_08095BEC:
	cmp r6, #0xb
	bne _08095C1C
	ldr r1, _08095C10 @ =0x00000236
	adds r2, r2, r1
	ldrb r0, [r2]
	movs r1, #0xc
	orrs r0, r1
	strb r0, [r2]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095C14 @ =0x086363B8 (sBlob_6131c8_63a19c+0x231F0)
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095C18 @ =EndingProcessFrontFacingShipThrusters
	b _08095C3A
	.align 2, 0
_08095C10: .4byte 0x00000236
_08095C14: .4byte sNextPageArrowPal+0x23210
_08095C18: .4byte EndingProcessFrontFacingShipThrusters
_08095C1C:
	cmp r6, #0xc
	bne _08095C3C
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r4]
	mov r0, ip
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08095C4C @ =0x086363A0 (sBlob_6131c8_63a19c+0x231D8)
	str r1, [r0]
	mov r0, ip
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08095C50 @ =EndingProcessFrontFacingShip
_08095C3A:
	str r1, [r0]
_08095C3C:
	lsrs r0, r7, #0x18
_08095C3E:
	add sp, #4
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08095C4C: .4byte sNextPageArrowPal+0x231F8
_08095C50: .4byte EndingProcessFrontFacingShip

	thumb_func_start EndingBslCrashingVblank
EndingBslCrashingVblank: @ 0x08095C54
	push {lr}
	ldr r3, _08095CE0 @ =0x040000D4
	ldr r0, _08095CE4 @ =gOamData
	str r0, [r3]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r3, #4]
	ldr r0, _08095CE8 @ =0x84000100
	str r0, [r3, #8]
	ldr r0, [r3, #8]
	ldr r2, _08095CEC @ =0x04000052
	ldr r0, _08095CF0 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08095CF4 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08095CF8 @ =0x04000054
	ldr r0, _08095CFC @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x40
	ldr r0, _08095D00 @ =gBg1XPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095D04 @ =gBg1YPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095D08 @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095D0C @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095D10 @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095D14 @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _08095D18 @ =gNonGameplayRam
	movs r0, #0x88
	lsls r0, r0, #1
	adds r2, r1, r0
	ldrb r0, [r2]
	cmp r0, #1
	bne _08095CDA
	movs r0, #0
	strb r0, [r2]
	ldr r2, _08095D1C @ =0x00000111
	adds r0, r1, r2
	ldrb r0, [r0]
	lsls r0, r0, #5
	ldr r1, _08095D20 @ =0x08636A38 (sBlob_6131c8_63a19c+0x23870)
	adds r0, r0, r1
	str r0, [r3]
	ldr r0, _08095D24 @ =0x05000120
	str r0, [r3, #4]
	ldr r0, _08095D28 @ =0x84000008
	str r0, [r3, #8]
	ldr r0, [r3, #8]
_08095CDA:
	pop {r0}
	bx r0
	.align 2, 0
_08095CE0: .4byte 0x040000D4
_08095CE4: .4byte gOamData
_08095CE8: .4byte 0x84000100
_08095CEC: .4byte 0x04000052
_08095CF0: .4byte gWrittenToBldalpha_Evb
_08095CF4: .4byte gWrittenToBldalpha_Eva
_08095CF8: .4byte 0x04000054
_08095CFC: .4byte gWrittenToBldy
_08095D00: .4byte gBg1XPosition
_08095D04: .4byte gBg1YPosition
_08095D08: .4byte 0x0300122C
_08095D0C: .4byte 0x0300122E
_08095D10: .4byte 0x03001230
_08095D14: .4byte 0x03001232
_08095D18: .4byte gNonGameplayRam
_08095D1C: .4byte 0x00000111
_08095D20: .4byte sNextPageArrowPal+0x23890
_08095D24: .4byte 0x05000120
_08095D28: .4byte 0x84000008

	thumb_func_start EndingShipFrontViewVblank
EndingShipFrontViewVblank: @ 0x08095D2C
	ldr r1, _08095D88 @ =0x040000D4
	ldr r0, _08095D8C @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08095D90 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r2, _08095D94 @ =0x04000052
	ldr r0, _08095D98 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08095D9C @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08095DA0 @ =0x04000054
	ldr r0, _08095DA4 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x40
	ldr r0, _08095DA8 @ =gBg1XPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095DAC @ =gBg1YPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095DB0 @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095DB4 @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095DB8 @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08095DBC @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	bx lr
	.align 2, 0
_08095D88: .4byte 0x040000D4
_08095D8C: .4byte gOamData
_08095D90: .4byte 0x84000100
_08095D94: .4byte 0x04000052
_08095D98: .4byte gWrittenToBldalpha_Evb
_08095D9C: .4byte gWrittenToBldalpha_Eva
_08095DA0: .4byte 0x04000054
_08095DA4: .4byte gWrittenToBldy
_08095DA8: .4byte gBg1XPosition
_08095DAC: .4byte gBg1YPosition
_08095DB0: .4byte 0x0300122C
_08095DB4: .4byte 0x0300122E
_08095DB8: .4byte 0x03001230
_08095DBC: .4byte 0x03001232

	thumb_func_start EndingGetPositionAndSlotOfOamByType
EndingGetPositionAndSlotOfOamByType: @ 0x08095DC0
	push {r4, r5, r6, r7, lr}
	adds r4, r1, #0
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	movs r1, #0
	ldr r7, _08095DF8 @ =gNonGameplayRam
	movs r6, #0x8b
	lsls r6, r6, #2
_08095DD0:
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r3, r0, r7
	adds r0, r3, r6
	ldrb r0, [r0]
	cmp r0, r5
	bne _08095E00
	movs r5, #0x8a
	lsls r5, r5, #2
	adds r0, r3, r5
	ldrh r0, [r0]
	strh r0, [r4]
	ldr r4, _08095DFC @ =0x0000022A
	adds r0, r3, r4
	ldrh r0, [r0]
	strh r0, [r2]
	adds r0, r1, #0
	b _08095E18
	.align 2, 0
_08095DF8: .4byte gNonGameplayRam
_08095DFC: .4byte 0x0000022A
_08095E00:
	adds r0, r1, #1
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0x13
	bls _08095DD0
	movs r5, #0x96
	lsls r5, r5, #1
	adds r0, r5, #0
	strh r0, [r4]
	movs r0, #0xc8
	strh r0, [r2]
	movs r0, #0x14
_08095E18:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start unk_95e20
unk_95e20: @ 0x08095E20
	bx lr
	.align 2, 0

	thumb_func_start EndingMonologueInit
EndingMonologueInit: @ 0x08095E24
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	sub sp, #4
	ldr r3, _08095F78 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _08095F7C @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08095F80 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08095F84 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _08095F88 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _08095F8C @ =unk_99940
	bl CallbackSetVBlank
	movs r6, #0
	str r6, [sp]
	ldr r4, _08095F90 @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r1, _08095F94 @ =gNonGameplayRam
	mov r8, r1
	str r1, [r4, #4]
	ldr r0, _08095F98 @ =0x85000150
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095F9C @ =0x086150E8 (sBlob_6131c8_63a19c+0x1F20)
	ldr r1, _08095FA0 @ =0x06010000
	bl LZ77UncompVram
	ldr r0, _08095FA4 @ =0x08636638 (sBlob_6131c8_63a19c+0x23470)
	str r0, [r4]
	ldr r0, _08095FA8 @ =0x05000200
	str r0, [r4, #4]
	ldr r5, _08095FAC @ =0x84000080
	str r5, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095FB0 @ =0x086186A4 (sBlob_6131c8_63a19c+0x54DC)
	ldr r1, _08095FB4 @ =0x06008000
	bl LZ77UncompVram
	ldr r0, _08095FB8 @ =0x086377F8 (sBlob_6131c8_63a19c+0x24630)
	ldr r1, _08095FBC @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _08095FC0 @ =0x08636438 (sBlob_6131c8_63a19c+0x23270)
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	str r5, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095FC4 @ =0x08662804 (sIntroTilemap_662804)
	movs r5, #0x80
	lsls r5, r5, #0x12
	adds r1, r5, #0
	bl LZ77UncompWram
	str r5, [r4]
	ldr r0, _08095FC8 @ =0x06004800
	str r0, [r4, #4]
	ldr r0, _08095FCC @ =0x84000200
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	str r6, [sp]
	mov r2, sp
	str r2, [r4]
	movs r0, #0xc0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	ldr r0, _08095FD0 @ =0x85001200
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095FD4 @ =0x08663820 (sIntroPal_663820)
	str r0, [r4]
	ldr r0, _08095FD8 @ =0x05000180
	str r0, [r4, #4]
	ldr r0, _08095FDC @ =0x84000020
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08095FE0 @ =gBg1XPosition
	strh r6, [r0]
	ldr r0, _08095FE4 @ =gBg1YPosition
	strh r6, [r0]
	ldr r0, _08095FE8 @ =0x0300122C
	strh r6, [r0]
	ldr r0, _08095FEC @ =0x0300122E
	strh r6, [r0]
	ldr r0, _08095FF0 @ =0x03001230
	strh r6, [r0]
	ldr r0, _08095FF4 @ =0x03001232
	strh r6, [r0]
	ldr r0, _08095FF8 @ =0x04000010
	strh r6, [r0]
	ldr r1, _08095FFC @ =0x04000012
	movs r0, #4
	strh r0, [r1]
	ldr r0, _08096000 @ =0x04000014
	strh r6, [r0]
	adds r0, #2
	strh r6, [r0]
	adds r0, #2
	strh r6, [r0]
	adds r0, #2
	strh r6, [r0]
	adds r0, #2
	strh r6, [r0]
	adds r0, #2
	strh r6, [r0]
	subs r1, #0xa
	movs r2, #0x90
	lsls r2, r2, #4
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _08096004 @ =0x00001E01
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #4
	ldr r2, _08096008 @ =0x00001F0B
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _0809600C @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08096010 @ =0x04000054
	strh r1, [r0]
	ldr r0, _08096014 @ =gWrittenToBldalpha_Eva
	strh r6, [r0]
	ldr r0, _08096018 @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	movs r1, #0x82
	lsls r1, r1, #1
	movs r0, #1
	movs r2, #0xb4
	movs r3, #0
	bl EndingDialogueSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r0, _0809601C @ =0x0863A19C (sCutsceneTextNone)
	mov r1, r8
	str r0, [r1]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0xc0
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08096020 @ =EndingMonologueVblank
	bl CallbackSetVBlank
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08095F78: .4byte 0x04000208
_08095F7C: .4byte 0x04000004
_08095F80: .4byte 0x0000FFEF
_08095F84: .4byte 0x04000200
_08095F88: .4byte 0x0000FFFD
_08095F8C: .4byte unk_99940
_08095F90: .4byte 0x040000D4
_08095F94: .4byte gNonGameplayRam
_08095F98: .4byte 0x85000150
_08095F9C: .4byte sNextPageArrowPal+0x1F40
_08095FA0: .4byte 0x06010000
_08095FA4: .4byte sNextPageArrowPal+0x23490
_08095FA8: .4byte 0x05000200
_08095FAC: .4byte 0x84000080
_08095FB0: .4byte sNextPageArrowPal+0x54FC
_08095FB4: .4byte 0x06008000
_08095FB8: .4byte sNextPageArrowPal+0x24650
_08095FBC: .4byte 0x0600F800
_08095FC0: .4byte sNextPageArrowPal+0x23290
_08095FC4: .4byte sIntroTilemap_662804
_08095FC8: .4byte 0x06004800
_08095FCC: .4byte 0x84000200
_08095FD0: .4byte 0x85001200
_08095FD4: .4byte sIntroPal_663820
_08095FD8: .4byte 0x05000180
_08095FDC: .4byte 0x84000020
_08095FE0: .4byte gBg1XPosition
_08095FE4: .4byte gBg1YPosition
_08095FE8: .4byte 0x0300122C
_08095FEC: .4byte 0x0300122E
_08095FF0: .4byte 0x03001230
_08095FF4: .4byte 0x03001232
_08095FF8: .4byte 0x04000010
_08095FFC: .4byte 0x04000012
_08096000: .4byte 0x04000014
_08096004: .4byte 0x00001E01
_08096008: .4byte 0x00001F0B
_0809600C: .4byte gWrittenToBldy
_08096010: .4byte 0x04000054
_08096014: .4byte gWrittenToBldalpha_Eva
_08096018: .4byte gWrittenToBldalpha_Evb
_0809601C: .4byte sCutsceneTextNone
_08096020: .4byte EndingMonologueVblank

	thumb_func_start EndingAdamConversationInit
EndingAdamConversationInit: @ 0x08096024
	push {r4, r5, r6, lr}
	sub sp, #8
	ldr r3, _0809617C @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _08096180 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08096184 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08096188 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _0809618C @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _08096190 @ =unk_99940
	bl CallbackSetVBlank
	movs r5, #0
	str r5, [sp]
	ldr r4, _08096194 @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r6, _08096198 @ =0x030016A0
	str r6, [r4, #4]
	ldr r0, _0809619C @ =0x850000B4
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	add r1, sp, #4
	strh r5, [r1]
	str r1, [r4]
	ldr r2, _080961A0 @ =0xFFFFFDF8
	adds r0, r6, r2
	str r0, [r4, #4]
	ldr r2, _080961A4 @ =0x8100007E
	str r2, [r4, #8]
	ldr r0, [r4, #8]
	strh r5, [r1]
	str r1, [r4]
	ldr r1, _080961A8 @ =0xFFFFFEF4
	adds r0, r6, r1
	str r0, [r4, #4]
	str r2, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080961AC @ =0x086131C8 (sBlob_6131c8_63a19c)
	ldr r1, _080961B0 @ =0x06008000
	bl LZ77UncompVram
	ldr r0, _080961B4 @ =0x08637238 (sBlob_6131c8_63a19c+0x24070)
	ldr r1, _080961B8 @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _080961BC @ =0x08598898 (sIntroSamusShipFlyingTextTilemap)
	ldr r1, _080961C0 @ =0x0600E000
	bl LZ77UncompVram
	ldr r0, _080961C4 @ =0x08636438 (sBlob_6131c8_63a19c+0x23270)
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	ldr r0, _080961C8 @ =0x84000080
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080961CC @ =0x03001224
	ldr r1, _080961D0 @ =0x0000FFF8
	adds r2, r1, #0
	strh r2, [r0]
	ldr r0, _080961D4 @ =0x03001226
	movs r1, #8
	strh r1, [r0]
	ldr r0, _080961D8 @ =gBg1XPosition
	strh r5, [r0]
	ldr r0, _080961DC @ =gBg1YPosition
	strh r5, [r0]
	ldr r0, _080961E0 @ =0x0300122C
	strh r5, [r0]
	ldr r0, _080961E4 @ =0x0300122E
	strh r5, [r0]
	ldr r0, _080961E8 @ =0x03001230
	strh r5, [r0]
	ldr r0, _080961EC @ =0x03001232
	strh r5, [r0]
	ldr r0, _080961F0 @ =0x04000010
	strh r2, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	ldr r1, _080961F4 @ =0x04000008
	ldr r2, _080961F8 @ =0x00001C08
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #6
	ldr r2, _080961FC @ =0x00001F0B
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _08096200 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08096204 @ =0x04000054
	strh r1, [r0]
	ldr r0, _08096208 @ =gWrittenToBldalpha_Eva
	strh r1, [r0]
	ldr r0, _0809620C @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	ldr r2, _08096210 @ =0x04000052
	lsls r0, r1, #8
	orrs r0, r1
	strh r0, [r2]
	movs r0, #2
	movs r1, #0x70
	movs r2, #0x50
	movs r3, #1
	bl EndingDialogueSetupOam
	movs r0, #3
	movs r1, #0x70
	movs r2, #0x50
	movs r3, #1
	bl EndingDialogueSetupOam
	movs r0, #4
	movs r1, #0x70
	movs r2, #0x50
	movs r3, #1
	bl EndingDialogueSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r0, _08096214 @ =0xFFFFFDE4
	adds r6, r6, r0
	ldr r0, _08096218 @ =0x0863A19C (sCutsceneTextNone)
	str r0, [r6]
	str r5, [sp]
	mov r1, sp
	str r1, [r4]
	ldr r0, _0809621C @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _08096220 @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0xc8
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08096224 @ =EndingConversationAndAnimalsVblank
	bl CallbackSetVBlank
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809617C: .4byte 0x04000208
_08096180: .4byte 0x04000004
_08096184: .4byte 0x0000FFEF
_08096188: .4byte 0x04000200
_0809618C: .4byte 0x0000FFFD
_08096190: .4byte unk_99940
_08096194: .4byte 0x040000D4
_08096198: .4byte 0x030016A0
_0809619C: .4byte 0x850000B4
_080961A0: .4byte 0xFFFFFDF8
_080961A4: .4byte 0x8100007E
_080961A8: .4byte 0xFFFFFEF4
_080961AC: .4byte sNextPageArrowPal+0x20
_080961B0: .4byte 0x06008000
_080961B4: .4byte sNextPageArrowPal+0x24090
_080961B8: .4byte 0x0600F800
_080961BC: .4byte sIntroSamusShipFlyingTextTilemap
_080961C0: .4byte 0x0600E000
_080961C4: .4byte sNextPageArrowPal+0x23290
_080961C8: .4byte 0x84000080
_080961CC: .4byte 0x03001224
_080961D0: .4byte 0x0000FFF8
_080961D4: .4byte 0x03001226
_080961D8: .4byte gBg1XPosition
_080961DC: .4byte gBg1YPosition
_080961E0: .4byte 0x0300122C
_080961E4: .4byte 0x0300122E
_080961E8: .4byte 0x03001230
_080961EC: .4byte 0x03001232
_080961F0: .4byte 0x04000010
_080961F4: .4byte 0x04000008
_080961F8: .4byte 0x00001C08
_080961FC: .4byte 0x00001F0B
_08096200: .4byte gWrittenToBldy
_08096204: .4byte 0x04000054
_08096208: .4byte gWrittenToBldalpha_Eva
_0809620C: .4byte gWrittenToBldalpha_Evb
_08096210: .4byte 0x04000052
_08096214: .4byte 0xFFFFFDE4
_08096218: .4byte sCutsceneTextNone
_0809621C: .4byte 0x0600D000
_08096220: .4byte 0x85000400
_08096224: .4byte EndingConversationAndAnimalsVblank

	thumb_func_start EndingAnimalsInit
EndingAnimalsInit: @ 0x08096228
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	sub sp, #8
	ldr r3, _08096390 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _08096394 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08096398 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _0809639C @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _080963A0 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _080963A4 @ =unk_99940
	bl CallbackSetVBlank
	movs r5, #0
	str r5, [sp]
	ldr r4, _080963A8 @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r1, _080963AC @ =0x030016A0
	mov r8, r1
	str r1, [r4, #4]
	ldr r0, _080963B0 @ =0x850000B4
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	add r6, sp, #4
	strh r5, [r6]
	str r6, [r4]
	ldr r0, _080963B4 @ =0xFFFFFDF8
	add r0, r8
	str r0, [r4, #4]
	ldr r1, _080963B8 @ =0x8100007E
	str r1, [r4, #8]
	ldr r0, [r4, #8]
	strh r5, [r6]
	str r6, [r4]
	ldr r0, _080963BC @ =0xFFFFFEF4
	add r0, r8
	str r0, [r4, #4]
	str r1, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080963C0 @ =0x0861B89C (sBlob_6131c8_63a19c+0x86D4)
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _080963C4 @ =0x086217A8 (sBlob_6131c8_63a19c+0xE5E0)
	ldr r1, _080963C8 @ =0x06008000
	bl LZ77UncompVram
	ldr r0, _080963CC @ =0x08638654 (sBlob_6131c8_63a19c+0x2548C)
	ldr r1, _080963D0 @ =0x0600F000
	bl LZ77UncompVram
	ldr r0, _080963D4 @ =0x08637DB8 (sBlob_6131c8_63a19c+0x24BF0)
	ldr r1, _080963D8 @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _080963DC @ =0x08636838 (sBlob_6131c8_63a19c+0x23670)
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	ldr r0, _080963E0 @ =0x84000080
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r2, _080963E4 @ =0x000002FF
	adds r0, r2, #0
	strh r0, [r6]
	str r6, [r4]
	ldr r0, _080963E8 @ =0x0600F500
	str r0, [r4, #4]
	ldr r0, _080963EC @ =0x81000180
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080963F0 @ =0x03001224
	strh r5, [r0]
	ldr r0, _080963F4 @ =0x03001226
	strh r5, [r0]
	ldr r0, _080963F8 @ =gBg1XPosition
	strh r5, [r0]
	ldr r0, _080963FC @ =gBg1YPosition
	strh r5, [r0]
	ldr r0, _08096400 @ =0x0300122C
	strh r5, [r0]
	ldr r0, _08096404 @ =0x03001230
	strh r5, [r0]
	ldr r1, _08096408 @ =0x0300122E
	ldr r2, _0809640C @ =0x0000FFE2
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08096410 @ =0x03001232
	movs r1, #0xe2
	strh r1, [r0]
	ldr r0, _08096414 @ =0x04000010
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r1, [r0]
	ldr r1, _08096418 @ =0x0400000C
	ldr r2, _0809641C @ =0x00001E0A
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	adds r2, #0xf9
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _08096420 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08096424 @ =0x04000054
	strh r1, [r0]
	ldr r0, _08096428 @ =gWrittenToBldalpha_Eva
	strh r1, [r0]
	ldr r0, _0809642C @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	ldr r2, _08096430 @ =0x04000052
	lsls r0, r1, #8
	orrs r0, r1
	strh r0, [r2]
	movs r0, #0x14
	movs r1, #0
	movs r2, #0
	movs r3, #0
	bl EndingDialogueSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r0, _08096434 @ =0xFFFFFDE4
	add r8, r0
	ldr r0, _08096438 @ =0x0863A19C (sCutsceneTextNone)
	mov r1, r8
	str r0, [r1]
	str r5, [sp]
	mov r2, sp
	str r2, [r4]
	ldr r0, _0809643C @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _08096440 @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0xe0
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08096444 @ =EndingConversationAndAnimalsVblank
	bl CallbackSetVBlank
	add sp, #8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08096390: .4byte 0x04000208
_08096394: .4byte 0x04000004
_08096398: .4byte 0x0000FFEF
_0809639C: .4byte 0x04000200
_080963A0: .4byte 0x0000FFFD
_080963A4: .4byte unk_99940
_080963A8: .4byte 0x040000D4
_080963AC: .4byte 0x030016A0
_080963B0: .4byte 0x850000B4
_080963B4: .4byte 0xFFFFFDF8
_080963B8: .4byte 0x8100007E
_080963BC: .4byte 0xFFFFFEF4
_080963C0: .4byte sNextPageArrowPal+0x86F4
_080963C4: .4byte sNextPageArrowPal+0xE600
_080963C8: .4byte 0x06008000
_080963CC: .4byte sNextPageArrowPal+0x254AC
_080963D0: .4byte 0x0600F000
_080963D4: .4byte sNextPageArrowPal+0x24C10
_080963D8: .4byte 0x0600F800
_080963DC: .4byte sNextPageArrowPal+0x23690
_080963E0: .4byte 0x84000080
_080963E4: .4byte 0x000002FF
_080963E8: .4byte 0x0600F500
_080963EC: .4byte 0x81000180
_080963F0: .4byte 0x03001224
_080963F4: .4byte 0x03001226
_080963F8: .4byte gBg1XPosition
_080963FC: .4byte gBg1YPosition
_08096400: .4byte 0x0300122C
_08096404: .4byte 0x03001230
_08096408: .4byte 0x0300122E
_0809640C: .4byte 0x0000FFE2
_08096410: .4byte 0x03001232
_08096414: .4byte 0x04000010
_08096418: .4byte 0x0400000C
_0809641C: .4byte 0x00001E0A
_08096420: .4byte gWrittenToBldy
_08096424: .4byte 0x04000054
_08096428: .4byte gWrittenToBldalpha_Eva
_0809642C: .4byte gWrittenToBldalpha_Evb
_08096430: .4byte 0x04000052
_08096434: .4byte 0xFFFFFDE4
_08096438: .4byte sCutsceneTextNone
_0809643C: .4byte 0x0600D000
_08096440: .4byte 0x85000400
_08096444: .4byte EndingConversationAndAnimalsVblank

	thumb_func_start EndingInShipProcess
EndingInShipProcess: @ 0x08096448
	push {r4, r5, r6, r7, lr}
	movs r6, #0
	ldr r2, _08096474 @ =gNonGameplayRam
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrh r1, [r0]
	adds r1, #1
	strh r1, [r0]
	movs r7, #0x85
	lsls r7, r7, #2
	adds r0, r2, r7
	ldrb r0, [r0]
	adds r5, r2, #0
	cmp r0, #0xf
	bls _0809646A
	b _08096920
_0809646A:
	lsls r0, r0, #2
	ldr r1, _08096478 @ =_0809647C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08096474: .4byte gNonGameplayRam
_08096478: .4byte _0809647C
_0809647C: @ jump table
	.4byte _080964BC @ case 0
	.4byte _080964F2 @ case 1
	.4byte _08096550 @ case 2
	.4byte _080965F4 @ case 3
	.4byte _0809663C @ case 4
	.4byte _08096698 @ case 5
	.4byte _080966E0 @ case 6
	.4byte _080966FC @ case 7
	.4byte _08096716 @ case 8
	.4byte _0809673C @ case 9
	.4byte _0809678A @ case 10
	.4byte _0809681C @ case 11
	.4byte _08096828 @ case 12
	.4byte _08096878 @ case 13
	.4byte _080968A0 @ case 14
	.4byte _080968E8 @ case 15
_080964BC:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r5, r0
	ldrh r0, [r1]
	cmp r0, #7
	beq _080964CA
	b _080968D8
_080964CA:
	movs r0, #0
	strh r0, [r1]
	ldr r1, _080964DC @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0
	beq _080964E0
	subs r0, #1
	strh r0, [r1]
	b _080968D8
	.align 2, 0
_080964DC: .4byte gWrittenToBldy
_080964E0:
	movs r0, #0x56
	movs r1, #0xe
	bl PlayMusic
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #1
	b _080968D6
_080964F2:
	movs r7, #0x84
	lsls r7, r7, #2
	adds r1, r5, r7
	ldrh r0, [r1]
	cmp r0, #0x46
	beq _08096500
	b _080968D8
_08096500:
	movs r4, #0
	movs r2, #0
	strh r2, [r1]
	movs r3, #0x80
	lsls r3, r3, #0x13
	ldrh r0, [r3]
	movs r7, #0x80
	lsls r7, r7, #1
	adds r1, r7, #0
	orrs r0, r1
	strh r0, [r3]
	strh r2, [r5, #0x12]
	strh r2, [r5, #0x10]
	strh r2, [r5, #0xe]
	strh r2, [r5, #0xc]
	ldr r1, _08096544 @ =0x00000212
	adds r0, r5, r1
	strb r4, [r0]
	ldr r1, _08096548 @ =0x0879C5A4 (sMonologueTextPointers)
	ldr r0, _0809654C @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldr r0, [r0, #0x1c]
	str r0, [r5]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #2
	b _080968D6
	.align 2, 0
_08096544: .4byte 0x00000212
_08096548: .4byte sData_79C2CC+0x2D8
_0809654C: .4byte 0x03000011
_08096550:
	ldr r0, [r5]
	ldrh r1, [r0]
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _08096578
	ldr r0, _08096598 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _08096578
	movs r7, #0x86
	lsls r7, r7, #2
	adds r1, r5, r7
	ldrb r0, [r1]
	cmp r0, #0
	bne _08096578
	movs r0, #1
	strb r0, [r1]
_08096578:
	ldr r3, _0809659C @ =gNonGameplayRam
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r4, #0
	movs r0, #0
	strh r0, [r1]
	movs r1, #0x86
	lsls r1, r1, #2
	adds r0, r3, r1
	ldrb r2, [r0]
	cmp r2, #2
	bne _080965A0
	strb r4, [r0]
	b _080965AE
	.align 2, 0
_08096598: .4byte gChangedInput
_0809659C: .4byte gNonGameplayRam
_080965A0:
	cmp r2, #3
	bne _080965AE
	strb r4, [r0]
	movs r7, #0x85
	lsls r7, r7, #2
	adds r0, r3, r7
	strb r2, [r0]
_080965AE:
	bl EndingCheckMonologueEnded
	cmp r0, #0
	beq _080965CC
	ldr r3, _080965DC @ =gNonGameplayRam
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r2, #0
	movs r0, #3
	strb r0, [r1]
	movs r1, #0x86
	lsls r1, r1, #2
	adds r0, r3, r1
	strb r2, [r0]
_080965CC:
	ldr r0, _080965DC @ =gNonGameplayRam
	ldr r2, _080965E0 @ =0x00000213
	adds r1, r0, r2
	ldrb r0, [r1]
	cmp r0, #0
	bne _080965E4
	movs r0, #0x64
	b _080968D6
	.align 2, 0
_080965DC: .4byte gNonGameplayRam
_080965E0: .4byte 0x00000213
_080965E4:
	cmp r0, #1
	beq _080965EA
	b _080968D8
_080965EA:
	movs r0, #0x64
	strb r0, [r1]
	bl SpecialCutsceneProcessMonologue
	b _080968D8
_080965F4:
	movs r7, #0x84
	lsls r7, r7, #2
	adds r1, r5, r7
	ldrh r0, [r1]
	cmp r0, #1
	bne _08096618
	ldr r1, _08096610 @ =gWrittenToBldalpha_Evb
	movs r0, #0
	strh r0, [r1]
	ldr r1, _08096614 @ =gWrittenToBldalpha_Eva
_08096608:
	movs r0, #0x10
	strh r0, [r1]
	b _080968D8
	.align 2, 0
_08096610: .4byte gWrittenToBldalpha_Evb
_08096614: .4byte gWrittenToBldalpha_Eva
_08096618:
	cmp r0, #0x14
	beq _0809661E
	b _080968D8
_0809661E:
	movs r0, #0
	strh r0, [r1]
	ldr r1, _08096634 @ =0x04000050
	ldr r2, _08096638 @ =0x00001841
	adds r0, r2, #0
	strh r0, [r1]
	movs r7, #0x85
	lsls r7, r7, #2
	adds r1, r5, r7
	movs r0, #4
	b _080968D6
	.align 2, 0
_08096634: .4byte 0x04000050
_08096638: .4byte 0x00001841
_0809663C:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r5, r0
	ldrh r0, [r1]
	cmp r0, #4
	beq _0809664A
	b _080968D8
_0809664A:
	movs r0, #0
	strh r0, [r1]
	ldr r2, _0809668C @ =gWrittenToBldalpha_Evb
	ldrh r0, [r2]
	cmp r0, #0xf
	bhi _0809665A
	adds r0, #1
	strh r0, [r2]
_0809665A:
	ldr r1, _08096690 @ =gWrittenToBldalpha_Eva
	ldrh r0, [r1]
	cmp r0, #0
	beq _08096666
	subs r0, #1
	strh r0, [r1]
_08096666:
	ldrh r0, [r2]
	cmp r0, #0x10
	beq _0809666E
	b _080968D8
_0809666E:
	ldrh r0, [r1]
	cmp r0, #0
	beq _08096676
	b _080968D8
_08096676:
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r1, [r2]
	ldr r0, _08096694 @ =0x0000FEFF
	ands r0, r1
	strh r0, [r2]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #5
	b _080968D6
	.align 2, 0
_0809668C: .4byte gWrittenToBldalpha_Evb
_08096690: .4byte gWrittenToBldalpha_Eva
_08096694: .4byte 0x0000FEFF
_08096698:
	movs r7, #0x84
	lsls r7, r7, #2
	adds r2, r5, r7
	ldrh r0, [r2]
	cmp r0, #0xa
	bne _080966B2
	movs r0, #0x1e
	movs r1, #0x78
	movs r2, #0x50
	movs r3, #1
	bl EndingDialogueSetupOam
	b _080968D8
_080966B2:
	cmp r0, #0x27
	bne _080966C0
	ldr r1, _080966BC @ =gWrittenToBldy
	b _08096608
	.align 2, 0
_080966BC: .4byte gWrittenToBldy
_080966C0:
	cmp r0, #0x28
	beq _080966C6
	b _080968D8
_080966C6:
	ldr r1, _080966DC @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
	movs r0, #0
	strh r0, [r2]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r5, r0
	movs r0, #6
	b _080968D6
	.align 2, 0
_080966DC: .4byte 0x04000050
_080966E0:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r1, r5, r2
	ldrh r0, [r1]
	cmp r0, #1
	beq _080966EE
	b _080968D8
_080966EE:
	movs r0, #0
	strh r0, [r1]
	movs r7, #0x85
	lsls r7, r7, #2
	adds r1, r5, r7
	movs r0, #7
	b _080968D6
_080966FC:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r5, r0
	movs r0, #0
	strh r0, [r1]
	bl EndingAdamConversationInit
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #8
	strb r0, [r1]
	b _08096920
_08096716:
	ldr r1, _08096738 @ =gWrittenToBldy
	movs r0, #0
	strh r0, [r1]
	movs r7, #0x84
	lsls r7, r7, #2
	adds r1, r5, r7
	movs r0, #0
	strh r0, [r1]
	movs r0, #0x93
	lsls r0, r0, #2
	bl SoundPlay
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r5, r0
	movs r0, #9
	b _080968D6
	.align 2, 0
_08096738: .4byte gWrittenToBldy
_0809673C:
	movs r1, #0x84
	lsls r1, r1, #2
	adds r4, r5, r1
	ldrh r0, [r4]
	cmp r0, #0xa
	beq _08096806
	cmp r0, #0x28
	bne _08096806
	movs r0, #0xff
	movs r1, #0
	movs r2, #0
	movs r3, #0
	bl EndingDialogueSetupOam
	movs r0, #6
	movs r1, #0x14
	movs r2, #0xc0
	movs r3, #0
	bl EndingDialogueSetupOam
	movs r0, #7
	movs r1, #0x80
	movs r2, #0xc0
	movs r3, #0
	bl EndingDialogueSetupOam
	movs r0, #9
	movs r1, #0x80
	movs r2, #0xc0
	movs r3, #0
	bl EndingDialogueSetupOam
	movs r0, #0
	strh r0, [r4]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #0xa
	b _08096804
_0809678A:
	movs r7, #0x84
	lsls r7, r7, #2
	adds r1, r5, r7
	movs r0, #0
	strh r0, [r1]
	ldr r0, [r5]
	ldrh r1, [r0]
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _080967BC
	ldr r0, _080967D4 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _080967BC
	movs r0, #0x86
	lsls r0, r0, #2
	adds r1, r5, r0
	ldrb r0, [r1]
	cmp r0, #0
	bne _080967BC
	movs r0, #1
	strb r0, [r1]
_080967BC:
	movs r1, #0x86
	lsls r1, r1, #2
	adds r3, r5, r1
	ldrb r0, [r3]
	cmp r0, #2
	bne _080967DC
	movs r0, #0
	strb r0, [r3]
	ldr r0, _080967D8 @ =0x00000203
	bl SoundPlay
	b _08096806
	.align 2, 0
_080967D4: .4byte gChangedInput
_080967D8: .4byte 0x00000203
_080967DC:
	cmp r0, #3
	bne _08096806
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r1, [r2]
	ldr r0, _08096814 @ =0x0000FEFF
	ands r0, r1
	strh r0, [r2]
	movs r0, #0
	strb r0, [r3]
	ldr r0, _08096818 @ =0x00000203
	bl SoundPlay
	movs r0, #0xa
	bl FadeMusic
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #0xb
_08096804:
	strb r0, [r1]
_08096806:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	bl EndingProcessAdamText
	b _08096920
	.align 2, 0
_08096814: .4byte 0x0000FEFF
_08096818: .4byte 0x00000203
_0809681C:
	movs r7, #0x84
	lsls r7, r7, #2
	adds r1, r5, r7
	movs r0, #0
	strh r0, [r1]
	b _080968D8
_08096828:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r5, r0
	ldrh r0, [r1]
	cmp r0, #1
	bne _0809685C
	ldr r2, _08096850 @ =0x080A8CDC (sMusicTrackDataRom)
	ldr r0, _08096854 @ =0x080A8D3C (sSoundDataEntries)
	ldr r1, _08096858 @ =0x00001264
	adds r0, r0, r1
	ldrh r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r0, [r0]
	movs r1, #0
	bl ApplyMusicSoundFading
	b _080968D8
	.align 2, 0
_08096850: .4byte sMusicTrackDataRom
_08096854: .4byte sSoundDataEntries
_08096858: .4byte 0x00001264
_0809685C:
	cmp r0, #0xa
	bne _080968D8
	movs r0, #0
	strh r0, [r1]
	ldr r1, _08096874 @ =gWrittenToBldy
	movs r0, #0x10
	strh r0, [r1]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #0xd
	b _080968D6
	.align 2, 0
_08096874: .4byte gWrittenToBldy
_08096878:
	bl EndingAnimalsInit
	ldr r2, _08096898 @ =gNonGameplayRam
	movs r7, #0x84
	lsls r7, r7, #2
	adds r0, r2, r7
	movs r1, #0
	strh r1, [r0]
	ldr r0, _0809689C @ =gWrittenToBldy
	strh r1, [r0]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r2, r0
	movs r0, #0xe
	strb r0, [r1]
	b _08096920
	.align 2, 0
_08096898: .4byte gNonGameplayRam
_0809689C: .4byte gWrittenToBldy
_080968A0:
	movs r1, #0x84
	lsls r1, r1, #2
	adds r2, r5, r1
	ldrh r1, [r2]
	cmp r1, #1
	bne _080968B6
	movs r0, #0x53
	movs r1, #0xe
	bl PlayMusic
	b _080968D8
_080968B6:
	movs r0, #0xa0
	lsls r0, r0, #2
	cmp r1, r0
	bne _080968D8
	movs r0, #0
	strh r0, [r2]
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r1, [r2]
	ldr r0, _080968E4 @ =0x0000FBFF
	ands r0, r1
	strh r0, [r2]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r5, r2
	movs r0, #0xf
_080968D6:
	strb r0, [r1]
_080968D8:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	b _08096920
	.align 2, 0
_080968E4: .4byte 0x0000FBFF
_080968E8:
	movs r7, #0x84
	lsls r7, r7, #2
	adds r1, r5, r7
	ldrh r0, [r1]
	cmp r0, #2
	bne _08096918
	movs r0, #0
	strh r0, [r1]
	ldr r1, _08096908 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _0809690C
	adds r0, #1
	strh r0, [r1]
	b _08096918
	.align 2, 0
_08096908: .4byte gWrittenToBldy
_0809690C:
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r5, r0
	movs r0, #0
	strb r0, [r1]
	movs r6, #1
_08096918:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_08096920:
	adds r0, r6, #0
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1

	thumb_func_start EndingInShip
EndingInShip: @ 0x08096928
	push {r4, r5, lr}
	movs r5, #0
	ldr r4, _08096940 @ =gNonGameplayRam
	ldrh r0, [r4, #8]
	cmp r0, #1
	beq _08096954
	cmp r0, #1
	bgt _08096944
	cmp r0, #0
	beq _0809694E
	b _080969A8
	.align 2, 0
_08096940: .4byte gNonGameplayRam
_08096944:
	cmp r0, #2
	beq _0809696C
	cmp r0, #3
	beq _08096988
	b _080969A8
_0809694E:
	bl EndingMonologueInit
	b _08096960
_08096954:
	bl SpecialCutsceneFadeIn
	ldr r0, _08096968 @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0
	bne _080969A8
_08096960:
	movs r0, #2
	strh r0, [r4, #8]
	b _080969A8
	.align 2, 0
_08096968: .4byte gWrittenToBldy
_0809696C:
	bl EndingInShipProcess
	cmp r0, #0
	beq _080969A8
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r4, r1
	strb r5, [r0]
	subs r1, #1
	adds r0, r4, r1
	strb r5, [r0]
	movs r0, #3
	strh r0, [r4, #8]
	b _080969A8
_08096988:
	ldr r1, _08096998 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _0809699C
	adds r0, #1
	strh r0, [r1]
	b _080969A0
	.align 2, 0
_08096998: .4byte gWrittenToBldy
_0809699C:
	strh r5, [r4, #8]
	movs r5, #1
_080969A0:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_080969A8:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1

	thumb_func_start EndingProcessMonologueCursor
EndingProcessMonologueCursor: @ 0x080969B0
	push {lr}
	adds r2, r0, #0
	ldr r3, _080969D0 @ =gNonGameplayRam
	ldr r0, [r3]
	ldrh r1, [r0]
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _080969D4
	movs r0, #0x76
	strh r0, [r2, #0xc]
	ldrh r0, [r3, #0xe]
	lsls r0, r0, #3
	adds r0, #0x18
	strh r0, [r2, #0xe]
	b _080969DA
	.align 2, 0
_080969D0: .4byte gNonGameplayRam
_080969D4:
	movs r0, #0x82
	lsls r0, r0, #1
	strh r0, [r2, #0xc]
_080969DA:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start unk_969e0
unk_969e0: @ 0x080969E0
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _08096A02
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _08096A02
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _08096A02
	strb r1, [r2, #0x12]
_08096A02:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start EndingProcessSr388RadarView
EndingProcessSr388RadarView: @ 0x08096A08
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _08096A34
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _08096A34
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _08096A34
	strb r1, [r2, #0x12]
	strb r1, [r2, #0x11]
	ldr r0, _08096A38 @ =0x08633EC4 (sBlob_6131c8_63a19c+0x20CFC)
	str r0, [r2, #0x1c]
	movs r0, #1
	strb r0, [r2, #0x14]
_08096A34:
	pop {r0}
	bx r0
	.align 2, 0
_08096A38: .4byte sNextPageArrowPal+0x20D1C

	thumb_func_start EndingProcessSamusViewRadarView
EndingProcessSamusViewRadarView: @ 0x08096A3C
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _08096A68
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _08096A68
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _08096A68
	strb r1, [r2, #0x12]
	strb r1, [r2, #0x11]
	ldr r0, _08096A6C @ =0x08633F0C (sBlob_6131c8_63a19c+0x20D44)
	str r0, [r2, #0x1c]
	movs r0, #1
	strb r0, [r2, #0x14]
_08096A68:
	pop {r0}
	bx r0
	.align 2, 0
_08096A6C: .4byte sNextPageArrowPal+0x20D64

	thumb_func_start unk_96a70
unk_96a70: @ 0x08096A70
	push {r4, r5, r6, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r6, r1, r0
	ldrb r5, [r4, #0x14]
	cmp r5, #0
	bne _08096AB4
	ldr r0, [r4, #0x10]
	ldr r1, _08096AAC @ =0x00FFFF00
	ands r0, r1
	ldr r1, _08096AB0 @ =0x00010100
	cmp r0, r1
	bne _08096A96
	movs r0, #0x8e
	lsls r0, r0, #1
	bl SoundPlay
_08096A96:
	ldrb r0, [r6, #4]
	ldrb r1, [r4, #0x12]
	cmp r0, r1
	bne _08096B06
	ldrb r0, [r6, #0xc]
	cmp r0, #0
	bne _08096B06
	strb r5, [r4, #0x12]
	movs r0, #1
	strb r0, [r4, #0x14]
	b _08096B06
	.align 2, 0
_08096AAC: .4byte 0x00FFFF00
_08096AB0: .4byte 0x00010100
_08096AB4:
	cmp r5, #1
	bne _08096AE8
	movs r1, #0
	strb r1, [r4, #0x12]
	ldr r0, _08096ADC @ =gNonGameplayRam
	movs r2, #0x85
	lsls r2, r2, #2
	adds r0, r0, r2
	ldrb r0, [r0]
	cmp r0, #0xb
	bne _08096B06
	strb r1, [r4, #0x11]
	ldr r0, _08096AE0 @ =0x08633244 (sBlob_6131c8_63a19c+0x2007C)
	str r0, [r4, #0x1c]
	ldr r0, _08096AE4 @ =0x0000011D
	bl SoundPlay
	movs r0, #2
	strb r0, [r4, #0x14]
	b _08096B06
	.align 2, 0
_08096ADC: .4byte gNonGameplayRam
_08096AE0: .4byte sNextPageArrowPal+0x2009C
_08096AE4: .4byte 0x0000011D
_08096AE8:
	cmp r5, #2
	bne _08096B06
	ldrb r0, [r6, #4]
	ldrb r1, [r4, #0x12]
	cmp r0, r1
	bne _08096B06
	ldrb r1, [r6, #0xc]
	cmp r1, #0
	bne _08096B06
	strb r1, [r4, #0x10]
	ldrb r1, [r4, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r4, #0x18]
_08096B06:
	pop {r4, r5, r6}
	pop {r0}
	bx r0

	thumb_func_start EndingProcessAdamTextCursor
EndingProcessAdamTextCursor: @ 0x08096B0C
	push {r4, lr}
	adds r2, r0, #0
	ldr r3, _08096B28 @ =gNonGameplayRam
	ldr r0, [r3]
	ldrh r1, [r0]
	movs r0, #0xff
	lsls r0, r0, #8
	cmp r1, r0
	bne _08096B2C
	movs r0, #0x91
	lsls r0, r0, #1
	strh r0, [r2, #0xc]
	b _08096B8E
	.align 2, 0
_08096B28: .4byte gNonGameplayRam
_08096B2C:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r1, r0
	beq _08096B70
	movs r0, #0xfd
	lsls r0, r0, #8
	cmp r1, r0
	bne _08096B54
	movs r0, #0
	movs r1, #0x91
	lsls r1, r1, #1
	strh r1, [r2, #0xc]
	strb r0, [r2, #0x12]
	strb r0, [r2, #0x11]
	ldr r0, _08096B50 @ =0x08633E8C (sBlob_6131c8_63a19c+0x20CC4)
	str r0, [r2, #0x1c]
	b _08096B8E
	.align 2, 0
_08096B50: .4byte sNextPageArrowPal+0x20CE4
_08096B54:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _08096B70
	movs r0, #0x78
	strh r0, [r2, #0xc]
	movs r0, #0x9a
	strh r0, [r2, #0xe]
	ldr r0, _08096B6C @ =0x08633E64 (sBlob_6131c8_63a19c+0x20C9C)
	str r0, [r2, #0x1c]
	b _08096B8E
	.align 2, 0
_08096B6C: .4byte sNextPageArrowPal+0x20CBC
_08096B70:
	ldrh r0, [r3, #0xc]
	ldr r4, _08096B94 @ =0x00000212
	adds r1, r3, r4
	lsls r0, r0, #3
	ldrb r1, [r1]
	adds r0, r0, r1
	adds r0, #0xe
	movs r1, #0
	strh r0, [r2, #0xc]
	ldrh r0, [r3, #0xe]
	lsls r0, r0, #3
	adds r0, #0x84
	strh r0, [r2, #0xe]
	strb r1, [r2, #0x12]
	strb r1, [r2, #0x11]
_08096B8E:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08096B94: .4byte 0x00000212

	thumb_func_start EndingProcessAdamPanel
EndingProcessAdamPanel: @ 0x08096B98
	push {r4, lr}
	adds r4, r0, #0
	ldrb r0, [r4, #0x14]
	cmp r0, #0
	bne _08096BD4
	strb r0, [r4, #0x12]
	strb r0, [r4, #0x11]
	ldrh r1, [r4, #0xe]
	movs r2, #0xe
	ldrsh r0, [r4, r2]
	cmp r0, #0x80
	ble _08096BB8
	adds r0, r1, #0
	subs r0, #8
	strh r0, [r4, #0xe]
	b _08096D34
_08096BB8:
	movs r0, #0x80
	strh r0, [r4, #0xe]
	ldrb r0, [r4, #0x10]
	cmp r0, #7
	bne _08096BC8
	ldr r0, _08096BD0 @ =0x0000020A
	bl SoundPlay
_08096BC8:
	movs r0, #1
	strb r0, [r4, #0x14]
	b _08096D34
	.align 2, 0
_08096BD0: .4byte 0x0000020A
_08096BD4:
	cmp r0, #1
	bne _08096C64
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #0x12]
	cmp r0, r3
	bne _08096C12
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _08096BF4
	strb r1, [r4, #0x12]
	movs r0, #2
	strb r0, [r4, #0x14]
_08096BF4:
	ldrb r0, [r4, #0x10]
	cmp r0, #7
	beq _08096BFC
	b _08096D34
_08096BFC:
	ldrb r0, [r4, #0x11]
	cmp r0, #0xa
	bne _08096C12
	movs r0, #0xc
	ldrsh r1, [r4, r0]
	movs r3, #0xe
	ldrsh r2, [r4, r3]
	movs r0, #8
	movs r3, #0
	bl EndingDialogueSetupOam
_08096C12:
	ldrb r0, [r4, #0x10]
	cmp r0, #7
	beq _08096C1A
	b _08096D34
_08096C1A:
	ldrb r0, [r4, #0x11]
	cmp r0, #0xb
	beq _08096C22
	b _08096D34
_08096C22:
	ldrb r0, [r4, #0x12]
	cmp r0, #0xf
	beq _08096C2A
	b _08096D34
_08096C2A:
	ldr r2, _08096C54 @ =gNonGameplayRam
	ldr r0, _08096C58 @ =0x00000212
	adds r1, r2, r0
	movs r0, #0
	strb r0, [r1]
	strh r0, [r2, #0xe]
	strh r0, [r2, #0xc]
	ldr r1, _08096C5C @ =0x0879C3AC (sBlob_79c394_79c3c8+0x18)
	ldr r0, _08096C60 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	movs r1, #0xe0
	lsls r1, r1, #1
	adds r0, r0, r1
	ldr r0, [r0]
	str r0, [r2]
	b _08096D34
	.align 2, 0
_08096C54: .4byte gNonGameplayRam
_08096C58: .4byte 0x00000212
_08096C5C: .4byte sData_79C2CC+0xE0
_08096C60: .4byte 0x03000011
_08096C64:
	cmp r0, #2
	bne _08096C82
	movs r1, #0
	strb r1, [r4, #0x12]
	ldrb r0, [r4, #0x13]
	adds r0, #1
	strb r0, [r4, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #1
	bne _08096D34
	strb r1, [r4, #0x13]
	movs r0, #3
	strb r0, [r4, #0x14]
	b _08096D34
_08096C82:
	cmp r0, #3
	bne _08096CCC
	movs r1, #0
	strb r1, [r4, #0x12]
	ldr r0, _08096CAC @ =gNonGameplayRam
	movs r2, #0x85
	lsls r2, r2, #2
	adds r0, r0, r2
	ldrb r0, [r0]
	cmp r0, #0xb
	bne _08096D34
	strb r1, [r4, #0x11]
	ldrb r0, [r4, #0x10]
	cmp r0, #7
	bne _08096CB8
	ldr r0, _08096CB0 @ =0x086332FC (sBlob_6131c8_63a19c+0x20134)
	str r0, [r4, #0x1c]
	ldr r0, _08096CB4 @ =0x0000020B
	bl SoundPlay
	b _08096CC0
	.align 2, 0
_08096CAC: .4byte gNonGameplayRam
_08096CB0: .4byte sNextPageArrowPal+0x20154
_08096CB4: .4byte 0x0000020B
_08096CB8:
	cmp r0, #9
	bne _08096CC0
	ldr r0, _08096CC8 @ =0x086333CC (sBlob_6131c8_63a19c+0x20204)
	str r0, [r4, #0x1c]
_08096CC0:
	movs r0, #4
	strb r0, [r4, #0x14]
	b _08096D34
	.align 2, 0
_08096CC8: .4byte sNextPageArrowPal+0x20224
_08096CCC:
	cmp r0, #4
	bne _08096CFC
	ldr r0, [r4, #0x10]
	ldr r1, _08096CF4 @ =0x00FFFF00
	ands r0, r1
	ldr r1, _08096CF8 @ =0x00030B00
	cmp r0, r1
	bne _08096D34
	ldrb r0, [r4, #0x10]
	cmp r0, #7
	bne _08096CE8
	movs r0, #8
	bl SpecialCutsceneDestroyOamOfType
_08096CE8:
	movs r0, #0
	strb r0, [r4, #0x12]
	movs r0, #5
	strb r0, [r4, #0x14]
	b _08096D34
	.align 2, 0
_08096CF4: .4byte 0x00FFFF00
_08096CF8: .4byte 0x00030B00
_08096CFC:
	cmp r0, #5
	bne _08096D34
	movs r2, #0
	strb r2, [r4, #0x12]
	ldrh r1, [r4, #0xe]
	movs r3, #0xe
	ldrsh r0, [r4, r3]
	cmp r0, #0xbf
	bgt _08096D16
	adds r0, r1, #0
	adds r0, #8
	strh r0, [r4, #0xe]
	b _08096D34
_08096D16:
	ldrb r0, [r4, #0x10]
	cmp r0, #7
	bne _08096D28
	ldr r0, _08096D3C @ =gNonGameplayRam
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r0, r1
	movs r1, #0xc
	strb r1, [r0]
_08096D28:
	strb r2, [r4, #0x10]
	ldrb r1, [r4, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r4, #0x18]
_08096D34:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08096D3C: .4byte gNonGameplayRam

	thumb_func_start EndingProcessAdamIcon
EndingProcessAdamIcon: @ 0x08096D40
	push {r4, lr}
	adds r2, r0, #0
	ldrb r3, [r2, #0x11]
	lsls r1, r3, #3
	ldr r0, [r2, #0x1c]
	adds r4, r0, r1
	ldrb r1, [r2, #0x14]
	cmp r1, #0
	bne _08096D80
	cmp r3, #3
	bne _08096D62
	strb r1, [r2, #0x12]
	strb r1, [r2, #0x11]
	ldr r0, _08096D78 @ =0x086338A4 (sBlob_6131c8_63a19c+0x206DC)
	str r0, [r2, #0x1c]
	movs r0, #1
	strb r0, [r2, #0x14]
_08096D62:
	ldr r0, _08096D7C @ =gNonGameplayRam
	movs r3, #0x85
	lsls r3, r3, #2
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0xb
	bne _08096DC0
	strb r1, [r2, #0x12]
	strb r1, [r2, #0x11]
	b _08096D98
	.align 2, 0
_08096D78: .4byte sNextPageArrowPal+0x206FC
_08096D7C: .4byte gNonGameplayRam
_08096D80:
	cmp r1, #1
	bne _08096DAC
	ldr r0, _08096DA4 @ =gNonGameplayRam
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #0xb
	bne _08096DC0
	movs r0, #0
	strb r0, [r2, #0x12]
	strb r0, [r2, #0x11]
_08096D98:
	ldr r0, _08096DA8 @ =0x0863345C (sBlob_6131c8_63a19c+0x20294)
	str r0, [r2, #0x1c]
	movs r0, #2
	strb r0, [r2, #0x14]
	b _08096DC0
	.align 2, 0
_08096DA4: .4byte gNonGameplayRam
_08096DA8: .4byte sNextPageArrowPal+0x202B4
_08096DAC:
	cmp r1, #2
	bne _08096DC0
	ldrb r0, [r4, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _08096DC0
	ldrb r0, [r4, #0xc]
	cmp r0, #0
	bne _08096DC0
	strb r0, [r2, #0x12]
_08096DC0:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start EndingProcessAnimalsScrolling
EndingProcessAnimalsScrolling: @ 0x08096DC8
	push {r4, lr}
	sub sp, #4
	adds r2, r0, #0
	ldrb r0, [r2, #0x13]
	adds r1, r0, #1
	movs r3, #0
	strb r1, [r2, #0x13]
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _08096E48
	ldr r0, _08096E20 @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r2, #0xc]
	ldr r0, _08096E24 @ =0x0300122E
	ldrh r1, [r0]
	strh r1, [r2, #0xe]
	ldr r0, _08096E28 @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r2]
	ldr r0, _08096E2C @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r2, #2]
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	movs r0, #0x20
	rsbs r0, r0, #0
	cmp r1, r0
	bge _08096E3C
	movs r0, #0x80
	lsls r0, r0, #7
	strh r0, [r2, #0xa]
	str r3, [sp]
	ldr r1, _08096E30 @ =0x040000D4
	mov r0, sp
	str r0, [r1]
	ldrh r0, [r2, #0xa]
	ldr r3, _08096E34 @ =0x06008000
	adds r0, r0, r3
	str r0, [r1, #4]
	ldr r0, _08096E38 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _08096E42
	.align 2, 0
_08096E20: .4byte 0x0300122C
_08096E24: .4byte 0x0300122E
_08096E28: .4byte 0x03001230
_08096E2C: .4byte 0x03001232
_08096E30: .4byte 0x040000D4
_08096E34: .4byte 0x06008000
_08096E38: .4byte 0x85000400
_08096E3C:
	movs r0, #0xa0
	lsls r0, r0, #7
	strh r0, [r2, #0xa]
_08096E42:
	movs r0, #0
	strb r0, [r2, #0x13]
	b _08096E56
_08096E48:
	cmp r0, #1
	bne _08096E5C
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xa
	bne _08096EF6
	strb r3, [r2, #0x13]
_08096E56:
	movs r0, #2
	strb r0, [r2, #0x14]
	b _08096EF6
_08096E5C:
	ldr r0, _08096ED8 @ =gNonGameplayRam
	movs r4, #0x85
	lsls r4, r4, #2
	adds r0, r0, r4
	ldrb r0, [r0]
	cmp r0, #0xe
	bne _08096EF4
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #2
	bne _08096EA6
	strb r3, [r2, #0x13]
	ldrh r3, [r2, #0xe]
	movs r0, #0xe
	ldrsh r1, [r2, r0]
	movs r0, #0xa0
	rsbs r0, r0, #0
	cmp r1, r0
	ble _08096E8C
	subs r0, r3, #1
	strh r0, [r2, #0xe]
	ldrh r0, [r2, #8]
	adds r0, #1
	strh r0, [r2, #8]
_08096E8C:
	ldrh r1, [r2, #2]
	movs r3, #2
	ldrsh r0, [r2, r3]
	cmp r0, #0
	ble _08096E9A
	subs r0, r1, #1
	strh r0, [r2, #2]
_08096E9A:
	ldr r1, _08096EDC @ =0x0300122E
	ldrh r0, [r2, #0xe]
	strh r0, [r1]
	ldr r1, _08096EE0 @ =0x03001232
	ldrh r0, [r2, #2]
	strh r0, [r1]
_08096EA6:
	movs r4, #8
	ldrsh r0, [r2, r4]
	cmp r0, #9
	bne _08096EF6
	movs r1, #0
	strh r1, [r2, #8]
	ldrh r0, [r2, #0xa]
	cmp r0, #0
	beq _08096EF6
	ldr r3, _08096EE4 @ =0xFFFFFC00
	adds r0, r0, r3
	strh r0, [r2, #0xa]
	str r1, [sp]
	ldr r1, _08096EE8 @ =0x040000D4
	mov r4, sp
	str r4, [r1]
	ldrh r0, [r2, #0xa]
	ldr r2, _08096EEC @ =0x06008000
	adds r0, r0, r2
	str r0, [r1, #4]
	ldr r0, _08096EF0 @ =0x85000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _08096EF6
	.align 2, 0
_08096ED8: .4byte gNonGameplayRam
_08096EDC: .4byte 0x0300122E
_08096EE0: .4byte 0x03001232
_08096EE4: .4byte 0xFFFFFC00
_08096EE8: .4byte 0x040000D4
_08096EEC: .4byte 0x06008000
_08096EF0: .4byte 0x85000100
_08096EF4:
	strb r3, [r2, #0x13]
_08096EF6:
	add sp, #4
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start unk_96f00
unk_96f00: @ 0x08096F00
	movs r1, #0
	strb r1, [r0, #0x10]
	bx lr
	.align 2, 0

	thumb_func_start EndingDialogueSetupOam
EndingDialogueSetupOam: @ 0x08096F08
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	lsls r1, r1, #0x10
	lsrs r6, r1, #0x10
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	mov r8, r2
	lsls r3, r3, #0x18
	cmp r3, #0
	bne _08096F68
	movs r2, #0
	ldr r0, _08096F64 @ =gNonGameplayRam
	movs r3, #0x8b
	lsls r3, r3, #2
	adds r1, r0, r3
	ldrb r1, [r1]
	mov ip, r0
	cmp r1, #0
	beq _08096F58
	mov r4, ip
_08096F38:
	lsls r0, r2, #0x18
	movs r1, #0x80
	lsls r1, r1, #0x11
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0x13
	bgt _08096FA8
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _08096F38
_08096F58:
	lsls r0, r2, #0x18
	asrs r1, r0, #0x18
	adds r7, r0, #0
	cmp r1, #0x13
	ble _08096FB0
	b _08096FA8
	.align 2, 0
_08096F64: .4byte gNonGameplayRam
_08096F68:
	movs r2, #0x13
	ldr r0, _08096FAC @ =gNonGameplayRam
	movs r3, #0x9b
	lsls r3, r3, #3
	adds r1, r0, r3
	ldrb r1, [r1]
	mov ip, r0
	cmp r1, #0
	beq _08096FA0
	mov r4, ip
	movs r3, #0x8b
	lsls r3, r3, #2
_08096F80:
	lsls r0, r2, #0x18
	movs r1, #0xff
	lsls r1, r1, #0x18
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0
	blt _08096FA8
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _08096F80
_08096FA0:
	lsls r0, r2, #0x18
	adds r7, r0, #0
	cmp r7, #0
	bge _08096FB0
_08096FA8:
	movs r0, #0x14
	b _08097272
	.align 2, 0
_08096FAC: .4byte gNonGameplayRam
_08096FB0:
	movs r0, #0
	str r0, [sp]
	ldr r2, _08097014 @ =0x040000D4
	mov r3, sp
	str r3, [r2]
	asrs r1, r7, #0x18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r4, r0, #2
	ldr r3, _08097018 @ =0x030016A0
	adds r0, r4, r3
	str r0, [r2, #4]
	ldr r0, _0809701C @ =0x85000009
	str r0, [r2, #8]
	ldr r0, [r2, #8]
	ldr r1, _08097020 @ =0xFFFFFDE4
	adds r0, r3, r1
	adds r2, r4, r0
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r0, r2, r1
	strh r6, [r0]
	adds r1, #2
	adds r0, r2, r1
	mov r1, r8
	strh r1, [r0]
	movs r1, #0x8b
	lsls r1, r1, #2
	adds r0, r2, r1
	strb r5, [r0]
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r6, r2, r0
	ldrb r1, [r6]
	movs r0, #1
	orrs r1, r0
	strb r1, [r6]
	cmp r5, #1
	bne _0809702C
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08097024 @ =0x08633E64 (sBlob_6131c8_63a19c+0x20C9C)
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08097028 @ =EndingProcessMonologueCursor
	str r1, [r0]
	b _08097270
	.align 2, 0
_08097014: .4byte 0x040000D4
_08097018: .4byte 0x030016A0
_0809701C: .4byte 0x85000009
_08097020: .4byte 0xFFFFFDE4
_08097024: .4byte sNextPageArrowPal+0x20CBC
_08097028: .4byte EndingProcessMonologueCursor
_0809702C:
	cmp r5, #2
	bne _08097064
	ldr r1, _08097058 @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _0809705C @ =0x086338D4 (sBlob_6131c8_63a19c+0x2070C)
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08097060 @ =unk_969e0
	str r1, [r0]
	b _08097270
	.align 2, 0
_08097058: .4byte 0x00000236
_0809705C: .4byte sNextPageArrowPal+0x2072C
_08097060: .4byte unk_969e0
_08097064:
	cmp r5, #3
	bne _0809709C
	ldr r0, _08097090 @ =0x00000236
	adds r2, r2, r0
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08097094 @ =0x086339D4 (sBlob_6131c8_63a19c+0x2080C)
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08097098 @ =EndingProcessSr388RadarView
	str r1, [r0]
	b _08097270
	.align 2, 0
_08097090: .4byte 0x00000236
_08097094: .4byte sNextPageArrowPal+0x2082C
_08097098: .4byte EndingProcessSr388RadarView
_0809709C:
	cmp r5, #4
	bne _080970D4
	ldr r1, _080970C8 @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _080970CC @ =0x08633C4C (sBlob_6131c8_63a19c+0x20A84)
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _080970D0 @ =EndingProcessSamusViewRadarView
	str r1, [r0]
	b _08097270
	.align 2, 0
_080970C8: .4byte 0x00000236
_080970CC: .4byte sNextPageArrowPal+0x20AA4
_080970D0: .4byte EndingProcessSamusViewRadarView
_080970D4:
	cmp r5, #5
	bne _0809710C
	ldr r0, _08097100 @ =0x00000236
	adds r2, r2, r0
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08097104 @ =0x086331EC (sBlob_6131c8_63a19c+0x20024)
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _08097108 @ =unk_96a70
	str r1, [r0]
	b _08097270
	.align 2, 0
_08097100: .4byte 0x00000236
_08097104: .4byte sNextPageArrowPal+0x20044
_08097108: .4byte unk_96a70
_0809710C:
	cmp r5, #6
	bne _08097130
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08097128 @ =0x08633E8C (sBlob_6131c8_63a19c+0x20CC4)
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _0809712C @ =EndingProcessAdamTextCursor
	str r1, [r0]
	b _08097270
	.align 2, 0
_08097128: .4byte sNextPageArrowPal+0x20CE4
_0809712C: .4byte EndingProcessAdamTextCursor
_08097130:
	cmp r5, #7
	bne _08097158
	ldr r1, _08097150 @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r2]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08097154 @ =0x08633294 (sBlob_6131c8_63a19c+0x200CC)
	b _080971AE
	.align 2, 0
_08097150: .4byte 0x00000236
_08097154: .4byte sNextPageArrowPal+0x200EC
_08097158:
	cmp r5, #8
	bne _08097190
	ldr r0, _08097184 @ =0x00000236
	adds r2, r2, r0
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r2]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _08097188 @ =0x08633434 (sBlob_6131c8_63a19c+0x2026C)
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _0809718C @ =EndingProcessAdamIcon
	str r1, [r0]
	b _08097270
	.align 2, 0
_08097184: .4byte 0x00000236
_08097188: .4byte sNextPageArrowPal+0x2028C
_0809718C: .4byte EndingProcessAdamIcon
_08097190:
	cmp r5, #9
	bne _080971C8
	ldr r1, _080971BC @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r2]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r4, r0
	ldr r1, _080971C0 @ =0x08633364 (sBlob_6131c8_63a19c+0x2019C)
_080971AE:
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _080971C4 @ =EndingProcessAdamPanel
	str r1, [r0]
	b _08097270
	.align 2, 0
_080971BC: .4byte 0x00000236
_080971C0: .4byte sNextPageArrowPal+0x201BC
_080971C4: .4byte EndingProcessAdamPanel
_080971C8:
	cmp r5, #0x14
	bne _080971E4
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r6]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r4, r0
	ldr r1, _080971E0 @ =EndingProcessAnimalsScrolling
	str r1, [r0]
	b _08097270
	.align 2, 0
_080971E0: .4byte EndingProcessAnimalsScrolling
_080971E4:
	cmp r5, #0x1e
	bne _08097238
	ldr r0, _08097224 @ =0x0000012D
	bl SoundPlay
	ldr r4, _08097228 @ =gNonGameplayRam
	asrs r0, r7, #0x18
	lsls r2, r0, #3
	adds r2, r2, r0
	lsls r2, r2, #2
	adds r3, r2, r4
	ldr r0, _0809722C @ =0x00000236
	adds r3, r3, r0
	ldrb r1, [r3]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r3]
	movs r1, #0x8e
	lsls r1, r1, #2
	adds r0, r4, r1
	adds r0, r2, r0
	ldr r1, _08097230 @ =0x08633F24 (sBlob_6131c8_63a19c+0x20D5C)
	str r1, [r0]
	movs r3, #0x8f
	lsls r3, r3, #2
	adds r4, r4, r3
	adds r2, r2, r4
	ldr r0, _08097234 @ =unk_97418
	b _0809726E
	.align 2, 0
_08097224: .4byte 0x0000012D
_08097228: .4byte gNonGameplayRam
_0809722C: .4byte 0x00000236
_08097230: .4byte sNextPageArrowPal+0x20D7C
_08097234: .4byte unk_97418
_08097238:
	cmp r5, #0xff
	bne _08097270
	asrs r0, r7, #0x18
	lsls r2, r0, #3
	adds r2, r2, r0
	lsls r2, r2, #2
	mov r0, ip
	adds r1, r2, r0
	movs r3, #0x8d
	lsls r3, r3, #2
	adds r1, r1, r3
	ldrb r3, [r1]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r3
	strb r0, [r1]
	movs r0, #0x8e
	lsls r0, r0, #2
	add r0, ip
	adds r0, r2, r0
	ldr r1, _08097280 @ =0x086331EC (sBlob_6131c8_63a19c+0x20024)
	str r1, [r0]
	movs r0, #0x8f
	lsls r0, r0, #2
	add r0, ip
	adds r2, r2, r0
	ldr r0, _08097284 @ =unk_96f00
_0809726E:
	str r0, [r2]
_08097270:
	lsrs r0, r7, #0x18
_08097272:
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08097280: .4byte sNextPageArrowPal+0x20044
_08097284: .4byte unk_96f00

	thumb_func_start EndingMonologueVblank
EndingMonologueVblank: @ 0x08097288
	push {lr}
	ldr r1, _080972EC @ =0x040000D4
	ldr r0, _080972F0 @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _080972F4 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r2, _080972F8 @ =0x04000052
	ldr r0, _080972FC @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08097300 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08097304 @ =0x04000054
	ldr r0, _08097308 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x40
	ldr r0, _0809730C @ =gBg1XPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097310 @ =gBg1YPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097314 @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097318 @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _0809731C @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097320 @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	bl unk_98158
	pop {r0}
	bx r0
	.align 2, 0
_080972EC: .4byte 0x040000D4
_080972F0: .4byte gOamData
_080972F4: .4byte 0x84000100
_080972F8: .4byte 0x04000052
_080972FC: .4byte gWrittenToBldalpha_Evb
_08097300: .4byte gWrittenToBldalpha_Eva
_08097304: .4byte 0x04000054
_08097308: .4byte gWrittenToBldy
_0809730C: .4byte gBg1XPosition
_08097310: .4byte gBg1YPosition
_08097314: .4byte 0x0300122C
_08097318: .4byte 0x0300122E
_0809731C: .4byte 0x03001230
_08097320: .4byte 0x03001232

	thumb_func_start EndingConversationAndAnimalsVblank
EndingConversationAndAnimalsVblank: @ 0x08097324
	ldr r1, _08097380 @ =0x040000D4
	ldr r0, _08097384 @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08097388 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r2, _0809738C @ =0x04000052
	ldr r0, _08097390 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08097394 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08097398 @ =0x04000054
	ldr r0, _0809739C @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x40
	ldr r0, _080973A0 @ =gBg1XPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _080973A4 @ =gBg1YPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _080973A8 @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _080973AC @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _080973B0 @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _080973B4 @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	bx lr
	.align 2, 0
_08097380: .4byte 0x040000D4
_08097384: .4byte gOamData
_08097388: .4byte 0x84000100
_0809738C: .4byte 0x04000052
_08097390: .4byte gWrittenToBldalpha_Evb
_08097394: .4byte gWrittenToBldalpha_Eva
_08097398: .4byte 0x04000054
_0809739C: .4byte gWrittenToBldy
_080973A0: .4byte gBg1XPosition
_080973A4: .4byte gBg1YPosition
_080973A8: .4byte 0x0300122C
_080973AC: .4byte 0x0300122E
_080973B0: .4byte 0x03001230
_080973B4: .4byte 0x03001232

	thumb_func_start EndingGetPositionAndSlotOfOamByType_2
EndingGetPositionAndSlotOfOamByType_2: @ 0x080973B8
	push {r4, r5, r6, r7, lr}
	adds r4, r1, #0
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	movs r1, #0
	ldr r7, _080973F0 @ =gNonGameplayRam
	movs r6, #0x8b
	lsls r6, r6, #2
_080973C8:
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r3, r0, r7
	adds r0, r3, r6
	ldrb r0, [r0]
	cmp r0, r5
	bne _080973F8
	movs r5, #0x8a
	lsls r5, r5, #2
	adds r0, r3, r5
	ldrh r0, [r0]
	strh r0, [r4]
	ldr r4, _080973F4 @ =0x0000022A
	adds r0, r3, r4
	ldrh r0, [r0]
	strh r0, [r2]
	adds r0, r1, #0
	b _08097410
	.align 2, 0
_080973F0: .4byte gNonGameplayRam
_080973F4: .4byte 0x0000022A
_080973F8:
	adds r0, r1, #1
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0x13
	bls _080973C8
	movs r5, #0x96
	lsls r5, r5, #1
	adds r0, r5, #0
	strh r0, [r4]
	movs r0, #0xc8
	strh r0, [r2]
	movs r0, #0x14
_08097410:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start unk_97418
unk_97418: @ 0x08097418
	bx lr
	.align 2, 0

	thumb_func_start DiedFromSr388CollisionHandler
DiedFromSr388CollisionHandler: @ 0x0809741C
	push {r4, r5, lr}
	sub sp, #4
	movs r5, #0
	ldr r4, _08097438 @ =gSubGameMode1
	movs r1, #0
	ldrsh r0, [r4, r1]
	cmp r0, #1
	beq _08097468
	cmp r0, #1
	bgt _0809743C
	cmp r0, #0
	beq _08097442
	b _080974B8
	.align 2, 0
_08097438: .4byte gSubGameMode1
_0809743C:
	cmp r0, #2
	beq _08097488
	b _080974B8
_08097442:
	str r5, [sp]
	ldr r1, _0809745C @ =0x040000D4
	mov r2, sp
	str r2, [r1]
	ldr r0, _08097460 @ =gNonGameplayRam
	str r0, [r1, #4]
	ldr r0, _08097464 @ =0x85000150
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r0, #1
	strh r0, [r4]
	b _080974B8
	.align 2, 0
_0809745C: .4byte 0x040000D4
_08097460: .4byte gNonGameplayRam
_08097464: .4byte 0x85000150
_08097468:
	bl DiedOnSr388Collision
	cmp r0, #0
	beq _080974B8
	ldr r0, _08097480 @ =gNonGameplayRam
	ldr r1, _08097484 @ =0x0000020E
	adds r0, r0, r1
	strh r5, [r0]
	movs r0, #2
	strh r0, [r4]
	b _080974B8
	.align 2, 0
_08097480: .4byte gNonGameplayRam
_08097484: .4byte 0x0000020E
_08097488:
	ldr r0, _080974A0 @ =gNonGameplayRam
	ldr r2, _080974A4 @ =0x0000020E
	adds r1, r0, r2
	ldrh r0, [r1]
	cmp r0, #0
	bne _080974B0
	ldr r1, _080974A8 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _080974AC
	adds r0, #1
	b _080974B2
	.align 2, 0
_080974A0: .4byte gNonGameplayRam
_080974A4: .4byte 0x0000020E
_080974A8: .4byte gWrittenToBldy
_080974AC:
	movs r5, #1
	b _080974B4
_080974B0:
	subs r0, #1
_080974B2:
	strh r0, [r1]
_080974B4:
	bl SpecialCutsceneDrawAllOam
_080974B8:
	adds r0, r5, #0
	add sp, #4
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start DiedOnSr388CollisionInit
DiedOnSr388CollisionInit: @ 0x080974C4
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	sub sp, #4
	ldr r3, _08097618 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _0809761C @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08097620 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08097624 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _08097628 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _0809762C @ =unk_99940
	bl CallbackSetVBlank
	movs r5, #0
	str r5, [sp]
	ldr r4, _08097630 @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r1, _08097634 @ =gNonGameplayRam
	mov r8, r1
	str r1, [r4, #4]
	ldr r0, _08097638 @ =0x85000150
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _0809763C @ =0x086238F4 (sBlob_6131c8_63a19c+0x1072C)
	ldr r1, _08097640 @ =0x06010000
	bl LZ77UncompVram
	ldr r0, _08097644 @ =0x08636C38 (sBlob_6131c8_63a19c+0x23A70)
	str r0, [r4]
	ldr r0, _08097648 @ =0x05000200
	str r0, [r4, #4]
	ldr r6, _0809764C @ =0x84000080
	str r6, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08097650 @ =0x0862B5F4 (sBlob_6131c8_63a19c+0x1842C)
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _08097654 @ =0x08638C14 (sBlob_6131c8_63a19c+0x25A4C)
	ldr r1, _08097658 @ =0x0600F000
	bl LZ77UncompVram
	ldr r0, _0809765C @ =0x08639BC4 (sBlob_6131c8_63a19c+0x269FC)
	ldr r1, _08097660 @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _08097664 @ =0x08637038 (sBlob_6131c8_63a19c+0x23E70)
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	str r6, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08097668 @ =gBg1XPosition
	strh r5, [r0]
	ldr r0, _0809766C @ =gBg1YPosition
	movs r2, #8
	strh r2, [r0]
	ldr r0, _08097670 @ =0x0300122C
	strh r5, [r0]
	ldr r0, _08097674 @ =0x0300122E
	strh r5, [r0]
	ldr r0, _08097678 @ =0x03001230
	strh r5, [r0]
	ldr r0, _0809767C @ =0x03001232
	strh r5, [r0]
	ldr r0, _08097680 @ =0x04000010
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	ldr r1, _08097684 @ =0x04000008
	ldr r3, _08097688 @ =0x00001C08
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #2
	ldr r3, _0809768C @ =0x00001E01
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #4
	ldr r3, _08097690 @ =0x00001F03
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xbf
	strh r0, [r1]
	ldr r0, _08097694 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08097698 @ =0x04000054
	strh r1, [r0]
	ldr r0, _0809769C @ =gWrittenToBldalpha_Eva
	strh r2, [r0]
	ldr r1, _080976A0 @ =gWrittenToBldalpha_Evb
	movs r0, #0xe
	strh r0, [r1]
	ldr r0, _080976A4 @ =0x0000024D
	bl SoundPlay_3b1c
	movs r0, #2
	movs r1, #0xa4
	movs r2, #0x28
	movs r3, #1
	bl DiedOnSr388CollisionSetupOam
	movs r0, #1
	movs r1, #0xa4
	movs r2, #0x28
	movs r3, #1
	bl DiedOnSr388CollisionSetupOam
	movs r0, #3
	movs r1, #0x86
	movs r2, #0x3c
	movs r3, #1
	bl DiedOnSr388CollisionSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r0, _080976A8 @ =0x0863A19C (sCutsceneTextNone)
	mov r1, r8
	str r0, [r1]
	str r5, [sp]
	mov r2, sp
	str r2, [r4]
	ldr r0, _080976AC @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _080976B0 @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r3, #0xc0
	lsls r3, r3, #5
	adds r0, r3, #0
	strh r0, [r1]
	ldr r0, _080976B4 @ =DiedOnSr388CollisionVblank
	bl CallbackSetVBlank
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08097618: .4byte 0x04000208
_0809761C: .4byte 0x04000004
_08097620: .4byte 0x0000FFEF
_08097624: .4byte 0x04000200
_08097628: .4byte 0x0000FFFD
_0809762C: .4byte unk_99940
_08097630: .4byte 0x040000D4
_08097634: .4byte gNonGameplayRam
_08097638: .4byte 0x85000150
_0809763C: .4byte sNextPageArrowPal+0x1074C
_08097640: .4byte 0x06010000
_08097644: .4byte sNextPageArrowPal+0x23A90
_08097648: .4byte 0x05000200
_0809764C: .4byte 0x84000080
_08097650: .4byte sNextPageArrowPal+0x1844C
_08097654: .4byte sNextPageArrowPal+0x25A6C
_08097658: .4byte 0x0600F000
_0809765C: .4byte sNextPageArrowPal+0x26A1C
_08097660: .4byte 0x0600F800
_08097664: .4byte sNextPageArrowPal+0x23E90
_08097668: .4byte gBg1XPosition
_0809766C: .4byte gBg1YPosition
_08097670: .4byte 0x0300122C
_08097674: .4byte 0x0300122E
_08097678: .4byte 0x03001230
_0809767C: .4byte 0x03001232
_08097680: .4byte 0x04000010
_08097684: .4byte 0x04000008
_08097688: .4byte 0x00001C08
_0809768C: .4byte 0x00001E01
_08097690: .4byte 0x00001F03
_08097694: .4byte gWrittenToBldy
_08097698: .4byte 0x04000054
_0809769C: .4byte gWrittenToBldalpha_Eva
_080976A0: .4byte gWrittenToBldalpha_Evb
_080976A4: .4byte 0x0000024D
_080976A8: .4byte sCutsceneTextNone
_080976AC: .4byte 0x0600D000
_080976B0: .4byte 0x85000400
_080976B4: .4byte DiedOnSr388CollisionVblank

	thumb_func_start DiedOnSr388CollisionProcess
DiedOnSr388CollisionProcess: @ 0x080976B8
	push {r4, r5, r6, lr}
	movs r5, #0
	ldr r2, _080976E4 @ =gNonGameplayRam
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrh r1, [r0]
	adds r1, #1
	strh r1, [r0]
	movs r4, #0x85
	lsls r4, r4, #2
	adds r0, r2, r4
	ldrb r0, [r0]
	adds r3, r2, #0
	cmp r0, #4
	bls _080976DA
	b _08097862
_080976DA:
	lsls r0, r0, #2
	ldr r1, _080976E8 @ =_080976EC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_080976E4: .4byte gNonGameplayRam
_080976E8: .4byte _080976EC
_080976EC: @ jump table
	.4byte _08097700 @ case 0
	.4byte _08097734 @ case 1
	.4byte _08097740 @ case 2
	.4byte _080977A8 @ case 3
	.4byte _08097808 @ case 4
_08097700:
	ldr r1, _08097710 @ =gWrittenToBldy
	ldrh r0, [r1]
	adds r2, r0, #0
	cmp r2, #0
	beq _08097714
	subs r0, #1
	strh r0, [r1]
	b _080977F8
	.align 2, 0
_08097710: .4byte gWrittenToBldy
_08097714:
	ldr r1, _08097730 @ =0x04000050
	movs r6, #0xc4
	lsls r6, r6, #4
	adds r0, r6, #0
	strh r0, [r1]
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r3, r1
	strh r2, [r0]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #1
	b _080977F6
	.align 2, 0
_08097730: .4byte 0x04000050
_08097734:
	movs r4, #0x84
	lsls r4, r4, #2
	adds r1, r3, r4
	movs r0, #0
	strh r0, [r1]
	b _080977F8
_08097740:
	movs r6, #0x84
	lsls r6, r6, #2
	adds r4, r3, r6
	ldrh r2, [r4]
	cmp r2, #1
	bne _08097774
	ldr r0, _08097768 @ =gWrittenToBldalpha_Eva
	movs r1, #0xa
	strh r1, [r0]
	ldr r0, _0809776C @ =gWrittenToBldalpha_Evb
	strh r1, [r0]
	movs r1, #0x88
	lsls r1, r1, #1
	adds r0, r3, r1
	movs r1, #0
	strb r2, [r0]
	ldr r2, _08097770 @ =0x00000111
	adds r0, r3, r2
	strb r1, [r0]
	b _080977F8
	.align 2, 0
_08097768: .4byte gWrittenToBldalpha_Eva
_0809776C: .4byte gWrittenToBldalpha_Evb
_08097770: .4byte 0x00000111
_08097774:
	cmp r2, #2
	bne _080977F8
	ldr r1, _080977A0 @ =0x04000050
	ldr r6, _080977A4 @ =0x00000842
	adds r0, r6, #0
	strh r0, [r1]
	movs r2, #0x80
	lsls r2, r2, #0x13
	ldrh r0, [r2]
	movs r6, #0x80
	lsls r6, r6, #2
	adds r1, r6, #0
	orrs r0, r1
	strh r0, [r2]
	movs r0, #0
	strh r0, [r4]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r0, #3
	b _080977F6
	.align 2, 0
_080977A0: .4byte 0x04000050
_080977A4: .4byte 0x00000842
_080977A8:
	ldr r1, _080977D4 @ =0x00000111
	adds r4, r3, r1
	ldrb r2, [r4]
	cmp r2, #0xe
	bhi _080977D8
	movs r6, #0x84
	lsls r6, r6, #2
	adds r1, r3, r6
	ldrh r0, [r1]
	cmp r0, #4
	bne _080977F8
	movs r0, #0
	strh r0, [r1]
	movs r0, #0x88
	lsls r0, r0, #1
	adds r1, r3, r0
	movs r0, #1
	strb r0, [r1]
	adds r0, r2, #1
	strb r0, [r4]
	b _080977F8
	.align 2, 0
_080977D4: .4byte 0x00000111
_080977D8:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r1, r3, r2
	ldrh r0, [r1]
	cmp r0, #0xf
	bne _080977F8
	movs r0, #0
	strh r0, [r1]
	ldr r1, _08097804 @ =gWrittenToBldy
	movs r0, #0x10
	strh r0, [r1]
	movs r4, #0x85
	lsls r4, r4, #2
	adds r1, r3, r4
	movs r0, #4
_080977F6:
	strb r0, [r1]
_080977F8:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	b _08097862
	.align 2, 0
_08097804: .4byte gWrittenToBldy
_08097808:
	ldr r4, _08097830 @ =gWrittenToBldalpha_Eva
	ldrh r2, [r4]
	cmp r2, #0xf
	bhi _08097838
	movs r6, #0x84
	lsls r6, r6, #2
	adds r1, r3, r6
	ldrh r0, [r1]
	cmp r0, #6
	bne _0809785A
	movs r0, #0
	strh r0, [r1]
	adds r0, r2, #1
	strh r0, [r4]
	ldr r1, _08097834 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r1]
	adds r0, #1
	strh r0, [r1]
	b _0809785A
	.align 2, 0
_08097830: .4byte gWrittenToBldalpha_Eva
_08097834: .4byte gWrittenToBldalpha_Evb
_08097838:
	ldr r0, _0809786C @ =0x04000050
	movs r1, #0xbf
	strh r1, [r0]
	movs r0, #0x84
	lsls r0, r0, #2
	adds r2, r3, r0
	ldrh r0, [r2]
	cmp r0, #0xf
	bne _0809785A
	movs r0, #0
	movs r1, #0
	strh r1, [r2]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	strb r0, [r1]
	movs r5, #1
_0809785A:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_08097862:
	adds r0, r5, #0
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_0809786C: .4byte 0x04000050

	thumb_func_start DiedOnSr388Collision
DiedOnSr388Collision: @ 0x08097870
	push {r4, r5, lr}
	movs r5, #0
	ldr r4, _08097888 @ =gNonGameplayRam
	ldrh r0, [r4, #8]
	cmp r0, #1
	beq _0809789C
	cmp r0, #1
	bgt _0809788C
	cmp r0, #0
	beq _08097896
	b _080978F0
	.align 2, 0
_08097888: .4byte gNonGameplayRam
_0809788C:
	cmp r0, #2
	beq _080978B4
	cmp r0, #3
	beq _080978D0
	b _080978F0
_08097896:
	bl DiedOnSr388CollisionInit
	b _080978A8
_0809789C:
	bl SpecialCutsceneFadeIn
	ldr r0, _080978B0 @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0
	bne _080978F0
_080978A8:
	movs r0, #2
	strh r0, [r4, #8]
	b _080978F0
	.align 2, 0
_080978B0: .4byte gWrittenToBldy
_080978B4:
	bl DiedOnSr388CollisionProcess
	cmp r0, #0
	beq _080978F0
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r4, r1
	strb r5, [r0]
	subs r1, #1
	adds r0, r4, r1
	strb r5, [r0]
	movs r0, #3
	strh r0, [r4, #8]
	b _080978F0
_080978D0:
	ldr r1, _080978E0 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _080978E4
	adds r0, #1
	strh r0, [r1]
	b _080978E8
	.align 2, 0
_080978E0: .4byte gWrittenToBldy
_080978E4:
	strh r5, [r4, #8]
	movs r5, #1
_080978E8:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_080978F0:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1

	thumb_func_start DiedOnSr388CollisionProcessFallingBsl
DiedOnSr388CollisionProcessFallingBsl: @ 0x080978F8
	push {r4, lr}
	adds r4, r0, #0
	ldrh r0, [r4, #0xa]
	adds r0, #1
	movs r2, #0
	strh r0, [r4, #0xa]
	ldrb r1, [r4, #0x14]
	cmp r1, #0
	bne _0809791A
	ldrh r0, [r4, #0xc]
	strh r0, [r4]
	ldrh r0, [r4, #0xe]
	strh r0, [r4, #2]
	strh r1, [r4, #0xa]
	movs r0, #1
	strb r0, [r4, #0x14]
	b _080979CA
_0809791A:
	cmp r1, #1
	bne _08097978
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #0x12]
	cmp r0, r3
	bne _08097936
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _08097936
	strb r2, [r4, #0x12]
_08097936:
	ldrh r0, [r4, #0xa]
	movs r1, #5
	bl __udivsi3
	ldrh r1, [r4]
	subs r1, r1, r0
	strh r1, [r4, #0xc]
	ldrh r0, [r4, #0xa]
	movs r1, #5
	bl __udivsi3
	ldrh r1, [r4, #2]
	adds r1, r1, r0
	strh r1, [r4, #0xe]
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	cmp r1, #0x50
	ble _08097962
	movs r0, #0
	strh r0, [r4, #0xa]
	movs r0, #2
	strb r0, [r4, #0x14]
_08097962:
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _08097970
	ldrh r0, [r4, #6]
	subs r0, #1
	strh r0, [r4, #6]
	b _080979CA
_08097970:
	ldrh r0, [r4, #6]
	subs r0, #2
	strh r0, [r4, #6]
	b _080979CA
_08097978:
	cmp r1, #2
	bne _080979A4
	movs r0, #3
	strb r0, [r4, #0x14]
	ldrb r0, [r4, #0x10]
	cmp r0, #1
	bne _080979BE
	ldr r0, _0809799C @ =0x086362B8 (sBlob_6131c8_63a19c+0x230F0)
	str r0, [r4, #0x1c]
	strb r2, [r4, #0x12]
	strb r2, [r4, #0x11]
	ldr r0, _080979A0 @ =gNonGameplayRam
	movs r2, #0x85
	lsls r2, r2, #2
	adds r0, r0, r2
	strb r1, [r0]
	b _080979CA
	.align 2, 0
_0809799C: .4byte sNextPageArrowPal+0x23110
_080979A0: .4byte gNonGameplayRam
_080979A4:
	cmp r1, #3
	bne _080979CA
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #0x12]
	cmp r0, r3
	bne _080979CA
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _080979CA
_080979BE:
	strb r2, [r4, #0x10]
	ldrb r1, [r4, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r4, #0x18]
_080979CA:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start unk_979d0
unk_979d0: @ 0x080979D0
	push {lr}
	adds r2, r0, #0
	ldrb r0, [r2, #0x14]
	cmp r0, #0
	bne _080979FC
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r2, #0x12]
	cmp r0, r3
	bne _080979FC
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080979FC
	strb r1, [r2, #0x10]
	ldrb r1, [r2, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2, #0x18]
_080979FC:
	pop {r0}
	bx r0

	thumb_func_start DiedOnSr388CollisionSetupOam
DiedOnSr388CollisionSetupOam: @ 0x08097A00
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r7, r0, #0x18
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	mov r8, r1
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	mov sb, r2
	lsls r3, r3, #0x18
	cmp r3, #0
	bne _08097A64
	movs r2, #0
	ldr r1, _08097A60 @ =gNonGameplayRam
	movs r3, #0x8b
	lsls r3, r3, #2
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, #0
	beq _08097A52
	adds r4, r1, #0
_08097A32:
	lsls r0, r2, #0x18
	movs r1, #0x80
	lsls r1, r1, #0x11
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0x13
	bgt _08097AA2
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _08097A32
_08097A52:
	lsls r0, r2, #0x18
	asrs r1, r0, #0x18
	mov ip, r0
	cmp r1, #0x13
	ble _08097AAC
	b _08097AA2
	.align 2, 0
_08097A60: .4byte gNonGameplayRam
_08097A64:
	movs r2, #0x13
	ldr r1, _08097AA8 @ =gNonGameplayRam
	movs r3, #0x9b
	lsls r3, r3, #3
	adds r0, r1, r3
	ldrb r0, [r0]
	cmp r0, #0
	beq _08097A9A
	adds r4, r1, #0
	movs r3, #0x8b
	lsls r3, r3, #2
_08097A7A:
	lsls r0, r2, #0x18
	movs r1, #0xff
	lsls r1, r1, #0x18
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0
	blt _08097AA2
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _08097A7A
_08097A9A:
	lsls r0, r2, #0x18
	mov ip, r0
	cmp r0, #0
	bge _08097AAC
_08097AA2:
	movs r0, #0x14
	b _08097BE6
	.align 2, 0
_08097AA8: .4byte gNonGameplayRam
_08097AAC:
	movs r0, #0
	str r0, [sp]
	ldr r2, _08097B3C @ =0x040000D4
	mov r3, sp
	str r3, [r2]
	mov r0, ip
	asrs r1, r0, #0x18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r5, r0, #2
	ldr r6, _08097B40 @ =0x030016A0
	adds r0, r5, r6
	str r0, [r2, #4]
	ldr r0, _08097B44 @ =0x85000009
	str r0, [r2, #8]
	ldr r0, [r2, #8]
	ldr r1, _08097B48 @ =0xFFFFFDE4
	adds r0, r6, r1
	adds r2, r5, r0
	movs r3, #0x8a
	lsls r3, r3, #2
	adds r0, r2, r3
	mov r1, r8
	strh r1, [r0]
	adds r3, #2
	adds r0, r2, r3
	mov r1, sb
	strh r1, [r0]
	adds r3, #2
	adds r0, r2, r3
	strb r7, [r0]
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r4, r2, r0
	ldrb r0, [r4]
	movs r1, #1
	orrs r0, r1
	strb r0, [r4]
	cmp r7, #1
	bne _08097B58
	subs r3, #0xa
	adds r1, r2, r3
	movs r0, #0x80
	lsls r0, r0, #1
	strh r0, [r1]
	ldr r0, _08097B4C @ =0x00000236
	adds r2, r2, r0
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	ldrb r1, [r4]
	movs r0, #7
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4]
	adds r0, r6, #0
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08097B50 @ =0x08636020 (sBlob_6131c8_63a19c+0x22E58)
	str r1, [r0]
	adds r0, r6, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08097B54 @ =DiedOnSr388CollisionProcessFallingBsl
	b _08097BE0
	.align 2, 0
_08097B3C: .4byte 0x040000D4
_08097B40: .4byte 0x030016A0
_08097B44: .4byte 0x85000009
_08097B48: .4byte 0xFFFFFDE4
_08097B4C: .4byte 0x00000236
_08097B50: .4byte sNextPageArrowPal+0x22E78
_08097B54: .4byte DiedOnSr388CollisionProcessFallingBsl
_08097B58:
	cmp r7, #2
	bne _08097BB8
	ldr r3, _08097BA8 @ =0x00000222
	adds r1, r2, r3
	movs r0, #0x80
	lsls r0, r0, #2
	strh r0, [r1]
	ldrb r1, [r4]
	movs r0, #0x19
	rsbs r0, r0, #0
	ands r0, r1
	movs r3, #8
	orrs r0, r3
	strb r0, [r4]
	ldr r0, _08097BAC @ =0x00000236
	adds r2, r2, r0
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	orrs r0, r3
	strb r0, [r2]
	ldrb r1, [r4]
	movs r0, #7
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4]
	adds r0, r6, #0
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08097BB0 @ =0x08636038 (sBlob_6131c8_63a19c+0x22E70)
	str r1, [r0]
	adds r0, r6, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08097BB4 @ =DiedOnSr388CollisionProcessFallingBsl
	b _08097BE0
	.align 2, 0
_08097BA8: .4byte 0x00000222
_08097BAC: .4byte 0x00000236
_08097BB0: .4byte sNextPageArrowPal+0x22E90
_08097BB4: .4byte DiedOnSr388CollisionProcessFallingBsl
_08097BB8:
	cmp r7, #3
	bne _08097BE2
	ldr r1, _08097BF4 @ =0x00000236
	adds r2, r2, r1
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r2]
	adds r0, r6, #0
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08097BF8 @ =0x08636050 (sBlob_6131c8_63a19c+0x22E88)
	str r1, [r0]
	adds r0, r6, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08097BFC @ =unk_979d0
_08097BE0:
	str r1, [r0]
_08097BE2:
	mov r3, ip
	lsrs r0, r3, #0x18
_08097BE6:
	add sp, #4
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08097BF4: .4byte 0x00000236
_08097BF8: .4byte sNextPageArrowPal+0x22EA8
_08097BFC: .4byte unk_979d0

	thumb_func_start DiedOnSr388CollisionVblank
DiedOnSr388CollisionVblank: @ 0x08097C00
	push {lr}
	ldr r3, _08097C8C @ =0x040000D4
	ldr r0, _08097C90 @ =gOamData
	str r0, [r3]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r3, #4]
	ldr r0, _08097C94 @ =0x84000100
	str r0, [r3, #8]
	ldr r0, [r3, #8]
	ldr r2, _08097C98 @ =0x04000052
	ldr r0, _08097C9C @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08097CA0 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08097CA4 @ =0x04000054
	ldr r0, _08097CA8 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x40
	ldr r0, _08097CAC @ =gBg1XPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097CB0 @ =gBg1YPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097CB4 @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097CB8 @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097CBC @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097CC0 @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _08097CC4 @ =gNonGameplayRam
	movs r0, #0x88
	lsls r0, r0, #1
	adds r2, r1, r0
	ldrb r0, [r2]
	cmp r0, #1
	bne _08097C86
	movs r0, #0
	strb r0, [r2]
	ldr r2, _08097CC8 @ =0x00000111
	adds r0, r1, r2
	ldrb r0, [r0]
	lsls r0, r0, #5
	ldr r1, _08097CCC @ =0x08636A38 (sBlob_6131c8_63a19c+0x23870)
	adds r0, r0, r1
	str r0, [r3]
	ldr r0, _08097CD0 @ =0x05000120
	str r0, [r3, #4]
	ldr r0, _08097CD4 @ =0x84000008
	str r0, [r3, #8]
	ldr r0, [r3, #8]
_08097C86:
	pop {r0}
	bx r0
	.align 2, 0
_08097C8C: .4byte 0x040000D4
_08097C90: .4byte gOamData
_08097C94: .4byte 0x84000100
_08097C98: .4byte 0x04000052
_08097C9C: .4byte gWrittenToBldalpha_Evb
_08097CA0: .4byte gWrittenToBldalpha_Eva
_08097CA4: .4byte 0x04000054
_08097CA8: .4byte gWrittenToBldy
_08097CAC: .4byte gBg1XPosition
_08097CB0: .4byte gBg1YPosition
_08097CB4: .4byte 0x0300122C
_08097CB8: .4byte 0x0300122E
_08097CBC: .4byte 0x03001230
_08097CC0: .4byte 0x03001232
_08097CC4: .4byte gNonGameplayRam
_08097CC8: .4byte 0x00000111
_08097CCC: .4byte sNextPageArrowPal+0x23890
_08097CD0: .4byte 0x05000120
_08097CD4: .4byte 0x84000008

	thumb_func_start DiedOnSr388CollisionVblank_Unused
DiedOnSr388CollisionVblank_Unused: @ 0x08097CD8
	ldr r1, _08097D34 @ =0x040000D4
	ldr r0, _08097D38 @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08097D3C @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r2, _08097D40 @ =0x04000052
	ldr r0, _08097D44 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08097D48 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08097D4C @ =0x04000054
	ldr r0, _08097D50 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x40
	ldr r0, _08097D54 @ =gBg1XPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097D58 @ =gBg1YPosition
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097D5C @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097D60 @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097D64 @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08097D68 @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	bx lr
	.align 2, 0
_08097D34: .4byte 0x040000D4
_08097D38: .4byte gOamData
_08097D3C: .4byte 0x84000100
_08097D40: .4byte 0x04000052
_08097D44: .4byte gWrittenToBldalpha_Evb
_08097D48: .4byte gWrittenToBldalpha_Eva
_08097D4C: .4byte 0x04000054
_08097D50: .4byte gWrittenToBldy
_08097D54: .4byte gBg1XPosition
_08097D58: .4byte gBg1YPosition
_08097D5C: .4byte 0x0300122C
_08097D60: .4byte 0x0300122E
_08097D64: .4byte 0x03001230
_08097D68: .4byte 0x03001232

	thumb_func_start DiedOnSr388CollisionGetPositionAndSlotOfOamByType
DiedOnSr388CollisionGetPositionAndSlotOfOamByType: @ 0x08097D6C
	push {r4, r5, r6, r7, lr}
	adds r4, r1, #0
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	movs r1, #0
	ldr r7, _08097DA4 @ =gNonGameplayRam
	movs r6, #0x8b
	lsls r6, r6, #2
_08097D7C:
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r3, r0, r7
	adds r0, r3, r6
	ldrb r0, [r0]
	cmp r0, r5
	bne _08097DAC
	movs r5, #0x8a
	lsls r5, r5, #2
	adds r0, r3, r5
	ldrh r0, [r0]
	strh r0, [r4]
	ldr r4, _08097DA8 @ =0x0000022A
	adds r0, r3, r4
	ldrh r0, [r0]
	strh r0, [r2]
	adds r0, r1, #0
	b _08097DC4
	.align 2, 0
_08097DA4: .4byte gNonGameplayRam
_08097DA8: .4byte 0x0000022A
_08097DAC:
	adds r0, r1, #1
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0x13
	bls _08097D7C
	movs r5, #0x96
	lsls r5, r5, #1
	adds r0, r5, #0
	strh r0, [r4]
	movs r0, #0xc8
	strh r0, [r2]
	movs r0, #0x14
_08097DC4:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start unk_97dcc
unk_97dcc: @ 0x08097DCC
	bx lr
	.align 2, 0

	thumb_func_start NewFileIntroCheckMonologueEnded
NewFileIntroCheckMonologueEnded: @ 0x08097DD0
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	movs r0, #0
	mov r8, r0
	ldr r6, _08097E0C @ =gNonGameplayRam
	movs r0, #0x83
	lsls r0, r0, #2
	adds r7, r6, r0
	ldrh r0, [r7]
	adds r4, r0, #1
	strh r4, [r7]
	ldr r3, [r6]
	ldrh r2, [r3]
	adds r5, r2, #0
	movs r0, #0xff
	lsls r0, r0, #8
	mov ip, r0
	cmp r5, ip
	bne _08097E14
	mov r0, r8
	strh r0, [r7]
	ldr r7, _08097E10 @ =0x00000213
	adds r1, r6, r7
	movs r0, #0x64
	strb r0, [r1]
	movs r0, #1
	mov r8, r0
	b _08097E96
	.align 2, 0
_08097E0C: .4byte gNonGameplayRam
_08097E10: .4byte 0x00000213
_08097E14:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r5, r0
	bne _08097E68
	mov r0, r8
	strh r0, [r7]
	movs r7, #0x86
	lsls r7, r7, #2
	adds r4, r6, r7
	ldrb r1, [r4]
	cmp r1, #1
	bne _08097E96
	adds r2, r3, #2
	str r2, [r6]
	subs r7, #5
	adds r0, r6, r7
	strb r1, [r0]
	ldrh r1, [r3, #2]
	movs r0, #0xfd
	lsls r0, r0, #8
	cmp r1, r0
	bne _08097E46
	movs r0, #2
	strb r0, [r4]
	b _08097E96
_08097E46:
	cmp r1, ip
	beq _08097E5C
	cmp r1, r5
	bne _08097E62
	movs r0, #4
	strb r0, [r4]
	adds r0, r2, #2
	str r0, [r6]
	ldrh r0, [r2, #2]
	cmp r0, ip
	bne _08097E96
_08097E5C:
	movs r0, #3
	strb r0, [r4]
	b _08097E96
_08097E62:
	movs r0, #0
	strb r0, [r4]
	b _08097E96
_08097E68:
	mov r0, ip
	ands r0, r2
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _08097E82
	movs r1, #0xff
	ands r1, r2
	lsls r0, r4, #0x10
	lsrs r0, r0, #0x10
	cmp r1, r0
	bhi _08097E96
	b _08097E8A
_08097E82:
	lsls r0, r4, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bls _08097E96
_08097E8A:
	ldr r0, _08097EA4 @ =0x00000213
	adds r1, r6, r0
	movs r0, #1
	strb r0, [r1]
	mov r0, r8
	strh r0, [r7]
_08097E96:
	mov r0, r8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08097EA4: .4byte 0x00000213

	thumb_func_start EndingCheckMonologueEnded
EndingCheckMonologueEnded: @ 0x08097EA8
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	movs r0, #0
	mov r8, r0
	ldr r6, _08097EE4 @ =gNonGameplayRam
	movs r0, #0x83
	lsls r0, r0, #2
	adds r7, r6, r0
	ldrh r0, [r7]
	adds r4, r0, #1
	strh r4, [r7]
	ldr r3, [r6]
	ldrh r2, [r3]
	adds r5, r2, #0
	movs r0, #0xff
	lsls r0, r0, #8
	mov ip, r0
	cmp r5, ip
	bne _08097EEC
	mov r0, r8
	strh r0, [r7]
	ldr r7, _08097EE8 @ =0x00000213
	adds r1, r6, r7
	movs r0, #0x64
	strb r0, [r1]
	movs r0, #1
	mov r8, r0
	b _08097F6E
	.align 2, 0
_08097EE4: .4byte gNonGameplayRam
_08097EE8: .4byte 0x00000213
_08097EEC:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r5, r0
	bne _08097F40
	mov r0, r8
	strh r0, [r7]
	movs r7, #0x86
	lsls r7, r7, #2
	adds r4, r6, r7
	ldrb r1, [r4]
	cmp r1, #1
	bne _08097F6E
	adds r2, r3, #2
	str r2, [r6]
	subs r7, #5
	adds r0, r6, r7
	strb r1, [r0]
	ldrh r1, [r3, #2]
	movs r0, #0xfd
	lsls r0, r0, #8
	cmp r1, r0
	bne _08097F1E
	movs r0, #2
	strb r0, [r4]
	b _08097F6E
_08097F1E:
	cmp r1, ip
	beq _08097F34
	cmp r1, r5
	bne _08097F3A
	movs r0, #4
	strb r0, [r4]
	adds r0, r2, #2
	str r0, [r6]
	ldrh r0, [r2, #2]
	cmp r0, ip
	bne _08097F6E
_08097F34:
	movs r0, #3
	strb r0, [r4]
	b _08097F6E
_08097F3A:
	movs r0, #0
	strb r0, [r4]
	b _08097F6E
_08097F40:
	mov r0, ip
	ands r0, r2
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _08097F5A
	movs r1, #0xff
	ands r1, r2
	lsls r0, r4, #0x10
	lsrs r0, r0, #0x10
	cmp r1, r0
	bhi _08097F6E
	b _08097F62
_08097F5A:
	lsls r0, r4, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #3
	bls _08097F6E
_08097F62:
	ldr r0, _08097F7C @ =0x00000213
	adds r1, r6, r0
	movs r0, #1
	strb r0, [r1]
	mov r0, r8
	strh r0, [r7]
_08097F6E:
	mov r0, r8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08097F7C: .4byte 0x00000213

	thumb_func_start SpecialCutsceneProcessMonologue
SpecialCutsceneProcessMonologue: @ 0x08097F80
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #8
	ldr r5, _08097FF0 @ =gNonGameplayRam
	ldr r2, [r5]
	ldrh r3, [r2]
	adds r1, r3, #0
	movs r6, #0xff
	lsls r6, r6, #8
	adds r4, r5, #0
	cmp r1, r6
	bne _08097F9C
	b _08098142
_08097F9C:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r1, r0
	bne _08097FF8
	ldrh r0, [r4, #0xc]
	adds r0, #1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	cmp r2, #0x1b
	bhi _08097FD4
	adds r6, r4, #0
	adds r5, #0x14
	movs r3, #0xff
_08097FB6:
	ldrh r1, [r6, #0xe]
	lsrs r1, r1, #1
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	adds r0, r2, r0
	adds r0, r0, r5
	ldrb r1, [r0]
	orrs r1, r3
	strb r1, [r0]
	adds r0, r2, #1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	cmp r2, #0x1b
	bls _08097FB6
_08097FD4:
	movs r1, #0
	movs r0, #0
	strh r0, [r4, #0xc]
	ldrh r0, [r4, #0xe]
	adds r0, #2
	strh r0, [r4, #0xe]
	ldr r0, [r4]
	adds r0, #2
	str r0, [r4]
	ldr r2, _08097FF4 @ =0x00000212
	adds r0, r4, r2
	strb r1, [r0]
	b _08098142
	.align 2, 0
_08097FF0: .4byte gNonGameplayRam
_08097FF4: .4byte 0x00000212
_08097FF8:
	movs r0, #0xfd
	lsls r0, r0, #8
	cmp r1, r0
	bne _0809807C
	movs r2, #0
	str r2, [sp, #4]
	ldr r1, _08098064 @ =0x040000D4
	add r5, sp, #4
	str r5, [r1]
	movs r0, #0xc0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08098068 @ =0x85001200
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r3, #0
	strh r2, [r4, #0x12]
	strh r2, [r4, #0x10]
	strh r2, [r4, #0xe]
	strh r2, [r4, #0xc]
	ldr r0, [r4]
	adds r0, #2
	str r0, [r4]
	ldr r5, _0809806C @ =0x00000212
	adds r0, r4, r5
	strb r3, [r0]
	str r2, [sp, #4]
	add r0, sp, #4
	str r0, [r1]
	adds r0, r4, #0
	adds r0, #0x14
	str r0, [r1, #4]
	ldr r3, _08098070 @ =0x8500003F
	str r3, [r1, #8]
	ldr r0, [r1, #8]
	str r2, [sp, #4]
	add r2, sp, #4
	str r2, [r1]
	movs r5, #0x88
	lsls r5, r5, #1
	adds r0, r4, r5
	str r0, [r1, #4]
	str r3, [r1, #8]
	ldr r0, [r1, #8]
	movs r0, #0x80
	lsls r0, r0, #0x12
	str r0, [r1]
	ldr r0, _08098074 @ =0x06004800
	str r0, [r1, #4]
	ldr r0, _08098078 @ =0x84000200
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _08098142
	.align 2, 0
_08098064: .4byte 0x040000D4
_08098068: .4byte 0x85001200
_0809806C: .4byte 0x00000212
_08098070: .4byte 0x8500003F
_08098074: .4byte 0x06004800
_08098078: .4byte 0x84000200
_0809807C:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _0809808C
	ldrh r0, [r4, #0xc]
	adds r0, #1
	strh r0, [r4, #0xc]
	b _08098142
_0809808C:
	adds r0, r6, #0
	ands r0, r3
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _0809809E
	adds r0, r2, #2
	str r0, [r4]
	b _08098142
_0809809E:
	ldrh r4, [r5, #0xc]
	lsls r4, r4, #5
	ldrh r0, [r5, #0xe]
	lsls r0, r0, #0xa
	adds r4, r4, r0
	movs r0, #0xc0
	lsls r0, r0, #0x13
	adds r4, r4, r0
	ldrh r0, [r2]
	bl TextGetCharacterWidth
	mov r8, r0
	ldr r0, [r5]
	ldrh r0, [r0]
	mov r1, r8
	lsls r2, r1, #0x18
	lsrs r2, r2, #0x18
	ldr r1, _08098150 @ =0x00000212
	adds r6, r5, r1
	ldrb r3, [r6]
	movs r1, #0
	str r1, [sp]
	adds r1, r4, #0
	bl TextDrawCharacter
	ldrh r0, [r5, #0xc]
	cmp r0, #0x1b
	bhi _0809813A
	ldrh r1, [r5, #0xe]
	lsrs r1, r1, #1
	lsls r0, r1, #3
	subs r0, r0, r1
	lsls r0, r0, #2
	ldrh r2, [r5, #0xc]
	adds r0, r0, r2
	adds r7, r5, #0
	adds r7, #0x14
	adds r0, r0, r7
	movs r1, #4
	strb r1, [r0]
	ldrb r0, [r6]
	add r0, r8
	strb r0, [r6]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r4, r5, #0
	cmp r0, #7
	bls _0809813A
	adds r2, r4, #0
	adds r3, r6, #0
	adds r4, r7, #0
_08098104:
	ldrb r0, [r3]
	adds r1, r0, #0
	subs r1, #8
	strb r1, [r3]
	ldrh r0, [r2, #0xc]
	adds r0, #1
	strh r0, [r2, #0xc]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x1b
	bhi _0809813A
	lsls r0, r1, #0x18
	cmp r0, #0
	beq _08098134
	ldrh r0, [r2, #0xe]
	lsrs r0, r0, #1
	lsls r1, r0, #3
	subs r1, r1, r0
	lsls r1, r1, #2
	ldrh r5, [r2, #0xc]
	adds r1, r1, r5
	adds r1, r1, r4
	movs r0, #4
	strb r0, [r1]
_08098134:
	ldrb r0, [r3]
	cmp r0, #7
	bhi _08098104
_0809813A:
	ldr r1, _08098154 @ =gNonGameplayRam
	ldr r0, [r1]
	adds r0, #2
	str r0, [r1]
_08098142:
	add sp, #8
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08098150: .4byte 0x00000212
_08098154: .4byte gNonGameplayRam

	thumb_func_start unk_98158
unk_98158: @ 0x08098158
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x10
	ldr r1, _08098198 @ =gNonGameplayRam
	ldrh r6, [r1, #0x10]
	ldrh r0, [r1, #0x12]
	lsrs r7, r0, #1
	ldrh r0, [r1, #0xe]
	lsrs r0, r0, #1
	str r1, [sp, #8]
	cmp r7, r0
	bls _08098178
	b _0809827C
_08098178:
	str r1, [sp]
_0809817A:
	ldr r2, [sp]
	ldr r0, [r2]
	ldrh r0, [r0]
	movs r3, #0xfc
	lsls r3, r3, #8
	cmp r0, r3
	bne _0809819C
	ldrh r0, [r1, #0xc]
	cmp r0, #0x1b
	bhi _080981B6
	adds r0, #1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	mov ip, r0
	b _080981BA
	.align 2, 0
_08098198: .4byte gNonGameplayRam
_0809819C:
	ldrh r0, [r1, #0xe]
	lsrs r0, r0, #1
	cmp r7, r0
	bne _080981B6
	ldr r1, [sp]
	ldrh r0, [r1, #0xc]
	movs r2, #0x1c
	mov ip, r2
	cmp r0, #0x1b
	bhi _080981BA
	adds r3, r0, #0
	mov ip, r3
	b _080981BA
_080981B6:
	movs r5, #0x1c
	mov ip, r5
_080981BA:
	adds r0, r7, #1
	str r0, [sp, #4]
	cmp r6, ip
	bhs _08098268
	ldr r1, _08098230 @ =gNonGameplayRam
	mov r8, r1
	lsls r0, r7, #3
	subs r0, r0, r7
	lsls r0, r0, #2
	mov sl, r0
	ldr r2, _08098234 @ =0x00000FFF
	mov sb, r2
_080981D2:
	mov r3, sl
	adds r2, r6, r3
	ldr r5, _08098238 @ =0x03001594
	adds r1, r2, r5
	ldrb r0, [r1]
	cmp r0, #5
	bne _0809825A
	movs r0, #0
	strb r0, [r1]
	ldr r0, [sp, #8]
	adds r0, #0x14
	adds r2, r2, r0
	ldrb r0, [r2]
	subs r1, r0, #1
	strb r1, [r2]
	lsls r0, r1, #0x18
	asrs r0, r0, #0x18
	cmp r0, #0
	ble _08098244
	lsls r2, r6, #1
	lsls r0, r7, #7
	adds r2, r2, r0
	ldr r0, _0809823C @ =0x06004842
	adds r0, r2, r0
	str r0, [sp, #0xc]
	ldr r1, _08098240 @ =0x06004882
	adds r2, r2, r1
	ldrh r3, [r0]
	ldrh r4, [r2]
	lsrs r0, r3, #0xc
	lsrs r1, r4, #0xc
	subs r0, #1
	lsls r0, r0, #0x10
	subs r1, #1
	lsls r1, r1, #0x10
	lsrs r0, r0, #4
	mov r5, sb
	ands r3, r5
	orrs r0, r3
	ldr r3, [sp, #0xc]
	strh r0, [r3]
	lsrs r1, r1, #4
	ands r4, r5
	orrs r1, r4
	strh r1, [r2]
	b _0809825E
	.align 2, 0
_08098230: .4byte gNonGameplayRam
_08098234: .4byte 0x00000FFF
_08098238: .4byte 0x03001594
_0809823C: .4byte 0x06004842
_08098240: .4byte 0x06004882
_08098244:
	cmp r0, #0
	bne _08098252
	mov r5, r8
	strh r6, [r5, #0x10]
	lsls r0, r7, #1
	strh r0, [r5, #0x12]
	b _0809825E
_08098252:
	movs r0, #0xff
	orrs r1, r0
	strb r1, [r2]
	b _08098268
_0809825A:
	adds r0, #1
	strb r0, [r1]
_0809825E:
	adds r0, r6, #1
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
	cmp r6, ip
	blo _080981D2
_08098268:
	movs r6, #0
	ldr r1, [sp, #4]
	lsls r0, r1, #0x10
	lsrs r7, r0, #0x10
	ldr r1, [sp, #8]
	ldrh r0, [r1, #0xe]
	lsrs r0, r0, #1
	cmp r7, r0
	bhi _0809827C
	b _0809817A
_0809827C:
	add sp, #0x10
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

	thumb_func_start EndingProcessAdamText
EndingProcessAdamText: @ 0x0809828C
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	sub sp, #8
	movs r7, #0
	ldr r5, _080982E8 @ =gNonGameplayRam
	movs r0, #0x83
	lsls r0, r0, #2
	adds r6, r5, r0
	ldrh r0, [r6]
	adds r2, r0, #1
	movs r1, #0
	mov sb, r1
	strh r2, [r6]
	ldr r3, [r5]
	ldrh r4, [r3]
	adds r1, r4, #0
	movs r0, #0xff
	lsls r0, r0, #8
	mov ip, r0
	cmp r1, ip
	bne _080982FC
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xf
	bhi _080982C4
	b _08098492
_080982C4:
	strh r7, [r6]
	str r7, [sp, #4]
	ldr r1, _080982EC @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _080982F0 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _080982F4 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	strh r7, [r5, #0xe]
	strh r7, [r5, #0xc]
	ldr r1, _080982F8 @ =0x00000212
	adds r0, r5, r1
	mov r1, sb
	strb r1, [r0]
	movs r7, #1
	b _08098492
	.align 2, 0
_080982E8: .4byte gNonGameplayRam
_080982EC: .4byte 0x040000D4
_080982F0: .4byte 0x0600D000
_080982F4: .4byte 0x85000400
_080982F8: .4byte 0x00000212
_080982FC:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r1, r0
	bne _0809836C
	ldrh r0, [r5, #0xe]
	cmp r0, #1
	bhi _0809832C
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #5
	bhi _08098314
	b _08098492
_08098314:
	strh r7, [r6]
	movs r0, #2
	strh r0, [r5, #0xe]
	strh r7, [r5, #0xc]
	ldr r1, _08098328 @ =0x00000212
	adds r0, r5, r1
	mov r1, sb
	strb r1, [r0]
	b _08098408
	.align 2, 0
_08098328: .4byte 0x00000212
_0809832C:
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x7d
	bhi _08098336
	b _08098492
_08098336:
	strh r7, [r6]
	strh r7, [r5, #0xe]
	strh r7, [r5, #0xc]
	ldr r1, _0809835C @ =0x00000212
	adds r0, r5, r1
	mov r1, sb
	strb r1, [r0]
	adds r0, r3, #2
	str r0, [r5]
	str r7, [sp, #4]
	ldr r1, _08098360 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _08098364 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _08098368 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _08098492
	.align 2, 0
_0809835C: .4byte 0x00000212
_08098360: .4byte 0x040000D4
_08098364: .4byte 0x0600D000
_08098368: .4byte 0x85000400
_0809836C:
	movs r0, #0xfd
	lsls r0, r0, #8
	mov r8, r0
	cmp r1, r8
	bne _080983B8
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xf
	bhi _08098380
	b _08098492
_08098380:
	strh r7, [r6]
	str r7, [sp, #4]
	ldr r1, _080983A8 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _080983AC @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _080983B0 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	strh r7, [r5, #0xe]
	strh r7, [r5, #0xc]
	adds r0, r3, #2
	str r0, [r5]
	ldr r1, _080983B4 @ =0x00000212
	adds r0, r5, r1
	mov r1, sb
	strb r1, [r0]
	b _08098492
	.align 2, 0
_080983A8: .4byte 0x040000D4
_080983AC: .4byte 0x0600D000
_080983B0: .4byte 0x85000400
_080983B4: .4byte 0x00000212
_080983B8:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _080983EE
	strh r7, [r6]
	movs r0, #0x86
	lsls r0, r0, #2
	adds r1, r5, r0
	ldrb r0, [r1]
	cmp r0, #1
	bne _08098492
	adds r0, r3, #2
	str r0, [r5]
	ldrh r0, [r3, #2]
	cmp r0, r8
	bne _080983DE
	movs r0, #2
	strb r0, [r1]
	b _08098492
_080983DE:
	cmp r0, ip
	bne _080983E8
	movs r0, #3
	strb r0, [r1]
	b _08098492
_080983E8:
	mov r0, sb
	strb r0, [r1]
	b _08098492
_080983EE:
	mov r0, ip
	ands r0, r4
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _0809840E
	movs r1, #0xff
	ands r1, r4
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r1, r0
	bhi _08098492
	strh r7, [r6]
_08098408:
	adds r0, r3, #2
	str r0, [r5]
	b _08098492
_0809840E:
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #5
	bls _08098492
	strh r7, [r6]
	ldrh r4, [r5, #0xc]
	lsls r4, r4, #5
	ldrh r0, [r5, #0xe]
	lsls r0, r0, #0xa
	adds r4, r4, r0
	ldr r1, _080984A4 @ =0x0600D000
	adds r4, r4, r1
	ldrh r0, [r3]
	bl TextGetCharacterWidth
	mov r8, r0
	ldr r0, [r5]
	ldrh r0, [r0]
	mov r1, r8
	lsls r2, r1, #0x18
	lsrs r2, r2, #0x18
	ldr r1, _080984A8 @ =0x00000212
	adds r6, r5, r1
	ldrb r3, [r6]
	str r7, [sp]
	adds r1, r4, #0
	bl TextDrawCharacter
	ldr r1, [r5]
	ldrh r0, [r1]
	cmp r0, #0x40
	beq _08098454
	movs r1, #1
	bl PlayCharacterAppearingSound
_08098454:
	ldrh r0, [r5, #0xc]
	adds r4, r5, #0
	cmp r0, #0x1f
	bhi _0809848C
	ldrb r0, [r6]
	add r0, r8
	strb r0, [r6]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _0809848C
	adds r3, r4, #0
	adds r2, r6, #0
_0809846E:
	ldrb r0, [r2]
	adds r1, r0, #0
	subs r1, #8
	strb r1, [r2]
	ldrh r0, [r3, #0xc]
	adds r0, #1
	strh r0, [r3, #0xc]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x1f
	bhi _0809848C
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _0809846E
_0809848C:
	ldr r0, [r4]
	adds r0, #2
	str r0, [r4]
_08098492:
	adds r0, r7, #0
	add sp, #8
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080984A4: .4byte 0x0600D000
_080984A8: .4byte 0x00000212

	thumb_func_start IntroProcessText
IntroProcessText: @ 0x080984AC
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #8
	movs r0, #0
	mov r8, r0
	ldr r5, _08098514 @ =gNonGameplayRam
	movs r1, #0x83
	lsls r1, r1, #2
	adds r7, r5, r1
	ldrh r0, [r7]
	adds r2, r0, #1
	movs r0, #0
	mov sl, r0
	strh r2, [r7]
	ldr r6, [r5]
	ldrh r4, [r6]
	adds r3, r4, #0
	movs r1, #0xff
	lsls r1, r1, #8
	mov ip, r1
	cmp r3, ip
	bne _08098528
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xc
	bhi _080984E8
	b _080986D2
_080984E8:
	mov r0, r8
	strh r0, [r7]
	mov r1, r8
	str r1, [sp, #4]
	ldr r1, _08098518 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _0809851C @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _08098520 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	mov r1, r8
	strh r1, [r5, #0xe]
	strh r1, [r5, #0xc]
	ldr r1, _08098524 @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	movs r0, #1
	mov r8, r0
	b _080986D2
	.align 2, 0
_08098514: .4byte gNonGameplayRam
_08098518: .4byte 0x040000D4
_0809851C: .4byte 0x0600D000
_08098520: .4byte 0x85000400
_08098524: .4byte 0x00000212
_08098528:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r3, r0
	bne _0809859C
	ldrh r0, [r5, #0xe]
	cmp r0, #1
	bhi _08098558
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bhi _08098540
	b _080986D2
_08098540:
	mov r1, r8
	strh r1, [r7]
	movs r0, #2
	strh r0, [r5, #0xe]
	strh r1, [r5, #0xc]
	ldr r1, _08098554 @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	b _08098654
	.align 2, 0
_08098554: .4byte 0x00000212
_08098558:
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x7a
	bhi _08098562
	b _080986D2
_08098562:
	mov r0, r8
	strh r0, [r7]
	strh r0, [r5, #0xe]
	strh r0, [r5, #0xc]
	ldr r1, _0809858C @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	adds r0, r6, #2
	str r0, [r5]
	mov r0, r8
	str r0, [sp, #4]
	ldr r1, _08098590 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _08098594 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _08098598 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _080986D2
	.align 2, 0
_0809858C: .4byte 0x00000212
_08098590: .4byte 0x040000D4
_08098594: .4byte 0x0600D000
_08098598: .4byte 0x85000400
_0809859C:
	movs r1, #0xfd
	lsls r1, r1, #8
	mov sb, r1
	cmp r3, sb
	bne _080985EC
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xc
	bhi _080985B0
	b _080986D2
_080985B0:
	mov r0, r8
	strh r0, [r7]
	mov r1, r8
	str r1, [sp, #4]
	ldr r1, _080985DC @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _080985E0 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _080985E4 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	mov r1, r8
	strh r1, [r5, #0xe]
	strh r1, [r5, #0xc]
	adds r0, r6, #2
	str r0, [r5]
	ldr r1, _080985E8 @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	b _080986D2
	.align 2, 0
_080985DC: .4byte 0x040000D4
_080985E0: .4byte 0x0600D000
_080985E4: .4byte 0x85000400
_080985E8: .4byte 0x00000212
_080985EC:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r3, r0
	bne _08098638
	mov r0, r8
	strh r0, [r7]
	movs r1, #0x86
	lsls r1, r1, #2
	adds r2, r5, r1
	ldrb r0, [r2]
	cmp r0, #1
	bne _080986D2
	adds r1, r6, #2
	str r1, [r5]
	ldrh r0, [r6, #2]
	cmp r0, sb
	bne _08098614
	movs r0, #2
	strb r0, [r2]
	b _080986D2
_08098614:
	cmp r0, ip
	beq _08098626
	cmp r0, r3
	bne _08098632
	adds r0, r1, #2
	str r0, [r5]
	ldrh r0, [r1, #2]
	cmp r0, ip
	bne _0809862C
_08098626:
	movs r0, #3
	strb r0, [r2]
	b _080986D2
_0809862C:
	movs r0, #4
	strb r0, [r2]
	b _080986D2
_08098632:
	mov r0, sl
	strb r0, [r2]
	b _080986D2
_08098638:
	mov r0, ip
	ands r0, r4
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _0809865A
	movs r1, #0xff
	ands r1, r4
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r1, r0
	bhi _080986D2
	mov r1, r8
	strh r1, [r7]
_08098654:
	adds r0, r6, #2
	str r0, [r5]
	b _080986D2
_0809865A:
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bls _080986D2
	mov r0, r8
	strh r0, [r7]
	ldrh r4, [r5, #0xc]
	lsls r4, r4, #5
	ldrh r0, [r5, #0xe]
	lsls r0, r0, #0xa
	adds r4, r4, r0
	ldr r1, _080986E4 @ =0x0600D000
	adds r4, r4, r1
	ldrh r0, [r6]
	bl TextGetCharacterWidth
	adds r7, r0, #0
	ldr r0, [r5]
	ldrh r0, [r0]
	lsls r2, r7, #0x18
	lsrs r2, r2, #0x18
	ldr r1, _080986E8 @ =0x00000212
	adds r6, r5, r1
	ldrb r3, [r6]
	mov r1, r8
	str r1, [sp]
	adds r1, r4, #0
	bl TextDrawCharacter
	ldrh r0, [r5, #0xc]
	cmp r0, #0x1f
	bhi _080986CA
	ldrb r0, [r6]
	adds r0, r0, r7
	strb r0, [r6]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _080986CA
	adds r3, r5, #0
	adds r2, r6, #0
_080986AC:
	ldrb r0, [r2]
	adds r1, r0, #0
	subs r1, #8
	strb r1, [r2]
	ldrh r0, [r3, #0xc]
	adds r0, #1
	strh r0, [r3, #0xc]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x1f
	bhi _080986CA
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _080986AC
_080986CA:
	ldr r1, _080986EC @ =gNonGameplayRam
	ldr r0, [r1]
	adds r0, #2
	str r0, [r1]
_080986D2:
	mov r0, r8
	add sp, #8
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_080986E4: .4byte 0x0600D000
_080986E8: .4byte 0x00000212
_080986EC: .4byte gNonGameplayRam

	thumb_func_start NewFileIntroProcessAdamText
NewFileIntroProcessAdamText: @ 0x080986F0
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #8
	movs r0, #0
	mov r8, r0
	ldr r5, _08098758 @ =gNonGameplayRam
	movs r1, #0x83
	lsls r1, r1, #2
	adds r7, r5, r1
	ldrh r0, [r7]
	adds r2, r0, #1
	movs r0, #0
	mov sl, r0
	strh r2, [r7]
	ldr r6, [r5]
	ldrh r4, [r6]
	adds r3, r4, #0
	movs r1, #0xff
	lsls r1, r1, #8
	mov ip, r1
	cmp r3, ip
	bne _0809876C
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xc
	bhi _0809872C
	b _08098924
_0809872C:
	mov r0, r8
	strh r0, [r7]
	mov r1, r8
	str r1, [sp, #4]
	ldr r1, _0809875C @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _08098760 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _08098764 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	mov r1, r8
	strh r1, [r5, #0xe]
	strh r1, [r5, #0xc]
	ldr r1, _08098768 @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	movs r0, #1
	mov r8, r0
	b _08098924
	.align 2, 0
_08098758: .4byte gNonGameplayRam
_0809875C: .4byte 0x040000D4
_08098760: .4byte 0x0600D000
_08098764: .4byte 0x85000400
_08098768: .4byte 0x00000212
_0809876C:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r3, r0
	bne _080987E0
	ldrh r0, [r5, #0xe]
	cmp r0, #1
	bhi _0809879C
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bhi _08098784
	b _08098924
_08098784:
	mov r1, r8
	strh r1, [r7]
	movs r0, #2
	strh r0, [r5, #0xe]
	strh r1, [r5, #0xc]
	ldr r1, _08098798 @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	b _08098898
	.align 2, 0
_08098798: .4byte 0x00000212
_0809879C:
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x7a
	bhi _080987A6
	b _08098924
_080987A6:
	mov r0, r8
	strh r0, [r7]
	strh r0, [r5, #0xe]
	strh r0, [r5, #0xc]
	ldr r1, _080987D0 @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	adds r0, r6, #2
	str r0, [r5]
	mov r0, r8
	str r0, [sp, #4]
	ldr r1, _080987D4 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _080987D8 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _080987DC @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _08098924
	.align 2, 0
_080987D0: .4byte 0x00000212
_080987D4: .4byte 0x040000D4
_080987D8: .4byte 0x0600D000
_080987DC: .4byte 0x85000400
_080987E0:
	movs r1, #0xfd
	lsls r1, r1, #8
	mov sb, r1
	cmp r3, sb
	bne _08098830
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xc
	bhi _080987F4
	b _08098924
_080987F4:
	mov r0, r8
	strh r0, [r7]
	mov r1, r8
	str r1, [sp, #4]
	ldr r1, _08098820 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _08098824 @ =0x0600D000
	str r0, [r1, #4]
	ldr r0, _08098828 @ =0x85000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	mov r1, r8
	strh r1, [r5, #0xe]
	strh r1, [r5, #0xc]
	adds r0, r6, #2
	str r0, [r5]
	ldr r1, _0809882C @ =0x00000212
	adds r0, r5, r1
	mov r1, sl
	strb r1, [r0]
	b _08098924
	.align 2, 0
_08098820: .4byte 0x040000D4
_08098824: .4byte 0x0600D000
_08098828: .4byte 0x85000400
_0809882C: .4byte 0x00000212
_08098830:
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r3, r0
	bne _0809887C
	mov r0, r8
	strh r0, [r7]
	movs r1, #0x86
	lsls r1, r1, #2
	adds r2, r5, r1
	ldrb r0, [r2]
	cmp r0, #1
	bne _08098924
	adds r1, r6, #2
	str r1, [r5]
	ldrh r0, [r6, #2]
	cmp r0, sb
	bne _08098858
	movs r0, #2
	strb r0, [r2]
	b _08098924
_08098858:
	cmp r0, ip
	beq _0809886A
	cmp r0, r3
	bne _08098876
	adds r0, r1, #2
	str r0, [r5]
	ldrh r0, [r1, #2]
	cmp r0, ip
	bne _08098870
_0809886A:
	movs r0, #3
	strb r0, [r2]
	b _08098924
_08098870:
	movs r0, #4
	strb r0, [r2]
	b _08098924
_08098876:
	mov r0, sl
	strb r0, [r2]
	b _08098924
_0809887C:
	mov r0, ip
	ands r0, r4
	movs r1, #0xe1
	lsls r1, r1, #8
	cmp r0, r1
	bne _0809889E
	movs r1, #0xff
	ands r1, r4
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r1, r0
	bhi _08098924
	mov r1, r8
	strh r1, [r7]
_08098898:
	adds r0, r6, #2
	str r0, [r5]
	b _08098924
_0809889E:
	lsls r0, r2, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bls _08098924
	mov r0, r8
	strh r0, [r7]
	ldrh r4, [r5, #0xc]
	lsls r4, r4, #5
	ldrh r0, [r5, #0xe]
	lsls r0, r0, #0xa
	adds r4, r4, r0
	ldr r1, _08098938 @ =0x0600D000
	adds r4, r4, r1
	ldrh r0, [r6]
	bl TextGetCharacterWidth
	adds r7, r0, #0
	ldr r0, [r5]
	ldrh r0, [r0]
	lsls r2, r7, #0x18
	lsrs r2, r2, #0x18
	ldr r1, _0809893C @ =0x00000212
	adds r6, r5, r1
	ldrb r3, [r6]
	mov r1, r8
	str r1, [sp]
	adds r1, r4, #0
	bl TextDrawCharacter
	ldr r1, [r5]
	ldrh r0, [r1]
	cmp r0, #0x40
	beq _080988E6
	movs r1, #1
	bl PlayCharacterAppearingSound
_080988E6:
	ldrh r0, [r5, #0xc]
	adds r4, r5, #0
	cmp r0, #0x1f
	bhi _0809891E
	ldrb r0, [r6]
	adds r0, r0, r7
	strb r0, [r6]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _0809891E
	adds r3, r4, #0
	adds r2, r6, #0
_08098900:
	ldrb r0, [r2]
	adds r1, r0, #0
	subs r1, #8
	strb r1, [r2]
	ldrh r0, [r3, #0xc]
	adds r0, #1
	strh r0, [r3, #0xc]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x1f
	bhi _0809891E
	lsls r0, r1, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bhi _08098900
_0809891E:
	ldr r0, [r4]
	adds r0, #2
	str r0, [r4]
_08098924:
	mov r0, r8
	add sp, #8
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08098938: .4byte 0x0600D000
_0809893C: .4byte 0x00000212

	thumb_func_start Dma3Transfer_Unused1
Dma3Transfer_Unused1: @ 0x08098940
	push {r4, r5, r6, r7, lr}
	adds r5, r0, #0
	adds r4, r1, #0
	lsls r3, r3, #0x10
	lsrs r7, r3, #0x10
	lsls r2, r2, #0x15
	movs r3, #0
	cmp r3, r7
	bhs _08098976
	ldr r1, _0809897C @ =0x040000D4
	lsrs r2, r2, #0x12
	movs r0, #0x84
	lsls r0, r0, #0x18
	orrs r2, r0
	movs r6, #0x80
	lsls r6, r6, #3
_08098960:
	str r5, [r1]
	str r4, [r1, #4]
	str r2, [r1, #8]
	ldr r0, [r1, #8]
	adds r5, r5, r6
	adds r4, r4, r6
	adds r0, r3, #1
	lsls r0, r0, #0x10
	lsrs r3, r0, #0x10
	cmp r3, r7
	blo _08098960
_08098976:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0809897C: .4byte 0x040000D4

	thumb_func_start Dma3Transfer_Unused2
Dma3Transfer_Unused2: @ 0x08098980
	push {r4, r5, r6, lr}
	adds r5, r0, #0
	adds r4, r1, #0
	lsls r3, r3, #0x10
	lsrs r6, r3, #0x10
	lsls r2, r2, #0x11
	movs r3, #0
	cmp r3, r6
	bhs _080989B2
	ldr r1, _080989B8 @ =0x040000D4
	lsrs r2, r2, #0x11
	movs r0, #0x80
	lsls r0, r0, #0x18
	orrs r2, r0
_0809899C:
	str r5, [r1]
	str r4, [r1, #4]
	str r2, [r1, #8]
	ldr r0, [r1, #8]
	adds r5, #0x40
	adds r4, #0x40
	adds r0, r3, #1
	lsls r0, r0, #0x10
	lsrs r3, r0, #0x10
	cmp r3, r6
	blo _0809899C
_080989B2:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080989B8: .4byte 0x040000D4

	thumb_func_start Dma3Clear_Unused
Dma3Clear_Unused: @ 0x080989BC
	push {r4, r5, r6, r7, lr}
	sub sp, #4
	adds r4, r0, #0
	lsls r2, r2, #0x10
	lsrs r5, r2, #0x10
	lsls r1, r1, #0x15
	movs r2, #0
	cmp r2, r5
	bhs _080989F6
	movs r7, #0
	ldr r3, _08098A00 @ =0x040000D4
	lsrs r1, r1, #0x12
	movs r0, #0x85
	lsls r0, r0, #0x18
	orrs r1, r0
	movs r6, #0x80
	lsls r6, r6, #3
_080989DE:
	str r7, [sp]
	mov r0, sp
	str r0, [r3]
	str r4, [r3, #4]
	str r1, [r3, #8]
	ldr r0, [r3, #8]
	adds r4, r4, r6
	adds r0, r2, #1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	cmp r2, r5
	blo _080989DE
_080989F6:
	add sp, #4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08098A00: .4byte 0x040000D4

	thumb_func_start unk_98a04
unk_98a04: @ 0x08098A04
	push {r4, r5, r6, r7, lr}
	movs r3, #0
	ldr r0, _08098A48 @ =gNonGameplayRam
	mov ip, r0
	movs r7, #0x88
	lsls r7, r7, #1
	add r7, ip
	movs r6, #0x96
	lsls r6, r6, #1
	add r6, ip
	movs r5, #0xb2
	lsls r5, r5, #1
	add r5, ip
	movs r4, #0xa4
	lsls r4, r4, #1
	add r4, ip
_08098A24:
	adds r0, r3, r7
	adds r1, r3, r6
	ldrb r2, [r1]
	ldrb r0, [r0]
	cmp r0, r2
	bhi _08098A50
	movs r2, #0
	strb r2, [r1]
	adds r1, r3, r5
	movs r0, #1
	strb r0, [r1]
	adds r1, r3, r4
	ldrb r0, [r1]
	cmp r0, #0x25
	bhi _08098A4C
	adds r0, #1
	b _08098A52
	.align 2, 0
_08098A48: .4byte gNonGameplayRam
_08098A4C:
	strb r2, [r1]
	b _08098A54
_08098A50:
	adds r0, r2, #1
_08098A52:
	strb r0, [r1]
_08098A54:
	adds r0, r3, #1
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	cmp r3, #3
	bls _08098A24
	movs r0, #0x8d
	lsls r0, r0, #1
	add r0, ip
	movs r2, #0x9b
	lsls r2, r2, #1
	add r2, ip
	ldrb r1, [r2]
	ldrb r0, [r0]
	cmp r0, r1
	bhi _08098A96
	movs r3, #0
	strb r3, [r2]
	movs r1, #0xb7
	lsls r1, r1, #1
	add r1, ip
	movs r0, #1
	strb r0, [r1]
	movs r1, #0xa9
	lsls r1, r1, #1
	add r1, ip
	ldrb r0, [r1]
	cmp r0, #0xe
	bhi _08098A92
	adds r0, #1
	strb r0, [r1]
	b _08098A9A
_08098A92:
	strb r3, [r1]
	b _08098A9A
_08098A96:
	adds r0, r1, #1
	strb r0, [r2]
_08098A9A:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

	thumb_func_start NewFileIntroSamusGettingCuredSetupWindow
NewFileIntroSamusGettingCuredSetupWindow: @ 0x08098AA0
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	ldr r1, _08098AE4 @ =0x040000D4
	ldr r0, _08098AE8 @ =0x02001000
	str r0, [r1]
	ldr r0, _08098AEC @ =0x02002000
	str r0, [r1, #4]
	ldr r0, _08098AF0 @ =0x84000058
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r1, _08098AF4 @ =gNonGameplayRam
	ldr r2, _08098AF8 @ =0x000001F5
	adds r0, r1, r2
	ldrb r2, [r0]
	ldr r3, _08098AFC @ =0x000001F3
	adds r0, r1, r3
	ldrb r3, [r0]
	subs r0, r2, r3
	lsls r0, r0, #0x10
	adds r7, r2, r3
	lsrs r2, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0
	bge _08098B00
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	lsls r0, r3, #1
	movs r2, #0
	cmp r5, r0
	ble _08098B02
	movs r2, #0xa1
	b _08098B02
	.align 2, 0
_08098AE4: .4byte 0x040000D4
_08098AE8: .4byte 0x02001000
_08098AEC: .4byte 0x02002000
_08098AF0: .4byte 0x84000058
_08098AF4: .4byte gNonGameplayRam
_08098AF8: .4byte 0x000001F5
_08098AFC: .4byte 0x000001F3
_08098B00:
	movs r5, #0
_08098B02:
	cmp r7, #0x9f
	ble _08098B08
	movs r7, #0xa0
_08098B08:
	ldr r0, _08098BBC @ =0x083E3294 (sHaze_PowerBomb_WindowValuesPointers)
	ldr r6, _08098BC0 @ =0x000001F3
	adds r1, r1, r6
	ldrb r1, [r1]
	lsls r1, r1, #2
	adds r1, r1, r0
	ldr r1, [r1]
	mov ip, r1
	ldr r4, _08098BC4 @ =0x02001000
	movs r6, #0
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	lsls r1, r7, #0x10
	cmp r6, r0
	bge _08098B3E
	movs r2, #0
	adds r3, r0, #0
_08098B2A:
	strh r2, [r4]
	adds r4, #2
	lsls r0, r6, #0x10
	movs r6, #0x80
	lsls r6, r6, #9
	adds r0, r0, r6
	lsrs r6, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, r3
	blt _08098B2A
_08098B3E:
	lsls r0, r6, #0x10
	asrs r3, r1, #0x10
	cmp r0, r1
	bgt _08098B98
	ldr r0, _08098BC8 @ =0x03001678
	mov r8, r0
	adds r7, r3, #0
_08098B4C:
	mov r1, r8
	ldrb r2, [r1]
	lsls r0, r5, #2
	add r0, ip
	ldrh r1, [r0, #2]
	adds r1, r2, r1
	lsls r1, r1, #0x10
	ldrh r0, [r0]
	adds r2, r2, r0
	lsls r2, r2, #0x10
	lsrs r2, r2, #0x10
	lsrs r3, r1, #0x10
	cmp r1, #0
	bge _08098B6A
	movs r3, #0
_08098B6A:
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xf0
	ble _08098B74
	movs r2, #0xf0
_08098B74:
	lsls r1, r3, #0x10
	asrs r1, r1, #8
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	orrs r0, r1
	strh r0, [r4]
	adds r4, #2
	adds r0, r5, #1
	lsls r0, r0, #0x10
	lsrs r5, r0, #0x10
	lsls r0, r6, #0x10
	movs r2, #0x80
	lsls r2, r2, #9
	adds r0, r0, r2
	lsrs r6, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, r7
	ble _08098B4C
_08098B98:
	lsls r1, r6, #0x10
	asrs r0, r1, #0x10
	cmp r0, #0x9f
	bgt _08098BB2
	movs r2, #0
_08098BA2:
	strh r2, [r4]
	adds r4, #2
	movs r3, #0x80
	lsls r3, r3, #9
	adds r1, r1, r3
	asrs r0, r1, #0x10
	cmp r0, #0x9f
	ble _08098BA2
_08098BB2:
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08098BBC: .4byte sHaze_PowerBomb_WindowValuesPointers
_08098BC0: .4byte 0x000001F3
_08098BC4: .4byte 0x02001000
_08098BC8: .4byte 0x03001678

	thumb_func_start SpecialCutsceneFadeIn
SpecialCutsceneFadeIn: @ 0x08098BCC
	push {lr}
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r1, _08098BE8 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0
	beq _08098BE2
	subs r0, #1
	strh r0, [r1]
_08098BE2:
	pop {r0}
	bx r0
	.align 2, 0
_08098BE8: .4byte gWrittenToBldy

	thumb_func_start SpecialCutsceneFadOut
SpecialCutsceneFadOut: @ 0x08098BEC
	push {lr}
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r1, _08098C08 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _08098C02
	adds r0, #1
	strh r0, [r1]
_08098C02:
	pop {r0}
	bx r0
	.align 2, 0
_08098C08: .4byte gWrittenToBldy

	thumb_func_start NewFileIntroProcessTextCursor
NewFileIntroProcessTextCursor: @ 0x08098C0C
	push {lr}
	adds r2, r0, #0
	ldr r0, _08098C28 @ =gNonGameplayRam
	ldr r0, [r0]
	ldrh r1, [r0]
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _08098C2C
	movs r0, #0xeb
	strh r0, [r2, #0xc]
	movs r0, #0x98
	strh r0, [r2, #0xe]
	b _08098C32
	.align 2, 0
_08098C28: .4byte gNonGameplayRam
_08098C2C:
	movs r0, #0x82
	lsls r0, r0, #1
	strh r0, [r2, #0xc]
_08098C32:
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start SpecialCutsceneClearOam
SpecialCutsceneClearOam: @ 0x08098C38
	push {r4, r5, r6, lr}
	movs r3, #0
	ldr r6, _08098C68 @ =gNonGameplayRam
	movs r4, #0x8d
	lsls r4, r4, #2
	movs r5, #2
	rsbs r5, r5, #0
_08098C46:
	lsls r1, r3, #3
	adds r1, r1, r3
	lsls r1, r1, #2
	adds r1, r1, r6
	adds r1, r1, r4
	ldrb r2, [r1]
	adds r0, r5, #0
	ands r0, r2
	strb r0, [r1]
	adds r0, r3, #1
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	cmp r3, #0x13
	bls _08098C46
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08098C68: .4byte gNonGameplayRam

	thumb_func_start SpecialCutsceneEnableOam
SpecialCutsceneEnableOam: @ 0x08098C6C
	push {r4, r5, r6, lr}
	movs r2, #0
	ldr r6, _08098CA4 @ =gNonGameplayRam
	movs r5, #0x8b
	lsls r5, r5, #2
	movs r4, #0x8d
	lsls r4, r4, #2
	movs r3, #1
_08098C7C:
	lsls r0, r2, #3
	adds r0, r0, r2
	lsls r0, r0, #2
	adds r1, r0, r6
	adds r0, r1, r5
	ldrb r0, [r0]
	cmp r0, #0
	beq _08098C94
	adds r1, r1, r4
	ldrb r0, [r1]
	orrs r0, r3
	strb r0, [r1]
_08098C94:
	adds r0, r2, #1
	lsls r0, r0, #0x18
	lsrs r2, r0, #0x18
	cmp r2, #0x13
	bls _08098C7C
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08098CA4: .4byte gNonGameplayRam

	thumb_func_start SpecialCutsceneDestroyOamOfType
SpecialCutsceneDestroyOamOfType: @ 0x08098CA8
	push {r4, r5, r6, r7, lr}
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	movs r3, #0
	ldr r6, _08098CE0 @ =gNonGameplayRam
	movs r7, #2
	rsbs r7, r7, #0
	movs r5, #0x8b
	lsls r5, r5, #2
_08098CBA:
	lsls r0, r3, #3
	adds r0, r0, r3
	lsls r0, r0, #2
	adds r2, r0, r6
	adds r1, r2, r5
	ldrb r0, [r1]
	cmp r0, r4
	bne _08098CE4
	movs r0, #0
	strb r0, [r1]
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r2, r2, r0
	ldrb r1, [r2]
	adds r0, r7, #0
	ands r0, r1
	strb r0, [r2]
	b _08098CEE
	.align 2, 0
_08098CE0: .4byte gNonGameplayRam
_08098CE4:
	adds r0, r3, #1
	lsls r0, r0, #0x18
	lsrs r3, r0, #0x18
	cmp r3, #0x13
	bls _08098CBA
_08098CEE:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

	thumb_func_start SpecialCutsceneProcessOam
SpecialCutsceneProcessOam: @ 0x08098CF4
	push {r4, r5, r6, lr}
	ldr r0, _08098D44 @ =gNonGameplayRam
	ldr r1, _08098D48 @ =0x00000215
	adds r2, r0, r1
	movs r1, #0
	strb r1, [r2]
	movs r4, #0
	adds r5, r0, #0
	adds r6, r2, #0
_08098D06:
	lsls r0, r4, #3
	adds r0, r0, r4
	lsls r2, r0, #2
	adds r0, r2, r5
	movs r3, #0x8b
	lsls r3, r3, #2
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	beq _08098D34
	movs r0, #0x8f
	lsls r0, r0, #2
	adds r1, r5, r0
	adds r1, r2, r1
	subs r3, #0x10
	adds r0, r5, r3
	adds r0, r2, r0
	ldr r1, [r1]
	bl _call_via_r1
	ldrb r0, [r6]
	adds r0, #1
	strb r0, [r6]
_08098D34:
	adds r0, r4, #1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0x13
	bls _08098D06
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08098D44: .4byte gNonGameplayRam
_08098D48: .4byte 0x00000215

	thumb_func_start SpecialCutsceneDrawAllOam
SpecialCutsceneDrawAllOam: @ 0x08098D4C
	push {r4, r5, r6, lr}
	movs r4, #0
	ldr r5, _08098D94 @ =gNonGameplayRam
	movs r0, #0x87
	lsls r0, r0, #2
	adds r6, r5, r0
_08098D58:
	lsls r0, r4, #3
	adds r0, r0, r4
	lsls r1, r0, #2
	adds r0, r1, r5
	movs r2, #0x8d
	lsls r2, r2, #2
	adds r0, r0, r2
	ldrb r0, [r0]
	lsls r0, r0, #0x1f
	cmp r0, #0
	beq _08098D74
	adds r0, r1, r6
	bl SpecialCutsceneDrawOam
_08098D74:
	adds r0, r4, #1
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	cmp r4, #0x13
	bls _08098D58
	bl ResetFreeOam
	ldr r0, _08098D98 @ =gNextOamSlot
	movs r1, #0
	strb r1, [r0]
	ldr r0, _08098D9C @ =0x03001238
	strb r1, [r0]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08098D94: .4byte gNonGameplayRam
_08098D98: .4byte gNextOamSlot
_08098D9C: .4byte 0x03001238

	thumb_func_start SpecialCutsceneDrawOam
SpecialCutsceneDrawOam: @ 0x08098DA0
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x38
	mov sb, r0
	ldr r3, _08098E9C @ =gNextOamSlot
	ldrb r0, [r3]
	lsls r0, r0, #3
	ldr r2, _08098EA0 @ =gOamData
	adds r0, r0, r2
	mov ip, r0
	mov r0, sb
	ldrb r5, [r0, #0x11]
	lsls r1, r5, #3
	ldr r0, [r0, #0x1c]
	adds r4, r0, r1
	ldrb r0, [r4, #4]
	mov r1, sb
	ldrb r1, [r1, #0x12]
	cmp r0, r1
	bne _08098DDA
	adds r0, r5, #1
	movs r1, #0
	mov r2, sb
	strb r0, [r2, #0x11]
	strb r1, [r2, #0x12]
	adds r4, #8
_08098DDA:
	ldrb r1, [r4, #4]
	cmp r1, #0
	bne _08098DEA
	mov r3, sb
	ldrb r0, [r3, #0x11]
	lsls r0, r0, #3
	subs r4, r4, r0
	strb r1, [r3, #0x11]
_08098DEA:
	ldr r4, [r4]
	mov sl, r4
	ldrh r4, [r4]
	str r4, [sp, #0x20]
	movs r5, #2
	add sl, r5
	mov r0, sb
	ldrb r1, [r0, #0x18]
	lsls r0, r1, #0x1d
	lsrs r0, r0, #0x1e
	cmp r0, #0
	beq _08098E04
	b _08098F78
_08098E04:
	movs r1, #0
	str r1, [sp, #0x1c]
	cmp r1, r4
	blt _08098E10
	bl _0809975A
_08098E10:
	ldr r2, _08098EA4 @ =0x000001FF
	adds r7, r2, #0
	movs r3, #3
	mov r8, r3
_08098E18:
	mov r4, sl
	ldrh r6, [r4]
	movs r5, #2
	add sl, r5
	mov r0, sl
	ldrh r5, [r0]
	movs r1, #2
	add sl, r1
	mov r2, ip
	strh r6, [r2]
	add ip, r1
	mov r3, ip
	strh r5, [r3]
	add ip, r1
	mov r4, sl
	ldrh r0, [r4]
	mov r1, ip
	strh r0, [r1]
	movs r2, #2
	add sl, r2
	add ip, r2
	ldr r3, _08098E9C @ =gNextOamSlot
	ldrb r0, [r3]
	ldr r4, [sp, #0x1c]
	adds r3, r0, r4
	mov r1, sb
	ldrb r0, [r1, #0x18]
	lsls r0, r0, #0x19
	lsrs r1, r0, #0x1f
	cmp r1, #1
	bne _08098EAC
	lsls r4, r3, #3
	ldr r3, _08098EA0 @ =gOamData
	adds r2, r4, r3
	ldrb r3, [r2, #3]
	lsls r0, r3, #0x1b
	lsrs r0, r0, #0x1f
	eors r0, r1
	lsls r0, r0, #4
	movs r1, #0x11
	rsbs r1, r1, #0
	ands r1, r3
	orrs r1, r0
	strb r1, [r2, #3]
	lsrs r1, r1, #6
	ldrb r0, [r2, #1]
	lsrs r0, r0, #6
	lsls r0, r0, #2
	adds r1, r1, r0
	ldr r0, _08098EA8 @ =0x0863A184 (sBlob_6131c8_63a19c+0x26FBC)
	adds r1, r1, r0
	ldrb r0, [r1]
	lsls r0, r0, #3
	adds r0, r5, r0
	mov r2, sb
	ldrh r1, [r2, #0xc]
	subs r0, r1, r0
	ands r0, r7
	str r0, [sp]
	ldrh r0, [r2, #0xe]
	adds r6, r6, r0
	movs r0, #0xff
	ands r6, r0
	str r6, [sp, #4]
	b _08098EC2
	.align 2, 0
_08098E9C: .4byte gNextOamSlot
_08098EA0: .4byte gOamData
_08098EA4: .4byte 0x000001FF
_08098EA8: .4byte sNextPageArrowPal+0x26FDC
_08098EAC:
	mov r4, sb
	ldrh r0, [r4, #0xe]
	adds r6, r6, r0
	movs r0, #0xff
	ands r6, r0
	str r6, [sp, #4]
	ldrh r0, [r4, #0xc]
	adds r5, r5, r0
	ands r5, r7
	str r5, [sp]
	lsls r4, r3, #3
_08098EC2:
	ldr r5, _08098F68 @ =gOamData
	adds r3, r4, r5
	mov r0, sp
	ldrb r0, [r0, #4]
	strb r0, [r3]
	ldr r1, [sp]
	ands r1, r7
	str r1, [sp]
	ldrh r1, [r3, #2]
	ldr r0, _08098F6C @ =0xFFFFFE00
	ands r0, r1
	ldr r2, [sp]
	orrs r0, r2
	strh r0, [r3, #2]
	mov r4, sb
	ldrb r0, [r4, #0x1a]
	lsls r0, r0, #0x1c
	lsrs r0, r0, #0x1e
	mov r5, r8
	ands r0, r5
	lsls r0, r0, #2
	ldrb r2, [r3, #5]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r3, #5]
	lsrs r2, r1, #4
	ldrb r0, [r4, #0x1a]
	lsrs r0, r0, #4
	adds r2, r2, r0
	lsls r2, r2, #4
	movs r0, #0xf
	ands r1, r0
	orrs r1, r2
	strb r1, [r3, #5]
	ldrh r2, [r3, #4]
	lsls r1, r2, #0x16
	lsrs r1, r1, #0x16
	ldr r0, [r4, #0x18]
	lsls r0, r0, #0xe
	lsrs r0, r0, #0x16
	adds r1, r1, r0
	ldr r4, _08098F70 @ =0x000003FF
	adds r0, r4, #0
	ands r1, r0
	ldr r0, _08098F74 @ =0xFFFFFC00
	ands r0, r2
	orrs r0, r1
	strh r0, [r3, #4]
	mov r5, sb
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #0x1b
	lsrs r0, r0, #0x1e
	mov r1, r8
	ands r0, r1
	lsls r0, r0, #2
	ldrb r2, [r3, #1]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r3, #1]
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #0x1a
	lsrs r0, r0, #0x1f
	lsls r0, r0, #4
	movs r2, #0x11
	rsbs r2, r2, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r3, #1]
	movs r3, #2
	add ip, r3
	ldr r4, [sp, #0x1c]
	adds r4, #1
	str r4, [sp, #0x1c]
	ldr r5, [sp, #0x20]
	cmp r4, r5
	bge _08098F64
	b _08098E18
_08098F64:
	b _0809975A
	.align 2, 0
_08098F68: .4byte gOamData
_08098F6C: .4byte 0xFFFFFE00
_08098F70: .4byte 0x000003FF
_08098F74: .4byte 0xFFFFFC00
_08098F78:
	cmp r0, #1
	beq _08098F7E
	b _08099400
_08098F7E:
	mov r2, sb
	ldrh r0, [r2, #0xc]
	adds r0, #0x40
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp]
	ldrh r0, [r2, #0xe]
	adds r0, #0x40
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #4]
	lsls r0, r1, #0x19
	cmp r0, #0
	blt _08098FA0
	ldrh r3, [r2, #6]
	str r3, [sp, #0x14]
	b _08098FAC
_08098FA0:
	mov r4, sb
	ldrh r0, [r4, #6]
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x14]
_08098FAC:
	lsls r0, r1, #0x18
	cmp r0, #0
	blt _08098FBA
	mov r5, sb
	ldrh r5, [r5, #6]
	str r5, [sp, #0x18]
	b _08098FC6
_08098FBA:
	mov r1, sb
	ldrh r0, [r1, #6]
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x18]
_08098FC6:
	movs r2, #0
	str r2, [sp, #0x28]
	movs r3, #0
	str r3, [sp, #0x1c]
	ldr r4, [sp, #0x14]
	lsls r4, r4, #0x10
	str r4, [sp, #0x34]
	ldr r5, [sp, #0x20]
	cmp r3, r5
	blt _08098FDC
	b _0809925C
_08098FDC:
	mov r0, sl
	ldrh r6, [r0]
	movs r1, #2
	add sl, r1
	mov r2, sl
	ldrh r5, [r2]
	add sl, r1
	mov r3, ip
	strh r6, [r3]
	add ip, r1
	mov r4, ip
	strh r5, [r4]
	add ip, r1
	mov r1, sl
	ldrh r0, [r1]
	mov r2, ip
	strh r0, [r2]
	movs r3, #2
	add sl, r3
	add ip, r3
	ldr r4, _08099098 @ =gNextOamSlot
	ldrb r0, [r4]
	ldr r1, [sp, #0x1c]
	adds r3, r0, r1
	lsls r0, r3, #3
	ldr r2, _0809909C @ =gOamData
	adds r0, r0, r2
	mov r8, r0
	ldrb r7, [r0, #3]
	lsrs r1, r7, #6
	ldrb r0, [r0, #1]
	lsrs r0, r0, #6
	lsls r0, r0, #2
	adds r1, r1, r0
	ldr r4, _080990A0 @ =0x0863A184 (sBlob_6131c8_63a19c+0x26FBC)
	adds r0, r1, r4
	ldrb r0, [r0]
	lsls r0, r0, #2
	str r0, [sp, #8]
	ldr r0, _080990A4 @ =0x0863A190 (sBlob_6131c8_63a19c+0x26FC8)
	adds r1, r1, r0
	ldrb r0, [r1]
	lsls r0, r0, #2
	str r0, [sp, #0xc]
	ldr r1, [sp, #4]
	adds r6, r6, r1
	movs r0, #0xff
	ands r6, r0
	ldr r2, [sp]
	adds r4, r5, r2
	ldr r5, _080990A8 @ =0x000001FF
	adds r0, r5, #0
	ands r4, r0
	subs r1, r4, r2
	ldr r0, [sp, #8]
	adds r1, r0, r1
	ldr r5, [sp, #4]
	subs r2, r6, r5
	ldr r0, [sp, #0xc]
	adds r2, r0, r2
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	ldr r5, [sp, #0x34]
	asrs r0, r5, #0x10
	muls r0, r1, r0
	asrs r0, r0, #8
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x10]
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	ldr r1, [sp, #0x18]
	lsls r0, r1, #0x10
	asrs r0, r0, #0x10
	muls r0, r2, r0
	asrs r0, r0, #8
	subs r0, r0, r2
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	lsls r0, r7, #0x1b
	cmp r0, #0
	bge _080990AC
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r7
	mov r5, r8
	strb r0, [r5, #3]
	movs r0, #1
	str r0, [sp, #0x28]
	movs r1, #1
	str r1, [sp, #0x24]
	b _080990B0
	.align 2, 0
_08099098: .4byte gNextOamSlot
_0809909C: .4byte gOamData
_080990A0: .4byte sNextPageArrowPal+0x26FDC
_080990A4: .4byte sNextPageArrowPal+0x26FE8
_080990A8: .4byte 0x000001FF
_080990AC:
	movs r5, #0
	str r5, [sp, #0x24]
_080990B0:
	lsls r0, r3, #3
	ldr r1, _080993E4 @ =gOamData
	adds r7, r0, r1
	ldrb r1, [r7, #3]
	lsls r0, r1, #0x1a
	cmp r0, #0
	bge _080990D0
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r7, #3]
	ldr r3, [sp, #0x18]
	lsls r0, r3, #0x10
	rsbs r0, r0, #0
	lsrs r0, r0, #0x10
	str r0, [sp, #0x18]
_080990D0:
	lsls r1, r4, #0x10
	asrs r1, r1, #0x10
	ldr r4, [sp, #0x10]
	lsls r0, r4, #0x10
	asrs r0, r0, #0x10
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r4, r1, #0x10
	lsls r1, r6, #0x10
	asrs r1, r1, #0x10
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r6, r1, #0x10
	ldr r5, [sp]
	subs r4, r4, r5
	ldr r0, [sp, #8]
	mov r8, r0
	add r4, r8
	ldr r1, [sp, #4]
	subs r3, r6, r1
	ldr r6, [sp, #0xc]
	adds r3, r6, r3
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	mov r2, sb
	ldrb r1, [r2, #0x15]
	adds r0, r1, #0
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r5, _080993E8 @ =0x080A4FA4 (sSineTable)
	adds r0, r0, r5
	movs r2, #0
	ldrsh r5, [r0, r2]
	adds r2, r4, #0
	muls r2, r5, r2
	lsls r3, r3, #0x10
	asrs r3, r3, #0x10
	lsls r1, r1, #1
	ldr r0, _080993E8 @ =0x080A4FA4 (sSineTable)
	adds r1, r1, r0
	movs r0, #0
	ldrsh r1, [r1, r0]
	adds r0, r3, #0
	muls r0, r1, r0
	subs r2, r2, r0
	lsls r2, r2, #8
	adds r0, r4, #0
	muls r0, r1, r0
	adds r1, r3, #0
	muls r1, r5, r1
	adds r0, r0, r1
	lsls r0, r0, #8
	asrs r2, r2, #0x10
	mov r1, r8
	subs r2, r2, r1
	asrs r0, r0, #0x10
	subs r0, r0, r6
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
	ldr r3, [sp, #4]
	adds r0, r6, r3
	subs r0, #0x40
	strb r0, [r7]
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	ldr r4, [sp]
	adds r2, r2, r4
	subs r2, #0x40
	ldr r4, _080993EC @ =0x000001FF
	ands r2, r4
	ldrh r0, [r7, #2]
	ldr r1, _080993F0 @ =0xFFFFFE00
	adds r3, r1, #0
	ands r3, r0
	orrs r3, r2
	strh r3, [r7, #2]
	ldr r5, [sp, #0x24]
	cmp r5, #1
	bne _08099180
	lsls r0, r3, #0x17
	lsrs r0, r0, #0x17
	subs r0, #1
	ands r0, r4
	ands r3, r1
	orrs r3, r0
	strh r3, [r7, #2]
_08099180:
	ldrb r1, [r7, #1]
	movs r0, #4
	rsbs r0, r0, #0
	ands r0, r1
	movs r3, #1
	orrs r0, r3
	strb r0, [r7, #1]
	ldr r1, _080993F4 @ =0x03001238
	ldrb r0, [r1]
	ldr r2, [sp, #0x24]
	adds r0, r0, r2
	movs r1, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080991A6
	ldrb r0, [r7, #3]
	movs r1, #0x20
	orrs r0, r1
	strb r0, [r7, #3]
_080991A6:
	ldr r4, _080993F4 @ =0x03001238
	ldrb r0, [r4]
	ldr r5, [sp, #0x24]
	adds r0, r0, r5
	movs r1, #8
	ands r0, r1
	cmp r0, #0
	beq _080991BE
	ldrb r0, [r7, #3]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r7, #3]
_080991BE:
	ldr r0, _080993F4 @ =0x03001238
	ldrb r1, [r0]
	ldr r2, [sp, #0x24]
	adds r1, r1, r2
	movs r0, #7
	ands r1, r0
	lsls r1, r1, #1
	ldrb r2, [r7, #3]
	subs r0, #0x16
	ands r0, r2
	orrs r0, r1
	strb r0, [r7, #3]
	mov r4, sb
	ldrb r0, [r4, #0x1a]
	lsls r0, r0, #0x1c
	lsrs r0, r0, #0x1e
	movs r5, #3
	ands r0, r5
	lsls r0, r0, #2
	ldrb r2, [r7, #5]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r7, #5]
	lsrs r2, r1, #4
	ldrb r0, [r4, #0x1a]
	lsrs r0, r0, #4
	adds r2, r2, r0
	lsls r2, r2, #4
	movs r0, #0xf
	ands r1, r0
	orrs r1, r2
	strb r1, [r7, #5]
	ldrh r2, [r7, #4]
	lsls r1, r2, #0x16
	lsrs r1, r1, #0x16
	ldr r0, [r4, #0x18]
	lsls r0, r0, #0xe
	lsrs r0, r0, #0x16
	adds r1, r1, r0
	ldr r4, _080993F8 @ =0x000003FF
	adds r0, r4, #0
	ands r1, r0
	ldr r0, _080993FC @ =0xFFFFFC00
	ands r0, r2
	orrs r0, r1
	strh r0, [r7, #4]
	mov r5, sb
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #0x1b
	lsrs r0, r0, #0x1e
	movs r1, #3
	ands r0, r1
	lsls r0, r0, #2
	ldrb r2, [r7, #1]
	subs r1, #0x10
	ands r1, r2
	orrs r1, r0
	strb r1, [r7, #1]
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #0x1a
	lsrs r0, r0, #0x1f
	ands r0, r3
	lsls r0, r0, #4
	movs r2, #0x11
	rsbs r2, r2, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r7, #1]
	movs r3, #2
	add ip, r3
	ldr r4, [sp, #0x1c]
	adds r4, #1
	str r4, [sp, #0x1c]
	ldr r5, [sp, #0x20]
	cmp r4, r5
	bge _0809925C
	b _08098FDC
_0809925C:
	ldr r1, _080993F4 @ =0x03001238
	ldrb r0, [r1]
	lsls r0, r0, #0x1a
	lsrs r7, r0, #0x18
	mov r2, sb
	ldrb r0, [r2, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r3, _080993E8 @ =0x080A4FA4 (sSineTable)
	adds r0, r0, r3
	movs r5, #0
	ldrsh r4, [r0, r5]
	ldr r0, [sp, #0x34]
	asrs r0, r0, #0x10
	mov sl, r0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	ldr r1, _080993E4 @ =gOamData
	mov r8, r1
	lsls r1, r7, #3
	add r1, r8
	strh r0, [r1, #6]
	mov r2, sb
	ldrb r0, [r2, #0x15]
	lsls r0, r0, #1
	ldr r3, _080993E8 @ =0x080A4FA4 (sSineTable)
	adds r0, r0, r3
	movs r5, #0
	ldrsh r4, [r0, r5]
	mov r0, sl
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #1
	lsls r1, r1, #3
	add r1, r8
	strh r0, [r1, #6]
	mov r1, sb
	ldrb r0, [r1, #0x15]
	lsls r0, r0, #1
	ldr r2, _080993E8 @ =0x080A4FA4 (sSineTable)
	adds r0, r0, r2
	ldrh r4, [r0]
	rsbs r4, r4, #0
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	ldr r3, [sp, #0x18]
	lsls r0, r3, #0x10
	asrs r6, r0, #0x10
	adds r0, r6, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #2
	lsls r1, r1, #3
	add r1, r8
	strh r0, [r1, #6]
	mov r4, sb
	ldrb r0, [r4, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r5, _080993E8 @ =0x080A4FA4 (sSineTable)
	adds r0, r0, r5
	movs r1, #0
	ldrsh r4, [r0, r1]
	adds r0, r6, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #3
	lsls r1, r1, #3
	add r1, r8
	strh r0, [r1, #6]
	ldr r2, _080993F4 @ =0x03001238
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r3, [sp, #0x28]
	cmp r3, #1
	beq _08099328
	b _0809975A
_08099328:
	ldrb r0, [r2]
	lsls r0, r0, #0x1a
	lsrs r7, r0, #0x18
	mov r4, sb
	ldrb r0, [r4, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	adds r0, r0, r5
	movs r1, #0
	ldrsh r5, [r0, r1]
	mov r2, sl
	rsbs r4, r2, #0
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	adds r0, r4, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r5, #0
	bl FixedMultiplication
	lsls r1, r7, #3
	add r1, r8
	strh r0, [r1, #6]
	mov r3, sb
	ldrb r0, [r3, #0x15]
	lsls r0, r0, #1
	ldr r5, _080993E8 @ =0x080A4FA4 (sSineTable)
	adds r0, r0, r5
	movs r1, #0
	ldrsh r5, [r0, r1]
	adds r0, r4, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r5, #0
	bl FixedMultiplication
	adds r1, r7, #1
	lsls r1, r1, #3
	add r1, r8
	strh r0, [r1, #6]
	mov r2, sb
	ldrb r0, [r2, #0x15]
	lsls r0, r0, #1
	ldr r3, _080993E8 @ =0x080A4FA4 (sSineTable)
	adds r0, r0, r3
	ldrh r4, [r0]
	rsbs r4, r4, #0
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	adds r0, r6, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #2
	lsls r1, r1, #3
	add r1, r8
	strh r0, [r1, #6]
	mov r4, sb
	ldrb r0, [r4, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r5, _080993E8 @ =0x080A4FA4 (sSineTable)
	adds r0, r0, r5
	movs r1, #0
	ldrsh r4, [r0, r1]
	adds r0, r6, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #3
	lsls r1, r1, #3
	add r1, r8
	strh r0, [r1, #6]
	ldr r2, _080993F4 @ =0x03001238
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	b _0809975A
	.align 2, 0
_080993E4: .4byte gOamData
_080993E8: .4byte sSineTable
_080993EC: .4byte 0x000001FF
_080993F0: .4byte 0xFFFFFE00
_080993F4: .4byte 0x03001238
_080993F8: .4byte 0x000003FF
_080993FC: .4byte 0xFFFFFC00
_08099400:
	cmp r0, #3
	beq _08099406
	b _0809975A
_08099406:
	mov r3, sb
	ldrh r0, [r3, #0xc]
	adds r0, #0x40
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp]
	ldrh r0, [r3, #0xe]
	adds r0, #0x40
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #4]
	lsls r0, r1, #0x19
	cmp r0, #0
	blt _08099428
	ldrh r4, [r3, #6]
	str r4, [sp, #0x14]
	b _08099434
_08099428:
	mov r5, sb
	ldrh r0, [r5, #6]
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x14]
_08099434:
	lsls r0, r1, #0x18
	cmp r0, #0
	blt _08099440
	mov r0, sb
	ldrh r0, [r0, #6]
	b _0809944A
_08099440:
	mov r1, sb
	ldrh r0, [r1, #6]
	rsbs r0, r0, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
_0809944A:
	str r0, [sp, #0x18]
	movs r2, #0
	str r2, [sp, #0x1c]
	ldr r3, [sp, #0x20]
	cmp r2, r3
	blt _08099458
	b _08099696
_08099458:
	mov r4, sl
	ldrh r6, [r4]
	movs r5, #2
	add sl, r5
	mov r0, sl
	ldrh r5, [r0]
	movs r1, #2
	add sl, r1
	mov r2, ip
	strh r6, [r2]
	add ip, r1
	mov r3, ip
	strh r5, [r3]
	add ip, r1
	mov r4, sl
	ldrh r0, [r4]
	mov r1, ip
	strh r0, [r1]
	movs r2, #2
	add sl, r2
	add ip, r2
	ldr r3, _0809977C @ =gNextOamSlot
	ldrb r0, [r3]
	ldr r4, [sp, #0x1c]
	adds r3, r0, r4
	lsls r0, r3, #3
	ldr r1, _08099780 @ =gOamData
	adds r7, r0, r1
	ldrb r2, [r7, #3]
	mov r8, r2
	mov r3, r8
	lsrs r1, r3, #6
	ldrb r0, [r7, #1]
	lsrs r0, r0, #6
	lsls r0, r0, #2
	adds r1, r1, r0
	ldr r4, _08099784 @ =0x0863A184 (sBlob_6131c8_63a19c+0x26FBC)
	adds r0, r1, r4
	ldrb r2, [r0]
	ldr r0, _08099788 @ =0x0863A190 (sBlob_6131c8_63a19c+0x26FC8)
	adds r1, r1, r0
	ldrb r3, [r1]
	ldr r1, [sp, #4]
	adds r6, r6, r1
	movs r0, #0xff
	ands r6, r0
	ldr r0, [sp]
	adds r4, r5, r0
	ldr r1, _0809978C @ =0x000001FF
	adds r0, r1, #0
	ands r4, r0
	ldr r5, [sp]
	subs r1, r4, r5
	lsls r2, r2, #2
	str r2, [sp, #0x2c]
	adds r1, r2, r1
	ldr r0, [sp, #4]
	subs r2, r6, r0
	lsls r3, r3, #2
	str r3, [sp, #0x30]
	adds r2, r3, r2
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	ldr r3, [sp, #0x14]
	lsls r0, r3, #0x10
	asrs r3, r0, #0x10
	adds r0, r1, #0
	muls r0, r3, r0
	asrs r0, r0, #8
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x10]
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	ldr r5, [sp, #0x18]
	lsls r0, r5, #0x10
	asrs r5, r0, #0x10
	adds r0, r2, #0
	muls r0, r5, r0
	asrs r0, r0, #8
	subs r0, r0, r2
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	mov r1, r8
	lsls r0, r1, #0x1b
	cmp r0, #0
	bge _08099518
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r7, #3]
	rsbs r0, r3, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x14]
_08099518:
	ldrb r1, [r7, #3]
	lsls r0, r1, #0x1a
	cmp r0, #0
	bge _08099530
	movs r0, #0x21
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r7, #3]
	rsbs r0, r5, #0
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #0x18]
_08099530:
	lsls r1, r4, #0x10
	asrs r1, r1, #0x10
	ldr r3, [sp, #0x10]
	lsls r0, r3, #0x10
	asrs r0, r0, #0x10
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r4, r1, #0x10
	lsls r1, r6, #0x10
	asrs r1, r1, #0x10
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	adds r1, r1, r0
	lsls r1, r1, #0x10
	lsrs r6, r1, #0x10
	ldr r5, [sp]
	subs r4, r4, r5
	ldr r0, [sp, #0x2c]
	adds r4, r0, r4
	ldr r1, [sp, #4]
	subs r3, r6, r1
	ldr r2, [sp, #0x30]
	adds r3, r2, r3
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	mov r5, sb
	ldrb r1, [r5, #0x15]
	adds r0, r1, #0
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r2, _08099790 @ =0x080A4FA4 (sSineTable)
	adds r0, r0, r2
	movs r2, #0
	ldrsh r5, [r0, r2]
	adds r2, r4, #0
	muls r2, r5, r2
	lsls r3, r3, #0x10
	asrs r3, r3, #0x10
	lsls r1, r1, #1
	ldr r0, _08099790 @ =0x080A4FA4 (sSineTable)
	adds r1, r1, r0
	movs r0, #0
	ldrsh r1, [r1, r0]
	adds r0, r3, #0
	muls r0, r1, r0
	subs r2, r2, r0
	lsls r2, r2, #8
	adds r0, r4, #0
	muls r0, r1, r0
	adds r1, r3, #0
	muls r1, r5, r1
	adds r0, r0, r1
	lsls r0, r0, #8
	ldr r3, [sp, #0x2c]
	lsls r1, r3, #1
	asrs r2, r2, #0x10
	subs r2, r2, r1
	ldr r4, [sp, #0x30]
	lsls r1, r4, #1
	asrs r0, r0, #0x10
	subs r0, r0, r1
	lsls r0, r0, #0x10
	lsrs r6, r0, #0x10
	ldr r5, [sp, #4]
	adds r0, r6, r5
	subs r0, #0x40
	strb r0, [r7]
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	ldr r0, [sp]
	adds r2, r2, r0
	subs r2, #0x40
	ldr r0, _0809978C @ =0x000001FF
	ands r2, r0
	ldrh r1, [r7, #2]
	ldr r0, _08099794 @ =0xFFFFFE00
	ands r0, r1
	orrs r0, r2
	strh r0, [r7, #2]
	ldrb r0, [r7, #1]
	movs r3, #3
	orrs r0, r3
	strb r0, [r7, #1]
	ldr r2, _08099798 @ =0x03001238
	ldrb r1, [r2]
	movs r2, #0x10
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _080995EC
	ldrb r0, [r7, #3]
	movs r1, #0x20
	orrs r0, r1
	strb r0, [r7, #3]
_080995EC:
	ldr r4, _08099798 @ =0x03001238
	ldrb r1, [r4]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _080995FE
	ldrb r0, [r7, #3]
	orrs r0, r2
	strb r0, [r7, #3]
_080995FE:
	ldr r5, _08099798 @ =0x03001238
	ldrb r0, [r5]
	movs r1, #7
	ands r1, r0
	lsls r1, r1, #1
	ldrb r2, [r7, #3]
	movs r0, #0xf
	rsbs r0, r0, #0
	ands r0, r2
	orrs r0, r1
	strb r0, [r7, #3]
	mov r1, sb
	ldrb r0, [r1, #0x1a]
	lsls r0, r0, #0x1c
	lsrs r0, r0, #0x1e
	ands r0, r3
	lsls r0, r0, #2
	ldrb r2, [r7, #5]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r7, #5]
	lsrs r2, r1, #4
	mov r4, sb
	ldrb r0, [r4, #0x1a]
	lsrs r0, r0, #4
	adds r2, r2, r0
	lsls r2, r2, #4
	movs r0, #0xf
	ands r1, r0
	orrs r1, r2
	strb r1, [r7, #5]
	ldrh r2, [r7, #4]
	lsls r1, r2, #0x16
	lsrs r1, r1, #0x16
	ldr r0, [r4, #0x18]
	lsls r0, r0, #0xe
	lsrs r0, r0, #0x16
	adds r1, r1, r0
	ldr r5, _0809979C @ =0x000003FF
	adds r0, r5, #0
	ands r1, r0
	ldr r0, _080997A0 @ =0xFFFFFC00
	ands r0, r2
	orrs r0, r1
	strh r0, [r7, #4]
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #0x1b
	lsrs r0, r0, #0x1e
	ands r0, r3
	lsls r0, r0, #2
	ldrb r2, [r7, #1]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r7, #1]
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #0x1a
	lsrs r0, r0, #0x1f
	lsls r0, r0, #4
	movs r2, #0x11
	rsbs r2, r2, #0
	ands r1, r2
	orrs r1, r0
	strb r1, [r7, #1]
	movs r3, #2
	add ip, r3
	ldr r4, [sp, #0x1c]
	adds r4, #1
	str r4, [sp, #0x1c]
	ldr r5, [sp, #0x20]
	cmp r4, r5
	bge _08099696
	b _08099458
_08099696:
	ldr r1, _08099798 @ =0x03001238
	ldrb r0, [r1]
	lsls r0, r0, #0x1a
	lsrs r7, r0, #0x18
	mov r2, sb
	ldrb r0, [r2, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r3, _08099790 @ =0x080A4FA4 (sSineTable)
	adds r0, r0, r3
	movs r4, #0
	ldrsh r5, [r0, r4]
	ldr r0, [sp, #0x14]
	lsls r4, r0, #0x10
	asrs r4, r4, #0x10
	adds r0, r4, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r5, #0
	bl FixedMultiplication
	ldr r6, _08099780 @ =gOamData
	lsls r1, r7, #3
	adds r1, r1, r6
	strh r0, [r1, #6]
	mov r1, sb
	ldrb r0, [r1, #0x15]
	lsls r0, r0, #1
	ldr r2, _08099790 @ =0x080A4FA4 (sSineTable)
	adds r0, r0, r2
	movs r3, #0
	ldrsh r5, [r0, r3]
	adds r0, r4, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r5, #0
	bl FixedMultiplication
	adds r1, r7, #1
	lsls r1, r1, #3
	adds r1, r1, r6
	strh r0, [r1, #6]
	mov r4, sb
	ldrb r0, [r4, #0x15]
	lsls r0, r0, #1
	ldr r5, _08099790 @ =0x080A4FA4 (sSineTable)
	adds r0, r0, r5
	ldrh r4, [r0]
	rsbs r4, r4, #0
	lsls r4, r4, #0x10
	asrs r4, r4, #0x10
	ldr r0, [sp, #0x18]
	lsls r5, r0, #0x10
	asrs r5, r5, #0x10
	adds r0, r5, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #2
	lsls r1, r1, #3
	adds r1, r1, r6
	strh r0, [r1, #6]
	mov r1, sb
	ldrb r0, [r1, #0x15]
	adds r0, #0x40
	lsls r0, r0, #1
	ldr r2, _08099790 @ =0x080A4FA4 (sSineTable)
	adds r0, r0, r2
	movs r3, #0
	ldrsh r4, [r0, r3]
	adds r0, r5, #0
	bl FixedInverse
	adds r1, r0, #0
	lsls r1, r1, #0x10
	asrs r1, r1, #0x10
	adds r0, r4, #0
	bl FixedMultiplication
	adds r1, r7, #3
	lsls r1, r1, #3
	adds r1, r1, r6
	strh r0, [r1, #6]
	ldr r4, _08099798 @ =0x03001238
	ldrb r0, [r4]
	adds r0, #1
	strb r0, [r4]
_0809975A:
	ldr r0, _0809977C @ =gNextOamSlot
	ldrb r1, [r0]
	ldr r5, [sp, #0x20]
	adds r1, r1, r5
	strb r1, [r0]
	mov r1, sb
	ldrb r0, [r1, #0x12]
	adds r0, #1
	strb r0, [r1, #0x12]
	add sp, #0x38
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0809977C: .4byte gNextOamSlot
_08099780: .4byte gOamData
_08099784: .4byte sNextPageArrowPal+0x26FDC
_08099788: .4byte sNextPageArrowPal+0x26FE8
_0809978C: .4byte 0x000001FF
_08099790: .4byte sSineTable
_08099794: .4byte 0xFFFFFE00
_08099798: .4byte 0x03001238
_0809979C: .4byte 0x000003FF
_080997A0: .4byte 0xFFFFFC00

	thumb_func_start NewFileIntroInit
NewFileIntroInit: @ 0x080997A4
	push {r4, lr}
	sub sp, #4
	ldr r3, _08099864 @ =0x04000208
	movs r4, #0
	strh r4, [r3]
	ldr r2, _08099868 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _0809986C @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08099870 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _08099874 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _08099878 @ =unk_99940
	bl CallbackSetVBlank
	ldr r1, _0809987C @ =0x04000050
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _08099880 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08099884 @ =0x04000054
	strh r1, [r0]
	ldr r0, _08099888 @ =gNextOamSlot
	strb r4, [r0]
	bl ResetFreeOam
	movs r2, #0
	str r2, [sp]
	ldr r1, _0809988C @ =0x040000D4
	mov r0, sp
	str r0, [r1]
	ldr r0, _08099890 @ =gNonGameplayRam
	str r0, [r1, #4]
	ldr r0, _08099894 @ =0x85000150
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _08099898 @ =0x00007FFF
	str r0, [sp]
	mov r0, sp
	str r0, [r1]
	movs r3, #0xa0
	lsls r3, r3, #0x13
	str r3, [r1, #4]
	ldr r0, _0809989C @ =0x85000080
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	strh r2, [r3]
	str r2, [sp]
	mov r0, sp
	str r0, [r1]
	movs r0, #0xc0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _080998A0 @ =0x85004000
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _080998A4 @ =0x0400000E
	strh r2, [r0]
	subs r0, #2
	strh r2, [r0]
	subs r0, #2
	strh r2, [r0]
	subs r0, #2
	strh r2, [r0]
	adds r0, #8
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	adds r0, #2
	strh r2, [r0]
	subs r0, #0x1e
	strh r2, [r0]
	ldr r0, _080998A8 @ =NewFileIntroVblank
	bl CallbackSetVBlank
	add sp, #4
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08099864: .4byte 0x04000208
_08099868: .4byte 0x04000004
_0809986C: .4byte 0x0000FFEF
_08099870: .4byte 0x04000200
_08099874: .4byte 0x0000FFFD
_08099878: .4byte unk_99940
_0809987C: .4byte 0x04000050
_08099880: .4byte gWrittenToBldy
_08099884: .4byte 0x04000054
_08099888: .4byte gNextOamSlot
_0809988C: .4byte 0x040000D4
_08099890: .4byte gNonGameplayRam
_08099894: .4byte 0x85000150
_08099898: .4byte 0x00007FFF
_0809989C: .4byte 0x85000080
_080998A0: .4byte 0x85004000
_080998A4: .4byte 0x0400000E
_080998A8: .4byte NewFileIntroVblank

	thumb_func_start SpecialCutsceneGetRandomNumber
SpecialCutsceneGetRandomNumber: @ 0x080998AC
	push {r4, lr}
	ldr r3, _080998E0 @ =0x03005404
	ldrh r1, [r3]
	lsls r0, r1, #2
	adds r1, r1, r0
	ldr r2, _080998E4 @ =gFrameCounter8Bit
	ldr r4, _080998E8 @ =0x00003573
	adds r0, r4, #0
	ldrb r2, [r2]
	adds r0, r0, r2
	adds r1, r1, r0
	strh r1, [r3]
	ldr r2, _080998EC @ =sRandomNumberTable
	ldr r0, _080998F0 @ =gFrameCounter16Bit
	ldrh r1, [r0]
	movs r0, #0x1f
	ands r0, r1
	adds r0, r0, r2
	ldrb r0, [r0]
	ldrb r1, [r3, #1]
	adds r0, r0, r1
	strb r0, [r3, #1]
	ldrb r0, [r3, #1]
	pop {r4}
	pop {r1}
	bx r1
	.align 2, 0
_080998E0: .4byte 0x03005404
_080998E4: .4byte gFrameCounter8Bit
_080998E8: .4byte 0x00003573
_080998EC: .4byte sRandomNumberTable
_080998F0: .4byte gFrameCounter16Bit

	thumb_func_start NewFileIntroVblank
NewFileIntroVblank: @ 0x080998F4
	ldr r1, _08099920 @ =0x040000D4
	ldr r0, _08099924 @ =gOamData
	str r0, [r1]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _08099928 @ =0x84000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r2, _0809992C @ =0x04000052
	ldr r0, _08099930 @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08099934 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08099938 @ =0x04000054
	ldr r0, _0809993C @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	bx lr
	.align 2, 0
_08099920: .4byte 0x040000D4
_08099924: .4byte gOamData
_08099928: .4byte 0x84000100
_0809992C: .4byte 0x04000052
_08099930: .4byte gWrittenToBldalpha_Evb
_08099934: .4byte gWrittenToBldalpha_Eva
_08099938: .4byte 0x04000054
_0809993C: .4byte gWrittenToBldy

	thumb_func_start unk_99940
unk_99940: @ 0x08099940
	push {lr}
	bl UpdateAudio
	pop {r0}
	bx r0
	.align 2, 0

