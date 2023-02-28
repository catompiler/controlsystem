#ifndef TEST_IQ24_CORDIC_H
#define TEST_IQ24_CORDIC_H


#include <CUnit/CUnit.h>
#include <stdint.h>
#include "iq24_cordic.h"


#define TEST_IQ24_PI 3.14159265359
#define TEST_IQ24_IQ24_PI 0x3243F6A

#define TEST_IQ24_SIN_PU_ERRMAX_F (2e-6f)
#define TEST_IQ24_SIN_ERRMAX_F (2e-6f)


static void test_iq24_cordic_atan2_pu(void)
{
    float f_val, fx, fy, fq_val;
    iq24_t q_val;

    float err, max_err = 0;

    //printf("float atan2 vs iq24 atan2 pu\n");

    float a;
    int ac = -359;
    while(ac < 359){
        a = (float)ac * M_PI / 180;
        ac ++;

        fx = cosf(a);
        fy = sinf(a);
        f_val = atan2f(fy, fx);
        if(f_val < 0) f_val += 2*M_PI;
        iq24_cordic_atan2_hyp_pu(IQ24(fx), IQ24(fy), &q_val, NULL);
        fq_val = (float)q_val * 2 * M_PI / IQ24_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float atan2: %01.08f | iq24 atan2: %01.08f | abs err: %01.08f\n", a * 180 / M_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ24_SIN_PU_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ24_SIN_PU_ERRMAX_F);
}

static void test_iq24_cordic_atan2(void)
{
    float f_val, fx, fy, fq_val;
    iq24_t q_val;

    float err, max_err = 0;

    //printf("float atan2 vs iq24 atan2 pu\n");

    float a;
    int ac = -359;
    while(ac < 359){
        a = (float)ac * M_PI / 180;
        ac ++;

        fx = cosf(a);
        fy = sinf(a);
        f_val = atan2f(fy, fx);
        if(f_val < 0) f_val += 2*M_PI;
        iq24_cordic_atan2_hyp(IQ24(fx), IQ24(fy), &q_val, NULL);
        fq_val = (float)q_val / IQ24_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float atan2: %01.08f | iq24 atan2: %01.08f | abs err: %01.08f\n", a * 180 / M_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ24_SIN_PU_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ24_SIN_PU_ERRMAX_F);
}

static void test_iq24_cordic_hyp(void)
{
    float f_val, fx, fy, fq_val;
    iq24_t q_val;

    float err, max_err = 0;

    //printf("float atan2 vs iq24 atan2 pu\n");

    float a;
    int ac = -359;
    while(ac < 359){
        a = (float)ac * M_PI / 180;
        ac ++;

        fx = cosf(a);
        fy = sinf(a);
        f_val = sqrtf(fx*fx + fy*fy);
        iq24_cordic_atan2_hyp_pu(IQ24(fx), IQ24(fy), NULL, &q_val);
        fq_val = (float)q_val / IQ24_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float atan2: %01.08f | iq24 atan2: %01.08f | abs err: %01.08f\n", a * 180 / M_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ24_SIN_PU_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ24_SIN_PU_ERRMAX_F);
}

static void test_iq24_cordic_sin_pu(void)
{
    float f_val, fq_val;
    iq24_t q_val;

    float err, max_err = 0;

    //printf("float sin vs iq24 sin pu\n");

    float a;
    int ac = -359;
    while(ac < 359){
        a = (float)ac * M_PI / 180;
        ac ++;

        f_val = sinf(a);
        iq24_cordic_sincos_pu(IQ24(a/(2*M_PI)), &q_val, NULL);
        fq_val = (float)q_val / IQ24_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float sin: %01.08f | iq24 sin: %01.08f | abs err: %01.08f\n", a * 180 / M_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ24_SIN_PU_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ24_SIN_PU_ERRMAX_F);
}

static void test_iq24_cordic_cos_pu(void)
{
    float f_val, fq_val;
    iq24_t q_val;

    float err, max_err = 0;

    //printf("float cos vs iq24 cos pu\n");

    float a;
    int ac = -359;
    while(ac < 359){
        a = (float)ac * M_PI / 180;
        ac ++;

        f_val = cosf(a);
        iq24_cordic_sincos_pu(IQ24(a/(2*M_PI)), NULL, &q_val);
        fq_val = (float)q_val / IQ24_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float cos: %01.08f | iq24 cos: %01.08f | abs err: %01.08f\n", a * 180 / M_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ24_SIN_PU_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ24_SIN_PU_ERRMAX_F);
}

static void test_iq24_cordic_sin(void)
{
    float f_val, fq_val;
    iq24_t q_val;

    float err, max_err = 0;

    //printf("float sin vs iq24 sin\n");

    float a;
    int ac = -359;
    while(ac < 359){
        a = (float)ac * M_PI / 180;
        ac ++;

        f_val = sinf(a);
        iq24_cordic_sincos(IQ24(a), &q_val, NULL);
        fq_val = (float)q_val / IQ24_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float sin: %01.08f | iq24 sin: %01.08f | abs err: %01.08f\n", a * 180 / M_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ24_SIN_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ24_SIN_ERRMAX_F);
}

static void test_iq24_cordic_cos(void)
{
    float f_val, fq_val;
    iq24_t q_val;

    float err, max_err = 0;

    //printf("float cos vs iq24 cos\n");

    float a;
    int ac = -359;
    while(ac < 359){
        a = (float)ac * M_PI / 180;
        ac ++;

        f_val = cosf(a);
        iq24_cordic_sincos(IQ24(a), NULL, &q_val);
        fq_val = (float)q_val / IQ24_BASE;

        err = fabs(fq_val - f_val);

        if(max_err < err) max_err = err;

        //printf("angle: %03.04f | float cos: %01.08f | iq24 cos: %01.08f | abs err: %01.08f\n", a * 180 / M_PI, f_val, fq_val, err);
        //CU_ASSERT_DOUBLE_EQUAL(f_val, fq_val, TEST_IQ24_SIN_ERRMAX_F);
    }

    //printf("max err: %01.08f\n", max_err);
    CU_ASSERT_TRUE(max_err < TEST_IQ24_SIN_ERRMAX_F);
}

#undef TEST_IQ24_SIN_PU_ERRMAX_F
#undef TEST_IQ24_SIN_ERRMAX_F

/*
static void test_iq24_(void)
{
    CU_ASSERT_EQUAL(, );
}
*/

#undef TEST_IQ24_PI
#undef TEST_IQ24_IQ24_PI

static CU_ErrorCode test_iq24_cordic(void)
{
    CU_pSuite suite = CU_add_suite("IQ24 cordic", NULL, NULL);
    if(suite == NULL) return CU_get_error();

    if(CU_add_test(suite, "iq24_cordic_atan2_pu", test_iq24_cordic_atan2_pu) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_cordic_atan2", test_iq24_cordic_atan2) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_cordic_hyp", test_iq24_cordic_hyp) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_cordic_sin_pu", test_iq24_cordic_sin_pu) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_cordic_cos_pu", test_iq24_cordic_cos_pu) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_cordic_sin", test_iq24_cordic_sin) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_cordic_cos", test_iq24_cordic_cos) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ24", test_) == NULL) return CU_get_error();
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

#endif /* TEST_IQ24_CORDIC_H */
