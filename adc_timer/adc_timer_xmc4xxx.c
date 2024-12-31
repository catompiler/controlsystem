#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "adc_timer_xmc4xxx.h"
#include <assert.h>
#include <stddef.h>
#include "modules/modules.h"
#include "hardware/config.h"


static void timer_callback(void* arg)
{
    M_adc_timer* adc_tmr = (M_adc_timer*)arg;

    assert(adc_tmr != NULL);

    adc_tmr->out_counter ++;

    CALLBACK_CALL(adc_tmr->on_timeout);
}

void ADC_TIM_IRQ_Handler(void)
{
    ADC_TIM_CCU4_CC4->SWR = CCU4_CC4_SWR_RPM_Msk;

    timer_callback(&adc_tim);
}

#define CCU_PRESCALER_N 4
#define CCU_PRESCALER 0b0010
#define CCU_PERIOD (CPU_FREQ) / (CCU_PRESCALER_N) / (ADC_TIMER_TICKS_FREQ)


static int timer_init_impl(M_adc_timer* adc_tmr)
{
    // configure.
    ADC_TIM_CCU4_CC4->PSC = CCU_PRESCALER;
    ADC_TIM_CCU4_CC4->PRS = CCU_PERIOD - 1;

    // irqs.
    ADC_TIM_CCU4_CC4->INTE = CCU4_CC4_INTE_PME_Msk;
    ADC_TIM_CCU4_CC4->SRS = ADC_TIM_SR << CCU4_CC4_SRS_POSR_Pos;

    // idle.
    ADC_TIM_CCU4->GIDLC = ADC_TIM_IDLE_CLR_Msk;

    return 0;
}

static int timer_start_impl(M_adc_timer* adc_tmr)
{
    // start.
    ADC_TIM_CCU4_CC4->TCSET = CCU4_CC4_TCSET_TRBS_Msk;

    return 0;
}

static int timer_stop_impl(M_adc_timer* adc_tmr)
{
    // start.
    ADC_TIM_CCU4_CC4->TCCLR = CCU4_CC4_TCCLR_TRBC_Msk;

    return 0;
}

static int timer_isrunning_impl(M_adc_timer* adc_tmr)
{
    return (ADC_TIM_CCU4_CC4->TCST & CCU4_CC4_TCST_TRB_Msk) != 0;
}

static void timer_deinit_impl(M_adc_timer* adc_tmr)
{
    ADC_TIM_CCU4->GIDLS = ADC_TIM_IDLE_SET_Msk;
}


METHOD_INIT_IMPL(M_adc_timer, adc_tmr)
{
    adc_tmr->control = 0;
    adc_tmr->status = 0;
    adc_tmr->out_counter = 0;

    int res = timer_init_impl(adc_tmr);

    if(res == 0){
        adc_tmr->status = ADC_TIMER_STATUS_READY;
    }else{
        adc_tmr->status = ADC_TIMER_STATUS_ERROR;
    }
}

METHOD_DEINIT_IMPL(M_adc_timer, adc_tmr)
{
    timer_deinit_impl(adc_tmr);

    adc_tmr->status = ADC_TIMER_STATUS_NONE;
}

METHOD_CONTROL_IMPL(M_adc_timer, adc_tmr)
{
    if(!(adc_tmr->status & ADC_TIMER_STATUS_READY)){
        return;
    }

    if(adc_tmr->control & ADC_TIMER_CONTROL_ENABLE){
        //if(!(adc_tmr->status & ADC_TIMER_STATUS_RUN)){
        if(!timer_isrunning_impl(adc_tmr)){
            int res = timer_start_impl(adc_tmr);
            if(res == 0){
                adc_tmr->status = ADC_TIMER_STATUS_READY | ADC_TIMER_STATUS_RUN;
            }else{
                adc_tmr->status = ADC_TIMER_STATUS_ERROR;
            }
        }
    }else{ // !(adc_tmr->control & ADC_TIMER_CONTROL_ENABLE)
        //if(adc_tmr->status & ADC_TIMER_STATUS_RUN){
        if(timer_isrunning_impl(adc_tmr)){
            int res = timer_stop_impl(adc_tmr);
            if(res == 0){
                adc_tmr->status = ADC_TIMER_STATUS_READY;
            }else{
                adc_tmr->status = ADC_TIMER_STATUS_ERROR;
            }
        }
    }
}

#endif
