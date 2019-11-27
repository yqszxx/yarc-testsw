.text
	.global _start
	.global GPIO
	.global DONE

_start:
	la gp, 0x1000
	li t0, 0x81828384
	sb t0, 0(gp)
	lw t1, 0(gp)
	la gp, DONE
	sw t1, 0(gp)

