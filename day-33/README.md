# Day 33: Doubly & Circular Linked List | 双向与循环链表

> A bilingual (English / 中文) walkthrough of Day 33.
> 本节为第三十三天的补充讲解：双向链表与循环链表。

---

## 1. Overview | 概述

**English**

A **doubly linked list** gives each node a `prev` pointer in addition to `next`, so you can traverse in both directions and delete a node in **O(1)** given only its pointer.

A **circular linked list** links the last node back to the first (singly) or links both ends (doubly), forming a ring with no `NULL`.

**中文**

**双向链表**给每个节点额外增加一个 `prev` 指针，因此可以双向遍历，并且只需节点的指针即可在 **O(1)** 内删除它。

**循环链表**让最后一个节点指回第一个节点（单循环）或首尾互相指向（双循环），形成没有 `NULL` 的环。

---

## 2. Doubly Linked List | 双向链表

```c
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

/* Delete a node given only its pointer — O(1). */
void erase(struct DList *l, struct Node *n) {
    if (n->prev) n->prev->next = n->next;
    else         l->head = n->next;       /* n was head */
    if (n->next) n->next->prev = n->prev;
    else         l->tail = n->prev;       /* n was tail */
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
```

**English**

`erase` needs no search: fixing `prev->next` and `next->prev` unlinks the node. This is the key advantage over a singly linked list.

**中文**

`erase` 无需查找：只需修改 `prev->next` 与 `next->prev` 即可摘除节点。这正是它相比单链表的核心优势。

---

## 3. Circular Linked List | 循环链表

**English**

A singly circular list keeps a pointer to any node (often the tail) and cycles back to itself. Useful for round-robin scheduling, buffers, and board-game turn loops.

**中文**

单循环链表保留指向任意节点（常为尾节点）的指针，并首尾相连。常用于轮转调度、缓冲区和棋盘类游戏的循环回合。

```c
struct CNode {
    int data;
    struct CNode *next;
};

/* Insert after the node `after`, and return the new tail if `tail` was passed. */
struct CNode *cinsert(struct CNode *tail, int x) {
    struct CNode *n = malloc(sizeof(*n));
    n->data = x;

    if (!tail) {            /* first node points to itself */
        n->next = n;
        return n;
    }
    n->next = tail->next;   /* insert just after the (old) tail's next */
    tail->next = n;
    return n;               /* new tail */
}

void cprint(struct CNode *tail) {
    if (!tail) return;
    struct CNode *n = tail->next;          /* head */
    do {
        printf("%d ", n->data);
        n = n->next;
    } while (n != tail->next);
    printf("\n");
}

/* Josephus: every k-th node is removed; return the last survivor. */
int josephus(int n, int k) {
    struct CNode *tail = NULL;
    for (int i = 1; i <= n; i++) tail = cinsert(tail, i);

    struct CNode *cur = tail->next;
    while (cur->next != cur) {
        for (int i = 1; i < k - 1; i++) cur = cur->next;
        struct CNode *gone = cur->next;    /* k-th node */
        cur->next = gone->next;
        free(gone);
        cur = cur->next;
    }
    int survivor = cur->data;
    free(cur);
    return survivor;
}
```

---

## 4. Demo | 示例

```c
int main(void)
{
    struct DList l; init(&l);
    push_back(&l, 10); push_back(&l, 20); push_back(&l, 30);
    push_front(&l, 5);

    printf("forward : "); print_forward(&l);
    printf("backward: "); print_backward(&l);

    erase(&l, l.head->next);   /* remove 10 */
    printf("after erase: "); print_forward(&l);

    printf("Josephus(7, 3) survivor = %d\n", josephus(7, 3));
    return 0;
}
```

**Expected output | 期望输出**:
```
forward : 5 10 20 30
backward: 30 20 10 5
after erase: 5 20 30
Josephus(7, 3) survivor = 4
```

---

## 5. Applications | 应用场景

**English**
- Doubly list: browser history (back/forward), LRU cache, text editors, music playlists.
- Circular list: round-robin scheduling, Josephus problem, circular buffers.

**中文**
- 双向链表：浏览器历史（前进/后退）、LRU 缓存、文本编辑器、音乐播放列表。
- 循环链表：轮转调度、约瑟夫问题、环形缓冲区。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `doubly_list.c` | Doubly linked list demo | 双向链表示例 |
| `circular_list.c` | Circular list + Josephus problem | 循环链表 + 约瑟夫问题 |
| `day-33-summary.md` | Day 33 notes | 第三十三天学习笔记 |
