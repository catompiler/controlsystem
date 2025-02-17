#ifndef PROT_H
#define PROT_H

#include "module/base.h"


//! Перечисление возможных бит ошибок слова 0.
enum _E_Prot_Errors0 {
    PROT_ERR0_NONE = ERROR_NONE, //!< Нет ошибок.

    PROT_ERR0_INTERNAL_SW = 0x01, //!< Ошибка ПО.
    PROT_ERR0_INTERNAL_HW = 0x02, //!< Ошибка аппаратной части.

    PROT_ERR0_INTERNAL_PWR,

    PROT_ERR0_INTERNAL_CAN_FAULT,
    PROT_ERR0_INTERNAL_COMM_TIMEOUT,

    //PROT_ERR0_ = 0x00, //!< .
};

//! Перечисление возможных бит ошибок слова 1.
enum _E_Prot_Errors1 {
    PROT_ERR1_NONE = ERROR_NONE, //!< Нет ошибок.

    PROT_ERR1_MAINS_LOST,
    PROT_ERR1_MAINS_INVALID,
    PROT_ERR1_MAINS_UNDERVOLTAGE,
    PROT_ERR1_MAINS_OVERVOLTAGE,
    PROT_ERR1_OVERCURRENT,
    PROT_ERR1_OVERVOLTAGE,

    //PROT_ERR1_ = 0x00, //!< .
};

//! Перечисление возможных бит ошибок слова 2.
enum _E_Prot_Errors2 {
    PROT_ERR2_NONE = ERROR_NONE, //!< Нет ошибок.

    PROT_ERR2_EXTERNAL_FAULT,
    PROT_ERR2_OVERLOAD,
    PROT_ERR2_CELL_FAULT,
    PROT_ERR2_ASYNC_RUN,

    //PROT_ERR2_ = 0x00, //!< .
};


//! Перечисление возможных бит предупреждений.
enum _E_Prot_Warnings0 {
    PROT_WARN0_NONE = WARNING_NONE, //!< Нет предупреждений.

    //PROT_WARN0_ = 0x00, //!<
};


//! Перечисление возможных бит управления.
enum _E_Prot_Control {
    PROT_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Prot_Status {
    PROT_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Prot M_prot;

//! Структура модуля.
struct _S_Prot {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    error_t errors0; //!< Слово ошибок 0.
    error_t errors1; //!< Слово ошибок 1.
    error_t warnings0; //!< Слово предупреждений 0.
    error_t warnings1; //!< Слово предупреждений 1.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_prot);
    METHOD_DEINIT(M_prot);
    METHOD_CALC(M_prot);
    METHOD_IDLE(M_prot);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_prot);
EXTERN METHOD_DEINIT_PROTO(M_prot);
EXTERN METHOD_CALC_PROTO(M_prot);
EXTERN METHOD_IDLE_PROTO(M_prot);

#define PROT_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        0, 0, /* errors0, errors1 */\
        0, 0, /* warnings0, warnings1 */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_prot), METHOD_DEINIT_PTR(M_prot),\
        METHOD_CALC_PTR(M_prot), METHOD_IDLE_PTR(M_prot),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* PROT_H */
