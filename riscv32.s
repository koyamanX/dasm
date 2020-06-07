.text
.globl _start
_start:
	add x1, x2, x3
	mul x1, x2, x3
	xor x1, x2, x3
	nop
	sub x1, x2, x3
	and x1, x2, x3
	j _start
