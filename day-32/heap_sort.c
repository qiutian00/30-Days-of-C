#include <stdio.h>

void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

void heapify_down(int a[], int n, int i) {
    for (;;) {
        int l = 2 * i + 1, r = 2 * i + 2, largest = i;
        if (l < n && a[l] > a[largest]) largest = l;
        if (r < n && a[r] > a[largest]) largest = r;
        if (largest == i) break;
        swap(&a[i], &a[largest]);
        i = largest;
    }
}

void heap_sort(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)   /* build max-heap */
        heapify_down(a, n, i);

    for (int i = n - 1; i >= 0; i--) {     /* extract max to the end */
        swap(&a[0], &a[i]);
        heapify_down(a, i, 0);
    }
}

int main(void) {
    int a[] = {12, 4, 5, 3, 8, 7};
    int n = sizeof(a) / sizeof(a[0]);

    heap_sort(a, n);

    printf("sorted: ");
    for (int i = 0; i < n; i++) printf("%d ", a[i]);
    printf("\n");

    return 0;
}
