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

The table shows the results of measuring the number of cycles for each function. The rdtsc processor command or the corresponding function was used to measure the number of cycles.
The second column of the table shows the results for the author's implementation (Dilithium developers), which were obtained using the keys of the GCC compiler, which were used by the authors (Linux).
The third column shows the results of our implementation for the same GCC compiler keys that were used to obtain the previous results (Linux)
The fourth column shows the results of our implementation using the msvc compiler
The following columns show the acceleration for our implementation in relation to the author's implementation.
Conclusions:
1 Due to the use of 512-bit operations and special mixing algorithms, acceleration is achieved regardless of platforms
2 Using the C language instead of the assembler language allows to use cross-platform code
As an auxiliary result, our experiments showed that the use of assembler language instead of C does not allow to obtain sufficient speedup, if compilation modes with full optimization are selected

# РЕАЛІЗАЦІЯ NTT ДЛЯ СХЕМИ ЦИФРОВОГО ПІДПИСУ DILITHIUM З ВИКОРИСТАННЯМ AVX512

Цифровий підпис Dilithium – фіналіст 2 раунду конкурсу NIST постквантових криптографічних алгоритмів( https://csrc.nist.gov/Projects/post-quantum-cryptography/round-3-submissions)
Особлива увага при оптимізації наділяється операції множення поліномів. 
Для множення поліномів необхідно виконати наступні функції:
Пряме NTT перетворення;
По компонентне множення;
Зворотне NTT перетворення
Автори Dilithium для реалізації цих функцій застосовували AVX-2 операції та  мову асемблер.
Ми застосовували AVX-512 операції та мову C.
Застосування мови С дозволяє використовувати один і той же код для застосування в процесорах з різною архітектурою та для різних операційних систем.
Результати нашої реалізації наведені в таблиці для процесору  Intel (R) Core (TM) i9-7960X CPU @ 2.80GHz, 2808 MHz cores, 16 logical processors: 32.
Компиляторы:
 Microsoft Visual Studio Community 2019, Version 16.6.2, VisualStudio.16.Release / 16.6.2 + 30204.135, / o2 optimization flags
GCC 9.3, флаги оптимізації: -О3 –march=native,-mtune=native

| Function  | Linux, Dilithium (lang asm, GCC)|Linux(lang С, GCC) |Windows 10, (lang С, msvc) |Speedup Linux |Speedup Windows |
| ------------- | ------------- |------------- |------------- |------------- |------------- |
| Пряме Ntt перетворення | 987  |663  |727 |1.48  |1.35  |
| Покомпонентне множення | 135  |81  |87  |1.6 |1.51  |
| Зворотне Ntt перетворення | 972  |677  |741  |1.43 |1.31  |

В таблиці наведені результати виміру кількості тактів для кожної функції. Для виміру кількості тактів застосовувалась команда процесора rdtsc або відповідна функція.
В другій колонці таблиці наведені результати для авторської реалізації (розробники Dilithium), які отримані  з застосуванням ключів компілятора GCC, які застосовували автори (Linux).
В третій колонці наведені результати нашої реалізації для тих же ключів компілятору GCC, які застосовувалися для отримання попередніх результатів (Linux)
В четвертій колонці наведені результати нашої реалізації з застосуванням компілятору msvc
В наступних колонках наведено прискорення для нашої реалізації по відношенню до авторської реалізації.
Висновки:
1 За рахунок застосування 512 бітних операцій та спеціальних алгоритмів перемішування досягнуто суттєве прискорення незалежно від платформ
2 Застосування мови С замість мови асемблер дозволяє застосовувати крос платформений код
3 Як допоміжний результат наші експерименти показали, що застосування мови асемблер замість мови С не дозволяє отримати прискорення при умові обрання режимів компіляції з повною оптимізацією


