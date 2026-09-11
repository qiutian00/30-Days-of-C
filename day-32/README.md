# Day 32: Heap & Priority Queue | 堆与优先队列

> A bilingual (English / 中文) walkthrough of Day 32.
> 本节为第三十二天的补充讲解：堆与优先队列。

---

## 1. Overview | 概述

**English**

A **heap** is a complete binary tree that satisfies the **heap property**: in a **max-heap** every parent is `>=` its children; in a **min-heap** every parent is `<=` its children.

A **priority queue** is the abstract interface — `push`, `pop` (always the max/min), and `peek` — and a heap is its most common implementation.

**中文**

**堆**是一棵满足**堆性质**的完全二叉树：**大顶堆（max-heap）**中每个父节点 `>=` 其子节点；**小顶堆（min-heap）**中每个父节点 `<=` 其子节点。

**优先队列**是抽象接口 —— `push`、`pop`（总是弹出最大/最小值）、`peek` —— 而堆是它最常见的实现。

---

## 2. Array Representation | 数组表示

**English**

A heap is stored in an array with no pointers. For a node at index `i` (0-based):

- left child: `2*i + 1`
- right child: `2*i + 2`
- parent: `(i - 1) / 2`

**中文**

堆用数组存储，无需指针。对于下标 `i` 的节点（从 0 开始）：

- 左孩子：`2*i + 1`
- 右孩子：`2*i + 2`
- 父节点：`(i - 1) / 2`

---

## 3. Max-Heap Implementation | 大顶堆实现

```c
#include <stdio.h>

#define CAP 100

struct Heap {
    int arr[CAP];
    int size;
};

void swap(int *a, int *b) { int t = *a; *a = *b; *b = t; }

void init(struct Heap *h) { h->size = 0; }

int peek(struct Heap *h) { return h->arr[0]; }

void push(struct Heap *h, int x) {
    h->arr[h->size] = x;
    int i = h->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (h->arr[p] >= h->arr[i]) break;   /* heap property ok */
        swap(&h->arr[p], &h->arr[i]);
        i = p;
    }
}

/* Sift the root down until the heap property holds. */
void heapify_down(struct Heap *h, int i) {
    for (;;) {
        int l = 2 * i + 1, r = 2 * i + 2, largest = i;
        if (l < h->size && h->arr[l] > h->arr[largest]) largest = l;
        if (r < h->size && h->arr[r] > h->arr[largest]) largest = r;
        if (largest == i) break;
        swap(&h->arr[i], &h->arr[largest]);
        i = largest;
    }
}

int pop(struct Heap *h) {
    int top = h->arr[0];
    h->arr[0] = h->arr[--h->size];
    heapify_down(h, 0);
    return top;
}

/* Build a heap from an arbitrary array in O(n). */
void build_heap(struct Heap *h, int a[], int n) {
    for (int i = 0; i < n; i++) h->arr[i] = a[i];
    h->size = n;
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify_down(h, i);
}
```

**English**

- `push` bubbles the new element **up** (`O(log n)`).
- `pop` swaps the root with the last element, shrinks, then sifts **down** (`O(log n)`).
- `build_heap` works bottom-up from the last internal node and runs in **O(n)**.

**中文**

- `push` 把新元素**上浮**（`O(log n)`）。
- `pop` 把根与最后一个元素交换、缩小，再**下沉**（`O(log n)`）。
- `build_heap` 从最后一个内部节点自底向上构建，时间为 **O(n)**。

---

## 4. Heap Sort | 堆排序

**English**

Since popping a max-heap always yields the largest remaining element, repeatedly popping gives a sorted (descending) sequence — **heap sort**. In-place, it sorts ascending by moving the root to the end.

**中文**

由于从大顶堆弹出一律得到剩余最大元素，反复弹出即得到降序序列 —— **堆排序**。原地实现时，把根移到末尾即可得到升序。

```c
void heap_sort(int a[], int n) {
    struct Heap h;
    build_heap(&h, a, n);
    for (int i = n - 1; i >= 0; i--) {
        swap(&h.arr[0], &h.arr[i]);   /* move max to its final place */
        h.size--;
        heapify_down(&h, 0);
    }
    for (int i = 0; i < n; i++) a[i] = h.arr[i];
}
```

**English**

Heap sort runs in **O(n log n)** time with **O(1)** extra space and is not stable.

**中文**

堆排序时间复杂度 **O(n log n)**，额外空间 **O(1)**，但不是稳定排序。

---

## 5. Demo | 示例

```c
int main(void)
{
    struct Heap h; init(&h);
    push(&h, 3); push(&h, 10); push(&h, 5); push(&h, 1); push(&h, 8);

    printf("peek = %d\n", peek(&h));
    while (h.size > 0)
        printf("pop = %d\n", pop(&h));

    int a[] = {12, 4, 5, 3, 8, 7};
    heap_sort(a, 6);
    printf("sorted: ");
    for (int i = 0; i < 6; i++) printf("%d ", a[i]);
    printf("\n");
    return 0;
}
```

**Expected output | 期望输出**:
```
peek = 10
pop = 10
pop = 8
pop = 5
pop = 3
pop = 1
sorted: 3 4 5 7 8 12
```

---

## 6. Complexity & Applications | 复杂度与应用

**English**

| Operation | Time |
|-----------|------|
| `push` / `pop` / `peek` | O(log n), O(log n), O(1) |
| `build_heap` | O(n) |

Applications: **Dijkstra** and **Prim** (min-heap), scheduling by priority, top-k problems, median maintenance (two heaps), heap sort.

**中文**

| 操作 | 时间 |
|------|------|
| `push` / `pop` / `peek` | O(log n)、O(log n)、O(1) |
| `build_heap` | O(n) |

应用：**Dijkstra** 与 **Prim**（小顶堆）、按优先级调度、Top-K 问题、维护中位数（双堆）、堆排序。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `max_heap.c` | Max-heap / priority queue demo | 大顶堆 / 优先队列示例 |
| `heap_sort.c` | In-place heap sort | 原地堆排序 |
| `day-32-summary.md` | Day 32 notes | 第三十二天学习笔记 |
