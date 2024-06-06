#ifndef MEAS_H
#define MEAS_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Meas_Control {
    MEAS_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Meas_Status {
    MEAS_STATUS_NONE = STATUS_NONE,
};

/*
 * Методы.
 */
// Метод calc_for_phc().
// Вычисление измерений напряжений и их фаз для СИФУ.
#define MEAS_METHOD_CALC_FOR_PHC_M_NAME calc_for_phc
#define MEAS_METHOD_CALC_FOR_PHC_RET void
#define MEAS_METHOD_CALC_FOR_PHC(MOD_TYPE)               METHOD(MOD_TYPE, MEAS_METHOD_CALC_FOR_PHC_M_NAME, MEAS_METHOD_CALC_FOR_PHC_RET)
#define MEAS_METHOD_CALC_FOR_PHC_PTR(MOD_NAME)           METHOD_PTR(MOD_NAME, MEAS_METHOD_CALC_FOR_PHC_M_NAME)
#define MEAS_METHOD_CALC_FOR_PHC_PROTO(MOD_NAME)         METHOD_PROTO(MOD_NAME, MEAS_METHOD_CALC_FOR_PHC_M_NAME, MEAS_METHOD_CALC_FOR_PHC_RET)
#define MEAS_METHOD_CALC_FOR_PHC_IMPL(MOD_NAME, THIS)    METHOD_IMPL(MOD_NAME, THIS, MEAS_METHOD_CALC_FOR_PHC_M_NAME, MEAS_METHOD_CALC_FOR_PHC_RET)
#define MEAS_CALC_FOR_PHC(MOD)                            CALL(MOD, MEAS_METHOD_CALC_FOR_PHC_M_NAME)

// Метод calc_for_model().
// Вычисление измерений напряжений ячейки (нужно отдельно для модели).
#define MEAS_METHOD_CALC_FOR_MODEL_M_NAME calc_for_model
#define MEAS_METHOD_CALC_FOR_MODEL_RET void
#define MEAS_METHOD_CALC_FOR_MODEL(MOD_TYPE)               METHOD(MOD_TYPE, MEAS_METHOD_CALC_FOR_MODEL_M_NAME, MEAS_METHOD_CALC_FOR_MODEL_RET)
#define MEAS_METHOD_CALC_FOR_MODEL_PTR(MOD_NAME)           METHOD_PTR(MOD_NAME, MEAS_METHOD_CALC_FOR_MODEL_M_NAME)
#define MEAS_METHOD_CALC_FOR_MODEL_PROTO(MOD_NAME)         METHOD_PROTO(MOD_NAME, MEAS_METHOD_CALC_FOR_MODEL_M_NAME, MEAS_METHOD_CALC_FOR_MODEL_RET)
#define MEAS_METHOD_CALC_FOR_MODEL_IMPL(MOD_NAME, THIS)    METHOD_IMPL(MOD_NAME, THIS, MEAS_METHOD_CALC_FOR_MODEL_M_NAME, MEAS_METHOD_CALC_FOR_MODEL_RET)
#define MEAS_CALC_FOR_MODEL(MOD)                            CALL(MOD, MEAS_METHOD_CALC_FOR_MODEL_M_NAME)


//! Предварительная декларация типа модуля.
typedef struct _S_Meas M_meas;

//! Структура модуля.
struct _S_Meas {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_meas);
    METHOD_DEINIT(M_meas);
    //! Вычисляет мгновенное напряжение, амплитуду и фазу сетевого напряжения для СИФУ.
    MEAS_METHOD_CALC_FOR_PHC(M_meas);
    //! Вычисляет мгновенное напряжение ячейки.
    MEAS_METHOD_CALC_FOR_MODEL(M_meas);
    METHOD_CALC(M_meas);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_meas);
EXTERN METHOD_DEINIT_PROTO(M_meas);
EXTERN MEAS_METHOD_CALC_FOR_PHC_PROTO(M_meas);
EXTERN MEAS_METHOD_CALC_FOR_MODEL_PROTO(M_meas);
EXTERN METHOD_CALC_PROTO(M_meas);

#define MEAS_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_meas), METHOD_DEINIT_PTR(M_meas),\
        MEAS_METHOD_CALC_FOR_PHC_PTR(M_meas), MEAS_METHOD_CALC_FOR_MODEL_PTR(M_meas),\
        METHOD_CALC_PTR(M_meas),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* MEAS_H */
