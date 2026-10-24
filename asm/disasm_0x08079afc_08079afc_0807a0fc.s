    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start NavigationConversationProcessText
NavigationConversationProcessText: @ 0x08079AFC
	push {r4, r5, r6, r7, lr}
	mov r7, r8
	push {r7}
	sub sp, #4
	ldr r0, _08079B14 @ =gNonGameplayRam
	ldrb r1, [r0, #0x17]
	adds r5, r0, #0
	cmp r1, #0
	beq _08079B18
	ldrh r1, [r5, #4]
	movs r0, #0x10
	b _08079B1C
	.align 2, 0
_08079B14: .4byte gNonGameplayRam
_08079B18:
	ldrh r1, [r5, #4]
	movs r0, #8
_08079B1C:
	ands r0, r1
	cmp r0, #0
	bne _08079B24
	b _0807A0EC
_08079B24:
	ldrb r0, [r5, #0x18]
	ldr r1, _08079B70 @ =0x06007000
	mov r8, r1
	cmp r0, #0
	beq _08079B32
	ldr r2, _08079B74 @ =0x06006000
	mov r8, r2
_08079B32:
	movs r7, #0
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #1
	adds r4, r5, #0
	adds r4, #0xe
	adds r2, r0, r4
	ldrh r1, [r2]
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r1, r0
	bne _08079B80
	ldr r0, _08079B78 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x83
	ands r0, r1
	cmp r0, #0
	bne _08079B56
	b _0807A0EC
_08079B56:
	ldr r0, _08079B7C @ =0x00000203
	bl SoundPlay
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #1
	adds r0, r0, r4
	movs r6, #0
	strh r7, [r0]
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #1
	adds r4, #4
	b _08079B94
	.align 2, 0
_08079B70: .4byte 0x06007000
_08079B74: .4byte 0x06006000
_08079B78: .4byte gChangedInput
_08079B7C: .4byte 0x00000203
_08079B80:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r1, r0
	bne _08079BDA
	movs r6, #0
	strh r7, [r2]
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #1
	adds r4, r5, #0
	adds r4, #0x12
_08079B94:
	adds r0, r0, r4
	ldrh r0, [r0]
	cmp r0, #0xe0
	bls _08079BA2
	movs r0, #2
	bl TextClearGraphics
_08079BA2:
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #1
	adds r0, r0, r4
	movs r1, #0xe0
	strh r1, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x36
	movs r1, #0xb
	strb r1, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x34
	strb r6, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x35
	strb r6, [r0]
	b _0807A0EC
_08079BDA:
	movs r0, #0xfd
	lsls r0, r0, #8
	cmp r1, r0
	bne _08079C48
	ldr r0, _08079C40 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x83
	ands r0, r1
	cmp r0, #0
	bne _08079BF0
	b _0807A0EC
_08079BF0:
	ldr r0, _08079C44 @ =0x00000203
	bl SoundPlay
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #1
	adds r0, r0, r4
	movs r4, #0
	strh r7, [r0]
	movs r0, #1
	bl TextClearGraphics
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #1
	adds r1, r5, #0
	adds r1, #0x12
	adds r0, r0, r1
	strh r7, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x36
	movs r1, #0xb
	strb r1, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x34
	strb r4, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x35
	strb r4, [r0]
	b _0807A0EC
	.align 2, 0
_08079C40: .4byte gChangedInput
_08079C44: .4byte 0x00000203
_08079C48:
	ldr r0, _08079C60 @ =0x0000E001
	cmp r1, r0
	bne _08079C64
	ldrh r1, [r5, #4]
	movs r0, #0x80
	lsls r0, r0, #3
	ands r0, r1
	cmp r0, #0
	beq _08079C5C
	b _0807A0EC
_08079C5C:
	strh r7, [r2]
	b _0807A0EC
	.align 2, 0
_08079C60: .4byte 0x0000E001
_08079C64:
	ldrb r0, [r5, #0x1f]
	cmp r0, #0
	beq _08079C70
	subs r0, #1
	strb r0, [r5, #0x1f]
	b _0807A0EC
_08079C70:
	ldrb r0, [r5, #0x1a]
	ldr r2, _08079CA8 @ =gButtonInput
	cmp r0, #0
	beq _08079C84
	ldrh r1, [r2]
	movs r0, #0x83
	ands r0, r1
	cmp r0, #0
	bne _08079C84
	strb r7, [r5, #0x1a]
_08079C84:
	ldrb r1, [r5, #0x18]
	lsls r1, r1, #1
	adds r0, r5, #0
	adds r0, #0xe
	adds r1, r1, r0
	ldrh r0, [r1]
	adds r0, #1
	strh r0, [r1]
	ldrh r1, [r2]
	movs r0, #0x83
	ands r0, r1
	cmp r0, #0
	beq _08079CAC
	ldrb r0, [r5, #0x1a]
	cmp r0, #0
	bne _08079CAC
	movs r7, #1
	b _08079CC0
	.align 2, 0
_08079CA8: .4byte gButtonInput
_08079CAC:
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #1
	adds r1, r5, #0
	adds r1, #0xe
	adds r0, r0, r1
	ldrh r0, [r0]
	ldrb r1, [r5, #0x1d]
	cmp r0, r1
	bhs _08079CC0
	b _0807A0EC
_08079CC0:
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #1
	adds r1, r5, #0
	adds r1, #0xe
	adds r0, r0, r1
	movs r1, #0
	strh r1, [r0]
	movs r2, #0x88
	lsls r2, r2, #2
	adds r0, r5, r2
	ldrb r1, [r0]
	subs r0, r1, #1
	lsls r3, r0, #1
	ldr r0, _08079D24 @ =gPreviousNavigationConversation
	ldrb r0, [r0]
	cmp r1, r0
	bne _08079CE4
	adds r3, #1
_08079CE4:
	ldr r1, _08079D28 @ =0x0879C0F0 (sBlob_79bec0_79c128+0x230)
	ldr r0, _08079D2C @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	lsls r0, r3, #2
	adds r0, r0, r1
	ldr r6, [r0]
	ldrh r0, [r5, #0xc]
	lsls r1, r0, #1
	adds r6, r6, r1
	adds r0, #1
	strh r0, [r5, #0xc]
_08079D04:
	movs r3, #0
	ldrh r0, [r6]
	lsrs r1, r0, #0xc
	movs r4, #0xff
	lsls r4, r4, #8
	ands r4, r0
	subs r1, #8
	adds r2, r0, #0
	cmp r1, #7
	bls _08079D1A
	b _08079F9C
_08079D1A:
	lsls r0, r1, #2
	ldr r1, _08079D30 @ =_08079D34
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08079D24: .4byte gPreviousNavigationConversation
_08079D28: .4byte sExploredMinimapBitFlags+0x314
_08079D2C: .4byte 0x03000011
_08079D30: .4byte _08079D34
_08079D34: @ jump table
	.4byte _08079F2C @ case 0
	.4byte _08079F0C @ case 1
	.4byte _08079EEC @ case 2
	.4byte _08079E96 @ case 3
	.4byte _08079E90 @ case 4
	.4byte _08079F9C @ case 5
	.4byte _08079DCE @ case 6
	.4byte _08079D54 @ case 7
_08079D54:
	movs r0, #0xff
	lsls r0, r0, #8
	cmp r2, r0
	bne _08079D60
	movs r0, #1
	b _08079DB8
_08079D60:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r2, r0
	bne _08079D78
_08079D68:
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #1
	adds r1, r5, #0
	adds r1, #0xe
	adds r0, r0, r1
	strh r2, [r0]
_08079D74:
	movs r3, #1
	b _08079F9C
_08079D78:
	movs r0, #0xfd
	lsls r0, r0, #8
	cmp r2, r0
	beq _08079D88
	movs r0, #0xfc
	lsls r0, r0, #8
	cmp r2, r0
	bne _08079DAC
_08079D88:
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #1
	adds r1, r5, #0
	adds r1, #0xe
	adds r0, r0, r1
	strh r2, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x36
	movs r1, #3
	strb r1, [r0]
	movs r0, #1
	strb r0, [r5, #0x1a]
	movs r3, #2
	b _08079F9C
_08079DAC:
	movs r0, #0xfb
	lsls r0, r0, #8
	cmp r2, r0
	beq _08079DB6
	b _08079F9C
_08079DB6:
	movs r0, #2
_08079DB8:
	strb r0, [r5, #0x1c]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x36
	movs r1, #3
	strb r1, [r0]
	movs r3, #2
	b _08079F9C
_08079DCE:
	movs r0, #0xe0
	lsls r0, r0, #8
	cmp r4, r0
	bne _08079E00
	lsls r0, r2, #0x10
	lsrs r2, r0, #0x10
	cmp r2, r4
	bne _08079DF4
	ldrh r1, [r5, #4]
	movs r0, #0x80
	lsls r0, r0, #2
	ands r0, r1
	cmp r0, #0
	beq _08079D74
	movs r2, #0x80
	lsls r2, r2, #3
	adds r0, r2, #0
	orrs r0, r1
	b _08079E82
_08079DF4:
	ldr r0, _08079DFC @ =0x0000E001
	cmp r2, r0
	bne _08079D74
	b _08079D68
	.align 2, 0
_08079DFC: .4byte 0x0000E001
_08079E00:
	movs r0, #0xe1
	lsls r0, r0, #8
	cmp r4, r0
	bne _08079E0C
	strb r2, [r5, #0x1f]
	b _08079D74
_08079E0C:
	movs r0, #0xe2
	lsls r0, r0, #8
	cmp r4, r0
	bne _08079E5C
	ldrh r1, [r6]
	adds r0, #1
	cmp r1, r0
	bne _08079E2C
	ldrh r0, [r5, #4]
	movs r1, #2
	orrs r0, r1
	strh r0, [r5, #4]
	movs r0, #1
	strb r0, [r5, #0x18]
	strb r1, [r5, #0x19]
	b _08079E56
_08079E2C:
	ldr r0, _08079E44 @ =0x0000E202
	cmp r1, r0
	bne _08079E48
	ldrh r1, [r5, #4]
	movs r0, #4
	orrs r0, r1
	strh r0, [r5, #4]
	movs r0, #1
	strb r0, [r5, #0x18]
	movs r0, #2
	strb r0, [r5, #0x19]
	b _08079E56
	.align 2, 0
_08079E44: .4byte 0x0000E202
_08079E48:
	ldrh r0, [r5, #4]
	movs r2, #1
	movs r1, #0
	orrs r0, r2
	strh r0, [r5, #4]
	strb r1, [r5, #0x18]
	strb r2, [r5, #0x19]
_08079E56:
	ldrh r0, [r6]
	strb r0, [r5, #0x17]
	b _08079D74
_08079E5C:
	movs r0, #0xe3
	lsls r0, r0, #8
	cmp r4, r0
	bne _08079D74
	lsls r0, r2, #0x10
	lsrs r1, r0, #0x10
	cmp r1, r4
	bne _08079E74
	ldrh r1, [r5, #4]
	movs r0, #0x40
	orrs r0, r1
	b _08079E82
_08079E74:
	ldr r0, _08079E88 @ =0x0000E301
	cmp r1, r0
	beq _08079E7C
	b _08079D74
_08079E7C:
	ldrh r1, [r5, #4]
	ldr r0, _08079E8C @ =0x0000FFBF
	ands r0, r1
_08079E82:
	strh r0, [r5, #4]
	b _08079D74
	.align 2, 0
_08079E88: .4byte 0x0000E301
_08079E8C: .4byte 0x0000FFBF
_08079E90:
	movs r0, #6
	strb r0, [r5, #0x1c]
	b _08079D74
_08079E96:
	lsls r0, r2, #0x10
	lsrs r1, r0, #0x10
	ldr r0, _08079EA8 @ =0x0000B001
	cmp r1, r0
	bne _08079EAC
	movs r0, #0x99
	lsls r0, r0, #2
	adds r1, r5, r0
	b _08079EB8
	.align 2, 0
_08079EA8: .4byte 0x0000B001
_08079EAC:
	ldr r0, _08079EC0 @ =0x0000B002
	cmp r1, r0
	bne _08079EC4
	movs r2, #0x99
	lsls r2, r2, #2
	adds r1, r5, r2
_08079EB8:
	movs r0, #1
	strb r0, [r1]
	b _08079D74
	.align 2, 0
_08079EC0: .4byte 0x0000B002
_08079EC4:
	ldr r0, _08079EE8 @ =0x0000B003
	cmp r1, r0
	bne _08079F9C
	ldrb r0, [r5, #0x1c]
	cmp r0, #5
	beq _08079F9A
	cmp r0, #3
	beq _08079F9A
	movs r0, #0x2a
	movs r1, #2
	bl PlayMusic
	movs r0, #0
	movs r1, #0xb
	bl SoundEventUpdate
	b _08079F9A
	.align 2, 0
_08079EE8: .4byte 0x0000B003
_08079EEC:
	ldr r1, _08079F04 @ =0x00000221
	adds r0, r5, r1
	ldrb r0, [r0]
	rsbs r1, r0, #0
	orrs r1, r0
	ldr r0, _08079F08 @ =0x00000FFF
	ands r0, r2
	lsrs r1, r1, #0x1f
	bl unk_3c14
	b _08079F9A
	.align 2, 0
_08079F04: .4byte 0x00000221
_08079F08: .4byte 0x00000FFF
_08079F0C:
	ldr r1, _08079F24 @ =0x00000221
	adds r0, r5, r1
	ldrb r0, [r0]
	rsbs r1, r0, #0
	orrs r1, r0
	ldr r0, _08079F28 @ =0x00000FFF
	ands r0, r2
	lsrs r1, r1, #0x1f
	bl unk_3bd4
	b _08079F9A
	.align 2, 0
_08079F24: .4byte 0x00000221
_08079F28: .4byte 0x00000FFF
_08079F2C:
	movs r0, #0x80
	lsls r0, r0, #8
	cmp r4, r0
	bne _08079F46
	ldrb r1, [r5, #0x18]
	lsls r1, r1, #1
	adds r0, r5, #0
	adds r0, #0x12
	adds r1, r1, r0
	movs r0, #0xff
	ands r0, r2
	ldrh r2, [r1]
	b _08079F96
_08079F46:
	movs r0, #0x81
	lsls r0, r0, #8
	cmp r4, r0
	bne _08079F52
	strb r2, [r5, #0x1e]
	b _08079F9A
_08079F52:
	movs r0, #0x82
	lsls r0, r0, #8
	cmp r4, r0
	bne _08079F68
	strb r2, [r5, #0x1d]
	lsls r0, r2, #0x18
	cmp r0, #0
	bne _08079F9A
	movs r0, #8
	strb r0, [r5, #0x1d]
	b _08079F9A
_08079F68:
	movs r0, #0x83
	lsls r0, r0, #8
	cmp r4, r0
	bne _08079F9A
	ldrb r0, [r5, #0x18]
	lsls r0, r0, #1
	adds r1, r5, #0
	adds r1, #0x12
	adds r1, r0, r1
	ldrh r0, [r1]
	cmp r0, #0xdf
	bls _08079F84
	movs r0, #0xe0
	b _08079F86
_08079F84:
	movs r0, #0
_08079F86:
	strh r0, [r1]
	ldrb r1, [r5, #0x18]
	lsls r1, r1, #1
	adds r0, r5, #0
	adds r0, #0x12
	adds r1, r1, r0
	ldrh r0, [r1]
	ldrb r2, [r6]
_08079F96:
	adds r0, r0, r2
	strh r0, [r1]
_08079F9A:
	movs r3, #3
_08079F9C:
	cmp r3, #3
	bne _08079FB4
	ldr r1, _08079FB0 @ =gNonGameplayRam
	ldrh r0, [r1, #0xc]
	adds r0, #1
	strh r0, [r1, #0xc]
	adds r6, #2
	adds r5, r1, #0
	b _08079D04
	.align 2, 0
_08079FB0: .4byte gNonGameplayRam
_08079FB4:
	cmp r3, #2
	bne _08079FE0
	ldr r2, _08079FDC @ =gNonGameplayRam
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	adds r0, #0x34
	movs r3, #0
	strb r3, [r0]
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	adds r0, #0x35
	strb r3, [r0]
	b _0807A0EC
	.align 2, 0
_08079FDC: .4byte gNonGameplayRam
_08079FE0:
	cmp r3, #1
	bne _08079FE6
	b _0807A0EC
_08079FE6:
	ldrh r0, [r6]
	bl TextGetCharacterWidth
	ldr r4, _0807A01C @ =gNonGameplayRam
	strb r0, [r4, #0x16]
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #1
	adds r5, r4, #0
	adds r5, #0x12
	adds r2, r0, r5
	ldrh r1, [r2]
	ldrb r0, [r4, #0x16]
	adds r3, r1, r0
	movs r0, #0xe0
	lsls r0, r0, #1
	cmp r3, r0
	ble _0807A020
	movs r0, #2
	bl TextClearGraphics
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #1
	adds r0, r0, r5
	movs r1, #0xe0
	strh r1, [r0]
	b _0807A02C
	.align 2, 0
_0807A01C: .4byte gNonGameplayRam
_0807A020:
	cmp r3, #0xe0
	ble _0807A02C
	cmp r1, #0xdf
	bhi _0807A02C
	movs r0, #0xe0
	strh r0, [r2]
_0807A02C:
	ldr r0, _0807A098 @ =gNonGameplayRam
	ldrb r1, [r0, #0x18]
	lsls r1, r1, #1
	adds r2, r0, #0
	adds r2, #0x12
	adds r1, r1, r2
	ldrh r2, [r1]
	adds r5, r0, #0
	cmp r2, #0
	beq _0807A044
	cmp r2, #0xe0
	bne _0807A046
_0807A044:
	strh r2, [r1]
_0807A046:
	adds r4, r5, #0
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #1
	adds r1, r4, #0
	adds r1, #0x12
	adds r1, r0, r1
	ldrh r3, [r1]
	cmp r3, #0xdf
	bls _0807A060
	movs r0, #0x80
	lsls r0, r0, #4
	add r8, r0
	subs r3, #0xe0
_0807A060:
	asrs r0, r3, #3
	lsls r3, r0, #5
	add r8, r3
	ldrh r1, [r1]
	movs r3, #7
	ldrh r0, [r6]
	ldrb r2, [r4, #0x16]
	ands r3, r1
	ldrb r1, [r4, #0x1e]
	str r1, [sp]
	mov r1, r8
	bl TextDrawCharacter
	cmp r7, #0
	bne _0807A0BA
	ldrh r0, [r6]
	cmp r0, #0x40
	beq _0807A0BA
	ldrb r0, [r4, #0x17]
	cmp r0, #1
	bne _0807A09C
	ldrh r0, [r6]
	movs r1, #0x21
	bl PlayCharacterAppearingSound
	movs r0, #2
	strb r0, [r4, #0x1b]
	b _0807A0BA
	.align 2, 0
_0807A098: .4byte gNonGameplayRam
_0807A09C:
	cmp r0, #2
	bne _0807A0AE
	ldrh r0, [r6]
	movs r1, #0x41
	bl PlayCharacterAppearingSound
	movs r0, #3
	strb r0, [r4, #0x1b]
	b _0807A0BA
_0807A0AE:
	ldrh r0, [r6]
	movs r1, #1
	bl PlayCharacterAppearingSound
	movs r0, #1
	strb r0, [r5, #0x1b]
_0807A0BA:
	movs r3, #1
	ldrh r2, [r6, #2]
	movs r0, #0x80
	lsls r0, r0, #8
	ands r0, r2
	cmp r0, #0
	beq _0807A0D4
	movs r1, #0xf0
	lsls r1, r1, #8
	bics r1, r2
	rsbs r0, r1, #0
	orrs r0, r1
	lsrs r3, r0, #0x1f
_0807A0D4:
	cmp r3, #0
	beq _0807A0EC
	ldr r2, _0807A0F8 @ =gNonGameplayRam
	ldrb r1, [r2, #0x18]
	lsls r1, r1, #1
	adds r0, r2, #0
	adds r0, #0x12
	adds r1, r1, r0
	ldrh r0, [r1]
	ldrb r2, [r2, #0x16]
	adds r0, r0, r2
	strh r0, [r1]
_0807A0EC:
	add sp, #4
	pop {r3}
	mov r8, r3
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807A0F8: .4byte gNonGameplayRam
