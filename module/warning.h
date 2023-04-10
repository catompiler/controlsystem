#ifndef MODULE_WARNING_H
#define MODULE_WARNING_H

#include <stdint.h>

//! Тип слова предупреждения.
typedef uint32_t warning_t;

//! Общие биты статуса.
enum _E_Base_Warning {
    WARNING_NONE = 0x00, //!< Нет предупреждений.
    WARNING_USER = 0x01  //!< Предупреждения модулей.
};

#endif /* MODULE_WARNING_H */
