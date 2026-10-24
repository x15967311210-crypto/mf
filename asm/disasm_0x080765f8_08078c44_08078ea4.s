    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start NavigationConversationUpdatePanel
NavigationConversationUpdatePanel: @ 0x08078EA4
	push {r4, r5, lr}
	ldr r1, _08078EC0 @ =gNonGameplayRam
	ldrh r0, [r1, #4]
	movs r2, #1
	ands r2, r0
	adds r5, r1, #0
	cmp r2, #0
	bne _08078EC4
	movs r1, #0x8e
	lsls r1, r1, #2
	adds r0, r5, r1
	strb r2, [r0]
	b _080790A8
	.align 2, 0
_08078EC0: .4byte gNonGameplayRam
_08078EC4:
	ldr r1, _08078EE8 @ =0x00000239
	adds r0, r5, r1
	ldrb r1, [r0]
	adds r1, #1
	strb r1, [r0]
	movs r2, #0x8e
	lsls r2, r2, #2
	adds r0, r5, r2
	ldrb r0, [r0]
	cmp r0, #0xd
	bls _08078EDC
	b _0807910E
_08078EDC:
	lsls r0, r0, #2
	ldr r1, _08078EEC @ =_08078EF0
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08078EE8: .4byte 0x00000239
_08078EEC: .4byte _08078EF0
_08078EF0: @ jump table
	.4byte _08078F28 @ case 0
	.4byte _08078F3E @ case 1
	.4byte _08078F60 @ case 2
	.4byte _0807908C @ case 3
	.4byte _08078F68 @ case 4
	.4byte _08078F90 @ case 5
	.4byte _08078FE0 @ case 6
	.4byte _08079038 @ case 7
	.4byte _08079060 @ case 8
	.4byte _08079066 @ case 9
	.4byte _0807908C @ case 10
	.4byte _080790B4 @ case 11
	.4byte _080790EC @ case 12
	.4byte _0807910E @ case 13
_08078F28:
	adds r1, r5, #0
	adds r1, #0x5c
	ldrh r2, [r1]
	movs r3, #0
	ldrsh r0, [r1, r3]
	cmp r0, #0x7c
	bne _08078F38
	b _080790D0
_08078F38:
	adds r0, r2, #0
	subs r0, #8
	b _080790C6
_08078F3E:
	ldr r2, _08078F5C @ =0x00000239
	adds r3, r5, r2
	ldrb r0, [r3]
	cmp r0, #8
	bhi _08078F4A
	b _0807910E
_08078F4A:
	movs r1, #0x8e
	lsls r1, r1, #2
	adds r0, r5, r1
	ldrb r1, [r0]
	adds r1, #1
	movs r2, #0
	strb r1, [r0]
	b _0807910C
	.align 2, 0
_08078F5C: .4byte 0x00000239
_08078F60:
	movs r0, #2
	bl PauseScreenSetNavigationTextPanelOam
	b _08079040
_08078F68:
	movs r0, #3
	movs r1, #0x49
	bl UpdateMenuOamDataId
	ldr r1, _08078F88 @ =gNonGameplayRam
	movs r0, #0x8e
	lsls r0, r0, #2
	adds r2, r1, r0
	ldrb r0, [r2]
	adds r0, #1
	movs r3, #0
	strb r0, [r2]
	ldr r2, _08078F8C @ =0x00000239
	adds r1, r1, r2
	strb r3, [r1]
	b _0807910E
	.align 2, 0
_08078F88: .4byte gNonGameplayRam
_08078F8C: .4byte 0x00000239
_08078F90:
	adds r0, r5, #0
	adds r0, #0x5b
	ldrb r1, [r0]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	bne _08078FA0
	b _0807910E
_08078FA0:
	ldrh r1, [r5, #4]
	movs r0, #8
	movs r2, #0
	orrs r0, r1
	strh r0, [r5, #4]
	movs r0, #8
	strh r0, [r5, #0x3a]
	ldr r0, _08078FDC @ =0x085766E0 (sBlob_5766D4_prefix+0xC)
	ldrb r0, [r0]
	strh r0, [r5, #0x38]
	adds r0, r5, #0
	adds r0, #0x40
	strb r2, [r0]
	adds r0, #1
	strb r2, [r0]
	ldrb r0, [r5, #0x1c]
	cmp r0, #5
	beq _08078FCC
	adds r1, r5, #0
	adds r1, #0x42
	movs r0, #0xb
	strb r0, [r1]
_08078FCC:
	movs r3, #0x8e
	lsls r3, r3, #2
	adds r0, r5, r3
	ldrb r1, [r0]
	adds r1, #1
	strb r1, [r0]
	b _080790DE
	.align 2, 0
_08078FDC: .4byte sCharacterWidths+0x4AC
_08078FE0:
	ldr r2, _08079004 @ =gNonGameplayRam
	ldrh r1, [r2, #4]
	movs r0, #8
	ands r0, r1
	lsls r0, r0, #0x10
	lsrs r3, r0, #0x10
	cmp r3, #0
	bne _0807900C
	movs r1, #0x8e
	lsls r1, r1, #2
	adds r0, r2, r1
	ldrb r1, [r0]
	adds r1, #1
	strb r1, [r0]
	ldr r1, _08079008 @ =0x00000239
	adds r0, r2, r1
	strb r3, [r0]
	b _0807901E
	.align 2, 0
_08079004: .4byte gNonGameplayRam
_08079008: .4byte 0x00000239
_0807900C:
	ldr r3, _08079030 @ =0x00000239
	adds r0, r2, r3
	ldrb r0, [r0]
	cmp r0, #0x10
	bne _0807901E
	movs r0, #3
	movs r1, #0x4c
	bl UpdateMenuOamDataId
_0807901E:
	ldr r0, _08079034 @ =gNonGameplayRam
	ldr r2, _08079030 @ =0x00000239
	adds r1, r0, r2
	ldrb r0, [r1]
	cmp r0, #0x3c
	bls _0807910E
	movs r0, #0x3c
	strb r0, [r1]
	b _0807910E
	.align 2, 0
_08079030: .4byte 0x00000239
_08079034: .4byte gNonGameplayRam
_08079038:
	movs r0, #3
	movs r1, #0x4a
	bl UpdateMenuOamDataId
_08079040:
	ldr r1, _08079058 @ =gNonGameplayRam
	movs r3, #0x8e
	lsls r3, r3, #2
	adds r2, r1, r3
	ldrb r0, [r2]
	adds r0, #1
	movs r3, #0
	strb r0, [r2]
	ldr r0, _0807905C @ =0x00000239
	adds r1, r1, r0
	strb r3, [r1]
	b _0807910E
	.align 2, 0
_08079058: .4byte gNonGameplayRam
_0807905C: .4byte 0x00000239
_08079060:
	adds r0, r5, #0
	adds r0, #0x5b
	b _08079090
_08079066:
	adds r0, r5, #0
	adds r0, #0x42
	movs r4, #0
	strb r4, [r0]
	movs r0, #3
	bl PauseScreenSetNavigationTextPanelOam
	movs r0, #0x8e
	lsls r0, r0, #2
	adds r1, r5, r0
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	ldr r1, _08079088 @ =0x00000239
	adds r0, r5, r1
	strb r4, [r0]
	b _0807910E
	.align 2, 0
_08079088: .4byte 0x00000239
_0807908C:
	adds r0, r5, #0
	adds r0, #0x67
_08079090:
	ldrb r1, [r0]
	movs r0, #0x10
	ands r0, r1
	cmp r0, #0
	beq _0807910E
	movs r2, #0x8e
	lsls r2, r2, #2
	adds r1, r5, r2
	ldrb r0, [r1]
	adds r0, #1
	movs r2, #0
	strb r0, [r1]
_080790A8:
	ldr r3, _080790B0 @ =0x00000239
	adds r0, r5, r3
	strb r2, [r0]
	b _0807910E
	.align 2, 0
_080790B0: .4byte 0x00000239
_080790B4:
	adds r1, r5, #0
	adds r1, #0x5c
	ldrh r2, [r1]
	movs r3, #0
	ldrsh r0, [r1, r3]
	cmp r0, #0xcc
	beq _080790D0
	adds r0, r2, #0
	adds r0, #8
_080790C6:
	strh r0, [r1]
	movs r0, #0
	bl PauseScreenSetNavigationTextPanelOam
	b _0807910E
_080790D0:
	movs r0, #0x8e
	lsls r0, r0, #2
	adds r1, r5, r0
	ldrb r0, [r1]
	adds r0, #1
	movs r2, #0
	strb r0, [r1]
_080790DE:
	ldr r1, _080790E8 @ =0x00000239
	adds r0, r5, r1
	strb r2, [r0]
	b _0807910E
	.align 2, 0
_080790E8: .4byte 0x00000239
_080790EC:
	ldr r2, _08079114 @ =0x00000239
	adds r3, r5, r2
	ldrb r0, [r3]
	cmp r0, #8
	bls _0807910E
	ldrh r0, [r5, #4]
	movs r1, #1
	eors r0, r1
	movs r2, #0
	strh r0, [r5, #4]
	movs r0, #0x8e
	lsls r0, r0, #2
	adds r1, r5, r0
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
_0807910C:
	strb r2, [r3]
_0807910E:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0
_08079114: .4byte 0x00000239


