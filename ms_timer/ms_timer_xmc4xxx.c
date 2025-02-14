#include "port.h"

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "ms_timer_xmc4xxx.h"
#include <assert.h>
#include <stddef.h>
#include "modules/modules.h"
#include "hardware/config.h"


static void timer_callback(void* arg)
{
    M_ms_timer* ms_tmr = (M_ms_timer*)arg;

    assert(ms_tmr != NULL);

    ms_tmr->out_counter ++;

    CALLBACK_CALL(ms_tmr->on_timeout);
}

void MS_TIM_IRQ_Handler(void)
{
    MS_TIM_CCU4_CC4->SWR = CCU4_CC4_SWR_RPM_Msk;

    timer_callback(&ms_tim);
}

#define CCU_PRESCALER_N 4
#define CCU_PRESCALER 0b0010
#define CCU_PERIOD (CPU_FREQ) / (CCU_PRESCALER_N) / (MS_TIMER_TICKS_FREQ)


static int timer_init_impl(M_ms_timer* ms_tmr)
{
    // configure.
    MS_TIM_CCU4_CC4->PSC = CCU_PRESCALER;
    MS_TIM_CCU4_CC4->PRS = CCU_PERIOD - 1;
    // shadow transfer.
    MS_TIM_CCU4->GCSS = MS_TIM_SHADOW_TRANSFER_Msk;

    // irqs.
    MS_TIM_CCU4_CC4->INTE = CCU4_CC4_INTE_PME_Msk;
    MS_TIM_CCU4_CC4->SRS = MS_TIM_SR << CCU4_CC4_SRS_POSR_Pos;
    // clear.
    MS_TIM_CCU4_CC4->SWR = CCU4_CC4_SWR_RPM_Msk;

    // idle.
    MS_TIM_CCU4->GIDLC = MS_TIM_IDLE_CLR_Msk;

    return 0;
}

static int timer_start_impl(M_ms_timer* ms_tmr)
{
    // start.
    MS_TIM_CCU4_CC4->TCSET = CCU4_CC4_TCSET_TRBS_Msk;

    return 0;
}

static int timer_stop_impl(M_ms_timer* ms_tmr)
{
    // start.
    MS_TIM_CCU4_CC4->TCCLR = CCU4_CC4_TCCLR_TRBC_Msk;

    return 0;
}

static int timer_isrunning_impl(M_ms_timer* ms_tmr)
{
    return (MS_TIM_CCU4_CC4->TCST & CCU4_CC4_TCST_TRB_Msk) != 0;
}

static void timer_deinit_impl(M_ms_timer* ms_tmr)
{
    MS_TIM_CCU4->GIDLS = MS_TIM_IDLE_SET_Msk;
}


METHOD_INIT_IMPL(M_ms_timer, ms_tmr)
{
    ms_tmr->control = 0;
    ms_tmr->status = 0;
    ms_tmr->out_counter = 0;

    int res = timer_init_impl(ms_tmr);

    if(res == 0){
        ms_tmr->status = MS_TIMER_STATUS_READY;
    }else{
        ms_tmr->status = MS_TIMER_STATUS_ERROR;
    }
}

METHOD_DEINIT_IMPL(M_ms_timer, ms_tmr)
{
    timer_deinit_impl(ms_tmr);

    ms_tmr->status = MS_TIMER_STATUS_NONE;
}

METHOD_CONTROL_IMPL(M_ms_timer, ms_tmr)
{
    if(!(ms_tmr->status & MS_TIMER_STATUS_READY)){
        return;
    }

    if(ms_tmr->control & MS_TIMER_CONTROL_ENABLE){
        //if(!(ms_tmr->status & MS_TIMER_STATUS_RUN)){
        if(!timer_isrunning_impl(ms_tmr)){
            int res = timer_start_impl(ms_tmr);
            if(res == 0){
                ms_tmr->status = MS_TIMER_STATUS_READY | MS_TIMER_STATUS_RUN;
            }else{
                ms_tmr->status = MS_TIMER_STATUS_ERROR;
            }
        }
    }else{ // !(ms_tmr->control & MS_TIMER_CONTROL_ENABLE)
        //if(ms_tmr->status & MS_TIMER_STATUS_RUN){
        if(timer_isrunning_impl(ms_tmr)){
            int res = timer_stop_impl(ms_tmr);
            if(res == 0){
                ms_tmr->status = MS_TIMER_STATUS_READY;
            }else{
                ms_tmr->status = MS_TIMER_STATUS_ERROR;
            }
        }
    }
}

#endif
