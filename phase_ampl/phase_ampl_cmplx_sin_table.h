#ifndef PHASE_AMPL_CMPLX_SIN_TABLE_H
#define PHASE_AMPL_CMPLX_SIN_TABLE_H

#include <stdint.h>


//! Число бит дробной части значений комплексного синуса.
#define PHASE_AMPL_CMPLX_SIN_TABLE_FRACT_BITS 14

//! Число значений комплексного синуса.
#define PHASE_AMPL_CMPLX_SIN_TABLE_SIZE 60

//! Таблица значений комплексного синуса.
//! Формат значений от младшего полуслова к старшему,
//! чётное слово - пара из действительных частей (R[n+1], R[n])
//! нечётное слово - пара из мнимых частей (I[n+1], I[n])
__attribute__((aligned(4)))
static const int32_t phase_ampl_cmplx_sin_table[PHASE_AMPL_CMPLX_SIN_TABLE_SIZE] = {
    0x00090000, 0x00590000, 0x00f7004a, 0x02f9015d, 0x0447023f, 0x0768050b, 0x0af9072b, 0x0c3009dd,
    0x154b0fb3, 0x0f780e23, 0x229b1ba6, 0x0f680ff6, 0x317829f5, 0x0a840da2, 0x3fd938dc, 0x000005fa,
    0x4b704623, 0xeff7f8a1, 0x520d4f7d, 0xdb78e62c, 0x520452f1, 0xc469d01d, 0x4a794f33, 0xad4ab8b1,
    0x3b9243e4, 0x98d2a28e, 0x267f31b2, 0x89869063, 0x0d501a42, 0x815a8475, 0xf2b00000, 0x815a804e,
    0xd981e5be, 0x89868475, 0xc46ece4e, 0x98d29063, 0xb587bc1c, 0xad4aa28e, 0xadfcb0cd, 0xc469b8b1,
    0xadf3ad0f, 0xdb78d01d, 0xb490b083, 0xeff7e62c, 0xc027b9dd, 0x0000f8a1, 0xce88c724, 0x0a8405fa,
    0xdd65d60b, 0x0f680da2, 0xeab5e45a, 0x0f780ff6, 0xf507f04d, 0x0c300e23, 0xfbb9f8d5, 0x076809dd,
    0xff09fdc1, 0x02f9050b, 0xfff7ffb6, 0x0059015d, 
};

#endif // PHASE_AMPL_CMPLX_SIN_TABLE_H
