#ifndef MODULE_STATUS_H
#define MODULE_STATUS_H

#include <stdint.h>

//! Тип слова статуса.
typedef uint32_t status_t;

//! Общие биты статуса.
enum _E_Base_Status {
    STATUS_NONE = 0x00, //!< Ничего.
    STATUS_READY = 0x01, //!< Готовность.
    STATUS_VALID = 0x02, //!< Правильность выходных данных.
    STATUS_RUN = 0x04, //!< Работа.
    STATUS_ERROR = 0x08, //!< Ошибка.
    STATUS_WARNING = 0x08, //!< Предупреждение.
    STATUS_USER = 0x10 //!< Статусы модулей.
};


#endif /* MODULE_STATUS_H */
