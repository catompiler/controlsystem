#ifndef ADC_H
#define ADC_H

#include "module/base.h"
#include "conf/conf.h"
#include <stdint.h>


//#define ADC_AC_FREQ (50)
#define ADC_SAMPLES_PER_PERIOD (CONF_PERIOD_SAMPLES)
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
enum _E_Adc_Control {
    ADC_CONTROL_NONE = CONTROL_NONE,
    //ADC_CONTROL_ENABLE = CONTROL_ENABLE, //!< Разрешает работу.
};

//! Перечисление возможных бит статуса.
enum _E_Adc_Status {
    ADC_STATUS_NONE = STATUS_NONE,
    ADC_STATUS_VALID = STATUS_VALID, //!< Устанавливается после первого преобразования.
};


typedef struct _S_Adc M_adc;

struct _S_Adc {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    // Напряжения сети.
    reg_u32_t out_Ua_raw; //!< Мнговенное напряжение фазы A (сырое).
    reg_u32_t out_Ub_raw; //!< Мнговенное напряжение фазы B (сырое).
    reg_u32_t out_Uc_raw; //!< Мнговенное напряжение фазы C (сырое).
    reg_iq24_t out_Ua; //!< Мнговенное напряжение фазы A.
    reg_iq24_t out_Ub; //!< Мнговенное напряжение фазы B.
    reg_iq24_t out_Uc; //!< Мнговенное напряжение фазы C.
    // Токи сети.
    reg_u32_t out_Ia_raw; //!< Мнговенный ток фазы A (сырое).
    reg_u32_t out_Ib_raw; //!< Мнговенный ток фазы B (сырое).
    reg_u32_t out_Ic_raw; //!< Мнговенный ток фазы C (сырое).
    reg_iq24_t out_Ia; //!< Мнговенный ток фазы A.
    reg_iq24_t out_Ib; //!< Мнговенный ток фазы B.
    reg_iq24_t out_Ic; //!< Мнговенный ток фазы C.
    // Напряжение выхода.
    reg_u32_t out_Uarm_raw; //!< Мнговенное напряжение выхода (сырое).
    reg_iq24_t out_Uarm; //!< Мнговенное напряжение выхода.
    // Ток выхода.
    reg_u32_t out_Iarm_raw; //!< Мнговенный ток выхода (сырое).
    reg_iq24_t out_Iarm; //!< Мнговенный ток выхода.
    // Ток резистора.
    reg_u32_t out_Ir_raw; //!< Мнговенный ток резистора (сырое).
    reg_iq24_t out_Ir; //!< Мнговенный ток резистора.
    // Напряжения статора.
    reg_u32_t out_s_Ua_raw; //!< Мнговенное напряжение фазы A статора (сырое).
    reg_u32_t out_s_Ub_raw; //!< Мнговенное напряжение фазы B статора (сырое).
    reg_u32_t out_s_Uc_raw; //!< Мнговенное напряжение фазы C статора (сырое).
    reg_iq24_t out_s_Ua; //!< Мнговенное напряжение фазы A статора.
    reg_iq24_t out_s_Ub; //!< Мнговенное напряжение фазы B статора.
    reg_iq24_t out_s_Uc; //!< Мнговенное напряжение фазы C статора.
    // Токи статора.
    reg_u32_t out_s_Ia_raw; //!< Мнговенный ток фазы A статора (сырое).
    reg_u32_t out_s_Ib_raw; //!< Мнговенный ток фазы B статора (сырое).
    reg_u32_t out_s_Ic_raw; //!< Мнговенный ток фазы C статора (сырое).
    reg_iq24_t out_s_Ia; //!< Мнговенный ток фазы A статора.
    reg_iq24_t out_s_Ib; //!< Мнговенный ток фазы B статора.
    reg_iq24_t out_s_Ic; //!< Мнговенный ток фазы C статора.
    // Параметры.
    // Напряжения сети.
    reg_iq24_t p_Ua_gain;   //!< Коэффициент усиления напряжения фазы A.
    reg_u32_t  p_Ua_offset; //!< Смещеие АЦП напряжения фазы A.
    reg_iq24_t p_Ub_gain;   //!< Коэффициент усиления напряжения фазы B.
    reg_u32_t  p_Ub_offset; //!< Смещеие АЦП напряжения фазы B.
    reg_iq24_t p_Uc_gain;   //!< Коэффициент усиления напряжения фазы C.
    reg_u32_t  p_Uc_offset; //!< Смещеие АЦП напряжения фазы C.
    // Токи сети.
    reg_iq24_t p_Ia_gain;   //!< Коэффициент усиления тока фазы A.
    reg_u32_t  p_Ia_offset; //!< Смещеие АЦП тока фазы A.
    reg_iq24_t p_Ib_gain;   //!< Коэффициент усиления тока фазы B.
    reg_u32_t  p_Ib_offset; //!< Смещеие АЦП тока фазы B.
    reg_iq24_t p_Ic_gain;   //!< Коэффициент усиления тока фазы C.
    reg_u32_t  p_Ic_offset; //!< Смещеие АЦП тока фазы C.
    // Напряжение выхода.
    reg_iq24_t p_Uarm_gain;   //!< Коэффициент усиления напряжения выхода.
    reg_u32_t  p_Uarm_offset; //!< Смещеие АЦП напряжения выхода.
    // Ток выхода.
    reg_iq24_t p_Iarm_gain;   //!< Коэффициент усиления тока выхода.
    reg_u32_t  p_Iarm_offset; //!< Смещеие АЦП тока выхода.
    // Ток резистора.
    reg_iq24_t p_Ir_gain;   //!< Коэффициент усиления тока резистора.
    reg_u32_t  p_Ir_offset; //!< Смещеие АЦП тока резистора.
    // Напряжения статора.
    reg_iq24_t p_s_Ua_gain;   //!< Коэффициент усиления напряжения фазы A статора.
    reg_u32_t  p_s_Ua_offset; //!< Смещеие АЦП напряжения фазы A статора.
    reg_iq24_t p_s_Ub_gain;   //!< Коэффициент усиления напряжения фазы B статора.
    reg_u32_t  p_s_Ub_offset; //!< Смещеие АЦП напряжения фазы B статора.
    reg_iq24_t p_s_Uc_gain;   //!< Коэффициент усиления напряжения фазы C статора.
    reg_u32_t  p_s_Uc_offset; //!< Смещеие АЦП напряжения фазы C статора.
    // Токи статора.
    reg_iq24_t p_s_Ia_gain;   //!< Коэффициент усиления тока фазы A статора.
    reg_u32_t  p_s_Ia_offset; //!< Смещеие АЦП тока фазы A статора.
    reg_iq24_t p_s_Ib_gain;   //!< Коэффициент усиления тока фазы B статора.
    reg_u32_t  p_s_Ib_offset; //!< Смещеие АЦП тока фазы B статора.
    reg_iq24_t p_s_Ic_gain;   //!< Коэффициент усиления тока фазы C статора.
    reg_u32_t  p_s_Ic_offset; //!< Смещеие АЦП тока фазы C статора.
    // Регистры.
    // Методы.
    METHOD_INIT(M_adc);
    METHOD_DEINIT(M_adc);
    METHOD_CALC(M_adc);
    METHOD_IDLE(M_adc);
    // Коллбэки.
    CALLBACK(on_conversion);
    // Внутренние данные.
    // Напряжения сети.
    iq24_t m_Ua_gain; //!< Суммарное усиление напряжения фазы A.
    iq24_t m_Ub_gain; //!< Суммарное усиление напряжения фазы B.
    iq24_t m_Uc_gain; //!< Суммарное усиление напряжения фазы C.
    // Токи сети.
    iq24_t m_Ia_gain; //!< Суммарное усиление тока фазы A.
    iq24_t m_Ib_gain; //!< Суммарное усиление тока фазы B.
    iq24_t m_Ic_gain; //!< Суммарное усиление тока фазы C.
    // Напряжение выхода.
    iq24_t m_Uarm_gain; //!< Суммарное усиление напряжения выхода.
    // Ток выхода.
    iq24_t m_Iarm_gain; //!< Суммарное усиление тока выхода.
    // Ток резистора.
    iq24_t m_Ir_gain; //!< Суммарное усиление тока резистора.
    // Напряжения статора.
    iq24_t m_s_Ua_gain; //!< Суммарное усиление напряжения фазы A статора.
    iq24_t m_s_Ub_gain; //!< Суммарное усиление напряжения фазы B статора.
    iq24_t m_s_Uc_gain; //!< Суммарное усиление напряжения фазы C статора.
    // Токи статора.
    iq24_t m_s_Ia_gain; //!< Суммарное усиление тока фазы A статора.
    iq24_t m_s_Ib_gain; //!< Суммарное усиление тока фазы B статора.
    iq24_t m_s_Ic_gain; //!< Суммарное усиление тока фазы C статора.
};

EXTERN METHOD_INIT_PROTO(M_adc);
EXTERN METHOD_DEINIT_PROTO(M_adc);
EXTERN METHOD_CALC_PROTO(M_adc);
EXTERN METHOD_IDLE_PROTO(M_adc);

#define ADC_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Напряжения сети */\
        0, 0, 0, /* raw Uabc */\
        0, 0, 0, /* Uabc */\
        /* Токи сети */\
        0, 0, 0, /* raw Iabc */\
        0, 0, 0, /* Iabc */\
        /* Напряжение выхода */\
        0, /* out_Uarm_raw */\
        0, /* out_Uarm */\
        /* Ток выхода */\
        0, /* out_Iarm_raw */\
        0, /* out_Iarm */\
        /* Ток резистора */\
        0, /* out_Ir_raw */\
        0, /* out_Ir */\
        /* Напряжения статора */\
        0, 0, 0, /* raw s Uabc */\
        0, 0, 0, /* s Uabc */\
        /* Токи статора */\
        0, 0, 0, /* raw s Iabc */\
        0, 0, 0, /* s Iabc */\
        /* Параметры */\
        /* Напряжения сети */\
        ADC_UPWR_GAIN_V_LSB_IQ24, ADC_UPWR_OFFSET_I32, /* Усиление и смещение Ua */\
        ADC_UPWR_GAIN_V_LSB_IQ24, ADC_UPWR_OFFSET_I32, /* Усиление и смещение Ub */\
        ADC_UPWR_GAIN_V_LSB_IQ24, ADC_UPWR_OFFSET_I32, /* Усиление и смещение Uc */\
        /* Токи сети */\
        0, 0, /* Усиление и смещение Ia */\
        0, 0, /* Усиление и смещение Ib */\
        0, 0, /* Усиление и смещение Ic */\
        /* Напряжение выхода */\
        0, 0, /* Усиление и смещение Uarm */\
        /* Ток выхода */\
        0, 0, /* Усиление и смещение Iarm */\
        /* Ток резистора */\
        0, 0, /* Усиление и смещение Ir */\
        /* Напряжения статора */\
        0, 0, /* Усиление и смещение Ua статора */\
        0, 0, /* Усиление и смещение Ub статора */\
        0, 0, /* Усиление и смещение Uc статора */\
        /* Токи статора */\
        0, 0, /* Усиление и смещение Ia статора */\
        0, 0, /* Усиление и смещение Ib статора */\
        0, 0, /* Усиление и смещение Ic статора */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_adc), METHOD_DEINIT_PTR(M_adc),\
        METHOD_CALC_PTR(M_adc), METHOD_IDLE_PTR(M_adc),\
        /* Коллбэки */\
        CALLBACK_DEFAULTS, /* on_conversion */\
        /* Внутренние данные */\
        0, 0, 0, /* gain Uabc */\
        0, 0, 0, /* gain Iabc */\
        0, /* gain Uarm */\
        0, /* gain Iarm */\
        0, /* gain Ir */\
        0, 0, 0, /* gain s Uabc */\
        0, 0, 0, /* gain s Iabc */\
    }


#endif //ADC_H
