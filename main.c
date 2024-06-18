#include <stdio.h>
#include <stddef.h>
#include <string.h>
//#include <sys/time.h>
//#include <stdio.h>

#ifndef __arm__
#define RUN_TESTS 0
#define WRITE_DLOG_TO_CSV 1
#define WRITE_DLOG_TO_VCD 0
#define WRITE_DLOG_ABSOLUTE_VALUES 0
#endif

#if defined(RUN_TESTS) && RUN_TESTS == 1
#include "test_main.h"
#endif

#include "modules/modules.h"
#include "reg/regs.h"

#ifndef __linux__
#include "thread_timer/windows_timer_res.h"
#ifdef WINDOWS_TIMER
//! Устанавливать ли разрешение таймера в windows.
//! 1 - да.
//! 0, либо не определено - нет.
#define WINDOWS_SET_TIMER_RESOLUTION 1
#endif
#endif


static float get_float_value(reg_type_t type, void* value)
{
    switch(type){
    default:
        break;
    case REG_TYPE_I32:
        return (float)(*(int32_t*)value);
    case REG_TYPE_U32:
        return (float)(*(uint32_t*)value);
    case REG_TYPE_IQ7:
        return (float)(*(int32_t*)value) / IQ7_BASE;
    case REG_TYPE_IQ15:
        return (float)(*(int32_t*)value) / IQ15_BASE;
    case REG_TYPE_IQ24:
        return (float)(*(int32_t*)value) / IQ24_BASE;
    }

    return 0.0f;
}

static float get_log_ch_data(data_log_ch_data_t* ch_data, uint32_t data_index)
{
    reg_t* reg = ch_data->reg;

    if(!reg){
        return 0.0f;
    }

    float valuef = get_float_value(reg->type, &ch_data->data[data_index]);
    float basef = 1.0f;

#if defined(WRITE_DLOG_ABSOLUTE_VALUES) && WRITE_DLOG_ABSOLUTE_VALUES == 1
    reg_t* base_reg = regs_find(reg->base_id);
    if(base_reg){
        basef = get_float_value(base_reg->type, base_reg->data);
    }
#endif

    return valuef * basef;
}


#if defined(WRITE_DLOG_TO_CSV) && WRITE_DLOG_TO_CSV == 1
static void write_dlog_to_file_csv(void)
{
    FILE* f = fopen("dlog.csv", "w");

    uint32_t get_index = dlog.r_get_index;
    uint32_t i, j;
    int first = 0;
    for(i = 0; i < dlog.r_count; i ++){
        first = 1;
        for(j = 0; j < DATA_LOG_CH_COUNT; j ++){
//            fprintf(f, "%d", dlog.r_ch[j].data[get_index]);
//            if(j != (DATA_LOG_CH_COUNT - 1)){
//                fprintf(f, ", ");
//            }else{
//                fprintf(f, "\n");
//            }
            if(dlog.p_ch[j].enabled){
                if(first == 0){
                    fprintf(f, ", ");
                }
                //fprintf(f, "%d", dlog.r_ch[j].data[get_index]);
                fprintf(f, "%f", get_log_ch_data(&dlog.r_ch[j], get_index));
                first = 0;
            }
        }
        fprintf(f, "\n");
        DATA_LOG_NEXT_INDEX(get_index);
    }

    fclose(f);
}
#endif

#if defined(WRITE_DLOG_TO_VCD) && WRITE_DLOG_TO_VCD == 1
static void make_bin_str(char* buf, size_t buf_size, uint32_t val, size_t bits)
{
    memset(buf, 0x0, buf_size);

    val = val << (32 - bits);

    int i,j;
    for(i = 0, j = 0; i < bits && j < buf_size - 1; i ++, j ++){
        buf[j] = (val & 0x80000000) ? '1' : '0';
        val <<= 1;
    }
    buf[j] = 0;
}

static void write_dlog_to_file_vcd(void)
{
    FILE* f = fopen("dlog.vcd", "w");

    char first_id_char = 'A';

    uint32_t get_index = dlog.r_get_index;
    uint32_t prev_index = get_index;
    uint32_t i, j;

    #define BIN_SIZE 32
    #define BIN_BUF_SIZE 33
    char buf[BIN_BUF_SIZE];

    // write header.
    fprintf(f, "$timescale 625 us $end\n");
    fprintf(f, "$scope module dlog $end\n");
    for(i = 0; i < DATA_LOG_CH_COUNT; i ++){
        if(dlog.p_ch[i].enabled){
            fprintf(f, "$var reg %d %c dlog_ch%d $end\n", BIN_SIZE, first_id_char + i, i);
        }
    }
    fprintf(f, "$upscope $end\n");
    fprintf(f, "$enddefinitions $end\n");

    /*fprintf(f, "$dumpvars\n");
    for(i = 0; i < DATA_LOG_CH_COUNT; i ++){
        if(dlog.p_ch[i].enabled){
            make_bin_str(buf, BIN_BUF_SIZE, 0, BIN_SIZE);
            fprintf(f, "b%s %c\n", buf, first_id_char + i);
        }
    }
    fprintf(f, "$end\n");*/

    // write data.
    DATA_LOG_PREV_INDEX(prev_index);
    for(i = 0; i < dlog.r_count; i ++){
        fprintf(f, "#%d\n", i);
        for(j = 0; j < DATA_LOG_CH_COUNT; j ++){
            if(dlog.p_ch[j].enabled){
                if((i == 0) ||
                   (dlog.r_ch[j].data[get_index] >> (32-BIN_SIZE)) !=
                   (dlog.r_ch[j].data[prev_index] >> (32-BIN_SIZE))){
                    //
                    make_bin_str(buf, BIN_BUF_SIZE, dlog.r_ch[j].data[get_index] >> (32-BIN_SIZE), BIN_SIZE);
                    fprintf(f, "b%s %c\n", buf, first_id_char + j);
                }
            }
        }
        prev_index = get_index;
        DATA_LOG_NEXT_INDEX(get_index);
    }

    fclose(f);

    #undef BIN_BUF_SIZE
}
#endif

int main(void)
{
    //loadsettings();
#if defined(WINDOWS_SET_TIMER_RESOLUTION) && WINDOWS_SET_TIMER_RESOLUTION == 1
    windows_timer_set_max_res();
#endif

    // Stator Uabc
    dlog.p_ch[0].reg_id = REG_ID_MODEL_STATOR_UA;
    dlog.p_ch[0].enabled = 1;
    dlog.p_ch[1].reg_id = REG_ID_MODEL_STATOR_UB;
    dlog.p_ch[1].enabled = 1;
    dlog.p_ch[2].reg_id = REG_ID_MODEL_STATOR_UC;
    dlog.p_ch[2].enabled = 1;
    // Stator Iabc
    dlog.p_ch[3].reg_id = REG_ID_MODEL_STATOR_IA;
    dlog.p_ch[3].enabled = 1;
    dlog.p_ch[4].reg_id = REG_ID_MODEL_STATOR_IB;
    dlog.p_ch[4].enabled = 1;
    dlog.p_ch[5].reg_id = REG_ID_MODEL_STATOR_IC;
    dlog.p_ch[5].enabled = 1;
    // Rotor U, I, Irstart
    dlog.p_ch[6].reg_id = REG_ID_MODEL_ROTOR_U;
    dlog.p_ch[6].enabled = 1;
    dlog.p_ch[7].reg_id = REG_ID_MODEL_ROTOR_I;
    dlog.p_ch[7].enabled = 1;;
    dlog.p_ch[8].reg_id = REG_ID_MODEL_R_START_I;
    dlog.p_ch[8].enabled = 1;
    // Motor M, w
    dlog.p_ch[9].reg_id = REG_ID_MODEL_MOTOR_M;
    dlog.p_ch[9].enabled = 1;
    dlog.p_ch[10].reg_id = REG_ID_MODEL_MOTOR_W;
    dlog.p_ch[10].enabled = 1;
    // Rectifier Uabc
    dlog.p_ch[11].reg_id = REG_ID_MODEL_RECTIFIER_UA;
    dlog.p_ch[11].enabled = 1;
    dlog.p_ch[12].reg_id = REG_ID_MODEL_RECTIFIER_UB;
    dlog.p_ch[12].enabled = 1;
    dlog.p_ch[13].reg_id = REG_ID_MODEL_RECTIFIER_UC;
    dlog.p_ch[13].enabled = 1;
    // Rectifier Iabc
    dlog.p_ch[14].reg_id = REG_ID_MODEL_RECTIFIER_IA;
    dlog.p_ch[14].enabled = 1;
    dlog.p_ch[15].reg_id = REG_ID_MODEL_RECTIFIER_IB;
    dlog.p_ch[15].enabled = 1;
    dlog.p_ch[16].reg_id = REG_ID_MODEL_RECTIFIER_IC;
    dlog.p_ch[16].enabled = 1;
    // Cell RMS.
    dlog.p_ch[17].reg_id = REG_ID_RMS_CELL_UA;
    dlog.p_ch[17].enabled = 1;
    dlog.p_ch[18].reg_id = REG_ID_RMS_CELL_UB;
    dlog.p_ch[18].enabled = 1;
    dlog.p_ch[19].reg_id = REG_ID_RMS_CELL_UC;
    dlog.p_ch[19].enabled = 1;
    dlog.p_ch[20].reg_id = REG_ID_RMS_CELL_IA;
    dlog.p_ch[20].enabled = 1;
    dlog.p_ch[21].reg_id = REG_ID_RMS_CELL_IB;
    dlog.p_ch[21].enabled = 1;
    dlog.p_ch[22].reg_id = REG_ID_RMS_CELL_IC;
    dlog.p_ch[22].enabled = 1;
    // Freq arm.
    // I.
    dlog.p_ch[23].reg_id = REG_ID_ARM_FREQ_IRSTART_FILT;
    dlog.p_ch[23].enabled = 1;
    dlog.p_ch[24].reg_id = REG_ID_ARM_FREQ_IRSTART_FREQ;
    dlog.p_ch[24].enabled = 1;

    dlog.p_ch[25].reg_id = REG_ID_ARM_FREQ_SLIP;
    dlog.p_ch[25].enabled = 1;

    dlog.p_ch[26].reg_id = REG_ID_MEAN_IRSTART_FILT;
    dlog.p_ch[26].enabled = 1;

    dlog.p_ch[27].reg_id = REG_ID_POWER_A_S;
    dlog.p_ch[27].enabled = 1;
    dlog.p_ch[28].reg_id = REG_ID_POWER_A_P;
    dlog.p_ch[28].enabled = 1;
    dlog.p_ch[29].reg_id = REG_ID_POWER_A_Q;
    dlog.p_ch[29].enabled = 1;

    dlog.p_ch[30].reg_id = REG_ID_RMS_CELL_UA_LINE;
    dlog.p_ch[30].enabled = 1;
    dlog.p_ch[31].reg_id = REG_ID_RMS_CELL_UB_LINE;
    dlog.p_ch[31].enabled = 1;
    dlog.p_ch[32].reg_id = REG_ID_RMS_CELL_UC_LINE;
    dlog.p_ch[32].enabled = 1;

    dlog.p_ch[33].reg_id = REG_ID_POWER_FACTOR_COS_PHI;
    dlog.p_ch[33].enabled = 1;

    dlog.p_ch[34].reg_id = REG_ID_POWER_FACTOR_SIN_PHI;
    dlog.p_ch[34].enabled = 1;

    dlog.p_ch[35].reg_id = REG_ID_POWER_FACTOR_TAN_PHI;
    dlog.p_ch[35].enabled = 1;

    dlog.control = CONTROL_ENABLE;

    // ADC model set to zero scales.
    adc_model.in_U_scale = IQ24(0.0);
    adc_model.in_F_scale = IQ24(0.0);

    // meas muxes sel to models.
    mains_U.p_sel = 1;
    mains_I.p_sel = 1;
    armature_U.p_sel = 1;
    armature_I.p_sel = 1;
    rstart_I.p_sel = 1;
    mux_cell_U.p_sel = 1;
    mux_cell_I.p_sel = 1;
    mux_slip.p_sel = 0;
    cell_U.p_sel = 0;
    cell_I.p_sel = 0;

    INIT(sys);

    if(sys.status & SYS_MAIN_STATUS_ERROR){
        printf("Error init main system!\n");
        DEINIT(sys);
#if defined(WINDOWS_SET_TIMER_RESOLUTION) && WINDOWS_SET_TIMER_RESOLUTION == 1
        windows_timer_restore_res();
#endif
        return 0;
    }

    // ADC model set to noise scales.
    adc_model.in_U_scale = IQ24(0.01);
    adc_model.in_F_scale = IQ24(100);

    //printf("Ks: %f, Kl: %f\n", (float)FRACT_MEAN_KS/(1<<24), (float)FRACT_MEAN_KL/(1<<24));

    for(;;){
        IDLE(sys);

        if(adc_tim.out_counter >= 64){
            // On.
            sys_cmd.out_command = SYS_COMMAND_COMMAND_ON;
        }

        if(adc_tim.out_counter >= 128){
            // ADC model set to normal scales.
            adc_model.in_U_scale = IQ24(1.0);
            adc_model.in_F_scale = IQ24(1.0); // 1.3
        }

        if(adc_tim.out_counter >= 192){
            // Main contactor is on.
            sys_cmd.out_command = SYS_COMMAND_COMMAND_ON |
                                  SYS_COMMAND_COMMAND_CONT_ON;
            if(lrm.in_stator_on == 0){
                lrm.in_stator_on = 1;
                lrm.in_start_r_on = 1;
            }
        }

        if(adc_tim.out_counter >= CONF_PERIOD_SAMPLES * 10){
            if(lrm.in_start_r_on == 1){
                lrm.in_start_r_on = 0;
            }
        }

        if(adc_tim.out_counter >= 4096){ // 256
            // Run.
            sys_cmd.out_command = SYS_COMMAND_COMMAND_ON |
                                  SYS_COMMAND_COMMAND_CONT_ON |
                                  SYS_COMMAND_COMMAND_RUN;
        }

        if(adc_tim.out_counter >= DATA_LOG_CH_LEN) break;
    }

    dlog.control = CONTROL_NONE;

    DEINIT(sys);

    printf("done\n");

#if defined(WRITE_DLOG_TO_CSV) && WRITE_DLOG_TO_CSV == 1
    write_dlog_to_file_csv();
    printf("csv written\n");
#endif
#if defined(WRITE_DLOG_TO_VCD) && WRITE_DLOG_TO_VCD == 1
    write_dlog_to_file_vcd();
    printf("vcd written\n");
#endif

#if defined(RUN_TESTS) && RUN_TESTS == 1
    test_main();
#endif

#if defined(WINDOWS_SET_TIMER_RESOLUTION) && WINDOWS_SET_TIMER_RESOLUTION == 1
        windows_timer_restore_res();
#endif

    return 0;
}
