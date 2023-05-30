#ifndef TEST_IQ15_MATH_H
#define TEST_IQ15_MATH_H


#include <CUnit/CUnit.h>
#include <stdint.h>
#include "iq15_math.h"


#define TEST_IQ15_PI 3.14159265359
#define TEST_IQ15_IQ15_PI 0x1921F

static void test_iq15_floor(void)
{
    CU_ASSERT_EQUAL(IQ15I(3), iq15_floor(TEST_IQ15_IQ15_PI));
}

static void test_iq15_ceil(void)
{
    CU_ASSERT_EQUAL(IQ15I(4), iq15_ceil(TEST_IQ15_IQ15_PI));
    CU_ASSERT_EQUAL(IQ15I(3), iq15_ceil(IQ15I(3)));
}

static void test_iq15_round(void)
{
    CU_ASSERT_EQUAL(IQ15I(3), iq15_round(TEST_IQ15_IQ15_PI));
    CU_ASSERT_EQUAL(IQ15I(4), iq15_round(IQ15(3.5)));
}

#define TEST_IQ15_SIN_PU_ERRMAX_F (3e-4f)
#define TEST_IQ15_SIN_ERRMAX_F (8e-4f)

static void test_iq15_sin_pu(void)
{
    float f_val, fq_val;
    iq15_t q_val;

    float err, max_err = 0;

    //printf("float sin vs iq15 sin pu\n");

    float a;
    int ac = -804;
    while(ac < 804){
        a = (float)ac * TEST_IQ15_PI / 180;
        ac ++;

        f_val = sinf(a);
        q_val = iq15_sin_pu(IQ15(a/(2*TEST_IQ15_PI)));
        fq_val = (float)q_val / IQ15_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float sin: %01.08f | iq15 sin: %01.08f | abs err: %01.08f\n", a * 180 / TEST_IQ15_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ15_SIN_PU_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ15_SIN_PU_ERRMAX_F);
}

static void test_iq15_cos_pu(void)
{
    float f_val, fq_val;
    iq15_t q_val;

    float err, max_err = 0;

    //printf("float cos vs iq15 cos pu\n");

    float a;
    int ac = -804;
    while(ac < 804){
        a = (float)ac * TEST_IQ15_PI / 180;
        ac ++;

        f_val = cosf(a);
        q_val = iq15_cos_pu(IQ15(a/(2*TEST_IQ15_PI)));
        fq_val = (float)q_val / IQ15_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float cos: %01.08f | iq15 cos: %01.08f | abs err: %01.08f\n", a * 180 / TEST_IQ15_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ15_SIN_PU_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ15_SIN_PU_ERRMAX_F);
}

static void test_iq15_sin(void)
{
    float f_val, fq_val;
    iq15_t q_val;

    float err, max_err = 0;

    //printf("float sin vs iq15 sin\n");

    float a;
    int ac = -804;
    while(ac < 804){
        a = (float)ac * TEST_IQ15_PI / 180;
        ac ++;

        f_val = sinf(a);
        q_val = iq15_sin(IQ15(a));
        fq_val = (float)q_val / IQ15_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float sin: %01.08f | iq15 sin: %01.08f | abs err: %01.08f\n", a * 180 / TEST_IQ15_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ15_SIN_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ15_SIN_ERRMAX_F);
}

static void test_iq15_cos(void)
{
    float f_val, fq_val;
    iq15_t q_val;

    float err, max_err = 0;

    //printf("float cos vs iq15 cos\n");

    float a;
    int ac = -804;
    while(ac < 804){
        a = (float)ac * TEST_IQ15_PI / 180;
        ac ++;

        f_val = cosf(a);
        q_val = iq15_cos(IQ15(a));
        fq_val = (float)q_val / IQ15_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float cos: %01.08f | iq15 cos: %01.08f | abs err: %01.08f\n", a * 180 / TEST_IQ15_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ15_SIN_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ15_SIN_ERRMAX_F);
}

#undef TEST_IQ15_SIN_PU_ERRMAX_F
#undef TEST_IQ15_SIN_ERRMAX_F

#define TEST_IQ15_SQRT_ERRMAX_F (4e-3)

static void test_iq15_sqrt(void)
{
    float f_val, fq_val;
    iq15_t q_val;

    float err, max_err = 0;

    //printf("float sqrt vs iq15 sqrt\n");

    float a;
    int ac = 0;
    while(ac < 65536){
        a = (float)ac;
        ac += 100;

        f_val = sqrtf(a);
        q_val = iq15_sqrt(IQ15(a));
        fq_val = (float)q_val / IQ15_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("value: %03.04f | float sqrt: %01.08f | iq15 sqrt: %01.08f | abs err: %01.08f\n", a, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ15_SQRT_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ15_SQRT_ERRMAX_F);
}

#undef TEST_IQ15_SQRT_ERRMAX_F

/*
static void test_iq15_(void)
{
    CU_ASSERT_EQUAL(, );
}
*/

#undef TEST_IQ15_PI
#undef TEST_IQ15_IQ15_PI

static CU_ErrorCode test_iq15_math(void)
{
    CU_pSuite suite = CU_add_suite("IQ15 math", NULL, NULL);
    if(suite == NULL) return CU_get_error();

    if(CU_add_test(suite, "iq15_floor", test_iq15_floor) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_ceil", test_iq15_ceil) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_round", test_iq15_round) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_sin_pu", test_iq15_sin_pu) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_cos_pu", test_iq15_cos_pu) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_sin", test_iq15_sin) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_cos", test_iq15_cos) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_sqrt", test_iq15_sqrt) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ15", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ15", test_) == NULL) return CU_get_error();

    return CUE_SUCCESS;
}

#endif /* TEST_IQ15_MATH_H */
