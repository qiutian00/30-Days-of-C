#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LEVEL 6

struct SLNode {
    int key;
    struct SLNode **next;
};

struct SLNode *sl_new(int key, int level) {
    struct SLNode *n = malloc(sizeof(*n));
    n->key = key;
    n->next = calloc(level, sizeof(struct SLNode *));
    return n;
}

int random_level(void) {
    int lvl = 1;
    while (lvl < MAX_LEVEL && (rand() % 2) == 0) lvl++;
    return lvl;
}

struct SLNode *sl_insert(struct SLNode *head, int key) {
    struct SLNode *update[MAX_LEVEL];
    struct SLNode *cur = head;

    for (int i = MAX_LEVEL - 1; i >= 0; i--) {
        while (cur->next[i] && cur->next[i]->key < key) cur = cur->next[i];
        update[i] = cur;
    }

    int lvl = random_level();
    struct SLNode *n = sl_new(key, lvl);
    for (int i = 0; i < lvl; i++) {
        n->next[i] = update[i]->next[i];
        update[i]->next[i] = n;
    }
    return n;
}

struct SLNode *sl_search(struct SLNode *head, int key) {
    struct SLNode *cur = head;
    for (int i = MAX_LEVEL - 1; i >= 0; i--)
        while (cur->next[i] && cur->next[i]->key < key) cur = cur->next[i];

    cur = cur->next[0];
    return (cur && cur->key == key) ? cur : NULL;
}

int main(void) {
    struct SLNode *head = sl_new(INT_MIN, MAX_LEVEL);

    sl_insert(head, 3); sl_insert(head, 6); sl_insert(head, 7);
    sl_insert(head, 9); sl_insert(head, 12);

    printf("search 7 -> %s\n", sl_search(head, 7) ? "found" : "not found");
    printf("search 8 -> %s\n", sl_search(head, 8) ? "found" : "not found");

    return 0;
}
