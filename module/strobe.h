#ifndef MODULE_STROBE_H
#define MODULE_STROBE_H

#include <stdint.h>

//! Тип строба.
typedef uint32_t strobe_t;

//! Общие биты строба.
enum _E_Base_Strobe {
    STROBE_NONE = 0x00, //!< Ничего.
    STROBE_ACTIVE = 0x01, //!< Активно.
};

#endif /* MODULE_STROBE_H */
