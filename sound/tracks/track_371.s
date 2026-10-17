.align 2

.global track_371

track_371_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 40
	.byte VOL, 25
	.byte PAN, c_v
	.byte N03, En3, v080
	.byte W03
	.byte En3, v040 @ N03
	.byte W03
	.byte FINE

.align 2

track_371:
	.byte 1
	.byte 0
	.byte 143
	.byte 0
	.word sMusicCommandFunctionPointers+0x16BC
	.word track_371_0

.align 2
