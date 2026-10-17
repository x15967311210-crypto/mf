.align 2

.global track_651

track_651_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 3
	.byte VOL, 50
	.byte PAN, c_v
	.byte N32, Cn3, v127
	.byte W32
	.byte FINE

.align 2

track_651:
	.byte 1
	.byte 0
	.byte 170
	.byte 0
	.word sMusicCommandFunctionPointers+0x2778
	.word track_651_0

.align 2
