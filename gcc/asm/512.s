.macro acc_512	 
vpaddq      %zmm10, %zmm2, %zmm2
vpaddq      %zmm11, %zmm3, %zmm3
vpaddq      %zmm12, %zmm4, %zmm4
vpaddq      %zmm13, %zmm5, %zmm5

vpaddq      %zmm14, %zmm6, %zmm6
vpaddq      %zmm15, %zmm7, %zmm7
vpaddq      %zmm16, %zmm8, %zmm8
vpaddq      %zmm17, %zmm9, %zmm9
.endm
	
.macro pointwise_512  off
vmovdqa32    \off(%rsi),%zmm10
vmovdqa32    \off+0x40(%rsi),%zmm12
vmovdqa32    \off+0x80(%rsi),%zmm14
vmovdqa32    \off+0xC0(%rsi),%zmm16 

vmovdqa32    \off(%rdx),%zmm18 
vmovdqa32    \off+0x40(%rdx),%zmm20
vmovdqa32    \off+0x80(%rdx),%zmm22
vmovdqa32    \off+0xC0(%rdx),%zmm24

vpsrlq		$32, %zmm10,%zmm11 
vpsrlq		$32, %zmm12,%zmm13
vpsrlq		$32, %zmm14,%zmm15
vpsrlq		$32, %zmm16,%zmm17 
vpsrlq		$32, %zmm18,%zmm19 
vpsrlq		$32, %zmm20,%zmm21 
vpsrlq		$32, %zmm22,%zmm23
vpsrlq		$32, %zmm24,%zmm25 	

vpmuludq	%zmm10, %zmm18, %zmm10 	
vpmuludq	%zmm11, %zmm19, %zmm11 	
vpmuludq	%zmm12, %zmm20, %zmm12 	
vpmuludq	%zmm13, %zmm21, %zmm13 	
vpmuludq	%zmm14, %zmm22, %zmm14 	
vpmuludq	%zmm15, %zmm23, %zmm15 	
vpmuludq	%zmm16, %zmm24, %zmm16 	
vpmuludq	%zmm17, %zmm25, %zmm17 
.endm



.macro cpp_butterfly_512_asm		zmmz0,zmmz1,zmmz2,zmmz3,rl0,rl1,rl2,rl3,rh0,rh1,rh2,rh3	
vpmuludq %zmm\zmmz0, %zmm\rh0, %zmm\rh0
vpmuludq %zmm\zmmz1, %zmm\rh1, %zmm\rh1

vpmuludq %zmm\zmmz2, %zmm\rh2, %zmm\rh2
vpmuludq %zmm\zmmz3, %zmm\rh3, %zmm\rh3

vpmuludq %zmm0, %zmm\rh0, %zmm12
vpmuludq %zmm0, %zmm\rh1, %zmm13

vpmuludq %zmm0, %zmm\rh2, %zmm14
vpmuludq %zmm0, %zmm\rh3, %zmm15

vpmuludq %zmm1,  %zmm12, %zmm12
vpmuludq %zmm1,  %zmm13, %zmm13
vpmuludq %zmm1,  %zmm14, %zmm14
vpmuludq %zmm1,  %zmm15, %zmm15

vpaddq	%zmm\rh0, %zmm12, %zmm12
vpaddq	%zmm\rh1, %zmm13, %zmm13 
vpaddq	%zmm\rh2, %zmm14, %zmm14
vpaddq	%zmm\rh3, %zmm15, %zmm15

vpsrlq	$32, %zmm12, %zmm12
vpsrlq	$32, %zmm13, %zmm13
vpsrlq	$32, %zmm14, %zmm14
vpsrlq	$32, %zmm15, %zmm15

vpaddd	%zmm2, %zmm\rh0, %zmm\rl0
vpaddd	%zmm2, %zmm\rh1, %zmm\rl1 
vpaddd	%zmm2, %zmm\rh2, %zmm\rl2
vpaddd	%zmm2, %zmm\rh3, %zmm\rl3

vpaddd	%zmm12, %zmm\rl0, %zmm\rl0
vpaddd	%zmm13, %zmm\rl1, %zmm\rl1
vpaddd	%zmm14, %zmm\rl2, %zmm\rl2
vpaddd	%zmm15, %zmm\rl3, %zmm\rl3

vpsubd	%zmm12, %zmm\rh0, %zmm\rh0
vpsubd	%zmm13, %zmm\rh1, %zmm\rh1
vpsubd	%zmm14, %zmm\rh2, %zmm\rh2
vpsubd	%zmm15, %zmm\rh3, %zmm\rh3
.endm


.global new_pointwise_acc_asm_512
new_pointwise_acc_asm_512:
push %rbp
mov		%rsp, %rbp
and		$31, %rbp
add		$64,%rbp
sub		%rbp, %rsp
push	%rbx

xor %rbx,%rbx
mov         $-21846, %ebx 
kmovw       %ebx,%k1

vmovdqa32  _8xqinv_512(%rip),%zmm0

vmovdqa32  _8xq_512(%rip),%zmm1
mov  $4,%eax

_looptop2_:
pointwise_512 0x400
acc_512

#;if L ge 3
pointwise_512 2048
acc_512
#;endif

#;if L ge 4
pointwise_512 3072
acc_512;
#;endif

#;if L ge 5
pointwise_512 0x1000
acc_512;
#;endif

vpmuludq	%zmm0, %zmm2, %zmm10
vpmuludq	%zmm0, %zmm3, %zmm11
vpmuludq	%zmm0, %zmm4, %zmm12
vpmuludq	%zmm0, %zmm5, %zmm13
vpmuludq	%zmm0, %zmm6, %zmm14
vpmuludq	%zmm0, %zmm7, %zmm15
vpmuludq	%zmm0, %zmm8, %zmm16
vpmuludq	%zmm0, %zmm9, %zmm17

vpmuludq	%zmm1, %zmm10, %zmm10
vpmuludq	%zmm1, %zmm11, %zmm11
vpmuludq	%zmm1, %zmm12, %zmm12
vpmuludq	%zmm1, %zmm13, %zmm13
vpmuludq	%zmm1, %zmm14, %zmm14
vpmuludq	%zmm1, %zmm15, %zmm15
vpmuludq	%zmm1, %zmm16, %zmm16
vpmuludq	%zmm1, %zmm17, %zmm17

VPADDQ	%zmm2, %zmm10, %zmm2
VPADDQ	%zmm3, %zmm11, %zmm3
VPADDQ	%zmm4, %zmm12, %zmm4
VPADDQ	%zmm5, %zmm13, %zmm5
VPADDQ	%zmm6, %zmm14, %zmm6
VPADDQ	%zmm7, %zmm15, %zmm7
VPADDQ	%zmm8, %zmm16, %zmm8
VPADDQ	%zmm9, %zmm17, %zmm9
		
vpsrlq		$32, %zmm2, %zmm2
vpsrlq		$32, %zmm4, %zmm4
vpsrlq		$32, %zmm6, %zmm6
vpsrlq		$32, %zmm8, %zmm8

vpblendmd   %zmm3, %zmm2, %zmm2{%k1}   
vpblendmd   %zmm5, %zmm4, %zmm4{%k1} 
vpblendmd   %zmm7, %zmm6, %zmm6{%k1}   
vpblendmd   %zmm9, %zmm8, %zmm8{%k1}   

vmovdqa32 %zmm2, (%rdi) 
vmovdqa32 %zmm4, 0x40(%rdi) 
vmovdqa32 %zmm6, 0x80(%rdi) 
vmovdqa32 %zmm8, 0xC0(%rdi) 

lea 0x100(%rsi),%rsi 
lea  0x100(%rdx ),%rdx  

lea	0x100(%rdi), %rdi 
dec	%eax
jnz	_looptop2_
pop	%rbx
add		%rbp, %rsp
pop		%rbp

ret


.global new_ntt_512_asm__
new_ntt_512_asm__:
push %rbp
mov		%rsp, %rbp
and		$63,%rbp
add		$2368, %rbp
sub		%rbp, %rsp
mov	%rsp,%r9
add	$64,%r9
mov	%r9,%r11	#; float registers
add	$2048, %r11

push %RBX

movaps      %xmm15, (%r11)
movaps      %xmm14, 0x10(%r11)
movaps      %xmm13, 0x20(%r11)
movaps      %xmm12, 0x30(%r11)
movaps      %xmm11, 0x40(%r11)
movaps      %xmm10, 0x50(%r11)
movaps      %xmm9, 0x60(%r11)
movaps      %xmm8, 0x70(%r11)
movaps      %xmm7, 0x80(%r11)
movaps      %xmm6, 0x90(%r11)

vmovdqa32 _8xqinv_512(%rip),%zmm0
vmovdqa32 _8xq_512(%rip),%zmm1
vmovdqa32 _8x2q_512(%rip),%zmm2

push	%rsi 
push	%r9
mov	$4,%eax
loop1:
vpmovzxdq	(%rsi),%zmm24 
vpmovzxdq	0x80(%rsi),%zmm25
vpmovzxdq	0x100(%rsi),%zmm26
vpmovzxdq	0x180(%rsi),%zmm27
vpmovzxdq	0x200(%rsi),%zmm28
vpmovzxdq	0x280(%rsi),%zmm29
vpmovzxdq	0x300(%rsi),%zmm30
vpmovzxdq	0x380(%rsi),%zmm31

cpp_butterfly_512_asm 16,16,16,16,24,25,26,27,28,29,30,31	

cpp_butterfly_512_asm 17,17,18,18,24,25,28,29,26,27,30,31	

cpp_butterfly_512_asm 19,20,21,22,24,26,28,30,25,27,29,31	

vmovdqa32	%zmm24, (%r9)
vmovdqa32	%zmm25, 0x100(%r9)
vmovdqa32	%zmm26, 0x200(%r9)
vmovdqa32	%zmm27, 0x300(%r9)
vmovdqa32	%zmm28, 0x400(%r9)
vmovdqa32	%zmm29, 0x500(%r9)
vmovdqa32	%zmm30, 0x600(%r9)
vmovdqa32	%zmm31, 0x700(%r9)

lea	0x40(%r9), %r9
lea	0x20(%rsi),%rsi 
dec %eax
jnz	loop1
pop	%r9
pop	%rsi 

lea	0x20(%rdx),%rdx  
mov $4,%eax

loop2:
mov	%rdx, %r10 
lea	0x7c(%r10),%r10

vmovdqa32	(%r9),%zmm24
vmovdqa32	0x40(%r9),%zmm25
vmovdqa32	0x80(%r9),%zmm26
vmovdqa32	0xc0(%r9),%zmm27
vmovdqa32	0x100(%r9),%zmm28
vmovdqa32	0x140(%r9),%zmm29
vmovdqa32	0x180(%r9),%zmm30
vmovdqa32	0x1c0(%r9),%zmm31

vlddqu (%rdx),%ymm3 #;;; win(r8) lin(rdx)
vlddqu (%r10),%ymm4
vpbroadcastd	%xmm3, %zmm12
vpbroadcastd	%xmm4, %zmm13


cpp_butterfly_512_asm 12, 12, 13, 13, 24, 25, 28, 29, 26, 27, 30, 31

vpsrldq $4,%ymm3, %ymm3
vpsrldq $4,%ymm4, %ymm4
vpbroadcastd	%xmm3, %zmm12
vpbroadcastd	%xmm4, %zmm14

vpsrldq $4,%ymm3, %ymm3
vpsrldq $4,%ymm4, %ymm4
vpbroadcastd	%xmm3, %zmm13
vpbroadcastd	%xmm4, %zmm15
		
mov         $-3856,%ebx  
kmovw       %ebx,%k1

vpblendmd   %zmm13, %zmm12, %zmm12{%k1}
vpblendmd   %zmm15, %zmm14, %zmm14{%k1}

vmovdqu32	%zmm24, %zmm23
vmovdqu32	const1_512(%rip),%zmm15
vmovdqu32	const1_512_(%rip),%zmm16
vpermt2q    %zmm26,%zmm15,%zmm23 

vpermt2q    %zmm26,%zmm16,%zmm24
vmovdqu32	%zmm24, %zmm26
vmovdqu32	 %zmm25,%zmm24
vpermt2q    %zmm27,%zmm15,%zmm24
vpermt2q    %zmm27,%zmm16,%zmm25
vmovdqu32	%zmm25, %zmm27
vmovdqu32	%zmm28, %zmm25
vpermt2q    %zmm30,%zmm15,%zmm25
vpermt2q    %zmm30,%zmm16,%zmm28
vmovdqu32	%zmm28, %zmm30
vmovdqu32	%zmm29, %zmm28
vpermt2q    %zmm31,%zmm15,%zmm28
vpermt2q    %zmm31,%zmm16,%zmm29
vmovdqu32	%zmm29, %zmm31

cpp_butterfly_512_asm 12, 12, 14, 14, 23, 26, 25, 30, 24, 27, 28, 31

vbroadcasti64x2	0xc(%rdx),%ymm3 #;;; win(r8) lin(rdx)
vbroadcasti64x2	0xc(%r10),%ymm4

vpmovzxdq	%ymm3, %zmm12
vpmovzxdq	%ymm4, %zmm13

vmovdqu32	const2_512(%rip),%zmm15
vmovdqu32	const2_512_(%rip),%zmm16
vmovdqu32	%zmm23, %zmm29

vpermt2q    %zmm24,%zmm15,%zmm29
vpermt2q    %zmm24,%zmm16,%zmm23
vmovdqu32	%zmm23, %zmm24
vmovdqu32	%zmm26, %zmm23
vpermt2q    %zmm27,%zmm15,%zmm23
vpermt2q    %zmm27,%zmm16,%zmm26
vmovdqu32	%zmm26, %zmm27
vmovdqu32	%zmm25, %zmm26
vpermt2q    %zmm28,%zmm15,%zmm26
vpermt2q    %zmm28,%zmm16,%zmm25
vmovdqu32	%zmm25, %zmm28
vmovdqu32	%zmm30, %zmm25
vpermt2q    %zmm31,%zmm15,%zmm25
vpermt2q    %zmm31,%zmm16,%zmm30
vmovdqu32	%zmm30, %zmm31

cpp_butterfly_512_asm 12, 12, 13, 13, 29, 24, 26, 28, 23, 27, 25, 31

vlddqu	0x1c(%rdx),%ymm3 #;;;; win(r8) lin(rdx)
vlddqu	0x1c(%rdx),%ymm4
vpmovzxdq %ymm3, %zmm13
vpmovzxdq %ymm4, %zmm15

vmovdqu32	const5_512(%rip),%zmm3	
vmovdqu32	const5_512_(%rip),%zmm4
vpermq %zmm13, %zmm3, %zmm12
vpermq %zmm13, %zmm4, %zmm13
vpermq %zmm15, %zmm3, %zmm14
vpermq %zmm15, %zmm4, %zmm15

cpp_butterfly_512_asm	12, 13, 14, 15, 29, 23, 26, 25, 24, 27, 28, 31

vlddqu 0x3c(%rdx),%ymm3 #;;; win(r8) lin(rdx)
vlddqu	0x5c(%rdx),%ymm4 
vlddqu 0x3c(%r10),%ymm5
vlddqu 0x5c(%r10),%ymm6

vpmovzxdq	%ymm3, %zmm12
vpmovzxdq	%ymm4, %zmm13
vpmovzxdq	%ymm5, %zmm14
vpmovzxdq	%ymm6, %zmm15

vmovdqu32	const6_512(%rip),%zmm17
vmovdqu32	const6_512(%rip),%zmm16
vmovdqu32	%zmm29, %zmm19

vpermt2q    %zmm24, %zmm17,%zmm19 
vpermt2q    %zmm24, %zmm16,%zmm29 
vmovdqu32	%zmm29, %zmm24
vmovdqu32	%zmm23, %zmm20
vpermt2q    %zmm27, %zmm17,%zmm20 
vpermt2q    %zmm27, %zmm16,%zmm23 
vmovdqu32	%zmm23, %zmm27
vmovdqu32	%zmm26, %zmm11
vpermt2q    %zmm28, %zmm17,%zmm11 
vpermt2q    %zmm28, %zmm16,%zmm26 
vmovdqu32	%zmm26, %zmm28
vmovdqu32	%zmm25, %zmm10
vpermt2q    %zmm31, %zmm17,%zmm10 
vpermt2q    %zmm31, %zmm16,%zmm25 
vmovdqu32	%zmm25, %zmm31
		
cpp_butterfly_512_asm 12, 13, 14, 15, 19, 20, 11, 10, 29, 23, 28, 31

vmovdqu32	const3_512(%rip),%zmm17
vpermt2d    %zmm29, %zmm17,%zmm19
vmovdqu32	%zmm20, %zmm12
vpermt2d    %zmm23, %zmm17,%zmm12 
vpermt2d    %zmm28, %zmm17,%zmm11 
vpermt2d    %zmm31, %zmm17,%zmm10 

vmovdqu32	const4_512(%rip),%zmm17
vpermt2q    %zmm19, %zmm17,%zmm19 
vpermt2q    %zmm12, %zmm17,%zmm12 
vpermt2q    %zmm11, %zmm17,%zmm11 
vpermt2q    %zmm10, %zmm17,%zmm10 

vmovdqu32	const7_512(%rip),%zmm15
vmovdqu32	const7_512_(%rip),%zmm16
vmovdqu32	%zmm19, %zmm20
vpermt2q    %zmm12, %zmm15,%zmm20 

vmovdqu32	%zmm19, %zmm21
vpermt2q    %zmm12, %zmm16, %zmm21 
vmovdqu32	%zmm11, %zmm22
vpermt2q    %zmm10, %zmm15,%zmm22 
vmovdqu32	%zmm11, %zmm23
vpermt2q    %zmm10, %zmm16,%zmm23 

vmovdqa32	%zmm20,(%rdi) 
vmovdqa32	%zmm21, 0x40(%rdi)
vmovdqa32	%zmm22, 0x80(%rdi)
vmovdqa32	%zmm23, 0xc0(%rdi)


lea	0x200(%r9),%r9
lea	0x100(%rdi),%rdi #;;;win(rcx) lin(rdi)
lea	0xF8(%rdx),%rdx #;;; win(r8) lin(rdx)
dec	%eax
jnz	loop2

movaps      (%r11),%xmm15
movaps      0x10(%r11),%xmm14
movaps      0x20(%r11),%xmm13
movaps      0x30(%r11),%xmm12
movaps      0x40(%r11),%xmm11
movaps      0x50(%r11),%xmm10
movaps      0x60(%r11),%xmm9
movaps      0x70(%r11),%xmm8
movaps      0x80(%r11),%xmm7
movaps      0x90(%r11),%xmm6


pop %RBX
add	%rbp, %rsp
pop		%rbp

ret
