# Day 13: Linked Lists and Other Basic Data Structures — Part 1 | 链表与其他基础数据结构（一）

> A bilingual (English / 中文) walkthrough of Day 13.
> 本节为第十三天的双语概念讲解。

---

## 1. Singly Linked List | 单链表

### What is a Linked List? | 什么是链表？

**English**

A linked list is a **linear** data structure where each element (a **node**) points to the next node. Unlike arrays, the memory for a linked list is **not contiguous** — nodes are allocated dynamically and connected via pointers.

**中文**

链表是一种**线性**数据结构，其中每个元素（**节点**）指向下一个节点。与数组不同，链表的内存**并不连续** —— 节点是动态分配的，并通过指针相连。

---

### Node Structure | 节点结构

**English**

```c
struct Node {
    int data;
    struct Node* next;
};
```

Each node holds a `data` field and a `next` pointer to the following node. The last node's `next` is `NULL`.

**中文**

```c
struct Node {
    int data;
    struct Node* next;
};
```

每个节点包含一个 `data` 字段和一个指向下一个节点的 `next` 指针。最后一个节点的 `next` 为 `NULL`。

---

### Basic Operations | 基本操作

**English**

- Create a node.
- Insert at the **beginning** of the list.
- Insert at the **end** of the list.
- Delete a node by **value**.
- Print the list.

**中文**

- 创建节点。
- 在链表**头部**插入。
- 在链表**尾部**插入。
- 按**值**删除节点。
- 打印链表。

---

### Advantages | 优点

**English**

- **Dynamic memory allocation** — the list grows and shrinks at runtime.
- **Easy insert/delete** — no need to shift elements as in arrays.

**中文**

- **动态内存分配** —— 链表可在运行时动态伸缩。
- **插入/删除方便** —— 无需像数组那样移动元素。

---

### Disadvantages | 缺点

**English**

- **No direct access** — accessing the i-th node requires traversal, so search is **O(n)**.
- **Extra memory** — each node must additionally store a pointer.

**中文**

- **不能随机访问** —— 访问第 i 个节点需从头遍历，查找复杂度为 **O(n)**。
- **额外内存开销** —— 每个节点都需要额外存放一个指针。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `linked_list.c` | Linked list implementation | 链表实现示例 |
| `day-13-summary.md` | Day 13 notes | 第十三天学习笔记 |