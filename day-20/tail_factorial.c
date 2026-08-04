#include <stdio.h>

long fact_tail(int n, long acc)
{
    if (n <= 1) return acc;
    return fact_tail(n - 1, n * acc);
}

int main(void)
{
    printf("5! = %ld\n", fact_tail(5, 1));
    return 0;
}
