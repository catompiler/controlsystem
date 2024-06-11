#ifndef DC_MEAN_H
#define DC_MEAN_H

#include "module/base.h"
#include "conf/consts.h"
#include <stddef.h>


//! Число точек в буфере.
#define DC_MEAN_BUF_LEN (CONF_PERIOD_SAMPLES/6)


//! Перечисление возможных бит управления.
enum _E_Dc_Mean_Control {
    DC_MEAN_CONTROL_NONE = CONTROL_NONE,//!< DC_MEAN_CONTROL_NONE
};

//! Перечисление возможных бит статуса.
enum _E_Dc_Mean_Status {
    DC_MEAN_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Dc_Mean M_dc_mean;

//! Структура модуля.
struct _S_Dc_Mean {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_value; //!< Текущее значение.
    // Выходные данные.
    reg_iq24_t out_value; //!< Посчитанное среднее.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_dc_mean);
    METHOD_DEINIT(M_dc_mean);
    METHOD_CALC(M_dc_mean);
    // Коллбэки.
    // Внутренние данные.
    iq24_t m_buf[DC_MEAN_BUF_LEN]; //!< Данные для вычисления среднего.
    size_t m_index; //!< Индекс в буфере.
    liq24_t m_sum; //!< Текущая сумма.
};

EXTERN METHOD_INIT_PROTO(M_dc_mean);
EXTERN METHOD_DEINIT_PROTO(M_dc_mean);
EXTERN METHOD_CALC_PROTO(M_dc_mean);

#define DC_MEAN_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_dc_mean), METHOD_DEINIT_PTR(M_dc_mean),\
        METHOD_CALC_PTR(M_dc_mean),\
        /* Коллбэки */\
        /* Внутренние данные */\
        {0}, /* m_buf */\
        0, /* m_index */\
        0, /* m_sum */\
    }

#endif /* DC_MEAN_H */
