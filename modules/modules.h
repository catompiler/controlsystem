#ifndef MODULES_H
#define MODULES_H


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
#include "data_log/data_log.h"
#include "meas/meas.h"
#include "rect_curr/rect_curr.h"
#include "mux/mux2.h"
#include "mux/mux3.h"
#include "mux/mux_abc.h"
#include "mux/mux_ui.h"
#include "phase_ampl/phase_ampl.h"
#include "zero_cross_detect/zero_cross_detect.h"
#include "slip/slip.h"
#include "phase_to_line/phase_to_line.h"
#include "rms/rms.h"
#include "dc_mean/dc_mean.h"
#include "power/power.h"
#include "fract_mean/fract_mean.h"
#include "valid_range3/valid_range3.h"
#include "filter1/filter1.h"
#include "phase3_control/phase3_control.h"
#include "larionov_model/smotor_larionov.h"
#include "motor/motor.h"
#include "prot/prot.h"


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
extern M_mux_abc cell_U;
//! Мультиплексор измерений токов ячейки.
extern M_mux_abc cell_I;
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
extern M_phase_to_line cell_U_line;

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

// Вычислители мощности.
extern M_power power_A;
extern M_power power_B;
extern M_power power_C;

// Допустимые диапазоны.
// Допустимый диапазон сетевых напряжений.
extern M_valid_range3 vr_rms_Umains;
// Допустимый диапазон частоты сети.
extern M_valid_range3 vr_filter_freq_Umains;

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
