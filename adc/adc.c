#include "adc.h"
#include "iqmath/iqmath.h"
#include "modules/modules.h"
#include "sys_counter/sys_counter.h"
#include "hardware/config.h"
#include "cpu.h"
#include "bits/bits.h"
#include "defs/defs.h"



#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#define ADC_PRESCALER 4
#define ADC_WAKEUP_DELAY_US 15

#define ADC_TRIGGER_ADC_TIM 0b0101 // CCU43.SR3

#define ADC_ADDITIONAL_SAMPLE_TIME 14

// Group 0 channels.
#define ADC_CH_Ucell_G VADC_G0
#define ADC_CH_UcellA_N 2
#define ADC_CH_UcellB_N 3
#define ADC_CH_UcellC_N 4
#define ADC_CH_Vref_cell_G VADC_G0
#define ADC_CH_Vref_cell_N 5
// Group 1 channels.
#define ADC_CH_Uph_G VADC_G1
#define ADC_CH_UphA_N 4
#define ADC_CH_UphB_N 5
#define ADC_CH_UphC_N 6
#define ADC_CH_Udc_G VADC_G1
#define ADC_CH_Udc_N 7
// Group 2 channels.
#define ADC_CH_Iph_G VADC_G2
#define ADC_CH_IphA_N 2
#define ADC_CH_IphB_N 3
#define ADC_CH_IphC_N 6
#define ADC_CH_Vref_main_G VADC_G2
#define ADC_CH_Vref_main_N 7
// Group 3 channels.
#define ADC_CH_Icell_G VADC_G3
#define ADC_CH_IcellA_N 3
#define ADC_CH_IcellB_N 4
#define ADC_CH_IcellC_N 5
#define ADC_CH_Uext_G VADC_G3
#define ADC_CH_Uext_N 6

#define ADC_G0_PRIOR_CHANNELS_MASK (BIT(ADC_CH_UcellA_N) | BIT(ADC_CH_UcellB_N) | BIT(ADC_CH_UcellC_N) | BIT(ADC_CH_Vref_cell_N))
#define ADC_G1_PRIOR_CHANNELS_MASK (BIT(ADC_CH_UphA_N)   | BIT(ADC_CH_UphB_N)   | BIT(ADC_CH_UphC_N)   | BIT(ADC_CH_Udc_N))
#define ADC_G2_PRIOR_CHANNELS_MASK (BIT(ADC_CH_IphA_N)   | BIT(ADC_CH_IphB_N)   | BIT(ADC_CH_IphC_N)   | BIT(ADC_CH_Vref_main_N))
#define ADC_G3_PRIOR_CHANNELS_MASK (BIT(ADC_CH_IcellA_N) | BIT(ADC_CH_IcellB_N) | BIT(ADC_CH_IcellC_N) | BIT(ADC_CH_Uext_N))

#define ADC_G0_BACK_CHANNELS_MASK 0b00000000
#define ADC_G1_BACK_CHANNELS_MASK 0b00000000
#define ADC_G2_BACK_CHANNELS_MASK 0b00000000
#define ADC_G3_BACK_CHANNELS_MASK 0b00000000

#endif

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

// channel control base value (except number of res reg).
#define CHCTR_base (((0b10) << VADC_G_CHCTR_ICLSEL_Pos) |\
                    ((1) << VADC_G_CHCTR_RESPOS_Pos))

static void adc_group0_init(M_adc* adc)
{
    (void) adc;

    VADC_G0->CHASS = ADC_G0_PRIOR_CHANNELS_MASK;
    VADC_G0->ASSEL = ADC_G0_PRIOR_CHANNELS_MASK;
    VADC_G0->ASCTRL = ((ADC_TRIGGER_ADC_TIM) << VADC_G_ASCTRL_XTSEL_Pos) |
                      ((0b10) << VADC_G_ASCTRL_XTMODE_Pos) |
                      (VADC_G_ASCTRL_XTWC_Msk) |
                      ((0) << VADC_G_ASCTRL_GTSEL_Pos) |
                      (VADC_G_ASCTRL_GTWC_Msk) |
                      ((0) << VADC_G_ASCTRL_TMEN_Pos) |
                      (VADC_G_ASCTRL_TMWC_Msk);
    VADC_G0->ASMR = ((0b01) << VADC_G_ASMR_ENGT_Pos) |
                    ((1) << VADC_G_ASMR_ENTR_Pos) |
                    ((1) << VADC_G_ASMR_ENSI_Pos) |
                    ((0) << VADC_G_ASMR_SCAN_Pos) |
                    ((0) << VADC_G_ASMR_LDM_Pos);
    VADC_G0->ARBPR = ((0b10) << VADC_G_ARBPR_PRIO1_Pos) |
                     ((1) << VADC_G_ARBPR_CSM1_Pos) |
                     ((1) << VADC_G_ARBPR_ASEN1_Pos);

    // channels.
    VADC_G0->CHCTR[ADC_CH_UcellA_N] = CHCTR_base | ((ADC_CH_UcellA_N) << VADC_G_CHCTR_RESREG_Pos);
    VADC_G0->CHCTR[ADC_CH_UcellB_N] = CHCTR_base | ((ADC_CH_UcellB_N) << VADC_G_CHCTR_RESREG_Pos);
    VADC_G0->CHCTR[ADC_CH_UcellC_N] = CHCTR_base | ((ADC_CH_UcellC_N) << VADC_G_CHCTR_RESREG_Pos);
    VADC_G0->CHCTR[ADC_CH_Vref_cell_N] = CHCTR_base | ((ADC_CH_Vref_cell_N) << VADC_G_CHCTR_RESREG_Pos);

    // result registers.
    VADC_G0->RCR[ADC_CH_UcellA_N] = 0;
    VADC_G0->RCR[ADC_CH_UcellB_N] = 0;
    VADC_G0->RCR[ADC_CH_UcellC_N] = 0;
    VADC_G0->RCR[ADC_CH_Vref_cell_N] = 0;
}

static void adc_group1_init(M_adc* adc)
{
    (void) adc;

    VADC_G1->CHASS = ADC_G1_PRIOR_CHANNELS_MASK;
    VADC_G1->ASSEL = ADC_G1_PRIOR_CHANNELS_MASK;
    VADC_G1->ASCTRL = ((ADC_TRIGGER_ADC_TIM) << VADC_G_ASCTRL_XTSEL_Pos) |
                      ((0b10) << VADC_G_ASCTRL_XTMODE_Pos) |
                      (VADC_G_ASCTRL_XTWC_Msk) |
                      ((0) << VADC_G_ASCTRL_GTSEL_Pos) |
                      (VADC_G_ASCTRL_GTWC_Msk) |
                      ((0) << VADC_G_ASCTRL_TMEN_Pos) |
                      (VADC_G_ASCTRL_TMWC_Msk);
    VADC_G1->ASMR = ((0b01) << VADC_G_ASMR_ENGT_Pos) |
                    ((1) << VADC_G_ASMR_ENTR_Pos) |
                    ((1) << VADC_G_ASMR_ENSI_Pos) |
                    ((0) << VADC_G_ASMR_SCAN_Pos) |
                    ((0) << VADC_G_ASMR_LDM_Pos);
    VADC_G1->ARBPR = ((0b10) << VADC_G_ARBPR_PRIO1_Pos) |
                     ((1) << VADC_G_ARBPR_CSM1_Pos) |
                     ((1) << VADC_G_ARBPR_ASEN1_Pos);

    // channels.
    VADC_G1->CHCTR[ADC_CH_UphA_N] = CHCTR_base | ((ADC_CH_UphA_N) << VADC_G_CHCTR_RESREG_Pos);
    VADC_G1->CHCTR[ADC_CH_UphB_N] = CHCTR_base | ((ADC_CH_UphB_N) << VADC_G_CHCTR_RESREG_Pos);
    VADC_G1->CHCTR[ADC_CH_UphC_N] = CHCTR_base | ((ADC_CH_UphC_N) << VADC_G_CHCTR_RESREG_Pos);
    VADC_G1->CHCTR[ADC_CH_Udc_N] = CHCTR_base | ((ADC_CH_Udc_N) << VADC_G_CHCTR_RESREG_Pos);

    // result registers.
    VADC_G1->RCR[ADC_CH_UphA_N] = 0;
    VADC_G1->RCR[ADC_CH_UphB_N] = 0;
    VADC_G1->RCR[ADC_CH_UphC_N] = 0;
    VADC_G1->RCR[ADC_CH_Udc_N] = 0;
}

static void adc_group2_init(M_adc* adc)
{
    (void) adc;

    VADC_G2->CHASS = ADC_G2_PRIOR_CHANNELS_MASK;
    VADC_G2->ASSEL = ADC_G2_PRIOR_CHANNELS_MASK;
    VADC_G2->ASCTRL = ((ADC_TRIGGER_ADC_TIM) << VADC_G_ASCTRL_XTSEL_Pos) |
                      ((0b10) << VADC_G_ASCTRL_XTMODE_Pos) |
                      (VADC_G_ASCTRL_XTWC_Msk) |
                      ((0) << VADC_G_ASCTRL_GTSEL_Pos) |
                      (VADC_G_ASCTRL_GTWC_Msk) |
                      ((0) << VADC_G_ASCTRL_TMEN_Pos) |
                      (VADC_G_ASCTRL_TMWC_Msk);
    VADC_G2->ASMR = ((0b01) << VADC_G_ASMR_ENGT_Pos) |
                    ((1) << VADC_G_ASMR_ENTR_Pos) |
                    ((1) << VADC_G_ASMR_ENSI_Pos) |
                    ((0) << VADC_G_ASMR_SCAN_Pos) |
                    ((0) << VADC_G_ASMR_LDM_Pos);
    VADC_G2->ARBPR = ((0b10) << VADC_G_ARBPR_PRIO1_Pos) |
                     ((1) << VADC_G_ARBPR_CSM1_Pos) |
                     ((1) << VADC_G_ARBPR_ASEN1_Pos);

    // channels.
    VADC_G2->CHCTR[ADC_CH_IphA_N] = CHCTR_base | ((ADC_CH_IphA_N) << VADC_G_CHCTR_RESREG_Pos);
    VADC_G2->CHCTR[ADC_CH_IphB_N] = CHCTR_base | ((ADC_CH_IphB_N) << VADC_G_CHCTR_RESREG_Pos);
    VADC_G2->CHCTR[ADC_CH_IphC_N] = CHCTR_base | ((ADC_CH_IphC_N) << VADC_G_CHCTR_RESREG_Pos);
    VADC_G2->CHCTR[ADC_CH_Vref_main_N] = CHCTR_base | ((ADC_CH_Vref_main_N) << VADC_G_CHCTR_RESREG_Pos);

    // result registers.
    VADC_G2->RCR[ADC_CH_IphA_N] = 0;
    VADC_G2->RCR[ADC_CH_IphB_N] = 0;
    VADC_G2->RCR[ADC_CH_IphC_N] = 0;
    VADC_G2->RCR[ADC_CH_Vref_main_N] = 0;
}

static void adc_group3_init(M_adc* adc)
{
    (void) adc;

    VADC_G3->CHASS = ADC_G3_PRIOR_CHANNELS_MASK;
    VADC_G3->ASSEL = ADC_G3_PRIOR_CHANNELS_MASK;
    VADC_G3->ASCTRL = ((ADC_TRIGGER_ADC_TIM) << VADC_G_ASCTRL_XTSEL_Pos) |
                      ((0b10) << VADC_G_ASCTRL_XTMODE_Pos) |
                      (VADC_G_ASCTRL_XTWC_Msk) |
                      ((0) << VADC_G_ASCTRL_GTSEL_Pos) |
                      (VADC_G_ASCTRL_GTWC_Msk) |
                      ((0) << VADC_G_ASCTRL_TMEN_Pos) |
                      (VADC_G_ASCTRL_TMWC_Msk);
    VADC_G3->ASMR = ((0b01) << VADC_G_ASMR_ENGT_Pos) |
                    ((1) << VADC_G_ASMR_ENTR_Pos) |
                    ((1) << VADC_G_ASMR_ENSI_Pos) |
                    ((0) << VADC_G_ASMR_SCAN_Pos) |
                    ((0) << VADC_G_ASMR_LDM_Pos);
    VADC_G3->ARBPR = ((0b10) << VADC_G_ARBPR_PRIO1_Pos) |
                     ((1) << VADC_G_ARBPR_CSM1_Pos) |
                     ((1) << VADC_G_ARBPR_ASEN1_Pos);

    // channels.
    VADC_G3->CHCTR[ADC_CH_IcellA_N] = CHCTR_base | ((ADC_CH_IcellA_N) << VADC_G_CHCTR_RESREG_Pos);
    VADC_G3->CHCTR[ADC_CH_IcellB_N] = CHCTR_base | ((ADC_CH_IcellB_N) << VADC_G_CHCTR_RESREG_Pos);
    VADC_G3->CHCTR[ADC_CH_IcellC_N] = CHCTR_base | ((ADC_CH_IcellC_N) << VADC_G_CHCTR_RESREG_Pos);
    VADC_G3->CHCTR[ADC_CH_Uext_N] = CHCTR_base | ((ADC_CH_Uext_N) << VADC_G_CHCTR_RESREG_Pos);

    // result registers.
    VADC_G3->RCR[ADC_CH_IcellA_N] = 0;
    VADC_G3->RCR[ADC_CH_IcellB_N] = 0;
    VADC_G3->RCR[ADC_CH_IcellC_N] = 0;
    VADC_G3->RCR[ADC_CH_Uext_N] = 0;
}

ALWAYS_INLINE static int32_t adc_result(VADC_G_TypeDef* VADC_G, size_t N)
{
    return (VADC_G->RES[N] & VADC_G_RES_RESULT_Msk) >> VADC_G_RES_RESULT_Pos;
}

void ADC_IRQ_Handler(void)
{
    ADC_IRQ_G->SEFCLR = VADC_G_SEFCLR_SEV1_Msk;

//    CALC(adc);

    // Вызвать коллбэк.
    CALLBACK_CALL(adc.on_conversion);
}

#endif

static void adc_init_hw(M_adc* adc)
{
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

    // clock div.
    VADC->GLOBCFG = ((ADC_PRESCALER - 1) << VADC_GLOBCFG_DIVA_Pos) |
                    ((0) << VADC_GLOBCFG_DIVD_Pos) |
                    (VADC_GLOBCFG_DIVWC_Msk);
    __DSB();

    // configuration.
    // global conversion classes.
    VADC->GLOBICLASS[0] = ((ADC_ADDITIONAL_SAMPLE_TIME) << VADC_GLOBICLASS_STCS_Pos) |
                          ((0) << VADC_GLOBICLASS_CMS_Pos);

    // groups.
    adc_group0_init(adc);
    adc_group1_init(adc);
    adc_group2_init(adc);
    adc_group3_init(adc);

    // start-up.
    VADC_G0->ARBCFG = ((0b11) << VADC_G_ARBCFG_ANONC_Pos) |
                      ((1)    << VADC_G_ARBCFG_ARBM_Pos);
    VADC_G1->ARBCFG = ((0b11) << VADC_G_ARBCFG_ANONC_Pos) |
                      ((1)    << VADC_G_ARBCFG_ARBM_Pos);
    VADC_G2->ARBCFG = ((0b11) << VADC_G_ARBCFG_ANONC_Pos) |
                      ((1)    << VADC_G_ARBCFG_ARBM_Pos);
    VADC_G3->ARBCFG = ((0b11) << VADC_G_ARBCFG_ANONC_Pos) |
                      ((1)    << VADC_G_ARBCFG_ARBM_Pos);

    struct timeval tv;
    tv.tv_sec = 0; tv.tv_usec = ADC_WAKEUP_DELAY_US;
    sys_counter_delay(&tv);

    // calibration.
    VADC->GLOBCFG = VADC_GLOBCFG_SUCAL_Msk;
    while(((VADC_G0->ARBCFG & VADC_G_ARBCFG_CAL_Msk) != 0) ||
          ((VADC_G1->ARBCFG & VADC_G_ARBCFG_CAL_Msk) != 0) ||
          ((VADC_G2->ARBCFG & VADC_G_ARBCFG_CAL_Msk) != 0) ||
          ((VADC_G3->ARBCFG & VADC_G_ARBCFG_CAL_Msk) != 0)) __NOP();

    // interrupts.
    ADC_IRQ_G->SEVNP = ((ADC_IRQ_SR) << VADC_G_SEVNP_SEV1NP_Pos);

#endif
}



static status_t recalc_values(M_adc* adc)
{
    status_t res_status = STATUS_READY;

    // Напряжения сети.
    adc->m_Ua_gain = iq24_mul(adc->p_Ua_gain, conf.r_U_base_inv);
    adc->m_Ub_gain = iq24_mul(adc->p_Ub_gain, conf.r_U_base_inv);
    adc->m_Uc_gain = iq24_mul(adc->p_Uc_gain, conf.r_U_base_inv);

    // Токи сети.
    adc->m_Ia_gain = iq24_mul(adc->p_Ia_gain, conf.r_I_base_inv);
    adc->m_Ib_gain = iq24_mul(adc->p_Ib_gain, conf.r_I_base_inv);
    adc->m_Ic_gain = iq24_mul(adc->p_Ic_gain, conf.r_I_base_inv);

    // Напряжение выхода.
    adc->m_Uarm_gain = iq24_mul(adc->p_Uarm_gain, motor.r_r_U_base_inv);

    // Ток выхода.
    adc->m_Iarm_gain = iq24_mul(adc->p_Iarm_gain, motor.r_r_I_base_inv);

    // Ток резистора.
    adc->m_Ir_gain = iq24_mul(adc->p_Ir_gain, motor.r_r_I_base_inv);

    // Напряжения статора.
    adc->m_s_Ua_gain = iq24_mul(adc->p_s_Ua_gain, motor.r_s_U_base_inv);
    adc->m_s_Ub_gain = iq24_mul(adc->p_s_Ub_gain, motor.r_s_U_base_inv);
    adc->m_s_Uc_gain = iq24_mul(adc->p_s_Uc_gain, motor.r_s_U_base_inv);

    // Токи статора.
    adc->m_s_Ia_gain = iq24_mul(adc->p_s_Ia_gain, motor.r_s_I_base_inv);
    adc->m_s_Ib_gain = iq24_mul(adc->p_s_Ib_gain, motor.r_s_I_base_inv);
    adc->m_s_Ic_gain = iq24_mul(adc->p_s_Ic_gain, motor.r_s_I_base_inv);

    return res_status;
}


METHOD_INIT_IMPL(M_adc, adc)
{
    adc_init_hw(adc);

    IDLE((*adc));
}

METHOD_DEINIT_IMPL(M_adc, adc)
{
    adc->status = STATUS_NONE;
}

/*
 * Сетевое напряжение.
 */
static void calc_Uabc(M_adc* adc)
{
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    int32_t Ua_raw = adc_result(ADC_CH_Uph_G, ADC_CH_UphA_N);
    int32_t Ub_raw = adc_result(ADC_CH_Uph_G, ADC_CH_UphB_N);
    int32_t Uc_raw = adc_result(ADC_CH_Uph_G, ADC_CH_UphC_N);
#endif
#if defined(PORT_POSIX)
    int32_t Ua_raw = 0;
    int32_t Ub_raw = 0;
    int32_t Uc_raw = 0;
#endif

    adc->out_Ua_raw = Ua_raw;
    adc->out_Ub_raw = Ub_raw;
    adc->out_Uc_raw = Uc_raw;

    // IQ24 = IQ0 * IQ24.
    iq24_t Ua = (Ua_raw - adc->p_Ua_offset) * adc->m_Ua_gain;
    iq24_t Ub = (Ub_raw - adc->p_Ub_offset) * adc->m_Ub_gain;
    iq24_t Uc = (Uc_raw - adc->p_Uc_offset) * adc->m_Uc_gain;

    adc->out_Ua = Ua;
    adc->out_Ub = Ub;
    adc->out_Uc = Uc;
}

/*
 * Сетевой ток.
 */
static void calc_Iabc(M_adc* adc)
{
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    int32_t Ia_raw = adc_result(ADC_CH_Iph_G, ADC_CH_IphA_N);
    int32_t Ib_raw = adc_result(ADC_CH_Iph_G, ADC_CH_IphB_N);
    int32_t Ic_raw = adc_result(ADC_CH_Iph_G, ADC_CH_IphC_N);
#endif
#if defined(PORT_POSIX)
    int32_t Ia_raw = 0;
    int32_t Ib_raw = 0;
    int32_t Ic_raw = 0;
#endif

    adc->out_Ia_raw = Ia_raw;
    adc->out_Ib_raw = Ib_raw;
    adc->out_Ic_raw = Ic_raw;

    // IQ24 = IQ0 * IQ24.
    iq24_t Ia = (Ia_raw - adc->p_Ia_offset) * adc->m_Ia_gain;
    iq24_t Ib = (Ib_raw - adc->p_Ib_offset) * adc->m_Ib_gain;
    iq24_t Ic = (Ic_raw - adc->p_Ic_offset) * adc->m_Ic_gain;

    adc->out_Ia = Ia;
    adc->out_Ib = Ib;
    adc->out_Ic = Ic;
}

/*
 * Напряжение выхода.
 */
static void calc_Uout(M_adc* adc)
{
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    int32_t Uarm_raw = adc_result(ADC_CH_Udc_G, ADC_CH_Udc_N);
#endif
#if defined(PORT_POSIX)
    int32_t Uarm_raw = 0;
#endif

    adc->out_Uarm_raw = Uarm_raw;

    // IQ24 = IQ0 * IQ24.
    iq24_t Uarm = (Uarm_raw - adc->p_Uarm_offset) * adc->m_Uarm_gain;

    adc->out_Uarm = Uarm;
}

/*
 * Ток выхода.
 */
static void calc_Iout(M_adc* adc)
{
    int32_t Iarm_raw = 0;

    adc->out_Iarm_raw = Iarm_raw;

    // IQ24 = IQ0 * IQ24.
    iq24_t Iarm = (Iarm_raw - adc->p_Iarm_offset) * adc->m_Iarm_gain;

    adc->out_Iarm = Iarm;
}

/*
 * Ток резистора.
 */
static void calc_Ir(M_adc* adc)
{
    int32_t Ir_raw = 0;

    adc->out_Ir_raw = Ir_raw;

    // IQ24 = IQ0 * IQ24.
    iq24_t Ir = (Ir_raw - adc->p_Ir_offset) * adc->m_Ir_gain;

    adc->out_Iarm = Ir;
}

/*
 * Напряжение статора.
 */
static void calc_s_Uabc(M_adc* adc)
{
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    int32_t Ua_raw = adc_result(ADC_CH_Ucell_G, ADC_CH_UcellA_N);
    int32_t Ub_raw = adc_result(ADC_CH_Ucell_G, ADC_CH_UcellB_N);
    int32_t Uc_raw = adc_result(ADC_CH_Ucell_G, ADC_CH_UcellC_N);
#endif
#if defined(PORT_POSIX)
    int32_t Ua_raw = 0;
    int32_t Ub_raw = 0;
    int32_t Uc_raw = 0;
#endif

    adc->out_s_Ua_raw = Ua_raw;
    adc->out_s_Ub_raw = Ub_raw;
    adc->out_s_Uc_raw = Uc_raw;

    // IQ24 = IQ0 * IQ24.
    iq24_t Ua = (Ua_raw - adc->p_s_Ua_offset) * adc->m_s_Ua_gain;
    iq24_t Ub = (Ub_raw - adc->p_s_Ub_offset) * adc->m_s_Ub_gain;
    iq24_t Uc = (Uc_raw - adc->p_s_Uc_offset) * adc->m_s_Uc_gain;

    adc->out_s_Ua = Ua;
    adc->out_s_Ub = Ub;
    adc->out_s_Uc = Uc;
}

/*
 * Ток статора.
 */
static void calc_s_Iabc(M_adc* adc)
{
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    int32_t Ia_raw = adc_result(ADC_CH_Icell_G, ADC_CH_IcellA_N);
    int32_t Ib_raw = adc_result(ADC_CH_Icell_G, ADC_CH_IcellB_N);
    int32_t Ic_raw = adc_result(ADC_CH_Icell_G, ADC_CH_IcellC_N);
#endif
#if defined(PORT_POSIX)
    int32_t Ia_raw = 0;
    int32_t Ib_raw = 0;
    int32_t Ic_raw = 0;
#endif

    adc->out_s_Ia_raw = Ia_raw;
    adc->out_s_Ib_raw = Ib_raw;
    adc->out_s_Ic_raw = Ic_raw;

    // IQ24 = IQ0 * IQ24.
    iq24_t Ia = (Ia_raw - adc->p_s_Ia_offset) * adc->m_s_Ia_gain;
    iq24_t Ib = (Ib_raw - adc->p_s_Ib_offset) * adc->m_s_Ib_gain;
    iq24_t Ic = (Ic_raw - adc->p_s_Ic_offset) * adc->m_s_Ic_gain;

    adc->out_s_Ia = Ia;
    adc->out_s_Ib = Ib;
    adc->out_s_Ic = Ic;
}

METHOD_CALC_IMPL(M_adc, adc)
{
    //if(!(adc->control & CONTROL_ENABLE)) return;

    calc_Uabc(adc);
    calc_Iabc(adc);
    calc_Uout(adc);
    calc_Iout(adc);
    calc_Ir(adc);
    calc_s_Uabc(adc);
    calc_s_Iabc(adc);

    // Установим статус.
    adc->status = STATUS_VALID;

    // Вызвать коллбэк.
//    CALLBACK_CALL(adc->on_conversion);
}

METHOD_IDLE_IMPL(M_adc, adc)
{
    recalc_values(adc);
}
