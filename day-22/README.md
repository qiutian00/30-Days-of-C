# Day 22: Intro to Trees — Part 1 | 树的入门（一）

> A bilingual (English / 中文) walkthrough of Day 22.
> 本节为第二十二天的双语概念讲解。

---

## 1. Overview | 概述

**English**

A **tree** is a hierarchical, non-linear data structure made of **nodes** connected by edges. It has a single **root**; every other node has exactly one parent and zero or more children. A **binary tree** is a tree in which each node has at most two children, called the **left** and **right** child.

**中文**

**树**是一种层次化、非线性的数据结构，由**节点**和连接它们的边组成。它只有一个**根**；其余每个节点都有且仅有一个父节点和零个或多个子节点。**二叉树**是每个节点最多有两个子节点（分别称为**左**孩子和**右**孩子）的树。

---

## 2. Tree Terminology | 树的术语

**English**

| Term | Meaning |
|------|---------|
| Root | The topmost node with no parent |
| Leaf | A node with no children |
| Internal node | A node with at least one child |
| Height of a node | Length of the longest path from it down to a leaf |
| Depth of a node | Length of the path from the root to it |
| Height of tree | Height of the root |
| Level | All nodes at the same depth |

**中文**

| 术语 | 含义 |
|------|------|
| 根 (root) | 顶部没有父节点的节点 |
| 叶子 (leaf) | 没有子节点的节点 |
| 内部节点 | 至少有一个子节点的节点 |
| 节点的高度 | 从该节点向下到叶子的最长路径长度 |
| 节点的深度 | 从根到该节点的路径长度 |
| 树的高度 | 根节点的高度 |
| 层 | 同一深度的所有节点 |

---

## 3. Node Structure | 节点结构

```c
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};
```

**English**

- `data` holds the node's value.
- `left` / `right` are pointers to the two children; a missing child is `NULL`.

**中文**

- `data` 存放节点值。
- `left` / `right` 是指向两个孩子节点的指针；缺失的孩子用 `NULL` 表示。

---

## 4. Tree Traversals | 树的遍历

**English**

"Visit" = process the node's `data` (e.g., print it). The three **depth-first** traversals differ by **when** the root is visited:

| Traversal | Order | Mnemonic |
|-----------|-------|----------|
| **Pre-order** | Root → Left → Right | "root first" |
| **In-order** | Left → Root → Right | "root in the middle" |
| **Post-order** | Left → Right → Root | "root last" |

**中文**

"访问" = 处理节点的 `data`（例如打印）。三种**深度优先**遍历的区别在于**何时**访问根：

| 遍历 | 顺序 | 助记 |
|------|------|------|
| **前序** | 根 → 左 → 右 | "根在前" |
| **中序** | 左 → 根 → 右 | "根在中" |
| **后序** | 左 → 右 → 根 | "根在后" |

---

## 5. Recursive Traversal Code | 递归遍历代码

```c
#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *newNode(int data)
{
    struct TreeNode *n = malloc(sizeof(*n));
    n->data  = data;
    n->left = n->right = NULL;
    return n;
}

void preorder(struct TreeNode *r)  { if (!r) return; printf("%d ", r->data); preorder(r->left);  preorder(r->right); }
void inorder(struct TreeNode *r)   { if (!r) return; inorder(r->left);   printf("%d ", r->data); inorder(r->right);  }
void postorder(struct TreeNode *r) { if (!r) return; postorder(r->left); postorder(r->right); printf("%d ", r->data); }

/* Builds this binary tree:
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

    printf("Pre-order : "); preorder(root);  printf("\n");
    printf("In-order  : "); inorder(root);   printf("\n");
    printf("Post-order: "); postorder(root); printf("\n");
    return 0;
}
```

**English**
- Each traversal follows the **left subtree before the right**; only the position of the `printf` changes.
- For the tree in `main`:
  - Pre-order:  `1 2 4 5 3 6`
  - In-order:   `4 2 5 1 3 6`
  - Post-order: `4 5 2 6 3 1`

**中文**
- 每种遍历都**先访问左子树、再访问右子树**；区别仅在于 `printf` 的位置。
- 对 `main` 中构造的树：
  - 前序：`1 2 4 5 3 6`
  - 中序：`4 2 5 1 3 6`
  - 后序：`4 5 2 6 3 1`

---

## 6. Key Takeaways | 要点

**English**
- Trees naturally model hierarchical data; binary trees are the foundation for BSTs (Day 24), AVL trees (Day 29), and heaps.
- The three DFS traversals differ only in **when the root is visited**.
- All traversals here are **O(n)** time and **O(h)** stack space, where `h` is the tree height.

**中文**
- 树天然适合表达层次结构；二叉树是二叉搜索树（第二十四天）、AVL 树（第二十九天）和堆的基础。
- 三种深度优先遍历的区别只是**根被访问的时机**。
- 这些遍历均为 **O(n)** 时间、**O(h)** 栈空间，其中 `h` 为树高。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `tree_traversals.c` | Builds a binary tree and runs pre/in/post-order | 构造二叉树并执行前序/中序/后序遍历 |
| `day-22-summary.md` | Day 22 notes | 第二十二天学习笔记 |