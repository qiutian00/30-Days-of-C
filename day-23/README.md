# Day 23: Intro to Trees — Part 2 | 树的入门（二）

> A bilingual (English / 中文) walkthrough of Day 23.
> 本节为第二十三天的双语概念讲解。

---

## 1. Overview | 概述

**English**

Building on Day 22, today we compute useful **metrics** of a binary tree and add a fourth traversal:

- **Height** of the tree.
- **Node count** and **leaf count**.
- **Level-order (BFS) traversal** using a queue.

**中文**

在第二十二天基础上，今天我们计算二叉树的一些常用**度量值**，并补充第四种遍历：

- 树的**高度**。
- 节点**总数**与**叶子数**。
- 借助队列实现的**层序遍历**（BFS）。

---

## 2. Height | 高度

**English**

Height of a node = `1 + max(height(left), height(right))`, with `height(NULL) = 0`. (Some texts define the height of a single-node tree as 0 — adjust the base case accordingly.)

```c
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode *left, *right;
};

struct TreeNode *newNode(int data)
{
    struct TreeNode *n = malloc(sizeof(*n));
    n->data = data;
    n->left = n->right = NULL;
    return n;
}

int height(struct TreeNode *r)
{
    if (!r) return 0;
    int hl = height(r->left);
    int hr = height(r->right);
    return 1 + (hl > hr ? hl : hr);
}
```

**中文**

节点高度 = `1 + max(左子树高度, 右子树高度)`，空树高度为 0。（个别教材把单节点树高度定义为 0，相应调整基本情况即可。）

---

## 3. Counting Nodes and Leaves | 统计节点数与叶子数

**English**

- **countNodes**: 1 + (left count) + (right count); an empty subtree contributes 0.
- **countLeaves**: a node with **both** children NULL is a leaf.

```c
int countNodes(struct TreeNode *r)
{
    if (!r) return 0;
    return 1 + countNodes(r->left) + countNodes(r->right);
}

int countLeaves(struct TreeNode *r)
{
    if (!r) return 0;
    if (!r->left && !r->right) return 1;
    return countLeaves(r->left) + countLeaves(r->right);
}
```

**中文**

- **countNodes**：1 + 左子树节点数 + 右子树节点数；空子树贡献 0。
- **countLeaves**：左右孩子均为 NULL 的节点即叶子。

---

## 4. Level-Order Traversal (BFS) | 层序遍历（BFS）

**English**

Visit nodes **level by level**, left to right. We use a simple **queue of pointers** backed by an array. For each node we dequeue it, print it, and enqueue its non-NULL children.

**中文**

逐层、从左到右访问节点。我们使用一个由数组支持的简单的**指针队列**：每出队一个节点就打印它，并将其非空的孩子入队。

为什么用队列？
队列的特点是先进先出（FIFO）。层序遍历要求：先访问的节点，它的孩子也要先被访问。这正好和队列的特性吻合。

对比一下：

DFS（前/中/后序） 用栈（或递归），一条路走到黑；

BFS（层序） 用队列，一层一层往外扩。

```c
#define MAXQ 128

void levelorder(struct TreeNode *root)
{
    if (!root) return;              // 空树直接返回
    struct TreeNode *q[MAXQ];       // 用数组模拟队列
    int head = 0, tail = 0;         // head: 出队位置; tail: 入队位置
    q[tail++] = root;               // 根节点入队

    while (head != tail) {          // 队列非空时循环
        struct TreeNode *cur = q[head++];   // 出队一个节点
        printf("%d ", cur->data);           // 访问它

        if (cur->left)  q[tail++] = cur->left;   // 左孩子入队
        if (cur->right) q[tail++] = cur->right;  // 右孩子入队
    }
}
```

---

## 5. Complete Demo | 完整示例

```c
/*
        1
      /   \
     2     3
    / \     \
   4   5     6
*/
int main(void)
{
    struct TreeNode *root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->right = newNode(6);

    printf("Height     : %d\n", height(root));
    printf("Nodes      : %d\n", countNodes(root));
    printf("Leaves     : %d\n", countLeaves(root));
    printf("Level-order: ");
    levelorder(root);
    printf("\n");
    return 0;
}
```

**Expected output | 期望输出**:

```
Height     : 3
Nodes      : 6
Leaves     : 3
Level-order: 1 2 3 4 5 6
```

---

## 6. Key Takeaways | 要点

**English**
- Most tree metrics follow a single recursive template: combine `1` with the metric on left and right subtrees.
- Level-order needs a queue and gives a true BFS view, useful for finding the tree's width or running BFS-based algorithms.
- All of these traversals are O(n).

**中文**
- 大多数树的度量值遵循同一个递归模板：把 `1` 与左右子树上的度量值合并即可。
- 层序遍历需要队列，提供真正的 BFS 视角，常用于求树的宽度或运行基于 BFS 的算法。
- 这些遍历的时间复杂度均为 O(n)。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `tree_metrics.c` | Height, node count, leaf count | 高度、节点数、叶子数统计 |
| `level_order.c` | Level-order (BFS) traversal with a queue | 借助队列的层序（BFS）遍历 |
| `day-23-summary.md` | Day 23 notes | 第二十三天学习笔记 |