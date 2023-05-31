#ifndef PHASE_AMPL_CMPLX_SIN_TABLE_H
#define PHASE_AMPL_CMPLX_SIN_TABLE_H

#include <stdint.h>


//! Число бит дробной части значений комплексного синуса.
#define PHASE_AMPL_CMPLX_SIN_TABLE_FRACT_BITS 14

//! Число значений комплексного синуса.
#define PHASE_AMPL_CMPLX_SIN_TABLE_SIZE 32

//! Таблица значений комплексного синуса.
//! Формат значений от младшего полуслова к старшему,
//! чётное слово - пара из действительных частей (R[n+1], R[n])
//! нечётное слово - пара из мнимых частей (I[n+1], I[n])
__attribute__((aligned(4)))
static const int32_t phase_ampl_cmplx_sin_table[PHASE_AMPL_CMPLX_SIN_TABLE_SIZE] = {
    0x003d0000, 0x01340000, 0x05fa01dc, 0x08f2047d, 0x17980d39, 0x0fc40d39, 0x3268246a, 0x0a070f15,
    0x4ad73fd9, 0xf11d0000, 0x52955190, 0xc8d2de37, 0x40f74d12, 0x9ec5b2ee, 0x18ac2f02, 0x83f68e84,
    0xe7540000, 0x83f6804e, 0xbf09d0fe, 0x9ec58e84, 0xad6bb2ee, 0xc8d2b2ee, 0xb529ae70, 0xf11dde37,
    0xcd98c027, 0x0a070000, 0xe868db96, 0x0fc40f15, 0xfa06f2c7, 0x08f20d39, 0xffc3fe24, 0x0134047d
};

#endif // PHASE_AMPL_CMPLX_SIN_TABLE_H
