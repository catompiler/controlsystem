#ifndef Q15_MATH_H
#define Q15_MATH_H

#include "q15.h"
#include "defs/defs.h"


//! Константа PI/4 в формате IQ15.
#define IQ15_PI4 (0x6487)


///**
// * Округляет вниз число с фиксированной запятой.
// * @param q Число.
// * @return Результат.
// */
//ALWAYS_INLINE static q15_t q15_floor(q15_t q)
//{
//    q15_t res = IQN_FLOOR(q, Q15_FRACT_BITS, Q15_MASK_TYPE);
//
//    return res;
//}
//
///**
// * Округляет вверх число с фиксированной запятой.
// * @param q Число.
// * @return Результат.
// */
//ALWAYS_INLINE static q15_t q15_ceil(q15_t q)
//{
//    q15_t res = IQN_CEIL(q, Q15_FRACT_BITS, Q15_TYPE, Q15_MASK_TYPE);
//
//    return res;
//}
//
///**
// * Округляет число с фиксированной запятой.
// * @param q Число.
// * @return Результат.
// */
//ALWAYS_INLINE static q15_t q15_round(q15_t q)
//{
//    q15_t res = IQN_ROUND(q, Q15_FRACT_BITS, Q15_TYPE, Q15_MASK_TYPE);
//
//    return res;
//}

/**
 * Функция sin.
 * Аргумент в циклических единицах.
 * @param angle Угол.
 * @return Значение.
 */
EXTERN q15_t q15_sin_pu(q15_t angle);

/**
 * Функция cos.
 * Аргумент в циклических единицах.
 * Работает через синус, т.к.
 * cos(a) = sin(pi/2 - a).
 * @param angle Угол.
 * @return Значение.
 */
ALWAYS_INLINE static q15_t q15_cos_pu(q15_t angle)
{
    return q15_sin_pu((q15_t)0x2000 - angle);
}

///**
// * Функция sin.
// * Аргумент в радианах.
// * @param angle Угол.
// * @return Значение.
// */
//ALWAYS_INLINE static q15_t q15_sin(q15_t angle)
//{
//    // Приведение угла в радианах в цикличные единицы.
//    // tmp = angle / (2*pi).
//    q15_t tmp = q15_mul(angle, 5215);
//    return q15_sin_pu(tmp);
//}
//
///**
// * Функция sin.
// * Аргумент в радианах.
// * Работает через синус, т.к.
// * cos(a) = sin(pi/2 - a).
// * @param angle Угол.
// * @return Значение.
// */
//ALWAYS_INLINE static q15_t q15_cos(q15_t angle)
//{
//    // Приведение угла в радианах в цикличные единицы.
//    // tmp = angle / (2*pi).
//    q15_t tmp = q15_mul(angle, 5215);
//    return q15_cos_pu(tmp);
//}

/**
 * Вычисляет квадратный корень.
 * Если аргумент меньше нуля -
 * возвращает -1.
 * @param val Значение.
 * @return Квадратный корень.
 */
EXTERN q15_t q15_sqrt(q15_t val);


#endif /* Q15_MATH_H */
