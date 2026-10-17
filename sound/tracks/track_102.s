.align 2

.global track_102

track_102_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 40
	.byte VOL, 20
	.byte PAN, c_v
	.byte N07, Cn3, v127
	.byte W07
	.byte FINE

.align 2

track_102:
	.byte 1
	.byte 0
	.byte 162
	.byte 0
	.word sMusicCommandFunctionPointers+0x1194
	.word track_102_0

.align 2
