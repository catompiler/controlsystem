#ifndef RMS_H
#define RMS_H

#include "module/base.h"
#include "conf/conf.h"
#include "defs/defs.h"
#include "iqmath/iq24.h"


//! Перечисление возможных бит управления.
enum _E_Rms_Control {
    RMS_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Rms_Status {
    RMS_STATUS_NONE = STATUS_NONE,
    RMS_STATUS_VALID = STATUS_VALID
};


//! Длина массива данных для вычисления RMS.
#define RMS_LEN (CONF_PERIOD_SAMPLES)


//! Предварительная декларация типа модуля.
typedef struct _S_Rms M_rms;

//! Структура модуля.
struct _S_Rms {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_value; //!< Входное значение.
    // Выходные данные.
    reg_iq24_t out_value; //!< Рассчитанное RMS.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_rms);
    METHOD_DEINIT(M_rms);
    METHOD_CALC(M_rms);
    // Коллбэки.
    // Внутренние данные.
    uint32_t m_count; //!< Число записанных данных.
    uint32_t m_put_index; //!< Индекс записи данных.
    iq24_t m_data[RMS_LEN] ALIGNED4; //!< Данные.
};

EXTERN METHOD_INIT_PROTO(M_rms);
EXTERN METHOD_DEINIT_PROTO(M_rms);
EXTERN METHOD_CALC_PROTO(M_rms);

#define RMS_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_rms), METHOD_DEINIT_PTR(M_rms),\
        METHOD_CALC_PTR(M_rms),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_count */\
        0, /* m_put_index */\
        {0}, /* m_data */\
    }

#endif /* RMS_H */
