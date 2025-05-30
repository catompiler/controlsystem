#include "event_log.h"


//static status_t recalc_values(M_event_log* elog)
//{
//    status_t res_status = STATUS_READY;
//
//    return res_status;
//}



METHOD_INIT_IMPL(M_event_log, elog)
{
    IDLE((*elog));
}

METHOD_DEINIT_IMPL(M_event_log, elog)
{
}

static void event_log_inc_queue_count(M_event_log* elog)
{
    if(elog->m_q_count < EVENT_LOG_QUEUE_LEN) elog->m_q_count ++;
}

static void event_log_dec_queue_count(M_event_log* elog)
{
    if(elog->m_q_count > 0) elog->m_q_count --;
}

static size_t event_log_inc_queue_index(size_t index)
{
    size_t new_index = index + 1;
    if(new_index >= EVENT_LOG_QUEUE_LEN) new_index = 0;
    return new_index;
}

ALWAYS_INLINE static void event_log_cmd_future_start(event_log_cmd_t* cmd)
{
    if(cmd->future) future_start(cmd->future);
}

ALWAYS_INLINE static void event_log_cmd_future_finish(event_log_cmd_t* cmd, err_t err)
{
    if(cmd->future) future_finish(cmd->future, FUTURE_RESULT(err));
}

static void event_log_cmd_done(M_event_log* elog, event_log_cmd_t* cmd, err_t err)
{
    event_log_cmd_future_finish(cmd, err);

    elog->m_q_tail_index = event_log_inc_queue_index(elog->m_q_tail_index);
    event_log_dec_queue_count(elog);

    elog->status = EVENT_LOG_STATUS_READY;
}

static void event_log_refresh(M_event_log* elog, event_log_cmd_t* cmd)
{
}

static err_t event_log_post_refresh(M_event_log* elog)
{
    if(elog->m_q_count == EVENT_LOG_QUEUE_LEN) return E_BUSY;

    event_log_cmd_t* cmd = &elog->m_queue[elog->m_q_head_index];

    cmd->type = STORAGE_CMD_READ;
    cmd->event_number = 0;
    cmd->osc_channel = 0;
    cmd->data = (void*)NULL;
    cmd->size = 0;
    cmd->future = NULL;

    future_init(&elog->m_future);

    elog->m_q_head_index = event_log_inc_queue_index(elog->m_q_head_index);
    event_log_inc_queue_count(elog);

    event_log_cmd_future_start(cmd);

    return E_IN_PROGRESS;
}

METHOD_CALC_IMPL(M_event_log, elog)
{
    err_t err;

    if(elog->control & EVENT_LOG_CONTROL_REFRESH){
        err = event_log_post_refresh(elog);
        if(err == E_NO_ERROR || err == E_IN_PROGRESS){
            elog->control &= ~EVENT_LOG_CONTROL_REFRESH;
        }
    }
}

METHOD_IDLE_IMPL(M_event_log, elog)
{
//    recalc_values(elog);

    if(elog->m_q_count == 0) return;

    event_log_cmd_t* cmd = &elog->m_queue[elog->m_q_tail_index];

    if(cmd->type == EVENT_LOG_CONTROL_REFRESH){
        event_log_refresh(elog, cmd);
    }
}
