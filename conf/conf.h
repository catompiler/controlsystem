#ifndef CONF_H
#define CONF_H

#include "module/base.h"
#include "iqmath/iqmath.h"

//! Перечисление возможных бит управления.
enum _E_Conf_Control {
    CONF_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Conf_Status {
    CONF_STATUS_NONE = STATUS_NONE,
    CONF_STATUS_READY = STATUS_READY,
    CONF_STATUS_VALID = STATUS_VALID,
};

typedef struct _S_Conf M_conf;

struct _S_Conf {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    reg_iq15_t p_U_nom; //!< Номинальное (базовое) напряжение.
    reg_iq15_t p_I_nom; //!< Номинальный (базовый) ток.
    // Регистры.
    reg_iq24_t r_inv_U_nom; //!< Инвертированное значение номинального (базового) напряжения.
    reg_iq24_t r_inv_I_nom; //!< Инвертированное значение номинального (базового) тока.
    // Методы.
    METHOD_INIT(M_conf);
    METHOD_DEINIT(M_conf);
    METHOD_IDLE(M_conf);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_conf);
EXTERN METHOD_DEINIT_PROTO(M_conf);
EXTERN METHOD_IDLE_PROTO(M_conf);

#define CONF_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        IQ15(230), IQ15(415), /* Номинальные(базовые) напряжение и ток */\
        /* Регистры */\
        0, 0, /* Инвертированные номинальные(базовые) напряжение и ток */\
        /* Методы */\
        METHOD_INIT_PTR(M_conf), METHOD_DEINIT_PTR(M_conf),\
        METHOD_IDLE_PTR(M_conf),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* CONF_H */
