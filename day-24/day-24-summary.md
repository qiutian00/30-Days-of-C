# Day 24: Binary Search Trees | 二叉搜索树

## BST Property | BST 性质
- Left subtree keys  <  node key.
- Right subtree keys >  node key.
- Both subtrees are themselves BSTs.

## Operations (recursive, all O(h)) | 操作（递归，均为 O(h)）
- `insert(root, key)`: walk left/right until reaching NULL; place new node there.
- `search(root, key)`: same walk; return pointer or NULL.
- `delete(root, key)`: three cases — leaf, one child, two children (replace with **in-order successor**).

## Invariants | 不变量
- In-order traversal yields keys in **ascending order**.

## Complexity | 复杂度
| Op | Average | Worst |
|----|---------|-------|
| search | O(log n) | O(n) |
| insert | O(log n) | O(n) |
| delete | O(log n) | O(n) |

Worst case `h = n` for a skewed tree → motivates self-balancing trees (AVL, Day 29).