    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start NewFileIntroLandingOnBslInit
NewFileIntroLandingOnBslInit: @ 0x08090D60
	push {r4, r5, r6, lr}
	mov r6, r8
	push {r6}
	sub sp, #4
	ldr r3, _08090EC0 @ =0x04000208
	movs r0, #0
	strh r0, [r3]
	ldr r2, _08090EC4 @ =0x04000004
	ldrh r1, [r2]
	ldr r0, _08090EC8 @ =0x0000FFEF
	ands r0, r1
	strh r0, [r2]
	ldr r2, _08090ECC @ =0x04000200
	ldrh r1, [r2]
	ldr r0, _08090ED0 @ =0x0000FFFD
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	strh r0, [r3]
	ldr r0, _08090ED4 @ =unk_99940
	bl CallbackSetVBlank
	movs r5, #0
	str r5, [sp]
	ldr r4, _08090ED8 @ =0x040000D4
	mov r0, sp
	str r0, [r4]
	ldr r1, _08090EDC @ =gNonGameplayRam
	mov r8, r1
	str r1, [r4, #4]
	ldr r0, _08090EE0 @ =0x85000150
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08090EE4 @ =0x085FAB54 (sBlob_5f6990_prefix+0x41C4)
	ldr r1, _08090EE8 @ =0x06010000
	bl LZ77UncompVram
	ldr r0, _08090EEC @ =0x085FFD08 (sBlob_5f6990_after+0x600)
	str r0, [r4]
	ldr r0, _08090EF0 @ =0x05000200
	str r0, [r4, #4]
	ldr r6, _08090EF4 @ =0x84000080
	str r6, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08090EF8 @ =0x085F7190 (sBlob_5f6990_prefix+0x800)
	movs r1, #0xc0
	lsls r1, r1, #0x13
	bl LZ77UncompVram
	ldr r0, _08090EFC @ =0x0860030C (sBlob_5f6990_after+0xC04)
	ldr r1, _08090F00 @ =0x0600F000
	bl LZ77UncompVram
	ldr r0, _08090F04 @ =0x085FFF08 (sBlob_5f6990_after+0x800)
	ldr r1, _08090F08 @ =0x0600F800
	bl LZ77UncompVram
	ldr r0, _08090F0C @ =0x08598898 (sIntroSamusShipFlyingTextTilemap)
	ldr r1, _08090F10 @ =0x0600E000
	bl LZ77UncompVram
	ldr r0, _08090F14 @ =0x085FF708 (sBlob_5f6990_after)
	str r0, [r4]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r4, #4]
	str r6, [r4, #8]
	ldr r0, [r4, #8]
	ldr r0, _08090F18 @ =0x0300122C
	strh r5, [r0]
	ldr r6, _08090F1C @ =0x0300122E
	movs r1, #0x28
	strh r1, [r6]
	ldr r0, _08090F20 @ =0x03001230
	strh r5, [r0]
	ldr r0, _08090F24 @ =0x03001232
	strh r5, [r0]
	ldr r0, _08090F28 @ =0x04000010
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
	adds r0, #2
	strh r5, [r0]
	adds r0, #2
	strh r5, [r0]
	ldr r1, _08090F2C @ =0x04000008
	ldr r2, _08090F30 @ =0x00001C08
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #4
	ldr r2, _08090F34 @ =0x00001E01
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _08090F38 @ =0x00001F03
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x42
	movs r0, #0xff
	strh r0, [r1]
	ldr r0, _08090F3C @ =gWrittenToBldy
	movs r1, #0x10
	strh r1, [r0]
	ldr r0, _08090F40 @ =0x04000054
	strh r1, [r0]
	movs r0, #1
	movs r1, #0x78
	movs r2, #0
	movs r3, #0
	bl NewFileIntroLandingOnBslSetupOam
	ldrh r0, [r6]
	movs r2, #0x64
	subs r2, r2, r0
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	movs r0, #0xb
	movs r1, #0x80
	movs r3, #1
	bl NewFileIntroLandingOnBslSetupOam
	ldrh r0, [r6]
	movs r2, #0x48
	subs r2, r2, r0
	lsls r2, r2, #0x10
	asrs r2, r2, #0x10
	movs r0, #2
	movs r1, #0x80
	movs r3, #0
	bl NewFileIntroLandingOnBslSetupOam
	movs r0, #3
	movs r1, #0
	movs r2, #0
	movs r3, #0
	bl NewFileIntroLandingOnBslSetupOam
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	ldr r0, _08090F44 @ =0x0863A19C (sCutsceneTextNone)
	mov r1, r8
	str r0, [r1]
	str r5, [sp]
	mov r2, sp
	str r2, [r4]
	ldr r0, _08090F48 @ =0x0600D000
	str r0, [r4, #4]
	ldr r0, _08090F4C @ =0x85000400
	str r0, [r4, #8]
	ldr r0, [r4, #8]
	movs r1, #0x80
	lsls r1, r1, #0x13
	movs r2, #0xe0
	lsls r2, r2, #5
	adds r0, r2, #0
	strh r0, [r1]
	ldr r0, _08090F50 @ =NewFileIntroLandingOnBslVblank
	bl CallbackSetVBlank
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08090EC0: .4byte 0x04000208
_08090EC4: .4byte 0x04000004
_08090EC8: .4byte 0x0000FFEF
_08090ECC: .4byte 0x04000200
_08090ED0: .4byte 0x0000FFFD
_08090ED4: .4byte unk_99940
_08090ED8: .4byte 0x040000D4
_08090EDC: .4byte gNonGameplayRam
_08090EE0: .4byte 0x85000150
_08090EE4: .4byte sIntroTilemap_5f65d8+0x457C
_08090EE8: .4byte 0x06010000
_08090EEC: .4byte sIntroTilemap_5f65d8+0x9730
_08090EF0: .4byte 0x05000200
_08090EF4: .4byte 0x84000080
_08090EF8: .4byte sIntroTilemap_5f65d8+0xBB8
_08090EFC: .4byte sIntroTilemap_5f65d8+0x9D34
_08090F00: .4byte 0x0600F000
_08090F04: .4byte sIntroTilemap_5f65d8+0x9930
_08090F08: .4byte 0x0600F800
_08090F0C: .4byte sIntroSamusShipFlyingTextTilemap
_08090F10: .4byte 0x0600E000
_08090F14: .4byte sIntroTilemap_5f65d8+0x9130
_08090F18: .4byte 0x0300122C
_08090F1C: .4byte 0x0300122E
_08090F20: .4byte 0x03001230
_08090F24: .4byte 0x03001232
_08090F28: .4byte 0x04000010
_08090F2C: .4byte 0x04000008
_08090F30: .4byte 0x00001C08
_08090F34: .4byte 0x00001E01
_08090F38: .4byte 0x00001F03
_08090F3C: .4byte gWrittenToBldy
_08090F40: .4byte 0x04000054
_08090F44: .4byte sCutsceneTextNone
_08090F48: .4byte 0x0600D000
_08090F4C: .4byte 0x85000400
_08090F50: .4byte NewFileIntroLandingOnBslVblank

	thumb_func_start NewFileIntroLandingOnBslProcess
NewFileIntroLandingOnBslProcess: @ 0x08090F54
	push {r4, r5, lr}
	movs r5, #0
	ldr r2, _08090F80 @ =gNonGameplayRam
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrh r1, [r0]
	adds r1, #1
	strh r1, [r0]
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrb r0, [r0]
	adds r4, r2, #0
	cmp r0, #5
	bls _08090F76
	b _08091072
_08090F76:
	lsls r0, r0, #2
	ldr r1, _08090F84 @ =_08090F88
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08090F80: .4byte gNonGameplayRam
_08090F84: .4byte _08090F88
_08090F88: @ jump table
	.4byte _08090FA0 @ case 0
	.4byte _08090FD0 @ case 1
	.4byte _08090FF0 @ case 2
	.4byte _08091016 @ case 3
	.4byte _08091022 @ case 4
	.4byte _08091046 @ case 5
_08090FA0:
	ldr r2, _08090FB0 @ =gWrittenToBldy
	ldrh r0, [r2]
	adds r1, r0, #0
	cmp r1, #0
	beq _08090FB4
	subs r0, #1
	strh r0, [r2]
	b _0809103C
	.align 2, 0
_08090FB0: .4byte gWrittenToBldy
_08090FB4:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r0, r4, r2
	strh r1, [r0]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r4, r0
	movs r0, #1
	strb r0, [r1]
	movs r0, #0x1e
	movs r1, #0xd
	bl PlayMusic
	b _0809103C
_08090FD0:
	ldr r0, _08090FEC @ =0x0300122E
	ldrh r1, [r0]
	cmp r1, #0
	bne _0809103C
	movs r2, #0x84
	lsls r2, r2, #2
	adds r0, r4, r2
	strh r1, [r0]
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r4, r0
	movs r0, #2
	b _0809103A
	.align 2, 0
_08090FEC: .4byte 0x0300122E
_08090FF0:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r1, r4, r2
	ldrh r0, [r1]
	cmp r0, #0x46
	bne _0809103C
	movs r0, #0
	strh r0, [r1]
	movs r0, #0xc
	movs r1, #0x80
	movs r2, #0x32
	movs r3, #0
	bl NewFileIntroLandingOnBslSetupOam
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r4, r0
	movs r0, #3
	b _0809103A
_08091016:
	movs r2, #0x84
	lsls r2, r2, #2
	adds r1, r4, r2
	movs r0, #0
	strh r0, [r1]
	b _0809103C
_08091022:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r4, r0
	ldrh r0, [r1]
	cmp r0, #0x5a
	bne _0809103C
	movs r0, #0
	strh r0, [r1]
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r4, r2
	movs r0, #5
_0809103A:
	strb r0, [r1]
_0809103C:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
	b _08091072
_08091046:
	movs r0, #0x84
	lsls r0, r0, #2
	adds r1, r4, r0
	ldrh r0, [r1]
	cmp r0, #2
	bne _0809106A
	movs r0, #0
	strh r0, [r1]
	ldr r1, _08091064 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _08091068
	adds r0, #1
	strh r0, [r1]
	b _0809106A
	.align 2, 0
_08091064: .4byte gWrittenToBldy
_08091068:
	movs r5, #1
_0809106A:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_08091072:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start NewFileIntroLandingOnBsl
NewFileIntroLandingOnBsl: @ 0x0809107C
	push {r4, r5, lr}
	movs r5, #0
	ldr r4, _08091094 @ =gNonGameplayRam
	ldrh r0, [r4, #8]
	cmp r0, #1
	beq _080910A8
	cmp r0, #1
	bgt _08091098
	cmp r0, #0
	beq _080910A2
	b _080910FC
	.align 2, 0
_08091094: .4byte gNonGameplayRam
_08091098:
	cmp r0, #2
	beq _080910C0
	cmp r0, #3
	beq _080910DC
	b _080910FC
_080910A2:
	bl NewFileIntroLandingOnBslInit
	b _080910B4
_080910A8:
	bl SpecialCutsceneFadeIn
	ldr r0, _080910BC @ =gWrittenToBldy
	ldrh r0, [r0]
	cmp r0, #0
	bne _080910FC
_080910B4:
	movs r0, #2
	strh r0, [r4, #8]
	b _080910FC
	.align 2, 0
_080910BC: .4byte gWrittenToBldy
_080910C0:
	bl NewFileIntroLandingOnBslProcess
	cmp r0, #0
	beq _080910FC
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r4, r1
	strb r5, [r0]
	subs r1, #1
	adds r0, r4, r1
	strb r5, [r0]
	movs r0, #3
	strh r0, [r4, #8]
	b _080910FC
_080910DC:
	ldr r1, _080910EC @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xf
	bhi _080910F0
	adds r0, #1
	strh r0, [r1]
	b _080910F4
	.align 2, 0
_080910EC: .4byte gWrittenToBldy
_080910F0:
	strh r5, [r4, #8]
	movs r5, #1
_080910F4:
	bl SpecialCutsceneProcessOam
	bl SpecialCutsceneDrawAllOam
_080910FC:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1

	thumb_func_start NewFileIntroProcessLandingOnBslScroll
NewFileIntroProcessLandingOnBslScroll: @ 0x08091104
	push {r4, r5, lr}
	adds r2, r0, #0
	ldr r0, _08091130 @ =gNonGameplayRam
	ldr r1, _08091134 @ =0x00000217
	adds r4, r0, r1
	movs r3, #0
	strb r3, [r4]
	ldrb r0, [r2, #0x13]
	adds r0, #1
	strb r0, [r2, #0x13]
	ldrb r1, [r2, #0x14]
	cmp r1, #0
	bne _0809113C
	ldr r0, _08091138 @ =0x0300122E
	ldrh r0, [r0]
	movs r1, #0
	strh r0, [r2, #0xe]
	strb r1, [r2, #0x13]
	movs r0, #1
	strb r0, [r2, #0x14]
	b _08091170
	.align 2, 0
_08091130: .4byte gNonGameplayRam
_08091134: .4byte 0x00000217
_08091138: .4byte 0x0300122E
_0809113C:
	cmp r1, #1
	bne _0809116E
	strb r3, [r4]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #4
	bne _08091170
	strb r3, [r2, #0x13]
	ldrh r1, [r2, #0xe]
	movs r5, #0xe
	ldrsh r0, [r2, r5]
	cmp r0, #0
	ble _08091168
	movs r0, #0xff
	strb r0, [r4]
	subs r1, #1
	strh r1, [r2, #0xe]
	ldr r0, _08091164 @ =0x0300122E
	strh r1, [r0]
	b _08091170
	.align 2, 0
_08091164: .4byte 0x0300122E
_08091168:
	strb r3, [r4]
	strb r3, [r2, #0x10]
	b _08091170
_0809116E:
	strb r3, [r2, #0x13]
_08091170:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start NewFileIntroProcessBslDoor
NewFileIntroProcessBslDoor: @ 0x08091178
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrb r5, [r4, #0x14]
	cmp r5, #0
	bne _080911AC
	movs r0, #6
	movs r1, #0
	movs r2, #0
	movs r3, #0
	bl NewFileIntroLandingOnBslSetupOam
	strb r5, [r4, #0x12]
	strb r5, [r4, #0x11]
	ldr r0, _080911A4 @ =0x085FE370 (sIntroLandingFrameData)
	str r0, [r4, #0x1c]
	ldr r0, _080911A8 @ =0x00000246
	bl SoundPlay_3b1c
	movs r0, #1
	strb r0, [r4, #0x14]
	b _080911FE
	.align 2, 0
_080911A4: .4byte sIntroTilemap_5f65d8+0x7D98
_080911A8: .4byte 0x00000246
_080911AC:
	cmp r5, #1
	bne _080911CE
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r4, #0x12]
	cmp r0, r2
	bne _080911FE
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080911FE
	strb r1, [r4, #0x12]
	movs r0, #2
	strb r0, [r4, #0x14]
	b _080911FE
_080911CE:
	cmp r5, #2
	bne _080911FE
	movs r0, #0xc
	ldrsh r1, [r4, r0]
	movs r0, #0xe
	ldrsh r2, [r4, r0]
	movs r0, #4
	movs r3, #1
	bl NewFileIntroLandingOnBslSetupOam
	movs r2, #0xc
	ldrsh r1, [r4, r2]
	movs r0, #0xe
	ldrsh r2, [r4, r0]
	movs r0, #5
	movs r3, #1
	bl NewFileIntroLandingOnBslSetupOam
	movs r0, #0
	strb r0, [r4, #0x10]
	ldrb r1, [r4, #0x18]
	subs r0, #2
	ands r0, r1
	strb r0, [r4, #0x18]
_080911FE:
	ldr r0, _08091214 @ =gNonGameplayRam
	ldr r1, _08091218 @ =0x00000217
	adds r0, r0, r1
	movs r1, #0
	ldrsb r1, [r0, r1]
	ldrh r0, [r4, #0xe]
	subs r0, r0, r1
	strh r0, [r4, #0xe]
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08091214: .4byte gNonGameplayRam
_08091218: .4byte 0x00000217

	thumb_func_start NewFileIntroProcessBslDoorLight
NewFileIntroProcessBslDoorLight: @ 0x0809121C
	push {r4, lr}
	adds r3, r0, #0
	ldrh r0, [r3, #0xa]
	adds r0, #1
	strh r0, [r3, #0xa]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #8
	bne _08091258
	movs r0, #0
	strh r0, [r3, #0xa]
	ldr r2, _0809124C @ =gNonGameplayRam
	movs r0, #0x88
	lsls r0, r0, #1
	adds r1, r2, r0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _08091250 @ =0x00000111
	adds r1, r2, r0
	ldrb r0, [r1]
	cmp r0, #4
	bhi _08091254
	adds r0, #1
	b _08091256
	.align 2, 0
_0809124C: .4byte gNonGameplayRam
_08091250: .4byte 0x00000111
_08091254:
	movs r0, #0
_08091256:
	strb r0, [r1]
_08091258:
	ldrb r0, [r3, #0x13]
	adds r0, #1
	movs r4, #0
	strb r0, [r3, #0x13]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #8
	bne _08091292
	strb r4, [r3, #0x13]
	ldr r2, _08091288 @ =gNonGameplayRam
	movs r0, #0x96
	lsls r0, r0, #1
	adds r1, r2, r0
	movs r0, #1
	strb r0, [r1]
	ldr r0, _0809128C @ =0x0000012D
	adds r1, r2, r0
	ldrb r0, [r1]
	cmp r0, #6
	bhi _08091290
	adds r0, #1
	strb r0, [r1]
	b _08091292
	.align 2, 0
_08091288: .4byte gNonGameplayRam
_0809128C: .4byte 0x0000012D
_08091290:
	strb r4, [r1]
_08091292:
	pop {r4}
	pop {r0}
	bx r0

	thumb_func_start NewFileIntroProcessBslDoorTop
NewFileIntroProcessBslDoorTop: @ 0x08091298
	push {r4, r5, r6, lr}
	sub sp, #4
	adds r5, r0, #0
	ldrh r0, [r5, #0xa]
	adds r0, #1
	movs r6, #0
	strh r0, [r5, #0xa]
	ldrb r1, [r5, #0x14]
	cmp r1, #0
	bne _080912B4
	strh r1, [r5, #0xa]
	movs r0, #1
	strb r0, [r5, #0x14]
	b _08091360
_080912B4:
	cmp r1, #1
	bne _080912DE
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #8
	bne _08091360
	strh r6, [r5, #0xa]
	ldrh r1, [r5, #2]
	movs r2, #2
	ldrsh r0, [r5, r2]
	cmp r0, #0x35
	bgt _080912D8
	adds r0, r1, #1
	strh r0, [r5, #2]
	ldrh r0, [r5, #0xe]
	subs r0, #1
	strh r0, [r5, #0xe]
	b _08091360
_080912D8:
	movs r0, #2
	strb r0, [r5, #0x14]
	b _08091360
_080912DE:
	cmp r1, #2
	bne _08091300
	mov r4, sp
	adds r4, #2
	movs r0, #7
	mov r1, sp
	adds r2, r4, #0
	bl NewFileIntroGetPositionAndSlotOfOamByType_2
	movs r1, #0
	ldrsh r0, [r4, r1]
	cmp r0, #0x5a
	ble _08091360
	strh r6, [r5, #0xa]
	movs r0, #3
	strb r0, [r5, #0x14]
	b _08091360
_08091300:
	cmp r1, #3
	bne _0809134E
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #8
	bne _08091360
	strh r6, [r5, #0xa]
	ldrh r1, [r5, #2]
	movs r2, #2
	ldrsh r0, [r5, r2]
	cmp r0, #0
	ble _08091338
	subs r0, r1, #1
	strh r0, [r5, #2]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0x25
	bne _08091330
	movs r0, #0xa
	movs r1, #0
	movs r2, #0
	movs r3, #1
	bl NewFileIntroLandingOnBslSetupOam
_08091330:
	ldrh r0, [r5, #0xe]
	adds r0, #1
	strh r0, [r5, #0xe]
	b _08091360
_08091338:
	movs r0, #4
	strb r0, [r5, #0x14]
	movs r0, #0xc
	ldrsh r1, [r5, r0]
	movs r0, #0xe
	ldrsh r2, [r5, r0]
	movs r0, #9
	movs r3, #1
	bl NewFileIntroLandingOnBslSetupOam
	b _08091360
_0809134E:
	cmp r1, #4
	bne _08091360
	movs r0, #0
	strb r0, [r5, #0x10]
	ldrb r1, [r5, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r5, #0x18]
_08091360:
	ldr r0, _08091378 @ =gNonGameplayRam
	ldr r1, _0809137C @ =0x00000217
	adds r0, r0, r1
	movs r1, #0
	ldrsb r1, [r0, r1]
	ldrh r0, [r5, #0xe]
	subs r0, r0, r1
	strh r0, [r5, #0xe]
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08091378: .4byte gNonGameplayRam
_0809137C: .4byte 0x00000217

	thumb_func_start NewFileIntroProcessBslDoorBottom
NewFileIntroProcessBslDoorBottom: @ 0x08091380
	push {r4, r5, r6, lr}
	sub sp, #4
	adds r5, r0, #0
	ldrh r0, [r5, #0xa]
	adds r0, #1
	movs r6, #0
	strh r0, [r5, #0xa]
	ldrb r1, [r5, #0x14]
	cmp r1, #0
	bne _0809139C
	strh r1, [r5, #0xa]
	movs r0, #1
	strb r0, [r5, #0x14]
	b _08091424
_0809139C:
	cmp r1, #1
	bne _080913C6
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #8
	bne _08091424
	strh r6, [r5, #0xa]
	ldrh r1, [r5, #2]
	movs r2, #2
	ldrsh r0, [r5, r2]
	cmp r0, #0x35
	bgt _080913C0
	adds r0, r1, #1
	strh r0, [r5, #2]
	ldrh r0, [r5, #0xe]
	adds r0, #1
	strh r0, [r5, #0xe]
	b _08091424
_080913C0:
	movs r0, #2
	strb r0, [r5, #0x14]
	b _08091424
_080913C6:
	cmp r1, #2
	bne _080913E8
	mov r4, sp
	adds r4, #2
	movs r0, #7
	mov r1, sp
	adds r2, r4, #0
	bl NewFileIntroGetPositionAndSlotOfOamByType_2
	movs r1, #0
	ldrsh r0, [r4, r1]
	cmp r0, #0x5a
	ble _08091424
	strh r6, [r5, #0xa]
	movs r0, #3
	strb r0, [r5, #0x14]
	b _08091424
_080913E8:
	cmp r1, #3
	bne _08091412
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #8
	bne _08091424
	strh r6, [r5, #0xa]
	ldrh r1, [r5, #2]
	movs r2, #2
	ldrsh r0, [r5, r2]
	cmp r0, #0
	ble _0809140C
	subs r0, r1, #1
	strh r0, [r5, #2]
	ldrh r0, [r5, #0xe]
	subs r0, #1
	strh r0, [r5, #0xe]
	b _08091424
_0809140C:
	movs r0, #4
	strb r0, [r5, #0x14]
	b _08091424
_08091412:
	cmp r1, #4
	bne _08091424
	movs r0, #0
	strb r0, [r5, #0x10]
	ldrb r1, [r5, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r5, #0x18]
_08091424:
	ldr r0, _0809143C @ =gNonGameplayRam
	ldr r1, _08091440 @ =0x00000217
	adds r0, r0, r1
	movs r1, #0
	ldrsb r1, [r0, r1]
	ldrh r0, [r5, #0xe]
	subs r0, r0, r1
	strh r0, [r5, #0xe]
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0809143C: .4byte gNonGameplayRam
_08091440: .4byte 0x00000217

	thumb_func_start unk_91444
unk_91444: @ 0x08091444
	push {r4, lr}
	adds r3, r0, #0
	ldrb r2, [r3, #0x14]
	cmp r2, #0
	bne _08091464
	ldr r1, _08091494 @ =gNonGameplayRam
	movs r4, #0xa4
	lsls r4, r4, #1
	adds r0, r1, r4
	strb r2, [r0]
	ldr r0, _08091498 @ =0x00000149
	adds r1, r1, r0
	movs r0, #5
	strb r0, [r1]
	movs r0, #1
	strb r0, [r3, #0x14]
_08091464:
	ldrh r0, [r3, #0xa]
	adds r0, #1
	strh r0, [r3, #0xa]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x4b
	bne _080914A0
	movs r0, #0
	strh r0, [r3, #0xa]
	ldr r2, _08091494 @ =gNonGameplayRam
	movs r4, #0xa4
	lsls r4, r4, #1
	adds r1, r2, r4
	movs r0, #1
	strb r0, [r1]
	ldr r0, _08091498 @ =0x00000149
	adds r1, r2, r0
	ldrb r0, [r1]
	cmp r0, #8
	bhi _0809149C
	adds r0, #1
	strb r0, [r1]
	b _080914A0
	.align 2, 0
_08091494: .4byte gNonGameplayRam
_08091498: .4byte 0x00000149
_0809149C:
	movs r0, #0
	strb r0, [r3, #0x10]
_080914A0:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start unk_914a8
unk_914a8: @ 0x080914A8
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #4
	adds r5, r0, #0
	ldrh r0, [r5, #0xa]
	adds r1, r0, #1
	movs r7, #0
	movs r0, #0
	mov r8, r0
	strh r1, [r5, #0xa]
	ldrb r6, [r5, #0x14]
	cmp r6, #0
	bne _080914E8
	mov r2, sp
	adds r2, #2
	movs r0, #4
	mov r1, sp
	bl NewFileIntroGetPositionAndSlotOfOamByType_2
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x14
	bne _080914DA
	b _080917C8
_080914DA:
	strh r6, [r5, #0xa]
	ldrh r0, [r5, #0xc]
	strh r0, [r5]
	ldrh r0, [r5, #0xe]
	strh r0, [r5, #2]
	movs r0, #1
	b _080917C6
_080914E8:
	cmp r6, #1
	bne _08091538
	mov r4, sp
	adds r4, #2
	movs r0, #4
	mov r1, sp
	adds r2, r4, #0
	bl NewFileIntroGetPositionAndSlotOfOamByType_2
	ldrh r0, [r5, #0xa]
	lsrs r0, r0, #2
	ldrh r1, [r5, #2]
	adds r2, r0, r1
	strh r2, [r5, #0xe]
	movs r3, #0xe
	ldrsh r0, [r5, r3]
	movs r3, #0
	ldrsh r1, [r4, r3]
	subs r0, r0, r1
	cmp r0, #8
	bgt _08091514
	b _080917C8
_08091514:
	ldr r1, _08091534 @ =gNonGameplayRam
	movs r3, #0xf8
	lsls r3, r3, #1
	adds r0, r1, r3
	strb r6, [r0]
	adds r3, #1
	adds r0, r1, r3
	strb r6, [r0]
	ldrh r0, [r5, #0xc]
	strh r0, [r5]
	strh r2, [r5, #2]
	mov r0, r8
	strh r0, [r5, #0xa]
	movs r0, #2
	b _080917C6
	.align 2, 0
_08091534: .4byte gNonGameplayRam
_08091538:
	cmp r6, #2
	beq _0809153E
	b _08091678
_0809153E:
	ldrb r0, [r5, #0x13]
	adds r2, r0, #1
	strb r2, [r5, #0x13]
	ldr r6, _08091588 @ =gNonGameplayRam
	ldr r3, _0809158C @ =0x000001F1
	adds r3, r3, r6
	mov ip, r3
	ldrb r4, [r3]
	adds r0, r4, #0
	cmp r0, #6
	bhi _08091590
	lsls r0, r1, #0x10
	lsrs r0, r0, #0x12
	ldrh r1, [r5, #2]
	adds r3, r0, r1
	strh r3, [r5, #0xe]
	lsls r0, r2, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xc
	beq _08091568
	b _08091664
_08091568:
	strb r7, [r5, #0x13]
	movs r2, #0xf8
	lsls r2, r2, #1
	adds r1, r6, r2
	movs r0, #1
	strb r0, [r1]
	adds r0, r4, #1
	mov r1, ip
	strb r0, [r1]
	ldrh r0, [r5, #0xc]
	strh r0, [r5]
	strh r3, [r5, #2]
	mov r2, r8
	strh r2, [r5, #0xa]
	b _08091664
	.align 2, 0
_08091588: .4byte gNonGameplayRam
_0809158C: .4byte 0x000001F1
_08091590:
	cmp r0, #7
	bne _080915C0
	lsls r0, r1, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bne _080915A6
	mov r3, r8
	strh r3, [r5, #0xa]
	ldrh r0, [r5, #0xe]
	adds r0, #1
	strh r0, [r5, #0xe]
_080915A6:
	ldrb r0, [r5, #0x13]
	cmp r0, #0xc
	bne _08091664
	strb r7, [r5, #0x13]
	ldr r0, _080915BC @ =0x085FF628 (sIntroShipLandingFrameData+0x150)
	str r0, [r5, #0x1c]
	movs r0, #0xf8
	lsls r0, r0, #1
	adds r1, r6, r0
	b _08091612
	.align 2, 0
_080915BC: .4byte sIntroTilemap_5f65d8+0x9050
_080915C0:
	cmp r0, #8
	bne _080915EE
	lsls r0, r1, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bne _080915D6
	mov r2, r8
	strh r2, [r5, #0xa]
	ldrh r0, [r5, #0xe]
	adds r0, #1
	strh r0, [r5, #0xe]
_080915D6:
	ldrb r0, [r5, #0x13]
	cmp r0, #0xa
	bne _08091664
	strb r7, [r5, #0x13]
	ldrb r1, [r5, #0x1a]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r5, #0x1a]
	b _0809160C
_080915EE:
	cmp r0, #0xd
	bhi _08091620
	lsls r0, r1, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bne _08091604
	mov r2, r8
	strh r2, [r5, #0xa]
	ldrh r0, [r5, #0xe]
	adds r0, #1
	strh r0, [r5, #0xe]
_08091604:
	ldrb r0, [r5, #0x13]
	cmp r0, #8
	bne _08091664
	strb r7, [r5, #0x13]
_0809160C:
	movs r3, #0xf8
	lsls r3, r3, #1
	adds r1, r6, r3
_08091612:
	movs r0, #1
	strb r0, [r1]
	mov r1, ip
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	b _08091664
_08091620:
	cmp r0, #0xe
	bne _08091664
	lsls r0, r1, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #2
	bne _08091636
	mov r2, r8
	strh r2, [r5, #0xa]
	ldrh r0, [r5, #0xe]
	adds r0, #1
	strh r0, [r5, #0xe]
_08091636:
	ldrb r0, [r5, #0x13]
	cmp r0, #8
	bne _08091664
	strb r7, [r5, #0x13]
	ldr r0, _08091674 @ =0x085FF638 (sIntroShipLandingFrameData+0x160)
	str r0, [r5, #0x1c]
	movs r3, #0xf8
	lsls r3, r3, #1
	adds r1, r6, r3
	movs r0, #1
	strb r0, [r1]
	mov r1, ip
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	ldrh r0, [r5, #0xc]
	strh r0, [r5]
	ldrh r0, [r5, #0xe]
	strh r0, [r5, #2]
	mov r2, r8
	strh r2, [r5, #0xa]
	movs r0, #3
	strb r0, [r5, #0x14]
_08091664:
	movs r3, #0xe
	ldrsh r0, [r5, r3]
	cmp r0, #0x50
	bgt _0809166E
	b _080917C8
_0809166E:
	movs r0, #0x50
	strh r0, [r5, #0xe]
	b _080917C8
	.align 2, 0
_08091674: .4byte sIntroTilemap_5f65d8+0x9060
_08091678:
	cmp r6, #3
	bne _0809169E
	lsls r0, r1, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x14
	beq _08091686
	b _080917C8
_08091686:
	mov r0, r8
	strh r0, [r5, #0xa]
	movs r0, #4
	strb r0, [r5, #0x14]
	movs r2, #0xc
	ldrsh r1, [r5, r2]
	movs r0, #8
	movs r2, #0x96
	movs r3, #0
	bl NewFileIntroLandingOnBslSetupOam
	b _080917C8
_0809169E:
	cmp r6, #4
	bne _080916DC
	ldrh r1, [r5, #8]
	adds r0, r1, #1
	strh r0, [r5, #8]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xff
	ble _080916B6
	adds r0, r1, #0
	subs r0, #0xff
	strh r0, [r5, #8]
_080916B6:
	mov r3, r8
	strh r3, [r5, #0xa]
	ldrh r0, [r5, #0xc]
	strh r0, [r5]
	ldrh r0, [r5, #0xe]
	strh r0, [r5, #2]
	strb r7, [r5, #0x12]
	strb r7, [r5, #0x11]
	ldrb r1, [r5, #0x18]
	movs r0, #7
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r5, #0x18]
	ldr r0, _080916D8 @ =0x085FF540 (sIntroShipLandingFrameData+0x68)
	str r0, [r5, #0x1c]
	movs r0, #5
	b _080917C6
	.align 2, 0
_080916D8: .4byte sIntroTilemap_5f65d8+0x8F68
_080916DC:
	cmp r6, #5
	bne _0809171C
	lsls r0, r1, #0x10
	lsrs r0, r0, #0x14
	ldrh r1, [r5, #2]
	adds r2, r0, r1
	strh r2, [r5, #0xe]
	lsls r0, r2, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0x5a
	ble _080917C8
	ldr r0, [r5, #0x10]
	ldr r1, _08091714 @ =0x00FFFF00
	ands r0, r1
	movs r1, #0x80
	lsls r1, r1, #9
	cmp r0, r1
	bne _080917C8
	ldr r0, _08091718 @ =0x085FF4D8 (sIntroShipLandingFrameData)
	str r0, [r5, #0x1c]
	mov r3, r8
	strh r3, [r5, #0xa]
	ldrh r0, [r5, #0xc]
	strh r0, [r5]
	strh r2, [r5, #2]
	movs r0, #6
	b _080917C6
	.align 2, 0
_08091714: .4byte 0x00FFFF00
_08091718: .4byte sIntroTilemap_5f65d8+0x8F00
_0809171C:
	cmp r6, #6
	bne _0809175C
	lsls r0, r1, #0x10
	lsrs r0, r0, #0x14
	ldrh r1, [r5, #2]
	adds r2, r0, r1
	strh r2, [r5, #0xe]
	ldrb r0, [r5, #0x11]
	lsls r0, r0, #3
	ldr r1, [r5, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r5, #0x12]
	cmp r0, r3
	bne _080917C8
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _080917C8
	mov r0, r8
	strh r0, [r5, #0xa]
	ldrh r0, [r5, #0xc]
	strh r0, [r5]
	strh r2, [r5, #2]
	strb r7, [r5, #0x12]
	strb r7, [r5, #0x11]
	ldr r0, _08091758 @ =0x085FF5A8 (sIntroShipLandingFrameData+0xD0)
	str r0, [r5, #0x1c]
	movs r0, #7
	b _080917C6
	.align 2, 0
_08091758: .4byte sIntroTilemap_5f65d8+0x8FD0
_0809175C:
	cmp r6, #7
	bne _0809178C
	lsls r0, r1, #0x10
	lsrs r0, r0, #0x14
	ldrh r2, [r5, #2]
	adds r1, r0, r2
	strh r1, [r5, #0xe]
	lsls r0, r1, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0x67
	ble _080917C8
	mov r3, r8
	strh r3, [r5, #0xa]
	ldrh r0, [r5, #0xc]
	strh r0, [r5]
	strh r1, [r5, #2]
	strb r7, [r5, #0x12]
	strb r7, [r5, #0x11]
	ldr r0, _08091788 @ =0x085FF580 (sIntroShipLandingFrameData+0xA8)
	str r0, [r5, #0x1c]
	movs r0, #8
	b _080917C6
	.align 2, 0
_08091788: .4byte sIntroTilemap_5f65d8+0x8FA8
_0809178C:
	cmp r6, #8
	bne _080917C8
	ldrb r0, [r5, #0x11]
	lsls r0, r0, #3
	ldr r1, [r5, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r5, #0x12]
	cmp r0, r2
	bne _080917C8
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080917C8
	strh r1, [r5, #0xa]
	ldrh r0, [r5, #0xc]
	strh r0, [r5]
	ldrh r0, [r5, #0xe]
	strh r0, [r5, #2]
	strb r7, [r5, #0x12]
	strb r7, [r5, #0x11]
	ldr r0, _080917D4 @ =0x085FF5A8 (sIntroShipLandingFrameData+0xD0)
	str r0, [r5, #0x1c]
	ldr r0, _080917D8 @ =gNonGameplayRam
	movs r3, #0x85
	lsls r3, r3, #2
	adds r0, r0, r3
	movs r1, #4
	strb r1, [r0]
	movs r0, #9
_080917C6:
	strb r0, [r5, #0x14]
_080917C8:
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080917D4: .4byte sIntroTilemap_5f65d8+0x8FD0
_080917D8: .4byte gNonGameplayRam

	thumb_func_start NewFileIntroProcessShipLandingSmoke
NewFileIntroProcessShipLandingSmoke: @ 0x080917DC
	push {r4, r5, r6, lr}
	sub sp, #4
	adds r5, r0, #0
	ldrb r6, [r5, #0x14]
	cmp r6, #0
	bne _08091834
	mov r4, sp
	adds r4, #2
	movs r0, #0xc
	mov r1, sp
	adds r2, r4, #0
	bl NewFileIntroGetPositionAndSlotOfOamByType_2
	mov r0, sp
	ldrh r0, [r0]
	movs r2, #0
	strh r0, [r5, #0xc]
	movs r0, #0x96
	strh r0, [r5, #0xe]
	movs r1, #0
	ldrsh r0, [r4, r1]
	cmp r0, #0x64
	ble _080918A0
	ldrb r0, [r5, #0x11]
	lsls r0, r0, #3
	ldr r1, [r5, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r5, #0x12]
	cmp r0, r3
	bne _080918A0
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _080918A0
	strh r6, [r5, #0xa]
	strb r2, [r5, #0x12]
	strb r2, [r5, #0x11]
	ldr r0, _08091830 @ =0x085FF5E8 (sIntroShipLandingFrameData+0x110)
	str r0, [r5, #0x1c]
	movs r0, #1
	strb r0, [r5, #0x14]
	b _080918A0
	.align 2, 0
_08091830: .4byte sIntroTilemap_5f65d8+0x9010
_08091834:
	cmp r6, #1
	bne _0809187A
	mov r4, sp
	adds r4, #2
	movs r0, #0xc
	mov r1, sp
	adds r2, r4, #0
	bl NewFileIntroGetPositionAndSlotOfOamByType_2
	mov r0, sp
	ldrh r0, [r0]
	movs r2, #0
	strh r0, [r5, #0xc]
	movs r0, #0x96
	strh r0, [r5, #0xe]
	movs r1, #0
	ldrsh r0, [r4, r1]
	cmp r0, #0x67
	ble _080918A0
	ldrb r0, [r5, #0x11]
	lsls r0, r0, #3
	ldr r1, [r5, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r5, #0x12]
	cmp r0, r3
	bne _080918A0
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _080918A0
	strb r2, [r5, #0x12]
	strb r2, [r5, #0x11]
	movs r0, #2
	strb r0, [r5, #0x14]
	b _080918A0
_0809187A:
	cmp r6, #2
	bne _080918A0
	ldrb r0, [r5, #0x11]
	lsls r0, r0, #3
	ldr r1, [r5, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r2, [r5, #0x12]
	cmp r0, r2
	bne _080918A0
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _080918A0
	strb r1, [r5, #0x10]
	ldrb r1, [r5, #0x18]
	movs r0, #2
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r5, #0x18]
_080918A0:
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0

	thumb_func_start unk_918a8
unk_918a8: @ 0x080918A8
	push {r4, lr}
	adds r2, r0, #0
	ldrb r3, [r2, #0x14]
	cmp r3, #0
	bne _080918DC
	ldrb r0, [r2, #0x11]
	lsls r0, r0, #3
	ldr r1, [r2, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r4, [r2, #0x12]
	cmp r0, r4
	bne _080918E4
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _080918E4
	strb r3, [r2, #0x12]
	strb r3, [r2, #0x11]
	ldr r0, _080918D8 @ =0x085FE430 (sIntroLandingFrameData+0xC0)
	str r0, [r2, #0x1c]
	movs r0, #1
	strb r0, [r2, #0x14]
	b _080918E4
	.align 2, 0
_080918D8: .4byte sIntroTilemap_5f65d8+0x7E58
_080918DC:
	cmp r3, #1
	bne _080918E4
	movs r0, #0
	strb r0, [r2, #0x12]
_080918E4:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start NewFileIntroProcessExtendingShipArms
NewFileIntroProcessExtendingShipArms: @ 0x080918EC
	push {r4, lr}
	adds r3, r0, #0
	ldrb r2, [r3, #0x14]
	cmp r2, #0
	bne _0809190C
	ldr r1, _0809193C @ =gNonGameplayRam
	movs r4, #0xa4
	lsls r4, r4, #1
	adds r0, r1, r4
	strb r2, [r0]
	ldr r0, _08091940 @ =0x00000149
	adds r1, r1, r0
	movs r0, #9
	strb r0, [r1]
	movs r0, #1
	strb r0, [r3, #0x14]
_0809190C:
	ldrh r0, [r3, #0xa]
	adds r0, #1
	strh r0, [r3, #0xa]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0x4b
	bne _08091948
	movs r0, #0
	strh r0, [r3, #0xa]
	ldr r2, _0809193C @ =gNonGameplayRam
	movs r4, #0xa4
	lsls r4, r4, #1
	adds r1, r2, r4
	movs r0, #1
	strb r0, [r1]
	ldr r0, _08091940 @ =0x00000149
	adds r1, r2, r0
	ldrb r0, [r1]
	cmp r0, #6
	bls _08091944
	subs r0, #1
	strb r0, [r1]
	b _08091948
	.align 2, 0
_0809193C: .4byte gNonGameplayRam
_08091940: .4byte 0x00000149
_08091944:
	movs r0, #0
	strb r0, [r3, #0x10]
_08091948:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start NewFileIntroProcessLandingLights
NewFileIntroProcessLandingLights: @ 0x08091950
	ldr r1, _08091964 @ =gNonGameplayRam
	ldr r2, _08091968 @ =0x00000217
	adds r1, r1, r2
	movs r2, #0
	ldrsb r2, [r1, r2]
	ldrh r1, [r0, #0xe]
	subs r1, r1, r2
	strh r1, [r0, #0xe]
	bx lr
	.align 2, 0
_08091964: .4byte gNonGameplayRam
_08091968: .4byte 0x00000217

	thumb_func_start NewFileIntroProcessShipLanding
NewFileIntroProcessShipLanding: @ 0x0809196C
	push {r4, r5, lr}
	adds r4, r0, #0
	ldrh r0, [r4, #0xa]
	adds r0, #1
	movs r2, #0
	movs r3, #0
	strh r0, [r4, #0xa]
	ldrb r1, [r4, #0x14]
	cmp r1, #0
	bne _0809198A
	strh r1, [r4, #0xa]
	ldrh r0, [r4, #0xc]
	strh r0, [r4]
	ldrh r0, [r4, #0xe]
	b _0809199E
_0809198A:
	cmp r1, #1
	bne _080919A6
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x12
	ldrh r1, [r4, #2]
	adds r0, r0, r1
	strh r0, [r4, #0xe]
	strh r3, [r4, #0xa]
	ldrh r1, [r4, #0xc]
	strh r1, [r4]
_0809199E:
	strh r0, [r4, #2]
	movs r0, #2
	strb r0, [r4, #0x14]
	b _08091B50
_080919A6:
	cmp r1, #2
	bne _08091A28
	ldrh r1, [r4, #6]
	movs r2, #6
	ldrsh r0, [r4, r2]
	cmp r0, #0xff
	bgt _080919E4
	adds r0, r1, #1
	strh r0, [r4, #6]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0xff
	ble _080919D2
	movs r0, #0x80
	lsls r0, r0, #1
	strh r0, [r4, #6]
	ldrb r1, [r4, #0x18]
	movs r0, #7
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r4, #0x18]
	b _080919E4
_080919D2:
	cmp r0, #0xbf
	ble _080919E4
	ldrb r0, [r4, #0x1a]
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r1, r0
	movs r0, #4
	orrs r1, r0
	strb r1, [r4, #0x1a]
_080919E4:
	ldrh r0, [r4, #0xa]
	lsrs r0, r0, #2
	ldrh r3, [r4, #2]
	adds r0, r0, r3
	movs r2, #0
	strh r0, [r4, #0xe]
	lsls r0, r0, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0x50
	bgt _080919FA
	b _08091B50
_080919FA:
	movs r1, #0x50
	strh r1, [r4, #0xe]
	ldrh r0, [r4, #0xc]
	strh r0, [r4]
	strh r1, [r4, #2]
	movs r0, #0
	strh r0, [r4, #0xa]
	movs r5, #6
	ldrsh r1, [r4, r5]
	movs r0, #0x80
	lsls r0, r0, #1
	cmp r1, r0
	beq _08091A16
	b _08091B50
_08091A16:
	strb r2, [r4, #0x12]
	strb r2, [r4, #0x11]
	ldr r0, _08091A24 @ =0x085FF530 (sIntroShipLandingFrameData+0x58)
	str r0, [r4, #0x1c]
	movs r0, #3
	strb r0, [r4, #0x14]
	b _08091B50
	.align 2, 0
_08091A24: .4byte sIntroTilemap_5f65d8+0x8F58
_08091A28:
	cmp r1, #3
	bne _08091A58
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #4
	bhi _08091A36
	b _08091B50
_08091A36:
	strh r3, [r4, #0xa]
	strb r2, [r4, #0x12]
	strb r2, [r4, #0x11]
	ldr r0, _08091A54 @ =0x085FF540 (sIntroShipLandingFrameData+0x68)
	str r0, [r4, #0x1c]
	movs r0, #4
	strb r0, [r4, #0x14]
	movs r0, #0xc
	ldrsh r1, [r4, r0]
	movs r0, #8
	movs r2, #0x96
	movs r3, #0
	bl NewFileIntroLandingOnBslSetupOam
	b _08091B50
	.align 2, 0
_08091A54: .4byte sIntroTilemap_5f65d8+0x8F68
_08091A58:
	cmp r1, #4
	bne _08091A78
	strh r3, [r4, #0xa]
	ldrb r0, [r4, #0x11]
	cmp r0, #6
	bne _08091B50
	strb r2, [r4, #0x12]
	strb r2, [r4, #0x11]
	ldr r0, _08091A74 @ =0x085FF530 (sIntroShipLandingFrameData+0x58)
	str r0, [r4, #0x1c]
	movs r0, #5
	strb r0, [r4, #0x14]
	b _08091B50
	.align 2, 0
_08091A74: .4byte sIntroTilemap_5f65d8+0x8F58
_08091A78:
	cmp r1, #5
	bne _08091A98
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0xa
	bls _08091B50
	strh r3, [r4, #0xa]
	ldrh r0, [r4, #0xc]
	strh r0, [r4]
	ldrh r0, [r4, #0xe]
	strh r0, [r4, #2]
	strb r2, [r4, #0x12]
	strb r2, [r4, #0x11]
	movs r0, #6
	strb r0, [r4, #0x14]
	b _08091B50
_08091A98:
	cmp r1, #6
	bne _08091AC8
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x13
	ldrh r5, [r4, #2]
	adds r1, r0, r5
	strh r1, [r4, #0xe]
	lsls r0, r1, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0x58
	ble _08091B50
	strh r3, [r4, #0xa]
	ldrh r0, [r4, #0xc]
	strh r0, [r4]
	strh r1, [r4, #2]
	strb r2, [r4, #0x12]
	strb r2, [r4, #0x11]
	ldr r0, _08091AC4 @ =0x085FF4D8 (sIntroShipLandingFrameData)
	str r0, [r4, #0x1c]
	movs r0, #7
	strb r0, [r4, #0x14]
	b _08091B50
	.align 2, 0
_08091AC4: .4byte sIntroTilemap_5f65d8+0x8F00
_08091AC8:
	cmp r1, #7
	bne _08091B14
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #0x12]
	cmp r0, r3
	bne _08091AE4
	ldrb r0, [r1, #0xc]
	cmp r0, #0
	bne _08091AE4
	strb r2, [r4, #0x12]
_08091AE4:
	ldrh r0, [r4, #0xa]
	lsrs r0, r0, #3
	ldrh r5, [r4, #2]
	adds r1, r0, r5
	movs r2, #0
	strh r1, [r4, #0xe]
	lsls r0, r1, #0x10
	asrs r0, r0, #0x10
	cmp r0, #0x67
	ble _08091B50
	movs r0, #0
	strh r0, [r4, #0xa]
	ldrh r0, [r4, #0xc]
	strh r0, [r4]
	strh r1, [r4, #2]
	strb r2, [r4, #0x12]
	strb r2, [r4, #0x11]
	ldr r0, _08091B10 @ =0x085FF580 (sIntroShipLandingFrameData+0xA8)
	str r0, [r4, #0x1c]
	movs r0, #8
	strb r0, [r4, #0x14]
	b _08091B50
	.align 2, 0
_08091B10: .4byte sIntroTilemap_5f65d8+0x8FA8
_08091B14:
	cmp r1, #8
	bne _08091B50
	ldrb r0, [r4, #0x11]
	lsls r0, r0, #3
	ldr r1, [r4, #0x1c]
	adds r1, r1, r0
	ldrb r0, [r1, #4]
	ldrb r3, [r4, #0x12]
	cmp r0, r3
	bne _08091B50
	ldrb r1, [r1, #0xc]
	cmp r1, #0
	bne _08091B50
	strh r1, [r4, #0xa]
	ldrh r0, [r4, #0xc]
	strh r0, [r4]
	ldrh r0, [r4, #0xe]
	strh r0, [r4, #2]
	strb r2, [r4, #0x12]
	strb r2, [r4, #0x11]
	ldr r0, _08091B68 @ =0x085FF5A8 (sIntroShipLandingFrameData+0xD0)
	str r0, [r4, #0x1c]
	movs r0, #9
	strb r0, [r4, #0x14]
	ldr r0, _08091B6C @ =gNonGameplayRam
	movs r5, #0x85
	lsls r5, r5, #2
	adds r0, r0, r5
	movs r1, #4
	strb r1, [r0]
_08091B50:
	ldr r0, _08091B6C @ =gNonGameplayRam
	ldr r1, _08091B70 @ =0x00000217
	adds r0, r0, r1
	movs r1, #0
	ldrsb r1, [r0, r1]
	ldrh r0, [r4, #0xe]
	subs r0, r0, r1
	strh r0, [r4, #0xe]
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08091B68: .4byte sIntroTilemap_5f65d8+0x8FD0
_08091B6C: .4byte gNonGameplayRam
_08091B70: .4byte 0x00000217

	thumb_func_start NewFileIntroLandingOnBslSetupOam
NewFileIntroLandingOnBslSetupOam: @ 0x08091B74
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
	bne _08091BD8
	movs r2, #0
	ldr r0, _08091BD4 @ =gNonGameplayRam
	movs r3, #0x8b
	lsls r3, r3, #2
	adds r1, r0, r3
	ldrb r1, [r1]
	mov ip, r0
	cmp r1, #0
	beq _08091BC8
	mov r4, ip
_08091BA8:
	lsls r0, r2, #0x18
	movs r1, #0x80
	lsls r1, r1, #0x11
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0x13
	bgt _08091C18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _08091BA8
_08091BC8:
	lsls r0, r2, #0x18
	asrs r1, r0, #0x18
	adds r7, r0, #0
	cmp r1, #0x13
	ble _08091C20
	b _08091C18
	.align 2, 0
_08091BD4: .4byte gNonGameplayRam
_08091BD8:
	movs r2, #0x13
	ldr r0, _08091C1C @ =gNonGameplayRam
	movs r3, #0x9b
	lsls r3, r3, #3
	adds r1, r0, r3
	ldrb r1, [r1]
	mov ip, r0
	cmp r1, #0
	beq _08091C10
	mov r4, ip
	movs r3, #0x8b
	lsls r3, r3, #2
_08091BF0:
	lsls r0, r2, #0x18
	movs r1, #0xff
	lsls r1, r1, #0x18
	adds r0, r0, r1
	lsrs r2, r0, #0x18
	asrs r1, r0, #0x18
	cmp r1, #0
	blt _08091C18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, r0, r3
	ldrb r0, [r0]
	cmp r0, #0
	bne _08091BF0
_08091C10:
	lsls r0, r2, #0x18
	adds r7, r0, #0
	cmp r7, #0
	bge _08091C20
_08091C18:
	movs r0, #0x14
	b _08091EDC
	.align 2, 0
_08091C1C: .4byte gNonGameplayRam
_08091C20:
	movs r0, #0
	str r0, [sp]
	ldr r2, _08091C84 @ =0x040000D4
	mov r3, sp
	str r3, [r2]
	asrs r1, r7, #0x18
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r5, r0, #2
	ldr r3, _08091C88 @ =0x030016A0
	adds r0, r5, r3
	str r0, [r2, #4]
	ldr r0, _08091C8C @ =0x85000009
	str r0, [r2, #8]
	ldr r0, [r2, #8]
	ldr r1, _08091C90 @ =0xFFFFFDE4
	adds r0, r3, r1
	adds r2, r5, r0
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r0, r2, r1
	mov r1, r8
	strh r1, [r0]
	ldr r1, _08091C94 @ =0x0000022A
	adds r0, r2, r1
	mov r1, sb
	strh r1, [r0]
	movs r1, #0x8b
	lsls r1, r1, #2
	adds r0, r2, r1
	strb r6, [r0]
	movs r0, #0x8d
	lsls r0, r0, #2
	adds r4, r2, r0
	ldrb r1, [r4]
	movs r0, #1
	orrs r1, r0
	strb r1, [r4]
	cmp r6, #1
	bne _08091C9C
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r4]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08091C98 @ =NewFileIntroProcessLandingOnBslScroll
	str r1, [r0]
	b _08091EDA
	.align 2, 0
_08091C84: .4byte 0x040000D4
_08091C88: .4byte 0x030016A0
_08091C8C: .4byte 0x85000009
_08091C90: .4byte 0xFFFFFDE4
_08091C94: .4byte 0x0000022A
_08091C98: .4byte NewFileIntroProcessLandingOnBslScroll
_08091C9C:
	cmp r6, #2
	bne _08091CD4
	ldr r1, _08091CC8 @ =0x00000236
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
	adds r0, r5, r0
	ldr r1, _08091CCC @ =0x085FE430 (sIntroLandingFrameData+0xC0)
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08091CD0 @ =NewFileIntroProcessBslDoor
	str r1, [r0]
	b _08091EDA
	.align 2, 0
_08091CC8: .4byte 0x00000236
_08091CCC: .4byte sIntroTilemap_5f65d8+0x7E58
_08091CD0: .4byte NewFileIntroProcessBslDoor
_08091CD4:
	cmp r6, #3
	bne _08091CF0
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r4]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08091CEC @ =NewFileIntroProcessBslDoorLight
	str r1, [r0]
	b _08091EDA
	.align 2, 0
_08091CEC: .4byte NewFileIntroProcessBslDoorLight
_08091CF0:
	cmp r6, #4
	bne _08091D28
	ldr r0, _08091D1C @ =0x00000236
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
	adds r0, r5, r0
	ldr r1, _08091D20 @ =0x085FE410 (sIntroLandingFrameData+0xA0)
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08091D24 @ =NewFileIntroProcessBslDoorTop
	str r1, [r0]
	b _08091EDA
	.align 2, 0
_08091D1C: .4byte 0x00000236
_08091D20: .4byte sIntroTilemap_5f65d8+0x7E38
_08091D24: .4byte NewFileIntroProcessBslDoorTop
_08091D28:
	cmp r6, #5
	bne _08091D60
	ldr r1, _08091D54 @ =0x00000236
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
	adds r0, r5, r0
	ldr r1, _08091D58 @ =0x085FE420 (sIntroLandingFrameData+0xB0)
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08091D5C @ =NewFileIntroProcessBslDoorBottom
	str r1, [r0]
	b _08091EDA
	.align 2, 0
_08091D54: .4byte 0x00000236
_08091D58: .4byte sIntroTilemap_5f65d8+0x7E48
_08091D5C: .4byte NewFileIntroProcessBslDoorBottom
_08091D60:
	cmp r6, #6
	bne _08091D7C
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r4]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08091D78 @ =unk_91444
	str r1, [r0]
	b _08091EDA
	.align 2, 0
_08091D78: .4byte unk_91444
_08091D7C:
	cmp r6, #7
	bne _08091DCC
	ldr r0, _08091DBC @ =0x00000222
	adds r1, r2, r0
	movs r0, #0x80
	lsls r0, r0, #1
	strh r0, [r1]
	ldrb r1, [r4]
	movs r0, #7
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4]
	ldr r1, _08091DC0 @ =0x00000236
	adds r2, r2, r1
	ldrb r0, [r2]
	movs r1, #0xc
	orrs r0, r1
	strb r0, [r2]
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08091DC4 @ =0x085FF618 (sIntroShipLandingFrameData+0x140)
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08091DC8 @ =unk_914a8
	str r1, [r0]
	b _08091EDA
	.align 2, 0
_08091DBC: .4byte 0x00000222
_08091DC0: .4byte 0x00000236
_08091DC4: .4byte sIntroTilemap_5f65d8+0x9040
_08091DC8: .4byte unk_914a8
_08091DCC:
	cmp r6, #8
	bne _08091DF0
	adds r0, r3, #0
	adds r0, #0x1c
	adds r0, r5, r0
	ldr r1, _08091DE8 @ =0x085FF5B8 (sIntroShipLandingFrameData+0xE0)
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08091DEC @ =NewFileIntroProcessShipLandingSmoke
	str r1, [r0]
	b _08091EDA
	.align 2, 0
_08091DE8: .4byte sIntroTilemap_5f65d8+0x8FE0
_08091DEC: .4byte NewFileIntroProcessShipLandingSmoke
_08091DF0:
	cmp r6, #9
	bne _08091E28
	ldr r0, _08091E1C @ =0x00000236
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
	adds r0, r5, r0
	ldr r1, _08091E20 @ =0x085FE3C0 (sIntroLandingFrameData+0x50)
	str r1, [r0]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08091E24 @ =unk_918a8
	str r1, [r0]
	b _08091EDA
	.align 2, 0
_08091E1C: .4byte 0x00000236
_08091E20: .4byte sIntroTilemap_5f65d8+0x7DE8
_08091E24: .4byte unk_918a8
_08091E28:
	cmp r6, #0xa
	bne _08091E44
	movs r0, #2
	rsbs r0, r0, #0
	ands r1, r0
	strb r1, [r4]
	adds r0, r3, #0
	adds r0, #0x20
	adds r0, r5, r0
	ldr r1, _08091E40 @ =NewFileIntroProcessExtendingShipArms
	str r1, [r0]
	b _08091EDA
	.align 2, 0
_08091E40: .4byte NewFileIntroProcessExtendingShipArms
_08091E44:
	cmp r6, #0xb
	bne _08091E8C
	asrs r0, r7, #0x18
	lsls r2, r0, #3
	adds r2, r2, r0
	lsls r2, r2, #2
	mov r1, ip
	adds r3, r2, r1
	ldr r0, _08091E80 @ =0x00000236
	adds r3, r3, r0
	ldrb r1, [r3]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #8
	orrs r0, r1
	strb r0, [r3]
	movs r0, #0x8e
	lsls r0, r0, #2
	add r0, ip
	adds r0, r2, r0
	ldr r1, _08091E84 @ =0x085FF6C0 (sIntroShipLandingFrameData+0x1E8)
	str r1, [r0]
	movs r0, #0x8f
	lsls r0, r0, #2
	add r0, ip
	adds r2, r2, r0
	ldr r0, _08091E88 @ =NewFileIntroProcessLandingLights
	b _08091ED8
	.align 2, 0
_08091E80: .4byte 0x00000236
_08091E84: .4byte sIntroTilemap_5f65d8+0x90E8
_08091E88: .4byte NewFileIntroProcessLandingLights
_08091E8C:
	cmp r6, #0xc
	bne _08091EDA
	asrs r0, r7, #0x18
	lsls r2, r0, #3
	adds r2, r2, r0
	lsls r2, r2, #2
	mov r1, ip
	adds r3, r2, r1
	ldr r0, _08091EEC @ =0x00000222
	adds r1, r3, r0
	movs r0, #2
	strh r0, [r1]
	movs r1, #0x8d
	lsls r1, r1, #2
	adds r4, r3, r1
	ldrb r1, [r4]
	subs r0, #9
	ands r0, r1
	movs r1, #2
	orrs r0, r1
	strb r0, [r4]
	ldr r0, _08091EF0 @ =0x00000236
	adds r3, r3, r0
	ldrb r0, [r3]
	movs r1, #0xc
	orrs r0, r1
	strb r0, [r3]
	movs r0, #0x8e
	lsls r0, r0, #2
	add r0, ip
	adds r0, r2, r0
	ldr r1, _08091EF4 @ =0x085FF638 (sIntroShipLandingFrameData+0x160)
	str r1, [r0]
	movs r0, #0x8f
	lsls r0, r0, #2
	add r0, ip
	adds r2, r2, r0
	ldr r0, _08091EF8 @ =NewFileIntroProcessShipLanding
_08091ED8:
	str r0, [r2]
_08091EDA:
	lsrs r0, r7, #0x18
_08091EDC:
	add sp, #4
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_08091EEC: .4byte 0x00000222
_08091EF0: .4byte 0x00000236
_08091EF4: .4byte sIntroTilemap_5f65d8+0x9060
_08091EF8: .4byte NewFileIntroProcessShipLanding

	thumb_func_start NewFileIntroLandingOnBslVblank
NewFileIntroLandingOnBslVblank: @ 0x08091EFC
	push {r4, lr}
	ldr r3, _08091FDC @ =0x040000D4
	ldr r0, _08091FE0 @ =gOamData
	str r0, [r3]
	movs r0, #0xe0
	lsls r0, r0, #0x13
	str r0, [r3, #4]
	ldr r0, _08091FE4 @ =0x84000100
	str r0, [r3, #8]
	ldr r0, [r3, #8]
	ldr r2, _08091FE8 @ =0x04000052
	ldr r0, _08091FEC @ =gWrittenToBldalpha_Evb
	ldrh r0, [r0]
	lsls r0, r0, #8
	ldr r1, _08091FF0 @ =gWrittenToBldalpha_Eva
	ldrh r1, [r1]
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08091FF4 @ =0x04000054
	ldr r0, _08091FF8 @ =gWrittenToBldy
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #0x3c
	ldr r0, _08091FFC @ =0x0300122C
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08092000 @ =0x0300122E
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08092004 @ =0x03001230
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldr r0, _08092008 @ =0x03001232
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r2, _0809200C @ =gNonGameplayRam
	movs r0, #0x88
	lsls r0, r0, #1
	adds r1, r2, r0
	ldrb r0, [r1]
	cmp r0, #1
	bne _08091F72
	movs r0, #0
	strb r0, [r1]
	ldr r1, _08092010 @ =0x00000111
	adds r0, r2, r1
	ldrb r0, [r0]
	lsls r0, r0, #5
	ldr r1, _08092014 @ =0x085FFB08 (sBlob_5f6990_after+0x400)
	adds r0, r0, r1
	str r0, [r3]
	ldr r0, _08092018 @ =0x05000340
	str r0, [r3, #4]
	ldr r0, _0809201C @ =0x84000008
	str r0, [r3, #8]
	ldr r0, [r3, #8]
_08091F72:
	movs r4, #0x96
	lsls r4, r4, #1
	adds r1, r2, r4
	ldrb r0, [r1]
	cmp r0, #1
	bne _08091F9A
	movs r0, #0
	strb r0, [r1]
	ldr r1, _08092020 @ =0x0000012D
	adds r0, r2, r1
	ldrb r0, [r0]
	lsls r0, r0, #5
	ldr r1, _08092024 @ =0x085FF908 (sBlob_5f6990_after+0x200)
	adds r0, r0, r1
	str r0, [r3]
	ldr r0, _08092028 @ =0x05000300
	str r0, [r3, #4]
	ldr r0, _0809201C @ =0x84000008
	str r0, [r3, #8]
	ldr r0, [r3, #8]
_08091F9A:
	movs r4, #0xa4
	lsls r4, r4, #1
	adds r1, r2, r4
	ldrb r0, [r1]
	cmp r0, #1
	bne _08091FD6
	movs r0, #0
	strb r0, [r1]
	ldr r0, _0809202C @ =0x00000149
	adds r0, r0, r2
	mov ip, r0
	ldrb r0, [r0]
	lsls r0, r0, #5
	ldr r2, _08092014 @ =0x085FFB08 (sBlob_5f6990_after+0x400)
	adds r0, r0, r2
	str r0, [r3]
	ldr r0, _08092030 @ =0x05000320
	str r0, [r3, #4]
	ldr r1, _0809201C @ =0x84000008
	str r1, [r3, #8]
	ldr r0, [r3, #8]
	mov r4, ip
	ldrb r0, [r4]
	lsls r0, r0, #5
	adds r0, r0, r2
	str r0, [r3]
	ldr r0, _08092034 @ =0x05000160
	str r0, [r3, #4]
	str r1, [r3, #8]
	ldr r0, [r3, #8]
_08091FD6:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_08091FDC: .4byte 0x040000D4
_08091FE0: .4byte gOamData
_08091FE4: .4byte 0x84000100
_08091FE8: .4byte 0x04000052
_08091FEC: .4byte gWrittenToBldalpha_Evb
_08091FF0: .4byte gWrittenToBldalpha_Eva
_08091FF4: .4byte 0x04000054
_08091FF8: .4byte gWrittenToBldy
_08091FFC: .4byte 0x0300122C
_08092000: .4byte 0x0300122E
_08092004: .4byte 0x03001230
_08092008: .4byte 0x03001232
_0809200C: .4byte gNonGameplayRam
_08092010: .4byte 0x00000111
_08092014: .4byte sIntroTilemap_5f65d8+0x9530
_08092018: .4byte 0x05000340
_0809201C: .4byte 0x84000008
_08092020: .4byte 0x0000012D
_08092024: .4byte sIntroTilemap_5f65d8+0x9330
_08092028: .4byte 0x05000300
_0809202C: .4byte 0x00000149
_08092030: .4byte 0x05000320
_08092034: .4byte 0x05000160

	thumb_func_start NewFileIntroGetPositionAndSlotOfOamByType_2
NewFileIntroGetPositionAndSlotOfOamByType_2: @ 0x08092038
	push {r4, r5, r6, r7, lr}
	adds r4, r1, #0
	lsls r0, r0, #0x18
	lsrs r5, r0, #0x18
	movs r1, #0
	ldr r7, _08092070 @ =gNonGameplayRam
	movs r6, #0x8b
	lsls r6, r6, #2
_08092048:
	lsls r0, r1, #3
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r3, r0, r7
	adds r0, r3, r6
	ldrb r0, [r0]
	cmp r0, r5
	bne _08092078
	movs r5, #0x8a
	lsls r5, r5, #2
	adds r0, r3, r5
	ldrh r0, [r0]
	strh r0, [r4]
	ldr r4, _08092074 @ =0x0000022A
	adds r0, r3, r4
	ldrh r0, [r0]
	strh r0, [r2]
	adds r0, r1, #0
	b _08092090
	.align 2, 0
_08092070: .4byte gNonGameplayRam
_08092074: .4byte 0x0000022A
_08092078:
	adds r0, r1, #1
	lsls r0, r0, #0x18
	lsrs r1, r0, #0x18
	cmp r1, #0x13
	bls _08092048
	movs r5, #0x96
	lsls r5, r5, #1
	adds r0, r5, #0
	strh r0, [r4]
	movs r0, #0xc8
	strh r0, [r2]
	movs r0, #0x14
_08092090:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start unk_92098
unk_92098: @ 0x08092098
	bx lr
	.align 2, 0

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

