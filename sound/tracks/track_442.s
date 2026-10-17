.align 2

.global track_442

track_442_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 78
	.byte VOL, 62
	.byte PAN, c_v
	.byte N15, Cn3, v127
	.byte W15
	.byte Cn3, v032 @ N15
	.byte W15
	.byte Cn3, v012 @ N15
	.byte W15
	.byte FINE

.align 2

track_442:
	.byte 1
	.byte 0
	.byte 181
	.byte 0
	.word sMusicCommandFunctionPointers+0x16BC
	.word track_442_0

.align 2
