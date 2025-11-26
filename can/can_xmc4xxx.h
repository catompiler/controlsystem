#include "port.h"

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



//! Число MO.
#if defined(CAN_MO)
#define CAN_MO_COUNT (sizeof(CAN_MO->MO)/sizeof(CAN_MO->MO[0]))
#elif defined(CAN_MO63)
#define CAN_MO_COUNT 64
#else
#error Unknown CAN MOs count!
#endif



//! Частота тактирования блока CAN.
#if defined(PORT_XMC4500)
    #define CAN_FREQ 60000000
#elif defined(PORT_XMC4700)
    #define CAN_FREQ 72000000
#endif


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
#define CAN_SINGLE_TRANSMIT_TRIAL 0


//! Размер данныех сообщения CAN.
#define CAN_DATA_SIZE 8

//! Тип сообщения CAN.
typedef struct _S_Can_Msg {
    uint32_t id; //!< Идентификатор.
    uint8_t ide; //!< Флаг расширенного идентификатора.
    bool rtr; //!< Флаг RTR.
    uint8_t dlc; //!< Число байт данных.
    uint8_t data[CAN_DATA_SIZE]; //!< Данные.
} can_msg_t;


//! Тип CAN.
typedef struct _S_Can {
    CAN_GLOBAL_TypeDef* const can_device; //!< Периферия CAN.
} can_t;


//! Структура инициализации CAN.
typedef struct _S_Can_Init {
} can_init_t;


//! Перечисление ошибок CAN.
typedef enum _E_Can_Error {
    CAN_ERROR_NONE  = 0b000,
    CAN_ERROR_STUFF = 0b001,
    CAN_ERROR_FORM  = 0b010,
    CAN_ERROR_ACK   = 0b011,
    CAN_ERROR_BIT1  = 0b100,
    CAN_ERROR_BIT0  = 0b101,
    CAN_ERROR_CRC   = 0b110,
    CAN_ERROR_CPU   = 0b111,
} can_error_t;


//! Тип события ноды.
typedef enum _E_Can_Node_Event_Type {
    CAN_NODE_EVENT_UNKNOWN = -1,//!< Неизвестное событие.
    CAN_NODE_EVENT_NONE = 0,    //!< Нет события.
    CAN_NODE_EVENT_MSG_RECV = 1,//!< Сообщение принято.
    CAN_NODE_EVENT_MSG_SEND = 2,//!< Сообщение отправлено.
    CAN_NODE_EVENT_ERROR = 3,   //!< Ошибка.
    CAN_NODE_EVENT_ALERT = 4,   //!< Тревога.
} can_node_event_type_t;

//! Событие приёма сообщения.
typedef struct _S_Can_Node_Event_Msg_Recv {
    size_t mo_index; //!< Индекс буфера.
    bool overflow; //!< Флаг переполнения.
} can_node_event_msg_recv_t;

//! Событие отправки сообщения.
typedef struct _S_Can_Node_Event_Msg_Send {
    size_t mo_index; //!< Индекс объекта сообщений.
} can_node_event_msg_send_t;

//! Событие ошибки.
typedef struct _S_Can_Node_Event_Error {
    can_error_t error; //!< Значение ошибки.
} can_node_event_error_t;

//! Событие тревоги.
typedef struct _S_Can_Node_Event_Alert {
    bool bus_off; //!< Шина отключена.
    bool warning_limit_reached; //!< Превышен лимит количества ошибок уровня предупреждения.
    bool init_set_by_hw; //!< Шина переведена аппаратурой в режим инициализации.
    bool internal; //!< Внутренняя ошибка (Например, ошибка работы со списками).
} can_node_event_alert_t;

//! События ноды.
typedef struct _S_Can_Node_Event {
    can_node_event_type_t type; //!< Тип события.
    union {
        can_node_event_msg_recv_t msg_recv;//!< Сообщение принято.
        can_node_event_msg_send_t msg_send;//!< Сообщение отправлено.
        can_node_event_error_t error;//!< Ошибка.
        can_node_event_alert_t alert;//!< Тревога.
    };
} can_node_event_t;


//! Декларация типа ноды CAN.
struct _S_Can_Node;

//! Коллбэк событий ноды.
typedef void (*can_node_event_callback_t)(struct _S_Can_Node* can_node, can_node_event_t* event);


//! Тип ноды CAN.
typedef struct _S_Can_Node {
    can_t* can; //!< CAN.
    CAN_NODE_TypeDef* const node_device; //!< CAN Node.
    size_t node_n; //!< Номер ноды.
    can_node_event_callback_t callback; //!< Коллбэк событий.
    uint32_t frames_counter_hi; //!< Верхняя часть счётчика фреймов.
    void* user_data; //!< Данные пользователя.
} can_node_t;


//! Структура инициализации ноды CAN.
typedef struct _S_Can_Node_Init {
    can_bit_rate_t bit_rate; //!< Битрейт.
    bool loopback; //!< Замыкание на себя.
    bool analyzer; //!< Анализ трафика.
    can_node_event_callback_t callback; //!< Коллбэк событий.
    void* user_data; //!< Данные пользователя.
    uint8_t sel_rx; //!< Селектор номера входа CAN ноды.
    GPIO_t* gpio_tx; //!< Порт TX.
    gpio_pin_t pin_tx_msk; //!< Пин TX.
    gpio_conf_t conf_tx; //!< Конфигурация TX.
    gpio_pad_driver_t pad_driver_tx; //!< Выходной драйвер TX.
    GPIO_t* gpio_rx; //!< Порт RX.
    gpio_pin_t pin_rx_msk; //!< Пин RX.
    gpio_conf_t conf_rx; //!< Конфигурация RX.
} can_node_init_t;


//! Тип индекса(номера) буфера.
typedef uint32_t can_mo_index_t;

//! Невалидный индекс.
#define CAN_MO_INVALID_INDEX (0xffffffff)



/**
 * Получает модуль CAN с заданным номером.
 * @param can_n Номер модуля.
 * @return Модуль CAN.
 */
EXTERN can_t* can_get(size_t can_n);

/**
 * Инициализирует CAN.
 * @param can Модуль CAN.
 * @param is Структура инициализации. Может быть NULL.
 * @return Код ошибки.
 */
EXTERN err_t can_init(can_t* can_node, can_init_t* is);

/**
 * Запрещает модуль CAN.
 * @param can Модуль CAN.
 */
EXTERN void can_disable(can_t* can);

/**
 * Получает ноду CAN модуля с заданным номером.
 * @param can Модуль CAN.
 * @param node_n Номер ноды.
 * @return Нода CAN.
 */
EXTERN can_node_t* can_node_get(can_t* can, size_t node_n);

/**
 * Инициализирует ноду CAN.
 * @param can_node Нода CAN.
 * @param is Структура инициализации.
 * @return Код ошибки.
 */
EXTERN err_t can_node_init(can_node_t* node, can_node_init_t* is);

/**
 * Получает флаг режима инициализации.
 * @param can_node Нода CAN.
 * @return Флаг режима инициализации.
 */
EXTERN bool can_node_init_mode(can_node_t* can_node);

/**
 * Устанавливает режим инициализации.
 * @param can_node Нода CAN.
 */
EXTERN void can_node_set_init_mode(can_node_t* can_node);

/**
 * Устанавливает режим работы.
 * @param can_node Нода CAN.
 */
EXTERN void can_node_set_run_mode(can_node_t* can_node);

/**
 * Получает флаг режима конфигурации.
 * @param can_node Нода CAN.
 * @return Флаг режима конфигурации.
 */
EXTERN bool can_node_configuration_mode(can_node_t* can_node);

/**
 * Устанавливает режим конфигурации.
 * @param can_node Нода CAN.
 */
EXTERN void can_node_set_configuration_mode(can_node_t* can_node);

/**
 * Устанавливает битрейт.
 * @param can_node Нода CAN.
 * @param bit_rate Битрейт.
 * @return Код ошибки.
 */
EXTERN err_t can_node_set_bitrate(can_node_t* can_node, can_bit_rate_t bit_rate);

/**
 * Устанавливает нормальный режим.
 * @param can_node Нода CAN.
 */
EXTERN void can_node_set_normal_mode(can_node_t* can_node);

/**
 * Получает данные пользователя.
 * @param can_node
 * @return Данные пользователя.
 */
EXTERN void* can_node_user_data(can_node_t* can_node);

/**
 * Устанавливает данные пользователя.
 * @param can_node
 * @param user_data Данные пользователя.
 */
EXTERN void can_node_set_user_data(can_node_t* can_node, void* user_data);

/**
 * Получает статус отключения шины.
 * @param can_node Нода CAN.
 * @return Статус отключения шины.
 */
EXTERN bool can_node_status_bus_off(can_node_t* can_node);

/**
 * Получает статус превышения уровня предупреждений.
 * @param can_node Нода CAN.
 * @return Статус превышения уровня предупреждений.
 */
EXTERN bool can_node_status_warning_limit_reached(can_node_t* can_node);

/**
 * Получает статус установки режима инициализации аппаратурой.
 * @param can_node Нода CAN.
 * @return Статус установки режима инициализации аппаратурой.
 */
EXTERN bool can_node_status_init_set_by_hw(can_node_t* can_node);

/**
 * Получает статус внутренней ошибки.
 * @param can_node Нода CAN.
 * @return Статус внутренней ошибки.
 */
EXTERN bool can_node_status_internal(can_node_t* can_node);

/**
 * Получает последнюю ошибку.
 * @param can_node Нода CAN.
 * @return Последняя ошибка.
 */
EXTERN can_error_t can_node_last_error(can_node_t* can_node);

/**
 * Получает уровень предупреждений.
 * @param can_node Нода CAN.
 * @return Уровень предупреждений.
 */
EXTERN uint8_t can_node_warning_level(can_node_t* can_node);

/**
 * Устанавливает уровень предупреждений.
 * @param can_node Нода CAN.
 * @param level Уровень предупреждений.
 */
EXTERN void can_node_set_warning_level(can_node_t* can_node, uint8_t level);

/**
 * Получает счётчик ошибок передачи.
 * @param can_node Нода CAN.
 * @return Счётчик ошибок передачи.
 */
EXTERN uint8_t can_node_transmit_error_counter(can_node_t* can_node);

/**
 * Получает счётчик ошибок приёма.
 * @param can_node Нода CAN.
 * @return Счётчик ошибок приёма.
 */
EXTERN uint8_t can_node_receive_error_counter(can_node_t* can_node);

/**
 * Получает счётчик принятых и переданных сообщений.
 * @param can_node Нода CAN.
 * @return Счётчик принятых и переданных сообщений.
 */
EXTERN uint64_t can_node_rxtx_count(can_node_t* can_node);

/**
 * Выделяет буфер приёма с заданным индексом.
 * @param can_node Нода CAN.
 * @param fifo_len Длина FIFO.
 * @return Номер объекта сообщений.
 */
EXTERN can_mo_index_t can_node_alloc_buffer(can_node_t* can_node, size_t fifo_len);

/**
 * Выделяет буфер приёма с заданным индексом.
 * @param can_node Нода CAN.
 * @param mo_index Номер объекта сообщений.
 */
EXTERN void can_node_free_buffer(can_node_t* can_node, can_mo_index_t mo_index);

/**
 * Выделяет и инициализирует буфер приёма с заданным индексом.
 * @param can_node Нода CAN.
 * @param fifo_len Длина FIFO.
 * @param ident Идентификатор.
 * @param mask Маска.
 * @param rtr Флаг RTR.
 * @return Номер объекта сообщений.
 */
EXTERN can_mo_index_t can_node_alloc_init_rx_buffer(can_node_t* can_node, size_t fifo_len, uint16_t ident, uint16_t mask, bool rtr);

/**
 * Выделяет и инициализирует буфер передачи с заданным индексом.
 * @param can_node Нода CAN.
 * @param fifo_len Длина FIFO.
 * @param ident Идентификатор.
 * @param rtr Флаг RTR.
 * @param noOfBytes Количество байт данных.
 * @return Номер объекта сообщений.
 */
EXTERN can_mo_index_t can_node_alloc_init_tx_buffer(can_node_t* can_node, size_t fifo_len, uint16_t ident, bool rtr, uint8_t noOfBytes);

/**
 * Инициализирует буфер приёма с заданным индексом.
 * @param can_node Нода CAN.
 * @param mo_index Номер объекта сообщений.
 * @param ident Идентификатор.
 * @param mask Маска.
 * @param rtr Флаг RTR.
 * @return Код ошибки.
 */
EXTERN err_t can_node_init_rx_buffer(can_node_t* can_node, can_mo_index_t mo_index, uint16_t ident, uint16_t mask, bool rtr);

/**
 * Инициализирует буфер передачи с заданным индексом.
 * @param can_node Нода CAN.
 * @param mo_index Номер объекта сообщений.
 * @param ident Идентификатор.
 * @param rtr Флаг RTR.
 * @param noOfBytes Количество байт данных.
 * @return Код ошибки.
 */
EXTERN err_t can_node_init_tx_buffer(can_node_t* can_node, can_mo_index_t mo_index, uint16_t ident, bool rtr, uint8_t noOfBytes);

/**
 * Отправляет сообщение через буфер с указанным индексом.
 * @param can_node Нода CAN.
 * @param mo_index Номер объекта сообщений.
 * @param msg Сообщение.
 * @return Код ошибки.
 */
EXTERN err_t can_node_send_msg(can_node_t* can_node, can_mo_index_t mo_index, const can_msg_t* msg);

/**
 * Принимает сообщение из буфера с указанным индексом.
 * @param can_node Нода CAN.
 * @param mo_index Номер объекта сообщений.
 * @param msg Сообщение.
 * @return Код ошибки.
 */
EXTERN err_t can_node_recv_msg(can_node_t* can_node, can_mo_index_t mo_index, can_msg_t* msg);

#endif /* CAN_CAN_XMC4XXX_H_ */

#endif
