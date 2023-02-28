# -*- coding: utf-8 -*-
# coding: utf8

import sys;
import math;


def round(val):
    return math.floor(val + 0.5);

def ssat(val):
    if(val >= 0x8000):
        val = 0x7fff;
    elif(val < -0x8000):
        val = -0x8000;
    return val;

def gen_sin_table():
    fract_bits = 15;
    base = (1 << fract_bits);
    table_size = 128;
    print("//! Число значений в таблице синуса.");
    print("#define Q15_SIN_TABLE_SIZE %u\n" % (table_size));
    print("//! Таблица значений синуса.");
    print("static const int16_t q15_sin_table[Q15_SIN_TABLE_SIZE] = {\n    ", end='');
    for i in range(0, table_size):
        y = math.sin(2 * math.pi * i / table_size);
        y_iq = ssat(round(y * base));
        print("0x%04x" % (y_iq & 0xffff), end='');
        if((i + 1) % 8 == 0):
            if((i + 1) != table_size):
                print(",\n    ", end='');
        else:
            print(", ", end = '');
    print("\n};");


def main():
    print("#ifndef Q15_SIN_TABLE_H");
    print("#define Q15_SIN_TABLE_H");
    print("\n#include <stdint.h>\n\n");

    gen_sin_table();

    print("\n#endif // Q15_SIN_TABLE_H");


if(__name__ == '__main__'):
    sys.stdout = open(1, 'w', encoding='utf-8', newline = '\n', closefd=False)
    main();

