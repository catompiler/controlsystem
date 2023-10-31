#include "modules/modules.h"
#include "sys_main.h"
#include "defs/defs.h"
#include <assert.h>
//#include <sys/time.h>
//#include <stdio.h>


/*
 * Общие функции.
 */

/*
 * Состояние.
 */

// Макрос для обработки первого входа в состояние.
#define STATE_ENTRY(sys)\
            if(sys->m_state_entry)

//! Получение состояния.
ALWAYS_INLINE static state_t sys_main_state(M_sys_main* sys)
{
    return sys->state;
}

//! Получение предыдущего состояния.
ALWAYS_INLINE static state_t sys_main_prev_state(M_sys_main* sys)
{
    return sys->m_prev_state;
}

//! Установка состояния.
ALWAYS_INLINE static void sys_main_set_state(M_sys_main* sys, state_t state)
{
    sys->state = state;
}

/*
 * Обработчики коллбэков.
 */

//static void sys_tim_handler(void* arg);


static void adc_tim_handler(void* arg)
{
    M_sys_main* sys = (M_sys_main*)arg;
    assert(sys != NULL);

    CALC(adc);
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

    CALC(sys_time); // Системное время.
}

static void adc_handler(void* arg)
{
    M_sys_main* sys = (M_sys_main*)arg;
    assert(sys != NULL);

    // Если системный таймер однократного счёта, то запустим его.
    #if defined(SYS_TIMER_ONE_SHOT) && SYS_TIMER_ONE_SHOT == 1

    //sys_tim_handler(arg);

    sys_tim.control = SYS_TIMER_CONTROL_ENABLE;
    CONTROL(sys_tim);

    if(sys_tim.status & SYS_TIMER_STATUS_ERROR){
        sys->errors |= SYS_MAIN_ERROR_INTERNAL;
        sys_main_set_state(sys, SYS_MAIN_STATE_FATAL);
    }

    #endif
}

/*
 * Основной функционал.
 */

METHOD_INIT_IMPL(M_sys_main, sys)
{
    // Сброс состояния.
    sys->state = STATE_INIT;
    sys->m_prev_state = STATE_NONE;

    // Конечные автоматы.
    fsm_init(&sys->fsm_ready_on);

    // Инициализация модулей.

    // Флаг состояния модулей.
    status_t init_status = STATUS_NONE;

    // Базовый конфиг.
    INIT(conf);

    // Системное время.
    INIT(sys_time);

    // Таймеры мс.
    // Таймер КА.
    INIT(tmr_sys_fsm);

    // Осциллограф.
    INIT(dlog);

    // АЦП.
    INIT(adc);
    CALLBACK_PROC(adc.on_conversion) = adc_handler;
    CALLBACK_ARG(adc.on_conversion) = (void*)sys;

    // АЦП модель.
    INIT(adc_model);

    // Мультиплексоры измерений.
    INIT(mains_U);
    INIT(mains_I);

    // Вычислительные модули.
    // Фазы и амплитуды.
    INIT(phase_ampl_Ua);
    INIT(phase_ampl_Ub);
    INIT(phase_ampl_Uc);
    // ZCD.
    INIT(zcd_Ua);
    INIT(zcd_Ub);
    INIT(zcd_Uc);
    // RMS.
    INIT(rms_Ua);
    INIT(rms_Ub);
    INIT(rms_Uc);
    // Пороги.
    // Пороги напряжений при включении контактора.
    INIT(th_rms_Ua);
    INIT(th_rms_Ub);
    INIT(th_rms_Uc);
    // Фильтры частоты фаз.
    INIT(filter_Ua_freq);
    INIT(filter_Ub_freq);
    INIT(filter_Uc_freq);

    // Основные модули.
    // СИФУ.
    INIT(ph3c);
    // Модель 3х фазного выпрямителя.
    INIT(lrm);

    // Таймеры.
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
    // Если есть ошибки - установим состояние непоправимой ошибки.
    if(init_status & STATUS_ERROR){
        sys->errors |= SYS_MAIN_ERROR_INTERNAL;
        sys_main_set_state(sys, SYS_MAIN_STATE_FATAL);
    }else{// Если нет ошибок - продолжим инициализацию в КА.
        //sys_main_set_state(sys, SYS_MAIN_STATE_INIT);
    }
}

METHOD_DEINIT_IMPL(M_sys_main, sys)
{
    // Останов таймеров.
    adc_tim.control = CONTROL_NONE;
    CONTROL(adc_tim);
    sys_tim.control = CONTROL_NONE;
    CONTROL(sys_tim);
    ms_tim.control = CONTROL_NONE;
    CONTROL(ms_tim);

    // Деинициализация модулей.
    // От основных к базовым.

    // Основные модули.
    DEINIT(lrm);
    DEINIT(ph3c);

    // Вычислительные модули.
    // Фильтры частоты фаз.
    DEINIT(filter_Ua_freq);
    DEINIT(filter_Ub_freq);
    DEINIT(filter_Uc_freq);
    // Пороги.
    // Пороги напряжений при включении контактора.
    DEINIT(th_rms_Ua);
    DEINIT(th_rms_Ub);
    DEINIT(th_rms_Uc);
    // RMS.
    DEINIT(rms_Ua);
    DEINIT(rms_Ub);
    DEINIT(rms_Uc);
    // ZCD.
    DEINIT(zcd_Ua);
    DEINIT(zcd_Ub);
    DEINIT(zcd_Uc);
    // Фазы и амплитуды.
    DEINIT(phase_ampl_Ua);
    DEINIT(phase_ampl_Ub);
    DEINIT(phase_ampl_Uc);

    // Мультиплексоры измерений.
    DEINIT(mains_U);
    DEINIT(mains_I);

    // Базовые модули.
    DEINIT(adc_tim);
    DEINIT(sys_tim);
    DEINIT(ms_tim);
    DEINIT(adc_model);
    DEINIT(adc);
    DEINIT(dlog);
    DEINIT(tmr_sys_fsm);
    DEINIT(sys_time);
    DEINIT(conf);

    // Конечные автоматы.
    fsm_deinit(&sys->fsm_ready_on);

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

//! Последовательное включение в работу и
//! ожидание доступности выходных данных
//! модулей.
static void FSM_state_init(M_sys_main* sys)
{
    STATE_ENTRY(sys){
    }

    status_t status = STATUS_VALID;

    status &= (adc.status | adc_model.status);

    // Все модули, от которых зависят модули ниже
    // имеют валидные выходные данные.
    if(status & STATUS_VALID){
        phase_ampl_Ua.control = CONTROL_ENABLE;
        phase_ampl_Ub.control = CONTROL_ENABLE;
        phase_ampl_Uc.control = CONTROL_ENABLE;
        zcd_Ua.control = CONTROL_ENABLE;
        zcd_Ub.control = CONTROL_ENABLE;
        zcd_Uc.control = CONTROL_ENABLE;
        rms_Ua.control = CONTROL_ENABLE;
        rms_Ub.control = CONTROL_ENABLE;
        rms_Uc.control = CONTROL_ENABLE;
    }

    status &= phase_ampl_Ua.status;
    status &= phase_ampl_Ub.status;
    status &= phase_ampl_Uc.status;

    status &= zcd_Ua.status;
    status &= zcd_Ub.status;
    status &= zcd_Uc.status;

    status &= rms_Ua.status;
    status &= rms_Ub.status;
    status &= rms_Uc.status;

    // Если все модули имеют валидный выход.
    if(status & STATUS_VALID){
        // Переход в состояние ожидания включения.
        sys_main_set_state(sys, SYS_MAIN_STATE_READY_ON);
    }
}

static void FSM_state_ready_on(M_sys_main* sys)
{
    STATE_ENTRY(sys){
        // Установим состояние КА включения.
        fsm_set_state(&sys->fsm_ready_on, SYS_MAIN_READY_ON_WAIT_ON);
    }

    fsm_begin(&sys->fsm_ready_on);

    switch(fsm_cur_state(&sys->fsm_ready_on)){
    case SYS_MAIN_READY_ON_NONE:
        fsm_set_state(&sys->fsm_ready_on, SYS_MAIN_READY_ON_WAIT_ON);
        break;

    case SYS_MAIN_READY_ON_WAIT_ON:
        FSM_STATE_ENTRY(&sys->fsm_ready_on){
            //
        }
        break;

    case SYS_MAIN_READY_ON_WAIT_MAINS:
        FSM_STATE_ENTRY(&sys->fsm_ready_on){
            //
        }
        break;

    case SYS_MAIN_READY_ON_WAIT_FREQ:
        FSM_STATE_ENTRY(&sys->fsm_ready_on){
            //
        }
        break;

    case SYS_MAIN_READY_ON_DONE:
        // Переход в состояние ожидания запуска.
        sys_main_set_state(sys, SYS_MAIN_STATE_READY_RUN);
        break;
    }

    fsm_end(&sys->fsm_ready_on);
}

static void FSM_state_ready_run(M_sys_main* sys)
{
}

static void FSM_state_run(M_sys_main* sys)
{
}

static void FSM_state_error(M_sys_main* sys)
{
}

static void FSM_state_fatal(M_sys_main* sys)
{
    //TODO: Fatal state process.
}

static void FSM_state(M_sys_main* sys)
{
    // Состояние и предыдущее состояние
    // на момент начала обработки конечного автомата.
    state_t cur_state = sys->state;
    state_t prev_state = sys->m_prev_state;

    // Если было установлено состояние -
    // установим флаг первого входа.
    sys->m_state_entry = cur_state != prev_state;

    switch(cur_state){
    case SYS_MAIN_STATE_NONE:
        FSM_state_none(sys);
        break;
    case SYS_MAIN_STATE_INIT:
        FSM_state_init(sys);
        break;
    case SYS_MAIN_STATE_READY_ON:
        FSM_state_ready_on(sys);
        break;
    case SYS_MAIN_STATE_READY_RUN:
        FSM_state_ready_run(sys);
        break;
    case SYS_MAIN_STATE_RUN:
        FSM_state_run(sys);
        break;
    case SYS_MAIN_STATE_ERROR:
        FSM_state_error(sys);
        break;
    case SYS_MAIN_STATE_FATAL:
        FSM_state_fatal(sys);
        break;
    default:
        sys->errors |= SYS_MAIN_ERROR_SOFTWARE;
        sys_main_set_state(sys, SYS_MAIN_STATE_FATAL);
        break;
    }

    // Установим предыдущее состояние.
    sys->m_prev_state = cur_state;
}

METHOD_CALC_IMPL(M_sys_main, sys)
{
    // Счётчик.
    int i;

    //CALC(conf); // conf не требует вычисления.
    //CALC(adc); // АЦП вычисляется в коллбэке таймера АЦП.
    CALC(adc_model); // АЦП модель.

    // Мультиплексор измерений напряжения.
    // Напряжение фазы A.
    mains_U.in_Ua[0] = adc.out_Ua;
    mains_U.in_Ua[1] = adc_model.out_Ua;
    // Напряжение фазы B.
    mains_U.in_Ub[0] = adc.out_Ub;
    mains_U.in_Ub[1] = adc_model.out_Ub;
    // Напряжение фазы C.
    mains_U.in_Uc[0] = adc.out_Uc;
    mains_U.in_Uc[1] = adc_model.out_Uc;
    CALC(mains_U);

    // Вычислительные и основные модули.
    // Фаза и амплитуда.
    // Фаза A.
    phase_ampl_Ua.in_value = mains_U.out_Ua;
    CALC(phase_ampl_Ua);
    // Фаза B.
    phase_ampl_Ub.in_value = mains_U.out_Ub;
    CALC(phase_ampl_Ub);
    // Фаза C.
    phase_ampl_Uc.in_value = mains_U.out_Uc;
    CALC(phase_ampl_Uc);


    // СИФУ.
    ph3c.in_Uab_angle_pu = phase_ampl_Ua.out_phase;
    ph3c.in_Ubc_angle_pu = phase_ampl_Ub.out_phase;
    ph3c.in_Uca_angle_pu = phase_ampl_Uc.out_phase;
    CALC(ph3c);


    // Модель 3х фазного выпрямителя.
    lrm.in_Uab = mains_U.out_Ua;
    lrm.in_Ubc = mains_U.out_Ub;
    lrm.in_Uca = mains_U.out_Uc;
    lrm.in_Uref_angle_pu = phase_ampl_Ua.out_phase;
    // Копирование управления.
    for(i = 0; i < PHASE3_CONTROL_KEYS_COUNT; i ++)
    { lrm.in_control[i] = ph3c.out_control[i]; }
    lrm.in_control_delay_angle_pu = ph3c.out_control_delay_angle_pu;
    lrm.in_control_duration_angle_pu = ph3c.out_control_max_duration_angle_pu;
    CALC(lrm);

    // Остальные мультиплексоры измерений.
    // Мультиплексор измерений тока.
    // Ток фазы A.
    mains_I.in_Ia[0] = adc.out_Ia;
    mains_I.in_Ia[1] = lrm.out_Iab;
    // Ток фазы B.
    mains_I.in_Ib[0] = adc.out_Ib;
    mains_I.in_Ib[1] = lrm.out_Ibc;
    // Ток фазы C.
    mains_I.in_Ic[0] = adc.out_Ic;
    mains_I.in_Ic[1] = lrm.out_Ica;
    CALC(mains_I);
    // Мультиплексор измерений выходного напряжения.
    armature_U.in_Uarm[0] = adc.out_Uarm;
    armature_U.in_Uarm[1] = lrm.out_U;
    CALC(armature_U);
    // Мультиплексор измерений выходного тока.
    armature_I.in_Iarm[0] = adc.out_Iarm;
    armature_I.in_Iarm[1] = lrm.out_I;
    CALC(armature_I);


    // Детект нуля и вычисление частоты.
    // Фаза A.
    zcd_Ua.in_value = mains_U.out_Ua;
    CALC(zcd_Ua);
    // Фаза B.
    zcd_Ub.in_value = mains_U.out_Ub;
    CALC(zcd_Ub);
    // Фаза C.
    zcd_Uc.in_value = mains_U.out_Uc;
    CALC(zcd_Uc);

    // Фильтры частоты фаз.
    // Фаза A.
    filter_Ua_freq.in_value = zcd_Ua.out_freq;
    CALC(filter_Ua_freq);
    // Фаза B.
    filter_Ub_freq.in_value = zcd_Ub.out_freq;
    CALC(filter_Ub_freq);
    // Фаза C.
    filter_Uc_freq.in_value = zcd_Uc.out_freq;
    CALC(filter_Uc_freq);


    // RMS.
    // Фаза A.
    rms_Ua.in_value = mains_U.out_Ua;
    CALC(rms_Ua);
    // Фаза B.
    rms_Ub.in_value = mains_U.out_Ub;
    CALC(rms_Ub);
    // Фаза C.
    rms_Uc.in_value = mains_U.out_Uc;
    CALC(rms_Uc);


    // Пороги,
    // Пороги напряжений при включении контактора.
    // Фаза A.
    th_rms_Ua.in_value = rms_Ua.out_value;
    CALC(th_rms_Ua);
    // Фаза B.
    th_rms_Ub.in_value = rms_Ub.out_value;
    CALC(th_rms_Ub);
    // Фаза C.
    th_rms_Uc.in_value = rms_Uc.out_value;
    CALC(th_rms_Uc);


    // Защиты.

    // Регуляторы.

    // Таймеры - счётчики.
    // Таймер КА.
    CALC(tmr_sys_fsm);

    // Конечный автомат.
    FSM_state(sys);

    // Последний модуль - запись лога.
    CALC(dlog);
}

METHOD_IDLE_IMPL(M_sys_main, sys)
{
    IDLE(conf);
    IDLE(adc);
    IDLE(adc_model);
    IDLE(dlog);
    IDLE(lrm);
}

