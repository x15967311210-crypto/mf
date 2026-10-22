    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start ProcessPauseScreenText
ProcessPauseScreenText: @ 0x0807B8D4
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	ldr r4, _0807B93C @ =0x0200C000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	movs r1, #0
	adds r2, r4, #0
	bl BitFill
	movs r6, #0
	ldr r2, _0807B940 @ =0x0879C10C (sBlob_79bec0_79c128+0x24C)
	ldr r0, _0807B944 @ =0x03000011
	movs r1, #0
	ldrsb r1, [r0, r1]
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r0, _0807B948 @ =gEventCounter
	ldrb r0, [r0]
	ldr r1, [r1]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r7, [r0]
	ldrh r2, [r7]
	movs r1, #0xff
	lsls r1, r1, #8
	adds r0, r1, #0
	cmp r2, r0
	beq _0807B9D8
	movs r5, #0x80
	lsls r5, r5, #8
	mov sl, r5
	movs r1, #0xfe
	lsls r1, r1, #8
	mov sb, r1
_0807B926:
	movs r5, #1
	adds r1, r0, #0
	ands r1, r2
	cmp r1, sl
	bne _0807B94C
	movs r5, #0xff
	mov r8, r5
	mov r0, r8
	ands r0, r2
	mov r8, r0
	b _0807B9C2
	.align 2, 0
_0807B93C: .4byte 0x0200C000
_0807B940: .4byte sExploredMinimapBitFlags+0x330
_0807B944: .4byte 0x03000011
_0807B948: .4byte gEventCounter
_0807B94C:
	movs r0, #0x83
	lsls r0, r0, #8
	cmp r1, r0
	bne _0807B95E
	movs r1, #0
	mov r8, r1
	movs r6, #0xff
	ands r6, r2
	b _0807B9C2
_0807B95E:
	cmp r2, sb
	bne _0807B96E
	movs r2, #0
	mov r8, r2
	cmp r6, #0xe0
	bgt _0807B9D8
	movs r6, #0xe0
	movs r5, #0
_0807B96E:
	cmp r5, #0
	beq _0807B9C2
	ldrh r0, [r7]
	bl TextGetCharacterWidth
	mov r8, r0
	adds r5, r6, r0
	cmp r5, #0xe0
	ble _0807B988
	cmp r6, #0xdf
	bgt _0807B988
	movs r6, #0xe0
	b _0807B990
_0807B988:
	movs r0, #0xe0
	lsls r0, r0, #1
	cmp r5, r0
	bgt _0807B9D8
_0807B990:
	cmp r6, #0xdf
	ble _0807B99E
	movs r5, #0x80
	lsls r5, r5, #4
	adds r4, r6, #0
	subs r4, #0xe0
	b _0807B9A2
_0807B99E:
	movs r5, #0
	adds r4, r6, #0
_0807B9A2:
	asrs r0, r4, #3
	lsls r0, r0, #5
	adds r5, r5, r0
	movs r3, #7
	ldrh r0, [r7]
	ldr r2, _0807B9E8 @ =0x0200C000
	adds r1, r2, r5
	mov r5, r8
	lsls r2, r5, #0x18
	lsrs r2, r2, #0x18
	ands r4, r3
	movs r3, #0
	str r3, [sp]
	adds r3, r4, #0
	bl TextDrawCharacter
_0807B9C2:
	adds r7, #2
	add r6, r8
	ldr r0, _0807B9EC @ =0x000001BF
	cmp r6, r0
	bgt _0807B9D8
	ldrh r2, [r7]
	movs r1, #0xff
	lsls r1, r1, #8
	adds r0, r1, #0
	cmp r2, r0
	bne _0807B926
_0807B9D8:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807B9E8: .4byte 0x0200C000
_0807B9EC: .4byte 0x000001BF

	thumb_func_start ProcessEasySleepText
ProcessEasySleepText: @ 0x0807B9F0
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #4
	ldr r2, _0807BA80 @ =0x0200D000
	movs r5, #0x80
	lsls r5, r5, #5
	movs r4, #0x10
	str r4, [sp]
	movs r0, #3
	movs r1, #0
	adds r3, r5, #0
	bl BitFill
	ldr r2, _0807BA84 @ =0x0200E000
	str r4, [sp]
	movs r0, #3
	movs r1, #0
	adds r3, r5, #0
	bl BitFill
	ldr r2, _0807BA88 @ =0x0200F000
	movs r3, #0x80
	lsls r3, r3, #4
	str r4, [sp]
	movs r0, #3
	movs r1, #0
	bl BitFill
	movs r3, #0
_0807BA30:
	ldr r0, _0807BA84 @ =0x0200E000
	mov sl, r0
	cmp r3, #0
	bne _0807BA3C
	ldr r1, _0807BA80 @ =0x0200D000
	mov sl, r1
_0807BA3C:
	ldr r1, _0807BA8C @ =0x0879CDF4 (sMessageTextPointers)
	ldr r0, _0807BA90 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	lsls r0, r3, #2
	adds r0, r0, r1
	adds r0, #0xb4
	ldr r6, [r0]
	movs r7, #0
	ldrh r2, [r6]
	movs r4, #0xff
	lsls r4, r4, #8
	adds r0, r4, #0
	adds r3, #1
	mov sb, r3
	cmp r2, r4
	beq _0807BB24
_0807BA66:
	movs r5, #1
	adds r1, r0, #0
	ands r1, r2
	movs r0, #0x80
	lsls r0, r0, #8
	cmp r1, r0
	bne _0807BA94
	movs r1, #0xff
	mov r8, r1
	mov r4, r8
	ands r4, r2
	mov r8, r4
	b _0807BB0E
	.align 2, 0
_0807BA80: .4byte 0x0200D000
_0807BA84: .4byte 0x0200E000
_0807BA88: .4byte 0x0200F000
_0807BA8C: .4byte sMessageTextPointers
_0807BA90: .4byte 0x03000011
_0807BA94:
	movs r0, #0x83
	lsls r0, r0, #8
	cmp r1, r0
	bne _0807BAA6
	movs r5, #0
	mov r8, r5
	movs r7, #0xff
	ands r7, r2
	b _0807BB0E
_0807BAA6:
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r2, r0
	bne _0807BABA
	movs r1, #0
	mov r8, r1
	cmp r7, #0xe0
	bgt _0807BB24
	movs r7, #0xe0
	movs r5, #0
_0807BABA:
	cmp r5, #0
	beq _0807BB0E
	ldrh r0, [r6]
	bl TextGetCharacterWidth
	mov r8, r0
	adds r5, r7, r0
	cmp r5, #0xe0
	ble _0807BAD4
	cmp r7, #0xdf
	bgt _0807BAD4
	movs r7, #0xe0
	b _0807BADC
_0807BAD4:
	movs r0, #0xe0
	lsls r0, r0, #1
	cmp r5, r0
	bgt _0807BB24
_0807BADC:
	cmp r7, #0xdf
	ble _0807BAEA
	movs r5, #0x80
	lsls r5, r5, #4
	adds r4, r7, #0
	subs r4, #0xe0
	b _0807BAEE
_0807BAEA:
	movs r5, #0
	adds r4, r7, #0
_0807BAEE:
	asrs r0, r4, #3
	lsls r0, r0, #5
	adds r5, r5, r0
	movs r3, #7
	ldrh r0, [r6]
	mov r2, sl
	adds r1, r2, r5
	mov r5, r8
	lsls r2, r5, #0x18
	lsrs r2, r2, #0x18
	ands r4, r3
	movs r3, #0
	str r3, [sp]
	adds r3, r4, #0
	bl TextDrawCharacter
_0807BB0E:
	adds r6, #2
	add r7, r8
	ldr r0, _0807BB60 @ =0x000001BF
	cmp r7, r0
	bgt _0807BB24
	ldrh r2, [r6]
	movs r1, #0xff
	lsls r1, r1, #8
	adds r0, r1, #0
	cmp r2, r1
	bne _0807BA66
_0807BB24:
	mov r3, sb
	cmp r3, #1
	ble _0807BA30
	ldr r2, _0807BB64 @ =0x0200F000
	mov sl, r2
	ldr r1, _0807BB68 @ =0x0879CDF4 (sMessageTextPointers)
	ldr r0, _0807BB6C @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	adds r0, #0xbc
	ldr r6, [r0]
	movs r7, #0
	ldrh r1, [r6]
	movs r0, #0xff
	lsls r0, r0, #8
	cmp r1, r0
	beq _0807BBE0
	movs r5, #1
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r1, r0
	bne _0807BB70
	movs r4, #0
	mov r8, r4
	movs r7, #0x70
	b _0807BBB2
	.align 2, 0
_0807BB60: .4byte 0x000001BF
_0807BB64: .4byte 0x0200F000
_0807BB68: .4byte sMessageTextPointers
_0807BB6C: .4byte 0x03000011
_0807BB70:
	ldrh r1, [r6]
	movs r0, #0x80
	lsls r0, r0, #8
	ands r0, r1
	cmp r0, #0
	beq _0807BB80
	movs r5, #0
	mov r8, r5
_0807BB80:
	cmp r5, #0
	beq _0807BBB2
	ldrh r0, [r6]
	bl TextGetCharacterWidth
	mov r8, r0
	adds r5, r7, r0
	movs r0, #0xe0
	lsls r0, r0, #1
	cmp r5, r0
	bgt _0807BBE0
	asrs r0, r7, #3
	lsls r5, r0, #5
	movs r3, #7
	ldrh r0, [r6]
	mov r2, sl
	adds r1, r2, r5
	mov r4, r8
	lsls r2, r4, #0x18
	lsrs r2, r2, #0x18
	ands r3, r7
	movs r4, #0
	str r4, [sp]
	bl TextDrawCharacter
_0807BBB2:
	adds r6, #2
	add r7, r8
	ldr r0, _0807BBDC @ =0x000001BF
	cmp r7, r0
	bgt _0807BBE0
	ldrh r1, [r6]
	movs r0, #0xff
	lsls r0, r0, #8
	cmp r1, r0
	beq _0807BBE0
	movs r5, #1
	movs r0, #0xfe
	lsls r0, r0, #8
	cmp r1, r0
	bne _0807BB70
	movs r5, #0
	mov r8, r5
	cmp r7, #0x70
	bgt _0807BBE0
	movs r7, #0x70
	b _0807BBB2
	.align 2, 0
_0807BBDC: .4byte 0x000001BF
_0807BBE0:
	add sp, #4
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

	thumb_func_start GetFlashingSectorNumber
GetFlashingSectorNumber: @ 0x0807BBF0
	push {r4, r5, r6, r7, lr}
	ldr r0, _0807BC80 @ =0x0300004D
	movs r1, #0
	strb r1, [r0]
	ldr r1, _0807BC84 @ =gEventCounter
	ldrb r2, [r1]
	adds r6, r0, #0
	ldr r1, _0807BC88 @ =0x08575A60 (sEventLocationAndNavigationInfo)
	ldr r7, _0807BC8C @ =gPreviousNavigationConversation
	cmp r2, #0
	ble _0807BC2A
	lsls r0, r2, #1
	adds r0, r0, r2
	lsls r3, r0, #2
	adds r0, r3, r1
	ldrb r0, [r0, #6]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #0
	bne _0807BC2A
	adds r3, r3, r1
_0807BC1A:
	subs r3, #0xc
	subs r2, #1
	cmp r2, #0
	ble _0807BC2A
	movs r0, #6
	ldrsb r0, [r3, r0]
	cmp r0, #0
	beq _0807BC1A
_0807BC2A:
	lsls r0, r2, #1
	adds r0, r0, r2
	lsls r0, r0, #2
	adds r0, r0, r1
	movs r3, #6
	ldrsb r3, [r0, r3]
	ldrb r4, [r7]
	cmp r4, r3
	bne _0807BC76
	movs r3, #0
	movs r2, #0
	ldr r0, _0807BC90 @ =0x085766E4 (sBlob_5766D4_prefix+0x10)
	movs r1, #0
	ldrsb r1, [r0, r1]
	adds r5, r0, #0
	cmp r4, r1
	beq _0807BC68
_0807BC4C:
	adds r2, #1
	cmp r2, #0x20
	bhi _0807BC64
	ldrb r0, [r7]
	lsls r1, r2, #3
	adds r1, r1, r5
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	cmp r0, r1
	bne _0807BC4C
	movs r3, #1
_0807BC64:
	cmp r3, #0
	beq _0807BC76
_0807BC68:
	lsls r0, r2, #3
	adds r0, r0, r5
	ldrb r2, [r0, #1]
	ldr r0, _0807BC94 @ =0x08576066 (sNavigationTargetLocationAreas)
	adds r0, r2, r0
	ldrb r0, [r0]
	strb r0, [r6]
_0807BC76:
	ldrb r0, [r6]
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0807BC80: .4byte 0x0300004D
_0807BC84: .4byte gEventCounter
_0807BC88: .4byte sEventLocationAndNavigationInfo
_0807BC8C: .4byte gPreviousNavigationConversation
_0807BC90: .4byte sCharacterWidths+0x4B0
_0807BC94: .4byte sNavigationTargetLocationAreas

	thumb_func_start NavigationConversationLoadPopUpGraphics
NavigationConversationLoadPopUpGraphics: @ 0x0807BC98
	push {r4, r5, r6, lr}
	sub sp, #8
	movs r4, #3
	ldr r0, _0807BD68 @ =gNonGameplayRam
	movs r1, #0x88
	lsls r1, r1, #2
	adds r0, r0, r1
	ldrb r2, [r0]
	ldr r0, _0807BD6C @ =0x0857BCC8 (sBlob_5766D4_after)
	movs r1, #8
	ldrsb r1, [r0, r1]
	adds r3, r0, #0
	cmp r2, r1
	beq _0807BCC8
	adds r1, r3, #0
	adds r1, #8
_0807BCB8:
	subs r1, #4
	subs r4, #1
	cmp r4, #0
	ble _0807BCC8
	movs r0, #0
	ldrsb r0, [r1, r0]
	cmp r2, r0
	bne _0807BCB8
_0807BCC8:
	cmp r4, #0
	beq _0807BD5E
	subs r4, #1
	lsls r0, r4, #2
	adds r4, r0, r3
	ldrb r0, [r4, #1]
	cmp r0, #0
	beq _0807BCF0
	ldr r2, _0807BD70 @ =0x0857BC50 (sNavigationConversationPopUpGraphics)
	adds r1, r0, #0
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	adds r2, #0x14
	adds r0, r0, r2
	ldr r0, [r0]
	movs r1, #0x80
	lsls r1, r1, #0x12
	bl LZ77UncompVram
_0807BCF0:
	ldrb r0, [r4, #2]
	cmp r0, #0
	beq _0807BD0C
	ldr r2, _0807BD70 @ =0x0857BC50 (sNavigationConversationPopUpGraphics)
	adds r1, r0, #0
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	adds r2, #0x14
	adds r0, r0, r2
	ldr r0, [r0]
	ldr r1, _0807BD74 @ =0x02004000
	bl LZ77UncompVram
_0807BD0C:
	ldrb r0, [r4, #3]
	cmp r0, #0
	beq _0807BD28
	ldr r2, _0807BD70 @ =0x0857BC50 (sNavigationConversationPopUpGraphics)
	adds r1, r0, #0
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	adds r2, #0x14
	adds r0, r0, r2
	ldr r0, [r0]
	ldr r1, _0807BD78 @ =0x02008000
	bl LZ77UncompVram
_0807BD28:
	movs r4, #5
	ldr r5, _0807BD7C @ =0x06015700
	movs r6, #0x20
_0807BD2E:
	str r6, [sp]
	movs r0, #3
	movs r1, #1
	rsbs r1, r1, #0
	adds r2, r5, #0
	movs r3, #0x80
	lsls r3, r3, #1
	bl BitFill
	ldr r0, _0807BD80 @ =0xFFFFFC00
	adds r5, r5, r0
	subs r4, #1
	cmp r4, #0
	bge _0807BD2E
	movs r0, #0
	str r0, [sp, #4]
	ldr r1, _0807BD84 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _0807BD88 @ =0x050003E0
	str r0, [r1, #4]
	ldr r0, _0807BD8C @ =0x85000008
	str r0, [r1, #8]
	ldr r0, [r1, #8]
_0807BD5E:
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0807BD68: .4byte gNonGameplayRam
_0807BD6C: .4byte sCharacterWidths+0x5A94
_0807BD70: .4byte sCharacterWidths+0x5A1C
_0807BD74: .4byte 0x02004000
_0807BD78: .4byte 0x02008000
_0807BD7C: .4byte 0x06015700
_0807BD80: .4byte 0xFFFFFC00
_0807BD84: .4byte 0x040000D4
_0807BD88: .4byte 0x050003E0
_0807BD8C: .4byte 0x85000008

	thumb_func_start NavigationConversationUpdatePopUp
NavigationConversationUpdatePopUp: @ 0x0807BD90
	push {r4, lr}
	ldr r4, _0807BDD0 @ =gNonGameplayRam
	movs r0, #0x86
	lsls r0, r0, #2
	adds r2, r4, r0
	ldrb r0, [r2]
	cmp r0, #0
	beq _0807BDC8
	ldr r0, _0807BDD4 @ =0x0000021B
	adds r1, r4, r0
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	ldr r1, _0807BDD8 @ =0x0879C170 (sBlob_79c170_79c27c)
	ldrb r0, [r2]
	subs r0, #1
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r0, [r0]
	bl _call_via_r0
	ldr r1, _0807BDDC @ =0x0000021D
	adds r0, r4, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807BDC8
	bl NavigationConversationFadeInPopUpPalette
_0807BDC8:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0807BDD0: .4byte gNonGameplayRam
_0807BDD4: .4byte 0x0000021B
_0807BDD8: .4byte sExploredMinimapBitFlags+0x394
_0807BDDC: .4byte 0x0000021D

	thumb_func_start unk_7bde0
unk_7bde0: @ 0x0807BDE0
	push {r4, r5, r6, r7, lr}
	ldr r2, _0807BE2C @ =gNonGameplayRam
	ldr r0, _0807BE30 @ =0x0000021A
	adds r1, r2, r0
	movs r0, #0xff
	strb r0, [r1]
	movs r3, #3
	movs r1, #0x88
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrb r4, [r0]
	ldr r0, _0807BE34 @ =0x0857BCC8 (sBlob_5766D4_after)
	movs r1, #8
	ldrsb r1, [r0, r1]
	adds r6, r2, #0
	adds r2, r0, #0
	cmp r4, r1
	beq _0807BE18
	adds r1, r2, #0
	adds r1, #8
_0807BE08:
	subs r1, #4
	subs r3, #1
	cmp r3, #0
	ble _0807BE18
	movs r0, #0
	ldrsb r0, [r1, r0]
	cmp r4, r0
	bne _0807BE08
_0807BE18:
	subs r3, #1
	cmp r3, #0xff
	bne _0807BE38
	movs r2, #0x86
	lsls r2, r2, #2
	adds r1, r6, r2
	movs r0, #0
	strb r0, [r1]
	b _0807BFAE
	.align 2, 0
_0807BE2C: .4byte gNonGameplayRam
_0807BE30: .4byte 0x0000021A
_0807BE34: .4byte sCharacterWidths+0x5A94
_0807BE38:
	ldr r1, _0807BE4C @ =0x00000219
	adds r0, r6, r1
	ldrb r0, [r0]
	cmp r0, #1
	bne _0807BE50
	lsls r0, r3, #2
	adds r0, r0, r2
	ldrb r1, [r0, #2]
	b _0807BE62
	.align 2, 0
_0807BE4C: .4byte 0x00000219
_0807BE50:
	cmp r0, #2
	bne _0807BE5C
	lsls r0, r3, #2
	adds r0, r0, r2
	ldrb r1, [r0, #3]
	b _0807BE62
_0807BE5C:
	lsls r0, r3, #2
	adds r0, r0, r2
	ldrb r1, [r0, #1]
_0807BE62:
	ldr r2, _0807BE7C @ =0x0000021A
	adds r0, r6, r2
	strb r1, [r0]
	ldr r1, _0807BE7C @ =0x0000021A
	adds r0, r6, r1
	ldrb r3, [r0]
	cmp r3, #0
	bne _0807BE80
	movs r2, #0x86
	lsls r2, r2, #2
	adds r0, r6, r2
	strb r3, [r0]
	b _0807BFAE
	.align 2, 0
_0807BE7C: .4byte 0x0000021A
_0807BE80:
	ldr r1, _0807BEA4 @ =0x00000229
	adds r0, r6, r1
	movs r1, #0
	strb r1, [r0]
	movs r2, #0x8a
	lsls r2, r2, #2
	adds r0, r6, r2
	strb r1, [r0]
	ldr r1, _0807BEA8 @ =0x00000219
	adds r0, r6, r1
	ldrb r0, [r0]
	cmp r0, #1
	bne _0807BEB0
	subs r2, #0x14
	adds r1, r6, r2
	ldr r0, _0807BEAC @ =0x02004000
	b _0807BECE
	.align 2, 0
_0807BEA4: .4byte 0x00000229
_0807BEA8: .4byte 0x00000219
_0807BEAC: .4byte 0x02004000
_0807BEB0:
	cmp r0, #2
	bne _0807BEC4
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r6, r0
	ldr r0, _0807BEC0 @ =0x02008000
	b _0807BECE
	.align 2, 0
_0807BEC0: .4byte 0x02008000
_0807BEC4:
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r6, r2
	movs r0, #0x80
	lsls r0, r0, #0x12
_0807BECE:
	str r0, [r1]
	ldr r2, _0807BF28 @ =0x0857BC50 (sNavigationConversationPopUpGraphics)
	ldr r1, _0807BF2C @ =0x0000021A
	adds r0, r6, r1
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	adds r1, r0, r2
	ldrb r0, [r1, #0x12]
	lsls r2, r0, #0x1c
	lsrs r0, r2, #0x1c
	cmp r0, #8
	bne _0807BF40
	ldrb r2, [r1, #0x11]
	lsls r0, r2, #0x1c
	lsrs r3, r0, #0x1c
	cmp r3, #0
	ble _0807BF82
	ldr r5, _0807BF30 @ =0x040000D4
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r6, r1
	ldr r1, [r0]
	lsls r0, r3, #0xa
	adds r4, r0, r1
	ldr r0, _0807BF34 @ =0xFFFFFC00
	mov ip, r0
	lsls r7, r2, #0x18
_0807BF08:
	add r4, ip
	subs r3, #1
	lsls r2, r3, #0xa
	str r4, [r5]
	lsrs r0, r7, #0x1c
	lsls r0, r0, #0xa
	ldr r1, _0807BF38 @ =0x06014300
	adds r0, r0, r1
	adds r2, r2, r0
	str r2, [r5, #4]
	ldr r0, _0807BF3C @ =0x80000080
	str r0, [r5, #8]
	ldr r0, [r5, #8]
	cmp r3, #0
	bgt _0807BF08
	b _0807BF82
	.align 2, 0
_0807BF28: .4byte sCharacterWidths+0x5A1C
_0807BF2C: .4byte 0x0000021A
_0807BF30: .4byte 0x040000D4
_0807BF34: .4byte 0xFFFFFC00
_0807BF38: .4byte 0x06014300
_0807BF3C: .4byte 0x80000080
_0807BF40:
	lsrs r0, r2, #0x1c
	cmp r0, #4
	bne _0807BF82
	ldrb r2, [r1, #0x11]
	lsls r0, r2, #0x1c
	lsrs r3, r0, #0x1c
	cmp r3, #0
	ble _0807BF82
	ldr r5, _0807BFB4 @ =0x040000D4
	movs r1, #0x85
	lsls r1, r1, #2
	adds r0, r6, r1
	ldr r1, [r0]
	lsls r0, r3, #0xa
	adds r4, r0, r1
	lsls r7, r2, #0x18
_0807BF60:
	ldr r2, _0807BFB8 @ =0xFFFFFC00
	adds r4, r4, r2
	subs r3, #1
	lsls r2, r3, #0xa
	str r4, [r5]
	lsrs r0, r7, #0x1c
	lsls r0, r0, #0xa
	ldr r1, _0807BFBC @ =0x06014300
	adds r0, r0, r1
	adds r2, r2, r0
	adds r2, #0x40
	str r2, [r5, #4]
	ldr r0, _0807BFC0 @ =0x80000040
	str r0, [r5, #8]
	ldr r0, [r5, #8]
	cmp r3, #0
	bgt _0807BF60
_0807BF82:
	ldr r1, _0807BFC4 @ =0x0000021A
	adds r0, r6, r1
	ldrb r0, [r0]
	cmp r0, #3
	bne _0807BF92
	ldr r0, _0807BFC8 @ =0x00000125
	bl SoundPlay
_0807BF92:
	ldr r2, _0807BFCC @ =0x0000021D
	adds r1, r6, r2
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	movs r0, #0x86
	lsls r0, r0, #2
	adds r1, r6, r0
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	ldr r1, _0807BFD0 @ =0x0000021B
	adds r0, r6, r1
	strb r2, [r0]
_0807BFAE:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807BFB4: .4byte 0x040000D4
_0807BFB8: .4byte 0xFFFFFC00
_0807BFBC: .4byte 0x06014300
_0807BFC0: .4byte 0x80000040
_0807BFC4: .4byte 0x0000021A
_0807BFC8: .4byte 0x00000125
_0807BFCC: .4byte 0x0000021D
_0807BFD0: .4byte 0x0000021B

	thumb_func_start NavigationConversationFadeInPopUpPalette
NavigationConversationFadeInPopUpPalette: @ 0x0807BFD4
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #8
	ldr r2, _0807C068 @ =0x0857BC50 (sNavigationConversationPopUpGraphics)
	ldr r3, _0807C06C @ =gNonGameplayRam
	ldr r1, _0807C070 @ =0x0000021A
	adds r0, r3, r1
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	adds r2, #8
	adds r0, r0, r2
	ldr r2, [r0]
	ldr r6, _0807C074 @ =0x050003E0
	movs r0, #0
	mov ip, r0
	mov sb, sp
	movs r1, #0xf8
	lsls r1, r1, #7
	mov sl, r1
	add r5, sp, #4
_0807C006:
	ldrb r1, [r2]
	movs r0, #0x1f
	ands r0, r1
	mov r1, sb
	strb r0, [r1]
	ldrh r1, [r2]
	movs r0, #0xf8
	lsls r0, r0, #2
	ands r0, r1
	lsrs r0, r0, #5
	mov r1, sb
	strb r0, [r1, #1]
	ldrh r1, [r2]
	mov r0, sl
	ands r0, r1
	lsrs r0, r0, #0xa
	mov r1, sb
	strb r0, [r1, #2]
	ldrb r1, [r6]
	movs r0, #0x1f
	ands r0, r1
	strb r0, [r5]
	ldrh r1, [r6]
	movs r0, #0xf8
	lsls r0, r0, #2
	ands r0, r1
	lsrs r0, r0, #5
	strb r0, [r5, #1]
	ldrh r1, [r6]
	mov r0, sl
	ands r0, r1
	lsrs r0, r0, #0xa
	strb r0, [r5, #2]
	movs r4, #0
	movs r0, #1
	add ip, r0
	adds r7, r2, #2
	adds r1, r6, #2
	mov r8, r1
	adds r3, r5, #0
_0807C056:
	mov r1, sp
	adds r0, r1, r4
	ldrb r2, [r3]
	ldrb r1, [r0]
	adds r0, r2, #0
	cmp r1, r0
	bls _0807C078
	adds r0, r2, #1
	b _0807C07E
	.align 2, 0
_0807C068: .4byte sCharacterWidths+0x5A1C
_0807C06C: .4byte gNonGameplayRam
_0807C070: .4byte 0x0000021A
_0807C074: .4byte 0x050003E0
_0807C078:
	cmp r1, r0
	bhs _0807C080
	subs r0, r2, #1
_0807C07E:
	strb r0, [r3]
_0807C080:
	adds r3, #1
	adds r4, #1
	cmp r4, #2
	ble _0807C056
	ldrb r0, [r5]
	ldrb r1, [r5, #1]
	lsls r1, r1, #5
	orrs r0, r1
	ldrb r1, [r5, #2]
	lsls r1, r1, #0xa
	orrs r0, r1
	strh r0, [r6]
	adds r2, r7, #0
	mov r6, r8
	mov r0, ip
	cmp r0, #0xf
	ble _0807C006
	ldr r1, _0807C0B4 @ =gNonGameplayRam
	ldr r0, _0807C0B8 @ =0x0000021D
	adds r3, r1, r0
	ldrb r0, [r3]
	cmp r0, #0x20
	bls _0807C0BC
	movs r0, #0
	b _0807C0BE
	.align 2, 0
_0807C0B4: .4byte gNonGameplayRam
_0807C0B8: .4byte 0x0000021D
_0807C0BC:
	adds r0, #1
_0807C0BE:
	strb r0, [r3]
	add sp, #8
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0

	thumb_func_start NavigationConversationUpdateXParasitePopUp
NavigationConversationUpdateXParasitePopUp: @ 0x0807C0D0
	push {r4, r5, r6, r7, lr}
	bl unk_7c3b4
	ldr r0, _0807C148 @ =0x0857BC50 (sNavigationConversationPopUpGraphics)
	mov ip, r0
	ldr r3, _0807C14C @ =gNonGameplayRam
	ldr r1, _0807C150 @ =0x0000021A
	adds r6, r3, r1
	ldrb r1, [r6]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	mov r2, ip
	adds r1, r0, r2
	ldrb r0, [r1, #0x12]
	lsls r2, r0, #0x1c
	lsrs r0, r2, #0x1c
	cmp r0, #8
	beq _0807C0F8
	b _0807C20C
_0807C0F8:
	ldr r7, [r1]
	ldr r0, _0807C154 @ =0x0000021B
	adds r2, r3, r0
	movs r1, #0x87
	lsls r1, r1, #2
	adds r4, r3, r1
	ldrb r0, [r4]
	lsls r0, r0, #1
	adds r0, r0, r7
	ldrb r1, [r2]
	ldrb r0, [r0, #1]
	cmp r1, r0
	bhs _0807C114
	b _0807C2F4
_0807C114:
	movs r5, #0
	strb r5, [r2]
	ldrb r0, [r4]
	adds r0, #1
	strb r0, [r4]
	ldrb r2, [r6]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	add r1, ip
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1, #4]
	cmp r0, r1
	blo _0807C134
	strb r5, [r4]
_0807C134:
	ldr r2, _0807C158 @ =0x00000219
	adds r0, r3, r2
	ldrb r0, [r0]
	cmp r0, #1
	bne _0807C160
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	ldr r0, _0807C15C @ =0x02004000
	b _0807C17E
	.align 2, 0
_0807C148: .4byte sCharacterWidths+0x5A1C
_0807C14C: .4byte gNonGameplayRam
_0807C150: .4byte 0x0000021A
_0807C154: .4byte 0x0000021B
_0807C158: .4byte 0x00000219
_0807C15C: .4byte 0x02004000
_0807C160:
	cmp r0, #2
	bne _0807C174
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	ldr r0, _0807C170 @ =0x02008000
	b _0807C17E
	.align 2, 0
_0807C170: .4byte 0x02008000
_0807C174:
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r0, #0x80
	lsls r0, r0, #0x12
_0807C17E:
	str r0, [r1]
	ldr r3, _0807C1F0 @ =0x0857BC50 (sNavigationConversationPopUpGraphics)
	ldr r2, _0807C1F4 @ =gNonGameplayRam
	ldr r1, _0807C1F8 @ =0x0000021A
	adds r0, r2, r1
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	adds r0, r0, r3
	ldrb r0, [r0, #0x11]
	lsls r3, r0, #0x1c
	lsrs r6, r0, #4
	movs r1, #0x87
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrb r0, [r0]
	lsls r0, r0, #1
	adds r0, r0, r7
	ldrb r1, [r0]
	movs r0, #3
	ands r0, r1
	lsls r4, r0, #8
	lsrs r1, r1, #2
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #0xb
	adds r4, r4, r0
	movs r0, #0x85
	lsls r0, r0, #2
	adds r2, r2, r0
	ldr r0, [r2]
	adds r5, r0, r4
	str r5, [r2]
	lsrs r4, r3, #0x1c
	cmp r4, #0
	bgt _0807C1CA
	b _0807C2F4
_0807C1CA:
	ldr r3, _0807C1FC @ =0x040000D4
	lsls r2, r4, #0xa
	ldr r0, _0807C200 @ =0x06014300
	adds r1, r2, r0
	lsls r0, r6, #0xa
	adds r1, r1, r0
	adds r2, r2, r5
	ldr r5, _0807C204 @ =0xFFFFFC00
	ldr r6, _0807C208 @ =0x80000080
_0807C1DC:
	adds r1, r1, r5
	adds r2, r2, r5
	subs r4, #1
	str r2, [r3]
	str r1, [r3, #4]
	str r6, [r3, #8]
	ldr r0, [r3, #8]
	cmp r4, #0
	bgt _0807C1DC
	b _0807C2F4
	.align 2, 0
_0807C1F0: .4byte sCharacterWidths+0x5A1C
_0807C1F4: .4byte gNonGameplayRam
_0807C1F8: .4byte 0x0000021A
_0807C1FC: .4byte 0x040000D4
_0807C200: .4byte 0x06014300
_0807C204: .4byte 0xFFFFFC00
_0807C208: .4byte 0x80000080
_0807C20C:
	lsrs r0, r2, #0x1c
	cmp r0, #4
	bne _0807C2F4
	ldr r7, [r1]
	ldr r1, _0807C260 @ =0x0000021B
	adds r2, r3, r1
	movs r0, #0x87
	lsls r0, r0, #2
	adds r4, r3, r0
	ldrb r0, [r4]
	lsls r0, r0, #1
	adds r0, r0, r7
	ldrb r1, [r2]
	ldrb r0, [r0, #1]
	cmp r1, r0
	blo _0807C2F4
	movs r5, #0
	strb r5, [r2]
	ldrb r0, [r4]
	adds r0, #1
	strb r0, [r4]
	ldrb r2, [r6]
	lsls r1, r2, #1
	adds r1, r1, r2
	lsls r1, r1, #3
	add r1, ip
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1, #4]
	cmp r0, r1
	blo _0807C24C
	strb r5, [r4]
_0807C24C:
	ldr r1, _0807C264 @ =0x00000219
	adds r0, r3, r1
	ldrb r0, [r0]
	cmp r0, #1
	bne _0807C26C
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	ldr r0, _0807C268 @ =0x02004000
	b _0807C28A
	.align 2, 0
_0807C260: .4byte 0x0000021B
_0807C264: .4byte 0x00000219
_0807C268: .4byte 0x02004000
_0807C26C:
	cmp r0, #2
	bne _0807C280
	movs r0, #0x85
	lsls r0, r0, #2
	adds r1, r3, r0
	ldr r0, _0807C27C @ =0x02008000
	b _0807C28A
	.align 2, 0
_0807C27C: .4byte 0x02008000
_0807C280:
	movs r2, #0x85
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #0x80
	lsls r0, r0, #0x12
_0807C28A:
	str r0, [r1]
	ldr r3, _0807C2FC @ =0x0857BC50 (sNavigationConversationPopUpGraphics)
	ldr r2, _0807C300 @ =gNonGameplayRam
	ldr r1, _0807C304 @ =0x0000021A
	adds r0, r2, r1
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #3
	adds r0, r0, r3
	ldrb r0, [r0, #0x11]
	lsls r3, r0, #0x1c
	lsrs r6, r0, #4
	movs r1, #0x87
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrb r0, [r0]
	lsls r0, r0, #1
	adds r0, r0, r7
	ldrb r1, [r0]
	movs r0, #7
	ands r0, r1
	lsls r4, r0, #7
	lsrs r1, r1, #3
	lsls r1, r1, #0xc
	adds r4, r4, r1
	movs r0, #0x85
	lsls r0, r0, #2
	adds r2, r2, r0
	ldr r0, [r2]
	adds r5, r0, r4
	str r5, [r2]
	lsrs r4, r3, #0x1c
	cmp r4, #0
	ble _0807C2F4
	ldr r3, _0807C308 @ =0x040000D4
	lsls r2, r4, #0xa
	ldr r0, _0807C30C @ =0x06014340
	adds r1, r2, r0
	lsls r0, r6, #0xa
	adds r1, r1, r0
	adds r2, r2, r5
	ldr r5, _0807C310 @ =0xFFFFFC00
	ldr r6, _0807C314 @ =0x80000040
_0807C2E2:
	adds r1, r1, r5
	adds r2, r2, r5
	subs r4, #1
	str r2, [r3]
	str r1, [r3, #4]
	str r6, [r3, #8]
	ldr r0, [r3, #8]
	cmp r4, #0
	bgt _0807C2E2
_0807C2F4:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807C2FC: .4byte sCharacterWidths+0x5A1C
_0807C300: .4byte gNonGameplayRam
_0807C304: .4byte 0x0000021A
_0807C308: .4byte 0x040000D4
_0807C30C: .4byte 0x06014340
_0807C310: .4byte 0xFFFFFC00
_0807C314: .4byte 0x80000040

	thumb_func_start NavigationConversationClearPopUpGraphics
NavigationConversationClearPopUpGraphics: @ 0x0807C318
	push {r4, r5, r6, lr}
	sub sp, #8
	movs r5, #5
	ldr r4, _0807C390 @ =0x06015700
	movs r6, #0x20
_0807C322:
	str r6, [sp]
	movs r0, #3
	movs r1, #1
	rsbs r1, r1, #0
	adds r2, r4, #0
	movs r3, #0x80
	lsls r3, r3, #1
	bl BitFill
	ldr r0, _0807C394 @ =0xFFFFFC00
	adds r4, r4, r0
	subs r5, #1
	cmp r5, #0
	bge _0807C322
	movs r5, #0
	str r5, [sp, #4]
	ldr r1, _0807C398 @ =0x040000D4
	add r0, sp, #4
	str r0, [r1]
	ldr r0, _0807C39C @ =0x050003E0
	str r0, [r1, #4]
	ldr r0, _0807C3A0 @ =0x85000008
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r4, _0807C3A4 @ =gNonGameplayRam
	ldr r1, _0807C3A8 @ =0x0000021A
	adds r0, r4, r1
	ldrb r0, [r0]
	cmp r0, #3
	bne _0807C364
	ldr r0, _0807C3AC @ =0x00000125
	bl SoundStop
_0807C364:
	movs r1, #0x86
	lsls r1, r1, #2
	adds r0, r4, r1
	strb r5, [r0]
	adds r1, #4
	adds r0, r4, r1
	strb r5, [r0]
	subs r1, #1
	adds r0, r4, r1
	strb r5, [r0]
	adds r1, #2
	adds r0, r4, r1
	strb r5, [r0]
	ldr r0, _0807C3B0 @ =0x00000219
	adds r1, r4, r0
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	add sp, #8
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0807C390: .4byte 0x06015700
_0807C394: .4byte 0xFFFFFC00
_0807C398: .4byte 0x040000D4
_0807C39C: .4byte 0x050003E0
_0807C3A0: .4byte 0x85000008
_0807C3A4: .4byte gNonGameplayRam
_0807C3A8: .4byte 0x0000021A
_0807C3AC: .4byte 0x00000125
_0807C3B0: .4byte 0x00000219

	thumb_func_start unk_7c3b4
unk_7c3b4: @ 0x0807C3B4
	push {r4, r5, r6, lr}
	ldr r4, _0807C42C @ =0x0857BC50 (sNavigationConversationPopUpGraphics)
	ldr r5, _0807C430 @ =gNonGameplayRam
	ldr r0, _0807C434 @ =0x0000021A
	adds r2, r5, r0
	ldrb r0, [r2]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #3
	adds r1, r1, r4
	ldrb r0, [r1, #0x10]
	cmp r0, #0
	beq _0807C424
	ldr r1, _0807C438 @ =0x00000229
	adds r3, r5, r1
	ldrb r1, [r3]
	adds r1, #1
	movs r6, #0
	strb r1, [r3]
	ldrb r2, [r2]
	lsls r0, r2, #1
	adds r0, r0, r2
	lsls r2, r0, #3
	adds r0, r2, r4
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	ldrb r0, [r0, #0x10]
	cmp r1, r0
	blo _0807C424
	strb r6, [r3]
	adds r0, r4, #0
	adds r0, #0xc
	adds r0, r2, r0
	movs r1, #0x8a
	lsls r1, r1, #2
	adds r4, r5, r1
	ldrb r1, [r4]
	lsls r1, r1, #1
	ldr r3, [r0]
	adds r2, r3, r1
	ldrh r0, [r2]
	cmp r0, #0
	bne _0807C40E
	strb r6, [r4]
	adds r2, r3, #0
_0807C40E:
	ldr r1, _0807C43C @ =0x050003FE
	ldrh r0, [r2]
	strh r0, [r1]
	ldrb r0, [r4]
	adds r0, #1
	strb r0, [r4]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0xf
	bls _0807C424
	strb r6, [r4]
_0807C424:
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0807C42C: .4byte sCharacterWidths+0x5A1C
_0807C430: .4byte gNonGameplayRam
_0807C434: .4byte 0x0000021A
_0807C438: .4byte 0x00000229
_0807C43C: .4byte 0x050003FE

	thumb_func_start unk_7c440
unk_7c440: @ 0x0807C440
	push {r4, r5, r6, r7, lr}
	ldr r2, _0807C518 @ =gNonGameplayRam
	ldr r0, _0807C51C @ =0x00000225
	adds r5, r2, r0
	ldrb r0, [r5]
	adds r0, #1
	movs r7, #0
	strb r0, [r5]
	ldr r3, _0807C520 @ =0x0857BEB4 (sBlob_5766D4_after+0x1EC)
	movs r1, #0x89
	lsls r1, r1, #2
	adds r4, r2, r1
	ldrb r1, [r4]
	adds r1, r1, r3
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	adds r6, r2, #0
	ldrb r1, [r1]
	cmp r0, r1
	blo _0807C4B0
	strb r7, [r5]
	ldrb r0, [r4]
	adds r0, #1
	strb r0, [r4]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bls _0807C47A
	strb r7, [r4]
_0807C47A:
	movs r3, #0xa0
	lsls r3, r3, #0x13
	ldr r1, _0807C524 @ =0x0857BCD4 (sBlob_5766D4_after+0xC)
	ldrb r0, [r4]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r0, [r0]
	strh r0, [r3, #0x24]
	ldrb r0, [r4]
	lsls r0, r0, #1
	adds r0, r0, r1
	ldrh r0, [r0]
	strh r0, [r3, #0x26]
	adds r1, r3, #0
	adds r1, #0x44
	ldr r2, _0807C528 @ =0x0857BCF4 (sBlob_5766D4_after+0x2C)
	ldrb r0, [r4]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	ldrb r0, [r4]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	strh r0, [r1]
_0807C4B0:
	adds r1, r6, #0
	ldrb r0, [r1]
	cmp r0, #0
	beq _0807C59C
	cmp r0, #1
	bne _0807C53C
	ldr r6, _0807C52C @ =0x0000022D
	adds r3, r1, r6
	ldrb r0, [r3]
	adds r0, #1
	movs r5, #0
	strb r0, [r3]
	ldr r2, _0807C530 @ =0x0857BEB8 (sBlob_5766D4_after+0x1F0)
	subs r6, #1
	adds r4, r1, r6
	ldrb r1, [r4]
	adds r1, r1, r2
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1]
	cmp r0, r1
	blo _0807C59C
	strb r5, [r3]
	ldrb r0, [r4]
	adds r0, #1
	strb r0, [r4]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #3
	bls _0807C4EE
	strb r5, [r4]
_0807C4EE:
	ldr r3, _0807C534 @ =0x05000138
	ldrb r0, [r4]
	lsls r0, r0, #4
	adds r0, #0xc
	adds r2, r0, #0
	movs r1, #0
	ldr r4, _0807C538 @ =0x0857BD34 (sBlob_5766D4_after+0x6C)
_0807C4FC:
	lsls r0, r2, #1
	adds r0, r0, r4
	ldrh r0, [r0]
	strh r0, [r3]
	adds r0, r1, #1
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	adds r0, r2, #1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	adds r3, #2
	cmp r1, #3
	bls _0807C4FC
	b _0807C59C
	.align 2, 0
_0807C518: .4byte gNonGameplayRam
_0807C51C: .4byte 0x00000225
_0807C520: .4byte sCharacterWidths+0x5C80
_0807C524: .4byte sCharacterWidths+0x5AA0
_0807C528: .4byte sCharacterWidths+0x5AC0
_0807C52C: .4byte 0x0000022D
_0807C530: .4byte sCharacterWidths+0x5C84
_0807C534: .4byte 0x05000138
_0807C538: .4byte sCharacterWidths+0x5B00
_0807C53C:
	cmp r0, #2
	bne _0807C59C
	ldr r0, _0807C5A4 @ =0x0000022D
	adds r3, r6, r0
	ldrb r0, [r3]
	adds r0, #1
	movs r5, #0
	strb r0, [r3]
	ldr r2, _0807C5A8 @ =0x0857BEBC (sBlob_5766D4_after+0x1F4)
	movs r1, #0x8b
	lsls r1, r1, #2
	adds r4, r6, r1
	ldrb r1, [r4]
	adds r1, r1, r2
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1]
	cmp r0, r1
	blo _0807C59C
	strb r5, [r3]
	ldrb r0, [r4]
	adds r0, #1
	strb r0, [r4]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _0807C574
	strb r5, [r4]
_0807C574:
	ldr r3, _0807C5AC @ =0x05000194
	ldrb r0, [r4]
	lsls r0, r0, #4
	adds r0, #0xa
	adds r2, r0, #0
	movs r1, #0
	ldr r4, _0807C5B0 @ =0x0857BDB4 (sBlob_5766D4_after+0xEC)
_0807C582:
	lsls r0, r2, #1
	adds r0, r0, r4
	ldrh r0, [r0]
	strh r0, [r3]
	adds r0, r1, #1
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	adds r0, r2, #1
	lsls r0, r0, #0x10
	lsrs r2, r0, #0x10
	adds r3, #2
	cmp r1, #5
	bls _0807C582
_0807C59C:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_0807C5A4: .4byte 0x0000022D
_0807C5A8: .4byte sCharacterWidths+0x5C88
_0807C5AC: .4byte 0x05000194
_0807C5B0: .4byte sCharacterWidths+0x5B80

	thumb_func_start NavigationConversationLoadSpecialGraphics
NavigationConversationLoadSpecialGraphics: @ 0x0807C5B4
	push {lr}
	ldr r0, _0807C5F0 @ =gNonGameplayRam
	movs r1, #0x88
	lsls r1, r1, #2
	adds r0, r0, r1
	ldrb r0, [r0]
	cmp r0, #0x35
	bne _0807C618
	ldr r0, _0807C5F4 @ =0x0857C0C4 (sBlob_5766D4_after+0x3FC)
	movs r1, #0x80
	lsls r1, r1, #0x12
	bl LZ77UncompVram
	ldr r0, _0807C5F8 @ =0x0857FCA0 (sBlob_5766D4_after+0x3FD8)
	ldr r1, _0807C5FC @ =0x02006000
	bl LZ77UncompVram
	ldr r0, _0807C600 @ =0x08580238 (sBlob_5766D4_after+0x4570)
	ldr r1, _0807C604 @ =0x02006800
	bl LZ77UncompVram
	ldr r0, _0807C608 @ =0x085807D0 (sBlob_5766D4_after+0x4B08)
	ldr r1, _0807C60C @ =0x02007000
	bl LZ77UncompVram
	ldr r0, _0807C610 @ =0x08580D68 (sBlob_5766D4_after+0x50A0)
	ldr r1, _0807C614 @ =0x02007800
	bl LZ77UncompVram
	b _0807C626
	.align 2, 0
_0807C5F0: .4byte gNonGameplayRam
_0807C5F4: .4byte sCharacterWidths+0x5E90
_0807C5F8: .4byte sCharacterWidths+0x9A6C
_0807C5FC: .4byte 0x02006000
_0807C600: .4byte sCharacterWidths+0xA004
_0807C604: .4byte 0x02006800
_0807C608: .4byte sCharacterWidths+0xA59C
_0807C60C: .4byte 0x02007000
_0807C610: .4byte sCharacterWidths+0xAB34
_0807C614: .4byte 0x02007800
_0807C618:
	cmp r0, #0xe
	bne _0807C626
	ldr r0, _0807C62C @ =0x0872F2E0 (sSaXCloseUpGfx)
	movs r1, #0x80
	lsls r1, r1, #0x12
	bl LZ77UncompVram
_0807C626:
	pop {r0}
	bx r0
	.align 2, 0
_0807C62C: .4byte sSaXCloseUpGfx

	thumb_func_start unk_7c630
unk_7c630: @ 0x0807C630
	push {r4, lr}
	sub sp, #4
	ldr r1, _0807C650 @ =gNonGameplayRam
	ldr r2, _0807C654 @ =0x00000265
	adds r0, r1, r2
	ldrb r0, [r0]
	adds r4, r1, #0
	cmp r0, #0x25
	bls _0807C646
	bl _0807CE56
_0807C646:
	lsls r0, r0, #2
	ldr r1, _0807C658 @ =_0807C65C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807C650: .4byte gNonGameplayRam
_0807C654: .4byte 0x00000265
_0807C658: .4byte _0807C65C
_0807C65C: @ jump table
	.4byte _0807C6F4 @ case 0
	.4byte _0807C770 @ case 1
	.4byte _0807C79C @ case 2
	.4byte _0807C7B8 @ case 3
	.4byte _0807C7E4 @ case 4
	.4byte _0807C810 @ case 5
	.4byte _0807C82C @ case 6
	.4byte _0807C858 @ case 7
	.4byte _0807C884 @ case 8
	.4byte _0807C8A0 @ case 9
	.4byte _0807C8CC @ case 10
	.4byte _0807C924 @ case 11
	.4byte _0807C940 @ case 12
	.4byte _0807C970 @ case 13
	.4byte _0807C99C @ case 14
	.4byte _0807C9C8 @ case 15
	.4byte _0807C9F0 @ case 16
	.4byte _0807CA10 @ case 17
	.4byte _0807CA50 @ case 18
	.4byte _0807CA90 @ case 19
	.4byte _0807CAD0 @ case 20
	.4byte _0807CAFC @ case 21
	.4byte _0807CB20 @ case 22
	.4byte _0807CB58 @ case 23
	.4byte _0807CBB0 @ case 24
	.4byte _0807CBE0 @ case 25
	.4byte _0807CC18 @ case 26
	.4byte _0807CC4C @ case 27
	.4byte _0807CC70 @ case 28
	.4byte _0807CC9C @ case 29
	.4byte _0807CCC8 @ case 30
	.4byte _0807CCE4 @ case 31
	.4byte _0807CD30 @ case 32
	.4byte _0807CD5C @ case 33
	.4byte _0807CD78 @ case 34
	.4byte _0807CDA4 @ case 35
	.4byte _0807CDD0 @ case 36
	.4byte _0807CE10 @ case 37
_0807C6F4:
	movs r0, #0x80
	lsls r0, r0, #0x13
	ldrh r1, [r0]
	ldr r3, _0807C74C @ =0x0000026A
	adds r0, r4, r3
	movs r2, #0
	strh r1, [r0]
	ldr r0, _0807C750 @ =0x0400000E
	ldrh r1, [r0]
	adds r3, #2
	adds r0, r4, r3
	strh r1, [r0]
	ldr r0, _0807C754 @ =0x0400000C
	ldrh r1, [r0]
	adds r3, #2
	adds r0, r4, r3
	strh r1, [r0]
	ldr r0, _0807C758 @ =0x04000050
	ldrh r1, [r0]
	adds r3, #2
	adds r0, r4, r3
	strh r1, [r0]
	ldr r0, _0807C75C @ =0x04000052
	ldrh r1, [r0]
	adds r3, #2
	adds r0, r4, r3
	strh r1, [r0]
	movs r1, #0x9a
	lsls r1, r1, #2
	adds r0, r4, r1
	strh r2, [r0]
	ldr r1, _0807C760 @ =0x040000D4
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r1]
	ldr r0, _0807C764 @ =0x02035000
	str r0, [r1, #4]
	ldr r0, _0807C768 @ =0x80000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r2, _0807C76C @ =0x00000265
	adds r1, r4, r2
	b _0807CDEE
	.align 2, 0
_0807C74C: .4byte 0x0000026A
_0807C750: .4byte 0x0400000E
_0807C754: .4byte 0x0400000C
_0807C758: .4byte 0x04000050
_0807C75C: .4byte 0x04000052
_0807C760: .4byte 0x040000D4
_0807C764: .4byte 0x02035000
_0807C768: .4byte 0x80000100
_0807C76C: .4byte 0x00000265
_0807C770:
	ldr r1, _0807C78C @ =0x06004000
	ldr r2, _0807C790 @ =0x02008000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C794 @ =gNonGameplayRam
	ldr r3, _0807C798 @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807C78C: .4byte 0x06004000
_0807C790: .4byte 0x02008000
_0807C794: .4byte gNonGameplayRam
_0807C798: .4byte 0x00000265
_0807C79C:
	ldr r1, _0807C7B0 @ =0x06005000
	ldr r2, _0807C7B4 @ =0x02009000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _0807CDE8
	.align 2, 0
_0807C7B0: .4byte 0x06005000
_0807C7B4: .4byte 0x02009000
_0807C7B8:
	ldr r1, _0807C7D4 @ =0x06006000
	ldr r2, _0807C7D8 @ =0x0200A000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C7DC @ =gNonGameplayRam
	ldr r2, _0807C7E0 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807C7D4: .4byte 0x06006000
_0807C7D8: .4byte 0x0200A000
_0807C7DC: .4byte gNonGameplayRam
_0807C7E0: .4byte 0x00000265
_0807C7E4:
	ldr r1, _0807C800 @ =0x06007000
	ldr r2, _0807C804 @ =0x0200B000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C808 @ =gNonGameplayRam
	ldr r3, _0807C80C @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807C800: .4byte 0x06007000
_0807C804: .4byte 0x0200B000
_0807C808: .4byte gNonGameplayRam
_0807C80C: .4byte 0x00000265
_0807C810:
	movs r1, #0x80
	lsls r1, r1, #0x12
	ldr r2, _0807C828 @ =0x06004000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _0807CDE8
	.align 2, 0
_0807C828: .4byte 0x06004000
_0807C82C:
	ldr r1, _0807C848 @ =0x02001000
	ldr r2, _0807C84C @ =0x06005000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C850 @ =gNonGameplayRam
	ldr r2, _0807C854 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807C848: .4byte 0x02001000
_0807C84C: .4byte 0x06005000
_0807C850: .4byte gNonGameplayRam
_0807C854: .4byte 0x00000265
_0807C858:
	ldr r1, _0807C874 @ =0x02002000
	ldr r2, _0807C878 @ =0x06006000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C87C @ =gNonGameplayRam
	ldr r3, _0807C880 @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807C874: .4byte 0x02002000
_0807C878: .4byte 0x06006000
_0807C87C: .4byte gNonGameplayRam
_0807C880: .4byte 0x00000265
_0807C884:
	ldr r1, _0807C898 @ =0x02003000
	ldr r2, _0807C89C @ =0x06007000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _0807CDE8
	.align 2, 0
_0807C898: .4byte 0x02003000
_0807C89C: .4byte 0x06007000
_0807C8A0:
	ldr r1, _0807C8BC @ =0x02004000
	ldr r2, _0807C8C0 @ =0x06008000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C8C4 @ =gNonGameplayRam
	ldr r2, _0807C8C8 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807C8BC: .4byte 0x02004000
_0807C8C0: .4byte 0x06008000
_0807C8C4: .4byte gNonGameplayRam
_0807C8C8: .4byte 0x00000265
_0807C8CC:
	ldr r1, _0807C8F8 @ =0x02005000
	ldr r2, _0807C8FC @ =0x06009000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r4, #0x10
	str r4, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r2, _0807C900 @ =gNonGameplayRam
	movs r3, #0x88
	lsls r3, r3, #2
	adds r0, r2, r3
	ldrb r0, [r0]
	cmp r0, #0x35
	bne _0807C908
	ldr r0, _0807C904 @ =0x00000265
	adds r1, r2, r0
	movs r0, #0xd
	strb r0, [r1]
	b _0807CE56
	.align 2, 0
_0807C8F8: .4byte 0x02005000
_0807C8FC: .4byte 0x06009000
_0807C900: .4byte gNonGameplayRam
_0807C904: .4byte 0x00000265
_0807C908:
	ldr r1, _0807C918 @ =gWrittenToBldalpha_Evb
	movs r0, #0
	strh r0, [r1]
	ldr r0, _0807C91C @ =gWrittenToBldalpha_Eva
	strh r4, [r0]
	ldr r3, _0807C920 @ =0x00000265
	adds r1, r2, r3
	b _0807CDEE
	.align 2, 0
_0807C918: .4byte gWrittenToBldalpha_Evb
_0807C91C: .4byte gWrittenToBldalpha_Eva
_0807C920: .4byte 0x00000265
_0807C924:
	ldr r1, _0807C938 @ =0x02006000
	ldr r2, _0807C93C @ =0x0600A000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _0807CDE8
	.align 2, 0
_0807C938: .4byte 0x02006000
_0807C93C: .4byte 0x0600A000
_0807C940:
	ldr r1, _0807C960 @ =0x02007000
	ldr r2, _0807C964 @ =0x0600B000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r0, _0807C968 @ =gNonGameplayRam
	ldr r1, _0807C96C @ =0x00000265
	adds r0, r0, r1
	movs r1, #0x15
	strb r1, [r0]
	b _0807CE56
	.align 2, 0
_0807C960: .4byte 0x02007000
_0807C964: .4byte 0x0600B000
_0807C968: .4byte gNonGameplayRam
_0807C96C: .4byte 0x00000265
_0807C970:
	ldr r1, _0807C98C @ =0x02006000
	ldr r2, _0807C990 @ =0x0600A000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C994 @ =gNonGameplayRam
	ldr r2, _0807C998 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807C98C: .4byte 0x02006000
_0807C990: .4byte 0x0600A000
_0807C994: .4byte gNonGameplayRam
_0807C998: .4byte 0x00000265
_0807C99C:
	ldr r1, _0807C9B8 @ =0x02007000
	ldr r2, _0807C9BC @ =0x0600B000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807C9C0 @ =gNonGameplayRam
	ldr r3, _0807C9C4 @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807C9B8: .4byte 0x02007000
_0807C9BC: .4byte 0x0600B000
_0807C9C0: .4byte gNonGameplayRam
_0807C9C4: .4byte 0x00000265
_0807C9C8:
	ldr r1, _0807C9E0 @ =0x040000D4
	ldr r0, _0807C9E4 @ =0x0857BEC4 (sBlob_5766D4_after+0x1FC)
	str r0, [r1]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _0807C9E8 @ =0x80000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _0807C9EC @ =PauseScreenVBLank_Unused
	b _0807CDE4
	.align 2, 0
_0807C9E0: .4byte 0x040000D4
_0807C9E4: .4byte sCharacterWidths+0x5C90
_0807C9E8: .4byte 0x80000100
_0807C9EC: .4byte PauseScreenVBLank_Unused
_0807C9F0:
	ldr r1, _0807CA08 @ =0x0300000A
	ldr r2, _0807CA0C @ =0x00001407
	adds r0, r2, #0
	strh r0, [r1]
	movs r3, #0x9a
	lsls r3, r3, #2
	adds r2, r4, r3
	ldrh r1, [r2]
	movs r3, #0x80
	lsls r3, r3, #4
	b _0807CB7C
	.align 2, 0
_0807CA08: .4byte 0x0300000A
_0807CA0C: .4byte 0x00001407
_0807CA10:
	ldr r3, _0807CA3C @ =0x00000266
	adds r2, r4, r3
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r1, _0807CA40 @ =0x0879C17C (sBlob_79c170_79c27c+0xC)
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1]
	cmp r0, r1
	bhi _0807CA28
	b _0807CE56
_0807CA28:
	ldr r1, _0807CA44 @ =0x0300000A
	ldr r3, _0807CA48 @ =0x00001507
	adds r0, r3, #0
	strh r0, [r1]
	ldr r0, _0807CA4C @ =0x00000265
	adds r1, r4, r0
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	b _0807CC38
	.align 2, 0
_0807CA3C: .4byte 0x00000266
_0807CA40: .4byte sExploredMinimapBitFlags+0x3A0
_0807CA44: .4byte 0x0300000A
_0807CA48: .4byte 0x00001507
_0807CA4C: .4byte 0x00000265
_0807CA50:
	ldr r1, _0807CA7C @ =0x00000266
	adds r2, r4, r1
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r1, _0807CA80 @ =0x0879C17C (sBlob_79c170_79c27c+0xC)
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1, #1]
	cmp r0, r1
	bhi _0807CA68
	b _0807CE56
_0807CA68:
	ldr r1, _0807CA84 @ =0x0300000A
	ldr r3, _0807CA88 @ =0x00001607
	adds r0, r3, #0
	strh r0, [r1]
	ldr r0, _0807CA8C @ =0x00000265
	adds r1, r4, r0
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	b _0807CC38
	.align 2, 0
_0807CA7C: .4byte 0x00000266
_0807CA80: .4byte sExploredMinimapBitFlags+0x3A0
_0807CA84: .4byte 0x0300000A
_0807CA88: .4byte 0x00001607
_0807CA8C: .4byte 0x00000265
_0807CA90:
	ldr r1, _0807CABC @ =0x00000266
	adds r2, r4, r1
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r1, _0807CAC0 @ =0x0879C17C (sBlob_79c170_79c27c+0xC)
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1, #2]
	cmp r0, r1
	bhi _0807CAA8
	b _0807CE56
_0807CAA8:
	ldr r1, _0807CAC4 @ =0x0300000A
	ldr r3, _0807CAC8 @ =0x00001707
	adds r0, r3, #0
	strh r0, [r1]
	ldr r0, _0807CACC @ =0x00000265
	adds r1, r4, r0
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	b _0807CC38
	.align 2, 0
_0807CABC: .4byte 0x00000266
_0807CAC0: .4byte sExploredMinimapBitFlags+0x3A0
_0807CAC4: .4byte 0x0300000A
_0807CAC8: .4byte 0x00001707
_0807CACC: .4byte 0x00000265
_0807CAD0:
	ldr r1, _0807CAF0 @ =0x00000266
	adds r2, r4, r1
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r1, _0807CAF4 @ =0x0879C17C (sBlob_79c170_79c27c+0xC)
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1, #3]
	cmp r0, r1
	bhi _0807CAE8
	b _0807CE56
_0807CAE8:
	ldr r3, _0807CAF8 @ =0x00000265
	adds r0, r4, r3
	b _0807CC34
	.align 2, 0
_0807CAF0: .4byte 0x00000266
_0807CAF4: .4byte sExploredMinimapBitFlags+0x3A0
_0807CAF8: .4byte 0x00000265
_0807CAFC:
	ldr r0, _0807CB10 @ =0x087338C0 (sSaXCloseUpTileTable1)
	ldr r1, _0807CB14 @ =0x06007800
	bl LZ77UncompVram
	ldr r0, _0807CB18 @ =0x08733D58 (sSaXCloseUpTileTable2)
	ldr r1, _0807CB1C @ =0x0600B800
	bl LZ77UncompVram
	b _0807CDE8
	.align 2, 0
_0807CB10: .4byte sSaXCloseUpTileTable1
_0807CB14: .4byte 0x06007800
_0807CB18: .4byte sSaXCloseUpTileTable2
_0807CB1C: .4byte 0x0600B800
_0807CB20:
	ldr r1, _0807CB40 @ =0x040000D4
	ldr r0, _0807CB44 @ =0x0872F0E0 (sSaXCloseUpPalGrayscale)
	str r0, [r1]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _0807CB48 @ =0x80000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _0807CB4C @ =PauseScreenVBLank_Unused
	bl CallbackSetVBlank
	ldr r1, _0807CB50 @ =gNonGameplayRam
	ldr r2, _0807CB54 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807CB40: .4byte 0x040000D4
_0807CB44: .4byte sSaXCloseUpPalGrayscale
_0807CB48: .4byte 0x80000100
_0807CB4C: .4byte PauseScreenVBLank_Unused
_0807CB50: .4byte gNonGameplayRam
_0807CB54: .4byte 0x00000265
_0807CB58:
	ldr r1, _0807CB98 @ =0x0400000C
	ldr r3, _0807CB9C @ =0x00000F06
	adds r0, r3, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _0807CBA0 @ =0x00001707
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #0x42
	ldr r3, _0807CBA4 @ =0x00000844
	adds r0, r3, #0
	strh r0, [r1]
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r4, r0
	ldrh r1, [r2]
	movs r3, #0xc0
	lsls r3, r3, #4
_0807CB7C:
	adds r0, r3, #0
	movs r3, #0
	orrs r0, r1
	strh r0, [r2]
	ldr r0, _0807CBA8 @ =0x00000265
	adds r1, r4, r0
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	ldr r1, _0807CBAC @ =0x00000266
	adds r0, r4, r1
	strb r3, [r0]
	b _0807CE56
	.align 2, 0
_0807CB98: .4byte 0x0400000C
_0807CB9C: .4byte 0x00000F06
_0807CBA0: .4byte 0x00001707
_0807CBA4: .4byte 0x00000844
_0807CBA8: .4byte 0x00000265
_0807CBAC: .4byte 0x00000266
_0807CBB0:
	ldr r3, _0807CBD4 @ =0x00000266
	adds r2, r4, r3
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r1, _0807CBD8 @ =0x0873421C (sSaXCloseUpDurations)
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1]
	cmp r0, r1
	bhi _0807CBC8
	b _0807CE56
_0807CBC8:
	ldr r1, _0807CBDC @ =0x00000265
	adds r0, r4, r1
	ldrb r1, [r0]
	adds r1, #1
	b _0807CC36
	.align 2, 0
_0807CBD4: .4byte 0x00000266
_0807CBD8: .4byte sSaXCloseUpDurations
_0807CBDC: .4byte 0x00000265
_0807CBE0:
	ldr r1, _0807CBF8 @ =gWrittenToBldalpha_Eva
	ldrh r0, [r1]
	adds r2, r0, #0
	cmp r2, #0
	bne _0807CC04
	ldr r3, _0807CBFC @ =0x00000265
	adds r0, r4, r3
	ldrb r1, [r0]
	adds r1, #1
	strb r1, [r0]
	ldr r1, _0807CC00 @ =0x00000266
	b _0807CE52
	.align 2, 0
_0807CBF8: .4byte gWrittenToBldalpha_Eva
_0807CBFC: .4byte 0x00000265
_0807CC00: .4byte 0x00000266
_0807CC04:
	subs r0, #1
	strh r0, [r1]
	ldr r2, _0807CC14 @ =gWrittenToBldalpha_Evb
	movs r1, #0x10
	subs r1, r1, r0
	strh r1, [r2]
	b _0807CE56
	.align 2, 0
_0807CC14: .4byte gWrittenToBldalpha_Evb
_0807CC18:
	ldr r3, _0807CC40 @ =0x00000266
	adds r2, r4, r3
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldr r1, _0807CC44 @ =0x0873421C (sSaXCloseUpDurations)
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	ldrb r1, [r1, #1]
	cmp r0, r1
	bhi _0807CC30
	b _0807CE56
_0807CC30:
	ldr r1, _0807CC48 @ =0x00000265
	adds r0, r4, r1
_0807CC34:
	movs r1, #0x1b
_0807CC36:
	strb r1, [r0]
_0807CC38:
	movs r0, #0
	strb r0, [r2]
	b _0807CE56
	.align 2, 0
_0807CC40: .4byte 0x00000266
_0807CC44: .4byte sSaXCloseUpDurations
_0807CC48: .4byte 0x00000265
_0807CC4C:
	movs r2, #0x9a
	lsls r2, r2, #2
	adds r1, r4, r2
	movs r2, #0
	movs r0, #0
	strh r0, [r1]
	ldr r3, _0807CC68 @ =0x00000265
	adds r1, r4, r3
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	ldr r1, _0807CC6C @ =0x00000266
	b _0807CE52
	.align 2, 0
_0807CC68: .4byte 0x00000265
_0807CC6C: .4byte 0x00000266
_0807CC70:
	ldr r1, _0807CC8C @ =0x08561FA8 (sMinimapTilesGfx)
	ldr r2, _0807CC90 @ =0x06008000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807CC94 @ =gNonGameplayRam
	ldr r2, _0807CC98 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807CC8C: .4byte sMinimapTilesGfx
_0807CC90: .4byte 0x06008000
_0807CC94: .4byte gNonGameplayRam
_0807CC98: .4byte 0x00000265
_0807CC9C:
	ldr r1, _0807CCB8 @ =0x08562FA8 (sMinimapTilesGfx+0x1000)
	ldr r2, _0807CCBC @ =0x06009000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807CCC0 @ =gNonGameplayRam
	ldr r3, _0807CCC4 @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807CCB8: .4byte sMinimapTilesGfx+0x1000
_0807CCBC: .4byte 0x06009000
_0807CCC0: .4byte gNonGameplayRam
_0807CCC4: .4byte 0x00000265
_0807CCC8:
	ldr r1, _0807CCDC @ =0x08563FA8 (sMinimapTilesGfx+0x2000)
	ldr r2, _0807CCE0 @ =0x0600A000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _0807CDE8
	.align 2, 0
_0807CCDC: .4byte sMinimapTilesGfx+0x2000
_0807CCE0: .4byte 0x0600A000
_0807CCE4:
	ldr r1, _0807CD10 @ =0x08564FA8 (sMinimapTilesGfx+0x3000)
	ldr r2, _0807CD14 @ =0x0600B000
	movs r3, #0x80
	lsls r3, r3, #4
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807CD18 @ =0x040000D4
	ldr r0, _0807CD1C @ =0x06009800
	str r0, [r1]
	ldr r0, _0807CD20 @ =0x06009400
	str r0, [r1, #4]
	ldr r0, _0807CD24 @ =0x80000200
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r1, _0807CD28 @ =gNonGameplayRam
	ldr r2, _0807CD2C @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807CD10: .4byte sMinimapTilesGfx+0x3000
_0807CD14: .4byte 0x0600B000
_0807CD18: .4byte 0x040000D4
_0807CD1C: .4byte 0x06009800
_0807CD20: .4byte 0x06009400
_0807CD24: .4byte 0x80000200
_0807CD28: .4byte gNonGameplayRam
_0807CD2C: .4byte 0x00000265
_0807CD30:
	ldr r1, _0807CD4C @ =0x02008000
	ldr r2, _0807CD50 @ =0x06004000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807CD54 @ =gNonGameplayRam
	ldr r3, _0807CD58 @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807CD4C: .4byte 0x02008000
_0807CD50: .4byte 0x06004000
_0807CD54: .4byte gNonGameplayRam
_0807CD58: .4byte 0x00000265
_0807CD5C:
	ldr r1, _0807CD70 @ =0x02009000
	ldr r2, _0807CD74 @ =0x06005000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _0807CDE8
	.align 2, 0
_0807CD70: .4byte 0x02009000
_0807CD74: .4byte 0x06005000
_0807CD78:
	ldr r1, _0807CD94 @ =0x0200A000
	ldr r2, _0807CD98 @ =0x06006000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807CD9C @ =gNonGameplayRam
	ldr r2, _0807CDA0 @ =0x00000265
	adds r1, r1, r2
	b _0807CDEE
	.align 2, 0
_0807CD94: .4byte 0x0200A000
_0807CD98: .4byte 0x06006000
_0807CD9C: .4byte gNonGameplayRam
_0807CDA0: .4byte 0x00000265
_0807CDA4:
	ldr r1, _0807CDC0 @ =0x0200B000
	ldr r2, _0807CDC4 @ =0x06007000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _0807CDC8 @ =gNonGameplayRam
	ldr r3, _0807CDCC @ =0x00000265
	adds r1, r1, r3
	b _0807CDEE
	.align 2, 0
_0807CDC0: .4byte 0x0200B000
_0807CDC4: .4byte 0x06007000
_0807CDC8: .4byte gNonGameplayRam
_0807CDCC: .4byte 0x00000265
_0807CDD0:
	ldr r1, _0807CDF8 @ =0x040000D4
	ldr r0, _0807CDFC @ =0x02035000
	str r0, [r1]
	movs r0, #0xa0
	lsls r0, r0, #0x13
	str r0, [r1, #4]
	ldr r0, _0807CE00 @ =0x80000100
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	ldr r0, _0807CE04 @ =PauseScreenVBLank
_0807CDE4:
	bl CallbackSetVBlank
_0807CDE8:
	ldr r1, _0807CE08 @ =gNonGameplayRam
	ldr r0, _0807CE0C @ =0x00000265
	adds r1, r1, r0
_0807CDEE:
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	b _0807CE56
	.align 2, 0
_0807CDF8: .4byte 0x040000D4
_0807CDFC: .4byte 0x02035000
_0807CE00: .4byte 0x80000100
_0807CE04: .4byte PauseScreenVBLank
_0807CE08: .4byte gNonGameplayRam
_0807CE0C: .4byte 0x00000265
_0807CE10:
	ldr r1, _0807CE60 @ =0x0400000E
	movs r2, #0x9b
	lsls r2, r2, #2
	adds r0, r4, r2
	ldrh r0, [r0]
	strh r0, [r1]
	subs r1, #2
	ldr r3, _0807CE64 @ =0x0000026E
	adds r0, r4, r3
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #0x44
	adds r2, #4
	adds r0, r4, r2
	ldrh r0, [r0]
	strh r0, [r1]
	adds r1, #2
	adds r3, #4
	adds r0, r4, r3
	ldrh r0, [r0]
	strh r0, [r1]
	ldr r1, _0807CE68 @ =0x0000026A
	adds r0, r4, r1
	ldrh r1, [r0]
	subs r2, #8
	adds r0, r4, r2
	movs r2, #0
	strh r1, [r0]
	subs r3, #0xd
	adds r0, r4, r3
	strb r2, [r0]
	movs r1, #0x99
	lsls r1, r1, #2
_0807CE52:
	adds r0, r4, r1
	strb r2, [r0]
_0807CE56:
	add sp, #4
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0807CE60: .4byte 0x0400000E
_0807CE64: .4byte 0x0000026E
_0807CE68: .4byte 0x0000026A

	thumb_func_start unk_7ce6c
unk_7ce6c: @ 0x0807CE6C
	push {r4, r5, r6, lr}
	sub sp, #4
	ldr r3, _0807CEBC @ =gCurrentArea
	ldrb r0, [r3]
	cmp r0, #6
	bls _0807CE7A
	b _0807CF8A
_0807CE7A:
	ldr r2, _0807CEC0 @ =gNonGameplayRam
	movs r0, #0x90
	lsls r0, r0, #2
	adds r1, r2, r0
	ldr r0, _0807CEC4 @ =0x08581500 (sBlob_5766D4_after+0x5838)
	ldm r0!, {r4, r5, r6}
	stm r1!, {r4, r5, r6}
	ldr r0, [r0]
	str r0, [r1]
	ldrb r0, [r2]
	adds r6, r2, #0
	cmp r0, #0
	beq _0807CF8A
	ldr r0, _0807CEC8 @ =gPauseScreenFlag
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	beq _0807CF8A
	ldrb r0, [r3]
	cmp r0, #0
	beq _0807CED4
	ldr r2, _0807CECC @ =0x0857607D (sEvent_57607D)
	ldr r1, _0807CED0 @ =0x08576073 (sEvent_576073)
	adds r0, r0, r1
	ldrb r0, [r0]
	adds r0, r0, r2
	ldrb r1, [r0]
	movs r2, #0x91
	lsls r2, r2, #2
	adds r0, r6, r2
	b _0807CEDE
	.align 2, 0
_0807CEBC: .4byte gCurrentArea
_0807CEC0: .4byte gNonGameplayRam
_0807CEC4: .4byte sCharacterWidths+0xB2CC
_0807CEC8: .4byte gPauseScreenFlag
_0807CECC: .4byte sEvent_57607D
_0807CED0: .4byte sEvent_576073
_0807CED4:
	ldr r0, _0807CF48 @ =0x0857607D (sEvent_57607D)
	ldrb r1, [r0, #7]
	movs r4, #0x91
	lsls r4, r4, #2
	adds r0, r6, r4
_0807CEDE:
	strb r1, [r0]
	ldr r1, _0807CF4C @ =0x0879C180 (sBlob_79c170_79c27c+0x10)
	movs r5, #0x91
	lsls r5, r5, #2
	adds r0, r6, r5
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	adds r0, r0, r1
	ldrb r0, [r0]
	adds r1, r6, #0
	adds r1, #0xc6
	strb r0, [r1]
	subs r1, #8
	movs r0, #0x1c
	strh r0, [r1]
	subs r1, #2
	movs r0, #0x32
	strh r0, [r1]
	adds r2, r6, #0
	adds r2, #0xc7
	ldrb r1, [r2]
	movs r4, #4
	rsbs r4, r4, #0
	adds r0, r4, #0
	ands r0, r1
	movs r5, #1
	orrs r0, r5
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r0, r1
	strb r0, [r2]
	movs r0, #0xa
	movs r1, #0
	bl UpdateMenuOamDataId
	adds r1, r6, #0
	adds r1, #0xaf
	ldrb r0, [r1]
	ands r4, r0
	orrs r4, r5
	strb r4, [r1]
	ldr r2, _0807CF50 @ =gCurrentArea
	ldrb r0, [r2]
	cmp r0, #0
	beq _0807CF5C
	ldr r1, _0807CF54 @ =0x08576073 (sEvent_576073)
	adds r0, r0, r1
	ldrb r1, [r0]
	ldr r2, _0807CF58 @ =0x00000249
	adds r0, r6, r2
	b _0807CF6C
	.align 2, 0
_0807CF48: .4byte sEvent_57607D
_0807CF4C: .4byte sExploredMinimapBitFlags+0x3A4
_0807CF50: .4byte gCurrentArea
_0807CF54: .4byte sEvent_576073
_0807CF58: .4byte 0x00000249
_0807CF5C:
	ldr r1, _0807CF94 @ =0x085760E8 (sBlob_5760e8_576168)
	ldr r0, _0807CF98 @ =gCurrentRoom
	ldrb r0, [r0]
	adds r0, #1
	adds r0, r0, r1
	ldrb r1, [r0]
	ldr r4, _0807CF9C @ =0x00000249
	adds r0, r6, r4
_0807CF6C:
	strb r1, [r0]
	bl unk_7d27c
	mov r1, sp
	ldr r5, _0807CFA0 @ =0x00007A73
	adds r0, r5, #0
	strh r0, [r1]
	ldr r1, _0807CFA4 @ =0x040000D4
	mov r6, sp
	str r6, [r1]
	ldr r0, _0807CFA8 @ =0x05000342
	str r0, [r1, #4]
	ldr r0, _0807CFAC @ =0x8100000C
	str r0, [r1, #8]
	ldr r0, [r1, #8]
_0807CF8A:
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_0807CF94: .4byte sSecurityUnlockEvents+0x20
_0807CF98: .4byte gCurrentRoom
_0807CF9C: .4byte 0x00000249
_0807CFA0: .4byte 0x00007A73
_0807CFA4: .4byte 0x040000D4
_0807CFA8: .4byte 0x05000342
_0807CFAC: .4byte 0x8100000C

	thumb_func_start unk_7cfb0
unk_7cfb0: @ 0x0807CFB0
	push {r4, lr}
	ldr r1, _0807D034 @ =gNonGameplayRam
	ldrb r0, [r1]
	mov ip, r1
	cmp r0, #0
	bne _0807CFBE
	b _0807D270
_0807CFBE:
	ldr r0, _0807D038 @ =gPauseScreenFlag
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	bne _0807CFCC
	b _0807D270
_0807CFCC:
	movs r1, #0x92
	lsls r1, r1, #2
	add r1, ip
	ldrb r0, [r1]
	adds r0, #1
	movs r2, #0
	strb r0, [r1]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #7
	bls _0807D014
	strb r2, [r1]
	ldr r3, _0807D03C @ =0x00000247
	add r3, ip
	ldrb r0, [r3]
	adds r0, #1
	strb r0, [r3]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #5
	bls _0807CFF8
	strb r2, [r3]
_0807CFF8:
	ldr r0, _0807D040 @ =0x00000249
	add r0, ip
	ldrb r4, [r0]
	lsls r1, r4, #1
	ldr r0, _0807D044 @ =0x05000340
	adds r1, r1, r0
	ldr r2, _0807D048 @ =0x08581300 (sBlob_5766D4_after+0x5638)
	ldrb r0, [r3]
	lsls r0, r0, #4
	adds r0, r0, r4
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrh r0, [r0]
	strh r0, [r1]
_0807D014:
	ldr r1, _0807D04C @ =0x0000024A
	add r1, ip
	ldrb r0, [r1]
	cmp r0, #2
	bne _0807D050
	movs r0, #3
	strb r0, [r1]
	mov r1, ip
	adds r1, #0xa6
	movs r0, #0x1c
	strh r0, [r1]
	subs r1, #2
	movs r0, #0x32
	strh r0, [r1]
	b _0807D0DA
	.align 2, 0
_0807D034: .4byte gNonGameplayRam
_0807D038: .4byte gPauseScreenFlag
_0807D03C: .4byte 0x00000247
_0807D040: .4byte 0x00000249
_0807D044: .4byte 0x05000340
_0807D048: .4byte sCharacterWidths+0xB0CC
_0807D04C: .4byte 0x0000024A
_0807D050:
	cmp r0, #3
	bne _0807D0DA
	ldr r0, _0807D090 @ =0x0857608A (sEvent_57608A)
	ldr r1, _0807D094 @ =0x0300004C
	ldrb r1, [r1]
	adds r0, r1, r0
	movs r4, #0
	ldrsb r4, [r0, r4]
	cmp r4, #0
	blt _0807D09C
	movs r0, #0x91
	lsls r0, r0, #2
	add r0, ip
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	adds r4, r4, r0
	cmp r4, #0x23
	ble _0807D078
	subs r4, #0x24
_0807D078:
	mov r1, ip
	adds r1, #0xbe
	ldr r3, _0807D098 @ =0x0879C1A4 (sBlob_79c170_79c27c+0x34)
	lsls r2, r4, #1
	adds r2, r2, r4
	adds r0, r2, r3
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	ldrh r1, [r1]
	adds r0, r0, r1
	b _0807D0B2
	.align 2, 0
_0807D090: .4byte sEvent_57608A
_0807D094: .4byte 0x0300004C
_0807D098: .4byte sExploredMinimapBitFlags+0x3C8
_0807D09C:
	mov r4, ip
	adds r4, #0xbe
	ldr r3, _0807D108 @ =0x0879C210 (sBlob_79c170_79c27c+0xA0)
	lsls r2, r1, #1
	adds r2, r2, r1
	adds r0, r2, r3
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	ldrh r4, [r4]
	adds r0, r0, r4
_0807D0B2:
	mov r1, ip
	adds r1, #0xa6
	strh r0, [r1]
	adds r1, #0x16
	adds r0, r3, #1
	adds r0, r2, r0
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	ldrh r1, [r1]
	adds r0, r0, r1
	mov r1, ip
	adds r1, #0xa4
	strh r0, [r1]
	adds r3, #2
	adds r2, r2, r3
	ldrb r0, [r2]
	adds r0, #0x16
	adds r1, #0xa
	strb r0, [r1]
_0807D0DA:
	movs r2, #0x90
	lsls r2, r2, #2
	add r2, ip
	ldrb r0, [r2]
	cmp r0, #0
	bne _0807D0E8
	b _0807D270
_0807D0E8:
	ldr r0, _0807D10C @ =0x00000242
	add r0, ip
	ldrb r1, [r0]
	adds r1, #1
	strb r1, [r0]
	ldrb r0, [r2]
	subs r0, #1
	cmp r0, #5
	bls _0807D0FC
	b _0807D270
_0807D0FC:
	lsls r0, r0, #2
	ldr r1, _0807D110 @ =_0807D114
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807D108: .4byte sExploredMinimapBitFlags+0x434
_0807D10C: .4byte 0x00000242
_0807D110: .4byte _0807D114
_0807D114: @ jump table
	.4byte _0807D12C @ case 0
	.4byte _0807D142 @ case 1
	.4byte _0807D164 @ case 2
	.4byte _0807D19C @ case 3
	.4byte _0807D1C4 @ case 4
	.4byte _0807D1EC @ case 5
_0807D12C:
	mov r0, ip
	ldrh r1, [r0, #4]
	movs r0, #0x80
	lsls r0, r0, #3
	ands r0, r1
	cmp r0, #0
	bne _0807D13C
	b _0807D270
_0807D13C:
	movs r1, #0x90
	lsls r1, r1, #2
	b _0807D1DE
_0807D142:
	mov r0, ip
	ldrh r1, [r0, #4]
	movs r0, #0x80
	lsls r0, r0, #3
	ands r0, r1
	cmp r0, #0
	beq _0807D152
	b _0807D270
_0807D152:
	ldr r1, _0807D160 @ =0x0000024A
	add r1, ip
	movs r0, #2
	strb r0, [r1]
	movs r1, #0x90
	lsls r1, r1, #2
	b _0807D1B6
	.align 2, 0
_0807D160: .4byte 0x0000024A
_0807D164:
	ldr r1, _0807D194 @ =0x00000242
	add r1, ip
	ldrb r0, [r1]
	cmp r0, #8
	bhi _0807D170
	b _0807D270
_0807D170:
	movs r3, #0
	strb r3, [r1]
	movs r2, #0x91
	lsls r2, r2, #2
	add r2, ip
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #0x23
	ble _0807D18A
	strb r3, [r2]
_0807D18A:
	ldr r1, _0807D198 @ =0x0879C180 (sBlob_79c170_79c27c+0x10)
	movs r0, #0
	ldrsb r0, [r2, r0]
	b _0807D266
	.align 2, 0
_0807D194: .4byte 0x00000242
_0807D198: .4byte sExploredMinimapBitFlags+0x3A4
_0807D19C:
	mov r0, ip
	ldrh r1, [r0, #4]
	movs r0, #0x80
	lsls r0, r0, #3
	ands r0, r1
	cmp r0, #0
	beq _0807D270
	movs r1, #0x90
	lsls r1, r1, #2
	add r1, ip
	movs r0, #5
	strb r0, [r1]
	ldr r1, _0807D1C0 @ =0x00000241
_0807D1B6:
	add r1, ip
	movs r0, #1
	strb r0, [r1]
	b _0807D270
	.align 2, 0
_0807D1C0: .4byte 0x00000241
_0807D1C4:
	mov r0, ip
	ldrh r1, [r0, #4]
	movs r0, #0x80
	lsls r0, r0, #3
	ands r0, r1
	cmp r0, #0
	bne _0807D270
	movs r1, #0x90
	lsls r1, r1, #2
	add r1, ip
	movs r0, #6
	strb r0, [r1]
	ldr r1, _0807D1E8 @ =0x0000024A
_0807D1DE:
	add r1, ip
	movs r0, #2
	strb r0, [r1]
	b _0807D270
	.align 2, 0
_0807D1E8: .4byte 0x0000024A
_0807D1EC:
	movs r2, #0x91
	lsls r2, r2, #2
	add r2, ip
	ldr r0, _0807D21C @ =0x00000245
	add r0, ip
	ldrb r4, [r2]
	movs r1, #0
	ldrsb r1, [r2, r1]
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r1, r0
	bne _0807D224
	movs r1, #0x90
	lsls r1, r1, #2
	add r1, ip
	movs r2, #0
	movs r0, #4
	strb r0, [r1]
	ldr r0, _0807D220 @ =0x00000241
	add r0, ip
	strb r2, [r0]
	b _0807D270
	.align 2, 0
_0807D21C: .4byte 0x00000245
_0807D220: .4byte 0x00000241
_0807D224:
	ldr r1, _0807D248 @ =0x00000242
	add r1, ip
	ldrb r0, [r1]
	cmp r0, #8
	bls _0807D270
	movs r3, #0
	strb r3, [r1]
	ldr r0, _0807D24C @ =0x00000246
	add r0, ip
	ldrb r0, [r0]
	adds r0, r4, r0
	strb r0, [r2]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #0x23
	ble _0807D250
	strb r3, [r2]
	b _0807D258
	.align 2, 0
_0807D248: .4byte 0x00000242
_0807D24C: .4byte 0x00000246
_0807D250:
	cmp r0, #0
	bge _0807D258
	movs r0, #0x23
	strb r0, [r2]
_0807D258:
	ldr r1, _0807D278 @ =0x0879C180 (sBlob_79c170_79c27c+0x10)
	movs r0, #0x91
	lsls r0, r0, #2
	add r0, ip
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
_0807D266:
	adds r0, r0, r1
	ldrb r1, [r0]
	mov r0, ip
	adds r0, #0xc6
	strb r1, [r0]
_0807D270:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0807D278: .4byte sExploredMinimapBitFlags+0x3A4

	thumb_func_start unk_7d27c
unk_7d27c: @ 0x0807D27C
	push {r4, r5, lr}
	ldr r0, _0807D294 @ =0x0300004C
	ldrb r1, [r0]
	adds r5, r0, #0
	cmp r1, #0
	bne _0807D29C
	ldr r0, _0807D298 @ =gNonGameplayRam
	movs r2, #0x90
	lsls r2, r2, #2
	adds r0, r0, r2
	b _0807D33E
	.align 2, 0
_0807D294: .4byte 0x0300004C
_0807D298: .4byte gNonGameplayRam
_0807D29C:
	ldr r0, _0807D2C4 @ =gNonGameplayRam
	movs r2, #0x90
	lsls r2, r2, #2
	adds r1, r0, r2
	movs r4, #1
	strb r4, [r1]
	subs r2, #0x20
	adds r1, r0, r2
	ldr r2, _0807D2C8 @ =gPreviousNavigationConversation
	ldrb r1, [r1]
	adds r3, r0, #0
	ldrb r2, [r2]
	cmp r1, r2
	bne _0807D2D0
	ldr r0, _0807D2CC @ =0x0000024A
	adds r1, r3, r0
	movs r0, #2
	strb r0, [r1]
	b _0807D2D6
	.align 2, 0
_0807D2C4: .4byte gNonGameplayRam
_0807D2C8: .4byte gPreviousNavigationConversation
_0807D2CC: .4byte 0x0000024A
_0807D2D0:
	ldr r1, _0807D324 @ =0x0000024A
	adds r0, r3, r1
	strb r4, [r0]
_0807D2D6:
	ldr r1, _0807D328 @ =0x0857607D (sEvent_57607D)
	ldrb r0, [r5]
	adds r0, r0, r1
	ldrb r1, [r0]
	movs r2, #0
	ldrsb r2, [r0, r2]
	cmp r2, #0
	blt _0807D340
	ldr r0, _0807D32C @ =0x00000245
	adds r5, r3, r0
	strb r1, [r5]
	movs r1, #0x91
	lsls r1, r1, #2
	adds r4, r3, r1
	movs r0, #0
	ldrsb r0, [r4, r0]
	cmp r2, r0
	beq _0807D340
	movs r2, #0x90
	lsls r2, r2, #2
	adds r1, r3, r2
	movs r0, #4
	strb r0, [r1]
	movs r1, #0
	ldrsb r1, [r5, r1]
	movs r0, #0
	ldrsb r0, [r4, r0]
	subs r1, r1, r0
	movs r0, #1
	cmp r1, #0
	bge _0807D316
	subs r0, #2
_0807D316:
	muls r1, r0, r1
	cmp r1, #0x12
	ble _0807D330
	movs r1, #1
	rsbs r1, r1, #0
	b _0807D338
	.align 2, 0
_0807D324: .4byte 0x0000024A
_0807D328: .4byte sEvent_57607D
_0807D32C: .4byte 0x00000245
_0807D330:
	cmp r1, #0x12
	bne _0807D336
	movs r0, #1
_0807D336:
	movs r1, #1
_0807D338:
	muls r1, r0, r1
	ldr r2, _0807D348 @ =0x00000246
	adds r0, r3, r2
_0807D33E:
	strb r1, [r0]
_0807D340:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0807D348: .4byte 0x00000246
