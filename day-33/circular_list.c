#include <stdio.h>
#include <stdlib.h>

struct CNode {
    int data;
    struct CNode *next;
};

struct CNode *cinsert(struct CNode *tail, int x) {
    struct CNode *n = malloc(sizeof(*n));
    n->data = x;

    if (!tail) {
        n->next = n;
        return n;
    }
    n->next = tail->next;
    tail->next = n;
    return n;
}

void cprint(struct CNode *tail) {
    if (!tail) return;
    struct CNode *n = tail->next;
    do {
        printf("%d ", n->data);
        n = n->next;
    } while (n != tail->next);
    printf("\n");
}

int josephus(int n, int k) {
    struct CNode *tail = NULL;
    for (int i = 1; i <= n; i++) tail = cinsert(tail, i);

    struct CNode *cur = tail->next;
    while (cur->next != cur) {
        for (int i = 1; i < k - 1; i++) cur = cur->next;
        struct CNode *gone = cur->next;
        cur->next = gone->next;
        free(gone);
        cur = cur->next;
    }
    int survivor = cur->data;
    free(cur);
    return survivor;
}

int main(void) {
    struct CNode *tail = NULL;
    for (int i = 1; i <= 5; i++) tail = cinsert(tail, i);
    printf("circular: "); cprint(tail);

    printf("Josephus(7, 3) survivor = %d\n", josephus(7, 3));

    return 0;
}
