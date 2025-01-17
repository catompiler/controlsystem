#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "sys_timer_xmc4xxx.h"
#include <assert.h>
#include <stddef.h>
#include "modules/modules.h"
#include "hardware/config.h"


static void timer_callback(void* arg)
{
    M_sys_timer* sys_tmr = (M_sys_timer*)arg;

    assert(sys_tmr != NULL);

    sys_tmr->out_counter ++;

    CALLBACK_CALL(sys_tmr->on_timeout);
}

void SYS_TIM_IRQ_Handler(void)
{
    SYS_TIM_CCU4_CC4->SWR = CCU4_CC4_SWR_RPM_Msk;

    timer_callback(&sys_tim);
}

#define CCU_PRESCALER_N 0
#define CCU_PRESCALER 0b0000
#define CCU_PERIOD 10


static int timer_init_impl(M_sys_timer* sys_tmr)
{
    // configure.
    SYS_TIM_CCU4_CC4->PSC = CCU_PRESCALER;
    SYS_TIM_CCU4_CC4->PRS = CCU_PERIOD - 1;
    // one-shot.
    SYS_TIM_CCU4_CC4->TC = CCU4_CC4_TC_TSSM_Msk;
    // shadow transfer.
    SYS_TIM_CCU4->GCSS = SYS_TIM_SHADOW_TRANSFER_Msk;

    // irqs.
    SYS_TIM_CCU4_CC4->INTE = CCU4_CC4_INTE_PME_Msk;
    SYS_TIM_CCU4_CC4->SRS = SYS_TIM_SR << CCU4_CC4_SRS_POSR_Pos;
    // clear.
    SYS_TIM_CCU4_CC4->SWR = CCU4_CC4_SWR_RPM_Msk;

    // idle.
    SYS_TIM_CCU4->GIDLC = SYS_TIM_IDLE_CLR_Msk;

    return 0;
}

static int timer_start_impl(M_sys_timer* sys_tmr)
{
    // start.
    SYS_TIM_CCU4_CC4->TCSET = CCU4_CC4_TCSET_TRBS_Msk;

    return 0;
}

static int timer_stop_impl(M_sys_timer* sys_tmr)
{
    // stop.
    SYS_TIM_CCU4_CC4->TCCLR = CCU4_CC4_TCCLR_TRBC_Msk;

    return 0;
}

static int timer_isrunning_impl(M_sys_timer* sys_tmr)
{
    return (SYS_TIM_CCU4_CC4->TCST & CCU4_CC4_TCST_TRB_Msk) != 0;
}

static void timer_deinit_impl(M_sys_timer* sys_tmr)
{
    SYS_TIM_CCU4->GIDLS = SYS_TIM_IDLE_SET_Msk;
}


METHOD_INIT_IMPL(M_sys_timer, sys_tmr)
{
    sys_tmr->control = 0;
    sys_tmr->status = 0;
    sys_tmr->out_counter = 0;

    int res = timer_init_impl(sys_tmr);

    if(res == 0){
        sys_tmr->status = SYS_TIMER_STATUS_READY;
    }else{
        sys_tmr->status = SYS_TIMER_STATUS_ERROR;
    }
}

METHOD_DEINIT_IMPL(M_sys_timer, sys_tmr)
{
    timer_deinit_impl(sys_tmr);

    sys_tmr->status = SYS_TIMER_STATUS_NONE;
}

METHOD_CONTROL_IMPL(M_sys_timer, sys_tmr)
{
    if(!(sys_tmr->status & SYS_TIMER_STATUS_READY)){
        return;
    }

    if(sys_tmr->control & SYS_TIMER_CONTROL_ENABLE){
        //if(!(sys_tmr->status & SYS_TIMER_STATUS_RUN)){
        if(!timer_isrunning_impl(sys_tmr)){
            int res = timer_start_impl(sys_tmr);
            if(res == 0){
                sys_tmr->status = SYS_TIMER_STATUS_READY | SYS_TIMER_STATUS_RUN;
            }else{
                sys_tmr->status = SYS_TIMER_STATUS_ERROR;
            }
        }
    }else{ // !(sys_tmr->control & SYS_TIMER_CONTROL_ENABLE)
        //if(sys_tmr->status & SYS_TIMER_STATUS_RUN){
        if(timer_isrunning_impl(sys_tmr)){
            int res = timer_stop_impl(sys_tmr);
            if(res == 0){
                sys_tmr->status = SYS_TIMER_STATUS_READY;
            }else{
                sys_tmr->status = SYS_TIMER_STATUS_ERROR;
            }
        }
    }
}

#endif
