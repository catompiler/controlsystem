#include "field_trig.h"
#include "modules/modules.h"


METHOD_INIT_IMPL(M_field_trig, ft)
{
}

METHOD_DEINIT_IMPL(M_field_trig, ft)
{
}

static void field_trig_calc_run(M_field_trig* ft)
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

    ft->out_run = tmr_run_trig.out_value;
}

static void field_trig_calc_field_on(M_field_trig* ft)
{
    // Ток статора для условий пуска.
    iq24_t I_stator = mean_rms_Icell.out_value;

    // Основное условие пуска.
    // Порог скольжения.
    thr_prim_Slip.in_value = slip.out_value;
    CALC(thr_prim_Slip);
    // Порог тока.
    thr_prim_I_s.in_value = I_stator;
    CALC(thr_prim_I_s);
    // Порог времени.
    thr_prim_T.in_value = cnt_start.out_value;
    CALC(thr_prim_T);
    // И с маской.
    am_prim_field_on.in_value[0] = thr_prim_Slip.out_value;
    am_prim_field_on.in_value[1] = thr_prim_I_s.out_value;
    am_prim_field_on.in_value[2] = thr_prim_T.out_value;
    CALC(am_prim_field_on);

    // Дополнительное условие пуска.
    // Порог скольжения.
    thr_sec_Slip.in_value = slip.out_value;
    CALC(thr_sec_Slip);
    // Порог тока.
    thr_sec_I_s.in_value = I_stator;
    CALC(thr_sec_I_s);
    // Порог времени.
    thr_sec_T.in_value = cnt_start.out_value;
    CALC(thr_sec_T);
    // И с маской.
    am_sec_field_on.in_value[0] = thr_sec_Slip.out_value;
    am_sec_field_on.in_value[1] = thr_sec_I_s.out_value;
    am_sec_field_on.in_value[2] = thr_sec_T.out_value;
    CALC(am_sec_field_on);

    // Таймер подачи возбуждения по условиям.
    tmr_field_on.in_value = am_prim_field_on.out_value || am_sec_field_on.out_value;
    CALC(tmr_field_on);


    // Подача возбуждения при самопроизвольном втягивании двигателя в синхронизм.
    // Триггер.
    thr_field_on_I_r_sync.in_value = mean_Irstart.out_value;
    CALC(thr_field_on_I_r_sync);
    // Таймер.
    tmr_field_on_I_r_sync.in_value = thr_field_on_I_r_sync.out_value;
    CALC(tmr_field_on_I_r_sync);


    // Цепочка завершения запуска и переход к подаче возбуждения.
    // Компаратор отрицательного значения величины для определения скольжения.
    thr_value_for_slip_lt_zero.in_value = filter_zcd_slip.out_value;
    CALC(thr_value_for_slip_lt_zero);

    // Готов подавать возбуждение.
    flag_t ready_to_exc = tmr_field_on.out_value && (thr_value_for_slip_lt_zero.out_value || tmr_field_on_I_r_sync.out_value);

    // Таймер отключения пускового сопротивления.
    tmr_field_on_rstart_off.in_value = ready_to_exc;
    CALC(tmr_field_on_rstart_off);

    ft->out_field_on = tmr_field_on_rstart_off.out_value;


    // Цепочка управления пусковым сопротивлением.
    // Включение пускового сопротивления == Не готов к подаче возбуждения И запуск.
    ft->out_rstart_on = (ready_to_exc == FLAG_NONE) && (fsm_state(&sys_ctrl.fsm_state) == SYS_CONTROL_STATE_START);
}

METHOD_CALC_IMPL(M_field_trig, ft)
{
    field_trig_calc_run(ft);
    field_trig_calc_field_on(ft);
}
