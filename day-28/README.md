# Day 28: More on Graphs | 图的进阶

> A bilingual (English / 中文) walkthrough of Day 28.
> 本节为第二十八天的双语概念讲解。

---

## 1. Overview | 概述

**English**

Day 27 covered the basics of graphs and BFS/DFS. Today we use BFS to compute **shortest paths in unweighted graphs**, then introduce **Dijkstra's algorithm** for **non-negative weighted graphs**.

**中文**

第二十七天介绍了图和 BFS/DFS 的基础。今天我们用 BFS 求**无权图的最短路径**，并引入**Dijkstra 算法**求解**非负权重图**的最短路径。

---

## 2. Shortest Path in Unweighted Graphs (via BFS) | 无权图最短路径（BFS）

**English**

BFS naturally visits vertices in order of their distance from the source. By recording each vertex's **predecessor** when first discovered, we can reconstruct the path back to the source.

**中文**

BFS 天然按距源点的距离顺序访问顶点。当某个顶点首次被发现时，记录它的**前驱**，便可从目标顶点回溯到源点。

```c
#define V 6
#define INF 999999

void bfsShortestPath(struct Graph *g, int src, int dist[], int prev[])
{
    for (int i = 0; i < V; i++) { dist[i] = INF; prev[i] = -1; }
    dist[src] = 0;

    int q[V], head = 0, tail = 0;
    q[tail++] = src;

    while (head != tail) {
        int u = q[head++];
        for (struct Node *p = g->adj[u]; p; p = p->next) {
            if (dist[p->v] == INF) {           /* unvisited */
                dist[p->v] = dist[u] + 1;
                prev[p->v] = u;
                q[tail++] = p->v;
            }
        }
    }
}
```

**English**
- `dist[v]` = number of edges from `src` to `v` (or `INF` if unreachable).
- `prev[v]` = predecessor on a shortest path; chain it back to the source.
- Time: **O(V + E)**.

**中文**
- `dist[v]` = 从 `src` 到 `v` 的边数（不可达则 `INF`）。
- `prev[v]` = 最短路径上的前驱；沿此前驱链可回到源点。
- 时间：**O(V + E)**。

---

## 3. Dijkstra's Algorithm | Dijkstra 算法

**English**

For **non-negative weighted** graphs, Dijkstra's algorithm generalizes BFS: instead of a FIFO queue, repeatedly pick the **unvisited vertex with the smallest tentative distance** and relax its outgoing edges.

We use an adjacency list with edge weights:

```c
struct WNode {
    int v, w;
    struct WNode *next;
};

struct WGraph {
    struct WNode *adj[V];
};
```

```c
void dijkstra(struct WGraph *g, int src, int dist[], int prev[])
{
    bool visited[V] = {false};
    for (int i = 0; i < V; i++) { dist[i] = INF; prev[i] = -1; }
    dist[src] = 0;

    for (int iter = 0; iter < V; iter++) {
        /* pick the unvisited vertex with min dist */
        int u = -1, best = INF;
        for (int i = 0; i < V; i++)
            if (!visited[i] && dist[i] < best) { best = dist[i]; u = i; }
        if (u == -1) break;               /* remaining are unreachable */
        visited[u] = true;

        for (struct WNode *p = g->adj[u]; p; p = p->next) {
            if (dist[u] + p->w < dist[p->v]) {
                dist[p->v] = dist[u] + p->w;
                prev[p->v] = u;
            }
        }
    }
}
```

**English**
- **Relaxation**: `if dist[u] + w(u,v) < dist[v], update dist[v]`.
- Picking the min-distance vertex with a linear scan yields **O(V²)** — fine for dense graphs; a min-heap brings it to **O((V+E) log V)**.
- Dijkstra **does not** work with negative edges — for those use Bellman-Ford.

**中文**
- **松弛**：`若 dist[u] + w(u,v) < dist[v]，则更新 dist[v]`。
- 线性扫描选最小距离顶点得到 **O(V²)** —— 对稠密图可接受；用最小堆可降到 **O((V+E) log V)**。
- Dijkstra **不能**处理负权边 —— 需用 Bellman-Ford。

---

## 4. Demo | 示例

**English**

Graph used for both demos (weighted, undirected):

```
       (4)     (1)
    0 ----- 1 ----- 2
    |       |       |
  (2)     (3)     (5)
    |       |       |
    3 ----- 4 ----- 5
       (1)     (1)
```

**中文**

两个示例共用此图（无向带权）：

```
       (4)     (1)
    0 ----- 1 ----- 2
    |       |       |
  (2)     (3)     (5)
    |       |       |
    3 ----- 4 ----- 5
       (1)     (1)
```

```c
int main(void)
{
    struct WGraph g;
    for (int i = 0; i < V; i++) g.adj[i] = NULL;
    addW(&g, 0, 1, 4); addW(&g, 1, 2, 1); addW(&g, 0, 3, 2);
    addW(&g, 1, 4, 3); addW(&g, 2, 5, 5); addW(&g, 3, 4, 1);
    addW(&g, 4, 5, 1);

    int dist[V], prev[V];
    dijkstra(&g, 0, dist, prev);

    printf("Vertex  dist  prev\n");
    for (int i = 0; i < V; i++)
        printf("  %d      %2d    %2d\n", i, dist[i], prev[i]);
    return 0;
}
```

**Expected output | 期望输出**:
```
Vertex  dist  prev
  0       0    -1
  1       4     0
  2       5     1
  3       2     0
  4       3     3
  5       4     4
```

---

## 5. Key Takeaways | 要点

**English**
- BFS computes shortest **hop counts** in **O(V + E)** for unweighted graphs.
- Dijkstra computes shortest **weighted distances** in **O(V²)** (or O((V+E) log V) with a heap) for **non-negative** weights.
- The `prev[]` array lets you reconstruct the actual path.

**中文**
- BFS 在**无权图**中以 **O(V + E)** 计算最短**跳数**。
- Dijkstra 在**非负权图**中以 **O(V²)**（或用堆 O((V+E) log V)）计算最短**加权距离**。
- `prev[]` 数组可还原实际路径。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `bfs_shortest_path.c` | BFS for unweighted shortest paths | 无权图最短路径 BFS |
| `dijkstra.c` | Dijkstra's algorithm (linear-scan min) | Dijkstra 算法（线性选最小） |
| `day-28-summary.md` | Day 28 notes | 第二十八天学习笔记 |