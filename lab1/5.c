// Write a C program to check whether the Host machine is in Little Endian or
// Big Endian.
// Enter a number, print the content of each byte location and
// Convert the Endianness of the same i.e. Little to Big Endian and vice-versa

#include <stdio.h>

void main()
{
    unsigned int n = 0x00000001;

    char *ptr = (char *)&n;

    if (*ptr == 1)
    {
        printf("Little Endian\n");
    }
    else
    {
        printf("Big Endian\n");
    }

    unsigned int num;
    printf("Enter a number: ");
    scanf("%x", &num);

    printf("Byte 1: %x\n", (num & 0xFF000000) >> 24);
    printf("Byte 2: %x\n", (num & 0x00FF0000) >> 16);
    printf("Byte 3: %x\n", (num & 0x0000FF00) >> 8);
    printf("Byte 4: %x\n", (num & 0x000000FF));

    unsigned int swapped = ((num & 0xFF000000) >> 24) | ((num & 0x00FF0000) >> 8) | ((num & 0x0000FF00) << 8) | ((num & 0x000000FF) << 24);
    printf("Swapped: %x\n", swapped);
}
