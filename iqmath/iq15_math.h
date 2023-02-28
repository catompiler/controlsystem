#ifndef IQ15_MATH_H
#define IQ15_MATH_H

#include "iq15.h"
#include "defs/defs.h"


//! Константа PI в формате IQ15.
#define IQ15_PI (0x1921F)

//! Константа Е в формате IQ15.
#define IQ15_E (0xADF8)

//! Константа 2*PI в формате IQ15.
#define IQ15_2PI (0x3243F)

//! Константа PI/2 в формате IQ15.
#define IQ15_PI2 (0xC90F)

//! Константа PI/4 в формате IQ15.
#define IQ15_PI4 (0x6487)


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


#endif /* IQ15_MATH_H */
