#include "triacs.h"
#include "cpu.h"
#include "hardware/config.h"
#include "gpio/gpio_xmc4xxx.h"
#include "conf/consts.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "utils/utils.h"


/*
 * !!!
 * Используется POSIF Multi Channel Pattern!
 * При использовании POSIF необходимо
 * сохранять значение по-умолчанию (0)!
 * !!!
 */


#define CCU_MOD_DEGREES_F 120.0
#define CCU_MOD_DEGREES_PU IQ24((CCU_MOD_DEGREES_F) / 360.0)
#define CCU_MOD_FREQ_F ( (360.0 / (CCU_MOD_DEGREES_F)) * (CONF_MAINS_FREQ) )
#define CCU_MOD_PRESCALER_N 16
#define CCU_MOD_PRESCALER 0b0100
#define CCU_MOD_PERIOD_F ( (1.0 * (CPU_FREQ)) / (CCU_MOD_PRESCALER_N) / (CCU_MOD_FREQ_F) )
#define CCU_MOD_PERIOD ((uint32_t)CCU_MOD_PERIOD_F)
#define CCU_MOD_TICKS_2PI_PU ( (uint32_t)((CCU_MOD_PERIOD_F) * 360.0 / (CCU_MOD_DEGREES_F)) )


#define CCU_OUT_DEGREES_F TRIACS_MAINS_SINGLE_PULSE_ANGLE_F
#define CCU_OUT_DEGREES_PU IQ24((CCU_OUT_DEGREES_F) / 360.0)
#define CCU_OUT_FREQ_F ( (360.0 / (CCU_OUT_DEGREES_F)) * (CONF_MAINS_FREQ) )
#define CCU_OUT_PRESCALER_N 16
#define CCU_OUT_PRESCALER 0b0100
#define CCU_OUT_PERIOD ((uint32_t)((CPU_FREQ) / (CCU_OUT_PRESCALER_N) / (CCU_OUT_FREQ_F)))


//void TRIACS_MAINS_MOD_TIM_IRQ_Handler(void)
//{
//    TRIACS_MAINS_MOD_TIM_CCU8_CC8->SWR = CCU8_CC8_SWR_RPM_Msk;
//}


static void triacs_ctrl_gpio_init(M_triacs* tr)
{
    (void) tr;

    // en.
#ifdef TRIACS_CTRL_EN_PORT
    gpio_reset(TRIACS_CTRL_EN_PORT, TRIACS_CTRL_EN_PIN_Msk);
    gpio_set_pad_driver(TRIACS_CTRL_EN_PORT, TRIACS_CTRL_EN_PIN_Msk, TRIACS_CTRL_EN_PIN_DRIVER);
    gpio_init(TRIACS_CTRL_EN_PORT, TRIACS_CTRL_EN_PIN_Msk, TRIACS_CTRL_EN_PIN_CONF);
#endif
    // sel.
#ifdef TRIACS_CTRL_SEL_PORT
    gpio_reset(TRIACS_CTRL_SEL_PORT, TRIACS_CTRL_SEL_PIN_Msk);
    gpio_set_pad_driver(TRIACS_CTRL_SEL_PORT, TRIACS_CTRL_SEL_PIN_Msk, TRIACS_CTRL_SEL_PIN_DRIVER);
    gpio_init(TRIACS_CTRL_SEL_PORT, TRIACS_CTRL_SEL_PIN_Msk, TRIACS_CTRL_SEL_PIN_CONF);
#endif
}

static void triacs_ctrl_gpio_deinit(M_triacs* tr)
{
    (void) tr;

    // en.
#ifdef TRIACS_CTRL_EN_PORT
    gpio_reset(TRIACS_CTRL_EN_PORT, TRIACS_CTRL_EN_PIN_Msk);
    gpio_init(TRIACS_CTRL_EN_PORT, TRIACS_CTRL_EN_PIN_Msk, GPIO_CONF_INPUT);
#endif
    // sel.
#ifdef TRIACS_CTRL_SEL_PORT
    gpio_reset(TRIACS_CTRL_SEL_PORT, TRIACS_CTRL_SEL_PIN_Msk);
    gpio_init(TRIACS_CTRL_SEL_PORT, TRIACS_CTRL_SEL_PIN_Msk, GPIO_CONF_INPUT);
#endif
}

static void triacs_ctrl_gpio_triacs_enable(M_triacs* tr)
{
    (void) tr;

#ifdef TRIACS_CTRL_EN_PORT
    gpio_set(TRIACS_CTRL_EN_PORT, TRIACS_CTRL_EN_PIN_Msk);
#endif
}

static void triacs_ctrl_gpio_triacs_disable(M_triacs* tr)
{
    (void) tr;

#ifdef TRIACS_CTRL_EN_PORT
    gpio_reset(TRIACS_CTRL_EN_PORT, TRIACS_CTRL_EN_PIN_Msk);
#endif
}

static void triacs_ctrl_gpio_triacs_select_fwd(M_triacs* tr)
{
    (void) tr;

#ifdef TRIACS_CTRL_SEL_PORT
    gpio_reset(TRIACS_CTRL_SEL_PORT, TRIACS_CTRL_SEL_PIN_Msk);
#endif
}

static void triacs_ctrl_gpio_triacs_select_bwd(M_triacs* tr)
{
    (void) tr;

#ifdef TRIACS_CTRL_SEL_PORT
    gpio_set(TRIACS_CTRL_SEL_PORT, TRIACS_CTRL_SEL_PIN_Msk);
#endif
}


static void triacs_mains_mod_tim_init(M_triacs* tr)
{
    (void) tr;

    // configure.
    TRIACS_MAINS_MOD_TIM_CCU8_CC8->PSC = CCU_MOD_PRESCALER;
    TRIACS_MAINS_MOD_TIM_CCU8_CC8->PRS = CCU_MOD_PERIOD - 1;
    TRIACS_MAINS_MOD_TIM_CCU8_CC8->CR1S = 0;
    TRIACS_MAINS_MOD_TIM_CCU8_CC8->CR2S = CCU_MOD_PERIOD >> 1;
    TRIACS_MAINS_MOD_TIM_CCU8_CC8->CHC = CCU8_CC8_CHC_ASE_Msk; // Ассимметричный режим.
    TRIACS_MAINS_MOD_TIM_CCU8_CC8->TC = CCU8_CC8_TC_TSSM_Msk; // Однократный запуск.
    // shadow transfer.
    TRIACS_MAINS_MOD_TIM_CCU8->GCSS = TRIACS_MAINS_MOD_TIM_SHADOW_TRANSFER_Msk;

//    // irqs.
//    TRIACS_MAINS_A_MOD_TIM_CCU8_CC8->INTE = CCU8_CC8_INTE_PME_Msk;
//    TRIACS_MAINS_A_MOD_TIM_CCU8_CC8->SRS = TRIACS_MAINS_A_MOD_TIM_SR << CCU8_CC8_SRS_POSR_Pos;
//    // clear.
//    TRIACS_MAINS_A_MOD_TIM_CCU8_CC8->SWR = CCU8_CC8_SWR_RPM_Msk;

    // idle.
    TRIACS_MAINS_MOD_TIM_CCU8->GIDLC = TRIACS_MAINS_MOD_TIM_IDLE_CLR_Msk;
}

static void triacs_mains_mod_tim_deinit(M_triacs* tr)
{
    (void) tr;

    TRIACS_MAINS_MOD_TIM_CCU8->GIDLS = TRIACS_MAINS_MOD_TIM_IDLE_SET_Msk;
}

static int triacs_mains_mod_tim_start(M_triacs* tr)
{
    (void) tr;

    // start.
    TRIACS_MAINS_MOD_TIM_CCU8_CC8->TCSET = CCU8_CC8_TCSET_TRBS_Msk;

    return 0;
}

static int triacs_mains_mod_tim_stop(M_triacs* tr)
{
    (void) tr;

    // stop.
    TRIACS_MAINS_MOD_TIM_CCU8_CC8->TCCLR = CCU8_CC8_TCCLR_TRBC_Msk | CCU8_CC8_TCCLR_TCC_Msk;

    return 0;
}

//static int triacs_mains_mod_tim_isrunning(M_triacs* tr)
//{
//    (void) tr;
//
//    return (TRIACS_MAINS_A_MOD_TIM_CCU8_CC8->TCST & CCU8_CC8_TCST_TRB_Msk) != 0;
//}


static void triacs_mains_out_a_tim_init(M_triacs* tr)
{
    (void) tr;

    // configure.
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->PSC = CCU_OUT_PRESCALER;
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->PRS = CCU_OUT_PERIOD - 1;
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->CR1S = CCU_OUT_PERIOD >> 1;
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->CR2S = CCU_OUT_PERIOD >> 1;

    // events.
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->INS = ((12) << CCU8_CC8_INS_EV0IS_Pos) | // Событие 0 - INyM (CCU8_ST0).
                                           ((1) << CCU8_CC8_INS_EV0LM_Pos) | // Активно при 0.
                                           ((12) << CCU8_CC8_INS_EV1IS_Pos) | // Событие 1 - INyM (CCU8_ST0).
                                           ((1) << CCU8_CC8_INS_EV1EM_Pos) | // По переднему фронту.
                                           ((12) << CCU8_CC8_INS_EV2IS_Pos) | // Событие 2 - INyM (CCU8_ST0).
                                           ((2) << CCU8_CC8_INS_EV2EM_Pos); // По заднему фронту.

    // modulation.
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->CMC = ((1) << CCU8_CC8_CMC_MOS_Pos) | // Модуляция по событию 0.
                                           ((2) << CCU8_CC8_CMC_STRTS_Pos) | // Старт по событию 1.
                                           ((0/*3*/) << CCU8_CC8_CMC_ENDS_Pos); // Стоп по событию 2.
    // configuration.
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->TC = ((2/*2*/) << CCU8_CC8_TC_ENDM_Pos) | // Очистить таймер при Останове.
                                          ((1) << CCU8_CC8_TC_STRM_Pos) | // Очистить таймер при запуске.
                                          ((1) << CCU8_CC8_TC_EMS_Pos) | // Синхронная модуляция.
                                          ((1) << CCU8_CC8_TC_EMT_Pos) | // Стробирование.
                                          ((3) << CCU8_CC8_TC_EME_Pos); // Разрешить модуляцию для канала 1 и 2.

    // output.
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->CHC = ((1) << (CCU8_CC8_CHC_OCS1_Pos + TRIACS_MAINS_AP_OUT_CHANNEL)) |
                                           ((1) << (CCU8_CC8_CHC_OCS1_Pos + TRIACS_MAINS_AN_OUT_CHANNEL)); // Инверсия сигналов.
                                           //CCU8_CC8_CHC_ASE_Msk; // Ассимметричный режим.
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->PSL = 0;

    // shadow transfer.
    TRIACS_MAINS_A_OUT_TIM_CCU8->GCSS = TRIACS_MAINS_A_OUT_TIM_SHADOW_TRANSFER_Msk;

    // idle.
    TRIACS_MAINS_A_OUT_TIM_CCU8->GIDLC = TRIACS_MAINS_A_OUT_TIM_IDLE_CLR_Msk;

    // gpio.
    // pos.
#ifdef TRIACS_MAINS_AP_PORT
    gpio_reset(TRIACS_MAINS_AP_PORT, TRIACS_MAINS_AP_PIN_Msk);
    gpio_set_pad_driver(TRIACS_MAINS_AP_PORT, TRIACS_MAINS_AP_PIN_Msk, TRIACS_MAINS_AP_PIN_DRIVER);
    gpio_init(TRIACS_MAINS_AP_PORT, TRIACS_MAINS_AP_PIN_Msk, TRIACS_MAINS_AP_PIN_CONF);
#endif
    // neg.
#ifdef TRIACS_MAINS_AN_PORT
    gpio_reset(TRIACS_MAINS_AN_PORT, TRIACS_MAINS_AN_PIN_Msk);
    gpio_set_pad_driver(TRIACS_MAINS_AN_PORT, TRIACS_MAINS_AN_PIN_Msk, TRIACS_MAINS_AN_PIN_DRIVER);
    gpio_init(TRIACS_MAINS_AN_PORT, TRIACS_MAINS_AN_PIN_Msk, TRIACS_MAINS_AN_PIN_CONF);
#endif
}

static void triacs_mains_out_a_tim_deinit(M_triacs* tr)
{
    (void) tr;

    TRIACS_MAINS_A_OUT_TIM_CCU8->GIDLS = TRIACS_MAINS_A_OUT_TIM_IDLE_SET_Msk;
}

static int triacs_mains_out_a_tim_stop(M_triacs* tr)
{
    (void) tr;

    // stop.
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->TCCLR = CCU8_CC8_TCCLR_TRBC_Msk | CCU8_CC8_TCCLR_TCC_Msk;

    return 0;
}

static void triacs_mains_out_ap_tim_out_enable(M_triacs* tr)
{
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->TC &= ~CCU8_CC8_TC_MCME1_Msk;
}

static void triacs_mains_out_ap_tim_out_disable(M_triacs* tr)
{
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->TC |= CCU8_CC8_TC_MCME1_Msk;
}

static void triacs_mains_out_an_tim_out_enable(M_triacs* tr)
{
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->TC &= ~CCU8_CC8_TC_MCME2_Msk;
}

static void triacs_mains_out_an_tim_out_disable(M_triacs* tr)
{
    TRIACS_MAINS_A_OUT_TIM_CCU8_CC8->TC |= CCU8_CC8_TC_MCME2_Msk;
}


static void triacs_mains_out_b_tim_init(M_triacs* tr)
{
    (void) tr;

    // configure.
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->PSC = CCU_OUT_PRESCALER;
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->PRS = CCU_OUT_PERIOD - 1;
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->CR1S = CCU_OUT_PERIOD >> 1;
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->CR2S = CCU_OUT_PERIOD >> 1;

    // events.
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->INS = ((12) << CCU8_CC8_INS_EV0IS_Pos) | // Событие 0 - INyM (CCU8_ST0).
                                           ((1) << CCU8_CC8_INS_EV0LM_Pos) | // Активно при 0.
                                           ((12) << CCU8_CC8_INS_EV1IS_Pos) | // Событие 1 - INyM (CCU8_ST0).
                                           ((1) << CCU8_CC8_INS_EV1EM_Pos) | // По переднему фронту.
                                           ((12) << CCU8_CC8_INS_EV2IS_Pos) | // Событие 2 - INyM (CCU8_ST0).
                                           ((2) << CCU8_CC8_INS_EV2EM_Pos); // По заднему фронту.

    // modulation.
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->CMC = ((1) << CCU8_CC8_CMC_MOS_Pos) | // Модуляция по событию 0.
                                           ((2) << CCU8_CC8_CMC_STRTS_Pos) | // Старт по событию 1.
                                           ((0/*3*/) << CCU8_CC8_CMC_ENDS_Pos); // Стоп по событию 2.
    // configuration.
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->TC = ((2/*2*/) << CCU8_CC8_TC_ENDM_Pos) | // Очистить таймер при Останове.
                                          ((1) << CCU8_CC8_TC_STRM_Pos) | // Очистить таймер при запуске.
                                          ((1) << CCU8_CC8_TC_EMS_Pos) | // Синхронная модуляция.
                                          ((1) << CCU8_CC8_TC_EMT_Pos) | // Стробирование.
                                          ((3) << CCU8_CC8_TC_EME_Pos); // Разрешить модуляцию для канала 1 и 2.

    // output.
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->CHC = ((1) << (CCU8_CC8_CHC_OCS1_Pos + TRIACS_MAINS_BP_OUT_CHANNEL)) |
                                           ((1) << (CCU8_CC8_CHC_OCS1_Pos + TRIACS_MAINS_BN_OUT_CHANNEL)); // Инверсия сигналов.
                                           //CCU8_CC8_CHC_ASE_Msk; // Ассимметричный режим.
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->PSL = 0;

    // shadow transfer.
    TRIACS_MAINS_B_OUT_TIM_CCU8->GCSS = TRIACS_MAINS_B_OUT_TIM_SHADOW_TRANSFER_Msk;

    // idle.
    TRIACS_MAINS_B_OUT_TIM_CCU8->GIDLC = TRIACS_MAINS_B_OUT_TIM_IDLE_CLR_Msk;

    // gpio.
    // pos.
#ifdef TRIACS_MAINS_BP_PORT
    gpio_reset(TRIACS_MAINS_BP_PORT, TRIACS_MAINS_BP_PIN_Msk);
    gpio_set_pad_driver(TRIACS_MAINS_BP_PORT, TRIACS_MAINS_BP_PIN_Msk, TRIACS_MAINS_BP_PIN_DRIVER);
    gpio_init(TRIACS_MAINS_BP_PORT, TRIACS_MAINS_BP_PIN_Msk, TRIACS_MAINS_BP_PIN_CONF);
#endif
    // neg.
#ifdef TRIACS_MAINS_BN_PORT
    gpio_reset(TRIACS_MAINS_BN_PORT, TRIACS_MAINS_BN_PIN_Msk);
    gpio_set_pad_driver(TRIACS_MAINS_BN_PORT, TRIACS_MAINS_BN_PIN_Msk, TRIACS_MAINS_BN_PIN_DRIVER);
    gpio_init(TRIACS_MAINS_BN_PORT, TRIACS_MAINS_BN_PIN_Msk, TRIACS_MAINS_BN_PIN_CONF);
#endif
}

static void triacs_mains_out_b_tim_deinit(M_triacs* tr)
{
    (void) tr;

    TRIACS_MAINS_B_OUT_TIM_CCU8->GIDLS = TRIACS_MAINS_B_OUT_TIM_IDLE_SET_Msk;
}

static int triacs_mains_out_b_tim_stop(M_triacs* tr)
{
    (void) tr;

    // stop.
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->TCCLR = CCU8_CC8_TCCLR_TRBC_Msk | CCU8_CC8_TCCLR_TCC_Msk;

    return 0;
}

static void triacs_mains_out_bp_tim_out_enable(M_triacs* tr)
{
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->TC &= ~CCU8_CC8_TC_MCME1_Msk;
}

static void triacs_mains_out_bp_tim_out_disable(M_triacs* tr)
{
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->TC |= CCU8_CC8_TC_MCME1_Msk;
}

static void triacs_mains_out_bn_tim_out_enable(M_triacs* tr)
{
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->TC &= ~CCU8_CC8_TC_MCME2_Msk;
}

static void triacs_mains_out_bn_tim_out_disable(M_triacs* tr)
{
    TRIACS_MAINS_B_OUT_TIM_CCU8_CC8->TC |= CCU8_CC8_TC_MCME2_Msk;
}


static void triacs_mains_out_c_tim_eru_init(M_triacs* tr)
{
    TRIACS_MAINS_C_ERU->EXISEL |= ((TRIACS_MAINS_C_ERU_EXISEL_VALUE) << TRIACS_MAINS_C_ERU_EXISEL_Pos);
    TRIACS_MAINS_C_ERU->EXICON[TRIACS_MAINS_C_ERU_EXICON_N] = ((0) << ERU_EXICON_NB_Pos) | // not inverted.
                                    ((TRIACS_MAINS_C_ERU_EXICON_SS) << ERU_EXICON_SS_Pos) | // only B
                                    ((1) << ERU_EXICON_LD_Pos) | // level detection.
                                    ((1) << ERU_EXICON_RE_Pos) | // Rising edge.
                                    ((0) << ERU_EXICON_FE_Pos) | // Falling edge.
                                    ((TRIACS_MAINS_C_ERU_EXOCON_N) << ERU_EXICON_OCS_Pos); // channel 1.
    TRIACS_MAINS_C_ERU->EXOCON[TRIACS_MAINS_C_ERU_EXOCON_N] = ((1) << (ERU_EXOCON_IPEN0_Pos + TRIACS_MAINS_C_ERU_EXICON_N));// | // input 0.

//    gpio_reset(PORT1, GPIO_PIN_2);
//    gpio_set_pad_driver(PORT1, GPIO_PIN_2, GPIO_PAD_A2_DRIVER_STRONG_EDGE_SOFT);
//    gpio_init(PORT1, GPIO_PIN_2, GPIO_CONF_OUTPUT_PP_ALT4);
}

static void triacs_mains_out_c_tim_init(M_triacs* tr)
{
    (void) tr;

    // Interconnect CCU80.ST0 -> CCU81.INyI
    triacs_mains_out_c_tim_eru_init(tr);

    // configure.
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->PSC = CCU_OUT_PRESCALER;
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->PRS = CCU_OUT_PERIOD - 1;
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->CR1S = CCU_OUT_PERIOD >> 1;
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->CR2S = CCU_OUT_PERIOD >> 1;

    // events.
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->INS = ((8) << CCU8_CC8_INS_EV0IS_Pos) | // Событие 0 - INyI (ERU1.PDOUT1).
                                           ((1) << CCU8_CC8_INS_EV0LM_Pos) | // Активно при 0.
                                           ((8) << CCU8_CC8_INS_EV1IS_Pos) | // Событие 1 - INyI (ERU1.PDOUT1).
                                           ((1) << CCU8_CC8_INS_EV1EM_Pos) | // По переднему фронту.
                                           ((8) << CCU8_CC8_INS_EV2IS_Pos) | // Событие 2 - INyI (ERU1.PDOUT1).
                                           ((2) << CCU8_CC8_INS_EV2EM_Pos); // По заднему фронту.

    // modulation.
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->CMC = ((1) << CCU8_CC8_CMC_MOS_Pos) | // Модуляция по событию 0.
                                           ((2) << CCU8_CC8_CMC_STRTS_Pos) | // Старт по событию 1.
                                           ((0/*3*/) << CCU8_CC8_CMC_ENDS_Pos); // Стоп по событию 2.
    // configuration.
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->TC = ((2/*2*/) << CCU8_CC8_TC_ENDM_Pos) | // Очистить таймер при Останове.
                                          ((1) << CCU8_CC8_TC_STRM_Pos) | // Очистить таймер при запуске.
                                          ((1) << CCU8_CC8_TC_EMS_Pos) | // Синхронная модуляция.
                                          ((1) << CCU8_CC8_TC_EMT_Pos) | // Стробирование.
                                          ((3) << CCU8_CC8_TC_EME_Pos); // Разрешить модуляцию для канала 1 и 2.

    // output.
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->CHC = ((1) << (CCU8_CC8_CHC_OCS1_Pos + TRIACS_MAINS_CP_OUT_CHANNEL)) |
                                           ((1) << (CCU8_CC8_CHC_OCS1_Pos + TRIACS_MAINS_CN_OUT_CHANNEL)); // Инверсия сигналов.
                                           //CCU8_CC8_CHC_ASE_Msk; // Ассимметричный режим.
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->PSL = 0;

    // shadow transfer.
    TRIACS_MAINS_C_OUT_TIM_CCU8->GCSS = TRIACS_MAINS_C_OUT_TIM_SHADOW_TRANSFER_Msk;

    // idle.
    TRIACS_MAINS_C_OUT_TIM_CCU8->GIDLC = TRIACS_MAINS_C_OUT_TIM_IDLE_CLR_Msk;

    // gpio.
    // pos.
#ifdef TRIACS_MAINS_CP_PORT
    gpio_reset(TRIACS_MAINS_CP_PORT, TRIACS_MAINS_CP_PIN_Msk);
    gpio_set_pad_driver(TRIACS_MAINS_CP_PORT, TRIACS_MAINS_CP_PIN_Msk, TRIACS_MAINS_CP_PIN_DRIVER);
    gpio_init(TRIACS_MAINS_CP_PORT, TRIACS_MAINS_CP_PIN_Msk, TRIACS_MAINS_CP_PIN_CONF);
#endif
    // neg.
#ifdef TRIACS_MAINS_CN_PORT
    gpio_reset(TRIACS_MAINS_CN_PORT, TRIACS_MAINS_CN_PIN_Msk);
    gpio_set_pad_driver(TRIACS_MAINS_CN_PORT, TRIACS_MAINS_CN_PIN_Msk, TRIACS_MAINS_CN_PIN_DRIVER);
    gpio_init(TRIACS_MAINS_CN_PORT, TRIACS_MAINS_CN_PIN_Msk, TRIACS_MAINS_CN_PIN_CONF);
#endif
}

static void triacs_mains_out_c_tim_deinit(M_triacs* tr)
{
    (void) tr;

    TRIACS_MAINS_C_OUT_TIM_CCU8->GIDLS = TRIACS_MAINS_C_OUT_TIM_IDLE_SET_Msk;
}

static int triacs_mains_out_c_tim_stop(M_triacs* tr)
{
    (void) tr;

    // stop.
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->TCCLR = CCU8_CC8_TCCLR_TRBC_Msk | CCU8_CC8_TCCLR_TCC_Msk;

    return 0;
}

static void triacs_mains_out_cp_tim_out_enable(M_triacs* tr)
{
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->TC &= ~CCU8_CC8_TC_MCME1_Msk;
}

static void triacs_mains_out_cp_tim_out_disable(M_triacs* tr)
{
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->TC |= CCU8_CC8_TC_MCME1_Msk;
}

static void triacs_mains_out_cn_tim_out_enable(M_triacs* tr)
{
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->TC &= ~CCU8_CC8_TC_MCME2_Msk;
}

static void triacs_mains_out_cn_tim_out_disable(M_triacs* tr)
{
    TRIACS_MAINS_C_OUT_TIM_CCU8_CC8->TC |= CCU8_CC8_TC_MCME2_Msk;
}


static void triacs_mains_close(M_triacs* tr)
{
    triacs_mains_mod_tim_stop(tr);
    triacs_mains_out_a_tim_stop(tr);
    triacs_mains_out_b_tim_stop(tr);
    triacs_mains_out_c_tim_stop(tr);
    triacs_mains_out_ap_tim_out_disable(tr);
    triacs_mains_out_an_tim_out_disable(tr);
    triacs_mains_out_bp_tim_out_disable(tr);
    triacs_mains_out_bn_tim_out_disable(tr);
    triacs_mains_out_cp_tim_out_disable(tr);
    triacs_mains_out_cn_tim_out_disable(tr);
}

static iq24_t triacs_mains_calc_duration_angle(M_triacs* tr, iq24_t max_dur)
{
    iq24_t pulses_count_iq = iq24_mul(max_dur, TRIACS_MAINS_SINGLE_PULSE_ANGLE_INV_PU);
    uint32_t pulses_count = iq24_int(pulses_count_iq);

    pulses_count = CLAMP(pulses_count, TRIACS_MAINS_PULSES_MIN, TRIACS_MAINS_PULSES_MAX);

    return pulses_count * TRIACS_MAINS_SINGLE_PULSE_ANGLE_PU;
}

static void triacs_mains_setup_fire(M_triacs* tr)
{
    (void) tr;

    iq24_t delay_angle = tr->in_control_delay_angle;
    iq24_t max_duration_angle = tr->in_control_max_duration_angle;

    uint32_t start_ticks = (uint32_t)iq24_mul(delay_angle, CCU_MOD_TICKS_2PI_PU);

    iq24_t duration_angle = triacs_mains_calc_duration_angle(tr, max_duration_angle);
    uint32_t duration_ticks = (uint32_t)iq24_mul(duration_angle, CCU_MOD_TICKS_2PI_PU);

    uint32_t end_ticks = start_ticks + duration_ticks;

    TRIACS_MAINS_MOD_TIM_CCU8_CC8->CR1S = start_ticks;
    TRIACS_MAINS_MOD_TIM_CCU8_CC8->CR2S = end_ticks;
    // shadow transfer.
    TRIACS_MAINS_MOD_TIM_CCU8->GCSS = TRIACS_MAINS_MOD_TIM_SHADOW_TRANSFER_Msk;
}


static void triacs_mains_fire(M_triacs* tr)
{
    triacs_mains_mod_tim_stop(tr);

    if(tr->in_control[PHASE3_CONTROL_A_HI]) triacs_mains_out_ap_tim_out_enable(tr);
    else                                    triacs_mains_out_ap_tim_out_disable(tr);

    if(tr->in_control[PHASE3_CONTROL_A_LO]) triacs_mains_out_an_tim_out_enable(tr);
    else                                    triacs_mains_out_an_tim_out_disable(tr);

    if(tr->in_control[PHASE3_CONTROL_B_HI]) triacs_mains_out_bp_tim_out_enable(tr);
    else                                    triacs_mains_out_bp_tim_out_disable(tr);

    if(tr->in_control[PHASE3_CONTROL_B_LO]) triacs_mains_out_bn_tim_out_enable(tr);
    else                                    triacs_mains_out_bn_tim_out_disable(tr);

    if(tr->in_control[PHASE3_CONTROL_C_HI]) triacs_mains_out_cp_tim_out_enable(tr);
    else                                    triacs_mains_out_cp_tim_out_disable(tr);

    if(tr->in_control[PHASE3_CONTROL_C_LO]) triacs_mains_out_cn_tim_out_enable(tr);
    else                                    triacs_mains_out_cn_tim_out_disable(tr);

    triacs_mains_setup_fire(tr);

    triacs_mains_mod_tim_start(tr);
}


METHOD_INIT_IMPL(M_triacs, tr)
{
    triacs_ctrl_gpio_init(tr);
    triacs_ctrl_gpio_triacs_select_fwd(tr);
    triacs_ctrl_gpio_triacs_enable(tr);

    triacs_mains_mod_tim_init(tr);
    triacs_mains_out_a_tim_init(tr);
    triacs_mains_out_b_tim_init(tr);
    triacs_mains_out_c_tim_init(tr);
}

METHOD_DEINIT_IMPL(M_triacs, tr)
{
    triacs_mains_close(tr);

    triacs_ctrl_gpio_deinit(tr);

    triacs_mains_out_a_tim_deinit(tr);
    triacs_mains_out_b_tim_deinit(tr);
    triacs_mains_out_c_tim_deinit(tr);
    triacs_mains_mod_tim_deinit(tr);
}

METHOD_CALC_IMPL(M_triacs, tr)
{
    if(!(tr->control & CONTROL_ENABLE)){
        triacs_mains_close(tr);
        return;
    }

    bool need_fire = false;
    size_t i;
    for(i = 0; i < TRIACS_MAINS_KEYS_COUNT; i ++){
        if(tr->in_control[i]){
            need_fire = true;
            //break; // constant delay.
        }
    }

    if(need_fire) triacs_mains_fire(tr);
}

METHOD_CONTROL_IMPL(M_triacs, tr)
{
    if(tr->control & TRIACS_CONTROL_CLOSE){
        triacs_mains_close(tr);
    }
}
