#ifndef TEST_IQ24_H
#define TEST_IQ24_H

#include <CUnit/CUnit.h>
#include <stdint.h>
#include "iq24.h"

#define TEST_IQ24_PI 3.14159265359
#define TEST_IQ24_IQ24_PI 0x3243F6A

static void test_iq24_iq24(void)
{
    CU_ASSERT_EQUAL(TEST_IQ24_IQ24_PI, IQ24(TEST_IQ24_PI));
}

static void test_iq24_iq24i(void)
{
    CU_ASSERT_EQUAL(0x03000000, IQ24I(3));
}

static void test_iq24_iq24f(void)
{
    CU_ASSERT_EQUAL(IQ24(0.5), IQ24F(1,2));
}

static void test_iq24_max(void)
{
    CU_ASSERT_EQUAL(0x7fffffff, IQ24_MAX);
}

static void test_iq24_min(void)
{
    CU_ASSERT_EQUAL(0x80000000, IQ24_MIN);
}

static void test_iq24_imax(void)
{
    CU_ASSERT_EQUAL(127, IQ24_IMAX);
}

static void test_iq24_imin(void)
{
    CU_ASSERT_EQUAL(-128, IQ24_IMIN);
}

static void test_iq24_abs(void)
{
    CU_ASSERT_EQUAL(IQ24(TEST_IQ24_PI), iq24_abs(IQ24(-TEST_IQ24_PI)));
}

static void test_iq24_int(void)
{
    CU_ASSERT_EQUAL(3, iq24_int(IQ24(TEST_IQ24_PI)));
    CU_ASSERT_EQUAL(-3, iq24_int(IQ24(-TEST_IQ24_PI)));
}

static void test_iq24_fract(void)
{
    CU_ASSERT_EQUAL(IQ24(TEST_IQ24_PI-3), iq24_fract(IQ24(TEST_IQ24_PI)));
    CU_ASSERT_EQUAL(IQ24(3-TEST_IQ24_PI), iq24_fract(IQ24(-TEST_IQ24_PI)));
}

static void test_iq24_sat(void)
{
    CU_ASSERT_EQUAL(0x7fffffff, iq24_sat(0x100000000ULL));
    CU_ASSERT_EQUAL(0x80000000, iq24_sat(-0x100000000ULL));
}

static void test_iq24_add(void)
{
    CU_ASSERT_EQUAL(IQ24(4), iq24_add(IQ24(2), IQ24(2)));
    CU_ASSERT_EQUAL(IQ24(-4), iq24_add(IQ24(-2), IQ24(-2)));
    CU_ASSERT_EQUAL(IQ24(0), iq24_add(IQ24(2), IQ24(-2)));
    CU_ASSERT_EQUAL(IQ24(0), iq24_add(IQ24(-2), IQ24(2)));
}

static void test_iq24_add_sat(void)
{
    CU_ASSERT_EQUAL(IQ24(4), iq24_add_sat(IQ24(2), IQ24(2)));
    CU_ASSERT_EQUAL(IQ24(-4), iq24_add_sat(IQ24(-2), IQ24(-2)));
    CU_ASSERT_EQUAL(IQ24(0), iq24_add_sat(IQ24(2), IQ24(-2)));
    CU_ASSERT_EQUAL(IQ24(0), iq24_add_sat(IQ24(-2), IQ24(2)));
    CU_ASSERT_EQUAL(IQ24_MAX, iq24_add_sat(IQ24(2), IQ24_MAX));
    CU_ASSERT_EQUAL(IQ24_MIN, iq24_add_sat(IQ24(-2), IQ24_MIN));
}

static void test_iq24_addl(void)
{
    CU_ASSERT_EQUAL(0x80000000ULL, iq24_addl(IQ24(127), IQ24(1)));
}

static void test_iq24_iadd(void)
{
    CU_ASSERT_EQUAL(IQ24(4), iq24_iadd(IQ24(2), 2));
    CU_ASSERT_EQUAL(IQ24(-4), iq24_iadd(IQ24(-2), -2));
    CU_ASSERT_EQUAL(IQ24(0), iq24_iadd(IQ24(2), -2));
}

static void test_iq24_iadd_sat(void)
{
    CU_ASSERT_EQUAL(IQ24(4), iq24_iadd_sat(IQ24(2), 2));
    CU_ASSERT_EQUAL(IQ24(-4), iq24_iadd_sat(IQ24(-2), -2));
    CU_ASSERT_EQUAL(IQ24(0), iq24_iadd_sat(IQ24(2), -2));
    CU_ASSERT_EQUAL(IQ24_MAX, iq24_iadd_sat(IQ24(2), IQ24_IMAX));
    CU_ASSERT_EQUAL(IQ24_MIN, iq24_iadd_sat(IQ24(-2), IQ24_IMIN));
}

static void test_iq24_iaddl(void)
{
    CU_ASSERT_EQUAL(0x80000000ULL, iq24_iaddl(IQ24(0), 128));
}

static void test_iq24_sub(void)
{
    CU_ASSERT_EQUAL(IQ24(0), iq24_sub(IQ24(2), IQ24(2)));
    CU_ASSERT_EQUAL(IQ24(0), iq24_sub(IQ24(-2), IQ24(-2)));
    CU_ASSERT_EQUAL(IQ24(-4), iq24_sub(IQ24(-2), IQ24(2)));
    CU_ASSERT_EQUAL(IQ24(4), iq24_sub(IQ24(2), IQ24(-2)));
}

static void test_iq24_sub_sat(void)
{
    CU_ASSERT_EQUAL(IQ24(0), iq24_sub_sat(IQ24(2), IQ24(2)));
    CU_ASSERT_EQUAL(IQ24(0), iq24_sub_sat(IQ24(-2), IQ24(-2)));
    CU_ASSERT_EQUAL(IQ24(-4), iq24_sub_sat(IQ24(-2), IQ24(2)));
    CU_ASSERT_EQUAL(IQ24(4), iq24_sub_sat(IQ24(2), IQ24(-2)));
    CU_ASSERT_EQUAL(IQ24_MAX, iq24_sub_sat(IQ24(2), IQ24_MIN));
    CU_ASSERT_EQUAL(IQ24_MIN, iq24_sub_sat(IQ24(-2), IQ24_MAX));
}

static void test_iq24_subl(void)
{
    CU_ASSERT_EQUAL(0x80000000ULL, iq24_subl(IQ24(0), IQ24(-128)));
}

static void test_iq24_isub(void)
{
    CU_ASSERT_EQUAL(IQ24(0), iq24_isub(IQ24(2), 2));
    CU_ASSERT_EQUAL(IQ24(0), iq24_isub(IQ24(-2), -2));
    CU_ASSERT_EQUAL(IQ24(-4), iq24_isub(IQ24(-2), 2));
    CU_ASSERT_EQUAL(IQ24(4), iq24_isub(IQ24(2), -2));
}

static void test_iq24_isub_sat(void)
{
    CU_ASSERT_EQUAL(IQ24(0), iq24_isub_sat(IQ24(2), 2));
    CU_ASSERT_EQUAL(IQ24(0), iq24_isub_sat(IQ24(-2), -2));
    CU_ASSERT_EQUAL(IQ24(-4), iq24_isub_sat(IQ24(-2), 2));
    CU_ASSERT_EQUAL(IQ24(4), iq24_isub_sat(IQ24(2), -2));
    CU_ASSERT_EQUAL(IQ24_MAX, iq24_isub_sat(IQ24(2), IQ24_IMIN));
    CU_ASSERT_EQUAL(IQ24_MIN, iq24_isub_sat(IQ24(-2), IQ24_IMAX));
}

static void test_iq24_isubl(void)
{
    CU_ASSERT_EQUAL(0x80000000ULL, iq24_isubl(IQ24(0), -128));
}

static void test_iq24_mul(void)
{
    CU_ASSERT_EQUAL(IQ24(4), iq24_mul(IQ24(2), IQ24(2)));
    CU_ASSERT_EQUAL(IQ24(-4), iq24_mul(IQ24(2), IQ24(-2)));
    CU_ASSERT_EQUAL(IQ24(4), iq24_mul(IQ24(-2), IQ24(-2)));
}

static void test_iq24_mul_sat(void)
{
    CU_ASSERT_EQUAL(IQ24(4), iq24_mul_sat(IQ24(2), IQ24(2)));
    CU_ASSERT_EQUAL(IQ24(-4), iq24_mul_sat(IQ24(2), IQ24(-2)));
    CU_ASSERT_EQUAL(IQ24(4), iq24_mul_sat(IQ24(-2), IQ24(-2)));
    CU_ASSERT_EQUAL(IQ24_MAX, iq24_mul_sat(IQ24(100), IQ24(100)));
    CU_ASSERT_EQUAL(IQ24_MIN, iq24_mul_sat(IQ24(100), IQ24(-100)));
    CU_ASSERT_EQUAL(IQ24_MAX, iq24_mul_sat(IQ24(-100), IQ24(-100)));
}

static void test_iq24_mull(void)
{
    CU_ASSERT_EQUAL(0x2710000000ULL, iq24_mull(IQ24(100), IQ24(100)));
    CU_ASSERT_EQUAL(0x2710000000ULL, iq24_mull(IQ24(-100), IQ24(-100)));
}

static void test_iq24_imul(void)
{
    CU_ASSERT_EQUAL(IQ24(4), iq24_imul(IQ24(2), 2));
    CU_ASSERT_EQUAL(IQ24(-4), iq24_imul(IQ24(2), -2));
    CU_ASSERT_EQUAL(IQ24(4), iq24_imul(IQ24(-2), -2));
}

static void test_iq24_imul_sat(void)
{
    CU_ASSERT_EQUAL(IQ24(4), iq24_imul_sat(IQ24(2), 2));
    CU_ASSERT_EQUAL(IQ24(-4), iq24_imul_sat(IQ24(2), -2));
    CU_ASSERT_EQUAL(IQ24(4), iq24_imul_sat(IQ24(-2), -2));
    CU_ASSERT_EQUAL(IQ24_MAX, iq24_imul_sat(IQ24(100), 100));
    CU_ASSERT_EQUAL(IQ24_MIN, iq24_imul_sat(IQ24(100), -100));
    CU_ASSERT_EQUAL(IQ24_MAX, iq24_imul_sat(IQ24(-100), -100));
}

static void test_iq24_imull(void)
{
    CU_ASSERT_EQUAL(0x2710000000ULL, iq24_imull(IQ24I(100), 100));
    CU_ASSERT_EQUAL(0x2710000000ULL, iq24_imull(IQ24I(-100), -100));
}

static void test_iq24_div(void)
{
    CU_ASSERT_EQUAL(IQ24(0.5), iq24_div(IQ24(1), IQ24(2)));
    CU_ASSERT_EQUAL(IQ24(2), iq24_div(IQ24(1), IQ24(0.5)));
    CU_ASSERT_EQUAL(IQ24(0.5), iq24_div(IQ24(-1), IQ24(-2)));
    CU_ASSERT_EQUAL(IQ24(-2), iq24_div(IQ24(-1), IQ24(0.5)));
}

static void test_iq24_div_sat(void)
{
    CU_ASSERT_EQUAL(IQ24(0.5), iq24_div_sat(IQ24(1), IQ24(2)));
    CU_ASSERT_EQUAL(IQ24(2), iq24_div_sat(IQ24(1), IQ24(0.5)));
    CU_ASSERT_EQUAL(IQ24(0.5), iq24_div_sat(IQ24(-1), IQ24(-2)));
    CU_ASSERT_EQUAL(IQ24(-2), iq24_div_sat(IQ24(-1), IQ24(0.5)));
    CU_ASSERT_EQUAL(IQ24_MAX, iq24_div_sat(IQ24(1), IQ24(0.001)));
    CU_ASSERT_EQUAL(IQ24_MAX, iq24_div_sat(IQ24(-1), IQ24(-0.001)));
    CU_ASSERT_EQUAL(IQ24_MIN, iq24_div_sat(IQ24(1), IQ24(-0.001)));
    CU_ASSERT_EQUAL(IQ24_MIN, iq24_div_sat(IQ24(-1), IQ24(0.001)));
}

static void test_iq24_divl(void)
{
    CU_ASSERT_EQUAL(0x100000000ULL, iq24_divl(IQ24(0x10), IQ24(0.0625)));
    CU_ASSERT_EQUAL(0x100000000ULL, iq24_divl(IQ24(-0x10), IQ24(-0.0625)));
}

static void test_iq24_idiv(void)
{
    CU_ASSERT_EQUAL(IQ24(0.5), iq24_idiv(IQ24(1), 2));
    CU_ASSERT_EQUAL(IQ24(0.5), iq24_idiv(IQ24(-1), -2));
}
/*
static void test_iq24_(void)
{
    CU_ASSERT_EQUAL(, );
}
*/

#undef TEST_IQ24_PI
#undef TEST_IQ24_IQ24_PI

static CU_ErrorCode test_iq24(void)
{
    CU_pSuite suite = CU_add_suite("IQ24", NULL, NULL);
    if(suite == NULL) return CU_get_error();

    if(CU_add_test(suite, "IQ24", test_iq24_iq24) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ24I", test_iq24_iq24i) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ24F", test_iq24_iq24f) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ24_MAX", test_iq24_max) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ24_MIN", test_iq24_min) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ24_IMAX", test_iq24_imax) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ24_IMIN", test_iq24_imin) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_abs", test_iq24_abs) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_int", test_iq24_int) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_fract", test_iq24_fract) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_sat", test_iq24_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_add", test_iq24_add) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_add_sat", test_iq24_add_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_addl", test_iq24_addl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_iadd", test_iq24_iadd) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_iadd_sat", test_iq24_iadd_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_iaddl", test_iq24_iaddl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_sub", test_iq24_sub) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_sub_sat", test_iq24_sub_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_subl", test_iq24_subl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_isub", test_iq24_isub) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_isub_sat", test_iq24_isub_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_isubl", test_iq24_isubl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_mul", test_iq24_mul) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_mul_sat", test_iq24_mul_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_mull", test_iq24_mull) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_imul", test_iq24_imul) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_imul_sat", test_iq24_imul_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_imull", test_iq24_imull) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_div", test_iq24_div) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_div_sat", test_iq24_div_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_divl", test_iq24_divl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_idiv", test_iq24_idiv) == NULL) return CU_get_error();
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

#endif /* TEST_IQ24_H */
