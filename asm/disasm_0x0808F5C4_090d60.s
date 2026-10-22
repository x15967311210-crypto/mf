    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start unk_9209c
unk_9209c: @ 0x0809209C
	push {r4, r5, lr}
	sub sp, #4
	ldr r3, _080921B4 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _080921B8 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _080921BC @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _080921C0 @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _080921C4 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _080921C8 @ =unk_99940
	bl CallbackSetVBlank
	movs r0, #0
	str r0, [sp]
	ldr r1, _080921CC @ =0x040000D4
	mov r0, sp
	str r0, [r1]
	ldr r0, _080921D0 @ =gNonGameplayRam
	str r0, [r1, #4]
	ldr r0, _080921D4 @ =0x85000150
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r4, #0
	ldr r5, _080921D8 @ =0x0879C41C (sIntroSamusSittingBgGfxPointers)
_080920DC:
	lsls r0, r4, #2
	adds r0, r0, r5
	ldr r0, [r0]
	lsls r1, r4, #0xc
	ldr r2, _080921DC @ =0x06008000
	adds r1, r1, r2
	bl LZ77UncompVram
	adds r0, r4, #1
	lsls r0, r0, #0x10
	lsrs r4, r0, #0x10
	cmp r4, #4
	bls _080920DC
	ldr r0, _080921E0 @ =0x08658BE0 (sBlob_64e470_662804+0xA770)
	ldr r1, _080921E4 @ =0x0600E800
	bl LZ77UncompVram
	ldr r0, _080921E8 @ =0x08598898 (sIntroSamusShipFlyingTextTilemap)
	ldr r1, _080921EC @ =0x0600E000
	bl LZ77UncompVram
	ldr r4, _080921CC @ =0x040000D4
	ldr r0, _080921F0 @ =0x086591E4 (sBlob_64e470_662804+0xAD74)
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	ldr r0, _080921F4 @ =0x84000080
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _080921F8 @ =0x04000010
	movs r3, #0
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	adds r0, #2
	strh r3, [r0]
	ldr r0, _080921FC @ =0x0300122C
	movs r1, #8
	strh r1, [r0]
	ldr r0, _08092200 @ =0x0300122E
	strh r1, [r0]
	ldr r0, _08092204 @ =0x03001230
	strh r1, [r0]
	ldr r0, _08092208 @ =0x03001232
	strh r1, [r0]
	ldr r1, _0809220C @ =0x04000008
	ldr r2, _08092210 @ =0x00001C08
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _08092214 @ =0x00001D08
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x46
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _08092218 @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _0809221C @ =0x04000054
	strh r1, [r0]
	ldr r0, _08092220 @ =gWrittenToBldalpha_Eva
	ldr r2, _08092224 @ =gWrittenToBldalpha_Evb
	strh r3, [r0]
	strh r1, [r2]
	ldr r0, _08092228 @ =0x04000052
	lsls r1, r1, #8
	strh r1, [r0]
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r1, _080921D0 @ =gNonGameplayRam
	ldr r0, _0809222C @ =0x0863A19C (sCutsceneTextNone)
	str r0, [r1]
	movs r0, #0
	str r0, [sp]
	mov r0, sp
	str r0, [r4]
	ldr r0, _08092230 @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _08092234 @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0x98
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08092238 @ =unk_93884
	bl CallbackSetVBlank
	add sp, #4
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_080921B4: .4byte 0x04000208
_080921B8: .4byte 0x04000004
_080921BC: .4byte 0x0000FFEF
_080921C0: .4byte 0x04000200
_080921C4: .4byte 0x0000FFFD
_080921C8: .4byte unk_99940
_080921CC: .4byte 0x040000D4
_080921D0: .4byte gNonGameplayRam
_080921D4: .4byte 0x85000150
_080921D8: .4byte sData_79C2CC+0x150
_080921DC: .4byte 0x06008000
_080921E0: .4byte sIntroSamusHelmetCloseupBgGfx5+0xADBC
_080921E4: .4byte 0x0600E800
_080921E8: .4byte sIntroSamusShipFlyingTextTilemap
_080921EC: .4byte 0x0600E000
_080921F0: .4byte sIntroSamusHelmetCloseupBgGfx5+0xB3C0
_080921F4: .4byte 0x84000080
_080921F8: .4byte 0x04000010
_080921FC: .4byte 0x0300122C
_08092200: .4byte 0x0300122E
_08092204: .4byte 0x03001230
_08092208: .4byte 0x03001232
_0809220C: .4byte 0x04000008
_08092210: .4byte 0x00001C08
_08092214: .4byte 0x00001D08
_08092218: .4byte gWrittenToBldy
_0809221C: .4byte 0x04000054
_08092220: .4byte gWrittenToBldalpha_Eva
_08092224: .4byte gWrittenToBldalpha_Evb
_08092228: .4byte 0x04000052
_0809222C: .4byte sCutsceneTextNone
_08092230: .4byte 0x0600D000
_08092234: .4byte 0x85000400
_08092238: .4byte unk_93884

