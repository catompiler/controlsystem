#ifndef REG_REG_H_
#define REG_REG_H_

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "defs/defs.h"
#include "reg_types.h"

//! Тип идентификатора регистра.
typedef uint32_t reg_id_t;

//! Значение отсутствующего идентификатора.
#define REG_ID_NONE ((reg_id_t)-1)
//! Синоним отсутствующего идентификатора -
//! некорректный идентификатор.
#define REG_ID_INVALID REG_ID_NONE


typedef enum _E_Reg_Flag {
    REG_FLAG_NONE = 0x00,
    REG_FLAG_CONF = 0x01,
    REG_FLAG_READONLY = 0x02,
} reg_flags_t;

//! Структура регистра.
typedef struct _S_Reg {
    reg_id_t id; //!< Идентификатор.
    void* data; //!< Указатель на данные.
    reg_type_t type; //!< Тип данных регистра.
    reg_flags_t flags; //!< Флаги регистра.
    reg_id_t base_id; //!< Идентификатор базовой величины.
} reg_t;


/**
 * Получает идентификатор регистра.
 * @param reg Регистр.
 * @return Идентификатор регистра.
 */
ALWAYS_INLINE static reg_id_t reg_id(const reg_t* reg)
{
    return reg->id;
}

/**
 * Получает указатель на данные регистра.
 * @param reg Регистр.
 * @return Указатель на данные регистра.
 */
ALWAYS_INLINE static void* reg_data(reg_t* reg)
{
    return reg->data;
}

/**
 * Получает тип данных регистра.
 * @param reg Регистр.
 * @return Тип данных регистра.
 */
ALWAYS_INLINE static reg_type_t reg_type(const reg_t* reg)
{
    return reg->type;
}

/**
 * Получает флаги регистра.
 * @param reg Регистр.
 * @return Флаги регистра.
 */
ALWAYS_INLINE static reg_flags_t reg_flags(const reg_t* reg)
{
    return reg->flags;
}


/**
 * Получает идентификатор регистра базовой величины.
 * @param reg Регистр.
 * @return Идентификатор регистра базовой величины.
 */
ALWAYS_INLINE static reg_id_t reg_base_id(const reg_t* reg)
{
    return reg->base_id;
}

/**
 * Получает размер данных регистра.
 * @param reg Регистр.
 * @return Размер данных регистра.
 */
EXTERN size_t reg_data_size(const reg_t* reg);

/**
 * Получает значение регистра как 32 бита.
 * @param reg Регистр.
 * @return Значение регистра как 32 бита.
 */
EXTERN iql_t reg_valuel(const reg_t* reg);


//! Получает значение регистра reg приведённое к типу T.
#define reg_value(reg, T) *((T*)(reg)->data)

/**
 * Получает значение данных регистра.
 * @param reg Регистр.
 * @return Значение данных.
 */
ALWAYS_INLINE static reg_iq24_t reg_value_iq24(const reg_t* reg)
{
    return reg_value(reg, reg_iq24_t);
}

/**
 * Получает значение данных регистра.
 * @param reg Регистр.
 * @return Значение данных.
 */
ALWAYS_INLINE static reg_iq15_t reg_value_iq15(const reg_t* reg)
{
    return reg_value(reg, reg_iq15_t);
}

/**
 * Получает значение данных регистра.
 * @param reg Регистр.
 * @return Значение данных.
 */
ALWAYS_INLINE static reg_iq7_t reg_value_iq7(const reg_t* reg)
{
    return reg_value(reg, reg_iq7_t);
}

/**
 * Получает значение данных регистра.
 * @param reg Регистр.
 * @return Значение данных.
 */
ALWAYS_INLINE static reg_i8_t reg_value_i8(const reg_t* reg)
{
    return reg_value(reg, reg_i8_t);
}

/**
 * Получает значение данных регистра.
 * @param reg Регистр.
 * @return Значение данных.
 */
ALWAYS_INLINE static reg_i16_t reg_value_i16(const reg_t* reg)
{
    return reg_value(reg, reg_i16_t);
}

/**
 * Получает значение данных регистра.
 * @param reg Регистр.
 * @return Значение данных.
 */
ALWAYS_INLINE static reg_i32_t reg_value_i32(const reg_t* reg)
{
    return reg_value(reg, reg_i32_t);
}

/**
 * Получает значение данных регистра.
 * @param reg Регистр.
 * @return Значение данных.
 */
ALWAYS_INLINE static reg_u8_t reg_value_u8(const reg_t* reg)
{
    return reg_value(reg, reg_u8_t);
}

/**
 * Получает значение данных регистра.
 * @param reg Регистр.
 * @return Значение данных.
 */
ALWAYS_INLINE static reg_u16_t reg_value_u16(const reg_t* reg)
{
    return reg_value(reg, reg_u16_t);
}

/**
 * Получает значение данных регистра.
 * @param reg Регистр.
 * @return Значение данных.
 */
ALWAYS_INLINE static reg_u32_t reg_value_u32(const reg_t* reg)
{
    return reg_value(reg, reg_u32_t);
}

/**
 * Получает флаг является ли тип регистра знаковым.
 * @param type Тип.
 * @return Флаг является ли тип регистра знаковым.
 */
EXTERN bool reg_type_is_signed(reg_type_t type);

/**
 * Получает флаг является ли регистр знаковым.
 * @param reg Регистр.
 * @return Флаг является ли регистр знаковым.
 */
ALWAYS_INLINE static bool reg_is_signed(const reg_t* reg)
{
    return reg_type_is_signed(reg->type);
}

#endif /* REG_REG_H_ */
