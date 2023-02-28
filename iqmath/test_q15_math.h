#ifndef TEST_Q15_MATH_H
#define TEST_Q15_MATH_H


#include <CUnit/CUnit.h>
#include <stdint.h>
#include "q15_math.h"


#define TEST_Q15_PI4 (3.14159265359/4)
#define TEST_Q15_Q15_PI4 0x6487

#define TEST_Q15_SIN_PU_ERRMAX_F (3e-4f)
#define TEST_Q15_SIN_ERRMAX_F (8e-4f)

static void test_q15_sin_pu(void)
{
    float f_val, fq_val;
    q15_t q_val;

    float err, max_err = 0;

    //printf("float sin vs q15 sin pu\n");

    float a;
    int ac = -804;
    while(ac < 804){
        a = (float)ac * M_PI / 180;
        ac ++;

        if(ac == 630 + 1){
            asm("nop");
        }

        f_val = sinf(a);
        q_val = q15_sin_pu(Q15(a/(2*M_PI)));
        fq_val = (float)q_val / Q15_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float sin: %01.08f | q15 sin: %01.08f | abs err: %01.08f\n", a * 180 / M_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_Q15_SIN_PU_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_Q15_SIN_PU_ERRMAX_F);
}

static void test_q15_cos_pu(void)
{
    float f_val, fq_val;
    q15_t q_val;

    float err, max_err = 0;

    //printf("float cos vs q15 cos pu\n");

    float a;
    int ac = -804;
    while(ac < 804){
        a = (float)ac * M_PI / 180;
        ac ++;

        f_val = cosf(a);
        q_val = q15_cos_pu(Q15(a/(2*M_PI)));
        fq_val = (float)q_val / Q15_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float cos: %01.08f | q15 cos: %01.08f | abs err: %01.08f\n", a * 180 / M_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_Q15_SIN_PU_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_Q15_SIN_PU_ERRMAX_F);
}

#undef TEST_Q15_SIN_PU_ERRMAX_F
#undef TEST_Q15_SIN_ERRMAX_F

#define TEST_Q15_SQRT_ERRMAX_F (4e-3)

static void test_q15_sqrt(void)
{
    float f_val, fq_val;
    q15_t q_val;

    float err, max_err = 0;

    //printf("float sqrt vs q15 sqrt\n");

    float a;
    int ac = 0;
    while(ac < 32768){
        a = (float)ac / Q15_BASE;
        ac += 100;

        f_val = sqrtf(a);
        q_val = q15_sqrt(Q15(a));
        fq_val = (float)q_val / Q15_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("value: %03.04f | float sqrt: %01.08f | q15 sqrt: %01.08f | abs err: %01.08f\n", a, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_Q15_SQRT_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_Q15_SQRT_ERRMAX_F);
}

#undef TEST_Q15_SQRT_ERRMAX_F

/*
static void test_q15_(void)
{
    CU_ASSERT_EQUAL(, );
}
*/

#undef TEST_Q15_PI4
#undef TEST_Q15_Q15_PI4

static CU_ErrorCode test_q15_math(void)
{
    CU_pSuite suite = CU_add_suite("Q15 math", NULL, NULL);
    if(suite == NULL) return CU_get_error();

    if(CU_add_test(suite, "q15_sin_pu", test_q15_sin_pu) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_cos_pu", test_q15_cos_pu) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_sqrt", test_q15_sqrt) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "Q15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "Q15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "Q15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "Q15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "Q15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "Q15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "Q15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "Q15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "Q15", test_) == NULL) return CU_get_error();

    return CUE_SUCCESS;
}

#endif /* TEST_Q15_MATH_H */
