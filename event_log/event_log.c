#include "event_log.h"
#include "modules/modules.h"
#include "crc/crc16_ccitt.h"
#include "utils/utils.h"
#include <string.h>



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

    elog->status = (err == E_NO_ERROR) ? EVENT_LOG_STATUS_READY : EVENT_LOG_STATUS_ERROR;
}

static void event_log_refresh(M_event_log* elog, event_log_cmd_t* cmd)
{
    if(future_running(&elog->m_future)) return;

    err_t err = E_NO_ERROR;

    if(future_done(&elog->m_future)){

        err = FUTURE_RESULT_ERR(future_result(&elog->m_future));

        if(err != E_NO_ERROR){
            event_log_cmd_done(elog, cmd, err);
            return;
        }

        event_header_t* header = &elog->m_event_data.header;
        uint16_t crc = crc16_ccitt_ansi(header, EVENT_HEADER_SIZE - 2);

        if(header->crc == crc){
            elog->m_events_count ++;
            elog->m_events_map[elog->m_events_get] = elog->m_event_data.header.type;

            if(header->index >= elog->m_events_index){
                elog->m_events_index = header->index;

                elog->m_events_put = elog->m_events_get;
                CYCLIC_INC(elog->m_events_put, 0, (EVENTS_COUNT-1));
            }
        }

        elog->m_events_get ++;

    }else{
        // init new refresh.
        elog->m_events_count = 0;
        elog->m_events_index = 0;
        elog->m_events_put = 0;
        elog->m_events_get = 0;
        memset(elog->m_events_map, 0x0, sizeof(elog->m_events_map));
    }

    if(elog->m_events_get < EVENTS_COUNT){

        err = STORAGE_READ(storage, STORAGE_RGN_EVENTS, elog->m_events_get * EVENT_STORAGE_SIZE, &elog->m_event_data.header, EVENT_HEADER_SIZE, &elog->m_future);

        if(err != E_IN_PROGRESS && err != E_NO_ERROR){
            event_log_cmd_done(elog, cmd, err);
            return;
        }
    }else{
        event_log_cmd_done(elog, cmd, E_NO_ERROR);
    }
}

static err_t event_log_post_refresh(M_event_log* elog, future_t* future)
{
    if(elog->m_q_count == EVENT_LOG_QUEUE_LEN) return E_BUSY;

    event_log_cmd_t* cmd = &elog->m_queue[elog->m_q_head_index];

    cmd->type = EVENT_LOG_CONTROL_REFRESH;
    cmd->event_number = 0;
    cmd->osc_channel = 0;
    cmd->data = (void*)NULL;
    cmd->size = 0;
    cmd->future = future;

    future_init(&elog->m_future);

    elog->m_q_head_index = event_log_inc_queue_index(elog->m_q_head_index);
    event_log_inc_queue_count(elog);

    event_log_cmd_future_start(cmd);

    return E_IN_PROGRESS;
}

METHOD_CONTROL_IMPL(M_event_log, elog)
{
    err_t err;

    if(elog->control & EVENT_LOG_CONTROL_REFRESH){
        elog->control &= ~EVENT_LOG_CONTROL_REFRESH;

        err = event_log_post_refresh(elog, NULL);
        if(err == E_NO_ERROR){
            elog->status = EVENT_LOG_STATUS_READY;
        }else if(err == E_IN_PROGRESS){
            elog->status = EVENT_LOG_STATUS_RUN;
        }else{
            elog->status = ~EVENT_LOG_STATUS_ERROR;
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

EVENT_LOG_METHOD_REFRESH_IMPL(M_event_log, elog, future_t* future)
{
    return event_log_post_refresh(elog, future);
}
