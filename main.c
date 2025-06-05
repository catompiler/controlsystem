#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "port.h"
#include "sys_counter/sys_counter.h"
#include "syslog/syslog.h"
#include "eeprom/eeprom.h"

#if defined(PORT_POSIX)
#include <stdlib.h>
#endif

// Системный лог.
syslog_t SYSLOG_NAME;

// Конфигурация EEPROM.
#if defined(PORT_POSIX)
// Имя файла EEPROM.
#define EEPROM_FILENAME "eeprom.bin"
#endif
// Размер EEPROM.
#define EEPROM_SIZE (128*1024)
// EEPROM.
static eeprom_t eep;

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
#include "hardware/hardware.h"
#include "interrupts/interrupts.h"
#include "gpio/gpio_xmc4xxx.h"
#include "usart/usart_stdio_xmc4xxx.h"
#include "spi/spi_xmc4xxx.h"
#include "spi/eep_spi_xmc4xxx.h"
#include "can/can_xmc4xxx.h"

// Шина SPI для EEPROM.
static spi_bus_t eep_spi_bus;
// Микросхема EEPROM.
static m95x_t eep_m95x;

// Модуль CAN.
static can_t* can;

// // DEBUG!
//#define SPI_DATA_LEN 128
//uint8_t spi_tx_data[SPI_DATA_LEN] = {0x0};
//uint8_t spi_rx_data[SPI_DATA_LEN] = {0x0};
//spi_message_t spi_msg;

#endif


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

    fflush(f);
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



static void init_first()
{
#if defined(WINDOWS_SET_TIMER_RESOLUTION) && WINDOWS_SET_TIMER_RESOLUTION == 1
    windows_timer_set_max_res();
#endif

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    // Configure NVIC.
    interrupts_init();
#endif
}

static void init_hardware()
{
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    // Configure GPIO.
    hardware_init_ports();

    // Configure DMA.
    hardware_init_dma();
    interrupts_enable_dma();

    // Counting timers.
    hardware_init_counting_timers();

    // Periodic timers.
    hardware_init_periodic_timers();

    // Triacs timers.
    hardware_init_triacs_timers();

    // Usarts.
    hardware_init_usarts();

    // SPIs.
    hardware_init_spis();

    // CAN.
    hardware_init_can();

    // DAC.
    hardware_init_dac();

    // ADC.
    hardware_init_adc();
#endif
}

static void init_sys_counter()
{
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    interrupts_enable_sys_counter();
#endif

    sys_counter_init();
    sys_counter_start();
}

static void init_syslog()
{
    // Init syslog.
    syslog_init(&SYSLOG_NAME);
    syslog_set_level(&SYSLOG_NAME, SYSLOG_DEBUG);

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    // Init stdio.

    interrupts_enable_stdio_uart();

    err_t err = usart_stdio_init();
    if(err != E_NO_ERROR){
        SYSLOG(SYSLOG_WARNING, "Error init usart stdio! (%u)", (unsigned int)err);
    }else{
        syslog_set_putchar_callback(&SYSLOG_NAME, putchar);
        SYSLOG(SYSLOG_INFO, "usart stdio initialized!");
    }
#endif

#if defined(PORT_POSIX)
    syslog_set_putchar_callback(&SYSLOG_NAME, putchar);
#endif
}

static void init_eeprom()
{
    err_t err = E_NO_ERROR;
    void* eep_param_ptr = NULL;

#if defined(PORT_POSIX)
    eep_param_ptr = EEPROM_FILENAME;
#endif

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    // Init eeprom.

    // Init nHOLD.
    gpio_set(EEP_PORT_nHOLD, EEP_PIN_nHOLD_Msk);
    gpio_set_pad_driver(EEP_PORT_nHOLD, EEP_PIN_nHOLD_Msk, EEP_PIN_nHOLD_DRIVER);
    gpio_init(EEP_PORT_nHOLD, EEP_PIN_nHOLD_Msk, EEP_PIN_nHOLD_CONF);

    // Init nWP.
    gpio_set(EEP_PORT_nWP, EEP_PIN_nWP_Msk);
    gpio_set_pad_driver(EEP_PORT_nWP, EEP_PIN_nWP_Msk, EEP_PIN_nWP_DRIVER);
    gpio_init(EEP_PORT_nWP, EEP_PIN_nWP_Msk, EEP_PIN_nWP_CONF);

    eeprom_init_t eep_is;
    eep_is.gpio_nhold = EEP_PORT_nHOLD;
    eep_is.pin_nhold = EEP_PIN_nHOLD_Msk;
    eep_is.gpio_nwp = EEP_PORT_nWP;
    eep_is.pin_nwp = EEP_PIN_nWP_Msk;
    eep_is.m95x = NULL; // Invalid (not initializable eeprom).
    eep_param_ptr = &eep_is;
    //for(;;){
        //hardware_init_dma();
    interrupts_enable_eep_spi();

    err = eep_spi_init(&eep_spi_bus);
    if(err != E_NO_ERROR){
        SYSLOG(SYSLOG_WARNING, "Error init eep spi! (%u)", (unsigned int)err);
    }else{
        SYSLOG(SYSLOG_INFO, "Eep spi initialized!");

        // init m95x.
        m95x_init_t m95x_is;
        m95x_is.transfer_id = M95X_DEFAULT_TRANSFER_ID;
        m95x_is.spi = &eep_spi_bus;
        m95x_is.page = M95X_PAGE_256;
        m95x_is.ce_gpio = NULL;
        m95x_is.ce_pin_sel_msk = EEP_CS_SEL_Msk;
        err = m95x_init(&eep_m95x, &m95x_is);
        if(err != E_NO_ERROR){
            SYSLOG(SYSLOG_WARNING, "Error init eep m95x! (%u)", (unsigned int)err);
        }else{
            SYSLOG(SYSLOG_INFO, "Eep m95x initialized!");
            eep_is.m95x = &eep_m95x;
            spi_bus_set_user_data(&eep_spi_bus, &eep_m95x);
            spi_bus_set_callback(&eep_spi_bus, (spi_callback_t)m95x_spi_callback);
        }
    }

    /*if(err == E_NO_ERROR){
        err = spi_message_init(&spi_msg, SPI_WRITE, spi_tx_data, NULL, SPI_DATA_LEN); //spi_rx_data
        if(err != E_NO_ERROR){
            SYSLOG(SYSLOG_WARNING, "spi msg init failed!");
        }else{
            size_t i;
            for(i = 0; i < SPI_DATA_LEN; i ++){
                spi_tx_data[i] = ((uint8_t)i & 0xff);
                spi_rx_data[i] = 0x0;
            }
            spi_bus_set_hw_sel(&eep_spi_bus, 0x0);
            err = spi_bus_transfer(&eep_spi_bus, &spi_msg, 1);
            if(err != E_NO_ERROR){
                SYSLOG(SYSLOG_WARNING, "spi transfer start failed!");
            }else{
                spi_bus_wait(&eep_spi_bus);
                SYSLOG(SYSLOG_DEBUG, "spi transfers errs: 0x%x", (unsigned int)spi_bus_errors(&eep_spi_bus));
                __NOP();
            }
        }
    }

    for(;;) __NOP();*/
#endif

    /*m95x_status_t status;
    status.block_protect = 0;
    status.status_reg_write_protect = 0;
    status.write_enable_latch = 0;
    status.write_in_progress = 0;

    for(;;){
        err = m95x_write_status(&eep_m95x, &status);
        if(err != E_NO_ERROR){
            SYSLOG(SYSLOG_WARNING, "Error m95x_write_status! (%u)", (unsigned int)err);
        }
    }*/

    err = eeprom_init(&eep, eep_param_ptr, EEPROM_SIZE);
    if(err != E_NO_ERROR){
        SYSLOG(SYSLOG_WARNING, "Error init eeprom! (%u)", (unsigned int)err);
    }else{
        SYSLOG(SYSLOG_INFO, "Eeprom initialized!");
    }
}

static void init_storage()
{
    err_t err = E_NO_ERROR;

    err = STORAGE_INIT(storage, &eep);
    if(err != E_NO_ERROR){
        SYSLOG(SYSLOG_WARNING, "Error init storage! (%u)", (unsigned int)err);
    }else{
        SYSLOG(SYSLOG_INFO, "Storage initialized!");
    }
}

static void init_settings()
{
    INIT(settings);
}

static void init_event_log()
{
    // Лог событий.
    INIT(event_log);
}

static void load_settings()
{
    // Read settings.
    settings.control = SETTINGS_CONTROL_LOAD;
    CONTROL(settings);

    for(;;){
        // Настройки.
        IDLE(settings);

        if((settings.control & SETTINGS_CONTROL_LOAD) == 0) break;

        // Хранилище.
        IDLE(storage);
    }

    if(settings.status & STATUS_ERROR){
        SYSLOG(SYSLOG_WARNING, "Settings read error!");
        //settings.control = SETTINGS_CONTROL_STORE;
        //CONTROL(settings);
    }else{
        SYSLOG(SYSLOG_INFO, "Settings readed successfully!");
    }
}

static void refresh_event_log()
{
    // Read settings.
    event_log.control = EVENT_LOG_CONTROL_REFRESH;
    CONTROL(event_log);

    for(;;){
        // Настройки.
        IDLE(event_log);

        if((event_log.status & EVENT_LOG_STATUS_RUN) == 0) break;

        // Хранилище.
        IDLE(storage);
    }

    if(event_log.status & STATUS_ERROR){
        SYSLOG(SYSLOG_WARNING, "Event log refresh error!");
    }else{
        SYSLOG(SYSLOG_INFO, "Event log refreshed successfully!");
    }
}



#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
//static can_node_t* can_node;
static can_node_t* can_node[2];
static can_msg_t msg;

static can_mo_index_t mo_0_tx;
static can_mo_index_t mo_0_rx;
static can_mo_index_t mo_1_tx;
static can_mo_index_t mo_1_rx;

static volatile size_t events_counter = 0;

void on_node_event(can_node_t* can_node, can_node_event_t* event)
{
    __NOP();

    events_counter ++;

    if(event->type == CAN_NODE_EVENT_MSG_RECV){

        can_mo_index_t mo_rx_index = event->msg_recv.mo_index;
        can_mo_index_t mo_tx_index = (mo_rx_index == mo_0_rx) ? mo_0_tx : mo_1_tx;

        can_node_recv_msg(can_node, mo_rx_index, &msg);
        for(int i = 0; i < 8; i ++){
            msg.data[i] ++;
        }
        can_node_send_msg(can_node, mo_tx_index, &msg);
    }
}
#endif


static void init_can()
{
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    interrupts_enable_can();

    err_t err = E_NO_ERROR;
    can = can_get(CAN_N);

    if(can != NULL){
        err = can_init(can, NULL);
    }

    if(can != NULL && err == E_NO_ERROR){
        SYSLOG(SYSLOG_INFO, "CAN module initialized!");
    }else{
        SYSLOG(SYSLOG_ERROR, "CAN module initialization error!");
    }
#endif

    CO_driver_t* codrv = CO_driver_init();

    if(codrv != NULL){
        SYSLOG(SYSLOG_INFO, "CAN CO driver initialized!");
    }else{
        SYSLOG(SYSLOG_ERROR, "CAN CO driver initialization error!");
    }
}

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
static void init_can_node()
{
    can_node_init_t cnis;
    cnis.loopback = false;
    cnis.analyzer = false;
    cnis.bit_rate = CAN_BIT_RATE_125kbit;
    cnis.callback = NULL;
    cnis.sel_rx = CAN_NODE_RX_SEL;
    cnis.gpio_tx = CAN_NODE_PORT_TX;
    cnis.pin_tx_msk = CAN_NODE_PIN_TX_Msk;
    cnis.conf_tx = CAN_NODE_PIN_TX_CONF;
    cnis.pad_driver_tx = CAN_NODE_PIN_TX_DRIVER;
    cnis.gpio_rx = CAN_NODE_PORT_RX;
    cnis.pin_rx_msk = CAN_NODE_PIN_RX_Msk;
    cnis.conf_rx = CAN_NODE_PIN_RX_CONF;

    cnis.sel_rx = 0;
    cnis.gpio_tx = NULL;
    cnis.pin_tx_msk = 0;
    cnis.conf_tx = 0;
    cnis.pad_driver_tx = 0;
    cnis.gpio_rx = NULL;
    cnis.pin_rx_msk = 0;
    cnis.conf_rx = 0;

    can_node[0] = can_node_get(can, 1);
    can_node[1] = can_node_get(can, 2);

    err_t err = E_NO_ERROR;

    err = can_node_init(can_node[0], &cnis);
    if(err != E_NO_ERROR){
        for(;;){
            __NOP();
        }
    }

    err = can_node_init(can_node[1], &cnis);
    if(err != E_NO_ERROR){
        for(;;){
            __NOP();
        }
    }

    mo_0_tx = can_node_init_tx_buffer(can_node[0], 1, 0x400, false, 8);
    mo_0_rx = can_node_init_rx_buffer(can_node[0], 1, 0x400, 0x0, false);

    mo_1_tx = can_node_init_tx_buffer(can_node[1], 1, 0x400, false, 8);
    mo_1_rx = can_node_init_rx_buffer(can_node[1], 1, 0x400, 0x0, false);

    can_node_set_normal_mode(can_node[0]);
    can_node_set_normal_mode(can_node[1]);

    can_msg_t can_msg;
    size_t i;

    can_msg.rtr = false;
    can_msg.ide = 0;
    can_msg.id = 0x01;
    can_msg.dlc = 8;
    for(i = 0; i < 8; i ++){
        can_msg.data[i] = i;
    }

    //can_msg.id ++;
    can_node_send_msg(can_node[0], 0, &can_msg);
}
#endif

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
static void test_can()
{
    /*can_msg_t can_msg;
    size_t i;

    can_msg.rtr = false;
    can_msg.ide = 0;
    can_msg.id = 0x01;
    can_msg.dlc = 8;
    for(i = 0; i < 8; i ++){
        can_msg.data[i] = i;
    }

    //can_msg.id ++;
    can_send_msg(can_node, 0, &can_msg);

    can_msg.id ++;
    can_send_msg(can_node, 0, &can_msg);

    can_msg.id ++;
    can_send_msg(can_node, 0, &can_msg);

    can_msg.id ++;
    can_send_msg(can_node, 0, &can_msg);

    can_msg.id ++;
    can_send_msg(can_node, 0, &can_msg);*/
}
#endif

static void setup()
{
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
    dlog.p_ch[dlog_i++].enabled = 1;*/
#if defined(PORT_POSIX)
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
    // Phases
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_PHASE_AMPL_UA_OUT_PHASE;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_PHASE_AMPL_UB_OUT_PHASE;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_PHASE_AMPL_UC_OUT_PHASE;
    dlog.p_ch[dlog_i++].enabled = 1;
    // LRM control
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_IN_CONTROL0;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_IN_CONTROL1;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_IN_CONTROL2;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_IN_CONTROL3;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_IN_CONTROL4;
    dlog.p_ch[dlog_i++].enabled = 1;
    dlog.p_ch[dlog_i  ].reg_id = REG_ID_LRM_IN_CONTROL5;
    dlog.p_ch[dlog_i++].enabled = 1;

    dlog.p_ch[dlog_i  ].reg_id = REG_ID_PROT_RAW_ERRORS1;
    dlog.p_ch[dlog_i++].enabled = 1;

    dlog.p_ch[dlog_i  ].reg_id = REG_ID_SYS_CTRL_FSM_STATE_STATE;
    dlog.p_ch[dlog_i++].enabled = 1;
#endif
    // Cell RMS.
    /*dlog.p_ch[dlog_i  ].reg_id = REG_ID_RMS_CELL_UA_OUT_VALUE;
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
    dlog.p_ch[dlog_i++].enabled = 1;*/

    dlog.control = CONTROL_ENABLE;

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

    // ADC model set to noise scales.
    adc_model.in_U_scale = IQ24(0.01);
    adc_model.in_F_scale = IQ24(100);

    //printf("Ks: %f, Kl: %f\n", (float)FRACT_MEAN_KS/(1<<24), (float)FRACT_MEAN_KL/(1<<24));

    // Off.
    sys_cmd.out_command = SYS_COMMAND_COMMAND_CELL_CB_NC;

    // ADC model set to normal scales.
    adc_model.in_U_scale = IQ24(1.0);
    adc_model.in_F_scale = IQ24(1.0);
}

static void init_sysmain()
{
#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    interrupts_inited_enable();
#endif

    INIT(sys);

    if(sys.status & SYS_MAIN_STATUS_ERROR){
        SYSLOG(SYSLOG_FATAL, "Error init main system!\n");
        DEINIT(sys);
#if defined(WINDOWS_SET_TIMER_RESOLUTION) && WINDOWS_SET_TIMER_RESOLUTION == 1
        windows_timer_restore_res();
#endif

#if defined(PORT_POSIX)
        exit(-1);
#endif

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
        for(;;){
            // TODO: led blinking.
            __NOP();
        }
#endif
    }
}

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
__attribute__((noreturn))
#endif
static void main_end()
{
#if defined(PORT_POSIX)
    dlog.control = CONTROL_NONE;

    DEINIT(sys);

    // Лог событий.
    DEINIT(event_log);

    // Настройки.
    DEINIT(settings);

    // Хранилище.
    DEINIT(storage);

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

#endif

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
    for(;;){
        // TODO: led blinking.
        __NOP();
    }
#endif
}

int main(void)
{
    init_first();
    init_hardware();

    init_sys_counter();
    init_syslog();

    init_can();

//#if defined(PORT_XMC4500) || defined(PORT_XMC4700)
//    //init_can_node();
//    test_can();
//    for(;;){
//        //test_can();
//        __NOP();
//    }
//#endif

    init_eeprom();
    init_storage();
    init_settings();
    init_event_log();

    load_settings();
    refresh_event_log();

    setup();

    init_sysmain();

    for(;;){
        IDLE(sys);

#if defined(PORT_POSIX)
        if(adc_tim.out_counter >= DATA_LOG_CH_LEN / 8){
            // Main contactor is on.
            sys_cmd.out_command = SYS_COMMAND_COMMAND_CELL_CB_NO;
        }
#endif

#if defined(PORT_POSIX)
        if(adc_tim.out_counter >= DATA_LOG_CH_LEN - DATA_LOG_CH_LEN / 8){
            // Stop.
            sys_cmd.out_command = SYS_COMMAND_COMMAND_CELL_CB_NC;
        }
#endif

        if(sys_cmd.out_command == SYS_COMMAND_COMMAND_CELL_CB_NO){
            lrm.in_stator_on = 1;
        }

        if((sys_cmd.out_command == SYS_COMMAND_COMMAND_CELL_CB_NC) || (sys_cmd.out_command & SYS_COMMAND_COMMAND_CELL_PROT)){
            lrm.in_stator_on = 0;
        }

#if defined(PORT_POSIX)
        if(adc_tim.out_counter >= DATA_LOG_CH_LEN) break;
        if(sys.status & SYS_MAIN_STATUS_QUIT) break;

        struct timespec ts_sleep = {0, 1000000};
        nanosleep(&ts_sleep, NULL);
#endif
    }

    main_end();

    return 0;
}
