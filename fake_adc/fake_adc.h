#ifndef FAKE_ADC_H
#define FAKE_ADC_H

#include "adc_timer/adc_timer.h"
#include "module/base.h"
#include <stdint.h>


//#define ADC_AC_FREQ (50)
#define ADC_SAMPLES_PER_PERIOD (ADC_TIMER_TICKS_PER_PERIOD) //(32)
//#define ADC_SAMPLES_FREQ (ADC_AC_FREQ * ADC_SAMPLES_PER_PERIOD)
//#define ADC_SAMPLES_PERIOD_S (0)
//#define ADC_SAMPLES_PERIOD_US (1000000 / ADC_SAMPLES_FREQ)
//#define ADC_SAMPLES_PERIOD_NS (ADC_SAMPLES_PERIOD_US * 1000)

#define ADC_BITS 12
#define ADC_OFFSET 2048
#define ADC_UPHASE_AMPL 631
//#define ADC_HW_GAIN (IQ24(1.0))
//#define ADC_HW_OFFSET (IQ24(0.5));
#define ADC_SAMPLE_ANGLE_PU (IQ24_2PI_PU / ADC_SAMPLES_PER_PERIOD)

// Vadc_in = ((U+ - U-) * Khw + OFFSET) * Kadc.
/*
 * Общие параметры.
 */
// Коэффициент преобразования АЦП, LSB/V.
#define ADC_GAIN_LSB_V_F (4096.0/3.3)
/*
 * Сетевое напряжение.
 */
// Коэффициент преобразования сетевого напряжения к напряжению на входе АЦП, В/В.
#define ADC_UPWR_ANALOG_GAIN_V_V_F (0.00156398104265402844)
// Смещение напряжения на входе АЦП, В.
#define ADC_UPWR_ANALOG_OFFSET_F (1.65)
// Смещение АЦП, LSB.
#define ADC_UPWR_OFFSET_I32 ((int32_t)(ADC_UPWR_ANALOG_OFFSET_F * ADC_GAIN_LSB_V_F))
// Коэффициент АЦП, LSB/V.
#define ADC_UPWR_GAIN_LSB_V_IQ24 IQ24(ADC_GAIN_LSB_V_F * ADC_UPWR_ANALOG_GAIN_V_V_F)
// Коэффициент АЦП, V/LSB.
#define ADC_UPWR_GAIN_V_LSB_IQ24 IQ24(1.0/(ADC_GAIN_LSB_V_F * ADC_UPWR_ANALOG_GAIN_V_V_F))



//! Перечисление возможных бит управления.
enum _E_Fake_Adc_Control {
    FAKE_ADC_CONTROL_NONE = CONTROL_NONE
};

//! Перечисление возможных бит статуса.
enum _E_Fake_Adc_Status {
    FAKE_ADC_STATUS_NONE = STATUS_NONE,
    FAKE_ADC_STATUS_READY = STATUS_READY,
    FAKE_ADC_STATUS_VALID = STATUS_VALID,
};


typedef struct _S_Fake_Adc M_fake_adc;

struct _S_Fake_Adc {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    //reg_iq15_t in_U; //!< Напряжение фаз.
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
    METHOD_INIT(M_fake_adc);
    METHOD_DEINIT(M_fake_adc);
    METHOD_CALC(M_fake_adc);
    METHOD_IDLE(M_fake_adc);
    // Коллбэки.
    CALLBACK(on_conversion);
    // Внутренние данные.
    iq24_t m_acnt; //!< Счётчик электрического угла.
    iq24_t m_Ua_gain; //!< Суммарное усиление напряжения фазы A.
    iq24_t m_Ub_gain; //!< Суммарное усиление напряжения фазы B.
    iq24_t m_Uc_gain; //!< Суммарное усиление напряжения фазы C.
};

EXTERN METHOD_INIT_PROTO(M_fake_adc);
EXTERN METHOD_DEINIT_PROTO(M_fake_adc);
EXTERN METHOD_CALC_PROTO(M_fake_adc);
EXTERN METHOD_IDLE_PROTO(M_fake_adc);

#define FAKE_ADC_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /*0,*/\
        /* Выходные данные */\
        0, 0, 0, /* raw Uabc */\
        0, 0, 0, /* Uabc */\
        /* Параметры */\
        ADC_UPWR_GAIN_V_LSB_IQ24, ADC_UPWR_OFFSET_I32, /* Усиление и смещение Ua */\
        ADC_UPWR_GAIN_V_LSB_IQ24, ADC_UPWR_OFFSET_I32, /* Усиление и смещение Ub */\
        ADC_UPWR_GAIN_V_LSB_IQ24, ADC_UPWR_OFFSET_I32, /* Усиление и смещение Uc */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_fake_adc), METHOD_DEINIT_PTR(M_fake_adc),\
        METHOD_CALC_PTR(M_fake_adc), METHOD_IDLE_PTR(M_fake_adc),\
        /* Коллбэки */\
        CALLBACK_DEFAULTS, /* on_conversion */\
        /* Внутренние данные */\
        0, /* m_acnt */\
        0, 0, 0 /* gain Uabc */\
    }


#endif //FAKE_ADC_H
