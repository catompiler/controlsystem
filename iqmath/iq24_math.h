#ifndef IQ24_MATH_H
#define IQ24_MATH_H

#include "iq24.h"
#include "defs/defs.h"
#include <stddef.h>


//! Константа sqrt(2) в формате IQ24.
#define IQ24_SQRT2 (0x16A09E6)

//! Константа 1/sqrt(2) в формате IQ24.
#define IQ24_INV_SQRT2 (0xB504F3)

//! Константа Е в формате IQ24.
#define IQ24_E (0x2B7E151)

//! Константа PI в формате IQ24.
#define IQ24_PI (0x3243F6A)

//! Константа 2*PI в формате IQ24.
#define IQ24_2PI (0x6487ED5)

//! Константа PI/2 в формате IQ24.
#define IQ24_PI2 (0x1921FB5)

//! Константа PI/4 в формате IQ24.
#define IQ24_PI4 (0xC90FDA)

//! Угол PI в относительных единицах в формате IQ24.
#define IQ24_PI_PU (0x800000)

//! Угол 2*PI в относительных единицах в формате IQ24.
#define IQ24_2PI_PU (0x1000000)

//! Угол PI/2 в относительных единицах в формате IQ24.
#define IQ24_PI2_PU (0x400000)

//! Угол PI/4 в относительных единицах в формате IQ24.
#define IQ24_PI4_PU (0x200000)

//! Инвертированный угол 2*PI в радианах.
#define IQ24_INV_2PI (0x28BE61)


/**
 * Округляет вниз число с фиксированной запятой.
 * @param q Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_floor(iq24_t q)
{
    iq24_t res = IQN_FLOOR(q, IQ24_FRACT_BITS, IQ24_MASK_TYPE);

    return res;
}

/**
 * Округляет вверх число с фиксированной запятой.
 * @param q Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_ceil(iq24_t q)
{
    iq24_t res = IQN_CEIL(q, IQ24_FRACT_BITS, IQ24_TYPE, IQ24_MASK_TYPE);

    return res;
}

/**
 * Округляет число с фиксированной запятой.
 * @param q Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_round(iq24_t q)
{
    iq24_t res = IQN_ROUND(q, IQ24_FRACT_BITS, IQ24_TYPE, IQ24_MASK_TYPE);

    return res;
}

/**
 * Преобразует радианы в периодические единицы.
 * @param angle Угол в радианах.
 * @return Угол в периодических единицах.
 */
ALWAYS_INLINE static iq24_t iq24_rads_to_pu(iq24_t angle)
{
    return iq24_mul(angle, IQ24_INV_2PI);
}

/**
 * Преобразует периодические единицы в радианы.
 * @param angle Угол в периодических единицах.
 * @return Угол в радианах.
 */
ALWAYS_INLINE static iq24_t iq24_pu_to_rads(iq24_t angle)
{
    return iq24_mul(angle, IQ24_2PI);
}

/**
 * Функция sin.
 * Аргумент в периодических единицах.
 * @param angle Угол.
 * @return Значение.
 */
EXTERN iq24_t iq24_sin_pu(iq24_t angle);

/**
 * Функция cos.
 * Аргумент в периодических единицах.
 * Работает через синус, т.к.
 * cos(a) = sin(pi/2 - a).
 * @param angle Угол.
 * @return Значение.
 */
ALWAYS_INLINE static iq24_t iq24_cos_pu(iq24_t angle)
{
    return iq24_sin_pu(IQ24_PI2_PU - angle);
}

/**
 * Функция sin.
 * Аргумент в радианах.
 * @param angle Угол.
 * @return Значение.
 */
ALWAYS_INLINE static iq24_t iq24_sin(iq24_t angle)
{
    // Приведение угла в радианах в цикличные единицы.
    iq24_t tmp = iq24_rads_to_pu(angle);
    return iq24_sin_pu(tmp);
}

/**
 * Функция sin.
 * Аргумент в радианах.
 * Работает через синус, т.к.
 * cos(a) = sin(pi/2 - a).
 * @param angle Угол.
 * @return Значение.
 */
ALWAYS_INLINE static iq24_t iq24_cos(iq24_t angle)
{
    // Приведение угла в радианах в цикличные единицы.
    iq24_t tmp = iq24_rads_to_pu(angle);
    return iq24_cos_pu(tmp);
}

/**
 * Вычисляет квадратный корень.
 * Если аргумент меньше нуля -
 * возвращает -1.
 * @param val Значение.
 * @return Квадратный корень.
 */
EXTERN iq24_t iq24_sqrt(iq24_t val);

/**
 * Вычисляет арктангенс от значений Y и X ( atan(Y/X) ).
 * Угол возвращается в периодических единицах.
 * @param y Координата Y.
 * @param x Координата X.
 * @return Угол.
 */
EXTERN iq24_t iq24_atan2_pu(iq24_t y, iq24_t x);

/**
 * Вычисляет арктангенс от значений Y и X ( atan(Y/X) ).
 * Угол возвращается в радианах.
 * @param y Координата Y.
 * @param x Координата X.
 * @return Угол.
 */
ALWAYS_INLINE static iq24_t iq24_atan2(iq24_t y, iq24_t x)
{
    iq24_t tmp = iq24_atan2_pu(y, x);
    // Приведение угла в периодических единицах в радианы.
    tmp = iq24_pu_to_rads(tmp);

    return tmp;
}


#endif /* IQ24_MATH_H */
