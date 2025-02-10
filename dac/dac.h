#ifndef DAC_H
#define DAC_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Dac_Control {
    DAC_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Dac_Status {
    DAC_STATUS_NONE = STATUS_NONE,
};

//! Число каналов ЦАП.
#define DAC_CHANNELS 2

// Разрешённые каналы.
// Канал 0.
#ifndef DAC_CHANNEL0_ENABLED
#define DAC_CHANNEL0_ENABLED 1
#endif
// Канал 1.
#ifndef DAC_CHANNEL1_ENABLED
#define DAC_CHANNEL1_ENABLED 0
#endif

//! Предварительная декларация типа модуля.
typedef struct _S_Dac M_dac;

//! Структура модуля.
struct _S_Dac {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_value[DAC_CHANNELS];
    // Выходные данные.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_dac);
    METHOD_DEINIT(M_dac);
    METHOD_CALC(M_dac);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_dac);
EXTERN METHOD_DEINIT_PROTO(M_dac);
EXTERN METHOD_CALC_PROTO(M_dac);

#define DAC_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_value */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_dac), METHOD_DEINIT_PTR(M_dac),\
        METHOD_CALC_PTR(M_dac),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* DAC_H */
