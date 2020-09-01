#ifndef NTT_H
#define NTT_H


#include <stdint.h>
#include "const.h"


void set_const_512();
void new_pointwise_acc_cpp_512(uint32_t c[], uint32_t a[], uint32_t b[]);
void new_pointwise_acc_asm_512(uint32_t c[], uint32_t a[], uint32_t b[]);
void new_ntt_512_cpp_(uint32_t* dest, uint32_t* src,const uint32_t* z);
void new_ntt_512_asm__(uint32_t* dest, uint32_t* src,const uint32_t* z);
void new_ntt_inv_512_cpp(uint32_t dest[N], uint32_t src[N], const uint32_t *zetas_inv);
void new_pointwise_mul_512_cpp(uint32_t* c, const uint32_t* a, const uint32_t* b);
void pointwise_avx(uint32_t* c, const uint32_t* a, const uint32_t* b);
void ntt_levels0t2_avx(uint64_t* dest, uint32_t* src,const uint32_t* z);
void ntt_levels3t8_avx(uint32_t* dest, uint64_t* src,const uint32_t* z);
void invntt_levels0t4_avx(uint64_t* dest, uint32_t* src,const uint32_t* z);
void invntt_levels5t7_avx(uint32_t* dest, uint64_t* src,const uint32_t* z);
void pointwise_acc_avx(uint32_t c[], uint32_t a[], uint32_t b[]);

#endif
