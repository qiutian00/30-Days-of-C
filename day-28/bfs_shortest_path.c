#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6
#define INF 999999

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

static void bfsShortestPath(struct Graph *g, int src, int dist[], int prev[])
{
    for (int i = 0; i < V; i++) { dist[i] = INF; prev[i] = -1; }
    dist[src] = 0;

    int q[V], head = 0, tail = 0;
    q[tail++] = src;

    while (head != tail) {
        int u = q[head++];
        for (struct Node *p = g->adj[u]; p; p = p->next) {
            if (dist[p->v] == INF) {
                dist[p->v] = dist[u] + 1;
                prev[p->v] = u;
                q[tail++] = p->v;
            }
        }
    }
}

static void printPath(int prev[], int target)
{
    if (prev[target] != -1) printPath(prev, prev[target]);
    printf("%d ", target);
}

int main(void)
{
    struct Graph g;
    for (int i = 0; i < V; i++) g.adj[i] = NULL;

    /* 0 - 1 - 2
       |   |   |
       3 - 4 - 5  (unweighted) */
    addEdge(&g, 0, 1); addEdge(&g, 1, 2); addEdge(&g, 0, 3);
    addEdge(&g, 1, 4); addEdge(&g, 2, 5); addEdge(&g, 3, 4);
    addEdge(&g, 4, 5);

    int dist[V], prev[V];
    bfsShortestPath(&g, 0, dist, prev);

    printf("Vertex  dist  prev  path\n");
    for (int i = 0; i < V; i++) {
        printf("  %d      %2d    %2d    ", i, dist[i], prev[i]);
        printPath(prev, i);
        printf("\n");
    }
    return 0;
}
