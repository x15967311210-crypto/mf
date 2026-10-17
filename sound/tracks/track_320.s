.align 2

.global track_320

track_320_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 12
	.byte VOL, 62
	.byte PAN, c_v
	.byte N15, An2, v127
	.byte W04
	.byte VOL, 78
	.byte W11
	.byte FINE

.align 2

track_320:
	.byte 1
	.byte 0
	.byte 197
	.byte 0
	.word sMusicCommandFunctionPointers+0x2C58
	.word track_320_0

.align 2
