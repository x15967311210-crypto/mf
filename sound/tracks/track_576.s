.align 2

.global track_576

track_576_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 63
	.byte VOL, 65
	.byte PAN, c_v
	.byte W05
	.byte N44, Cn3, v127
	.byte W44
	.byte W01
	.byte FINE

.align 2

track_576:
	.byte 1
	.byte 0
	.byte 226
	.byte 0
	.word sMusicCommandFunctionPointers+0x2100
	.word track_576_0

.align 2
