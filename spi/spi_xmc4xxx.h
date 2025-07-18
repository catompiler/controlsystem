#include "port.h"

#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

/**
 * @file spi.h
 * Библиотека для работы с SPI.
 */

#ifndef SPI_XMC4XXX_H
#define	SPI_XMC4XXX_H

#include "cpu.h"
#include "dma/dma_xmc4xxx.h"
#include <stddef.h>
#include <stdbool.h>
#include "errors/errors.h"
#include "defs/defs.h"

//! Ошибки SPI.
#define E_SPI (E_USER + 10)
//! Ошибка при некорректном сообщении.
#define E_SPI_INVALID_MESSAGE (E_SPI)


//! Использовать ли FIFO.
#define SPI_BUS_USE_FIFO 0

//! Имеется ли аппаратный селектор.
#define SPI_BUS_HW_SEL 1


/**
 * Тип функции обратного вызова.
 * Вызывается при окончании приёма/передачи
 * даннх, или при возникновении ошибки.
 * @return true, если событие обработано, иначе false.
 */
typedef bool (*spi_callback_t)(void* user_data);

//! Декларация структуры сообщения ниже.
struct _SPI_Message;
/**
 * Тип функции обратного вызова для сообщения.
 * Вызывается при успешном окончании передачи сообщения.
 */
typedef void (*spi_message_callback_t)(struct _SPI_Message*);

/**
 * Тип идентификатора передачи.
 */
typedef uint8_t spi_transfer_id_t;

//! Идентификатор передачи по умолчанию.
#define SPI_BUS_DEFAULT_TRANSFER_ID 0

//! Тип формата данных карда шины spi.
typedef enum _spi_data_frame_format {
    SPI_DATA_FRAME_FORMAT_8BIT = 0, //!< 8 бит.
    SPI_DATA_FRAME_FORMAT_16BIT = 1 //!< 16 бит.
} spi_data_frame_format_t;

//! Тип формата карда шины spi.
typedef enum _spi_frame_format {
    SPI_FRAME_FORMAT_MSBFIRST = 0, //!< Сперва наиболее значащий бит.
    SPI_FRAME_FORMAT_LSBFIRST = 1 //!< Сперва наименее значащий бит.
} spi_frame_format_t;

//! Тип статуса шины spi.
typedef enum _spi_status {
    SPI_STATUS_IDLE = 0,//!< Бездействие.
    SPI_STATUS_TRANSFERING,//!< Обмен данными.
    SPI_STATUS_TRANSFERED,//!< Обмен данными завершён.
    SPI_STATUS_ERROR//!< Ошибка.
} spi_status_t;

//! Тип ошибки spi.
typedef enum _spi_error {
    SPI_NO_ERROR                = 0,//!< Нет ошибки.
    SPI_ERROR_MASTER_MODE_FAULT = 1,//!< Ошибка приоритета, появился новый мастер.
    SPI_ERROR_OVERRUN           = 2,//!< Слишком быстрая пересылка данных.
    //SPI_ERROR_CRC               = 4,//!< Ошибка CRC.
    SPI_ERROR_DMA               = 8//!< Ошибка DMA.
} spi_error_t;

//! Тип ошибок SPI.
typedef uint8_t spi_errors_t;

//! Направление передачи spi.
typedef enum _spi_direction {
    SPI_READ = 0,//!< Чтение.
    SPI_WRITE,//!< Запись.
    SPI_READ_WRITE,//!< Чтение и запись.
} spi_direction_t;

//! Тип сообщения spi.
typedef struct _SPI_Message {
    spi_direction_t direction;//!< Режим передачи.
    const void* tx_data;//!< Данные для передачи.
    void* rx_data;//!< Данные для приёма.
    size_t data_size;//!< Размер данных.
    spi_message_callback_t callback;//!< Функция обратного вызова.
    void* sender_data;//!< Данные отправителя сообщения.
} spi_message_t;

//! Структуры шины spi.
typedef struct _SPI_Bus {
    // DMA.
    dma_channel_t* dma_rx_channel;
    size_t dma_rx_ch_n;//!< Номер канала DMA для приёма.
    size_t dma_rx_line_n; //!< Номер линии DMA для приёма.
    dma_req_line_source_t dma_rx_line_req_n; //!< Номер источника запроса DMA для приёма.
    size_t dma_rx_sr_n; //!< Номер SR канала DMA для приёма.
    dma_channel_t* dma_tx_channel;
    size_t dma_tx_ch_n;//!< Номер канала DMA для передачи.
    size_t dma_tx_line_n; //!< Номер линии DMA для передачи.
    dma_req_line_source_t dma_tx_line_req_n; //!< Номер источника запроса DMA для передачи.
    size_t dma_tx_sr_n; //!< Номер SR канала DMA для передачи.
    // SPI.
    USIC_CH_TypeDef* spi_device;//!< Периферия.
    spi_status_t status;//!< Статус шины.
    spi_errors_t errors;//!< Ошибка шины.
    spi_callback_t callback;//!< Функция обратного вызова.
    void* user_data; //!< Данные пользователя.
    spi_transfer_id_t transfer_id;//!< Идентификатор передачи.
    spi_message_t* messages;//!< Массив сообщений.
    size_t messages_count;//!< Число сообщений.
    size_t message_index;//!< Индекс текущего сообщения.
    uint8_t state;//!< Состояние передачи.
    bool dma_rx_locked;//!< Заблокирован канал получения.
    bool dma_tx_locked;//!< Заблокирован канал передачи.
    uint16_t tx_default; //!< Передаваемые данные при приёме.
} spi_bus_t;

//! Структура инициализации шины spi.
typedef struct _SPI_Bus_Init{
    USIC_CH_TypeDef* spi_device;//!< Периферия.
    size_t dma_rx_ch_n;//!< Номер канала DMA для приёма.
    size_t dma_rx_line_n; //!< Номер линии DMA для приёма.
    dma_req_line_source_t dma_rx_line_req_n; //!< Номер источника запроса DMA для приёма.
    size_t dma_rx_sr_n; //!< Номер SR канала DMA для приёма.
    size_t dma_tx_ch_n;//!< Номер канала DMA для передачи.
    size_t dma_tx_line_n; //!< Номер линии DMA для передачи.
    dma_req_line_source_t dma_tx_line_req_n; //!< Номер источника запроса DMA для передачи.
    size_t dma_tx_sr_n; //!< Номер SR канала DMA для передачи.
} spi_bus_init_t;

/**
 * Инициализирует шину spi.
 * @param spi Шина spi.
 * @param device Периферия spi.
 * @return Код ошибки.
 */
EXTERN err_t spi_bus_init(spi_bus_t* spi, spi_bus_init_t* init);

/**
 * Обработчик прерывания spi.
 * @param spi Шина spi.
 */
EXTERN void spi_bus_irq_handler(spi_bus_t* spi);

/**
 * Обработчик прерывания канала передачи DMA.
 * @param spi Шина spi.
 * @return true, если канал использовался шиной spi, иначе false.
 */
EXTERN bool spi_bus_dma_rx_channel_irq_handler(spi_bus_t* spi);

/**
 * Обработчик прерывания канала приёма DMA.
 * @param spi Шина spi.
 * @return true, если канал использовался шиной spi, иначе false.
 */
EXTERN bool spi_bus_dma_tx_channel_irq_handler(spi_bus_t* spi);

#if defined(SPI_BUS_HW_SEL) && SPI_BUS_HW_SEL == 1
/**
 * Устанавливает аппаратный nCS.
 * @param spi Шина spi.
 * @param sel Маска аппаратных CS, 0 - снятия CS.
 * @return Флаг установки аппаратных CS.
 */
EXTERN bool spi_bus_set_hw_sel(spi_bus_t* spi, uint32_t sel);
#endif

/**
 * Получает флаг занятости шины spi.
 * @param spi Шина spi.
 * @return Флаг занятости шины spi.
 */
EXTERN bool spi_bus_busy(spi_bus_t* spi);

/**
 * Ждёт завершения текущей операции spi.
 * @param spi Шина spi.
 */
EXTERN void spi_bus_wait(spi_bus_t* spi);

/**
 * Получает флаг включения шины.
 * @param spi Шина spi.
 * @return Флаг включения шины.
 */
EXTERN bool spi_bus_enabled(spi_bus_t* spi);

/**
 * Устанавливает флаг включения шины.
 * @param spi Шина spi.
 * @param enabled Флаг включения шины.
 * @return true в случае успеха, иначе false (шина занята).
 */
EXTERN bool spi_bus_set_enabled(spi_bus_t* spi, bool enabled);

/**
 * Получает функцию обратного вызова.
 * @param spi Шина spi.
 * @return Функция обратного вызова.
 */
EXTERN spi_callback_t spi_bus_callback(spi_bus_t* spi);

/**
 * Устанавливает функцию обратного вызова.
 * @param spi Шина spi.
 * @param callback Функция обратного вызова.
 */
EXTERN void spi_bus_set_callback(spi_bus_t* spi, spi_callback_t callback);

/**
 * Получает данные пользователя.
 * @param spi Шина spi.
 * @return Данные пользователя.
 */
EXTERN void* spi_bus_user_data(spi_bus_t* spi);

/**
 * Устанавливает данные пользователя.
 * @param spi Шина spi.
 * @param user_data Данные пользователя.
 */
EXTERN void spi_bus_set_user_data(spi_bus_t* spi, void* user_data);

/**
 * Получает идентификатор передачи.
 * @param spi Шина spi.
 * @return Идентификатор передачи.
 */
EXTERN spi_transfer_id_t spi_bus_transfer_id(spi_bus_t* spi);

/**
 * Устанавливает идентификатор передачи.
 * @param spi Шина spi.
 * @param id Идентификатор передачи.
 * @return true, если идентификатор передачи установлен, иначе false (шина занята).
 */
EXTERN bool spi_bus_set_transfer_id(spi_bus_t* spi, spi_transfer_id_t id);

/**
 * Устанавливает значение передаваемых данных по-умолчанию.
 * @param spi Шина SPI.
 * @param value Значение передаваемых данных по-умолчанию.
 */
EXTERN void spi_bus_set_tx_default_value(spi_bus_t* spi, uint16_t value);

/**
 * Получает флаг включения вычисления
 * контрольной суммы CRC и её приёма / передачи.
 * @param spi Шина spi.
 * @return Флаг включения вычисления CRC.
 */
EXTERN bool spi_bus_crc_enabled(spi_bus_t* spi);

/**
 * Устанавливает флаг включения вычисления
 * контрольной суммы CRC и её приёма / передачи.
 * Шина SPI должна быть отключена.
 * @param spi Шина spi.
 * @param enabled Флаг включения вычисления CRC.
 * @return true в случае успеха, иначе false (шина занята).
 */
EXTERN bool spi_bus_set_crc_enabled(spi_bus_t* spi, bool enabled);

/**
 * Получает полином контрольной суммы CRC.
 * @param spi Шина spi.
 * @return Полином контрольной суммы CRC.
 */
EXTERN uint16_t spi_bus_crc_polynomial(spi_bus_t* spi);

/**
 * Устанавливает полином контрольной суммы CRC.
 * @param spi Шина spi.
 * @param polynomial Полином контрольной суммы CRC.
 * @return true в случае успеха, иначе false (шина занята).
 */
EXTERN bool spi_bus_set_crc_polynomial(spi_bus_t* spi, uint16_t polynomial);

/**
 * Получает контрольную сумму переданных данных.
 * @param spi Шина SPI.
 * @return Контрольная сумма переданных данных.
 */
EXTERN uint16_t spi_bus_tx_crc(spi_bus_t* spi);

/**
 * Получает контрольную сумму полученных данных.
 * @param spi Шина SPI.
 * @return Контрольная сумма полученных данных.
 */
EXTERN uint16_t spi_bus_rx_crc(spi_bus_t* spi);

/**
 * Сбрасывает контрольные суммы.
 * Шина SPI должна быть отключена.
 * @param spi Шина SPI.
 * @return true в случае успеха, иначе false (шина занята).
 */
EXTERN bool spi_bus_reset_crc(spi_bus_t* spi);

/**
 * Получает формат карда данных.
 * @param spi Шина SPI.
 * @return Формат кадра данных.
 */
EXTERN spi_data_frame_format_t spi_bus_data_frame_format(spi_bus_t* spi);

/**
 * Устанавливает формат кадра данных.
 * @param spi Шина SPI.
 * @param format Формат кадра данных.
 * @return Флаг установки формата кадра данных.
 */
EXTERN bool spi_bus_set_data_frame_format(spi_bus_t* spi, spi_data_frame_format_t format);

/**
 * Получает формат карда данных.
 * @param spi Шина SPI.
 * @return Формат кадра данных.
 */
EXTERN spi_frame_format_t spi_bus_frame_format(spi_bus_t* spi);

/**
 * Устанавливает формат кадра данных.
 * @param spi Шина SPI.
 * @param format Формат кадра данных.
 * @return Флаг установки формата кадра данных.
 */
EXTERN bool spi_bus_set_frame_format(spi_bus_t* spi, spi_frame_format_t format);

/**
 * Получает состояние шины spi.
 * @param spi Шина spi.
 * @return Состояние шины spi.
 */
EXTERN spi_status_t spi_bus_status(spi_bus_t* spi);

/**
 * Получает ошибку шины spi.
 * @param spi Шина spi.
 * @return Ошибку шины spi.
 */
EXTERN spi_errors_t spi_bus_errors(spi_bus_t* spi);

/**
 * Инициализирует сообщение.
 * Неиспользуемые буфера должны быть NULL.
 * @param message Сообщение.
 * @param direction Направление передачи.
 * @param tx_data Данные для передачи.
 * @param rx_data Буфер для приёма данных.
 * @param data_size Размер буфера для приёма данных.
 * @return Код ошибки.
 */
EXTERN err_t spi_message_init(spi_message_t* message, spi_direction_t direction, const void* tx_data, void* rx_data, size_t data_size);

/**
 * Инициализирует сообщение.
 * Не проверяет ничего.
 * Для критичных к времени мест.
 * @param message Сообщение.
 * @param direction Направление передачи.
 * @param tx_data Данные для передачи.
 * @param rx_data Буфер для приёма данных.
 * @param data_size Размер буфера для приёма данных.
 */
ALWAYS_INLINE static void spi_message_setup(spi_message_t* message, spi_direction_t direction, const void* tx_data, void* rx_data, size_t data_size)
{
    message->direction = direction;
    message->tx_data = tx_data;
    message->rx_data = rx_data;
    message->data_size = data_size;
    message->sender_data = NULL;
    message->callback = NULL;
}

/**
 * Получает функцию обратного вызова сообщения.
 * @param message Сообщение.
 */
ALWAYS_INLINE static spi_message_callback_t spi_message_callback(spi_message_t* message)
{
    return message->callback;
}

/**
 * Устанавливает функцию обратного вызова сообщения.
 * @param message Сообщение.
 * @param callback Функция обратного вызова.
 */
ALWAYS_INLINE static void spi_message_set_callback(spi_message_t* message, spi_message_callback_t callback)
{
    message->callback = callback;
}

/**
 * Получает данные отправителя.
 * @param message Сообщение.
 */
ALWAYS_INLINE static void* spi_message_sender_data(spi_message_t* message)
{
    return message->sender_data;
}

/**
 * Устанавливает данные отправителя.
 * @param message Сообщение.
 * @param sender_data Данные отправителя.
 */
ALWAYS_INLINE static void spi_message_set_sender_data(spi_message_t* message, void* sender_data)
{
    message->sender_data = sender_data;
}

/**
 * Обменивается сообщениями по шине SPI.
 * @param spi Шина SPI.
 * @param messages Сообщения.
 * @param messages_count Число сообщений.
 * @return Код ошибки.
 */
EXTERN err_t spi_bus_transfer(spi_bus_t* spi, spi_message_t* messages, size_t messages_count);

/**
 * Обменивается данными по шине SPI.
 * @param spi Шина SPI.
 * @param tx_data Данные для передачи.
 * @param rx_data Буфер для приёма, может быть NULL.
 * @return Код ошибки.
 */
EXTERN err_t spi_bus_transmit(spi_bus_t* spi, uint16_t tx_data, uint16_t* rx_data);

#endif	/* SPI_XMC4XXX_H */

#endif
