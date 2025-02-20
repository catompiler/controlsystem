#ifndef PROT_H
#define PROT_H

#include "module/base.h"
#include "prot_item_gt.h"
#include "prot_item_lt.h"



//! Перечисление возможных бит ошибок слова 0.
enum _E_Prot_Errors0 {
    PROT_ERR0_NONE = ERROR_NONE, //!< Нет ошибок.

    PROT_ERR0_INTERNAL_SW = 0x01, //!< Ошибка ПО.
    PROT_ERR0_INTERNAL_HW = 0x02, //!< Ошибка аппаратной части.

    PROT_ERR0_INTERNAL_PWR = 0x04,

    PROT_ERR0_INTERNAL_CAN_FAULT = 0x08,
    PROT_ERR0_INTERNAL_COMM_TIMEOUT = 0x10,

    //PROT_ERR0_ = 0x00, //!< .
};

//! Перечисление возможных бит ошибок слова 1.
enum _E_Prot_Errors1 {
    PROT_ERR1_NONE = ERROR_NONE, //!< Нет ошибок.

    PROT_ERR1_MAINS_LOST = 0x01,
    PROT_ERR1_MAINS_INVALID = 0x02,
    PROT_ERR1_MAINS_UNDERVOLTAGE = 0x04,
    PROT_ERR1_MAINS_OVERVOLTAGE = 0x08,
    PROT_ERR1_MAINS_OVERCURRENT = 0x10,
    PROT_ERR1_OVERVOLTAGE = 0x20,
    PROT_ERR1_OVERCURRENT = 0x40,

    //PROT_ERR1_ = 0x00, //!< .
};

//! Перечисление возможных бит ошибок слова 2.
enum _E_Prot_Errors2 {
    PROT_ERR2_NONE = ERROR_NONE, //!< Нет ошибок.

    PROT_ERR2_EXTERNAL_FAULT = 0x01,
    PROT_ERR2_OVERLOAD = 0x02,
    PROT_ERR2_CELL_FAULT = 0x04,
    PROT_ERR2_ASYNC_RUN = 0x08,

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
    error_t errors2; //!< Слово ошибок 1.
    warning_t warnings0; //!< Слово предупреждений 0.
    warning_t warnings1; //!< Слово предупреждений 1.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    // Потеря фаз(ы).
    reg_iq24_t p_mains_lost_U_low;
    // Отклонение угла фаз и частоты.
    reg_iq24_t p_mains_invalid_A_delta;
    reg_iq24_t p_mains_invalid_F_delta;
    // Снижение напряжения.
    reg_iq24_t p_mains_undervoltage_U_low;
    // Превышение напряжения.
    reg_iq24_t p_mains_overvoltage_U_hi;
    // Превышение тока.
    reg_iq24_t p_mains_overcurrent_I_hi;
    // Превышение напряжения выхода.
    reg_iq24_t p_overvoltage_U_hi;
    // Превышение тока выхода.
    reg_iq24_t p_overcurrent_I_hi;
    // Регистры.
    // "Сырые" значения защит.
    error_t raw_errors0;
    error_t raw_errors1;
    error_t raw_errors2;
    // Маска - разрешение срабатывания защит.
    error_t mask_errors0;
    error_t mask_errors1;
    error_t mask_errors2;
    // Потеря фаз(ы).
    M_timer_on r_mains_lost_timer;
    // Отклонение угла фаз и частоты.
    M_timer_on r_mains_invalid_timer;
    // Снижение напряжения.
    M_timer_on r_mains_undervoltage_timer;
    // Превышение напряжения.
    M_timer_on r_mains_overvoltage_timer;
    // Превышение тока.
    M_timer_on r_mains_overcurrent_timer;
    // Превышение напряжения выхода.
    M_timer_on r_overvoltage_timer;
    // Превышение тока выхода.
    M_timer_on r_overcurrent_timer;
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
        0, 0, 0, /* errors0, errors1, errors2 */\
        0, 0, /* warnings0, warnings1 */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        IQ24(0.3), /* p_mains_lost_U_low */\
        IQ24(0.05), /* p_mains_invalid_A_delta */\
        IQ24(5.0), /* p_mains_invalid_F_delta */\
        IQ24(0.8), /* p_mains_undervoltage_U_low */\
        IQ24(1.2), /* p_mains_overvoltage_U_hi */\
        IQ24(1.4), /* p_mains_overcurrent_I_hi */\
        IQ24(1.5), /* p_overvoltage_U_hi */\
        IQ24(1.4), /* p_overcurrent_I_hi */\
        /* Регистры */\
        0, 0, 0, /* raw_errors0, raw_errors1, raw_errors2 */\
        0, 0, 0, /* mask_errors0, mask_errors1, mask_errors2 */\
        TIMER_ON_DEFCFG(20), /* r_mains_lost_timer */\
        TIMER_ON_DEFCFG(100), /* r_mains_invalid_timer */\
        TIMER_ON_DEFCFG(100), /* r_mains_undervoltage_timer */\
        TIMER_ON_DEFCFG(100), /* r_mains_overvoltage_timer */\
        TIMER_ON_DEFCFG(10), /* r_mains_overcurrent_timer */\
        TIMER_ON_DEFCFG(10), /* r_overcurrent_timer */\
        TIMER_ON_DEFCFG(100), /* r_overvoltage_timer */\
        /* Методы */\
        METHOD_INIT_PTR(M_prot), METHOD_DEINIT_PTR(M_prot),\
        METHOD_CALC_PTR(M_prot), METHOD_IDLE_PTR(M_prot),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* PROT_H */
