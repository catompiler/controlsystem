#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "syslog/syslog.h"
//#include <sys/time.h>
//#include <stdio.h>

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "hardware/hardware.h"
#include "interrupts/interrupts.h"
#include "gpio/gpio_xmc4xxx.h"
#endif


syslog_t SYSLOG_NAME;


#ifndef __arm__
#define RUN_TESTS 0
#define WRITE_DLOG_TO_CSV 1
#define WRITE_DLOG_TO_VCD 0
#define WRITE_DLOG_ABSOLUTE_VALUES 0

#if defined(RUN_TESTS) && RUN_TESTS == 1
#include "test_main.h"
#endif

#ifndef __linux__
#include "thread_timer/windows_timer_res.h"
#ifdef WINDOWS_TIMER
//! Устанавливать ли разрешение таймера в windows.
//! 1 - да.
//! 0, либо не определено - нет.
#define WINDOWS_SET_TIMER_RESOLUTION 1
#endif // WINDOWS_TIMER
#endif // __linux__
#endif // __arm__

#include "modules/modules.h"
#include "reg/regs.h"


#if (defined(WRITE_DLOG_TO_CSV) && WRITE_DLOG_TO_CSV == 1) ||\
    (defined(WRITE_DLOG_TO_VCD) && WRITE_DLOG_TO_VCD == 1)

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
#endif


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
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    gpio_set_pad_driver(PORT1, GPIO_PIN_0, GPIO_PAD_A1P_DRIVER_STRONG_EDGE_SOFT);
    gpio_set(PORT1, GPIO_PIN_0);
    gpio_init(PORT1, GPIO_PIN_0, GPIO_CONF_OUTPUT_PP_GP);

    gpio_toggle(PORT1, GPIO_PIN_0);
    __NOP();
    gpio_toggle(PORT1, GPIO_PIN_0);
    __NOP();
    gpio_reset(PORT1, GPIO_PIN_0);

    for(;;){
    }
#endif

    syslog_init(&SYSLOG_NAME);
    syslog_set_level(&SYSLOG_NAME, SYSLOG_DEBUG);
#if defined(PORT_POSIX)
    syslog_set_putchar_callback(&SYSLOG_NAME, putchar);
#endif

    SYSLOG(SYSLOG_INFO, "Hello, syslog!");
    SYSLOG(SYSLOG_DEBUG, "Blablabla!");
    SYSLOG(SYSLOG_WARNING, "Ololo!");
    SYSLOG(SYSLOG_ERROR, "AAAAAAAAAAggggghhhh!");
    SYSLOG(SYSLOG_FATAL, "UUUUuuuuuuu!");

    SYSLOG(SYSLOG_DEBUG, "INTEGERRR!!! %d", 123456);

    char msg[SYSLOG_MAX_FULL_MSG_LEN + 1];
    msg[SYSLOG_MAX_FULL_MSG_LEN] = 0;

    int first_index = syslog_first_message_index(&SYSLOG_NAME);
    if(first_index >= 0){
        int index = 0;
        do{
            if(syslog_get_message(&SYSLOG_NAME, first_index, index, msg, SYSLOG_MAX_FULL_MSG_LEN) > 0){
                puts(msg);
            }
            index = syslog_next_message_index(&SYSLOG_NAME, first_index, index);
        }while(index >= 0);
    }

    return 0;

    //loadsettings();
#if defined(WINDOWS_SET_TIMER_RESOLUTION) && WINDOWS_SET_TIMER_RESOLUTION == 1
    windows_timer_set_max_res();
#endif
    int dlog_i = 0;
    // Stator Uabc
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_ADC_MODEL_OUT_S_UA;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_ADC_MODEL_OUT_S_UB;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_ADC_MODEL_OUT_S_UC;
    dlog.p_ch[dlog_i++].enabled = 1;
    // Stator Iabc
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_STATOR_IA;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_STATOR_IB;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_STATOR_IC;
    dlog.p_ch[dlog_i++].enabled = 1;
    // Rotor U, I, Irstart
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_UFLD;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_IFLD;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_IRSTART;
    dlog.p_ch[dlog_i++].enabled = 1;
    // Motor M, w
    /*dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_M;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_W;
    dlog.p_ch[dlog_i++].enabled = 1;
    // Rectifier Uabc
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_ADC_MODEL_OUT_UA;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_ADC_MODEL_OUT_UB;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_ADC_MODEL_OUT_UC;
    dlog.p_ch[dlog_i++].enabled = 1;
    // Rectifier Iabc
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_IA;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_IB;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_IC;
    dlog.p_ch[dlog_i++].enabled = 1;
    // Cell RMS.
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_RMS_CELL_UA_OUT_VALUE;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_RMS_CELL_UB_OUT_VALUE;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_RMS_CELL_UC_OUT_VALUE;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_RMS_CELL_IA_OUT_VALUE;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_RMS_CELL_IB_OUT_VALUE;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_RMS_CELL_IC_OUT_VALUE;
    dlog.p_ch[dlog_i++].enabled = 1;
    // Freq arm.
    // I.
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_FILTER_ZCD_SLIP_OUT_VALUE;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_FILTER_FREQ_SLIP_OUT_VALUE;
    dlog.p_ch[dlog_i++].enabled = 1;

    dlog.p_ch[dlog_i  ].reg_id = REG_ID_ZCD_SLIP_OUT_FREQ;
    dlog.p_ch[dlog_i++].enabled = 1;

    dlog.p_ch[dlog_i  ].reg_id = REG_ID_FILTER_MEAN_IRSTART_OUT_VALUE;
    dlog.p_ch[dlog_i++].enabled = 1;

    dlog.p_ch[dlog_i  ].reg_id = REG_ID_POWER_A_OUT_S;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_POWER_A_OUT_P;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_POWER_A_OUT_Q;
    dlog.p_ch[dlog_i++].enabled = 1;

    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_STATOR_IA;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_STATOR_IA;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_OUT_STATOR_IA;
    dlog.p_ch[dlog_i++].enabled = 1;

    dlog.p_ch[dlog_i  ].reg_id = REG_ID_PHASE_LRM_I_STATOR_OUT_A;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_PHASE_LRM_I_STATOR_OUT_B;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_PHASE_LRM_I_STATOR_OUT_C;
    dlog.p_ch[dlog_i++].enabled = 1;

    dlog.p_ch[dlog_i  ].reg_id = REG_ID_POWER_FACTOR_OUT_COS_PHI;
    dlog.p_ch[dlog_i++].enabled = 1;

    dlog.p_ch[dlog_i  ].reg_id = REG_ID_POWER_FACTOR_OUT_SIN_PHI;
    dlog.p_ch[dlog_i++].enabled = 1;

    dlog.p_ch[dlog_i  ].reg_id = REG_ID_POWER_FACTOR_OUT_TAN_PHI;
    dlog.p_ch[dlog_i++].enabled = 1;


    dlog.control = CONTROL_ENABLE;*/

    // ADC model set to zero scales.
    adc_model.in_U_scale = IQ24(0.0);
    adc_model.in_F_scale = IQ24(0.0);

    // meas muxes sel to models.
    mux_Umains.p_sel = 1;
    mux_Imains.p_sel = 1;
    mux_Uarm.p_sel = 1;
    mux_Iarm.p_sel = 1;
    mux_Irstart.p_sel = 1;
    mux_Ucell.p_sel = 1;
    mux_Icell.p_sel = 1;
    mux_slip.p_sel = 0;
    calc_Ucell.p_sel = 0;
    calc_Icell.p_sel = 0;

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

    settings.control = SETTINGS_CONTROL_LOAD;
    CONTROL(settings);

    for(;;){
        IDLE(sys);
        if((settings.control & SETTINGS_CONTROL_LOAD) == 0) break;
    }

    if(settings.status & STATUS_ERROR){
        printf("Settings read error!\n");
        printf("Starting write default settings.\n");
        settings.control = SETTINGS_CONTROL_STORE;
        CONTROL(settings);
    }
//    else{
//        printf("Settings readed successfully!\n");
//    }

    //printf("Ks: %f, Kl: %f\n", (float)FRACT_MEAN_KS/(1<<24), (float)FRACT_MEAN_KL/(1<<24));

    // Off.
    sys_cmd.out_command = SYS_COMMAND_COMMAND_CELL_CB_NC;

    // ADC model set to normal scales.
    adc_model.in_U_scale = IQ24(1.0);
    adc_model.in_F_scale = IQ24(1.0);

    for(;;){
        IDLE(sys);

//        if(adc_tim.out_counter >= 256){
//            if(lrm.in_stator_on == 0){
//                // Main contactor is on.
//                sys_cmd.out_command = SYS_COMMAND_COMMAND_CELL_CB_NO;
//                lrm.in_stator_on = 1;
////                lrm.in_start_r_on = 1;
//            }
//        }

        if(sys_cmd.out_command == SYS_COMMAND_COMMAND_CELL_CB_NO){
            lrm.in_stator_on = 1;
        }

        if((sys_cmd.out_command == SYS_COMMAND_COMMAND_CELL_CB_NC) || (sys_cmd.out_command & SYS_COMMAND_COMMAND_CELL_PROT)){
            lrm.in_stator_on = 0;
        }

//        if(adc_tim.out_counter >= DATA_LOG_CH_LEN - DATA_LOG_CH_LEN / 8){
//            if(lrm.in_stator_on == 1){
//                // Stop.
//                sys_cmd.out_command = SYS_COMMAND_COMMAND_CELL_CB_NC;
//                lrm.in_stator_on = 0;
//            }
//        }

        //if(adc_tim.out_counter >= DATA_LOG_CH_LEN) break;
        if(sys.status & SYS_MAIN_STATUS_QUIT) break;
#ifndef __arm__
        struct timespec ts_sleep = {0, 1000000};
        nanosleep(&ts_sleep, NULL);
#endif
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
