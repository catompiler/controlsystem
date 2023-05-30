#ifndef MODULES_H
#define MODULES_H


#include "conf/conf.h"
#include "sys_main/sys_main.h"
#include "fake_adc/fake_adc.h"
#include "adc_timer/adc_timer.h"
#include "sys_timer/sys_timer.h"
#include "ms_timer/ms_timer.h"
#include "data_log/data_log.h"
#include "phase_ampl/phase_ampl.h"


extern M_conf conf;
extern M_sys_main sys;
extern M_fake_adc adc;
extern M_adc_timer adc_tim;
extern M_sys_timer sys_tim;
extern M_ms_timer ms_tim;
extern M_data_log dlog;

extern M_phase_ampl Ua_phase_ampl;
extern M_phase_ampl Ub_phase_ampl;
extern M_phase_ampl Uc_phase_ampl;

#endif /* MODULES_H */
