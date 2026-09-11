# Day 31: Hash Table | 哈希表

> A bilingual (English / 中文) walkthrough of Day 31.
> 本节为第三十一天的补充讲解：哈希表。

---

## 1. Overview | 概述

**English**

A **hash table** maps keys to values in **O(1)** average time. It computes an array index from a key via a **hash function**, then stores the entry there.

Key concepts:

- **Hash function** `h(key)` — converts a key into an integer index.
- **Collision** — two different keys map to the same index.
- **Load factor** — `n / capacity`; resizing keeps it low so operations stay fast.

**中文**

**哈希表**以**平均 O(1)** 的时间将键映射到值。它通过**哈希函数**由键算出数组下标，再把条目存到该位置。

关键概念：

- **哈希函数** `h(key)` —— 把键转换成一个整数下标。
- **冲突（Collision）** —— 两个不同键映射到同一个下标。
- **装载因子（Load factor）** —— `n / capacity`；扩容使其保持较低，从而保证操作快速。

---

## 2. Hash Function | 哈希函数

```c
/* A simple hash for integer keys | 针对整数键的简单哈希 */
int hash_int(int key, int capacity)
{
    return ((unsigned)key) % capacity;
}

/* djb2 — a popular hash for strings | 针对字符串的经典 djb2 哈希 */
unsigned long hash_str(const char *s)
{
    unsigned long h = 5381;
    int c;
    while ((c = *s++))
        h = ((h << 5) + h) + c;   /* h * 33 + c */
    return h;
}
```

**English**

A good hash function spreads keys uniformly to reduce collisions. For strings, `djb2` is simple and effective. The result is reduced with `% capacity`.

**中文**

好的哈希函数把键均匀散开以降低冲突。对字符串，`djb2` 简单且有效。结果用 `% capacity` 取模。

---

## 3. Collision Resolution: Chaining | 冲突处理：链地址法

**English**

Each bucket is a linked list (or any small dynamic structure). Every key whose hash lands on the same index is stored in that bucket's list, so the table may hold more entries than its capacity — the load factor is allowed to exceed 1.

- **Insert** — compute `idx = h(key)`, then prepend (or append) a new node to `buckets[idx]`. Prepending runs in O(1).
- **Lookup** — compute `idx = h(key)`, then linear-scan that bucket's short list, comparing keys with `strcmp` (or `==`).
- **Delete** — standard singly-linked-list deletion: unlink the node, then `free` the key and the node.
- **Load factor** `λ = n / m` — the average chain length is `λ`, so lookups average **O(1 + λ)**, i.e. O(1) when `λ` is bounded by a small constant.

**Pros**: simple; tolerant of a high load factor; deletion is trivial. **Cons**: extra memory for `next` pointers; nodes are scattered in memory (poor cache locality); degrades to O(n) if the hash function is poor.

**中文**

每个桶是一条链表（或其它小型动态结构）。所有哈希值落在同一下标上的键都存放在该桶的链表里，因此表可以存放比容量更多的条目——装载因子允许超过 1。

- **插入** —— 计算 `idx = h(key)`，然后把新节点头插（或尾插）到 `buckets[idx]`。头插是 O(1)。
- **查找** —— 计算 `idx = h(key)`，然后线性扫描该桶的短链表，用 `strcmp`（或 `==`）比较键。
- **删除** —— 标准的单链表删除：从链表中摘下节点，再 `free` 掉键与节点。
- **装载因子** `λ = n / m` —— 平均链长为 `λ`，因此查找平均 **O(1 + λ)**，即当 `λ` 被控制在较小常数范围内时为 O(1)。

**优点**：实现简单；能容忍较高的装载因子；删除很直接。**缺点**：需要额外的 `next` 指针内存；节点在内存中分散（缓存局部性差）；哈希函数不好时退化为 O(n)。

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CAP 10

struct Entry {
    char *key;
    int   value;
    struct Entry *next;      /* next entry in the same bucket */
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
    while ((c = *s++)) h = ((h << 5) + h) + c;
    return h;
}

void put(struct HashTable *ht, const char *key, int value) {
    int idx = hash_str(key) % CAP;
    struct Entry *e = ht->buckets[idx];

    while (e) {                                  /* key already exists? */
        if (strcmp(e->key, key) == 0) { e->value = value; return; }
        e = e->next;
    }

    struct Entry *n = malloc(sizeof(*n));        /* prepend new entry */
    n->key = strdup(key);
    n->value = value;
    n->next = ht->buckets[idx];
    ht->buckets[idx] = n;
}

/* Returns the value, or -1 if the key is not found. */
int get(struct HashTable *ht, const char *key) {
    int idx = hash_str(key) % CAP;
    for (struct Entry *e = ht->buckets[idx]; e; e = e->next)
        if (strcmp(e->key, key) == 0) return e->value;
    return -1;                                   /* not found */
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
```

---

## 4. Collision Resolution: Open Addressing | 冲突处理：开放寻址法

**English**

All entries live inside the array itself, at most one per slot. When the target slot is occupied, we walk a **deterministic probe sequence** to find an empty slot. Common probe sequences:

- **Linear probing** — `h(k, i) = (h(k) + i) mod m`. Simple, but suffers **primary clustering**: occupied slots form long contiguous runs, and any key hashing into a run extends it further.
- **Quadratic probing** — `h(k, i) = (h(k) + c₁·i + c₂·i²) mod m`. Avoids primary clustering but keys with the same initial hash still follow the same sequence (**secondary clustering**).
- **Double hashing** — `h(k, i) = (h₁(k) + i·h₂(k)) mod m`, using a second hash function `h₂`. Generally the best of the three; sequences depend on the key, not just the initial slot.

Because each slot holds one entry, the **load factor must stay below 1**; in practice tables are resized around `λ ≈ 0.7`.

- **Insert** — probe until an `EMPTY` slot (or reuse the first `DELETED` tombstone); if the key already exists, update its value.
- **Lookup** — probe along the same sequence; stop at the first `EMPTY` slot (key absent) or when the key matches.
- **Delete** — must mark the slot `DELETED` (a **tombstone**), never `EMPTY`, otherwise the probing chain breaks and later lookups fail prematurely.

**Pros**: better cache locality (contiguous array), no pointer overhead. **Cons**: clustering, mandatory resizing, and the tombstone bookkeeping shown below.

**中文**

所有条目都存放在数组内部，每个槽位至多一个。当目标槽位被占用时，我们沿着一条**确定的探测序列**寻找空槽。常见的探测序列有：

- **线性探测** —— `h(k, i) = (h(k) + i) mod m`。实现简单，但有**主聚集（primary clustering）**问题：被占用的槽位形成连续的长段，任何哈希到该段内的键都会让这段更长。
- **二次探测** —— `h(k, i) = (h(k) + c₁·i + c₂·i²) mod m`。避免了主聚集，但初始哈希相同的键仍走同一条序列（**次聚集 secondary clustering**）。
- **双重哈希** —— `h(k, i) = (h₁(k) + i·h₂(k)) mod m`，使用第二个哈希函数 `h₂`。通常三者中最好；探测序列依赖键本身，而不仅是初始槽位。

因为每个槽位只放一个条目，**装载因子必须小于 1**；实践中通常在 `λ ≈ 0.7` 左右就扩容。

- **插入** —— 一直探测到 `EMPTY` 槽位（或复用第一个 `DELETED` 墓碑）；若键已存在则更新其值。
- **查找** —— 沿同一条序列探测；遇到第一个 `EMPTY` 槽位即停止（键不存在），或键匹配时返回。
- **删除** —— 必须把槽位标记为 `DELETED`（**墓碑**），绝不能标记为 `EMPTY`，否则探测链被打断，后续查找会提前失败。

**优点**：缓存局部性更好（连续数组）、无指针开销。**缺点**：存在聚集现象、必须扩容、以及下面展示的墓碑簿记。

```c
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
        if (t->keys[p] == key) { t->vals[p] = val; return; }   /* update */
        if (t->keys[p] == DELETED && first_del == -1) first_del = p;
        if (t->keys[p] == EMPTY) {                             /* insert */
            if (first_del != -1) p = first_del;
            t->keys[p] = key; t->vals[p] = val;
            return;
        }
    }
    /* table full — real code would resize here */
}

int oa_get(struct OA *t, int key) {
    int idx = ((unsigned)key) % CAP2;
    for (int i = 0; i < CAP2; i++) {
        int p = (idx + i) % CAP2;
        if (t->keys[p] == EMPTY) return -1;                    /* stop probing */
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
```

**English**

Deletion in open addressing must mark a slot `DELETED` (a tombstone) rather than `EMPTY`, otherwise the probing chain is broken and lookups fail prematurely.

**中文**

开放寻址法中，删除必须把槽位标记为 `DELETED`（墓碑）而非 `EMPTY`，否则探测链会被打断，导致查找提前失败。

---

## 5. Demo | 示例

```c
int main(void)
{
    struct HashTable ht; init_ht(&ht);

    put(&ht, "apple",  1);
    put(&ht, "banana", 2);
    put(&ht, "cherry", 3);
    put(&ht, "apple", 10);        /* update existing key */

    printf("apple  = %d\n", get(&ht, "apple"));
    printf("banana = %d\n", get(&ht, "banana"));
    printf("grape  = %d\n", get(&ht, "grape"));   /* not present -> -1 */

    remove_key(&ht, "banana");
    printf("banana after remove = %d\n", get(&ht, "banana"));

    struct OA oa; init_oa(&oa);
    oa_put(&oa, 5, 50);
    oa_put(&oa, 16, 160);        /* 16 % 11 == 5 -> collision, probes to 6 */
    printf("oa[5]  = %d\n", oa_get(&oa, 5));
    printf("oa[16] = %d\n", oa_get(&oa, 16));
    oa_remove(&oa, 5);
    printf("oa[5] after remove = %d\n", oa_get(&oa, 5));
    return 0;
}
```

**Expected output | 期望输出**:
```
apple  = 10
banana = 2
grape  = -1
banana after remove = -1
oa[5]  = 50
oa[16] = 160
oa[5] after remove = -1
```

---

## 6. Complexity & Applications | 复杂度与应用

**English**

| Operation | Average | Worst case |
|-----------|---------|------------|
| `put`/`get`/`remove` | O(1) | O(n) |

Worst case (all keys collide) is rare with a good hash function and low load factor. Applications: symbol tables in compilers, caches, sets (`unordered_set`), databases.

**中文**

| 操作 | 平均 | 最坏 |
|------|------|------|
| `put`/`get`/`remove` | O(1) | O(n) |

有了好的哈希函数和较低的装载因子，最坏情况（所有键冲突）很少发生。应用：编译器符号表、缓存、集合（`unordered_set`）、数据库。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `hash_table_chaining.c` | Hash table with chaining demo | 链地址法哈希表示例 |
| `hash_table_open.c` | Hash table with open addressing demo | 开放寻址法哈希表示例 |
| `day-31-summary.md` | Day 31 notes | 第三十一天学习笔记 |
