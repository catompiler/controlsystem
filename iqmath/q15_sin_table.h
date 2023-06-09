#ifndef Q15_SIN_TABLE_H
#define Q15_SIN_TABLE_H

#include <stdint.h>


//! Число значений в таблице синуса.
#define Q15_SIN_TABLE_SIZE 128

//! Таблица значений синуса.
__attribute__((aligned(4)))
static const int16_t q15_sin_table[Q15_SIN_TABLE_SIZE] = {
    0x0000, 0x0648, 0x0c8c, 0x12c8, 0x18f9, 0x1f1a, 0x2528, 0x2b1f,
    0x30fc, 0x36ba, 0x3c57, 0x41ce, 0x471d, 0x4c40, 0x5134, 0x55f6,
    0x5a82, 0x5ed7, 0x62f2, 0x66d0, 0x6a6e, 0x6dca, 0x70e3, 0x73b6,
    0x7642, 0x7885, 0x7a7d, 0x7c2a, 0x7d8a, 0x7e9d, 0x7f62, 0x7fd9,
    0x7fff, 0x7fd9, 0x7f62, 0x7e9d, 0x7d8a, 0x7c2a, 0x7a7d, 0x7885,
    0x7642, 0x73b6, 0x70e3, 0x6dca, 0x6a6e, 0x66d0, 0x62f2, 0x5ed7,
    0x5a82, 0x55f6, 0x5134, 0x4c40, 0x471d, 0x41ce, 0x3c57, 0x36ba,
    0x30fc, 0x2b1f, 0x2528, 0x1f1a, 0x18f9, 0x12c8, 0x0c8c, 0x0648,
    0x0000, 0xf9b8, 0xf374, 0xed38, 0xe707, 0xe0e6, 0xdad8, 0xd4e1,
    0xcf04, 0xc946, 0xc3a9, 0xbe32, 0xb8e3, 0xb3c0, 0xaecc, 0xaa0a,
    0xa57e, 0xa129, 0x9d0e, 0x9930, 0x9592, 0x9236, 0x8f1d, 0x8c4a,
    0x89be, 0x877b, 0x8583, 0x83d6, 0x8276, 0x8163, 0x809e, 0x8027,
    0x8000, 0x8027, 0x809e, 0x8163, 0x8276, 0x83d6, 0x8583, 0x877b,
    0x89be, 0x8c4a, 0x8f1d, 0x9236, 0x9592, 0x9930, 0x9d0e, 0xa129,
    0xa57e, 0xaa0a, 0xaecc, 0xb3c0, 0xb8e3, 0xbe32, 0xc3a9, 0xc946,
    0xcf04, 0xd4e1, 0xdad8, 0xe0e6, 0xe707, 0xed38, 0xf374, 0xf9b8
};

#endif // Q15_SIN_TABLE_H
