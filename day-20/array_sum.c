#include <stdio.h>

int sum(int arr[], int n)
{
    if (n == 0) return 0;
    return arr[n - 1] + sum(arr, n - 1);
}

int main(void)
{
    int a[] = {2, 4, 6, 8, 10};
    printf("sum = %d\n", sum(a, 5));
    return 0;
}
