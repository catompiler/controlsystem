# -*- coding: utf-8 -*-
# coding: utf8

import sys;
import math;


def round(val):
    return math.floor(val + 0.5);

def gen_sin_table():
    fract_bits = 24;
    base = (1 << fract_bits);
    table_size = 256;
    print("//! Число значений в таблице синуса.");
    print("#define IQ24_SIN_TABLE_SIZE %u\n" % (table_size));
    print("//! Таблица значений синуса.");
    print("__attribute__((aligned(4)))");
    print("static const int32_t iq24_sin_table[IQ24_SIN_TABLE_SIZE] = {\n    ", end='');
    for i in range(0, table_size):
        y = math.sin(2 * math.pi * i / table_size);
        y_iq = round(y * base);
        print("0x%08x" % (y_iq & 0xffffffff), end='');
        if((i + 1) % 8 == 0):
            if((i + 1) != table_size):
                print(",\n    ", end='');
        else:
            print(", ", end = '');
    print("\n};");


def main():
    print("#ifndef IQ24_SIN_TABLE_H");
    print("#define IQ24_SIN_TABLE_H");
    print("\n#include <stdint.h>\n\n");

    gen_sin_table();

    print("\n#endif // IQ24_SIN_TABLE_H");


if(__name__ == '__main__'):
    sys.stdout = open(1, 'w', encoding='utf-8', newline = '\n', closefd=False)
    main();

