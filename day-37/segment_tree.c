#include <stdio.h>

#define MAXN 100

int seg[4 * MAXN];

void seg_build(int a[], int node, int lo, int hi) {
    if (lo == hi) { seg[node] = a[lo]; return; }
    int mid = (lo + hi) / 2;
    seg_build(a, node * 2,     lo, mid);
    seg_build(a, node * 2 + 1, mid + 1, hi);
    seg[node] = seg[node * 2] + seg[node * 2 + 1];
}

void seg_update(int node, int lo, int hi, int idx, int val) {
    if (lo == hi) { seg[node] = val; return; }
    int mid = (lo + hi) / 2;
    if (idx <= mid) seg_update(node * 2,     lo, mid, idx, val);
    else            seg_update(node * 2 + 1, mid + 1, hi, idx, val);
    seg[node] = seg[node * 2] + seg[node * 2 + 1];
}

int seg_query(int node, int lo, int hi, int ql, int qr) {
    if (qr < lo || hi < ql) return 0;
    if (ql <= lo && hi <= qr) return seg[node];
    int mid = (lo + hi) / 2;
    return seg_query(node * 2,     lo, mid, ql, qr)
         + seg_query(node * 2 + 1, mid + 1, hi, ql, qr);
}

int main(void) {
    int b[] = {1, 3, 5, 7, 9};   /* 0-based */
    seg_build(b, 1, 0, 4);

    printf("sum[1..3] = %d\n", seg_query(1, 0, 4, 1, 3));
    seg_update(1, 0, 4, 2, 10);  /* b[2] = 10 */
    printf("sum[1..3] = %d\n", seg_query(1, 0, 4, 1, 3));

    return 0;
}
