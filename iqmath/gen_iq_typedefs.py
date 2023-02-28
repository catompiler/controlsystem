# -*- coding: utf-8 -*-
# coding: utf8

import sys;


def gen_q_format():
    print("/*");
    print("   Формат с фиксированной запятой");
    print("   +------------------+");
    print("   |S|III|QQQQQQQQQQQQ|");
    print("   +------------------+");
    print("   S - бит знака")
    print("   I - биты целой части");
    print("   Q - биты дробной части");
    print("   В примере на диаграмме изображена");
    print("   страктура числа с фиксированной запятой");
    print("   со знаком, с тремя битами целой части и");
    print("   с двенадцатью битами дробной части.");
    print("*/\n");

def gen_iq_typedef(B, S, I, Q, suff):
    sign_prefix = "u" if (S == 0) else "";
    q_prefix = "%s%s" %(sign_prefix , "i" if (I != 0) else "");
    print("typedef %sint%u_t %sq%u%s_t; //!< S%u I%u Q%u" % (sign_prefix, B, q_prefix, Q, suff, S, I, Q));

def gen_N_bit(B, Q1, QN, suff):
    print("/**\n * Числа с фиксированной запятой разрядностью %u бит.\n */\n" % (B));

    Q1S = max(1, Q1);
    QNS = min(B-1, QN);

    Q1SI = max(0, Q1);
    QNSI = min(B-1-1, QN);

    Q1U = max(1, Q1);
    QNU = min(B, QN);

    Q1UI = max(0, Q1);
    QNUI = min(B-1, QN);

    print("//! Знаковые без целой части.");
    print("typedef int%u_t q%s_t; //!< S1 I0 Qm" % (B, suff));
    for i in range(Q1S,QNS+1):
        gen_iq_typedef(B, 1, 0, i, suff);
    print("//! Знаковые с целой частью.");
    print("typedef int%u_t iq%s_t; //!< S1 In Qm" % (B, suff));
    for i in range(Q1SI,QNSI+1):
        gen_iq_typedef(B, 1, QN-1-i, i, suff);
    print("//! Беззнаковые без целой части.");
    print("typedef uint%u_t uq%s_t; //!< S0 I0 Qm" % (B, suff));
    for i in range(Q1U,QNU+1):
        gen_iq_typedef(B, 0, 0, i, suff);
    print("//! Беззнаковые с целой частью.");
    print("typedef uint%u_t uiq%s_t; //!< S0 In Qm" % (B, suff));
    for i in range(Q1UI,QNUI+1):
        gen_iq_typedef(B, 0, QN-i, i, suff);
    print("\n");

def gen_8_bit():
    gen_N_bit(8, 1, 8, "b");

def gen_16_bit():
    gen_N_bit(16, 1, 16, "s");

def gen_32_bit():
    gen_N_bit(32, 1, 32, "l");

def gen_64_bit():
    gen_N_bit(64, 1, 64, "ll");

def main():
    print("#ifndef IQ_TYPES_H");
    print("#define IQ_TYPES_H");
    print("\n#include <stdint.h>\n");
    gen_q_format();
    gen_8_bit();
    gen_16_bit();
    gen_32_bit();
    gen_64_bit();
    print("#endif // IQ_TYPES_H");


if(__name__ == '__main__'):
    sys.stdout = open(1, 'w', encoding='utf-8', newline = '\n', closefd=False)
    main();

