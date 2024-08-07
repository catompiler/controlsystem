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
#include "threshold/threshold_gt.h"
#include "logic/and1_mask.h"
#include "logic/and3_mask.h"
#include "logic/or2_mask.h"
#include "logic/or2.h"
#include "cell_cb/cell_cb.h"
#include "phase3_control/phase3_control.h"
#include "larionov_model/smotor_larionov.h"
#include "motor/motor.h"
#include "prot/prot.h"
#include "pid/pid.h"
#include "pid/pid_coefs.h"


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
extern M_mux_abc mains_U;
//! Мультиплексор измерений входных токов.
extern M_mux_abc mains_I;
//! Мультиплексор измерений выходного напряжения.
extern M_mux2 armature_U;
//! Мультиплексор измерений выходного тока.
extern M_mux3 armature_I;
//! Мультиплексор измерений тока пускового сопротивления.
extern M_mux2 rstart_I;
//! Мультиплексор измерений напряжений ячейки.
extern M_mux_abc mux_cell_U;
//! Мультиплексор измерений токов ячейки.
extern M_mux_abc mux_cell_I;
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
extern M_delta_line_to_phase lrm_I_stator_phase;

// Преобразование линейных напряжений в фазные.
extern M_star_line_to_phase cell_U_phase;

// Вычисление значения одной из фаз тока и напряжения.
extern M_value_3phase cell_U;
extern M_value_3phase cell_I;

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
extern M_mean3 mean_rms_I_cell;

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

// Порог тока ротора при втягивании ротора
// в синхронизм без подачи возбуждения.
extern M_threshold_lt thr_field_on_I_r_sync;
// Таймер разрешения включения
// при втягивании в синхронизм (нет детекта отрицательной полуволны).
extern M_timer_on tmr_field_on_I_r_sync;
// Таймер отключения пускового сопротивления.
extern M_timer tmr_field_on_rstart_off;

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
extern M_filter1 filter_Ua_zcd;
extern M_filter1 filter_Ub_zcd;
extern M_filter1 filter_Uc_zcd;
extern M_filter1 filter_slip_zcd;
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

// Регуляторы.
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
