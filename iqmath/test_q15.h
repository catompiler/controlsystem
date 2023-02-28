#ifndef TEST_Q15_H
#define TEST_Q15_H

#include <CUnit/CUnit.h>
#include <stdint.h>
#include "q15.h"

#define TEST_Q15_PI_4 (3.14159265359 / 4)
#define TEST_Q15_Q15_PI_4 0x6487

static void test_q15_q15(void)
{
    CU_ASSERT_EQUAL(TEST_Q15_Q15_PI_4, Q15(TEST_Q15_PI_4));
}

static void test_q15_q15i(void)
{
    CU_ASSERT_EQUAL(0xffff8000U, Q15I(-1));
}

static void test_q15_q15f(void)
{
    CU_ASSERT_EQUAL(Q15(0.5), Q15F(1,2));
}

static void test_q15_max(void)
{
    CU_ASSERT_EQUAL(0x7fff, Q15_MAX);
}

static void test_q15_min(void)
{
    CU_ASSERT_EQUAL(0xffff8000, Q15_MIN);
}

static void test_q15_imax(void)
{
    CU_ASSERT_EQUAL(0, Q15_IMAX);
}

static void test_q15_imin(void)
{
    CU_ASSERT_EQUAL(-1, Q15_IMIN);
}

static void test_q15_abs(void)
{
    CU_ASSERT_EQUAL(Q15(TEST_Q15_PI_4), q15_abs(Q15(-TEST_Q15_PI_4)));
}

static void test_q15_int(void)
{
    CU_ASSERT_EQUAL(0, q15_int(Q15(TEST_Q15_PI_4)));
    CU_ASSERT_EQUAL(0, q15_int(Q15(-TEST_Q15_PI_4)));
}

static void test_q15_fract(void)
{
    CU_ASSERT_EQUAL(Q15(TEST_Q15_PI_4), q15_fract(Q15(TEST_Q15_PI_4)));
    CU_ASSERT_EQUAL(Q15(-TEST_Q15_PI_4), q15_fract(Q15(-TEST_Q15_PI_4)));
}

static void test_q15_sat(void)
{
    CU_ASSERT_EQUAL(0x00007fff, q15_sat(0x100000U));
    CU_ASSERT_EQUAL(0xffff8000, q15_sat(-0x100000U));
}

static void test_q15_add(void)
{
    CU_ASSERT_EQUAL(Q15(0.5), q15_add(Q15(0.25), Q15(0.25)));
    CU_ASSERT_EQUAL(Q15(-0.5), q15_add(Q15(-0.25), Q15(-0.25)));
    CU_ASSERT_EQUAL(Q15(0), q15_add(Q15(0.25), Q15(-0.25)));
    CU_ASSERT_EQUAL(Q15(0), q15_add(Q15(-0.25), Q15(0.25)));
}

static void test_q15_add_sat(void)
{
    CU_ASSERT_EQUAL(Q15(0.5), q15_add_sat(Q15(0.25), Q15(0.25)));
    CU_ASSERT_EQUAL(Q15(-0.5), q15_add_sat(Q15(-0.25), Q15(-0.25)));
    CU_ASSERT_EQUAL(Q15(0), q15_add_sat(Q15(0.25), Q15(-0.25)));
    CU_ASSERT_EQUAL(Q15(0), q15_add_sat(Q15(-0.25), Q15(0.25)));
    CU_ASSERT_EQUAL(Q15_MAX, q15_add_sat(Q15(0.25), Q15_MAX));
    CU_ASSERT_EQUAL(Q15_MIN, q15_add_sat(Q15(-0.25), Q15_MIN));
}

static void test_q15_addl(void)
{
    CU_ASSERT_EQUAL(0x00008000UL, q15_addl(Q15(0.5), Q15(0.5)));
}

/*
static void test_q15_iadd(void)
{
    CU_ASSERT_EQUAL(Q15(4), q15_iadd(Q15(2), 2));
    CU_ASSERT_EQUAL(Q15(-4), q15_iadd(Q15(-2), -2));
    CU_ASSERT_EQUAL(Q15(0), q15_iadd(Q15(2), -2));
}

static void test_q15_iadd_sat(void)
{
    CU_ASSERT_EQUAL(Q15(4), q15_iadd_sat(Q15(2), 2));
    CU_ASSERT_EQUAL(Q15(-4), q15_iadd_sat(Q15(-2), -2));
    CU_ASSERT_EQUAL(Q15(0), q15_iadd_sat(Q15(2), -2));
    CU_ASSERT_EQUAL(Q15_MAX, q15_iadd_sat(Q15(2), Q15_IMAX));
    CU_ASSERT_EQUAL(Q15_MIN, q15_iadd_sat(Q15(-2), Q15_IMIN));
}
*/

static void test_q15_iaddl(void)
{
    CU_ASSERT_EQUAL(0x14000U, q15_iaddl(Q15(0.5), 2));
}

static void test_q15_sub(void)
{
    CU_ASSERT_EQUAL(Q15(0), q15_sub(Q15(0.25), Q15(0.25)));
    CU_ASSERT_EQUAL(Q15(0), q15_sub(Q15(-0.25), Q15(-0.25)));
    CU_ASSERT_EQUAL(Q15(-0.5), q15_sub(Q15(-0.25), Q15(0.25)));
    CU_ASSERT_EQUAL(Q15(0.5), q15_sub(Q15(0.25), Q15(-0.25)));
}

static void test_q15_sub_sat(void)
{
    CU_ASSERT_EQUAL(Q15(0), q15_sub_sat(Q15(0.25), Q15(0.25)));
    CU_ASSERT_EQUAL(Q15(0), q15_sub_sat(Q15(-0.25), Q15(-0.25)));
    CU_ASSERT_EQUAL(Q15(-0.5), q15_sub_sat(Q15(-0.25), Q15(0.25)));
    CU_ASSERT_EQUAL(Q15(0.5), q15_sub_sat(Q15(0.25), Q15(-0.25)));
    CU_ASSERT_EQUAL(Q15_MAX, q15_sub_sat(Q15(0.25), Q15_MIN));
    CU_ASSERT_EQUAL(Q15_MIN, q15_sub_sat(Q15(-0.25), Q15_MAX));
}

static void test_q15_subl(void)
{
    CU_ASSERT_EQUAL(0x00008000UL, q15_subl(Q15(0.5), Q15(-0.5)));
}

/*
static void test_q15_isub(void)
{
    CU_ASSERT_EQUAL(Q15(0), q15_isub(Q15(2), 2));
    CU_ASSERT_EQUAL(Q15(0), q15_isub(Q15(-2), -2));
    CU_ASSERT_EQUAL(Q15(-4), q15_isub(Q15(-2), 2));
    CU_ASSERT_EQUAL(Q15(4), q15_isub(Q15(2), -2));
}

static void test_q15_isub_sat(void)
{
    CU_ASSERT_EQUAL(Q15(0), q15_isub_sat(Q15(2), 2));
    CU_ASSERT_EQUAL(Q15(0), q15_isub_sat(Q15(-2), -2));
    CU_ASSERT_EQUAL(Q15(-4), q15_isub_sat(Q15(-2), 2));
    CU_ASSERT_EQUAL(Q15(4), q15_isub_sat(Q15(2), -2));
    CU_ASSERT_EQUAL(Q15_MAX, q15_isub_sat(Q15(2), Q15_IMIN));
    CU_ASSERT_EQUAL(Q15_MIN, q15_isub_sat(Q15(-2), Q15_IMAX));
}
*/

static void test_q15_isubl(void)
{
    CU_ASSERT_EQUAL(0x14000ULL, q15_isubl(Q15(0.5), -2));
}

static void test_q15_mul(void)
{
    CU_ASSERT_EQUAL(Q15(0.0625), q15_mul(Q15(0.25), Q15(0.25)));
    CU_ASSERT_EQUAL(Q15(-0.0625), q15_mul(Q15(0.25), Q15(-0.25)));
    CU_ASSERT_EQUAL(Q15(0.0625), q15_mul(Q15(-0.25), Q15(-0.25)));
}

static void test_q15_mul_sat(void)
{
    CU_ASSERT_EQUAL(Q15(0.0625), q15_mul_sat(Q15(0.25), Q15(0.25)));
    CU_ASSERT_EQUAL(Q15(-0.0625), q15_mul_sat(Q15(0.25), Q15(-0.25)));
    CU_ASSERT_EQUAL(Q15(0.0625), q15_mul_sat(Q15(-0.25), Q15(-0.25)));
    CU_ASSERT_EQUAL(Q15_MAX, q15_mul_sat(Q15(-1), Q15(-1)));
    //CU_ASSERT_EQUAL(Q15_MIN, q15_mul_sat(Q15(100), Q15(-100)));
    //CU_ASSERT_EQUAL(Q15_MAX, q15_mul_sat(Q15(-100), Q15(-100)));
}

static void test_q15_mull(void)
{
    CU_ASSERT_EQUAL(0x8000UL, q15_mull(Q15(-1), Q15(-1)));
    //CU_ASSERT_EQUAL(0x2710000000ULL, q15_mull(Q15(-100), Q15(-100)));
}

static void test_q15_imul(void)
{
    CU_ASSERT_EQUAL(Q15(0.5), q15_imul(Q15(0.25), 2));
    CU_ASSERT_EQUAL(Q15(-0.5), q15_imul(Q15(0.25), -2));
    CU_ASSERT_EQUAL(Q15(0.5), q15_imul(Q15(-0.25), -2));
}

static void test_q15_imul_sat(void)
{
    CU_ASSERT_EQUAL(Q15(0.5), q15_imul_sat(Q15(0.25), 2));
    CU_ASSERT_EQUAL(Q15(-0.5), q15_imul_sat(Q15(0.25), -2));
    CU_ASSERT_EQUAL(Q15(0.5), q15_imul_sat(Q15(-0.25), -2));
    CU_ASSERT_EQUAL(Q15_MAX, q15_imul_sat(Q15(0.5), 10));
    CU_ASSERT_EQUAL(Q15_MIN, q15_imul_sat(Q15(0.5), -10));
    CU_ASSERT_EQUAL(Q15_MAX, q15_imul_sat(Q15(-0.5), -10));
}

static void test_q15_imull(void)
{
    CU_ASSERT_EQUAL(0x10000U, q15_imull(Q15(0.5), 4));
    CU_ASSERT_EQUAL(0x10000U, q15_imull(Q15(-0.5), -4));
    CU_ASSERT_EQUAL(0xffff0000U, q15_imull(Q15(0.5), -4));
}

static void test_q15_div(void)
{
    CU_ASSERT_EQUAL(Q15(0.5), q15_div(Q15(0.125), Q15(0.25)));
    CU_ASSERT_EQUAL(Q15(-1), q15_div(Q15(0.1), Q15(-0.1)));
    CU_ASSERT_EQUAL(Q15(0.5), q15_div(Q15(-0.125), Q15(-0.25)));
    CU_ASSERT_EQUAL(Q15(0.125), q15_div(Q15(-0.125), Q15(-1)));
}

static void test_q15_div_sat(void)
{
    CU_ASSERT_EQUAL(Q15(0.5), q15_div_sat(Q15(0.125), Q15(0.25)));
    CU_ASSERT_EQUAL(Q15(-1), q15_div_sat(Q15(0.1), Q15(-0.1)));
    CU_ASSERT_EQUAL(Q15(0.5), q15_div_sat(Q15(-0.125), Q15(-0.25)));
    CU_ASSERT_EQUAL(Q15(0.125), q15_div_sat(Q15(-0.125), Q15(-1)));
    CU_ASSERT_EQUAL(Q15_MAX, q15_div_sat(Q15(0.1), Q15(0.1)));
    CU_ASSERT_EQUAL(Q15_MAX, q15_div_sat(Q15(-1), Q15(-0.1)));
    CU_ASSERT_EQUAL(Q15_MIN, q15_div_sat(Q15(0.1), Q15(-0.1)));
    CU_ASSERT_EQUAL(Q15_MIN, q15_div_sat(Q15(-1), Q15(0.1)));
}

static void test_q15_divl(void)
{
    CU_ASSERT_EQUAL(0x8000UL, q15_divl(Q15(0.1), Q15(0.1)));
    CU_ASSERT_EQUAL(0x8000UL, q15_divl(Q15(-0.1), Q15(-0.1)));
}

static void test_q15_idiv(void)
{
    CU_ASSERT_EQUAL(Q15(0.25), q15_idiv(Q15(0.5), 2));
    CU_ASSERT_EQUAL(Q15(0.5), q15_idiv(Q15(-1), -2));
}
/*
static void test_q15_(void)
{
    CU_ASSERT_EQUAL(, );
}
*/

#undef TEST_Q15_PI_4
#undef TEST_Q15_Q15_PI_4

static CU_ErrorCode test_q15(void)
{
    CU_pSuite suite = CU_add_suite("Q15", NULL, NULL);
    if(suite == NULL) return CU_get_error();

    if(CU_add_test(suite, "Q15", test_q15_q15) == NULL) return CU_get_error();
    if(CU_add_test(suite, "Q15I", test_q15_q15i) == NULL) return CU_get_error();
    if(CU_add_test(suite, "Q15F", test_q15_q15f) == NULL) return CU_get_error();
    if(CU_add_test(suite, "Q15_MAX", test_q15_max) == NULL) return CU_get_error();
    if(CU_add_test(suite, "Q15_MIN", test_q15_min) == NULL) return CU_get_error();
    if(CU_add_test(suite, "Q15_IMAX", test_q15_imax) == NULL) return CU_get_error();
    if(CU_add_test(suite, "Q15_IMIN", test_q15_imin) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_abs", test_q15_abs) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_int", test_q15_int) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_fract", test_q15_fract) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_sat", test_q15_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_add", test_q15_add) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_add_sat", test_q15_add_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_addl", test_q15_addl) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "q15_iadd", test_q15_iadd) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "q15_iadd_sat", test_q15_iadd_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_iaddl", test_q15_iaddl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_sub", test_q15_sub) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_sub_sat", test_q15_sub_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_subl", test_q15_subl) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "q15_isub", test_q15_isub) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "q15_isub_sat", test_q15_isub_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_isubl", test_q15_isubl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_mul", test_q15_mul) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_mul_sat", test_q15_mul_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_mull", test_q15_mull) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_imul", test_q15_imul) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_imul_sat", test_q15_imul_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_imull", test_q15_imull) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_div", test_q15_div) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_div_sat", test_q15_div_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_divl", test_q15_divl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "q15_idiv", test_q15_idiv) == NULL) return CU_get_error();
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

#endif /* TEST_Q15_H */
