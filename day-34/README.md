# Day 34: Deque | 双端队列

> A bilingual (English / 中文) walkthrough of Day 34.
> 本节为第三十四天的补充讲解：双端队列（Deque）。

---

## 1. Overview | 概述

**English**

A **deque** (double-ended queue) supports insertion and removal at **both** ends, all in **O(1)** time. It generalizes both stacks and queues: a stack restricts it to one end, a queue uses opposite ends.

Core operations:

- `push_front(x)` / `push_back(x)`
- `pop_front()` / `pop_back()`
- `front()` / `back()`

**中文**

**双端队列（Deque）**支持在**两端**进行插入与删除，全部 **O(1)**。它同时推广了栈和队列：栈只在一端操作，队列在两端分别进出。

核心操作：

- `push_front(x)` / `push_back(x)`
- `pop_front()` / `pop_back()`
- `front()` / `back()`

---

## 2. Circular Array Deque | 循环数组双端队列

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CAP 10

struct Deque {
    int data[CAP];
    int front;   /* index of the front element */
    int size;
};

void init(struct Deque *d) { d->front = 0; d->size = 0; }

bool isEmpty(struct Deque *d) { return d->size == 0; }
bool isFull (struct Deque *d) { return d->size == CAP; }

static int back_index(struct Deque *d) {
    return (d->front + d->size - 1) % CAP;   /* last element */
}

void push_front(struct Deque *d, int x) {
    if (isFull(d)) { fprintf(stderr, "deque overflow\n"); exit(1); }
    d->front = (d->front - 1 + CAP) % CAP;   /* move front back */
    d->data[d->front] = x;
    d->size++;
}

void push_back(struct Deque *d, int x) {
    if (isFull(d)) { fprintf(stderr, "deque overflow\n"); exit(1); }
    int idx = (d->front + d->size) % CAP;    /* slot just past the back */
    d->data[idx] = x;
    d->size++;
}

int pop_front(struct Deque *d) {
    if (isEmpty(d)) { fprintf(stderr, "deque underflow\n"); exit(1); }
    int v = d->data[d->front];
    d->front = (d->front + 1) % CAP;
    d->size--;
    return v;
}

int pop_back(struct Deque *d) {
    if (isEmpty(d)) { fprintf(stderr, "deque underflow\n"); exit(1); }
    int idx = back_index(d);
    int v = d->data[idx];
    d->size--;
    return v;
}

int front(struct Deque *d) { return d->data[d->front]; }
int back (struct Deque *d) { return d->data[back_index(d)]; }
```

**English**

The `% CAP` wrap-around makes both ends shift cheaply. `front` points at the first element and `size` tracks the count, so `back` is computed as `front + size - 1`.

**中文**

`% CAP` 回绕让两端移动都很廉价。`front` 指向首个元素，`size` 记录元素个数，因此 `back` 由 `front + size - 1` 计算得到。

---

## 3. Linked-List Deque | 链表双端队列

**English**

A doubly linked list (Day 33) is a natural deque: `push_front`/`pop_front` at the head, `push_back`/`pop_back` at the tail. No fixed capacity.

**中文**

双向链表（第三十三天）天然就是一个双端队列：`push_front`/`pop_front` 在头部，`push_back`/`pop_back` 在尾部。没有固定容量。

```c
struct Node { int data; struct Node *prev, *next; };

struct LDeque { struct Node *head, *tail; };

void linit(struct LDeque *d) { d->head = d->tail = NULL; }

void lpush_back(struct LDeque *d, int x) {
    struct Node *n = malloc(sizeof(*n));
    n->data = x; n->prev = d->tail; n->next = NULL;
    if (d->tail) d->tail->next = n; else d->head = n;
    d->tail = n;
}

void lpush_front(struct LDeque *d, int x) {
    struct Node *n = malloc(sizeof(*n));
    n->data = x; n->prev = NULL; n->next = d->head;
    if (d->head) d->head->prev = n; else d->tail = n;
    d->head = n;
}

int lpop_front(struct LDeque *d) {
    struct Node *n = d->head;
    int v = n->data;
    d->head = n->next;
    if (d->head) d->head->prev = NULL; else d->tail = NULL;
    free(n);
    return v;
}

int lpop_back(struct LDeque *d) {
    struct Node *n = d->tail;
    int v = n->data;
    d->tail = n->prev;
    if (d->tail) d->tail->next = NULL; else d->head = NULL;
    free(n);
    return v;
}
```

---

## 4. Application: Sliding Window Maximum | 应用：滑动窗口最大值

**English**

A deque maintains candidate indices for the maximum in a sliding window. Before pushing a new element, pop from the back all elements smaller than it (they can never be the max while the new one is present); pop from the front any index that has left the window.

**中文**

双端队列维护滑动窗口最大值的候选下标。入队前，从队尾弹出所有比新元素小的元素（只要新元素还在，它们永远不可能成为最大值）；从队首弹出已滑出窗口的下标。

```c
void sliding_window_max(int a[], int n, int k) {
    struct Deque d; init(&d);

    for (int i = 0; i < n; i++) {
        if (!isEmpty(&d) && front(&d) <= i - k) pop_front(&d);      /* out of window */

        while (!isEmpty(&d) && a[back(&d)] <= a[i]) pop_back(&d);    /* keep decreasing */

        push_back(&d, i);

        if (i >= k - 1) printf("%d ", a[front(&d)]);                 /* window [i-k+1, i] */
    }
    printf("\n");
}
```

**English**

Each element is pushed and popped at most once, so the whole pass is **O(n)**.

**中文**

每个元素至多入队、出队一次，因此整体为 **O(n)**。

---

## 5. Demo | 示例

```c
int main(void)
{
    struct Deque d; init(&d);
    push_back(&d, 10);
    push_front(&d, 5);
    push_back(&d, 20);

    printf("front = %d, back = %d\n", front(&d), back(&d));
    printf("pop_front = %d\n", pop_front(&d));
    printf("pop_back  = %d\n", pop_back(&d));
    printf("front = %d, back = %d\n", front(&d), back(&d));

    int a[] = {1, 3, -1, -3, 5, 3, 6, 7};
    printf("window max (k=3): ");
    sliding_window_max(a, 8, 3);
    return 0;
}
```

**Expected output | 期望输出**:
```
front = 5, back = 20
pop_front = 5
pop_back  = 20
front = 10, back = 10
window max (k=3): 3 3 5 5 6 7
```

---

## 6. Applications | 应用场景

**English**
- Sliding-window problems (maximum/minimum of each window).
- Work-stealing schedulers (deque used as both stack and queue).
- Palindrome checks, undo/redo with history at both ends.

**中文**
- 滑动窗口问题（每个窗口的最大/最小值）。
- 工作窃取调度器（双端队列同时用作栈和队列）。
- 回文检查、两端历史的撤销/重做。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `array_deque.c` | Circular-array deque demo | 循环数组双端队列示例 |
| `sliding_window.c` | Sliding-window maximum via deque | 滑动窗口最大值 |
| `day-34-summary.md` | Day 34 notes | 第三十四天学习笔记 |
