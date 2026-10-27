# Day 16: Arrays ADT — Part 1 | 数组 ADT（一）

> A bilingual (English / 中文) walkthrough of Day 16.
> 本节为第十六天的双语概念讲解。

---

## 1. Overview | 概述

**English**

An **Abstract Data Type (ADT)** defines a data structure by its **behavior** (the operations it supports) rather than by its concrete implementation. This day begins treating an **array** as an ADT — specifying what operations should be available on a list, independent of how the storage is organized in memory.

**中文**

**抽象数据类型（ADT）** 从**行为**（支持的操作）而非具体实现角度来定义数据结构。本节开始将**数组**视为 ADT —— 规定一个线性表应支持哪些操作，而与存储在内存中的具体组织方式无关。

---

## 2. The List ADT — Operations | 线性表 ADT 的操作

**English**

A list ADT typically provides the following operations on a collection of elements:

- `create()` — initialize an empty list.
- `insert(index, value)` — insert a value at position `index`.
- `append(value)` — insert a value at the end.
- `delete(index)` — remove the element at position `index`.
- `get(index)` — return the element at `index`.
- `set(index, value)` — replace the element at `index` with `value`.
- `find(value)` — search for `value` and return its index (or -1).
- `length()` — return the number of elements.
- `isEmpty()` — check whether the list is empty.

**中文**

线性表 ADT 通常对一组元素提供以下操作：

- `create()` —— 初始化一个空表。
- `insert(index, value)` —— 在位置 `index` 处插入 `value`。
- `append(value)` —— 在表尾追加 `value`。
- `delete(index)` —— 删除位置 `index` 处的元素。
- `get(index)` —— 返回位置 `index` 处的元素。
- `set(index, value)` —— 用 `value` 替换 `index` 处的元素。
- `find(value)` —— 查找 `value`，返回其下标（找不到返回 -1）。
- `length()` —— 返回元素个数。
- `isEmpty()` —— 判断表是否为空。

---

## 3. Array-Based Implementation | 基于数组的实现

**English**

When a list ADT is implemented on top of a **statically-sized array**, the storage is contiguous and indexed. Key considerations:

- A **capacity** field records the maximum number of elements the array can hold.
- A **length** field records how many elements are currently in use.
- **Insert and delete** must shift elements to maintain contiguity, giving them **O(n)** worst-case behavior.
- `get`/`set`/`length` are **O(1)** thanks to direct indexing.

**中文**

当一个线性表 ADT 基于**定长数组**实现时，存储是连续且可索引的。要点：

- **capacity** 字段记录数组可容纳的最大元素数。
- **length** 字段记录当前已使用的元素个数。
- **插入与删除**需要移动元素以保持连续性，最坏情况为 **O(n)**。
- `get`/`set`/`length` 由于直接索引而是 **O(1)**。

---

## 4. Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `content.md` | Day 16 notes (to be filled in) | 第十六天学习笔记（待补充） |

## 其他

线性表
├── 顺序表
│   └── 数组实现
│
└── 链表
    ├── 单链表
    ├── 双链表
    └── 循环链表