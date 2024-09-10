#ifndef SYS_CALC_H
#define SYS_CALC_H

#include "module/base.h"

//! Перечисление возможных бит управления.
enum _E_Sys_Calc_Control {
    SYS_CALC_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Sys_Calc_Status {
    SYS_CALC_STATUS_NONE = STATUS_NONE,
};

/*
 * Методы.
 */
// Метод calc_for_phc().
// Вычисление измерений напряжений и их фаз для СИФУ.
#define SYS_CALC_METHOD_CALC_FOR_PHC_M_NAME calc_for_phc
#define SYS_CALC_METHOD_CALC_FOR_PHC_RET void
#define SYS_CALC_METHOD_CALC_FOR_PHC(MOD_TYPE)               METHOD(MOD_TYPE, SYS_CALC_METHOD_CALC_FOR_PHC_M_NAME, SYS_CALC_METHOD_CALC_FOR_PHC_RET)
#define SYS_CALC_METHOD_CALC_FOR_PHC_PTR(MOD_NAME)           METHOD_PTR(MOD_NAME, SYS_CALC_METHOD_CALC_FOR_PHC_M_NAME)
#define SYS_CALC_METHOD_CALC_FOR_PHC_PROTO(MOD_NAME)         METHOD_PROTO(MOD_NAME, SYS_CALC_METHOD_CALC_FOR_PHC_M_NAME, SYS_CALC_METHOD_CALC_FOR_PHC_RET)
#define SYS_CALC_METHOD_CALC_FOR_PHC_IMPL(MOD_NAME, THIS)    METHOD_IMPL(MOD_NAME, THIS, SYS_CALC_METHOD_CALC_FOR_PHC_M_NAME, SYS_CALC_METHOD_CALC_FOR_PHC_RET)
#define SYS_CALC_CALC_FOR_PHC(MOD)                            CALL(MOD, SYS_CALC_METHOD_CALC_FOR_PHC_M_NAME)

// Метод calc_for_model().
// Вычисление измерений напряжений ячейки (нужно отдельно для модели).
#define SYS_CALC_METHOD_CALC_FOR_MODEL_M_NAME calc_for_model
#define SYS_CALC_METHOD_CALC_FOR_MODEL_RET void
#define SYS_CALC_METHOD_CALC_FOR_MODEL(MOD_TYPE)               METHOD(MOD_TYPE, SYS_CALC_METHOD_CALC_FOR_MODEL_M_NAME, SYS_CALC_METHOD_CALC_FOR_MODEL_RET)
#define SYS_CALC_METHOD_CALC_FOR_MODEL_PTR(MOD_NAME)           METHOD_PTR(MOD_NAME, SYS_CALC_METHOD_CALC_FOR_MODEL_M_NAME)
#define SYS_CALC_METHOD_CALC_FOR_MODEL_PROTO(MOD_NAME)         METHOD_PROTO(MOD_NAME, SYS_CALC_METHOD_CALC_FOR_MODEL_M_NAME, SYS_CALC_METHOD_CALC_FOR_MODEL_RET)
#define SYS_CALC_METHOD_CALC_FOR_MODEL_IMPL(MOD_NAME, THIS)    METHOD_IMPL(MOD_NAME, THIS, SYS_CALC_METHOD_CALC_FOR_MODEL_M_NAME, SYS_CALC_METHOD_CALC_FOR_MODEL_RET)
#define SYS_CALC_CALC_FOR_MODEL(MOD)                            CALL(MOD, SYS_CALC_METHOD_CALC_FOR_MODEL_M_NAME)


//! Предварительная декларация типа модуля.
typedef struct _S_Sys_Calc M_sys_calc;

//! Структура модуля.
struct _S_Sys_Calc {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_sys_calc);
    METHOD_DEINIT(M_sys_calc);
    //! Вычисляет мгновенное напряжение, амплитуду и фазу сетевого напряжения для СИФУ.
    SYS_CALC_METHOD_CALC_FOR_PHC(M_sys_calc);
    //! Вычисляет мгновенное напряжение ячейки.
    SYS_CALC_METHOD_CALC_FOR_MODEL(M_sys_calc);
    METHOD_CALC(M_sys_calc);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_sys_calc);
EXTERN METHOD_DEINIT_PROTO(M_sys_calc);
EXTERN SYS_CALC_METHOD_CALC_FOR_PHC_PROTO(M_sys_calc);
EXTERN SYS_CALC_METHOD_CALC_FOR_MODEL_PROTO(M_sys_calc);
EXTERN METHOD_CALC_PROTO(M_sys_calc);

#define SYS_CALC_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_sys_calc), METHOD_DEINIT_PTR(M_sys_calc),\
        SYS_CALC_METHOD_CALC_FOR_PHC_PTR(M_sys_calc), SYS_CALC_METHOD_CALC_FOR_MODEL_PTR(M_sys_calc),\
        METHOD_CALC_PTR(M_sys_calc),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* SYS_CALC_H */
