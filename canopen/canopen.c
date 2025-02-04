#include "canopen.h"
#include <string.h>
#include <assert.h>
// CANopen.
#include "OD.h"
// net timer.
#include "modules/modules.h"
// hardware config.
#include "hardware/config.h"




#ifdef CO_DRIVER_SLCAN_SLAVE

// slcan.
#ifndef SLCAN_SLAVE_TTY
#ifdef __linux
// socat -d -d pty,rawer,echo=0,link=/tmp/ttyV0,perm=0777 pty,rawer,echo=0,link=/tmp/ttyV1,perm=0777
#define SLCAN_SLAVE_TTY "/tmp/ttyV1"
#elif defined(__arm__)
#define SLCAN_SLAVE_TTY ""
#else
// cygwin + com0com
#define SLCAN_SLAVE_TTY "/dev/ttyS21"
#endif
#endif

#ifndef SLCAN_SLAVE_TTY_BAUD
#define SLCAN_SLAVE_TTY_BAUD SLCAN_PORT_BAUD_115200
#endif

#ifndef CANOPEN_BITRATE
#define CANOPEN_BITRATE 125
#endif


// CO driver.
static int init_CO_driver_slcan_slave(M_canopen* co)
{
    CO_driver_t* drv = CO_driver();

    if(drv == NULL) return -1;

    CO_driver_id_t drvid = CO_driver_init_slcan_slave(drv);
    if(drvid == CO_DRIVER_ID_INVALID) return -2;

    return 0;
}


// slcan.
static slcan_err_t slcan_callback_default()
{
    return E_SLCAN_NO_ERROR;
}

static int init_slcan_slave(M_canopen* co)
{
    assert(co != NULL);

    memset(&co->m_sc, 0x0, sizeof(slcan_t));

    if(slcan_init(&co->m_sc) != 0){
        //printf("Cann't init slcan!\n");
        return -1;
    }

    if(slcan_open(&co->m_sc, SLCAN_SLAVE_TTY) != 0){
        //printf("Cann't open serial port: %s\n", SLCAN_SLAVE_TTY);
        slcan_deinit(&co->m_sc);
        return -2;
    }

    slcan_port_conf_t port_conf;
    slcan_get_default_port_config(&port_conf);

    port_conf.baud = SLCAN_SLAVE_TTY_BAUD;

    if(slcan_configure(&co->m_sc, &port_conf) != 0){
        //printf("Error configuring serial port!\n");
        slcan_close(&co->m_sc);
        slcan_deinit(&co->m_sc);
        return -3;
    }

    co->m_scb.on_close = (slcan_on_close_t)slcan_callback_default;
    co->m_scb.on_listen = (slcan_on_listen_t)slcan_callback_default;
    co->m_scb.on_open = (slcan_on_open_t)slcan_callback_default;
    co->m_scb.on_set_acceptance_filter = (slcan_on_set_acceptance_filter_t)slcan_callback_default;
    co->m_scb.on_set_acceptance_mask = (slcan_on_set_acceptance_mask_t)slcan_callback_default;
    co->m_scb.on_setup_can_btr = (slcan_on_setup_can_btr_t)slcan_callback_default;
    co->m_scb.on_setup_can_std = (slcan_on_setup_can_std_t)slcan_callback_default;
    co->m_scb.on_setup_uart = (slcan_on_setup_uart_t)slcan_callback_default;

    memset(&co->m_scs, 0x0, sizeof(slcan_slave_t));

    if(slcan_slave_init(&co->m_scs, &co->m_sc, &co->m_scb) != 0){
        //printf("Error init slcan slave!\n");
        slcan_close(&co->m_sc);
        slcan_deinit(&co->m_sc);
        return -4;
    }

    return 0;
}

static void deinit_CO_slcan_slave(M_canopen* co)
{
    assert(co != NULL);

    if(co->m_co_ss == NULL || co->m_co_ss->CANmodule == NULL || co->m_co_ss->CANmodule->CANptr == NULL) return;
    CO_CANsetConfigurationMode(co->m_co_ss->CANmodule->CANptr);
}

static void destroy_CO_slcan_slave(M_canopen* co)
{
    assert(co != NULL);

    CO_delete(co->m_co_ss);
    co->m_co_ss = NULL;
}

static void deinit_slcan_slave(M_canopen* co)
{
    assert(co != NULL);

    slcan_slave_deinit(&co->m_scs);
    slcan_close(&co->m_sc);
    slcan_deinit(&co->m_sc);
}


// CANopen.
static int create_CO_slcan_slave(M_canopen* co)
{
    assert(co != NULL);

    CO_t* co_res = CO_new(NULL, NULL);

    if(co_res == NULL) return -1;

    co->m_co_ss = co_res;

    return 0;
}

static CO_ReturnError_t init_CO_slcan_slave(M_canopen* co)
{
    assert(co != NULL);

    CO_ReturnError_t coerr = CO_ERROR_NO;

    CO_driver_CAN_t driver_CAN_ss;
    driver_CAN_ss.driver_name = CO_DRIVER_SLCAN_SLAVE_NAME;
    driver_CAN_ss.CANptr = &co->m_scs;

    coerr = CO_CANinit(co->m_co_ss, &driver_CAN_ss, CANOPEN_BITRATE);
    if(coerr != CO_ERROR_NO) return coerr;

    uint32_t errInfo = 0;

    coerr = CO_CANopenInit(co->m_co_ss,
            NULL, NULL, OD, NULL, CO_CONFIG_NMT, FIRST_HB_TIME_MS, SDO_SERVER_TIMEOUT_MS, SDO_CLIENT_TIMEOUT_MS, SDO_CLIENT_BLOCK_TRANSFER, NODE_ID, &errInfo);

    if(coerr != CO_ERROR_NO){
        //printf("CANopen init fail! (err: %d err_info: %d)\n", (int)coerr, (int)errInfo);
        return coerr;
    }

    coerr = CO_CANopenInitPDO(co->m_co_ss, co->m_co_ss->em, OD, NODE_ID, &errInfo);

    if(coerr != CO_ERROR_NO){
        //printf("CANopen init PDO fail! (err: %d err_info: %d)\n", (int)coerr, (int)errInfo);
        return coerr;
    }

    /* Разрешение работы */
    CO_CANsetNormalMode(co->m_co_ss->CANmodule);

    return CO_ERROR_NO;
}

static int init_CAN_slcan_slave(M_canopen* co)
{
    int res;
    CO_ReturnError_t coerr;

    res = init_CO_driver_slcan_slave(co);
    if(res < 0){
        return -1;
    }

    res = init_slcan_slave(co);
    if(res < 0){
        return -2;
    }

    res = create_CO_slcan_slave(co);
    if(res < 0){
        deinit_slcan_slave(co);
        return -3;
    }

    coerr = init_CO_slcan_slave(co);
    if(coerr != CO_ERROR_NO){
        destroy_CO_slcan_slave(co);
        deinit_slcan_slave(co);
        return -4;
    }

    return 0;
}
#endif



#ifdef CO_DRIVER_XMC4XXX


static int init_CO_driver_xmc4xxx(M_canopen* co)
{
    CO_driver_t* drv = CO_driver();

    if(drv == NULL) return -1;

    CO_driver_id_t drvid = CO_driver_init_xmc4xxx(drv);
    if(drvid == CO_DRIVER_ID_INVALID) return -2;

    return 0;
}

static int init_xmc4xxx(M_canopen* co)
{
    assert(co != NULL);

    co->m_can_xmc4 = can_get(CAN_N);
    if(co->m_can_xmc4 == NULL) return -1;

    co->m_can_node_xmc4 = can_node_get(co->m_can_xmc4, CAN_NODE_N);
    if(co->m_can_node_xmc4 == NULL) return -2;

    return 0;
}

static void deinit_CO_xmc4xxx(M_canopen* co)
{
    assert(co != NULL);

    if(co->m_co_xmc4 == NULL || co->m_co_xmc4->CANmodule == NULL || co->m_co_xmc4->CANmodule->CANptr == NULL) return;
    CO_CANsetConfigurationMode(co->m_co_xmc4->CANmodule->CANptr);
}

static void destroy_CO_xmc4xxx(M_canopen* co)
{
    assert(co != NULL);

    CO_delete(co->m_co_xmc4);
    co->m_co_xmc4 = NULL;
}

static void deinit_xmc4xxx(M_canopen* co)
{
    assert(co != NULL);
}


// CANopen.
static int create_CO_xmc4xxx(M_canopen* co)
{
    assert(co != NULL);

    CO_t* co_res = CO_new(NULL, NULL);

    if(co_res == NULL) return -1;

    co->m_co_xmc4 = co_res;

    return 0;
}

static CO_ReturnError_t init_CO_xmc4xxx(M_canopen* co)
{
    assert(co != NULL);

    CO_ReturnError_t coerr = CO_ERROR_NO;

    CO_driver_CAN_t driver_CAN_xmc4;
    driver_CAN_xmc4.driver_name = CO_DRIVER_XMC4XXX_NAME;
    driver_CAN_xmc4.CANptr = co->m_can_node_xmc4;

    coerr = CO_CANinit(co->m_co_xmc4, &driver_CAN_xmc4, CANOPEN_BITRATE);
    if(coerr != CO_ERROR_NO) return coerr;

    uint32_t errInfo = 0;

    coerr = CO_CANopenInit(co->m_co_xmc4,
            NULL, NULL, OD, NULL, CO_CONFIG_NMT, FIRST_HB_TIME_MS, SDO_SERVER_TIMEOUT_MS, SDO_CLIENT_TIMEOUT_MS, SDO_CLIENT_BLOCK_TRANSFER, NODE_ID, &errInfo);

    if(coerr != CO_ERROR_NO){
        //printf("CANopen init fail! (err: %d err_info: %d)\n", (int)coerr, (int)errInfo);
        return coerr;
    }

    coerr = CO_CANopenInitPDO(co->m_co_xmc4, co->m_co_xmc4->em, OD, NODE_ID, &errInfo);

    if(coerr != CO_ERROR_NO){
        //printf("CANopen init PDO fail! (err: %d err_info: %d)\n", (int)coerr, (int)errInfo);
        return coerr;
    }

    /* Разрешение работы */
    CO_CANsetNormalMode(co->m_co_xmc4->CANmodule);

    return CO_ERROR_NO;
}

static status_t init_CAN_xmc4xxx(M_canopen* co)
{
    int res;
    CO_ReturnError_t coerr;

    res = init_CO_driver_xmc4xxx(co);
    if(res < 0){
        return -1;
    }

    res = init_xmc4xxx(co);
    if(res < 0){
        return -2;
    }

    res = create_CO_xmc4xxx(co);
    if(res < 0){
        deinit_xmc4xxx(co);
        return -3;
    }

    coerr = init_CO_xmc4xxx(co);
    if(coerr != CO_ERROR_NO){
        destroy_CO_xmc4xxx(co);
        deinit_xmc4xxx(co);
        return -4;
    }

    return 0;
}
#endif



METHOD_INIT_IMPL(M_canopen, co)
{
    assert(co != NULL);

    CO_driver_t* drv = CO_driver_init();
    if(drv == NULL){
        co->status = STATUS_ERROR;
        return;
    }

    status_t status = STATUS_NONE;
    size_t co_init_succ_cnt = 0;

#ifdef CO_DRIVER_SLCAN_SLAVE
    status = init_CAN_slcan_slave(co);
    if(status != STATUS_READY) co->status |= STATUS_WARNING;
    else co_init_succ_cnt ++;
#endif

#ifdef CO_DRIVER_XMC4XXX
    status = init_CAN_xmc4xxx(co);
    if(status != STATUS_READY) co->status |= STATUS_WARNING;
    else co_init_succ_cnt ++;
#endif

    if(co_init_succ_cnt == 0){
        co->status = STATUS_ERROR;
        return;
    }

    co->status = STATUS_RUN;
}

METHOD_DEINIT_IMPL(M_canopen, co)
{
    assert(co != NULL);

    if(co->status & STATUS_RUN){
#ifdef CO_DRIVER_SLCAN_SLAVE
        deinit_CO_slcan_slave(co);
        destroy_CO_slcan_slave(co);
        deinit_slcan_slave(co);
#endif
#ifdef CO_DRIVER_XMC4XXX
        deinit_CO_xmc4xxx(co);
        destroy_CO_xmc4xxx(co);
        deinit_xmc4xxx(co);
#endif
    }

}

METHOD_CALC_IMPL(M_canopen, co)
{
    assert(co != NULL);

    if(!(co->status & STATUS_RUN)) return;

    slcan_slave_poll(&co->m_scs);
    CO_CANinterrupt(co->m_co_ss->CANmodule);

    CO_NMT_reset_cmd_t reset_cmd = CO_process(co->m_co_ss, false, NET_TIMER_TICKS_PERIOD_US, NULL);

    if(reset_cmd == CO_RESET_NOT){
        //printf("CO_NMT_NO_COMMAND");
    }else if(reset_cmd == CO_RESET_COMM){
        //printf("CO_RESET_COMM");
    }else if(reset_cmd == CO_RESET_APP){
        //printf("CO_RESET_APP");
    }else if(reset_cmd == CO_RESET_QUIT){
        //printf("CO_RESET_QUIT");
    }
}
