#ifndef EVENT_LOG_H
#define EVENT_LOG_H

#include "module/base.h"
#include <stdbool.h>
#include "reg/reg.h"
#include "defs/defs.h"
#include "storage/storage.h"


//! Перечисление возможных бит управления.
enum _E_Event_Log_Control {
    EVENT_LOG_CONTROL_NONE = CONTROL_NONE,
    EVENT_LOG_CONTROL_RESET = CONTROL_RESET,
    EVENT_LOG_CONTROL_REFRESH = (CONTROL_USER << 0),
    EVENT_LOG_CONTROL_WRITE = (CONTROL_USER << 1),
    EVENT_LOG_CONTROL_READ_EVENT = (CONTROL_USER << 2),
    EVENT_LOG_CONTROL_READ_OSC = (CONTROL_USER << 3),
};

//! Перечисление возможных бит статуса.
enum _E_Event_Log_Status {
    EVENT_LOG_STATUS_NONE = STATUS_NONE,
    EVENT_LOG_STATUS_READY = STATUS_READY,
    EVENT_LOG_STATUS_RUN = STATUS_RUN,
    EVENT_LOG_STATUS_ERROR = STATUS_ERROR,
};


//! Идентификатор заголовка.
#define EVENT_MAGIC 0x544e5645


//! Структура заголовка событии.
typedef struct PACKED _S_Event_Header {
    uint32_t magic; //!< Идентификатор заголовка.
    uint32_t index; //!< Индекс события.
    uint8_t type; //!< Тип события.
    uint8_t reserved0[3]; //!< Зарезервировано.
    uint16_t crc; //!< Контрольная сумма.
} event_header_t;

//! Размер заголовка события.
#define EVENT_HEADER_SIZE sizeof(event_header_t)

static_assert(EVENT_HEADER_SIZE == 14, "event_header_t invalid size!");



//! Перечисление типов события.
typedef enum _E_Event_Type {
    EVENT_TYPE_NONE = 0,
    EVENT_TYPE_INFO = 1,
    EVENT_TYPE_WARNING = 2,
    EVENT_TYPE_ERROR = 3,
} event_type_t;


//! Структура информации о событии.
typedef struct PACKED _S_Event_Info {
    uint32_t time; //!< Время события.
    uint32_t error0; //!< Слово ошибки 0.
    uint32_t error1; //!< Слово ошибки 1.
    uint32_t error2; //!< Слово ошибки 2.
    uint32_t reg_error0; //!< Регистр ошибки 0.
    uint32_t reg_error1; //!< Регистр ошибки 1.
    uint32_t reg_error2; //!< Регистр ошибки 2.
    uint32_t warning0; //!< Слово предупреждения 0.
    uint32_t warning1; //!< Слово предупреждения 1.
    uint32_t warning2; //!< Слово предупреждения 2.
    uint32_t reg_warning0; //!< Регистр предупреждения 0.
    uint32_t reg_warning1; //!< Регистр предупреждения 1.
    uint32_t reg_warning2; //!< Регистр предупреждения 2.
    uint32_t din; //!< Состояния цифровых входов.
    uint32_t dout; //!< Состояния цифровых выходов.
    uint16_t crc; //!< Контрольная сумма.
} event_info_t;

//! Размер информации о событии.
#define EVENT_INFO_SIZE sizeof(event_info_t)

static_assert(EVENT_INFO_SIZE == 62, "event_info_t invalid size!");



//! Структура информации осциллограммы события.
typedef struct PACKED _S_Event_Osc_Info {
    uint32_t Fs; //!< Частота дискретизации.
    uint8_t channels_count; //!< Число каналов.
    uint8_t reserved0[3]; //!< Зарезервировано.
    uint16_t samples_count; //!< Число семплов.
    uint16_t event_sample; //!< Семпл возникновения события.
    uint16_t crc; //!< Контрольная сумма.
} event_osc_info_t;

//!< Размер структуры информации осциллограммы.
#define EVENT_OSC_INFO_SIZE sizeof(event_osc_info_t)

static_assert(EVENT_OSC_INFO_SIZE == (4 + 1 + 3 + 2 + 2 + 2), "event_osc_info_t invalid size!");



//! Структура информации канала осциллограммы.
typedef struct PACKED _S_Event_Osc_Channel_Info {
    reg_id_t reg_id; //!< Идентификатор осциллографируемого регистра.
    iql_t offset; //!< Смещение.
    iql_t gain; //!< Усиление.
    uint16_t crc; //!< Контрольная сумма.
} event_osc_channel_info_t;

//!< Размер структуры информации канала осциллограммы.
#define EVENT_OSC_CHANNEL_INFO_SIZE sizeof(event_osc_channel_info_t)

static_assert(EVENT_OSC_CHANNEL_INFO_SIZE == (4 + 4 + 4 + 2), "event_osc_channel_info_t invalid size!");



//! Тип семпла осциллограммы.
typedef uint8_t event_osc_sample_t;

//! Размер семпла осциллограммы.
#define EVENT_OSC_SAMPLE_SIZE sizeof(event_osc_sample_t)


//! Число семплов канала осциллограммы.
#define EVENT_OSC_SAMPLES_COUNT 480


//! Структура данных канала осциллограммы.
typedef struct PACKED _S_Event_Osc_Channel_Data {
    event_osc_sample_t samples[EVENT_OSC_SAMPLES_COUNT]; //!< Данные осциллограммы.
    uint16_t crc; //!< Контрольная сумма.
} event_osc_channel_data_t;

//!< Размер структуры данных канала осциллограммы.
#define EVENT_OSC_CHANNEL_DATA_SIZE sizeof(event_osc_channel_data_t)

static_assert(EVENT_OSC_CHANNEL_DATA_SIZE == (EVENT_OSC_SAMPLE_SIZE*EVENT_OSC_SAMPLES_COUNT + 2), "event_osc_channel_data_t invalid size!");



//! Структура канала осциллограммы события.
typedef struct PACKED _S_Event_Osc_Channel {
    event_osc_channel_info_t info; //!< Информация.
    event_osc_channel_data_t data; //!< Данные.
} event_osc_channel_t;

//!< Размер структуры канала осциллограммы.
#define EVENT_OSC_CHANNEL_SIZE sizeof(event_osc_channel_t)

static_assert(EVENT_OSC_CHANNEL_SIZE == (EVENT_OSC_CHANNEL_INFO_SIZE + EVENT_OSC_CHANNEL_DATA_SIZE), "event_osc_channel_t invalid size!");



//! Число каналов осциллограммы.
#define EVENT_OSC_CHANNELS_COUNT 16


//! Структура осциллограммы события.
typedef struct PACKED _S_Event_Osc {
    event_osc_channel_t channels[EVENT_OSC_CHANNELS_COUNT];
} event_osc_t;

//!< Размер структуры осциллограммы.
#define EVENT_OSC_SIZE sizeof(event_osc_t)

static_assert(EVENT_OSC_SIZE == (EVENT_OSC_CHANNEL_SIZE * EVENT_OSC_CHANNELS_COUNT), "event_osc_t invalid size!");



//! Событие.
typedef struct PACKED _S_Event {
    event_header_t header; //!< Заголовок события.
    event_info_t info; //!< Информация о событии.
    event_osc_info_t osc_info; //!< Информация об осциллограмме.
    event_osc_t osc; //!< Осциллограмма.
} event_t;

//!< Размер структуры события.
#define EVENT_SIZE sizeof(event_t)

static_assert(EVENT_SIZE == (EVENT_HEADER_SIZE + EVENT_INFO_SIZE + EVENT_OSC_INFO_SIZE + EVENT_OSC_SIZE), "event_t invalid size!");



//! Событие.
typedef struct PACKED _S_Event_Data {
    event_header_t header; //!< Заголовок события.
    event_info_t info; //!< Информация о событии.
    event_osc_info_t osc_info; //!< Информация об осциллограмме.
} event_data_t;

//!< Размер структуры события.
#define EVENT_DATA_SIZE sizeof(event_data_t)

static_assert(EVENT_DATA_SIZE == (EVENT_HEADER_SIZE + EVENT_INFO_SIZE + EVENT_OSC_INFO_SIZE), "event_data_t invalid size!");



//! Структура данных осциллограммы события.
typedef struct PACKED _S_Event_Osc_Data {
    event_osc_channel_t channel;
} event_osc_data_t;

//!< Размер структуры данных осциллограммы.
#define EVENT_OSC_DATA_SIZE sizeof(event_osc_data_t)

static_assert(EVENT_OSC_DATA_SIZE == (EVENT_OSC_CHANNEL_SIZE), "event_osc_data_t invalid size!");


//! Команда обновления списка событий.
typedef struct _S_Event_Log_Cmd_Refresh {
    size_t m_events_iter; //!< Итератор событий.
    size_t m_events_min_index; //!< Индекс первого события.
} event_log_cmd_refresh_t;

//! Команда сброса событий.
typedef struct _S_Event_Log_Cmd_Reset {
    size_t m_events_iter; //!< Итератор событий.
} event_log_cmd_reset_t;

//! Команда записи события.
typedef struct _S_Event_Log_Cmd_Write {
    event_type_t type; //!< Тип сообщения для записи.
    bool event_written; //!< Флаг записи события.
} event_log_cmd_write_t;

//! Команда чтения события.
typedef struct _S_Event_Log_Cmd_Read {
    size_t event_number; //!< Номер сообщения.
    size_t osc_channel; //!< Номер канала осциллограммы.
    void* data; //!< Адрес данных.
    size_t size; //!< Размер данных.
} event_log_cmd_read_t;


//! Структура элемента очереди.
typedef struct _S_Event_Log_Cmd {
    unsigned int type;//!< Команда.
    future_t* future; //!< Будущее.
    union {
        event_log_cmd_refresh_t refresh; //!< Обновление списка событий.
        event_log_cmd_reset_t reset; //!< Сброс списка событий.
        event_log_cmd_write_t write; //!< Запись нового события.
        event_log_cmd_read_t read; //!< Чтение данных события.
    };
} event_log_cmd_t;

//! Размер очереди.
#define EVENT_LOG_QUEUE_LEN 8



//! Размер хранилища для одного события.
#define EVENT_STORAGE_SIZE ((((EVENT_SIZE) + (STORAGE_MEM_RGN_EVENTS_ERASE_SIZE - 1)) / STORAGE_MEM_RGN_EVENTS_ERASE_SIZE) * STORAGE_MEM_RGN_EVENTS_ERASE_SIZE)

static_assert(EVENT_STORAGE_SIZE >= EVENT_SIZE, "Event size too large!");



//! Число событий в хранилище.
#define EVENTS_COUNT ((STORAGE_MEM_RGN_EVENTS_SIZE)/(EVENT_STORAGE_SIZE))



// Метод err_t refresh(future_t* future).
#define EVENT_LOG_METHOD_REFRESH_M_NAME refresh
#define EVENT_LOG_METHOD_REFRESH_RET err_t
#define EVENT_LOG_METHOD_REFRESH_ARGS future_t* future
#define EVENT_LOG_METHOD_REFRESH(MOD_TYPE)                       METHOD(MOD_TYPE, EVENT_LOG_METHOD_REFRESH_M_NAME, EVENT_LOG_METHOD_REFRESH_RET, EVENT_LOG_METHOD_REFRESH_ARGS)
#define EVENT_LOG_METHOD_REFRESH_PTR(MOD_NAME)                   METHOD_PTR(MOD_NAME, EVENT_LOG_METHOD_REFRESH_M_NAME)
#define EVENT_LOG_METHOD_REFRESH_PROTO(MOD_NAME)                 METHOD_PROTO(MOD_NAME, EVENT_LOG_METHOD_REFRESH_M_NAME, EVENT_LOG_METHOD_REFRESH_RET, EVENT_LOG_METHOD_REFRESH_ARGS)
#define EVENT_LOG_METHOD_REFRESH_IMPL(MOD_NAME, THIS, FUT)       METHOD_IMPL(MOD_NAME, THIS, EVENT_LOG_METHOD_REFRESH_M_NAME, EVENT_LOG_METHOD_REFRESH_RET, FUT)
#define EVENT_LOG_REFRESH(MOD, FUT)                              CALL(MOD, EVENT_LOG_METHOD_REFRESH_M_NAME, FUT)



// Метод err_t reset(future_t* future).
#define EVENT_LOG_METHOD_RESET_M_NAME reset
#define EVENT_LOG_METHOD_RESET_RET err_t
#define EVENT_LOG_METHOD_RESET_ARGS future_t* future
#define EVENT_LOG_METHOD_RESET(MOD_TYPE)                       METHOD(MOD_TYPE, EVENT_LOG_METHOD_RESET_M_NAME, EVENT_LOG_METHOD_RESET_RET, EVENT_LOG_METHOD_RESET_ARGS)
#define EVENT_LOG_METHOD_RESET_PTR(MOD_NAME)                   METHOD_PTR(MOD_NAME, EVENT_LOG_METHOD_RESET_M_NAME)
#define EVENT_LOG_METHOD_RESET_PROTO(MOD_NAME)                 METHOD_PROTO(MOD_NAME, EVENT_LOG_METHOD_RESET_M_NAME, EVENT_LOG_METHOD_RESET_RET, EVENT_LOG_METHOD_RESET_ARGS)
#define EVENT_LOG_METHOD_RESET_IMPL(MOD_NAME, THIS, FUT)       METHOD_IMPL(MOD_NAME, THIS, EVENT_LOG_METHOD_RESET_M_NAME, EVENT_LOG_METHOD_RESET_RET, FUT)
#define EVENT_LOG_RESET(MOD, FUT)                              CALL(MOD, EVENT_LOG_METHOD_RESET_M_NAME, FUT)




// Метод err_t read(unsigned int rgn, size_t offset, void* data, size_t size, future_t* future).
#define EVENT_LOG_METHOD_WRITE_M_NAME write
#define EVENT_LOG_METHOD_WRITE_RET err_t
#define EVENT_LOG_METHOD_WRITE_ARGS event_type_t type, future_t* future
#define EVENT_LOG_METHOD_WRITE(MOD_TYPE)                       METHOD(MOD_TYPE, EVENT_LOG_METHOD_WRITE_M_NAME, EVENT_LOG_METHOD_WRITE_RET, EVENT_LOG_METHOD_WRITE_ARGS)
#define EVENT_LOG_METHOD_WRITE_PTR(MOD_NAME)                   METHOD_PTR(MOD_NAME, EVENT_LOG_METHOD_WRITE_M_NAME)
#define EVENT_LOG_METHOD_WRITE_PROTO(MOD_NAME)                 METHOD_PROTO(MOD_NAME, EVENT_LOG_METHOD_WRITE_M_NAME, EVENT_LOG_METHOD_WRITE_RET, EVENT_LOG_METHOD_WRITE_ARGS)
#define EVENT_LOG_METHOD_WRITE_IMPL(MOD_NAME, THIS,\
                                    TYPE, FUT)                 METHOD_IMPL(MOD_NAME, THIS, EVENT_LOG_METHOD_WRITE_M_NAME, EVENT_LOG_METHOD_WRITE_RET, TYPE, FUT)
#define EVENT_LOG_WRITE(MOD, TYPE, FUT)                        CALL(MOD, EVENT_LOG_METHOD_WRITE_M_NAME, TYPE, FUT)




//// Метод err_t read(unsigned int rgn, size_t offset, void* data, size_t size, future_t* future).
//#define EVENT_LOG_METHOD_READ_M_NAME read
//#define EVENT_LOG_METHOD_READ_RET err_t
//#define EVENT_LOG_METHOD_READ_ARGS unsigned int rgn, size_t offset, void* data, size_t size, future_t* future
//#define EVENT_LOG_METHOD_READ(MOD_TYPE)                       METHOD(MOD_TYPE, EVENT_LOG_METHOD_READ_M_NAME, EVENT_LOG_METHOD_READ_RET, EVENT_LOG_METHOD_READ_ARGS)
//#define EVENT_LOG_METHOD_READ_PTR(MOD_NAME)                   METHOD_PTR(MOD_NAME, EVENT_LOG_METHOD_READ_M_NAME)
//#define EVENT_LOG_METHOD_READ_PROTO(MOD_NAME)                 METHOD_PROTO(MOD_NAME, EVENT_LOG_METHOD_READ_M_NAME, EVENT_LOG_METHOD_READ_RET, EVENT_LOG_METHOD_READ_ARGS)
//#define EVENT_LOG_METHOD_READ_IMPL(MOD_NAME, THIS, RGN,\
//                                   OFF, DAT, SIZ, FUT)       METHOD_IMPL(MOD_NAME, THIS, EVENT_LOG_METHOD_READ_M_NAME, EVENT_LOG_METHOD_READ_RET, RGN, OFF, DAT, SIZ, FUT)
//#define EVENT_LOG_READ(MOD, RGN, OFF, DAT, SIZ, FUT)          CALL(MOD, EVENT_LOG_METHOD_READ_M_NAME, RGN, OFF, DAT, SIZ, FUT)
//




//! Предварительная декларация типа модуля.
typedef struct _S_Event_Log M_event_log;

//! Структура модуля.
struct _S_Event_Log {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    // Регистры.
    //event_data_t r_event_data; //!< Буфер для чтения / записи события.
    //event_osc_data_t r_osc_channel_data; //!< Буфер для чтения / записи канала осциллограммы.
    // Методы.
    METHOD_INIT(M_event_log);
    METHOD_DEINIT(M_event_log);
    METHOD_CONTROL(M_event_log);
    METHOD_IDLE(M_event_log);
    EVENT_LOG_METHOD_REFRESH(M_event_log);
    EVENT_LOG_METHOD_RESET(M_event_log);
    EVENT_LOG_METHOD_WRITE(M_event_log);
    // Коллбэки.
    // Внутренние данные.
    event_data_t m_event_data; //!< Данные события.
    event_osc_data_t m_osc_channel_data; //!< Канал осциллограммы.
    uint8_t m_events_map[EVENTS_COUNT]; //!< Карта событий в памяти.
    size_t m_events_index; //!< Индекс последнего события.
    size_t m_events_put; //!< Индекс записи события.
    event_log_cmd_t m_queue[EVENT_LOG_QUEUE_LEN]; //!< Очередь команд.
    size_t m_q_head_index; //!< Голова очереди.
    size_t m_q_tail_index; //!< Хвост очереди.
    size_t m_q_count; //!< Число элементов в очереди.
    future_t m_future; //!< Будущее.
};

EXTERN METHOD_INIT_PROTO(M_event_log);
EXTERN METHOD_DEINIT_PROTO(M_event_log);
EXTERN METHOD_CONTROL_PROTO(M_event_log);
EXTERN METHOD_IDLE_PROTO(M_event_log);
EXTERN EVENT_LOG_METHOD_REFRESH_PROTO(M_event_log);
EXTERN EVENT_LOG_METHOD_RESET_PROTO(M_event_log);
EXTERN EVENT_LOG_METHOD_WRITE_PROTO(M_event_log);

#define EVENT_LOG_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        /* Регистры */\
        /*{{0}},*/ /* r_event_data */\
        /*{{{0}}},*/ /* r_osc_channel_data */\
        /* Методы */\
        METHOD_INIT_PTR(M_event_log), METHOD_DEINIT_PTR(M_event_log),\
        METHOD_CONTROL_PTR(M_event_log), METHOD_IDLE_PTR(M_event_log),\
        EVENT_LOG_METHOD_REFRESH_PTR(M_event_log),\
        EVENT_LOG_METHOD_RESET_PTR(M_event_log),\
        EVENT_LOG_METHOD_WRITE_PTR(M_event_log),\
        /* Коллбэки */\
        /* Внутренние данные */\
        {{0}}, /* m_event_data */\
        {{{0}}}, /* m_osc_channel_data */\
        {0}, /* m_events_map */\
        0, /* m_events_index */\
        0, /* m_events_put */\
        {{0}}, /* m_queue */\
        0, /* m_q_head_index */\
        0, /* m_q_tail_index */\
        0, /* m_q_count */\
        {0}, /* m_future */\
    }

#endif /* EVENT_LOG_H */
