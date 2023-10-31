#ifndef IQ7_H
#define IQ7_H

#include "defs/defs.h"
#include "iq.h"


//! Тип числа.
typedef iq7l_t iq7_t;
//! Расширенный тип.
typedef iq7ll_t liq7_t;


//! Число бит дробной части.
#define IQ7_FRACT_BITS 7
//! Число бит целой части.
#define IQ7_INT_BITS 24

//! Тип IQ7.
#define IQ7_TYPE iq7l_t
//! Базовый тип IQ7.
#define IQ7_BASE_TYPE int32_t
//! Тип маски IQ7.
#define IQ7_MASK_TYPE uint32_t
//! Расширенный тип для IQ7.
#define IQ7_EXT_TYPE iq7ll_t


//! Создаёт число с фиксированной запятой из константы float.
#define IQ7(F) IQN(F, IQ7_FRACT_BITS, IQ7_TYPE, IQ7_BASE_TYPE)
//! Создаёт число с фиксированной запятой из целого числа.
#define IQ7I(I) IQNI(I, IQ7_FRACT_BITS, IQ7_TYPE)
//! Создаёт число с фиксированной запятой из обыкновенной дроби.
#define IQ7F(A, B) IQNF(A, B, IQ7_FRACT_BITS, IQ7_TYPE, IQ7_EXT_TYPE)


//! Базовое значение.
#define IQ7_BASE IQN_BASE(IQ7_FRACT_BITS, IQ7_BASE_TYPE)
//! Маска дробной части.
#define IQ7_FRACT_MASK IQN_FRACT_MASK(IQ7_FRACT_BITS, IQ7_MASK_TYPE)


//! Максимум.
#define IQ7_MAX IQN_MAX(IQ7_INT_BITS, IQ7_FRACT_BITS, IQ7_TYPE, IQ7_MASK_TYPE)
//! Минимум.
#define IQ7_MIN IQN_MIN(IQ7_INT_BITS, IQ7_FRACT_BITS, IQ7_TYPE, IQ7_MASK_TYPE)

//! Максимум целой части.
#define IQ7_IMAX IQN_IMAX(IQ7_INT_BITS, IQ7_FRACT_BITS, IQ7_TYPE, IQ7_MASK_TYPE, IQ7_EXT_TYPE)
//! Минимум целой части.
#define IQ7_IMIN IQN_IMIN(IQ7_INT_BITS, IQ7_FRACT_BITS, IQ7_TYPE, IQ7_MASK_TYPE, IQ7_EXT_TYPE)

/**
 * Получает модуль числа с фиксированной запятой.
 * @param q Число.
 * @return Модуль числа.
 */
ALWAYS_INLINE static iq7_t iq7_abs(iq7_t q)
{
    iq7_t res =  IQN_ABS(q);

    return res;
}

/**
 * Получает целую часть числа с фиксированной запятой.
 * @param q Число.
 * @return Целая часть.
 */
ALWAYS_INLINE static int32_t iq7_int(iq7_t q)
{
    int32_t res = IQN_INT(q, IQ7_FRACT_BITS);

    return res;
}

/**
 * Получает дробную часть числа с фиксированной запятой.
 * @param q Число.
 * @return Дробная часть.
 */
ALWAYS_INLINE static iq7_t iq7_fract(iq7_t q)
{
    iq7_t res = IQN_FRACT(q, IQ7_FRACT_BITS, IQ7_MASK_TYPE);

    return res;
}

/**
 * Насыщает расширенное число с фиксированной запятой.
 * @param q Число.
 * @return Насыщенное значение.
 */
ALWAYS_INLINE static iq7_t iq7_sat(liq7_t q)
{
    iq7_t res = (q > IQ7_MAX) ? IQ7_MAX : (q < IQ7_MIN) ? IQ7_MIN : (iq7_t)q;

    return res;
}

/**
 * Складывает два числа с фиксированной запятой.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_add(iq7_t a, iq7_t b)
{
    iq7_t res = a + b;

    return res;
}

/**
 * Складывает два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_add_sat(iq7_t a, iq7_t b)
{
    iq7_t res = __QADD(a, b);

    return res;
}

/**
 * Складывает два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq7_t iq7_addl(iq7_t a, iq7_t b)
{
    liq7_t res = (liq7_t)a + b;

    return res;
}

/**
 * Складывает число с фиксированной запятой и целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_iadd(iq7_t a, int32_t b)
{
    iq7_t res = a + IQ7I(b);

    return res;
}

/**
 * Складывает число с фиксированной запятой и целое число
 * с насыщением.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_iadd_sat(iq7_t a, int32_t b)
{
    iq7_t res;

    if(b > IQ7_IMAX || b < IQ7_IMIN) {
        liq7_t ext = (liq7_t)a + (((liq7_t)b) << IQ7_FRACT_BITS);
        res = iq7_sat(ext);
    }
    else res = __QADD(a, IQ7I(b));

    return res;
}

/**
 * Складывает число с фиксированной запятой и целое число.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq7_t iq7_iaddl(iq7_t a, int32_t b)
{
    liq7_t res = (liq7_t)a + (((liq7_t)b) << IQ7_FRACT_BITS);

    return res;
}

/**
 * Вычитает два числа с фиксированной запятой.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_sub(iq7_t a, iq7_t b)
{
    iq7_t res = a - b;

    return res;
}

/**
 * Вычитает два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_sub_sat(iq7_t a, iq7_t b)
{
    iq7_t res = __QSUB(a, b);

    return res;
}

/**
 * Вычитает два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq7_t iq7_subl(iq7_t a, iq7_t b)
{
    liq7_t res = (liq7_t)a - b;

    return res;
}

/**
 * Вычитает из числа с фиксированной запятой целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_isub(iq7_t a, int32_t b)
{
    iq7_t res = a - IQ7I(b);

    return res;
}

/**
 * Вычитает из числа с фиксированной запятой целое число.
 * с насыщением.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_isub_sat(iq7_t a, int32_t b)
{
    iq7_t res;

    if(b > IQ7_IMAX || b < IQ7_IMIN) {
        liq7_t ext = (liq7_t)a - (((liq7_t)b) << IQ7_FRACT_BITS);
        res = iq7_sat(ext);
    }
    else res = __QSUB(a, IQ7I(b));

    return res;
}

/**
 * Вычитает из числа с фиксированной запятой целое число.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq7_t iq7_isubl(iq7_t a, int32_t b)
{
    liq7_t res = (liq7_t)a - (((liq7_t)b) << IQ7_FRACT_BITS);

    return res;
}

/**
 * Умножает два числа с фиксированной запятой.
 * Результатом умножения числа IQN на число IQM
 * является число IQ(N+M).
 * Для приведения к формату IQ7 выполняет уменьшение
 * дробной части на IQ7_FRACT_BITS бит, поэтому результатом
 * работы функции является число IQ(N+M-IQ7_FRACT_BITS).
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_mul(iq7_t a, iq7_t b)
{
    liq7_t ext = (liq7_t)a * b;
    iq7_t res = (iq7_t)(ext >> IQ7_FRACT_BITS);

    return res;
}

/**
 * Умножает два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_mul_sat(iq7_t a, iq7_t b)
{
    liq7_t ext = (liq7_t)a * b;
    ext = (ext >> IQ7_FRACT_BITS);

    iq7_t res = iq7_sat(ext);

    return res;
}

/**
 * Умножает два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq7_t iq7_mull(iq7_t a, iq7_t b)
{
    liq7_t res = (liq7_t)a * b;
    res = (res >> IQ7_FRACT_BITS);

    return res;
}

/**
 * Умножает число с фиксированной запятой на целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_imul(iq7_t a, int32_t b)
{
    iq7_t res = a * b;

    return res;
}

/**
 * Умножает число с фиксированной запятой на целое число
 * с насыщением.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_imul_sat(iq7_t a, int32_t b)
{
    liq7_t ext = (liq7_t)a * b;
    iq7_t res = iq7_sat(ext);

    return res;
}

/**
 * Умножает число с фиксированной запятой на целое число.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static liq7_t iq7_imull(iq7_t a, int32_t b)
{
    liq7_t res = (liq7_t)a * b;

    return res;
}

/**
 * Делит два числа с фиксированной запятой.
 * Результатом деления числа IQN на число IQM
 * является число IQ(N-M).
 * Для приведения к формату IQ7 выполняет увеличение
 * дробной части на IQ7_FRACT_BITS бит, поэтому результатом
 * работы функции является число IQ(N-M+IQ7_FRACT_BITS).
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_div(iq7_t a, iq7_t b)
{
    liq7_t ext = (liq7_t)a << IQ7_FRACT_BITS;
    iq7_t res = (iq7_t)(ext / b);

    return res;
}

/**
 * Делит два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_div_sat(iq7_t a, iq7_t b)
{
    liq7_t ext = (liq7_t)a << IQ7_FRACT_BITS;
    ext = (ext / b);
    iq7_t res = iq7_sat(ext);

    return res;
}

/**
 * Делит два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq7_t iq7_divl(iq7_t a, iq7_t b)
{
    liq7_t res = (liq7_t)a << IQ7_FRACT_BITS;
    res = (res / b);

    return res;
}

/**
 * Делит число с фиксированной запятой на целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq7_idiv(iq7_t a, int32_t b)
{
    iq7_t res = a / b;

    return res;
}


#endif /* IQ7_H */
