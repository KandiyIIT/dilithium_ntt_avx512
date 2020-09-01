#include <immintrin.h>
#include<inttypes.h>
#include "parameters.h"
#include "const.h"

#define cpp_batterfly_inv512_macro(z0, z1, z2, z3, l0, l1, l2, l3, h0, h1, h2, h3)	\
{	\
	zmm13 = _mm512_add_epi32(l0, zmm2);	\
	zmm14 = _mm512_add_epi32(l1, zmm2);	\
	zmm15 = _mm512_add_epi32(l2, zmm2);	\
	zmm16 = _mm512_add_epi32(l3, zmm2);	\
	\
	zmm13 = _mm512_sub_epi32(zmm13, h0);	\
	zmm14 = _mm512_sub_epi32(zmm14, h1);	\
	zmm15 = _mm512_sub_epi32(zmm15, h2);	\
	zmm16 = _mm512_sub_epi32(zmm16, h3);	\
	\
	zmm13 = _mm512_mul_epu32(zmm13, z0);	\
	zmm14 = _mm512_mul_epu32(zmm14, z1);	\
	zmm15 = _mm512_mul_epu32(zmm15, z2);	\
	zmm16 = _mm512_mul_epu32(zmm16, z3);	\
	\
	l0 = _mm512_add_epi32(h0, l0);			\
	l1 = _mm512_add_epi32(h1, l1);			\
	l2 = _mm512_add_epi32(h2, l2);			\
	l3 = _mm512_add_epi32(h3, l3);			\
	\
	h0 = _mm512_mul_epu32(zmm13, zmm0);		\
	h1 = _mm512_mul_epu32(zmm14, zmm0);		\
	h2 = _mm512_mul_epu32(zmm15, zmm0);		\
	h3 = _mm512_mul_epu32(zmm16, zmm0);		\
	\
	h0 = _mm512_mul_epu32(h0, zmm1);		\
	h1 = _mm512_mul_epu32(h1, zmm1);		\
	h2 = _mm512_mul_epu32(h2, zmm1);		\
	h3 = _mm512_mul_epu32(h3, zmm1);		\
	\
	h0 = _mm512_add_epi64(h0, zmm13);		\
	h1 = _mm512_add_epi64(h1, zmm14);		\
	h2 = _mm512_add_epi64(h2, zmm15);		\
	h3 = _mm512_add_epi64(h3, zmm16);		\
	\
	h0 = _mm512_srli_epi64(h0, 32);			\
	h1 = _mm512_srli_epi64(h1, 32);			\
	h2 = _mm512_srli_epi64(h2, 32);			\
	h3 = _mm512_srli_epi64(h3, 32);			\
}


__m512i const1_512, const1_512_, const2_512, const2_512_, const3_512, 
	const4_512, const5_512, const5_512_, const6_512, const6_512_, const7_512, const7_512_,
	const8_512, const8_512_, const9_512, const9_512_, const10_512, const10_512_, const11_512, const12_512, 
	const13_512, const14_512;
	
	
void set_const_512()
{
	const1_512 = _mm512_setr_epi64(0, 1, 8, 9, 2, 3, 10, 11);
	const1_512_ = _mm512_setr_epi64(4, 5, 12, 13, 6, 7, 14, 15);
	const2_512 = _mm512_setr_epi64(0, 8, 2, 10, 1, 9, 3, 11),
	const2_512_ = _mm512_setr_epi64(4, 12, 6, 14, 5, 13, 7, 15);
	const3_512 = _mm512_setr_epi32(0, 16, 2, 18, 4, 20, 6, 22, 8, 24, 10, 26, 12, 28, 14, 30);
	const4_512 = _mm512_setr_epi64(0, 4, 2, 6, 1, 5, 3, 7);
	const5_512 = _mm512_setr_epi64(0, 1, 2, 3, 0, 1, 2, 3);
	const5_512_ = _mm512_setr_epi64(4, 5, 6, 7, 4, 5, 6, 7);
	const6_512 = _mm512_setr_epi64(0, 1, 2, 3, 8, 9, 10, 11);
	const6_512_ = _mm512_setr_epi64(4, 5, 6, 7, 12, 13, 14, 15);
	const7_512 = _mm512_setr_epi64(0, 1, 8, 9, 4, 5, 12, 13);
	const7_512_ = _mm512_setr_epi64(2, 3, 10, 11, 6, 7, 14, 15);
	const8_512 = _mm512_setr_epi64(0, 4, 8, 12, 1, 5, 9, 13);
	const8_512_ = _mm512_setr_epi64(2, 6, 10, 14, 3, 7, 11, 15);
	const9_512 = _mm512_setr_epi64(0, 4, 2, 6, 8, 12, 10, 14);
	const9_512_ = _mm512_setr_epi64(1, 5, 3, 7, 9, 13, 11, 15);
	const10_512 = _mm512_setr_epi64(0, 1, 4, 5, 8, 9, 12, 13);
	const10_512_ = _mm512_setr_epi64(2, 3, 6, 7, 10, 11, 14, 15);
	const11_512 = _mm512_setr_epi32(0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1);
	const12_512 = _mm512_setr_epi32(0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1);
	const13_512 = _mm512_setr_epi32(1, 3, 5, 7, 17, 19, 21, 23, 9, 11, 13, 15, 25, 27, 29, 31);
	const14_512 = _mm512_setr_epi32(0, 2, 4, 6, 16, 18, 20, 22, 8, 10, 12, 14, 24, 26, 28, 30);
}

#define shuffle_512(r0, r1, r2, r3, c1, c2){	\
	r2 = _mm512_permutex2var_epi64(r0, c1, r1);	\
	r3 = _mm512_permutex2var_epi64(r0, c2, r1);	\
}

#define macro_cpp_butterfly_512(zmm0,zmm1,zmm2,zmmz0,zmmz1,zmmz2,zmmz3,rl0,rl1,rl2,rl3,rh0,rh1,rh2,rh3)	\
{\
	rh0 = _mm512_mul_epu32(rh0, zmmz0);		rh1 = _mm512_mul_epu32(rh1, zmmz1);		\
	rh2 = _mm512_mul_epu32(rh2, zmmz2);		rh3 = _mm512_mul_epu32(rh3, zmmz3);		\
	zmm12 = _mm512_mul_epu32(rh0, zmm0);	zmm13 = _mm512_mul_epu32(rh1, zmm0);	\
	zmm14 = _mm512_mul_epu32(rh2, zmm0);	zmm15 = _mm512_mul_epu32(rh3, zmm0);	\
	zmm12 = _mm512_mul_epu32(zmm12, zmm1);	zmm13 = _mm512_mul_epu32(zmm13, zmm1);	\
	zmm14 = _mm512_mul_epu32(zmm14, zmm1);	zmm15 = _mm512_mul_epu32(zmm15, zmm1);	\
	zmm12 = _mm512_add_epi64(zmm12, rh0);	zmm13 = _mm512_add_epi64(zmm13, rh1);	\
	zmm14 = _mm512_add_epi64(zmm14, rh2);	zmm15 = _mm512_add_epi64(zmm15, rh3);	\
	zmm12 = _mm512_srli_epi64(zmm12, 32);	zmm13 = _mm512_srli_epi64(zmm13, 32);	\
	zmm14 = _mm512_srli_epi64(zmm14, 32);	zmm15 = _mm512_srli_epi64(zmm15, 32);	\
	rh0 = _mm512_add_epi32(rl0, zmm2);		rh1 = _mm512_add_epi32(rl1, zmm2);		\
	rh2 = _mm512_add_epi32(rl2, zmm2);		rh3 = _mm512_add_epi32(rl3, zmm2);		\
	rl0 = _mm512_add_epi32(rl0, zmm12);		rl1 = _mm512_add_epi32(rl1, zmm13);		\
	rl2 = _mm512_add_epi32(rl2, zmm14);		rl3 = _mm512_add_epi32(rl3, zmm15);		\
	rh0 = _mm512_sub_epi32(rh0, zmm12);		rh1 = _mm512_sub_epi32(rh1, zmm13);		\
	rh2 = _mm512_sub_epi32(rh2, zmm14);		rh3 = _mm512_sub_epi32(rh3, zmm15);		\
}


void	pointwise_512_fun(__m512i* a512, __m512i* b512,
	__m512i* zmm10, __m512i* zmm11, __m512i* zmm12, __m512i* zmm13,
	__m512i* zmm14, __m512i* zmm15, __m512i* zmm16, __m512i* zmm17
) {
	__m512i zmm18, zmm19, zmm20, zmm21, zmm22, zmm23, zmm24, zmm25;
	*zmm10 = _mm512_load_si512(a512);
	*zmm12 = _mm512_load_si512(a512 + 1);
	*zmm14 = _mm512_load_si512(a512 + 2);
	*zmm16 = _mm512_load_si512(a512 + 3);
	zmm18 = _mm512_load_si512(b512);
	zmm20 = _mm512_load_si512(b512 + 1);
	zmm22 = _mm512_load_si512(b512 + 2);
	zmm24 = _mm512_load_si512(b512 + 3);
	*zmm11 = _mm512_srli_epi64(*zmm10, 32);
	*zmm13 = _mm512_srli_epi64(*zmm12, 32);
	*zmm15 = _mm512_srli_epi64(*zmm14, 32);
	*zmm17 = _mm512_srli_epi64(*zmm16, 32);
	zmm19 = _mm512_srli_epi64(zmm18, 32);
	zmm21 = _mm512_srli_epi64(zmm20, 32);
	zmm23 = _mm512_srli_epi64(zmm22, 32);
	zmm25 = _mm512_srli_epi64(zmm24, 32);
	*zmm10 = _mm512_mul_epu32(zmm18, *zmm10);
	*zmm11 = _mm512_mul_epu32(zmm19, *zmm11);
	*zmm12 = _mm512_mul_epu32(zmm20, *zmm12);
	*zmm13 = _mm512_mul_epu32(zmm21, *zmm13);
	*zmm14 = _mm512_mul_epu32(zmm22, *zmm14);
	*zmm15 = _mm512_mul_epu32(zmm23, *zmm15);
	*zmm16 = _mm512_mul_epu32(zmm24, *zmm16);
	*zmm17 = _mm512_mul_epu32(zmm25, *zmm17);
}


#define	 pointwise_512(a512, b512)	{		\
	zmm10 = _mm512_load_si512(a512);			\
	zmm12 = _mm512_load_si512(a512 + 1);		\
	zmm14 = _mm512_load_si512(a512 + 2);			\
	zmm16 = _mm512_load_si512(a512 + 3);		\
	zmm18 = _mm512_load_si512(b512);		\
	zmm20 = _mm512_load_si512(b512 + 1);		\
	zmm22 = _mm512_load_si512(b512 + 2);		\
	zmm24 = _mm512_load_si512(b512 + 3);		\
	zmm11 = _mm512_srli_epi64(zmm10, 32);			\
	zmm13 = _mm512_srli_epi64(zmm12, 32);			\
	zmm15 = _mm512_srli_epi64(zmm14, 32);			\
	zmm17 = _mm512_srli_epi64(zmm16, 32);			\
	zmm19 = _mm512_srli_epi64(zmm18, 32);			\
	zmm21 = _mm512_srli_epi64(zmm20, 32);			\
	zmm23 = _mm512_srli_epi64(zmm22, 32);			\
	zmm25 = _mm512_srli_epi64(zmm24, 32);			\
	zmm10 = _mm512_mul_epu32(zmm18, zmm10);			\
	zmm11 = _mm512_mul_epu32(zmm19, zmm11);			\
	zmm12= _mm512_mul_epu32(zmm20, zmm12);			\
	zmm13= _mm512_mul_epu32(zmm21, zmm13);			\
	zmm14 = _mm512_mul_epu32(zmm22, zmm14);			\
	zmm15 = _mm512_mul_epu32(zmm23, zmm15);			\
	zmm16 = _mm512_mul_epu32(zmm24, zmm16);			\
	zmm17 = _mm512_mul_epu32(zmm25, zmm17);			\
}

#define acc_512		{\
	zmm2 = _mm512_add_epi64(zmm2, zmm10);\
	zmm3 = _mm512_add_epi64(zmm3, zmm11);\
	zmm4 = _mm512_add_epi64(zmm4, zmm12);\
	zmm5 = _mm512_add_epi64(zmm5, zmm13);\
	zmm6 = _mm512_add_epi64(zmm6, zmm14);\
	zmm7 = _mm512_add_epi64(zmm7, zmm15);\
	zmm8 = _mm512_add_epi64(zmm8, zmm16);\
	zmm9 = _mm512_add_epi64(zmm9, zmm17);\
}

void new_pointwise_acc_cpp_512(uint32_t c[], uint32_t a[], uint32_t b[])
{

	__m512i zmm0, zmm1, zmm2, zmm3, zmm4, zmm5, zmm6, zmm7, zmm8, zmm9, zmm10,
		zmm11, zmm12, zmm13, zmm14, zmm15, zmm16, zmm17, zmm18, zmm19,
		zmm20, zmm21, zmm22, zmm23, zmm24, zmm25;
	__m512i* a512 = (__m512i*)a, * b512 = (__m512i*)b, * c512 = (__m512i*)c;
	uint32_t i;

	zmm0 = _mm512_set1_epi32(_8xqinv[0]);
	zmm1 = _mm512_set1_epi32(_8xq[0]);
	for (i = 0; i < 4; i++)
	{
		pointwise_512_fun(a512, b512, &zmm10, &zmm11, &zmm12, &zmm13, &zmm14, &zmm15, &zmm16, &zmm17);
		
		zmm2 = zmm10;
		zmm3 = zmm11;
		zmm4 = zmm12;
		zmm5 = zmm13;
		zmm6 = zmm14;
		zmm7 = zmm15;
		zmm8 = zmm16;
		zmm9 = zmm17;

		pointwise_512(a512 + 16, b512 + 16);//1024
		acc_512;
	
#if L >= 3
		pointwise_512(a512 + 32, b512 + 32);//2048
		acc_512
#endif
#if L >= 4
			pointwise_512(a512 + 48, b512 + 48);// 3072
		acc_512;
#endif
#if L >= 5
		pointwise_512(a512 + 64, b512 + 64);// 4096
		acc_512;
#endif

		zmm10 = _mm512_mul_epu32(zmm2, zmm0);
		zmm11 = _mm512_mul_epu32(zmm3, zmm0);
		zmm12 = _mm512_mul_epu32(zmm4, zmm0);
		zmm13 = _mm512_mul_epu32(zmm5, zmm0);

		zmm14 = _mm512_mul_epu32(zmm6, zmm0);
		zmm15 = _mm512_mul_epu32(zmm7, zmm0);
		zmm16 = _mm512_mul_epu32(zmm8, zmm0);
		zmm17 = _mm512_mul_epu32(zmm9, zmm0);

		zmm10 = _mm512_mul_epu32(zmm10, zmm1);
		zmm11 = _mm512_mul_epu32(zmm11, zmm1);
		zmm12 = _mm512_mul_epu32(zmm12, zmm1);
		zmm13 = _mm512_mul_epu32(zmm13, zmm1);

		zmm14 = _mm512_mul_epu32(zmm14, zmm1);
		zmm15 = _mm512_mul_epu32(zmm15, zmm1);
		zmm16 = _mm512_mul_epu32(zmm16, zmm1);
		zmm17 = _mm512_mul_epu32(zmm17, zmm1);

		zmm2 = _mm512_add_epi64(zmm10, zmm2);
		zmm3 = _mm512_add_epi64(zmm11, zmm3);
		zmm4 = _mm512_add_epi64(zmm12, zmm4);
		zmm5 = _mm512_add_epi64(zmm13, zmm5);

		zmm6 = _mm512_add_epi64(zmm14, zmm6);
		zmm7 = _mm512_add_epi64(zmm15, zmm7);
		zmm8 = _mm512_add_epi64(zmm16, zmm8);
		zmm9 = _mm512_add_epi64(zmm17, zmm9);

		zmm2 = _mm512_srli_epi64(zmm2, 32);
		zmm4 = _mm512_srli_epi64(zmm4, 32);
		zmm6 = _mm512_srli_epi64(zmm6, 32);
		zmm8 = _mm512_srli_epi64(zmm8, 32);

		zmm2 = _mm512_mask_blend_epi32(0xAAAA, zmm2, zmm3);
		zmm4 = _mm512_mask_blend_epi32(0xAAAA, zmm4, zmm5);

		zmm6 = _mm512_mask_blend_epi32(0xAAAA, zmm6, zmm7);
		zmm8 = _mm512_mask_blend_epi32(0xAAAA, zmm8, zmm9);
		_mm512_store_si512(c512, zmm2);
		_mm512_store_si512(c512 + 1, zmm4);

		_mm512_store_si512(c512 + 2, zmm6);
		_mm512_store_si512(c512 + 3, zmm8);
		a512 += 4;
		b512 += 4;
		c512 += 4;
	}
}


void new_ntt_512_cpp_(uint32_t* dest, uint32_t* src, uint32_t* z)
{
	
	__m512i zmm0 = _mm512_load_si512((__m512i*)_8xqinv_512);
	__m512i zmm1 = _mm512_load_si512((__m512i*)_8xq_512);
	__m512i zmm2 = _mm512_load_si512((__m512i*)_8x2q_512);
	__m512i temp512[N / 8], *tmp512 = temp512, *dest512;

	__m512i zmm3, zmm4, zmm5, zmm6, zmm7,
		zmm8, zmm9, zmm10, zmm11, zmm12, zmm13, zmm14, zmm15;
	
	__m512i zmm16; 
	__m512i zmm17, zmm18; 
	__m512i zmm19, zmm20, zmm21, zmm22;
	
	__m256i* src256 = (__m256i*)src, * tmp256 = (__m256i*)tmp512;

	__m128i zj0, zj1, zj2, zj3, zj4, zj5, zj6;

	uint32_t i, * zl, *zh;
	
	zj0 = _mm_loadu_si128((const __m128i*)(z + 1));
	zj1 = _mm_loadu_si128((const __m128i*)(z + 2));
	zj2 = _mm_loadu_si128((const __m128i*)(z + 3));
	zj3 = _mm_loadu_si128((const __m128i*)(z + 4));
	zj4 = _mm_loadu_si128((const __m128i*)(z + 5));
	zj5 = _mm_loadu_si128((const __m128i*)(z + 6));
	zj6 = _mm_loadu_si128((const __m128i*)(z + 7));

	zmm16 = _mm512_broadcastd_epi32(zj0);		
	zmm17 = _mm512_broadcastd_epi32(zj1);
	zmm18 = _mm512_broadcastd_epi32(zj2);
	zmm19 = _mm512_broadcastd_epi32(zj3);
	zmm20 = _mm512_broadcastd_epi32(zj4);
	zmm21 = _mm512_broadcastd_epi32(zj5);
	zmm22 = _mm512_broadcastd_epi32(zj6);


	for (i = 0; i < N / 64; ++i)
	{
		zmm4 = _mm512_cvtepu32_epi64(*(__m256i*)	(src256));		
		zmm5 = _mm512_cvtepu32_epi64(*(__m256i*)	(src256 + 4));	
		zmm6 = _mm512_cvtepu32_epi64(*(__m256i*)	(src256 + 8));	
		zmm7 = _mm512_cvtepu32_epi64(*(__m256i*)	(src256 + 12));	
		zmm8 = _mm512_cvtepu32_epi64(*(__m256i*)	(src256 + 16));	
		zmm9 = _mm512_cvtepu32_epi64(*(__m256i*)	(src256 + 20));	
		zmm10 = _mm512_cvtepu32_epi64(*(__m256i*)	(src256 + 24));	
		zmm11 = _mm512_cvtepu32_epi64(*(__m256i*)	(src256 + 28));	

		macro_cpp_butterfly_512(zmm0, zmm1, zmm2,
			zmm16, zmm16, zmm16, zmm16,
			zmm4, zmm5, zmm6, zmm7,
			zmm8, zmm9, zmm10, zmm11);
		
		macro_cpp_butterfly_512(zmm0, zmm1, zmm2,
			zmm17, zmm17, zmm18, zmm18,
			zmm4, zmm5, zmm8, zmm9,
			zmm6, zmm7, zmm10, zmm11);
				
		macro_cpp_butterfly_512(zmm0, zmm1, zmm2,
			zmm19, zmm20, zmm21, zmm22,
			zmm4, zmm6, zmm8, zmm10,
			zmm5, zmm7, zmm9, zmm11);

		_mm512_store_si512(tmp512, zmm4);
		_mm512_store_si512(tmp512 + 4, zmm5);
		_mm512_store_si512(tmp512 + 8, zmm6);
		_mm512_store_si512(tmp512 + 12, zmm7);

		_mm512_store_si512(tmp512 + 16, zmm8);
		_mm512_store_si512(tmp512 + 20, zmm9);
		_mm512_store_si512(tmp512 + 24, zmm10);
		_mm512_store_si512(tmp512 + 28, zmm11);

		src256++;
		tmp512++;
	}

	tmp512 = temp512;
	dest512 = (__m512i*)dest;
	zl = z + 8;
		
	for (i = 0; i < N / 64; ++i)
	{
		
		zh = zl + 31;
		zmm4 = _mm512_load_si512(tmp512);		// 4, 5
		zmm5 = _mm512_load_si512(tmp512 + 1);	// 6, 7
		zmm6 = _mm512_load_si512(tmp512 + 2);	// 8, 9
		zmm7 = _mm512_load_si512(tmp512 + 3);	// 10, 11
		zmm8 = _mm512_load_si512(tmp512 + 4);	// 4, 5
		zmm9 = _mm512_load_si512(tmp512 + 5);	// 6, 7
		zmm10 = _mm512_load_si512(tmp512 + 6);	// 8, 9
		zmm11 = _mm512_load_si512(tmp512 + 7);	// 10, 11

		zj0 = _mm_loadu_si128((const __m128i*)zl);
		zmm12 = _mm512_broadcastd_epi32(zj0);
		zj1 = _mm_loadu_si128((const __m128i*)(zh));
		zmm13 = _mm512_broadcastd_epi32(zj1);

		macro_cpp_butterfly_512(zmm0, zmm1, zmm2, zmm12, zmm12, zmm13, zmm13,
			zmm4, zmm5, zmm8, zmm9, zmm6, zmm7, zmm10, zmm11);
		zj0 = _mm_loadu_si128((const __m128i*)(zl + 1));
		zmm12 = _mm512_broadcastd_epi32(zj0);
		zj1 = _mm_loadu_si128((const __m128i*)(zl + 2));
		zmm13 = _mm512_broadcastd_epi32(zj1);
		zmm12 = _mm512_mask_blend_epi32(0xF0F0, zmm12, zmm13);

		zj2 = _mm_loadu_si128((const __m128i*)(zh + 1));
		zmm13 = _mm512_broadcastd_epi32(zj2);
		zj3 = _mm_loadu_si128((const __m128i*)(zh + 2));
		zmm14 = _mm512_broadcastd_epi32(zj3);
		zmm13 = _mm512_mask_blend_epi32(0xF0F0, zmm13, zmm14);

		zmm3 = _mm512_permutex2var_epi64(zmm4, const1_512, zmm6);
		zmm6 = _mm512_permutex2var_epi64(zmm4, const1_512_, zmm6);
				
		zmm4 = _mm512_permutex2var_epi64(zmm5, const1_512, zmm7);
		zmm7 = _mm512_permutex2var_epi64(zmm5, const1_512_, zmm7);

		zmm5 = _mm512_permutex2var_epi64(zmm8, const1_512, zmm10);
		zmm10 = _mm512_permutex2var_epi64(zmm8, const1_512_, zmm10);

		zmm8 = _mm512_permutex2var_epi64(zmm9, const1_512, zmm11);
		zmm11 = _mm512_permutex2var_epi64(zmm9, const1_512_, zmm11);
			
		macro_cpp_butterfly_512(zmm0, zmm1, zmm2, zmm12, zmm12, zmm13, zmm13,
			zmm3, zmm6, zmm5, zmm10, zmm4, zmm7, zmm8, zmm11);


		//	//level5:
		zj0 = _mm_loadu_si128((const __m128i*)(zl + 3));
		__m256i zj256 = _mm256_broadcast_i64x2(zj0);
		zmm12 = _mm512_cvtepu32_epi64(zj256);
		zj1 = _mm_loadu_si128((const __m128i*)(zh + 3));

		zj256 = _mm256_broadcast_i64x2(zj1);
		zmm13 = _mm512_cvtepu32_epi64(zj256);

		zmm9 = _mm512_permutex2var_epi64(zmm3, const2_512, zmm4);
		zmm4 = _mm512_permutex2var_epi64(zmm3, const2_512_, zmm4);

		zmm3 = _mm512_permutex2var_epi64(zmm6, const2_512, zmm7);
		zmm7 = _mm512_permutex2var_epi64(zmm6, const2_512_, zmm7);

		zmm6 = _mm512_permutex2var_epi64(zmm5, const2_512, zmm8);
		zmm8 = _mm512_permutex2var_epi64(zmm5, const2_512_, zmm8);

		zmm5 = _mm512_permutex2var_epi64(zmm10, const2_512, zmm11);
		zmm11 = _mm512_permutex2var_epi64(zmm10, const2_512_, zmm11);

		macro_cpp_butterfly_512(zmm0, zmm1, zmm2, zmm12, zmm12, zmm13, zmm13,
			zmm9, zmm4, zmm6, zmm8, zmm3, zmm7, zmm5, zmm11);


		//level6:
		zj256 = _mm256_loadu_si256((const __m256i*)(zl + 7));
		zmm13 = _mm512_cvtepu32_epi64(zj256);
		zmm12 = _mm512_permutexvar_epi64(const5_512, zmm13);
		zmm13 = _mm512_permutexvar_epi64(const5_512_, zmm13);

		zj256 = _mm256_loadu_si256((const __m256i*)(zh + 7));
		zmm15 = _mm512_cvtepu32_epi64(zj256);
		zmm14 = _mm512_permutexvar_epi64(const5_512, zmm15);
		zmm15 = _mm512_permutexvar_epi64(const5_512_, zmm15);

		macro_cpp_butterfly_512(zmm0, zmm1, zmm2, zmm12, zmm13, zmm14, zmm15,
			zmm9, zmm3, zmm6, zmm5, zmm4, zmm7, zmm8, zmm11);


		//level7:

		zj256 = _mm256_loadu_si256((const __m256i*)(zl + 15));
		zmm12 = _mm512_cvtepu32_epi64(zj256);

		zj256 = _mm256_loadu_si256((const __m256i*)(zl + 23));
		zmm13 = _mm512_cvtepu32_epi64(zj256);

		zj256 = _mm256_loadu_si256((const __m256i*)(zh + 15));
		zmm14 = _mm512_cvtepu32_epi64(zj256);

		zj256 = _mm256_loadu_si256((const __m256i*)(zh + 23));
		zmm15 = _mm512_cvtepu32_epi64(zj256);


		__m512i zmm9_ = _mm512_permutex2var_epi64(zmm9, const6_512, zmm4);	// 9
		zmm4 = _mm512_permutex2var_epi64(zmm9, const6_512_, zmm4);	// 4
		__m512i zmm3_ = _mm512_permutex2var_epi64(zmm3, const6_512, zmm7);	// 3
		zmm7 = _mm512_permutex2var_epi64(zmm3, const6_512_, zmm7);	// 7

		__m512i zmm6_ = _mm512_permutex2var_epi64(zmm6, const6_512, zmm8);	// 6
		zmm8 = _mm512_permutex2var_epi64(zmm6, const6_512_, zmm8);	// 8
		__m512i zmm5_ = _mm512_permutex2var_epi64(zmm5, const6_512, zmm11);	// 5
		zmm11 = _mm512_permutex2var_epi64(zmm5, const6_512_, zmm11);// 11


		macro_cpp_butterfly_512(zmm0, zmm1, zmm2, zmm12, zmm13, zmm14, zmm15,
			zmm9_, zmm3_, zmm6_, zmm5_, zmm4, zmm7, zmm8, zmm11);



		zmm9 = _mm512_permutex2var_epi32(zmm9_, const3_512, zmm4);	
		zmm3 = _mm512_permutex2var_epi32(zmm3_, const3_512, zmm7);	
		zmm6 = _mm512_permutex2var_epi32(zmm6_, const3_512, zmm8);	
		zmm5 = _mm512_permutex2var_epi32(zmm5_, const3_512, zmm11);	

		zmm9 = _mm512_permutex2var_epi64(zmm9, const4_512, zmm9);	
		zmm3 = _mm512_permutex2var_epi64(zmm3, const4_512, zmm3);	
		zmm6 = _mm512_permutex2var_epi64(zmm6, const4_512, zmm6);	
		zmm5 = _mm512_permutex2var_epi64(zmm5, const4_512, zmm5);	

		zmm10 = _mm512_permutex2var_epi64(zmm9, const7_512, zmm3);
		zmm11 = _mm512_permutex2var_epi64(zmm9, const7_512_, zmm3);	
		zmm12 = _mm512_permutex2var_epi64(zmm6, const7_512, zmm5);	
		zmm13 = _mm512_permutex2var_epi64(zmm6, const7_512_, zmm5);	

		//	store
		_mm512_store_si512(dest512, zmm10);
		_mm512_store_si512(dest512 + 1, zmm11);
		_mm512_store_si512(dest512 + 2, zmm12);
		_mm512_store_si512(dest512 + 3, zmm13);

		tmp512 += 8;
		dest512 += 4;
		zl += 62;
	}
}




void new_ntt_inv_512_cpp(uint32_t dest[N], uint32_t src[N], const uint32_t *zetas_inv)
{
	ALIGN64 uint64_t  tmp[N];
	__m512i* tmp512 = (__m512i*)tmp;
	__m512i zmm0 = _mm512_load_si512((__m512i*)_8xqinv_512);
	__m512i zmm1 = _mm512_load_si512((__m512i*)_8xq_512);
	__m512i zmm2 = _mm512_load_si512((__m512i*)_8x256q_512);
	
	__m512i* src512 = (__m512i*)src;
	__m512i	 zmm3, zmm4, zmm5, zmm6, zmm7, zmm8, zmm9, zmm10, zmm11, zmm12, zmm13, zmm14, zmm15;
	__m512i zmm16, zmm17, zmm18, zmm19, zmm20, zmm21, zmm22, zmm23, zmm24, zmm25, zmm26, zmm27;
	__m512i zmm28 , zmm29 , zmm30 , zmm31 ; 
		
	__m256i* z256l;
	__m256i* z256h, zj256;
	__m128i zj1, zj2;
	uint32_t i;

	for (i = 0; i < 4; i++)
	{
		z256l = (__m256i*)zetas_inv;
		z256h = (__m256i*)(zetas_inv + 31);
		zmm3 = _mm512_load_si512(src512);		
		zmm5 = _mm512_load_si512(src512 + 1);	
		zmm7 = _mm512_load_si512(src512 + 2);	
		zmm9 = _mm512_load_si512(src512 + 3);	

		zmm30 = const8_512; 
		zmm31 = const8_512_;
		zmm28 = const6_512; 
		zmm29 = const6_512_;
		zmm26 = const9_512; 
		zmm27 = const9_512_;
		shuffle_512(zmm3, zmm5, zmm4, zmm6, zmm30, zmm31);
		shuffle_512(zmm7, zmm9, zmm8, zmm10, zmm30, zmm31);

		zmm3 = _mm512_srli_epi64(zmm4, 32);
		zmm5 = _mm512_srli_epi64(zmm6, 32);
		zmm7 = _mm512_srli_epi64(zmm8, 32);
		zmm9 = _mm512_srli_epi64(zmm10, 32);

		zmm11 = _mm512_cvtepu32_epi64(*z256l);
		zmm12 = _mm512_cvtepu32_epi64(*(z256l + 1));
		zmm13 = _mm512_cvtepu32_epi64(*z256h);
		zmm14 = _mm512_cvtepu32_epi64(*(z256h + 1));

		zmm15 = _mm512_add_epi32(zmm4, zmm2);
		zmm16 = _mm512_add_epi32(zmm6, zmm2);
		zmm17 = _mm512_add_epi32(zmm8, zmm2);
		zmm18 = _mm512_add_epi32(zmm10, zmm2);

		zmm15 = _mm512_sub_epi32(zmm15, zmm3);
		zmm16 = _mm512_sub_epi32(zmm16, zmm5);
		zmm17 = _mm512_sub_epi32(zmm17, zmm7);
		zmm18 = _mm512_sub_epi32(zmm18, zmm9);

		zmm15 = _mm512_mul_epu32(zmm15, zmm11);
		zmm16 = _mm512_mul_epu32(zmm16, zmm12);
		zmm17 = _mm512_mul_epu32(zmm17, zmm13);
		zmm18 = _mm512_mul_epu32(zmm18, zmm14);

		zmm4 = _mm512_add_epi32(zmm3, zmm4);
		zmm6 = _mm512_add_epi32(zmm5, zmm6);
		zmm8 = _mm512_add_epi32(zmm7, zmm8);
		zmm10 = _mm512_add_epi32(zmm9, zmm10);

		zmm3 = _mm512_mul_epu32(zmm15, zmm0);
		zmm5 = _mm512_mul_epu32(zmm16, zmm0);
		zmm7 = _mm512_mul_epu32(zmm17, zmm0);
		zmm9 = _mm512_mul_epu32(zmm18, zmm0);

		zmm3 = _mm512_mul_epu32(zmm3, zmm1);
		zmm5 = _mm512_mul_epu32(zmm5, zmm1);
		zmm7 = _mm512_mul_epu32(zmm7, zmm1);
		zmm9 = _mm512_mul_epu32(zmm9, zmm1);

		zmm3 = _mm512_add_epi64(zmm3, zmm15);
		zmm5 = _mm512_add_epi64(zmm5, zmm16);
		zmm7 = _mm512_add_epi64(zmm7, zmm17);
		zmm9 = _mm512_add_epi64(zmm9, zmm18);

		zmm3 = _mm512_srli_epi64(zmm3, 32);
		zmm5 = _mm512_srli_epi64(zmm5, 32);
		zmm7 = _mm512_srli_epi64(zmm7, 32);
		zmm9 = _mm512_srli_epi64(zmm9, 32);

		shuffle_512(zmm4, zmm3, zmm17, zmm18, zmm28, zmm29);
		shuffle_512(zmm6, zmm5, zmm19, zmm20, zmm28, zmm29);
		shuffle_512(zmm8, zmm7, zmm21, zmm22, zmm28, zmm29);
		shuffle_512(zmm10, zmm9, zmm23, zmm24, zmm28, zmm29);

		zmm11 = _mm512_cvtepu32_epi64(*(z256l + 2));
		zmm13 = _mm512_cvtepu32_epi64(*(z256h + 2));
		shuffle_512(zmm11, zmm11, zmm4, zmm5, zmm28, zmm29);
		shuffle_512(zmm13, zmm13, zmm6, zmm7, zmm28, zmm29);

		cpp_batterfly_inv512_macro(
			zmm4, zmm5, zmm6, zmm7,
			zmm17, zmm19, zmm21, zmm23,
			zmm18, zmm20, zmm22, zmm24);

		zmm11 = _mm512_cvtepu32_epi64(*(z256l + 3));
		zmm13 = _mm512_cvtepu32_epi64(*(z256h + 3));

		shuffle_512(zmm11, zmm11, zmm4, zmm5, zmm28, zmm29);
		shuffle_512(zmm13, zmm13, zmm6, zmm7, zmm28, zmm29);

		cpp_batterfly_inv512_macro(
			zmm4, zmm4, zmm6, zmm6,
			zmm17, zmm18, zmm21, zmm22,
			zmm19, zmm20, zmm23, zmm24);

		//level3:
		shuffle_512(zmm17, zmm18, zmm3, zmm4, zmm26, zmm27);
		shuffle_512(zmm21, zmm22, zmm5, zmm6, zmm26, zmm27);
		shuffle_512(zmm19, zmm20, zmm7, zmm8, zmm26, zmm27);
		shuffle_512(zmm23, zmm24, zmm9, zmm10, zmm26, zmm27);

		zmm12 = const11_512;
		zmm17 = _mm512_loadu_si512((const __m128i*)(zetas_inv + 28));
		zmm18 = _mm512_loadu_si512((const __m128i*)(zetas_inv + 28 + 31));
		zmm11 = _mm512_permutex2var_epi32(zmm17, zmm12, zmm17);
		zmm12 = _mm512_permutex2var_epi32(zmm18, zmm12, zmm18);

		cpp_batterfly_inv512_macro(
			zmm11, zmm11, zmm12, zmm12,
			zmm3, zmm7, zmm5, zmm9,
			zmm4, zmm8, zmm6, zmm10);

		// level 4
		zmm26 = const10_512;
		zmm27 = const10_512_;
		shuffle_512(zmm3, zmm7, zmm20, zmm21, zmm26, zmm27);
		shuffle_512(zmm5, zmm9, zmm22, zmm23, zmm26, zmm27);
		shuffle_512(zmm4, zmm8, zmm3, zmm7, zmm26, zmm27);
		shuffle_512(zmm6, zmm10, zmm5, zmm9, zmm26, zmm27);

		zj1 = _mm_loadu_si128((const __m128i*)(zetas_inv + 30));
		zmm11 = _mm512_broadcastd_epi32(zj1);
		zj2 = _mm_loadu_si128((const __m128i*)(zetas_inv + 61));
		zmm12 = _mm512_broadcastd_epi32(zj2);


		cpp_batterfly_inv512_macro(
			zmm11, zmm11, zmm12, zmm12,
			zmm20, zmm3, zmm22, zmm5,
			zmm21, zmm7, zmm23, zmm9);

		_mm512_store_si512(tmp512, zmm20);
		_mm512_store_si512(tmp512 + 1, zmm3);
		_mm512_store_si512(tmp512 + 2, zmm21);
		_mm512_store_si512(tmp512 + 3, zmm7);
		_mm512_store_si512(tmp512 + 4, zmm22);
		_mm512_store_si512(tmp512 + 5, zmm5);
		_mm512_store_si512(tmp512 + 6, zmm23);
		_mm512_store_si512(tmp512 + 7, zmm9);
		src512 += 4;
		tmp512 += 8;
		zetas_inv += 62;

	}

	{
		
		
		__m512i* dest512 = (__m512i*)dest;
		tmp512 = (__m512i*)tmp;
		
		zmm3 = _mm512_load_si512((const __m512i*)_8xdiv_512);
		zj256 = _mm256_load_si256((const __m256i*)zetas_inv);
		zj1 = _mm256_extractf128_si256(zj256, 0);
		zj2 = _mm256_extractf128_si256(zj256, 1);

		zmm31 = _mm512_broadcastd_epi32(zj1);
		zj1 = _mm_alignr_epi32(zj1, zj1, 1);
		zmm30 = _mm512_broadcastd_epi32(zj1);
		zj1 = _mm_alignr_epi32(zj1, zj1, 1);
		zmm29 = _mm512_broadcastd_epi32(zj1);
		zj1 = _mm_alignr_epi32(zj1, zj1, 1);
		zmm28 = _mm512_broadcastd_epi32(zj1);
		zmm27 = _mm512_broadcastd_epi32(zj2);
		zj2 = _mm_alignr_epi32(zj2, zj2, 1);
		zmm26 = _mm512_broadcastd_epi32(zj2);
		zj2 = _mm_alignr_epi32(zj2, zj2, 1);
		zmm25 = _mm512_broadcastd_epi32(zj2);

		for (i = 0; i < 2; i++)
		{
			zmm4 = _mm512_load_si512(tmp512);
			zmm5 = _mm512_load_si512(tmp512 + 4);
			zmm6 = _mm512_load_si512(tmp512 + 8);
			zmm7 = _mm512_load_si512(tmp512 + 12);
			zmm8 = _mm512_load_si512(tmp512 + 16);
			zmm9 = _mm512_load_si512(tmp512 + 20);
			zmm10 = _mm512_load_si512(tmp512 + 24);
			zmm11 = _mm512_load_si512(tmp512 + 28);

			//level5:
			zmm13 = _mm512_add_epi32(zmm4, zmm2);
			zmm14 = _mm512_add_epi32(zmm6, zmm2);
			zmm15 = _mm512_add_epi32(zmm8, zmm2);
			zmm16 = _mm512_add_epi32(zmm10, zmm2);

			zmm13 = _mm512_sub_epi32(zmm13, zmm5);
			zmm14 = _mm512_sub_epi32(zmm14, zmm7);
			zmm15 = _mm512_sub_epi32(zmm15, zmm9);
			zmm16 = _mm512_sub_epi32(zmm16, zmm11);

			zmm13 = _mm512_mul_epu32(zmm13, zmm31);
			zmm14 = _mm512_mul_epu32(zmm14, zmm30);
			zmm15 = _mm512_mul_epu32(zmm15, zmm29);
			zmm16 = _mm512_mul_epu32(zmm16, zmm28);

			zmm4 = _mm512_add_epi32(zmm5, zmm4);
			zmm6 = _mm512_add_epi32(zmm7, zmm6);
			zmm8 = _mm512_add_epi32(zmm9, zmm8);
			zmm10 = _mm512_add_epi32(zmm11, zmm10);

			zmm5 = _mm512_mul_epu32(zmm13, zmm0);
			zmm7 = _mm512_mul_epu32(zmm14, zmm0);
			zmm9 = _mm512_mul_epu32(zmm15, zmm0);
			zmm11 = _mm512_mul_epu32(zmm16, zmm0);

			zmm5 = _mm512_mul_epu32(zmm5, zmm1);
			zmm7 = _mm512_mul_epu32(zmm7, zmm1);
			zmm9 = _mm512_mul_epu32(zmm9, zmm1);
			zmm11 = _mm512_mul_epu32(zmm11, zmm1);

			zmm5 = _mm512_add_epi64(zmm5, zmm13);
			zmm7 = _mm512_add_epi64(zmm7, zmm14);
			zmm9 = _mm512_add_epi64(zmm9, zmm15);
			zmm11 = _mm512_add_epi64(zmm11, zmm16);

			zmm5 = _mm512_srli_epi64(zmm5, 32);
			zmm7 = _mm512_srli_epi64(zmm7, 32);
			zmm9 = _mm512_srli_epi64(zmm9, 32);
			zmm11 = _mm512_srli_epi64(zmm11, 32);

			//level6:
			shuffle_512(zmm4, zmm5, zmm18, zmm19, const6_512, const6_512_);
			shuffle_512(zmm6, zmm7, zmm20, zmm21, const6_512, const6_512_);
			shuffle_512(zmm8, zmm9, zmm4, zmm5, const6_512, const6_512_);
			shuffle_512(zmm10, zmm11, zmm6, zmm7, const6_512, const6_512_);

			cpp_batterfly_inv512_macro(
				zmm27, zmm26, zmm27, zmm26,
				zmm18, zmm4, zmm19, zmm5,
				zmm20, zmm6, zmm21, zmm7);

			cpp_batterfly_inv512_macro(
				zmm25, zmm25, zmm25, zmm25,
				zmm18, zmm20, zmm19, zmm21,
				zmm4, zmm6, zmm5, zmm7);

			zmm18 = _mm512_mul_epu32(zmm18, zmm3);
			zmm20 = _mm512_mul_epu32(zmm20, zmm3);
			zmm19 = _mm512_mul_epu32(zmm19, zmm3);
			zmm21 = _mm512_mul_epu32(zmm21, zmm3);

			zmm12 = _mm512_mul_epu32(zmm18, zmm0);
			zmm22 = _mm512_mul_epu32(zmm20, zmm0);
			zmm23 = _mm512_mul_epu32(zmm19, zmm0);
			zmm24 = _mm512_mul_epu32(zmm21, zmm0);

			zmm12 = _mm512_mul_epu32(zmm12, zmm1);
			zmm22 = _mm512_mul_epu32(zmm22, zmm1);
			zmm23 = _mm512_mul_epu32(zmm23, zmm1);
			zmm24 = _mm512_mul_epu32(zmm24, zmm1);

			zmm18 = _mm512_add_epi64(zmm18, zmm12);	
			zmm20 = _mm512_add_epi64(zmm20, zmm22);	
			zmm19 = _mm512_add_epi64(zmm19, zmm23);	
			zmm21 = _mm512_add_epi64(zmm21, zmm24);	

			zmm12 = _mm512_permutex2var_epi32(zmm18, const13_512, zmm19);
			zmm22 = _mm512_permutex2var_epi32(zmm20, const13_512, zmm21);
			zmm23 = _mm512_permutex2var_epi32(zmm4, const14_512, zmm5);
			zmm24 = _mm512_permutex2var_epi32(zmm6, const14_512, zmm7);

			zmm4 = _mm512_load_si512(tmp512 + 1);
			zmm5 = _mm512_load_si512(tmp512 + 5);
			zmm6 = _mm512_load_si512(tmp512 + 9);
			zmm7 = _mm512_load_si512(tmp512 + 13);
			zmm8 = _mm512_load_si512(tmp512 + 17);
			zmm9 = _mm512_load_si512(tmp512 + 21);
			zmm10 = _mm512_load_si512(tmp512 + 25);
			zmm11 = _mm512_load_si512(tmp512 + 29);

			//level5:
			zmm13 = _mm512_add_epi32(zmm4, zmm2);
			zmm14 = _mm512_add_epi32(zmm6, zmm2);
			zmm15 = _mm512_add_epi32(zmm8, zmm2);
			zmm16 = _mm512_add_epi32(zmm10, zmm2);

			zmm13 = _mm512_sub_epi32(zmm13, zmm5);
			zmm14 = _mm512_sub_epi32(zmm14, zmm7);
			zmm15 = _mm512_sub_epi32(zmm15, zmm9);
			zmm16 = _mm512_sub_epi32(zmm16, zmm11);

			zmm13 = _mm512_mul_epu32(zmm13, zmm31);
			zmm14 = _mm512_mul_epu32(zmm14, zmm30);
			zmm15 = _mm512_mul_epu32(zmm15, zmm29);
			zmm16 = _mm512_mul_epu32(zmm16, zmm28);

			zmm4 = _mm512_add_epi32(zmm5, zmm4);
			zmm6 = _mm512_add_epi32(zmm7, zmm6);
			zmm8 = _mm512_add_epi32(zmm9, zmm8);
			zmm10 = _mm512_add_epi32(zmm11, zmm10);

			zmm5 = _mm512_mul_epu32(zmm13, zmm0);
			zmm7 = _mm512_mul_epu32(zmm14, zmm0);
			zmm9 = _mm512_mul_epu32(zmm15, zmm0);
			zmm11 = _mm512_mul_epu32(zmm16, zmm0);

			zmm5 = _mm512_mul_epu32(zmm5, zmm1);
			zmm7 = _mm512_mul_epu32(zmm7, zmm1);
			zmm9 = _mm512_mul_epu32(zmm9, zmm1);
			zmm11 = _mm512_mul_epu32(zmm11, zmm1);

			zmm5 = _mm512_add_epi64(zmm5, zmm13);
			zmm7 = _mm512_add_epi64(zmm7, zmm14);
			zmm9 = _mm512_add_epi64(zmm9, zmm15);
			zmm11 = _mm512_add_epi64(zmm11, zmm16);

			zmm5 = _mm512_srli_epi64(zmm5, 32);
			zmm7 = _mm512_srli_epi64(zmm7, 32);
			zmm9 = _mm512_srli_epi64(zmm9, 32);
			zmm11 = _mm512_srli_epi64(zmm11, 32);

			//level6:
			shuffle_512(zmm4, zmm5, zmm18, zmm19, const6_512, const6_512_);
			shuffle_512(zmm6, zmm7, zmm20, zmm21, const6_512, const6_512_);
			shuffle_512(zmm8, zmm9, zmm4, zmm5, const6_512, const6_512_);
			shuffle_512(zmm10, zmm11, zmm6, zmm7, const6_512, const6_512_);

			cpp_batterfly_inv512_macro(
				zmm27, zmm26, zmm27, zmm26,
				zmm18, zmm4, zmm19, zmm5,
				zmm20, zmm6, zmm21, zmm7);

			cpp_batterfly_inv512_macro(
				zmm25, zmm25, zmm25, zmm25,
				zmm18, zmm20, zmm19, zmm21,
				zmm4, zmm6, zmm5, zmm7);

			zmm18 = _mm512_mul_epu32(zmm18, zmm3);
			zmm20 = _mm512_mul_epu32(zmm20, zmm3);
			zmm19 = _mm512_mul_epu32(zmm19, zmm3);
			zmm21 = _mm512_mul_epu32(zmm21, zmm3);

			zmm8 = _mm512_mul_epu32(zmm18, zmm0);
			zmm9 = _mm512_mul_epu32(zmm20, zmm0);
			zmm10 = _mm512_mul_epu32(zmm19, zmm0);
			zmm11 = _mm512_mul_epu32(zmm21, zmm0);

			zmm8 = _mm512_mul_epu32(zmm8, zmm1);
			zmm9 = _mm512_mul_epu32(zmm9, zmm1);
			zmm10 = _mm512_mul_epu32(zmm10, zmm1);
			zmm11 = _mm512_mul_epu32(zmm11, zmm1);

			zmm18 = _mm512_add_epi64(zmm18, zmm8);	
			zmm20 = _mm512_add_epi64(zmm20, zmm9);	
			zmm19 = _mm512_add_epi64(zmm19, zmm10);	
			zmm21 = _mm512_add_epi64(zmm21, zmm11);	

			zmm8 = _mm512_permutex2var_epi32(zmm18, const13_512, zmm19);
			zmm9 = _mm512_permutex2var_epi32(zmm20, const13_512, zmm21);
			zmm10 = _mm512_permutex2var_epi32(zmm4, const14_512, zmm5);
			zmm11 = _mm512_permutex2var_epi32(zmm6, const14_512, zmm7);

			zmm14 = _mm512_permutex2var_epi64(zmm12, const6_512, zmm8);
			zmm15 = _mm512_permutex2var_epi64(zmm12, const6_512_, zmm8);

			zmm16 = _mm512_permutex2var_epi64(zmm22, const6_512, zmm9);
			zmm17 = _mm512_permutex2var_epi64(zmm22, const6_512_, zmm9);

			zmm12 = _mm512_permutex2var_epi64(zmm23, const6_512, zmm10);
			zmm8 = _mm512_permutex2var_epi64(zmm23, const6_512_, zmm10);

			zmm22 = _mm512_permutex2var_epi64(zmm24, const6_512, zmm11);
			zmm9 = _mm512_permutex2var_epi64(zmm24, const6_512_, zmm11);

			_mm512_store_si512(dest512, zmm14);
			_mm512_store_si512(dest512 + 2, zmm15);
			_mm512_store_si512(dest512 + 4, zmm16);
			_mm512_store_si512(dest512 + 6, zmm17);
			_mm512_store_si512(dest512 + 8, zmm12);
			_mm512_store_si512(dest512 + 10, zmm8);
			_mm512_store_si512(dest512 + 12, zmm22);
			_mm512_store_si512(dest512 + 14, zmm9);
			tmp512 += 2;
			dest512++;

		}
	}
}


void new_pointwise_mul_512_cpp(uint32_t* c, const uint32_t* a, const uint32_t* b)
{

	__m512i zmm0, zmm1, zmm2, zmm3, zmm4, zmm5, zmm6, zmm7,
			zmm8, zmm9, zmm10, zmm11, zmm12, zmm13, zmm14, zmm15,
			zmm30, zmm31;
	__m512i* a512 = (__m512i*)a, * b512 = (__m512i*)b, * c512 = (__m512i*)c;

	zmm30 = _mm512_load_si512((__m512i*)_8xqinv_512);
	zmm31 = _mm512_load_si512((__m512i*)_8xq_512);
			
	zmm0 = _mm512_load_si512(a512);
	zmm2 = _mm512_load_si512(a512 + 1);
	zmm4 = _mm512_load_si512(a512 + 2);
	zmm6 = _mm512_load_si512(a512 + 3);
		
	zmm8 = _mm512_load_si512(b512);
	zmm10 = _mm512_load_si512(b512 + 1);
	zmm12 = _mm512_load_si512(b512 + 2);
	zmm14 = _mm512_load_si512(b512 + 3);
		
	zmm1 = _mm512_srli_epi64(zmm0, 32);
	zmm3 = _mm512_srli_epi64(zmm2, 32);
	zmm5 = _mm512_srli_epi64(zmm4, 32);
	zmm7 = _mm512_srli_epi64(zmm6, 32);
	zmm9 = _mm512_srli_epi64(zmm8, 32);
	zmm11 = _mm512_srli_epi64(zmm10, 32);
	zmm13 = _mm512_srli_epi64(zmm12, 32);
	zmm15 = _mm512_srli_epi64(zmm14, 32);

	zmm0 = _mm512_mul_epu32(zmm8, zmm0);
	zmm1 = _mm512_mul_epu32(zmm9, zmm1);
	zmm2 = _mm512_mul_epu32(zmm10, zmm2);
	zmm3 = _mm512_mul_epu32(zmm11, zmm3);
	zmm4 = _mm512_mul_epu32(zmm12, zmm4);
	zmm5 = _mm512_mul_epu32(zmm13, zmm5);
	zmm6 = _mm512_mul_epu32(zmm14, zmm6);
	zmm7 = _mm512_mul_epu32(zmm15, zmm7);

	zmm8 = _mm512_mul_epu32(zmm0, zmm30);
	zmm9 = _mm512_mul_epu32(zmm1, zmm30);
	zmm10 = _mm512_mul_epu32(zmm2, zmm30);
	zmm11 = _mm512_mul_epu32(zmm3, zmm30);
	zmm12 = _mm512_mul_epu32(zmm4, zmm30);
	zmm13 = _mm512_mul_epu32(zmm5, zmm30);
	zmm14 = _mm512_mul_epu32(zmm6, zmm30);
	zmm15 = _mm512_mul_epu32(zmm7, zmm30);

	zmm8 = _mm512_mul_epu32(zmm8, zmm31);
	zmm9 = _mm512_mul_epu32(zmm9, zmm31);
	zmm10 = _mm512_mul_epu32(zmm10, zmm31);
	zmm11 = _mm512_mul_epu32(zmm11, zmm31);
	zmm12 = _mm512_mul_epu32(zmm12, zmm31);
	zmm13 = _mm512_mul_epu32(zmm13, zmm31);
	zmm14 = _mm512_mul_epu32(zmm14, zmm31);
	zmm15 = _mm512_mul_epu32(zmm15, zmm31);

	zmm0 = _mm512_add_epi64(zmm8, zmm0);
	zmm1 = _mm512_add_epi64(zmm9, zmm1);
	zmm2 = _mm512_add_epi64(zmm10, zmm2);
	zmm3 = _mm512_add_epi64(zmm11, zmm3);
	zmm4 = _mm512_add_epi64(zmm12, zmm4);
	zmm5 = _mm512_add_epi64(zmm13, zmm5);
	zmm6 = _mm512_add_epi64(zmm14, zmm6);
	zmm7 = _mm512_add_epi64(zmm15, zmm7);

	zmm0 = _mm512_srli_epi64(zmm0, 32);
	zmm2 = _mm512_srli_epi64(zmm2, 32);
	zmm4 = _mm512_srli_epi64(zmm4, 32);
	zmm6 = _mm512_srli_epi64(zmm6, 32);

	zmm0 = _mm512_mask_blend_epi32(0x5555, zmm1, zmm0);
	zmm2 = _mm512_mask_blend_epi32(0x5555, zmm3, zmm2);
	zmm4 = _mm512_mask_blend_epi32(0x5555, zmm5, zmm4);
	zmm6 = _mm512_mask_blend_epi32(0x5555, zmm7, zmm6);

	_mm512_store_si512(c512, zmm0);
	_mm512_store_si512(c512 + 1, zmm2);
	_mm512_store_si512(c512 + 2, zmm4);
	_mm512_store_si512(c512 + 3, zmm6);

	c512 += 4;
	b512 += 4;
	a512 += 4;
	zmm0 = _mm512_load_si512(a512);
	zmm2 = _mm512_load_si512(a512 + 1);
	zmm4 = _mm512_load_si512(a512 + 2);
	zmm6 = _mm512_load_si512(a512 + 3);

	zmm8 = _mm512_load_si512(b512);
	zmm10 = _mm512_load_si512(b512 + 1);
	zmm12 = _mm512_load_si512(b512 + 2);
	zmm14 = _mm512_load_si512(b512 + 3);

	zmm1 = _mm512_srli_epi64(zmm0, 32);
	zmm3 = _mm512_srli_epi64(zmm2, 32);
	zmm5 = _mm512_srli_epi64(zmm4, 32);
	zmm7 = _mm512_srli_epi64(zmm6, 32);
	zmm9 = _mm512_srli_epi64(zmm8, 32);
	zmm11 = _mm512_srli_epi64(zmm10, 32);
	zmm13 = _mm512_srli_epi64(zmm12, 32);
	zmm15 = _mm512_srli_epi64(zmm14, 32);

	zmm0 = _mm512_mul_epu32(zmm8, zmm0);
	zmm1 = _mm512_mul_epu32(zmm9, zmm1);
	zmm2 = _mm512_mul_epu32(zmm10, zmm2);
	zmm3 = _mm512_mul_epu32(zmm11, zmm3);
	zmm4 = _mm512_mul_epu32(zmm12, zmm4);
	zmm5 = _mm512_mul_epu32(zmm13, zmm5);
	zmm6 = _mm512_mul_epu32(zmm14, zmm6);
	zmm7 = _mm512_mul_epu32(zmm15, zmm7);

	zmm8 = _mm512_mul_epu32(zmm0, zmm30);
	zmm9 = _mm512_mul_epu32(zmm1, zmm30);
	zmm10 = _mm512_mul_epu32(zmm2, zmm30);
	zmm11 = _mm512_mul_epu32(zmm3, zmm30);
	zmm12 = _mm512_mul_epu32(zmm4, zmm30);
	zmm13 = _mm512_mul_epu32(zmm5, zmm30);
	zmm14 = _mm512_mul_epu32(zmm6, zmm30);
	zmm15 = _mm512_mul_epu32(zmm7, zmm30);

	zmm8 = _mm512_mul_epu32(zmm8, zmm31);
	zmm9 = _mm512_mul_epu32(zmm9, zmm31);
	zmm10 = _mm512_mul_epu32(zmm10, zmm31);
	zmm11 = _mm512_mul_epu32(zmm11, zmm31);
	zmm12 = _mm512_mul_epu32(zmm12, zmm31);
	zmm13 = _mm512_mul_epu32(zmm13, zmm31);
	zmm14 = _mm512_mul_epu32(zmm14, zmm31);
	zmm15 = _mm512_mul_epu32(zmm15, zmm31);

	zmm0 = _mm512_add_epi64(zmm8, zmm0);
	zmm1 = _mm512_add_epi64(zmm9, zmm1);
	zmm2 = _mm512_add_epi64(zmm10, zmm2);
	zmm3 = _mm512_add_epi64(zmm11, zmm3);
	zmm4 = _mm512_add_epi64(zmm12, zmm4);
	zmm5 = _mm512_add_epi64(zmm13, zmm5);
	zmm6 = _mm512_add_epi64(zmm14, zmm6);
	zmm7 = _mm512_add_epi64(zmm15, zmm7);

	zmm0 = _mm512_srli_epi64(zmm0, 32);
	zmm2 = _mm512_srli_epi64(zmm2, 32);
	zmm4 = _mm512_srli_epi64(zmm4, 32);
	zmm6 = _mm512_srli_epi64(zmm6, 32);


	zmm0 = _mm512_mask_blend_epi32(0x5555, zmm1, zmm0);
	zmm2 = _mm512_mask_blend_epi32(0x5555, zmm3, zmm2);
	zmm4 = _mm512_mask_blend_epi32(0x5555, zmm5, zmm4);
	zmm6 = _mm512_mask_blend_epi32(0x5555, zmm7, zmm6);

	_mm512_store_si512(c512, zmm0);
	_mm512_store_si512(c512 + 1, zmm2);
	_mm512_store_si512(c512 + 2, zmm4);
	_mm512_store_si512(c512 + 3, zmm6);

	c512 += 4;
	b512 += 4;
	a512 += 4;
	zmm0 = _mm512_load_si512(a512);
	zmm2 = _mm512_load_si512(a512 + 1);
	zmm4 = _mm512_load_si512(a512 + 2);
	zmm6 = _mm512_load_si512(a512 + 3);

	zmm8 = _mm512_load_si512(b512);
	zmm10 = _mm512_load_si512(b512 + 1);
	zmm12 = _mm512_load_si512(b512 + 2);
	zmm14 = _mm512_load_si512(b512 + 3);

	zmm1 = _mm512_srli_epi64(zmm0, 32);
	zmm3 = _mm512_srli_epi64(zmm2, 32);
	zmm5 = _mm512_srli_epi64(zmm4, 32);
	zmm7 = _mm512_srli_epi64(zmm6, 32);
	zmm9 = _mm512_srli_epi64(zmm8, 32);
	zmm11 = _mm512_srli_epi64(zmm10, 32);
	zmm13 = _mm512_srli_epi64(zmm12, 32);
	zmm15 = _mm512_srli_epi64(zmm14, 32);

	zmm0 = _mm512_mul_epu32(zmm8, zmm0);
	zmm1 = _mm512_mul_epu32(zmm9, zmm1);
	zmm2 = _mm512_mul_epu32(zmm10, zmm2);
	zmm3 = _mm512_mul_epu32(zmm11, zmm3);
	zmm4 = _mm512_mul_epu32(zmm12, zmm4);
	zmm5 = _mm512_mul_epu32(zmm13, zmm5);
	zmm6 = _mm512_mul_epu32(zmm14, zmm6);
	zmm7 = _mm512_mul_epu32(zmm15, zmm7);

	zmm8 = _mm512_mul_epu32(zmm0, zmm30);
	zmm9 = _mm512_mul_epu32(zmm1, zmm30);
	zmm10 = _mm512_mul_epu32(zmm2, zmm30);
	zmm11 = _mm512_mul_epu32(zmm3, zmm30);
	zmm12 = _mm512_mul_epu32(zmm4, zmm30);
	zmm13 = _mm512_mul_epu32(zmm5, zmm30);
	zmm14 = _mm512_mul_epu32(zmm6, zmm30);
	zmm15 = _mm512_mul_epu32(zmm7, zmm30);

	zmm8 = _mm512_mul_epu32(zmm8, zmm31);
	zmm9 = _mm512_mul_epu32(zmm9, zmm31);
	zmm10 = _mm512_mul_epu32(zmm10, zmm31);
	zmm11 = _mm512_mul_epu32(zmm11, zmm31);
	zmm12 = _mm512_mul_epu32(zmm12, zmm31);
	zmm13 = _mm512_mul_epu32(zmm13, zmm31);
	zmm14 = _mm512_mul_epu32(zmm14, zmm31);
	zmm15 = _mm512_mul_epu32(zmm15, zmm31);

	zmm0 = _mm512_add_epi64(zmm8, zmm0);
	zmm1 = _mm512_add_epi64(zmm9, zmm1);
	zmm2 = _mm512_add_epi64(zmm10, zmm2);
	zmm3 = _mm512_add_epi64(zmm11, zmm3);
	zmm4 = _mm512_add_epi64(zmm12, zmm4);
	zmm5 = _mm512_add_epi64(zmm13, zmm5);
	zmm6 = _mm512_add_epi64(zmm14, zmm6);
	zmm7 = _mm512_add_epi64(zmm15, zmm7);

	zmm0 = _mm512_srli_epi64(zmm0, 32);
	zmm2 = _mm512_srli_epi64(zmm2, 32);
	zmm4 = _mm512_srli_epi64(zmm4, 32);
	zmm6 = _mm512_srli_epi64(zmm6, 32);


	zmm0 = _mm512_mask_blend_epi32(0x5555, zmm1, zmm0);
	zmm2 = _mm512_mask_blend_epi32(0x5555, zmm3, zmm2);
	zmm4 = _mm512_mask_blend_epi32(0x5555, zmm5, zmm4);
	zmm6 = _mm512_mask_blend_epi32(0x5555, zmm7, zmm6);

	_mm512_store_si512(c512, zmm0);
	_mm512_store_si512(c512 + 1, zmm2);
	_mm512_store_si512(c512 + 2, zmm4);
	_mm512_store_si512(c512 + 3, zmm6);

	c512 += 4;
	b512 += 4;
	a512 += 4;
	zmm0 = _mm512_load_si512(a512);
	zmm2 = _mm512_load_si512(a512 + 1);
	zmm4 = _mm512_load_si512(a512 + 2);
	zmm6 = _mm512_load_si512(a512 + 3);

	zmm8 = _mm512_load_si512(b512);
	zmm10 = _mm512_load_si512(b512 + 1);
	zmm12 = _mm512_load_si512(b512 + 2);
	zmm14 = _mm512_load_si512(b512 + 3);

	zmm1 = _mm512_srli_epi64(zmm0, 32);
	zmm3 = _mm512_srli_epi64(zmm2, 32);
	zmm5 = _mm512_srli_epi64(zmm4, 32);
	zmm7 = _mm512_srli_epi64(zmm6, 32);
	zmm9 = _mm512_srli_epi64(zmm8, 32);
	zmm11 = _mm512_srli_epi64(zmm10, 32);
	zmm13 = _mm512_srli_epi64(zmm12, 32);
	zmm15 = _mm512_srli_epi64(zmm14, 32);

	zmm0 = _mm512_mul_epu32(zmm8, zmm0);
	zmm1 = _mm512_mul_epu32(zmm9, zmm1);
	zmm2 = _mm512_mul_epu32(zmm10, zmm2);
	zmm3 = _mm512_mul_epu32(zmm11, zmm3);
	zmm4 = _mm512_mul_epu32(zmm12, zmm4);
	zmm5 = _mm512_mul_epu32(zmm13, zmm5);
	zmm6 = _mm512_mul_epu32(zmm14, zmm6);
	zmm7 = _mm512_mul_epu32(zmm15, zmm7);

	zmm8 = _mm512_mul_epu32(zmm0, zmm30);
	zmm9 = _mm512_mul_epu32(zmm1, zmm30);
	zmm10 = _mm512_mul_epu32(zmm2, zmm30);
	zmm11 = _mm512_mul_epu32(zmm3, zmm30);
	zmm12 = _mm512_mul_epu32(zmm4, zmm30);
	zmm13 = _mm512_mul_epu32(zmm5, zmm30);
	zmm14 = _mm512_mul_epu32(zmm6, zmm30);
	zmm15 = _mm512_mul_epu32(zmm7, zmm30);

	zmm8 = _mm512_mul_epu32(zmm8, zmm31);
	zmm9 = _mm512_mul_epu32(zmm9, zmm31);
	zmm10 = _mm512_mul_epu32(zmm10, zmm31);
	zmm11 = _mm512_mul_epu32(zmm11, zmm31);
	zmm12 = _mm512_mul_epu32(zmm12, zmm31);
	zmm13 = _mm512_mul_epu32(zmm13, zmm31);
	zmm14 = _mm512_mul_epu32(zmm14, zmm31);
	zmm15 = _mm512_mul_epu32(zmm15, zmm31);

	zmm0 = _mm512_add_epi64(zmm8, zmm0);
	zmm1 = _mm512_add_epi64(zmm9, zmm1);
	zmm2 = _mm512_add_epi64(zmm10, zmm2);
	zmm3 = _mm512_add_epi64(zmm11, zmm3);
	zmm4 = _mm512_add_epi64(zmm12, zmm4);
	zmm5 = _mm512_add_epi64(zmm13, zmm5);
	zmm6 = _mm512_add_epi64(zmm14, zmm6);
	zmm7 = _mm512_add_epi64(zmm15, zmm7);

	zmm0 = _mm512_srli_epi64(zmm0, 32);
	zmm2 = _mm512_srli_epi64(zmm2, 32);
	zmm4 = _mm512_srli_epi64(zmm4, 32);
	zmm6 = _mm512_srli_epi64(zmm6, 32);


	zmm0 = _mm512_mask_blend_epi32(0x5555, zmm1, zmm0);
	zmm2 = _mm512_mask_blend_epi32(0x5555, zmm3, zmm2);
	zmm4 = _mm512_mask_blend_epi32(0x5555, zmm5, zmm4);
	zmm6 = _mm512_mask_blend_epi32(0x5555, zmm7, zmm6);

	_mm512_store_si512(c512, zmm0);
	_mm512_store_si512(c512 + 1, zmm2);
	_mm512_store_si512(c512 + 2, zmm4);
	_mm512_store_si512(c512 + 3, zmm6);
}
