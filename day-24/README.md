# Day 24: Binary Search Trees | 二叉搜索树

> A bilingual (English / 中文) walkthrough of Day 24.
> 本节为第二十四天的双语概念讲解。

---

## 1. Overview | 概述

**English**

A **Binary Search Tree (BST)** is a binary tree with the **ordering property**: for every node `N`,

- all keys in `N.left`  are **less than** `N.key`;
- all keys in `N.right` are **greater than** `N.key`; and
- both subtrees are themselves BSTs.

This property makes **search, insert, and delete** run in **O(h)** time, where `h` is the tree height (worst case `h = n`, average `h = O(log n)`).

**中文**

**二叉搜索树（BST）** 是满足以下**有序性**的二叉树：对每个节点 `N`，

- `N.left` 中的所有键都**小于** `N.key`；
- `N.right` 中的所有键都**大于** `N.key`；
- 左右子树本身也都是 BST。

该性质使得**查找、插入、删除**的时间复杂度为 **O(h)**，其中 `h` 为树高（最坏 `h = n`，平均 `h = O(log n)`）。

---

## 2. Insert | 插入

```c
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int key;
    struct Node *left, *right;
};

struct Node *newNode(int key)
{
    struct Node *n = malloc(sizeof(*n));
    n->key = key;
    n->left = n->right = NULL;
    return n;
}

struct Node *insert(struct Node *root, int key)
{
    if (!root) return newNode(key);
    if (key < root->key)      root->left  = insert(root->left,  key);
    else if (key > root->key) root->right = insert(root->right, key);
    /* duplicates: do nothing (no equal keys allowed in this BST) */
    return root;
}
```

**English**

Walk down the tree comparing `key` with `root->key`; go left if smaller, right if greater. When you hit an empty slot, put the new node there.

**中文**

沿树向下比较 `key` 与 `root->key`：更小向左、更大向右。遇到空位时把新节点放入。

---

## 3. Search | 查找

```c
struct Node *search(struct Node *root, int key)
{
    if (!root)            return NULL;
    if (key == root->key) return root;
    if (key <  root->key) return search(root->left,  key);
    return search(root->right, key);
}
```

**English**

Return a pointer to the matching node, or `NULL` if not found. Average **O(log n)**, worst **O(n)** for a degenerate (linked-list-like) tree.

**中文**

返回匹配节点的指针；找不到则返回 `NULL`。平均 **O(log n)**，退化（退化为链表的）情况下最坏 **O(n)**。

---

## 4. Delete | 删除

**English**

Three cases:

1. **Leaf** — just remove it.
2. **One child** — replace the node with its child.
3. **Two children** — find the **in-order successor** (smallest key in the right subtree), copy its value into this node, then delete the successor (which falls into case 1 or 2).

**中文**

三种情形：

1. **叶子** —— 直接删除。
2. **只有一个孩子** —— 用该孩子替换被删节点。
3. **有两个孩子** —— 找到**中序后继**（右子树中最小的键），把它的值拷到当前节点，再删除该后继（落在情形 1 或 2）。

```c
struct Node *minNode(struct Node *r)
{
    while (r->left) r = r->left;
    return r;
}

struct Node *delete(struct Node *root, int key)
{
    if (!root) return NULL;
    if (key < root->key)      root->left  = delete(root->left,  key);
    else if (key > root->key) root->right = delete(root->right, key);
    else {
        /* found the node */
        if (!root->left)  { struct Node *c = root->right; free(root); return c; }
        if (!root->right) { struct Node *c = root->left;  free(root); return c; }
        struct Node *succ = minNode(root->right);
        root->key = succ->key;
        root->right = delete(root->right, succ->key);
    }
    return root;
}
```

---

## 5. In-order Traversal Yields Sorted Order | 中序遍历得到有序序列

**English**

A hallmark of a BST: **in-order traversal** visits keys in **ascending order** — a quick way to verify the BST property.

**中文**

BST 的标志：**中序遍历**按键的**升序**访问 —— 这是验证 BST 性质的快捷方法。

```c
void inorder(struct Node *r)
{
    if (!r) return;
    inorder(r->left);
    printf("%d ", r->key);
    inorder(r->right);
}
```

---

## 6. Demo | 示例

```c
int main(void)
{
    struct Node *root = NULL;
    int keys[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) root = insert(root, keys[i]);

    printf("In-order : "); inorder(root); printf("\n");

    struct Node *f = search(root, 40);
    printf("Search 40: %s\n", f ? "found" : "not found");

    root = delete(root, 30);
    printf("After del 30: "); inorder(root); printf("\n");
    return 0;
}
```

**Expected output | 期望输出**:
```
In-order : 20 30 40 50 60 70 80 
Search 40: found
After del 30: 20 40 50 60 70 80 
```

---

## 7. Complexity Summary | 复杂度小结

**English**

| Operation | Average | Worst (degenerate) |
|-----------|---------|--------------------|
| Search | O(log n) | O(n) |
| Insert | O(log n) | O(n) |
| Delete | O(log n) | O(n) |

The worst case arises when insertions are already sorted, producing a skewed tree. **Self-balancing trees** (AVL, red-black) keep `h = O(log n)` always — see Day 29.

**中文**

| 操作 | 平均 | 最坏（退化） |
|------|------|--------------|
| 查找 | O(log n) | O(n) |
| 插入 | O(log n) | O(n) |
| 删除 | O(log n) | O(n) |

最坏情况出现在插入序列本身有序、树退化为链表时。**自平衡树**（AVL、红黑）可始终维持 `h = O(log n)` —— 见第二十九天。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `bst.c` | Full BST: insert, search, delete, in-order | 完整 BST：插入、查找、删除、中序遍历 |
| `day-24-summary.md` | Day 24 notes | 第二十四天学习笔记 |