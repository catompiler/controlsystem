#ifndef CELL_CB_H
#define CELL_CB_H

#include "module/base.h"


//! Перечисление возможных бит управления.
enum _E_Cell_Cb_Control {
    CELL_CB_CONTROL_NONE = CONTROL_NONE,
};

//! Перечисление возможных бит статуса.
enum _E_Cell_Cb_Status {
    CELL_CB_STATUS_NONE = STATUS_NONE,
};


//! Перечисление состояний выключателя.
enum _E_Cell_Cb_State {
    CELL_CB_INVALID_OFF = 0b00,
    CELL_CB_ON = 0b01,
    CELL_CB_OFF = 0b10,
    CELL_CB_INVALID_ON = 0b11,
};

//! Тип состояний сигнала.
typedef enum _E_Cell_Cb_State cell_cb_state_t;

//! Предварительная декларация типа модуля.
typedef struct _S_Cell_Cb M_cell_cb;

//! Структура модуля.
struct _S_Cell_Cb {
    // Базовые поля.
    control_t control; //!< Слово управления.
    status_t status; //!< Слово состояния.
    // Входные данные.
    flag_t in_no_state; //!< Состояние NO контакта выключателя ячейки.
    flag_t in_nc_state; //!< Состояние NC контакта выключателя ячейки.
    // Выходные данные.
    cell_cb_state_t out_state; //!< Состояние выключателя ячейки.
    // Параметры.
    // Регистры.
    // Методы.
    METHOD_INIT(M_cell_cb);
    METHOD_DEINIT(M_cell_cb);
    METHOD_CALC(M_cell_cb);
    // Коллбэки.
    // Внутренние данные.
};

EXTERN METHOD_INIT_PROTO(M_cell_cb);
EXTERN METHOD_DEINIT_PROTO(M_cell_cb);
EXTERN METHOD_CALC_PROTO(M_cell_cb);

#define CELL_CB_DEFAULTS {\
        /* Базовые поля */\
        0, 0, /* control, status */\
        /* Входные данные */\
        0, 0, /* in_no_state, in_nc_state */\
        /* Выходные данные */\
        0, /* out_state */\
        /* Параметры */\
        /* Регистры */\
        /* Методы */\
        METHOD_INIT_PTR(M_cell_cb), METHOD_DEINIT_PTR(M_cell_cb),\
        METHOD_CALC_PTR(M_cell_cb),\
        /* Коллбэки */\
        /* Внутренние данные */\
    }

#endif /* CELL_CB_H */
