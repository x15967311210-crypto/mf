.align 2

.global track_204

track_204_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 45
	.byte VOL, 60
	.byte PAN, c_v
	.byte N48, Cn3, v112
	.byte W56
	.byte FINE

.align 2

track_204:
	.byte 1
	.byte 0
	.byte 195
	.byte 0
	.word sMusicCommandFunctionPointers+0x1458
	.word track_204_0

.align 2
