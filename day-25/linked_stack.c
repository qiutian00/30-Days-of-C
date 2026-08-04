#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct SNode {
    int data;
    struct SNode *next;
};

struct LStack {
    struct SNode *top;
};

static void linit(struct LStack *s)    { s->top = NULL; }
static bool lisEmpty(struct LStack *s) { return s->top == NULL; }

static void lpush(struct LStack *s, int x) {
    struct SNode *n = malloc(sizeof(*n));
    n->data = x;
    n->next = s->top;
    s->top = n;
}

static int lpop(struct LStack *s) {
    if (lisEmpty(s)) { fprintf(stderr, "underflow\n"); exit(1); }
    struct SNode *n = s->top;
    int v = n->data;
    s->top = n->next;
    free(n);
    return v;
}

static int lpeek(struct LStack *s) {
    if (lisEmpty(s)) { fprintf(stderr, "empty\n"); exit(1); }
    return s->top->data;
}

int main(void)
{
    struct LStack s; linit(&s);
    lpush(&s, 1); lpush(&s, 2); lpush(&s, 3);
    printf("peek = %d\n", lpeek(&s));
    while (!lisEmpty(&s))
        printf("pop  = %d\n", lpop(&s));
    return 0;
}
