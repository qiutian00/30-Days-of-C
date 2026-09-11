#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAP 10

struct Entry {
    char *key;
    int   value;
    struct Entry *next;
};

struct HashTable {
    struct Entry *buckets[CAP];
};

void init_ht(struct HashTable *ht) {
    for (int i = 0; i < CAP; i++)
        ht->buckets[i] = NULL;
}

unsigned long hash_str(const char *s) {
    unsigned long h = 5381;
    int c;
    while ((c = *s++)) h = ((h << 5) + h) + c;   /* h * 33 + c */
    return h;
}

void put(struct HashTable *ht, const char *key, int value) {
    int idx = hash_str(key) % CAP;
    struct Entry *e = ht->buckets[idx];

    while (e) {
        if (strcmp(e->key, key) == 0) { e->value = value; return; }
        e = e->next;
    }

    struct Entry *n = malloc(sizeof(*n));
    n->key = strdup(key);
    n->value = value;
    n->next = ht->buckets[idx];
    ht->buckets[idx] = n;
}

int get(struct HashTable *ht, const char *key) {
    int idx = hash_str(key) % CAP;
    for (struct Entry *e = ht->buckets[idx]; e; e = e->next)
        if (strcmp(e->key, key) == 0) return e->value;
    return -1;
}

void remove_key(struct HashTable *ht, const char *key) {
    int idx = hash_str(key) % CAP;
    struct Entry *e = ht->buckets[idx], *prev = NULL;

    while (e) {
        if (strcmp(e->key, key) == 0) {
            if (prev) prev->next = e->next;
            else      ht->buckets[idx] = e->next;
            free(e->key);
            free(e);
            return;
        }
        prev = e;
        e = e->next;
    }
}

int main(void) {
    struct HashTable ht; init_ht(&ht);

    put(&ht, "apple",  1);
    put(&ht, "banana", 2);
    put(&ht, "cherry", 3);
    put(&ht, "apple", 10);        /* update */

    printf("apple  = %d\n", get(&ht, "apple"));
    printf("banana = %d\n", get(&ht, "banana"));
    printf("grape  = %d\n", get(&ht, "grape"));   /* -1 */

    remove_key(&ht, "banana");
    printf("banana after remove = %d\n", get(&ht, "banana"));

    return 0;
}
