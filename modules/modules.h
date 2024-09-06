#ifndef MODULES_H
#define MODULES_H


#include <phase_line/star_phase_to_line.h>
#include "conf/conf.h"
#include "adc/adc.h"
#include "adc_model/adc_model.h"
#include "sys_main/sys_main.h"
#include "sys_command/sys_command.h"
#include "sys_control/sys_control.h"
#include "sys_status/sys_status.h"
#include "adc_timer/adc_timer.h"
#include "sys_timer/sys_timer.h"
#include "ms_timer/ms_timer.h"
#include "sys_time/sys_time.h"
#include "timer/timer.h"
#include "timer/timer_on.h"
#include "timer/counter.h"
#include "data_log/data_log.h"
#include "filter1/filter1.h"
#include "meas/meas.h"
#include "rect_curr/rect_curr.h"
#include "mux/mux2.h"
#include "mux/mux3.h"
#include "mux/mux4.h"
#include "mux/mux_abc.h"
#include "mux/mux_ui.h"
#include "phase_ampl/phase_ampl.h"
#include "zero_cross_detect/zero_cross_detect.h"
#include "slip/slip.h"
#include "phase_line/delta_line_to_phase.h"
#include "phase_line/star_line_to_phase.h"
#include "value_3phase/value_3phase.h"
#include "rms/rms.h"
#include "dc_mean/dc_mean.h"
#include "mean/mean3.h"
#include "power/power.h"
#include "power_factor/power_factor.h"
#include "fract_mean/fract_mean.h"
#include "valid_range3/valid_range3.h"
#include "threshold/threshold_lt.h"
#include "threshold/threshold_le.h"
#include "threshold/threshold_gt.h"
#include "limit/limit.h"
#include "comp/comp_lt.h"
#include "comp/comp_eq.h"
#include "logic/and1_mask.h"
#include "logic/and3_mask.h"
#include "logic/and2.h"
#include "logic/or2_mask.h"
#include "logic/or2.h"
#include "logic/not.h"
#include "sum/sum3.h"
#include "cell_cb/cell_cb.h"
#include "phase3_control/phase3_control.h"
#include "larionov_model/smotor_larionov.h"
#include "motor/motor.h"
#include "prot/prot.h"
#include "pid/pid.h"
#include "pid/pid_coefs.h"
#include "mot_pot/mot_pot.h"


//! Основной модуль.
extern M_sys_main sys;
//! Основной командный модуль.
extern M_sys_command sys_cmd;
//! Основной модуль управления.
extern M_sys_control sys_ctrl;
//! Основной модуль состояния.
extern M_sys_status sys_stat;

//! Конфигурация.
extern M_conf conf;
//! АЦП.
extern M_adc adc;
//! АЦП модель.
extern M_adc_model adc_model;

// Аппаратные таймеры.
//! Таймер АЦП.
extern M_adc_timer adc_tim;
//! Таймер системы управления.
extern M_sys_timer sys_tim;
//! мс таймер.
extern M_ms_timer ms_tim;

//! Счётчик системного времени в с и мс.
extern M_sys_time sys_time;

// Программные мс таймеры.
//! Общий таймер для КА системы управления.
extern M_timer tmr_sys_fsm;
/*//! Таймер ожидания инициализации модулей.
extern M_timer tmr_sys_init;*/
/*//! Таймер ожидания запуска возбуждения.
extern M_timer tmr_sys_fld_wait;*/

//! Осциллограф.
extern M_data_log dlog;

//! Модуль измерений.
extern M_meas meas;

//! Вычислитель выпрямленного тока по трём входящим.
extern M_rect_curr rect_curr;

// Мультиплексоры измерений.
//! Мультиплексор измерений входных напряжений.
extern M_mux_abc mux_Umains;
//! Мультиплексор измерений входных токов.
extern M_mux_abc mux_Imains;
//! Мультиплексор измерений выходного напряжения.
extern M_mux2 mux_Uarm;
//! Мультиплексор измерений выходного тока.
extern M_mux3 mux_Iarm;
//! Мультиплексор измерений тока пускового сопротивления.
extern M_mux2 mux_Irstart;
//! Мультиплексор измерений напряжений ячейки.
extern M_mux_abc mux_Ucell;
//! Мультиплексор измерений токов ячейки.
extern M_mux_abc mux_Icell;
//! Мультиплексор скольжения.
extern M_mux2 mux_slip;

// Вычислители фазы и амплитуды фаз.
extern M_phase_ampl phase_ampl_Ua;
extern M_phase_ampl phase_ampl_Ub;
extern M_phase_ampl phase_ampl_Uc;

// Вычислители периода, частоты и пересечения нуля фаз.
extern M_zero_cross_detect zcd_Ua;
extern M_zero_cross_detect zcd_Ub;
extern M_zero_cross_detect zcd_Uc;
extern M_zero_cross_detect zcd_slip;

// Скольжение.
extern M_slip slip;

// Преобразование фазных напряжений ячейки в линейные.
extern M_delta_line_to_phase phase_lrm_I_stator;

// Преобразование линейных напряжений в фазные.
extern M_star_line_to_phase phase_Ucell;

// Вычисление значения одной из фаз тока и напряжения.
extern M_value_3phase calc_Ucell;
extern M_value_3phase calc_Icell;

// Вычислители RMS.
extern M_rms rms_Ua;
extern M_rms rms_Ub;
extern M_rms rms_Uc;
extern M_rms rms_Ia;
extern M_rms rms_Ib;
extern M_rms rms_Ic;
extern M_rms rms_cell_Ua;
extern M_rms rms_cell_Ub;
extern M_rms rms_cell_Uc;
extern M_rms rms_cell_Ua_phase;
extern M_rms rms_cell_Ub_phase;
extern M_rms rms_cell_Uc_phase;
extern M_rms rms_cell_Ia;
extern M_rms rms_cell_Ib;
extern M_rms rms_cell_Ic;

// Вычислители среднего.
#if (CONF_PERIOD_SAMPLES % 6 != 0)
extern M_fract_mean mean_Iarm;
extern M_fract_mean mean_Uarm;
extern M_fract_mean mean_Irstart;
#else // (CONF_PERIOD_SAMPLES % 6 != 0)
extern M_dc_mean mean_Iarm;
extern M_dc_mean mean_Uarm;
extern M_dc_mean mean_Irstart;
#endif // (CONF_PERIOD_SAMPLES % 6 != 0)
extern M_mean3 mean_rms_Icell;

// Сумматоры мощности.
extern M_sum3 sum_S;
extern M_sum3 sum_P;
extern M_sum3 sum_Q;

// Вычислители мощности.
extern M_power power_A;
extern M_power power_B;
extern M_power power_C;

// Коэффициент мощности.
extern M_power_factor power_factor;

// Допустимые диапазоны.
// Допустимый диапазон сетевых напряжений.
extern M_valid_range3 vr_rms_Umains;
// Допустимый диапазон частоты сети.
extern M_valid_range3 vr_filter_freq_Umains;
// Допустимый диапазон напряжений ячейки.
extern M_valid_range3 vr_rms_Ucell;

// Состояние ячейки.
extern M_cell_cb cell_cb;

// Триггеры работы двигателя.
// Порог превышения током статора заданного значения.
extern M_threshold_gt thr_run_trig_I_s;
// Разрешение учитывания тока статора.
extern M_and1_mask am_run_trig_I_s;
// Выбор условий запуска в зависимости от состояния контактов выключателя ячейки.
extern M_mux2 mux_run_trig;
// Таймер до включения по порогу тока статора.
extern M_timer_on tmr_run_trig;

// Подача возбуждения.
// Основной критерий подачи возбуждения.
// Порог снижения скольжения.
extern M_threshold_lt thr_prim_Slip;
// Порог снижения тока статора.
extern M_threshold_lt thr_prim_I_s;
// Порог минимального времени.
extern M_threshold_gt thr_prim_T;
// И по маске.
extern M_and3_mask am_prim_field_on;
// Дополнительный критерий подачи возбуждения.
// Порог снижения скольжения.
extern M_threshold_lt thr_sec_Slip;
// Порог снижения тока статора.
extern M_threshold_lt thr_sec_I_s;
// Порог минимального времени.
extern M_threshold_gt thr_sec_T;
// И по маске.
extern M_and3_mask am_sec_field_on;

// Триггер пуска.
// ИЛИ двух критериев.
extern M_or2 or_field_on;
// Таймер разрешения включения.
extern M_timer_on tmr_field_on;

// Цепочка завершения запуска и переход к подаче возбуждения.
// Компаратор отрицательного значения величины для определения скольжения.
extern M_threshold_lt thr_value_for_slip_lt_zero;
// Величина для определения меньше нуля ИЛИ ротор сам втянулся в синхронизм.
extern M_or2 or_value_slip_lt_zero_I_r_sync;
// Нужно подавать возбуждение И можно открывать тиристоры.
extern M_and2 and_ready_to_exc; // and_field_on_slip_sync
// Таймер отключения пускового сопротивления.
extern M_timer_on tmr_field_on_rstart_off;
// Цепочка управления пусковым сопротивлением.
// НЕ готовность подачи возбуждения.
extern M_not not_ready_to_exc;
// Компаратор состояния системы управления.
extern M_comp_eq cmp_ctrl_state_is_start;
// Включение пускового сопротивления == Не готов к подаче возбуждения И запуск.
extern M_and2 and_rstart_on;


// Порог тока ротора при втягивании ротора
// в синхронизм без подачи возбуждения.
extern M_threshold_lt thr_field_on_I_r_sync;
// Таймер разрешения включения
// при втягивании в синхронизм (нет детекта отрицательной полуволны).
extern M_timer_on tmr_field_on_I_r_sync;

// Гашение поля.
// Порог тока ротора, при котором гашения поля прекращается.
extern M_threshold_lt thr_field_supp_I_r;
// Таймер максимальной продолжительности гашения поля.
extern M_timer tmr_field_supp;

// Таймеры / счётчики.
// Счётчик времени старта.
extern M_counter cnt_start;


// Фильтры.
// Напряжения фаз для детекта перехода через ноль.
extern M_filter1 filter_zcd_Ua;
extern M_filter1 filter_zcd_Ub;
extern M_filter1 filter_zcd_Uc;
extern M_filter1 filter_zcd_slip;
// Частота фаз.
extern M_filter1 filter_freq_Ua;
extern M_filter1 filter_freq_Ub;
extern M_filter1 filter_freq_Uc;
extern M_filter1 filter_freq_slip;
// Среднее значение тока выхода.
extern M_filter1 filter_mean_Iarm;
// Среднее значение напряжения выхода.
extern M_filter1 filter_mean_Uarm;
// Среднее значение тока пускового сопротивления.
extern M_filter1 filter_mean_Irstart;

// Форсировка при запуске.
//! Таймер минимального времени форсировки.
extern M_timer tmr_start_min_forcing;
//! Таймер максимального времени форсировки.
extern M_timer tmr_start_max_forcing;
//! Таймер окончания форсировки (время стабилизации).
extern M_timer_on tmr_start_stab_forcing;
//! Компаратор не положительной реактивной мощности.
extern M_threshold_le thr_start_Q_le_zero;
//! Прошло минимальное время форсировки И форсировка завершена.
extern M_and2 and_start_min_forcing_end;
//! Прошло максимальное время форсировки ИЛИ форсировка завершена.
extern M_or2 or_start_forcing_end;

// Регуляторы.
// Контур тока.
//! Мультиплексор регуляторов.
//! 0 - Ручной.
extern M_mux4 mux_field_regs;
//! Ограничитель тока регуляторов.
extern M_limit lim_field_regs_curr_ref;
//! Мультиплексор задания тока при форсировке.
extern M_mux2 mux_field_force_ref;
//! Цифровой потенциометр для опробования.
extern M_mot_pot mot_pot_field_test;
//! Цифровой потенциометр ручного задания тока.
extern M_mot_pot mot_pot_manual_curr_ref;
//! Мультиплексор задания тока.
//! 0 - Задание гашения поля.
//! 1 - Задание опробования.
//! 2 - Задание форсировки.
//! 3 - Задание работы.
extern M_mux4 mux_curr_ref;
//! ПИД тока.
extern M_pid pid_i;
//! Коэффициенты ПИД тока.
extern M_pid_coefs pid_coefs_i;

//! СИФУ.
extern M_phase3_control ph3c;

//! Модель ларионова.
//extern M_larionov_model lrm;
extern M_smotor_larionov lrm;

//! Модуль мотора.
extern M_motor motor;

// Защиты.
//! Модуль защиты.
extern M_prot prot;

#endif /* MODULES_H */
