#ifndef REG_REGS_H
#define REG_REGS_H

#include "defs/defs.h"
#include "reg.h"
#include "reg_ids.h"


/**
 * Ищет регистр по идентификатору.
 * @param id Идентификатор.
 * @return Указатель на найденный регистр, либо NULL.
 */
EXTERN reg_t* regs_find(reg_id_t id);

/**
 * Получает первый регистр в списке.
 * @return Первый регистр в списке.
 */
EXTERN reg_t* regs_first(void);

/**
 * Получает конец списка регистров.
 * @return Конец списка регистров.
 */
EXTERN reg_t* regs_end(void);

/**
 * Получает следующий регистр в списке. NULL если регистров больше нет.
 * @param reg Текущий регистр.
 * @return Следующий регистр в списке. NULL если регистров больше нет.
 */
EXTERN reg_t* regs_next(reg_t* reg);

/**
 * Получает регистр с заданном номером в списке, либо NULL.
 * @param n Номер регистра.
 * @return Регистр с заданном номером в списке, либо NULL.
 */
EXTERN reg_t* regs_reg(size_t n);

/**
 * Получает количество регистров.
 * @return Количество регистров.
 */
EXTERN size_t regs_count();

#endif /* REG_REGS_H */
