#include "modules/modules.h"
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "reg/regs.h"

//#include <sys/time.h>
//#include <stdio.h>

#ifndef __linux__
#include "thread_timer/windows_timer_res.h"
#ifdef WINDOWS_TIMER
//! Устанавливать ли разрешение таймера в windows.
//! 1 - да.
//! 0, либо не определено - нет.
#define WINDOWS_SET_TIMER_RESOLUTION 1
#endif
#endif

#ifndef __arm__
#define RUN_TESTS 0
#define WRITE_DLOG_TO_CSV 1
#define WRITE_DLOG_TO_VCD 0
#endif

#if defined(RUN_TESTS) && RUN_TESTS == 1
#include "test_main.h"
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
                fprintf(f, "%d", dlog.r_ch[j].data[get_index]);
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

    dlog.p_ch[0].reg_id = REG_ID_ADC_UA;
    dlog.p_ch[0].enabled = 1;
    dlog.p_ch[1].reg_id = REG_ID_ADC_UB;
    dlog.p_ch[1].enabled = 1;
    dlog.p_ch[2].reg_id = REG_ID_ADC_UC;
    dlog.p_ch[2].enabled = 1;
    dlog.control = CONTROL_ENABLE;

    INIT(sys);

    if(sys.status & SYS_MAIN_STATUS_ERROR){
        printf("Error init main system!\n");
        DEINIT(sys);
#if defined(WINDOWS_SET_TIMER_RESOLUTION) && WINDOWS_SET_TIMER_RESOLUTION == 1
        windows_timer_restore_res();
#endif
        return 0;
    }

    for(;;){
        IDLE(sys);

        if(adc_tim.out_counter >= DATA_LOG_CH_LEN) break;

//        struct timespec t;
//        clock_gettime(CLOCK_MONOTONIC, &t);
//        printf("%ld s %ld ns\n", t.tv_sec, t.tv_nsec);
    }

    dlog.control = CONTROL_NONE;

    DEINIT(sys);

#if defined(WRITE_DLOG_TO_CSV) && WRITE_DLOG_TO_CSV == 1
    write_dlog_to_file_csv();
#endif
#if defined(WRITE_DLOG_TO_VCD) && WRITE_DLOG_TO_VCD == 1
    write_dlog_to_file_vcd();
#endif

    printf("done\n");

//    struct timespec t;
//    clock_getres(CLOCK_MONOTONIC, &t);
//    printf("Timer res: %ld sec %ld nsec\n", t.tv_sec, t.tv_nsec);


//    reg_t* r = regs_find(REG_ID_ADC_UA);
//    if(r != NULL){
//        printf("reg id %d, search id %d\n", r->id, REG_ID_ADC_UA);
//        printf("reg data: 0x%x\n", reg_value(r, int));
//    }

    //printf("0x%x 0x%x\n", conf.r_inv_U_nom, conf.r_inv_I_nom);

#if defined(RUN_TESTS) && RUN_TESTS == 1
    test_main();
#endif

#if defined(WINDOWS_SET_TIMER_RESOLUTION) && WINDOWS_SET_TIMER_RESOLUTION == 1
        windows_timer_restore_res();
#endif

    return 0;
}
