#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

/**
 * @file gpio.h Библиотека GPIO.
 */
#ifndef GPIO_H_
#define GPIO_H_

#include "cpu.h"
#include <stdint.h>
#include "bits/bits.h"
#include "defs/defs.h"


//! Тип GPIO.
typedef void GPIO_t;


// Пины.
#define GPIO_PIN_0 BIT(0)
#define GPIO_PIN_1 BIT(1)
#define GPIO_PIN_2 BIT(2)
#define GPIO_PIN_3 BIT(3)
#define GPIO_PIN_4 BIT(4)
#define GPIO_PIN_5 BIT(5)
#define GPIO_PIN_6 BIT(6)
#define GPIO_PIN_7 BIT(7)
#define GPIO_PIN_8 BIT(8)
#define GPIO_PIN_9 BIT(9)
#define GPIO_PIN_10 BIT(10)
#define GPIO_PIN_11 BIT(11)
#define GPIO_PIN_12 BIT(12)
#define GPIO_PIN_13 BIT(13)
#define GPIO_PIN_14 BIT(14)
#define GPIO_PIN_15 BIT(15)

//! Тип пина GPIO.
typedef uint16_t gpio_pin_t;

// Состояние пина.
//! Выключено.
#define GPIO_STATE_OFF 0
//! Включено.
#define GPIO_STATE_ON  1

//! Тип состояния пина.
typedef uint16_t gpio_state_t;

//! Конфигурация GPIO.
typedef enum _E_Gpio_Config {
    GPIO_CONF_INPUT             = 0b00000,
    GPIO_CONF_INPUT_PD          = 0b00001,
    GPIO_CONF_INPUT_PU          = 0b00010,
    GPIO_CONF_INPUT_TO_OUT      = 0b00011,
    GPIO_CONF_INPUT_INV         = 0b00100,
    GPIO_CONF_INPUT_INV_PD      = 0b00101,
    GPIO_CONF_INPUT_INV_PU      = 0b00110,
    GPIO_CONF_INPUT_INV_TO_OUT  = 0b00111,
    GPIO_CONF_OUTPUT_PP_GP      = 0b10000,
    GPIO_CONF_OUTPUT_PP_ALT1    = 0b10001,
    GPIO_CONF_OUTPUT_PP_ALT2    = 0b10010,
    GPIO_CONF_OUTPUT_PP_ALT3    = 0b10011,
    GPIO_CONF_OUTPUT_PP_ALT4    = 0b10100,
    GPIO_CONF_OUTPUT_OD_GP      = 0b11000,
    GPIO_CONF_OUTPUT_OD_ALT1    = 0b11001,
    GPIO_CONF_OUTPUT_OD_ALT2    = 0b11010,
    GPIO_CONF_OUTPUT_OD_ALT3    = 0b11011,
    GPIO_CONF_OUTPUT_OD_ALT4    = 0b11100
} gpio_conf_t;

//! Сила выхода.
typedef enum _E_Gpio_Pad_Driver {
    GPIO_PAD_A1_DRIVER_MEDIUM             = 0b000,
    GPIO_PAD_A1_DRIVER_WEAK               = 0b001,
    GPIO_PAD_A1P_DRIVER_STRONG_EDGE_SOFT  = 0b000,
    GPIO_PAD_A1P_DRIVER_STRONG_EDGE_SLOW  = 0b001,
    GPIO_PAD_A1P_DRIVER_MEDIUM            = 0b100,
    GPIO_PAD_A1P_DRIVER_WEAK              = 0b101,
    GPIO_PAD_A2_DRIVER_STRONG_EDGE_SHARP  = 0b000,
    GPIO_PAD_A2_DRIVER_STRONG_EDGE_MEDIUM = 0b001,
    GPIO_PAD_A2_DRIVER_STRONG_EDGE_SOFT   = 0b010,
    GPIO_PAD_A2_DRIVER_MEDIUM_0           = 0b100,
    GPIO_PAD_A2_DRIVER_MEDIUM_1           = 0b101,
    GPIO_PAD_A2_DRIVER_MEDIUM             = GPIO_PAD_A2_DRIVER_MEDIUM_0,
    GPIO_PAD_A2_DRIVER_WEAK               = 0b111
} gpio_pad_driver_t;

//! Отключение выхода.
typedef enum _E_Gpio_Pad_Decision {
    GPIO_PAD_ENABLED  = 0b0,
    GPIO_PAD_DISABLED = 0b1,
} gpio_pad_decision_t;

//! Аппаратный выбор направления.
typedef enum _E_Gpio_Hw_Sel {
    GPIO_HWSEL_SW        = 0b00,//!< GPIO_HWSEL_SW
    GPIO_HWSEL_HWI0_HWO0 = 0b01,//!< GPIO_HWSEL_HWI0_HWO0
    GPIO_HWSEL_HWI1_HWO1 = 0b10 //!< GPIO_HWSEL_HWI1_HWO1
} gpio_hwsel_t;

// //! Управление в режиме сбережения питания.
//typedef enum _E_Gpio_Power_Save {
//    GPIO_POWER_SAVE_DISABLED = 0b0,
//    GPIO_POWER_SAVE_ENABLED  = 0b1,
//} gpio_power_save_t;

/**
 * Инициализирует пин.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 * @param conf Конфигурация пина.
 */
EXTERN void gpio_init(GPIO_t* GPIO, gpio_pin_t pins, gpio_conf_t conf);

/**
 * Устанавливает выходной драйвер пина.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 * @param pad_driver Выходной драйвер.
 */
EXTERN void gpio_set_pad_driver(GPIO_t* GPIO, gpio_pin_t pins, gpio_pad_driver_t pad_driver);

/**
 * Устанавливает аппаратное управление пином.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 * @param hwsel Аппаратное управление пином.
 */
EXTERN void gpio_set_hw_control(GPIO_t* GPIO, gpio_pin_t pins, gpio_hwsel_t hwsel);

/**
 * Разрешает режим сбережения.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 */
ALWAYS_INLINE static void gpio_enable_power_save(GPIO_t* GPIO, gpio_pin_t pins)
{
    ((PORT0_Type*)GPIO)->PPS |= pins;
}

/**
 * Запрещает режим сбережения.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 */
ALWAYS_INLINE static void gpio_disable_power_save(GPIO_t* GPIO, gpio_pin_t pins)
{
    ((PORT0_Type*)GPIO)->PPS &= ~pins;
}

// Предварительная декларация функции установки выходного значения.
ALWAYS_INLINE static void gpio_set_output_value(GPIO_t* GPIO, gpio_pin_t pins, uint16_t val);
/**
 * Устанавливает значение в режим сбережения.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 * @param val Значение.
 */
ALWAYS_INLINE static void gpio_set_power_save_default_value(GPIO_t* GPIO, gpio_pin_t pins, uint16_t val)
{
    gpio_set_output_value(GPIO, pins, val);
}

/**
 * Разрешает цифровой пин.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 */
ALWAYS_INLINE static void gpio_enable_digital_pad(GPIO_t* GPIO, gpio_pin_t pins)
{
    ((PORT14_Type*)GPIO)->PDISC &= ~pins;
}

/**
 * Запрещает цифровой пин.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 */
ALWAYS_INLINE static void gpio_disable_digital_pad(GPIO_t* GPIO, gpio_pin_t pins)
{
    ((PORT14_Type*)GPIO)->PPS |= pins;
}

/**
 * Устанавливает биты пинов.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 */
ALWAYS_INLINE static void gpio_set(GPIO_t* GPIO, gpio_pin_t pins)
{
    ((PORT0_Type*)GPIO)->OMR = (uint32_t)pins;
}

/**
 * Сбрасывает биты пинов.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 */
ALWAYS_INLINE static void gpio_reset(GPIO_t* GPIO, gpio_pin_t pins)
{
    ((PORT0_Type*)GPIO)->OMR = ((uint32_t)pins) << 16;
}

/**
 * Изменяет биты пинов.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 */
ALWAYS_INLINE static void gpio_toggle(GPIO_t* GPIO, gpio_pin_t pins)
{
    ((PORT0_Type*)GPIO)->OUT ^= pins;
}

/**
 * Получает входное состояние пина.
 * @param GPIO Порт.
 * @param pin Пин.
 * @return Входное состояние пина.
 */
ALWAYS_INLINE static gpio_state_t gpio_input_state(GPIO_t* GPIO, gpio_pin_t pin)
{
    return __USAT(((PORT0_Type*)GPIO)->IN & pin, 1);
}

/**
 * Получает выходное состояние пина.
 * @param GPIO Порт.
 * @param pin Пин.
 * @return Выходное состояние пина.
 */
ALWAYS_INLINE static gpio_state_t gpio_output_state(GPIO_t* GPIO, gpio_pin_t pin)
{
    return __USAT(((PORT0_Type*)GPIO)->OUT & pin, 1);
}

/**
 * Получает входное значение пинов.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 * @return Входное значение пина.
 */
ALWAYS_INLINE static uint16_t gpio_input_value(GPIO_t* GPIO, gpio_pin_t pins)
{
    return ((PORT0_Type*)GPIO)->IN & pins;
}

/**
 * Получает выходное значение пинов.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 * @return Выходное значение пинов.
 */
ALWAYS_INLINE static uint16_t gpio_output_value(GPIO_t* GPIO, gpio_pin_t pins)
{
    return ((PORT0_Type*)GPIO)->OUT & pins;
}

/**
 * Устанавливает выходное значение пинов.
 * @param GPIO Порт.
 * @param pins Маска пинов.
 * @param val Выходное значение пинов.
 */
ALWAYS_INLINE static void gpio_set_output_value(GPIO_t* GPIO, gpio_pin_t pins, uint16_t val)
{
    ((PORT0_Type*)GPIO)->OMR = (uint32_t)(pins & val);
    ((PORT0_Type*)GPIO)->OMR = (uint32_t)(pins & ~val) << 16;
}

#endif /* GPIO_H_ */

#endif
