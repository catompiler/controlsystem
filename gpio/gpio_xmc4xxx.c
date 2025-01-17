#if defined(PORT_XMC4500) || defined(PORT_XMC4700)

#include "gpio_xmc4xxx.h"


//! Реализация установки параметров одного пина.
ALWAYS_INLINE static void gpio_init_pin_impl(GPIO_t* GPIO, uint32_t pin_n, gpio_conf_t conf)
{
    PORT0_Type* port = (PORT0_Type*)GPIO;

    volatile uint32_t* IOCR = NULL;
    uint32_t iocr_pc_n = 0;

    if(pin_n >= 12){
        IOCR = &port->IOCR12;
        iocr_pc_n = pin_n - 12;
    }else if(pin_n >= 8){
        IOCR = &port->IOCR8;
        iocr_pc_n = pin_n - 8;
    }else if(pin_n >= 4){
        IOCR = &port->IOCR4;
        iocr_pc_n = pin_n - 4;
    }else{
        IOCR = &port->IOCR0;
        iocr_pc_n = pin_n - 0;
    }

    uint32_t shift = iocr_pc_n << 3;
    *IOCR = ((*IOCR) & ~(PORT0_IOCR0_PC0_Msk << shift)) | ((uint32_t)conf << (shift + PORT0_IOCR0_PC0_Pos));
}

void gpio_init(GPIO_t* GPIO, gpio_pin_t pins, gpio_conf_t conf)
{
    // Номер пина.
    uint32_t pin_n;
    // Цикл по пинам.
    while(pins){
        // Следующий номер пина.
        pin_n = 31U - __CLZ((uint32_t)pins);
        // Инициализируем.
        gpio_init_pin_impl(GPIO, pin_n, conf);
        // Очищаем номер инициализированного пина.
        pins &= ~(BIT(pin_n));
    }
}

//! Реализация установки драйвера выхода одного пина.
ALWAYS_INLINE static void gpio_set_pad_driver_impl(GPIO_t* GPIO, uint32_t pin_n, gpio_pad_driver_t pad_driver)
{
    PORT0_Type* port = (PORT0_Type*)GPIO;

    volatile uint32_t* PDR = NULL;
    uint32_t pdr_pd_n = 0;

    if(pin_n >= 8){
        PDR = &port->PDR1;
        pdr_pd_n = pin_n - 8;
    }else{
        PDR = &port->PDR0;
        pdr_pd_n = pin_n - 0;
    }

    uint32_t shift = pdr_pd_n << 2;
    *PDR = ((*PDR) & ~(PORT0_PDR0_PD0_Msk << shift)) | ((uint32_t)pad_driver << (shift + PORT0_PDR0_PD0_Pos));
}

void gpio_set_pad_driver(GPIO_t* GPIO, gpio_pin_t pins, gpio_pad_driver_t pad_driver)
{
    // Номер пина.
    uint32_t pin_n;
    // Цикл по пинам.
    while(pins){
        // Следующий номер пина.
        pin_n = 31U - __CLZ((uint32_t)pins);
        // Инициализируем.
        gpio_set_pad_driver_impl(GPIO, pin_n, pad_driver);
        // Очищаем номер инициализированного пина.
        pins &= ~(BIT(pin_n));
    }
}


//! Реализация установки аппаратного управления одного пина.
ALWAYS_INLINE static void gpio_set_hw_control_impl(GPIO_t* GPIO, uint32_t pin_n, gpio_hwsel_t hwsel)
{
    PORT0_Type* port = (PORT0_Type*)GPIO;

    uint32_t shift = pin_n << 1;
    port->HWSEL = (port->HWSEL & ~(PORT0_HWSEL_HW0_Msk << shift)) | ((uint32_t)hwsel << (shift + PORT0_HWSEL_HW0_Pos));
}

void gpio_set_hw_control(GPIO_t* GPIO, gpio_pin_t pins, gpio_hwsel_t hwsel)
{
    // Номер пина.
    uint32_t pin_n;
    // Цикл по пинам.
    while(pins){
        // Следующий номер пина.
        pin_n = 31U - __CLZ((uint32_t)pins);
        // Инициализируем.
        gpio_set_hw_control_impl(GPIO, pin_n, hwsel);
        // Очищаем номер инициализированного пина.
        pins &= ~(BIT(pin_n));
    }
}

#endif
