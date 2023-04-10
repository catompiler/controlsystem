#ifndef MODULE_CONTROL_H
#define MODULE_CONTROL_H

#include <stdint.h>

//! Тип слова управления.
typedef uint32_t control_t;

//! Общие биты статуса.
enum _E_Base_Control {
    CONTROL_NONE = 0x00, //!< Ничего.
    CONTROL_RESET = 0x01, //!< Сброс.
    CONTROL_ENABLE = 0x02, //!< Разрешение работы.
    CONTROL_START = 0x04, //!< Запуск.
    CONTROL_STOP = 0x08, //!< Останов.
    CONTROL_USER = 0x10 //!< Управление модулей.
};

#endif /* MODULE_CONTROL_H */
