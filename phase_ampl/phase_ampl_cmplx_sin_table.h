#ifndef PHASE_AMPL_CMPLX_SIN_TABLE_H
#define PHASE_AMPL_CMPLX_SIN_TABLE_H

#include <stdint.h>


//! Число бит дробной части значений комплексного синуса.
#define PHASE_AMPL_CMPLX_SIN_TABLE_FRACT_BITS 14

//! Число значений комплексного синуса.
#define PHASE_AMPL_CMPLX_SIN_TABLE_SIZE 72

//! Таблица значений комплексного синуса.
//! Формат значений от младшего полуслова к старшему,
//! чётное слово - пара из действительных частей (R[n+1], R[n])
//! нечётное слово - пара из мнимых частей (I[n+1], I[n])
__attribute__((aligned(4)))
static const int32_t phase_ampl_cmplx_sin_table[PHASE_AMPL_CMPLX_SIN_TABLE_SIZE] = {
    0x00050000, 0x003e0000, 0x0090002b, 0x021a00f5, 0x02870151, 0x056c039e, 0x069f0447, 0x09750768,
    0x0d39099a, 0x0d390b71, 0x164d1179, 0x0f9e0ea9, 0x21691ba6, 0x0f940ff6, 0x2db6277a, 0x0c400e5e,
    0x3a1033f6, 0x05140929, 0x45263fd9, 0xf9f30000, 0x4da349cc, 0xeb33f2fd, 0x52525085, 0xd99de2b2,
    0x524d52f1, 0xc65fd01d, 0x4d12505a, 0xb2eebc94, 0x429f487b, 0xa0dba99f, 0x33703b92, 0x91b098d2,
    0x207d2a5c, 0x86c18b9f, 0x0b1c1602, 0x81088333, 0xf4e40000, 0x8108804e, 0xdf83e9fe, 0x86c18333,
    0xcc90d5a4, 0x91b08b9f, 0xbd61c46e, 0xa0db98d2, 0xb2eeb785, 0xb2eea99f, 0xadb3afa6, 0xc65fbc94,
    0xadaead0f, 0xd99dd01d, 0xb25daf7b, 0xeb33e2b2, 0xbadab634, 0xf9f3f2fd, 0xc5f0c027, 0x05140000,
    0xd24acc0a, 0x0c400929, 0xde97d886, 0x0f940e5e, 0xe9b3e45a, 0x0f9e0ff6, 0xf2c7ee87, 0x0d390ea9,
    0xf961f666, 0x09750b71, 0xfd79fbb9, 0x056c0768, 0xff70feaf, 0x021a039e, 0xfffbffd5, 0x003e00f5
};

#endif // PHASE_AMPL_CMPLX_SIN_TABLE_H
