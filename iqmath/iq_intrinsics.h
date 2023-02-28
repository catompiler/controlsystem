#ifndef IQ_INTRINSICS_H
#define IQ_INTRINSICS_H

#include <stdint.h>
#include "iq_types.h"


//! Выполняет насыщение числа с фиксированной запятой
//! Q до разряда N.
#ifndef __SSAT
#ifdef __arm__
#define __SSAT(Q, N)\
    ({ register int32_t __RES, __Q = Q;\
    __asm__("ssat %0, %1, %2" : "=r"(__RES) : "I"(N), "r"(__Q));\
    __RES;})
#else
#define __SSAT(Q, N)\
    ({ register int32_t __RES, __Q = Q;\
       const int32_t __MAX = (int32_t)( (1U<<((N)-1))-1);\
       const int32_t __MIN = (int32_t)(-(1U<<((N)-1))  );\
    __RES = (__Q > __MAX) ? __MAX : ((__Q < __MIN) ? __MIN : __Q);\
    __RES;})
#endif
#endif //__SSAT

//! Выполняет насыщение числа с фиксированной запятой
//! Q до разряда N со сдвигом вправо на S разрядов.
#ifndef __SSAT_ASR
#ifdef __arm__
#define __SSAT_ASR(Q, N, S)\
    ({ register int32_t __RES, __Q = Q;\
    __asm__("ssat %0, %1, %2 ASR %3" : "=r"(__RES) : "I"(N), "r"(__Q), "I"(S));\
    __RES;})
#else
#define __SSAT_ASR(Q, N, S)\
    ({ register int32_t __RES, __QS = (Q) >> (S);\
    __RES = __SSAT(__QS, N);\
    __RES;})
#endif
#endif //__SSAT_ASR

//! Выполняет насыщение пары 16 битных чисел с фиксированной запятой
//! Q до разряда N.
#ifndef __SSAT16
#ifdef __arm__
#define __SSAT16(Q, N)\
    ({ register int32_t __RES, __Q = Q;\
    __asm__("ssat16 %0, %1, %2" : "=r"(__RES) : "I"(N), "r"(__Q));\
    __RES;})
#else
#define __SSAT16(Q, N)\
    ({ register int32_t __RES, __Q = Q;\
       register int32_t __QHI = (int16_t)((__Q >> 16) & 0xffff);\
       register int32_t __QLO = (int16_t)(__Q  & 0xffff);\
       const int32_t __MAX = (int32_t)( (1U<<((N)-1))-1);\
       const int32_t __MIN = (int32_t)(-(1U<<((N)-1))  );\
    __QHI = (__QHI > __MAX) ? __MAX : ((__QHI < __MIN) ? __MIN : __QHI);\
    __QLO = (__QLO > __MAX) ? __MAX : ((__QLO < __MIN) ? __MIN : __QLO);\
    __RES = ((__QHI & 0xffff) << 16) | (__QLO & 0xffff);\
    __RES;})
#endif
#endif //__SSAT16

//! Выполняет сложение чисел с фиксированной запятой
//! Q1 и Q2 и насыщает результат.
#ifndef __QADD
#ifdef __arm__
#define __QADD(Q1, Q2)\
    ({ register int32_t __RES, __Q1 = Q1, __Q2 = Q2;\
    __asm__("qadd %0, %1, %2" : "=r"(__RES) : "r"(__Q1), "r"(__Q2));\
    __RES;})
#else
#define __QADD(Q1, Q2)\
    ({ register int32_t __RES, __Q1 = Q1, __Q2 = Q2;\
    __RES = __Q1 + __Q2;\
    __RES = (__RES <= 0 && __Q1 > 0 && __Q2 > 0) ? INT32_MAX : __RES;\
    __RES = (__RES >= 0 && __Q1 < 0 && __Q2 < 0) ? INT32_MIN : __RES;\
    __RES;})
#endif
#endif //__QADD

//! Выполняет сложение пар 16 битных чисел с фиксированной запятой
//! Q1 и Q2 и насыщает результат.
#ifndef __QADD16
#ifdef __arm__
#define __QADD16(Q1, Q2)\
    ({ register int32_t __RES, __Q1 = Q1, __Q2 = Q2;\
    __asm__("qadd16 %0, %1, %2" : "=r"(__RES) : "r"(__Q1), "r"(__Q2));\
    __RES;})
#else
#define __QADD16(Q1, Q2)\
    ({ register int32_t __RES, __RESHI, __RESLO, __Q1 = Q1, __Q2 = Q2;\
       register int32_t __Q1HI = (int16_t)((__Q1 >> 16) & 0xffff);\
       register int32_t __Q1LO = (int16_t)(__Q1  & 0xffff);\
       register int32_t __Q2HI = (int16_t)((__Q2 >> 16) & 0xffff);\
       register int32_t __Q2LO = (int16_t)(__Q2  & 0xffff);\
    __RESHI = __Q1HI + __Q2HI;\
    __RESLO = __Q1LO + __Q2LO;\
    __RESHI = (__RESHI > INT16_MAX) ? INT16_MAX : __RESHI;\
    __RESHI = (__RESHI < INT16_MIN) ? INT16_MIN : __RESHI;\
    __RESLO = (__RESLO > INT16_MAX) ? INT16_MAX : __RESLO;\
    __RESLO = (__RESLO < INT16_MIN) ? INT16_MIN : __RESLO;\
    __RES = ((__RESHI & 0xffff) << 16) | (__RESLO & 0xffff);\
    __RES;})
#endif
#endif //__QADD16

//! Выполняет вычитание чисел с фиксированной запятой
//! Q1 и Q2 и насыщает результат.
#ifndef __QSUB
#ifdef __arm__
#define __QSUB(Q1, Q2)\
    ({ register int32_t __RES, __Q1 = Q1, __Q2 = Q2;\
    __asm__("qsub %0, %1, %2" : "=r"(__RES) : "r"(__Q1), "r"(__Q2));\
    __RES;})
#else
#define __QSUB(Q1, Q2)\
    ({ register int32_t __RES, __Q1 = Q1, __Q2 = Q2;\
    __RES = __Q1 - __Q2;\
    __RES = (__RES <= 0 && __Q1 > 0 && __Q2 < 0) ? INT32_MAX : __RES;\
    __RES = (__RES >= 0 && __Q1 < 0 && __Q2 > 0) ? INT32_MIN : __RES;\
    __RES;})
#endif
#endif //__QSUB

//! Выполняет вычитание пар 16 битных чисел с фиксированной запятой
//! Q1 и Q2 и насыщает результат.
#ifndef __QSUB16
#ifdef __arm__
#define __QSUB16(Q1, Q2)\
    ({ register int32_t __RES, __Q1 = Q1, __Q2 = Q2;\
    __asm__("qsub16 %0, %1, %2" : "=r"(__RES) : "r"(__Q1), "r"(__Q2));\
    __RES;})
#else
#define __QSUB16(Q1, Q2)\
    ({ register int32_t __RES, __RESHI, __RESLO, __Q1 = Q1, __Q2 = Q2;\
       register int32_t __Q1HI = (int16_t)((__Q1 >> 16) & 0xffff);\
       register int32_t __Q1LO = (int16_t)(__Q1  & 0xffff);\
       register int32_t __Q2HI = (int16_t)((__Q2 >> 16) & 0xffff);\
       register int32_t __Q2LO = (int16_t)(__Q2  & 0xffff);\
    __RESHI = __Q1HI - __Q2HI;\
    __RESLO = __Q1LO - __Q2LO;\
    __RESHI = (__RESHI > INT16_MAX) ? INT16_MAX : __RESHI;\
    __RESHI = (__RESHI < INT16_MIN) ? INT16_MIN : __RESHI;\
    __RESLO = (__RESLO > INT16_MAX) ? INT16_MAX : __RESLO;\
    __RESLO = (__RESLO < INT16_MIN) ? INT16_MIN : __RESLO;\
    __RES = ((__RESHI & 0xffff) << 16) | (__RESLO & 0xffff);\
    __RES;})
#endif
#endif //__QSUB16

//! Выполняет умножение чисел с фиксированной запятой
//! Q1 и Q2 и сложение их с аккумулятором A.
#ifndef __MLA
#ifdef __arm__
#define __MLA(Q1, Q2, A)\
    ({ register int32_t __RES, __Q1 = Q1, __Q2 = Q2, __A = A;\
    __asm__("mla %0, %1, %2, %3" : "=r"(__RES) : "r"(__Q1), "r"(__Q2), "r"(__A));\
    __RES;})
#else
#define __MLA(Q1, Q2, A)\
    ({ register int32_t __RES, __Q1 = Q1, __Q2 = Q2, __A = A;\
    __RES = __Q1 * __Q2 + __A;\
    __RES;})
#endif
#endif //__MLA

//! Выполняет умножение чисел с фиксированной запятой
//! Q1 и Q2 и сложение их с 64 битным аккумулятором A.
#ifndef __SMLAL
#ifdef __arm__
#define __SMLAL(Q1, Q2, A)\
    ({ union __U_MLAL_64 { int64_t _64;\
           struct _S_MLAL_64 {int32_t lo; int32_t hi;} _32; };\
       register union __U_MLAL_64 __u_mlal_64 = {A};\
       register int32_t __Q1 = Q1, __Q2 = Q2;\
    __asm__("smlal %0, %1, %2, %3" : "=r"(__u_mlal_64._32.lo), "=r"(__u_mlal_64._32.hi) :\
            "r"(__Q1), "r"(__Q2), "0"(__u_mlal_64._32.lo), "1"(__u_mlal_64._32.hi));\
    (__u_mlal_64._64);})
#else
#define __SMLAL(Q1, Q2, A)\
    ({ register int32_t __Q1 = Q1, __Q2 = Q2;\
       register int64_t __RES, __A = A;\
    __RES = (int64_t)__Q1 * __Q2 + __A;\
    __RES;})
#endif
#endif //__SMLAL


#endif /* IQ_INTRINSICS_H */
