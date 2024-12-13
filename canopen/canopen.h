#ifndef CANOPEN_H
#define CANOPEN_H

#include "module/base.h"
#include <stddef.h>
// slcan.
#include "slcan/slcan.h"
#include "slcan/slcan_slave.h"
#include "slcan/slcan_utils.h"
// CANopen.
#include "CANopenNode/CANopen.h"


//! Перечисление возможных бит управления.
enum _E_Canopen_Control {
    CANOPEN_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Canopen_Status {
    CANOPEN_STATUS_NONE = STATUS_NONE,
    CANOPEN_STATUS_RUN = STATUS_RUN,
    CANOPEN_STATUS_ERROR = STATUS_ERROR,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Canopen M_canopen;

//! Структура модуля.
struct _S_Canopen {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_canopen);
    METHOD_DEINIT(M_canopen);
    METHOD_CALC(M_canopen);
    // Коллбэки.
    // Внутренние данные.
    slcan_t m_sc; //!< Serial-Line CAN.
    slcan_slave_t m_scs; //!< SLCAN slave.
    slcan_slave_callbacks_t m_scb; //!< SLCAN slave callbacks.
    CO_t* m_co; //!< CANopen.
};

EXTERN METHOD_INIT_PROTO(M_canopen);
EXTERN METHOD_DEINIT_PROTO(M_canopen);
EXTERN METHOD_CALC_PROTO(M_canopen);

#define CANOPEN_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_canopen), METHOD_DEINIT_PTR(M_canopen),\
        METHOD_CALC_PTR(M_canopen),\
        /* Коллбэки */\
        /* Внутренние данные */\
        {{0}}, /* m_sc */\
        {0}, /* m_scs */\
        {0}, /* m_scb */\
        NULL, /* m_co */\
    }

#endif /* CANOPEN_H */
