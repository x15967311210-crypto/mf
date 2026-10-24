    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start NavigationConversationHandler
NavigationConversationHandler: @ 0x0807A3A4
	push {r4, r5, r6, r7, lr}
	bl unk_7b674
	bl NavigationConversionScrollToTarget
	bl unk_7b56c
	bl NavigationConversationUpdatePanel
	bl unk_78c44
	movs r7, #0
	ldr r0, _0807A3D4 @ =gNonGameplayRam
	ldrb r0, [r0, #7]
	cmp r0, #0x15
	bls _0807A3C8
	bl _0807AE42
_0807A3C8:
	lsls r0, r0, #2
	ldr r1, _0807A3D8 @ =_0807A3DC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807A3D4: .4byte gNonGameplayRam
_0807A3D8: .4byte _0807A3DC
_0807A3DC: @ jump table
	.4byte _0807A434 @ case 0
	.4byte _0807A468 @ case 1
	.4byte _0807A51A @ case 2
	.4byte _0807A6C0 @ case 3
	.4byte _0807A700 @ case 4
	.4byte _0807A718 @ case 5
	.4byte _0807A76C @ case 6
	.4byte _0807A79E @ case 7
	.4byte _0807A7B0 @ case 8
	.4byte _0807A890 @ case 9
	.4byte _0807A938 @ case 10
	.4byte _0807AA2A @ case 11
	.4byte _0807AA48 @ case 12
	.4byte _0807AA84 @ case 13
	.4byte _0807AAE0 @ case 14
	.4byte _0807AB14 @ case 15
	.4byte _0807AB40 @ case 16
	.4byte _0807ABB4 @ case 17
	.4byte _0807AC28 @ case 18
	.4byte _0807ACAE @ case 19
	.4byte _0807AD6C @ case 20
	.4byte _0807ADE8 @ case 21
_0807A434:
	ldr r4, _0807A454 @ =gNonGameplayRam
	movs r0, #0
	strb r0, [r4, #6]
	bl NavigationConversationSetupOam
	ldr r1, _0807A458 @ =0x00000221
	adds r0, r4, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807A45C
	movs r0, #4
	strb r0, [r4, #0x1c]
	movs r0, #0x11
	strb r0, [r4, #7]
	bl _0807AE42
	.align 2, 0
_0807A454: .4byte gNonGameplayRam
_0807A458: .4byte 0x00000221
_0807A45C:
	strb r0, [r4, #0x1c]
	ldrb r0, [r4, #7]
	adds r0, #1
	strb r0, [r4, #7]
	bl _0807AE42
_0807A468:
	ldr r1, _0807A4D4 @ =gNonGameplayRam
	movs r2, #0x9a
	lsls r2, r2, #2
	adds r3, r1, r2
	ldrh r2, [r3]
	movs r4, #0x80
	lsls r4, r4, #1
	adds r0, r4, #0
	movs r5, #0
	orrs r0, r2
	strh r0, [r3]
	movs r2, #1
	strb r2, [r1, #9]
	strb r2, [r1, #0xb]
	movs r0, #8
	strb r0, [r1, #0x1d]
	strb r5, [r1, #0x1e]
	strb r5, [r1, #0x1f]
	movs r3, #0x88
	lsls r3, r3, #2
	adds r0, r1, r3
	ldrb r0, [r0]
	subs r0, #1
	lsls r3, r0, #1
	ldr r4, _0807A4D8 @ =0x00000221
	adds r0, r1, r4
	ldrb r0, [r0]
	adds r4, r1, #0
	cmp r0, #0
	beq _0807A4A6
	adds r3, #1
_0807A4A6:
	ldr r1, _0807A4DC @ =0x0879C0F0 (sBlob_79bec0_79c128+0x230)
	ldr r0, _0807A4E0 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r1, [r0]
	lsls r0, r3, #2
	adds r0, r0, r1
	ldr r0, [r0]
	ldrh r3, [r0]
	ldr r0, _0807A4E4 @ =0x0000E201
	cmp r3, r0
	bne _0807A4E8
	ldrh r0, [r4, #4]
	movs r1, #2
	orrs r0, r1
	strh r0, [r4, #4]
	strb r2, [r4, #0x18]
	strb r1, [r4, #0x19]
	strb r2, [r4, #0x17]
	b _0807A512
	.align 2, 0
_0807A4D4: .4byte gNonGameplayRam
_0807A4D8: .4byte 0x00000221
_0807A4DC: .4byte sExploredMinimapBitFlags+0x314
_0807A4E0: .4byte 0x03000011
_0807A4E4: .4byte 0x0000E201
_0807A4E8:
	ldr r0, _0807A500 @ =0x0000E202
	cmp r3, r0
	bne _0807A504
	ldrh r0, [r4, #4]
	movs r1, #4
	orrs r0, r1
	strh r0, [r4, #4]
	strb r2, [r4, #0x18]
	movs r0, #2
	strb r0, [r4, #0x19]
	strb r0, [r4, #0x17]
	b _0807A512
	.align 2, 0
_0807A500: .4byte 0x0000E202
_0807A504:
	ldrh r0, [r4, #4]
	movs r1, #1
	orrs r0, r1
	strh r0, [r4, #4]
	strb r5, [r4, #0x18]
	strb r1, [r4, #0x19]
	strb r5, [r4, #0x17]
_0807A512:
	ldrb r0, [r4, #7]
	adds r0, #1
	movs r1, #0
	b _0807AC3E
_0807A51A:
	ldr r1, _0807A584 @ =gNonGameplayRam
	movs r0, #0
	strb r0, [r1, #0x1b]
	ldrb r0, [r1, #0x1c]
	adds r4, r1, #0
	cmp r0, #1
	bne _0807A5B8
	ldr r0, _0807A588 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x83
	ands r0, r1
	cmp r0, #0
	beq _0807A590
	ldrh r1, [r4, #4]
	movs r0, #0x80
	lsls r0, r0, #2
	ands r0, r1
	cmp r0, #0
	bne _0807A59C
	ldr r1, _0807A58C @ =0x00000241
	adds r0, r4, r1
	ldrb r5, [r0]
	cmp r5, #0
	bne _0807A590
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x36
	strb r5, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x34
	strb r5, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x35
	strb r5, [r0]
	movs r0, #0
	bl TextClearGraphics
	movs r0, #3
	strb r0, [r4, #7]
	strb r5, [r4, #6]
	bl _0807AE42
	.align 2, 0
_0807A584: .4byte gNonGameplayRam
_0807A588: .4byte gChangedInput
_0807A58C: .4byte 0x00000241
_0807A590:
	ldrh r1, [r4, #4]
	movs r0, #0x80
	lsls r0, r0, #2
	ands r0, r1
	cmp r0, #0
	beq _0807A5F2
_0807A59C:
	ldrh r1, [r4, #4]
	movs r2, #0x80
	lsls r2, r2, #3
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	beq _0807A5AE
	bl _0807AE42
_0807A5AE:
	adds r0, r2, #0
	orrs r0, r1
	strh r0, [r4, #4]
	bl _0807AE42
_0807A5B8:
	cmp r0, #2
	bne _0807A5E6
	ldrh r1, [r4, #4]
	movs r0, #0x80
	lsls r0, r0, #3
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	bne _0807A5F2
	adds r0, r4, #0
	adds r0, #0x24
	strb r1, [r0]
	adds r2, r4, #0
	adds r2, #0x25
	movs r0, #1
	strb r0, [r2]
	strb r0, [r4, #0x1a]
	strb r1, [r4, #0x1b]
	movs r0, #8
	strb r0, [r4, #7]
	strb r1, [r4, #6]
	b _0807A5F2
_0807A5E6:
	cmp r0, #6
	bne _0807A5EE
	movs r7, #1
	b _0807A5F2
_0807A5EE:
	bl NavigationConversationProcessText
_0807A5F2:
	ldr r3, _0807A628 @ =gNonGameplayRam
	ldrb r0, [r3, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r3
	adds r0, r1, #0
	adds r0, #0x36
	ldrb r0, [r0]
	cmp r0, #3
	bne _0807A630
	movs r0, #0x74
	strh r0, [r1, #0x2e]
	ldrb r0, [r3, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r3
	ldr r2, _0807A62C @ =0x085766E0 (sBlob_5766D4_prefix+0xC)
	ldrb r0, [r3, #0x18]
	lsls r0, r0, #1
	adds r2, #1
	adds r0, r0, r2
	ldrb r0, [r0]
	strh r0, [r1, #0x2c]
	bl _0807AE42
	.align 2, 0
_0807A628: .4byte gNonGameplayRam
_0807A62C: .4byte sCharacterWidths+0x4AC
_0807A630:
	movs r2, #0
	strh r2, [r1, #0x2e]
	ldrb r1, [r3, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r3
	strh r2, [r0, #0x2c]
	ldrb r0, [r3, #0x18]
	lsls r0, r0, #1
	adds r1, r3, #0
	adds r1, #0x12
	adds r0, r0, r1
	ldrh r2, [r0]
	cmp r2, #0xdf
	bls _0807A68C
	ldrb r1, [r3, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r3
	ldr r4, _0807A684 @ =0x0000FF28
	adds r1, r2, r4
	ldrh r2, [r0, #0x2e]
	adds r1, r1, r2
	strh r1, [r0, #0x2e]
	ldrb r0, [r3, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r3
	ldr r2, _0807A688 @ =0x085766E0 (sBlob_5766D4_prefix+0xC)
	ldrb r0, [r3, #0x18]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrb r0, [r0]
	adds r0, #0x10
	ldrh r3, [r1, #0x2c]
	adds r0, r0, r3
	strh r0, [r1, #0x2c]
	bl _0807AE42
	.align 2, 0
_0807A684: .4byte 0x0000FF28
_0807A688: .4byte sCharacterWidths+0x4AC
_0807A68C:
	ldrb r1, [r3, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r3
	adds r1, r2, #0
	adds r1, #8
	ldrh r4, [r0, #0x2e]
	adds r1, r1, r4
	strh r1, [r0, #0x2e]
	ldrb r0, [r3, #0x19]
	lsls r2, r0, #1
	adds r2, r2, r0
	lsls r2, r2, #2
	adds r2, r2, r3
	ldr r0, _0807A6BC @ =0x085766E0 (sBlob_5766D4_prefix+0xC)
	ldrb r1, [r3, #0x18]
	lsls r1, r1, #1
	adds r1, r1, r0
	ldrh r0, [r2, #0x2c]
	ldrb r1, [r1]
	adds r0, r0, r1
	strh r0, [r2, #0x2c]
	b _0807AE42
	.align 2, 0
_0807A6BC: .4byte sCharacterWidths+0x4AC
_0807A6C0:
	ldr r1, _0807A6F4 @ =gNonGameplayRam
	movs r0, #0
	strb r0, [r1, #0x1b]
	movs r2, #0x88
	lsls r2, r2, #2
	adds r0, r1, r2
	ldr r2, _0807A6F8 @ =gPreviousNavigationConversation
	ldrb r0, [r0]
	ldrb r3, [r2]
	cmp r0, r3
	beq _0807A6E6
	strb r0, [r2]
	ldr r4, _0807A6FC @ =0x00000221
	adds r0, r1, r4
	ldrb r0, [r0]
	cmp r0, #0
	bne _0807A6E6
	bl SoundEventUpdateForNavConversation
_0807A6E6:
	ldr r0, _0807A6F4 @ =gNonGameplayRam
	ldrb r1, [r0, #7]
	adds r1, #1
	movs r2, #0
	strb r1, [r0, #7]
	strb r2, [r0, #6]
	b _0807AE42
	.align 2, 0
_0807A6F4: .4byte gNonGameplayRam
_0807A6F8: .4byte gPreviousNavigationConversation
_0807A6FC: .4byte 0x00000221
_0807A700:
	ldr r2, _0807A714 @ =gNonGameplayRam
	ldrb r0, [r2, #6]
	cmp r0, #8
	bhi _0807A70A
	b _0807AE42
_0807A70A:
	ldrb r0, [r2, #7]
	adds r0, #1
	movs r1, #0
	b _0807A798
	.align 2, 0
_0807A714: .4byte gNonGameplayRam
_0807A718:
	ldr r3, _0807A768 @ =gNonGameplayRam
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r3, r0
	ldrh r0, [r2]
	movs r4, #0x80
	lsls r4, r4, #1
	adds r1, r4, #0
	eors r0, r1
	strh r0, [r2]
	ldrh r1, [r3, #4]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _0807A73C
	movs r0, #0x40
	eors r0, r1
	strh r0, [r3, #4]
_0807A73C:
	ldrh r1, [r3, #4]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _0807A74C
	movs r0, #8
	eors r0, r1
	strh r0, [r3, #4]
_0807A74C:
	ldrh r1, [r3, #4]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0807A75C
	movs r0, #0x10
	eors r0, r1
	strh r0, [r3, #4]
_0807A75C:
	ldrb r0, [r3, #7]
	adds r0, #1
	strb r0, [r3, #7]
	movs r0, #0
	strb r0, [r3, #6]
	b _0807AE42
	.align 2, 0
_0807A768: .4byte gNonGameplayRam
_0807A76C:
	ldr r2, _0807A790 @ =gNonGameplayRam
	ldrh r1, [r2, #4]
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	bne _0807A78C
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	bne _0807A78C
	movs r0, #4
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r1, r0, #0x10
	cmp r1, #0
	beq _0807A794
_0807A78C:
	movs r0, #0
	b _0807AE44
	.align 2, 0
_0807A790: .4byte gNonGameplayRam
_0807A794:
	ldrb r0, [r2, #7]
	adds r0, #1
_0807A798:
	strb r0, [r2, #7]
	strb r1, [r2, #6]
	b _0807AE42
_0807A79E:
	movs r7, #1
	ldr r1, _0807A7AC @ =gNonGameplayRam
	movs r0, #0
	strb r0, [r1, #7]
	strb r0, [r1, #6]
	b _0807AE42
	.align 2, 0
_0807A7AC: .4byte gNonGameplayRam
_0807A7B0:
	ldr r5, _0807A818 @ =gNonGameplayRam
	adds r6, r5, #0
	adds r6, #0x24
	ldrb r4, [r6]
	cmp r4, #0
	bne _0807A824
	ldr r0, _0807A81C @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x83
	ands r0, r1
	cmp r0, #0
	bne _0807A7CA
	b _0807AE42
_0807A7CA:
	ldr r0, _0807A820 @ =0x00000203
	bl SoundPlay
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x36
	strb r4, [r0]
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
	movs r0, #1
	bl TextClearGraphics
	movs r0, #1
	strb r0, [r6]
	movs r0, #3
	strb r0, [r5, #0x1c]
	adds r0, r5, #0
	adds r0, #0x20
	strb r4, [r0]
	adds r0, #1
	strb r4, [r0]
	strh r4, [r5, #0x22]
	b _0807AE42
	.align 2, 0
_0807A818: .4byte gNonGameplayRam
_0807A81C: .4byte gChangedInput
_0807A820: .4byte 0x00000203
_0807A824:
	cmp r4, #2
	bne _0807A832
	movs r1, #0
	movs r0, #9
	strb r0, [r5, #7]
	strb r1, [r5, #6]
	b _0807AE42
_0807A832:
	movs r0, #0
	bl unk_7a0fc
	cmp r0, #0
	bne _0807A83E
	b _0807AE42
_0807A83E:
	movs r3, #0
	movs r2, #2
	strb r2, [r6]
	movs r0, #1
	strb r0, [r5, #0x1a]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x36
	strb r2, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x34
	strb r3, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x35
	strb r3, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	movs r1, #0x8c
	strh r1, [r0, #0x2c]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	movs r1, #0x34
	strh r1, [r0, #0x2e]
	b _0807AE42
_0807A890:
	movs r3, #0
	ldr r2, _0807A8C8 @ =gNonGameplayRam
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	movs r5, #0
	movs r1, #0x8c
	strh r1, [r0, #0x2c]
	ldr r0, _0807A8CC @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x20
	ands r0, r1
	adds r4, r2, #0
	cmp r0, #0
	beq _0807A8D0
	adds r5, r4, #0
	adds r5, #0x25
	ldrb r0, [r5]
	movs r2, #1
	eors r0, r2
	rsbs r1, r0, #0
	orrs r1, r0
	lsrs r3, r1, #0x1f
	strb r2, [r5]
	b _0807A8F8
	.align 2, 0
_0807A8C8: .4byte gNonGameplayRam
_0807A8CC: .4byte gChangedInput
_0807A8D0:
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0807A8E8
	adds r1, r4, #0
	adds r1, #0x25
	ldrb r0, [r1]
	cmp r0, #0
	beq _0807A8E4
	movs r3, #1
_0807A8E4:
	strb r5, [r1]
	b _0807A8F8
_0807A8E8:
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _0807A8F8
	movs r3, #2
	movs r0, #0xa
	strb r0, [r4, #7]
	strb r5, [r4, #6]
_0807A8F8:
	adds r0, r4, #0
	adds r0, #0x25
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807A910
	ldrb r0, [r4, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
	movs r0, #0x34
	b _0807A91C
_0807A910:
	ldrb r0, [r4, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
	movs r0, #0x84
_0807A91C:
	strh r0, [r1, #0x2e]
	cmp r3, #1
	bne _0807A924
	b _0807AD3E
_0807A924:
	cmp r3, #2
	beq _0807A92A
	b _0807AE42
_0807A92A:
	adds r0, r4, #0
	adds r0, #0x25
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807A936
	b _0807AD56
_0807A936:
	b _0807AD60
_0807A938:
	ldr r2, _0807A994 @ =gNonGameplayRam
	ldrh r1, [r2, #4]
	movs r0, #0xc0
	ands r0, r1
	adds r4, r2, #0
	cmp r0, #0
	bne _0807AA18
	movs r0, #0x10
	strb r0, [r4, #7]
	adds r0, r4, #0
	adds r0, #0x25
	ldrb r2, [r0]
	cmp r2, #0
	bne _0807A9DA
	ldr r0, _0807A998 @ =0x03000031
	ldrb r1, [r0]
	movs r3, #0x84
	lsls r3, r3, #2
	adds r0, r4, r3
	strb r1, [r0]
	ldr r0, _0807A99C @ =0x03000032
	ldrb r1, [r0]
	adds r3, #1
	adds r0, r4, r3
	strb r1, [r0]
	ldr r1, _0807A9A0 @ =0x00000212
	adds r0, r4, r1
	ldr r1, _0807A9A4 @ =gCurrentArea
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	beq _0807A9A8
	movs r0, #0xb
	strb r0, [r4, #7]
	subs r3, #0x5b
	adds r0, r4, r3
	strb r2, [r0]
	movs r1, #0xda
	lsls r1, r1, #1
	adds r0, r4, r1
	strb r2, [r0]
	subs r3, #1
	adds r0, r4, r3
	strb r2, [r0]
	b _0807A9B8
	.align 2, 0
_0807A994: .4byte gNonGameplayRam
_0807A998: .4byte 0x03000031
_0807A99C: .4byte 0x03000032
_0807A9A0: .4byte 0x00000212
_0807A9A4: .4byte gCurrentArea
_0807A9A8:
	movs r1, #0xd5
	lsls r1, r1, #1
	adds r0, r4, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807A9B8
	movs r0, #0xf
	strb r0, [r4, #7]
_0807A9B8:
	movs r2, #0xd5
	lsls r2, r2, #1
	adds r0, r4, r2
	movs r1, #0
	strb r1, [r0]
	movs r3, #0xd4
	lsls r3, r3, #1
	adds r0, r4, r3
	strb r1, [r0]
	subs r2, #1
	adds r0, r4, r2
	strb r1, [r0]
	movs r2, #0
	strh r1, [r4, #0xc]
	adds r3, #0x71
	adds r0, r4, r3
	strb r2, [r0]
_0807A9DA:
	movs r0, #1
	bl TextClearGraphics
	ldr r2, _0807AA14 @ =gNonGameplayRam
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	adds r0, #0x36
	movs r3, #0
	strb r3, [r0]
	movs r0, #1
	strb r0, [r2, #0x1a]
	ldrb r0, [r2, #0x18]
	lsls r0, r0, #1
	adds r1, r2, #0
	adds r1, #0x12
	adds r0, r0, r1
	movs r4, #0
	strh r3, [r0]
	ldrb r0, [r2, #0x18]
	lsls r0, r0, #1
	subs r1, #4
	adds r0, r0, r1
	strh r3, [r0]
	strb r4, [r2, #0x1c]
	b _0807AE40
	.align 2, 0
_0807AA14: .4byte gNonGameplayRam
_0807AA18:
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	bne _0807AA22
	b _0807AE42
_0807AA22:
	movs r0, #0x40
	eors r0, r1
	strh r0, [r4, #4]
	b _0807AE42
_0807AA2A:
	ldr r1, _0807AA44 @ =gNonGameplayRam
	movs r0, #0x94
	lsls r0, r0, #2
	adds r4, r1, r0
	ldrb r2, [r4]
	movs r0, #1
	movs r3, #0
	orrs r0, r2
	strb r0, [r4]
	strb r3, [r1, #6]
	movs r0, #0xc
	strb r0, [r1, #7]
	b _0807AE42
	.align 2, 0
_0807AA44: .4byte gNonGameplayRam
_0807AA48:
	ldr r5, _0807AA78 @ =gNonGameplayRam
	movs r1, #0x94
	lsls r1, r1, #2
	adds r0, r5, r1
	ldrb r1, [r0]
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	bne _0807AA5C
	b _0807AE42
_0807AA5C:
	ldr r0, _0807AA7C @ =gCurrentArea
	ldrb r1, [r0]
	ldr r2, _0807AA80 @ =0x00000212
	adds r0, r5, r2
	movs r4, #0
	strb r1, [r0]
	movs r0, #1
	bl unk_75988
	strb r4, [r5, #6]
	movs r0, #0xd
	strb r0, [r5, #7]
	b _0807AE42
	.align 2, 0
_0807AA78: .4byte gNonGameplayRam
_0807AA7C: .4byte gCurrentArea
_0807AA80: .4byte 0x00000212
_0807AA84:
	ldr r6, _0807AAC8 @ =gNonGameplayRam
	ldrb r0, [r6, #6]
	cmp r0, #4
	bhi _0807AA8E
	b _0807AE42
_0807AA8E:
	ldr r3, _0807AACC @ =0x00000212
	adds r4, r6, r3
	ldrb r0, [r4]
	ldr r5, _0807AAD0 @ =0x02034000
	adds r1, r5, #0
	bl GetMinimapData
	ldrb r0, [r4]
	bl MinimapSetVisitedTilesAndCollectedItems
	ldr r1, _0807AAD4 @ =0x040000D4
	str r5, [r1]
	ldr r0, _0807AAD8 @ =0x0600E000
	str r0, [r1, #4]
	ldr r0, _0807AADC @ =0x80000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r1, #0
	movs r0, #0xe
	strb r0, [r6, #7]
	strb r1, [r6, #6]
	movs r4, #0x94
	lsls r4, r4, #2
	adds r2, r6, r4
	ldrb r1, [r2]
	movs r0, #8
	orrs r0, r1
	strb r0, [r2]
	b _0807AE42
	.align 2, 0
_0807AAC8: .4byte gNonGameplayRam
_0807AACC: .4byte 0x00000212
_0807AAD0: .4byte 0x02034000
_0807AAD4: .4byte 0x040000D4
_0807AAD8: .4byte 0x0600E000
_0807AADC: .4byte 0x80000400
_0807AAE0:
	ldr r2, _0807AB10 @ =gNonGameplayRam
	movs r1, #0x94
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrb r1, [r0]
	cmp r1, #0
	beq _0807AAF0
	b _0807AE42
_0807AAF0:
	movs r4, #0xdb
	lsls r4, r4, #1
	adds r3, r2, r4
	movs r0, #1
	strb r0, [r3]
	movs r3, #0xda
	lsls r3, r3, #1
	adds r0, r2, r3
	strb r1, [r0]
	subs r4, #1
	adds r0, r2, r4
	strb r1, [r0]
	strb r1, [r2, #6]
	movs r0, #0x10
	strb r0, [r2, #7]
	b _0807AE42
	.align 2, 0
_0807AB10: .4byte gNonGameplayRam
_0807AB14:
	ldr r4, _0807AB38 @ =gNonGameplayRam
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r4, r1
	ldrb r0, [r0]
	ldr r2, _0807AB3C @ =0x00000211
	adds r1, r4, r2
	ldrb r1, [r1]
	bl NavigationConversationScrollMapToDestination
	cmp r0, #0
	bne _0807AB2E
	b _0807AE42
_0807AB2E:
	movs r0, #0
	strb r0, [r4, #6]
	movs r0, #0x10
	strb r0, [r4, #7]
	b _0807AE42
	.align 2, 0
_0807AB38: .4byte gNonGameplayRam
_0807AB3C: .4byte 0x00000211
_0807AB40:
	ldr r4, _0807ABAC @ =gNonGameplayRam
	ldrb r0, [r4, #6]
	cmp r0, #0x10
	bhi _0807AB4A
	b _0807AE42
_0807AB4A:
	movs r0, #0
	bl NavigationConversationUpdateTarget
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r3, #0
	movs r1, #8
	strh r1, [r0, #0x2e]
	ldrb r0, [r4, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
	ldr r2, _0807ABB0 @ =0x085766E0 (sBlob_5766D4_prefix+0xC)
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrb r0, [r0]
	strh r0, [r1, #0x2c]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x36
	movs r1, #0xb
	strb r1, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x34
	strb r3, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x35
	strb r3, [r0]
	movs r0, #1
	strb r0, [r4, #7]
	strb r3, [r4, #6]
	b _0807AE42
	.align 2, 0
_0807ABAC: .4byte gNonGameplayRam
_0807ABB0: .4byte sCharacterWidths+0x4AC
_0807ABB4:
	ldr r5, _0807AC24 @ =gNonGameplayRam
	movs r3, #0x9a
	lsls r3, r3, #2
	adds r1, r5, r3
	ldrh r3, [r1]
	movs r4, #0x80
	lsls r4, r4, #1
	adds r0, r4, #0
	movs r2, #0
	movs r4, #0
	orrs r0, r3
	strh r0, [r1]
	movs r0, #8
	strb r0, [r5, #0x1d]
	strb r2, [r5, #0x1e]
	strb r2, [r5, #0x1f]
	ldrh r0, [r5, #4]
	movs r1, #1
	orrs r0, r1
	strh r0, [r5, #4]
	strb r2, [r5, #0x18]
	strb r1, [r5, #0x19]
	strb r2, [r5, #0x17]
	adds r0, r5, #0
	adds r0, #0x24
	strb r1, [r0]
	adds r0, #0x1e
	strb r2, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x34
	strb r2, [r0]
	ldrb r1, [r5, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x35
	strb r2, [r0]
	adds r0, r5, #0
	adds r0, #0x20
	strb r2, [r0]
	adds r0, #1
	strb r2, [r0]
	strh r4, [r5, #0x22]
	movs r0, #5
	strb r0, [r5, #0x1c]
	ldrb r0, [r5, #7]
	adds r0, #1
	strb r0, [r5, #7]
	strb r2, [r5, #6]
	b _0807AE42
	.align 2, 0
_0807AC24: .4byte gNonGameplayRam
_0807AC28:
	ldr r4, _0807AC44 @ =gNonGameplayRam
	adds r5, r4, #0
	adds r5, #0x24
	ldrb r0, [r5]
	cmp r0, #0
	bne _0807AC36
	b _0807AE42
_0807AC36:
	cmp r0, #2
	bne _0807AC48
	movs r1, #0
	movs r0, #0x13
_0807AC3E:
	strb r0, [r4, #7]
	strb r1, [r4, #6]
	b _0807AE42
	.align 2, 0
_0807AC44: .4byte gNonGameplayRam
_0807AC48:
	movs r0, #1
	bl unk_7a0fc
	cmp r0, #0
	bne _0807AC54
	b _0807AE42
_0807AC54:
	movs r3, #0
	movs r2, #2
	strb r2, [r5]
	movs r0, #1
	strb r0, [r4, #0x1a]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x36
	strb r2, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x34
	strb r3, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x35
	strb r3, [r0]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r2, #0
	movs r1, #0x8c
	strh r1, [r0, #0x2c]
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r1, #0x84
	strh r1, [r0, #0x2e]
	adds r0, r4, #0
	adds r0, #0x25
	strb r2, [r0]
	b _0807AE42
_0807ACAE:
	movs r3, #0
	ldr r2, _0807ACE4 @ =gNonGameplayRam
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	movs r5, #0
	movs r1, #0x8c
	strh r1, [r0, #0x2c]
	ldr r0, _0807ACE8 @ =gChangedInput
	ldrh r1, [r0]
	movs r0, #0x20
	ands r0, r1
	adds r4, r2, #0
	cmp r0, #0
	beq _0807ACEC
	adds r5, r4, #0
	adds r5, #0x25
	ldrb r0, [r5]
	movs r2, #1
	eors r0, r2
	rsbs r1, r0, #0
	orrs r1, r0
	lsrs r3, r1, #0x1f
	strb r2, [r5]
	b _0807AD14
	.align 2, 0
_0807ACE4: .4byte gNonGameplayRam
_0807ACE8: .4byte gChangedInput
_0807ACEC:
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0807AD04
	adds r1, r4, #0
	adds r1, #0x25
	ldrb r0, [r1]
	cmp r0, #0
	beq _0807AD00
	movs r3, #1
_0807AD00:
	strb r5, [r1]
	b _0807AD14
_0807AD04:
	movs r0, #1
	ands r0, r1
	cmp r0, #0
	beq _0807AD14
	movs r3, #2
	movs r0, #0x14
	strb r0, [r4, #7]
	strb r5, [r4, #6]
_0807AD14:
	adds r0, r4, #0
	adds r0, #0x25
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807AD2C
	ldrb r0, [r4, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
	movs r0, #0x34
	b _0807AD38
_0807AD2C:
	ldrb r0, [r4, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r4
	movs r0, #0x84
_0807AD38:
	strh r0, [r1, #0x2e]
	cmp r3, #1
	bne _0807AD48
_0807AD3E:
	movs r0, #0xfd
	lsls r0, r0, #1
	bl SoundPlay
	b _0807AE42
_0807AD48:
	cmp r3, #2
	bne _0807AE42
	adds r0, r4, #0
	adds r0, #0x25
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807AD60
_0807AD56:
	movs r0, #0x81
	lsls r0, r0, #2
	bl SoundPlay
	b _0807AE42
_0807AD60:
	ldr r0, _0807AD68 @ =0x00000205
	bl SoundPlay
	b _0807AE42
	.align 2, 0
_0807AD68: .4byte 0x00000205
_0807AD6C:
	ldr r4, _0807ADDC @ =gNonGameplayRam
	movs r5, #0
	movs r0, #0x15
	strb r0, [r4, #7]
	adds r0, r4, #0
	adds r0, #0x25
	ldrb r0, [r0]
	cmp r0, #1
	bne _0807ADA4
	ldr r1, _0807ADE0 @ =gPreviousNavigationConversation
	movs r0, #0xff
	strb r0, [r1]
	movs r1, #0xd5
	lsls r1, r1, #1
	adds r0, r4, r1
	strb r5, [r0]
	movs r2, #0xd4
	lsls r2, r2, #1
	adds r0, r4, r2
	strb r5, [r0]
	ldr r3, _0807ADE4 @ =0x000001A9
	adds r0, r4, r3
	strb r5, [r0]
	movs r1, #0
	strh r5, [r4, #0xc]
	adds r2, #0x71
	adds r0, r4, r2
	strb r1, [r0]
_0807ADA4:
	movs r0, #1
	bl TextClearGraphics
	ldrb r1, [r4, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	adds r0, #0x36
	strb r5, [r0]
	movs r0, #1
	strb r0, [r4, #0x1a]
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #1
	adds r1, r4, #0
	adds r1, #0x12
	adds r0, r0, r1
	movs r2, #0
	strh r5, [r0]
	ldrb r0, [r4, #0x18]
	lsls r0, r0, #1
	subs r1, #4
	adds r0, r0, r1
	strh r5, [r0]
	strb r2, [r4, #0x1c]
	strb r2, [r4, #6]
	b _0807AE42
	.align 2, 0
_0807ADDC: .4byte gNonGameplayRam
_0807ADE0: .4byte gPreviousNavigationConversation
_0807ADE4: .4byte 0x000001A9
_0807ADE8:
	ldr r2, _0807AE4C @ =gNonGameplayRam
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	movs r4, #0
	movs r1, #8
	strh r1, [r0, #0x2e]
	ldrb r0, [r2, #0x19]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r2
	ldr r3, _0807AE50 @ =0x085766E0 (sBlob_5766D4_prefix+0xC)
	ldrb r0, [r2, #0x18]
	lsls r0, r0, #1
	adds r0, r0, r3
	ldrb r0, [r0]
	strh r0, [r1, #0x2c]
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	adds r0, #0x36
	movs r1, #0xb
	strb r1, [r0]
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	adds r0, #0x34
	strb r4, [r0]
	ldrb r1, [r2, #0x19]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r2
	adds r0, #0x35
	strb r4, [r0]
	movs r0, #1
	strb r0, [r2, #7]
_0807AE40:
	strb r4, [r2, #6]
_0807AE42:
	adds r0, r7, #0
_0807AE44:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0807AE4C: .4byte gNonGameplayRam
_0807AE50: .4byte sCharacterWidths+0x4AC

	thumb_func_start NavigationConversationSetupOam
NavigationConversationSetupOam: @ 0x0807AE54
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	ldr r6, _0807AF60 @ =gNonGameplayRam
	adds r1, r6, #0
	adds r1, #0x5e
	movs r0, #0
	mov sb, r0
	movs r2, #0
	mov sl, r2
	movs r0, #0x7c
	strh r0, [r1]
	subs r1, #2
	movs r0, #0xcc
	strh r0, [r1]
	subs r1, #2
	movs r0, #0x4b
	strb r0, [r1]
	adds r0, r6, #0
	adds r0, #0x58
	mov r3, sb
	strb r3, [r0]
	adds r0, #1
	strb r3, [r0]
	movs r0, #1
	bl PauseScreenSetNavigationTextPanelOam
	movs r4, #0x73
	adds r4, r4, r6
	mov r8, r4
	ldrb r1, [r4]
	movs r2, #0xd
	rsbs r2, r2, #0
	adds r0, r2, #0
	ands r0, r1
	movs r5, #4
	orrs r0, r5
	strb r0, [r4]
	movs r0, #0x43
	adds r0, r0, r6
	mov ip, r0
	ldrb r1, [r0]
	movs r7, #4
	rsbs r7, r7, #0
	adds r0, r7, #0
	ands r0, r1
	ands r0, r2
	mov r1, ip
	strb r0, [r1]
	movs r3, #0x5b
	adds r3, r3, r6
	ldrb r1, [r3]
	adds r0, r7, #0
	ands r0, r1
	ands r0, r2
	strb r0, [r3]
	movs r4, #0x67
	adds r4, r4, r6
	ldrb r1, [r4]
	adds r0, r7, #0
	ands r0, r1
	ands r0, r2
	strb r0, [r4]
	movs r5, #0x85
	lsls r5, r5, #2
	adds r1, r6, r5
	ldr r0, _0807AF64 @ =0x085766D4 (sBlob_5766D4_prefix)
	ldm r0!, {r3, r4, r5}
	stm r1!, {r3, r4, r5}
	mov r0, sb
	strb r0, [r6, #0x1a]
	mov r1, sl
	strh r1, [r6, #4]
	adds r5, r6, #0
	adds r5, #0xa3
	ldrb r0, [r5]
	adds r4, r2, #0
	ands r4, r0
	movs r3, #4
	orrs r4, r3
	strb r4, [r5]
	adds r3, r6, #0
	adds r3, #0x4f
	ldrb r1, [r3]
	adds r0, r7, #0
	ands r0, r1
	ands r0, r2
	strb r0, [r3]
	adds r3, #0x48
	ldrb r1, [r3]
	adds r0, r7, #0
	ands r0, r1
	ands r0, r2
	strb r0, [r3]
	subs r3, #0xc
	ldrb r1, [r3]
	adds r0, r7, #0
	ands r0, r1
	ands r0, r2
	strb r0, [r3]
	subs r3, #0xc
	ldrb r1, [r3]
	adds r0, r7, #0
	ands r0, r1
	ands r0, r2
	strb r0, [r3]
	adds r0, r6, #0
	adds r0, #0x82
	movs r2, #0xd4
	strh r2, [r0]
	subs r0, #2
	movs r1, #0x44
	strh r1, [r0]
	subs r0, #0xa
	strh r2, [r0]
	subs r0, #2
	strh r1, [r0]
	ldrb r0, [r6]
	cmp r0, #0
	beq _0807AF68
	mov r1, r8
	ldrb r0, [r1]
	adds r1, r7, #0
	ands r1, r0
	movs r0, #1
	orrs r1, r0
	mov r2, r8
	strb r1, [r2]
	ands r4, r7
	orrs r4, r0
	strb r4, [r5]
	b _0807AF7C
	.align 2, 0
_0807AF60: .4byte gNonGameplayRam
_0807AF64: .4byte sCharacterWidths+0x4A0
_0807AF68:
	ands r4, r7
	movs r2, #2
	orrs r4, r2
	strb r4, [r5]
	mov r3, r8
	ldrb r1, [r3]
	adds r0, r7, #0
	ands r0, r1
	orrs r0, r2
	strb r0, [r3]
_0807AF7C:
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start NavigationConversationUpdateTarget
NavigationConversationUpdateTarget: @ 0x0807AF8C
	push {r4, lr}
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	bl NavigationConverstionFindTarget
	cmp r0, #0
	beq _0807AFF2
	cmp r4, #0
	beq _0807AFF2
	ldr r1, _0807AFCC @ =gNonGameplayRam
	movs r2, #0xd4
	lsls r2, r2, #1
	adds r0, r1, r2
	movs r2, #0
	strb r2, [r0]
	ldr r3, _0807AFD0 @ =0x000001A9
	adds r0, r1, r3
	strb r2, [r0]
	ldr r2, _0807AFD4 @ =0x0000020F
	adds r0, r1, r2
	ldrb r0, [r0]
	adds r2, r1, #0
	cmp r0, #1
	bne _0807AFDC
	ldr r1, _0807AFD8 @ =0x085767EC (sBlob_5766D4_prefix+0x118)
	adds r3, #0x6a
	adds r0, r2, r3
	ldrb r0, [r0]
	adds r0, r0, r1
	ldrb r1, [r0]
	b _0807AFEA
	.align 2, 0
_0807AFCC: .4byte gNonGameplayRam
_0807AFD0: .4byte 0x000001A9
_0807AFD4: .4byte 0x0000020F
_0807AFD8: .4byte sCharacterWidths+0x5B8
_0807AFDC:
	ldr r1, _0807AFF8 @ =0x00000212
	adds r0, r2, r1
	ldrb r0, [r0]
	movs r1, #0xe
	cmp r0, #0
	bne _0807AFEA
	movs r1, #0xf
_0807AFEA:
	movs r3, #0xd5
	lsls r3, r3, #1
	adds r0, r2, r3
	strb r1, [r0]
_0807AFF2:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_0807AFF8: .4byte 0x00000212

	thumb_func_start NavigationConverstionFindTarget
NavigationConverstionFindTarget: @ 0x0807AFFC
	push {r4, r5, r6, r7, lr}
	ldr r2, _0807B03C @ =gNonGameplayRam
	ldr r1, _0807B040 @ =0x0000020F
	adds r0, r2, r1
	movs r3, #0
	strb r3, [r0]
	movs r0, #0x83
	lsls r0, r0, #2
	adds r1, r2, r0
	movs r0, #0xff
	strb r0, [r1]
	ldr r0, _0807B044 @ =0x0000020D
	adds r1, r2, r0
	movs r0, #1
	rsbs r0, r0, #0
	strb r0, [r1]
	ldr r1, _0807B048 @ =0x0000020E
	adds r0, r2, r1
	strb r3, [r0]
	adds r1, #5
	adds r0, r2, r1
	strb r3, [r0]
	ldr r0, _0807B04C @ =gPauseScreenFlag
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	adds r5, r2, #0
	cmp r0, #4
	bne _0807B060
_0807B036:
	movs r0, #0
	b _0807B146
	.align 2, 0
_0807B03C: .4byte gNonGameplayRam
_0807B040: .4byte 0x0000020F
_0807B044: .4byte 0x0000020D
_0807B048: .4byte 0x0000020E
_0807B04C: .4byte gPauseScreenFlag
_0807B050:
	movs r4, #1
	ldrb r1, [r1, #4]
	ldr r3, _0807B05C @ =0x00000213
	adds r0, r5, r3
	strb r1, [r0]
	b _0807B086
	.align 2, 0
_0807B05C: .4byte 0x00000213
_0807B060:
	ldr r0, _0807B0B8 @ =0x0300004C
	strb r3, [r0]
	movs r4, #0
	movs r2, #0
	adds r7, r0, #0
	ldr r6, _0807B0BC @ =0x085766E4 (sBlob_5766D4_prefix+0x10)
	movs r1, #0x88
	lsls r1, r1, #2
	adds r0, r5, r1
	ldrb r3, [r0]
	adds r1, r6, #0
_0807B076:
	movs r0, #0
	ldrsb r0, [r1, r0]
	cmp r3, r0
	beq _0807B050
	adds r1, #8
	adds r2, #1
	cmp r2, #0x20
	bls _0807B076
_0807B086:
	cmp r4, #0
	beq _0807B036
	lsls r0, r2, #3
	adds r2, r0, r6
	ldrb r0, [r2, #1]
	strb r0, [r7]
	ldr r1, _0807B0C0 @ =0x08576066 (sNavigationTargetLocationAreas)
	ldrb r0, [r7]
	adds r0, r0, r1
	ldrb r0, [r0]
	ldr r3, _0807B0C4 @ =0x0000020E
	adds r6, r5, r3
	strb r0, [r6]
	ldr r1, _0807B0C8 @ =0x00000212
	adds r3, r5, r1
	ldrb r1, [r3]
	adds r4, r0, #0
	cmp r1, r4
	bne _0807B0D0
	ldrb r3, [r2, #2]
	ldrb r2, [r2, #3]
	ldr r0, _0807B0CC @ =0x0000020F
	adds r1, r5, r0
	movs r0, #1
	b _0807B11E
	.align 2, 0
_0807B0B8: .4byte 0x0300004C
_0807B0BC: .4byte sCharacterWidths+0x4B0
_0807B0C0: .4byte sNavigationTargetLocationAreas
_0807B0C4: .4byte 0x0000020E
_0807B0C8: .4byte 0x00000212
_0807B0CC: .4byte 0x0000020F
_0807B0D0:
	cmp r1, #0
	bne _0807B0F4
	ldr r2, _0807B0EC @ =0x08576218 (sBlob_576217_576234+0x1)
	ldrb r0, [r6]
	lsls r0, r0, #1
	adds r1, r0, r2
	ldrb r3, [r1]
	adds r2, #1
	adds r0, r0, r2
	ldrb r2, [r0]
	ldr r0, _0807B0F0 @ =0x0000020F
	adds r1, r5, r0
	movs r0, #2
	b _0807B11E
	.align 2, 0
_0807B0EC: .4byte sMaintainedInputDelays+0x8
_0807B0F0: .4byte 0x0000020F
_0807B0F4:
	ldr r0, _0807B110 @ =0x08576226 (sBlob_576217_576234+0xF)
	ldrb r1, [r3]
	lsls r1, r1, #1
	adds r2, r1, r0
	ldrb r3, [r2]
	adds r0, #1
	adds r1, r1, r0
	ldrb r2, [r1]
	cmp r4, #0
	bne _0807B118
	ldr r0, _0807B114 @ =0x0000020F
	adds r1, r5, r0
	movs r0, #2
	b _0807B11E
	.align 2, 0
_0807B110: .4byte sMaintainedInputDelays+0x16
_0807B114: .4byte 0x0000020F
_0807B118:
	ldr r0, _0807B14C @ =0x0000020F
	adds r1, r5, r0
	movs r0, #3
_0807B11E:
	strb r0, [r1]
	subs r1, r3, #1
	movs r3, #0x83
	lsls r3, r3, #2
	adds r0, r5, r3
	strb r1, [r0]
	subs r1, r2, #1
	ldr r2, _0807B150 @ =0x0000020D
	adds r0, r5, r2
	strb r1, [r0]
	movs r4, #0
	ldr r0, _0807B154 @ =gPreviousNavigationConversation
	adds r3, #0x14
	adds r1, r5, r3
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	bne _0807B144
	movs r4, #1
_0807B144:
	adds r0, r4, #0
_0807B146:
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1
	.align 2, 0
_0807B14C: .4byte 0x0000020F
_0807B150: .4byte 0x0000020D
_0807B154: .4byte gPreviousNavigationConversation

	thumb_func_start NavigationConversionScrollToTarget
NavigationConversionScrollToTarget: @ 0x0807B158
	push {r4, r5, r6, r7, lr}
	ldr r1, _0807B178 @ =gNonGameplayRam
	ldrb r0, [r1, #8]
	adds r0, #1
	strb r0, [r1, #8]
	ldrb r0, [r1, #9]
	adds r7, r1, #0
	cmp r0, #0xd
	bls _0807B16C
	b _0807B4BC
_0807B16C:
	lsls r0, r0, #2
	ldr r1, _0807B17C @ =_0807B180
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807B178: .4byte gNonGameplayRam
_0807B17C: .4byte _0807B180
_0807B180: @ jump table
	.4byte _0807B4BC @ case 0
	.4byte _0807B1B8 @ case 1
	.4byte _0807B226 @ case 2
	.4byte _0807B236 @ case 3
	.4byte _0807B46C @ case 4
	.4byte _0807B23E @ case 5
	.4byte _0807B300 @ case 6
	.4byte _0807B30A @ case 7
	.4byte _0807B32A @ case 8
	.4byte _0807B400 @ case 9
	.4byte _0807B420 @ case 10
	.4byte _0807B46C @ case 11
	.4byte _0807B488 @ case 12
	.4byte _0807B4BC @ case 13
_0807B1B8:
	movs r2, #0
	movs r1, #0x83
	lsls r1, r1, #2
	adds r0, r7, r1
	ldrb r0, [r0]
	cmp r0, #0xff
	beq _0807B200
	ldr r3, _0807B204 @ =0x0000020D
	adds r0, r7, r3
	ldrb r0, [r0]
	cmp r0, #0xff
	beq _0807B200
	movs r4, #0xd5
	lsls r4, r4, #1
	adds r0, r7, r4
	ldr r1, _0807B208 @ =0x085767EC (sBlob_5766D4_prefix+0x118)
	ldrb r0, [r0]
	ldrb r3, [r1]
	cmp r0, r3
	beq _0807B200
	ldrb r4, [r1, #1]
	cmp r0, r4
	beq _0807B200
	ldrb r3, [r1, #2]
	cmp r0, r3
	beq _0807B200
	ldrb r1, [r1, #3]
	cmp r0, r1
	beq _0807B200
	cmp r0, #0xe
	beq _0807B200
	cmp r0, #0xf
	bne _0807B1FC
	movs r2, #1
_0807B1FC:
	cmp r2, #0
	beq _0807B20C
_0807B200:
	movs r0, #0xc
	b _0807B4BA
	.align 2, 0
_0807B204: .4byte 0x0000020D
_0807B208: .4byte sCharacterWidths+0x5B8
_0807B20C:
	movs r0, #2
	strb r0, [r7, #9]
	ldrh r1, [r7, #4]
	movs r4, #0x80
	lsls r4, r4, #1
	adds r0, r4, #0
	orrs r0, r1
	movs r2, #0x80
	lsls r2, r2, #2
	adds r1, r2, #0
	orrs r0, r1
	strh r0, [r7, #4]
	b _0807B4BC
_0807B226:
	ldrh r1, [r7, #4]
	movs r0, #0x80
	lsls r0, r0, #3
	ands r0, r1
	cmp r0, #0
	bne _0807B234
	b _0807B4BC
_0807B234:
	b _0807B4B2
_0807B236:
	movs r0, #0
	strb r0, [r7, #8]
	movs r0, #4
	b _0807B4BA
_0807B23E:
	movs r3, #0x83
	lsls r3, r3, #2
	adds r0, r7, r3
	ldrb r0, [r0]
	ldr r4, _0807B270 @ =0x0000020D
	adds r1, r7, r4
	ldrb r1, [r1]
	bl NavigationConversationScrollMapToDestination
	cmp r0, #0
	bne _0807B256
	b _0807B4BC
_0807B256:
	ldr r1, _0807B274 @ =0x0000020F
	adds r0, r7, r1
	ldrb r0, [r0]
	cmp r0, #1
	bne _0807B280
	ldr r1, _0807B278 @ =0x085767EC (sBlob_5766D4_prefix+0x118)
	ldr r2, _0807B27C @ =0x00000213
	adds r0, r7, r2
	ldrb r0, [r0]
	adds r0, r0, r1
	ldrb r2, [r0]
	b _0807B28E
	.align 2, 0
_0807B270: .4byte 0x0000020D
_0807B274: .4byte 0x0000020F
_0807B278: .4byte sCharacterWidths+0x5B8
_0807B27C: .4byte 0x00000213
_0807B280:
	ldr r3, _0807B2B8 @ =0x00000212
	adds r0, r7, r3
	ldrb r0, [r0]
	movs r2, #0xe
	cmp r0, #0
	bne _0807B28E
	movs r2, #0xf
_0807B28E:
	ldr r5, _0807B2BC @ =gNonGameplayRam
	movs r4, #0xd5
	lsls r4, r4, #1
	adds r0, r5, r4
	movs r1, #0
	strb r2, [r0]
	movs r2, #0xd4
	lsls r2, r2, #1
	adds r0, r5, r2
	strb r1, [r0]
	ldr r3, _0807B2C0 @ =0x000001A9
	adds r0, r5, r3
	strb r1, [r0]
	strb r1, [r5, #8]
	adds r4, #0x65
	adds r0, r5, r4
	ldrb r0, [r0]
	cmp r0, #1
	bne _0807B2C4
	movs r0, #0xc
	b _0807B2C6
	.align 2, 0
_0807B2B8: .4byte 0x00000212
_0807B2BC: .4byte gNonGameplayRam
_0807B2C0: .4byte 0x000001A9
_0807B2C4:
	movs r0, #6
_0807B2C6:
	strb r0, [r5, #9]
	ldr r0, _0807B2F0 @ =0x00000119
	bl SoundStop
	ldr r1, _0807B2F4 @ =gNonGameplayRam
	movs r2, #0x83
	lsls r2, r2, #2
	adds r0, r1, r2
	ldrb r2, [r0]
	movs r3, #0x96
	lsls r3, r3, #2
	adds r0, r1, r3
	strb r2, [r0]
	ldr r4, _0807B2F8 @ =0x0000020D
	adds r0, r1, r4
	ldrb r0, [r0]
	ldr r2, _0807B2FC @ =0x00000259
	adds r1, r1, r2
	strb r0, [r1]
	b _0807B4BC
	.align 2, 0
_0807B2F0: .4byte 0x00000119
_0807B2F4: .4byte gNonGameplayRam
_0807B2F8: .4byte 0x0000020D
_0807B2FC: .4byte 0x00000259
_0807B300:
	ldrb r0, [r7, #8]
	cmp r0, #0x3c
	bhi _0807B308
	b _0807B4BC
_0807B308:
	b _0807B4B2
_0807B30A:
	movs r3, #0x94
	lsls r3, r3, #2
	adds r2, r7, r3
	movs r1, #0
	movs r0, #1
	strb r0, [r2]
	movs r4, #0xd5
	lsls r4, r4, #1
	adds r0, r7, r4
	strb r1, [r0]
	movs r2, #0xdb
	lsls r2, r2, #1
	adds r0, r7, r2
	strb r1, [r0]
	strb r1, [r7, #8]
	b _0807B4B6
_0807B32A:
	movs r3, #0x94
	lsls r3, r3, #2
	adds r0, r7, r3
	ldrb r1, [r0]
	movs r0, #4
	ands r0, r1
	cmp r0, #0
	bne _0807B33C
	b _0807B4BC
_0807B33C:
	ldr r4, _0807B36C @ =0x0000020F
	adds r0, r7, r4
	ldrb r0, [r0]
	cmp r0, #3
	bne _0807B34E
	ldr r0, _0807B370 @ =0x0000020E
	adds r1, r7, r0
	movs r0, #0
	strb r0, [r1]
_0807B34E:
	ldr r1, _0807B370 @ =0x0000020E
	adds r3, r7, r1
	ldrb r0, [r3]
	cmp r0, #0
	bne _0807B37C
	ldr r2, _0807B374 @ =0x08576218 (sBlob_576217_576234+0x1)
	ldr r4, _0807B378 @ =0x00000212
	adds r3, r7, r4
	ldrb r0, [r3]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrb r0, [r0]
	subs r0, #1
	subs r4, #2
	b _0807B38C
	.align 2, 0
_0807B36C: .4byte 0x0000020F
_0807B370: .4byte 0x0000020E
_0807B374: .4byte sMaintainedInputDelays+0x8
_0807B378: .4byte 0x00000212
_0807B37C:
	ldr r2, _0807B3E0 @ =0x08576226 (sBlob_576217_576234+0xF)
	ldrb r0, [r3]
	lsls r0, r0, #1
	adds r0, r0, r2
	ldrb r0, [r0]
	subs r0, #1
	movs r4, #0x84
	lsls r4, r4, #2
_0807B38C:
	adds r1, r7, r4
	strb r0, [r1]
	ldrb r0, [r3]
	lsls r0, r0, #1
	adds r2, #1
	adds r0, r0, r2
	ldrb r0, [r0]
	subs r0, #1
	ldr r2, _0807B3E4 @ =0x00000211
	adds r1, r7, r2
	strb r0, [r1]
	ldr r3, _0807B3E8 @ =0x0000020E
	adds r0, r7, r3
	ldrb r0, [r0]
	ldr r1, _0807B3EC @ =0x00000212
	adds r4, r7, r1
	movs r6, #0
	strb r0, [r4]
	ldrb r0, [r4]
	ldr r5, _0807B3F0 @ =0x02034000
	adds r1, r5, #0
	bl GetMinimapData
	ldrb r0, [r4]
	bl MinimapSetVisitedTilesAndCollectedItems
	ldr r1, _0807B3F4 @ =0x040000D4
	str r5, [r1]
	ldr r0, _0807B3F8 @ =0x0600E000
	str r0, [r1, #4]
	ldr r0, _0807B3FC @ =0x80000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	movs r0, #1
	bl unk_75988
	movs r0, #0
	bl NavigationConversationUpdateTarget
	strb r6, [r7, #8]
	b _0807B4B6
	.align 2, 0
_0807B3E0: .4byte sMaintainedInputDelays+0x16
_0807B3E4: .4byte 0x00000211
_0807B3E8: .4byte 0x0000020E
_0807B3EC: .4byte 0x00000212
_0807B3F0: .4byte 0x02034000
_0807B3F4: .4byte 0x040000D4
_0807B3F8: .4byte 0x0600E000
_0807B3FC: .4byte 0x80000400
_0807B400:
	ldrb r0, [r7, #8]
	cmp r0, #8
	bls _0807B4BC
	movs r0, #0
	strb r0, [r7, #8]
	ldrb r0, [r7, #9]
	adds r0, #1
	strb r0, [r7, #9]
	movs r3, #0x94
	lsls r3, r3, #2
	adds r2, r7, r3
	ldrb r1, [r2]
	movs r0, #8
	orrs r0, r1
	strb r0, [r2]
	b _0807B4BC
_0807B420:
	movs r4, #0x94
	lsls r4, r4, #2
	adds r0, r7, r4
	ldrb r0, [r0]
	cmp r0, #0
	bne _0807B4BC
	ldr r1, _0807B460 @ =0x0000020E
	adds r0, r7, r1
	ldrb r0, [r0]
	cmp r0, #0
	beq _0807B442
	ldr r2, _0807B464 @ =0x00000212
	adds r0, r7, r2
	ldrb r0, [r0]
	movs r2, #0xf
	cmp r0, #0
	bne _0807B444
_0807B442:
	movs r2, #0xe
_0807B444:
	movs r3, #0xdb
	lsls r3, r3, #1
	adds r0, r7, r3
	movs r1, #0
	strb r2, [r0]
	movs r4, #0xda
	lsls r4, r4, #1
	adds r0, r7, r4
	strb r1, [r0]
	ldr r2, _0807B468 @ =0x000001B5
	adds r0, r7, r2
	strb r1, [r0]
	strb r1, [r7, #8]
	b _0807B4B6
	.align 2, 0
_0807B460: .4byte 0x0000020E
_0807B464: .4byte 0x00000212
_0807B468: .4byte 0x000001B5
_0807B46C:
	ldrb r0, [r7, #8]
	cmp r0, #0x1e
	bls _0807B4BC
	movs r0, #0
	strb r0, [r7, #8]
	movs r0, #5
	strb r0, [r7, #9]
	ldr r0, _0807B484 @ =0x00000119
	bl SoundPlay
	b _0807B4BC
	.align 2, 0
_0807B484: .4byte 0x00000119
_0807B488:
	adds r2, r7, #0
	ldrh r1, [r2, #4]
	movs r3, #0x80
	lsls r3, r3, #2
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _0807B49E
	adds r0, r3, #0
	eors r0, r1
	strh r0, [r2, #4]
_0807B49E:
	ldrh r1, [r2, #4]
	movs r3, #0x80
	lsls r3, r3, #3
	adds r0, r3, #0
	ands r0, r1
	cmp r0, #0
	beq _0807B4B2
	adds r0, r3, #0
	eors r0, r1
	strh r0, [r2, #4]
_0807B4B2:
	movs r0, #0
	strb r0, [r7, #8]
_0807B4B6:
	ldrb r0, [r7, #9]
	adds r0, #1
_0807B4BA:
	strb r0, [r7, #9]
_0807B4BC:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start NavigationConversationScrollMapToDestination
NavigationConversationScrollMapToDestination: @ 0x0807B4C4
	push {r4, r5, r6, r7, lr}
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	lsls r1, r1, #0x18
	lsrs r1, r1, #0x18
	movs r2, #1
	mov ip, r2
	movs r2, #0xf
	subs r2, r2, r0
	lsls r2, r2, #3
	movs r3, #0x80
	lsls r3, r3, #2
	subs r5, r3, r2
	movs r0, #0xa
	subs r0, r0, r1
	lsls r0, r0, #3
	subs r6, r3, r0
	ldr r1, _0807B520 @ =gBackgroundPositions
	ldrh r4, [r1, #0xc]
	subs r2, r4, r5
	ldrh r0, [r1, #0xe]
	subs r3, r0, r6
	cmp r2, #0
	bge _0807B4F6
	rsbs r2, r2, #0
_0807B4F6:
	cmp r3, #0
	bge _0807B4FC
	rsbs r3, r3, #0
_0807B4FC:
	asrs r0, r2, #4
	adds r7, r0, #1
	asrs r0, r3, #4
	adds r3, r0, #1
	subs r2, r4, r5
	cmp r2, #0
	beq _0807B534
	movs r0, #0
	mov ip, r0
	cmp r2, #0
	ble _0807B524
	subs r0, r4, r7
	strh r0, [r1, #0xc]
	ldrh r0, [r1, #0xc]
	cmp r0, r5
	bge _0807B534
	b _0807B532
	.align 2, 0
_0807B520: .4byte gBackgroundPositions
_0807B524:
	cmp r2, #0
	bge _0807B534
	adds r0, r4, r7
	strh r0, [r1, #0xc]
	ldrh r0, [r1, #0xc]
	cmp r0, r5
	ble _0807B534
_0807B532:
	strh r5, [r1, #0xc]
_0807B534:
	adds r4, r1, #0
	ldrh r0, [r4, #0xe]
	subs r2, r0, r6
	cmp r2, #0
	beq _0807B564
	movs r5, #0
	mov ip, r5
	cmp r2, #0
	ble _0807B554
	subs r0, r0, r3
	strh r0, [r4, #0xe]
	ldrh r0, [r4, #0xe]
	cmp r0, r6
	bge _0807B564
	strh r6, [r4, #0xe]
	b _0807B564
_0807B554:
	cmp r2, #0
	bge _0807B564
	adds r0, r0, r3
	strh r0, [r1, #0xe]
	ldrh r0, [r1, #0xe]
	cmp r0, r6
	ble _0807B564
	strh r6, [r1, #0xe]
_0807B564:
	mov r0, ip
	pop {r4, r5, r6, r7}
	pop {r1}
	bx r1

	thumb_func_start unk_7b56c
unk_7b56c: @ 0x0807B56C
	push {r4, r5, lr}
	ldr r1, _0807B588 @ =gNonGameplayRam
	ldrb r0, [r1, #0xa]
	adds r0, #1
	strb r0, [r1, #0xa]
	ldrb r0, [r1, #0xb]
	adds r5, r1, #0
	cmp r0, #9
	bhi _0807B668
	lsls r0, r0, #2
	ldr r1, _0807B58C @ =_0807B590
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807B588: .4byte gNonGameplayRam
_0807B58C: .4byte _0807B590
_0807B590: @ jump table
	.4byte _0807B668 @ case 0
	.4byte _0807B5B8 @ case 1
	.4byte _0807B5BE @ case 2
	.4byte _0807B5CE @ case 3
	.4byte _0807B5EE @ case 4
	.4byte _0807B612 @ case 5
	.4byte _0807B624 @ case 6
	.4byte _0807B650 @ case 7
	.4byte _0807B668 @ case 8
	.4byte _0807B668 @ case 9
_0807B5B8:
	movs r0, #0
	strb r0, [r5, #0xa]
	b _0807B662
_0807B5BE:
	ldrh r1, [r5, #4]
	movs r0, #0x40
	ands r0, r1
	cmp r0, #0
	beq _0807B668
	movs r0, #0
	strb r0, [r5, #0xa]
	b _0807B662
_0807B5CE:
	adds r1, r5, #0
	adds r1, #0xea
	movs r4, #0
	movs r0, #0x41
	strb r0, [r1]
	adds r0, r5, #0
	adds r0, #0xe8
	strb r4, [r0]
	adds r0, #1
	strb r4, [r0]
	movs r0, #0x8e
	lsls r0, r0, #1
	bl SoundPlay
	strb r4, [r5, #0xa]
	b _0807B662
_0807B5EE:
	ldrb r0, [r5, #0xa]
	cmp r0, #0x1e
	bls _0807B668
	movs r0, #0x86
	lsls r0, r0, #2
	adds r1, r5, r0
	movs r2, #0
	movs r0, #1
	strb r0, [r1]
	strb r2, [r5, #0xa]
	ldrb r0, [r5, #0xb]
	adds r0, #1
	strb r0, [r5, #0xb]
	ldrh r1, [r5, #4]
	movs r0, #0x80
	orrs r0, r1
	strh r0, [r5, #4]
	b _0807B668
_0807B612:
	ldrh r1, [r5, #4]
	movs r0, #0x40
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #0
	bne _0807B668
	strb r0, [r5, #0xa]
	b _0807B662
_0807B624:
	movs r0, #0x86
	lsls r0, r0, #2
	adds r1, r5, r0
	movs r4, #0
	movs r0, #3
	strb r0, [r1]
	adds r1, r5, #0
	adds r1, #0xea
	movs r0, #0x42
	strb r0, [r1]
	adds r0, r5, #0
	adds r0, #0xe8
	strb r4, [r0]
	adds r0, #1
	strb r4, [r0]
	ldr r0, _0807B64C @ =0x0000011D
	bl SoundPlay
	strb r4, [r5, #0xa]
	b _0807B662
	.align 2, 0
_0807B64C: .4byte 0x0000011D
_0807B650:
	ldrb r0, [r5, #0xa]
	cmp r0, #0x1e
	bls _0807B668
	ldrh r1, [r5, #4]
	ldr r0, _0807B670 @ =0x0000FF7F
	ands r0, r1
	movs r1, #0
	strh r0, [r5, #4]
	strb r1, [r5, #0xa]
_0807B662:
	ldrb r0, [r5, #0xb]
	adds r0, #1
	strb r0, [r5, #0xb]
_0807B668:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0807B670: .4byte 0x0000FF7F

	thumb_func_start unk_7b674
unk_7b674: @ 0x0807B674
	push {r4, r5, lr}
	ldr r2, _0807B6AC @ =gNonGameplayRam
	movs r1, #0x94
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrb r1, [r0]
	movs r0, #3
	ands r0, r1
	adds r4, r2, #0
	cmp r0, #0
	bne _0807B68C
	b _0807B8C4
_0807B68C:
	ldr r2, _0807B6B0 @ =0x00000252
	adds r0, r4, r2
	ldrb r1, [r0]
	adds r1, #1
	strb r1, [r0]
	ldr r1, _0807B6B4 @ =0x00000251
	adds r0, r4, r1
	ldrb r0, [r0]
	cmp r0, #8
	bls _0807B6A2
	b _0807B8C4
_0807B6A2:
	lsls r0, r0, #2
	ldr r1, _0807B6B8 @ =_0807B6BC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807B6AC: .4byte gNonGameplayRam
_0807B6B0: .4byte 0x00000252
_0807B6B4: .4byte 0x00000251
_0807B6B8: .4byte _0807B6BC
_0807B6BC: @ jump table
	.4byte _0807B6E0 @ case 0
	.4byte _0807B72C @ case 1
	.4byte _0807B82C @ case 2
	.4byte _0807B780 @ case 3
	.4byte _0807B7BC @ case 4
	.4byte _0807B7D4 @ case 5
	.4byte _0807B82C @ case 6
	.4byte _0807B858 @ case 7
	.4byte _0807B8B0 @ case 8
_0807B6E0:
	movs r2, #0x94
	lsls r2, r2, #2
	adds r0, r4, r2
	ldrb r1, [r0]
	movs r2, #1
	adds r0, r2, #0
	ands r0, r1
	cmp r0, #0
	beq _0807B700
	ldr r1, _0807B6FC @ =0x00000251
	adds r0, r4, r1
	strb r2, [r0]
	b _0807B710
	.align 2, 0
_0807B6FC: .4byte 0x00000251
_0807B700:
	movs r0, #2
	ands r0, r1
	cmp r0, #0
	beq _0807B710
	ldr r2, _0807B720 @ =0x00000251
	adds r1, r4, r2
	movs r0, #4
	strb r0, [r1]
_0807B710:
	ldr r1, _0807B724 @ =gPreviousArea
	movs r0, #0xff
	strb r0, [r1]
	ldr r0, _0807B728 @ =0x00000252
	adds r1, r4, r0
	movs r0, #0
	strb r0, [r1]
	b _0807B8C4
	.align 2, 0
_0807B720: .4byte 0x00000251
_0807B724: .4byte gPreviousArea
_0807B728: .4byte 0x00000252
_0807B72C:
	ldr r1, _0807B770 @ =0x00000252
	adds r2, r4, r1
	ldrb r1, [r2]
	movs r0, #7
	ands r0, r1
	cmp r0, #0
	bne _0807B73C
	b _0807B8C4
_0807B73C:
	ldr r0, _0807B774 @ =gWrittenToMosaic_L
	ldrh r1, [r0]
	adds r1, #0x11
	strh r1, [r0]
	ldr r0, _0807B778 @ =0x08576802 (sBlob_5766D4_prefix+0x12E)
	lsls r1, r1, #0x10
	lsrs r1, r1, #0x10
	ldrb r0, [r0]
	cmp r1, r0
	beq _0807B752
	b _0807B8C4
_0807B752:
	movs r0, #0
	strb r0, [r2]
	ldr r2, _0807B77C @ =0x00000251
	adds r1, r4, r2
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	movs r0, #0x94
	lsls r0, r0, #2
	adds r2, r4, r0
	ldrb r1, [r2]
	movs r0, #4
	orrs r0, r1
	strb r0, [r2]
	b _0807B8C4
	.align 2, 0
_0807B770: .4byte 0x00000252
_0807B774: .4byte gWrittenToMosaic_L
_0807B778: .4byte sCharacterWidths+0x5CE
_0807B77C: .4byte 0x00000251
_0807B780:
	ldr r0, _0807B7B0 @ =0x00000252
	adds r2, r4, r0
	ldrb r1, [r2]
	movs r0, #7
	ands r0, r1
	cmp r0, #0
	bne _0807B790
	b _0807B8C4
_0807B790:
	ldr r1, _0807B7B4 @ =gWrittenToMosaic_L
	ldrh r0, [r1]
	subs r0, #0x11
	strh r0, [r1]
	lsls r0, r0, #0x10
	lsrs r3, r0, #0x10
	cmp r3, #0
	beq _0807B7A2
	b _0807B8C4
_0807B7A2:
	ldr r0, _0807B7B8 @ =0x00000251
	adds r1, r4, r0
	movs r0, #8
	strb r0, [r1]
	strb r3, [r2]
	b _0807B8C4
	.align 2, 0
_0807B7B0: .4byte 0x00000252
_0807B7B4: .4byte gWrittenToMosaic_L
_0807B7B8: .4byte 0x00000251
_0807B7BC:
	ldr r1, _0807B7CC @ =0x00000253
	adds r0, r4, r1
	movs r2, #0
	strb r2, [r0]
	ldr r0, _0807B7D0 @ =0x00000251
	adds r1, r4, r0
	movs r0, #5
	b _0807B846
	.align 2, 0
_0807B7CC: .4byte 0x00000253
_0807B7D0: .4byte 0x00000251
_0807B7D4:
	ldr r2, _0807B81C @ =0x00000253
	adds r5, r4, r2
	ldrb r1, [r5]
	movs r2, #0x50
	subs r0, r2, r1
	asrs r0, r0, #4
	cmp r0, #3
	bgt _0807B7E6
	movs r0, #4
_0807B7E6:
	adds r0, r1, r0
	strb r0, [r5]
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	cmp r0, #0x50
	bls _0807B814
	strb r2, [r5]
	ldr r0, _0807B820 @ =0x00000252
	adds r1, r4, r0
	movs r0, #0
	strb r0, [r1]
	ldr r2, _0807B824 @ =0x00000251
	adds r1, r4, r2
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	movs r0, #0x94
	lsls r0, r0, #2
	adds r2, r4, r0
	ldrb r0, [r2]
	movs r1, #4
	orrs r0, r1
	strb r0, [r2]
_0807B814:
	ldr r3, _0807B828 @ =0x04000046
	ldrb r2, [r5]
	b _0807B89A
	.align 2, 0
_0807B81C: .4byte 0x00000253
_0807B820: .4byte 0x00000252
_0807B824: .4byte 0x00000251
_0807B828: .4byte 0x04000046
_0807B82C:
	movs r1, #0x94
	lsls r1, r1, #2
	adds r0, r4, r1
	ldrb r1, [r0]
	movs r0, #8
	ands r0, r1
	cmp r0, #0
	beq _0807B8C4
	ldr r2, _0807B850 @ =0x00000251
	adds r1, r4, r2
	ldrb r0, [r1]
	adds r0, #1
	movs r2, #0
_0807B846:
	strb r0, [r1]
	ldr r1, _0807B854 @ =0x00000252
	adds r0, r4, r1
	strb r2, [r0]
	b _0807B8C4
	.align 2, 0
_0807B850: .4byte 0x00000251
_0807B854: .4byte 0x00000252
_0807B858:
	ldr r2, _0807B884 @ =0x00000253
	adds r3, r4, r2
	ldrb r1, [r3]
	movs r0, #0x50
	subs r0, r0, r1
	asrs r0, r0, #4
	cmp r0, #3
	bgt _0807B86A
	movs r0, #4
_0807B86A:
	subs r0, r1, r0
	cmp r0, #0
	bge _0807B890
	movs r2, #0
	strb r2, [r3]
	ldr r0, _0807B888 @ =0x00000251
	adds r1, r4, r0
	movs r0, #8
	strb r0, [r1]
	ldr r1, _0807B88C @ =0x00000252
	adds r0, r4, r1
	strb r2, [r0]
	b _0807B892
	.align 2, 0
_0807B884: .4byte 0x00000253
_0807B888: .4byte 0x00000251
_0807B88C: .4byte 0x00000252
_0807B890:
	strb r0, [r3]
_0807B892:
	ldr r3, _0807B8A8 @ =0x04000046
	ldr r2, _0807B8AC @ =0x00000253
	adds r0, r4, r2
	ldrb r2, [r0]
_0807B89A:
	lsls r1, r2, #8
	movs r0, #0xa0
	subs r0, r0, r2
	orrs r1, r0
	strh r1, [r3]
	b _0807B8C4
	.align 2, 0
_0807B8A8: .4byte 0x04000046
_0807B8AC: .4byte 0x00000253
_0807B8B0:
	ldr r1, _0807B8CC @ =0x00000252
	adds r0, r4, r1
	movs r1, #0
	strb r1, [r0]
	ldr r2, _0807B8D0 @ =0x00000251
	adds r0, r4, r2
	strb r1, [r0]
	subs r2, #1
	adds r0, r4, r2
	strb r1, [r0]
_0807B8C4:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_0807B8CC: .4byte 0x00000252
_0807B8D0: .4byte 0x00000251

