#ifndef TEST_IQUTILS_H
#define TEST_IQUTILS_H


#include <CUnit/CUnit.h>
#include <stdint.h>
#include <math.h>
#include "iqutils.h"



static void test_iqn_to_m(void)
{
    CU_ASSERT_EQUAL(IQ15(0.5), iqn_to_m(IQ15(0.5), 15, 15));
    CU_ASSERT_EQUAL(IQ24(0.5), iqn_to_m(IQ7(0.5), 7, 24));
    CU_ASSERT_EQUAL(IQ7(0.5), iqn_to_m(IQ24(0.5), 24, 7));
}

static void test_liqn_to_m(void)
{
    CU_ASSERT_EQUAL(IQ15(0.5), liqn_to_m(IQ15(0.5), 15, 15));
    CU_ASSERT_EQUAL(IQ24(0.5), liqn_to_m(IQ7(0.5), 7, 24));
    CU_ASSERT_EQUAL(IQ7(0.5), liqn_to_m(IQ24(0.5), 24, 7));
}

static void test_iq7_inv24(void)
{
    CU_ASSERT_EQUAL(IQ24(2.0), iq7_inv24(IQ7(0.5)));
}

static void test_iq15_inv24(void)
{
    CU_ASSERT_EQUAL(IQ24(2.0), iq15_inv24(IQ15(0.5)));
}

static void test_iq24_inv15(void)
{
    CU_ASSERT_EQUAL(IQ15(2.0), iq24_inv15(IQ24(0.5)));
}

static void test_iq24_inv7(void)
{
    CU_ASSERT_EQUAL(IQ7(2.0), iq24_inv7(IQ24(0.5)));
}

static void test_iqn_in_range(void)
{
    CU_ASSERT_EQUAL(0, iqn_in_range(IQ24(0.5), IQ24(1.0), IQ24(10.0)));
    CU_ASSERT_EQUAL(1, iqn_in_range(IQ24(5.0), IQ24(1.0), IQ24(10.0)));
    CU_ASSERT_EQUAL(0, iqn_in_range(IQ24(15.0), IQ24(1.0), IQ24(10.0)));

    CU_ASSERT_EQUAL(0, iqn_in_range(IQ15(0.5), IQ15(1.0), IQ15(10.0)));
    CU_ASSERT_EQUAL(1, iqn_in_range(IQ15(5.0), IQ15(1.0), IQ15(10.0)));
    CU_ASSERT_EQUAL(0, iqn_in_range(IQ15(15.0), IQ15(1.0), IQ15(10.0)));

    CU_ASSERT_EQUAL(0, iqn_in_range(IQ7(0.5), IQ7(1.0), IQ7(10.0)));
    CU_ASSERT_EQUAL(1, iqn_in_range(IQ7(5.0), IQ7(1.0), IQ7(10.0)));
    CU_ASSERT_EQUAL(0, iqn_in_range(IQ7(15.0), IQ7(1.0), IQ7(10.0)));

    CU_ASSERT_EQUAL(0, iqn_in_range(0, 1, 10));
    CU_ASSERT_EQUAL(1, iqn_in_range(5, 1, 10));
    CU_ASSERT_EQUAL(0, iqn_in_range(15, 1, 10));
}

static void test_liqn_in_range(void)
{
    CU_ASSERT_EQUAL(0, liqn_in_range( 0LL, 1LL, 10LL));
    CU_ASSERT_EQUAL(1, liqn_in_range( 5LL, 1LL, 10LL));
    CU_ASSERT_EQUAL(0, liqn_in_range(15LL, 1LL, 10LL));
    CU_ASSERT_EQUAL(1, liqn_in_range(0x0500000000LL, 0x100000000LL, 0x1000000000LL));
    CU_ASSERT_EQUAL(0, liqn_in_range(0x1500000000LL, 0x100000000LL, 0x1000000000LL));
}

static void test_i32_inv24(void)
{
    CU_ASSERT_EQUAL(IQ24(0.5), i32_inv24(2));
}

static void test_liq7_int(void)
{
    CU_ASSERT_EQUAL(100000000, liq7_int(((liq7_t)100000000) << IQ7_FRACT_BITS));
}

static void test_liq15_int(void)
{
    CU_ASSERT_EQUAL(100000, liq15_int(((liq15_t)100000) << IQ15_FRACT_BITS));
}

static void test_liq24_int(void)
{
    CU_ASSERT_EQUAL(1000, liq24_int(((liq24_t)1000) << IQ24_FRACT_BITS));
}

static void test_i32_div_iq15(void)
{
    CU_ASSERT_EQUAL(IQ15(5), i32_div_iq15(10, IQ15(2)));
    CU_ASSERT_EQUAL(IQ15(-5), i32_div_iq15(-10, IQ15(2)));
    CU_ASSERT_EQUAL(IQ15(-5), i32_div_iq15(10, IQ15(-2)));
    CU_ASSERT_EQUAL(IQ15(5), i32_div_iq15(-10, IQ15(-2)));
}

static void test_iq15_mul24(void)
{
    CU_ASSERT_EQUAL(IQ24(10), iq15_mul24(IQ15(5), IQ15(2)));
    CU_ASSERT_EQUAL(IQ24(-10), iq15_mul24(IQ15(-5), IQ15(2)));
    CU_ASSERT_EQUAL(IQ24(-10), iq15_mul24(IQ15(5), IQ15(-2)));
    CU_ASSERT_EQUAL(IQ24(10), iq15_mul24(IQ15(-5), IQ15(-2)));
}

static void test_iq15_div24(void)
{
    CU_ASSERT_EQUAL(IQ24(2), iq15_div24(IQ15(4), IQ15(2)));
    CU_ASSERT_EQUAL(IQ24(-2), iq15_div24(IQ15(-4), IQ15(2)));
    CU_ASSERT_EQUAL(IQ24(-0.5), iq15_div24(IQ15(2), IQ15(-4)));
    CU_ASSERT_EQUAL(IQ24(0.5), iq15_div24(IQ15(-2), IQ15(-4)));
}

static void test_iql_mean2(void)
{
    CU_ASSERT_EQUAL(0, iql_mean2(0, 0));
    CU_ASSERT_EQUAL(0, iql_mean2(0, 1));
    CU_ASSERT_EQUAL(0, iql_mean2(1, -1));
    CU_ASSERT_EQUAL(0, iql_mean2(INT32_MAX, -INT32_MAX));
    CU_ASSERT_EQUAL(4, iql_mean2(3, 5));
    CU_ASSERT_EQUAL(40, iql_mean2(30, 50));
    CU_ASSERT_EQUAL(INT32_MAX, iql_mean2(INT32_MAX, INT32_MAX));
    CU_ASSERT_EQUAL(INT32_MIN, iql_mean2(INT32_MIN, INT32_MIN));
}

static void test_iql_mean(void)
{
    static iql_t iqs2[] = {1, 3};
    CU_ASSERT_EQUAL(2, iql_mean(iqs2, sizeof(iqs2)/sizeof(iqs2[0])));

    static iql_t iqs3[] = {INT32_MAX, INT32_MAX, INT32_MAX};
    CU_ASSERT_EQUAL(INT32_MAX, iql_mean(iqs3, sizeof(iqs3)/sizeof(iqs3[0])));

    static iql_t iqs5[] = {INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN};
    CU_ASSERT_EQUAL(INT32_MIN, iql_mean(iqs5, sizeof(iqs5)/sizeof(iqs5[0])));
}

static void test_iql_mean3(void)
{
    CU_ASSERT_EQUAL(0, iql_mean3(0, 0, 0));
    CU_ASSERT_EQUAL(0, iql_mean3(0, 0, 1));
    CU_ASSERT_EQUAL(0, iql_mean3(1, 0, -1));
    CU_ASSERT_EQUAL(0, iql_mean3(INT32_MAX, 0, -INT32_MAX));
    CU_ASSERT_EQUAL(3, iql_mean3(1, 3, 5));
    CU_ASSERT_EQUAL(30, iql_mean3(10, 30, 50));
    CU_ASSERT_EQUAL(INT32_MAX, iql_mean3(INT32_MAX, INT32_MAX, INT32_MAX));
    CU_ASSERT_EQUAL(INT32_MIN, iql_mean3(INT32_MIN, INT32_MIN, INT32_MIN));
}


static CU_ErrorCode test_iqutils(void)
{
    CU_pSuite suite = CU_add_suite("IQ utils", NULL, NULL);
    if(suite == NULL) return CU_get_error();

    if(CU_add_test(suite, "iqn_to_m", test_iqn_to_m) == NULL) return CU_get_error();
    if(CU_add_test(suite, "liqn_to_m", test_liqn_to_m) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq7_inv24", test_iq7_inv24) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_inv24", test_iq15_inv24) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_inv15", test_iq24_inv15) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq24_inv7", test_iq24_inv7) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iqn_in_range", test_iqn_in_range) == NULL) return CU_get_error();
    if(CU_add_test(suite, "liqn_in_range", test_liqn_in_range) == NULL) return CU_get_error();
    if(CU_add_test(suite, "i32_inv24", test_i32_inv24) == NULL) return CU_get_error();
    if(CU_add_test(suite, "liq7_int", test_liq7_int) == NULL) return CU_get_error();
    if(CU_add_test(suite, "liq15_int", test_liq15_int) == NULL) return CU_get_error();
    if(CU_add_test(suite, "liq24_int", test_liq24_int) == NULL) return CU_get_error();
    if(CU_add_test(suite, "i32_div_iq15", test_i32_div_iq15) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_mul24", test_iq15_mul24) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iq15_div24", test_iq15_div24) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iql_mean2", test_iql_mean2) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iql_mean", test_iql_mean) == NULL) return CU_get_error();
    if(CU_add_test(suite, "iql_mean3", test_iql_mean3) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ24", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ24", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ24", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ24", test_) == NULL) return CU_get_error();

    return CUE_SUCCESS;
}

#endif /* TEST_IQUTILS_H */
