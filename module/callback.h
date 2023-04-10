#ifndef MODULE_CALLBACK_H
#define MODULE_CALLBACK_H

#include <stddef.h>


//! Тип обратного вызова.
typedef struct _S_Callback {
    void (*proc)(void*); //!< Функция.
    void* arg; //!< Аргумент.
} callback_t;

//! Декларация обратного вызова.
#define CALLBACK(NAME) callback_t NAME

//! Значения для инициализации обратного вызова.
#define CALLBACK_DEFAULTS {NULL, NULL}

//! Функция обратного вызова.
#define CALLBACK_PROC(CB) CB.proc

//! Аргумент обратного вызова.
#define CALLBACK_ARG(CB) CB.arg

//! Обратный вызов.
#define CALLBACK_CALL(CB) do{ if(CB.proc){ CB.proc(CB.arg); } }while(0)


#endif /* MODULE_CALLBACK_H */
