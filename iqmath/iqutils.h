#ifndef IQMATH_IQUTILS_H
#define IQMATH_IQUTILS_H

#include <stdint.h>
#include "iq24.h"
#include "iq15.h"



/**
 * Преобразует 32 бит число с фиксированной запятой
 * из одного формата в другой.
 * @param q Число с фиксированной запятой.
 * @param n Исходное число бит дробной части.
 * @param m Новое число бит дробной части.
 * @return Число с фиксированной запятой.
 */
ALWAYS_INLINE static iql_t iqn_to_m(iql_t q, uint32_t n, uint32_t m)
{
    iql_t res = IQ_N_TO_M(q, n, m);

    return res;
}

/**
 * Преобразует 64 бит число с фиксированной запятой
 * из одного формата в другой.
 * @param q Число с фиксированной запятой.
 * @param n Исходное число бит дробной части.
 * @param m Новое число бит дробной части.
 * @return Число с фиксированной запятой.
 */
ALWAYS_INLINE static iqll_t liqn_to_m(iqll_t q, uint32_t n, uint32_t m)
{
    iqll_t res = IQ_N_TO_M(q, n, m);

    return res;
}

/**
 * Инвертирует значение IQ7
 * с результатом IQ24.
 * @param value Значение. Не должно быть 0.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq7_inv24(iq7_t value)
{
    // IQ(41) = IQ(24+24) - IQ(7).
    iq41ll_t resl = iq24_divl(IQ24(1), value);
    iq24_t res = IQ_N_TO_M(resl, 41, 24);

    return res;
}

/**
 * Инвертирует значение IQ15
 * с результатом IQ24.
 * @param value Значение. Не должно быть 0.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq15_inv24(iq15_t value)
{
    // IQ(33) = IQ(24+24) - IQ(15).
    iq33ll_t resl = iq24_divl(IQ24(1), value);
    iq24_t res = IQ_N_TO_M(resl, 33, 24);

    return res;
}

/**
 * Инвертирует значение IQ24
 * с результатом IQ15.
 * @param value Значение. Не должно быть 0.
 * @return Результат.
 */
ALWAYS_INLINE static iq15_t iq24_inv15(iq24_t value)
{
    // IQ(24) = IQ(24+24) - IQ(24).
    iq24ll_t resl = iq24_divl(IQ24(1), value);
    iq15_t res = IQ_N_TO_M(resl, 24, 15);

    return res;
}

/**
 * Инвертирует значение IQ24
 * с результатом IQ7.
 * @param value Значение. Не должно быть 0.
 * @return Результат.
 */
ALWAYS_INLINE static iq7_t iq24_inv7(iq24_t value)
{
    // IQ(24) = IQ(24+24) - IQ(24).
    iq24ll_t resl = iq24_divl(IQ24(1), value);
    iq7_t res = IQ_N_TO_M(resl, 24, 7);

    return res;
}

/**
 * Инвертирует целое значение I32
 * с результатом IQ24.
 * @param value Значение. Не должно быть 0.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t i32_inv24(int32_t value)
{
    return IQ24(1) / value;
}

/**
 * Проверяет значение на нахождение
 * в заданном интервале [min_value, max_value].
 * @param value Значение.
 * @return 1, если значение находится в интервале, иначе 0.
 */
ALWAYS_INLINE static uint32_t iqn_in_range(iql_t value , iql_t min_value, iql_t max_value)
{
    if(value < min_value) return 0;
    if(value > max_value) return 0;

    return 1;
}

/**
 * Проверяет значение на нахождение
 * в заданном интервале [min_value, max_value].
 * @param value Значение.
 * @return 1, если значение находится в интервале, иначе 0.
 */
ALWAYS_INLINE static uint32_t liqn_in_range(iqll_t value , iqll_t min_value, iqll_t max_value)
{
    if(value < min_value) return 0;
    if(value > max_value) return 0;

    return 1;
}

/**
 * Получает целую часть числа с фиксированной запятой.
 * @param q Число.
 * @return Целая часть.
 */
ALWAYS_INLINE static int32_t liq7_int(liq7_t q)
{
    int32_t res = IQN_INT(q, IQ7_FRACT_BITS);

    return res;
}

/**
 * Получает целую часть числа с фиксированной запятой.
 * @param q Число.
 * @return Целая часть.
 */
ALWAYS_INLINE static int32_t liq15_int(liq15_t q)
{
    int32_t res = IQN_INT(q, IQ15_FRACT_BITS);

    return res;
}

/**
 * Получает целую часть числа с фиксированной запятой.
 * @param q Число.
 * @return Целая часть.
 */
ALWAYS_INLINE static int32_t liq24_int(liq24_t q)
{
    int32_t res = IQN_INT(q, IQ24_FRACT_BITS);

    return res;
}

/**
 * Делит целое число I32
 * на число с фиксированной запятой IQ15.
 * @param a Делимое.
 * @param b Делитель. Не должно быть 0.
 * @return Результат в формате IQ15.
 */
ALWAYS_INLINE static iq15_t i32_div_iq15(int32_t a, iq15_t b)
{
    // IQ30 = IQ0 -> IQ(15 + 15).
    liq15_t ext = (liq15_t)a << (IQ15_FRACT_BITS + IQ15_FRACT_BITS);
    iq15_t res = (iq15_t)(ext / b);

    return res;
}

/**
 * Умножает два числа IQ15 с результатом IQ24.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iq24_t iq15_mul24(iq15_t a, iq15_t b)
{
    iq30ll_t ext = (iq30ll_t)a * b;
    iq24_t res = (iq24_t)(ext >> (IQ15_FRACT_BITS + IQ15_FRACT_BITS - IQ24_FRACT_BITS));

    return res;
}

/**
 * Безопасное среднее двух чисел.
 * @param a Число.
 * @param b Число.
 * @return Результат.
 */
ALWAYS_INLINE static iql_t iql_mean2(iql_t a, iql_t b)
{
    iql_t res = (a >> 1) + (b >> 1) + (a & b & 0x1);

    return res;
}

/**
 * Безопасное среднее трёх чисел.
 * @param a Число.
 * @param b Число.
 * @param c Число.
 * @return Результат.
 */
ALWAYS_INLINE static iql_t iql_mean3(iql_t a, iql_t b, iql_t c)
{
    iqll_t sum = (iqll_t)a + b + c;

    iql_t res = 0;

    if(sum <= INT32_MAX && sum >= INT32_MIN){
        res = ((iql_t)sum) / (iql_t)3;
    }else{
        res = (iql_t)(sum / (iql_t)3);
    }
    return res;
}

/**
 * Безопасное среднее трёх чисел.
 * @param q Массив чисел.
 * @param n Количество чисел, не более INT32_MAX.
 * @return Результат.
 */
ALWAYS_INLINE static iql_t iql_mean(iql_t* q, size_t n)
{
    iqll_t sum = 0;
    size_t i;

    iql_t* q_ptr = q;

    size_t unrolls_count = n >> 2; // /4
    for(i = 0; i < unrolls_count; i ++){
        sum += (iqll_t)(*q_ptr ++);
        sum += (iqll_t)(*q_ptr ++);
        sum += (iqll_t)(*q_ptr ++);
        sum += (iqll_t)(*q_ptr ++);
    }

    size_t unrolls_rem = n & 0x3; // %3
    for(i = 0; i < unrolls_rem; i ++){
        sum += (iqll_t)(*q_ptr ++);
    }

    iql_t res = 0;

    if(sum <= INT32_MAX && sum >= INT32_MIN){
        res = ((iql_t)sum) / (iql_t)n;
    }else{
        res = (iql_t)(sum / (iql_t)n);
    }

    return res;
}

#endif /* IQMATH_IQUTILS_H */
