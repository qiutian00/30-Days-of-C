#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct QNode {
    int data;
    struct QNode *next;
};

struct LQueue {
    struct QNode *front, *rear;
    int size;
};

static void linit(struct LQueue *q)    { q->front = q->rear = NULL; q->size = 0; }
static bool lisEmpty(struct LQueue *q) { return q->front == NULL; }

static void lenqueue(struct LQueue *q, int x) {
    struct QNode *n = malloc(sizeof(*n));
    n->data = x; n->next = NULL;
    if (q->rear) q->rear->next = n;
    else         q->front = n;
    q->rear = n;
    q->size++;
}

static int ldequeue(struct LQueue *q) {
    if (lisEmpty(q)) { fprintf(stderr, "underflow\n"); exit(1); }
    struct QNode *n = q->front;
    int v = n->data;
    q->front = n->next;
    if (!q->front) q->rear = NULL;
    free(n);
    q->size--;
    return v;
}

int main(void)
{
    struct LQueue q; linit(&q);
    lenqueue(&q, 1); lenqueue(&q, 2); lenqueue(&q, 3);
    while (!lisEmpty(&q))
        printf("dequeue = %d\n", ldequeue(&q));
    return 0;
}
