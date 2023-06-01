/**
 * @file iq24_cordic.h
 * Библиотека для вычисления тригонометрических функций алгоритмом CORDIC,
 * используя числа с фиксированной запятой.
 */
#ifndef IQ24_CORDIC_H
#define	IQ24_CORDIC_H

#include <stdint.h>
#include <stddef.h>
#include "iq24.h"
#include "iq24_math.h"
#include "defs/defs.h"


/**
 * Вычисляет угол и радиус от значений X и Y.
 * Угол в периодических единицах.
 * @param x Координата X.
 * @param y Координата Y.
 * @param angle Результат - угол, может быть передан NULL.
 * @param hyp Результат - радиус, может быть передан NULL.
 */
EXTERN void iq24_cordic_atan2_hyp_pu(iq24_t x, iq24_t y, iq24_t* angle, iq24_t* hyp);

/**
 * Вычисляет угол и радиус от значений X и Y.
 * Угол в радианах.
 * @param x Координата X.
 * @param y Координата Y.
 * @param angle Результат - угол, может быть передан NULL.
 * @param hyp Результат - радиус, может быть передан NULL.
 */
ALWAYS_INLINE static void iq24_cordic_atan2_hyp(iq24_t x, iq24_t y, iq24_t* angle, iq24_t* hyp)
{
    iq24_cordic_atan2_hyp_pu(x, y, angle, hyp);
    // Приведение угла в периодических единицах в радианы.
    if(angle) { *angle = iq24_pu_to_rads(*angle); }
}

/**
 * Вычисляет синус и косинус угла.
 * Угол в периодических единицах.
 * @param angle Угол.
 * @param sin Результат: синус угла, может быть передан NULL.
 * @param cos Результат: косинус угла, может быть передан NULL.
 */
EXTERN void iq24_cordic_sincos_pu(iq24_t angle, iq24_t* sin, iq24_t* cos);

/**
 * Вычисляет синус и косинус угла.
 * Угол в радианах.
 * @param angle Угол.
 * @param sin Результат: синус угла, может быть передан NULL.
 * @param cos Результат: косинус угла, может быть передан NULL.
 */
ALWAYS_INLINE static void iq24_cordic_sincos(iq24_t angle, iq24_t* sin, iq24_t* cos)
{
    // Приведение угла в радианах в периодические единицы.
    iq24_t tmp = iq24_rads_to_pu(angle);
    iq24_cordic_sincos_pu(tmp, sin, cos);
}

#endif	/* CORDIC32_H */
