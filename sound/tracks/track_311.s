.align 2

.global track_311

track_311_0:
	.byte KEYSH, 0
	.byte TEMPO, 75
	.byte VOICE, 5
	.byte VOL, 28
	.byte PAN, c_v
	.byte BENDR, 12
	.byte BEND, c_v
	.byte N18, Cn2, v127
	.byte W06
	.byte VOL, 56
	.byte BEND, c_v+15
	.byte W06
	.byte VOL, 85
	.byte BEND, c_v+31
	.byte W06
	.byte FINE

.align 2

track_311:
	.byte 1
	.byte 0
	.byte 180
	.byte 0
	.word sMusicCommandFunctionPointers+0x2C58
	.word track_311_0

.align 2
