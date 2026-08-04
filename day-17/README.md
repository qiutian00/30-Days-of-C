# Day 17: Arrays ADT — Part 2 | 数组 ADT（二）

> A bilingual (English / 中文) walkthrough of Day 17.
> 本节为第十七天的双语概念讲解。

---

## 1. Overview | 概述

**English**

Building on Day 16, this day extends the array-based list ADT with more advanced operations and discusses the practical trade-offs: when to use an array-based list versus a linked-list-based list.

**中文**

在第十六天的基础上，本节朝基于数组的线性表 ADT 补充更多进阶操作，并讨论其实际权衡：何时使用基于数组实现的线性表，何时使用基于链表的线性表。

---

## 2. Additional Operations | 补充操作

**English**

A more complete array-based list ADT commonly adds:

- `resize(new_capacity)` — grow or shrink the underlying storage (e.g., doubling capacity when full).
- `clear()` — remove all elements and reset length to zero.
- `reverse()` — reverse the order of elements in place.
- `slice(start, end)` — return a sub-list view from `start` to `end`.
- `merge(other)` — merge a sorted list with another sorted list.
- `sort()` — sort the elements in place.

**中文**

一个更完整的数组线性表 ADT 通常还提供：

- `resize(new_capacity)` —— 扩展或缩减底层存储（例如满时容量翻倍）。
- `clear()` —— 清空所有元素并将长度置 0。
- `reverse()` —— 原地反转元素顺序。
- `slice(start, end)` —— 返回 `start` 到 `end` 之间的子表视图。
- `merge(other)` —— 将两个有序表合并。
- `sort()` —— 原地对元素排序。

---

## 3. Array List vs Linked List | 数组实现与链表实现的对比

**English**

| Aspect | Array-based list | Linked list |
|--------|------------------|-------------|
| Random access (`get(i)`) | **O(1)** | **O(n)** |
| Insert/delete at end | **O(1)** amortized | **O(1)** (with tail pointer) / **O(n)** |
| Insert/delete at front | **O(n)** | **O(1)** |
| Memory overhead | Low (only data) | Extra pointer per node |
| Cache locality | Good (contiguous) | Poor |
| Resizing | Need `resize`/reallocation | Grows/shrinks dynamically |

Choose an array-based list when random access dominates and the size is predictable; choose a linked list when frequent insertions/deletions occur away from the ends.

**中文**

| 方面 | 基于数组的线性表 | 链表 |
|------|------------------|------|
| 随机访问（`get(i)`） | **O(1)** | **O(n)** |
| 表尾插入/删除 | 摊还 **O(1)** | **O(1)**（带尾指针）/ **O(n)** |
| 表头插入/删除 | **O(n)** | **O(1)** |
| 内存开销 | 小（仅数据） | 每个节点额外存指针 |
| 缓存局部性 | 好（连续存储） | 差 |
| 扩容 | 需要 `resize`/重新分配 | 可动态增减 |

当随机访问占主导且规模可预测时，优先选择数组实现；当频繁在非表尾位置插入/删除时，优先选择链表实现。

---

## 4. Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `content.md` | Day 17 notes (to be filled in) | 第十七天学习笔记（待补充） |