#ifndef CANOPEN_H
#define CANOPEN_H

#include "module/base.h"
#include <stddef.h>
// CANopen.
#include "CANopenNode/CANopen.h"
// Драйвера CAN.
#include "CO_driver_target.h"

#ifdef CO_DRIVER_SLCAN_SLAVE
// slcan.
#include "slcan/slcan.h"
#include "slcan/slcan_slave.h"
#include "slcan/slcan_utils.h"
#endif

#ifdef CO_DRIVER_XMC4XXX
// CAN xmc4xxx.
#include "can/can_xmc4xxx.h"
#endif


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
#ifdef CO_DRIVER_SLCAN_SLAVE
    slcan_t m_sc; //!< Serial-Line CAN.
    slcan_slave_t m_scs; //!< SLCAN slave.
    slcan_slave_callbacks_t m_scb; //!< SLCAN slave callbacks.
    CO_t* m_co_ss; //!< CANopen SLCAN slave.
#endif
#ifdef CO_DRIVER_XMC4XXX
    CO_t* m_co_xmc4; //!< CANopen XMC4XXX.
    can_t* m_can_xmc4; //!< Интерфейс CAN XMC4XXX.
    can_node_t* m_can_node_xmc4; //!< Нода CAN XMC4XXX.
#endif
};

EXTERN METHOD_INIT_PROTO(M_canopen);
EXTERN METHOD_DEINIT_PROTO(M_canopen);
EXTERN METHOD_CALC_PROTO(M_canopen);

#ifdef CO_DRIVER_SLCAN_SLAVE
#define CANOPEN_CO_DRIVER_SLCAN_SLAVE_DEFAULTS {{0}}, {0}, {0}, NULL,
#else
#define CANOPEN_CO_DRIVER_SLCAN_SLAVE_DEFAULTS
#endif

#ifdef CO_DRIVER_XMC4XXX
#define CANOPEN_CO_DRIVER_XMC4XXX_DEFAULTS NULL, NULL, NULL,
#else
#define CANOPEN_CO_DRIVER_XMC4XXX_DEFAULTS
#endif

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
        CANOPEN_CO_DRIVER_SLCAN_SLAVE_DEFAULTS\
        CANOPEN_CO_DRIVER_XMC4XXX_DEFAULTS\
    }

#endif /* CANOPEN_H */
