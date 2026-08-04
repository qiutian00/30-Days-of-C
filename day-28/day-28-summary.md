# Day 28: More on Graphs | 图的进阶

## Shortest paths | 最短路径
- **Unweighted**: BFS records predecessor when first discovering a vertex → `dist[v] = hops`, `prev[v]` = parent. Reconstruct path by chaining `prev` back to source. O(V + E).
- **Weighted (non-negative)**: Dijkstra — repeatedly relax edges from the closest unvisited vertex.
  - Linear-scan min selection: O(V^2). With a min-heap: O((V+E) log V).
  - **Relaxation**: `if dist[u] + w(u,v) < dist[v]: dist[v] = dist[u] + w; prev[v] = u`.
  - **No negative edges** — use Bellman-Ford for those.

## Demo graph | 示例图
```
       (4)     (1)
    0 ----- 1 ----- 2
    |       |       |
  (2)     (3)     (5)
    |       |       |
    3 ----- 4 ----- 5
       (1)     (1)
```
From 0, Dijkstra distances: 0, 4, 5, 2, 3, 4.