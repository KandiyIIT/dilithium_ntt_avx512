include mode.inc
EXTERN  _8xqinv_512 : QWORD
EXTERN  _8xq_512 : QWORD
EXTERN  _8x2q_512 : QWORD
EXTERN	_8x256q : QWORD
EXTERN	_8xdiv : QWORD
EXTERN	const1_512 : QWORD
EXTERN	const1_512_ : QWORD
EXTERN	const2_512 : QWORD
EXTERN	const2_512_ : QWORD
EXTERN	const3_512 : QWORD
EXTERN	const4_512 : QWORD
EXTERN	const5_512 : QWORD
EXTERN	const5_512_ : QWORD
EXTERN	const6_512 : QWORD
EXTERN	const6_512_ : QWORD
EXTERN	const7_512 : QWORD
EXTERN	const7_512_ : QWORD

EXTERN	__mask : QWORD

acc_512	macro 
vpaddq      zmm2, zmm2, zmm10
vpaddq      zmm3, zmm3, zmm11
vpaddq      zmm4, zmm4, zmm12
vpaddq      zmm5, zmm5, zmm13

vpaddq      zmm6, zmm6, zmm14
vpaddq      zmm7, zmm7, zmm15
vpaddq      zmm8, zmm8, zmm16
vpaddq      zmm9, zmm9, zmm17
endm
	
pointwise_512 MACRO off
VMOVDQA32	zmm10, zmmword ptr[rdx + off]	
VMOVDQA32		zmm12, zmmword ptr[rdx + 64 + off]
VMOVDQA32		zmm14, zmmword ptr[rdx  + 128 + off]
VMOVDQA32		zmm16, zmmword ptr[rdx + 192 + off]

VMOVDQA32		zmm18, zmmword ptr[r8 + off]
VMOVDQA32		zmm20, zmmword ptr[r8 + 64 + off]
VMOVDQA32		zmm22, zmmword ptr[r8 +  128 + off]
VMOVDQA32		zmm24, zmmword ptr[r8 +  192 + off]


vpsrlq		zmm11, zmm10, 32
vpsrlq		zmm13, zmm12, 32
vpsrlq		zmm15, zmm14, 32
vpsrlq		zmm17, zmm16, 32
vpsrlq		zmm19, zmm18, 32
vpsrlq		zmm21, zmm20, 32
vpsrlq		zmm23, zmm22, 32
vpsrlq		zmm25, zmm24, 32

vpmuludq	zmm10, zmm18, zmm10 	
vpmuludq	zmm11, zmm19, zmm11 	
vpmuludq	zmm12, zmm20, zmm12 	
vpmuludq	zmm13, zmm21, zmm13 	
vpmuludq	zmm14, zmm22, zmm14 	
vpmuludq	zmm15, zmm23, zmm15 	
vpmuludq	zmm16, zmm24, zmm16 	
vpmuludq	zmm17, zmm25, zmm17 	
endm
	
cpp_butterfly_512_asm macro		zmmz0,zmmz1,zmmz2,zmmz3,rl0,rl1,rl2,rl3,rh0,rh1,rh2,rh3	
	vpmuludq rh0, rh0, zmmz0
	vpmuludq rh1, rh1, zmmz1
	vpmuludq rh2, rh2, zmmz2
	vpmuludq rh3, rh3, zmmz3

	vpmuludq zmm12, rh0, zmm0
	vpmuludq zmm13, rh1, zmm0
	vpmuludq zmm14, rh2, zmm0
	vpmuludq zmm15, rh3, zmm0

	vpmuludq zmm12, zmm12, zmm1
	vpmuludq zmm13, zmm13, zmm1
	vpmuludq zmm14, zmm14, zmm1
	vpmuludq zmm15, zmm15, zmm1

	vpaddq	zmm12, zmm12, rh0
	vpaddq	zmm13, zmm13, rh1
	vpaddq	zmm14, zmm14, rh2
	vpaddq	zmm15, zmm15, rh3

	vpsrlq	zmm12, zmm12, 32	
	vpsrlq	zmm13, zmm13, 32	
	vpsrlq	zmm14, zmm14, 32
	vpsrlq	zmm15, zmm15, 32

	vpaddd	rh0, rl0, zmm2
	vpaddd	rh1, rl1, zmm2
	vpaddd	rh2, rl2, zmm2
	vpaddd	rh3, rl3, zmm2
	vpaddd	rl0, rl0, zmm12
	vpaddd	rl1, rl1, zmm13
	vpaddd	rl2, rl2, zmm14
	vpaddd	rl3, rl3, zmm15

	vpsubd	rh0, rh0, zmm12
	vpsubd	rh1, rh1, zmm13
	vpsubd	rh2, rh2, zmm14
	vpsubd	rh3, rh3, zmm15
endm

_TEXT    SEGMENT
new_pointwise_acc_asm_512 PROC

push rbp
mov		rbp, rsp
and		rbp, 31
add		rbp, 64
sub		rsp, rbp
push	rbx

mov         ebx,0AAAAh  
kmovw       k1,ebx  

VMOVDQA32		zmm0, zmmword ptr[_8xqinv_512]


VMOVDQA32		zmm1, zmmword ptr[_8xq_512]
mov	eax, 4


_looptop2:

pointwise_512	0

vpblendmd   zmm2{k1}, zmm10, zmm10  
vpblendmd   zmm3{k1}, zmm11, zmm11  
vpblendmd   zmm4{k1}, zmm12, zmm12  


vpblendmd   zmm5{k1}, zmm13, zmm13  
vpblendmd   zmm6{k1}, zmm14, zmm14  
vpblendmd   zmm7{k1}, zmm15, zmm15  
vpblendmd   zmm8{k1}, zmm16, zmm16  
vpblendmd   zmm9{k1}, zmm17, zmm17  

pointwise_512 1024

acc_512;

if L ge 3
		pointwise_512 2048
		acc_512
endif

if L ge 4
		pointwise_512 3072
		acc_512;
endif

if L ge 5
		pointwise_512 4096
		acc_512;
endif

vpmuludq	zmm10, zmm2, zmm0
vpmuludq	zmm11, zmm3, zmm0
vpmuludq	zmm12, zmm4, zmm0
vpmuludq	zmm13, zmm5, zmm0
vpmuludq	zmm14, zmm6, zmm0
vpmuludq	zmm15, zmm7, zmm0
vpmuludq	zmm16, zmm8, zmm0
vpmuludq	zmm17, zmm9, zmm0
vpmuludq	zmm10, zmm10, zmm1
vpmuludq	zmm11, zmm11, zmm1
vpmuludq	zmm12, zmm12, zmm1
vpmuludq	zmm13, zmm13, zmm1
vpmuludq	zmm14, zmm14, zmm1
vpmuludq	zmm15, zmm15, zmm1
vpmuludq	zmm16, zmm16, zmm1
vpmuludq	zmm17, zmm17, zmm1

VPADDQ	zmm2, zmm10, zmm2
VPADDQ	zmm3, zmm11, zmm3
VPADDQ	zmm4, zmm12, zmm4
VPADDQ	zmm5, zmm13, zmm5
VPADDQ	zmm6, zmm14, zmm6
VPADDQ	zmm7, zmm15, zmm7
VPADDQ	zmm8, zmm16, zmm8
VPADDQ	zmm9, zmm17, zmm9
		
vpsrlq		zmm2, zmm2, 32
vpsrlq		zmm4, zmm4, 32
vpsrlq		zmm6, zmm6, 32
vpsrlq		zmm8, zmm8, 32

vpblendmd   zmm2{k1}, zmm2, zmm3  
vpblendmd   zmm4{k1}, zmm4, zmm5  
vpblendmd   zmm6{k1}, zmm6, zmm7  
vpblendmd   zmm8{k1}, zmm8, zmm9  

VMOVDQA32	zmmword ptr[rcx], zmm2
VMOVDQA32	zmmword ptr[rcx + 64], zmm4
VMOVDQA32	zmmword ptr[rcx + 128], zmm6
VMOVDQA32	zmmword ptr[rcx + 192], zmm8
;a512 += 4;
lea	rdx, [rdx + 256]
;b512 += 4;
lea	r8, [r8 + 256]
;c512 += 4;
lea	rcx, [rcx + 256]
dec	eax
jnz	_looptop2
pop	rbx

add		rsp, rbp
pop		rbp
ret

new_pointwise_acc_asm_512 endp

new_ntt_512_asm__ PROC
; linux
; rdi phat
; rsi p
; rdx zetas

; Win32
; rcx - phat
; rdx - p;
;r8	- zetas

push rbp
mov		rbp, rsp
and		rbp, 63
add		rbp, 2368
sub		rsp, rbp

mov	r9, rsp
add	r9, 64
mov	r11, r9	; float registers
add	r11, 2048

push RBX

movaps      xmmword ptr [R11],xmm15
movaps      xmmword ptr [R11 + 10H],xmm14
movaps      xmmword ptr [R11 + 20H],xmm13
movaps      xmmword ptr [R11 + 30H],xmm12
movaps      xmmword ptr [R11 + 40H],xmm11
movaps      xmmword ptr [R11 + 50H],xmm10
movaps      xmmword ptr [R11 + 60H],xmm9
movaps      xmmword ptr [R11 + 70H],xmm8
movaps      xmmword ptr [R11 + 80H],xmm7
movaps      xmmword ptr [R11 + 90H],xmm6

VMOVDQA32		zmm0, zmmword ptr[_8xqinv_512]
VMOVDQA32		zmm1, zmmword ptr[_8xq_512]
VMOVDQA32		zmm2, zmmword ptr[_8x2q_512]

vmovdqa ymm3, ymmword ptr [r8]
vextractf128 xmm4, ymm3, 1

psrldq	xmm3, 4
vpbroadcastd zmm16, xmm3
psrldq	xmm3, 4
vpbroadcastd zmm17, xmm3
psrldq	xmm3, 4
vpbroadcastd zmm18, xmm3
vpbroadcastd zmm19, xmm4
psrldq	xmm4, 4
vpbroadcastd zmm20, xmm4
psrldq	xmm4, 4
vpbroadcastd zmm21, xmm4
psrldq	xmm4, 4
vpbroadcastd zmm22, xmm4

push	rdx
push	r9
mov	eax, 4
loop1:

vpmovzxdq	zmm24, ymmword ptr [rdx]
vpmovzxdq	zmm25, ymmword ptr [rdx + 128]
vpmovzxdq	zmm26, ymmword ptr [rdx + 256]
vpmovzxdq	zmm27, ymmword ptr [rdx + 384]
vpmovzxdq	zmm28, ymmword ptr [rdx + 512]
vpmovzxdq	zmm29, ymmword ptr [rdx + 640]
vpmovzxdq	zmm30, ymmword ptr [rdx + 768]
vpmovzxdq	zmm31, ymmword ptr [rdx + 896]

cpp_butterfly_512_asm zmm16,zmm16,zmm16,zmm16,zmm24,zmm25,zmm26,zmm27,zmm28,zmm29,zmm30,zmm31	

cpp_butterfly_512_asm zmm17,zmm17,zmm18,zmm18,zmm24,zmm25,zmm28,zmm29,zmm26,zmm27,zmm30,zmm31	

cpp_butterfly_512_asm zmm19,zmm20,zmm21,zmm22,zmm24,zmm26,zmm28,zmm30,zmm25,zmm27,zmm29,zmm31	

vmovdqa32	zmmword ptr[r9], zmm24
vmovdqa32	zmmword ptr[r9 + 256], zmm25
vmovdqa32	zmmword ptr[r9 + 512], zmm26
vmovdqa32	zmmword ptr[r9 + 768], zmm27
vmovdqa32	zmmword ptr[r9 + 1024], zmm28
vmovdqa32	zmmword ptr[r9 + 1280], zmm29
vmovdqa32	zmmword ptr[r9 + 1536], zmm30
vmovdqa32	zmmword ptr[r9 + 1792], zmm31

lea	r9, [r9 + 64]
lea	rdx, [rdx + 32]
dec eax
jnz	loop1
pop	r9
pop	rdx

lea	r8, [r8 + 32]
mov	eax, 4
loop2:

mov	r10, r8
lea	r10, [r10 + 124]

vmovdqa32	zmm24, zmmword ptr [r9]
vmovdqa32	zmm25, zmmword ptr [r9 + 64]
vmovdqa32	zmm26, zmmword ptr [r9 + 128]
vmovdqa32	zmm27, zmmword ptr [r9 + 192]
vmovdqa32	zmm28, zmmword ptr [r9 + 256]
vmovdqa32	zmm29, zmmword ptr [r9 + 320]
vmovdqa32	zmm30, zmmword ptr [r9 + 384]
vmovdqa32	zmm31, zmmword ptr [r9 + 448]

vlddqu ymm3, ymmword ptr [r8];
vlddqu ymm4, ymmword ptr [r10];
	
vpbroadcastd	zmm12, xmm3
vpbroadcastd	zmm13, xmm4

cpp_butterfly_512_asm zmm12, zmm12, zmm13, zmm13, zmm24, zmm25, zmm28, zmm29, zmm26, zmm27, zmm30, zmm31

vpsrldq ymm3, ymm3, 4
vpsrldq ymm4, ymm4, 4

vpbroadcastd	zmm12, xmm3
vpbroadcastd	zmm14, xmm4

vpsrldq ymm3, ymm3, 4
vpsrldq ymm4, ymm4, 4
vpbroadcastd	zmm13, xmm3
vpbroadcastd	zmm15, xmm4
		
mov         ebx,0F0F0h  
kmovw       k1,ebx 

vpblendmd   zmm12{k1}, zmm12, zmm13
vpblendmd   zmm14{k1}, zmm14, zmm15

vmovdqu32	zmm23, zmm24
vmovdqu32	zmm15, zmmword ptr [const1_512]
vmovdqu32	zmm16, zmmword ptr [const1_512_]
vpermt2q    zmm23,zmm15,zmm26 

vpermt2q    zmm24,zmm16,zmm26
vmovdqu32	zmm26, zmm24

vmovdqu32	zmm24, zmm25
vpermt2q    zmm24,zmm15,zmm27

vpermt2q    zmm25,zmm16,zmm27
vmovdqu32	zmm27, zmm25

vmovdqu32	zmm25, zmm28
vpermt2q    zmm25,zmm15,zmm30

vpermt2q    zmm28,zmm16,zmm30
vmovdqu32	zmm30, zmm28

vmovdqu32	zmm28, zmm29
vpermt2q    zmm28,zmm15,zmm31

vpermt2q    zmm29,zmm16,zmm31
vmovdqu32	zmm31, zmm29

cpp_butterfly_512_asm zmm12, zmm12, zmm14, zmm14, zmm23, zmm26, zmm25, zmm30, zmm24, zmm27, zmm28, zmm31

vbroadcasti64x2	ymm3, xmmword ptr[r8 + 12]
vbroadcasti64x2	ymm4, xmmword ptr[r10 + 12]

vpmovzxdq	zmm12, ymm3
vpmovzxdq	zmm13, ymm4
	
vmovdqu32	zmm15, zmmword ptr [const2_512]
vmovdqu32	zmm16, zmmword ptr [const2_512_]
vmovdqu32	zmm29, zmm23
vpermt2q    zmm29,zmm15,zmm24
vpermt2q    zmm23,zmm16,zmm24
vmovdqu32	zmm24, zmm23
vmovdqu32	zmm23, zmm26
vpermt2q    zmm23,zmm15,zmm27

vpermt2q    zmm26,zmm16,zmm27
vmovdqu32	zmm27, zmm26

vmovdqu32	zmm26, zmm25
vpermt2q    zmm26,zmm15,zmm28

vpermt2q    zmm25,zmm16,zmm28
vmovdqu32	zmm28, zmm25

vmovdqu32	zmm25, zmm30
vpermt2q    zmm25,zmm15,zmm31

vpermt2q    zmm30,zmm16,zmm31
vmovdqu32	zmm31, zmm30

cpp_butterfly_512_asm zmm12, zmm12, zmm13, zmm13, zmm29, zmm24, zmm26, zmm28, zmm23, zmm27, zmm25, zmm31

vlddqu	ymm3, ymmword ptr [r8 + 28]
vlddqu	ymm4, ymmword ptr [r10 + 28]

vpmovzxdq zmm13, ymm3
vpmovzxdq zmm15, ymm4

vmovdqu32	zmm3, zmmword ptr [const5_512]	
vmovdqu32	zmm4, zmmword ptr [const5_512_]	
vpermq zmm12, zmm3, zmm13

vpermq zmm13, zmm4, zmm13
vpermq zmm14, zmm3, zmm15
vpermq zmm15, zmm4, zmm15

cpp_butterfly_512_asm	zmm12, zmm13, zmm14, zmm15, zmm29, zmm23, zmm26, zmm25, zmm24, zmm27, zmm28, zmm31

vlddqu ymm3, ymmword ptr [r8 + 60];
vlddqu	ymm4, ymmword ptr [r8 + 92];
vlddqu ymm5, ymmword ptr [r10 + 60];
vlddqu ymm6, ymmword ptr [r10 + 92];
vpmovzxdq	zmm12, ymm3
vpmovzxdq	zmm13, ymm4
vpmovzxdq	zmm14, ymm5
vpmovzxdq	zmm15, ymm6

vmovdqu32	zmm17, zmmword ptr [const6_512]
vmovdqu32	zmm16, zmmword ptr [const6_512_]
vmovdqu32	zmm19, zmm29
vpermt2q    zmm19, zmm17,zmm24 

vpermt2q    zmm29, zmm16,zmm24 
vmovdqu32	zmm24, zmm29
vmovdqu32	zmm20, zmm23
vpermt2q    zmm20, zmm17,zmm27 

vpermt2q    zmm23, zmm16,zmm27 
vmovdqu32	zmm27, zmm23

vmovdqu32	zmm11, zmm26
vpermt2q    zmm11, zmm17,zmm28 

vpermt2q    zmm26, zmm16,zmm28 
vmovdqu32	zmm28, zmm26

vmovdqu32	zmm10, zmm25
vpermt2q    zmm10, zmm17,zmm31 

vpermt2q    zmm25, zmm16,zmm31 
vmovdqu32	zmm31, zmm25
		
cpp_butterfly_512_asm zmm12, zmm13, zmm14, zmm15, zmm19, zmm20, zmm11, zmm10, zmm29, zmm23, zmm28, zmm31

vmovdqu32	zmm17, zmmword ptr [const3_512]
vpermt2d    zmm19, zmm17,zmm29

vmovdqu32	zmm12, zmm20
vpermt2d    zmm12, zmm17,zmm23 

vpermt2d    zmm11, zmm17,zmm28 
vpermt2d    zmm10, zmm17,zmm31 

vmovdqu32	zmm17, zmmword ptr [const4_512]
vpermt2q    zmm19, zmm17,zmm19 

vpermt2q    zmm12, zmm17,zmm12 
vpermt2q    zmm11, zmm17,zmm11 
vpermt2q    zmm10, zmm17,zmm10 

vmovdqu32	zmm15, zmmword ptr [const7_512]
vmovdqu32	zmm16, zmmword ptr [const7_512_]
vmovdqu32	zmm20, zmm19
vpermt2q    zmm20, zmm15,zmm12 

vmovdqu32	zmm21, zmm19
vpermt2q    zmm21, zmm16, zmm12 
vmovdqu32	zmm22, zmm11
vpermt2q    zmm22, zmm15,zmm10 

vmovdqu32	zmm23, zmm11
vpermt2q    zmm23, zmm16,zmm10 

vmovdqa32	zmmword ptr[rcx], zmm20
vmovdqa32	zmmword ptr[rcx + 64], zmm21
vmovdqa32	zmmword ptr[rcx + 128], zmm22
vmovdqa32	zmmword ptr[rcx + 192], zmm23

;	tmp512 += 8;
lea	r9, [r9 + 512]
;	dest512 += 4;
lea	rcx, [rcx + 256]
;	zl += 62;
lea	r8, [r8 + 248]
dec	eax
jnz	loop2
movaps      xmm15, xmmword ptr [R11];		xmm15
movaps      xmm14, xmmword ptr [R11 + 10H];	xmm14
movaps      xmm13, xmmword ptr [R11 + 20H];	xmm13
movaps      xmm12, xmmword ptr [R11 + 30H]; xmm12
movaps      xmm11, xmmword ptr [R11 + 40H];	xmm11
movaps      xmm10, xmmword ptr [R11 + 50H];	xmm10
movaps      xmm9, xmmword ptr [R11 + 60H];	xmm9
movaps      xmm8, xmmword ptr [R11 + 70H];	xmm8
movaps      xmm7, xmmword ptr [R11 + 80H];	xmm7
movaps      xmm6, xmmword ptr [R11 + 90H];	xmm6


pop RBX
add	rsp, rbp
pop		rbp

ret
new_ntt_512_asm__ endp

_TEXT	ends
end
