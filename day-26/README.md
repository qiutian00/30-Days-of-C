# Day 26: Queues | 队列

> A bilingual (English / 中文) walkthrough of Day 26.
> 本节为第二十六天的双语概念讲解。

---

## 1. Overview | 概述

**English**

A **queue** is a **First-In, First-Out (FIFO)** structure: elements leave in the same order they arrived.

Core operations:

- `enqueue(x)` — add `x` at the **rear**.
- `dequeue()`   — remove and return the element at the **front**.
- `front()`     — peek at the front element.
- `isEmpty()` — whether the queue is empty.

All operations run in **O(1)** time.

**中文**

**队列**是一种**先进先出（FIFO）**结构：元素按入队顺序出队。

核心操作：

- `enqueue(x)` —— 在**队尾**加入 `x`。
- `dequeue()`  —— 移除并返回**队首**元素。
- `front()`    —— 查看队首元素。
- `isEmpty()` —— 判断队列是否为空。

所有操作均为 **O(1)** 时间。

---

## 2. Circular Array Queue | 循环数组队列

```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CAP 100

struct Queue {
    int data[CAP];
    int front;     /* index of the front element */
    int rear;      /* index of the last element  */
    int size;      /* number of elements          */
};

void init(struct Queue *q)       { q->front = q->rear = 0; q->size = 0; }
bool isEmpty(struct Queue *q)    { return q->size == 0; }
bool isFull(struct Queue *q)     { return q->size == CAP; }

void enqueue(struct Queue *q, int x) {
    if (isFull(q)) { fprintf(stderr, "queue overflow\n"); exit(1); }
    q->rear = (q->rear + 1) % CAP;     /* wrap around */
    q->data[q->rear] = x;
    q->size++;
}

int dequeue(struct Queue *q) {
    if (isEmpty(q)) { fprintf(stderr, "queue underflow\n"); exit(1); }
    q->front = (q->front + 1) % CAP;
    q->size--;
    return q->data[q->front];
}
```

**English**

- A **size** field tracks the element count, making empty/full checks trivial.
- `% CAP` **wraps the indices around** so the array acts like a ring — no shifting needed.
- Alternatively use the invariant `(rear + 1) % CAP == front` to detect full, wasting one slot.

**中文**

- 用一个 **size** 字段记录元素个数，空/满判断变得简单。
- `% CAP` **让下标回绕**，使数组像环形一样使用 —— 无需移动元素。
- 另一种做法是用不变式 `(rear + 1) % CAP == front` 判满，牺牲一个槽位。

---

## 3. Linked-List Queue | 链表队列

```c
struct QNode {
    int data;
    struct QNode *next;
};

struct LQueue {
    struct QNode *front, *rear;
    int size;
};

void linit(struct LQueue *q)      { q->front = q->rear = NULL; q->size = 0; }
bool lisEmpty(struct LQueue *q)   { return q->front == NULL; }

void lenqueue(struct LQueue *q, int x) {
    struct QNode *n = malloc(sizeof(*n));
    n->data = x; n->next = NULL;
    if (q->rear) q->rear->next = n;
    else         q->front = n;     /* first element */
    q->rear = n;
    q->size++;
}

int ldequeue(struct LQueue *q) {
    if (lisEmpty(q)) { fprintf(stderr, "underflow\n"); exit(1); }
    struct QNode *n = q->front;
    int v = n->data;
    q->front = n->next;
    if (!q->front) q->rear = NULL;   /* became empty */
    free(n);
    q->size--;
    return v;
}
```

**English**

Keep a `front` and a `rear` pointer. `enqueue` appends to the tail; `dequeue` removes the head. Capacity is limited only by memory.

**中文**

维护 `front` 和 `rear` 两个指针。`enqueue` 在尾部追加；`dequeue` 删除头节点。容量仅受内存限制。

---

## 4. Demo | 示例

```c
int main(void)
{
    struct Queue q; init(&q);
    enqueue(&q, 10); enqueue(&q, 20); enqueue(&q, 30);
    printf("dequeue = %d\n", dequeue(&q));   /* 10 */
    printf("dequeue = %d\n", dequeue(&q));   /* 20 */
    enqueue(&q, 40);
    while (!isEmpty(&q))
        printf("dequeue = %d\n", dequeue(&q));
    return 0;
}
```

**Expected output | 期望输出**:
```
dequeue = 10
dequeue = 20
dequeue = 30
dequeue = 40
```

---

## 5. Applications | 应用场景

**English**
- Task scheduling / job queues.
- BFS in graphs and trees.
- Print spooling, message queues, producer-consumer buffering.

**中文**
- 任务调度 / 作业队列。
- 图和树的 BFS。
- 打印队列、消息队列、生产者-消费者缓冲。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `array_queue.c` | Circular-array queue demo | 循环数组队列示例 |
| `linked_queue.c` | Linked-list queue demo | 链表队列示例 |
| `day-26-summary.md` | Day 26 notes | 第二十六天学习笔记 |