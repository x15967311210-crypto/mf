.align 2

.global track_647

track_647_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 20
	.byte VOL, 50
	.byte PAN, c_v
	.byte N02, Gn2, v127
	.byte W02
	.byte N05, En3 @ v127
	.byte W05
	.byte FINE

.align 2

track_647:
	.byte 1
	.byte 0
	.byte 170
	.byte 0
	.word sMusicCommandFunctionPointers+0x267C
	.word track_647_0

.align 2
