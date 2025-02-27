#include "run_trig.h"
#include "modules/modules.h"


METHOD_INIT_IMPL(M_run_trig, rt)
{
}

METHOD_DEINIT_IMPL(M_run_trig, rt)
{
}

METHOD_CALC_IMPL(M_run_trig, rt)
{
    // Ток статора больше порогового.
    thr_run_trig_I_s.in_value = mean_rms_Icell.out_value;
    CALC(thr_run_trig_I_s);

    // Разрешение учитывания тока статора.
    am_run_trig_I_s.in_value[0] = thr_run_trig_I_s.out_value;
    CALC(am_run_trig_I_s);
    // Выбор условий запуска в зависимости от состояния контактов выключателя ячейки.
    if(cell_cb.out_state == CELL_CB_ON || cell_cb.out_state == CELL_CB_OFF){
        tmr_run_trig.in_value = (cell_cb.out_state == CELL_CB_ON) ? FLAG_ACTIVE : FLAG_NONE;
    }else{
        tmr_run_trig.in_value = am_run_trig_I_s.out_value;
    }
    // Таймер включения.
    CALC(tmr_run_trig);

    rt->out_value = tmr_run_trig.out_value;
}
