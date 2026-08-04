# Day 29: AVL Trees | AVL 树

> A bilingual (English / 中文) walkthrough of Day 29.
> 本节为第二十九天的双语概念讲解。

---

## 1. Why AVL? | 为什么需要 AVL？

**English**

A plain BST (Day 24) can become **skewed** when keys are inserted in sorted order, degrading search/insert/delete to **O(n)**. An **AVL tree** is a **self-balancing BST** that keeps, for every node, the **balance factor** `BF = height(left) − height(right)` in the range `{-1, 0, +1}`. After each insert/delete, the tree performs **rotations** to restore this invariant, guaranteeing `h = O(log n)`.

**中文**

普通 BST（第二十四天）在按键有序插入时会**退化**为链表，查找/插入/删除退化为 **O(n)**。**AVL 树**是一种**自平衡 BST**，对每个节点都保持**平衡因子** `BF = 左子树高度 − 右子树高度` 在 `{-1, 0, +1}` 范围内。每次插入/删除后通过**旋转**恢复这一不变式，保证 `h = O(log n)`。

---

## 2. Node and Balance Factor | 节点与平衡因子

```c
#include <stdio.h>
#include <stdlib.h>

struct AVLNode {
    int key;
    int height;                 /* height of the subtree rooted here */
    struct AVLNode *left, *right;
};

static int h(struct AVLNode *n) { return n ? n->height : 0; }
static int max(int a, int b)    { return a > b ? a : b; }

static void updateH(struct AVLNode *n) { n->height = 1 + max(h(n->left), h(n->right)); }
static int  bf(struct AVLNode *n)      { return n ? h(n->left) - h(n->right) : 0; }
```

**English**

- `h(NULL) = 0`, `h(leaf) = 1`.
- `bf(n)` returns the balance factor of `n`.

**中文**

- `h(NULL) = 0`，`h(叶子) = 1`。
- `bf(n)` 返回 `n` 的平衡因子。

---

## 3. The Four Rotations | 四种旋转

**English**

There are four cases, each fixed by a specific (possibly double) rotation:

| Case | BF at `z` | BF at child | Fix |
|------|-----------|-------------|-----|
| **LL** | `+2` | `>= 0` | rightRotate(z) |
| **RR** | `-2` | `<= 0` | leftRotate(z) |
| **LR** | `+2` | `< 0`  | leftRotate(z.left); rightRotate(z) |
| **RL** | `-2` | `> 0`  | rightRotate(z.right); leftRotate(z) |

**中文**

四种情形分别用（可能是双）旋转修复：

| 情形 | `z` 的 BF | 子节点 BF | 修复 |
|------|-----------|-----------|------|
| **LL** | `+2` | `>= 0` | 对 z 右旋 |
| **RR** | `-2` | `<= 0` | 对 z 左旋 |
| **LR** | `+2` | `< 0`  | 先对 z.left 左旋；再对 z 右旋 |
| **RL** | `-2` | `> 0`  | 先对 z.right 右旋；再对 z 左旋 |

### 3.1 Single rotations | 单旋

```c
static struct AVLNode *rightRotate(struct AVLNode *z)
{
    struct AVLNode *y = z->left;
    struct AVLNode *T3 = y->right;

    y->right = z;
    z->left  = T3;

    updateH(z);
    updateH(y);
    return y;                       /* new subtree root */
}

static struct AVLNode *leftRotate(struct AVLNode *z)
{
    struct AVLNode *y = z->right;
    struct AVLNode *T2 = y->left;

    y->left  = z;
    z->right = T2;

    updateH(z);
    updateH(y);
    return y;
}
```

**English**

A right rotation around `z` lifts `y = z->left` up, making `z` the right child of `y`. The middle subtree `T3` moves to become `z->left`. Heights of `z` then `y` are recomputed bottom-up. Left rotation is the mirror image.

**中文**

围绕 `z` 的右旋把 `y = z->left` 上提，使 `z` 成为 `y` 的右孩子；中间子树 `T3` 转为 `z->left`。按自底向上顺序更新 `z` 和 `y` 的高度。左旋为镜像操作。

---

## 4. Insertion with Rebalancing | 带再平衡的插入

```c
static struct AVLNode *newNode(int key)
{
    struct AVLNode *n = malloc(sizeof(*n));
    n->key = key; n->height = 1;
    n->left = n->right = NULL;
    return n;
}

struct AVLNode *insert(struct AVLNode *n, int key)
{
    /* 1) standard BST insert */
    if (!n) return newNode(key);
    if      (key < n->key) n->left  = insert(n->left,  key);
    else if (key > n->key) n->right = insert(n->right, key);
    else return n;                  /* no duplicates */

    /* 2) update height and read balance factor */
    updateH(n);
    int b = bf(n);

    /* 3) four rebalancing cases */
    if (b > 1 && key < n->left->key)                       /* LL */
        return rightRotate(n);
    if (b < -1 && key > n->right->key)                     /* RR */
        return leftRotate(n);
    if (b > 1 && key > n->left->key) {                     /* LR */
        n->left = leftRotate(n->left);
        return rightRotate(n);
    }
    if (b < -1 && key < n->right->key) {                   /* RL */
        n->right = rightRotate(n->right);
        return leftRotate(n);
    }
    return n;
}
```

**English**
- Do a normal BST insert, then walk back up the recursion, updating heights and checking the balance factor.
- When a violation is found, apply the matching rotation. Because the recursion returns the new subtree root, the parent's pointer is updated automatically.

**中文**
- 先做普通 BST 插入，再在递归回溯过程中更新高度并检查平衡因子。
- 发现失衡时执行对应的旋转。由于递归返回新的子树根，父指针会自动更新。

---

## 5. Demo | 示例

```c
static void preorder(struct AVLNode *r)
{
    if (!r) return;
    printf("%d(h=%d) ", r->key, r->height);
    preorder(r->left);
    preorder(r->right);
}

int main(void)
{
    struct AVLNode *root = NULL;
    int keys[] = {10, 20, 30, 40, 50, 25};

    for (int i = 0; i < 6; i++) {
        root = insert(root, keys[i]);
        printf("After inserting %2d: ", keys[i]);
        preorder(root);
        printf("\n");
    }
    return 0;
}
```

**Expected output | 期望输出**:
```
After inserting 10: 10(h=1) 
After inserting 20: 10(h=2) 20(h=1) 
After inserting 30: 20(h=2) 10(h=1) 30(h=1) 
After inserting 40: 20(h=3) 10(h=1) 30(h=2) 40(h=1) 
After inserting 50: 20(h=3) 10(h=1) 40(h=2) 30(h=1) 50(h=1) 
After inserting 25: 30(h=3) 20(h=2) 10(h=1) 25(h=1) 40(h=2) 50(h=1) 
```

**English**
- Inserting `30` (after `10, 20`) triggers an **RR** case at `10` → a left rotation makes `20` the root.
- Inserting `50` triggers another RR; the tree rebalances again.
- Inserting `25` creates an **RL** case; after the double rotation the final root is `30` with both subtrees balanced.

**中文**
- 先后插入 `10、20` 后再插入 `30`，在 `10` 处触发 **RR** 情形 → 左旋后 `20` 成为根。
- 插入 `50` 又触发一次 RR，树再次再平衡。
- 插入 `25` 形成 **RL** 情形；双旋后最终根为 `30`，左右子树均平衡。

---

## 6. Complexity | 复杂度

**English**

| Operation | Time | Space (stack) |
|-----------|------|---------------|
| Search    | O(log n) | O(log n) |
| Insert    | O(log n) | O(log n) |
| Delete    | O(log n) | O(log n) |

AVL keeps height within `1.44 log₂(n + 2) − 0.328`, so all operations are logarithmic. Deletion is similar to BST deletion but with rebalancing on the way back up.

**中文**

| 操作 | 时间 | 栈空间 |
|------|------|--------|
| 查找 | O(log n) | O(log n) |
| 插入 | O(log n) | O(log n) |
| 删除 | O(log n) | O(log n) |

AVL 的高度被限制在 `1.44 log₂(n + 2) − 0.328` 之内，所有操作均为对数级。删除与 BST 类似，只是回溯时需要再平衡。

---

## 7. Key Takeaways | 要点

**English**
- AVL trees keep `|BF| ≤ 1` after every insert/delete via rotations, guaranteeing `h = O(log n)`.
- Four rotation cases cover all imbalances: **LL, RR, LR, RL**.
- Heights are stored on nodes and recomputed bottom-up after structural changes.

**中文**
- AVL 通过旋转在每次插入/删除后保持 `|BF| ≤ 1`，保证 `h = O(log n)`。
- 四种旋转情形覆盖所有失衡：**LL、RR、LR、RL**。
- 高度存储在节点上，结构变化后按自底向上更新。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `avl.c` | AVL tree with rotations and insertion | 带旋转与插入的 AVL 树 |
| `day-29-summary.md` | Day 29 notes | 第二十九天学习笔记 |