.equ N, 16

.text
	.global _start
	.global PRINT

_start:
	la t4, a                   # t4 holds the base address of array a
	la t5, a
	addi t5, t5, 64            # t5 holds the address of last enelemt in a
	la t6, PRINT               # t6 holds 0xFFFC for print, for done use 4(t6)
	call printArray
	sw zero, 4(t6)

printArray:
	mv t0, t4                  # t0 is the pointer of current element
	.loop:
		lw t2, 0(t0)       # load the element
		sw t2, 0(t6)       # print
		addi t0, t0, 4     # move pointer to next element
		blt t0, t5, .loop  # loop until the last element
	ret

.data
	a: .word 0xf, 0xa, 0xb, 0xe, 0x9, 0x1, 0x8, 0x4, 0x6, 0x2, 0x5, 0x7, 0x3, 0xc, 0x0, 0xd
