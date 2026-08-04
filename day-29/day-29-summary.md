# Day 29: AVL Trees | AVL 树

## Motivation | 动机
- BST can degenerate to O(n) when keys are inserted sorted.
- AVL is a **self-balancing BST**: keeps `|BF| <= 1` for every node via rotations → `h = O(log n)`.

## Balance factor | 平衡因子
- `BF(n) = h(left) - h(right)`; valid range `{-1, 0, +1}`.
- Store `height` on each node; `h(NULL) = 0`, `h(leaf) = 1`.

## Four cases | 四种情形
| Case | BF at z | BF at child | Fix |
|------|---------|-------------|-----|
| LL | +2 | >= 0 | rightRotate(z) |
| RR | -2 | <= 0 | leftRotate(z) |
| LR | +2 | < 0  | leftRotate(z.left); rightRotate(z) |
| RL | -2 | > 0  | rightRotate(z.right); leftRotate(z) |

## Insert algorithm | 插入算法
1. Standard BST insert.
2. Update height on the way back up.
3. Read BF; apply matching rotation; return new subtree root.

## Complexity | 复杂度
- Search / Insert / Delete all **O(log n)** time, **O(log n)** stack.
- Tree height bounded by `~1.44 log2(n)`.