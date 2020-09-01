#ifndef _const_h
#define _const_h
#include <stdint.h>
#include "parameters.h"
#include "align64.h"
extern uint32_t _8xqinv[];
extern uint32_t _8xq[];
extern uint32_t _8xqinv_512[];
extern uint32_t _8xq_512[];
extern uint32_t _8xq_1[8];
extern uint32_t _8x256q[];
extern uint32_t _8x256q_512[];
extern uint32_t _8x2q[];
extern uint32_t _8x2q_512[];
extern const uint32_t	_8x_one_shl_D[];
extern const uint32_t	_8x_one_shl_D_1[];
extern const uint32_t	_8x_one_shl_D_1_plus_1[];
extern const uint32_t	_8x_one_shl_D_1_minus_1[];

extern uint32_t _8x_7FFFFF[];

extern uint64_t _f;
extern uint32_t _mask[];
extern uint32_t __mask[];
extern const uint32_t zetas[];
extern const uint32_t zetas_[];
extern const uint32_t	zetas_inv[];
extern const uint32_t	zetas_inv_[];
extern const uint32_t new_zetas_inv[];
extern const uint32_t _8xdiv[];
extern const uint32_t _8xdiv_512[];

// 512
extern const uint32_t _16xFFFFFFFF[];
extern const uint64_t _8xFFFFFFFFFFFFFFFF[];

#ifdef _TEST_VECTORS
extern int32_t write_rand_count;
#endif

#endif