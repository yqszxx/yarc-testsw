.text
	.global _start
	.global GPIO
	.global DONE

_start:
	la   gp, GPIO    # gp = *GPIO
	li   t0, 0       # t0 = 0
	li   t2, 857143  # t2 = 1/2s@12MHz, 7142@100kHz
	li   t1, 0       # t1 = 0
L1:
	bne  t0, t2, L2  # if t0 != t2 then goto L2
	not  t1, t1      # t1 = ~t1
	sw   t1, 0(gp)   # *GPIO = t1
	li   t0, 0       # t0 = 0
L2:
	addi t0, t0, 1   # t0++
	j    L1          # goto L1

