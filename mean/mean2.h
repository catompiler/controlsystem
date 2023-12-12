#ifndef MEAN2_H
#define MEAN2_H

#include "module/base.h"


//! Число усредняемых значений.
#define MEAN2_COUNT 2

//! Перечисление возможных бит управления.
enum _E_Mean2_Control {
    MEAN2_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Mean2_Status {
    MEAN2_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Mean2 M_mean2;

//! Структура модуля.
struct _S_Mean2 {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value[MEAN2_COUNT]; //!< Усредняемые значения.
    // Выходные данные.
    iql_t out_value; //!< Среднее значение.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_mean2);
    METHOD_DEINIT(M_mean2);
    METHOD_CALC(M_mean2);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_mean2);
EXTERN METHOD_DEINIT_PROTO(M_mean2);
EXTERN METHOD_CALC_PROTO(M_mean2);

#define MEAN2_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_mean2), METHOD_DEINIT_PTR(M_mean2),\
        METHOD_CALC_PTR(M_mean2),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MEAN2_H */
