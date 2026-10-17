.align 2

.global track_296

track_296_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 56
	.byte VOL, 70
	.byte PAN, c_v
	.byte PRIO, 1
	.byte N03, Fn1, v127
	.byte W03
	.byte FINE

.align 2

track_296:
	.byte 1
	.byte 0
	.byte 161
	.byte 0
	.word sMusicCommandFunctionPointers+0x1B54
	.word track_296_0

.align 2
