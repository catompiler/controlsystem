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



#endif /* REG_REGS_H */
