#include "iq15_math.h"
#include "iq15_cordic.h"
#include "iq15_sin_table.h"

//#define IQ15_1_DIV_2_PI (5215)
#define IQ15_2_PI_DIV_SIN_TABLE_SIZE (1608)
#define SIN_TABLE_SIZE_2PI_PLUS_PI_DIV_2 (IQ15_SIN_TABLE_SIZE + IQ15_SIN_TABLE_SIZE/4)

iq15_t iq15_sin_pu(iq15_t angle)
{
    int32_t i_f;
    iq15_t f0, f1, df0, df1;

    iq15_t t;
    iq15_t t2;
    iq15_t t3;
    iq15_t a, b;
    //iq15_t c, d;

    iq15_t tmp, res;

    /*
     * Приведённый к интервалу [0; 1) угол:
     * IQ15:
     * ----------------
     * | 16 bit INT   | - Игнорируется (1 == 2*pi).
     * ----------------
     * | 15 bit FRACT | - Два компонента.
     * ----------------
     * FRACT:
     * ---------
     * | 7 bit | - Индекс в таблице.
     * ---------
     * | 8 bit | - Значение интерполяции.
     * ---------
     */

    // Функция в цикла на единицу (PU).
    // Приведение угла в радианах к относительному интервалу [0; 1).
    //tmp = iq15_mul(angle, IQ15_1_DIV_2_PI); // [-2*pi*N; 2*pi*N) -> [-N; N)
    tmp = angle;
    // Дополнительный код дробной части меняется от -1(-2*pi) до 0,
    // повторяя изменение основного кода дробной части от 0 до 1(2*pi),
    // так же целая часть не учитывается (т.к. функция периодична),
    // поэтому не требуется интервал [-N; N) приводить к интервалу [0; 1).
    //tmp = iq15_fract(tmp); // [-N; N) -> [-1; 1)
    //tmp = iq15_iadd(tmp, 1); // [-1; 1) -> [0; 2)
    // Целая часть периодов игнорируется,
    // поэтому интервал [0; 2) можно не приводить к интервалу [0; 1).
    //angle_tu = iq15_fract(angle_tu); // [0; 2) -> [0; 1)
    //angle_tu = angle_tu & 0x7fff;    // [0; 2) -> [0; 1)

    // Индекс в таблице для f(0).
    i_f = (tmp >> 8) & 0x7f;

    // t.
    // t(q8).
    t = tmp & 0xff;
    // t^2.
    // tmp(q16) = t(q8) * t(q8).
    tmp = t * t;
    // t^2(q15) = tmp(q16 -> q15).
    t2 = ((uint32_t)tmp) >> 1;
    // t^3.
    // tmp(q24) = t(q8) * tmp(q16).
    tmp = t * tmp;
    // t^3(q15) = tmp(q24 -> q15).
    t3 = ((uint32_t)tmp) >> 9;
    // t.
    // t(q15) = t(q8 -> q15).
    t = ((uint32_t)t) << 7;

    // Значение f(0).
    f0 = iq15_sin_table[i_f];
    // Индекс в таблице для f(1).
    i_f = (i_f + 1) & 0x7f;
    // Значение f(1).
    f1 = iq15_sin_table[i_f];
    // Индекс в таблице для f'(1).
    i_f = (SIN_TABLE_SIZE_2PI_PLUS_PI_DIV_2 - i_f) & 0x7f;
    // Значение f'(1).
    df1 = iq15_sin_table[i_f];
    // Индекс в таблице для f'(0).
    i_f = (i_f + 1) & 0x7f;
    // Значение f'(0).
    df0 = iq15_sin_table[i_f];

    // Масштабировать производную от [0; 2*pi) до [0; 1/SIZE].
    df0 = iq15_mul(df0, IQ15_2_PI_DIV_SIN_TABLE_SIZE);
    df1 = iq15_mul(df1, IQ15_2_PI_DIV_SIN_TABLE_SIZE);

    // a = 2 * f(0) - 2 * f(1) + f'(0) + f'(1).
    // f(0) - f(1).
    a = iq15_sub(f0, f1);
    // f'(0) + 2 * a.
    a = iq15_add(df0, a << 1);
    // + f'(1).
    a = iq15_add(a, df1);

    // b = -3 * f(0) + 3 * f(1) - 2 * f'(0) - f'(1).
    // f(1) - f(0).
    b = iq15_sub(f1, f0);
    // * 3.
    b = iq15_imul(b, 3);
    // - 2 * f'(0).
    b = iq15_sub(b, df0 << 1);
    // - f'(1).
    b = iq15_sub(b, df1);

    // c = f'(0).
    //c = df0;
    // d = f(0).
    //d = f0;

    // res = a * t^3 + b * t^2 + c * t + d.
    // res = t * (t * (a * t + b) + c) + d.

    // a * t^3.
    res = iq15_mul(a, t3);
    // b * t^2.
    tmp = iq15_mul(b, t2);
    res = iq15_add(res, tmp);
    // c * t.
    tmp = iq15_mul(df0, t);
    res = iq15_add(res, tmp);
    // d.
    res = iq15_add(res, f0);

    return res;
}


iq15_t iq15_sqrt(iq15_t val)
{
#define IQ15_SQRT_VALUE_BITS 32
#define IQ15_SQRT_FRACT_BITS 15

    if(val < 0) return -1;

    uint32_t x = (uint32_t)val;
    uint32_t y = 0;
    uint32_t b = 0b1 << (IQ15_SQRT_VALUE_BITS - 2 - (IQ15_SQRT_FRACT_BITS & 0x1));
    uint32_t p = 0;
    int i;

    // int part.
    #pragma GCC unroll 16
    for(i = 0; i < (IQ15_SQRT_VALUE_BITS/2); i ++){
        y = p | b;
        if(y <= x){
            x -= y;
            p = b | (p >> 1);
        }else{
            p >>= 1;
        }
        b >>= 2;
    }

    // fract part.
    b = 0b1;
    #pragma GCC unroll 8
    for(i = 0; i < (IQ15_SQRT_FRACT_BITS-(IQ15_SQRT_FRACT_BITS/2)); i ++){
        x <<= 2;
        y = b | (p << 2);
        if(y <= x){
            x -= y;
            p = b | (p << 1);
        }else{
            p <<= 1;
        }
    }

    return (iq15_t)p;

#undef IQ15_SQRT_FRACT_BITS
#undef IQ15_SQRT_VALUE_BITS
}


iq15_t iq15_atan2_pu(iq15_t y, iq15_t x)
{
    iq15_t angle = 0;

    iq15_cordic_atan2_hyp_pu(x, y, &angle, NULL);

    return angle;
}
