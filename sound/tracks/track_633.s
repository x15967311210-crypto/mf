.align 2

.global track_633

track_633_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 28
	.byte VOL, 127
	.byte PAN, c_v
	.byte N24, Cn3, v127
	.byte W24
	.byte W03
	.byte FINE

.align 2

track_633:
	.byte 1
	.byte 0
	.byte 180
	.byte 0
	.word sMusicCommandFunctionPointers+0x240C
	.word track_633_0

.align 2
