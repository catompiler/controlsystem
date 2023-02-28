/**
 * @file iq15_cordic.h
 * Библиотека для вычисления тригонометрических функций алгоритмом CORDIC,
 * используя числа с фиксированной запятой.
 */
#ifndef IQ15_CORDIC_H
#define	IQ15_CORDIC_H

#include <stdint.h>
#include <stddef.h>
#include "iq15.h"
#include "defs/defs.h"


/**
 * Вычисляет угол и радиус от значений X и Y.
 * Угол в периодических единицах.
 * @param x Координата X.
 * @param y Координата Y.
 * @param angle Результат - угол, может быть передан NULL.
 * @param hyp Результат - радиус, может быть передан NULL.
 */
EXTERN void iq15_cordic_atan2_hyp_pu(iq15_t x, iq15_t y, iq15_t* angle, iq15_t* hyp);

/**
 * Вычисляет угол и радиус от значений X и Y.
 * Угол в радианах.
 * @param x Координата X.
 * @param y Координата Y.
 * @param angle Результат - угол, может быть передан NULL.
 * @param hyp Результат - радиус, может быть передан NULL.
 */
ALWAYS_INLINE static void iq15_cordic_atan2_hyp(iq15_t x, iq15_t y, iq15_t* angle, iq15_t* hyp)
{
    iq15_cordic_atan2_hyp_pu(x, y, angle, hyp);
    // Приведение угла в периодических единицах в радианы.
    // angle = angle * 2*pi.
    if(angle) { *angle = iq15_mull(*angle, 205887); }
}

/**
 * Вычисляет синус и косинус угла.
 * Угол в периодических единицах.
 * @param angle Угол.
 * @param sin Результат: синус угла, может быть передан NULL.
 * @param cos Результат: косинус угла, может быть передан NULL.
 */
EXTERN void iq15_cordic_sincos_pu(iq15_t angle, iq15_t* sin, iq15_t* cos);

/**
 * Вычисляет синус и косинус угла.
 * Угол в радианах.
 * @param angle Угол.
 * @param sin Результат: синус угла, может быть передан NULL.
 * @param cos Результат: косинус угла, может быть передан NULL.
 */
ALWAYS_INLINE static void iq15_cordic_sincos(iq15_t angle, iq15_t* sin, iq15_t* cos)
{
    // Приведение угла в радианах в периодические единицы.
    // tmp = angle / (2*pi).
    iq15_t tmp = iq15_mul(angle, 5215);
    iq15_cordic_sincos_pu(tmp, sin, cos);
}

#endif	/* CORDIC32_H */
