#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CAP 10

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
    if (isFull(d)) { fprintf(stderr, "deque overflow\n"); exit(1); }
    d->front = (d->front - 1 + CAP) % CAP;
    d->data[d->front] = x;
    d->size++;
}

void push_back(struct Deque *d, int x) {
    if (isFull(d)) { fprintf(stderr, "deque overflow\n"); exit(1); }
    int idx = (d->front + d->size) % CAP;
    d->data[idx] = x;
    d->size++;
}

int pop_front(struct Deque *d) {
    if (isEmpty(d)) { fprintf(stderr, "deque underflow\n"); exit(1); }
    int v = d->data[d->front];
    d->front = (d->front + 1) % CAP;
    d->size--;
    return v;
}

int pop_back(struct Deque *d) {
    if (isEmpty(d)) { fprintf(stderr, "deque underflow\n"); exit(1); }
    int idx = back_index(d);
    int v = d->data[idx];
    d->size--;
    return v;
}

int front(struct Deque *d) { return d->data[d->front]; }
int back (struct Deque *d) { return d->data[back_index(d)]; }

int main(void) {
    struct Deque d; init(&d);
    push_back(&d, 10);
    push_front(&d, 5);
    push_back(&d, 20);

    printf("front = %d, back = %d\n", front(&d), back(&d));
    printf("pop_front = %d\n", pop_front(&d));
    printf("pop_back  = %d\n", pop_back(&d));
    printf("front = %d, back = %d\n", front(&d), back(&d));

    return 0;
}
