#ifndef __parameters_h
#define __parameters_h
#define MODE	3

//#define MODE	5

#define OID	"\x00\x00\x01"
#define BITS_IN_BYTE	8

#define LAMBDA  256
#define ROOT_OF_UNITY 1753U
#define ROOT_OF_INVERSE_UNITY 731434U
#define SEEDBYTES	LAMBDA / BITS_IN_BYTE 
#if LAMBDA == 256


#define N			256
#define Q_ 8380417
#define Q_1 (Q_ - 1)
#define Q_2 (Q_1 / 2)

#define GAMMA1 (Q_1 / 16)
#define LOG2GAMMA1	19
#define LOG2_2GAMMA1	20
#define GAMMA2 (GAMMA1 / 2)
#define ALPHA	(2 * GAMMA2)
#define MONT 4193792U // 2^32 % Q
#define QINV 4236238847U // -q^(-1) mod 2^32
#define ROOT 25847
#define		K_ROOT	32736

#define LOG2Q		23
#define	D_DEF		14


#define HASHBYTES		64




#if MODE == 0
#define K	3
#define L	2
#define NJU	7
#define LOG2_2NJU	4
#define BETA	375
#define OMEGA	64

#elif MODE == 1
#define K	4
#define L	3
#define NJU	6
#define LOG2_2NJU	4
#define BETA	325
#define OMEGA	80

#elif MODE == 2
#define K	5
#define L	4
#define NJU	5
#define LOG2_2NJU	4
#define BETA	275
#define OMEGA	96

#elif MODE == 3
#define K	6
#define L	5
#define NJU	3
#define LOG2_2NJU	3
#define BETA	175
#define OMEGA	120

#elif MODE == 4
#define K	9
#define L	8

#define NJU	3
#define LOG2_2NJU	3
#define BETA	175
#define OMEGA	120
#elif MODE == 5
#define K	9
#define L	8
#define NJU	2
#define LOG2_2NJU	2
#define BETA	115
#define OMEGA	140
#else
#error Bad mode
#endif

#define NJUQ	(NJU - Q_)





#define POLWHIGH_SIZE_PACKED ((N*4)/BITS_IN_BYTE)
#define PKBYTES (SEEDBYTES + K * (LOG2Q - D_DEF) * N / BITS_IN_BYTE)

#define SKBYTES (2 * SEEDBYTES + HASHBYTES + N * ((L + K) * LOG2_2NJU + K * D_DEF)  / BITS_IN_BYTE)

#define LOG2Z	20	

#define DSBYTES ((LOG2Z * 256 * L) / 8 + (OMEGA + K)+ 40)
#define CRYPTOBYTES DSBYTES

#define SHAKE256_RATE 136







#endif
#endif
