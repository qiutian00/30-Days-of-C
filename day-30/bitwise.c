#include <stdio.h>

int main(void)
{
    unsigned int x = 0b1100;          /* 12 */

    printf("x       = %u\n", x);
    printf("x & 10  = %u\n", x & 0b1010);
    printf("x | 10  = %u\n", x | 0b1010);
    printf("x ^ 10  = %u\n", x ^ 0b1010);
    printf("x << 2  = %u\n", x << 2);
    printf("x >> 1  = %u\n", x >> 1);

    unsigned int flags = 0;
    flags |=  (1u << 3);   printf("set    bit 3: %u\n", flags);
    flags ^=  (1u << 3);   printf("toggle bit 3: %u\n", flags);
    flags |=  (1u << 3);
    flags &= ~(1u << 3);   printf("clear  bit 3: %u\n", flags);
    return 0;
}
