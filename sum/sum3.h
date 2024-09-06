#ifndef SUM3_H
#define SUM3_H

#include "module/base.h"


//! Число усредняемых значений.
#define SUM3_COUNT 3

//! Перечисление возможных бит управления.
enum _E_Sum3_Control {
    SUM3_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Sum3_Status {
    SUM3_STATUS_NONE = STATUS_NONE,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Sum3 M_sum3;

//! Структура модуля.
struct _S_Sum3 {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    iql_t in_value[SUM3_COUNT]; //!< Усредняемые значения.
    // Выходные данные.
    iql_t out_value; //!< Среднее значение.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_sum3);
    METHOD_DEINIT(M_sum3);
    METHOD_CALC(M_sum3);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_sum3);
EXTERN METHOD_DEINIT_PROTO(M_sum3);
EXTERN METHOD_CALC_PROTO(M_sum3);

#define SUM3_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_value */\
        /* Выходные данные */\
        0, /* out_value */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_sum3), METHOD_DEINIT_PTR(M_sum3),\
        METHOD_CALC_PTR(M_sum3),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* SUM3_H */
