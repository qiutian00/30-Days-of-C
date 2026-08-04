#include <stdio.h>

void countdown(int n)
{
    printf("enter countdown(%d)\n", n);
    if (n == 0) {
        printf("liftoff!\n");
        return;
    }
    countdown(n - 1);
    printf("exit countdown(%d)\n", n);
}

int main(void)
{
    countdown(3);
    return 0;
}
