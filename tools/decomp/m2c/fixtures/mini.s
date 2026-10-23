@ tools/decomp/m2c/fixtures/mini.s -- tiny split-disassembly fixture used by
@ `extract.py --self-check` and `run.sh --self-check`.
@
@ The shape (thumb_func_start macro, column-0 label with an @ 0x... comment,
@ .4byte literal pool, no .size directive) is copied from asm/*.s, but the code
@ is synthetic: two thumb functions, one arm function, two literal pools.

	.syntax unified


	thumb_func_start Mini_Add
Mini_Add: @ 0x08000000
	adds r0, r0, r1
	ldr r1, _08000008
	bx lr
	.align 2, 0
_08000008: .4byte 0x03001234

	thumb_func_start Mini_Next
Mini_Next: @ 0x08000010
	movs r0, #1
	.align 2, 0
_08000014: .4byte 0x0000FFFF

	arm_func_start Mini_Arm
Mini_Arm: @ 0x08000018
	mov r0, #0
	bx lr
