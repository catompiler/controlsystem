#ifndef IQ24_TAN_TABLE_H
#define IQ24_TAN_TABLE_H

#include <stdint.h>


//! Коэффициент деформации (0.607252935).
#define IQ24_CORDIC_GAIN 0x009b74ee

//! Угол 0 градусов.
#define IQ24_CORDIC_ANGLE_PU_0 0x00000000
//! Угол 90 градусов.
#define IQ24_CORDIC_ANGLE_PU_90 0x00400000
//! Угол 180 градусов.
#define IQ24_CORDIC_ANGLE_PU_180 0x00800000
//! Угол 270 градусов.
#define IQ24_CORDIC_ANGLE_PU_270 0x00c00000
//! Угол 360 градусов.
#define IQ24_CORDIC_ANGLE_PU_360 0x01000000

//! Число значений в таблице тангенсов.
#define IQ24_CORDIC_TAN_TABLE_SIZE 24

//! Таблица значений тангенсов.
static const int32_t iq24_cordic_tan_table[IQ24_CORDIC_TAN_TABLE_SIZE] = {
    0x00200000, 0x0012e405, 0x0009fb38, 0x00051112, 0x00028b0d, 0x000145d8, 0x0000a2f6, 0x0000517c,
    0x000028be, 0x0000145f, 0x00000a30, 0x00000518, 0x0000028c, 0x00000146, 0x000000a3, 0x00000051,
    0x00000029, 0x00000014, 0x0000000a, 0x00000005, 0x00000003, 0x00000001, 0x00000001, 0x00000000
};

#endif // IQ24_TAN_TABLE_H
