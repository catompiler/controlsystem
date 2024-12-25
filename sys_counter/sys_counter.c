#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include "hardware/config.h"
#include "sys_counter.h"


//! Тип структуры высокоточного таймера.
typedef struct _Sys_Counter {
    uint32_t counter; //!< Счётчик переполнений таймера.
} sys_counter_t;

//! Высокоточный таймер.
static sys_counter_t system_counter;


#define CCU_PRESCALER_N 0
#define CCU_PRESCALER 0b0000
#define CCU_PERIOD (CPU_FREQ) / (SYS_COUNTER_PERIOD_TICKS)


static void sys_counter_priph_init(void)
{
    // configure.
    SYS_TIM_CCU4_CC4->PSC = CCU_PRESCALER;
    SYS_TIM_CCU4_CC4->PRS = CCU_PERIOD - 1;

    // irqs.
    SYS_TIM_CCU4_CC4->INTE = CCU4_CC4_INTE_PME_Msk;
    SYS_TIM_CCU4_CC4->SRS = SYS_CNT_TIM_SR << CCU4_CC4_SRS_POSR_Pos;

    // idle.
    SYS_TIM_CCU4->GIDLC = SYS_TIM_IDLE_CLR_Msk;
}


void sys_counter_init(void)
{
    system_counter.counter = 0;
    
    sys_counter_priph_init();
}

void SYS_CNT_TIM_IRQ_Handler(void)
{
    SYS_CNT_TIM_CCU4_CC4->SWR = CCU4_CC4_SWR_RPM_Msk;

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
    return (SYS_TIM_CCU4_CC4->INTE & CCU4_CC4_INTE_PME_Msk) != 0;
}

void sys_counter_irq_enable(void)
{
    SYS_TIM_CCU4_CC4->INTE = CCU4_CC4_INTE_PME_Msk;
}

void sys_counter_irq_disable(void)
{
    SYS_TIM_CCU4_CC4->INTE = 0;
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
    return (SYS_CNT_TIM_CCU4_CC4->TCST & CCU4_CC4_TCST_TRB_Msk) != 0;
}

void sys_counter_start(void)
{
    SYS_CNT_TIM_CCU4_CC4->TCSET = CCU4_CC4_TCSET_TRBS_Msk;
}

void sys_counter_stop(void)
{
    SYS_CNT_TIM_CCU4_CC4->TCCLR = CCU4_CC4_TCCLR_TRBC_Msk;
}

void sys_counter_reset(void)
{
    SYS_CNT_TIM_CCU4_CC4->TCCLR = CCU4_CC4_TCCLR_TCC_Msk;
}

__attribute__((noinline))
void sys_counter_value(struct timeval* tv)
{
    if(tv == NULL) return;
    
    // Сохраним флаг разрешения прерывания.
    bool irq_enabled = sys_counter_irq_enabled();
    // Запретим прерывание переполнения.
    sys_counter_irq_disable();
    
    // Считаем значение счётчиков.
    uint32_t cnt_us = SYS_CNT_TIM_CCU4_CC4->TIMER;
    uint32_t cnt_s = system_counter.counter;
    
    // Защита от переполнения.
    // Повторно считаем счётчик таймера.
    uint32_t cnt_us2 = SYS_CNT_TIM_CCU4_CC4->TIMER;
    
    // Если прерывание переполнения было разрешено.
    if(irq_enabled){
        // Вновь разрешим прерывание переполнения.
    	sys_counter_irq_enable();
    }
    
    // Если он меньше предыдущего значения - таймер переполнился.
    if(cnt_us2 < cnt_us){
        // Присвоим новое значение.
        cnt_us = cnt_us2;
        // И увеличим счётчик секунд.
        cnt_s ++;
    }
    
    tv->tv_usec = cnt_us;
    tv->tv_sec = cnt_s;
}

void sys_counter_delay(struct timeval* tv)
{
	struct timeval tv_cur;
    struct timeval tv_dt;
    struct timeval tv_end;

    tv_dt.tv_sec = tv->tv_sec;
    tv_dt.tv_usec = tv->tv_usec;

    sys_counter_value(&tv_cur);
    timeradd(&tv_cur, &tv_dt, &tv_end);

    for(;;){
		if(timercmp(&tv_cur, &tv_end, >=)){
			break;
		}
    	sys_counter_value(&tv_cur);
    }
}

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

