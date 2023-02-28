#ifndef TEST_IQ15_H
#define TEST_IQ15_H

#include <CUnit/CUnit.h>
#include <stdint.h>
#include "iq15.h"

#define TEST_IQ15_PI 3.14159265359
#define TEST_IQ15_IQ15_PI 0x1921F

static void test_iq15_iq15(void)
{
    CU_ASSERT_EQUAL(TEST_IQ15_IQ15_PI, IQ15(TEST_IQ15_PI));
}

static void test_iq15_iq15i(void)
{
    CU_ASSERT_EQUAL(0x018000, IQ15I(3));
}

static void test_iq15_iq15f(void)
{
    CU_ASSERT_EQUAL(IQ15(0.5), IQ15F(1,2));
}

static void test_iq15_max(void)
{
    CU_ASSERT_EQUAL(0x7fffffff, IQ15_MAX);
}

static void test_iq15_min(void)
{
    CU_ASSERT_EQUAL(0x80000000, IQ15_MIN);
}

static void test_iq15_imax(void)
{
    CU_ASSERT_EQUAL(65535, IQ15_IMAX);
}

static void test_iq15_imin(void)
{
    CU_ASSERT_EQUAL(-65536, IQ15_IMIN);
}

static void test_iq15_abs(void)
{
    CU_ASSERT_EQUAL(IQ15(TEST_IQ15_PI), iq15_abs(IQ15(-TEST_IQ15_PI)));
}

static void test_iq15_int(void)
{
    CU_ASSERT_EQUAL(3, iq15_int(IQ15(TEST_IQ15_PI)));
    CU_ASSERT_EQUAL(-3, iq15_int(IQ15(-TEST_IQ15_PI)));
}

static void test_iq15_fract(void)
{
    CU_ASSERT_EQUAL(IQ15(TEST_IQ15_PI-3), iq15_fract(IQ15(TEST_IQ15_PI)));
    CU_ASSERT_EQUAL(IQ15(3-TEST_IQ15_PI), iq15_fract(IQ15(-TEST_IQ15_PI)));
}

static void test_iq15_sat(void)
{
    CU_ASSERT_EQUAL(0x7fffffff, iq15_sat(0x100000000ULL));
    CU_ASSERT_EQUAL(0x80000000, iq15_sat(-0x100000000ULL));
}

static void test_iq15_add(void)
{
    CU_ASSERT_EQUAL(IQ15(4), iq15_add(IQ15(2), IQ15(2)));
    CU_ASSERT_EQUAL(IQ15(-4), iq15_add(IQ15(-2), IQ15(-2)));
    CU_ASSERT_EQUAL(IQ15(0), iq15_add(IQ15(2), IQ15(-2)));
    CU_ASSERT_EQUAL(IQ15(0), iq15_add(IQ15(-2), IQ15(2)));
}

static void test_iq15_add_sat(void)
{
    CU_ASSERT_EQUAL(IQ15(4), iq15_add_sat(IQ15(2), IQ15(2)));
    CU_ASSERT_EQUAL(IQ15(-4), iq15_add_sat(IQ15(-2), IQ15(-2)));
    CU_ASSERT_EQUAL(IQ15(0), iq15_add_sat(IQ15(2), IQ15(-2)));
    CU_ASSERT_EQUAL(IQ15(0), iq15_add_sat(IQ15(-2), IQ15(2)));
    CU_ASSERT_EQUAL(IQ15_MAX, iq15_add_sat(IQ15(2), IQ15_MAX));
    CU_ASSERT_EQUAL(IQ15_MIN, iq15_add_sat(IQ15(-2), IQ15_MIN));
}

static void test_iq15_addl(void)
{
    CU_ASSERT_EQUAL(0x80000000ULL, iq15_addl(IQ15(65535), IQ15(1)));
}

static void test_iq15_iadd(void)
{
    CU_ASSERT_EQUAL(IQ15(4), iq15_iadd(IQ15(2), 2));
    CU_ASSERT_EQUAL(IQ15(-4), iq15_iadd(IQ15(-2), -2));
    CU_ASSERT_EQUAL(IQ15(0), iq15_iadd(IQ15(2), -2));
}

static void test_iq15_iadd_sat(void)
{
    CU_ASSERT_EQUAL(IQ15(4), iq15_iadd_sat(IQ15(2), 2));
    CU_ASSERT_EQUAL(IQ15(-4), iq15_iadd_sat(IQ15(-2), -2));
    CU_ASSERT_EQUAL(IQ15(0), iq15_iadd_sat(IQ15(2), -2));
    CU_ASSERT_EQUAL(IQ15_MAX, iq15_iadd_sat(IQ15(2), IQ15_IMAX));
    CU_ASSERT_EQUAL(IQ15_MIN, iq15_iadd_sat(IQ15(-2), IQ15_IMIN));
}

static void test_iq15_iaddl(void)
{
    CU_ASSERT_EQUAL(0x80000000ULL, iq15_iaddl(IQ15(0), 65536));
}

static void test_iq15_sub(void)
{
    CU_ASSERT_EQUAL(IQ15(0), iq15_sub(IQ15(2), IQ15(2)));
    CU_ASSERT_EQUAL(IQ15(0), iq15_sub(IQ15(-2), IQ15(-2)));
    CU_ASSERT_EQUAL(IQ15(-4), iq15_sub(IQ15(-2), IQ15(2)));
    CU_ASSERT_EQUAL(IQ15(4), iq15_sub(IQ15(2), IQ15(-2)));
}

static void test_iq15_sub_sat(void)
{
    CU_ASSERT_EQUAL(IQ15(0), iq15_sub_sat(IQ15(2), IQ15(2)));
    CU_ASSERT_EQUAL(IQ15(0), iq15_sub_sat(IQ15(-2), IQ15(-2)));
    CU_ASSERT_EQUAL(IQ15(-4), iq15_sub_sat(IQ15(-2), IQ15(2)));
    CU_ASSERT_EQUAL(IQ15(4), iq15_sub_sat(IQ15(2), IQ15(-2)));
    CU_ASSERT_EQUAL(IQ15_MAX, iq15_sub_sat(IQ15(2), IQ15_MIN));
    CU_ASSERT_EQUAL(IQ15_MIN, iq15_sub_sat(IQ15(-2), IQ15_MAX));
}

static void test_iq15_subl(void)
{
    CU_ASSERT_EQUAL(0x80000000ULL, iq15_subl(IQ15(0), IQ15(-65536)));
}

static void test_iq15_isub(void)
{
    CU_ASSERT_EQUAL(IQ15(0), iq15_isub(IQ15(2), 2));
    CU_ASSERT_EQUAL(IQ15(0), iq15_isub(IQ15(-2), -2));
    CU_ASSERT_EQUAL(IQ15(-4), iq15_isub(IQ15(-2), 2));
    CU_ASSERT_EQUAL(IQ15(4), iq15_isub(IQ15(2), -2));
}

static void test_iq15_isub_sat(void)
{
    CU_ASSERT_EQUAL(IQ15(0), iq15_isub_sat(IQ15(2), 2));
    CU_ASSERT_EQUAL(IQ15(0), iq15_isub_sat(IQ15(-2), -2));
    CU_ASSERT_EQUAL(IQ15(-4), iq15_isub_sat(IQ15(-2), 2));
    CU_ASSERT_EQUAL(IQ15(4), iq15_isub_sat(IQ15(2), -2));
    CU_ASSERT_EQUAL(IQ15_MAX, iq15_isub_sat(IQ15(2), IQ15_IMIN));
    CU_ASSERT_EQUAL(IQ15_MIN, iq15_isub_sat(IQ15(-2), IQ15_IMAX));
}

static void test_iq15_isubl(void)
{
    CU_ASSERT_EQUAL(0x80000000ULL, iq15_isubl(IQ15(0), -65536));
}

static void test_iq15_mul(void)
{
    CU_ASSERT_EQUAL(IQ15(4), iq15_mul(IQ15(2), IQ15(2)));
    CU_ASSERT_EQUAL(IQ15(-4), iq15_mul(IQ15(2), IQ15(-2)));
    CU_ASSERT_EQUAL(IQ15(4), iq15_mul(IQ15(-2), IQ15(-2)));
}

static void test_iq15_mul_sat(void)
{
    CU_ASSERT_EQUAL(IQ15(4), iq15_mul_sat(IQ15(2), IQ15(2)));
    CU_ASSERT_EQUAL(IQ15(-4), iq15_mul_sat(IQ15(2), IQ15(-2)));
    CU_ASSERT_EQUAL(IQ15(4), iq15_mul_sat(IQ15(-2), IQ15(-2)));
    CU_ASSERT_EQUAL(IQ15_MAX, iq15_mul_sat(IQ15(1000), IQ15(1000)));
    CU_ASSERT_EQUAL(IQ15_MIN, iq15_mul_sat(IQ15(1000), IQ15(-1000)));
    CU_ASSERT_EQUAL(IQ15_MAX, iq15_mul_sat(IQ15(-1000), IQ15(-1000)));
}

static void test_iq15_mull(void)
{
    CU_ASSERT_EQUAL(0x13880000ULL, iq15_mull(IQ15(100), IQ15(100)));
    CU_ASSERT_EQUAL(0x13880000ULL, iq15_mull(IQ15(-100), IQ15(-100)));
}

static void test_iq15_imul(void)
{
    CU_ASSERT_EQUAL(IQ15(4), iq15_imul(IQ15(2), 2));
    CU_ASSERT_EQUAL(IQ15(-4), iq15_imul(IQ15(2), -2));
    CU_ASSERT_EQUAL(IQ15(4), iq15_imul(IQ15(-2), -2));
}

static void test_iq15_imul_sat(void)
{
    CU_ASSERT_EQUAL(IQ15(4), iq15_imul_sat(IQ15(2), 2));
    CU_ASSERT_EQUAL(IQ15(-4), iq15_imul_sat(IQ15(2), -2));
    CU_ASSERT_EQUAL(IQ15(4), iq15_imul_sat(IQ15(-2), -2));
    CU_ASSERT_EQUAL(IQ15_MAX, iq15_imul_sat(IQ15(1000), 1000));
    CU_ASSERT_EQUAL(IQ15_MIN, iq15_imul_sat(IQ15(1000), -1000));
    CU_ASSERT_EQUAL(IQ15_MAX, iq15_imul_sat(IQ15(-1000), -1000));
}

static void test_iq15_imull(void)
{
    CU_ASSERT_EQUAL(0x13880000ULL, iq15_imull(IQ15I(100), 100));
    CU_ASSERT_EQUAL(0x13880000ULL, iq15_imull(IQ15I(-100), -100));
}

static void test_iq15_div(void)
{
    CU_ASSERT_EQUAL(IQ15(0.5), iq15_div(IQ15(1), IQ15(2)));
    CU_ASSERT_EQUAL(IQ15(2), iq15_div(IQ15(1), IQ15(0.5)));
    CU_ASSERT_EQUAL(IQ15(0.5), iq15_div(IQ15(-1), IQ15(-2)));
    CU_ASSERT_EQUAL(IQ15(-2), iq15_div(IQ15(-1), IQ15(0.5)));
}

static void test_iq15_div_sat(void)
{
    CU_ASSERT_EQUAL(IQ15(0.5), iq15_div_sat(IQ15(1), IQ15(2)));
    CU_ASSERT_EQUAL(IQ15(2), iq15_div_sat(IQ15(1), IQ15(0.5)));
    CU_ASSERT_EQUAL(IQ15(0.5), iq15_div_sat(IQ15(-1), IQ15(-2)));
    CU_ASSERT_EQUAL(IQ15(-2), iq15_div_sat(IQ15(-1), IQ15(0.5)));
    CU_ASSERT_EQUAL(IQ15_MAX, iq15_div_sat(IQ15(1000), IQ15(0.001)));
    CU_ASSERT_EQUAL(IQ15_MAX, iq15_div_sat(IQ15(-1000), IQ15(-0.001)));
    CU_ASSERT_EQUAL(IQ15_MIN, iq15_div_sat(IQ15(1000), IQ15(-0.001)));
    CU_ASSERT_EQUAL(IQ15_MIN, iq15_div_sat(IQ15(-1000), IQ15(0.001)));
}

static void test_iq15_divl(void)
{
    CU_ASSERT_EQUAL(0x100000000ULL, iq15_divl(IQ15(0x1000), IQ15(0.03125)));
    CU_ASSERT_EQUAL(0x100000000ULL, iq15_divl(IQ15(-0x1000), IQ15(-0.03125)));
}

static void test_iq15_idiv(void)
{
    CU_ASSERT_EQUAL(IQ15(0.5), iq15_idiv(IQ15(1), 2));
    CU_ASSERT_EQUAL(IQ15(0.5), iq15_idiv(IQ15(-1), -2));
}
/*
static void test_iq15_(void)
{
    CU_ASSERT_EQUAL(, );
}
*/

#undef TEST_IQ15_PI
#undef TEST_IQ15_IQ15_PI

static CU_ErrorCode test_iq15(void)
{
    CU_pSuite suite = CU_add_suite("IQ15", NULL, NULL);
    if(suite == NULL) return CU_get_error();

    if(CU_add_test(suite, "IQ15", test_iq15_iq15) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ15I", test_iq15_iq15i) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ15F", test_iq15_iq15f) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ15_MAX", test_iq15_max) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ15_MIN", test_iq15_min) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ15_IMAX", test_iq15_imax) == NULL) return CU_get_error();
    if(CU_add_test(suite, "IQ15_IMIN", test_iq15_imin) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_abs", test_iq15_abs) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_int", test_iq15_int) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_fract", test_iq15_fract) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_sat", test_iq15_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_add", test_iq15_add) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_add_sat", test_iq15_add_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_addl", test_iq15_addl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_iadd", test_iq15_iadd) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_iadd_sat", test_iq15_iadd_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_iaddl", test_iq15_iaddl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_sub", test_iq15_sub) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_sub_sat", test_iq15_sub_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_subl", test_iq15_subl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_isub", test_iq15_isub) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_isub_sat", test_iq15_isub_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_isubl", test_iq15_isubl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_mul", test_iq15_mul) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_mul_sat", test_iq15_mul_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_mull", test_iq15_mull) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_imul", test_iq15_imul) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_imul_sat", test_iq15_imul_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_imull", test_iq15_imull) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_div", test_iq15_div) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_div_sat", test_iq15_div_sat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_divl", test_iq15_divl) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_idiv", test_iq15_idiv) == NULL) return CU_get_error();
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

#endif /* TEST_IQ15_H */
