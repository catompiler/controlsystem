#ifndef IQ15_MATH_H
#define IQ15_MATH_H

#include "iq15.h"
#include "iq15_cordic.h"
#include "defs/defs.h"
#include <stddef.h>


//! Константа sqrt(2) в формате IQ15.
#define IQ15_SQRT2 (0xB505)

//! Константа 1/sqrt(2) в формате IQ15.
#define IQ15_INV_SQRT2 (0x5A82)

//! Константа Е в формате IQ15.
#define IQ15_E (0xADF8)

//! Константа PI в формате IQ15.
#define IQ15_PI (0x1921F)

//! Константа 2*PI в формате IQ15.
#define IQ15_2PI (0x3243F)

//! Константа PI/2 в формате IQ15.
#define IQ15_PI2 (0xC90F)

//! Константа PI/4 в формате IQ15.
#define IQ15_PI4 (0x6487)

//! Угол PI в относительных единицах в формате IQ15.
#define IQ15_PI_PU (0x4000)

//! Угол 2*PI в относительных единицах в формате IQ15.
#define IQ15_2PI_PU (0x8000)

//! Угол PI/2 в относительных единицах в формате IQ15.
#define IQ15_PI2_PU (0x2000)

//! Угол PI/4 в относительных единицах в формате IQ15.
#define IQ15_PI4_PU (0x1000)


/**
 * Округляет вниз число с фиксированной запятой.
 * @param q Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_floor(iq15_t q)
{
    iq15_t res = IQN_FLOOR(q, IQ15_FRACT_BITS, IQ15_MASK_TYPE);

    return res;
}

/**
 * Округляет вверх число с фиксированной запятой.
 * @param q Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_ceil(iq15_t q)
{
    iq15_t res = IQN_CEIL(q, IQ15_FRACT_BITS, IQ15_TYPE, IQ15_MASK_TYPE);

    return res;
}

/**
 * Округляет число с фиксированной запятой.
 * @param q Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_round(iq15_t q)
{
    iq15_t res = IQN_ROUND(q, IQ15_FRACT_BITS, IQ15_TYPE, IQ15_MASK_TYPE);

    return res;
}

/**
 * Функция sin.
 * Аргумент в циклических единицах.
 * @param angle Угол.
 * @return Значение.
 */
EXTERN iq15_t iq15_sin_pu(iq15_t angle);

/**
 * Функция cos.
 * Аргумент в циклических единицах.
 * Работает через синус, т.к.
 * cos(a) = sin(pi/2 - a).
 * @param angle Угол.
 * @return Значение.
 */
ALWAYS_INLINE static iq15_t iq15_cos_pu(iq15_t angle)
{
    return iq15_sin_pu((iq15_t)0x2000 - angle);
}

/**
 * Функция sin.
 * Аргумент в радианах.
 * @param angle Угол.
 * @return Значение.
 */
ALWAYS_INLINE static iq15_t iq15_sin(iq15_t angle)
{
    // Приведение угла в радианах в цикличные единицы.
    // tmp = angle / (2*pi).
    iq15_t tmp = iq15_mul(angle, 5215);
    return iq15_sin_pu(tmp);
}

/**
 * Функция sin.
 * Аргумент в радианах.
 * Работает через синус, т.к.
 * cos(a) = sin(pi/2 - a).
 * @param angle Угол.
 * @return Значение.
 */
ALWAYS_INLINE static iq15_t iq15_cos(iq15_t angle)
{
    // Приведение угла в радианах в цикличные единицы.
    // tmp = angle / (2*pi).
    iq15_t tmp = iq15_mul(angle, 5215);
    return iq15_cos_pu(tmp);
}

/**
 * Вычисляет квадратный корень.
 * Если аргумент меньше нуля -
 * возвращает -1.
 * @param val Значение.
 * @return Квадратный корень.
 */
EXTERN iq15_t iq15_sqrt(iq15_t val);

/**
 * Вычисляет арктангенс от значений Y и X ( atan(Y/X) ).
 * Угол возвращается в периодических единицах.
 * @param y Координата Y.
 * @param x Координата X.
 * @return Угол.
 */
ALWAYS_INLINE static iq15_t iq15_atan2_pu(iq15_t y, iq15_t x)
{
    iq15_t angle = 0;

    iq15_cordic_atan2_hyp_pu(x, y, &angle, NULL);

    return angle;
}

/**
 * Вычисляет арктангенс от значений Y и X ( atan(Y/X) ).
 * Угол возвращается в радианах.
 * @param y Координата Y.
 * @param x Координата X.
 * @return Угол.
 */
ALWAYS_INLINE static iq15_t iq15_atan2(iq15_t y, iq15_t x)
{
    iq15_t angle = 0;

    iq15_cordic_atan2_hyp(x, y, &angle, NULL);

    return angle;
}


#endif /* IQ15_MATH_H */
