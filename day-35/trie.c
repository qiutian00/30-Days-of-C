#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA 26

struct Trie {
    struct Trie *child[ALPHA];
    bool is_end;
};

struct Trie *trie_new(void) {
    return calloc(1, sizeof(struct Trie));
}

void trie_insert(struct Trie *root, const char *word) {
    struct Trie *t = root;
    for (; *word; word++) {
        int idx = *word - 'a';
        if (!t->child[idx])
            t->child[idx] = trie_new();
        t = t->child[idx];
    }
    t->is_end = true;
}

bool trie_search(struct Trie *root, const char *word) {
    struct Trie *t = root;
    for (; *word; word++) {
        int idx = *word - 'a';
        if (!t->child[idx]) return false;
        t = t->child[idx];
    }
    return t->is_end;
}

bool trie_starts_with(struct Trie *root, const char *prefix) {
    struct Trie *t = root;
    for (; *prefix; prefix++) {
        int idx = *prefix - 'a';
        if (!t->child[idx]) return false;
        t = t->child[idx];
    }
    return true;
}

void collect(struct Trie *t, char *buf, int depth, char words[][32], int *count) {
    if (t->is_end) {
        buf[depth] = '\0';
        strcpy(words[(*count)++], buf);
    }
    for (int i = 0; i < ALPHA; i++) {
        if (t->child[i]) {
            buf[depth] = (char)('a' + i);
            collect(t->child[i], buf, depth + 1, words, count);
        }
    }
}

void autocomplete(struct Trie *root, const char *prefix, char words[][32], int *count) {
    *count = 0;
    struct Trie *t = root;
    char buf[32];
    strcpy(buf, prefix);

    for (; *prefix; prefix++) {
        int idx = *prefix - 'a';
        if (!t->child[idx]) return;
        t = t->child[idx];
    }
    collect(t, buf, (int)strlen(buf), words, count);
}

int main(void) {
    struct Trie *root = trie_new();
    const char *words[] = {"cat", "car", "card", "dog", "do", "dot"};
    for (int i = 0; i < 6; i++) trie_insert(root, words[i]);

    printf("search \"cat\"  = %d\n", trie_search(root, "cat"));
    printf("search \"ca\"   = %d\n", trie_search(root, "ca"));
    printf("search \"cow\"  = %d\n", trie_search(root, "cow"));
    printf("prefix \"ca\"   = %d\n", trie_starts_with(root, "ca"));

    char out[32][32];
    int count;
    autocomplete(root, "ca", out, &count);
    printf("autocomplete \"ca\": ");
    for (int i = 0; i < count; i++) printf("%s ", out[i]);
    printf("\n");

    return 0;
}
