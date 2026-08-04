# Day 27: Intro to Graphs | 图的入门

## Graph G = (V, E) | 图
- Vertices + edges; directed/undirected, weighted/unweighted, cyclic/acyclic.
- Tree = connected acyclic undirected graph.

## Representations | 表示
- **Adjacency matrix**: O(V^2) space, O(1) edge lookup. Good for dense graphs.
- **Adjacency list**: O(V + E) space, efficient traversal. Good for sparse graphs.

## Traversals (both O(V + E)) | 遍历（均 O(V + E)）
- **BFS**: queue-based; explores by distance from source; finds shortest paths in unweighted graphs.
- **DFS**: recursion or explicit stack; goes deep, then backtracks; basis for cycle detection, topo sort, connected components.

## Implementation | 实现
- `struct Graph { struct Node *adj[V]; }` with singly linked lists per vertex.
- `addEdge` prepends to both endpoints (undirected).