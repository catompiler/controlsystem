#ifndef IQ24_H
#define IQ24_H

#include "defs/defs.h"
#include "iq.h"


//! Тип числа.
typedef iq24l_t iq24_t;
//! Расширенный тип.
typedef iq24ll_t liq24_t;


//! Число бит дробной части.
#define IQ24_FRACT_BITS 24
//! Число бит целой части.
#define IQ24_INT_BITS 7

//! Тип IQ24.
#define IQ24_TYPE iq24l_t
//! Базовый тип IQ24.
#define IQ24_BASE_TYPE int32_t
//! Тип маски IQ24.
#define IQ24_MASK_TYPE uint32_t
//! Расширенный тип для IQ24.
#define IQ24_EXT_TYPE iq24ll_t


//! Создаёт число с фиксированной запятой из константы float.
#define IQ24(F) IQN(F, IQ24_FRACT_BITS, IQ24_TYPE, IQ24_BASE_TYPE)
//! Создаёт число с фиксированной запятой из целого числа.
#define IQ24I(I) IQNI(I, IQ24_FRACT_BITS, IQ24_TYPE)
//! Создаёт число с фиксированной запятой из обыкновенной дроби.
#define IQ24F(A, B) IQNF(A, B, IQ24_FRACT_BITS, IQ24_TYPE, IQ24_EXT_TYPE)


//! Базовое значение.
#define IQ24_BASE IQN_BASE(IQ24_FRACT_BITS, IQ24_BASE_TYPE)
//! Маска дробной части.
#define IQ24_FRACT_MASK IQN_FRACT_MASK(IQ24_FRACT_BITS, IQ24_MASK_TYPE)


//! Максимум.
#define IQ24_MAX IQN_MAX(IQ24_INT_BITS, IQ24_FRACT_BITS, IQ24_TYPE, IQ24_MASK_TYPE)
//! Минимум.
#define IQ24_MIN IQN_MIN(IQ24_INT_BITS, IQ24_FRACT_BITS, IQ24_TYPE, IQ24_MASK_TYPE)

//! Максимум целой части.
#define IQ24_IMAX IQN_IMAX(IQ24_INT_BITS, IQ24_FRACT_BITS, IQ24_TYPE, IQ24_MASK_TYPE, IQ24_EXT_TYPE)
//! Минимум целой части.
#define IQ24_IMIN IQN_IMIN(IQ24_INT_BITS, IQ24_FRACT_BITS, IQ24_TYPE, IQ24_MASK_TYPE, IQ24_EXT_TYPE)

/**
 * Получает модуль числа с фиксированной запятой.
 * @param q Число.
 * @return Модуль числа.
 */
ALWAYS_INLINE static iq24_t iq24_abs(iq24_t q)
{
    iq24_t res =  IQN_ABS(q);

    return res;
}

/**
 * Получает целую часть числа с фиксированной запятой.
 * @param q Число.
 * @return Целая часть.
 */
ALWAYS_INLINE static int32_t iq24_int(iq24_t q)
{
    int32_t res = IQN_INT(q, IQ24_FRACT_BITS);

    return res;
}

/**
 * Получает дробную часть числа с фиксированной запятой.
 * @param q Число.
 * @return Дробная часть.
 */
ALWAYS_INLINE static iq24_t iq24_fract(iq24_t q)
{
    iq24_t res = IQN_FRACT(q, IQ24_FRACT_BITS, IQ24_MASK_TYPE);

    return res;
}

/**
 * Насыщает расширенное число с фиксированной запятой.
 * @param q Число.
 * @return Насыщенное значение.
 */
ALWAYS_INLINE static iq24_t iq24_sat(liq24_t q)
{
    iq24_t res = (q > IQ24_MAX) ? IQ24_MAX : (q < IQ24_MIN) ? IQ24_MIN : (iq24_t)q;

    return res;
}

/**
 * Складывает два числа с фиксированной запятой.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_add(iq24_t a, iq24_t b)
{
    iq24_t res = a + b;

    return res;
}

/**
 * Складывает два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_add_sat(iq24_t a, iq24_t b)
{
    iq24_t res = __QADD(a, b);

    return res;
}

/**
 * Складывает два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq24_t iq24_addl(iq24_t a, iq24_t b)
{
    liq24_t res = (liq24_t)a + b;

    return res;
}

/**
 * Складывает число с фиксированной запятой и целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_iadd(iq24_t a, int32_t b)
{
    iq24_t res = a + IQ24I(b);

    return res;
}

/**
 * Складывает число с фиксированной запятой и целое число
 * с насыщением.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_iadd_sat(iq24_t a, int32_t b)
{
    iq24_t res;

    if(b > IQ24_IMAX || b < IQ24_IMIN) {
        liq24_t ext = (liq24_t)a + (((liq24_t)b) << IQ24_FRACT_BITS);
        res = iq24_sat(ext);
    }
    else res = __QADD(a, IQ24I(b));

    return res;
}

/**
 * Складывает число с фиксированной запятой и целое число.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq24_t iq24_iaddl(iq24_t a, int32_t b)
{
    liq24_t res = (liq24_t)a + (((liq24_t)b) << IQ24_FRACT_BITS);

    return res;
}

/**
 * Вычитает два числа с фиксированной запятой.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_sub(iq24_t a, iq24_t b)
{
    iq24_t res = a - b;

    return res;
}

/**
 * Вычитает два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_sub_sat(iq24_t a, iq24_t b)
{
    iq24_t res = __QSUB(a, b);

    return res;
}

/**
 * Вычитает два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq24_t iq24_subl(iq24_t a, iq24_t b)
{
    liq24_t res = (liq24_t)a - b;

    return res;
}

/**
 * Вычитает из числа с фиксированной запятой целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_isub(iq24_t a, int32_t b)
{
    iq24_t res = a - IQ24I(b);

    return res;
}

/**
 * Вычитает из числа с фиксированной запятой целое число.
 * с насыщением.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_isub_sat(iq24_t a, int32_t b)
{
    iq24_t res;

    if(b > IQ24_IMAX || b < IQ24_IMIN) {
        liq24_t ext = (liq24_t)a - (((liq24_t)b) << IQ24_FRACT_BITS);
        res = iq24_sat(ext);
    }
    else res = __QSUB(a, IQ24I(b));

    return res;
}

/**
 * Вычитает из числа с фиксированной запятой целое число.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq24_t iq24_isubl(iq24_t a, int32_t b)
{
    liq24_t res = (liq24_t)a - (((liq24_t)b) << IQ24_FRACT_BITS);

    return res;
}

/**
 * Умножает два числа с фиксированной запятой.
 * Результатом умножения числа IQN на число IQM
 * является число IQ(N+M).
 * Для приведения к формату IQ24 выполняет уменьшение
 * дробной части на IQ24_FRACT_BITS бит, поэтому результатом
 * работы функции является число IQ(N+M-IQ24_FRACT_BITS).
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_mul(iq24_t a, iq24_t b)
{
    liq24_t ext = (liq24_t)a * b;
    iq24_t res = (iq24_t)(ext >> IQ24_FRACT_BITS);

    return res;
}

/**
 * Умножает два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_mul_sat(iq24_t a, iq24_t b)
{
    liq24_t ext = (liq24_t)a * b;
    ext = (ext >> IQ24_FRACT_BITS);

    iq24_t res = iq24_sat(ext);

    return res;
}

/**
 * Умножает два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq24_t iq24_mull(iq24_t a, iq24_t b)
{
    liq24_t res = (liq24_t)a * b;
    res = (res >> IQ24_FRACT_BITS);

    return res;
}

/**
 * Умножает число с фиксированной запятой на целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_imul(iq24_t a, int32_t b)
{
    iq24_t res = a * b;

    return res;
}

/**
 * Умножает число с фиксированной запятой на целое число
 * с насыщением.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_imul_sat(iq24_t a, int32_t b)
{
    liq24_t ext = (liq24_t)a * b;
    iq24_t res = iq24_sat(ext);

    return res;
}

/**
 * Умножает число с фиксированной запятой на целое число.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static liq24_t iq24_imull(iq24_t a, int32_t b)
{
    liq24_t res = (liq24_t)a * b;

    return res;
}

/**
 * Делит два числа с фиксированной запятой.
 * Результатом деления числа IQN на число IQM
 * является число IQ(N-M).
 * Для приведения к формату IQ24 выполняет увеличение
 * дробной части на IQ24_FRACT_BITS бит, поэтому результатом
 * работы функции является число IQ(N-M+IQ24_FRACT_BITS).
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_div(iq24_t a, iq24_t b)
{
    liq24_t ext = (liq24_t)a << IQ24_FRACT_BITS;
    iq24_t res = (iq24_t)(ext / b);

    return res;
}

/**
 * Делит два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_div_sat(iq24_t a, iq24_t b)
{
    liq24_t ext = (liq24_t)a << IQ24_FRACT_BITS;
    ext = (ext / b);
    iq24_t res = iq24_sat(ext);

    return res;
}

/**
 * Делит два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq24_t iq24_divl(iq24_t a, iq24_t b)
{
    liq24_t res = (liq24_t)a << IQ24_FRACT_BITS;
    res = (res / b);

    return res;
}

/**
 * Делит число с фиксированной запятой на целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq24_idiv(iq24_t a, int32_t b)
{
    iq24_t res = a / b;

    return res;
}


#endif /* IQ24_H */
