#ifndef IQ24_MATH_H
#define IQ24_MATH_H

#include "iq24.h"
#include "defs/defs.h"


//! Константа PI в формате IQ24.
#define IQ24_PI (0x3243F6A)

//! Константа Е в формате IQ24.
#define IQ24_E (0x2B7E151)

//! Константа 2*PI в формате IQ24.
#define IQ24_2PI (0x6487ED5)

//! Константа PI/2 в формате IQ24.
#define IQ24_PI2 (0x1921FB5)

//! Константа PI/4 в формате IQ24.
#define IQ24_PI4 (0xC90FDA)


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
    return iq24_sin_pu((iq24_t)0x400000 - angle);
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
    // tmp = angle / (2*pi).
    iq24_t tmp = iq24_mul(angle, 2670177);
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
    // tmp = angle / (2*pi).
    iq24_t tmp = iq24_mul(angle, 2670177);
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


#endif /* IQ24_MATH_H */
