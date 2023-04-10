#include "regs.h"
#include <stdlib.h>
#include "reg_list.h"


/**
 * Функция сравнения двух регистров по идентификатору.
 * @param a Параметр А.
 * @param b Параметр Б.
 * @return Результат сравнения.
 */
static int regs_compare_ids(const void * key, const void * item)
{
    const reg_t* reg = (const reg_t*)item;
    reg_id_t item_id = reg->id;
    reg_id_t key_id = (reg_id_t)(unsigned long)key;

    if(key_id > item_id) return 1;
    if(key_id < item_id) return -1;

    return 0;
}

reg_t* regs_find(reg_id_t id)
{
    reg_t* reg = bsearch((const void*)(unsigned long)id,
                           (const void*)regs, REGS_COUNT, sizeof(reg_t),
                           regs_compare_ids);

    return reg;
}


