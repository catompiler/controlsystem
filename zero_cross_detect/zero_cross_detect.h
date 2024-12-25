#ifndef ZERO_CROSS_DETECT_H
#define ZERO_CROSS_DETECT_H

#include "module/base.h"
#include "conf/consts.h"



//! Число точек для вычисления пересечения нуля.
#define ZERO_CROSS_DETECT_POINTS 2
//! Расстояние между точками для вычисления пересечения нуля, в семплах.
#define ZERO_CROSS_DETECT_SAMPLES_DISTANCE (CONF_PERIOD_SAMPLES / 16)
//! Количество усредняемых семплов.
#define ZERO_CROSS_DETECT_SAMPLES_NUMBER (CONF_PERIOD_SAMPLES / 8)
// Размер буфера в семплах.
#define ZERO_CROSS_DETECT_BUF_LEN (\
        ((ZERO_CROSS_DETECT_POINTS-1) * ZERO_CROSS_DETECT_SAMPLES_DISTANCE+1) +\
        (ZERO_CROSS_DETECT_SAMPLES_NUMBER-1)\
    )
//! Минимальное число накомпленных семплов для повторного детекта.
#define ZERO_CROSS_DETECT_SAMPLES_MIN (CONF_PERIOD_SAMPLES / 4) //_DEFAULT
//! Период дискретизации по-умолчанию.
#define ZERO_CROSS_DETECT_SAMPLES_PERIOD_DEFAULT (IQ24(1.0/(CONF_SAMPLE_RATE)))


//! Перечисление возможных бит управления.
enum _E_Zero_Cross_Detect_Control {
    ZERO_CROSS_DETECT_CONTROL_NONE = CONTROL_NONE,    //!< ZERO_CROSS_DETECT_CONTROL_NONE
    ZERO_CROSS_DETECT_CONTROL_ENABLE = CONTROL_ENABLE,//!< ZERO_CROSS_DETECT_CONTROL_ENABLE
};

//! Перечисление возможных бит статуса.
enum _E_Zero_Cross_Detect_Status {
    ZERO_CROSS_DETECT_STATUS_NONE = STATUS_NONE,
    ZERO_CROSS_DETECT_STATUS_VALID = STATUS_VALID,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Zero_Cross_Detect M_zero_cross_detect;

//! Структура модуля.
struct _S_Zero_Cross_Detect {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_value; //!< Текущее значение сигнала.
    // Выходные данные.
    strobe_t out_zero_cross; //!< Строб пересечения нуля.
    reg_iq24_t out_period; //!< Период.
    reg_iq24_t out_freq; //!< Частота.
    // Параметры.
    // Регистры.
    reg_iq24_t r_samples_period; //!< Период дискретизации.
    //reg_u32_t r_samples_min; //!< Минимальное число накомленных семплов до следующего детекта пересечения нуля.
    // Методы.
    METHOD_INIT(M_zero_cross_detect);
    METHOD_DEINIT(M_zero_cross_detect);
    METHOD_CALC(M_zero_cross_detect);
    // Коллбэки.
    // Внутренние данные.
    iq24_t m_buf[ZERO_CROSS_DETECT_BUF_LEN]; //!< Буфер для семплов.
    uint32_t m_count; //!< Число обработанных точек с прошлого пересечения нуля.
    iq24_t m_period_sum; //!< Сумма периодов семплов с прошлого пересечения нуля.
    flag_t m_zero_cross; //!< Текущий флаг пересечения нуля.
    iq24_t m_weight; //!< Текущее положение пересечения нуля между точками.
    iq24_t m_old_period; //!< Предыдущее значение периода.
    flag_t m_old_zero_cross; //!< Флаг предыдущего детекта пересечения нуля.
};

EXTERN METHOD_INIT_PROTO(M_zero_cross_detect);
EXTERN METHOD_DEINIT_PROTO(M_zero_cross_detect);
EXTERN METHOD_CALC_PROTO(M_zero_cross_detect);

#define ZERO_CROSS_DETECT_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_zero_cross */\
        0, /* out_period */\
        0, /* out_freq */\
        /* Параметры */\
        /* Регистры */\
        ZERO_CROSS_DETECT_SAMPLES_PERIOD_DEFAULT, /* r_samples_period */\
        /*ZERO_CROSS_DETECT_SAMPLES_MIN_DEFAULT,*/ /* r_samples_min */\
        /* Методы */\
        METHOD_INIT_PTR(M_zero_cross_detect), METHOD_DEINIT_PTR(M_zero_cross_detect),\
        METHOD_CALC_PTR(M_zero_cross_detect),\
        /* Коллбэки */\
        /* Внутренние данные */\
        {0}, /* m_buf */\
        0, /* m_count */\
        0, /* m_period_sum */\
        0, /* m_zero_cross */\
        0, /* m_weight */\
        0, /* m_old_period */\
        0, /* m_old_zero_cross */\
    }

#endif /* ZERO_CROSS_DETECT_H */
