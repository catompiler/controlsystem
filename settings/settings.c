#include "settings.h"
#include "reg/regs.h"
#include "modules/modules.h"
#include "crc/crc16_ccitt.h"
#include <string.h>



//! Максимальный размер данных регистра.
#define SETTINGS_REG_DATA_SIZE_MAX 4

//! Окончание списка.
//! Идентификатор.
#define SETTINGS_END_ID ((uint32_t)-1)
//! Тип данных.
#define SETTINGS_END_TYPE ((uint8_t)-1)
//! Размер данных.
#define SETTINGS_END_DATA_SIZE ((uint8_t)-1)



METHOD_INIT_IMPL(M_settings, settings)
{
}

METHOD_DEINIT_IMPL(M_settings, settings)
{
}

METHOD_CONTROL_IMPL(M_settings, settings)
{
    if(settings->status & STATUS_RUN) return;

    if(settings->control & (SETTINGS_CONTROL_LOAD | SETTINGS_CONTROL_STORE)){
        future_init(&settings->m_future);
    }
}

static size_t settings_buf_put(M_settings* settings, size_t index, const void* data, size_t size)
{
    uint8_t* data_bytes = (uint8_t*)data;

    size_t i = 0;
    for(; i < size; i ++){
        if(index >= (SETTINGS_BUF_SIZE)) break;
        if(data_bytes) settings->m_buf[index] = data_bytes[i];
        index ++;
    }
    return i;
}

static size_t settings_buf_get(M_settings* settings, size_t index, void* data, size_t size)
{
    uint8_t* data_bytes = (uint8_t*)data;

    size_t i;
    for(i = 0; i < size; i ++){
        if(index >= (SETTINGS_BUF_SIZE)) break;
        if(data_bytes) data_bytes[i] = settings->m_buf[index];
        index ++;
    }
    return i;
}

static int settings_put_reg_atomic(M_settings* settings, reg_t* reg)
{
    size_t id_putted = 0;
    size_t type_putted = 0;
    size_t size_putted = 0;
    size_t data_putted = 0;

    void* data = reg->data;
    if(data == NULL) return 0;

    size_t data_size = reg_data_size(reg);
    if(data_size == 0) return 0;

    uint8_t type = (uint8_t)reg->type;
    uint8_t size = (uint8_t)data_size;
    uint32_t id = (uint32_t)reg->id;

    size_t index = settings->m_index;

    if(index + sizeof(id) > (SETTINGS_BUF_HEADER_SIZE + SETTINGS_BUF_DATA_SIZE)) return -1;
    id_putted = settings_buf_put(settings, index, &id, sizeof(id));
    if(id_putted != sizeof(id)) return -1;

    index += id_putted;

    if(index + sizeof(type) > (SETTINGS_BUF_HEADER_SIZE + SETTINGS_BUF_DATA_SIZE)) return -1;
    type_putted = settings_buf_put(settings, index, &type, sizeof(type));
    if(type_putted != sizeof(type)) return -1;

    index += type_putted;

    if(index + sizeof(size) > (SETTINGS_BUF_HEADER_SIZE + SETTINGS_BUF_DATA_SIZE)) return -1;
    size_putted = settings_buf_put(settings, index, &size, sizeof(size));
    if(size_putted != sizeof(size)) return -1;

    index += size_putted;

    if(index + data_size > (SETTINGS_BUF_HEADER_SIZE + SETTINGS_BUF_DATA_SIZE)) return -1;
    data_putted = settings_buf_put(settings, index, data, data_size);
    if(data_putted != data_size) return -1;

    index += data_putted;

    settings->m_index = index;

    return (int)(sizeof(id) + sizeof(type) + sizeof(size) + data_size);
}

static int settings_get_reg_atomic(M_settings* settings, reg_id_t* p_id, reg_type_t* p_type, size_t* p_size, void* p_data, size_t data_size_max)
{
    size_t id_getted = 0;
    size_t type_getted = 0;
    size_t size_getted = 0;
    size_t data_getted = 0;
    size_t data_size = 0;

    uint32_t id;
    uint8_t type;
    uint8_t size;

    size_t index = settings->m_index;

    if(index + sizeof(id) > (SETTINGS_BUF_HEADER_SIZE + SETTINGS_BUF_DATA_SIZE)) return -1;
    id_getted = settings_buf_get(settings, index, &id, sizeof(id));
    if(id_getted != sizeof(id)) return -1;

    index += id_getted;

    if(index + sizeof(type) > (SETTINGS_BUF_HEADER_SIZE + SETTINGS_BUF_DATA_SIZE)) return -1;
    type_getted = settings_buf_get(settings, index, &type, sizeof(type));
    if(type_getted != sizeof(type)) return -1;

    index += type_getted;

    if(index + sizeof(size) > (SETTINGS_BUF_HEADER_SIZE + SETTINGS_BUF_DATA_SIZE)) return -1;
    size_getted = settings_buf_get(settings, index, &size, sizeof(size));
    if(size_getted != sizeof(size)) return -1;

    index += size_getted;

    if(id != SETTINGS_END_ID || type != SETTINGS_END_TYPE || size != SETTINGS_END_DATA_SIZE){

        data_size = (size_t)size;

        if(index + data_size > (SETTINGS_BUF_HEADER_SIZE + SETTINGS_BUF_DATA_SIZE)) return -1;

        if(data_size <= data_size_max){
            data_getted = settings_buf_get(settings, index, p_data, data_size);
            if(data_getted != data_size) return -1;
        }

        index += data_size;

        if(p_size) *p_size = data_getted;
    }else{
        if(p_size) *p_size = (size_t)size;
    }

    if(p_type) *p_type = (reg_type_t)type;
    if(p_id) *p_id = id;

    settings->m_index = index;

    return (int)(sizeof(id) + sizeof(type) + sizeof(size) + data_size);
}

static int settings_put_end_atomic(M_settings* settings)
{
    uint32_t end_id = SETTINGS_END_ID;
    uint8_t end_type = SETTINGS_END_TYPE;
    uint8_t end_data_size = SETTINGS_END_DATA_SIZE;

    int putted;

    size_t index = settings->m_index;

    if(index + sizeof(end_id) > (SETTINGS_BUF_HEADER_SIZE + SETTINGS_BUF_DATA_SIZE)) return -1;
    putted = settings_buf_put(settings, index, &end_id, sizeof(end_id));
    if(putted != sizeof(end_id)) return -1;

    index += putted;

    if(index + sizeof(end_type) > (SETTINGS_BUF_HEADER_SIZE + SETTINGS_BUF_DATA_SIZE)) return -1;
    putted = settings_buf_put(settings, index, &end_type, sizeof(end_type));
    if(putted != sizeof(end_type)) return -1;

    index += putted;

    if(index + sizeof(end_data_size) > (SETTINGS_BUF_HEADER_SIZE + SETTINGS_BUF_DATA_SIZE)) return -1;
    putted = settings_buf_put(settings, index, &end_data_size, sizeof(end_data_size));
    if(putted != sizeof(end_data_size)) return -1;

    index += putted;

    settings->m_index = index;

    return (int)(sizeof(end_id) + sizeof(end_type) + sizeof(end_data_size));
}

static void settings_process_store(M_settings* settings)
{
    if(future_running(&settings->m_future)) return;

    err_t err = E_NO_ERROR;

    // Если операция завершена.
    if(future_done(&settings->m_future)){
        // Проверим успех операции.
        if(FUTURE_RESULT_ERR(future_result(&settings->m_future)) != E_NO_ERROR){
            settings->control &= ~SETTINGS_CONTROL_STORE;
            settings->errors = SETTINGS_ERROR_STORE;
            settings->status = STATUS_ERROR;
            return;
        }

        //! Если индекс регистра равен нулю - то завершено только стирание.
        //if(settings->m_reg_n == 0){
            //
        //}
    }
    // Если операция ещё не запускалась.
    else{
        // Запустим стирание.
        err = STORAGE_ERASE(storage, STORAGE_RGN_SETTINGS, &settings->m_future);
        if((err != E_NO_ERROR) && (err != E_IN_PROGRESS)){
            settings->control &= ~SETTINGS_CONTROL_STORE;
            settings->errors = SETTINGS_ERROR_STORE;
            settings->status = STATUS_ERROR;
            return;
        }

        settings->errors &= ~SETTINGS_ERROR_STORE;
        settings->status = STATUS_RUN;
        settings->m_index = 0;
        settings->m_reg_n = 0;
        settings->m_offset = 0;

        if(err == E_IN_PROGRESS) return;
    }

    do{
        memset(&settings->m_buf[0], 0xff, SETTINGS_BUF_SIZE);

        uint16_t putted = 0;

        settings->m_index = SETTINGS_BUF_HEADER_SIZE;

        for(; settings->m_reg_n < regs_count();){
            reg_t* reg = regs_reg(settings->m_reg_n);

            if(reg == NULL) break;

            if(reg_flags(reg) & REG_FLAG_CONF){

                int reg_putted = settings_put_reg_atomic(settings, reg);
                if(reg_putted < 0) break;

                putted += (uint16_t)reg_putted;
            }

            settings->m_reg_n ++;
        }

        //printf("%u of %u\n", settings->m_reg_n, regs_count());

        if(settings->m_reg_n == regs_count()){
            int end_putted = settings_put_end_atomic(settings);

            if(end_putted > 0){
                settings->m_reg_n = regs_count() + 1;
                putted += end_putted;
            }
        }

        // Больше нечего записывать.
        if(putted == 0){
            settings->control &= ~SETTINGS_CONTROL_STORE;
            settings->errors = SETTINGS_ERROR_NONE;
            settings->status = STATUS_READY;
            break;
        }else{
            uint16_t crc = crc16_ccitt_ansi(&settings->m_buf[SETTINGS_BUF_HEADER_SIZE], putted);

            if((settings_buf_put(settings, 0, &putted, sizeof(putted)) != sizeof(putted)) ||
               (settings_buf_put(settings, settings->m_index, &crc, sizeof(crc)) != sizeof(crc))){
                settings->control &= ~SETTINGS_CONTROL_STORE;
                settings->errors = SETTINGS_ERROR_STORE;
                settings->status = STATUS_ERROR;
                break;
            }

            err = STORAGE_WRITE(storage, STORAGE_RGN_SETTINGS, settings->m_offset, settings->m_buf, putted + SETTINGS_BUF_HEADER_SIZE + SETTINGS_BUF_CHECK_SIZE, &settings->m_future);
            if((err != E_NO_ERROR) && (err != E_IN_PROGRESS)){
                settings->control &= ~SETTINGS_CONTROL_STORE;
                settings->errors = SETTINGS_ERROR_STORE;
                settings->status = STATUS_ERROR;
                break;
            }

            settings->m_offset += SETTINGS_BUF_SIZE;
        }
    }while(err == E_NO_ERROR);
}

static void settings_process_load(M_settings* settings)
{
    if(future_running(&settings->m_future)) return;

    err_t err = E_NO_ERROR;

    // Если операция завершена.
    if(future_done(&settings->m_future)){
        // Проверим успех операции.
        if(FUTURE_RESULT_ERR(future_result(&settings->m_future)) != E_NO_ERROR){
            settings->control &= ~SETTINGS_CONTROL_LOAD;
            settings->errors = SETTINGS_ERROR_LOAD;
            settings->status = STATUS_ERROR;
            return;
        }

        //! Если индекс регистра равен нулю - то завершено только стирание.
        //if(settings->m_reg_n == 0){
            //
        //}
    }
    // Если операция ещё не запускалась.
    else{
        settings->errors &= ~SETTINGS_ERROR_LOAD;
        settings->status = STATUS_RUN;
        settings->m_index = 0;
        settings->m_reg_n = 0;
        settings->m_offset = 0;

        // Запустим чтение.
        err = STORAGE_READ(storage, STORAGE_RGN_SETTINGS, settings->m_offset, settings->m_buf, SETTINGS_BUF_SIZE, &settings->m_future);
        if((err != E_NO_ERROR) && (err != E_IN_PROGRESS)){
            settings->control &= ~SETTINGS_CONTROL_LOAD;
            settings->errors = SETTINGS_ERROR_LOAD;
            settings->status = STATUS_ERROR;
            return;
        }

        if(err == E_IN_PROGRESS) return;
    }

    do{
        uint16_t getted = 0;
        settings->m_index = SETTINGS_BUF_HEADER_SIZE;

        reg_id_t id;
        reg_type_t type;
        size_t data_size;
        uint8_t data[SETTINGS_REG_DATA_SIZE_MAX];

        uint16_t size_bytes;

        if(settings_buf_get(settings, 0, &size_bytes, sizeof(size_bytes)) != sizeof(size_bytes)){
            settings->control &= ~SETTINGS_CONTROL_LOAD;
            settings->errors = SETTINGS_ERROR_LOAD;
            settings->status = STATUS_ERROR;
            return;
        }

        // Invalid size.
        if(size_bytes > SETTINGS_BUF_DATA_SIZE){
            settings->control &= ~SETTINGS_CONTROL_LOAD;
            settings->errors = SETTINGS_ERROR_LOAD;
            settings->status = STATUS_ERROR;
            return;
        }

        uint16_t act_crc = *((uint16_t*)&settings->m_buf[SETTINGS_BUF_HEADER_SIZE + size_bytes]);
        uint16_t crc = crc16_ccitt_ansi(&settings->m_buf[SETTINGS_BUF_HEADER_SIZE], size_bytes);
        if(crc != act_crc){
            settings->control &= ~SETTINGS_CONTROL_LOAD;
            settings->errors = SETTINGS_ERROR_LOAD;
            settings->status = STATUS_ERROR;
            return;
        }

        for(; getted < size_bytes; ){

            int reg_getted = settings_get_reg_atomic(settings, &id, &type, &data_size, data, SETTINGS_REG_DATA_SIZE_MAX);
            if(reg_getted < 0) break;

            getted += (uint16_t)reg_getted;

            // Маркер конца списка.
            if(id == SETTINGS_END_ID && type == SETTINGS_END_TYPE && data_size == SETTINGS_END_DATA_SIZE){
                // Больше нечего читать.
                settings->control &= ~SETTINGS_CONTROL_LOAD;
                settings->errors = SETTINGS_ERROR_NONE;
                settings->status = STATUS_VALID;
                return;
            }

            reg_t* reg = regs_find(id);
            if(reg == NULL) continue;

            void* data_ptr = reg_data(reg);
            if(data_ptr == NULL) continue;

            if(type != reg_type(reg)) continue;

            size_t act_data_size = reg_data_size(reg);
            if(act_data_size != data_size) continue;

            memcpy(data_ptr, data, data_size);
        }

        // Всё прочитано без ошибок.
        if(getted == size_bytes){
            settings->m_offset += SETTINGS_BUF_SIZE;

            // Запустим чтение.
            err = STORAGE_READ(storage, STORAGE_RGN_SETTINGS, settings->m_offset, settings->m_buf, SETTINGS_BUF_SIZE, &settings->m_future);
            if((err != E_NO_ERROR) && (err != E_IN_PROGRESS)){
                settings->control &= ~SETTINGS_CONTROL_LOAD;
                settings->errors = SETTINGS_ERROR_LOAD;
                settings->status = STATUS_ERROR;
                return;
            }
        }else{
            settings->control &= ~SETTINGS_CONTROL_LOAD;
            settings->errors = SETTINGS_ERROR_LOAD;
            settings->status = STATUS_ERROR;
            return;
        }
    }while(err == E_NO_ERROR);
}

METHOD_IDLE_IMPL(M_settings, settings)
{
    if(settings->control & SETTINGS_CONTROL_STORE){
        settings_process_store(settings);
    }
    else if(settings->control & SETTINGS_CONTROL_LOAD){
        settings_process_load(settings);
    }
}
