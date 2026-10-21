    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start SetLanguage
SetLanguage: @ 0x080A13D0
	ldr r1, _080A13DC @ =0x03000011
	movs r0, #2
	strb r0, [r1]
	movs r0, #1
	bx lr
	.align 2, 0
_080A13DC: .4byte 0x03000011

	thumb_func_start unk_a13e0
unk_a13e0: @ 0x080A13E0
	push {r4, lr}
	ldr r4, _080A1454 @ =0x04000208
	movs r1, #0
	strh r1, [r4]
	ldr r3, _080A1458 @ =0x04000004
	ldrh r2, [r3]
	ldr r0, _080A145C @ =0x0000FFEF
	ands r0, r2
	strh r0, [r3]
	ldr r3, _080A1460 @ =0x04000200
	ldrh r2, [r3]
	ldr r0, _080A1464 @ =0x0000FFFD
	ands r0, r2
	strh r0, [r3]
	movs r0, #1
	strh r0, [r4]
	movs r3, #0x80
	lsls r3, r3, #0x13
	strh r1, [r3]
	ldr r2, _080A1468 @ =0x04000050
	movs r0, #0xff
	strh r0, [r2]
	ldr r0, _080A146C @ =gWrittenToBldy
	movs r2, #0x10
	strh r2, [r0]
	ldr r0, _080A1470 @ =0x04000054
	strh r2, [r0]
	subs r0, #0x46
	strh r1, [r0]
	subs r0, #2
	strh r1, [r0]
	subs r0, #2
	strh r1, [r0]
	subs r0, #2
	strh r1, [r0]
	adds r0, #8
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	adds r0, #2
	strh r1, [r0]
	strh r1, [r3]
	ldr r0, _080A1474 @ =unk_a1478
	bl CallbackSetVBlank
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A1454: .4byte 0x04000208
_080A1458: .4byte 0x04000004
_080A145C: .4byte 0x0000FFEF
_080A1460: .4byte 0x04000200
_080A1464: .4byte 0x0000FFFD
_080A1468: .4byte 0x04000050
_080A146C: .4byte gWrittenToBldy
_080A1470: .4byte 0x04000054
_080A1474: .4byte unk_a1478

	thumb_func_start unk_a1478
unk_a1478: @ 0x080A1478
	bx lr
	.align 2, 0

	thumb_func_start unk_a147c
unk_a147c: @ 0x080A147C
	movs r0, #1
	bx lr

	thumb_func_start EndingDrawIgtAndCompletionPercentage
EndingDrawIgtAndCompletionPercentage: @ 0x080A1480
	push {r4, r5, r6, r7, lr}
	mov r7, sb
	mov r6, r8
	push {r6, r7}
	movs r1, #0
	ldr r0, _080A1548 @ =gInGameTimer
	ldrb r4, [r0]
	ldr r7, _080A154C @ =0x0874E650 (sBlob_74e650_74eb50)
	ldr r2, _080A1550 @ =0x0874E8D0 (sBlob_74e650_74eb50+0x280)
	mov ip, r2
	ldr r5, _080A1554 @ =gNonGameplayRam
	mov r8, r5
	cmp r4, #9
	ble _080A14A4
_080A149C:
	subs r4, #0xa
	adds r1, #1
	cmp r4, #9
	bgt _080A149C
_080A14A4:
	movs r6, #0
	ldrb r5, [r0, #1]
	lsls r4, r4, #6
	mov sb, r4
	cmp r5, #9
	ble _080A14B8
_080A14B0:
	subs r5, #0xa
	adds r6, #1
	cmp r5, #9
	bgt _080A14B0
_080A14B8:
	cmp r1, #0
	beq _080A14DC
	lsls r3, r1, #6
	ldr r0, _080A1558 @ =0x040000D4
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A155C @ =0x06010000
	str r1, [r0, #4]
	ldr r2, _080A1560 @ =0x80000020
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	mov r4, ip
	adds r1, r3, r4
	str r1, [r0]
	ldr r1, _080A1564 @ =0x06010400
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r0, [r0, #8]
_080A14DC:
	mov r3, sb
	ldr r0, _080A1558 @ =0x040000D4
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A1568 @ =0x06010040
	str r1, [r0, #4]
	ldr r2, _080A1560 @ =0x80000020
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	mov r4, ip
	adds r1, r3, r4
	str r1, [r0]
	ldr r1, _080A156C @ =0x06010440
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	lsls r3, r6, #6
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A1570 @ =0x060100A0
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	adds r1, r3, r4
	str r1, [r0]
	ldr r1, _080A1574 @ =0x060104A0
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	lsls r3, r5, #6
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A1578 @ =0x060100E0
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	adds r1, r3, r4
	str r1, [r0]
	ldr r1, _080A157C @ =0x060104E0
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r0, [r0, #8]
	movs r1, #0
	movs r4, #0
	mov r0, r8
	adds r0, #0x9a
	ldrb r6, [r0]
	cmp r6, #0x63
	ble _080A1584
_080A153E:
	subs r6, #0x64
	adds r1, #1
	cmp r6, #0x63
	bgt _080A153E
	b _080A1584
	.align 2, 0
_080A1548: .4byte gInGameTimer
_080A154C: .4byte sPreResultsSamusBgTilemapPointers+0x10
_080A1550: .4byte sPreResultsSamusBgTilemapPointers+0x290
_080A1554: .4byte gNonGameplayRam
_080A1558: .4byte 0x040000D4
_080A155C: .4byte 0x06010000
_080A1560: .4byte 0x80000020
_080A1564: .4byte 0x06010400
_080A1568: .4byte 0x06010040
_080A156C: .4byte 0x06010440
_080A1570: .4byte 0x060100A0
_080A1574: .4byte 0x060104A0
_080A1578: .4byte 0x060100E0
_080A157C: .4byte 0x060104E0
_080A1580:
	subs r6, #0xa
	adds r4, #1
_080A1584:
	cmp r6, #9
	bgt _080A1580
	cmp r1, #0
	beq _080A15C0
	lsls r3, r1, #6
	ldr r0, _080A15B0 @ =0x040000D4
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A15B4 @ =0x06010120
	str r1, [r0, #4]
	ldr r2, _080A15B8 @ =0x80000020
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	mov r5, ip
	adds r1, r3, r5
	str r1, [r0]
	ldr r1, _080A15BC @ =0x06010520
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r0, [r0, #8]
	b _080A15C4
	.align 2, 0
_080A15B0: .4byte 0x040000D4
_080A15B4: .4byte 0x06010120
_080A15B8: .4byte 0x80000020
_080A15BC: .4byte 0x06010520
_080A15C0:
	cmp r4, #0
	beq _080A15E4
_080A15C4:
	lsls r3, r4, #6
	ldr r0, _080A1610 @ =0x040000D4
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A1614 @ =0x06010160
	str r1, [r0, #4]
	ldr r2, _080A1618 @ =0x80000020
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	mov r4, ip
	adds r1, r3, r4
	str r1, [r0]
	ldr r1, _080A161C @ =0x06010560
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r0, [r0, #8]
_080A15E4:
	lsls r3, r6, #6
	ldr r0, _080A1610 @ =0x040000D4
	adds r1, r3, r7
	str r1, [r0]
	ldr r1, _080A1620 @ =0x060101A0
	str r1, [r0, #4]
	ldr r2, _080A1618 @ =0x80000020
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	mov r5, ip
	adds r1, r3, r5
	str r1, [r0]
	ldr r1, _080A1624 @ =0x060105A0
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r0, [r0, #8]
	pop {r3, r4}
	mov r8, r3
	mov sb, r4
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A1610: .4byte 0x040000D4
_080A1614: .4byte 0x06010160
_080A1618: .4byte 0x80000020
_080A161C: .4byte 0x06010560
_080A1620: .4byte 0x060101A0
_080A1624: .4byte 0x060105A0

	thumb_func_start EndingImageUpdateLettersSpawnDelay
EndingImageUpdateLettersSpawnDelay: @ 0x080A1628
	push {r4, lr}
	adds r3, r0, #0
	ldr r1, _080A1660 @ =gNonGameplayRam
	movs r2, #0x92
	lsls r2, r2, #1
	adds r0, r1, r2
	adds r2, r3, r0
	ldrb r0, [r2]
	cmp r0, #0
	beq _080A165A
	movs r4, #0xa1
	lsls r4, r4, #1
	adds r0, r1, r4
	adds r1, r3, r0
	ldrb r0, [r1]
	cmp r0, #0
	beq _080A165A
	subs r0, #1
	strb r0, [r1]
	lsls r0, r0, #0x18
	cmp r0, #0
	bne _080A165A
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
_080A165A:
	pop {r4}
	pop {r0}
	bx r0
	.align 2, 0
_080A1660: .4byte gNonGameplayRam

	thumb_func_start EndingImageLoadTextOam
EndingImageLoadTextOam: @ 0x080A1664
	push {r4, r5, r6, r7, lr}
	adds r1, r0, #0
	ldr r0, _080A1680 @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	beq _080A175C
	cmp r0, #4
	bgt _080A1684
	cmp r0, #3
	beq _080A1692
	b _080A1A28
	.align 2, 0
_080A1680: .4byte 0x03000011
_080A1684:
	cmp r0, #5
	bne _080A168A
	b _080A1828
_080A168A:
	cmp r0, #6
	bne _080A1690
	b _080A195C
_080A1690:
	b _080A1A28
_080A1692:
	cmp r1, #0
	bne _080A16F8
	ldr r1, _080A16F0 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x13
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A16F4 @ =0x0874DE94 (sBlob_74dc48_74e620+0x24C)
	movs r0, #0x95
	lsls r0, r0, #1
	adds r4, r5, r0
	movs r1, #0xb3
	lsls r1, r1, #1
	adds r6, r5, r1
	adds r0, #0x60
	adds r0, r0, r5
	mov ip, r0
_080A16BA:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0xc
	ble _080A16BA
	b _080A1B50
	.align 2, 0
_080A16F0: .4byte gNonGameplayRam
_080A16F4: .4byte sCredits+0x2DE4
_080A16F8:
	ldr r1, _080A1754 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x14
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1758 @ =0x0874DF30 (sBlob_74dc48_74e620+0x2E8)
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A171C:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0xd
	ble _080A171C
	b _080A1B50
	.align 2, 0
_080A1754: .4byte gNonGameplayRam
_080A1758: .4byte sCredits+0x2E80
_080A175C:
	cmp r1, #0
	bne _080A17C4
	ldr r1, _080A17BC @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x16
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A17C0 @ =0x0874E020 (sBlob_74dc48_74e620+0x3D8)
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A1784:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0xf
	ble _080A1784
	b _080A1B50
	.align 2, 0
_080A17BC: .4byte gNonGameplayRam
_080A17C0: .4byte sCredits+0x2F70
_080A17C4:
	ldr r1, _080A1820 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x1a
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1824 @ =0x0874E0E0 (sBlob_74dc48_74e620+0x498)
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A17E8:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0x13
	ble _080A17E8
	b _080A1B50
	.align 2, 0
_080A1820: .4byte gNonGameplayRam
_080A1824: .4byte sCredits+0x3030
_080A1828:
	cmp r1, #0
	bne _080A1890
	ldr r1, _080A1888 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x18
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A188C @ =0x0874E218 (sBlob_74dc48_74e620+0x5D0)
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A1850:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0x11
	ble _080A1850
	b _080A1B50
	.align 2, 0
_080A1888: .4byte gNonGameplayRam
_080A188C: .4byte sCredits+0x3168
_080A1890:
	cmp r1, #1
	bne _080A18F8
	ldr r1, _080A18F0 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x11
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A18F4 @ =0x0874E2F0 (sBlob_74dc48_74e620+0x6A8)
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A18B8:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0xa
	ble _080A18B8
	b _080A1B50
	.align 2, 0
_080A18F0: .4byte gNonGameplayRam
_080A18F4: .4byte sCredits+0x3240
_080A18F8:
	ldr r1, _080A1954 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x17
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1958 @ =0x0874E374 (sBlob_74dc48_74e620+0x72C)
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A191C:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0x10
	ble _080A191C
	b _080A1B50
	.align 2, 0
_080A1954: .4byte gNonGameplayRam
_080A1958: .4byte sCredits+0x32C4
_080A195C:
	cmp r1, #0
	bne _080A19C4
	ldr r1, _080A19BC @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x15
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A19C0 @ =0x0874E488 (sBlob_74dc48_74e620+0x840)
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A1984:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0xe
	ble _080A1984
	b _080A1B50
	.align 2, 0
_080A19BC: .4byte gNonGameplayRam
_080A19C0: .4byte sCredits+0x33D8
_080A19C4:
	ldr r1, _080A1A20 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x19
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1A24 @ =0x0874E53C (sBlob_74dc48_74e620+0x8F4)
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A19E8:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0x12
	ble _080A19E8
	b _080A1B50
	.align 2, 0
_080A1A20: .4byte gNonGameplayRam
_080A1A24: .4byte sCredits+0x348C
_080A1A28:
	cmp r1, #0
	bne _080A1A90
	ldr r1, _080A1A88 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0xf
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1A8C @ =0x0874DC90 (sBlob_74dc48_74e620+0x48)
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A1A50:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #8
	ble _080A1A50
	b _080A1B50
	.align 2, 0
_080A1A88: .4byte gNonGameplayRam
_080A1A8C: .4byte sCredits+0x2BE0
_080A1A90:
	cmp r1, #1
	bne _080A1AF8
	ldr r1, _080A1AF0 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x11
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1AF4 @ =0x0874DCFC (sBlob_74dc48_74e620+0xB4)
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A1AB8:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0xa
	ble _080A1AB8
	b _080A1B50
	.align 2, 0
_080A1AF0: .4byte gNonGameplayRam
_080A1AF4: .4byte sCredits+0x2C4C
_080A1AF8:
	ldr r1, _080A1B58 @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0x9b
	movs r0, #0x17
	strb r0, [r2]
	movs r3, #0
	adds r5, r1, #0
	movs r7, #0x18
	ldr r2, _080A1B5C @ =0x0874DD80 (sBlob_74dc48_74e620+0x138)
	movs r1, #0x95
	lsls r1, r1, #1
	adds r4, r5, r1
	movs r0, #0xb3
	lsls r0, r0, #1
	adds r6, r5, r0
	adds r1, #0x60
	adds r1, r1, r5
	mov ip, r1
_080A1B1C:
	ldrb r0, [r2]
	strb r0, [r4]
	ldrb r0, [r2, #1]
	strb r0, [r4, #0x1e]
	ldrb r0, [r2, #2]
	strb r0, [r6]
	ldrh r0, [r2, #4]
	mov r1, ip
	strh r0, [r1]
	ldrh r0, [r2, #6]
	strh r0, [r1, #0x3c]
	movs r1, #0xfc
	lsls r1, r1, #1
	adds r0, r5, r1
	adds r0, r7, r0
	ldr r1, [r2, #8]
	str r1, [r0]
	adds r7, #4
	movs r0, #2
	add ip, r0
	adds r2, #0xc
	adds r4, #1
	adds r6, #1
	adds r3, #1
	cmp r3, #0x10
	ble _080A1B1C
_080A1B50:
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080A1B58: .4byte gNonGameplayRam
_080A1B5C: .4byte sCredits+0x2CD0

	thumb_func_start EndingImageDisplayLinePermanently
EndingImageDisplayLinePermanently: @ 0x080A1B60
	push {r4, r5, r6, lr}
	adds r6, r0, #0
	ldr r0, _080A1B7C @ =0x03000011
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	beq _080A1BA4
	cmp r0, #4
	bgt _080A1B80
	cmp r0, #3
	beq _080A1B8A
	b _080A1BEC
	.align 2, 0
_080A1B7C: .4byte 0x03000011
_080A1B80:
	cmp r0, #5
	beq _080A1BBC
	cmp r0, #6
	beq _080A1BD4
	b _080A1BEC
_080A1B8A:
	ldr r0, _080A1B9C @ =gNonGameplayRam
	mov ip, r0
	movs r1, #0x92
	lsls r1, r1, #1
	add r1, ip
	adds r1, r6, r1
	ldr r5, _080A1BA0 @ =0x0874DE4C (sBlob_74dc48_74e620+0x204)
	b _080A1BFA
	.align 2, 0
_080A1B9C: .4byte gNonGameplayRam
_080A1BA0: .4byte sCredits+0x2D9C
_080A1BA4:
	ldr r0, _080A1BB4 @ =gNonGameplayRam
	mov ip, r0
	movs r1, #0x92
	lsls r1, r1, #1
	add r1, ip
	adds r1, r6, r1
	ldr r5, _080A1BB8 @ =0x0874DFD8 (sBlob_74dc48_74e620+0x390)
	b _080A1BFA
	.align 2, 0
_080A1BB4: .4byte gNonGameplayRam
_080A1BB8: .4byte sCredits+0x2F28
_080A1BBC:
	ldr r0, _080A1BCC @ =gNonGameplayRam
	mov ip, r0
	movs r1, #0x92
	lsls r1, r1, #1
	add r1, ip
	adds r1, r6, r1
	ldr r5, _080A1BD0 @ =0x0874E1D0 (sBlob_74dc48_74e620+0x588)
	b _080A1BFA
	.align 2, 0
_080A1BCC: .4byte gNonGameplayRam
_080A1BD0: .4byte sCredits+0x3120
_080A1BD4:
	ldr r0, _080A1BE4 @ =gNonGameplayRam
	mov ip, r0
	movs r1, #0x92
	lsls r1, r1, #1
	add r1, ip
	adds r1, r6, r1
	ldr r5, _080A1BE8 @ =0x0874E440 (sBlob_74dc48_74e620+0x7F8)
	b _080A1BFA
	.align 2, 0
_080A1BE4: .4byte gNonGameplayRam
_080A1BE8: .4byte sCredits+0x3390
_080A1BEC:
	ldr r0, _080A1C7C @ =gNonGameplayRam
	mov ip, r0
	movs r1, #0x92
	lsls r1, r1, #1
	add r1, ip
	adds r1, r6, r1
	ldr r5, _080A1C80 @ =0x0874DC48 (sBlob_74dc48_74e620)
_080A1BFA:
	lsls r3, r6, #1
	adds r4, r3, r6
	lsls r4, r4, #2
	adds r2, r4, r5
	ldrb r0, [r2]
	strb r0, [r1]
	movs r0, #0xa1
	lsls r0, r0, #1
	add r0, ip
	adds r0, r6, r0
	ldrb r1, [r2, #1]
	strb r1, [r0]
	movs r0, #0xb0
	lsls r0, r0, #1
	add r0, ip
	adds r0, r6, r0
	ldrb r1, [r2, #2]
	strb r1, [r0]
	movs r0, #0xbf
	lsls r0, r0, #1
	add r0, ip
	adds r0, r3, r0
	ldrh r1, [r2, #4]
	strh r1, [r0]
	movs r0, #0xdd
	lsls r0, r0, #1
	add r0, ip
	adds r3, r3, r0
	ldrh r0, [r2, #6]
	strh r0, [r3]
	lsls r1, r6, #2
	movs r0, #0xfc
	lsls r0, r0, #1
	add r0, ip
	adds r1, r1, r0
	adds r5, #8
	adds r4, r4, r5
	ldr r0, [r4]
	str r0, [r1]
	mov r1, ip
	movs r3, #0
	adds r2, r1, #0
	adds r2, #0x9b
	ldrb r0, [r2]
	subs r0, #6
	cmp r3, r0
	bge _080A1C70
	movs r5, #0
	adds r4, r2, #0
	movs r0, #0x95
	lsls r0, r0, #1
	adds r2, r1, r0
_080A1C62:
	strb r5, [r2]
	adds r2, #1
	adds r3, #1
	ldrb r0, [r4]
	subs r0, #6
	cmp r3, r0
	blt _080A1C62
_080A1C70:
	adds r1, #0x9b
	movs r0, #6
	strb r0, [r1]
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_080A1C7C: .4byte gNonGameplayRam
_080A1C80: .4byte sCredits+0x2B98

