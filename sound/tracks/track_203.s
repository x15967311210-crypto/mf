.align 2

.global track_203

track_203_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 47
	.byte VOL, 60
	.byte PAN, c_v
	.byte N44, Cn3, v127
	.byte W54
	.byte FINE

.align 2

track_203:
	.byte 1
	.byte 0
	.byte 195
	.byte 0
	.word sMusicCommandFunctionPointers+0x1458
	.word track_203_0

.align 2
