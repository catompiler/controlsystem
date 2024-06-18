#include "sys_main.h"
#include "modules/modules.h"
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

    // Если произошла ошибка при запуске таймера.
    if(sys_tim.status & SYS_TIMER_STATUS_ERROR){
        // Установим ошибку.
        sys->errors |= SYS_MAIN_ERROR_HARDWARE;
        sys->status |= SYS_MAIN_STATUS_ERROR;

        // Остановим таймер.
        sys_tim.control = SYS_TIMER_CONTROL_NONE;
        CONTROL(sys_tim);

        // Принудительно вызовем обработчик.
        sys_tim_handler(arg);
    }

    #endif
}

/*
 * Основной функционал.
 */

METHOD_INIT_IMPL(M_sys_main, sys)
{
    // Сброс внутренних переменных.
    sys->control = SYS_MAIN_CONTROL_NONE;
    sys->status = SYS_MAIN_STATUS_NONE;
    sys->errors = SYS_MAIN_ERROR_NONE;
    sys->warnings = SYS_MAIN_WARNING_NONE;

    // Конечные автоматы.
    // Основной КА.
    fsm_init(&sys->fsm_state);

    // Инициализация модулей.

    // Ошибки инициализации модулей.
    error_t init_errors = ERROR_NONE;

    // Базовый конфиг.
    INIT(conf);

    // Системное время.
    INIT(sys_time);

    // Осциллограф.
    INIT(dlog);

    // Мотор.
    INIT(motor);

    // Лог.
    //TODO: text_log.

    // Основные системные модули.
    INIT(sys_cmd);
    INIT(sys_ctrl);
    INIT(sys_stat);

    // Таймеры мс.
    // Таймер КА.
    INIT(tmr_sys_fsm);

    // АЦП.
    INIT(adc);
    CALLBACK_PROC(adc.on_conversion) = adc_handler;
    CALLBACK_ARG(adc.on_conversion) = (void*)sys;

    // АЦП модель.
    INIT(adc_model);

    // Вычислитель выходного тока по входным токам фаз.
    INIT(rect_curr);

    // Мультиплексоры измерений.
    INIT(mains_U);
    INIT(mains_I);
    INIT(armature_U);
    INIT(armature_I);
    INIT(rstart_I);
    INIT(mux_cell_U);
    INIT(mux_cell_I);
    INIT(mux_slip);

    // Вычислительные модули.
    // Фазы и амплитуды.
    INIT(phase_ampl_Ua);
    INIT(phase_ampl_Ub);
    INIT(phase_ampl_Uc);
    // ZCD.
    INIT(zcd_Ua);
    INIT(zcd_Ub);
    INIT(zcd_Uc);
    INIT(zcd_slip);
    // Slip.
    INIT(slip);
    // 3phase value.
    INIT(cell_U);
    INIT(cell_I);
    // Phase to line.
    INIT(cell_U_line);
    // RMS.
    INIT(rms_Ua);
    INIT(rms_Ub);
    INIT(rms_Uc);
    INIT(rms_Ia);
    INIT(rms_Ib);
    INIT(rms_Ic);
    INIT(rms_cell_Ua);
    INIT(rms_cell_Ub);
    INIT(rms_cell_Uc);
    INIT(rms_cell_Ia);
    INIT(rms_cell_Ib);
    INIT(rms_cell_Ic);
    // Mean.
    INIT(mean_Iarm);
    INIT(mean_Uarm);
    INIT(mean_Irstart);
    // Power.
    INIT(power_A);
    INIT(power_B);
    INIT(power_C);

    // Фильтры.
    // Фильтры напряжений для детекта нуля фаз.
    INIT(filter_Ua_zcd);
    INIT(filter_Ub_zcd);
    INIT(filter_Uc_zcd);
    INIT(filter_slip_zcd);
    // Фильтры частоты фаз.
    INIT(filter_freq_Ua);
    INIT(filter_freq_Ub);
    INIT(filter_freq_Uc);
    INIT(filter_freq_slip);
    // Фильтр выходного тока.
    INIT(filter_mean_Iarm);
    // Фильтр выходного напряжения.
    INIT(filter_mean_Uarm);
    // Фильтр тока пускового сопротивления.
    INIT(filter_mean_Irstart);

    // Измерения.
    INIT(meas);

    // Допустимые диапазоны.
    // Допустимый диапазон напряжений сети.
    INIT(vr_rms_Umains);
    // Допустимый диапазон частоты сети.
    INIT(vr_filter_freq_Umains);

    // Основные модули.
    // СИФУ.
    INIT(ph3c);
    // Модель 3х фазного выпрямителя.
    INIT(lrm);

    // Защита.
    INIT(prot);

    // Таймеры.
    // Таймер АЦП.
    INIT(adc_tim);
    CALLBACK_PROC(adc_tim.on_timeout) = adc_tim_handler;
    CALLBACK_ARG(adc_tim.on_timeout) = (void*)sys;
    if(adc_tim.status & ADC_TIMER_STATUS_ERROR){
        init_errors |= SYS_MAIN_ERROR_HARDWARE;
    }

    // Системный таймер.
    INIT(sys_tim);
    CALLBACK_PROC(sys_tim.on_timeout) = sys_tim_handler;
    CALLBACK_ARG(sys_tim.on_timeout) = (void*)sys;
    if(sys_tim.status & SYS_TIMER_STATUS_ERROR){
        init_errors |= SYS_MAIN_ERROR_HARDWARE;
    }

    // Медленный таймер.
    INIT(ms_tim);
    CALLBACK_PROC(ms_tim.on_timeout) = ms_tim_handler;
    CALLBACK_ARG(ms_tim.on_timeout) = (void*)sys;
    if(ms_tim.status & MS_TIMER_STATUS_ERROR){
        init_errors |= SYS_MAIN_ERROR_HARDWARE;
    }

    // Включение в работу модулей.
    // Не будем включать модули,
    // если инициализация завершена с ошибкой.
    if(init_errors == ERROR_NONE){

        // Запуск таймера АЦП.
        adc_tim.control = ADC_TIMER_CONTROL_ENABLE;
        CONTROL(adc_tim);
        if(!(adc_tim.status & ADC_TIMER_STATUS_RUN)){
            init_errors |= SYS_MAIN_ERROR_HARDWARE;
        }

        // Запуск медленного таймера.
        ms_tim.control = MS_TIMER_CONTROL_ENABLE;
        CONTROL(ms_tim);
        if(!(ms_tim.status & MS_TIMER_STATUS_RUN)){
            init_errors |= SYS_MAIN_ERROR_HARDWARE;
        }
    }

    // Проверка ошибок инициализации.
    // Если есть ошибки - установим состояние непоправимой ошибки.
    if(init_errors != ERROR_NONE){
        sys->errors = init_errors;
        sys->status = SYS_MAIN_STATUS_ERROR;
    }else{// Если нет ошибок - продолжим инициализацию в КА.
        fsm_set_state(&sys->fsm_state, SYS_MAIN_STATE_INIT);
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

    // Защита.
    DEINIT(prot);

    // Основные модули.
    DEINIT(lrm);
    DEINIT(ph3c);

    // Вычислительные модули.

    // Допустимые диапазоны.
    // Допустимый диапазон частоты сети.
    DEINIT(vr_filter_freq_Umains);
    // Допустимый диапазон напряжений сети.
    DEINIT(vr_rms_Umains);

    // Измерения.
    DEINIT(meas);

    // Фильтры.
    // Фильтры напряжений для детекта нуля фаз.
    DEINIT(filter_Ua_zcd);
    DEINIT(filter_Ub_zcd);
    DEINIT(filter_Uc_zcd);
    DEINIT(filter_slip_zcd);
    // Фильтры частоты фаз.
    DEINIT(filter_freq_Ua);
    DEINIT(filter_freq_Ub);
    DEINIT(filter_freq_Uc);
    DEINIT(filter_freq_slip);
    // Фильтр тока пускового сопротивления.
    DEINIT(filter_mean_Irstart);
    // Фильтр выходного напряжения.
    DEINIT(filter_mean_Uarm);
    // Фильтр выходного тока.
    DEINIT(filter_mean_Iarm);
    // Power.
    DEINIT(power_A);
    DEINIT(power_B);
    DEINIT(power_C);
    // Mean.
    DEINIT(mean_Irstart);
    DEINIT(mean_Uarm);
    DEINIT(mean_Iarm);
    // RMS.
    DEINIT(rms_Ua);
    DEINIT(rms_Ub);
    DEINIT(rms_Uc);
    DEINIT(rms_Ia);
    DEINIT(rms_Ib);
    DEINIT(rms_Ic);
    DEINIT(rms_cell_Ua);
    DEINIT(rms_cell_Ub);
    DEINIT(rms_cell_Uc);
    DEINIT(rms_cell_Ia);
    DEINIT(rms_cell_Ib);
    DEINIT(rms_cell_Ic);
    // ZCD.
    DEINIT(zcd_Ua);
    DEINIT(zcd_Ub);
    DEINIT(zcd_Uc);
    DEINIT(zcd_slip);
    // 3phase value.
    DEINIT(cell_U);
    DEINIT(cell_I);
    // Phase to line.
    DEINIT(cell_U_line);
    // Slip.
    DEINIT(slip);
    // Фазы и амплитуды.
    DEINIT(phase_ampl_Ua);
    DEINIT(phase_ampl_Ub);
    DEINIT(phase_ampl_Uc);

    // Мультиплексоры измерений.
    DEINIT(mux_slip);
    DEINIT(mux_cell_U);
    DEINIT(mux_cell_I);
    DEINIT(armature_U);
    DEINIT(armature_I);
    DEINIT(rstart_I);
    DEINIT(mains_U);
    DEINIT(mains_I);

    // Вычислитель выходного тока по входным токам фаз.
    DEINIT(rect_curr);

    // Базовые модули.
    DEINIT(adc_tim);
    DEINIT(sys_tim);
    DEINIT(ms_tim);
    DEINIT(adc_model);
    DEINIT(adc);
    DEINIT(tmr_sys_fsm);
    DEINIT(sys_stat);
    DEINIT(sys_ctrl);
    DEINIT(sys_cmd);

    // Мотор.
    DEINIT(motor);

    DEINIT(dlog);
    DEINIT(sys_time);
    DEINIT(conf);

    // Конечные автоматы.
    // Основной КА.
    fsm_deinit(&sys->fsm_state);

    // Сброс внутренних переменных.
    sys->control = SYS_MAIN_CONTROL_NONE;
    sys->status = SYS_MAIN_STATUS_NONE;
    sys->errors = SYS_MAIN_ERROR_NONE;
    sys->warnings = SYS_MAIN_WARNING_NONE;
}


//! Последовательное включение в работу и
//! ожидание доступности выходных данных
//! модулей.
static void FSM_state_init(M_sys_main* sys)
{
    FSM_STATE_ENTRY(&sys->fsm_state){
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
        zcd_slip.control = CONTROL_ENABLE;

        slip.control = CONTROL_ENABLE;

        rms_Ua.control = CONTROL_ENABLE;
        rms_Ub.control = CONTROL_ENABLE;
        rms_Uc.control = CONTROL_ENABLE;
        rms_Ia.control = CONTROL_ENABLE;
        rms_Ib.control = CONTROL_ENABLE;
        rms_Ic.control = CONTROL_ENABLE;

        rms_cell_Ua.control = CONTROL_ENABLE;
        rms_cell_Ub.control = CONTROL_ENABLE;
        rms_cell_Uc.control = CONTROL_ENABLE;
        rms_cell_Ia.control = CONTROL_ENABLE;
        rms_cell_Ib.control = CONTROL_ENABLE;
        rms_cell_Ic.control = CONTROL_ENABLE;
    }

    status &= phase_ampl_Ua.status;
    status &= phase_ampl_Ub.status;
    status &= phase_ampl_Uc.status;

    status &= zcd_Ua.status;
    status &= zcd_Ub.status;
    status &= zcd_Uc.status;
    status &= zcd_slip.status;

    status &= slip.status;

    status &= rms_Ua.status;
    status &= rms_Ub.status;
    status &= rms_Uc.status;
    status &= rms_Ia.status;
    status &= rms_Ib.status;
    status &= rms_Ic.status;

    status &= rms_cell_Ua.status;
    status &= rms_cell_Ub.status;
    status &= rms_cell_Uc.status;
    status &= rms_cell_Ia.status;
    status &= rms_cell_Ib.status;
    status &= rms_cell_Ic.status;

    if(status & STATUS_VALID){
        power_A.control = CONTROL_ENABLE;
        power_B.control = CONTROL_ENABLE;
        power_C.control = CONTROL_ENABLE;
    }

    status &= power_A.status;
    status &= power_B.status;
    status &= power_C.status;


    // Если все модули имеют валидный выход.
    if(status & STATUS_VALID){
        // Разрешим систему управления.
        sys_ctrl.control = SYS_CONTROL_CONTROL_ENABLE;

        // Переход в состояние ожидания включения.
        fsm_set_state(&sys->fsm_state, SYS_MAIN_STATE_RUN);
    }
}

static void FSM_state_run(M_sys_main* sys)
{
    FSM_STATE_ENTRY(&sys->fsm_state){
    }
}

static void FSM_state(M_sys_main* sys)
{
    // Начнём обработку состояний.
    fsm_begin(&sys->fsm_state);

    switch(fsm_cur_state(&sys->fsm_state)){
    case SYS_MAIN_STATE_NONE:
        break;
    case SYS_MAIN_STATE_INIT:
        FSM_state_init(sys);
        break;
    case SYS_MAIN_STATE_RUN:
        FSM_state_run(sys);
        break;
    default:
        sys->errors |= SYS_MAIN_ERROR_SOFTWARE;
        sys->status |= SYS_MAIN_STATUS_ERROR;
        //TODO: Unhandled state process.
        break;
    }

    // Окончим обработку состояний.
    fsm_end(&sys->fsm_state);
}

METHOD_CALC_IMPL(M_sys_main, sys)
{
    // Счётчик.
    int i;

    //CALC(conf); // conf не требует вычисления.
    //CALC(adc); // АЦП вычисляется в коллбэке таймера АЦП.
    CALC(adc_model); // АЦП модель.


    // Вычислительные и основные модули.

    // Вычисление измерений для СИФУ.
    MEAS_CALC_FOR_PHC(meas);

    // СИФУ.
    ph3c.in_Uab_angle_pu = phase_ampl_Ua.out_phase;
    ph3c.in_Ubc_angle_pu = phase_ampl_Ub.out_phase;
    ph3c.in_Uca_angle_pu = phase_ampl_Uc.out_phase;
    CALC(ph3c);

    // Вычисление измерений напряжения ячейки
    // (для модели нужно вычислить это до вычисления модели).
    MEAS_CALC_FOR_MODEL(meas);

    // Модель 3х фазного выпрямителя.
    lrm.in_Uab = mains_U.out_A;
    lrm.in_Ubc = mains_U.out_B;
    lrm.in_Uca = mains_U.out_C;
    lrm.in_Uref_angle = phase_ampl_Ua.out_phase;
    lrm.in_stator_Uab = cell_U_line.out_A;
    lrm.in_stator_Ubc = cell_U_line.out_B;
    lrm.in_stator_Uca = cell_U_line.out_C;
    // Копирование управления.
    for(i = 0; i < PHASE3_CONTROL_KEYS_COUNT; i ++)
    { lrm.in_control[i] = ph3c.out_control[i]; }
    lrm.in_control_delay_angle = ph3c.out_control_delay_angle_pu;
    lrm.in_control_duration_angle = ph3c.out_control_max_duration_angle_pu;
    CALC(lrm);


    // Измерения.
    CALC(meas);


    // Таймеры - счётчики.
    // Таймер КА.
    CALC(tmr_sys_fsm);


    // Защиты.
    CALC(prot);


    // Основные модули.
    // Командный модуль.
    CALC(sys_cmd);

    // Соединение входов и выходов системных модулей.

    // if(prot.errors == 0){

    if(sys_cmd.out_command & SYS_COMMAND_COMMAND_ON){
        sys_ctrl.control |= SYS_CONTROL_CONTROL_ON;
    }else{
        sys_ctrl.control &= ~SYS_CONTROL_CONTROL_ON;
    }

    if(sys_cmd.out_command & SYS_COMMAND_COMMAND_CONT_ON){
        sys_ctrl.control |= SYS_CONTROL_CONTROL_CONT_ON;
    }else{
        sys_ctrl.control &= ~SYS_CONTROL_CONTROL_CONT_ON;
    }

    if(sys_cmd.out_command & SYS_COMMAND_COMMAND_RUN){
        sys_ctrl.control |= SYS_CONTROL_CONTROL_RUN;
    }else{
        sys_ctrl.control &= ~SYS_CONTROL_CONTROL_RUN;
    }

    //} // prot.errors == 0

    // Модуль управления.
    CALC(sys_ctrl);
    // Модуль состояния.
    CALC(sys_stat);

    // Конечный автомат.
    FSM_state(sys);

    // Последний модуль - запись лога.
    CALC(dlog);
}

METHOD_IDLE_IMPL(M_sys_main, sys)
{
    IDLE(conf);
    IDLE(dlog);
    // Мотор.
    IDLE(motor);
    IDLE(adc);
    IDLE(adc_model);
    IDLE(lrm);
    // Фильтры.
    // Фильтры напряжений для детекта нуля фаз.
    IDLE(filter_Ua_zcd);
    IDLE(filter_Ub_zcd);
    IDLE(filter_Uc_zcd);
    IDLE(filter_slip_zcd);
    // Фильтры частоты фаз.
    IDLE(filter_freq_Ua);
    IDLE(filter_freq_Ub);
    IDLE(filter_freq_Uc);
    IDLE(filter_freq_slip);
    // Фильтр выходного тока.
    IDLE(filter_mean_Iarm);
    // Фильтр выходного напряжения.
    IDLE(filter_mean_Uarm);
    // Фильтр тока пускового сопротивления.
    IDLE(filter_mean_Irstart);
}

