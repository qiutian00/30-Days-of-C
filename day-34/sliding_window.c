#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CAP 100

struct Deque {
    int data[CAP];
    int front;
    int size;
};

void init(struct Deque *d) { d->front = 0; d->size = 0; }

bool isEmpty(struct Deque *d) { return d->size == 0; }
bool isFull (struct Deque *d) { return d->size == CAP; }

static int back_index(struct Deque *d) {
    return (d->front + d->size - 1) % CAP;
}

void push_front(struct Deque *d, int x) {
    if (isFull(d)) return;
    d->front = (d->front - 1 + CAP) % CAP;
    d->data[d->front] = x;
    d->size++;
}

void push_back(struct Deque *d, int x) {
    if (isFull(d)) return;
    d->data[(d->front + d->size) % CAP] = x;
    d->size++;
}

int pop_front(struct Deque *d) {
    int v = d->data[d->front];
    d->front = (d->front + 1) % CAP;
    d->size--;
    return v;
}

int pop_back(struct Deque *d) {
    int idx = back_index(d);
    int v = d->data[idx];
    d->size--;
    return v;
}

int front(struct Deque *d) { return d->data[d->front]; }
int back (struct Deque *d) { return d->data[back_index(d)]; }

void sliding_window_max(int a[], int n, int k) {
    struct Deque d; init(&d);

    for (int i = 0; i < n; i++) {
        if (!isEmpty(&d) && front(&d) <= i - k) pop_front(&d);

        while (!isEmpty(&d) && a[back(&d)] <= a[i]) pop_back(&d);

        push_back(&d, i);

        if (i >= k - 1) printf("%d ", a[front(&d)]);
    }
    printf("\n");
}

int main(void) {
    int a[] = {1, 3, -1, -3, 5, 3, 6, 7};
    int n = sizeof(a) / sizeof(a[0]);
    int k = 3;

    printf("window max (k=%d): ", k);
    sliding_window_max(a, n, k);

    return 0;
}
