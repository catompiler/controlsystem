#ifndef IQ_H
#define IQ_H

#include <stdint.h>
#include "iq_types.h"
#include "iqn.h"
#include "iq_intrinsics.h"

//! Преобразовывает число с фиксированной запятой
//! из формата Qn в формат Qm.
#define IQ_N_TO_M(Q, N, M) IQN_N_TO_M(Q, N, M)

#endif /* IQ_H */
