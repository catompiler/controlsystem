# -*- coding: utf-8 -*-
# coding: utf8

import sys;
import math;


def round(val):
    #return int(val);
    return int(math.floor(val + 0.5));

def ssat(val):
    if(val >= 0x8000):
        val = 0x7fff;
    elif(val < -0x8000):
        val = -0x8000;
    return val;

# Оконная функция.
def win(n, width):
    # Без окна.
    #return 1.0;
    # Окно Ханна.
    # Коэффициент ослабления окна Ханна.
    beta = -6.0;
    # Нормирующий коэффициент для амплитуды.
    k = math.pow(10.0, beta / 20.0);
    # Элемент окна Ханна.
    h = 0.5 * (1.0 - math.cos((2.0 * math.pi * n)/(width))); # width - 1 для симметричного окна.
    return h / k;

def gen_cmplx_sin_table():
    fract_bits = 14;
    base = (1 << fract_bits);
    table_size = 72;
    print("//! Число бит дробной части значений комплексного синуса.");
    print("#define PHASE_AMPL_CMPLX_SIN_TABLE_FRACT_BITS %u\n" % (fract_bits));
    print("//! Число значений комплексного синуса.");
    print("#define PHASE_AMPL_CMPLX_SIN_TABLE_SIZE %u\n" % (table_size));
    print("//! Таблица значений комплексного синуса.");
    print("//! Формат значений от младшего полуслова к старшему,");
    print("//! чётное слово - пара из действительных частей (R[n+1], R[n])");
    print("//! нечётное слово - пара из мнимых частей (I[n+1], I[n])");
    print("#ifdef CCM_DATA");
    print("CCM_DATA");
    print("#endif");
    print("__attribute__((aligned(4)))");
    print("static const int32_t phase_ampl_cmplx_sin_table[PHASE_AMPL_CMPLX_SIN_TABLE_SIZE] = {\n    ", end='');
    for i in range(0, table_size >> 1):

        n0 = i * 2;
        n1 = i * 2 + 1;

        a0 = 2.0 * math.pi * n0 / table_size;
        a1 = 2.0 * math.pi * n1 / table_size;

        w0 = win(n0, table_size);
        w1 = win(n1, table_size);

        r0 = math.sin(a0) * w0;
        i0 = math.cos(a0) * w0;
        r1 = math.sin(a1) * w1;
        i1 = math.cos(a1) * w1;

        r0_iq = ssat(round(r0 * base));
        i0_iq = ssat(round(i0 * base));
        r1_iq = ssat(round(r1 * base));
        i1_iq = ssat(round(i1 * base));

        print("0x%04x%04x, " % (r1_iq & 0xffff, r0_iq & 0xffff), end='');
        print("0x%04x%04x"   % (i1_iq & 0xffff, i0_iq & 0xffff), end='');
        if((i + 1) % 4 == 0):
            if(((i + 1) * 2) != table_size):
                print(",\n    ", end='');
        else:
            print(", ", end = '');
    print("\n};");


def main():
    print("#ifndef PHASE_AMPL_CMPLX_SIN_TABLE_H");
    print("#define PHASE_AMPL_CMPLX_SIN_TABLE_H");
    print("\n#include <stdint.h>\n\n");

    gen_cmplx_sin_table();

    print("\n#endif // PHASE_AMPL_CMPLX_SIN_TABLE_H");


if(__name__ == '__main__'):
    sys.stdout = open(1, 'w', encoding='utf-8', newline = '\n', closefd=False)
    main();

