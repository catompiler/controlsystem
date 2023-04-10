#ifndef MODULE_ERROR_H
#define MODULE_ERROR_H

#include <stdint.h>

//! Тип слова ошибки.
typedef uint32_t error_t;

//! Общие биты статуса.
enum _E_Base_Error {
    ERROR_NONE = 0x00, //!< Нет ошибок.
    ERROR_USER = 0x01  //!< Ошибки модулей.
};

#endif /* MODULE_ERROR_H */
