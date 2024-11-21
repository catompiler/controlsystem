#ifndef BASE_REG_TYPES_H
#define BASE_REG_TYPES_H

#include <stdint.h>
#include "iqmath/iq24.h"
#include "iqmath/iq15.h"
#include "iqmath/iq7.h"


// Перечисление типов.
typedef enum _E_Reg_Type {
    REG_TYPE_I32 = 0, //!< Целочисленное знаковое 32 бит.
    REG_TYPE_I16 = 1, //!< Целочисленное знаковое 16 бит.
    REG_TYPE_I8 = 2, //!< Целочисленное знаковое 8 бит.
    REG_TYPE_U32 = 3, //!< Целочисленное беззнаковое 32 бит.
    REG_TYPE_U16 = 4, //!< Целочисленное беззнаковое 16 бит.
    REG_TYPE_U8 = 5, //!< Целочисленное беззнаковое 8 бит.
    REG_TYPE_IQ24 = 6, //!< Фиксированная запятая с дробной частью 24 бит.
    REG_TYPE_IQ15 = 7, //!< Фиксированная запятая с дробной частью 15 бит.
    REG_TYPE_IQ7 = 8, //!< Фиксированная запятая с дробной частью 7 бит.
    REG_TYPE_STR = 9, //!< Строка.
    REG_TYPE_MEM = 10 //!< Область памяти.
} reg_type_t;

// Целочисленные типы.
//! int8.
typedef int8_t reg_i8_t;
//! int16.
typedef int16_t reg_i16_t;
//! int32.
typedef int32_t reg_i32_t;
//! unt8.
typedef uint8_t reg_u8_t;
//! unt16.
typedef uint16_t reg_u16_t;
//! uint32.
typedef uint32_t reg_u32_t;

// Дробные типы.
//! iq24.
typedef iq24_t reg_iq24_t;
//! iq15.
typedef iq15_t reg_iq15_t;
//! iq7.
typedef iq7_t reg_iq7_t;

// Дополнительные типы.
//! str.
typedef const char* reg_str_t;
//! mem.
typedef void* reg_mem_t;


#endif /* BASE_REG_TYPES_H */
