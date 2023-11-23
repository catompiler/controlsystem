#ifndef MEAN3_H
#define MEAN3_H

#include "module/base.h"


//! Число усредняемых значений.
#define MEAN3_COUNT 3

//! Перечисление возможных бит управления.
enum _E_Mean3_Control {
    MEAN3_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Mean3_Status {
    MEAN3_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mean3 M_mean3;

//! Структура модуля.
struct _S_Mean3 {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value[MEAN3_COUNT]; //!< Усредняемые значения.
    // Выходные данные.
    iql_t out_value; //!< Среднее значение.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_mean3);
    METHOD_DEINIT(M_mean3);
    METHOD_CALC(M_mean3);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_mean3);
EXTERN METHOD_DEINIT_PROTO(M_mean3);
EXTERN METHOD_CALC_PROTO(M_mean3);

#define MEAN3_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_mean3), METHOD_DEINIT_PTR(M_mean3),\
        METHOD_CALC_PTR(M_mean3),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MEAN3_H */
