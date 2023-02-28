#ifndef Q15_H
#define Q15_H

#include "defs/defs.h"
#include "iq.h"


//! Тип числа.
typedef q15s_t q15_t;
//! Расширенный тип.
typedef q15l_t lq15_t;


//! Число бит дробной части.
#define Q15_FRACT_BITS 15
//! Число бит целой части.
#define Q15_INT_BITS 0

//! Тип Q15.
#define Q15_TYPE q15s_t
//! Базовый тип Q15.
#define Q15_BASE_TYPE int32_t
//! Тип маски Q15.
#define Q15_MASK_TYPE uint16_t
//! Расширенный тип для Q15.
#define Q15_EXT_TYPE q15l_t


//! Создаёт число с фиксированной запятой из константы float.
#define Q15(F) IQN(F, Q15_FRACT_BITS, Q15_TYPE, Q15_BASE_TYPE)
//! Создаёт число с фиксированной запятой из целого числа.
#define Q15I(I) IQNI(I, Q15_FRACT_BITS, Q15_TYPE)
//! Создаёт число с фиксированной запятой из обыкновенной дроби.
#define Q15F(A, B) IQNF(A, B, Q15_FRACT_BITS, Q15_TYPE, Q15_EXT_TYPE)


//! Базовое значение.
#define Q15_BASE IQN_BASE(Q15_FRACT_BITS, Q15_BASE_TYPE)
//! Маска дробной части.
#define Q15_FRACT_MASK IQN_FRACT_MASK(Q15_FRACT_BITS, Q15_MASK_TYPE)


//! Максимум.
#define Q15_MAX IQN_MAX(Q15_INT_BITS, Q15_FRACT_BITS, Q15_TYPE, Q15_MASK_TYPE)
//! Минимум.
#define Q15_MIN IQN_MIN(Q15_INT_BITS, Q15_FRACT_BITS, Q15_TYPE, Q15_MASK_TYPE)

//! Максимум целой части.
#define Q15_IMAX IQN_IMAX(Q15_INT_BITS, Q15_FRACT_BITS, Q15_TYPE, Q15_MASK_TYPE, Q15_EXT_TYPE)
//! Минимум целой части.
#define Q15_IMIN IQN_IMIN(Q15_INT_BITS, Q15_FRACT_BITS, Q15_TYPE, Q15_MASK_TYPE, Q15_EXT_TYPE)

/**
 * Получает модуль числа с фиксированной запятой.
 * @param q Число.
 * @return Модуль числа.
 */
ALWAYS_INLINE static q15_t q15_abs(q15_t q)
{
    q15_t res =  IQN_ABS(q);

    return res;
}

/**
 * Получает целую часть числа с фиксированной запятой.
 * @param q Число.
 * @return Целая часть.
 */
ALWAYS_INLINE static int32_t q15_int(q15_t q)
{
    int32_t res = IQN_INT(q, Q15_FRACT_BITS);

    return res;
}

/**
 * Получает дробную часть числа с фиксированной запятой.
 * @param q Число.
 * @return Дробная часть.
 */
ALWAYS_INLINE static q15_t q15_fract(q15_t q)
{
    q15_t res = IQN_FRACT(q, Q15_FRACT_BITS, Q15_MASK_TYPE);

    return res;
}

/**
 * Насыщает расширенное число с фиксированной запятой.
 * @param q Число.
 * @return Насыщенное значение.
 */
ALWAYS_INLINE static q15_t q15_sat(lq15_t q)
{
    q15_t res = (q15_t)__SSAT(q, 16);

    return res;
}

/**
 * Складывает два числа с фиксированной запятой.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static q15_t q15_add(q15_t a, q15_t b)
{
    q15_t res = a + b;

    return res;
}

/**
 * Складывает два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static q15_t q15_add_sat(q15_t a, q15_t b)
{
    q15_t res = (int16_t)__QADD16((int16_t)a, (int16_t)b);

    return res;
}

/**
 * Складывает два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static lq15_t q15_addl(q15_t a, q15_t b)
{
    lq15_t res = (lq15_t)a + b;

    return res;
}

///**
// * Складывает число с фиксированной запятой и целое число.
// * @param a Число.
// * @param b Целое число.
// * @return Результат.
// */
//ALWAYS_INLINE static q15_t q15_iadd(q15_t a, int32_t b)
//{
//    q15_t res = a + Q15I(b);
//
//    return res;
//}
//
///**
// * Складывает число с фиксированной запятой и целое число
// * с насыщением.
// * @param a Число.
// * @param b Целое число.
// * @return Результат.
// */
//ALWAYS_INLINE static q15_t q15_iadd_sat(q15_t a, int32_t b)
//{
//    q15_t res;
//
//    if(b > Q15_IMAX || b < Q15_IMIN) {
//        lq15_t ext = (lq15_t)a + (((lq15_t)b) << Q15_FRACT_BITS);
//        res = q15_sat(ext);
//    }
//    else res = __QADD16(a, Q15I(b));
//
//    return res;
//}

/**
 * Складывает число с фиксированной запятой и целое число.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static lq15_t q15_iaddl(q15_t a, int32_t b)
{
    lq15_t res = (lq15_t)a + (((lq15_t)b) << Q15_FRACT_BITS);

    return res;
}

/**
 * Вычитает два числа с фиксированной запятой.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static q15_t q15_sub(q15_t a, q15_t b)
{
    q15_t res = a - b;

    return res;
}

/**
 * Вычитает два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static q15_t q15_sub_sat(q15_t a, q15_t b)
{
    q15_t res = (int16_t)__QSUB16((int16_t)a, (int16_t)b);

    return res;
}

/**
 * Вычитает два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static lq15_t q15_subl(q15_t a, q15_t b)
{
    lq15_t res = (lq15_t)a - b;

    return res;
}

///**
// * Вычитает из числа с фиксированной запятой целое число.
// * @param a Число.
// * @param b Целое число.
// * @return Результат.
// */
//ALWAYS_INLINE static q15_t q15_isub(q15_t a, int32_t b)
//{
//    q15_t res = a - Q15I(b);
//
//    return res;
//}
//
///**
// * Вычитает из числа с фиксированной запятой целое число.
// * с насыщением.
// * @param a Число.
// * @param b Целое число.
// * @return Результат.
// */
//ALWAYS_INLINE static q15_t q15_isub_sat(q15_t a, int32_t b)
//{
//    q15_t res;
//
//    if(b > Q15_IMAX || b < Q15_IMIN) {
//        lq15_t ext = (lq15_t)a - (((lq15_t)b) << Q15_FRACT_BITS);
//        res = q15_sat(ext);
//    }
//    else res = __QSUB16(a, Q15I(b));
//
//    return res;
//}

/**
 * Вычитает из числа с фиксированной запятой целое число.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static lq15_t q15_isubl(q15_t a, int32_t b)
{
    lq15_t res = (lq15_t)a - (((lq15_t)b) << Q15_FRACT_BITS);

    return res;
}

/**
 * Умножает два числа с фиксированной запятой.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static q15_t q15_mul(q15_t a, q15_t b)
{
    lq15_t ext = (lq15_t)a * b;
    q15_t res = (q15_t)(ext >> Q15_FRACT_BITS);

    return res;
}

/**
 * Умножает два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static q15_t q15_mul_sat(q15_t a, q15_t b)
{
    lq15_t ext = (lq15_t)a * b;
    ext = (ext >> Q15_FRACT_BITS);

    q15_t res = q15_sat(ext);

    return res;
}

/**
 * Умножает два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static lq15_t q15_mull(q15_t a, q15_t b)
{
    lq15_t res = (lq15_t)a * b;
    res = (res >> Q15_FRACT_BITS);

    return res;
}

/**
 * Умножает число с фиксированной запятой на целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static q15_t q15_imul(q15_t a, int32_t b)
{
    q15_t res = a * b;

    return res;
}

/**
 * Умножает число с фиксированной запятой на целое число
 * с насыщением.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static q15_t q15_imul_sat(q15_t a, int32_t b)
{
    lq15_t ext = (lq15_t)a * b;
    q15_t res = q15_sat(ext);

    return res;
}

/**
 * Умножает число с фиксированной запятой на целое число.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static lq15_t q15_imull(q15_t a, int32_t b)
{
    lq15_t res = (lq15_t)a * b;

    return res;
}

/**
 * Делит два числа с фиксированной запятой.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static q15_t q15_div(q15_t a, q15_t b)
{
    lq15_t ext = (lq15_t)a << Q15_FRACT_BITS;
    q15_t res = (q15_t)(ext / b);

    return res;
}

/**
 * Делит два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static q15_t q15_div_sat(q15_t a, q15_t b)
{
    lq15_t ext = (lq15_t)a << Q15_FRACT_BITS;
    ext = (ext / b);
    q15_t res = q15_sat(ext);

    return res;
}

/**
 * Делит два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static lq15_t q15_divl(q15_t a, q15_t b)
{
    lq15_t res = (lq15_t)a << Q15_FRACT_BITS;
    res = (res / b);

    return res;
}

/**
 * Делит число с фиксированной запятой на целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static q15_t q15_idiv(q15_t a, int32_t b)
{
    q15_t res = a / b;

    return res;
}


#endif /* Q15_H */
