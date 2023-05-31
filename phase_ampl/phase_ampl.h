#ifndef PHASE_AMPL_H
#define PHASE_AMPL_H

#include "module/base.h"
#include "iqmath/iq_types.h"
#include "conf/conf.h"


/*
 * Формат данных буфера - IQ14.
 */
//! Число целых бит данных в буфере.
#define PHASE_AMPL_DATA_INT_BITS 1
//! Число дробных бит данных в буфере.
#define PHASE_AMPL_DATA_FRACT_BITS 14
//! Номер бита для сатурации.
#define PHASE_AMPL_DATA_SAT_BIT (PHASE_AMPL_DATA_INT_BITS +\
                                     PHASE_AMPL_DATA_FRACT_BITS + 1)

//! Тип данных буфера.
typedef iq14s_t phase_ampl_data_t;
//! Размер одного семпла в байтах.
#define PHASE_AMPL_SAMPLE_SIZE (sizeof(phase_ampl_data_t))


//! Число семплов за период.
#define PHASE_AMPL_SAMPLES_COUNT (CONF_PERIOD_SAMPLES)
//! Размер блока в байтах (для оптимизации сдвига буфера).
#define PHASE_AMPL_BLOCK_SIZE 8
//! Размер блока в семплах.
#define PHASE_AMPL_BLOCK_LEN ((PHASE_AMPL_BLOCK_SIZE)/(PHASE_AMPL_SAMPLE_SIZE))
//! Размер буфера.
#define PHASE_AMPL_LEN ((PHASE_AMPL_SAMPLES_COUNT)+(PHASE_AMPL_BLOCK_LEN))


//! Перечисление возможных бит управления.
enum _E_Phase_Ampl_Control {
    PHASE_AMPL_CONTROL_NONE = CONTROL_NONE,//!< PHASE_AMPL_CONTROL_NONE
};

//! Перечисление возможных бит статуса.
enum _E_Phase_Ampl_Status {
    PHASE_AMPL_STATUS_NONE = STATUS_NONE,
    PHASE_AMPL_STATUS_VALID = STATUS_VALID
};

typedef struct _S_Phase_Ampl M_phase_ampl;

struct _S_Phase_Ampl {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_value;
    // Выходные данные.
    //reg_iq24_t out_value;
    reg_iq24_t out_phase;
    reg_iq24_t out_ampl;
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_phase_ampl);
    METHOD_DEINIT(M_phase_ampl);
    METHOD_CALC(M_phase_ampl);
    // Коллбэки.
    // Внутренние данные.
    uint32_t m_count; //!< Число записанных данных.
    uint32_t m_get_index; //!< Индекс чтения данных.
    uint32_t m_put_index; //!< Индекс записи данных.
    phase_ampl_data_t m_data[PHASE_AMPL_LEN] ALIGNED4; //!< Данные.
};

EXTERN METHOD_INIT_PROTO(M_phase_ampl);
EXTERN METHOD_DEINIT_PROTO(M_phase_ampl);
EXTERN METHOD_CALC_PROTO(M_phase_ampl);

#define PHASE_AMPL_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, /* in_value */\
        /* Выходные данные */\
        /*0,*/ /* out_value */\
        0, /* out_phase */\
        0, /* out_ampl */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_phase_ampl), METHOD_DEINIT_PTR(M_phase_ampl),\
        METHOD_CALC_PTR(M_phase_ampl),\
        /* Коллбэки */\
        /* Внутренние данные */\
        0, /* m_count */\
        0, /* m_get_index */\
        0, /* m_put_index */\
        {0}, /* m_data */\
    }

#endif /* PHASE_AMPL_H */
