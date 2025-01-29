#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef CAN_CAN_XMC4XXX_H_
#define CAN_CAN_XMC4XXX_H_

#include "cpu.h"
#include "defs/defs.h"
#include "errors/errors.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "gpio/gpio_xmc4xxx.h"


//! Число CAN.
#define CANS_COUNT 1


//! Число нод CAN.
#if defined(CAN_NODE7)
#define CAN_NODES_COUNT 8
#elif defined(CAN_NODE6)
#define CAN_NODES_COUNT 7
#elif defined(CAN_NODE5)
#define CAN_NODES_COUNT 6
#elif defined(CAN_NODE4)
#define CAN_NODES_COUNT 5
#elif defined(CAN_NODE3)
#define CAN_NODES_COUNT 4
#elif defined(CAN_NODE2)
#define CAN_NODES_COUNT 3
#elif defined(CAN_NODE1)
#define CAN_NODES_COUNT 2
#elif defined(CAN_NODE0)
#define CAN_NODES_COUNT 1
#else
#error Unknown nodes count!
#define CAN_NODES_COUNT 0
#endif


//! Частота тактирования блока CAN.
#define CAN_FREQ 60000000


//! Перечисление стандартных битрейтов.
typedef enum _E_Can_Bit_Rate {
    CAN_BIT_RATE_10kbit = 0,
    CAN_BIT_RATE_20kbit = 1,
    CAN_BIT_RATE_50kbit = 2,
    CAN_BIT_RATE_100kbit = 3,
    CAN_BIT_RATE_125kbit = 4,
    CAN_BIT_RATE_250kbit = 5,
    CAN_BIT_RATE_500kbit = 6,
    CAN_BIT_RATE_800kbit = 7,
    CAN_BIT_RATE_1000kbit = 8
} can_bit_rate_t;


//! Битрейт по-умолчанию.
#define CAN_BIT_RATE_DEFAULT CAN_BIT_RATE_125kbit


//! Режим замыкания на себя.
#define CAN_LOOPBACK 0


//! Пытаться отправить только один раз.
#define CAN_SINGLE_TRANSMIT_TRIAL 1


//! Размер данныех сообщения CAN.
#define CAN_DATA_SIZE 8

//! Тип сообщения CAN.
typedef struct _S_Can_Msg {
    uint8_t ide;
    uint32_t id;
    bool rtr;
    uint8_t dlc;
    uint8_t data[CAN_DATA_SIZE];
} can_msg_t;




//! Тип CAN.
typedef struct _S_Can {
    CAN_GLOBAL_TypeDef* can_device; //!< Периферия CAN.
} can_t;


//! Структура инициализации CAN.
typedef struct _S_Can_Init {
    size_t can_n; //!< Номер CAN. На будущее. Должно быть 0.
} can_init_t;



//! Тип события ноды.
typedef enum _E_Can_Node_Event_Type {
    CAN_NODE_EVENT_NONE = 0,
    CAN_NODE_EVENT_MSG_RECV = 1,
    CAN_NODE_EVENT_MSG_SEND = 2,
    CAN_NODE_EVENT_ERROR = 3,
} can_node_event_type_t;

//! Событие приёма сообщения.
typedef struct _S_Can_Node_Event_Msg_Recv {
} can_node_event_msg_recv_t;

//! Событие отправки сообщения.
typedef struct _S_Can_Node_Event_Msg_Send {
} can_node_event_msg_send_t;

//! Событие ошибки.
typedef struct _S_Can_Node_Event_Error {
} can_node_event_error_t;

//! События ноды.
typedef struct _S_Can_Node_Event {
    can_node_event_type_t type;
    union {
        can_node_event_msg_recv_t msg_recv;
        can_node_event_msg_send_t msg_send;
        can_node_event_error_t error;
    };
} can_node_event_t;


//! Декларация типа ноды CAN.
struct _S_Can_Node;

//! Коллбэк событий ноды.
typedef void (*can_node_event_callback_t)(struct _S_Can_Node* can_node, can_node_event_t* event);


//! Тип ноды CAN.
typedef struct _S_Can_Node {
    can_t* can; //!< CAN.
    CAN_NODE_TypeDef* node_device; //!< CAN Node.
    size_t node_n; //!< Номер ноды.
    can_node_event_callback_t callback; //!< Коллбэк событий.
} can_node_t;


//! Структура инициализации ноды CAN.
typedef struct _S_Can_Node_Init {
    can_t* can; //!< CAN.
    size_t can_node_n; //!< Номер ноды.
    can_bit_rate_t bit_rate; //!< Битрейт.
    bool loopback; //!< Замыкание на себя.
    bool analyzer; //!< Анализ трафика.
    can_node_event_callback_t callback; //!< Коллбэк событий.
    uint8_t sel_rx; //!< Селектор номера входа CAN ноды.
    GPIO_t* gpio_tx; //!< Порт TX.
    gpio_pin_t pin_tx; //!< Пин TX.
    gpio_conf_t conf_tx; //!< Конфигурация TX.
    gpio_pad_driver_t pad_driver_tx; //!< Выходной драйвер TX.
    GPIO_t* gpio_rx; //!< Порт RX.
    gpio_pin_t pin_rx; //!< Пин RX.
    gpio_conf_t conf_rx; //!< Конфигурация RX.
} can_node_init_t;



//! Инициализирует CAN.
EXTERN can_t* can_init(can_init_t* is);

//! Запрещает модуль CAN.
EXTERN void can_disable(can_t* can);

//! Инициализирует CAN.
EXTERN can_node_t* can_node_init(can_node_init_t* is);

//! Устанавливает режим конфигурации.
EXTERN void can_node_set_configuration_mode(can_node_t* can_node);

//! Устанавливает битрейт.
EXTERN err_t can_node_set_bitrate(can_node_t* can_node, can_bit_rate_t bit_rate);

//! Устанавливает нормальный режим.
EXTERN void can_node_set_normal_mode(can_node_t* can_node);

//! Инициализирует буфер приёма с заданным индексом.
EXTERN err_t can_init_rx_buffer(can_node_t* can_node, size_t index, uint16_t ident, uint16_t mask, bool rtr);

//! Инициализирует буфер передачи с заданным индексом.
EXTERN err_t can_init_tx_buffer(can_node_t* can_node, size_t index, uint16_t ident, bool rtr, uint8_t noOfBytes);

//! Отправляет сообщение через буфер с указанным индексом.
EXTERN err_t can_send_msg(can_node_t* can_node, size_t index, const can_msg_t* msg);

//! Принимает сообщение из буфера с указанным индексом.
EXTERN err_t can_recv_msg(can_node_t* can_node, size_t index, can_msg_t* msg);

#endif /* CAN_CAN_XMC4XXX_H_ */

#endif
