/**
 * @file bits.h
 * Макросы для работы с битами.
 */

#ifndef BITS_H
#define	BITS_H

#include <stdint.h>
#include <stddef.h>
#include "defs/defs.h"

#ifndef BIT_SET_TEST_0BIT
#define BIT_SET_TEST_0BIT 1
#endif

/**
 * Формирует число с установленным битом
 * в заданной позиции B.
 */
#define BIT(B) (1 << (B))
/**
 * Формирует число с битом, равным V
 * в заданной позиции B.
 */
#if BIT_SET_TEST_0BIT == 1
#define BIT_BYVAL(B, V) ((V & 0x1) << B)
#else
#define BIT_BYVAL(B, V) ((V      ) << B)
#endif
/**
 * Устанавливает бит номер B в переменной P.
 */
#define BIT_ON(P, B) do{(P) |= BIT(B);}while(0)
/**
 * Сбрасывает бит номер B в переменной P.
 */
#define BIT_OFF(P, B) do{(P) &= ~BIT(B);}while(0)
/**
 * Изменяет бит номер B в переменной P.
 */
#define BIT_TOGGLE(P, B) do{(P) ^= BIT(B);}while(0)
/**
 * Устанавливает бит номер B в переменной P в значение V.
 */
#if BIT_SET_TEST_0BIT == 1
    #define BIT_SET(P, B, V) do{ if( (V) & 0x1 ){ BIT_ON(P, B); }else{ BIT_OFF(P, B); } }while(0)
#else
    #define BIT_SET(P, B, V) do{ if( (V)       ){ BIT_ON(P, B); }else{ BIT_OFF(P, B); } }while(0)
#endif
/**
 * Инвертирует нулевой бит в числе P.
 */
#define BIT0_NOT(P) ((P) ^ 1)
/**
 * Проверяет бит номер B в переменной P.
 */
#define BIT_TEST(P, B) ((P) & BIT(B))
/**
 * Возвращает сырое значение бита B в переменной P.
 */
#define BIT_RAW_VALUE(P, B) ((P) & BIT(B))
/**
 * Ждёт установки бита B в переменной P.
 */
#define BIT_WAIT_ON(P, B) do{}while(!BIT_TEST(P, B))
/**
 * Ждёт снятия бита B в переменной P.
 */
#define BIT_WAIT_OFF(P, B) do{}while(BIT_TEST(P, B))
/**
 * Возвращает значение бита B в переменной P.
 */
#define BIT_VALUE(P, B) ((BIT_TEST(P, B)) ? 0x1 : 0x0)
/**
 * Возвращает 1, если бит установлен, иначе возвращает 0.
 */
#define BIT_IS_ON(P, B) ((BIT_TEST(P, B)) ? 0x1 : 0x0)
/**
 * Возвращает 1, если бит сброшен, иначе возвращает 0.
 */
#define BIT_IS_OFF(P, B) ((BIT_TEST(P, B)) ? 0x0 : 0x1)
/**
 * Устанавливает биты, соответствущие маске.
 */
#define BIT_ON_MASK(P, M) do{(P) |= (M);}while(0)
/**
 * Сбрасывает биты, соответствующие маске.
 */
#define BIT_OFF_MASK(P, M) do{(P) &= ~(M);}while(0)
/**
 * Изменяет биты, соответствующие маске.
 */
#define BIT_TOGGLE_MASK(P, M) do{(P) ^= (M);}while(0)
/**
 * Устанавливает биты, соответсвующие маске M, в переменной P в значение V.
 */
#if BIT_SET_TEST_0BIT == 1
    #define BIT_SET_MASK(P, M, V) do{ if( (V) & 0x1 ){ BIT_ON_MASK(P, M); }else{ BIT_OFF_MASK(P, M); } }while(0)
#else
    #define BIT_SET_MASK(P, M, V) do{ if( (V)       ){ BIT_ON_MASK(P, M); }else{ BIT_OFF_MASK(P, M); } }while(0)
#endif
/**
 * Проверяет биты, соответствующие маске.
 */
#define BIT_TEST_MASK(P, M) ((P) & (M))
/**
 * Возвращает наличие хотябы одного установленного бита по маске M в переменной P.
 */
#define BIT_TEST_VALUE_MASK(P, M) ((BIT_TEST_MASK(P, M)) ? 0x1 : 0x0)
/**
 * Формирует маску длиной N бит и смещением S бит.
 */
#define BIT_MAKE_MASK(N, S) ((BIT(N) - 1) << (S))
/**
 * Получает значение бит смещением O и длиной S в переменной P.
 */
#define BIT_VALUE_LEN(P, O, S) (((P) >> (O)) & (BIT(S) - 1))
/**
 * Получает значение бит смещением O и маской M в переменной P.
 */
#define BIT_VALUE_MASK(P, O, M) (((P) >> (O)) & (M))

/**
 * Проверяет является ли значение V степенью двойки.
 */
#define IS_POW2(V) (((V) & ((V) - 1)) == 0)

// Вспомогательный макрос для получение степени двойки для значения.
#define _GP2_TB(V, B) (BIT_IS_ON((V), (B)) ? ((B)) : (0))
/**
 * Получает степень двойки для значения V.
 * Значение должно быть степенью двойки.
 */
#define GET_POW2(V) (_GP2_TB((V), 0)  + _GP2_TB((V), 1) +\
                       _GP2_TB((V), 2)  + _GP2_TB((V), 3) +\
                       _GP2_TB((V), 4)  + _GP2_TB((V), 5) +\
                       _GP2_TB((V), 6)  + _GP2_TB((V), 7) +\
                       _GP2_TB((V), 8)  + _GP2_TB((V), 9) +\
                       _GP2_TB((V), 10) + _GP2_TB((V), 11) +\
                       _GP2_TB((V), 12) + _GP2_TB((V), 13) +\
                       _GP2_TB((V), 14) + _GP2_TB((V), 15) +\
                       _GP2_TB((V), 16) + _GP2_TB((V), 17) +\
                       _GP2_TB((V), 18) + _GP2_TB((V), 19) +\
                       _GP2_TB((V), 20) + _GP2_TB((V), 21) +\
                       _GP2_TB((V), 22) + _GP2_TB((V), 23) +\
                       _GP2_TB((V), 24) + _GP2_TB((V), 25) +\
                       _GP2_TB((V), 26) + _GP2_TB((V), 27) +\
                       _GP2_TB((V), 28) + _GP2_TB((V), 29) +\
                       _GP2_TB((V), 30) + _GP2_TB((V), 31))


/*
 * Работа с битами массива байт.
 */

/**
 * Устанавливает бит в массиве.
 * @param bits Массив.
 * @param bit_n Номер бита.
 */
ALWAYS_INLINE static void bits_on(uint8_t* bits, size_t bit_n)
{
    BIT_ON(bits[bit_n >> 3], bit_n & 0x7);
}

/**
 * Сбрасывает бит в массиве.
 * @param bits Массив.
 * @param bit_n Номер бита.
 */
ALWAYS_INLINE static void bits_off(uint8_t* bits, size_t bit_n)
{
    BIT_OFF(bits[bit_n >> 3], bit_n & 0x7);
}

/**
 * Возвращает бит в массиве.
 * @param bits Массив.
 * @param bit_n Номер бита.
 * @return Бит.
 */
ALWAYS_INLINE static uint32_t bits_value(const uint8_t* bits, size_t bit_n)
{
    return BIT_VALUE(bits[bit_n >> 3], bit_n & 0x7);
}

/**
 * Устанавливает значение бита в массиве.
 * @param bits Массив.
 * @param bit_n Номер бита.
 * @param bit Значение бита.
 */
ALWAYS_INLINE static void bits_set_value(uint8_t* bits, size_t bit_n, uint32_t bit)
{
    size_t byte_n = bit_n >> 3;
    size_t byte_bit_n = bit_n & 0x7;
    
    BIT_SET(bits[byte_n], byte_bit_n, bit);
}

#endif	/* BITS_H */

