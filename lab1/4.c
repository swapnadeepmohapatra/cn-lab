// Write a C Program to enter a number and store the number across the
// following structure and print the content of each member of the structure.
// Then aggregate each member of the structure to form the original number and
// print the same.

#include <stdio.h>

struct pkt {
    char ch1;
    char ch2[2];
    char ch3;
};

int main() {
    int num;
    struct pkt p;

    printf("Enter a number (0-9999): ");
    scanf("%d", &num);

    p.ch1 = (num / 1000) % 10;
    p.ch2[0] = (num / 100) % 10;
    p.ch2[1] = (num / 10) % 10;
    p.ch3 = num % 10;

    printf("Structure members:\n");
    printf("ch1: %d\n", p.ch1);
    printf("ch2[0]: %d\n", p.ch2[0]);
    printf("ch2[1]: %d\n", p.ch2[1]);
    printf("ch3: %d\n", p.ch3);

    int original_num = p.ch1 * 1000 + p.ch2[0] * 100 + p.ch2[1] * 10 + p.ch3;
    
    printf("Aggregated number: %d\n", original_num);

    return 0;
}
