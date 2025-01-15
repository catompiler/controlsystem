#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "eeprom/eeprom_xmc4xxx.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "defs/defs.h"



static err_t eeprom_create(eeprom_t* eeprom)
{
    return E_INVALID_OPERATION;
}


static err_t eeprom_open(eeprom_t* eeprom)
{
    return E_NO_ERROR;
}

static err_t eeprom_erase_block(eeprom_t* eeprom, size_t address)
{
    if(eeprom->m95x == NULL) return E_STATE;

    size_t erase_address = address & ~(EEPROM_ERASE_SIZE - 1);
    if((erase_address + EEPROM_ERASE_SIZE) > eeprom->size) return E_OUT_OF_RANGE;

    memset(eeprom->page_buf, 0xff, EEPROM_ERASE_SIZE);

    err_t err = m95x_write_enable(eeprom->m95x);
    if(err != E_NO_ERROR) return err;

    err = m95x_write(eeprom->m95x, (m95x_address_t)erase_address, eeprom->page_buf, EEPROM_ERASE_SIZE);
    if(err != E_NO_ERROR) return err;

    return E_IN_PROGRESS;
}

err_t eeprom_write_page(eeprom_t* eeprom, size_t address, const void* cur_data_ptr, size_t cur_data_size)
{
    if(eeprom->m95x == NULL) return E_STATE;

    size_t page_address = address & ~(EEPROM_PAGE_SIZE - 1);
    if((page_address + EEPROM_PAGE_SIZE) > eeprom->size) return E_OUT_OF_RANGE;

    size_t in_page_address = address - page_address;
    if((in_page_address + cur_data_size) > EEPROM_PAGE_SIZE) return E_OUT_OF_RANGE;

    //memset(eeprom->page_buf, 0xff, EEPROM_PAGE_SIZE);
    //memcpy(&eeprom->page_buf[in_page_address], cur_data_ptr, cur_data_size);
    memcpy(eeprom->page_buf, cur_data_ptr, cur_data_size);

    err_t err = m95x_write_enable(eeprom->m95x);
    if(err != E_NO_ERROR) return err;

    err = m95x_write(eeprom->m95x, (m95x_address_t)address, eeprom->page_buf, cur_data_size);
    if(err != E_NO_ERROR) return err;

    return E_IN_PROGRESS;
}

err_t eeprom_read_page(eeprom_t* eeprom, size_t address, void* cur_data_ptr, size_t cur_data_size)
{
    if(eeprom->m95x == NULL) return E_STATE;

    size_t page_address = address & ~(EEPROM_PAGE_SIZE - 1);
    if((page_address + EEPROM_PAGE_SIZE) > eeprom->size) return E_OUT_OF_RANGE;

    size_t in_page_address = address - page_address;
    if((in_page_address + cur_data_size) > EEPROM_PAGE_SIZE) return E_OUT_OF_RANGE;

    err_t err = m95x_read(eeprom->m95x, (m95x_address_t)address, eeprom->page_buf, cur_data_size);
    if(err != E_NO_ERROR) return err;

    return E_IN_PROGRESS;
}

static err_t eeprom_cur_op_state(eeprom_t* eeprom)
{
    if(m95x_done(eeprom->m95x)) return m95x_error(eeprom->m95x);
    return E_IN_PROGRESS;
}

static void eeprom_close(eeprom_t* eeprom)
{
}



err_t eeprom_init(eeprom_t* eeprom, m95x_t* m95x, size_t size)
{
    assert(eeprom != NULL);

    //if(m95x == NULL) return E_NULL_POINTER;
    if(size == 0) return E_INVALID_VALUE;

    eeprom->m95x = m95x;
    eeprom->size = size;
    eeprom->state = EEPROM_STATE_NONE;
    eeprom->address = 0;
    eeprom->data_ptr = NULL;
    eeprom->data_size = 0;
    eeprom->data_processed = 0;
    eeprom->future = NULL;

    err_t err = E_NO_ERROR;

    err = eeprom_open(eeprom);
    if(err != E_NO_ERROR) return err;

    eeprom_close(eeprom);

    return E_NO_ERROR;
}

void eeprom_deinit(eeprom_t* eeprom)
{
    assert(eeprom != NULL);

    eeprom_close(eeprom);

    eeprom->m95x = NULL;
    eeprom->size = 0;
    eeprom->state = EEPROM_STATE_NONE;
}



//ALWAYS_INLINE static void eeprom_future_init(eeprom_t* eeprom)
//{
//    if(eeprom->future) future_init(eeprom->future);
//}

ALWAYS_INLINE static void eeprom_future_start(eeprom_t* eeprom)
{
    if(eeprom->future) future_start(eeprom->future);
}

ALWAYS_INLINE static void eeprom_future_finish(eeprom_t* eeprom, err_t err)
{
    if(eeprom->future) future_finish(eeprom->future, FUTURE_RESULT(err));
}

static err_t eeprom_process_erase(eeprom_t* eeprom)
{
    if(eeprom->state == EEPROM_STATE_DONE){
        eeprom->op = EEPROM_OP_NONE;
        return E_STATE;
    }

    size_t cur_address = eeprom->address + eeprom->data_processed;
    size_t cur_data_remain = eeprom->data_size - eeprom->data_processed;

    size_t cur_data_erase_size = cur_data_remain;
    if(cur_data_erase_size > EEPROM_ERASE_SIZE) cur_data_erase_size = EEPROM_ERASE_SIZE;

    if(eeprom->state == EEPROM_STATE_NONE){
        eeprom->state = EEPROM_STATE_ERASE;
        eeprom_future_start(eeprom);
    }

    err_t err = E_NO_ERROR;

    switch(eeprom->state){
    default:
        break;
    case EEPROM_STATE_ERASE:{
        err = eeprom_open(eeprom);
        if(err != E_NO_ERROR) break;

        err = eeprom_erase_block(eeprom, cur_address);
        if(err == E_IN_PROGRESS) eeprom->state = EEPROM_STATE_WAIT_ERASE;
        if(err != E_NO_ERROR) break;

        eeprom->data_processed += cur_data_erase_size;
        if(eeprom->data_processed == eeprom->data_size){
            eeprom->state = EEPROM_STATE_DONE;
            err = E_NO_ERROR;
        }else{
            err = E_IN_PROGRESS;
        }
    }break;
    case EEPROM_STATE_WAIT_ERASE:
        err = eeprom_cur_op_state(eeprom);
        if(err != E_NO_ERROR) break;

        eeprom->data_processed += cur_data_erase_size;
        if(eeprom->data_processed == eeprom->data_size){
            eeprom->state = EEPROM_STATE_DONE;
        }else{
            eeprom->state = EEPROM_STATE_ERASE;
        }
        err = E_IN_PROGRESS;
        break;
    case EEPROM_STATE_DONE:
        break;
    }

    eeprom_close(eeprom);

    if(((err != E_NO_ERROR) && (err != E_IN_PROGRESS)) || (eeprom->state == EEPROM_STATE_DONE)){
        eeprom->state = EEPROM_STATE_DONE;
        eeprom->op = EEPROM_OP_NONE;
        eeprom_future_finish(eeprom, err);
    }

    return err;
}

/*static err_t eeprom_process_modify(eeprom_t* eeprom)
{
}*/

static err_t eeprom_process_write(eeprom_t* eeprom)
{
    if(eeprom->state == EEPROM_STATE_DONE){
        eeprom->op = EEPROM_OP_NONE;
        return E_STATE;
    }
    //if(eeprom->flags & EEPROM_FLAG_MODIFY) return eeprom_process_modify(eeprom);

    size_t cur_address = eeprom->address + eeprom->data_processed;
    size_t cur_data_remain = eeprom->data_size - eeprom->data_processed;

    size_t cur_data_write_size = cur_data_remain;
    if(cur_data_write_size > EEPROM_PAGE_SIZE) cur_data_write_size = EEPROM_PAGE_SIZE;

    size_t cur_data_erase_size = cur_data_remain;
    if(cur_data_erase_size > EEPROM_ERASE_SIZE) cur_data_erase_size = EEPROM_ERASE_SIZE;

    if(eeprom->state == EEPROM_STATE_NONE){
        if(eeprom->flags & EEPROM_FLAG_ERASE){
            eeprom->state = EEPROM_STATE_ERASE;
        }else{
            eeprom->state = EEPROM_STATE_WRITE;
        }
        eeprom_future_start(eeprom);
    }

    err_t err = E_NO_ERROR;

    switch(eeprom->state){
    default:
        break;
    case EEPROM_STATE_WRITE:{
        void* cur_data_ptr = (void*)((uint8_t*)eeprom->data_ptr + eeprom->data_processed);

        err = eeprom_open(eeprom);
        if(err != E_NO_ERROR) break;

        err = eeprom_write_page(eeprom, cur_address, cur_data_ptr, cur_data_write_size);
        if(err == E_IN_PROGRESS) eeprom->state = EEPROM_STATE_WAIT_WRITE;
        if(err != E_NO_ERROR) break;

        eeprom->data_processed += cur_data_write_size;
        if(eeprom->data_processed == eeprom->data_size){
            eeprom->state = EEPROM_STATE_DONE;
            err = E_NO_ERROR;
        }else{
            err = E_IN_PROGRESS;
        }
    }break;
    case EEPROM_STATE_WAIT_WRITE:
        err = eeprom_cur_op_state(eeprom);
        if(err != E_NO_ERROR) break;

        eeprom->data_processed += cur_data_write_size;
        if(eeprom->data_processed == eeprom->data_size){
            eeprom->state = EEPROM_STATE_DONE;
            err = E_NO_ERROR;
        }else{
            eeprom->state = EEPROM_STATE_WRITE;
            err = E_IN_PROGRESS;
        }
        break;
    case EEPROM_STATE_ERASE:{
        err = eeprom_open(eeprom);
        if(err != E_NO_ERROR) break;

        err = eeprom_erase_block(eeprom, cur_address);
        if(err == E_IN_PROGRESS) eeprom->state = EEPROM_STATE_WAIT_ERASE;
        if(err != E_NO_ERROR) break;

        eeprom->data_processed += cur_data_erase_size;
        if(eeprom->data_processed == eeprom->data_size){
            eeprom->data_processed = 0;
            eeprom->state = EEPROM_STATE_WRITE;
            err = E_IN_PROGRESS;
        }
    }break;
    case EEPROM_STATE_WAIT_ERASE:
        err = eeprom_cur_op_state(eeprom);
        if(err != E_NO_ERROR) break;

        eeprom->data_processed += cur_data_erase_size;
        if(eeprom->data_processed == eeprom->data_size){
            eeprom->data_processed = 0;
            eeprom->state = EEPROM_STATE_WRITE;
        }else{
            eeprom->state = EEPROM_STATE_ERASE;
        }
        err = E_IN_PROGRESS;
        break;
    case EEPROM_STATE_DONE:
        break;
    }

    eeprom_close(eeprom);

    if(((err != E_NO_ERROR) && (err != E_IN_PROGRESS)) || (eeprom->state == EEPROM_STATE_DONE)){
        eeprom->state = EEPROM_STATE_DONE;
        eeprom->op = EEPROM_OP_NONE;
        eeprom_future_finish(eeprom, err);
    }

    return err;
}

static err_t eeprom_process_read(eeprom_t* eeprom)
{
    if(eeprom->state == EEPROM_STATE_DONE){
        eeprom->op = EEPROM_OP_NONE;
        return E_STATE;
    }

    size_t cur_address = eeprom->address + eeprom->data_processed;
    size_t cur_data_remain = eeprom->data_size - eeprom->data_processed;

    size_t cur_data_read_size = cur_data_remain;
    if(cur_data_read_size > EEPROM_PAGE_SIZE) cur_data_read_size = EEPROM_PAGE_SIZE;

    void* cur_data_ptr = (void*)((uint8_t*)eeprom->data_ptr + eeprom->data_processed);

    if(eeprom->state == EEPROM_STATE_NONE){
        eeprom->state = EEPROM_STATE_READ;
        eeprom_future_start(eeprom);
    }

    err_t err = E_NO_ERROR;

    switch(eeprom->state){
    default:
        break;
    case EEPROM_STATE_READ:{
        err = eeprom_open(eeprom);
        if(err != E_NO_ERROR) break;

        err = eeprom_read_page(eeprom, cur_address, cur_data_ptr, cur_data_read_size);
        if(err == E_IN_PROGRESS) eeprom->state = EEPROM_STATE_WAIT_READ;
        if(err != E_NO_ERROR) break;

        eeprom->data_processed += cur_data_read_size;
        if(eeprom->data_processed == eeprom->data_size){
            eeprom->state = EEPROM_STATE_DONE;
            err = E_NO_ERROR;
        }else{
            err = E_IN_PROGRESS;
        }
    }break;
    case EEPROM_STATE_WAIT_READ:
        err = eeprom_cur_op_state(eeprom);
        if(err != E_NO_ERROR) break;

        memcpy(cur_data_ptr, eeprom->page_buf, cur_data_read_size);

        eeprom->data_processed += cur_data_read_size;
        if(eeprom->data_processed == eeprom->data_size){
            eeprom->state = EEPROM_STATE_DONE;
            err = E_NO_ERROR;
        }else{
            eeprom->state = EEPROM_STATE_READ;
            err = E_IN_PROGRESS;
        }
        break;
    case EEPROM_STATE_DONE:
        break;
    }

    eeprom_close(eeprom);

    if(((err != E_NO_ERROR) && (err != E_IN_PROGRESS)) || (eeprom->state == EEPROM_STATE_DONE)){
        eeprom->state = EEPROM_STATE_DONE;
        eeprom->op = EEPROM_OP_NONE;
        eeprom_future_finish(eeprom, err);
    }

    return err;
}


err_t eeprom_erase(eeprom_t* eeprom, size_t address, size_t size, future_t* future, eeprom_flags_t flags)
{
    assert(eeprom != NULL);

    if(eeprom->m95x == NULL || eeprom->size == 0) return E_STATE;
    if(size == 0) return E_INVALID_VALUE;
    if(eeprom_busy(eeprom)) return E_BUSY;

    eeprom->state = EEPROM_STATE_NONE;
    eeprom->address = address;
    eeprom->data_ptr = NULL;
    eeprom->data_size = size;
    eeprom->flags = flags;
    eeprom->future = future;

    eeprom->op = EEPROM_OP_ERASE;
    eeprom->data_processed = 0;

    //eeprom_future_init(eeprom);

    return eeprom_process_erase(eeprom);
}


err_t eeprom_write(eeprom_t* eeprom, size_t address, const void* data, size_t size, future_t* future, eeprom_flags_t flags)
{
    assert(eeprom != NULL);

    if(eeprom->m95x == NULL || eeprom->size == 0) return E_STATE;
    if(data == NULL) return E_NULL_POINTER;
    if(size == 0) return E_INVALID_VALUE;
    if(eeprom_busy(eeprom)) return E_BUSY;

    eeprom->state = EEPROM_STATE_NONE;
    eeprom->address = address;
    eeprom->data_ptr = (void*)data;
    eeprom->data_size = size;
    eeprom->flags = flags;
    eeprom->future = future;

    eeprom->op = EEPROM_OP_WRITE;
    eeprom->data_processed = 0;

    //eeprom_future_init(eeprom);

    return eeprom_process_write(eeprom);
}

err_t eeprom_read(eeprom_t* eeprom, size_t address, void* data, size_t size, future_t* future, eeprom_flags_t flags)
{
    assert(eeprom != NULL);

    if(eeprom->m95x == NULL || eeprom->size == 0) return E_STATE;
    if(data == NULL) return E_NULL_POINTER;
    if(size == 0) return E_INVALID_VALUE;
    if(eeprom_busy(eeprom)) return E_BUSY;

    eeprom->state = EEPROM_STATE_NONE;
    eeprom->address = address;
    eeprom->data_ptr = (void*)data;
    eeprom->data_size = size;
    eeprom->flags = flags;
    eeprom->future = future;

    eeprom->op = EEPROM_OP_READ;
    eeprom->data_processed = 0;

    //eeprom_future_init(eeprom);

    return eeprom_process_read(eeprom);
}

void eeprom_process(eeprom_t* eeprom)
{
    assert(eeprom != NULL);

    if(eeprom->m95x == NULL || eeprom->size == 0) return;

    switch(eeprom->op){
    case EEPROM_OP_NONE:
        break;
    case EEPROM_OP_ERASE:
        eeprom_process_erase(eeprom);
        break;
    case EEPROM_OP_WRITE:
        eeprom_process_write(eeprom);
        break;
    case EEPROM_OP_READ:
        eeprom_process_read(eeprom);
        break;
    }
}

bool eeprom_busy(eeprom_t* eeprom)
{
    assert(eeprom != NULL);

    if(eeprom->m95x == NULL || eeprom->size == 0) return false;

    return eeprom->state != EEPROM_STATE_NONE && eeprom->state != EEPROM_STATE_DONE;
}

#endif
