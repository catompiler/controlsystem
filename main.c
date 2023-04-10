#include "modules/modules.h"
#include <stdio.h>
#include <stddef.h>
#include "reg/regs.h"

//#include <sys/time.h>
//#include <stdio.h>


#ifndef __arm__
#define RUN_TESTS 0
#endif

#if defined(RUN_TESTS) && RUN_TESTS == 1
#include "test_main.h"
#endif

static void write_dlog_to_file(void)
{
    FILE* f = fopen("dlog.csv", "w");

    uint32_t get_index = dlog.r_get_index;
    uint32_t i, j;
    for(i = 0; i < dlog.r_count; i ++){
        for(j = 0; j < DATA_LOG_CH_COUNT; j ++){
            fprintf(f, "%d", dlog.r_ch[j].data[get_index]);
            if(j != (DATA_LOG_CH_COUNT - 1)){
                fprintf(f, ", ");
            }else{
                fprintf(f, "\n");
            }
        }
        DATA_LOG_NEXT_INDEX(get_index);
    }

    fclose(f);
}


int main(void)
{
    //loadsettings();

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

    write_dlog_to_file();

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

    return 0;
}
