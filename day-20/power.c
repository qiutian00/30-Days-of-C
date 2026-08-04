#include <stdio.h>

long power_fast(int base, int exp)
{
    if (exp == 0) return 1;
    long half = power_fast(base, exp / 2);
    if (exp % 2 == 0)
        return half * half;
    return base * half * half;
}

int main(void)
{
    printf("2^10 = %ld\n", power_fast(2, 10));
    printf("3^5  = %ld\n", power_fast(3, 5));
    return 0;
}
