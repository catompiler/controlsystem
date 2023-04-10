#ifndef MODULE_STATE_H
#define MODULE_STATE_H

#include <stdint.h>

//! Тип слова состояния.
typedef uint32_t state_t;

//! Общие биты состояния.
enum _E_Base_State {
    STATE_NONE = 0x00, //!< Ничего.
    STATE_INIT = 0x01, //!< Инициализация.
    STATE_IDLE = 0x02, //!< Простой.
    STATE_READY = 0x04, //!< Готовность.
    STATE_RUN = 0x08, //!< Работа.
    STATE_ERROR = 0x10, //!< Ошибка.
    STATE_USER = 0x20 //!< Состояния модулей.
};

#endif /* MODULE_STATE_H */
