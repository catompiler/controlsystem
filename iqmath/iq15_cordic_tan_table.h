#ifndef IQ15_TAN_TABLE_H
#define IQ15_TAN_TABLE_H

#include <stdint.h>


//! Коэффициент деформации (0.607252935).
#define IQ15_CORDIC_GAIN 0x00004dba

//! Угол 0 градусов.
#define IQ15_CORDIC_ANGLE_PU_0 0x00000000
//! Угол 90 градусов.
#define IQ15_CORDIC_ANGLE_PU_90 0x00002000
//! Угол 180 градусов.
#define IQ15_CORDIC_ANGLE_PU_180 0x00004000
//! Угол 270 градусов.
#define IQ15_CORDIC_ANGLE_PU_270 0x00006000
//! Угол 360 градусов.
#define IQ15_CORDIC_ANGLE_PU_360 0x00008000

//! Число значений в таблице тангенсов.
#define IQ15_CORDIC_TAN_TABLE_SIZE 15

//! Таблица значений тангенсов.
static const int32_t iq15_cordic_tan_table[IQ15_CORDIC_TAN_TABLE_SIZE] = {
    0x00001000, 0x00000972, 0x000004fe, 0x00000289, 0x00000146, 0x000000a3, 0x00000051, 0x00000029,
    0x00000014, 0x0000000a, 0x00000005, 0x00000003, 0x00000001, 0x00000001, 0x00000000
};

#endif // IQ15_TAN_TABLE_H
