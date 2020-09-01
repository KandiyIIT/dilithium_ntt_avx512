#include <stdint.h>
#include <stdio.h>
#include <immintrin.h>
#include <math.h>
#include "parameters.h"
#include <stdlib.h>
#include <string.h>

#include "ntt.h"
#include <omp.h>
#include <time.h>



#define TESTS	100000
uint64_t start, dif, finish, mintime = 0xffffffff, maxtime = 0;

extern const uint32_t new_zetas[];
extern const uint32_t new_zetas_inv[N];

static inline long long __rdtsc(void)
{
  unsigned long long result;
  asm volatile(".byte 15;.byte 49;shlq $32,%%rdx;orq %%rdx,%%rax"
    : "=a" (result) ::  "%rdx");
  return result;
}

static void random_pol(uint32_t* a) {
	unsigned int i;
	uint32_t t;

	i = 0;
	while (i < N) {
		t = (rand() << 8) | (rand() % 256);
		if (t < Q_)
			a[i++] = t;
	}
}



void test_ntt()
{
	ALIGN64 uint32_t  a[N], c1[N], c2[N];
	uint32_t i, j, k;

	ALIGN64 uint64_t  tmp[N];
	random_pol(a);

	printf("\n\n====TESTING NTT====\n");

	mintime = 0xffffffff, maxtime = 0;
	for (i = 0; i < TESTS; i++)
	{
		start = __rdtsc();
  		for(j = 0; j < N/32; ++j)
    			ntt_levels0t2_avx(tmp + 4*j, a + 4*j, &new_zetas[1]);
  		for(j = 0; j < N/32; ++j)
    			ntt_levels3t8_avx(a + 32*j, tmp + 32*j, new_zetas + 8 + 31*j);
		finish = __rdtsc();
		dif = finish - start;
		if (dif < mintime)
			mintime = dif;
		if (dif > maxtime)
			maxtime = dif;
	}

	
	printf("dilithium_ntt: time = [%lu : %lu]\n", mintime, maxtime);
		
	mintime = 0xffffffff, maxtime = 0;
	for (i = 0; i < TESTS; i++)
	{
		start = __rdtsc();
		new_ntt_512_cpp_(c2, a, new_zetas);
		finish = __rdtsc();
		dif = finish - start;
		if (dif < mintime)
			mintime = dif;
		if (dif > maxtime)
			maxtime = dif;
	}

	printf("new_ntt_512_cpp_: time = [%lu : %lu]\n", mintime, maxtime);
	
	mintime = 0xffffffff, maxtime = 0;
	for (i = 0; i < TESTS; i++)
	{
		start = __rdtsc();
		new_ntt_512_asm__(c2, a, new_zetas);
		finish = __rdtsc();
		dif = finish - start;
		if (dif < mintime)
			mintime = dif;
		if (dif > maxtime)
			maxtime = dif;
	}

	printf("new_ntt_512_asm__: time = [%lu : %lu]\n", mintime, maxtime);

}

void test_pointwise()
{
	printf("\n\n====TESTING POINTWISE====\n");

	ALIGN64 uint32_t  a[N], b[N], c1[N], c2[N], i, j;
	random_pol(a);
	random_pol(b);
	
	mintime = 0xffffffff, maxtime = 0;
	for (i = 0; i < TESTS; i++)
	{
		start = __rdtsc();
		new_pointwise_mul_512_cpp(c2, a, b);
		finish = __rdtsc();
		dif = finish - start;
		if (dif < mintime)
			mintime = dif;
		if (dif > maxtime)
			maxtime = dif;
	}

	printf("new_pointwise_mul_512_cpp : time = [%lu : %lu]\n", mintime, maxtime);
		
	mintime = 0xffffffff, maxtime = 0;
	for (i = 0; i < TESTS; i++)
	{
		start = __rdtsc();
		pointwise_avx(c2, a, b);
		finish = __rdtsc();
		dif = finish - start;
		if (dif < mintime)
			mintime = dif;
		if (dif > maxtime)
			maxtime = dif;
	}

	printf("dilithium_pointwise_avx: time = [%lu : %lu]\n", mintime, maxtime);

}
void test_invntt()
{
	
	ALIGN64 uint32_t  a[N], c1[N], c2[N], i, j;
	ALIGN64 uint64_t  tmp[N];
	random_pol(a);

	printf("\n\n====TESTING INV NTT====\n");

	mintime = 0xffffffff, maxtime = 0;
	for (i = 0; i < TESTS; i++)
	{
		start = __rdtsc();
		new_ntt_inv_512_cpp(c2, a, new_zetas_inv);
		finish = __rdtsc();
		dif = finish - start;
		if (dif < mintime)
			mintime = dif;
		if (dif > maxtime)
			maxtime = dif;
	}


	printf("new_ntt_inv_512_cpp : time = [%lu : %lu]\n", mintime, maxtime);
	
	mintime = 0xffffffff, maxtime = 0;
	for (i = 0; i < TESTS; i++)
	{
		start = __rdtsc();
  		for(j = 0; j < N/32; j++)
    			invntt_levels0t4_avx(tmp + 32*j, a + 32*j, new_zetas_inv + 31*j);
  		for(j = 0; j < N/32; j++)
    			invntt_levels5t7_avx(a + 4*j, tmp + 4*j, new_zetas_inv + 248);
		finish = __rdtsc();
		dif = finish - start;
		if (dif < mintime)
			mintime = dif;
		if (dif > maxtime)
			maxtime = dif;
	}

	printf("ndilithium_ntt_inv: time = [%lu : %lu]\n", mintime, maxtime);

}


void test_new_pointwise_acc()
{
	ALIGN64 uint32_t  a[L*N],b[L*N],c1 [N],c2 [N],s1 [N],s2 [N];
	uint32_t i, j, k;

	printf("\n\n====TESTING POINTWISE ACC====\n");

	for (i = 0; i < L; i++)
	{
		random_pol(a + i * N);
		random_pol(b + i * N);
	}

	mintime = 0xffffffff, maxtime = 0;
	for (k = 0; k < TESTS; k++)
	{
		start = __rdtsc();
		new_pointwise_acc_cpp_512(c2, a, b);
		finish = __rdtsc();
		dif = finish - start;
		if (dif < mintime)
			mintime = dif;
		if (dif > maxtime)
			maxtime = dif;
	}

	printf("new_pointwise_acc_cpp_512: time = [%lu : %lu]\n", mintime, maxtime);
		
	mintime = 0xffffffff, maxtime = 0;
	for (k = 0; k < TESTS; k++)
	{
		start = __rdtsc();
		new_pointwise_acc_asm_512(c2, a, b);
		finish = __rdtsc();
		dif = finish - start;
		if (dif < mintime)
			mintime = dif;
		if (dif > maxtime)
			maxtime = dif;
	}

	printf("new_pointwise_acc_asm_512 : time = [%lu : %lu]\n", mintime, maxtime);

	mintime = 0xffffffff, maxtime = 0;
	for (k = 0; k < TESTS; k++)
	{
		start = __rdtsc();
		pointwise_acc_avx(c2, a, b);
		finish = __rdtsc();
		dif = finish - start;
		if (dif < mintime)
			mintime = dif;
		if (dif > maxtime)
			maxtime = dif;
	}

	printf("dilithium_pointwise_acc_avx: time = [%lu : %lu]\n", mintime, maxtime);
}

int main(void) {
	set_const_512();
	test_ntt();
	test_pointwise();
	test_invntt();
	test_new_pointwise_acc();
	return 0;
}
