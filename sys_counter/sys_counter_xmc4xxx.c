#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "sys_counter_xmc4xxx.h"
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <errno.h>
#include "hardware/config.h"
#include "interrupts/interrupts.h"
#include "utils/barrier.h"



//! Тип структуры высокоточного таймера.
typedef struct _Sys_Counter {
    uint32_t counter; //!< Счётчик переполнений таймера.
} sys_counter_t;

//! Высокоточный таймер.
static sys_counter_t system_counter;

// Параметры таймеров.
// Pre.
#define CCU_PRESCALER_N_PRE 1
#define CCU_PRESCALER_PRE 0b0000
#define CCU_PERIOD_PRE 120
// Lo.
#define CCU_PRESCALER_N_LO 1
#define CCU_PRESCALER_LO 0b0000
#define CCU_PERIOD_LO 1000
// Hi.
#define CCU_PRESCALER_N_HI 1
#define CCU_PRESCALER_HI 0b0000
#define CCU_PERIOD_HI 1000


static void sys_counter_priph_init(void)
{
    // configure.
    // pre.
    SYS_CNT_TIM_CCU4_CC4_PRE->PSC = CCU_PRESCALER_PRE;
    SYS_CNT_TIM_CCU4_CC4_PRE->PRS = CCU_PERIOD_PRE - 1;
    // lo.
    SYS_CNT_TIM_CCU4_CC4_LO->PSC = CCU_PRESCALER_LO;
    SYS_CNT_TIM_CCU4_CC4_LO->PRS = CCU_PERIOD_LO - 1;
    // hi.
    SYS_CNT_TIM_CCU4_CC4_HI->PSC = CCU_PRESCALER_HI;
    SYS_CNT_TIM_CCU4_CC4_HI->PRS = CCU_PERIOD_HI - 1;

    // irqs.
    SYS_CNT_TIM_CCU4_CC4_HI->INTE = CCU4_CC4_INTE_PME_Msk;
    SYS_CNT_TIM_CCU4_CC4_HI->SRS = SYS_CNT_TIM_SR << CCU4_CC4_SRS_POSR_Pos;

    // shadow transfer.
    SYS_CNT_TIM_CCU4->GCSS = SYS_CNT_TIM_SHADOW_TRANSFER_Msk;

    // clear flags.
    SYS_CNT_TIM_CCU4_CC4_HI->SWR = CCU4_CC4_SWR_RPM_Msk;

    // concat.
    SYS_CNT_TIM_CCU4_CC4_LO->CMC = CCU4_CC4_CMC_TCE_Msk;
    SYS_CNT_TIM_CCU4_CC4_HI->CMC = CCU4_CC4_CMC_TCE_Msk;

    // idle.
    SYS_CNT_TIM_CCU4->GIDLC = SYS_CNT_TIM_IDLE_CLR_Msk;
}


void sys_counter_init(void)
{
    system_counter.counter = 0;
    
    sys_counter_priph_init();
}

void SYS_CNT_TIM_IRQ_Handler(void)
{
    SYS_CNT_TIM_CCU4_CC4_HI->SWR = CCU4_CC4_SWR_RPM_Msk;
    //STDIO_UART_USIC_CH->TBUF[0] = '.';
    system_counter.counter ++;
}

void sys_counter_irq_set_enabled(bool enabled)
{
    if(enabled){
        sys_counter_irq_enable();
    }else{
        sys_counter_irq_disable();
    }
}

bool sys_counter_irq_enabled(void)
{
    return (SYS_CNT_TIM_CCU4_CC4_HI->INTE & CCU4_CC4_INTE_PME_Msk) != 0;
}

void sys_counter_irq_enable(void)
{
    SYS_CNT_TIM_CCU4_CC4_HI->INTE = CCU4_CC4_INTE_PME_Msk;
}

void sys_counter_irq_disable(void)
{
    SYS_CNT_TIM_CCU4_CC4_HI->INTE = 0;
}

void sys_counter_set_running(bool running)
{
    if(running){
    	sys_counter_start();
    }else{
    	sys_counter_stop();
    }
}

bool sys_counter_running(void)
{
    return (SYS_CNT_TIM_CCU4_CC4_PRE->TCST & CCU4_CC4_TCST_TRB_Msk) != 0;
}

void sys_counter_start(void)
{
    SYS_CNT_TIM_CCU4_CC4_HI->TCSET = CCU4_CC4_TCSET_TRBS_Msk;
    SYS_CNT_TIM_CCU4_CC4_LO->TCSET = CCU4_CC4_TCSET_TRBS_Msk;
    SYS_CNT_TIM_CCU4_CC4_PRE->TCSET = CCU4_CC4_TCSET_TRBS_Msk;
}

void sys_counter_stop(void)
{
    SYS_CNT_TIM_CCU4_CC4_PRE->TCCLR = CCU4_CC4_TCCLR_TRBC_Msk;
    SYS_CNT_TIM_CCU4_CC4_LO->TCCLR = CCU4_CC4_TCCLR_TRBC_Msk;
    SYS_CNT_TIM_CCU4_CC4_HI->TCCLR = CCU4_CC4_TCCLR_TRBC_Msk;
}

void sys_counter_reset(void)
{
    SYS_CNT_TIM_CCU4_CC4_PRE->TCCLR = CCU4_CC4_TCCLR_TCC_Msk;
    SYS_CNT_TIM_CCU4_CC4_LO->TCCLR = CCU4_CC4_TCCLR_TCC_Msk;
    SYS_CNT_TIM_CCU4_CC4_HI->TCCLR = CCU4_CC4_TCCLR_TCC_Msk;
}

__attribute__((noinline))
static uint32_t sys_counter_get_usecs(void)
{
    // Актуальные значения счётчиков.
    uint32_t cnt_us_lo = 0;
    uint32_t cnt_us_hi = 0;

    // Считаем значение счётчиков.
    uint32_t cnt_us_lo1 = SYS_CNT_TIM_CCU4_CC4_LO->TIMER;
    barrier();
    uint32_t cnt_us_hi1 = SYS_CNT_TIM_CCU4_CC4_HI->TIMER;
    barrier();
    uint32_t cnt_us_lo2 = SYS_CNT_TIM_CCU4_CC4_LO->TIMER;
    barrier();
    uint32_t cnt_us_hi2 = SYS_CNT_TIM_CCU4_CC4_HI->TIMER;
    barrier();

    // Обработка переполнения.
    if(cnt_us_lo1 <= cnt_us_lo2){
        cnt_us_lo = cnt_us_lo1;
        cnt_us_hi = cnt_us_hi1;
    }else{ // cnt_us_lo1 > cnt_us_lo2
        cnt_us_lo = cnt_us_lo2;
        cnt_us_hi = cnt_us_hi2;
    }

    return cnt_us_hi * 1000 + cnt_us_lo;
}

__attribute__((noinline))
void sys_counter_value(struct timeval* tv)
{
    if(tv == NULL) return;
    
//    // Сохраним флаг разрешения прерывания.
//    bool irq_enabled = sys_counter_irq_enabled();
//    // Запретим прерывание переполнения.
//    sys_counter_irq_disable();
    
    // Запрет прерываний на короткое время.
    interrupts_disable();

    // Считаем значение счётчиков.
    uint32_t cnt_us = sys_counter_get_usecs();
    uint32_t cnt_s = system_counter.counter;
    uint32_t cnt_us2 = sys_counter_get_usecs();
    
    // Разрешение прерываний.
    interrupts_enable();

//    // Если прерывание переполнения было разрешено.
//    if(irq_enabled){
//        // Вновь разрешим прерывание переполнения.
//    	sys_counter_irq_enable();
//    }

    // Если он меньше предыдущего значения - таймер переполнился.
    if(cnt_us2 < cnt_us){
        // Присвоим новое значение.
        cnt_us = cnt_us2;
        // И увеличим счётчик секунд.
        cnt_s ++;

        //SYS_CNT_TIM_CCU4_CC4_HI->SWS = CCU4_CC4_SWS_SPM_Msk;
    }
    
    tv->tv_usec = cnt_us;
    tv->tv_sec = cnt_s;
}

void sys_counter_delay(struct timeval* tv)
{
	struct timeval tv_cur;
    struct timeval tv_dt;
    struct timeval tv_end;
    //struct timeval tv_start;

    tv_dt.tv_sec = tv->tv_sec;
    tv_dt.tv_usec = tv->tv_usec;

    sys_counter_value(&tv_cur);
    //tv_start.tv_sec = tv_cur.tv_sec;
    //tv_start.tv_usec = tv_cur.tv_usec;
    timeradd(&tv_cur, &tv_dt, &tv_end);

    for(;;){
		if(timercmp(&tv_cur, &tv_end, >=)){
			break;
		}
    	sys_counter_value(&tv_cur);
    }
}

#if defined(SYS_COUNTER_CLOCK_GETTIME) && SYS_COUNTER_CLOCK_GETTIME == 1

int clock_gettime (clockid_t clock_id, struct timespec *tp)
{
    if(clock_id != CLOCK_MONOTONIC){
        errno = EINVAL;
        return -1;
    }
    if(tp == NULL){
        errno = EFAULT;
        return -1;
    }

    struct timeval tv;
    sys_counter_value(&tv);

    tp->tv_sec = tv.tv_sec;
    tp->tv_nsec = tv.tv_usec * 1000;

    return 0;
}

#endif

#endif
