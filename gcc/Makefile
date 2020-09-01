all:
	gcc 512c.c TestMul.c const.c  asm/ntt.s asm/invntt.s asm/pointwise.S  asm/512.s -O3 -mtune=native  -march=native
