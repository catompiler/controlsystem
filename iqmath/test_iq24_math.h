#ifndef TEST_IQ24_MATH_H
#define TEST_IQ24_MATH_H


#include <CUnit/CUnit.h>
#include <stdint.h>
#include <math.h>
#include "iq24_math.h"


#define TEST_IQ24_PI 3.14159265359
#define TEST_IQ24_IQ24_PI 0x3243F6A



static void test_iq24_floor(void)
{
    CU_ASSERT_EQUAL(IQ24I(3), iq24_floor(TEST_IQ24_IQ24_PI));
}

static void test_iq24_ceil(void)
{
    CU_ASSERT_EQUAL(IQ24I(4), iq24_ceil(TEST_IQ24_IQ24_PI));
    CU_ASSERT_EQUAL(IQ24I(3), iq24_ceil(IQ24I(3)));
}

static void test_iq24_round(void)
{
    CU_ASSERT_EQUAL(IQ24I(3), iq24_round(TEST_IQ24_IQ24_PI));
    CU_ASSERT_EQUAL(IQ24I(4), iq24_round(IQ24(3.5)));
}

static void test_iq24_inv(void)
{
    CU_ASSERT_EQUAL(IQ24(2.0), iq24_inv(IQ24(0.5)));
}

static void test_iq24_inv_sat(void)
{
    CU_ASSERT_EQUAL(IQ24_MAX, iq24_inv_sat(IQ24(0.001)));
}

#define TEST_IQ24_SIN_PU_ERRMAX_F (1e-6f)
#define TEST_IQ24_SIN_ERRMAX_F (2e-6f)

static void test_iq24_sin_pu(void)
{
    float f_val, fq_val;
    iq24_t q_val;

    float err, max_err = 0;

    //printf("float sin vs iq24 sin pu\n");

    float a;
    int ac = -804;
    while(ac < 804){
        a = (float)ac * TEST_IQ24_PI / 180;
        ac ++;

        f_val = sinf(a);
        q_val = iq24_sin_pu(IQ24(a/(2*TEST_IQ24_PI)));
        fq_val = (float)q_val / IQ24_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float sin: %01.08f | iq24 sin: %01.08f | abs err: %01.08f\n", a * 180 / TEST_IQ24_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ24_SIN_PU_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ24_SIN_PU_ERRMAX_F);
}

static void test_iq24_cos_pu(void)
{
    float f_val, fq_val;
    iq24_t q_val;

    float err, max_err = 0;

    //printf("float cos vs iq24 cos pu\n");

    float a;
    int ac = -804;
    while(ac < 804){
        a = (float)ac * TEST_IQ24_PI / 180;
        ac ++;

        f_val = cosf(a);
        q_val = iq24_cos_pu(IQ24(a/(2*TEST_IQ24_PI)));
        fq_val = (float)q_val / IQ24_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float cos: %01.08f | iq24 cos: %01.08f | abs err: %01.08f\n", a * 180 / TEST_IQ24_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ24_SIN_PU_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ24_SIN_PU_ERRMAX_F);
}

static void test_iq24_sin(void)
{
    float f_val, fq_val;
    iq24_t q_val;

    float err, max_err = 0;

    //printf("float sin vs iq24 sin\n");

    float a;
    int ac = -804;
    while(ac < 804){
        a = (float)ac * TEST_IQ24_PI / 180;
        ac ++;

        f_val = sinf(a);
        q_val = iq24_sin(IQ24(a));
        fq_val = (float)q_val / IQ24_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float sin: %01.08f | iq24 sin: %01.08f | abs err: %01.08f\n", a * 180 / TEST_IQ24_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ24_SIN_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ24_SIN_ERRMAX_F);
}

static void test_iq24_cos(void)
{
    float f_val, fq_val;
    iq24_t q_val;

    float err, max_err = 0;

    //printf("float cos vs iq24 cos\n");

    float a;
    int ac = -804;
    while(ac < 804){
        a = (float)ac * TEST_IQ24_PI / 180;
        ac ++;

        f_val = cosf(a);
        q_val = iq24_cos(IQ24(a));
        fq_val = (float)q_val / IQ24_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float cos: %01.08f | iq24 cos: %01.08f | abs err: %01.08f\n", a * 180 / TEST_IQ24_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ24_SIN_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ24_SIN_ERRMAX_F);
}

#undef TEST_IQ24_SIN_PU_ERRMAX_F
#undef TEST_IQ24_SIN_ERRMAX_F

#define TEST_IQ24_SQRT_ERRMAX_F (1e-6)

static void test_iq24_sqrt(void)
{
    float f_val, fq_val;
    iq24_t q_val;

    float err, max_err = 0;

    //printf("float sqrt vs iq24 sqrt\n");

    float a;
    int ac = 0;
    while(ac < 1271){
        a = (float)ac / 10;
        ac ++;

        f_val = sqrtf(a);
        q_val = iq24_sqrt(IQ24(a));
        fq_val = (float)q_val / IQ24_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("value: %03.04f | float sqrt: %01.08f | iq24 sqrt: %01.08f | abs err: %01.08f\n", a, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ24_SQRT_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ24_SQRT_ERRMAX_F);
}

#undef TEST_IQ24_SQRT_ERRMAX_F

static void test_iq24_angle_norm_pu(void)
{
    CU_ASSERT_EQUAL(IQ24_2PI_PU-1, iq24_angle_norm_pu(-1));
}

static void test_iq24_lerp(void)
{
    CU_ASSERT_EQUAL(IQ24(0), iq24_lerp(IQ24(0), IQ24(1), IQ24(0)));
    CU_ASSERT_EQUAL(IQ24(1), iq24_lerp(IQ24(0), IQ24(1), IQ24(1)));
    CU_ASSERT_EQUAL(IQ24(0.25), iq24_lerp(IQ24(0), IQ24(1), IQ24(0.25)));
    CU_ASSERT_EQUAL(IQ24(0.5), iq24_lerp(IQ24(0), IQ24(1), IQ24(0.5)));
    CU_ASSERT_EQUAL(IQ24(0.75), iq24_lerp(IQ24(0), IQ24(1), IQ24(0.75)));
}

/*
static void test_iq24_(void)
{
    CU_ASSERT_EQUAL(, );
}
*/

#undef TEST_IQ24_PI
#undef TEST_IQ24_IQ24_PI

static CU_ErrorCode test_iq24_math(void)
{
    CU_pSuite suite = CU_add_suite("IQ24 math", NULL, NULL);
    if(suite == NULL) return CU_get_error();

    if(CU_add_test(suite, "iq24_floor", test_iq24_floor) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_ceil", test_iq24_ceil) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_round", test_iq24_round) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_inv", test_iq24_inv) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_inv_sat", test_iq24_inv_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_sin_pu", test_iq24_sin_pu) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_cos_pu", test_iq24_cos_pu) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_sin", test_iq24_sin) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_cos", test_iq24_cos) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_sqrt", test_iq24_sqrt) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_angle_norm_pu", test_iq24_angle_norm_pu) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_lerp", test_iq24_lerp) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ24", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ24", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ24", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ24", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ24", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ24", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ24", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ24", test_) == NULL) return CU_get_error();

    return CUE_SUCCESS;
}

#endif /* TEST_IQ24_MATH_H */
