#ifndef REG_LIST_H
#define REG_LIST_H

#include "reg.h"
#include "reg_ids.h"


/*
 * Начало массива регистров с именем NAME.
 * Для обеспечения поиска регистра по идентификатору,
 * регистры в массиве должны находиться в порядке
 * возрастания значения идентификатора.
 */
#define REGS_BEGIN(NAME) static const reg_t NAME[] = {
/*
 * Элемент массива регистров.
 * ID - идентификатор регистра.
 * DATA - Переменная с данными (берётся указатель).
 * TYPE - Тип данных.
 * //DEF - Значение по-умолчанию.
 * //FLG - Флаги.
 */
#define REG(ID, DATA, TYPE, FLAG) {ID, (void*)&DATA, TYPE, FLAG},
/*
 * Окончание массива регистров.
 */
#define REGS_END() };

/*
 * Значение количества регистров в массиве с именем NAME.
 */
#define REGS_COUNT_VALUE(NAME) (sizeof(NAME)/sizeof(NAME[0]))


#define REG_ARRAY_NAME regs
#include "reg_list_data.h"


#endif /* REG_LIST_H */
