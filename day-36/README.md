# Day 36: Union-Find | 并查集

> A bilingual (English / 中文) walkthrough of Day 36.
> 本节为第三十六天的补充讲解：并查集（不相交集合）。

---

## 1. Overview | 概述

**English**

**Union-Find** (Disjoint Set Union, DSU) maintains a partition of elements into disjoint sets, supporting two near-constant-time operations:

- `find(x)` — return the representative/root of `x`'s set.
- `union(x, y)` — merge the two sets containing `x` and `y`.

It is used to answer connectivity queries and to detect cycles in a graph.

**中文**

**并查集（不相交集合，DSU）**维护元素集合的一种划分，支持两个近常数时间的操作：

- `find(x)` —— 返回 `x` 所在集合的代表元/根。
- `union(x, y)` —— 合并包含 `x` 与 `y` 的两个集合。

它用于回答连通性查询，以及检测图中的环。

---

## 2. Optimizations | 两种优化

**English**

- **Path compression** — during `find`, point every node on the path directly to the root.
- **Union by rank/size** — always attach the smaller (by rank) tree under the larger one.

Together they make the amortized time **O(α(n))**, where α is the inverse Ackermann function — effectively constant for any practical `n`.

**中文**

- **路径压缩（Path compression）** —— 在 `find` 过程中，把路径上的每个节点直接指向根。
- **按秩/大小合并（Union by rank/size）** —— 总是把秩较小的树挂到较大的树下。

两者结合使摊还时间达到 **O(α(n))**，其中 α 是反阿克曼函数 —— 对任何实际 `n` 几乎等同于常数。

---

## 3. Implementation | 实现

```c
#include <stdio.h>
#include <stdbool.h>

#define N 100

int parent[N];
int rank[N];

void make_set(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;      /* each element is its own root */
        rank[i] = 0;
    }
}

/* Find the root with path compression. */
int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

/* Union by rank. Returns true if the sets were merged, false if already joined. */
bool union_sets(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return false;          /* already in the same set */

    if (rank[rx] < rank[ry]) {
        int t = rx; rx = ry; ry = t;     /* keep rx as the taller tree */
    }
    parent[ry] = rx;
    if (rank[rx] == rank[ry]) rank[rx]++;
    return true;
}
```

---

## 4. Application: Cycle Detection in an Undirected Graph | 应用：无向图判环

**English**

Process each edge. If its two endpoints already belong to the same set, adding it would create a cycle; otherwise union them.

**中文**

逐条处理边。若某条边的两个端点已在同一集合，加入它就会形成环；否则合并两者。

```c
bool has_cycle(int edges[][2], int m, int n) {
    make_set(n);
    for (int i = 0; i < m; i++) {
        int u = edges[i][0], v = edges[i][1];
        if (!union_sets(u, v))
            return true;                 /* endpoints already connected */
    }
    return false;
}
```

---

## 5. Application: Number of Connected Components | 应用：连通分量计数

**English**

Start with `n` components; each successful `union` reduces the count by one.

**中文**

初始有 `n` 个分量；每次成功的 `union` 让分量数减一。

```c
int count_components(int edges[][2], int m, int n) {
    make_set(n);
    int components = n;
    for (int i = 0; i < m; i++)
        if (union_sets(edges[i][0], edges[i][1]))
            components--;
    return components;
}
```

---

## 6. Demo | 示例

```c
int main(void)
{
    int edges[][2] = { {0,1}, {1,2}, {3,4}, {2,3} };
    printf("components = %d\n", count_components(edges, 4, 5));

    int edges2[][2] = { {0,1}, {1,2}, {2,0} };
    printf("cycle? %s\n", has_cycle(edges2, 3, 3) ? "yes" : "no");
    return 0;
}
```

**Expected output | 期望输出**:
```
components = 2
cycle? yes
```

---

## 7. Complexity & Applications | 复杂度与应用

**English**

| Operation | Time |
|-----------|------|
| `find` / `union` | O(α(n)) amortized |

Applications: Kruskal's MST, detecting graph cycles, network connectivity, image labeling (connected components), percolation.

**中文**

| 操作 | 时间 |
|------|------|
| `find` / `union` | 摊还 O(α(n)) |

应用：Kruskal 最小生成树、图判环、网络连通性、图像连通域标记、渗流问题。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `union_find.c` | DSU + cycle detection + component count | 并查集 + 判环 + 计数 |
| `day-36-summary.md` | Day 36 notes | 第三十六天学习笔记 |
