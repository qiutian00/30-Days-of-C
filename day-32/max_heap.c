#include <stdio.h>

#define CAP 100

struct Heap {
    int arr[CAP];
    int size;
};

void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

void init(struct Heap *h) { h->size = 0; }

int peek(struct Heap *h) { return h->arr[0]; }

void push(struct Heap *h, int x) {
    h->arr[h->size] = x;
    int i = h->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->arr[p] >= h->arr[i]) break;
        swap(&h->arr[p], &h->arr[i]);
        i = p;
    }
}

void heapify_down(struct Heap *h, int i) {
    for (;;) {
        int l = 2 * i + 1, r = 2 * i + 2, largest = i;
        if (l < h->size && h->arr[l] > h->arr[largest]) largest = l;
        if (r < h->size && h->arr[r] > h->arr[largest]) largest = r;
        if (largest == i) break;
        swap(&h->arr[i], &h->arr[largest]);
        i = largest;
    }
}

int pop(struct Heap *h) {
    int top = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    heapify_down(h, 0);
    return top;
}

void build_heap(struct Heap *h, int a[], int n) {
    for (int i = 0; i < n; i++) h->arr[i] = a[i];
    h->size = n;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_down(h, i);
}

int main(void) {
    struct Heap h; init(&h);
    push(&h, 3); push(&h, 10); push(&h, 5); push(&h, 1); push(&h, 8);

    printf("peek = %d\n", peek(&h));
    while (h.size > 0)
        printf("pop = %d\n", pop(&h));

    return 0;
}
