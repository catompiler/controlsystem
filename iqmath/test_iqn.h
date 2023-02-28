#ifndef TEST_IQN_H
#define TEST_IQN_H

#include <CUnit/CUnit.h>
//#include <stdio.h>
#include <stdint.h>
#include "iqn.h"


/*
#define TEST_IQN_ITEM(MSG, REF, VAL)\
    do{\
        printf("Test: %16s\t", (MSG));\
        printf("| Ref: 0x%08x | Val: 0x%08x ", (uint32_t)(REF), (uint32_t)(VAL));\
        printf("|\t%s\n", ((REF) == (VAL)) ? "SUCC" : "FAIL");\
    }while(0)\
*/

#define TEST_IQN_ITEM(MSG, REF, VAL)\
    do{\
        CU_ASSERT_EQUAL(REF, VAL)\
    }while(0)

static void test_iqn_iq24(void)
{
#define NI 7
#define N 24
#define T int32_t
#define BT int32_t
#define MT uint32_t
#define ET int64_t

    //printf("IQ_%u_%u\n", NI, N);

    TEST_IQN_ITEM("IQN_BASE", 0x1000000, IQN_BASE(N, BT));
    TEST_IQN_ITEM("IQN_FRACT_MASK", 0xFFFFFF, IQN_FRACT_MASK(N, MT));
    TEST_IQN_ITEM("IQN_SIGN_MASK", 0x80000000, IQN_SIGN_MASK(NI, N, MT));
    TEST_IQN_ITEM("IQN_SAT_BIT", 32, IQN_SAT_BIT(NI, N));
    TEST_IQN_ITEM("IQN", 0x1800000, IQN(1.5f, N, T, BT));
    TEST_IQN_ITEM("IQNI", 0x1000000, IQNI(1, N, T));
    TEST_IQN_ITEM("IQNF", 0x1800000, IQNF(3, 2, N, T, ET));
    TEST_IQN_ITEM("IQN NEG", 0xFE800000, IQN(-1.5f, N, T, BT));
    TEST_IQN_ITEM("IQNI NEG", 0xFF000000, IQNI(-1, N, T));
    TEST_IQN_ITEM("IQNF NEG", 0xFE800000, IQNF(-3, 2, N, T, ET));
    TEST_IQN_ITEM("IQN_HALF", 0x0800000, IQN_HALF(N, T));
    TEST_IQN_ITEM("IQN_MAX", 0x7FFFFFFF, IQN_MAX(NI, N, T, MT));
    TEST_IQN_ITEM("IQN_MIN", 0x80000000, IQN_MIN(NI, N, T, MT));
    TEST_IQN_ITEM("IQN_IMAX", 0x0000007F, IQN_IMAX(NI, N, T, MT, BT));
    TEST_IQN_ITEM("IQN_IMIN", 0xffffff80, IQN_IMIN(NI, N, T, MT, BT));
    TEST_IQN_ITEM("IQN_INT", 0x1, IQN_INT(0x1800000, N));
    TEST_IQN_ITEM("IQN_FRACT", 0x800000, IQN_FRACT(0x1800000, N, MT));
    TEST_IQN_ITEM("IQN_INT NEG", 0xffffffff, IQN_INT((T)0xFE800000, N));
    TEST_IQN_ITEM("IQN_FRACT NEG", 0xff800000, IQN_FRACT((T)0xFE800000, N, MT));
    TEST_IQN_ITEM("IQN_ABS", 0x1800000, IQN_ABS((T)0xFE800000));
    TEST_IQN_ITEM("IQN_FLOOR", 0x03000000, IQN_FLOOR((T)0x03243F6A, N, MT));
    TEST_IQN_ITEM("IQN_FLOOR NEG", 0xfd000000, IQN_FLOOR((T)0xFCDBC096, N, MT));
    TEST_IQN_ITEM("IQN_CEIL", 0x04000000, IQN_CEIL((T)0x03243F6A, N, T, MT));
    TEST_IQN_ITEM("IQN_CEIL NEG", 0xfc000000, IQN_CEIL((T)0xFCDBC096, N, T, MT));
    TEST_IQN_ITEM("IQN_ROUND", 0x03000000, IQN_ROUND((T)0x03243F6A, N, T, MT));
    TEST_IQN_ITEM("IQN_ROUND NEG", 0xfd000000, IQN_ROUND((T)0xFCDBC096, N, T, MT));
    //printf(": 0x%x\n", );

#undef ET
#undef MT
#undef BT
#undef T
#undef N
#undef NI
}

static void test_iqn_uiq24(void)
{
#define NI 8
#define N 24
#define T uint32_t
#define BT uint32_t
#define MT uint32_t
#define ET uint64_t

    //printf("UIQ_%u_%u\n", NI, N);

    TEST_IQN_ITEM("IQN_BASE", 0x1000000, IQN_BASE(N, BT));
    TEST_IQN_ITEM("IQN_FRACT_MASK", 0xFFFFFF, IQN_FRACT_MASK(N, MT));
    TEST_IQN_ITEM("IQN_SAT_BIT", 33, IQN_SAT_BIT(NI, N));
    TEST_IQN_ITEM("IQN", 0x1800000, IQN(1.5f, N, T, BT));
    TEST_IQN_ITEM("IQNI", 0x1000000, IQNI(1, N, T));
    TEST_IQN_ITEM("IQNF", 0x1800000, IQNF(3, 2, N, T, ET));
    TEST_IQN_ITEM("IQN_HALF", 0x0800000, IQN_HALF(N, T));
    TEST_IQN_ITEM("UIQN_MAX", 0xFFFFFFFF, UIQN_MAX(NI, N, T, MT));
    TEST_IQN_ITEM("UIQN_MIN", 0x00000000, UIQN_MIN(NI, N, T, MT));
    TEST_IQN_ITEM("UIQN_IMAX", 0x000000FF, UIQN_IMAX(NI, N, T, MT, BT));
    TEST_IQN_ITEM("UIQN_IMIN", 0x00000000, UIQN_IMIN(NI, N, T, MT, BT));
    TEST_IQN_ITEM("IQN_INT", 0x1, IQN_INT(0x1800000, N));
    TEST_IQN_ITEM("IQN_FRACT", 0x800000, IQN_FRACT(0x1800000, N, MT));
    TEST_IQN_ITEM("IQN_FLOOR", 0x03000000, IQN_FLOOR((T)0x03243F6A, N, MT));
    TEST_IQN_ITEM("IQN_CEIL", 0x04000000, IQN_CEIL((T)0x03243F6A, N, T, MT));
    TEST_IQN_ITEM("IQN_ROUND", 0x03000000, IQN_ROUND((T)0x03243F6A, N, T, MT));
    //printf(": 0x%x\n", );

#undef ET
#undef MT
#undef BT
#undef T
#undef N
#undef NI
}

static void test_iqn_q31(void)
{
#define NI 0
#define N 31
#define T int32_t
#define BT int64_t
#define MT uint32_t
#define ET int64_t

    //printf("IQ_%u_%u\n", NI, N);

    TEST_IQN_ITEM("IQN_BASE", 0x80000000, IQN_BASE(N, BT));
    TEST_IQN_ITEM("IQN_FRACT_MASK", 0x7FFFFFFF, IQN_FRACT_MASK(N, MT));
    TEST_IQN_ITEM("IQN_SIGN_MASK", 0x80000000, IQN_SIGN_MASK(NI, N, MT));
    TEST_IQN_ITEM("IQN_SAT_BIT", 32, IQN_SAT_BIT(NI, N));
    TEST_IQN_ITEM("IQN", 0x40000000, IQN(0.5f, N, T, BT));
    TEST_IQN_ITEM("IQNF", 0x40000000, IQNF(1, 2, N, T, ET));
    TEST_IQN_ITEM("IQN NEG", 0xC0000000, IQN(-0.5f, N, T, BT));
    TEST_IQN_ITEM("IQNF NEG", 0xC0000000, IQNF(-1, 2, N, T, ET));
    TEST_IQN_ITEM("IQN_HALF", 0x40000000, IQN_HALF(N, T));
    TEST_IQN_ITEM("IQN_MAX", 0x7FFFFFFF, IQN_MAX(NI, N, T, MT));
    TEST_IQN_ITEM("IQN_MIN", 0x80000000, IQN_MIN(NI, N, T, MT));
    TEST_IQN_ITEM("IQN_IMAX", 0x00000000, IQN_IMAX(NI, N, T, MT, BT));
    TEST_IQN_ITEM("IQN_IMIN", 0xffffffff, IQN_IMIN(NI, N, T, MT, BT));
    TEST_IQN_ITEM("IQN_FRACT", 0x40000000, IQN_FRACT(0x40000000, N, MT));
    TEST_IQN_ITEM("IQN_FRACT NEG", 0xC0000000, IQN_FRACT((T)0xC0000000, N, MT));
    TEST_IQN_ITEM("IQN_ABS", 0x40000000, IQN_ABS((T)0xC0000000));
    //printf(": 0x%x\n", );

#undef ET
#undef MT
#undef BT
#undef T
#undef N
#undef NI
}

static void test_iqn_uq32(void)
{
#define NI 0
#define N 32
#define T uint32_t
#define BT uint64_t
#define MT uint32_t
#define ET uint64_t

    //printf("UIQ_%u_%u\n", NI, N);

    TEST_IQN_ITEM("IQN_BASE", 0x100000000, IQN_BASE(N, BT));
    TEST_IQN_ITEM("IQN_FRACT_MASK", 0xFFFFFFFF, IQN_FRACT_MASK(N, MT));
    TEST_IQN_ITEM("IQN_SAT_BIT", 33, IQN_SAT_BIT(NI, N));
    TEST_IQN_ITEM("IQN", 0x80000000, IQN(0.5f, N, T, BT));
    TEST_IQN_ITEM("IQNF", 0x80000000, IQNF(1, 2, N, T, ET));
    TEST_IQN_ITEM("IQN_HALF", 0x80000000, IQN_HALF(N, T));
    TEST_IQN_ITEM("UIQN_MAX", 0xFFFFFFFF, UIQN_MAX(NI, N, T, MT));
    TEST_IQN_ITEM("UIQN_MIN", 0x00000000, UIQN_MIN(NI, N, T, MT));
    TEST_IQN_ITEM("UIQN_IMAX", 0x00000000, UIQN_IMAX(NI, N, T, MT, BT));
    TEST_IQN_ITEM("UIQN_IMIN", 0x00000000, UIQN_IMIN(NI, N, T, MT, BT));
    TEST_IQN_ITEM("IQN_FRACT", 0x80000000, IQN_FRACT(0x80000000, N, MT));
    //printf(": 0x%x\n", );

#undef ET
#undef MT
#undef BT
#undef T
#undef N
#undef NI
}

#undef TEST_IQN_ITEM

static CU_ErrorCode test_iqn(void)
{
    CU_pSuite suite = CU_add_suite("IQN", NULL, NULL);
    if(suite == NULL) return CU_get_error();

    if(CU_add_test(suite, "IQ24", test_iqn_iq24) == NULL) return CU_get_error();
    if(CU_add_test(suite, "UIQ24", test_iqn_uiq24) == NULL) return CU_get_error();
    if(CU_add_test(suite, "Q31", test_iqn_q31) == NULL) return CU_get_error();
    if(CU_add_test(suite, "UQ32", test_iqn_uq32) == NULL) return CU_get_error();

    return CUE_SUCCESS;
}

#endif /* TEST_IQN_H */
