# Day 27: Intro to Graphs | 图的入门

> A bilingual (English / 中文) walkthrough of Day 27.
> 本节为第二十七天的双语概念讲解。

---

## 1. What is a Graph? | 什么是图？

**English**

A **graph** `G = (V, E)` consists of a set of **vertices** `V` and a set of **edges** `E`, where each edge connects two vertices. Graphs may be:

- **Directed** vs **undirected** — edges have direction or not.
- **Weighted** vs **unweighted** — edges carry weights or not.
- **Cyclic** vs **acyclic** — contains cycles or not.

Trees are a special case: a connected, acyclic, undirected graph.

**中文**

**图** `G = (V, E)` 由一组**顶点** `V` 和一组**边** `E` 构成，每条边连接两个顶点。图可分为：

- **有向** vs **无向** —— 边是否有方向。
- **带权** vs **无权** —— 边是否带权重。
- **有环** vs **无环** —— 是否存在环。

树是一种特例：连通、无环的无向图。

---

## 2. Representations | 表示方法

**English**

| Representation | Space | Good for |
|----------------|-------|----------|
| **Adjacency matrix** `V×V` | O(V²) | dense graphs, fast edge lookup O(1) |
| **Adjacency list** (array of lists) | O(V + E) | sparse graphs, efficient traversal |

**中文**

| 表示方法 | 空间 | 适合 |
|----------|------|------|
| **邻接矩阵** `V×V` | O(V²) | 稠密图，查边 O(1) |
| **邻接表**（数组的链表） | O(V + E) | 稀疏图，遍历高效 |

---

## 3. Adjacency List in C | C 中的邻接表

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6

struct Node {
    int v;
    struct Node *next;
};

struct Graph {
    struct Node *adj[V];
};

void addEdge(struct Graph *g, int u, int v) {       /* undirected */
    struct Node *n1 = malloc(sizeof(*n1)); n1->v = v; n1->next = g->adj[u]; g->adj[u] = n1;
    struct Node *n2 = malloc(sizeof(*n2)); n2->v = u; n2->next = g->adj[v]; g->adj[v] = n2;
}
```

**English**

Each `adj[u]` is a singly linked list of vertices adjacent to `u`. Prepending keeps insertion O(1) at the cost of reverse neighbor order — fine for traversal demos.

**中文**

每个 `adj[u]` 是与 `u` 相邻的顶点的单链表。头插法使插入 O(1)，但邻居顺序会反过来 —— 对遍历演示无影响。

---

## 4. Breadth-First Search (BFS) | 广度优先搜索

**English**

From a source vertex, explore **level by level** using a queue. Track visited vertices to avoid revisiting.

**中文**

从源点出发，借助队列**逐层**探索。用 visited 数组避免重复访问。

```c
void bfs(struct Graph *g, int src)
{
    bool visited[V] = {false};
    int q[V], head = 0, tail = 0;

    visited[src] = true;
    q[tail++] = src;

    while (head != tail) {
        int u = q[head++];
        printf("%d ", u);
        for (struct Node *p = g->adj[u]; p; p = p->next) {
            if (!visited[p->v]) {
                visited[p->v] = true;
                q[tail++] = p->v;
            }
        }
    }
}
```

**English**
- Visits all vertices reachable from `src`, in non-decreasing distance order.
- Time: **O(V + E)**.

**中文**
- 按"距源点距离非递减"的顺序访问所有可达顶点。
- 时间：**O(V + E)**。

---

## 5. Depth-First Search (DFS) | 深度优先搜索

**English**

Go as deep as possible along one branch before backtracking. Use recursion (the call stack) or an explicit stack.

**中文**

沿一条分支尽可能深入，再回溯。可用递归（调用栈）或显式栈实现。

```c
void dfsRec(struct Graph *g, int u, bool visited[V])
{
    visited[u] = true;
    printf("%d ", u);
    for (struct Node *p = g->adj[u]; p; p = p->next)
        if (!visited[p->v])
            dfsRec(g, p->v, visited);
}

void dfs(struct Graph *g, int src)
{
    bool visited[V] = {false};
    dfsRec(g, src, visited);
}
```

- Time: **O(V + E)**.

---

## 6. Demo | 示例

```c
int main(void)
{
    struct Graph g;
    for (int i = 0; i < V; i++) g.adj[i] = NULL;

    /* Graph:
       0 - 1 - 2
       |   |   |
       3 - 4 - 5
    */
    addEdge(&g, 0, 1); addEdge(&g, 1, 2); addEdge(&g, 0, 3);
    addEdge(&g, 1, 4); addEdge(&g, 2, 5); addEdge(&g, 3, 4);
    addEdge(&g, 4, 5);

    printf("BFS from 0: "); bfs(&g, 0); printf("\n");
    printf("DFS from 0: "); dfs(&g, 0); printf("\n");
    return 0;
}
```

**Expected output | 期望输出** (with head-prepended adjacency lists):
```
BFS from 0: 0 3 1 4 2 5 
DFS from 0: 0 3 4 5 2 1 
```
> Neighbor order depends on insertion order; the *set* of visited vertices is the same regardless.

> 邻居顺序取决于插入顺序；无论顺序如何，访问到的顶点集合是相同的。

---

## 7. Key Takeaways | 要点

**English**
- Graphs generalize trees with arbitrary connections.
- Use adjacency lists for sparse graphs (most real-world graphs).
- BFS explores by distance and finds shortest paths in unweighted graphs (see Day 28); DFS explores deep and is the basis for cycle detection, topological sort, and connected components.

**中文**
- 图是树的推广，允许任意连接。
- 稀疏图（大多数真实图）优先用邻接表。
- BFS 按距离探索，可在无权图中求最短路径（见第二十八天）；DFS 深入探索，是环检测、拓扑排序、连通分量等算法的基础。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `graph_bfs_dfs.c` | Adjacency-list graph with BFS and DFS | 邻接表图 + BFS 与 DFS |
| `day-27-summary.md` | Day 27 notes | 第二十七天学习笔记 |