.align 2

.global track_250

track_250_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 2
	.byte VOL, 75
	.byte PAN, c_v
	.byte N24, Cn3, v127
	.byte W24
	.byte FINE

.align 2

track_250:
	.byte 1
	.byte 0
	.byte 220
	.byte 0
	.word sMusicCommandFunctionPointers+0x1B54
	.word track_250_0

.align 2
