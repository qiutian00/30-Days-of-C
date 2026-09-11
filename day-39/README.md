# Day 39: Skip List & Bloom Filter | 跳表与布隆过滤器

> A bilingual (English / 中文) walkthrough of Day 39.
> 本节为第三十九天的补充讲解：跳表与布隆过滤器。

---

## 1. Skip List | 跳表

**English**

A **skip list** is a probabilistic data structure that adds "express lanes" above a sorted linked list, giving **O(log n)** average search/insert/delete — comparable to a balanced tree but much simpler to implement. It is used in Redis's sorted sets.

**中文**

**跳表**是一种概率数据结构，在有序链表之上添加"快速通道"，使平均查找/插入/删除达到 **O(log n)** —— 可与平衡树媲美，但实现简单得多。Redis 的有序集合就使用了跳表。

**English**

Idea: each node is promoted to higher levels with some probability (e.g. 1/2), creating shorter upper lists. Search starts at the top-left, drops down and skips ahead.

**中文**

思路：每个节点以一定概率（如 1/2）被提升到更高层，形成更短的上层链表。查找从左上角开始，不断下降并向前跳过。

```c
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_LEVEL 6

struct SLNode {
    int key;
    struct SLNode **next;   /* next[i] points to the next node at level i */
};

struct SLNode *sl_new(int key, int level) {
    struct SLNode *n = malloc(sizeof(*n));
    n->key = key;
    n->next = calloc(level, sizeof(struct SLNode *));
    return n;
}

/* Random level with geometric distribution (p = 1/2). */
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
```

---

## 2. Bloom Filter | 布隆过滤器

**English**

A **Bloom filter** is a space-efficient probabilistic set. It uses `k` hash functions to set bits in a bit array. It can tell you "definitely not present" or "possibly present" — it never has false negatives, but it **can** have false positives.

**中文**

**布隆过滤器**是一种空间高效的概率性集合。它用 `k` 个哈希函数在比特数组中置位。它能告诉你"一定不存在"或"可能存在" —— 它**没有假阴性**，但**可能**有假阳性。

```c
#include <stdbool.h>
#include <string.h>

#define BITS 64

unsigned char filter[(BITS + 7) / 8];

void bf_set(int bit)   { filter[bit / 8] |=  (1 << (bit % 8)); }
bool bf_get(int bit)   { return filter[bit / 8] & (1 << (bit % 8)); }

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
    bf_set(djb2(s)  % BITS);
    bf_set(sdbm(s)  % BITS);
}

bool bf_contains(const char *s) {
    return bf_get(djb2(s) % BITS) && bf_get(sdbm(s) % BITS);
}
```

**English**

Add inserts bits for each hash; `contains` checks them all. If any bit is 0, the item is definitely absent. If all are 1, it is *probably* present (a false positive is possible).

**中文**

添加时对每个哈希结果置位；`contains` 检查所有位。若任一位为 0，则元素一定不存在；若全为 1，则*可能*存在（可能误报）。

---

## 3. Demo | 示例

```c
int main(void)
{
    struct SLNode *head = sl_new(INT_MIN, MAX_LEVEL);

    sl_insert(head, 3); sl_insert(head, 6); sl_insert(head, 7);
    sl_insert(head, 9); sl_insert(head, 12);

    printf("skip list search 7  -> %s\n", sl_search(head, 7)  ? "found" : "not found");
    printf("skip list search 8  -> %s\n", sl_search(head, 8)  ? "found" : "not found");

    bf_add("apple");
    bf_add("banana");
    printf("bloom contains apple  -> %s\n", bf_contains("apple")  ? "probably" : "no");
    printf("bloom contains grape  -> %s\n", bf_contains("grape")  ? "probably" : "no");
    return 0;
}
```

**Expected output | 期望输出**:
```
skip list search 7  -> found
skip list search 8  -> not found
bloom contains apple  -> probably
bloom contains grape  -> no
```

---

## 4. Complexity & Applications | 复杂度与应用

**English**

| Structure | Search | Insert | Space |
|-----------|--------|--------|-------|
| Skip list | O(log n) avg | O(log n) avg | O(n) |
| Bloom filter | O(k) | O(k) | O(m) bits |

Applications: skip lists in Redis/LSM databases; Bloom filters in caches (avoid disk lookups), spell-checkers, network routers, and database query optimizers.

**中文**

| 结构 | 查找 | 插入 | 空间 |
|------|------|------|------|
| 跳表 | 平均 O(log n) | 平均 O(log n) | O(n) |
| 布隆过滤器 | O(k) | O(k) | O(m) 比特 |

应用：跳表用于 Redis/LSM 数据库；布隆过滤器用于缓存（避免磁盘查找）、拼写检查、网络路由器和数据库查询优化器。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `skip_list.c` | Skip list insert/search | 跳表插入/查找 |
| `bloom_filter.c` | Bloom filter add/contains | 布隆过滤器 |
| `day-39-summary.md` | Day 39 notes | 第三十九天学习笔记 |
