#ifndef FRACT_MEAN_H
#define FRACT_MEAN_H

#include "module/base.h"
#include "conf/consts.h"
#include "iqmath/iq24.h"
#include <stddef.h>


//! Делитель периода - число открытий пар тиристоров за период.
#define FRACT_MEAN_K 6

//! Число точек малой части (N).
#define FRACT_MEAN_COUNT_S (CONF_PERIOD_SAMPLES / FRACT_MEAN_K)

//! Число точек большой части (M).
#define FRACT_MEAN_COUNT_L ((CONF_PERIOD_SAMPLES + FRACT_MEAN_K - 1) / FRACT_MEAN_K)

//! Коффициент для малой части.
#define FRACT_MEAN_KS IQ24F((FRACT_MEAN_K * FRACT_MEAN_COUNT_L - CONF_PERIOD_SAMPLES), (FRACT_MEAN_K * FRACT_MEAN_COUNT_S))

//! Коффициент для большой части.
#define FRACT_MEAN_KL IQ24F((CONF_PERIOD_SAMPLES - FRACT_MEAN_K * FRACT_MEAN_COUNT_S), (FRACT_MEAN_K * FRACT_MEAN_COUNT_L))

// Длина буфера.
#define FRACT_MEAN_BUF_LEN FRACT_MEAN_COUNT_L


//! Перечисление возможных бит управления.
enum _E_Fract_Mean_Control {
    FRACT_MEAN_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Fract_Mean_Status {
    FRACT_MEAN_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Fract_Mean M_fract_mean;

//! Структура модуля.
struct _S_Fract_Mean {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_value; //!< Входное значение.
    // Выходные данные.
    reg_iq24_t out_value; //!< Выходное значение.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_fract_mean);
    METHOD_DEINIT(M_fract_mean);
    METHOD_CALC(M_fract_mean);
    // Коллбэки.
    // Внутренние данные.
    iq24_t m_buf[FRACT_MEAN_BUF_LEN]; //!< Буфер значений.
    size_t m_index; //!< Текущий индекс в массиве.
    iq24_t m_sum_s_z1; //!< Малая сумма, задержанная на 1 такт.
};

EXTERN METHOD_INIT_PROTO(M_fract_mean);
EXTERN METHOD_DEINIT_PROTO(M_fract_mean);
EXTERN METHOD_CALC_PROTO(M_fract_mean);

#define FRACT_MEAN_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_fract_mean), METHOD_DEINIT_PTR(M_fract_mean),\
        METHOD_CALC_PTR(M_fract_mean),\
        /* Коллбэки */\
        /* Внутренние данные */\
        {0}, /* m_buf */\
        0, /* m_index */\
        0, /* m_sum_s_z1 */\
    }

#endif /* FRACT_MEAN_H */
