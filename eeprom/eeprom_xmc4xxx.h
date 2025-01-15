#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#ifndef EEPROM_XMC4XXX_H
#define EEPROM_XMC4XXX_H


#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>
#include "errors/errors.h"
#include "future/future.h"
#include "m95x/m95x.h"
#include "gpio/gpio.h"



//! Размер читаемой / записываемой страницы.
#define EEPROM_PAGE_SIZE M95X_PAGE_256

static_assert((EEPROM_PAGE_SIZE & (EEPROM_PAGE_SIZE - 1)) == 0, "EEPROM page size is not power of two!");

//! Размер стираемого блока.
#define EEPROM_ERASE_SIZE EEPROM_PAGE_SIZE

static_assert((EEPROM_ERASE_SIZE & (EEPROM_ERASE_SIZE - 1)) == 0, "EEPROM erase size is not power of two!");

static_assert((EEPROM_ERASE_SIZE >= EEPROM_PAGE_SIZE), "EEPROM erase size < page size!");


//! Состояния.
typedef enum _E_Eeprom_State {
    EEPROM_STATE_NONE = 0,
    EEPROM_STATE_ERASE = 1,
    EEPROM_STATE_READ = 2,
    EEPROM_STATE_WRITE = 3,
    EEPROM_STATE_DONE = 4,
    //EEPROM_STATE_MOD_READ = 5,
    //EEPROM_STATE_MOD_WRITE = 6,
    EEPROM_STATE_WAIT_READ = 7,
    EEPROM_STATE_WAIT_WRITE = 8,
    EEPROM_STATE_WAIT_ERASE = 9,
} eeprom_state_t;

//! Тип операции.
typedef enum _E_Eeprom_Op {
    EEPROM_OP_NONE = 0,
    EEPROM_OP_ERASE = 1,
    EEPROM_OP_READ = 2,
    EEPROM_OP_WRITE = 3
} eeprom_op_t;

//! Флаги операции.
typedef enum _E_Eeprom_Flag {
    EEPROM_FLAG_NONE = 0,
    EEPROM_FLAG_ERASE = 1, //!< Предварительно стереть блок с записываемой страницей.
    //EEPROM_FLAG_MODIFY = 2 //!< Не игнорировать имеющееся содержимое записываемой страницы.
} eeprom_flag_t;
//! Тип флагов.
typedef uint32_t eeprom_flags_t;


//! Структура EEPROM.
typedef struct _S_Eeprom {
    m95x_t* m95x; //!< Микросхема EEPROM.
    GPIO_t* gpio_nwp; //!< Порт nWP.
    gpio_pin_t pin_nwp; //!< Пин nWP.
    GPIO_t* gpio_nhold; //!< Порт nHOLD.
    gpio_pin_t pin_nhold; //!< Пин nHOLD.
    size_t size; //!< Размер.
    uint8_t page_buf[EEPROM_ERASE_SIZE]; //!< Буфер данных.
    eeprom_state_t state; //!< Состояние.
    eeprom_op_t op; //!< Тип операции.
    size_t address; //!< Адрес операции.
    void* data_ptr; //!< Данные для операции.
    size_t data_size; //!< Размер данных для операции.
    eeprom_flags_t flags; //!< Флаги операции.
    size_t data_processed; //!< Размер обработанных данных.
    future_t* future; //!< Будущее операции.
} eeprom_t;


//! Структура инициализации.
typedef struct _S_Eeprom_Init {
    m95x_t* m95x; //!< Микросхема EEPROM.
    GPIO_t* gpio_nwp; //!< Порт nWP.
    gpio_pin_t pin_nwp; //!< Пин nWP.
    GPIO_t* gpio_nhold; //!< Порт nHOLD.
    gpio_pin_t pin_nhold; //!< Пин nHOLD.
} eeprom_init_t;


/**
 * Инициализирует EEPROM.
 * @param eeprom EEPROM.
 * @param m95x Микросхема EEPROM, NULL при ошибке доступа.
 * @param size Размер EEPROM.
 * @return Код ошибки.
 */
err_t eeprom_init(eeprom_t* eeprom, eeprom_init_t* is, size_t size);


/**
 * Деинициализирует EEPROM.
 */
void eeprom_deinit(eeprom_t* eeprom);

/**
 * Стирает данные в EEPROM.
 * Может быть как синхронной,
 * так и асинхронной операцией,
 * в зависимости от реализации.
 * @param eeprom EEPROM.
 * @param address Адрес.
 * @param size Размер данных.
 * @param future Будущее.
 * @param flags Флаги.
 * @return Код ошибки. E_IN_PROGRESS, если операция запущена, но пока не завершена.
 */
err_t eeprom_erase(eeprom_t* eeprom, size_t address, size_t size, future_t* future, eeprom_flags_t flags);

/**
 * Записывает данные в EEPROM.
 * Может быть как синхронной,
 * так и асинхронной операцией,
 * в зависимости от реализации.
 * @param eeprom EEPROM.
 * @param address Адрес.
 * @param data Данные.
 * @param size Размер данных.
 * @param future Будущее.
 * @param flags Флаги.
 * @return Код ошибки. E_IN_PROGRESS, если операция запущена, но пока не завершена.
 */
err_t eeprom_write(eeprom_t* eeprom, size_t address, const void* data, size_t size, future_t* future, eeprom_flags_t flags);

/**
 * Читает данные из EEPROM.
 * Может быть как синхронной,
 * так и асинхронной операцией,
 * в зависимости от реализации.
 * @param eeprom EEPROM.
 * @param address Адрес.
 * @param data Данные.
 * @param size Размер данных.
 * @param future Будущее.
 * @param flags Флаги.
 * @return Код ошибки. E_IN_PROGRESS, если операция запущена, но пока не завершена.
 */
err_t eeprom_read(eeprom_t* eeprom, size_t address, void* data, size_t size, future_t* future, eeprom_flags_t flags);

/**
 * Производит обработку конечного автомата.
 * @param eeprom EEPROM.
 */
void eeprom_process(eeprom_t* eeprom);

/**
 * Получает флаг занятости EEPROM.
 * @param eeprom EEPROM.
 * @return Флаг занятости.
 */
bool eeprom_busy(eeprom_t* eeprom);


#endif /* EEPROM_XMC4XXX_H */

#endif
