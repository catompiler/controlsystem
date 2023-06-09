#ifndef IQ15_SIN_TABLE_H
#define IQ15_SIN_TABLE_H

#include <stdint.h>


//! Число значений в таблице синуса.
#define IQ15_SIN_TABLE_SIZE 128

//! Таблица значений синуса.
__attribute__((aligned(4)))
static const int32_t iq15_sin_table[IQ15_SIN_TABLE_SIZE] = {
    0x00000000, 0x00000648, 0x00000c8c, 0x000012c8, 0x000018f9, 0x00001f1a, 0x00002528, 0x00002b1f,
    0x000030fc, 0x000036ba, 0x00003c57, 0x000041ce, 0x0000471d, 0x00004c40, 0x00005134, 0x000055f6,
    0x00005a82, 0x00005ed7, 0x000062f2, 0x000066d0, 0x00006a6e, 0x00006dca, 0x000070e3, 0x000073b6,
    0x00007642, 0x00007885, 0x00007a7d, 0x00007c2a, 0x00007d8a, 0x00007e9d, 0x00007f62, 0x00007fd9,
    0x00008000, 0x00007fd9, 0x00007f62, 0x00007e9d, 0x00007d8a, 0x00007c2a, 0x00007a7d, 0x00007885,
    0x00007642, 0x000073b6, 0x000070e3, 0x00006dca, 0x00006a6e, 0x000066d0, 0x000062f2, 0x00005ed7,
    0x00005a82, 0x000055f6, 0x00005134, 0x00004c40, 0x0000471d, 0x000041ce, 0x00003c57, 0x000036ba,
    0x000030fc, 0x00002b1f, 0x00002528, 0x00001f1a, 0x000018f9, 0x000012c8, 0x00000c8c, 0x00000648,
    0x00000000, 0xfffff9b8, 0xfffff374, 0xffffed38, 0xffffe707, 0xffffe0e6, 0xffffdad8, 0xffffd4e1,
    0xffffcf04, 0xffffc946, 0xffffc3a9, 0xffffbe32, 0xffffb8e3, 0xffffb3c0, 0xffffaecc, 0xffffaa0a,
    0xffffa57e, 0xffffa129, 0xffff9d0e, 0xffff9930, 0xffff9592, 0xffff9236, 0xffff8f1d, 0xffff8c4a,
    0xffff89be, 0xffff877b, 0xffff8583, 0xffff83d6, 0xffff8276, 0xffff8163, 0xffff809e, 0xffff8027,
    0xffff8000, 0xffff8027, 0xffff809e, 0xffff8163, 0xffff8276, 0xffff83d6, 0xffff8583, 0xffff877b,
    0xffff89be, 0xffff8c4a, 0xffff8f1d, 0xffff9236, 0xffff9592, 0xffff9930, 0xffff9d0e, 0xffffa129,
    0xffffa57e, 0xffffaa0a, 0xffffaecc, 0xffffb3c0, 0xffffb8e3, 0xffffbe32, 0xffffc3a9, 0xffffc946,
    0xffffcf04, 0xffffd4e1, 0xffffdad8, 0xffffe0e6, 0xffffe707, 0xffffed38, 0xfffff374, 0xfffff9b8
};

#endif // IQ15_SIN_TABLE_H
