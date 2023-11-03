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
#include "meas_mux/armature_i_mux.h"
#include "meas_mux/armature_u_mux.h"
#include "meas_mux/mains_i_mux.h"
#include "meas_mux/mains_u_mux.h"
#include "phase_ampl/phase_ampl.h"
#include "zero_cross_detect/zero_cross_detect.h"
#include "rms/rms.h"
#include "valid_range/valid_range.h"
#include "filter1/filter1.h"
#include "phase3_control/phase3_control.h"
#include "larionov_model/larionov_model.h"
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

// Мультиплексоры измерений.
//! Мультиплексор измерений входных напряжений.
extern M_mains_u_mux mains_U;
//! Мультиплексор измерений входных токов.
extern M_mains_i_mux mains_I;
//! Мультиплексор измерений выходного напряжения.
extern M_armature_u_mux armature_U;
//! Мультиплексор измерений выходного тока.
extern M_armature_i_mux armature_I;

// Вычислители фазы и амплитуды фаз.
extern M_phase_ampl phase_ampl_Ua;
extern M_phase_ampl phase_ampl_Ub;
extern M_phase_ampl phase_ampl_Uc;

// Вычислители периода, частоты и пересечения нуля фаз.
extern M_zero_cross_detect zcd_Ua;
extern M_zero_cross_detect zcd_Ub;
extern M_zero_cross_detect zcd_Uc;

// Вычислители RMS.
extern M_rms rms_Ua;
extern M_rms rms_Ub;
extern M_rms rms_Uc;

// Допустимые диапазоны значений.
// Допустимые диапазоны сетевых напряжений.
extern M_valid_range vr_rms_Ua;
extern M_valid_range vr_rms_Ub;
extern M_valid_range vr_rms_Uc;
// Допустимые диапазоны частоты сети.
extern M_valid_range vr_filter_freq_Ua;
extern M_valid_range vr_filter_freq_Ub;
extern M_valid_range vr_filter_freq_Uc;

// Фильтры.
// Напряжения фаз для детекта перехода через ноль.
extern M_filter1 filter_Ua_zcd;
extern M_filter1 filter_Ub_zcd;
extern M_filter1 filter_Uc_zcd;
// Частота фаз.
extern M_filter1 filter_freq_Ua;
extern M_filter1 filter_freq_Ub;
extern M_filter1 filter_freq_Uc;

//! СИФУ.
extern M_phase3_control ph3c;

//! Модель ларионова.
extern M_larionov_model lrm;

// Защиты.
//! Модуль защиты.
extern M_prot prot;

#endif /* MODULES_H */
