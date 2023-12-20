#ifndef CONF_H
#define CONF_H

#include "module/base.h"
#include "iqmath/iqmath.h"
#include "consts.h"



/*
 * Модуль общих настроек преобразователя.
 */


// Значения параметров.
// Номинальное напряжение.
// Минимум.
#define CONF_U_NOM_MIN IQ15(1)
// Максимум.
#define CONF_U_NOM_MAX IQ15(1000)
// По-умолчанию.
#define CONF_U_NOM_DEFAULT IQ15(100)

// Номинальный ток.
// Минимум.
#define CONF_I_NOM_MIN IQ15(1)
// Максимум.
#define CONF_I_NOM_MAX IQ15(10000)
// По-умолчанию.
#define CONF_I_NOM_DEFAULT IQ15(300)

// Номинальная частота.
// Минимум.
#define CONF_f_NOM_MIN IQ15(45)
// Максимум.
#define CONF_f_NOM_MAX IQ15(65)
// По-умолчанию.
#define CONF_f_NOM_DEFAULT IQ15(50)



//! Перечисление возможных бит управления.
enum _E_Conf_Control {
    CONF_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Conf_Status {
    CONF_STATUS_NONE = STATUS_NONE,
    // TODO: Conf warning handle.
    CONF_STATUS_WARNING = STATUS_WARNING,
};

//! Перечисление возможных бит предупреждений.
enum _E_Conf_Warnings {
    CONF_WARNING_NONE = WARNING_NONE,
    CONF_WARNING_INVALID_PARAMS = (WARNING_USER << 0),
};

typedef struct _S_Conf M_conf;

struct _S_Conf {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    warning_t warnings; //!< Слово предупреждений.
    // Входные данные.
    // Выходные данные.
    // Параметры.
    reg_iq15_t p_U_nom; //!< Номинальное (базовое) напряжение.
    reg_iq15_t p_I_nom; //!< Номинальный (базовый) ток.
    reg_iq15_t p_f_nom; //!< Номинальная (базовый) частота.
    // Регистры.
    // Базовые величины.
    // Напряжение.
    reg_iq15_t r_U_base; //!< Базовое напряжение.
    reg_iq24_t r_U_base_inv; //!< Базовое напряжение, инвертированное значение.
    // Ток.
    reg_iq15_t r_I_base; //!< Базовый ток.
    reg_iq24_t r_I_base_inv; //!< Базовый ток, инвертированное значение.
    // Частота.
    reg_iq15_t r_f_base; //!< Базовая частота.
    reg_iq24_t r_f_base_inv; //!< Базовая частота, инвертированное значение.
    // Мощность.
    reg_iq7_t r_P_base; //!< Базовая мощность.
    reg_iq24_t r_P_base_inv; //!< Базовая мощность, инвертированное значение.
    // Методы.
    METHOD_INIT(M_conf);
    METHOD_DEINIT(M_conf);
    METHOD_IDLE(M_conf);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_conf);
EXTERN METHOD_DEINIT_PROTO(M_conf);
EXTERN METHOD_IDLE_PROTO(M_conf);

#define CONF_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        0, /* warnings*/\
        /* Входные данные */\
        /* Выходные данные */\
        /* Параметры */\
        CONF_U_NOM_DEFAULT, /* Номинальное напряжение */\
        CONF_I_NOM_DEFAULT, /* Номинальный ток */\
        CONF_f_NOM_DEFAULT, /* Номинальная частота */\
        /* Регистры */\
        0, 0, /* Базовое напряжение и его инвертированное значение */\
        0, 0, /* Базовый ток и его инвертированное значение */\
        0, 0, /* Базовая частота и её инвертированное значение */\
        0, 0, /* Базовая мощность и её инвертированное значение */\
        /* Методы */\
        METHOD_INIT_PTR(M_conf), METHOD_DEINIT_PTR(M_conf),\
        METHOD_IDLE_PTR(M_conf),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* CONF_H */
