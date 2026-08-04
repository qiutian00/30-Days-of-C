#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CAP 100

struct Queue {
    int data[CAP];
    int front, rear, size;
};

static void init(struct Queue *q)    { q->front = q->rear = 0; q->size = 0; }
static bool isEmpty(struct Queue *q) { return q->size == 0; }
static bool isFull(struct Queue *q)  { return q->size == CAP; }

static void enqueue(struct Queue *q, int x) {
    if (isFull(q)) { fprintf(stderr, "queue overflow\n"); exit(1); }
    q->rear = (q->rear + 1) % CAP;
    q->data[q->rear] = x;
    q->size++;
}

static int dequeue(struct Queue *q) {
    if (isEmpty(q)) { fprintf(stderr, "queue underflow\n"); exit(1); }
    q->front = (q->front + 1) % CAP;
    q->size--;
    return q->data[q->front];
}

int main(void)
{
    struct Queue q; init(&q);
    enqueue(&q, 10); enqueue(&q, 20); enqueue(&q, 30);
    printf("dequeue = %d\n", dequeue(&q));
    printf("dequeue = %d\n", dequeue(&q));
    enqueue(&q, 40);
    while (!isEmpty(&q))
        printf("dequeue = %d\n", dequeue(&q));
    return 0;
}
