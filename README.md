# AVX512 NTT FOR DILITHIUM SIGNATURE SCHEME

Authors: O. Kachko, I. Gorbenko,M. Yesina,S. Kandiy

Digital signature Dilithium – the finalist of the 2nd round of the NIST competition of post-quantum cryptographic algorithms (https://csrc.nist.gov/Projects/post-quantum-cryptography/round-3-submissions)
Special attention in optimization is paid to the operation of polynomials multiplication. To multiply polynomials, it is necessary to perform the following functions:
- Direct NTT transformation;
- Component-wise multiplication;
- Inverse NTT transformation.

The authors of Dilithium used AVX-2 operations and assembler language to implement these functions. We used AVX-512 operations and C language.
The use of C allows the same code to be used in processors with different architectures and different operating systems. The results of our implementation for:
- Processor Intel (R) Core (TM) i9-7960X CPU @ 2.80GHz, 2808 MHz cores, 16 logical processors: 32.
- System (Windows 10), Microsoft Visual Studio Community 2019, Version 16.6.2, VisualStudio.16.Release / 16.6.2 + 30204.135, / o2 optimization flags
- System (Linux), GCC 9.3, optimization flags: -O3 –march = native, -mtune = native

| Function  | Linux, Dilithium (lang asm, GCC)|Linux(lang С, GCC) |Windows 10, (lang С, msvc) |Speedup Linux |Speedup Windows |
| ------------- | ------------- |------------- |------------- |------------- |------------- |
| Direct NTT transformation | 987  |663  |727 |1.48  |1.35  |
| Component-wise multiplication | 135  |81  |87  |1.6 |1.51  |
| Inverse NTT | 972  |677  |741  |1.43 |1.31  |
