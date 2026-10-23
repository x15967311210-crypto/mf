    .include "asm/macros.inc"

    .syntax unified

	thumb_func_start PauseScreenProcessOam
PauseScreenProcessOam: @ 0x080783F0
	push {r4, r5, r6, r7, lr}
	mov r7, sl
	mov r6, sb
	mov r5, r8
	push {r5, r6, r7}
	sub sp, #0x10
	ldr r0, _0807844C @ =gOamData
	str r0, [sp, #8]
	ldr r0, _08078450 @ =gNextOamSlot
	ldrb r1, [r0]
	lsls r0, r1, #3
	ldr r2, [sp, #8]
	adds r2, r0, r2
	str r2, [sp, #8]
	str r1, [sp]
	mov sb, r1
	movs r3, #0
	str r3, [sp, #0xc]
_08078414:
	ldr r1, [sp, #0xc]
	lsls r0, r1, #1
	adds r1, r0, r1
	lsls r1, r1, #2
	ldr r3, _08078454 @ =gNonGameplayRam
	adds r2, r1, r3
	adds r3, r2, #0
	adds r3, #0x36
	ldrb r1, [r3]
	adds r7, r0, #0
	cmp r1, #0
	bne _0807842E
	b _08078A36
_0807842E:
	adds r2, #0x37
	ldrb r1, [r2]
	movs r0, #0x11
	rsbs r0, r0, #0
	ands r0, r1
	strb r0, [r2]
	ldrb r0, [r3]
	cmp r0, #0x8b
	bls _08078442
	b _0807868C
_08078442:
	lsls r0, r0, #2
	ldr r1, _08078458 @ =_0807845C
	adds r0, r0, r1
	ldr r0, [r0]
	mov pc, r0
	.align 2, 0
_0807844C: .4byte gOamData
_08078450: .4byte gNextOamSlot
_08078454: .4byte gNonGameplayRam
_08078458: .4byte _0807845C
_0807845C: @ jump table
	.4byte _08078962 @ case 0
	.4byte _080786B4 @ case 1
	.4byte _080786B4 @ case 2
	.4byte _080786B4 @ case 3
	.4byte _080786B4 @ case 4
	.4byte _080786B4 @ case 5
	.4byte _080786B4 @ case 6
	.4byte _080786B4 @ case 7
	.4byte _080786B4 @ case 8
	.4byte _080786B4 @ case 9
	.4byte _0807868C @ case 10
	.4byte _080786B4 @ case 11
	.4byte _080786B4 @ case 12
	.4byte _0807868C @ case 13
	.4byte _080786B4 @ case 14
	.4byte _080786B4 @ case 15
	.4byte _080787F0 @ case 16
	.4byte _0807868C @ case 17
	.4byte _08078708 @ case 18
	.4byte _08078708 @ case 19
	.4byte _08078708 @ case 20
	.4byte _08078708 @ case 21
	.4byte _080786B4 @ case 22
	.4byte _080786B4 @ case 23
	.4byte _080786B4 @ case 24
	.4byte _080786B4 @ case 25
	.4byte _0807868C @ case 26
	.4byte _0807890C @ case 27
	.4byte _0807868C @ case 28
	.4byte _0807890C @ case 29
	.4byte _0807868C @ case 30
	.4byte _0807890C @ case 31
	.4byte _0807868C @ case 32
	.4byte _0807890C @ case 33
	.4byte _0807868C @ case 34
	.4byte _0807890C @ case 35
	.4byte _0807868C @ case 36
	.4byte _0807890C @ case 37
	.4byte _0807868C @ case 38
	.4byte _0807890C @ case 39
	.4byte _080786B4 @ case 40
	.4byte _080786B4 @ case 41
	.4byte _080786B4 @ case 42
	.4byte _080786B4 @ case 43
	.4byte _0807868C @ case 44
	.4byte _0807868C @ case 45
	.4byte _0807868C @ case 46
	.4byte _0807868C @ case 47
	.4byte _0807868C @ case 48
	.4byte _0807868C @ case 49
	.4byte _0807868C @ case 50
	.4byte _0807868C @ case 51
	.4byte _0807868C @ case 52
	.4byte _0807890C @ case 53
	.4byte _0807868C @ case 54
	.4byte _0807868C @ case 55
	.4byte _0807868C @ case 56
	.4byte _0807868C @ case 57
	.4byte _0807868C @ case 58
	.4byte _0807868C @ case 59
	.4byte _0807868C @ case 60
	.4byte _080786B4 @ case 61
	.4byte _080786B4 @ case 62
	.4byte _0807868C @ case 63
	.4byte _0807868C @ case 64
	.4byte _08078780 @ case 65
	.4byte _080787F0 @ case 66
	.4byte _08078780 @ case 67
	.4byte _0807868C @ case 68
	.4byte _08078780 @ case 69
	.4byte _08078780 @ case 70
	.4byte _0807868C @ case 71
	.4byte _08078780 @ case 72
	.4byte _08078780 @ case 73
	.4byte _08078780 @ case 74
	.4byte _080786B4 @ case 75
	.4byte _080786B4 @ case 76
	.4byte _08078780 @ case 77
	.4byte _0807868C @ case 78
	.4byte _080787F0 @ case 79
	.4byte _08078780 @ case 80
	.4byte _0807868C @ case 81
	.4byte _080787F0 @ case 82
	.4byte _08078780 @ case 83
	.4byte _0807868C @ case 84
	.4byte _080787F0 @ case 85
	.4byte _08078780 @ case 86
	.4byte _0807868C @ case 87
	.4byte _080787F0 @ case 88
	.4byte _08078780 @ case 89
	.4byte _0807868C @ case 90
	.4byte _080787F0 @ case 91
	.4byte _08078780 @ case 92
	.4byte _0807868C @ case 93
	.4byte _080787F0 @ case 94
	.4byte _08078844 @ case 95
	.4byte _080786B4 @ case 96
	.4byte _0807868C @ case 97
	.4byte _080787F0 @ case 98
	.4byte _08078898 @ case 99
	.4byte _0807868C @ case 100
	.4byte _0807890C @ case 101
	.4byte _080787F0 @ case 102
	.4byte _080786B4 @ case 103
	.4byte _0807868C @ case 104
	.4byte _0807868C @ case 105
	.4byte _0807868C @ case 106
	.4byte _0807868C @ case 107
	.4byte _0807868C @ case 108
	.4byte _0807868C @ case 109
	.4byte _0807868C @ case 110
	.4byte _0807868C @ case 111
	.4byte _0807868C @ case 112
	.4byte _0807868C @ case 113
	.4byte _0807868C @ case 114
	.4byte _0807868C @ case 115
	.4byte _0807868C @ case 116
	.4byte _0807868C @ case 117
	.4byte _0807868C @ case 118
	.4byte _0807868C @ case 119
	.4byte _0807868C @ case 120
	.4byte _0807868C @ case 121
	.4byte _0807868C @ case 122
	.4byte _0807868C @ case 123
	.4byte _0807868C @ case 124
	.4byte _0807868C @ case 125
	.4byte _0807868C @ case 126
	.4byte _0807868C @ case 127
	.4byte _0807868C @ case 128
	.4byte _0807868C @ case 129
	.4byte _0807868C @ case 130
	.4byte _0807868C @ case 131
	.4byte _0807868C @ case 132
	.4byte _0807868C @ case 133
	.4byte _0807868C @ case 134
	.4byte _0807868C @ case 135
	.4byte _0807868C @ case 136
	.4byte _0807868C @ case 137
	.4byte _0807868C @ case 138
	.4byte _0807868C @ case 139
_0807868C:
	ldr r2, _080786AC @ =0x0879BEC0 (sBlob_79bec0_79c128)
	ldr r0, _080786B0 @ =gNonGameplayRam
	ldr r3, [sp, #0xc]
	adds r1, r7, r3
	lsls r1, r1, #2
	adds r1, r1, r0
	adds r0, r1, #0
	adds r0, #0x36
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r5, [r0]
	adds r1, #0x34
	movs r0, #0
	strb r0, [r1]
	b _08078962
	.align 2, 0
_080786AC: .4byte sExploredMinimapBitFlags+0xE4
_080786B0: .4byte gNonGameplayRam
_080786B4:
	ldr r2, _08078700 @ =0x0879BEC0 (sBlob_79bec0_79c128)
	ldr r1, _08078704 @ =gNonGameplayRam
	ldr r3, [sp, #0xc]
	adds r0, r7, r3
	lsls r0, r0, #2
	adds r1, r0, r1
	adds r0, r1, #0
	adds r0, #0x36
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r5, [r0]
	adds r3, r1, #0
	adds r3, #0x34
	adds r2, r1, #0
	adds r2, #0x35
	ldrb r0, [r2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r1, [r3]
	ldrb r0, [r0, #4]
	cmp r1, r0
	bhs _080786E4
	b _08078962
_080786E4:
	movs r0, #0
	strb r0, [r3]
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldrb r0, [r2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r0, [r0, #4]
	cmp r0, #0
	beq _080786FC
	b _08078962
_080786FC:
	strb r0, [r2]
	b _08078962
	.align 2, 0
_08078700: .4byte sExploredMinimapBitFlags+0xE4
_08078704: .4byte gNonGameplayRam
_08078708:
	ldr r1, _0807876C @ =0x0879BEC0 (sBlob_79bec0_79c128)
	ldr r4, _08078770 @ =gNonGameplayRam
	ldr r2, [sp, #0xc]
	adds r0, r7, r2
	lsls r0, r0, #2
	adds r2, r0, r4
	adds r0, r2, #0
	adds r0, #0x36
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r5, [r0]
	adds r3, r2, #0
	adds r3, #0x34
	adds r2, #0x35
	ldrb r0, [r2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r1, [r3]
	ldrb r0, [r0, #4]
	cmp r1, r0
	bhs _08078736
	b _08078962
_08078736:
	movs r0, #0
	strb r0, [r3]
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldrb r0, [r2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r0, [r0, #4]
	cmp r0, #0
	beq _0807874E
	b _08078962
_0807874E:
	strb r0, [r2]
	adds r0, r4, #0
	adds r0, #0x28
	ldrb r0, [r0]
	cmp r0, #1
	bne _0807875C
	b _08078962
_0807875C:
	ldrb r0, [r4]
	cmp r0, #0
	beq _08078774
	movs r0, #0x8d
	lsls r0, r0, #1
	bl SoundPlay
	b _08078962
	.align 2, 0
_0807876C: .4byte sExploredMinimapBitFlags+0xE4
_08078770: .4byte gNonGameplayRam
_08078774:
	ldr r0, _0807877C @ =0x0000012B
	bl SoundPlay
	b _08078962
	.align 2, 0
_0807877C: .4byte 0x0000012B
_08078780:
	ldr r2, _080787E8 @ =0x0879BEC0 (sBlob_79bec0_79c128)
	ldr r1, _080787EC @ =gNonGameplayRam
	ldr r3, [sp, #0xc]
	adds r0, r7, r3
	lsls r0, r0, #2
	adds r3, r0, r1
	adds r0, r3, #0
	adds r0, #0x36
	ldrb r0, [r0]
	lsls r0, r0, #2
	adds r0, r0, r2
	ldr r5, [r0]
	adds r4, r3, #0
	adds r4, #0x35
	ldrb r0, [r4]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r0, [r0, #0xc]
	cmp r0, #0
	bne _080787B4
	adds r2, r3, #0
	adds r2, #0x37
	ldrb r0, [r2]
	movs r1, #0x10
	orrs r0, r1
	strb r0, [r2]
_080787B4:
	adds r2, r3, #0
	adds r2, #0x34
	ldrb r0, [r4]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r1, [r2]
	ldrb r0, [r0, #4]
	cmp r1, r0
	bhs _080787C8
	b _08078962
_080787C8:
	movs r0, #0
	strb r0, [r2]
	ldrb r0, [r4]
	adds r0, #1
	strb r0, [r4]
	ldrb r1, [r4]
	lsls r0, r1, #3
	adds r0, r0, r5
	ldrb r0, [r0, #4]
	cmp r0, #0
	beq _080787E0
	b _08078962
_080787E0:
	subs r0, r1, #1
	strb r0, [r4]
	b _08078962
	.align 2, 0
_080787E8: .4byte sExploredMinimapBitFlags+0xE4
_080787EC: .4byte gNonGameplayRam
_080787F0:
	ldr r1, _0807883C @ =0x0879BEC0 (sBlob_79bec0_79c128)
	ldr r2, [sp, #0xc]
	adds r0, r7, r2
	lsls r0, r0, #2
	ldr r3, _08078840 @ =gNonGameplayRam
	adds r2, r0, r3
	adds r4, r2, #0
	adds r4, #0x36
	ldrb r0, [r4]
	lsls r0, r0, #2
	adds r0, r0, r1
	ldr r5, [r0]
	adds r3, r2, #0
	adds r3, #0x34
	adds r2, #0x35
	ldrb r0, [r2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r1, [r3]
	ldrb r0, [r0, #4]
	cmp r1, r0
	bhs _0807881E
	b _08078962
_0807881E:
	movs r0, #0
	strb r0, [r3]
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldrb r0, [r2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r0, [r0, #4]
	cmp r0, #0
	beq _08078836
	b _08078962
_08078836:
	strb r0, [r4]
	strb r0, [r2]
	b _08078A36
	.align 2, 0
_0807883C: .4byte sExploredMinimapBitFlags+0xE4
_08078840: .4byte gNonGameplayRam
_08078844:
	ldr r6, _08078890 @ =0x0879BEC0 (sBlob_79bec0_79c128)
	ldr r1, _08078894 @ =gNonGameplayRam
	ldr r2, [sp, #0xc]
	adds r0, r7, r2
	lsls r0, r0, #2
	adds r1, r0, r1
	adds r3, r1, #0
	adds r3, #0x36
	ldrb r0, [r3]
	lsls r0, r0, #2
	adds r0, r0, r6
	ldr r5, [r0]
	adds r4, r1, #0
	adds r4, #0x34
	adds r2, r1, #0
	adds r2, #0x35
	ldrb r0, [r2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r1, [r4]
	ldrb r0, [r0, #4]
	cmp r1, r0
	blo _08078962
	movs r0, #0
	strb r0, [r4]
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldrb r0, [r2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r1, [r0, #4]
	cmp r1, #0
	bne _08078962
	ldrb r0, [r3]
	adds r0, #1
	b _08078954
	.align 2, 0
_08078890: .4byte sExploredMinimapBitFlags+0xE4
_08078894: .4byte gNonGameplayRam
_08078898:
	ldr r3, _08078904 @ =0x0879BEC0 (sBlob_79bec0_79c128)
	mov r8, r3
	ldr r6, _08078908 @ =gNonGameplayRam
	ldr r1, [sp, #0xc]
	adds r0, r7, r1
	lsls r0, r0, #2
	adds r1, r0, r6
	adds r3, r1, #0
	adds r3, #0x36
	ldrb r0, [r3]
	lsls r0, r0, #2
	add r0, r8
	ldr r5, [r0]
	adds r4, r1, #0
	adds r4, #0x34
	adds r2, r1, #0
	adds r2, #0x35
	ldrb r0, [r2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r1, [r4]
	ldrb r0, [r0, #4]
	cmp r1, r0
	blo _08078962
	movs r0, #0
	strb r0, [r4]
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldrb r0, [r2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r1, [r0, #4]
	cmp r1, #0
	bne _08078962
	ldrb r0, [r3]
	adds r0, #1
	strb r0, [r3]
	ldrb r0, [r3]
	lsls r0, r0, #2
	add r0, r8
	ldr r5, [r0]
	strb r1, [r4]
	strb r1, [r2]
	adds r2, r6, #0
	adds r2, #0x7e
	movs r0, #0x67
	strb r0, [r2]
	adds r0, r6, #0
	adds r0, #0x7c
	strb r1, [r0]
	adds r0, #1
	strb r1, [r0]
	b _08078962
	.align 2, 0
_08078904: .4byte sExploredMinimapBitFlags+0xE4
_08078908: .4byte gNonGameplayRam
_0807890C:
	ldr r6, _08078A5C @ =0x0879BEC0 (sBlob_79bec0_79c128)
	ldr r1, _08078A60 @ =gNonGameplayRam
	ldr r2, [sp, #0xc]
	adds r0, r7, r2
	lsls r0, r0, #2
	adds r1, r0, r1
	adds r3, r1, #0
	adds r3, #0x36
	ldrb r0, [r3]
	lsls r0, r0, #2
	adds r0, r0, r6
	ldr r5, [r0]
	adds r4, r1, #0
	adds r4, #0x34
	adds r2, r1, #0
	adds r2, #0x35
	ldrb r0, [r2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r1, [r4]
	ldrb r0, [r0, #4]
	cmp r1, r0
	blo _08078962
	movs r0, #0
	strb r0, [r4]
	ldrb r0, [r2]
	adds r0, #1
	strb r0, [r2]
	ldrb r0, [r2]
	lsls r0, r0, #3
	adds r0, r0, r5
	ldrb r1, [r0, #4]
	cmp r1, #0
	bne _08078962
	ldrb r0, [r3]
	subs r0, #1
_08078954:
	strb r0, [r3]
	ldrb r0, [r3]
	lsls r0, r0, #2
	adds r0, r0, r6
	ldr r5, [r0]
	strb r1, [r4]
	strb r1, [r2]
_08078962:
	ldr r2, _08078A60 @ =gNonGameplayRam
	ldr r3, [sp, #0xc]
	adds r0, r7, r3
	lsls r0, r0, #2
	adds r3, r0, r2
	adds r1, r3, #0
	adds r1, #0x34
	ldrb r0, [r1]
	adds r0, #1
	strb r0, [r1]
	ldrh r0, [r3, #0x2c]
	adds r0, #4
	lsls r0, r0, #0x10
	lsrs r0, r0, #0x10
	str r0, [sp, #4]
	ldrh r0, [r3, #0x2e]
	adds r0, #4
	lsls r0, r0, #0x10
	lsrs r7, r0, #0x10
	adds r0, r3, #0
	adds r0, #0x35
	ldrb r0, [r0]
	lsls r0, r0, #3
	adds r5, r5, r0
	ldr r4, [r5]
	adds r0, r3, #0
	adds r0, #0x37
	ldrb r1, [r0]
	lsls r0, r1, #0x1e
	lsrs r6, r0, #0x1e
	lsls r1, r1, #0x1c
	lsrs r3, r1, #0x1e
	ldrh r0, [r4]
	ldr r1, [sp]
	adds r0, r1, r0
	cmp r0, #0x7f
	bgt _08078A42
	str r0, [sp]
	adds r4, #2
	cmp sb, r0
	bge _08078A36
	ldr r0, _08078A64 @ =gOamData
	lsls r1, r7, #0x10
	asrs r1, r1, #0x10
	mov r8, r1
	lsls r6, r6, #2
	mov ip, r6
	lsls r7, r3, #2
	mov r2, sb
	lsls r1, r2, #3
	adds r3, r1, r0
	ldr r0, _08078A68 @ =0x000001FF
	mov sl, r0
	movs r6, #0xd
	rsbs r6, r6, #0
	ldr r1, [sp]
	subs r1, r1, r2
	mov sb, r1
_080789D6:
	ldrh r0, [r4]
	adds r4, #2
	ldr r2, [sp, #8]
	strh r0, [r2]
	adds r2, #2
	ldr r1, [sp, #4]
	adds r0, r1, r0
	strb r0, [r3]
	ldrh r1, [r4]
	adds r4, #2
	strh r1, [r2]
	adds r2, #2
	str r2, [sp, #8]
	add r1, r8
	mov r2, sl
	ands r1, r2
	ldrh r2, [r3, #2]
	ldr r0, _08078A6C @ =0xFFFFFE00
	ands r0, r2
	orrs r0, r1
	strh r0, [r3, #2]
	ldrh r0, [r4]
	ldr r1, [sp, #8]
	strh r0, [r1]
	adds r4, #2
	ldrb r1, [r3, #5]
	adds r0, r6, #0
	ands r0, r1
	mov r2, ip
	orrs r0, r2
	strb r0, [r3, #5]
	ldrb r1, [r3, #1]
	adds r0, r6, #0
	ands r0, r1
	orrs r0, r7
	strb r0, [r3, #1]
	ldr r0, [sp, #8]
	adds r0, #4
	str r0, [sp, #8]
	adds r3, #8
	movs r1, #1
	rsbs r1, r1, #0
	add sb, r1
	mov r2, sb
	cmp r2, #0
	bne _080789D6
	ldr r3, [sp]
	mov sb, r3
_08078A36:
	ldr r0, [sp, #0xc]
	adds r0, #1
	str r0, [sp, #0xc]
	cmp r0, #0x27
	bgt _08078A42
	b _08078414
_08078A42:
	ldr r0, _08078A70 @ =gNextOamSlot
	mov r1, sp
	ldrb r1, [r1]
	strb r1, [r0]
	add sp, #0x10
	pop {r3, r4, r5}
	mov r8, r3
	mov sb, r4
	mov sl, r5
	pop {r4, r5, r6, r7}
	pop {r0}
	bx r0
	.align 2, 0
_08078A5C: .4byte sExploredMinimapBitFlags+0xE4
_08078A60: .4byte gNonGameplayRam
_08078A64: .4byte gOamData
_08078A68: .4byte 0x000001FF
_08078A6C: .4byte 0xFFFFFE00
_08078A70: .4byte gNextOamSlot

