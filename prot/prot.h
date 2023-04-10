#ifndef PROT_PROT_H
#define PROT_PROT_H

#include "module/base.h"


//! Перечисление возможных бит ошибок слова 0.
enum _E_Ptor_Errors0 {
    PROT_ERR0_NONE = ERROR_NONE, //!< Нет ошибок.

    PROT_ERR0_INTERNAL_SW = 0x01, //!< Ошибка ПО.
    PROT_ERR0_INTERNAL_HW = 0x02, //!< Ошибка аппаратной части.

    //PROT_ERR0_ = 0x00, //!< .
};

//! Перечисление возможных бит ошибок слова 1.
enum _E_Prot_Errors1 {
    PROT_ERR1_NONE = ERROR_NONE, //!< Нет ошибок.

    PROT_ERR1_PWR_UA_OVF = 0x01, //!< Повышение напряжения фазы A.
    PROT_ERR1_PWR_UA_UDF = 0x02, //!< Понижение напряжения фазы A.
    PROT_ERR1_PWR_UB_OVF = 0x04, //!< Повышение напряжения фазы B.
    PROT_ERR1_PWR_UB_UDF = 0x08, //!< Понижение напряжения фазы B.
    PROT_ERR1_PWR_UC_OVF = 0x10, //!< Повышение напряжения фазы C.
    PROT_ERR1_PWR_UC_UDF = 0x20, //!< Понижение напряжения фазы C.

    PROT_ERR1_PWR_IA_OVF = 0x40, //!< Повышение тока фазы A.
    PROT_ERR1_PWR_IB_OVF = 0x80, //!< Повышение тока фазы B.
    PROT_ERR1_PWR_IC_OVF = 0x100, //!< Повышение тока фазы C.

    //PROT_ERR1_ = 0x00, //!< .
};


//! Перечисление возможных бит предупреждений.
enum _E_Prot_Warnings {
    PROT_WARN0_NONE = WARNING_NONE, //!< Нет предупреждений.

    //PROT_WARN0_ = 0x00, //!<
};

#endif /* PROT_PROT_H */
