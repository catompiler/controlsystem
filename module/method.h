#ifndef MODULE_METHOD_H
#define MODULE_METHOD_H

#include "defs/defs.h"


//typedef struct _S_Module_Name MModuleName;
//typedef struct _S_Module_Name module_name_t;
//typedef struct _S_Module_Name mmodule_name;
//typedef struct _S_Module_Name m_module_name;
//typedef struct _S_Module_Name mmodule_name_t;
//typedef struct _S_Module_Name m_module_name_t;
//typedef struct _S_Module_Name M_module_name;
//typedef struct _S_Module_Name M_MODULE_NAME;
//typedef struct _S_Module_Name MMODULE_NAME;
//typedef struct _S_Module_Name Mmodule_name;
//typedef struct _S_Module_Name Mmodule_name_t;
//
// MModuleName     mod;     /* 01 */
// module_name_t   mod;     /* 02 */
// mmodule_name    mod;     /* 03 */
// m_module_name   mod;     /* 04 */
// mmodule_name_t  mod;     /* 05 */
// m_module_name_t mod;     /* 06 */
// M_module_name   mod;     /* 07 */
// M_MODULE_NAME   mod;     /* 08 */
// MMODULE_NAME    mod;     /* 09 */
// Mmodule_name    mod;     /* 10 */
// Mmodule_name_t  mod;     /* 11 */


/*
 * Макросы для объявления методов модуля.
 */
/**
 * Объявление метода в структуре.
 * @param MOD_TYPE Тип модуля для аргумента this функции.
 * @param NAME Имя метода.
 */
#define METHOD(MOD_TYPE, NAME, RET, ...) RET (*NAME)(MOD_TYPE*, ##__VA_ARGS__)
/**
 * Вспомогательный макрос - формирует имя функции метода модуля.
 * @param MOD_NAME Имя модуля.
 * @param NAME Имя метода.
 */
#define METHOD_FUNC_NAME(MOD_NAME, NAME) CONCAT(MOD_NAME, CONCAT(_, NAME))
/**
 * Получает указатель на функцию метода модуля.
 * @param MOD_NAME Имя модуля.
 * @param NAME Имя метода.
 */
#define METHOD_PTR(MOD_NAME, NAME) METHOD_FUNC_NAME(MOD_NAME, NAME)
/**
 * Объявляет прототип метода модуля
 * с указанием типа структуры модуля.
 * @param MOD_NAME Имя модуля.
 * @param MOD_TYPE Тип модуля для аргумента this функции.
 * @param NAME Имя метода.
 */
#define METHOD_PROTO_S(MOD_NAME, MOD_TYPE, NAME, RET, ...) RET METHOD_FUNC_NAME(MOD_NAME, NAME)(MOD_TYPE*, ##__VA_ARGS__)
/**
 * Объявляет прототип метода модуля,
 * для указанием типа структуры модуля
 * использует имя модуля.
 * @param MOD_NAME Имя модуля.
 * @param NAME Имя метода.
 */
#define METHOD_PROTO(MOD_NAME, NAME, RET, ...) METHOD_PROTO_S(MOD_NAME, MOD_NAME, NAME, RET, ##__VA_ARGS__)
/**
 * Объявляет реализацию метода модуля
 * с указанием типа структуры модуля.
 * @param MOD_NAME Имя модуля.
 * @param MOD_TYPE Тип модуля для аргумента this функции.
 * @param THIS Имя аргумента this.
 * @param NAME Имя метода.
 */
#define METHOD_IMPL_S(MOD_NAME, MOD_TYPE, THIS, NAME, RET, ...) RET METHOD_FUNC_NAME(MOD_NAME, NAME)(MOD_TYPE* THIS, ##__VA_ARGS__)
/**
 * Объявляет реализацию метода модуля,
 * для указанием типа структуры модуля
 * использует имя модуля.
 * @param MOD_NAME Имя модуля.
 * @param THIS Имя аргумента this.
 * @param NAME Имя метода.
 */
#define METHOD_IMPL(MOD_NAME, THIS, NAME, RET, ...) METHOD_IMPL_S(MOD_NAME, MOD_NAME, THIS, NAME, RET, ##__VA_ARGS__)
/**
 * Вызывает метод модуля.
 * @param MOD Переменная модуля.
 * @param NAME Имя модуля.
 */
#define CALL(MOD, NAME, ...) MOD.NAME(&MOD, ##__VA_ARGS__)
// /**
//  * Вызывает метод модуля по указателю.
//  * @param MOD Переменная модуля.
//  * @param NAME Имя модуля.
//  */
// #define CALL_PTR(MOD_PTR, NAME, ...) MOD_PTR->NAME(MOD_PTR, ##__VA_ARGS__)


// Метод init().
// Инициализацию модуля.
#define METHOD_INIT_M_NAME init
#define METHOD_INIT_RET void
#define METHOD_INIT(MOD_TYPE)                        METHOD(MOD_TYPE, METHOD_INIT_M_NAME, METHOD_INIT_RET)
#define METHOD_INIT_PTR(MOD_NAME)                    METHOD_PTR(MOD_NAME, METHOD_INIT_M_NAME)
#define METHOD_INIT_PROTO(MOD_NAME)                  METHOD_PROTO(MOD_NAME, METHOD_INIT_M_NAME, METHOD_INIT_RET)
#define METHOD_INIT_IMPL(MOD_NAME, THIS)             METHOD_IMPL(MOD_NAME, THIS, METHOD_INIT_M_NAME, METHOD_INIT_RET)
#define INIT(MOD)                                     CALL(MOD, METHOD_INIT_M_NAME)

// Метод deinit().
// Деинициализация модуля.
#define METHOD_DEINIT_M_NAME deinit
#define METHOD_DEINIT_RET void
#define METHOD_DEINIT(MOD_TYPE)                        METHOD(MOD_TYPE, METHOD_DEINIT_M_NAME, METHOD_DEINIT_RET)
#define METHOD_DEINIT_PTR(MOD_NAME)                    METHOD_PTR(MOD_NAME, METHOD_DEINIT_M_NAME)
#define METHOD_DEINIT_PROTO(MOD_NAME)                  METHOD_PROTO(MOD_NAME, METHOD_DEINIT_M_NAME, METHOD_DEINIT_RET)
#define METHOD_DEINIT_IMPL(MOD_NAME, THIS)             METHOD_IMPL(MOD_NAME, THIS, METHOD_DEINIT_M_NAME, METHOD_DEINIT_RET)
#define DEINIT(MOD)                                     CALL(MOD, METHOD_DEINIT_M_NAME)

// Метод calc().
// Основная итерация работы, расчёта модуля.
#define METHOD_CALC_M_NAME calc
#define METHOD_CALC_RET void
#define METHOD_CALC(MOD_TYPE)                        METHOD(MOD_TYPE, METHOD_CALC_M_NAME, METHOD_CALC_RET)
#define METHOD_CALC_PTR(MOD_NAME)                    METHOD_PTR(MOD_NAME, METHOD_CALC_M_NAME)
#define METHOD_CALC_PROTO(MOD_NAME)                  METHOD_PROTO(MOD_NAME, METHOD_CALC_M_NAME, METHOD_CALC_RET)
#define METHOD_CALC_IMPL(MOD_NAME, THIS)             METHOD_IMPL(MOD_NAME, THIS, METHOD_CALC_M_NAME, METHOD_CALC_RET)
#define CALC(MOD)                                     CALL(MOD, METHOD_CALC_M_NAME)

// Метод update().
//#define METHOD_UPDATE_M_NAME update
//#define METHOD_UPDATE_RET void
//#define METHOD_UPDATE(MOD_TYPE)                        METHOD(MOD_TYPE, METHOD_UPDATE_M_NAME, METHOD_UPDATE_RET)
//#define METHOD_UPDATE_PTR(MOD_NAME)                    METHOD_PTR(MOD_NAME, METHOD_UPDATE_M_NAME)
//#define METHOD_UPDATE_PROTO(MOD_NAME)                  METHOD_PROTO(MOD_NAME, METHOD_UPDATE_M_NAME, METHOD_UPDATE_RET)
//#define METHOD_UPDATE_IMPL(MOD_NAME, THIS)             METHOD_IMPL(MOD_NAME, THIS, METHOD_UPDATE_M_NAME, METHOD_UPDATE_RET)
//#define UPDATE(MOD)                                     CALL(MOD, METHOD_UPDATE_M_NAME)

// Метод idle().
// Низкоприоритетные работа, вычисления модуля.
#define METHOD_IDLE_M_NAME idle
#define METHOD_IDLE_RET void
#define METHOD_IDLE(MOD_TYPE)                        METHOD(MOD_TYPE, METHOD_IDLE_M_NAME, METHOD_IDLE_RET)
#define METHOD_IDLE_PTR(MOD_NAME)                    METHOD_PTR(MOD_NAME, METHOD_IDLE_M_NAME)
#define METHOD_IDLE_PROTO(MOD_NAME)                  METHOD_PROTO(MOD_NAME, METHOD_IDLE_M_NAME, METHOD_IDLE_RET)
#define METHOD_IDLE_IMPL(MOD_NAME, THIS)             METHOD_IMPL(MOD_NAME, THIS, METHOD_IDLE_M_NAME, METHOD_IDLE_RET)
#define IDLE(MOD)                                     CALL(MOD, METHOD_IDLE_M_NAME)

// Метод cntl().
// Управление модулем беза расчёта.
#define METHOD_CONTROL_M_NAME cntl
#define METHOD_CONTROL_RET void
#define METHOD_CONTROL(MOD_TYPE)                        METHOD(MOD_TYPE, METHOD_CONTROL_M_NAME, METHOD_CONTROL_RET)
#define METHOD_CONTROL_PTR(MOD_NAME)                    METHOD_PTR(MOD_NAME, METHOD_CONTROL_M_NAME)
#define METHOD_CONTROL_PROTO(MOD_NAME)                  METHOD_PROTO(MOD_NAME, METHOD_CONTROL_M_NAME, METHOD_CONTROL_RET)
#define METHOD_CONTROL_IMPL(MOD_NAME, THIS)             METHOD_IMPL(MOD_NAME, THIS, METHOD_CONTROL_M_NAME, METHOD_CONTROL_RET)
#define CONTROL(MOD)                                     CALL(MOD, METHOD_CONTROL_M_NAME)

//// Метод start().
//#define METHOD_START_M_NAME start
//#define METHOD_START_RET void
//#define METHOD_START(MOD_TYPE)                        METHOD(MOD_TYPE, METHOD_START_M_NAME, METHOD_START_RET)
//#define METHOD_START_PTR(MOD_NAME)                    METHOD_PTR(MOD_NAME, METHOD_START_M_NAME)
//#define METHOD_START_PROTO(MOD_NAME)                  METHOD_PROTO(MOD_NAME, METHOD_START_M_NAME, METHOD_START_RET)
//#define METHOD_START_IMPL(MOD_NAME, THIS)             METHOD_IMPL(MOD_NAME, THIS, METHOD_START_M_NAME, METHOD_START_RET)
//#define START(MOD)                                    CALL(MOD, METHOD_START_M_NAME)

//// Метод stop().
//#define METHOD_STOP_M_NAME stop
//#define METHOD_STOP_RET void
//#define METHOD_STOP(MOD_TYPE)                        METHOD(MOD_TYPE, METHOD_STOP_M_NAME, METHOD_STOP_RET)
//#define METHOD_STOP_PTR(MOD_NAME)                    METHOD_PTR(MOD_NAME, METHOD_STOP_M_NAME)
//#define METHOD_STOP_PROTO(MOD_NAME)                  METHOD_PROTO(MOD_NAME, METHOD_STOP_M_NAME, METHOD_STOP_RET)
//#define METHOD_STOP_IMPL(MOD_NAME, THIS)             METHOD_IMPL(MOD_NAME, THIS, METHOD_STOP_M_NAME, METHOD_STOP_RET)
//#define STOP(MOD)                                     CALL(MOD, METHOD_STOP_M_NAME)


/*
// Декларация типа модуля.
typedef struct _S_Test M_test;

struct _S_Test {
    const char* str;
    METHOD(struct _S_Test, print);
    METHOD(M_test, printTest, const char* str);
    M_CALC(M_test);
};


static METHOD_PROTO_S(M_test, struct _S_Test, print);

extern int puts(const char*);
static METHOD_IMPL_S(M_test, struct _S_Test, test, print)
{
    puts(test->str);
}

static M_CALC_PROTO(M_test);

static M_CALC_IMPL(M_test, test)
{
}

static void module_methods_test(void)
{
    struct _S_Test st;
    st.str = "Test\n";
    st.print = METHOD_PTR(M_test, print);
    st.calc = M_CALC_PTR(M_test);

    CALL(st, print);
    CALL(st, printTest, "Test");
    CALC(st);
}
//*/

#endif /* MODULE_METHOD_H */
