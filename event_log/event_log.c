#include "event_log.h"
#include "modules/modules.h"
#include "crc/crc16_ccitt.h"
#include "utils/utils.h"
#include "conf/consts.h"
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
    if(cmd->type == EVENT_LOG_CONTROL_WRITE){
        if(cmd->write.samples_before != 0 || cmd->write.samples_after != 0){
            dlog.control = DATA_LOG_CONTROL_ENABLE | DATA_LOG_CONTROL_RESET;
            CONTROL(dlog);
        }
    }

    event_log_cmd_future_finish(cmd, err);

    elog->m_q_tail_index = event_log_inc_queue_index(elog->m_q_tail_index);
    event_log_dec_queue_count(elog);

    elog->status = (err == E_NO_ERROR) ? EVENT_LOG_STATUS_READY : EVENT_LOG_STATUS_ERROR;
}

static void event_log_write_make_event(M_event_log* elog, event_data_t* ed, event_log_cmd_t* cmd)
{
    size_t i;

    // Заголовок.
    ed->header.magic = (uint32_t)EVENT_MAGIC;
    ed->header.index = elog->m_events_index + 1;
    ed->header.type = cmd->write.type;

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
    ed->osc_info.Fs = CONF_SAMPLE_RATE;
    ed->osc_info.samples_count = cmd->write.samples_before + cmd->write.samples_after;
    ed->osc_info.event_sample  = cmd->write.samples_before;
    ed->osc_info.channels_count = EVENT_OSC_CHANNELS_COUNT;

    for(i = 0; i < (sizeof(ed->osc_info.reserved0)/sizeof(ed->osc_info.reserved0[0])); i ++){
       ed->osc_info.reserved0[i] = 0;
    }

    ed->osc_info.crc = crc16_ccitt_ansi(&ed->osc_info, EVENT_OSC_INFO_SIZE - 2);
}

static void event_log_write_make_osc_channel(M_event_log* elog, event_osc_channel_t* ch, event_log_cmd_t* cmd)
{
    size_t i;
    size_t sample_index;

    data_log_ch_data_t* dlog_ch = &dlog.r_ch[cmd->write.osc_ch_n];

    if(dlog_ch->reg != NULL){
        bool is_signed = reg_is_signed(dlog_ch->reg);

        iql_t sample_min = (iql_t)dlog_ch->data[cmd->write.dlog_first];
        iql_t sample_max = (iql_t)dlog_ch->data[cmd->write.dlog_first];

        iql_t offset = 0;
        uiql_t gain = 0; //S0IQ8

        iql_t sample = 0;
        uiql_t delta = 0;

        // min/max.
        sample_index = cmd->write.dlog_first;
        for(i = 0; i < EVENT_OSC_SAMPLES_COUNT; i ++){

            sample = (iql_t)dlog_ch->data[sample_index];

            if(is_signed){
                if(sample_min > sample){
                    sample_min = sample;
                }
                if(sample_max < sample){
                    sample_max = sample;
                }
            }else{
                if((uint32_t)sample_min > (uint32_t)sample){
                    sample_min = (uint32_t)sample;
                }
                if((uint32_t)sample_max < (uint32_t)sample){
                    sample_max = (uint32_t)sample;
                }
            }

            DATA_LOG_NEXT_INDEX(sample_index);
        }

        // offset/gain.
        if(is_signed){
            offset = sample_min;
            gain = (uint32_t)((int64_t)sample_max - sample_min);
        }else{
            offset = sample_min;
            gain = (uint32_t)((uint32_t)sample_max - (uint32_t)sample_min);
        }
        // /256 -> /255
        {
            uint64_t gain64 = (((uint64_t)gain << 8)/255);
            if(gain64 <= UINT32_MAX){
                gain = (uint32_t)gain64;
            }else{
                gain = UINT32_MAX;
            }
        }

        // samples.
        sample_index = cmd->write.dlog_first;
        for(i = 0; i < EVENT_OSC_SAMPLES_COUNT; i ++){

            sample = (iql_t)dlog_ch->data[sample_index];

            if(is_signed){
                delta = (uint32_t)((int64_t)sample - sample_min);
            }else{
                delta = (uint32_t)sample - (uint32_t)sample_min;
            }

            if(gain != 0){
                delta = ((uint64_t)delta << 8) / gain;
            }

            ch->data.samples[i] = (delta <= 0xff) ? (uint8_t)delta : 0xff;

            DATA_LOG_NEXT_INDEX(sample_index);
        }

        ch->info.reg_id = reg_id(dlog_ch->reg);
        ch->info.gain = gain;
        ch->info.offset = offset;

    }else{
        ch->info.reg_id = REG_ID_NONE;
        ch->info.gain = 0;
        ch->info.offset = 0;
        memset(&ch->data.samples, 0x0, EVENT_OSC_SAMPLES_COUNT);
    }

    ch->info.crc = crc16_ccitt_ansi(&ch->info, EVENT_OSC_CHANNEL_INFO_SIZE - 2);
    ch->data.crc = crc16_ccitt_ansi(&ch->data, EVENT_OSC_CHANNEL_DATA_SIZE - 2);
}

static void event_log_handle_event_written(M_event_log* elog)
{
    elog->m_events_map[elog->m_events_put] = elog->m_event_data.header.type;

    elog->m_events_index ++;

    CYCLIC_INC(elog->m_events_put, 0, (EVENTS_COUNT));
}

static void event_log_refresh(M_event_log* elog, event_log_cmd_t* cmd)
{
    if(future_running(&cmd->m_future)) return;

    err_t err = E_NO_ERROR;

    if(future_done(&cmd->m_future)){

        err = FUTURE_RESULT_ERR(future_result(&cmd->m_future));

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

        err = STORAGE_READ(storage, STORAGE_RGN_EVENTS, cmd->refresh.m_events_iter * EVENT_STORAGE_SIZE, &elog->m_event_data.header, EVENT_HEADER_SIZE, &cmd->m_future);

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

    future_init(&cmd->m_future);

    elog->m_q_head_index = event_log_inc_queue_index(elog->m_q_head_index);
    event_log_inc_queue_count(elog);

    event_log_cmd_future_start(cmd);

    return E_IN_PROGRESS;
}

static void event_log_reset(M_event_log* elog, event_log_cmd_t* cmd)
{
    if(future_running(&cmd->m_future)) return;

    err_t err = E_NO_ERROR;

    if(future_done(&cmd->m_future)){

        err = FUTURE_RESULT_ERR(future_result(&cmd->m_future));

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

        err = STORAGE_WRITE(storage, STORAGE_RGN_EVENTS, cmd->reset.m_events_iter * EVENT_STORAGE_SIZE, &elog->m_event_data.header, EVENT_HEADER_SIZE, &cmd->m_future);

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

    future_init(&cmd->m_future);

    elog->m_q_head_index = event_log_inc_queue_index(elog->m_q_head_index);
    event_log_inc_queue_count(elog);

    event_log_cmd_future_start(cmd);

    return E_IN_PROGRESS;
}

static void event_log_write(M_event_log* elog, event_log_cmd_t* cmd)
{
    if(future_running(&cmd->m_future)) return;

    err_t err = E_NO_ERROR;

    if(future_done(&cmd->m_future)){

        err = FUTURE_RESULT_ERR(future_result(&cmd->m_future));

        if(err != E_NO_ERROR){
            event_log_cmd_done(elog, cmd, err);
            return;
        }

        if(!cmd->write.event_written){
            cmd->write.event_written = true;
        }
        else if(!cmd->write.osc_written){

            if(cmd->write.osc_ch_n == EVENT_OSC_CHANNELS_COUNT){
                cmd->write.osc_written = true;
            }
        }

    }else{
        if(dlog.control & DATA_LOG_CONTROL_ENABLE){
            cmd->write.samples_before = MIN(dlog.r_count, EVENT_OSC_SAMPLES_BEFORE_MAX);
            cmd->write.samples_after = EVENT_OSC_SAMPLES_COUNT - cmd->write.samples_before;

            cmd->write.dlog_first = dlog.r_put_index;
            DATA_LOG_BEFORE_INDEX(cmd->write.dlog_first, cmd->write.samples_before);

            dlog.in_stop_samples = EVENT_OSC_SAMPLES_AFTER_MIN;
            dlog.control |= DATA_LOG_CONTROL_STOP;
            CONTROL(dlog);

            cmd->write.osc_written = false;
        }else{
            cmd->write.samples_before = 0;
            cmd->write.samples_after = 0;

            cmd->write.osc_written = true;
        }

        event_log_write_make_event(elog, &elog->m_event_data, cmd);

        cmd->write.event_written = false;
        cmd->write.osc_ch_n = 0;
    }

    if(!cmd->write.event_written){

        err = STORAGE_WRITE(storage, STORAGE_RGN_EVENTS, elog->m_events_put * EVENT_STORAGE_SIZE, &elog->m_event_data, EVENT_DATA_SIZE, &cmd->m_future);

        if(err != E_IN_PROGRESS && err != E_NO_ERROR){
            event_log_cmd_done(elog, cmd, err);
            return;
        }
    }
    else if(!cmd->write.osc_written){

        if((dlog.control & DATA_LOG_CONTROL_STOP) && (dlog.control & DATA_LOG_CONTROL_ENABLE)){
            // Ждём окончания записи осциллограммы.
            return;
        }else if(dlog.control & DATA_LOG_CONTROL_ENABLE){
            // Кто-то вмешался в дата логгер.
            event_log_cmd_done(elog, cmd, E_STATE);
        }

        // Осциллограмма.
        event_osc_channel_t* osc_channel = &elog->m_osc_channel_data.channel;
        event_log_write_make_osc_channel(elog, osc_channel, cmd);

        // Адрес события в регионе.
        size_t address = elog->m_events_put * EVENT_STORAGE_SIZE;
        // Адрес осциллограммы.
        address += offsetof(event_t, osc);
        // Адрес данных.
        address += EVENT_OSC_CHANNEL_SIZE * cmd->write.osc_ch_n;

        err = STORAGE_WRITE(storage, STORAGE_RGN_EVENTS, address, osc_channel, EVENT_OSC_CHANNEL_SIZE, &cmd->m_future);

        if(err != E_IN_PROGRESS && err != E_NO_ERROR){
            event_log_cmd_done(elog, cmd, err);
            return;
        }

        cmd->write.osc_ch_n ++;
    }
    else{
        event_log_handle_event_written(elog);

        event_log_cmd_done(elog, cmd, E_NO_ERROR);
    }
}

static err_t event_log_post_write(M_event_log* elog, event_type_t type, future_t* future)
{
    if((size_t)type > EVENT_TYPE_ERROR) return E_INVALID_VALUE;

    if(elog->m_q_count == EVENT_LOG_QUEUE_LEN) return E_BUSY;

    event_log_cmd_t* cmd = &elog->m_queue[elog->m_q_head_index];

    cmd->type = EVENT_LOG_CONTROL_WRITE;
    cmd->future = future;
    cmd->write.type = type;
    cmd->write.event_written = false;
    cmd->write.osc_written = false;
    cmd->write.dlog_first = 0;
    cmd->write.samples_before = 0;
    cmd->write.samples_after = 0;
    cmd->write.osc_ch_n = 0;

    future_init(&cmd->m_future);

    elog->m_q_head_index = event_log_inc_queue_index(elog->m_q_head_index);
    event_log_inc_queue_count(elog);

    event_log_cmd_future_start(cmd);

    return E_IN_PROGRESS;
}

static void event_log_read(M_event_log* elog, event_log_cmd_t* cmd)
{
    if(future_running(&cmd->m_future)) return;

    err_t err = E_NO_ERROR;

    if(future_done(&cmd->m_future)){

        err = FUTURE_RESULT_ERR(future_result(&cmd->m_future));

        if(err != E_NO_ERROR){
            event_log_cmd_done(elog, cmd, err);
            return;
        }

        event_log_cmd_done(elog, cmd, E_NO_ERROR);

    }else{
        err = STORAGE_READ(storage, STORAGE_RGN_EVENTS, cmd->read.event_index * EVENT_STORAGE_SIZE, cmd->read.event_data, EVENT_DATA_SIZE, &cmd->m_future);

        if(err != E_IN_PROGRESS && err != E_NO_ERROR){
            event_log_cmd_done(elog, cmd, err);
            return;
        }
    }
}

static err_t event_log_post_read(M_event_log* elog, size_t event_n, event_data_t* event_data, future_t* future)
{
    if(event_n >= EVENTS_COUNT) return E_OUT_OF_RANGE;
    if(event_data == NULL) return E_NULL_POINTER;

    if(elog->m_q_count == EVENT_LOG_QUEUE_LEN) return E_BUSY;

    event_log_cmd_t* cmd = &elog->m_queue[elog->m_q_head_index];

    size_t event_index = elog->m_events_put + event_n;
    if(event_index >= EVENTS_COUNT) event_index -= EVENTS_COUNT;

    cmd->type = EVENT_LOG_CONTROL_READ;
    cmd->future = future;
    cmd->read.event_index = event_index;
    cmd->read.event_data = event_data;

    future_init(&cmd->m_future);

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

        err = event_log_post_write(elog, elog->in_event_type, NULL);
        if(err == E_NO_ERROR){
            elog->status = EVENT_LOG_STATUS_READY;
        }else if(err == E_IN_PROGRESS){
            elog->status = EVENT_LOG_STATUS_RUN;
        }else{
            elog->status = EVENT_LOG_STATUS_ERROR;
        }
    }

    if(elog->control & EVENT_LOG_CONTROL_READ){
        elog->control &= ~EVENT_LOG_CONTROL_READ;

        err = event_log_post_read(elog, elog->in_event_n, &elog->r_event_data, NULL);
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
    case EVENT_LOG_CONTROL_READ:
        event_log_read(elog, cmd);
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

EVENT_LOG_METHOD_READ_IMPL(M_event_log, elog, size_t event_n, event_data_t* event_data, future_t* future)
{
    return event_log_post_read(elog, event_n, event_data, future);
}
