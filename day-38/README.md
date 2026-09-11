# Day 38: Red-Black Tree | 红黑树

> A bilingual (English / 中文) walkthrough of Day 38.
> 本节为第三十八天的补充讲解：红黑树。

---

## 1. Overview | 概述

**English**

A **red-black tree** is a self-balancing binary search tree (BST). It keeps a weaker balance condition than AVL (fewer rotations), which makes insertion and deletion faster in practice, while still guaranteeing **O(log n)** for search, insert, and delete.

**中文**

**红黑树**是一种自平衡二叉搜索树（BST）。它的平衡条件比 AVL 更弱（旋转更少），因此实践中插入和删除更快，同时仍保证查找、插入、删除都是 **O(log n)**。

---

## 2. The Five Properties | 五条性质

**English**

1. Every node is red or black.
2. The root is black.
3. Every leaf (NIL) is black.
4. If a node is red, both its children are black (no two reds in a row).
5. Every path from a node to its descendant leaves has the same number of black nodes (**black-height**).

**中文**

1. 每个节点是红色或黑色。
2. 根是黑色。
3. 每个叶子（NIL）是黑色。
4. 红节点的两个子节点都是黑色（不能有连续红节点）。
5. 从任一节点到其叶子的每条路径都包含相同数目的黑节点（**黑高**）。

Properties 4 and 5 together imply the tree is roughly balanced — the longest path is at most twice the shortest.

性质 4 和 5 共同保证树大致平衡 —— 最长路径至多是最短路径的两倍。

---

## 3. Node and Rotations | 节点与旋转

```c
#include <stdio.h>
#include <stdlib.h>

#define RED   0
#define BLACK 1

struct Node {
    int key;
    int color;
    struct Node *left, *right, *parent;
};

struct Node *rb_new(int key) {
    struct Node *n = malloc(sizeof(*n));
    n->key = key; n->color = RED;            /* new nodes start red */
    n->left = n->right = n->parent = NULL;
    return n;
}

/* Left rotation: bring the right child up. */
void left_rotate(struct Node **root, struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->parent = x->parent;

    if (!x->parent)      *root = y;
    else if (x == x->parent->left) x->parent->left = y;
    else                 x->parent->right = y;

    y->left = x;
    x->parent = y;
}

/* Right rotation: bring the left child up. */
void right_rotate(struct Node **root, struct Node *x) {
    struct Node *y = x->left;
    x->left = y->right;
    if (y->right) y->right->parent = x;
    y->parent = x->parent;

    if (!x->parent)      *root = y;
    else if (x == x->parent->right) x->parent->right = y;
    else                 x->parent->left = y;

    y->right = x;
    x->parent = y;
}
```

---

## 4. Insertion | 插入

**English**

Insert as in a normal BST, color the new node **red**, then fix the red-black violations (a red node with a red parent). The fix uses rotations and recoloring based on the color of the uncle node.

**中文**

像普通 BST 一样插入，把新节点染成**红色**，然后修复红黑性质冲突（红节点的父节点也是红色）。修复根据叔叔节点的颜色进行旋转和重新着色。

```c
void rb_fixup(struct Node **root, struct Node *z) {
    while (z->parent && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            struct Node *uncle = z->parent->parent->right;
            if (uncle && uncle->color == RED) {            /* case 1: recolor */
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {               /* case 2: rotate */
                    z = z->parent;
                    left_rotate(root, z);
                }
                z->parent->color = BLACK;                  /* case 3 */
                z->parent->parent->color = RED;
                right_rotate(root, z->parent->parent);
            }
        } else {                                           /* mirror image */
            struct Node *uncle = z->parent->parent->left;
            if (uncle && uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void rb_insert(struct Node **root, int key) {
    struct Node *z = rb_new(key);
    struct Node *y = NULL, *x = *root;

    while (x) { y = x; x = (z->key < x->key) ? x->left : x->right; }
    z->parent = y;
    if (!y) *root = z;
    else if (z->key < y->key) y->left = z;
    else                      y->right = z;

    rb_fixup(root, z);
}
```

---

## 5. Search & Traversal | 查找与遍历

```c
struct Node *rb_search(struct Node *root, int key) {
    while (root && root->key != key)
        root = (key < root->key) ? root->left : root->right;
    return root;
}

void rb_inorder(struct Node *root) {
    if (!root) return;
    rb_inorder(root->left);
    printf("%d(%c) ", root->key, root->color == RED ? 'R' : 'B');
    rb_inorder(root->right);
}

int rb_height(struct Node *root) {
    if (!root) return 0;
    int l = rb_height(root->left), r = rb_height(root->right);
    return (l > r ? l : r) + 1;
}
```

---

## 6. Demo | 示例

```c
int main(void)
{
    struct Node *root = NULL;
    int keys[] = {10, 20, 30, 15, 25, 5, 1};

    for (int i = 0; i < 7; i++) rb_insert(&root, keys[i]);

    printf("in-order: ");
    rb_inorder(root);
    printf("\nheight = %d\n", rb_height(root));

    printf("search 15 -> %s\n", rb_search(root, 15) ? "found" : "not found");
    printf("search 99 -> %s\n", rb_search(root, 99) ? "found" : "not found");
    return 0;
}
```

**Expected output | 期望输出**:
```
in-order: 1(B) 5(R) 10(B) 15(R) 20(B) 25(R) 30(B)
height = 3
search 15 -> found
search 99 -> not found
```

---

## 7. AVL vs Red-Black | AVL 与红黑树对比

**English**

| | AVL tree | Red-black tree |
|---|---|---|
| Balance | Strict (height diff <= 1) | Relaxed |
| Height | ~1.44 log n | ~2 log n |
| Lookup | Faster (more balanced) | Slightly slower |
| Insert/delete | More rotations | Fewer rotations |

AVL is preferred for read-heavy workloads; red-black for write-heavy ones. Red-black is used in Linux's kernel, C++ `std::map`, and Java's `TreeMap`.

**中文**

| | AVL 树 | 红黑树 |
|---|---|---|
| 平衡 | 严格（高度差 <= 1） | 宽松 |
| 高度 | ~1.44 log n | ~2 log n |
| 查找 | 更快（更平衡） | 稍慢 |
| 插入/删除 | 旋转更多 | 旋转更少 |

读多写少用 AVL；写多读少用红黑树。红黑树被用于 Linux 内核、C++ `std::map`、Java `TreeMap`。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `red_black_tree.c` | Red-black tree insert/search/in-order | 红黑树插入/查找/中序 |
| `day-38-summary.md` | Day 38 notes | 第三十八天学习笔记 |
