.align 2

.global track_116

track_116_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 2
	.byte VOL, 65
	.byte PAN, c_v
	.byte N04, Cn3, v127
	.byte W04
	.byte FINE

.align 2

track_116:
	.byte 1
	.byte 0
	.byte 163
	.byte 0
	.word sMusicCommandFunctionPointers+0x1194
	.word track_116_0

.align 2
