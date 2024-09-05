#include "sys_control.h"
#include "modules/modules.h"


METHOD_INIT_IMPL(M_sys_control, sys_ctrl)
{
    // Сброс внутренних переменных.
    sys_ctrl->control = SYS_CONTROL_CONTROL_NONE;
    sys_ctrl->status = SYS_CONTROL_STATUS_NONE;
    sys_ctrl->errors = SYS_CONTROL_ERROR_NONE;
    sys_ctrl->warnings = SYS_CONTROL_WARNING_NONE;

    // Конечные автоматы.
    // Основной КА.
    fsm_init(&sys_ctrl->fsm_state);
    // КА включения.
    fsm_init(&sys_ctrl->fsm_idle);

    // Начальное состояние.
    fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_INIT);
}

METHOD_DEINIT_IMPL(M_sys_control, sys_ctrl)
{
    // Конечные автоматы.
    // Основной КА.
    fsm_deinit(&sys_ctrl->fsm_state);
    // КА включения.
    fsm_deinit(&sys_ctrl->fsm_idle);

    // Сброс внутренних переменных.
    sys_ctrl->control = SYS_CONTROL_CONTROL_NONE;
    sys_ctrl->status = SYS_CONTROL_STATUS_NONE;
    sys_ctrl->errors = SYS_CONTROL_ERROR_NONE;
    sys_ctrl->warnings = SYS_CONTROL_WARNING_NONE;
}

static void FSM_state_init(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
    }

    // Если всё проинициализировано.
    //if(){
        // Выйдем из состояния инициализации.
        // Перейдём в состояние "Простой".
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_CHECK);
    //}
}

static void FSM_state_check(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
        // Сбросим КА включения.
        fsm_reset(&sys_ctrl->fsm_check);
    }

    fsm_begin(&sys_ctrl->fsm_check);

    switch(fsm_cur_state(&sys_ctrl->fsm_check)){
    case SYS_CONTROL_CHECK_NONE:
        FSM_STATE_ENTRY(&sys_ctrl->fsm_check){
            //
        }

        fsm_set_state(&sys_ctrl->fsm_check, SYS_CONTROL_CHECK_WAIT_MAINS);
        break;

    case SYS_CONTROL_CHECK_WAIT_MAINS:
        FSM_STATE_ENTRY(&sys_ctrl->fsm_check){
            //
        }

        // Если напряжения в допустимых пределах.
        if(vr_rms_Umains.out_value_all == VALID_RANGE3_ALL_WITHIN){
            // Перейдём в состояние ожидания частоты сети.
            fsm_set_state(&sys_ctrl->fsm_check, SYS_CONTROL_CHECK_WAIT_MAINS_FREQ);
        }

        break;

    case SYS_CONTROL_CHECK_WAIT_MAINS_FREQ:
        FSM_STATE_ENTRY(&sys_ctrl->fsm_check){
        }

        // Если частота в допустимых пределах.
        if(vr_filter_freq_Umains.out_value_all == VALID_RANGE3_ALL_WITHIN){
            // Перейдём в состояние ожидания включения контактора.
            fsm_set_state(&sys_ctrl->fsm_check, SYS_CONTROL_CHECK_DONE);
        }

        break;

    case SYS_CONTROL_CHECK_DONE:
        // Переход в состояние ожидания запуска.
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_IDLE);
        break;
    }

    fsm_end(&sys_ctrl->fsm_check);
}

static void FSM_state_idle(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
        // Сбросим КА включения.
        fsm_reset(&sys_ctrl->fsm_idle);
    }

    fsm_begin(&sys_ctrl->fsm_idle);

    switch(fsm_cur_state(&sys_ctrl->fsm_idle)){
    case SYS_CONTROL_IDLE_NONE:
        FSM_STATE_ENTRY(&sys_ctrl->fsm_idle){
            //
        }

        fsm_set_state(&sys_ctrl->fsm_idle, SYS_CONTROL_IDLE_WAIT_CELL);
        break;

    case SYS_CONTROL_IDLE_WAIT_CELL:
        FSM_STATE_ENTRY(&sys_ctrl->fsm_idle){
            //
        }

        // Если напряжения в допустимых пределах.
        if(vr_rms_Ucell.out_value_all == VALID_RANGE3_ALL_WITHIN){
            // Перейдём в состояние ожидания частоты сети.
            fsm_set_state(&sys_ctrl->fsm_idle, SYS_CONTROL_IDLE_DONE);
        }

        break;

    case SYS_CONTROL_IDLE_DONE:
        // Переход в состояние ожидания запуска.
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_READY);
        break;
    }

    fsm_end(&sys_ctrl->fsm_idle);
}

static void FSM_state_ready(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
    }

    // Если получена команда "Опробование".
    if(sys_ctrl->control & SYS_CONTROL_CONTROL_TEST){
        // Перейдём в состояние "Опробование".
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_TEST);
    }

    // Если получена команда "Работа".
    if(sys_ctrl->control & SYS_CONTROL_CONTROL_RUN){
        // Перейдём в состояние "Запуск".
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_START);
    }
}

static void FSM_state_test(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
        ph3c.control |= CONTROL_ENABLE;
        //ph3c.in_control_value = IQ24(0.37667); //0.376658 //0.252
        ph3c.in_control_value = IQ24(0.5); //0.376658 //0.252
    }

    // Если отменена команда "Опробование".
    if(!(sys_ctrl->control & SYS_CONTROL_CONTROL_TEST)){
        // Перейдём в состояние "Инициализация".
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_INIT);
    }
}

static void FSM_state_start(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
        // Запустим счётчик времени пуска.
        cnt_start.control = CONTROL_START;
        CONTROL(cnt_start);
    }

    // Если время ожидания отключения пускового сопротивления вышло.
    if(tmr_field_on_rstart_off.out_value == FLAG_ACTIVE){
        // Остановим счётчик времени пуска.
        cnt_start.control = CONTROL_STOP;
        CONTROL(cnt_start);
        // Перейдём в состояние "Работа".
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_RUN);
    }

}

static void FSM_state_run(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
        pid_i.control = CONTROL_ENABLE;
        ph3c.control = CONTROL_ENABLE;

        pid_i.in_ref = IQ24(0.15);
    }

    pid_i.in_ref = pid_i.in_ref + IQ24(0.000025);//0.35
    pid_i.in_fbk = mean_Iarm.out_value;
    CALC(pid_i);

    ph3c.in_control_value = pid_i.out_value;


    // Если отменена команда "Работа".
    if(!(sys_ctrl->control & SYS_CONTROL_CONTROL_RUN)){
        // Перейдём в состояние "Гашение поля".
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_FIELD_SUPP);
    }
}

static void FSM_state_field_force(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
        pid_i.control = CONTROL_ENABLE;
        ph3c.control = CONTROL_ENABLE;

        pid_i.in_ref = IQ24(1.2);
    }

    pid_i.in_fbk = mean_Iarm.out_value;
    CALC(pid_i);

    ph3c.in_control_value = pid_i.out_value;


    // Если отменена команда "Форсировка".
    if(!(sys_ctrl->control & SYS_CONTROL_CONTROL_FORCE)){
        // Перейдём в состояние "Работа".
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_RUN);
    }
}

static void FSM_state_field_supp(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
        pid_i.control = CONTROL_ENABLE;
        ph3c.control = CONTROL_ENABLE;

        tmr_field_supp.control = CONTROL_START;
        CONTROL(tmr_field_supp);
    }

    pid_i.in_ref = 0;
    pid_i.in_fbk = mean_Iarm.out_value;
    CALC(pid_i);

    ph3c.in_control_value = pid_i.out_value;

    // Если поле погашено.
    if(tmr_field_supp.out_expired ||
       thr_field_supp_I_r.out_value == FLAG_ACTIVE){
        // Перейдём в состояние "Инициализация".
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_INIT);
    }
}

static void FSM_state_error(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
    }
}

//! До обработки состояний.
static void FSM_pre_state(M_sys_control* sys_ctrl)
{
}

//! После обработки состояний.
static void FSM_post_state(M_sys_control* sys_ctrl)
{
    //fsm_state_t state = fsm_state(&sys_ctrl->fsm_state);
    fsm_state_t cur_state = fsm_cur_state(&sys_ctrl->fsm_state);


    // Пусковое сопротивление.
    if(and_rstart_on.out_value == FLAG_ACTIVE){
        sys_ctrl->out_command |= SYS_CONTROL_COMMAND_R_START_ON;
    }else{
        sys_ctrl->out_command &= ~SYS_CONTROL_COMMAND_R_START_ON;
    }


    // Включение / выключение модулей в зависимости от состояния.
    switch(cur_state){
    case SYS_CONTROL_STATE_NONE:
        break;
    case SYS_CONTROL_STATE_INIT:
        break;
    case SYS_CONTROL_STATE_CHECK:
        break;
    case SYS_CONTROL_STATE_IDLE:
        break;
    case SYS_CONTROL_STATE_READY:
        break;
    case SYS_CONTROL_STATE_TEST:
        break;
    case SYS_CONTROL_STATE_START:
        break;
    case SYS_CONTROL_STATE_RUN:
        break;
    case SYS_CONTROL_STATE_FIELD_FORCE:
        break;
    case SYS_CONTROL_STATE_FIELD_SUPP:
        break;
    case SYS_CONTROL_STATE_ERROR:
        break;
    default:
        break;
    }
}

static void FSM_state(M_sys_control* sys_ctrl)
{
    // Начнём обработку состояний.
    fsm_begin(&sys_ctrl->fsm_state);

    // Общие действия до обработки состояний.
    FSM_pre_state(sys_ctrl);

    switch(fsm_cur_state(&sys_ctrl->fsm_state)){
    case SYS_CONTROL_STATE_NONE:
        break;
    case SYS_CONTROL_STATE_INIT:
        FSM_state_init(sys_ctrl);
        break;
    case SYS_CONTROL_STATE_CHECK:
        FSM_state_check(sys_ctrl);
        break;
    case SYS_CONTROL_STATE_IDLE:
        FSM_state_idle(sys_ctrl);
        break;
    case SYS_CONTROL_STATE_READY:
        FSM_state_ready(sys_ctrl);
        break;
    case SYS_CONTROL_STATE_TEST:
        FSM_state_test(sys_ctrl);
        break;
    case SYS_CONTROL_STATE_START:
        FSM_state_start(sys_ctrl);
        break;
    case SYS_CONTROL_STATE_RUN:
        FSM_state_run(sys_ctrl);
        break;
    case SYS_CONTROL_STATE_FIELD_FORCE:
        FSM_state_field_force(sys_ctrl);
        break;
    case SYS_CONTROL_STATE_FIELD_SUPP:
        FSM_state_field_supp(sys_ctrl);
        break;
    case SYS_CONTROL_STATE_ERROR:
        FSM_state_error(sys_ctrl);
        break;
    default:
        sys_ctrl->errors |= SYS_CONTROL_ERROR_SOFTWARE;
        sys_ctrl->status |= SYS_CONTROL_STATUS_ERROR;
        //TODO: Unhandled state process.
        break;
    }

    // Общие действия после обработки состояний.
    FSM_post_state(sys_ctrl);

    // Окончим обработку состояний.
    fsm_end(&sys_ctrl->fsm_state);
}

METHOD_CALC_IMPL(M_sys_control, sys_ctl)
{
    FSM_state(sys_ctl);
}
