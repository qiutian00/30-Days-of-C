#include <stdio.h>
#include <stdbool.h>

#define N 100

int parent[N];
int rank[N];

void make_set(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

bool union_sets(int x, int y) {
    int rx = find(x), ry = find(y);
    if (rx == ry) return false;

    if (rank[rx] < rank[ry]) {
        int t = rx; rx = ry; ry = t;
    }
    parent[ry] = rx;
    if (rank[rx] == rank[ry]) rank[rx]++;
    return true;
}

bool has_cycle(int edges[][2], int m, int n) {
    make_set(n);
    for (int i = 0; i < m; i++) {
        if (!union_sets(edges[i][0], edges[i][1]))
            return true;
    }
    return false;
}

int count_components(int edges[][2], int m, int n) {
    make_set(n);
    int components = n;
    for (int i = 0; i < m; i++)
        if (union_sets(edges[i][0], edges[i][1]))
            components--;
    return components;
}

int main(void) {
    int edges[][2] = { {0,1}, {1,2}, {3,4}, {2,3} };
    printf("components = %d\n", count_components(edges, 4, 5));

    int edges2[][2] = { {0,1}, {1,2}, {2,0} };
    printf("cycle? %s\n", has_cycle(edges2, 3, 3) ? "yes" : "no");

    return 0;
}
