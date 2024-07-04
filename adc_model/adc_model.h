#ifndef ADC_MODEL_H
#define ADC_MODEL_H

#include "module/base.h"
#include "conf/conf.h"
#include "clarke/clarke_inv.h"
#include <stdint.h>


/*
 * Параметры семплирования.
 */
//#define ADC_MODEL_AC_FREQ (50)
#define ADC_MODEL_SAMPLES_PER_PERIOD (CONF_PERIOD_SAMPLES)
//#define ADC_MODEL_SAMPLES_FREQ (ADC_MODEL_AC_FREQ * ADC_MODEL_SAMPLES_PER_PERIOD)
//#define ADC_MODEL_SAMPLES_PERIOD_S (0)
//#define ADC_MODEL_SAMPLES_PERIOD_US (1000000 / ADC_MODEL_SAMPLES_FREQ)
//#define ADC_MODEL_SAMPLES_PERIOD_NS (ADC_MODEL_SAMPLES_PERIOD_US * 1000)
#define ADC_MODEL_SAMPLE_ANGLE_PU ((IQ24_2PI_PU + ADC_MODEL_SAMPLES_PER_PERIOD - 1) / ADC_MODEL_SAMPLES_PER_PERIOD)

/*
 * Общие параметры.
 */
#define ADC_MODEL_BITS 12
#define ADC_MODEL_BASE (1<<ADC_MODEL_BITS)
#define ADC_MODEL_OFFSET (ADC_MODEL_BASE / 2)

/*
 * Сетевое напряжение.
 */
#define ADC_MODEL_MAINS_U_PHASE (IQ24_2PI_PU / 31)
#define ADC_MODEL_MAINS_U_OFFSET (ADC_MODEL_OFFSET)
#define ADC_MODEL_MAINS_U_GAIN_F (0.271)
#define ADC_MODEL_MAINS_U_AMPL (106.1) //75 * sqrt(2)
#define ADC_MODEL_MAINS_U_GAIN (IQ24(ADC_MODEL_MAINS_U_GAIN_F))
#define ADC_MODEL_MAINS_U_AMPL_RAW ((int32_t)(1.0 / ADC_MODEL_MAINS_U_GAIN_F * ADC_MODEL_MAINS_U_AMPL))//275
#define ADC_MODEL_MAINS_RAW_MIN 0
#define ADC_MODEL_MAINS_RAW_MAX 4095

/*
 * Напряжение статора.
 */
#define ADC_MODEL_STATOR_U_PHASE (IQ24_2PI_PU / 17)
#define ADC_MODEL_STATOR_U_OFFSET (ADC_MODEL_OFFSET)
#define ADC_MODEL_STATOR_U_GAIN_F (8.1)
#define ADC_MODEL_STATOR_U_AMPL (8910) //6300 * sqrt(2)
#define ADC_MODEL_STATOR_U_GAIN (IQ24(ADC_MODEL_STATOR_U_GAIN_F))
#define ADC_MODEL_STATOR_U_AMPL_RAW ((int32_t)(1.0 / ADC_MODEL_STATOR_U_GAIN_F * ADC_MODEL_STATOR_U_AMPL))
#define ADC_MODEL_STATOR_RAW_MIN 0
#define ADC_MODEL_STATOR_RAW_MAX 4095



//! Перечисление возможных бит управления.
enum _E_Adc_Model_Control {
    ADC_MODEL_CONTROL_NONE = CONTROL_NONE,
    //ADC_MODEL_CONTROL_ENABLE = CONTROL_ENABLE, //!< Разрешает работу.
};

//! Перечисление возможных бит статуса.
enum _E_Adc_Model_Status {
    ADC_MODEL_STATUS_NONE = STATUS_NONE,
    ADC_MODEL_STATUS_VALID = STATUS_VALID, //!< Устанавливается после первого преобразования.
};


typedef struct _S_Adc_Model M_adc_model;

struct _S_Adc_Model {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    reg_iq24_t in_U_scale; //!< Масштабирование напряжения фаз основного ввода.
    reg_iq24_t in_F_scale; //!< Масштабирование частоты фаз основного ввода.
    reg_iq24_t in_s_U_scale; //!< Масштабирование напряжения фаз статора.
    reg_iq24_t in_s_F_scale; //!< Масштабирование частоты фаз статора.
    // Выходные данные.
    // Напряжения сети.
    reg_u32_t out_Ua_raw; //!< Мнговенное напряжение фазы A (сырое).
    reg_u32_t out_Ub_raw; //!< Мнговенное напряжение фазы B (сырое).
    reg_u32_t out_Uc_raw; //!< Мнговенное напряжение фазы C (сырое).
    reg_iq24_t out_Ua; //!< Мнговенное напряжение фазы A.
    reg_iq24_t out_Ub; //!< Мнговенное напряжение фазы B.
    reg_iq24_t out_Uc; //!< Мнговенное напряжение фазы C.
    // Напряжения статора.
    reg_u32_t out_s_Ua_raw; //!< Мнговенное напряжение фазы A статора (сырое).
    reg_u32_t out_s_Ub_raw; //!< Мнговенное напряжение фазы B статора (сырое).
    reg_u32_t out_s_Uc_raw; //!< Мнговенное напряжение фазы C статора (сырое).
    reg_iq24_t out_s_Ua; //!< Мнговенное напряжение фазы A статора.
    reg_iq24_t out_s_Ub; //!< Мнговенное напряжение фазы B статора.
    reg_iq24_t out_s_Uc; //!< Мнговенное напряжение фазы C статора.
    // Параметры.
    // Напряжения сети.
    reg_iq24_t p_Ua_gain;   //!< Коэффициент усиления напряжения фазы A.
    reg_u32_t  p_Ua_offset; //!< Смещеие АЦП напряжения фазы A.
    reg_iq24_t p_Ub_gain;   //!< Коэффициент усиления напряжения фазы B.
    reg_u32_t  p_Ub_offset; //!< Смещеие АЦП напряжения фазы B.
    reg_iq24_t p_Uc_gain;   //!< Коэффициент усиления напряжения фазы C.
    reg_u32_t  p_Uc_offset; //!< Смещеие АЦП напряжения фазы C.
    // Напряжения статора.
    reg_iq24_t p_s_Ua_gain;   //!< Коэффициент усиления напряжения фазы A статора.
    reg_u32_t  p_s_Ua_offset; //!< Смещеие АЦП напряжения фазы A статора.
    reg_iq24_t p_s_Ub_gain;   //!< Коэффициент усиления напряжения фазы B статора.
    reg_u32_t  p_s_Ub_offset; //!< Смещеие АЦП напряжения фазы B статора.
    reg_iq24_t p_s_Uc_gain;   //!< Коэффициент усиления напряжения фазы C статора.
    reg_u32_t  p_s_Uc_offset; //!< Смещеие АЦП напряжения фазы C статора.
    // Регистры.
    // Методы.
    METHOD_INIT(M_adc_model);
    METHOD_DEINIT(M_adc_model);
    METHOD_CALC(M_adc_model);
    METHOD_IDLE(M_adc_model);
    // Коллбэки.
    CALLBACK(on_conversion);
    // Внутренние данные.
    iq24_t m_mains_acnt; //!< Счётчик электрического угла фаз ввода.
    iq24_t m_stator_acnt; //!< Счётчик электрического угла статора.
    // Напряжения сети.
    iq24_t m_Ua_gain; //!< Суммарное усиление напряжения фазы A.
    iq24_t m_Ub_gain; //!< Суммарное усиление напряжения фазы B.
    iq24_t m_Uc_gain; //!< Суммарное усиление напряжения фазы C.
    // Напряжения статора.
    iq24_t m_s_Ua_gain; //!< Суммарное усиление напряжения фазы A статора.
    iq24_t m_s_Ub_gain; //!< Суммарное усиление напряжения фазы B статора.
    iq24_t m_s_Uc_gain; //!< Суммарное усиление напряжения фазы C статора.
    /* Внутренние модули */\
    M_clarke_inv m_clarke_inv; //!< Модуль преобразования Кларк для фаз основного ввода.
    M_clarke_inv m_s_clarke_inv; //!< Модуль преобразования Кларк для фаз статора.
};

EXTERN METHOD_INIT_PROTO(M_adc_model);
EXTERN METHOD_DEINIT_PROTO(M_adc_model);
EXTERN METHOD_CALC_PROTO(M_adc_model);
EXTERN METHOD_IDLE_PROTO(M_adc_model);

#define ADC_MODEL_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        IQ24(1.0), /* in_mains_U_scale */\
        IQ24(1.0), /* in_mains_F_scale */\
        IQ24(1.0), /* in_stator_U_scale */\
        IQ24(1.0), /* in_stator_F_scale */\
        /* Выходные данные */\
        /* Напряжения сети */\
        0, 0, 0, /* raw Uabc */\
        0, 0, 0, /* Uabc */\
        /* Напряжения статора */\
        0, 0, 0, /* raw s Uabc */\
        0, 0, 0, /* s Uabc */\
        /* Параметры */\
        /* Напряжения сети */\
        ADC_MODEL_MAINS_U_GAIN, ADC_MODEL_MAINS_U_OFFSET, /* Усиление и смещение Ua */\
        ADC_MODEL_MAINS_U_GAIN, ADC_MODEL_MAINS_U_OFFSET, /* Усиление и смещение Ub */\
        ADC_MODEL_MAINS_U_GAIN, ADC_MODEL_MAINS_U_OFFSET, /* Усиление и смещение Uc */\
        /* Напряжения статора */\
        ADC_MODEL_STATOR_U_GAIN, ADC_MODEL_STATOR_U_OFFSET, /* Усиление и смещение Ua статора */\
        ADC_MODEL_STATOR_U_GAIN, ADC_MODEL_STATOR_U_OFFSET, /* Усиление и смещение Ub статора */\
        ADC_MODEL_STATOR_U_GAIN, ADC_MODEL_STATOR_U_OFFSET, /* Усиление и смещение Uc статора */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_adc_model), METHOD_DEINIT_PTR(M_adc_model),\
        METHOD_CALC_PTR(M_adc_model), METHOD_IDLE_PTR(M_adc_model),\
        /* Коллбэки */\
        CALLBACK_DEFAULTS, /* on_conversion */\
        /* Внутренние данные */\
        0, /* m_mains_acnt */\
        0, /* m_stator_acnt */\
        0, 0, 0, /* gain Uabc */\
        0, 0, 0, /* gain s Uabc */\
        /* Внутренние модули */\
        CLARKE_INV_DEFAULTS,\
        CLARKE_INV_DEFAULTS,\
    }


#endif //ADC_MODEL_H
