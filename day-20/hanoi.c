#include <stdio.h>

void hanoi(int n, char from, char via, char to)
{
    if (n == 0) return;
    hanoi(n - 1, from, to, via);
    printf("Move disk %d: %c -> %c\n", n, from, to);
    hanoi(n - 1, via, from, to);
}

int main(void)
{
    hanoi(3, 'A', 'B', 'C');
    return 0;
}
