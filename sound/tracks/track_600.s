.align 2

.global track_600

track_600_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 20
	.byte VOL, 50
	.byte PAN, c_v
	.byte N30, Cn3, v127
	.byte W30
	.byte FINE

.align 2

track_600:
	.byte 1
	.byte 0
	.byte 180
	.byte 0
	.word sMusicCommandFunctionPointers+0x1FBC
	.word track_600_0

.align 2
