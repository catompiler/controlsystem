#ifndef BASE_REG_TYPES_H
#define BASE_REG_TYPES_H

#include <stdint.h>
#include "iqmath/iq24.h"
#include "iqmath/iq15.h"


// Перечисление типов.
typedef enum _E_Reg_Type {
    REG_TYPE_I32 = 0, //!< Целочисленное знаковое 32 бит.
    REG_TYPE_U32 = 1, //!< Целочисленное беззнаковое 32 бит.
    REG_TYPE_IQ24 = 2, //!< Фиксированная запятая с дробной частью 24 бит.
    REG_TYPE_IQ15 = 3, //!< Фиксированная запятая с дробной частью 15 бит.
} reg_type_t;

// Целочисленные типы.
//! int32.
typedef int32_t reg_i32_t;
//! uint32.
typedef uint32_t reg_u32_t;

// Дробные типы.
//! iq24.
typedef iq24_t reg_iq24_t;
//! iq15.
typedef iq15_t reg_iq15_t;


#endif /* BASE_REG_TYPES_H */
