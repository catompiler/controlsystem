#include "modules/modules.h"
#include "sys_main.h"
#include <assert.h>

//#include <sys/time.h>
//#include <stdio.h>


//static void sys_tim_handler(void* arg);


static void adc_tim_handler(void* arg)
{
    CALC(adc);

    M_sys_main* sys = (M_sys_main*)arg;
    assert(sys != NULL);

    // Если системный таймер однократного счёта, то запустим его.
#if defined(SYS_TIMER_ONE_SHOT) && SYS_TIMER_ONE_SHOT == 1

    //sys_tim_handler(arg);

    sys_tim.control = SYS_TIMER_CONTROL_ENABLE;
    CONTROL(sys_tim);

    // TODO: reaction on timer error.
    if(sys_tim.status & SYS_TIMER_STATUS_ERROR){
        sys->errors |= SYS_MAIN_ERROR_INTERNAL;
        sys->state = SYS_MAIN_STATE_ERROR;
    }

//    static struct timespec t_old;
//    struct timespec t;
//
//    clock_gettime(CLOCK_MONOTONIC, &t);
//
//    long dnsec = t.tv_nsec - t_old.tv_nsec;
//    if(t.tv_sec > t_old.tv_sec) dnsec += 1000000000LL;
//
//    printf("%ld us\n", dnsec / 1000);
//    t_old.tv_sec = t.tv_sec;
//    t_old.tv_nsec = t.tv_nsec;


//    struct timespec t;
//    clock_gettime(CLOCK_MONOTONIC, &t);
//    printf("%ld s %ld ns\n", t.tv_sec, t.tv_nsec);

#endif
}

static void sys_tim_handler(void* arg)
{
    M_sys_main* sys = (M_sys_main*)arg;
    assert(sys != NULL);

    CALC((*sys));
}

static void ms_tim_handler(void* arg)
{
    M_sys_main* sys = (M_sys_main*)arg;
    assert(sys != NULL);

//    struct timeval tv;
//    gettimeofday(&tv, NULL);
//    printf("%ld s %ld us\n", tv.tv_sec, tv.tv_usec);
}


//static void check_modules_error_status(M_sys_main* sys)
//{
//    status_t status = STATUS_NONE;
//
//    status |= adc.status;
//    status |= adc_tim.status;
//    status |= sys_tim.status;
//    status |= ms_tim.status;
//
//    status &= STATUS_ERROR;
//}

METHOD_INIT_IMPL(M_sys_main, sys)
{
    // Инициализация внутренних переменных.
    sys->control = SYS_MAIN_CONTROL_NONE;
    sys->status = SYS_MAIN_STATUS_NONE;
    sys->errors = SYS_MAIN_ERROR_NONE;
    sys->warnings = SYS_MAIN_WARNING_NONE;
    sys->state = SYS_MAIN_STATE_NONE;


    // Инициализация модулей.

    status_t init_status = STATUS_NONE;

    // Базовый конфиг.
    INIT(conf);

    // Осциллограф.
    INIT(dlog);

    // АЦП.
    INIT(adc);

    // Таймер АЦП.
    INIT(adc_tim);
    CALLBACK_PROC(adc_tim.on_timeout) = adc_tim_handler;
    CALLBACK_ARG(adc_tim.on_timeout) = (void*)sys;
    if(adc_tim.status & ADC_TIMER_STATUS_ERROR){
        init_status = STATUS_ERROR;
    }

    // Системный таймер.
    INIT(sys_tim);
    CALLBACK_PROC(sys_tim.on_timeout) = sys_tim_handler;
    CALLBACK_ARG(sys_tim.on_timeout) = (void*)sys;
    if(sys_tim.status & SYS_TIMER_STATUS_ERROR){
        init_status = STATUS_ERROR;
    }

    // Медленный таймер.
    INIT(ms_tim);
    CALLBACK_PROC(ms_tim.on_timeout) = ms_tim_handler;
    CALLBACK_ARG(ms_tim.on_timeout) = (void*)sys;
    if(ms_tim.status & MS_TIMER_STATUS_ERROR){
        init_status = STATUS_ERROR;
    }

    // Включение в работу модулей.
    // Не будем включать модули,
    // если инициализация завершена с ошибкой.
    if(!(init_status & STATUS_ERROR)){

        // Запуск таймера АЦП.
        adc_tim.control = ADC_TIMER_CONTROL_ENABLE;
        CONTROL(adc_tim);
        if(!(adc_tim.status & ADC_TIMER_STATUS_RUN)){
            init_status = STATUS_ERROR;
        }

        // Запуск медленного таймера.
        ms_tim.control = MS_TIMER_CONTROL_ENABLE;
        CONTROL(ms_tim);
        if(!(ms_tim.status & MS_TIMER_STATUS_RUN)){
            init_status = STATUS_ERROR;
        }

    }

    // Проверка ошибок инициализации.
    // Если нет ошибок - продолжим инициализацию.
    if(!(init_status & STATUS_ERROR)){
        sys->state = SYS_MAIN_STATE_INIT;
    }else{ // Иначе установим статус ошибки.
        // TODO: reaction on init error.
        sys->errors |= SYS_MAIN_ERROR_INTERNAL;
        sys->status = SYS_MAIN_STATUS_ERROR;
    }
}

METHOD_DEINIT_IMPL(M_sys_main, sys)
{
    // Деинициализация модулей.
    DEINIT(adc_tim);
    DEINIT(sys_tim);
    DEINIT(ms_tim);
    DEINIT(adc);
    DEINIT(dlog);
    DEINIT(conf);

    // Сброс внутренних переменных.
    sys->control = SYS_MAIN_CONTROL_NONE;
    sys->status = SYS_MAIN_STATUS_NONE;
    sys->errors = SYS_MAIN_ERROR_NONE;
    sys->warnings = SYS_MAIN_WARNING_NONE;
    sys->state = SYS_MAIN_STATE_NONE;
}


static void FSM_state_none(M_sys_main* sys)
{
}

static void FSM_state_init(M_sys_main* sys)
{
}

static void FSM_state_idle(M_sys_main* sys)
{
}

static void FSM_state_ready(M_sys_main* sys)
{
}

static void FSM_state_run(M_sys_main* sys)
{
}

static void FSM_state_error(M_sys_main* sys)
{
}

static void FSM_state(M_sys_main* sys)
{
    switch(sys->state){
    case STATE_NONE:
        FSM_state_none(sys);
        break;
    case STATE_INIT:
        FSM_state_init(sys);
        break;
    case STATE_IDLE:
        FSM_state_idle(sys);
        break;
    case STATE_READY:
        FSM_state_ready(sys);
        break;
    case STATE_RUN:
        FSM_state_run(sys);
        break;
    case STATE_ERROR:
        FSM_state_error(sys);
        break;
    default:
        // TODO: reaction on invalid state error.
        sys->errors |= SYS_MAIN_ERROR_SOFTWARE;
        sys->state = STATE_ERROR;
        break;
    }
}

METHOD_CALC_IMPL(M_sys_main, sys)
{
    FSM_state(sys);

    //CALC(conf); // conf не требует вычисления.
    //CALC(adc); // АЦП вычисляется в коллбэке таймера АЦП.
    CALC(dlog);
}

METHOD_IDLE_IMPL(M_sys_main, sys)
{
    IDLE(conf);
    IDLE(adc);
    IDLE(dlog);
}

