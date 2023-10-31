#ifndef PHASE_AMPL_CMPLX_SIN_TABLE_H
#define PHASE_AMPL_CMPLX_SIN_TABLE_H

#include <stdint.h>


//! Число бит дробной части значений комплексного синуса.
#define PHASE_AMPL_CMPLX_SIN_TABLE_FRACT_BITS 14

//! Число значений комплексного синуса.
#define PHASE_AMPL_CMPLX_SIN_TABLE_SIZE 64

//! Таблица значений комплексного синуса.
//! Формат значений от младшего полуслова к старшему,
//! чётное слово - пара из действительных частей (R[n+1], R[n])
//! нечётное слово - пара из мнимых частей (I[n+1], I[n])
__attribute__((aligned(4)))
static const int32_t phase_ampl_cmplx_sin_table[PHASE_AMPL_CMPLX_SIN_TABLE_SIZE] = {
    0x00080000, 0x004e0000, 0x00cc003d, 0x02a20134, 0x038e01dc, 0x06a6047d, 0x093205fa, 0x0b3408f2,
    0x120b0d39, 0x0ecf0d39, 0x1dc41798, 0x0fe90fc4, 0x2b5d246a, 0x0d270f15, 0x39503268, 0x05a50a07,
    0x45c53fd9, 0xf9210000, 0x4ed64ad7, 0xe816f11d, 0x52da5190, 0xd3b7de37, 0x50ab5295, 0xbdcdc8d2,
    0x47d14d12, 0xa87eb2ee, 0x38a440f7, 0x96089ec5, 0x24452f02, 0x886f8e84, 0x0c7d18ac, 0x813983f6,
    0xf3830000, 0x8139804e, 0xdbbbe754, 0x886f83f6, 0xc75cd0fe, 0x96088e84, 0xb82fbf09, 0xa87e9ec5,
    0xaf55b2ee, 0xbdcdb2ee, 0xad26ad6b, 0xd3b7c8d2, 0xb12aae70, 0xe816de37, 0xba3bb529, 0xf921f11d,
    0xc6b0c027, 0x05a50000, 0xd4a3cd98, 0x0d270a07, 0xe23cdb96, 0x0fe90f15, 0xedf5e868, 0x0ecf0fc4,
    0xf6cef2c7, 0x0b340d39, 0xfc72fa06, 0x06a608f2, 0xff34fe24, 0x02a2047d, 0xfff8ffc3, 0x004e0134
};

#endif // PHASE_AMPL_CMPLX_SIN_TABLE_H
