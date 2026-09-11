#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
};

struct DList {
    struct Node *head;
    struct Node *tail;
};

struct Node *new_node(int x) {
    struct Node *n = malloc(sizeof(*n));
    n->data = x; n->prev = n->next = NULL;
    return n;
}

void init(struct DList *l) { l->head = l->tail = NULL; }

void push_back(struct DList *l, int x) {
    struct Node *n = new_node(x);
    if (!l->tail) { l->head = l->tail = n; return; }
    n->prev = l->tail;
    l->tail->next = n;
    l->tail = n;
}

void push_front(struct DList *l, int x) {
    struct Node *n = new_node(x);
    if (!l->head) { l->head = l->tail = n; return; }
    n->next = l->head;
    l->head->prev = n;
    l->head = n;
}

void erase(struct DList *l, struct Node *n) {
    if (n->prev) n->prev->next = n->next;
    else         l->head = n->next;
    if (n->next) n->next->prev = n->prev;
    else         l->tail = n->prev;
    free(n);
}

void print_forward(struct DList *l) {
    for (struct Node *n = l->head; n; n = n->next)
        printf("%d ", n->data);
    printf("\n");
}

void print_backward(struct DList *l) {
    for (struct Node *n = l->tail; n; n = n->prev)
        printf("%d ", n->data);
    printf("\n");
}

int main(void) {
    struct DList l; init(&l);
    push_back(&l, 10); push_back(&l, 20); push_back(&l, 30);
    push_front(&l, 5);

    printf("forward : "); print_forward(&l);
    printf("backward: "); print_backward(&l);

    erase(&l, l.head->next);   /* remove 10 */
    printf("after erase: "); print_forward(&l);

    return 0;
}
