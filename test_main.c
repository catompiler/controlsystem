#if defined(PORT_POSIX)

#include "test_main.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdio.h>
#include "iqmath/test_iqn.h"
#include "iqmath/test_iq_intrinsics.h"
#include "iqmath/test_iq24.h"
#include "iqmath/test_iq24_math.h"
#include "iqmath/test_iq15.h"
#include "iqmath/test_iq15_math.h"
#include "iqmath/test_q15.h"
#include "iqmath/test_q15_math.h"
#include "iqmath/test_iq24_cordic.h"
#include "iqmath/test_iq15_cordic.h"
#include "iqmath/test_iq7.h"
#include "iqmath/test_iqutils.h"


int test_main(void)
{
    if(CU_initialize_registry() != CUE_SUCCESS){
        return -1;
    }

    if(test_iqn() != CUE_SUCCESS){
        printf("test_iqn() cunit error: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return -1;
    }

    if(test_iq_intrinsics() != CUE_SUCCESS){
        printf("test_iq_intrinsics() cunit error: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return -1;
    }

    if(test_iq24() != CUE_SUCCESS){
        printf("test_iq24() cunit error: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return -1;
    }

    if(test_iq24_math() != CUE_SUCCESS){
        printf("test_iq24_math() cunit error: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return -1;
    }

    if(test_iq15() != CUE_SUCCESS){
        printf("test_iq15() cunit error: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return -1;
    }

    if(test_iq15_math() != CUE_SUCCESS){
        printf("test_iq15_math() cunit error: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return -1;
    }

    if(test_q15() != CUE_SUCCESS){
        printf("test_q15() cunit error: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return -1;
    }

    if(test_q15_math() != CUE_SUCCESS){
        printf("test_q15_math() cunit error: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return -1;
    }

    if(test_iq24_cordic() != CUE_SUCCESS){
        printf("test_iq24_cordic() cunit error: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return -1;
    }

    if(test_iq15_cordic() != CUE_SUCCESS){
        printf("test_iq15_cordic() cunit error: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return -1;
    }

    if(test_iq7() != CUE_SUCCESS){
        printf("test_iq7() cunit error: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return -1;
    }

    if(test_iqutils() != CUE_SUCCESS){
        printf("test_iqutils() cunit error: %s\n", CU_get_error_msg());
        CU_cleanup_registry();
        return -1;
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    CU_cleanup_registry();

    return 0;
}

#endif
