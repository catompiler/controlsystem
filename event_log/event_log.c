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

static void event_log_make_event(M_event_log* elog, event_data_t* ed, event_type_t type)
{
    size_t i;

    // Заголовок.
    ed->header.magic = (uint32_t)EVENT_MAGIC;
    ed->header.index = elog->m_events_index + 1;
    ed->header.type = type;

    for(i = 0; i < (sizeof(ed->header.reserved0)/sizeof(ed->header.reserved0[0])); i ++){
        ed->header.reserved0[i] = 0;
    }

    ed->header.crc = crc16_ccitt_ansi(&ed->header, EVENT_HEADER_SIZE - 2);

    // Информация о сообщении.
    ed->info.time = sys_time.r_counter_s;
    ed->info.error0 = prot.errors0;
    ed->info.error1 = prot.errors1;
    ed->info.error2 = prot.errors2;
    ed->info.reg_error0 = 0;
    ed->info.reg_error1 = 0;
    ed->info.reg_error2 = 0;
    ed->info.warning0 = prot.warnings0;
    ed->info.warning1 = prot.warnings1;
    ed->info.warning2 = prot.warnings2;
    ed->info.reg_warning0 = 0;
    ed->info.reg_warning1 = 0;
    ed->info.reg_warning2 = 0;
    ed->info.din = sys_cmd.out_command;
    ed->info.dout = sys_stat.in_command;
    ed->info.crc = crc16_ccitt_ansi(&ed->info, EVENT_INFO_SIZE - 2);

    // Информация об осциллограмме.
    ed->osc_info.Fs = 0;
    ed->osc_info.channels_count = 0;

    for(i = 0; i < (sizeof(ed->osc_info.reserved0)/sizeof(ed->osc_info.reserved0[0])); i ++){
       ed->osc_info.reserved0[i] = 0;
    }

    ed->osc_info.samples_count = 0;
    ed->osc_info.event_sample  = 0;
    ed->osc_info.crc = crc16_ccitt_ansi(&ed->osc_info, EVENT_OSC_INFO_SIZE - 2);
}

static void event_log_handle_event_written(M_event_log* elog)
{
    elog->m_events_map[elog->m_events_put] = elog->m_event_data.header.type;

    elog->m_events_index ++;

    CYCLIC_INC(elog->m_events_put, 0, (EVENTS_COUNT));
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

        if(header->crc == crc && header->magic == EVENT_MAGIC){

            elog->m_events_map[cmd->refresh.m_events_iter] = elog->m_event_data.header.type;

            if(header->index >= elog->m_events_index){
                elog->m_events_index = header->index;

                elog->m_events_put = cmd->refresh.m_events_iter;
                CYCLIC_INC(elog->m_events_put, 0, (EVENTS_COUNT));
            }
        }

        cmd->refresh.m_events_iter ++;

    }else{
        // init new refresh.
        elog->m_events_index = 0;
        elog->m_events_put = 0;
        cmd->refresh.m_events_iter = 0;
        cmd->refresh.m_events_min_index = 0;

        memset(elog->m_events_map, 0x0, sizeof(elog->m_events_map));
    }

    if(cmd->refresh.m_events_iter < EVENTS_COUNT){

        err = STORAGE_READ(storage, STORAGE_RGN_EVENTS, cmd->refresh.m_events_iter * EVENT_STORAGE_SIZE, &elog->m_event_data.header, EVENT_HEADER_SIZE, &elog->m_future);

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
    cmd->future = future;
    cmd->refresh.m_events_iter = 0;
    cmd->refresh.m_events_min_index = 0;

    future_init(&elog->m_future);

    elog->m_q_head_index = event_log_inc_queue_index(elog->m_q_head_index);
    event_log_inc_queue_count(elog);

    event_log_cmd_future_start(cmd);

    return E_IN_PROGRESS;
}

static void event_log_reset(M_event_log* elog, event_log_cmd_t* cmd)
{
    if(future_running(&elog->m_future)) return;

    err_t err = E_NO_ERROR;

    if(future_done(&elog->m_future)){

        err = FUTURE_RESULT_ERR(future_result(&elog->m_future));

        if(err != E_NO_ERROR){
            event_log_cmd_done(elog, cmd, err);
            return;
        }

        cmd->reset.m_events_iter ++;

    }else{
        // init new reset.
        elog->m_events_index = 0;
        elog->m_events_put = 0;
        cmd->reset.m_events_iter = 0;

        event_header_t* header = &elog->m_event_data.header;
        memset(header, 0xff, sizeof(event_header_t));

        memset(elog->m_events_map, 0x0, sizeof(elog->m_events_map));
    }

    if(cmd->reset.m_events_iter < EVENTS_COUNT){

        err = STORAGE_WRITE(storage, STORAGE_RGN_EVENTS, cmd->reset.m_events_iter * EVENT_STORAGE_SIZE, &elog->m_event_data.header, EVENT_HEADER_SIZE, &elog->m_future);

        if(err != E_IN_PROGRESS && err != E_NO_ERROR){
            event_log_cmd_done(elog, cmd, err);
            return;
        }
    }else{
        event_log_cmd_done(elog, cmd, E_NO_ERROR);
    }
}

static err_t event_log_post_reset(M_event_log* elog, future_t* future)
{
    if(elog->m_q_count == EVENT_LOG_QUEUE_LEN) return E_BUSY;

    event_log_cmd_t* cmd = &elog->m_queue[elog->m_q_head_index];

    cmd->type = EVENT_LOG_CONTROL_RESET;
    cmd->future = future;
    cmd->reset.m_events_iter = 0;

    future_init(&elog->m_future);

    elog->m_q_head_index = event_log_inc_queue_index(elog->m_q_head_index);
    event_log_inc_queue_count(elog);

    event_log_cmd_future_start(cmd);

    return E_IN_PROGRESS;
}

static void event_log_write(M_event_log* elog, event_log_cmd_t* cmd)
{
    if(future_running(&elog->m_future)) return;

    err_t err = E_NO_ERROR;

    if(future_done(&elog->m_future)){

        err = FUTURE_RESULT_ERR(future_result(&elog->m_future));

        if(err != E_NO_ERROR){
            event_log_cmd_done(elog, cmd, err);
            return;
        }

        if(!cmd->write.event_written){
            cmd->write.event_written = true;
        }

    }else{
        event_log_make_event(elog, &elog->m_event_data, cmd->write.type);

        cmd->write.event_written = false;
    }

    if(!cmd->write.event_written){

        err = STORAGE_WRITE(storage, STORAGE_RGN_EVENTS, elog->m_events_put * EVENT_STORAGE_SIZE, &elog->m_event_data, EVENT_DATA_SIZE, &elog->m_future);

        if(err != E_IN_PROGRESS && err != E_NO_ERROR){
            event_log_cmd_done(elog, cmd, err);
            return;
        }
    }else{
        event_log_handle_event_written(elog);

        event_log_cmd_done(elog, cmd, E_NO_ERROR);
    }
}

static err_t event_log_post_write(M_event_log* elog, event_type_t type, future_t* future)
{
    if(elog->m_q_count == EVENT_LOG_QUEUE_LEN) return E_BUSY;

    event_log_cmd_t* cmd = &elog->m_queue[elog->m_q_head_index];

    cmd->type = EVENT_LOG_CONTROL_WRITE;
    cmd->future = future;
    cmd->write.type = type;

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
            elog->status = EVENT_LOG_STATUS_ERROR;
        }
    }

    if(elog->control & EVENT_LOG_CONTROL_RESET){
        elog->control &= ~EVENT_LOG_CONTROL_RESET;

        err = event_log_post_reset(elog, NULL);
        if(err == E_NO_ERROR){
            elog->status = EVENT_LOG_STATUS_READY;
        }else if(err == E_IN_PROGRESS){
            elog->status = EVENT_LOG_STATUS_RUN;
        }else{
            elog->status = EVENT_LOG_STATUS_ERROR;
        }
    }

    if(elog->control & EVENT_LOG_CONTROL_WRITE){
        elog->control &= ~EVENT_LOG_CONTROL_WRITE;

        err = event_log_post_write(elog, EVENT_TYPE_INFO, NULL);
        if(err == E_NO_ERROR){
            elog->status = EVENT_LOG_STATUS_READY;
        }else if(err == E_IN_PROGRESS){
            elog->status = EVENT_LOG_STATUS_RUN;
        }else{
            elog->status = EVENT_LOG_STATUS_ERROR;
        }
    }
}

METHOD_IDLE_IMPL(M_event_log, elog)
{
//    recalc_values(elog);

    if(elog->m_q_count == 0) return;

    event_log_cmd_t* cmd = &elog->m_queue[elog->m_q_tail_index];

    switch(cmd->type){
    default:
        event_log_cmd_done(elog, cmd, E_INVALID_OPERATION);
        break;
    case EVENT_LOG_CONTROL_REFRESH:
        event_log_refresh(elog, cmd);
        break;
    case EVENT_LOG_CONTROL_RESET:
        event_log_reset(elog, cmd);
        break;
    case EVENT_LOG_CONTROL_WRITE:
        event_log_write(elog, cmd);
        break;
    }
}

EVENT_LOG_METHOD_REFRESH_IMPL(M_event_log, elog, future_t* future)
{
    return event_log_post_refresh(elog, future);
}

EVENT_LOG_METHOD_RESET_IMPL(M_event_log, elog, future_t* future)
{
    return event_log_post_reset(elog, future);
}

EVENT_LOG_METHOD_WRITE_IMPL(M_event_log, elog, event_type_t type, future_t* future)
{
    return event_log_post_write(elog, type, future);
}
