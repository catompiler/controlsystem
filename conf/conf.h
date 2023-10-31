#ifndef CONF_H
#define CONF_H

#include "module/base.h"
#include "iqmath/iqmath.h"
#include "consts.h"



//! Значение номинального напряжения по-умолчанию.
#define CONF_U_NOM_DEFAULT (400)
//! Значение номинального тока по-умолчанию.
#define CONF_I_NOM_DEFAULT (415)
//! Значение номинальной частоты по-умолчанию.
#define CONF_f_NOM_DEFAULT (50)


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
    // TODO: Базовые значения для разных измерений, как то ток фаз, якоря и ток возбуждения.
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
    // Угловая частота.
    reg_iq15_t r_w_base; //!< Базовая угловая частота.
    reg_iq24_t r_w_base_inv; //!< Базовая угловая частота, инвертированное значение.
    // Время.
    reg_iq24_t r_t_base; //!< Базовое время.
    reg_iq15_t r_t_base_inv; //!< Базовое время, инвертированное значение.
    // Момент.
    reg_iq15_t r_M_base; //!< Базовый момент.
    reg_iq24_t r_M_base_inv; //!< Базовый момент, инвертированное значение.
    // Момент инерции.
    reg_iq24_t r_J_base; //!< Базовый момент инерции.
    reg_iq7_t r_J_base_inv; //!< Базовый момент инерции, инвертированное значение.
    // Магнитный поток.
    reg_iq24_t r_Psi_base; //!< Базовое потокосцепление.
    reg_iq24_t r_Psi_base_inv; //!< Базовое потокосцепление, инвертированное значение.
    // Сопротивление.
    reg_iq24_t r_R_base; //!< Базовое сопротивление.
    reg_iq24_t r_R_base_inv; //!< Базовое сопротивление, инвертированное значение.
    // Индуктивность.
    reg_iq24_t r_L_base; //!< Базовая индуктивность.
    reg_iq15_t r_L_base_inv; //!< Базовая индуктивность, инвертированное значение.
    // Ёмкость.
    reg_iq24_t r_C_base; //!< Базовая ёмкость.
    reg_iq15_t r_C_base_inv; //!< Базовая ёмкость, инвертированное значение.
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
        IQ15(CONF_U_NOM_DEFAULT), /* Номинальное напряжение */\
        IQ15(CONF_I_NOM_DEFAULT), /* Номинальный ток */\
        IQ15(CONF_f_NOM_DEFAULT), /* Номинальная частота */\
        /* Регистры */\
        0, 0, /* Базовое напряжение и его инвертированное значение */\
        0, 0, /* Базовый ток и его инвертированное значение */\
        0, 0, /* Базовая частота и её инвертированное значение */\
        0, 0, /* Базовая мощность и её инвертированное значение */\
        0, 0, /* Базовая угловая частота и её инвертированное значение */\
        0, 0, /* Базовое время и его инвертированное значение */\
        0, 0, /* Базовый момент и его инвертированное значение */\
        0, 0, /* Базовый момент инерции и его инвертированное значение */\
        0, 0, /* Базовое потокосцепление и его инвертированное значение */\
        0, 0, /* Базовое сопротивление и его инвертированное значение */\
        0, 0, /* Базовая индуктивность и её инвертированное значение */\
        0, 0, /* Базовая ёмкость и её инвертированное значение */\
        /* Методы */\
        METHOD_INIT_PTR(M_conf), METHOD_DEINIT_PTR(M_conf),\
        METHOD_IDLE_PTR(M_conf),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* CONF_H */
