#include <stdio.h>

#define CAP2 11
#define EMPTY -1
#define DELETED -2

struct OA {
    int keys[CAP2];
    int vals[CAP2];
};

void init_oa(struct OA *t) {
    for (int i = 0; i < CAP2; i++) t->keys[i] = EMPTY;
}

void oa_put(struct OA *t, int key, int val) {
    int idx = ((unsigned)key) % CAP2;
    int first_del = -1;

    for (int i = 0; i < CAP2; i++) {
        int p = (idx + i) % CAP2;
        if (t->keys[p] == key) { t->vals[p] = val; return; }
        if (t->keys[p] == DELETED && first_del == -1) first_del = p;
        if (t->keys[p] == EMPTY) {
            if (first_del != -1) p = first_del;
            t->keys[p] = key; t->vals[p] = val;
            return;
        }
    }
}

int oa_get(struct OA *t, int key) {
    int idx = ((unsigned)key) % CAP2;
    for (int i = 0; i < CAP2; i++) {
        int p = (idx + i) % CAP2;
        if (t->keys[p] == EMPTY) return -1;
        if (t->keys[p] == key)   return t->vals[p];
    }
    return -1;
}

void oa_remove(struct OA *t, int key) {
    int idx = ((unsigned)key) % CAP2;
    for (int i = 0; i < CAP2; i++) {
        int p = (idx + i) % CAP2;
        if (t->keys[p] == EMPTY) return;
        if (t->keys[p] == key) { t->keys[p] = DELETED; return; }
    }
}

int main(void) {
    struct OA oa; init_oa(&oa);

    oa_put(&oa, 5, 50);
    oa_put(&oa, 16, 160);   /* 16 % 11 == 5 -> collision, probes to 6 */

    printf("oa[5]  = %d\n", oa_get(&oa, 5));
    printf("oa[16] = %d\n", oa_get(&oa, 16));

    oa_remove(&oa, 5);
    printf("oa[5] after remove = %d\n", oa_get(&oa, 5));
    printf("oa[16] still reachable = %d\n", oa_get(&oa, 16));

    return 0;
}
