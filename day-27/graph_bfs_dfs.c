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

static void addEdge(struct Graph *g, int u, int v)
{
    struct Node *n1 = malloc(sizeof(*n1)); n1->v = v; n1->next = g->adj[u]; g->adj[u] = n1;
    struct Node *n2 = malloc(sizeof(*n2)); n2->v = u; n2->next = g->adj[v]; g->adj[v] = n2;
}

static void bfs(struct Graph *g, int src)
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

static void dfsRec(struct Graph *g, int u, bool visited[V])
{
    visited[u] = true;
    printf("%d ", u);
    for (struct Node *p = g->adj[u]; p; p = p->next)
        if (!visited[p->v])
            dfsRec(g, p->v, visited);
}

static void dfs(struct Graph *g, int src)
{
    bool visited[V] = {false};
    dfsRec(g, src, visited);
}

int main(void)
{
    struct Graph g;
    for (int i = 0; i < V; i++) g.adj[i] = NULL;

    /* 0 - 1 - 2
       |   |   |
       3 - 4 - 5  */
    addEdge(&g, 0, 1); addEdge(&g, 1, 2); addEdge(&g, 0, 3);
    addEdge(&g, 1, 4); addEdge(&g, 2, 5); addEdge(&g, 3, 4);
    addEdge(&g, 4, 5);

    printf("BFS from 0: ");
    bfs(&g, 0);
    printf("\n");

    printf("DFS from 0: ");
    dfs(&g, 0);
    printf("\n");
    return 0;
}
