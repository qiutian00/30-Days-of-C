# Day 32: Heap & Priority Queue | 堆与优先队列

## Idea | 思路
- A **complete binary tree** in an array satisfying the **heap property** (max-heap: parent >= children).

## Index math (0-based) | 下标计算
- left = `2*i + 1`, right = `2*i + 2`, parent = `(i - 1) / 2`.

## Operations | 操作
- `push`: append at end, bubble **up**. O(log n).
- `pop`: root -> last, shrink, sift **down**. O(log n).
- `peek`: root. O(1).
- `build_heap`: bottom-up from `n/2 - 1` down to 0. **O(n)**.

## Heap sort | 堆排序
- Repeatedly move root to the end and re-heapify. O(n log n), O(1) space, not stable.

## Applications | 应用
- Priority queues, Dijkstra/Prim, top-k, median maintenance, scheduling.
