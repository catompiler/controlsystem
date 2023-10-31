#ifndef TEST_IQ7_H
#define TEST_IQ7_H

#include <CUnit/CUnit.h>
#include <stdint.h>
#include "iq7.h"

#define TEST_IQ7_PI 3.14159265359
#define TEST_IQ7_IQ7_PI 0x192

static void test_iq7_iq7(void)
{
    CU_ASSERT_EQUAL(TEST_IQ7_IQ7_PI, IQ7(TEST_IQ7_PI));
}

static void test_iq7_iq7i(void)
{
    CU_ASSERT_EQUAL(0x00000180, IQ7I(3));
}

static void test_iq7_iq7f(void)
{
    CU_ASSERT_EQUAL(IQ7(0.5), IQ7F(1,2));
}

static void test_iq7_max(void)
{
    CU_ASSERT_EQUAL(0x7fffffff, IQ7_MAX);
}

static void test_iq7_min(void)
{
    CU_ASSERT_EQUAL(0x80000000, IQ7_MIN);
}

static void test_iq7_imax(void)
{
    CU_ASSERT_EQUAL(16777215, IQ7_IMAX);
}

static void test_iq7_imin(void)
{
    CU_ASSERT_EQUAL(-16777216, IQ7_IMIN);
}

static void test_iq7_abs(void)
{
    CU_ASSERT_EQUAL(IQ7(TEST_IQ7_PI), iq7_abs(IQ7(-TEST_IQ7_PI)));
}

static void test_iq7_int(void)
{
    CU_ASSERT_EQUAL(3, iq7_int(IQ7(TEST_IQ7_PI)));
    CU_ASSERT_EQUAL(-3, iq7_int(IQ7(-TEST_IQ7_PI)));
}

static void test_iq7_fract(void)
{
    CU_ASSERT_EQUAL(IQ7(TEST_IQ7_PI-3), iq7_fract(IQ7(TEST_IQ7_PI)));
    CU_ASSERT_EQUAL(IQ7(3-TEST_IQ7_PI), iq7_fract(IQ7(-TEST_IQ7_PI)));
}

static void test_iq7_sat(void)
{
    CU_ASSERT_EQUAL(0x7fffffff, iq7_sat(0x100000000ULL));
    CU_ASSERT_EQUAL(0x80000000, iq7_sat(-0x100000000ULL));
}

static void test_iq7_add(void)
{
    CU_ASSERT_EQUAL(IQ7(4), iq7_add(IQ7(2), IQ7(2)));
    CU_ASSERT_EQUAL(IQ7(-4), iq7_add(IQ7(-2), IQ7(-2)));
    CU_ASSERT_EQUAL(IQ7(0), iq7_add(IQ7(2), IQ7(-2)));
    CU_ASSERT_EQUAL(IQ7(0), iq7_add(IQ7(-2), IQ7(2)));
}

static void test_iq7_add_sat(void)
{
    CU_ASSERT_EQUAL(IQ7(4), iq7_add_sat(IQ7(2), IQ7(2)));
    CU_ASSERT_EQUAL(IQ7(-4), iq7_add_sat(IQ7(-2), IQ7(-2)));
    CU_ASSERT_EQUAL(IQ7(0), iq7_add_sat(IQ7(2), IQ7(-2)));
    CU_ASSERT_EQUAL(IQ7(0), iq7_add_sat(IQ7(-2), IQ7(2)));
    CU_ASSERT_EQUAL(IQ7_MAX, iq7_add_sat(IQ7(2), IQ7_MAX));
    CU_ASSERT_EQUAL(IQ7_MIN, iq7_add_sat(IQ7(-2), IQ7_MIN));
}

static void test_iq7_addl(void)
{
    CU_ASSERT_EQUAL(0xffffff00ULL, iq7_addl(IQ7(16777215), IQ7(16777215)));
}

static void test_iq7_iadd(void)
{
    CU_ASSERT_EQUAL(IQ7(4), iq7_iadd(IQ7(2), 2));
    CU_ASSERT_EQUAL(IQ7(-4), iq7_iadd(IQ7(-2), -2));
    CU_ASSERT_EQUAL(IQ7(0), iq7_iadd(IQ7(2), -2));
}

static void test_iq7_iadd_sat(void)
{
    CU_ASSERT_EQUAL(IQ7(4), iq7_iadd_sat(IQ7(2), 2));
    CU_ASSERT_EQUAL(IQ7(-4), iq7_iadd_sat(IQ7(-2), -2));
    CU_ASSERT_EQUAL(IQ7(0), iq7_iadd_sat(IQ7(2), -2));
    CU_ASSERT_EQUAL(IQ7_MAX, iq7_iadd_sat(IQ7(2), IQ7_IMAX));
    CU_ASSERT_EQUAL(IQ7_MIN, iq7_iadd_sat(IQ7(-2), IQ7_IMIN));
}

static void test_iq7_iaddl(void)
{
    CU_ASSERT_EQUAL(0xffffff00ULL, iq7_iaddl(IQ7(16777215), 16777215));
}

static void test_iq7_sub(void)
{
    CU_ASSERT_EQUAL(IQ7(0), iq7_sub(IQ7(2), IQ7(2)));
    CU_ASSERT_EQUAL(IQ7(0), iq7_sub(IQ7(-2), IQ7(-2)));
    CU_ASSERT_EQUAL(IQ7(-4), iq7_sub(IQ7(-2), IQ7(2)));
    CU_ASSERT_EQUAL(IQ7(4), iq7_sub(IQ7(2), IQ7(-2)));
}

static void test_iq7_sub_sat(void)
{
    CU_ASSERT_EQUAL(IQ7(0), iq7_sub_sat(IQ7(2), IQ7(2)));
    CU_ASSERT_EQUAL(IQ7(0), iq7_sub_sat(IQ7(-2), IQ7(-2)));
    CU_ASSERT_EQUAL(IQ7(-4), iq7_sub_sat(IQ7(-2), IQ7(2)));
    CU_ASSERT_EQUAL(IQ7(4), iq7_sub_sat(IQ7(2), IQ7(-2)));
    CU_ASSERT_EQUAL(IQ7_MAX, iq7_sub_sat(IQ7(2), IQ7_MIN));
    CU_ASSERT_EQUAL(IQ7_MIN, iq7_sub_sat(IQ7(-2), IQ7_MAX));
}

static void test_iq7_subl(void)
{
    CU_ASSERT_EQUAL(0x80000000ULL, iq7_subl(IQ7(0), IQ7(-16777216)));
}

static void test_iq7_isub(void)
{
    CU_ASSERT_EQUAL(IQ7(0), iq7_isub(IQ7(2), 2));
    CU_ASSERT_EQUAL(IQ7(0), iq7_isub(IQ7(-2), -2));
    CU_ASSERT_EQUAL(IQ7(-4), iq7_isub(IQ7(-2), 2));
    CU_ASSERT_EQUAL(IQ7(4), iq7_isub(IQ7(2), -2));
}

static void test_iq7_isub_sat(void)
{
    CU_ASSERT_EQUAL(IQ7(0), iq7_isub_sat(IQ7(2), 2));
    CU_ASSERT_EQUAL(IQ7(0), iq7_isub_sat(IQ7(-2), -2));
    CU_ASSERT_EQUAL(IQ7(-4), iq7_isub_sat(IQ7(-2), 2));
    CU_ASSERT_EQUAL(IQ7(4), iq7_isub_sat(IQ7(2), -2));
    CU_ASSERT_EQUAL(IQ7_MAX, iq7_isub_sat(IQ7(2), IQ7_IMIN));
    CU_ASSERT_EQUAL(IQ7_MIN, iq7_isub_sat(IQ7(-2), IQ7_IMAX));
}

static void test_iq7_isubl(void)
{
    CU_ASSERT_EQUAL(0x80000000ULL, iq7_isubl(IQ7(0), -16777216));
}

static void test_iq7_mul(void)
{
    CU_ASSERT_EQUAL(IQ7(4), iq7_mul(IQ7(2), IQ7(2)));
    CU_ASSERT_EQUAL(IQ7(-4), iq7_mul(IQ7(2), IQ7(-2)));
    CU_ASSERT_EQUAL(IQ7(4), iq7_mul(IQ7(-2), IQ7(-2)));
}

static void test_iq7_mul_sat(void)
{
    CU_ASSERT_EQUAL(IQ7(4), iq7_mul_sat(IQ7(2), IQ7(2)));
    CU_ASSERT_EQUAL(IQ7(-4), iq7_mul_sat(IQ7(2), IQ7(-2)));
    CU_ASSERT_EQUAL(IQ7(4), iq7_mul_sat(IQ7(-2), IQ7(-2)));
    CU_ASSERT_EQUAL(IQ7_MAX, iq7_mul_sat(IQ7(16777215), IQ7(16777215)));
    CU_ASSERT_EQUAL(IQ7_MIN, iq7_mul_sat(IQ7(16777215), IQ7(-16777215)));
    CU_ASSERT_EQUAL(IQ7_MAX, iq7_mul_sat(IQ7(-16777215), IQ7(-16777215)));
}

static void test_iq7_mull(void)
{
    CU_ASSERT_EQUAL(0x8000000000ULL, iq7_mull(IQ7(0x10000), IQ7(0x10000)));
    CU_ASSERT_EQUAL(0x8000000000ULL, iq7_mull(IQ7(-0x10000), IQ7(-0x10000)));
}

static void test_iq7_imul(void)
{
    CU_ASSERT_EQUAL(IQ7(4), iq7_imul(IQ7(2), 2));
    CU_ASSERT_EQUAL(IQ7(-4), iq7_imul(IQ7(2), -2));
    CU_ASSERT_EQUAL(IQ7(4), iq7_imul(IQ7(-2), -2));
}

static void test_iq7_imul_sat(void)
{
    CU_ASSERT_EQUAL(IQ7(4), iq7_imul_sat(IQ7(2), 2));
    CU_ASSERT_EQUAL(IQ7(-4), iq7_imul_sat(IQ7(2), -2));
    CU_ASSERT_EQUAL(IQ7(4), iq7_imul_sat(IQ7(-2), -2));
    CU_ASSERT_EQUAL(IQ7_MAX, iq7_imul_sat(IQ7(16777215), 16777215));
    CU_ASSERT_EQUAL(IQ7_MIN, iq7_imul_sat(IQ7(16777215), -16777215));
    CU_ASSERT_EQUAL(IQ7_MAX, iq7_imul_sat(IQ7(-16777215), -16777215));
}

static void test_iq7_imull(void)
{
    CU_ASSERT_EQUAL(0x8000000000ULL, iq7_imull(IQ7I(0x10000), 0x10000));
    CU_ASSERT_EQUAL(0x8000000000ULL, iq7_imull(IQ7I(-0x10000), -0x10000));
}

static void test_iq7_div(void)
{
    CU_ASSERT_EQUAL(IQ7(0.5), iq7_div(IQ7(1), IQ7(2)));
    CU_ASSERT_EQUAL(IQ7(2), iq7_div(IQ7(1), IQ7(0.5)));
    CU_ASSERT_EQUAL(IQ7(0.5), iq7_div(IQ7(-1), IQ7(-2)));
    CU_ASSERT_EQUAL(IQ7(-2), iq7_div(IQ7(-1), IQ7(0.5)));
}

static void test_iq7_div_sat(void)
{
    CU_ASSERT_EQUAL(IQ7(0.5), iq7_div_sat(IQ7(1), IQ7(2)));
    CU_ASSERT_EQUAL(IQ7(2), iq7_div_sat(IQ7(1), IQ7(0.5)));
    CU_ASSERT_EQUAL(IQ7(0.5), iq7_div_sat(IQ7(-1), IQ7(-2)));
    CU_ASSERT_EQUAL(IQ7(-2), iq7_div_sat(IQ7(-1), IQ7(0.5)));
    CU_ASSERT_EQUAL(IQ7_MAX, iq7_div_sat(IQ7(16777215), IQ7(0.1)));
    CU_ASSERT_EQUAL(IQ7_MAX, iq7_div_sat(IQ7(-16777215), IQ7(-0.1)));
    CU_ASSERT_EQUAL(IQ7_MIN, iq7_div_sat(IQ7(16777215), IQ7(-0.1)));
    CU_ASSERT_EQUAL(IQ7_MIN, iq7_div_sat(IQ7(-16777215), IQ7(0.1)));
}

static void test_iq7_divl(void)
{
    CU_ASSERT_EQUAL(0x100000000ULL, iq7_divl(IQ7(8388608), IQ7(0.25)));
    CU_ASSERT_EQUAL(0x100000000ULL, iq7_divl(IQ7(-8388608), IQ7(-0.25)));
}

static void test_iq7_idiv(void)
{
    CU_ASSERT_EQUAL(IQ7(0.5), iq7_idiv(IQ7(1), 2));
    CU_ASSERT_EQUAL(IQ7(0.5), iq7_idiv(IQ7(-1), -2));
}
/*
static void test_iq7_(void)
{
    CU_ASSERT_EQUAL(, );
}
*/

#undef TEST_IQ7_PI
#undef TEST_IQ7_IQ7_PI

static CU_ErrorCode test_iq7(void)
{
    CU_pSuite suite = CU_add_suite("IQ7", NULL, NULL);
    if(suite == NULL) return CU_get_error();

    if(CU_add_test(suite, "IQ7", test_iq7_iq7) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ7I", test_iq7_iq7i) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ7F", test_iq7_iq7f) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ7_MAX", test_iq7_max) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ7_MIN", test_iq7_min) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ7_IMAX", test_iq7_imax) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ7_IMIN", test_iq7_imin) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_abs", test_iq7_abs) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_int", test_iq7_int) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_fract", test_iq7_fract) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_sat", test_iq7_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_add", test_iq7_add) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_add_sat", test_iq7_add_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_addl", test_iq7_addl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_iadd", test_iq7_iadd) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_iadd_sat", test_iq7_iadd_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_iaddl", test_iq7_iaddl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_sub", test_iq7_sub) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_sub_sat", test_iq7_sub_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_subl", test_iq7_subl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_isub", test_iq7_isub) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_isub_sat", test_iq7_isub_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_isubl", test_iq7_isubl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_mul", test_iq7_mul) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_mul_sat", test_iq7_mul_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_mull", test_iq7_mull) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_imul", test_iq7_imul) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_imul_sat", test_iq7_imul_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_imull", test_iq7_imull) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_div", test_iq7_div) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_div_sat", test_iq7_div_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_divl", test_iq7_divl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_idiv", test_iq7_idiv) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ7", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ7", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ7", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ7", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ7", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ7", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ7", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ7", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ7", test_) == NULL) return CU_get_error();

    return CUE_SUCCESS;
}

#endif /* TEST_IQ7_H */
