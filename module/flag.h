#ifndef MODULE_FLAG_H
#define MODULE_FLAG_H

#include <stdint.h>

//! Тип флага.
typedef uint32_t flag_t;

//! Общие биты флага.
enum _E_Base_Flag {
    FLAG_NONE = 0x00, //!< Ничего.
    FLAG_ACTIVE = 0x01, //!< Активно.
};

#endif /* MODULE_FLAG_H */
