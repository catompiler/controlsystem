#include "port.h"

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "net_timer_xmc4xxx.h"
#include <assert.h>
#include <stddef.h>
#include "modules/modules.h"
#include "hardware/config.h"


static void timer_callback(void* arg)
{
    M_net_timer* net_tmr = (M_net_timer*)arg;

    assert(net_tmr != NULL);

    net_tmr->out_counter ++;

    CALLBACK_CALL(net_tmr->on_timeout);
}

void NET_TIM_IRQ_Handler(void)
{
    NET_TIM_CCU4_CC4->SWR = CCU4_CC4_SWR_RPM_Msk;

    timer_callback(&net_tim);
}

#define CCU_PRESCALER_N 4
#define CCU_PRESCALER 0b0010
#define CCU_PERIOD (CPU_FREQ) / (CCU_PRESCALER_N) / (NET_TIMER_TICKS_FREQ)


static int timer_init_impl(M_net_timer* net_tmr)
{
    // configure.
    NET_TIM_CCU4_CC4->PSC = CCU_PRESCALER;
    NET_TIM_CCU4_CC4->PRS = CCU_PERIOD - 1;
    // shadow transfer.
    NET_TIM_CCU4->GCSS = NET_TIM_SHADOW_TRANSFER_Msk;

    // irqs.
    NET_TIM_CCU4_CC4->INTE = CCU4_CC4_INTE_PME_Msk;
    NET_TIM_CCU4_CC4->SRS = NET_TIM_SR << CCU4_CC4_SRS_POSR_Pos;
    // clear.
    NET_TIM_CCU4_CC4->SWR = CCU4_CC4_SWR_RPM_Msk;

    // idle.
    NET_TIM_CCU4->GIDLC = NET_TIM_IDLE_CLR_Msk;

    return 0;
}

static int timer_start_impl(M_net_timer* net_tmr)
{
    // start.
    NET_TIM_CCU4_CC4->TCSET = CCU4_CC4_TCSET_TRBS_Msk;

    return 0;
}

static int timer_stop_impl(M_net_timer* net_tmr)
{
    // start.
    NET_TIM_CCU4_CC4->TCCLR = CCU4_CC4_TCCLR_TRBC_Msk;

    return 0;
}

static int timer_isrunning_impl(M_net_timer* net_tmr)
{
    return (NET_TIM_CCU4_CC4->TCST & CCU4_CC4_TCST_TRB_Msk) != 0;
}

static void timer_deinit_impl(M_net_timer* net_tmr)
{
    NET_TIM_CCU4->GIDLS = NET_TIM_IDLE_SET_Msk;
}


METHOD_INIT_IMPL(M_net_timer, net_tmr)
{
    net_tmr->control = 0;
    net_tmr->status = 0;
    net_tmr->out_counter = 0;

    int res = timer_init_impl(net_tmr);

    if(res == 0){
        net_tmr->status = NET_TIMER_STATUS_READY;
    }else{
        net_tmr->status = NET_TIMER_STATUS_ERROR;
    }
}

METHOD_DEINIT_IMPL(M_net_timer, net_tmr)
{
    timer_deinit_impl(net_tmr);

    net_tmr->status = NET_TIMER_STATUS_NONE;
}

METHOD_CONTROL_IMPL(M_net_timer, net_tmr)
{
    if(!(net_tmr->status & NET_TIMER_STATUS_READY)){
        return;
    }

    if(net_tmr->control & NET_TIMER_CONTROL_ENABLE){
        //if(!(net_tmr->status & NET_TIMER_STATUS_RUN)){
        if(!timer_isrunning_impl(net_tmr)){
            int res = timer_start_impl(net_tmr);
            if(res == 0){
                net_tmr->status = NET_TIMER_STATUS_READY | NET_TIMER_STATUS_RUN;
            }else{
                net_tmr->status = NET_TIMER_STATUS_ERROR;
            }
        }
    }else{ // !(net_tmr->control & NET_TIMER_CONTROL_ENABLE)
        //if(net_tmr->status & NET_TIMER_STATUS_RUN){
        if(timer_isrunning_impl(net_tmr)){
            int res = timer_stop_impl(net_tmr);
            if(res == 0){
                net_tmr->status = NET_TIMER_STATUS_READY;
            }else{
                net_tmr->status = NET_TIMER_STATUS_ERROR;
            }
        }
    }
}

#endif
