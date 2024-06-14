#ifndef POWER_H
#define POWER_H

#include "module/base.h"
#include "conf/consts.h"


//! Число семплов для сдвига фазы тока на pi/2.
#define POWER_PI2_LEN (CONF_PERIOD_SAMPLES / 4)
// Вывод предупреждения если число точек за период не делится ровно на 4.
#if (POWER_PI2_LEN * 4 != CONF_PERIOD_SAMPLES)
#warning The number of points per period is not a multiple of 4!
#endif


//! Длина массива данных для вычисления мощностей.
#define POWER_LEN (CONF_PERIOD_SAMPLES)


//! Перечисление возможных бит управления.
enum _E_Power_Control {
    POWER_CONTROL_NONE = CONTROL_NONE,
    POWER_CONTROL_ENABLE = CONTROL_ENABLE,
};

//! Перечисление возможных бит статуса.
enum _E_Power_Status {
    POWER_STATUS_NONE = STATUS_NONE,
    POWER_STATUS_VALID = STATUS_VALID,
};

//! Предварительная декларация типа модуля.
typedef struct _S_Power M_power;

//! Структура модуля.
struct _S_Power {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_U; //!< Мгновенное значение напряжения.
    reg_iq24_t in_I; //!< Мгновенное значение тока.
    reg_iq24_t in_rms_U; //!< Действующее значение напряжения.
    reg_iq24_t in_rms_I; //!< Действующее значение тока.
    // Выходные данные.
    reg_iq24_t out_S; //!< Полная мощность.
    reg_iq24_t out_P; //!< Активная мощность.
    reg_iq24_t out_Q; //!< Реактивная мощность.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_power);
    METHOD_DEINIT(M_power);
    METHOD_CALC(M_power);
    // Коллбэки.
    // Внутренние данные.
    // Активная мощность.
    uint32_t m_p_count; //!< Число записанных данных.
    uint32_t m_p_put_index; //!< Индекс записи данных.
    liq24_t m_p_data[POWER_LEN]; //!< Буфер для вычисления активной мощности.
    liq24_t m_p_sum; //!< Текущая сумма.
    // Реактивная мощность.
    // Буфер для сдвига тока.
    uint32_t m_uz_put_index; //!< Индекс записи данных.
    iq24_t m_uz_data[POWER_PI2_LEN]; //!< Буфер для сдвига фазы тока на pi/2.
    // Данные для вычисления реактивной мощности.
    uint32_t m_q_count; //!< Число записанных данных.
    uint32_t m_q_put_index; //!< Индекс записи данных.
    liq24_t m_q_data[POWER_LEN]; //!< Буфер для вычисления реактивной мощности.
    liq24_t m_q_sum; //!< Текущая сумма.
};

EXTERN METHOD_INIT_PROTO(M_power);
EXTERN METHOD_DEINIT_PROTO(M_power);
EXTERN METHOD_CALC_PROTO(M_power);

#define POWER_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_U */\
        0, /* in_I */\
        0, /* in_rms_U */\
        0, /* in_rms_I */\
        /* Выходные данные */\
        0, /* out_S */\
        0, /* out_P */\
        0, /* out_Q */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_power), METHOD_DEINIT_PTR(M_power),\
        METHOD_CALC_PTR(M_power),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_p_count */\
        0, /* m_p_put_index */\
        {0}, /* m_data_P */\
        0, /* m_p_sum */\
        0, /* m_uz_put_index */\
        {0}, /* m_data_U_z_pi2 */\
        0, /* m_q_count */\
        0, /* m_q_put_index */\
        {0}, /* m_data_Q */\
        0, /* m_q_sum */\
    }

#endif /* POWER_H */
