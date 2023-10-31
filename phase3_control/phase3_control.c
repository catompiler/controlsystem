#include "phase3_control.h"
#include "utils/utils.h"


METHOD_INIT_IMPL(M_phase3_control, ph3c)
{
}

METHOD_DEINIT_IMPL(M_phase3_control, ph3c)
{
}

METHOD_CALC_IMPL(M_phase3_control, ph3c)
{
    // [ AB, AC, BC, BA, CA, CB ]
    iq24_t angles_values[PHASE3_CONTROL_KEYS_COUNT] = {
         ph3c->in_Uab_angle_pu, (ph3c->in_Uca_angle_pu + IQ24_PI_PU) & (IQ24_2PI_PU - 1),
         ph3c->in_Ubc_angle_pu, (ph3c->in_Uab_angle_pu + IQ24_PI_PU) & (IQ24_2PI_PU - 1),
         ph3c->in_Uca_angle_pu, (ph3c->in_Ubc_angle_pu + IQ24_PI_PU) & (IQ24_2PI_PU - 1)
    };

    int i = 0;

    // Вычисления фазового управления.
    for(i = 0; i < PHASE3_CONTROL_KEYS_COUNT; i ++){
        ph3c->phc[i].control = ph3c->control & CONTROL_ENABLE;
        ph3c->phc[i].in_angle_pu = angles_values[i];
        ph3c->phc[i].in_control_angle_pu = ph3c->in_control_angle_pu;
        ph3c->phc[i].in_min_angle_to_control_pu = ph3c->p_min_angle_to_control_pu;
        ph3c->phc[i].in_max_angle_to_control_pu = ph3c->p_max_angle_to_control_pu;

        ph3c->phc[i].calc(&ph3c->phc[i]);
    }

    // Сброс выходов управления.
    for(i = 0; i < PHASE3_CONTROL_KEYS_COUNT; i ++){
        ph3c->out_control[i] = 0;
    }

    if(ph3c->control & CONTROL_ENABLE){

        int control_index = -1; // Индекс управления.
        iq24_t control_delay_angle = 0; // Угол до подачи управления.
        iq24_t control_duration_angle = 0; // Продолжительность (угол) управления.

        // Поиск управления с минимальным углом фазы,
        // так как эта фаза наиболее близка к углу управления.
        iq24_t min_angle = 2 * IQ24_2PI_PU; // Минимальный фазный угол. По-умолчанию заведомо бОльшее значение.

        for(i = 0; i < PHASE3_CONTROL_KEYS_COUNT; i ++){
            if(ph3c->phc[i].out_control && ph3c->phc[i].in_angle_pu < min_angle){
                min_angle = ph3c->phc[i].in_angle_pu;
                control_index = i;
                control_delay_angle = ph3c->phc[i].out_control_angle_pu - ph3c->phc[i].in_angle_pu;
                control_duration_angle = MAX(0, ph3c->p_max_angle_to_control_pu - ph3c->phc[i].out_control_angle_pu);
            }
        }

        // Если есть активное управление,
        // то установим его выход.
        if(control_index != -1){

            int self_index = control_index;
            int pair_index = self_index - 1;
            if(pair_index < 0) pair_index = PHASE3_CONTROL_KEYS_COUNT - 1;

            //TODO: out_control as bit field.
            ph3c->out_control[self_index] = STROBE_ACTIVE;
            ph3c->out_control[pair_index] = STROBE_ACTIVE;

            ph3c->out_control_delay_angle_pu = control_delay_angle;
            ph3c->out_control_max_duration_angle_pu = control_duration_angle;
        }
    } //in_enable
}
