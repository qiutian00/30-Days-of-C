# Day 14: Linked Lists and Other Basic Data Structures — Part 2 | 链表与其他基础数据结构（二）

> A bilingual (English / 中文) walkthrough of Day 14.
> 本节为第十四天的双语概念讲解。

---

## 1. Stack (LIFO) | 栈（后进先出）

**English**

A **stack** is a Last-In, First-Out (LIFO) structure: the most recently added element is removed first.

Operations:
- `push()` — add an element to the top.
- `pop()` — remove the element at the top.
- `peek()` — inspect the top element without removing it.

Uses:
- Expression evaluation (e.g., parsing arithmetic).
- Undo operations.
- Depth-First Search (DFS).

**中文**

**栈**是一种后进先出（LIFO）结构：最后加入的元素最先被移除。

操作：
- `push()` —— 将元素压入栈顶。
- `pop()` —— 移除并返回栈顶元素。
- `peek()` —— 查看但不移除栈顶元素。

用途：
- 表达式求值（如解析算术表达式）。
- 撤销操作。
- 深度优先搜索（DFS）。

---

## 2. Queue (FIFO) | 队列（先进先出）

**English**

A **queue** is a First-In, First-Out (FIFO) structure: elements are removed in the same order they were added.

Operations:
- `enqueue()` — add an element to the rear.
- `dequeue()` — remove an element from the front.

Uses:
- Task scheduling.
- Breadth-First Search (BFS).
- Print queues.

**中文**

**队列**是一种先进先出（FIFO）结构：元素的出队顺序与入队顺序相同。

操作：
- `enqueue()` —— 在队尾加入元素。
- `dequeue()` —— 从队首移除元素。

用途：
- 任务调度。
- 广度优先搜索（BFS）。
- 打印队列。

---

## 3. Key Differences | 主要区别

**English**

| Structure | Insertion | Deletion | Use Case |
|-----------|-----------|----------|----------|
| Stack     | Top       | Top      | Backtracking |
| Queue     | Rear      | Front    | Scheduling  |

**中文**

| 结构 | 插入位置 | 删除位置 | 典型用途 |
|------|---------|---------|---------|
| 栈   | 栈顶    | 栈顶    | 回溯 |
| 队列 | 队尾    | 队首    | 调度 |

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `more_data_structures.c` | Stack and queue examples | 栈与队列实现示例 |
| `day-14-summary.md` | Day 14 notes | 第十四天学习笔记 |