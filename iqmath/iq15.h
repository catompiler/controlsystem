#ifndef IQ15_H
#define IQ15_H

#include "defs/defs.h"
#include "iq.h"


//! Тип числа.
typedef iq15l_t iq15_t;
//! Расширенный тип.
typedef iq15ll_t liq15_t;


//! Число бит дробной части.
#define IQ15_FRACT_BITS 15
//! Число бит целой части.
#define IQ15_INT_BITS 16

//! Тип IQ15.
#define IQ15_TYPE iq15l_t
//! Базовый тип IQ15.
#define IQ15_BASE_TYPE int32_t
//! Тип маски IQ15.
#define IQ15_MASK_TYPE uint32_t
//! Расширенный тип для IQ15.
#define IQ15_EXT_TYPE iq15ll_t


//! Создаёт число с фиксированной запятой из константы float.
#define IQ15(F) IQN(F, IQ15_FRACT_BITS, IQ15_TYPE, IQ15_BASE_TYPE)
//! Создаёт число с фиксированной запятой из целого числа.
#define IQ15I(I) IQNI(I, IQ15_FRACT_BITS, IQ15_TYPE)
//! Создаёт число с фиксированной запятой из обыкновенной дроби.
#define IQ15F(A, B) IQNF(A, B, IQ15_FRACT_BITS, IQ15_TYPE, IQ15_EXT_TYPE)


//! Базовое значение.
#define IQ15_BASE IQN_BASE(IQ15_FRACT_BITS, IQ15_BASE_TYPE)
//! Маска дробной части.
#define IQ15_FRACT_MASK IQN_FRACT_MASK(IQ15_FRACT_BITS, IQ15_MASK_TYPE)


//! Максимум.
#define IQ15_MAX IQN_MAX(IQ15_INT_BITS, IQ15_FRACT_BITS, IQ15_TYPE, IQ15_MASK_TYPE)
//! Минимум.
#define IQ15_MIN IQN_MIN(IQ15_INT_BITS, IQ15_FRACT_BITS, IQ15_TYPE, IQ15_MASK_TYPE)

//! Максимум целой части.
#define IQ15_IMAX IQN_IMAX(IQ15_INT_BITS, IQ15_FRACT_BITS, IQ15_TYPE, IQ15_MASK_TYPE, IQ15_EXT_TYPE)
//! Минимум целой части.
#define IQ15_IMIN IQN_IMIN(IQ15_INT_BITS, IQ15_FRACT_BITS, IQ15_TYPE, IQ15_MASK_TYPE, IQ15_EXT_TYPE)

/**
 * Получает модуль числа с фиксированной запятой.
 * @param q Число.
 * @return Модуль числа.
 */
ALWAYS_INLINE static iq15_t iq15_abs(iq15_t q)
{
    iq15_t res =  IQN_ABS(q);

    return res;
}

/**
 * Получает целую часть числа с фиксированной запятой.
 * @param q Число.
 * @return Целая часть.
 */
ALWAYS_INLINE static int32_t iq15_int(iq15_t q)
{
    int32_t res = IQN_INT(q, IQ15_FRACT_BITS);

    return res;
}

/**
 * Получает дробную часть числа с фиксированной запятой.
 * @param q Число.
 * @return Дробная часть.
 */
ALWAYS_INLINE static iq15_t iq15_fract(iq15_t q)
{
    iq15_t res = IQN_FRACT(q, IQ15_FRACT_BITS, IQ15_MASK_TYPE);

    return res;
}

/**
 * Насыщает расширенное число с фиксированной запятой.
 * @param q Число.
 * @return Насыщенное значение.
 */
ALWAYS_INLINE static iq15_t iq15_sat(liq15_t q)
{
    iq15_t res = (q > IQ15_MAX) ? IQ15_MAX : (q < IQ15_MIN) ? IQ15_MIN : (iq15_t)q;

    return res;
}

/**
 * Складывает два числа с фиксированной запятой.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_add(iq15_t a, iq15_t b)
{
    iq15_t res = a + b;

    return res;
}

/**
 * Складывает два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_add_sat(iq15_t a, iq15_t b)
{
    iq15_t res = __QADD(a, b);

    return res;
}

/**
 * Складывает два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq15_t iq15_addl(iq15_t a, iq15_t b)
{
    liq15_t res = (liq15_t)a + b;

    return res;
}

/**
 * Складывает число с фиксированной запятой и целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_iadd(iq15_t a, int32_t b)
{
    iq15_t res = a + IQ15I(b);

    return res;
}

/**
 * Складывает число с фиксированной запятой и целое число
 * с насыщением.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_iadd_sat(iq15_t a, int32_t b)
{
    iq15_t res;

    if(b > IQ15_IMAX || b < IQ15_IMIN) {
        liq15_t ext = (liq15_t)a + (((liq15_t)b) << IQ15_FRACT_BITS);
        res = iq15_sat(ext);
    }
    else res = __QADD(a, IQ15I(b));

    return res;
}

/**
 * Складывает число с фиксированной запятой и целое число.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq15_t iq15_iaddl(iq15_t a, int32_t b)
{
    liq15_t res = (liq15_t)a + (((liq15_t)b) << IQ15_FRACT_BITS);

    return res;
}

/**
 * Вычитает два числа с фиксированной запятой.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_sub(iq15_t a, iq15_t b)
{
    iq15_t res = a - b;

    return res;
}

/**
 * Вычитает два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_sub_sat(iq15_t a, iq15_t b)
{
    iq15_t res = __QSUB(a, b);

    return res;
}

/**
 * Вычитает два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq15_t iq15_subl(iq15_t a, iq15_t b)
{
    liq15_t res = (liq15_t)a - b;

    return res;
}

/**
 * Вычитает из числа с фиксированной запятой целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_isub(iq15_t a, int32_t b)
{
    iq15_t res = a - IQ15I(b);

    return res;
}

/**
 * Вычитает из числа с фиксированной запятой целое число.
 * с насыщением.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_isub_sat(iq15_t a, int32_t b)
{
    iq15_t res;

    if(b > IQ15_IMAX || b < IQ15_IMIN) {
        liq15_t ext = (liq15_t)a - (((liq15_t)b) << IQ15_FRACT_BITS);
        res = iq15_sat(ext);
    }
    else res = __QSUB(a, IQ15I(b));

    return res;
}

/**
 * Вычитает из числа с фиксированной запятой целое число.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq15_t iq15_isubl(iq15_t a, int32_t b)
{
    liq15_t res = (liq15_t)a - (((liq15_t)b) << IQ15_FRACT_BITS);

    return res;
}

/**
 * Умножает два числа с фиксированной запятой.
 * Результатом умножения числа IQN на число IQM
 * является число IQ(N+M).
 * Для приведения к формату IQ15 выполняет уменьшение
 * дробной части на IQ15_FRACT_BITS бит, поэтому результатом
 * работы функции является число IQ(N+M-IQ15_FRACT_BITS).
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_mul(iq15_t a, iq15_t b)
{
    liq15_t ext = (liq15_t)a * b;
    iq15_t res = (iq15_t)(ext >> IQ15_FRACT_BITS);

    return res;
}

/**
 * Умножает два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_mul_sat(iq15_t a, iq15_t b)
{
    liq15_t ext = (liq15_t)a * b;
    ext = (ext >> IQ15_FRACT_BITS);

    iq15_t res = iq15_sat(ext);

    return res;
}

/**
 * Умножает два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq15_t iq15_mull(iq15_t a, iq15_t b)
{
    liq15_t res = (liq15_t)a * b;
    res = (res >> IQ15_FRACT_BITS);

    return res;
}

/**
 * Умножает число с фиксированной запятой на целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_imul(iq15_t a, int32_t b)
{
    iq15_t res = a * b;

    return res;
}

/**
 * Умножает число с фиксированной запятой на целое число
 * с насыщением.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_imul_sat(iq15_t a, int32_t b)
{
    liq15_t ext = (liq15_t)a * b;
    iq15_t res = iq15_sat(ext);

    return res;
}

/**
 * Умножает число с фиксированной запятой на целое число.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static liq15_t iq15_imull(iq15_t a, int32_t b)
{
    liq15_t res = (liq15_t)a * b;

    return res;
}

/**
 * Делит два числа с фиксированной запятой.
 * Результатом деления числа IQN на число IQM
 * является число IQ(N-M).
 * Для приведения к формату IQ15 выполняет увеличение
 * дробной части на IQ15_FRACT_BITS бит, поэтому результатом
 * работы функции является число IQ(N-M+IQ15_FRACT_BITS).
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_div(iq15_t a, iq15_t b)
{
    liq15_t ext = (liq15_t)a << IQ15_FRACT_BITS;
    iq15_t res = (iq15_t)(ext / b);

    return res;
}

/**
 * Делит два числа с фиксированной запятой
 * с насыщением.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_div_sat(iq15_t a, iq15_t b)
{
    liq15_t ext = (liq15_t)a << IQ15_FRACT_BITS;
    ext = (ext / b);
    iq15_t res = iq15_sat(ext);

    return res;
}

/**
 * Делит два числа с фиксированной запятой.
 * Возвращает расширенный результат.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static liq15_t iq15_divl(iq15_t a, iq15_t b)
{
    liq15_t res = (liq15_t)a << IQ15_FRACT_BITS;
    res = (res / b);

    return res;
}

/**
 * Делит число с фиксированной запятой на целое число.
 * @param a Число.
 * @param b Целое число.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq15_idiv(iq15_t a, int32_t b)
{
    iq15_t res = a / b;

    return res;
}


#endif /* IQ15_H */
