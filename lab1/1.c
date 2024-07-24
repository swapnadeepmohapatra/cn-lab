// Write a C program to swap the content of 2 variables entered through the command line using function and pointer.

#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void main()
{
    int a, b;

    printf("Enter two numbers: ");
    scanf("%d", &a);
    scanf("%d", &b);

    printf("Before swapping: a = %d, b = %d\n", a, b);

    swap(&a, &b);

    printf("After swapping: a = %d, b = %d\n", a, b);
}