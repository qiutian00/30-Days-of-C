# Day 36: Union-Find | 并查集

## Idea | 思路
- Maintain disjoint sets; each set has a root (representative).

## Operations | 操作
- `find(x)`: follow parent pointers to the root; apply **path compression**.
- `union(x, y)`: attach smaller-rank root under larger (**union by rank**).

## Complexity | 复杂度
- Amortized O(α(n)) with both optimizations; effectively constant.

## Applications | 应用
- Cycle detection in undirected graphs (union fails -> cycle).
- Count connected components (n - #successful unions).
- Kruskal's MST, network connectivity, image labeling.
