#include <stdio.h>
#include <stdbool.h>

#define BITS 64

unsigned char filter[(BITS + 7) / 8];

void bf_set(int bit) { filter[bit / 8] |= (1 << (bit % 8)); }
bool bf_get(int bit) { return filter[bit / 8] & (1 << (bit % 8)); }

unsigned long djb2(const char *s) {
    unsigned long h = 5381;
    int c;
    while ((c = *s++)) h = ((h << 5) + h) + c;
    return h;
}

unsigned long sdbm(const char *s) {
    unsigned long h = 0;
    int c;
    while ((c = *s++)) h = c + (h << 6) + (h << 16) - h;
    return h;
}

void bf_add(const char *s) {
    bf_set(djb2(s) % BITS);
    bf_set(sdbm(s) % BITS);
}

bool bf_contains(const char *s) {
    return bf_get(djb2(s) % BITS) && bf_get(sdbm(s) % BITS);
}

int main(void) {
    bf_add("apple");
    bf_add("banana");

    printf("contains apple -> %s\n", bf_contains("apple") ? "probably" : "no");
    printf("contains grape -> %s\n", bf_contains("grape") ? "probably" : "no");

    return 0;
}
