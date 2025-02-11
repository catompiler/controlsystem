#include "sys_main.h"
#include "modules/modules.h"
#include "defs/defs.h"
#include <assert.h>
#include <stdbool.h>
#include "sys_counter/sys_counter.h"
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
    // Измерение времени выполнения.
    struct timeval tv_run_start, tv_run_end, tv_run_time;
    sys_counter_value(&tv_run_start);

    M_sys_main* sys = (M_sys_main*)arg;
    assert(sys != NULL);

    CALC(adc);

    // Измерение времени выаполнения.
    sys_counter_value(&tv_run_end);
    timersub(&tv_run_end, &tv_run_start, &tv_run_time);
    sys->r_adc_tim_run_time_us = tv_run_time.tv_sec * 1000000 + tv_run_time.tv_usec;
}

static void sys_tim_handler(void* arg)
{
    // Измерение времени выполнения.
    struct timeval tv_run_start, tv_run_end, tv_run_time;
    sys_counter_value(&tv_run_start);

    M_sys_main* sys = (M_sys_main*)arg;
    assert(sys != NULL);

    CALC((*sys));

    // Измерение времени выаполнения.
    sys_counter_value(&tv_run_end);
    timersub(&tv_run_end, &tv_run_start, &tv_run_time);
    sys->r_sys_tim_run_time_us = tv_run_time.tv_sec * 1000000 + tv_run_time.tv_usec;
}

static void ms_tim_handler(void* arg)
{
    // Измерение времени выполнения.
    struct timeval tv_run_start, tv_run_end, tv_run_time;
    sys_counter_value(&tv_run_start);

    M_sys_main* sys = (M_sys_main*)arg;
    assert(sys != NULL);

    CALC(sys_time); // Системное время.

    // Измерение времени выаполнения.
    sys_counter_value(&tv_run_end);
    timersub(&tv_run_end, &tv_run_start, &tv_run_time);
    sys->r_ms_tim_run_time_us = tv_run_time.tv_sec * 1000000 + tv_run_time.tv_usec;
}

static void net_tim_handler(void* arg)
{
    // Измерение времени выполнения.
    struct timeval tv_run_start, tv_run_end, tv_run_time;
    sys_counter_value(&tv_run_start);

    M_sys_main* sys = (M_sys_main*)arg;
    assert(sys != NULL);

    CALC(canopen); // CANopen.

    // Измерение времени выаполнения.
    sys_counter_value(&tv_run_end);
    timersub(&tv_run_end, &tv_run_start, &tv_run_time);
    sys->r_net_run_time_us = tv_run_time.tv_sec * 1000000 + tv_run_time.tv_usec;
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

    // Предупреждения инициализации модулей.
    warning_t init_warnings = WARNING_NONE;

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

    // ЦАП.
    INIT(dac);

    // АЦП модель.
    INIT(adc_model);

    // Вычислитель выходного тока по входным токам фаз.
    INIT(rect_curr);

    // Мультиплексоры измерений.
    INIT(mux_Umains);
    INIT(mux_Imains);
    INIT(mux_Uarm);
    INIT(mux_Iarm);
    INIT(mux_Irstart);
    INIT(mux_Ucell);
    INIT(mux_Icell);
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
    INIT(calc_Ucell);
    INIT(calc_Icell);
    // Line to phase.
    INIT(phase_lrm_I_stator);
    INIT(phase_Ucell);
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
    INIT(rms_cell_Ua_phase);
    INIT(rms_cell_Ub_phase);
    INIT(rms_cell_Uc_phase);
    INIT(rms_cell_Ia);
    INIT(rms_cell_Ib);
    INIT(rms_cell_Ic);
    // Mean.
    INIT(mean_Iarm);
    INIT(mean_Uarm);
    INIT(mean_Irstart);
    INIT(mean_rms_Icell);
    // Power.
    INIT(power_A);
    INIT(power_B);
    INIT(power_C);
    // Power factor.
    INIT(power_factor);

    // Фильтры.
    // Фильтры напряжений для детекта нуля фаз.
    INIT(filter_zcd_Ua);
    INIT(filter_zcd_Ub);
    INIT(filter_zcd_Uc);
    INIT(filter_zcd_slip);
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
    INIT(sys_calc);

    // Допустимые диапазоны.
    // Допустимый диапазон напряжений сети.
    INIT(vr_rms_Umains);
    // Допустимый диапазон частоты сети.
    INIT(vr_filter_freq_Umains);
    // Допустимый диапазон напряжений ячейки.
    INIT(vr_rms_Ucell);

    // Основные модули.
    // Тиристоры.
    INIT(triacs);
    // СИФУ.
    INIT(ph3c);
    // Модель 3х фазного выпрямителя.
    INIT(lrm);
    // Форсировка при запуске.
    INIT(tmr_start_min_forcing);
    INIT(tmr_start_max_forcing);
    INIT(tmr_start_stab_forcing);
    INIT(thr_start_Q_le_zero);
    INIT(and_start_min_forcing_end);
    INIT(or_start_forcing_end);
    // Регуляторы.
    INIT(mux_field_regs);
    INIT(lim_field_regs_curr_ref);
    INIT(mux_field_force_ref);
    // Field forcing current default value - 1.4 x Inom.
    mux_field_force_ref.in_value[0] = IQ24(1.4);
    INIT(mot_pot_field_test);
    INIT(mot_pot_manual_curr_ref);
    INIT(mux_curr_ref);
    //! ПИД тока.
    INIT(pid_i);
    //! Коэффициенты ПИД тока.
    INIT(pid_coefs_i);
    pid_i.r_kp = pid_coefs_i.out_kp;
    pid_i.r_ki = pid_coefs_i.out_ki;
    pid_i.r_kd = pid_coefs_i.out_kd;
    pid_i.r_kf = pid_coefs_i.out_kf;
    pid_i.r_min = ph3c.out_min_control_value;
    pid_i.r_max = ph3c.out_max_control_value;

    // Состояние ячейки.
    INIT(cell_cb);

    // Триггеры пуска.
    // Триггер пуска по превышению током статора заданного значения.
    INIT(thr_run_trig_I_s);
    // Разрешение учитывания тока статора.
    INIT(am_run_trig_I_s);
    // Выбор условий запуска в зависимости от состояния контактов выключателя ячейки.
    INIT(mux_run_trig);
    // Таймер включения по току статора.
    INIT(tmr_run_trig);

    // Критерии подачи возбуждения.
    // Основной.
    INIT(thr_prim_Slip);
    INIT(thr_prim_I_s);
    INIT(thr_prim_T);
    INIT(am_prim_field_on);
    // Основной.
    INIT(thr_sec_Slip);
    INIT(thr_sec_I_s);
    INIT(thr_sec_T);
    INIT(am_sec_field_on);
    // Общие модули критериев.
    INIT(or_field_on);
    INIT(tmr_field_on);
    INIT(thr_field_on_I_r_sync);
    INIT(tmr_field_on_I_r_sync);
    // Модули старта подачи возбуждения.
    INIT(thr_value_for_slip_lt_zero);
    INIT(or_value_slip_lt_zero_I_r_sync);
    INIT(and_ready_to_exc);
    INIT(tmr_field_on_rstart_off);
    INIT(not_ready_to_exc);
    INIT(cmp_ctrl_state_is_start);
    INIT(and_rstart_on);

    // Гашение поля.
    INIT(thr_field_supp_I_r);
    INIT(tmr_field_supp);

    // Таймеры / счётчики.
    INIT(cnt_start);

    // Защита.
    INIT(prot);

    // Сеть.
    // CANopen.
    INIT(canopen);
    if(canopen.status & CANOPEN_STATUS_ERROR){
        init_warnings |= SYS_MAIN_WARNING_NET;
    }

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

    // Сетевой таймер.
    INIT(net_tim);
    CALLBACK_PROC(net_tim.on_timeout) = net_tim_handler;
    CALLBACK_ARG(net_tim.on_timeout) = (void*)sys;
    if(net_tim.status & NET_TIMER_STATUS_ERROR){
        init_errors |= SYS_MAIN_ERROR_HARDWARE;
    }

    // Инициализируется в main().
//    // Хранилище.
//    INIT(storage);
//    if(storage.status & STATUS_ERROR){
//        init_errors |= SYS_MAIN_ERROR_HARDWARE;
//    }

    // Инициализируется в main().
//    // Настройки.
//    INIT(settings);

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

        // Запуск сетевого таймера.
        net_tim.control = NET_TIMER_CONTROL_ENABLE;
        CONTROL(net_tim);
        if(!(net_tim.status & NET_TIMER_STATUS_RUN)){
            init_errors |= SYS_MAIN_ERROR_HARDWARE;
        }
    }

    // Установка предупреждений инициализации.
    sys->warnings = init_warnings;

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
    net_tim.control = CONTROL_NONE;
    CONTROL(net_tim);

    // Деинициализация модулей.
    // От основных к базовым.

    // Настройки.
    DEINIT(settings);

    // Хранилище.
    DEINIT(storage);

    // Сеть.
    // CANopen.
    DEINIT(canopen);

    // Защита.
    DEINIT(prot);

    // Основные модули.
    DEINIT(lrm);
    DEINIT(ph3c);
    DEINIT(triacs);
    // Форсировка при запуске.
    DEINIT(tmr_start_min_forcing);
    DEINIT(tmr_start_max_forcing);
    DEINIT(tmr_start_stab_forcing);
    DEINIT(thr_start_Q_le_zero);
    DEINIT(and_start_min_forcing_end);
    DEINIT(or_start_forcing_end);
    // Регуляторы.
    INIT(mux_field_regs);
    INIT(lim_field_regs_curr_ref);
    INIT(mux_field_force_ref);
    INIT(mot_pot_field_test);
    INIT(mot_pot_manual_curr_ref);
    INIT(mux_curr_ref);
    //! ПИД тока.
    DEINIT(pid_i);
    //! Коэффициенты ПИД тока.
    DEINIT(pid_coefs_i);

    // Таймеры / счётчики.
    DEINIT(cnt_start);

    // Гашение поля.
    DEINIT(thr_field_supp_I_r);
    DEINIT(tmr_field_supp);

    // Критерии подачи возбуждения.
    DEINIT(thr_prim_Slip);
    DEINIT(thr_prim_I_s);
    DEINIT(thr_prim_T);
    DEINIT(am_prim_field_on);
    // Основной.
    DEINIT(thr_sec_Slip);
    DEINIT(thr_sec_I_s);
    DEINIT(thr_sec_T);
    DEINIT(am_sec_field_on);
    // Общие модули критериев.
    DEINIT(or_field_on);
    DEINIT(tmr_field_on);
    DEINIT(thr_field_on_I_r_sync);
    DEINIT(tmr_field_on_I_r_sync);
    // Модули старта подачи возбуждения.
    DEINIT(thr_value_for_slip_lt_zero);
    DEINIT(or_value_slip_lt_zero_I_r_sync);
    DEINIT(and_ready_to_exc);
    DEINIT(tmr_field_on_rstart_off);
    DEINIT(not_ready_to_exc);
    DEINIT(cmp_ctrl_state_is_start);
    DEINIT(and_rstart_on);

    // Триггеры пуска.
    // Триггер пуска по превышению током статора заданного значения.
    DEINIT(thr_run_trig_I_s);
    // Разрешение учитывания тока статора.
    DEINIT(am_run_trig_I_s);
    // Выбор условий запуска в зависимости от состояния контактов выключателя ячейки.
    DEINIT(mux_run_trig);
    // Таймер включения по току статора.
    DEINIT(tmr_run_trig);

    // Состояние ячейки.
    DEINIT(cell_cb);

    // Вычислительные модули.

    // Допустимые диапазоны.
    // Допустимый диапазон напряжений ячейки.
    DEINIT(vr_rms_Ucell);
    // Допустимый диапазон частоты сети.
    DEINIT(vr_filter_freq_Umains);
    // Допустимый диапазон напряжений сети.
    DEINIT(vr_rms_Umains);

    // Измерения.
    DEINIT(sys_calc);

    // Фильтры.
    // Фильтры напряжений для детекта нуля фаз.
    DEINIT(filter_zcd_Ua);
    DEINIT(filter_zcd_Ub);
    DEINIT(filter_zcd_Uc);
    DEINIT(filter_zcd_slip);
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
    // Power factor.
    DEINIT(power_factor);
    // Power.
    DEINIT(power_A);
    DEINIT(power_B);
    DEINIT(power_C);
    // Mean.
    DEINIT(mean_rms_Icell);
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
    DEINIT(rms_cell_Ua_phase);
    DEINIT(rms_cell_Ub_phase);
    DEINIT(rms_cell_Uc_phase);
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
    DEINIT(calc_Ucell);
    DEINIT(calc_Icell);
    // Line to phase.
    DEINIT(phase_Ucell);
    DEINIT(phase_lrm_I_stator);
    // Slip.
    DEINIT(slip);
    // Фазы и амплитуды.
    DEINIT(phase_ampl_Ua);
    DEINIT(phase_ampl_Ub);
    DEINIT(phase_ampl_Uc);

    // Мультиплексоры измерений.
    DEINIT(mux_slip);
    DEINIT(mux_Ucell);
    DEINIT(mux_Icell);
    DEINIT(mux_Uarm);
    DEINIT(mux_Iarm);
    DEINIT(mux_Irstart);
    DEINIT(mux_Umains);
    DEINIT(mux_Imains);

    // Вычислитель выходного тока по входным токам фаз.
    DEINIT(rect_curr);

    // Базовые модули.
    DEINIT(adc_tim);
    DEINIT(sys_tim);
    DEINIT(ms_tim);
    DEINIT(net_tim);
    DEINIT(adc_model);
    DEINIT(dac);
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
        rms_cell_Ua_phase.control = CONTROL_ENABLE;
        rms_cell_Ub_phase.control = CONTROL_ENABLE;
        rms_cell_Uc_phase.control = CONTROL_ENABLE;
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
    status &= rms_cell_Ua_phase.status;
    status &= rms_cell_Ub_phase.status;
    status &= rms_cell_Uc_phase.status;
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

    fsm_state_t ctrl_state = fsm_state(&sys_ctrl.fsm_state);

    bool ctrl_need_triacs =
            (ctrl_state == SYS_CONTROL_STATE_TEST) ||
            (ctrl_state == SYS_CONTROL_STATE_RUN) ||
            (ctrl_state == SYS_CONTROL_STATE_START_FIELD_FORCE) ||
            (ctrl_state == SYS_CONTROL_STATE_FIELD_FORCE) ||
            (ctrl_state == SYS_CONTROL_STATE_FIELD_SUPP);

    if(ctrl_need_triacs){
        ph3c.control = CONTROL_ENABLE;
    }else{
        ph3c.control = CONTROL_NONE;
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
    SYS_CALC_CALC_FOR_PHC(sys_calc);

    // СИФУ.
    ph3c.in_Ua_angle = phase_ampl_Ua.out_phase;
    ph3c.in_Ub_angle = phase_ampl_Ub.out_phase;
    ph3c.in_Uc_angle = phase_ampl_Uc.out_phase;
    CALC(ph3c);

    // Отпирание тиристоров.
    // Копирование управления.
    for(i = 0; i < TRIACS_MAINS_KEYS_COUNT; i ++)
    { triacs.in_control[i] = ph3c.out_control[i]; }
    triacs.in_control_delay_angle = ph3c.out_control_delay_angle;
    triacs.in_control_max_duration_angle = ph3c.out_control_max_duration_angle;
    CALC(triacs);

    // Вычисление измерений напряжения ячейки
    // (для модели нужно вычислить это до вычисления модели).
    SYS_CALC_CALC_FOR_MODEL(sys_calc);

    // Модель 3х фазного выпрямителя.
    lrm.in_Ua = mux_Umains.out_A;
    lrm.in_Ub = mux_Umains.out_B;
    lrm.in_Uc = mux_Umains.out_C;
    lrm.in_Uref_angle = phase_ampl_Ua.out_phase;
    lrm.in_stator_Ua = calc_Ucell.out_A;
    lrm.in_stator_Ub = calc_Ucell.out_B;
    lrm.in_stator_Uc = calc_Ucell.out_C;
    // Копирование управления.
    for(i = 0; i < PHASE3_CONTROL_KEYS_COUNT; i ++)
    { lrm.in_control[i] = ph3c.out_control[i]; }
    lrm.in_control_delay_angle = ph3c.out_control_delay_angle;
    lrm.in_control_duration_angle = ph3c.out_control_max_duration_angle;
    lrm.in_start_r_on = (sys_stat.in_command & SYS_STATUS_COMMAND_R_START_ON) ? FLAG_ACTIVE : FLAG_NONE;
    CALC(lrm);


    // Измерения.
    CALC(sys_calc);


    // Таймеры - счётчики.
    // Таймер КА.
    CALC(tmr_sys_fsm);


    // Защиты.
    CALC(prot);


    // Основные модули.
    // Командный модуль.
    CALC(sys_cmd);

    // Соединение входов и выходов системных модулей.

    // Состояние выключателя ячейки.
    cell_cb.in_no_state = (sys_cmd.out_command & SYS_COMMAND_COMMAND_CELL_CB_NO) ? FLAG_ACTIVE : FLAG_NONE;
    cell_cb.in_nc_state = (sys_cmd.out_command & SYS_COMMAND_COMMAND_CELL_CB_NC) ? FLAG_ACTIVE : FLAG_NONE;
    CALC(cell_cb);

    // if(prot.errors == 0){

    // Входные команды.
    // Опробование.
    if(sys_cmd.out_command & SYS_COMMAND_COMMAND_TEST){
        sys_ctrl.control |= SYS_CONTROL_CONTROL_TEST;
    }else{
        sys_ctrl.control &= ~SYS_CONTROL_CONTROL_TEST;
    }
    // Включение.
    if(tmr_run_trig.out_value == FLAG_ACTIVE){
        sys_ctrl.control |= SYS_CONTROL_CONTROL_RUN;
    }else{
        sys_ctrl.control &= ~SYS_CONTROL_CONTROL_RUN;
    }
    // Защиты ячейки.
    if(sys_cmd.out_command & SYS_COMMAND_COMMAND_CELL_PROT){
    }
    // Выходные команды.
    // Включение пускового сопротивления.
    if(sys_ctrl.out_command & SYS_CONTROL_COMMAND_R_START_ON){
        sys_stat.in_command |= SYS_STATUS_COMMAND_R_START_ON;
    }else{
        sys_stat.in_command &= ~SYS_STATUS_COMMAND_R_START_ON;
    }

    // Команда выхода.
    if(sys->control & SYS_MAIN_CONTROL_QUIT){
        sys->control &= ~SYS_MAIN_CONTROL_QUIT;
        sys->status |= SYS_MAIN_STATUS_QUIT;
    }

    //} // prot.errors == 0

    // Модуль управления.
    CALC(sys_ctrl);
    // Модуль состояния.
    CALC(sys_stat);

    // Конечный автомат.
    FSM_state(sys);

#warning DEBUG // begin {
    dac.in_value[0] = iq24_mul(lrm.out_Ufld, IQ24(0.5));
    // } end

    // Запись выхода ЦАП.
    CALC(dac);

    // Последний модуль - запись лога.
    CALC(dlog);
}

METHOD_IDLE_IMPL(M_sys_main, sys)
{
    // Измерение времени выполнения.
    struct timeval tv_run_start, tv_run_end, tv_run_time;
    sys_counter_value(&tv_run_start);

    IDLE(conf);
    IDLE(dlog);
    // Мотор.
    IDLE(motor);
    IDLE(adc);
    IDLE(adc_model);
    IDLE(lrm);
    // Обновим минимум и максимум тока цифровых потенциометров.
    // Опробование.
    mot_pot_field_test.p_min = 0;
    mot_pot_field_test.p_max = lim_field_regs_curr_ref.p_max_value;
    // Ручное задание тока.
    mot_pot_manual_curr_ref.p_min = lim_field_regs_curr_ref.p_min_value;
    mot_pot_manual_curr_ref.p_max = lim_field_regs_curr_ref.p_max_value;
    // Цифровой потенциометр опробования.
    IDLE(mot_pot_field_test);
    // Цифровой потенциометр ручного задания тока возбуждения.
    IDLE(mot_pot_manual_curr_ref);
    // Коэффициенты регуляторов.
    // Тока.
    IDLE(pid_coefs_i);
    pid_i.r_kp = pid_coefs_i.out_kp;
    pid_i.r_ki = pid_coefs_i.out_ki;
    pid_i.r_kd = pid_coefs_i.out_kd;
    pid_i.r_kf = pid_coefs_i.out_kf;
    // СИФУ.
    IDLE(ph3c);
    pid_i.r_min = ph3c.out_min_control_value;
    pid_i.r_max = ph3c.out_max_control_value;
    // Фильтры.
    // Фильтры напряжений для детекта нуля фаз.
    IDLE(filter_zcd_Ua);
    IDLE(filter_zcd_Ub);
    IDLE(filter_zcd_Uc);
    IDLE(filter_zcd_slip);
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

    // Настройки.
    IDLE(settings);

    // Хранилище.
    IDLE(storage);

    // Измерение времени выаполнения.
    sys_counter_value(&tv_run_end);
    timersub(&tv_run_end, &tv_run_start, &tv_run_time);
    sys->r_idle_run_time_us = tv_run_time.tv_sec * 1000000 + tv_run_time.tv_usec;
}

