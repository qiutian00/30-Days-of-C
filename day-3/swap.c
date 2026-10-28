#include <stdio.h>
int main()
{
    int a = 5;
    int b = 10;
    int temp;

    temp = a; // Store the value of a in temp
    a = b;    // Assign the value of b to a
    b = temp; // Assign the value of temp (original a) to b
    printf("After swapping: a = %d, b = %d\n", a, b);
    return 0;
}