# -*- coding: utf-8 -*-
# coding: utf8

import sys;
import math;


def round(val):
    return math.floor(val + 0.5);

def print_angle_def(angle, base):
    print("//! Угол %d градусов." % (angle));
    print("#define IQ15_CORDIC_ANGLE_PU_%d 0x%08x" % (angle, round(angle / 360.0 * base)));

def gen_tan_table():
    fract_bits = 15;
    base = (1 << fract_bits);
    table_size = 15;
    gain = 1.0;
    for i in range(0, table_size):
        gain = gain * math.sqrt(1+math.pow(2, -2 * i));
    gain_iq = round(1.0 / gain * base);
    print("//! Коэффициент деформации (%.09f)." % (1.0/gain));
    print("#define IQ15_CORDIC_GAIN 0x%08x\n" % (gain_iq));
    print_angle_def(0, base);
    print_angle_def(90, base);
    print_angle_def(180, base);
    print_angle_def(270, base);
    print_angle_def(360, base);
    print("");

    print("//! Число значений в таблице тангенсов.");
    print("#define IQ15_CORDIC_TAN_TABLE_SIZE %u\n" % (table_size));
    print("//! Таблица значений тангенсов.");
    print("static const int32_t iq15_cordic_tan_table[IQ15_CORDIC_TAN_TABLE_SIZE] = {\n    ", end='');
    tan_val = 1.0;
    for i in range(0, table_size):
        y = math.atan(tan_val) / (2.0 * math.pi);
        y_iq = round(y * base);
        tan_val = tan_val / 2;
        print("0x%08x" % (y_iq & 0xffffffff), end='');
        #print("%.08f" % (y * 180 / math.pi), end = '');
        if((i + 1) != table_size):
            if((i + 1) % 8 == 0):
                print(",\n    ", end='');
            else:
                print(", ", end = '');
    print("\n};");


def main():
    print("#ifndef IQ15_TAN_TABLE_H");
    print("#define IQ15_TAN_TABLE_H");
    print("\n#include <stdint.h>\n\n");

    gen_tan_table();

    print("\n#endif // IQ15_TAN_TABLE_H");


if(__name__ == '__main__'):
    sys.stdout = open(1, 'w', encoding='utf-8', newline = '\n', closefd=False)
    main();

