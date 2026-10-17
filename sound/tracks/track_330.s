.align 2

.global track_330

track_330_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 34
	.byte VOL, 40
	.byte PAN, c_v
	.byte N07, Cn3, v127
	.byte W07
	.byte FINE

.align 2

track_330:
	.byte 1
	.byte 0
	.byte 166
	.byte 0
	.word sMusicCommandFunctionPointers+0x16BC
	.word track_330_0

.align 2
