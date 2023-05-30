#ifndef PHASE_AMPL_CMPLX_SIN_TABLE_H
#define PHASE_AMPL_CMPLX_SIN_TABLE_H

#include <stdint.h>


//! Число значений комплексного синуса.
#define PHASE_AMPL_CMPLX_SIN_TABLE_SIZE 32

//! Таблица значений комплексного синуса.
//! Формат значений от младшего полуслова к старшему,
//! чётное слово - пара из действительных частей (R[n+1], R[n])
//! нечётное слово - пара из мнимых частей (I[n+1], I[n])
__attribute__((aligned(4)))
static const int32_t phase_ampl_cmplx_sin_table[PHASE_AMPL_CMPLX_SIN_TABLE_SIZE] = {
    0x18f90000, 0x7d8a7fff, 0x471d30fc, 0x6a6e7642, 0x6a6e5a82, 0x471d5a82, 0x7d8a7642, 0x18f930fc,
    0x7d8a7fff, 0xe7070000, 0x6a6e7642, 0xb8e3cf04, 0x471d5a82, 0x9592a57e, 0x18f930fc, 0x827689be,
    0xe7070000, 0x82768000, 0xb8e3cf04, 0x959289be, 0x9592a57e, 0xb8e3a57e, 0x827689be, 0xe707cf04,
    0x82768000, 0x18f90000, 0x959289be, 0x471d30fc, 0xb8e3a57e, 0x6a6e5a82, 0xe707cf04, 0x7d8a7642
};

#endif // PHASE_AMPL_CMPLX_SIN_TABLE_H
