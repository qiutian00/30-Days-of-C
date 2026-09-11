#include <stdio.h>

#define N 100

int bit[N + 1];

void bit_update(int i, int delta, int n) {
    for (; i <= n; i += i & -i)
        bit[i] += delta;
}

int bit_query(int i) {
    int sum = 0;
    for (; i > 0; i -= i & -i)
        sum += bit[i];
    return sum;
}

int range_sum(int l, int r) {
    return bit_query(r) - bit_query(l - 1);
}

int main(void) {
    int a[] = {0, 1, 3, 5, 7, 9};   /* 1-based: a[1..5] */

    for (int i = 1; i <= 5; i++) bit_update(i, a[i], 5);

    printf("sum[2..4] = %d\n", range_sum(2, 4));
    bit_update(3, 10, 5);           /* a[3] += 10 */
    printf("sum[2..4] = %d\n", range_sum(2, 4));

    return 0;
}
