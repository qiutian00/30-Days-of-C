#include <stdio.h>
#include <stdbool.h>

#define ROWS 5
#define COLS 5

/* A single maze cell, addressed by (row, column).
   一个迷宫格子，用 (行, 列) 定位。 */
typedef struct { int r, c; } Point;

/* A stack of cells used by the iterative DFS.
   迭代式 DFS 所用的格子栈。 */
struct PStack {
    Point data[ROWS * COLS];
    int top;                        /* index of top element; -1 means empty
                                       栈顶下标；-1 表示空栈 */
};

static void pinit(struct PStack *s)   { s->top = -1; }
static bool pempty(struct PStack *s)  { return s->top == -1; }
static void ppush(struct PStack *s, Point p) { s->data[++s->top] = p; }
static Point ppop(struct PStack *s)   { return s->data[s->top--]; }

/* 0 = open path, 1 = wall. Start (0,0), goal (4,4).
   0 表示通路，1 表示墙。起点 (0,0)，终点 (4,4)。 */
int maze[ROWS][COLS] = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0},
};

static bool visited[ROWS][COLS];    /* whether a cell has already been explored
                                       标记某个格子是否已被探索过 */
static Point parent[ROWS][COLS];    /* the cell we came from, to rebuild the path
                                       记录来时的格子，用于重建路径 */

/* up, down, left, right
   上、下、左、右 */
static int dr[4] = {-1, 1,  0, 0};
static int dc[4] = { 0, 0, -1, 1};

/* Depth-first search: walk one branch to its end, backtrack on dead ends.
   深度优先搜索：沿一条分支走到尽头，遇到死路则回溯。 */
static bool solve_maze(Point start, Point goal)
{
    struct PStack st; pinit(&st);
    ppush(&st, start);
    visited[start.r][start.c] = true;
    parent[start.r][start.c] = start;   /* sentinel: stop walking parents here
                                           哨兵：回溯到此处即停止 */

    while (!pempty(&st)) {
        Point cur = ppop(&st);          /* visit the cell on top
                                           访问栈顶格子 */
        if (cur.r == goal.r && cur.c == goal.c) return true;   /* reached goal
                                                                  已到达终点 */

        /* Push every reachable, unvisited neighbour.
           把每个可达且未访问的邻居压入栈。 */
        for (int d = 0; d < 4; d++) {
            int nr = cur.r + dr[d];
            int nc = cur.c + dc[d];
            if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) continue;   /* out of bounds
                                                                              越界 */
            if (maze[nr][nc] == 1 || visited[nr][nc]) continue;            /* wall or seen
                                                                              是墙或已访问 */

            visited[nr][nc] = true;
            parent[nr][nc] = cur;       /* remember where we came from
                                           记住来路 */
            ppush(&st, (Point){nr, nc});
        }
    }
    return false;                       /* stack drained: no path
                                           栈已清空：无路径 */
}

/* Walk the parent chain from the goal back to the start, then print forward.
   沿 parent 链从终点回溯到起点，再正向打印。 */
static void print_path(Point goal)
{
    Point path[ROWS * COLS];
    int n = 0;
    Point p = goal;
    while (!(p.r == 0 && p.c == 0)) {   /* collect cells in reverse order
                                           倒序收集路径上的格子 */
        path[n++] = p;
        p = parent[p.r][p.c];
    }
    path[n++] = (Point){0, 0};          /* the start cell
                                           起点格子 */

    printf("Path: ");
    for (int i = n - 1; i >= 0; i--)    /* print from start to goal
                                           从起点到终点依次打印 */
        printf("(%d,%d)%s", path[i].r, path[i].c, i ? " -> " : "\n");
}

int main(void)
{
    Point start = {0, 0};
    Point goal  = {ROWS - 1, COLS - 1};

    if (solve_maze(start, goal))
        print_path(goal);
    else
        printf("No path found.\n");
    return 0;
}
