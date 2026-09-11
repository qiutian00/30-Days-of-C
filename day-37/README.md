# Day 37: Segment Tree & Fenwick Tree | 线段树与树状数组

> A bilingual (English / 中文) walkthrough of Day 37.
> 本节为第三十七天的补充讲解：线段树与树状数组。

---

## 1. Overview | 概述

**English**

Both structures answer **range queries** (sum, min, max, …) and support **point updates** on an array in **O(log n)** time.

- **Segment tree** is general: it handles any associative query (sum, min, max, GCD) and even range updates (with lazy propagation).
- **Fenwick tree** (Binary Indexed Tree) is simpler and faster, but only for **invertible** queries like prefix sums.

**中文**

这两种结构都能在 **O(log n)** 内回答**区间查询**（和、最小值、最大值等）并支持**单点更新**。

- **线段树**更通用：支持任意可结合的查询（和、最小、最大、GCD），配合懒惰传播还能做区间更新。
- **树状数组（Fenwick 树，BIT）**更简单、更快，但只适合**可逆**查询，如前缀和。

---

## 2. Fenwick Tree (BIT) | 树状数组

**English**

A BIT stores partial sums so that `prefix_sum(i)` and `update(i, delta)` are both O(log n). The key trick: index `i` is responsible for `i & -i` elements.

**中文**

树状数组存储部分和，使 `prefix_sum(i)` 和 `update(i, delta)` 都是 O(log n)。关键技巧：下标 `i` 负责 `i & -i` 个元素。

```c
#include <stdio.h>

#define N 100

int bit[N + 1];

void bit_update(int i, int delta, int n) {
    for (; i <= n; i += i & -i)
        bit[i] += delta;
}

int bit_query(int i) {                  /* prefix sum a[1..i] */
    int sum = 0;
    for (; i > 0; i -= i & -i)
        sum += bit[i];
    return sum;
}

int range_sum(int l, int r) {           /* a[l..r], 1-based inclusive */
    return bit_query(r) - bit_query(l - 1);
}
```

**English**

`i & -i` extracts the lowest set bit. `update` walks *up* adding the delta to every node covering `i`; `query` walks *down* summing nodes that partition `[1..i]`.

**中文**

`i & -i` 提取最低位的 1。`update` 向上走，把增量加到每个覆盖 `i` 的节点；`query` 向下走，累加构成 `[1..i]` 的节点。

---

## 3. Segment Tree | 线段树

**English**

A segment tree is a full binary tree over the array; each node stores the aggregate of its segment. Built in O(n), queried/updated in O(log n).

**中文**

线段树是建立在数组上的满二叉树；每个节点保存其区间的聚合值。构建 O(n)，查询/更新 O(log n)。

```c
#define MAXN 100

int seg[4 * MAXN];

void seg_build(int a[], int node, int lo, int hi) {
    if (lo == hi) { seg[node] = a[lo]; return; }
    int mid = (lo + hi) / 2;
    seg_build(a, node * 2,     lo, mid);
    seg_build(a, node * 2 + 1, mid + 1, hi);
    seg[node] = seg[node * 2] + seg[node * 2 + 1];     /* sum */
}

void seg_update(int node, int lo, int hi, int idx, int val) {
    if (lo == hi) { seg[node] = val; return; }
    int mid = (lo + hi) / 2;
    if (idx <= mid) seg_update(node * 2,     lo, mid, idx, val);
    else            seg_update(node * 2 + 1, mid + 1, hi, idx, val);
    seg[node] = seg[node * 2] + seg[node * 2 + 1];
}

int seg_query(int node, int lo, int hi, int ql, int qr) {
    if (qr < lo || hi < ql) return 0;                   /* no overlap */
    if (ql <= lo && hi <= qr) return seg[node];         /* full overlap */
    int mid = (lo + hi) / 2;
    return seg_query(node * 2,     lo, mid, ql, qr)
         + seg_query(node * 2 + 1, mid + 1, hi, ql, qr);
}
```

**English**

Query cases: **no overlap** → return identity (0 for sum); **full overlap** → return the stored value; otherwise **split** and recurse into both children.

**中文**

查询分三种情况：**无重叠** → 返回单位元（求和时为 0）；**完全重叠** → 返回存储值；否则**分裂**并递归左右孩子。

---

## 4. Demo | 示例

```c
int main(void)
{
    int a[] = {0, 1, 3, 5, 7, 9};        /* 1-based: a[1..5] */

    for (int i = 1; i <= 5; i++) bit_update(i, a[i], 5);
    printf("BIT sum[2..4] = %d\n", range_sum(2, 4));
    bit_update(3, 10, 5);                /* a[3] += 10 */
    printf("BIT sum[2..4] = %d\n", range_sum(2, 4));

    int b[] = {1, 3, 5, 7, 9};           /* 0-based */
    seg_build(b, 1, 0, 4);
    printf("Seg sum[1..3] = %d\n", seg_query(1, 0, 4, 1, 3));
    seg_update(1, 0, 4, 2, 10);          /* b[2] = 10 */
    printf("Seg sum[1..3] = %d\n", seg_query(1, 0, 4, 1, 3));
    return 0;
}
```

**Expected output | 期望输出**:
```
BIT sum[2..4] = 15
BIT sum[2..4] = 25
Seg sum[1..3] = 15
Seg sum[1..3] = 20
```

---

## 5. Comparison & Applications | 对比与应用

**English**

| | Fenwick tree | Segment tree |
|---|---|---|
| Build | O(n) | O(n) |
| Query/update | O(log n) | O(log n) |
| Memory | n + 1 | 4n |
| Supports | prefix/invertible queries | any associative query, range updates |

Applications: range-sum/min/max queries, order statistics, LIS, range updates with lazy propagation, 2D versions.

**中文**

| | 树状数组 | 线段树 |
|---|---|---|
| 构建 | O(n) | O(n) |
| 查询/更新 | O(log n) | O(log n) |
| 内存 | n + 1 | 4n |
| 支持 | 前缀/可逆查询 | 任意结合查询、区间更新 |

应用：区间和/最小/最大查询、顺序统计、最长上升子序列（LIS）、带懒惰传播的区间更新、二维版本。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `fenwick.c` | Fenwick tree (BIT) range sum | 树状数组区间和 |
| `segment_tree.c` | Segment tree range sum | 线段树区间和 |
| `day-37-summary.md` | Day 37 notes | 第三十七天学习笔记 |
