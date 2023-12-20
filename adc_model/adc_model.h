#ifndef ADC_MODEL_H
#define ADC_MODEL_H

#include "module/base.h"
#include "conf/conf.h"
#include <stdint.h>


//#define ADC_MODEL_AC_FREQ (50)
#define ADC_MODEL_SAMPLES_PER_PERIOD (CONF_PERIOD_SAMPLES)
//#define ADC_MODEL_SAMPLES_FREQ (ADC_MODEL_AC_FREQ * ADC_MODEL_SAMPLES_PER_PERIOD)
//#define ADC_MODEL_SAMPLES_PERIOD_S (0)
//#define ADC_MODEL_SAMPLES_PERIOD_US (1000000 / ADC_MODEL_SAMPLES_FREQ)
//#define ADC_MODEL_SAMPLES_PERIOD_NS (ADC_MODEL_SAMPLES_PERIOD_US * 1000)

#define ADC_MODEL_BITS 12
#define ADC_MODEL_OFFSET 2048
#define ADC_MODEL_UPHASE_AMPL 275 /*1097*/ /* 400 */ //631 /* 230 */
//#define ADC_MODEL_HW_GAIN (IQ24(1.0))
//#define ADC_MODEL_HW_OFFSET (IQ24(0.5));
#define ADC_MODEL_SAMPLE_ANGLE_PU (IQ24_2PI_PU / ADC_MODEL_SAMPLES_PER_PERIOD)

// Vadc_in = ((U+ - U-) * Khw + OFFSET) * Kadc.
/*
 * Общие параметры.
 */
// Коэффициент преобразования АЦП, LSB/V.
#define ADC_MODEL_GAIN_LSB_V_F (4096.0/3.3)
/*
 * Сетевое напряжение.
 */
// Коэффициент преобразования сетевого напряжения к напряжению на входе АЦП, В/В.
#define ADC_MODEL_UPWR_ANALOG_GAIN_V_V_F (0.00156398104265402844)
// Смещение напряжения на входе АЦП, В.
#define ADC_MODEL_UPWR_ANALOG_OFFSET_F (1.65)
// Смещение АЦП, LSB.
#define ADC_MODEL_UPWR_OFFSET_I32 ((int32_t)(ADC_MODEL_UPWR_ANALOG_OFFSET_F * ADC_MODEL_GAIN_LSB_V_F))
// Коэффициент АЦП, LSB/V.
#define ADC_MODEL_UPWR_GAIN_LSB_V_IQ24 IQ24(ADC_MODEL_GAIN_LSB_V_F * ADC_MODEL_UPWR_ANALOG_GAIN_V_V_F)
// Коэффициент АЦП, V/LSB.
#define ADC_MODEL_UPWR_GAIN_V_LSB_IQ24 IQ24(1.0/(ADC_MODEL_GAIN_LSB_V_F * ADC_MODEL_UPWR_ANALOG_GAIN_V_V_F))



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
    reg_iq24_t in_U_scale; //!< Масштабирование напряжения фаз.
    reg_iq24_t in_F_scale; //!< Масштабирование частоты фаз.
    // Выходные данные.
    reg_u32_t out_Ua_raw; //!< Мнговенное напряжение фазы A (сырое).
    reg_u32_t out_Ub_raw; //!< Мнговенное напряжение фазы B (сырое).
    reg_u32_t out_Uc_raw; //!< Мнговенное напряжение фазы C (сырое).
    reg_iq24_t out_Ua; //!< Мнговенное напряжение фазы A.
    reg_iq24_t out_Ub; //!< Мнговенное напряжение фазы B.
    reg_iq24_t out_Uc; //!< Мнговенное напряжение фазы C.
    // Параметры.
    reg_iq24_t p_Ua_gain;   //!< Коэффициент усиления напряжения фазы A.
    reg_u32_t  p_Ua_offset; //!< Смещеие АЦП напряжения фазы A.
    reg_iq24_t p_Ub_gain;   //!< Коэффициент усиления напряжения фазы B.
    reg_u32_t  p_Ub_offset; //!< Смещеие АЦП напряжения фазы B.
    reg_iq24_t p_Uc_gain;   //!< Коэффициент усиления напряжения фазы C.
    reg_u32_t  p_Uc_offset; //!< Смещеие АЦП напряжения фазы C.
    // Регистры.
    // Методы.
    METHOD_INIT(M_adc_model);
    METHOD_DEINIT(M_adc_model);
    METHOD_CALC(M_adc_model);
    METHOD_IDLE(M_adc_model);
    // Коллбэки.
    CALLBACK(on_conversion);
    // Внутренние данные.
    iq24_t m_acnt; //!< Счётчик электрического угла.
    iq24_t m_Ua_gain; //!< Суммарное усиление напряжения фазы A.
    iq24_t m_Ub_gain; //!< Суммарное усиление напряжения фазы B.
    iq24_t m_Uc_gain; //!< Суммарное усиление напряжения фазы C.
};

EXTERN METHOD_INIT_PROTO(M_adc_model);
EXTERN METHOD_DEINIT_PROTO(M_adc_model);
EXTERN METHOD_CALC_PROTO(M_adc_model);
EXTERN METHOD_IDLE_PROTO(M_adc_model);

#define ADC_MODEL_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        IQ24(1.0), /* in_U_scale */\
        IQ24(1.0), /* in_F_scale */\
        /* Выходные данные */\
        0, 0, 0, /* raw Uabc */\
        0, 0, 0, /* Uabc */\
        /* Параметры */\
        ADC_MODEL_UPWR_GAIN_V_LSB_IQ24, ADC_MODEL_UPWR_OFFSET_I32, /* Усиление и смещение Ua */\
        ADC_MODEL_UPWR_GAIN_V_LSB_IQ24, ADC_MODEL_UPWR_OFFSET_I32, /* Усиление и смещение Ub */\
        ADC_MODEL_UPWR_GAIN_V_LSB_IQ24, ADC_MODEL_UPWR_OFFSET_I32, /* Усиление и смещение Uc */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_adc_model), METHOD_DEINIT_PTR(M_adc_model),\
        METHOD_CALC_PTR(M_adc_model), METHOD_IDLE_PTR(M_adc_model),\
        /* Коллбэки */\
        CALLBACK_DEFAULTS, /* on_conversion */\
        /* Внутренние данные */\
        0, /* m_acnt */\
        0, 0, 0 /* gain Uabc */\
    }


#endif //ADC_MODEL_H
