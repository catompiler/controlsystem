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
    fsm_init(&sys_ctrl->fsm_ready_on);

    // Начальное состояние.
    fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_INIT);
}

METHOD_DEINIT_IMPL(M_sys_control, sys_ctrl)
{
    // Конечные автоматы.
    // Основной КА.
    fsm_deinit(&sys_ctrl->fsm_state);
    // КА включения.
    fsm_deinit(&sys_ctrl->fsm_ready_on);

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
        // Перейдём в состояние "Выключен".
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_OFF);
    //}
}

static void FSM_state_off(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
    }

    // Если система управления разрешена.
    if(sys_ctrl->control & SYS_CONTROL_CONTROL_ENABLE){
        // Перейдём в состояние "Готов к включению".
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_READY_ON);
    }
}

static void FSM_state_ready_on(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
        // Сбросим КА включения.
        fsm_reset(&sys_ctrl->fsm_ready_on);
    }

    fsm_begin(&sys_ctrl->fsm_ready_on);

    switch(fsm_cur_state(&sys_ctrl->fsm_ready_on)){
    case SYS_CONTROL_READY_ON_NONE:
        fsm_set_state(&sys_ctrl->fsm_ready_on, SYS_CONTROL_READY_ON_WAIT_ON);
        break;

    case SYS_CONTROL_READY_ON_WAIT_ON:
        FSM_STATE_ENTRY(&sys_ctrl->fsm_ready_on){
            //
        }

        // Если получена команда включения.
        if(sys_ctrl->control & SYS_CONTROL_CONTROL_ON){
            // Перейдём в состояние ожидания сетевого напряжения.
            fsm_set_state(&sys_ctrl->fsm_ready_on, SYS_CONTROL_READY_ON_WAIT_MAINS);
        }

        break;

    case SYS_CONTROL_READY_ON_WAIT_MAINS:
        FSM_STATE_ENTRY(&sys_ctrl->fsm_ready_on){
            //
        }

        // Если напряжения в допустимых пределах.
        if((vr_rms_Ua.out_value == VALID_RANGE_WITHIN) &&
           (vr_rms_Ub.out_value == VALID_RANGE_WITHIN) &&
           (vr_rms_Uc.out_value == VALID_RANGE_WITHIN)){
            // Перейдём в состояние ожидания частоты сети.
            fsm_set_state(&sys_ctrl->fsm_ready_on, SYS_CONTROL_READY_ON_WAIT_MAINS_FREQ);
        }

        break;

    case SYS_CONTROL_READY_ON_WAIT_MAINS_FREQ:
        FSM_STATE_ENTRY(&sys_ctrl->fsm_ready_on){
        }

        //TODO: Wait for PLL.
        // Если частота в допустимых пределах.
        if((vr_filter_freq_Ua.out_value == VALID_RANGE_WITHIN) &&
           (vr_filter_freq_Ub.out_value == VALID_RANGE_WITHIN) &&
           (vr_filter_freq_Uc.out_value == VALID_RANGE_WITHIN)){
            // Перейдём в состояние ожидания частоты сети.
            fsm_set_state(&sys_ctrl->fsm_ready_on, SYS_CONTROL_READY_ON_WAIT_CONT_ON);
        }
        break;

    case SYS_CONTROL_READY_ON_WAIT_CONT_ON:
        FSM_STATE_ENTRY(&sys_ctrl->fsm_ready_on){
            //
        }

        // Если получено подтверждение включения главного контактора.
        if(sys_ctrl->control & SYS_CONTROL_CONTROL_ON){
            // Перейдём в состояние ожидания сетевого напряжения.
            fsm_set_state(&sys_ctrl->fsm_ready_on, SYS_CONTROL_READY_ON_DONE);
        }
        break;

    case SYS_CONTROL_READY_ON_DONE:
        // Переход в состояние ожидания запуска.
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_READY_RUN);
        break;
    }

    fsm_end(&sys_ctrl->fsm_ready_on);
}

static void FSM_state_ready_run(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
    }

    // Если получена команда "Работа".
    if(sys_ctrl->control & SYS_CONTROL_CONTROL_RUN){
        // Перейдём в состояние "Готов к включению".
        fsm_set_state(&sys_ctrl->fsm_state, SYS_CONTROL_STATE_RUN);
    }
}

static void FSM_state_run(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
    }
}

static void FSM_state_error(M_sys_control* sys_ctrl)
{
    FSM_STATE_ENTRY(&sys_ctrl->fsm_state){
    }
}

static void FSM_state(M_sys_control* sys_ctrl)
{
    // Начнём обработку состояний.
    fsm_begin(&sys_ctrl->fsm_state);

    switch(fsm_cur_state(&sys_ctrl->fsm_state)){
    case SYS_CONTROL_STATE_NONE:
        break;
    case SYS_CONTROL_STATE_INIT:
        FSM_state_init(sys_ctrl);
        break;
    case SYS_CONTROL_STATE_OFF:
        FSM_state_off(sys_ctrl);
        break;
    case SYS_CONTROL_STATE_READY_ON:
        FSM_state_ready_on(sys_ctrl);
        break;
    case SYS_CONTROL_STATE_READY_RUN:
        FSM_state_ready_run(sys_ctrl);
        break;
    case SYS_CONTROL_STATE_RUN:
        FSM_state_run(sys_ctrl);
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

    // Окончим обработку состояний.
    fsm_end(&sys_ctrl->fsm_state);
}

METHOD_CALC_IMPL(M_sys_control, sys_ctl)
{
    FSM_state(sys_ctl);
}
