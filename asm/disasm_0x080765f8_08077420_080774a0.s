    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start PauseDebugWindowDisappearing
PauseDebugWindowDisappearing: @ 0x080774A0
	push {r4, r5, lr}
	movs r5, #0
	ldr r4, _080774B8 @ =gNonGameplayRam
	ldrb r0, [r4, #7]
	cmp r0, #1
	beq _080774D4
	cmp r0, #1
	bgt _080774BC
	cmp r0, #0
	beq _080774C2
	b _080774F6
	.align 2, 0
_080774B8: .4byte gNonGameplayRam
_080774BC:
	cmp r0, #2
	beq _080774E2
	b _080774F6
_080774C2:
	ldr r0, _080774D0 @ =0x00000201
	bl SoundPlay
	movs r0, #4
	bl unk_77840
	b _080774DA
	.align 2, 0
_080774D0: .4byte 0x00000201
_080774D4:
	ldrb r0, [r4, #6]
	cmp r0, #4
	bls _080774F6
_080774DA:
	movs r0, #2
	strb r0, [r4, #7]
	strb r5, [r4, #6]
	b _080774F6
_080774E2:
	movs r1, #0x80
	lsls r1, r1, #1
	movs r0, #1
	bl PauseScreenMoveBackgroundToYPosition
	cmp r0, #0
	beq _080774F2
	movs r5, #1
_080774F2:
	bl PauseScreenSetPauseDebugWindow
_080774F6:
	adds r0, r5, #0
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0

	thumb_func_start EasySleepMenuInit
EasySleepMenuInit: @ 0x08077500
	push {r4, r5, lr}
	sub sp, #4
	movs r5, #0
	ldr r0, _0807751C @ =gNonGameplayRam
	ldrb r1, [r0, #7]
	adds r4, r0, #0
	cmp r1, #8
	bls _08077512
	b _080776FC
_08077512:
	lsls r0, r1, #2
	ldr r1, _08077520 @ =_08077524
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807751C: .4byte gNonGameplayRam
_08077520: .4byte _08077524
_08077524: @ jump table
	.4byte _08077548 @ case 0
	.4byte _08077564 @ case 1
	.4byte _08077588 @ case 2
	.4byte _080775A0 @ case 3
	.4byte _080775F8 @ case 4
	.4byte _08077658 @ case 5
	.4byte _08077668 @ case 6
	.4byte _08077684 @ case 7
	.4byte _080776EE @ case 8
_08077548:
	ldr r0, _08077560 @ =0x00000202
	bl SoundPlay
	movs r0, #0x11
	movs r1, #0x2b
	bl UpdateMenuOamDataId
	movs r0, #3
	bl unk_77840
	b _08077702
	.align 2, 0
_08077560: .4byte 0x00000202
_08077564:
	ldr r1, _08077578 @ =0x040000D4
	ldr r0, _0807757C @ =0x02010000
	str r0, [r1]
	ldr r0, _08077580 @ =0x0600C000
	str r0, [r1, #4]
	ldr r0, _08077584 @ =0x80000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _08077702
	.align 2, 0
_08077578: .4byte 0x040000D4
_0807757C: .4byte 0x02010000
_08077580: .4byte 0x0600C000
_08077584: .4byte 0x80000400
_08077588:
	ldr r1, _08077598 @ =0x04000050
	ldr r2, _0807759C @ =0x00003FFE
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	movs r0, #0x10
	strh r0, [r1]
	b _08077702
	.align 2, 0
_08077598: .4byte 0x04000050
_0807759C: .4byte 0x00003FFE
_080775A0:
	ldr r0, _080775D0 @ =0x040000D4
	ldr r1, _080775D4 @ =0x0200F000
	str r1, [r0]
	ldr r1, _080775D8 @ =0x0200D380
	str r1, [r0, #4]
	ldr r2, _080775DC @ =0x80000040
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	ldr r1, _080775E0 @ =0x0200F400
	str r1, [r0]
	ldr r1, _080775E4 @ =0x0200D780
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	ldr r1, _080775E8 @ =0x0200F080
	str r1, [r0]
	ldr r1, _080775EC @ =0x0200DB80
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	ldr r1, _080775F0 @ =0x0200F480
	str r1, [r0]
	ldr r1, _080775F4 @ =0x0200DF80
	b _08077626
	.align 2, 0
_080775D0: .4byte 0x040000D4
_080775D4: .4byte 0x0200F000
_080775D8: .4byte 0x0200D380
_080775DC: .4byte 0x80000040
_080775E0: .4byte 0x0200F400
_080775E4: .4byte 0x0200D780
_080775E8: .4byte 0x0200F080
_080775EC: .4byte 0x0200DB80
_080775F0: .4byte 0x0200F480
_080775F4: .4byte 0x0200DF80
_080775F8:
	ldr r0, _08077630 @ =0x040000D4
	ldr r1, _08077634 @ =0x0200F1C0
	str r1, [r0]
	ldr r1, _08077638 @ =0x0200E380
	str r1, [r0, #4]
	ldr r2, _0807763C @ =0x80000040
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	ldr r1, _08077640 @ =0x0200F5C0
	str r1, [r0]
	ldr r1, _08077644 @ =0x0200E780
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	ldr r1, _08077648 @ =0x0200F240
	str r1, [r0]
	ldr r1, _0807764C @ =0x0200EB80
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r1, [r0, #8]
	ldr r1, _08077650 @ =0x0200F640
	str r1, [r0]
	ldr r1, _08077654 @ =0x0200EF80
_08077626:
	str r1, [r0, #4]
	str r2, [r0, #8]
	ldr r0, [r0, #8]
	b _08077702
	.align 2, 0
_08077630: .4byte 0x040000D4
_08077634: .4byte 0x0200F1C0
_08077638: .4byte 0x0200E380
_0807763C: .4byte 0x80000040
_08077640: .4byte 0x0200F5C0
_08077644: .4byte 0x0200E780
_08077648: .4byte 0x0200F240
_0807764C: .4byte 0x0200EB80
_08077650: .4byte 0x0200F640
_08077654: .4byte 0x0200EF80
_08077658:
	ldr r1, _08077660 @ =0x0200D000
	ldr r2, _08077664 @ =0x06006000
	b _0807766C
	.align 2, 0
_08077660: .4byte 0x0200D000
_08077664: .4byte 0x06006000
_08077668:
	ldr r1, _0807767C @ =0x0200E000
	ldr r2, _08077680 @ =0x06007000
_0807766C:
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	b _08077702
	.align 2, 0
_0807767C: .4byte 0x0200E000
_08077680: .4byte 0x06007000
_08077684:
	ldrb r0, [r4, #6]
	cmp r0, #1
	bls _080776FC
	movs r0, #0
	strb r0, [r4, #6]
	ldr r1, _080776D8 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0xb
	bhi _080776DC
	adds r0, #1
	strh r0, [r1]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #6
	bne _080776FC
	movs r3, #0x9a
	lsls r3, r3, #2
	adds r2, r4, r3
	ldrh r1, [r2]
	movs r3, #0x80
	lsls r3, r3, #1
	adds r0, r3, #0
	orrs r0, r1
	strh r0, [r2]
	movs r0, #1
	movs r1, #2
	bl UpdateMenuOamDataId
	movs r0, #0x8c
	strh r0, [r4, #0x3a]
	movs r0, #0x44
	strh r0, [r4, #0x38]
	adds r2, r4, #0
	adds r2, #0x43
	ldrb r1, [r2]
	subs r0, #0x51
	ands r0, r1
	movs r1, #4
	orrs r0, r1
	strb r0, [r2]
	b _080776FC
	.align 2, 0
_080776D8: .4byte gWrittenToBldy
_080776DC:
	movs r0, #0x10
	movs r1, #0x28
	bl UpdateMenuOamDataId
	movs r0, #0x11
	movs r1, #0x2a
	bl UpdateMenuOamDataId
	b _08077702
_080776EE:
	ldr r0, _08077718 @ =gDisableSoftReset
	movs r1, #1
	strb r1, [r0]
	movs r5, #1
	movs r0, #0
	strb r0, [r4, #7]
	strb r0, [r4, #6]
_080776FC:
	movs r0, #0
	cmp r0, #0
	beq _0807770E
_08077702:
	ldr r0, _0807771C @ =gNonGameplayRam
	ldrb r1, [r0, #7]
	adds r1, #1
	movs r2, #0
	strb r1, [r0, #7]
	strb r2, [r0, #6]
_0807770E:
	adds r0, r5, #0
	add sp, #4
	pop {r4, r5}
	pop {r1}
	bx r1
	.align 2, 0
_08077718: .4byte gDisableSoftReset
_0807771C: .4byte gNonGameplayRam

	thumb_func_start EasySleepMenuQuit
EasySleepMenuQuit: @ 0x08077720
	push {r4, r5, r6, lr}
	sub sp, #4
	movs r5, #0
	ldr r0, _0807773C @ =gNonGameplayRam
	ldrb r1, [r0, #7]
	adds r4, r0, #0
	cmp r1, #6
	bls _08077732
	b _08077820
_08077732:
	lsls r0, r1, #2
	ldr r1, _08077740 @ =_08077744
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807773C: .4byte gNonGameplayRam
_08077740: .4byte _08077744
_08077744: @ jump table
	.4byte _08077760 @ case 0
	.4byte _0807776C @ case 1
	.4byte _08077824 @ case 2
	.4byte _080777B8 @ case 3
	.4byte _080777D0 @ case 4
	.4byte _080777F4 @ case 5
	.4byte _08077818 @ case 6
_08077760:
	ldr r1, _08077768 @ =gDisableSoftReset
	movs r0, #0
	strb r0, [r1]
	b _08077824
	.align 2, 0
_08077768: .4byte gDisableSoftReset
_0807776C:
	ldrb r0, [r4, #6]
	cmp r0, #1
	bls _08077820
	movs r0, #0
	strb r0, [r4, #6]
	ldr r1, _080777B0 @ =gWrittenToBldy
	ldrh r0, [r1]
	cmp r0, #0
	beq _08077824
	subs r0, #1
	strh r0, [r1]
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	cmp r0, #6
	bne _08077820
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r4, r0
	ldrh r1, [r2]
	ldr r0, _080777B4 @ =0x0000FEFF
	ands r0, r1
	strh r0, [r2]
	movs r0, #1
	movs r1, #0
	bl UpdateMenuOamDataId
	adds r2, r4, #0
	adds r2, #0x43
	ldrb r1, [r2]
	movs r0, #0xd
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	b _08077820
	.align 2, 0
_080777B0: .4byte gWrittenToBldy
_080777B4: .4byte 0x0000FEFF
_080777B8:
	ldr r2, _080777CC @ =0x06006000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x20
	str r0, [sp]
	movs r0, #3
	movs r1, #0
	bl BitFill
	b _08077824
	.align 2, 0
_080777CC: .4byte 0x06006000
_080777D0:
	ldr r1, _080777E4 @ =0x040000D4
	ldr r0, _080777E8 @ =0x0200F800
	str r0, [r1]
	ldr r0, _080777EC @ =0x0600C000
	str r0, [r1, #4]
	ldr r0, _080777F0 @ =0x80000400
	str r0, [r1, #8]
	ldr r0, [r1, #8]
	b _08077824
	.align 2, 0
_080777E4: .4byte 0x040000D4
_080777E8: .4byte 0x0200F800
_080777EC: .4byte 0x0600C000
_080777F0: .4byte 0x80000400
_080777F4:
	ldr r1, _08077810 @ =0x04000050
	movs r2, #0xfc
	lsls r2, r2, #6
	adds r0, r2, #0
	strh r0, [r1]
	adds r1, #2
	ldr r2, _08077814 @ =0x0000040C
	adds r0, r2, #0
	strh r0, [r1]
	movs r0, #4
	bl unk_77840
	b _08077824
	.align 2, 0
_08077810: .4byte 0x04000050
_08077814: .4byte 0x0000040C
_08077818:
	movs r5, #1
	movs r0, #0
	strb r0, [r4, #7]
	strb r0, [r4, #6]
_08077820:
	cmp r6, #0
	beq _08077830
_08077824:
	ldr r0, _0807783C @ =gNonGameplayRam
	ldrb r1, [r0, #7]
	adds r1, #1
	movs r2, #0
	strb r1, [r0, #7]
	strb r2, [r0, #6]
_08077830:
	adds r0, r5, #0
	add sp, #4
	pop {r4, r5, r6}
	pop {r1}
	bx r1
	.align 2, 0
_0807783C: .4byte gNonGameplayRam

	thumb_func_start unk_77840
unk_77840: @ 0x08077840
	push {r4, r5, r6, lr}
	sub sp, #4
	lsls r0, r0, #0x18
	lsrs r4, r0, #0x18
	movs r6, #0
	ldr r1, _08077860 @ =gNonGameplayRam
	ldrb r0, [r1, #1]
	adds r5, r1, #0
	cmp r0, #0xb
	bls _08077856
	b _08077ADA
_08077856:
	lsls r0, r0, #2
	ldr r1, _08077864 @ =_08077868
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08077860: .4byte gNonGameplayRam
_08077864: .4byte _08077868
_08077868: @ jump table
	.4byte _08077898 @ case 0
	.4byte _08077ADA @ case 1
	.4byte _08077ADA @ case 2
	.4byte _080778C0 @ case 3
	.4byte _080778EC @ case 4
	.4byte _08077944 @ case 5
	.4byte _0807796A @ case 6
	.4byte _080779A4 @ case 7
	.4byte _080779DC @ case 8
	.4byte _08077A24 @ case 9
	.4byte _08077A78 @ case 10
	.4byte _08077AB0 @ case 11
_08077898:
	movs r6, #5
	ldr r1, _080778B4 @ =0x0200C000
	ldr r2, _080778B8 @ =0x06007000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	ldr r1, _080778BC @ =gNonGameplayRam
	movs r0, #8
	strb r0, [r1, #1]
	b _08077ADA
	.align 2, 0
_080778B4: .4byte 0x0200C000
_080778B8: .4byte 0x06007000
_080778BC: .4byte gNonGameplayRam
_080778C0:
	movs r6, #1
	adds r1, r5, #0
	adds r1, #0xd1
	movs r0, #9
	strb r0, [r1]
	adds r1, #0xc
	strb r0, [r1]
	ldr r1, _080778E4 @ =0x0200C000
	ldr r2, _080778E8 @ =0x06007000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	movs r0, #4
	b _08077AD8
	.align 2, 0
_080778E4: .4byte 0x0200C000
_080778E8: .4byte 0x06007000
_080778EC:
	cmp r4, #1
	bne _08077908
	movs r6, #2
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r5, r0
	ldrh r0, [r2]
	movs r3, #0x80
	lsls r3, r3, #1
	adds r1, r3, #0
	eors r0, r1
	strh r0, [r2]
	movs r0, #5
	b _08077AD8
_08077908:
	cmp r4, #3
	bne _08077924
	movs r6, #2
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r5, r0
	ldrh r1, [r2]
	ldr r0, _08077920 @ =0x0000FEFF
	ands r0, r1
	strh r0, [r2]
	movs r0, #6
	b _08077AD8
	.align 2, 0
_08077920: .4byte 0x0000FEFF
_08077924:
	cmp r4, #5
	beq _0807792A
	b _08077ADA
_0807792A:
	movs r6, #3
	movs r3, #0x9a
	lsls r3, r3, #2
	adds r2, r5, r3
	ldrh r1, [r2]
	ldr r0, _08077940 @ =0x0000FEFF
	ands r0, r1
	strh r0, [r2]
	movs r0, #6
	b _08077AD8
	.align 2, 0
_08077940: .4byte 0x0000FEFF
_08077944:
	cmp r4, #2
	bne _08077960
	movs r6, #1
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r5, r0
	ldrh r1, [r2]
	movs r3, #0x80
	lsls r3, r3, #1
	adds r0, r3, #0
	orrs r0, r1
	strh r0, [r2]
	movs r0, #4
	b _080779F6
_08077960:
	cmp r4, #3
	beq _08077966
	b _08077ADA
_08077966:
	movs r0, #7
	b _08077AD8
_0807796A:
	cmp r4, #4
	beq _08077970
	b _08077ADA
_08077970:
	movs r6, #1
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r5, r0
	ldrh r1, [r2]
	movs r3, #0x80
	lsls r3, r3, #1
	adds r0, r3, #0
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _0807799C @ =0x0200C000
	ldr r2, _080779A0 @ =0x06007000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	strb r4, [r5, #1]
	b _08077ADA
	.align 2, 0
_0807799C: .4byte 0x0200C000
_080779A0: .4byte 0x06007000
_080779A4:
	cmp r4, #4
	beq _080779AA
	b _08077ADA
_080779AA:
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r5, r0
	ldrh r1, [r2]
	ldr r0, _080779D0 @ =0x0000FEFF
	ands r0, r1
	strh r0, [r2]
	ldr r1, _080779D4 @ =0x0200C000
	ldr r2, _080779D8 @ =0x06007000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	movs r0, #5
	b _08077AD8
	.align 2, 0
_080779D0: .4byte 0x0000FEFF
_080779D4: .4byte 0x0200C000
_080779D8: .4byte 0x06007000
_080779DC:
	cmp r4, #2
	bne _08077A04
	movs r6, #4
	movs r3, #0x9a
	lsls r3, r3, #2
	adds r2, r5, r3
	ldrh r1, [r2]
	movs r3, #0x80
	lsls r3, r3, #1
	adds r0, r3, #0
	orrs r0, r1
	strh r0, [r2]
	movs r0, #9
_080779F6:
	strb r0, [r5, #1]
	ldr r0, _08077A00 @ =0x00000203
	bl SoundPlay
	b _08077ADA
	.align 2, 0
_08077A00: .4byte 0x00000203
_08077A04:
	cmp r4, #3
	beq _08077A0C
	cmp r4, #5
	bne _08077ADA
_08077A0C:
	movs r6, #6
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r5, r0
	ldrh r1, [r2]
	ldr r0, _08077A20 @ =0x0000FEFF
	ands r0, r1
	strh r0, [r2]
	movs r0, #0xb
	b _08077AD8
	.align 2, 0
_08077A20: .4byte 0x0000FEFF
_08077A24:
	cmp r4, #1
	bne _08077A40
	movs r6, #5
	movs r3, #0x9a
	lsls r3, r3, #2
	adds r2, r5, r3
	ldrh r1, [r2]
	ldr r0, _08077A3C @ =0x0000FEFF
	ands r0, r1
	strh r0, [r2]
	b _08077AD6
	.align 2, 0
_08077A3C: .4byte 0x0000FEFF
_08077A40:
	cmp r4, #3
	bne _08077A5C
	movs r6, #6
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r5, r0
	ldrh r1, [r2]
	ldr r0, _08077A58 @ =0x0000FEFF
	ands r0, r1
	strh r0, [r2]
	movs r0, #0xa
	b _08077AD8
	.align 2, 0
_08077A58: .4byte 0x0000FEFF
_08077A5C:
	cmp r4, #5
	bne _08077ADA
	movs r6, #6
	movs r3, #0x9a
	lsls r3, r3, #2
	adds r2, r5, r3
	ldrh r1, [r2]
	ldr r0, _08077A74 @ =0x0000FEFF
	ands r0, r1
	strh r0, [r2]
	movs r0, #0xa
	b _08077AD8
	.align 2, 0
_08077A74: .4byte 0x0000FEFF
_08077A78:
	cmp r4, #4
	bne _08077ADA
	movs r6, #4
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r5, r0
	ldrh r1, [r2]
	movs r3, #0x80
	lsls r3, r3, #1
	adds r0, r3, #0
	orrs r0, r1
	strh r0, [r2]
	ldr r1, _08077AA8 @ =0x0200C000
	ldr r2, _08077AAC @ =0x06007000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
	movs r0, #9
	b _08077AD8
	.align 2, 0
_08077AA8: .4byte 0x0200C000
_08077AAC: .4byte 0x06007000
_08077AB0:
	cmp r4, #4
	bne _08077ADA
	movs r6, #5
	movs r0, #0x9a
	lsls r0, r0, #2
	adds r2, r5, r0
	ldrh r1, [r2]
	ldr r0, _08077AEC @ =0x0000FEFF
	ands r0, r1
	strh r0, [r2]
	ldr r1, _08077AF0 @ =0x0200C000
	ldr r2, _08077AF4 @ =0x06007000
	movs r3, #0x80
	lsls r3, r3, #5
	movs r0, #0x10
	str r0, [sp]
	movs r0, #3
	bl DmaTransfer
_08077AD6:
	movs r0, #8
_08077AD8:
	strb r0, [r5, #1]
_08077ADA:
	subs r0, r6, #1
	cmp r0, #5
	bls _08077AE2
	b _08077C6E
_08077AE2:
	lsls r0, r0, #2
	ldr r1, _08077AF8 @ =_08077AFC
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_08077AEC: .4byte 0x0000FEFF
_08077AF0: .4byte 0x0200C000
_08077AF4: .4byte 0x06007000
_08077AF8: .4byte _08077AFC
_08077AFC: @ jump table
	.4byte _08077B14 @ case 0
	.4byte _08077B74 @ case 1
	.4byte _08077B94 @ case 2
	.4byte _08077BA8 @ case 3
	.4byte _08077C18 @ case 4
	.4byte _08077C60 @ case 5
_08077B14:
	ldr r4, _08077B70 @ =gNonGameplayRam
	adds r1, r4, #0
	adds r1, #0xd2
	movs r0, #0x59
	strb r0, [r1]
	adds r5, r4, #0
	adds r5, #0xd3
	ldrb r2, [r5]
	movs r1, #4
	rsbs r1, r1, #0
	adds r0, r1, #0
	ands r0, r2
	movs r3, #2
	orrs r0, r3
	movs r2, #0xd
	rsbs r2, r2, #0
	ands r0, r2
	strb r0, [r5]
	adds r5, #0xb
	movs r0, #0x5c
	strb r0, [r5]
	adds r5, #1
	ldrb r0, [r5]
	ands r1, r0
	orrs r1, r3
	ands r1, r2
	movs r0, #4
	orrs r1, r0
	strb r1, [r5]
	adds r0, r4, #0
	adds r0, #0xca
	movs r2, #0x74
	strh r2, [r0]
	subs r0, #2
	movs r1, #0x84
	strh r1, [r0]
	adds r0, #0xe
	strh r2, [r0]
	subs r0, #2
	strh r1, [r0]
	adds r1, r4, #0
	adds r1, #0xbe
	movs r0, #0x1c
	strh r0, [r1]
	b _08077C6E
	.align 2, 0
_08077B70: .4byte gNonGameplayRam
_08077B74:
	ldr r1, _08077B8C @ =gNonGameplayRam
	adds r2, r1, #0
	adds r2, #0xd2
	movs r0, #0
	strb r0, [r2]
	adds r2, #0xc
	strb r0, [r2]
	adds r1, #0xbe
	ldr r0, _08077B90 @ =0x0000FF9C
	strh r0, [r1]
	b _08077C6E
	.align 2, 0
_08077B8C: .4byte gNonGameplayRam
_08077B90: .4byte 0x0000FF9C
_08077B94:
	ldr r0, _08077BA4 @ =gNonGameplayRam
	adds r2, r0, #0
	adds r2, #0xd2
	movs r1, #0
	strb r1, [r2]
	adds r0, #0xde
	b _08077C6C
	.align 2, 0
_08077BA4: .4byte gNonGameplayRam
_08077BA8:
	ldr r4, _08077C14 @ =gNonGameplayRam
	adds r1, r4, #0
	adds r1, #0xd2
	movs r0, #0x59
	strb r0, [r1]
	adds r5, r4, #0
	adds r5, #0xd3
	ldrb r2, [r5]
	movs r1, #4
	rsbs r1, r1, #0
	adds r0, r1, #0
	ands r0, r2
	movs r3, #2
	orrs r0, r3
	movs r2, #0xd
	rsbs r2, r2, #0
	ands r0, r2
	strb r0, [r5]
	adds r5, #0xb
	movs r0, #0x5c
	strb r0, [r5]
	adds r5, #1
	ldrb r0, [r5]
	ands r1, r0
	orrs r1, r3
	ands r1, r2
	movs r0, #4
	orrs r1, r0
	strb r1, [r5]
	adds r0, r4, #0
	adds r0, #0xca
	movs r3, #0
	movs r2, #0x74
	strh r2, [r0]
	subs r0, #2
	movs r1, #0x84
	strh r1, [r0]
	adds r0, #0xe
	strh r2, [r0]
	subs r0, #2
	strh r1, [r0]
	adds r1, r4, #0
	adds r1, #0xd1
	movs r0, #9
	strb r0, [r1]
	adds r1, #0xc
	strb r0, [r1]
	adds r0, r4, #0
	adds r0, #0xd0
	strb r3, [r0]
	adds r0, #0xc
	strb r3, [r0]
	b _08077C6E
	.align 2, 0
_08077C14: .4byte gNonGameplayRam
_08077C18:
	ldr r3, _08077C5C @ =gNonGameplayRam
	adds r1, r3, #0
	adds r1, #0xde
	movs r0, #0
	strb r0, [r1]
	subs r1, #0xc
	movs r0, #0x34
	strb r0, [r1]
	subs r1, #8
	movs r2, #0
	movs r0, #0xca
	strh r0, [r1]
	subs r1, #2
	movs r0, #0x8e
	strh r0, [r1]
	adds r0, r3, #0
	adds r0, #0xd1
	strb r2, [r0]
	subs r0, #1
	strb r2, [r0]
	adds r2, r3, #0
	adds r2, #0xd3
	ldrb r1, [r2]
	movs r0, #4
	rsbs r0, r0, #0
	ands r0, r1
	movs r1, #2
	orrs r0, r1
	movs r1, #0xd
	rsbs r1, r1, #0
	ands r0, r1
	strb r0, [r2]
	b _08077C6E
	.align 2, 0
_08077C5C: .4byte gNonGameplayRam
_08077C60:
	ldr r0, _08077C78 @ =gNonGameplayRam
	adds r2, r0, #0
	adds r2, #0xde
	movs r1, #0
	strb r1, [r2]
	adds r0, #0xd2
_08077C6C:
	strb r1, [r0]
_08077C6E:
	add sp, #4
	pop {r4, r5, r6}
	pop {r0}
	bx r0
	.align 2, 0
_08077C78: .4byte gNonGameplayRam

	thumb_func_start MapScreenUpdateArrowsAndBlinkingSquare
MapScreenUpdateArrowsAndBlinkingSquare: @ 0x08077C7C
	push {r4, r5, lr}
	ldr r3, _08077D4C @ =gNonGameplayRam
	movs r1, #0x84
	lsls r1, r1, #2
	adds r0, r3, r1
	ldrb r0, [r0]
	lsls r0, r0, #3
	ldr r2, _08077D50 @ =gBackgroundPositions
	ldrh r1, [r2, #0xc]
	subs r0, r0, r1
	movs r4, #0xd7
	lsls r4, r4, #1
	adds r1, r3, r4
	strh r0, [r1]
	ldr r5, _08077D54 @ =0x00000211
	adds r0, r3, r5
	ldrb r0, [r0]
	lsls r0, r0, #3
	ldrh r1, [r2, #0xe]
	subs r0, r0, r1
	subs r4, #2
	adds r1, r3, r4
	strh r0, [r1]
	movs r1, #1
	subs r5, #0x67
	adds r0, r3, r5
	ldrb r0, [r0]
	adds r4, r3, #0
	cmp r0, #0x12
	beq _08077CCE
	cmp r0, #0x13
	beq _08077CCE
	cmp r0, #0x14
	beq _08077CCE
	cmp r0, #0x15
	beq _08077CCE
	cmp r0, #0xe
	beq _08077CCE
	cmp r0, #0xf
	beq _08077CCE
	movs r1, #0
_08077CCE:
	cmp r1, #0
	beq _08077CFC
	movs r1, #0x83
	lsls r1, r1, #2
	adds r0, r4, r1
	ldrb r0, [r0]
	lsls r0, r0, #3
	ldrh r1, [r2, #0xc]
	subs r0, r0, r1
	movs r3, #0xd1
	lsls r3, r3, #1
	adds r1, r4, r3
	strh r0, [r1]
	ldr r5, _08077D58 @ =0x0000020D
	adds r0, r4, r5
	ldrb r0, [r0]
	lsls r0, r0, #3
	ldrh r1, [r2, #0xe]
	subs r0, r0, r1
	movs r2, #0xd0
	lsls r2, r2, #1
	adds r1, r4, r2
	strh r0, [r1]
_08077CFC:
	ldr r0, _08077D5C @ =gPauseScreenFlag
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #2
	beq _08077D0A
	b _08077E38
_08077D0A:
	adds r0, r4, #0
	adds r0, #0x28
	ldrb r0, [r0]
	cmp r0, #0
	beq _08077D64
	ldr r3, _08077D60 @ =0x08576158 (sBlob_5760e8_576168+0x70)
	ldrb r1, [r3]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	movs r2, #0x80
	lsls r2, r2, #1
	strh r2, [r0, #0x2e]
	ldrb r1, [r3, #4]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	strh r2, [r0, #0x2e]
	ldrb r1, [r3, #8]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	strh r2, [r0, #0x2e]
	ldrb r1, [r3, #0xc]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r4
	strh r2, [r0, #0x2e]
	b _08077E38
	.align 2, 0
_08077D4C: .4byte gNonGameplayRam
_08077D50: .4byte gBackgroundPositions
_08077D54: .4byte 0x00000211
_08077D58: .4byte 0x0000020D
_08077D5C: .4byte gPauseScreenFlag
_08077D60: .4byte sSecurityUnlockEvents+0x90
_08077D64:
	ldr r2, _08077D8C @ =0x08576158 (sBlob_5760e8_576168+0x70)
	ldrb r1, [r2]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r3, r0, r4
	ldr r5, _08077D90 @ =0x0000025A
	adds r0, r4, r5
	movs r1, #0
	ldrsb r1, [r0, r1]
	subs r5, #2
	adds r0, r4, r5
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	subs r1, r1, r0
	cmp r1, #0xd
	ble _08077D94
	ldrb r0, [r2, #2]
	b _08077D9A
	.align 2, 0
_08077D8C: .4byte sSecurityUnlockEvents+0x90
_08077D90: .4byte 0x0000025A
_08077D94:
	movs r1, #0x80
	lsls r1, r1, #1
	adds r0, r1, #0
_08077D9A:
	strh r0, [r3, #0x2e]
	ldrb r1, [r2, #4]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r3, r0, r4
	movs r5, #0x96
	lsls r5, r5, #2
	adds r0, r4, r5
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	adds r5, #3
	adds r1, r4, r5
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	subs r0, r0, r1
	cmp r0, #0xe
	ble _08077DC6
	ldrb r0, [r2, #6]
	b _08077DCC
_08077DC6:
	movs r1, #0x80
	lsls r1, r1, #1
	adds r0, r1, #0
_08077DCC:
	strh r0, [r3, #0x2e]
	ldrb r1, [r2, #8]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r3, r0, r4
	ldr r5, _08077DF8 @ =0x00000259
	adds r0, r4, r5
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	adds r5, #3
	adds r1, r4, r5
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	subs r0, r0, r1
	cmp r0, #8
	ble _08077DFC
	ldrb r0, [r2, #0xa]
	b _08077E02
	.align 2, 0
_08077DF8: .4byte 0x00000259
_08077DFC:
	movs r1, #0x80
	lsls r1, r1, #1
	adds r0, r1, #0
_08077E02:
	strh r0, [r3, #0x2e]
	ldrb r1, [r2, #0xc]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r3, r0, r4
	ldr r5, _08077E2C @ =0x0000025D
	adds r0, r4, r5
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	subs r5, #4
	adds r1, r4, r5
	ldrb r1, [r1]
	lsls r1, r1, #0x18
	asrs r1, r1, #0x18
	subs r0, r0, r1
	cmp r0, #8
	ble _08077E30
	ldrb r0, [r2, #0xe]
	b _08077E36
	.align 2, 0
_08077E2C: .4byte 0x0000025D
_08077E30:
	movs r1, #0x80
	lsls r1, r1, #1
	adds r0, r1, #0
_08077E36:
	strh r0, [r3, #0x2e]
_08077E38:
	pop {r4, r5}
	pop {r0}
	bx r0
	.align 2, 0

	thumb_func_start MapScreenDrawSpecialOam
MapScreenDrawSpecialOam: @ 0x08077E40
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	lsls r0, r0, #0x18
	lsrs r0, r0, #0x18
	mov r8, r0
	ldr r0, _08077E70 @ =gPauseScreenFlag
	ldrb r0, [r0]
	lsls r0, r0, #0x18
	asrs r0, r0, #0x18
	cmp r0, #4
	bne _08077E5E
	b _080780E0
_08077E5E:
	mov r0, r8
	cmp r0, #1
	beq _08077EF0
	cmp r0, #1
	bgt _08077E74
	cmp r0, #0
	beq _08077E7C
	b _08077F5A
	.align 2, 0
_08077E70: .4byte gPauseScreenFlag
_08077E74:
	mov r1, r8
	cmp r1, #2
	beq _08077F3C
	b _08077F5A
_08077E7C:
	ldr r0, _08077EE0 @ =gNonGameplayRam
	ldrb r1, [r0]
	movs r2, #3
	cmp r1, #0
	beq _08077E88
	movs r2, #1
_08077E88:
	movs r4, #0
	ldr r7, _08077EE4 @ =gEquipment
	ldr r5, _08077EE8 @ =0x08576150 (sBlob_5760e8_576168+0x68)
	mov sb, r2
	movs r2, #4
	rsbs r2, r2, #0
	mov sl, r2
_08077E96:
	movs r6, #0
	ldrb r0, [r7, #0xd]
	adds r3, r4, #1
	cmp r0, #0xff
	beq _08077EA6
	cmp r0, r3
	blt _08077EA6
	movs r6, #1
_08077EA6:
	lsls r2, r4, #1
	adds r0, r2, r5
	ldrb r0, [r0]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	ldr r0, _08077EE0 @ =gNonGameplayRam
	adds r1, r1, r0
	ldr r0, _08077EEC @ =0x08576151 (sBlob_5760e8_576168+0x69)
	adds r2, r2, r0
	ldrb r0, [r2]
	adds r0, r0, r6
	movs r2, #0x36
	strb r0, [r2, r1]
	movs r0, #0x24
	strh r0, [r1, #0x2c]
	movs r0, #0xd4
	strh r0, [r1, #0x2e]
	adds r1, #0x37
	ldrb r2, [r1]
	mov r0, sl
	ands r0, r2
	mov r2, sb
	orrs r0, r2
	strb r0, [r1]
	adds r4, r3, #0
	cmp r4, #3
	bls _08077E96
	b _08077F5A
	.align 2, 0
_08077EE0: .4byte gNonGameplayRam
_08077EE4: .4byte gEquipment
_08077EE8: .4byte sSecurityUnlockEvents+0x88
_08077EEC: .4byte sSecurityUnlockEvents+0x89
_08077EF0:
	movs r4, #0
	ldr r7, _08077F30 @ =gEquipment
	ldr r3, _08077F34 @ =gNonGameplayRam
	mov ip, r3
	ldr r5, _08077F38 @ =0x08576150 (sBlob_5760e8_576168+0x68)
	adds r0, r5, #1
	mov sb, r0
_08077EFE:
	movs r6, #0
	ldrb r0, [r7, #0xd]
	adds r3, r4, #1
	cmp r0, #0xff
	beq _08077F0E
	cmp r0, r3
	blt _08077F0E
	movs r6, #1
_08077F0E:
	lsls r2, r4, #1
	adds r0, r2, r5
	ldrb r1, [r0]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	add r0, ip
	add r2, sb
	ldrb r1, [r2]
	adds r1, r1, r6
	adds r0, #0x36
	strb r1, [r0]
	adds r4, r3, #0
	cmp r4, #3
	bls _08077EFE
	b _08077F5A
	.align 2, 0
_08077F30: .4byte gEquipment
_08077F34: .4byte gNonGameplayRam
_08077F38: .4byte sSecurityUnlockEvents+0x88
_08077F3C:
	movs r4, #0
	ldr r5, _08077F84 @ =gNonGameplayRam
	movs r3, #0
	ldr r2, _08077F88 @ =0x08576150 (sBlob_5760e8_576168+0x68)
_08077F44:
	ldrb r1, [r2]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	adds r0, #0x36
	strb r3, [r0]
	adds r2, #2
	adds r4, #1
	cmp r4, #3
	bls _08077F44
_08077F5A:
	movs r4, #0
	ldr r1, _08077F8C @ =0x03000014
	movs r0, #0
	ldrsb r0, [r1, r0]
	cmp r0, #0
	bne _08077F68
	movs r4, #1
_08077F68:
	ldr r2, _08077F84 @ =gNonGameplayRam
	ldrb r0, [r2]
	cmp r0, #0
	beq _08077F72
	movs r4, #1
_08077F72:
	cmp r4, #0
	beq _08077F90
	ldr r3, _08077F84 @ =gNonGameplayRam
	movs r0, #0x9d
	lsls r0, r0, #2
	adds r1, r3, r0
	movs r0, #0
	b _080780DE
	.align 2, 0
_08077F84: .4byte gNonGameplayRam
_08077F88: .4byte sSecurityUnlockEvents+0x88
_08077F8C: .4byte 0x03000014
_08077F90:
	mov r1, r8
	cmp r1, #0
	beq _08077F98
	b _080780E0
_08077F98:
	movs r4, #3
	cmp r0, #0
	beq _08077FA0
	movs r4, #1
_08077FA0:
	bl PauseScreenMapCountTanks
	movs r0, #0
	bl PauseScreenMapDrawIgtAndTanks
	movs r6, #0
	ldr r7, _080780F0 @ =gNonGameplayRam
	ldr r2, _080780F4 @ =0x0879BE8C (sUnk_79be88+0x4)
	mov r8, r2
	movs r0, #3
	mov ip, r4
	mov r3, ip
	ands r3, r0
	mov ip, r3
	movs r0, #4
	rsbs r0, r0, #0
	mov sb, r0
	mov r5, r8
_08077FC4:
	lsls r3, r6, #2
	ldrb r0, [r5]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r7
	mov r0, r8
	adds r0, #1
	adds r0, r3, r0
	ldrb r0, [r0]
	adds r1, #0x36
	strb r0, [r1]
	ldrb r0, [r5]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r7
	adds r1, #0x37
	ldrb r2, [r1]
	mov r0, sb
	ands r0, r2
	mov r2, ip
	orrs r0, r2
	strb r0, [r1]
	ldrb r1, [r5]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r7
	mov r1, r8
	adds r1, #2
	adds r3, r3, r1
	ldrb r1, [r3]
	strh r1, [r0, #0x2e]
	ldrb r1, [r5]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r7
	ldrb r1, [r5, #3]
	strh r1, [r0, #0x2c]
	adds r5, #4
	adds r6, #1
	cmp r6, #3
	bls _08077FC4
	movs r6, #0
	ldr r7, _080780F8 @ =0x0879BE9C (sUnk_79be88+0x14)
	ldr r5, _080780F0 @ =gNonGameplayRam
	mov ip, r7
	movs r0, #3
	ands r4, r0
	mov r8, r4
	movs r3, #4
	rsbs r3, r3, #0
	mov sb, r3
	adds r4, r7, #0
_08078034:
	lsls r3, r6, #2
	ldrb r0, [r4]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r5
	adds r1, #0x37
	ldrb r2, [r1]
	mov r0, sb
	ands r0, r2
	mov r2, r8
	orrs r0, r2
	strb r0, [r1]
	ldrb r1, [r4]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	mov r1, ip
	adds r1, #2
	adds r3, r3, r1
	ldrb r1, [r3]
	strh r1, [r0, #0x2e]
	ldrb r1, [r4]
	lsls r0, r1, #1
	adds r0, r0, r1
	lsls r0, r0, #2
	adds r0, r0, r5
	ldrb r1, [r4, #3]
	strh r1, [r0, #0x2c]
	adds r4, #4
	adds r6, #1
	cmp r6, #2
	bls _08078034
	ldr r2, _080780F0 @ =gNonGameplayRam
	ldr r3, _080780FC @ =0x00000275
	adds r0, r2, r3
	adds r3, #1
	adds r1, r2, r3
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	bne _0807809A
	ldrb r0, [r7]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r2
	ldrb r0, [r7, #1]
	adds r1, #0x36
	strb r0, [r1]
_0807809A:
	ldr r1, _08078100 @ =0x00000277
	adds r0, r2, r1
	movs r3, #0x9e
	lsls r3, r3, #2
	adds r1, r2, r3
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	bne _080780BC
	ldrb r0, [r7, #4]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	adds r1, r1, r2
	ldrb r0, [r7, #5]
	adds r1, #0x36
	strb r0, [r1]
_080780BC:
	ldr r1, _080780F0 @ =gNonGameplayRam
	ldr r2, _08078104 @ =0x00000279
	adds r0, r1, r2
	ldr r3, _08078108 @ =0x0000027A
	adds r1, r1, r3
	ldrb r0, [r0]
	ldrb r1, [r1]
	cmp r0, r1
	bne _080780E0
	ldrb r0, [r7, #8]
	lsls r1, r0, #1
	adds r1, r1, r0
	lsls r1, r1, #2
	ldr r0, _080780F0 @ =gNonGameplayRam
	adds r1, r1, r0
	ldrb r0, [r7, #9]
	adds r1, #0x36
_080780DE:
	strb r0, [r1]
_080780E0:
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_080780F0: .4byte gNonGameplayRam
_080780F4: .4byte sExploredMinimapBitFlags+0xB0
_080780F8: .4byte sExploredMinimapBitFlags+0xC0
_080780FC: .4byte 0x00000275
_08078100: .4byte 0x00000277
_08078104: .4byte 0x00000279
_08078108: .4byte 0x0000027A
