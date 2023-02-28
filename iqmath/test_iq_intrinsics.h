#ifndef TEST_IQ_INTRINSICS_H
#define TEST_IQ_INTRINSICS_H

#include <CUnit/CUnit.h>
#include <stdint.h>
#include "iq_intrinsics.h"


static void test_iq_intrinsics_ssat(void)
{
    CU_ASSERT_EQUAL(0x7fff, __SSAT(0x10000, 16));
    CU_ASSERT_EQUAL(0x1000, __SSAT(0x1000, 16));
}

static void test_iq_intrinsics_ssat_asr(void)
{
    CU_ASSERT_EQUAL(0x7fff, __SSAT_ASR(0x20000, 16, 1));
    CU_ASSERT_EQUAL(0x1000, __SSAT_ASR(0x2000, 16, 1));
}

static void test_iq_intrinsics_ssat16(void)
{
    CU_ASSERT_EQUAL(0x07fff800, __SSAT16(0x7fff8000, 12));
    CU_ASSERT_EQUAL(0x10001000, __SSAT16(0x10001000, 16));
}

static void test_iq_intrinsics_qadd(void)
{
    CU_ASSERT_EQUAL(0x7fffffff, __QADD(0x70000000, 0x70000000));
    CU_ASSERT_EQUAL(0x00020000, __QADD(0x00010000, 0x00010000));
    CU_ASSERT_EQUAL(0x80000000, __QADD(0x80000000, 0x80000000));
    CU_ASSERT_EQUAL(0xfffffffe, __QADD(0xffffffff, 0xffffffff));
    CU_ASSERT_EQUAL(0xffffffff, __QADD(0xfffffffe, 0x00000001));
}

static void test_iq_intrinsics_qadd16(void)
{
    CU_ASSERT_EQUAL(0x20002000, __QADD16(0x10001000, 0x10001000));
    CU_ASSERT_EQUAL(0x80007fff, __QADD16(0x80007fff, 0x80007fff));
    CU_ASSERT_EQUAL(0x7fff8000, __QADD16(0x7fff8000, 0x7fff8000));
}

static void test_iq_intrinsics_qsub(void)
{
    CU_ASSERT_EQUAL(0x7fffffff, __QSUB(0x70000000, 0x80000000));
    CU_ASSERT_EQUAL(0x00010000, __QSUB(0x00020000, 0x00010000));
    CU_ASSERT_EQUAL(0x80000000, __QSUB(0x80000000, 0x70000000));
    CU_ASSERT_EQUAL(0xffffffff, __QSUB(0xfffffffe, 0xffffffff));
    CU_ASSERT_EQUAL(0xfffffffe, __QSUB(0xffffffff, 0x00000001));
}

static void test_iq_intrinsics_qsub16(void)
{
    CU_ASSERT_EQUAL(0x10001000, __QSUB16(0x20002000, 0x10001000));
    CU_ASSERT_EQUAL(0x80007fff, __QSUB16(0x80007fff, 0x7fff8000));
    CU_ASSERT_EQUAL(0x7fff8000, __QSUB16(0x7fff8000, 0x80007fff));
}

static void test_iq_intrinsics_mla(void)
{
    CU_ASSERT_EQUAL(0x1001000, __MLA(0x1000, 0x1000, 0x1000));
}

static void test_iq_intrinsics_smlal(void)
{
    CU_ASSERT_EQUAL(0x100010000LL, __SMLAL(0x10000, 0x10000, 0x10000));
}

static CU_ErrorCode test_iq_intrinsics(void)
{
    CU_pSuite suite = CU_add_suite("IQ_INTRINSICS", NULL, NULL);
    if(suite == NULL) return CU_get_error();

    if(CU_add_test(suite, "SSAT", test_iq_intrinsics_ssat) == NULL) return CU_get_error();
    if(CU_add_test(suite, "SSAT_ASR", test_iq_intrinsics_ssat_asr) == NULL) return CU_get_error();
    if(CU_add_test(suite, "SSAT16", test_iq_intrinsics_ssat16) == NULL) return CU_get_error();
    if(CU_add_test(suite, "QADD", test_iq_intrinsics_qadd) == NULL) return CU_get_error();
    if(CU_add_test(suite, "QADD16", test_iq_intrinsics_qadd16) == NULL) return CU_get_error();
    if(CU_add_test(suite, "QSUB", test_iq_intrinsics_qsub) == NULL) return CU_get_error();
    if(CU_add_test(suite, "QSUB16", test_iq_intrinsics_qsub16) == NULL) return CU_get_error();
    if(CU_add_test(suite, "MLA", test_iq_intrinsics_mla) == NULL) return CU_get_error();
    if(CU_add_test(suite, "SMLAL", test_iq_intrinsics_smlal) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ", test_) == NULL) return CU_get_error();
    //if(CU_add_test(suite, "IQ", test_) == NULL) return CU_get_error();

    return CUE_SUCCESS;
}

#endif /* TEST_IQ_INTRINSICS_H */
