#include "oscope.h"
#include "reg/regs.h"
#include "utils/utils.h"



static status_t recalc_values(M_oscope* scp)
{
    status_t res_status = STATUS_READY;

    oscope_ch_param_t* ch_par;
    oscope_ch_private_t* ch_prv;
    reg_t* reg;

    int i;
    for(i = 0; i < OSCOPE_CHANNELS; i ++){
        ch_par = &scp->r_ch[i];
        ch_prv = &scp->m_ch[i];

        if(ch_par->enabled && (reg = regs_find(ch_par->reg_id))){
            ch_prv->reg = reg;
            ch_prv->base_reg = regs_find(reg->base_id);
        }else{
            ch_prv->reg = NULL;
        }
    }

    return res_status;
}


METHOD_INIT_IMPL(M_oscope, scp)
{
    IDLE((*scp));
}

METHOD_DEINIT_IMPL(M_oscope, scp)
{
}

METHOD_CONTROL_IMPL(M_oscope, scp)
{
    if(scp->control & CONTROL_RESET){
        scp->r_start = 0;
        scp->r_index = 0;
        scp->r_count = 0;
        scp->m_trig_state_z1 = OSCOPE_TRIG_STATE_NONE;
        scp->m_triggered = false;
        scp->m_psc_cnt = 0;

        scp->status = STATUS_NONE;
        scp->control &= ~CONTROL_RESET;
    }

    if(!(scp->control & CONTROL_ENABLE)) return;

    if(scp->control & CONTROL_START){
        scp->r_start = 0;
        scp->r_index = 0;
        scp->r_count = 0;
        scp->m_trig_state_z1 = OSCOPE_TRIG_STATE_NONE;
        scp->m_triggered = false;
        scp->m_psc_cnt = 0;

        scp->status = (scp->status & STATUS_READY) | STATUS_RUN;
        scp->control &= ~CONTROL_START;
    }
}

static oscope_trig_state_t oscope_check_trig(M_oscope* scp, oscope_trig_t* trig, oscope_sample_t val)
{
    switch(trig->type){
    default:
        break;
    case OSCOPE_TRIG_RISING:
        return val > trig->value;
    case OSCOPE_TRIG_FALLING:
        return val < trig->value;
    }

    return OSCOPE_TRIG_STATE_NONE;
}

static void oscope_process_trig(M_oscope* scp)
{
    oscope_trig_t* trig = &scp->r_trig;

    if(!trig->enabled){
        return;
    }

    if(scp->m_triggered){
        return;
    }

    // Ограничим количество семплов до срабатывания триггера числом семплов истории.
    size_t hist_samples = CLAMP(scp->r_hist_samples, 0, OSCOPE_SAMPLES);
    size_t hist_count = CLAMP(scp->r_count, 0, hist_samples);
    size_t start_index = CLAMP(scp->r_index, 0, OSCOPE_SAMPLES);
    scp->r_hist_samples = hist_samples;
    scp->r_count = hist_count;
    scp->r_start = start_index;

    size_t i;

    oscope_ch_param_t* ch_par;
    oscope_ch_private_t* ch_prv;
    oscope_sample_t val;

    oscope_trig_state_t trig_state = OSCOPE_TRIG_STATE_NONE;

    for(i = 0; i < OSCOPE_CHANNELS; i ++){
        ch_par = &scp->r_ch[i];
        ch_prv = &scp->m_ch[i];

        if(ch_par->enabled && ch_prv->reg != NULL && reg_data(ch_prv->reg) != NULL){
            val = (oscope_sample_t)reg_valuel(ch_prv->reg);
        }else{
            val = 0;
        }

        if(trig->ch_n == i){
            trig_state = oscope_check_trig(scp, trig, val);
            break;
        }
    }

    scp->m_triggered = (scp->m_trig_state_z1 == OSCOPE_TRIG_STATE_NOT_ACTIVE) &&
                       (trig_state == OSCOPE_TRIG_STATE_ACTIVE);

    scp->m_trig_state_z1 = trig_state;
}

METHOD_CALC_IMPL(M_oscope, scp)
{
    CONTROL((*scp));

    if(!(scp->control & CONTROL_ENABLE)) return;

    if(!(scp->status & STATUS_RUN)) return;

    // Обработка триггера.
    oscope_process_trig(scp);

    // Обработка предделителя.
    if(scp->m_psc_cnt < scp->r_prescaler){
        scp->m_psc_cnt ++;
        return;
    }
    scp->m_psc_cnt = 0;

    // Индексация.
    size_t index = scp->r_index;
    size_t count = scp->r_count;

    // Обработка границ массива данных.
    index = CLAMP(index, 0, ((OSCOPE_SAMPLES) - 1));
    count = CLAMP(count, 0, (OSCOPE_SAMPLES));

    // Запись осциллограмм.
    size_t i;
    oscope_ch_param_t* ch_par;
    oscope_ch_private_t* ch_prv;
    oscope_ch_data_t* ch_dat;
    oscope_sample_t val;

    for(i = 0; i < OSCOPE_CHANNELS; i ++){
        ch_par = &scp->r_ch[i];
        ch_dat = &scp->r_ch_data[i];
        ch_prv = &scp->m_ch[i];

        if(ch_par->enabled && ch_prv->reg != NULL && reg_data(ch_prv->reg) != NULL){
            val = (oscope_sample_t)reg_valuel(ch_prv->reg);
        }else{
            val = 0;
        }

        ch_dat->samples[index] = val;
    }

    // Изменение индексации.
    CYCLIC_INC(index, 0, OSCOPE_SAMPLES);
    count ++; count = MIN(count, OSCOPE_SAMPLES);

    // Обновление индексации.
    scp->r_index = index;
    scp->r_count = count;

    // Завершение осциллографирования
    // после записи необходимого числа семплов.
    if(count == OSCOPE_SAMPLES){
        scp->status = (scp->status & STATUS_READY) | STATUS_VALID;
    }
}

METHOD_IDLE_IMPL(M_oscope, scp)
{
    // Обновление поддерживаемого числа семплов.
    scp->r_samples = OSCOPE_SAMPLES;

    // Обновление указателей на осциллографируемые регистры.
    recalc_values(scp);

    // Готовность к осциллографированию.
    scp->status |= STATUS_READY;
}
