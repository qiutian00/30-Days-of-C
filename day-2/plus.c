#include <stdio.h>
int main()
{
    int a;
    int b;
    // 没有被初始化在c99中表现不同的
    printf("Enter two integers to add: ");
    scanf("%d %d", &a, &b);
    int sum = a + b;
    printf("The sum of %d and %d is %d\n", a, b, sum);
    return 0;
}