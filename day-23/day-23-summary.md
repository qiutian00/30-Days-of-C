# Day 23: Intro to Trees — Part 2 | 树的入门（二）

## Metrics (all recursive, O(n)) | 度量值（均为 O(n) 递归）
- `height(r) = 0` if `r == NULL`; else `1 + max(height(L), height(R))`.
- `countNodes(r) = 0` if NULL; else `1 + countNodes(L) + countNodes(R)`.
- `countLeaves`: both children NULL -> 1; else sum of leaves in L + R.

## Level-order (BFS) | 层序遍历
- Use a queue of node pointers.
- Enqueue root; while queue not empty: dequeue, print, enqueue non-NULL children.
- O(n) time, O(w) space where `w` is the maximum width.

## Demo | 示例
```
        1
      /   \
     2     3
    / \     \
   4   5     6

Height     : 3
Nodes      : 6
Leaves     : 3
Level-order: 1 2 3 4 5 6
```