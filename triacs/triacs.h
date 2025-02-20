#ifndef TRIACS_H
#define TRIACS_H

#include "module/base.h"
#include "phase3_control/phase3_control.h"
#include <assert.h>


//! Перечисление возможных бит управления.
enum _E_Triacs_Control {
    TRIACS_CONTROL_NONE = CONTROL_NONE,
    TRIACS_CONTROL_ENABLE = CONTROL_ENABLE,
    TRIACS_CONTROL_FIRE = CONTROL_START,
    TRIACS_CONTROL_CLOSE = CONTROL_STOP,
};

//! Перечисление возможных бит статуса.
enum _E_Triacs_Status {
    TRIACS_STATUS_NONE = STATUS_NONE,
};


//! Длительность импульса отпирания основных тиристоров, эл. градусов.
#define TRIACS_MAINS_PULSE_ANGLE_F 9.0

//! Коэффициент заполнения.
#define TRIACS_MAINS_PULSE_DUTY_CYCLE_F 0.5

//! Длительность одного импульса отпирания основных тиристоров, эл. град.
#define TRIACS_MAINS_SINGLE_PULSE_ANGLE_F ( (TRIACS_MAINS_PULSE_ANGLE_F) / (TRIACS_MAINS_PULSE_DUTY_CYCLE_F) )

//! Длительность одного импульса отпирания основных тиристоров, периодические единицы, в формате IQ.
#define TRIACS_MAINS_SINGLE_PULSE_ANGLE_PU ( IQ24((TRIACS_MAINS_SINGLE_PULSE_ANGLE_F) / 360.0) )

static_assert((360.0 / TRIACS_MAINS_SINGLE_PULSE_ANGLE_F) < 127.0, "IQ24 overflow!");

//! Длительность одного импульса отпирания основных тиристоров, инвертированное значение, периодические единицы, в формате IQ.
#define TRIACS_MAINS_SINGLE_PULSE_ANGLE_INV_PU ( IQ24(360.0 / (TRIACS_MAINS_SINGLE_PULSE_ANGLE_F)) )


//! Максимальный угол "гребёнки"
#define TRIACS_MAINS_PULSE_TRAIN_ANGLE_MAX_F 60.0

//! Минимальное число импульсов отпирания основных тиристоров.
#define TRIACS_MAINS_PULSES_MIN 1
//! Максимальное число импульсов отпирания основных тиристоров.
//#define TRIACS_MAINS_PULSES_MAX ( (uint32_t)((TRIACS_MAINS_PULSE_TRAIN_ANGLE_MAX_F) / (TRIACS_MAINS_SINGLE_PULSE_ANGLE_F)) )
#define TRIACS_MAINS_PULSES_MAX 1

//! Общая длительность отпирания основных тиристоров, эл. град.
#define TRIACS_MAINS_ALL_PULSES_ANGLE_F ( (TRIACS_MAINS_PULSE_ANGLE_F) / (TRIACS_MAINS_PULSE_DUTY_CYCLE_F) * (TRIACS_MAINS_PULSES) )


//! Число тиристоров.
#define TRIACS_MAINS_KEYS_COUNT (PHASE3_CONTROL_KEYS_COUNT)


//! Предварительная декларация типа модуля.
typedef struct _S_Triacs M_triacs;

//! Структура модуля.
struct _S_Triacs {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_u32_t in_control[TRIACS_MAINS_KEYS_COUNT]; //!< Слова управления тиристорами.
    reg_iq24_t in_control_delay_angle; //!< Угол до импульса управления, в периодических единицах.
    reg_iq24_t in_control_max_duration_angle; //!< Максимальная продолжительность (угол) управления, в периодических единицах.
    // Выходные данные.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_triacs);
    METHOD_DEINIT(M_triacs);
    METHOD_CALC(M_triacs);
    METHOD_CONTROL(M_triacs);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_triacs);
EXTERN METHOD_DEINIT_PROTO(M_triacs);
EXTERN METHOD_CALC_PROTO(M_triacs);
EXTERN METHOD_CONTROL_PROTO(M_triacs);

#define TRIACS_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        {0}, /* in_control */\
        0, /* in_control_delay_angle */\
        0, /* in_control_max_duration_angle */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_triacs), METHOD_DEINIT_PTR(M_triacs),\
        METHOD_CALC_PTR(M_triacs), METHOD_CONTROL_PTR(M_triacs),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* TRIACS_H */
