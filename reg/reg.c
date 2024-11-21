#include "reg.h"
#include <stddef.h>



iql_t reg_valuel(const reg_t* reg)
{
	if(reg == NULL) return 0;

	iql_t val = 0;

	switch(reg->type){
	default:
		break;
	case REG_TYPE_I8:
		val = (iql_t)reg_value_i8(reg);
		break;
	case REG_TYPE_I16:
		val = (iql_t)reg_value_i16(reg);
		break;
	case REG_TYPE_I32:
		val = (iql_t)reg_value_i32(reg);
		break;
	case REG_TYPE_U8:
		val = (iql_t)reg_value_u8(reg);
		break;
	case REG_TYPE_U16:
		val = (iql_t)reg_value_u16(reg);
		break;
	case REG_TYPE_U32:
		val = (iql_t)reg_value_u32(reg);
		break;
	case REG_TYPE_IQ24:
		val = (iql_t)reg_value_iq24(reg);
		break;
	case REG_TYPE_IQ15:
		val = (iql_t)reg_value_iq15(reg);
		break;
	case REG_TYPE_IQ7:
		val = (iql_t)reg_value_iq7(reg);
		break;
	}
	return val;
}
