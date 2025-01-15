#include "storage.h"
#include "defs/defs.h"



STORAGE_METHOD_INIT_IMPL(M_storage, storage, eeprom_t* eeprom)
{
    err_t err = E_NO_ERROR;

    if(eeprom == NULL) err = E_NULL_POINTER;

    storage->m_eeprom = eeprom;
    storage->m_q_count = 0;
    storage->m_q_head_index = 0;
    storage->m_q_tail_index = 0;

    future_init(&storage->m_future);

    if(err != E_NO_ERROR){
        storage->status = STORAGE_STATUS_ERROR;
    }else{
        storage->status = STORAGE_STATUS_READY;
    }

    return err;
}

METHOD_DEINIT_IMPL(M_storage, storage)
{
    eeprom_deinit(storage->m_eeprom);
}

static void storage_inc_queue_count(M_storage* storage)
{
    if(storage->m_q_count < STORAGE_QUEUE_LEN) storage->m_q_count ++;
}

static void storage_dec_queue_count(M_storage* storage)
{
    if(storage->m_q_count > 0) storage->m_q_count --;
}

static size_t storage_inc_queue_index(size_t index)
{
    size_t new_index = index + 1;
    if(new_index >= STORAGE_QUEUE_LEN) new_index = 0;
    return new_index;
}

ALWAYS_INLINE static void storage_cmd_future_start(storage_cmd_t* cmd)
{
    if(cmd->future) future_start(cmd->future);
}

ALWAYS_INLINE static void storage_cmd_future_finish(storage_cmd_t* cmd, err_t err)
{
    if(cmd->future) future_finish(cmd->future, FUTURE_RESULT(err));
}

static void storage_cmd_done(M_storage* storage, storage_cmd_t* cmd, err_t err)
{
    storage_cmd_future_finish(cmd, err);

    storage->m_q_tail_index = storage_inc_queue_index(storage->m_q_tail_index);
    storage_dec_queue_count(storage);

    storage->status = STORAGE_STATUS_READY;
}

static void storage_process_erase(M_storage* storage, storage_cmd_t* cmd)
{
    if(future_running(&storage->m_future)) return;

    if(future_done(&storage->m_future)){
        storage_cmd_done(storage, cmd, FUTURE_RESULT_ERR(future_result(&storage->m_future)));
        return;
    }

    future_init(&storage->m_future);

    err_t err = eeprom_erase(storage->m_eeprom, cmd->address, cmd->size, &storage->m_future, EEPROM_FLAG_NONE);
    if(err != E_IN_PROGRESS){
        storage_cmd_done(storage, cmd, err);
        return;
    }

    storage->status = STORAGE_STATUS_RUN;
}

static void storage_process_write(M_storage* storage, storage_cmd_t* cmd)
{
    if(future_running(&storage->m_future)) return;

    if(future_done(&storage->m_future)){
        storage_cmd_done(storage, cmd, FUTURE_RESULT_ERR(future_result(&storage->m_future)));
        return;
    }

    future_init(&storage->m_future);

    err_t err = eeprom_write(storage->m_eeprom, cmd->address, cmd->data, cmd->size, &storage->m_future, EEPROM_FLAG_NONE);
    if(err != E_IN_PROGRESS){
        storage_cmd_done(storage, cmd, err);
        return;
    }

    storage->status = STORAGE_STATUS_RUN;
}

static void storage_process_read(M_storage* storage, storage_cmd_t* cmd)
{
    if(future_running(&storage->m_future)) return;

    if(future_done(&storage->m_future)){
        storage_cmd_done(storage, cmd, FUTURE_RESULT_ERR(future_result(&storage->m_future)));
        return;
    }

    future_init(&storage->m_future);

    err_t err = eeprom_read(storage->m_eeprom, cmd->address, cmd->data, cmd->size, &storage->m_future, EEPROM_FLAG_NONE);
    if(err != E_IN_PROGRESS){
        storage_cmd_done(storage, cmd, err);
        return;
    }

    storage->status = STORAGE_STATUS_RUN;
}

METHOD_IDLE_IMPL(M_storage, storage)
{
    if(storage->m_q_count == 0) return;

    storage_cmd_t* cmd = &storage->m_queue[storage->m_q_tail_index];

    if(cmd->type == STORAGE_CMD_ERASE){
        storage_process_erase(storage, cmd);
    }
    else if(cmd->type == STORAGE_CMD_WRITE){
        storage_process_write(storage, cmd);
    }
    else if(cmd->type == STORAGE_CMD_READ){
        storage_process_read(storage, cmd);
    }

    eeprom_process(storage->m_eeprom);
}

static size_t storage_region_address(unsigned int rgn)
{
    switch(rgn){
    default:
        break;
    case STORAGE_RGN_SETTINGS:
        return STORAGE_MEM_BEG + STORAGE_MEM_RGN_SETTINGS_OFFSET;
    case STORAGE_RGN_OSC0:
    case STORAGE_RGN_OSC1:
    case STORAGE_RGN_OSC2:
    case STORAGE_RGN_OSC3:
        break;
    }
    return 0;
}

static size_t storage_region_size(unsigned int rgn)
{
    switch(rgn){
    default:
        break;
    case STORAGE_RGN_SETTINGS:
        return STORAGE_MEM_RGN_SETTINGS_SIZE;
    case STORAGE_RGN_OSC0:
    case STORAGE_RGN_OSC1:
    case STORAGE_RGN_OSC2:
    case STORAGE_RGN_OSC3:
        break;
    }
    return 0;
}

STORAGE_METHOD_READ_IMPL(M_storage, storage, unsigned int rgn, size_t offset, void* data, size_t size, future_t* future)
{
    if(storage->m_q_count == STORAGE_QUEUE_LEN) return E_BUSY;

    if(size == 0) return E_INVALID_VALUE;
    size_t rgn_size = storage_region_size(rgn);

    if(rgn_size == 0) return E_INVALID_VALUE;
    if(offset + size > rgn_size) return E_OUT_OF_RANGE;

    size_t rgn_address = storage_region_address(rgn);

    storage_cmd_t* cmd = &storage->m_queue[storage->m_q_head_index];

    cmd->type = STORAGE_CMD_READ;
    cmd->address = rgn_address + offset;
    //cmd->offset = offset;
    cmd->data = (void*)data;
    cmd->size = size;
    cmd->future = future;

    future_init(&storage->m_future);

    storage->m_q_head_index = storage_inc_queue_index(storage->m_q_head_index);
    storage_inc_queue_count(storage);

    storage_cmd_future_start(cmd);

    return E_IN_PROGRESS;
}

STORAGE_METHOD_WRITE_IMPL(M_storage, storage, unsigned int rgn, size_t offset, const void* data, size_t size, future_t* future)
{
    if(storage->m_q_count == STORAGE_QUEUE_LEN) return E_BUSY;

    if(size == 0) return E_INVALID_VALUE;
    size_t rgn_size = storage_region_size(rgn);

    if(rgn_size == 0) return E_INVALID_VALUE;
    if(offset + size > rgn_size) return E_OUT_OF_RANGE;

    size_t rgn_address = storage_region_address(rgn);

    storage_cmd_t* cmd = &storage->m_queue[storage->m_q_head_index];

    cmd->type = STORAGE_CMD_WRITE;
    cmd->address = rgn_address + offset;
    //cmd->offset = offset;
    cmd->data = (void*)data;
    cmd->size = size;
    cmd->future = future;

    future_init(&storage->m_future);

    storage->m_q_head_index = storage_inc_queue_index(storage->m_q_head_index);
    storage_inc_queue_count(storage);

    storage_cmd_future_start(cmd);

    return E_IN_PROGRESS;
}

STORAGE_METHOD_ERASE_IMPL(M_storage, storage, unsigned int rgn, future_t* future)
{
    if(storage->m_q_count == STORAGE_QUEUE_LEN) return E_BUSY;

    size_t rgn_size = storage_region_size(rgn);

    if(rgn_size == 0) return E_INVALID_VALUE;

    size_t rgn_address = storage_region_address(rgn);

    storage_cmd_t* cmd = &storage->m_queue[storage->m_q_head_index];

    cmd->type = STORAGE_CMD_ERASE;
    cmd->address = rgn_address;
    //cmd->offset = 0;
    cmd->data = NULL;
    cmd->size = rgn_size;
    cmd->future = future;

    future_init(&storage->m_future);

    storage->m_q_head_index = storage_inc_queue_index(storage->m_q_head_index);
    storage_inc_queue_count(storage);

    storage_cmd_future_start(cmd);

    return E_IN_PROGRESS;
}

