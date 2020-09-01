#include <stdint.h>
#include <stdio.h>
#include <intrin.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



#include "align64.h"
#include "cpucycles.h"
#include "parameters.h"

#define TESTS	10000

uint64_t start, dif, finish, mintime = 0xffffffff, maxtime = 0;
extern uint64_t _f;

extern const uint32_t new_zetas[];
extern const uint32_t new_zetas_inv[N];



void set_const_512();
void new_pointwise_mul_512_cpp(uint32_t* c, const uint32_t* a, const uint32_t* b);
void new_ntt_512_cpp_(uint32_t* dest, uint32_t* src, uint32_t* z);
void new_pointwise_acc_cpp_512(uint32_t c[], uint32_t a[], uint32_t b[]);
void new_pointwise_acc_asm_512(uint32_t c[], uint32_t a[], uint32_t b[]);
void new_ntt_inv_512_cpp(uint32_t dest[N], uint32_t src[N], const uint32_t* zetas_inv);


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
	printf("\n\n\n====TEST NTT====\n");

	ALIGN64 uint32_t a[N], c1[N], c2[N];
	uint32_t i, j, k;
	
	ALIGN64 uint64_t tmp[N];
	random_pol(a);

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

	printf("new_ntt_512_cpp_: time = [%I64d : %I64d]\n", mintime, maxtime);

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

	printf("new_ntt_512_asm__: time = [%I64d : %I64d]\n", mintime, maxtime);

}

void test_pointwise()
{
	printf("\n\n\n====TEST POINTWISE====\n");

	ALIGN64 uint32_t a[N], b[N], c1[N], c2[N], i, j;
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

	printf("new_pointwise_mul_512_cpp: time = [%I64d : %I64d]\n", mintime, maxtime);

}
void test_invntt()
{
	printf("\n\n\n====TEST INV NTT====\n");
	
	ALIGN64 uint32_t a[N], c1[N], c2[N], i, j;
	
	random_pol(a);

	ALIGN64 uint64_t temp1[N], temp2 [N];

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

	printf("new_ntt_inv_512_cpp: time = [%I64d : %I64d]\n", mintime, maxtime);

}


void test_new_pointwise_acc()
{
	printf("\n\n\n====TEST POINTWISE ACC====\n");

	ALIGN64 uint32_t a[L*N], b[L*N], c1 [N], c2 [N], s1 [N], s2 [N];
	uint32_t i, j, k;

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

	printf("new_pointwise_acc_cpp_512 time = [%I64d..%I64d]\n", mintime, maxtime);

	
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

	printf("new_pointwise_acc_asm_512 time = [%I64d..%I64d]\n",mintime, maxtime);
}

int main(void) {
	set_const_512();
	test_ntt();
	test_pointwise();
	test_invntt();
	test_new_pointwise_acc();
	return 0;
}