#include "iq24_math.h"
#include "iq24_cordic.h"
#include "iq24_sin_table.h"

//#define IQ24_1_DIV_2_PI (2670177)
#define IQ24_2_PI_DIV_SIN_TABLE_SIZE (411775)
#define SIN_TABLE_SIZE_2PI_PLUS_PI_DIV_2 (IQ24_SIN_TABLE_SIZE + IQ24_SIN_TABLE_SIZE/4)

iq24_t iq24_sin_pu(iq24_t angle)
{
    int32_t i_f;
    iq24_t f0, f1, df0, df1;

    iq24_t t;
    iq24_t t2;
    iq24_t t3;
    iq24_t a, b;
    //iq24_t c, d;

    iq24_t tmp, res;

    /*
     * Приведённый к интервалу [0; 1) угол:
     * IQ24:
     * ----------------
     * |  7 bit INT   | - Игнорируется (1 == 2*pi).
     * ----------------
     * | 24 bit FRACT | - Два компонента.
     * ----------------
     * FRACT:
     * ----------
     * |  8 bit | - Индекс в таблице.
     * ----------
     * | 16 bit | - Значение интерполяции.
     * ----------
     */

    // Функция в цикла на единицу (PU).
    // Приведение угла в радианах к относительному интервалу [0; 1).
    //tmp = iq24_mul(angle, IQ24_1_DIV_2_PI); // [-2*pi*N; 2*pi*N) -> [-N; N)
    tmp = angle;
    // Дополнительный код дробной части меняется от -1(-2*pi) до 0,
    // повторяя изменение основного кода дробной части от 0 до 1(2*pi),
    // так же целая часть не учитывается (т.к. функция периодична),
    // поэтому не требуется интервал [-N; N) приводить к интервалу [0; 1).
    //tmp = iq24_fract(tmp); // [-N; N) -> [-1; 1)
    //tmp = iq24_iadd(tmp, 1); // [-1; 1) -> [0; 2)
    // Целая часть периодов игнорируется,
    // поэтому интервал [0; 2) можно не приводить к интервалу [0; 1).
    //angle_tu = iq24_fract(angle_tu); // [0; 2) -> [0; 1)
    //angle_tu = angle_tu & 0xffffffff;// [0; 2) -> [0; 1)

    // Индекс в таблице для f(0).
    i_f = (tmp >> 16) & 0xff;

    // t.
    // t(q16).
    t = tmp & 0xffff;
    // t^2.
    // tmp(q32) = t(q16) * t(q16).
    tmp = t * t;
    // t^2(q24) = tmp(q32 -> q24).
    t2 = ((uint32_t)tmp) >> 8;
    // t^3.
    // tmp(q16) = t2(q24 -> q16).
    tmp = ((uint32_t)t2) >> 8;
    // tmp(q32) = t(q16) * tmp(q16).
    tmp = t * tmp;
    // t^3(q24) = tmp(q32 -> q24).
    t3 = ((uint32_t)tmp) >> 8;
    // t.
    // t(q24) = t(q16 -> q24).
    t = ((uint32_t)t) << 8;

    // Значение f(0).
    f0 = iq24_sin_table[i_f];
    // Индекс в таблице для f(1).
    i_f = (i_f + 1) & 0xff;
    // Значение f(1).
    f1 = iq24_sin_table[i_f];
    // Индекс в таблице для f'(1).
    i_f = (SIN_TABLE_SIZE_2PI_PLUS_PI_DIV_2 - i_f) & 0xff;
    // Значение f'(1).
    df1 = iq24_sin_table[i_f];
    // Индекс в таблице для f'(0).
    i_f = (i_f + 1) & 0xff;
    // Значение f'(0).
    df0 = iq24_sin_table[i_f];

    // Масштабировать производную от [0; 2*pi) до [0; 1/SIZE].
    df0 = iq24_mul(df0, IQ24_2_PI_DIV_SIN_TABLE_SIZE);
    df1 = iq24_mul(df1, IQ24_2_PI_DIV_SIN_TABLE_SIZE);

    // a = 2 * f(0) - 2 * f(1) + f'(0) + f'(1).
    // f(0) - f(1).
    a = iq24_sub(f0, f1);
    // f'(0) + 2 * a.
    a = iq24_add(df0, a << 1);
    // + f'(1).
    a = iq24_add(a, df1);

    // b = -3 * f(0) + 3 * f(1) - 2 * f'(0) - f'(1).
    // f(1) - f(0).
    b = iq24_sub(f1, f0);
    // * 3.
    b = iq24_imul(b, 3);
    // - 2 * f'(0).
    b = iq24_sub(b, df0 << 1);
    // - f'(1).
    b = iq24_sub(b, df1);

    // c = f'(0).
    //c = df0;
    // d = f(0).
    //d = f0;

    // res = a * t^3 + b * t^2 + c * t + d.
    // res = t * (t * (a * t + b) + c) + d.

    // a * t^3.
    res = iq24_mul(a, t3);
    // b * t^2.
    tmp = iq24_mul(b, t2);
    res = iq24_add(res, tmp);
    // c * t.
    tmp = iq24_mul(df0, t);
    res = iq24_add(res, tmp);
    // d.
    res = iq24_add(res, f0);

    return res;
}


iq24_t iq24_sqrt(iq24_t val)
{
#define IQ24_SQRT_VALUE_BITS 32
#define IQ24_SQRT_FRACT_BITS 24

    if(val < 0) return -1;

    uint32_t x = (uint32_t)val;
    uint32_t y = 0;
    uint32_t b = 0b1 << (IQ24_SQRT_VALUE_BITS - 2 - (IQ24_SQRT_FRACT_BITS & 0x1));
    uint32_t p = 0;
    int i;

    // int part.
    #pragma GCC unroll 16
    for(i = 0; i < (IQ24_SQRT_VALUE_BITS/2); i ++){
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
    #pragma GCC unroll 12
    for(i = 0; i < (IQ24_SQRT_FRACT_BITS-IQ24_SQRT_FRACT_BITS/2); i ++){
        x <<= 2;
        y = b | (p << 2);
        if(y <= x){
            x -= y;
            p = b | (p << 1);
        }else{
            p <<= 1;
        }
    }

    return (iq24_t)p;

#undef IQ24_SQRT_FRACT_BITS
#undef IQ24_SQRT_VALUE_BITS
}


iq24_t iq24_atan2_pu(iq24_t y, iq24_t x)
{
    iq24_t angle = 0;

    iq24_cordic_atan2_hyp_pu(x, y, &angle, NULL);

    return angle;
}


iq24_t iq24_lerp(iq24_t a, iq24_t b, iq24_t t)
{
    // res = a * (1.0 - t) + b * t == a + (b - a) * t;
    iq24_t res;

    res = iq24_sub(b, a);
    res = iq24_mul(res, t);
    res = iq24_add(res, a);

    return res;
}
