// Write a C program to extract each byte from a given number and store them in
// separate character variables and print the content of those variables.

#include <stdio.h>

void main()
{
    unsigned int num = 0x123456;

    int byte1 = (num & 0xFF0000) >> 16;
    int byte2 = (num & 0x00FF00) >> 8;
    int byte3 = (num & 0x0000FF);

    printf("Byte 1: %x\n", byte1);
    printf("Byte 2: %x\n", byte2);
    printf("Byte 3: %x\n", byte3);
}
