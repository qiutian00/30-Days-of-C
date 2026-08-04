#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 6
#define INF 999999

struct WNode {
    int v, w;
    struct WNode *next;
};

struct WGraph {
    struct WNode *adj[V];
};

static void addW(struct WGraph *g, int u, int v, int w)
{
    struct WNode *n1 = malloc(sizeof(*n1)); n1->v = v; n1->w = w; n1->next = g->adj[u]; g->adj[u] = n1;
    struct WNode *n2 = malloc(sizeof(*n2)); n2->v = u; n2->w = w; n2->next = g->adj[v]; g->adj[v] = n2;
}

static void dijkstra(struct WGraph *g, int src, int dist[], int prev[])
{
    bool visited[V] = {false};
    for (int i = 0; i < V; i++) { dist[i] = INF; prev[i] = -1; }
    dist[src] = 0;

    for (int iter = 0; iter < V; iter++) {
        int u = -1, best = INF;
        for (int i = 0; i < V; i++)
            if (!visited[i] && dist[i] < best) { best = dist[i]; u = i; }
        if (u == -1) break;
        visited[u] = true;

        for (struct WNode *p = g->adj[u]; p; p = p->next) {
            if (dist[u] + p->w < dist[p->v]) {
                dist[p->v] = dist[u] + p->w;
                prev[p->v] = u;
            }
        }
    }
}

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
