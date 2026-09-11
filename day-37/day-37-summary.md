# Day 37: Segment Tree & Fenwick Tree | 线段树与树状数组

## Fenwick tree (BIT) | 树状数组
- `i & -i` = lowest set bit; index i covers that many elements.
- `update(i, delta)`: `i += i & -i`. `query(i)`: `i -= i & -i`. Both O(log n).
- Only for invertible queries (prefix sums).

## Segment tree | 线段树
- Full binary tree over the array; node stores aggregate of its segment.
- Build O(n); query/update O(log n); memory ~4n.
- Query cases: no overlap -> identity; full overlap -> stored value; else split.
- General: sum/min/max/GCD, range updates via lazy propagation.

## When to use | 何时使用
- Simple prefix/invertible + point update -> Fenwick (faster, smaller).
- Arbitrary associative query or range update -> Segment tree.
