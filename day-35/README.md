# Day 35: Trie | 字典树

> A bilingual (English / 中文) walkthrough of Day 35.
> 本节为第三十五天的补充讲解：字典树（Trie）。

---

## 1. Overview | 概述

**English**

A **trie** (prefix tree) stores a set of strings by sharing common prefixes. Each edge is labeled by a character, and a node is marked if some word ends there.

Key properties:

- Insert, search, and prefix-existence all run in **O(L)**, where `L` is the length of the word — independent of how many words are stored.
- Ideal for autocomplete, spell-check, and IP-routing prefix lookup.

**中文**

**字典树（前缀树）**通过共享公共前缀来存储字符串集合。每条边标有一个字符，若某个单词在该节点结束则打上标记。

关键性质：

- 插入、查找、前缀查询均为 **O(L)**，其中 `L` 为单词长度 —— 与已存储单词总数无关。
- 非常适合自动补全、拼写检查和 IP 路由前缀查找。

---

## 2. Array-of-Children Implementation | 子节点数组实现

**English**

A fixed 26-child array (lowercase letters) is simple and fast. Memory can be optimized later (hash map, linked list, or compressed/Patricia trie).

**中文**

固定 26 个子节点数组（小写字母）简单且快。后续可用哈希表、链表或压缩字典树（Patricia）优化内存。

```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define ALPHA 26

struct Trie {
    struct Trie *child[ALPHA];
    bool is_end;                 /* a word ends here */
};

struct Trie *trie_new(void) {
    struct Trie *t = calloc(1, sizeof(*t));
    return t;
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
    return true;                  /* prefix exists, even if no word ends here */
}
```

---

## 3. Autocomplete | 自动补全

**English**

Walk to the prefix node, then DFS to collect every word that ends in its subtree.

**中文**

先走到前缀节点，再 DFS 收集其子树中所有结束的单词。

```c
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

    for (; *prefix; prefix++) {       /* descend to the prefix node */
        int idx = *prefix - 'a';
        if (!t->child[idx]) return;   /* no words with this prefix */
        t = t->child[idx];
    }
    collect(t, buf, (int)strlen(buf), words, count);
}
```

---

## 4. Demo | 示例

```c
int main(void)
{
    struct Trie *root = trie_new();
    const char *words[] = {"cat", "car", "card", "dog", "do", "dot"};
    for (int i = 0; i < 6; i++) trie_insert(root, words[i]);

    printf("search \"cat\"  = %d\n", trie_search(root, "cat"));
    printf("search \"ca\"   = %d\n", trie_search(root, "ca"));      /* not a full word */
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
```

**Expected output | 期望输出**:
```
search "cat"  = 1
search "ca"   = 0
search "cow"  = 0
prefix "ca"   = 1
autocomplete "ca": cat car card
```

---

## 5. Complexity & Applications | 复杂度与应用

**English**

| Operation | Time |
|-----------|------|
| insert / search / starts_with | O(L) |

Applications: autocomplete, spell-checking, IP routing (longest-prefix match), word games (Boggle), T9 predictive text.

**中文**

| 操作 | 时间 |
|------|------|
| insert / search / starts_with | O(L) |

应用：自动补全、拼写检查、IP 路由（最长前缀匹配）、单词游戏（Boggle）、T9 输入法联想。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `trie.c` | Trie insert/search/prefix + autocomplete | 字典树 + 自动补全 |
| `day-35-summary.md` | Day 35 notes | 第三十五天学习笔记 |
