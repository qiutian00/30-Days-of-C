# Day 38: Red-Black Tree | 红黑树

## Properties | 性质
1. Nodes are red or black.
2. Root is black.
3. Leaves (NIL) are black.
4. A red node's children are black (no two reds in a row).
5. Equal black-height on all root-to-leaf paths.

## Balance guarantee | 平衡保证
- Longest path <= 2x shortest; height ~ 2 log n; all ops O(log n).

## Insertion | 插入
- Insert as BST, color new node red, then fix violations:
  - Uncle red -> recolor and move up.
  - Uncle black -> rotate (zig-zig / zig-zag) and recolor.
- Root always re-colored black at the end.

## Rotations | 旋转
- `left_rotate`: right child becomes parent.
- `right_rotate`: left child becomes parent.

## AVL vs RB | 对比
- AVL: stricter balance, faster lookup, more rotations.
- RB: fewer rotations, faster insert/delete; used in kernel, std::map, TreeMap.
