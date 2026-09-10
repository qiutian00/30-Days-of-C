# Day 25: Stacks | 栈

> A bilingual (English / 中文) walkthrough of Day 25.
> 本节为第二十五天的双语概念讲解。

---

## 1. Overview | 概述

**English**

A **stack** is a **Last-In, First-Out (LIFO)** structure: the most recently pushed element is the first to be popped. All operations happen at one end called the **top**.

Core operations:

- `push(x)` — add `x` on top.
- `pop()`     — remove and return the top element.
- `peek()`    — read the top without removing it.
- `isEmpty()` — whether the stack has no elements.

All operations run in **O(1)** time.

**中文**

**栈**是一种**后进先出（LIFO）**结构：最后入栈的元素最先出栈。所有操作都在称为**栈顶**的一端进行。

核心操作：

- `push(x)` —— 将 `x` 压入栈顶。
- `pop()`   —— 移除并返回栈顶元素。
- `peek()`  —— 查看但不移除栈顶。
- `isEmpty()` —— 判断栈是否为空。

所有操作均为 **O(1)** 时间。

---

## 2. Array-Based Stack | 基于数组的栈

```c
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CAP 100

struct Stack {
    int data[CAP];
    int top;        /* index of the top element; -1 means empty */
};

void init(struct Stack *s)       { s->top = -1; }
bool isEmpty(struct Stack *s)    { return s->top == -1; }
bool isFull(struct Stack *s)     { return s->top == CAP - 1; }

void push(struct Stack *s, int x) {
    if (isFull(s)) { fprintf(stderr, "stack overflow\n"); exit(1); }
    s->data[++s->top] = x;
}

int pop(struct Stack *s) {
    if (isEmpty(s)) { fprintf(stderr, "stack underflow\n"); exit(1); }
    return s->data[s->top--];
}

int peek(struct Stack *s) {
    if (isEmpty(s)) { fprintf(stderr, "empty stack\n"); exit(1); }
    return s->data[s->top];
}
```

**English**

`top` is the index of the last pushed element. Overflow is detected when `top == CAP - 1`.

**中文**

`top` 是最后压入元素的下标。当 `top == CAP - 1` 时检测到栈上溢。

---

## 3. Linked-List-Based Stack | 基于链表的栈

```c
struct SNode {
    int data;
    struct SNode *next;
};

struct LStack {
    struct SNode *top;
};

void linit(struct LStack *s)      { s->top = NULL; }
bool lisEmpty(struct LStack *s)   { return s->top == NULL; }

void lpush(struct LStack *s, int x) {
    struct SNode *n = malloc(sizeof(*n));
    n->data = x;
    n->next = s->top;
    s->top = n;
}

int lpop(struct LStack *s) {
    if (lisEmpty(s)) { fprintf(stderr, "underflow\n"); exit(1); }
    struct SNode *n = s->top;
    int v = n->data;
    s->top = n->next;
    free(n);
    return v;
}
```

**English**

Each `push` prepends a new node; `pop` removes the head. Capacity is limited only by available memory.

**中文**

每次 `push` 都在链表头插入新节点；`pop` 删除头节点。容量仅受可用内存限制。

---

## 4. Application: Balanced Parentheses | 应用：括号匹配

**English**

A classic use of stacks: check whether each opening bracket has a matching closing bracket in the correct order. For `(`, `{`, `[` push; for `)`, `}`, `]` pop and compare.

**中文**

栈的经典应用：检查每个开括号是否在正确顺序下有匹配的闭括号。遇到 `(`、`{`、`[` 则压栈；遇到 `)`、`}`、`]` 则出栈并比较。

```c
bool balanced(const char *s)
{
    struct Stack st; init(&st);
    for (int i = 0; s[i]; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            push(&st, c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (isEmpty(&st)) return false;
            char o = (char)pop(&st);
            if ((c == ')' && o != '(') ||
                (c == '}' && o != '{') ||
                (c == ']' && o != '[')) return false;
        }
    }
    return isEmpty(&st);   /* balanced iff stack ends empty */
}
```

---

## 5. Application: Backtracking (DFS, Maze Solving) | 应用：回溯（DFS、迷宫求解）

**English**

**Backtracking** is a systematic way to explore a search space: make a choice, go deeper, and — if you hit a dead end — *undo* the last choice and try the next option. The "undo and retry" behavior maps directly onto the LIFO nature of a stack.

**Depth-First Search (DFS)** walks as far as possible along one branch before backtracking. DFS can be written recursively (using the implicit call stack) or iteratively with an explicit stack, which is exactly the structure we built in this lesson.

A classic example is **maze solving**: from the start cell, push each reachable neighbor onto the stack, pop the next cell to visit, and mark cells as visited so we never revisit them. The stack remembers the trail so we can backtrack when a corridor is blocked.

**中文**

**回溯（Backtracking）**是一种系统地探索解空间的方法：做出一个选择、深入一步，一旦走入死胡同就**撤销**上一步选择并尝试下一个选项。这种"撤销并重试"的行为正好对应栈的后进先出特性。

**深度优先搜索（DFS）**沿着一条分支尽可能走到底，再回溯。DFS 既可以用递归实现（依赖隐式调用栈），也可以用显式栈迭代实现——正是本节所构建的结构。

一个经典例子是**迷宫求解**：从起点格子出发，把每个可达邻居压入栈，弹出下一个待访问格子，并标记已访问避免重复。栈记住了走过的路径，以便在通道被堵死时回溯。

```c
#include <stdio.h>
#include <stdbool.h>

#define ROWS 5
#define COLS 5

typedef struct { int r, c; } Point;      /* a cell (row, column) */

/* A stack whose elements are maze cells. */
struct PStack {
    Point data[ROWS * COLS];
    int top;
};

void pinit(struct PStack *s)   { s->top = -1; }
bool pempty(struct PStack *s)  { return s->top == -1; }
void ppush(struct PStack *s, Point p) { s->data[++s->top] = p; }
Point ppop(struct PStack *s)   { return s->data[s->top--]; }

/* 0 = open path, 1 = wall. Start (0,0), goal (4,4). */
int maze[ROWS][COLS] = {
    {0, 1, 0, 0, 0},
    {0, 1, 0, 1, 0},
    {0, 0, 0, 1, 0},
    {0, 1, 1, 1, 0},
    {0, 0, 0, 0, 0},
};

bool visited[ROWS][COLS];
Point parent[ROWS][COLS];       /* to rebuild the path backwards */

int dr[4] = {-1, 1,  0, 0};     /* up, down, left, right */
int dc[4] = { 0, 0, -1, 1};

bool solve_maze(Point start, Point goal)
{
    struct PStack st; pinit(&st);
    ppush(&st, start);
    visited[start.r][start.c] = true;
    parent[start.r][start.c] = start;   /* sentinel: stop backtracking here */

    while (!pempty(&st)) {
        Point cur = ppop(&st);
        if (cur.r == goal.r && cur.c == goal.c) return true;  /* found! */

        for (int d = 0; d < 4; d++) {
            int nr = cur.r + dr[d];
            int nc = cur.c + dc[d];
            if (nr < 0 || nr >= ROWS || nc < 0 || nc >= COLS) continue;
            if (maze[nr][nc] == 1 || visited[nr][nc]) continue;

            visited[nr][nc] = true;
            parent[nr][nc] = cur;
            ppush(&st, (Point){nr, nc});
        }
    }
    return false;                        /* no path */
}

void print_path(Point goal)
{
    Point path[ROWS * COLS];
    int n = 0;
    Point p = goal;
    while (!(p.r == 0 && p.c == 0)) {    /* walk parents back to start */
        path[n++] = p;
        p = parent[p.r][p.c];
    }
    path[n++] = (Point){0, 0};

    printf("Path: ");
    for (int i = n - 1; i >= 0; i--)
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
```

**English**

Each pop visits one cell; each reachable, unvisited neighbor is marked and pushed. When a dead end is reached, the search simply pops the previous cell — that is the **backtrack**. The `parent` array lets us reconstruct the route from the goal back to the start.

Note that plain DFS finds *a* path, not necessarily the shortest one (that would need BFS).

**中文**

每次弹栈访问一个格子；每个可达且未访问的邻居都会被标记并压栈。当走到死胡同时，程序只需弹出上一个格子——这就是**回溯**。`parent` 数组让我们能从终点反推出到达起点的路线。

注意：普通 DFS 找到的是*某一条*路径，而不一定是最短路径（最短路径需要 BFS）。

**Expected output | 期望输出**:
```
Path: (0,0) -> (1,0) -> (2,0) -> (2,1) -> (2,2) -> (1,2) -> (0,2) -> (0,3) -> (0,4) -> (1,4) -> (2,4) -> (3,4) -> (4,4)
```

---

## 6. Demo | 示例

```c
int main(void)
{
    struct Stack s; init(&s);
    push(&s, 10); push(&s, 20); push(&s, 30);
    printf("peek = %d\n", peek(&s));
    printf("pop  = %d\n", pop(&s));
    printf("pop  = %d\n", pop(&s));

    const char *tests[] = {"(a{b[c]d}e)", "(a{b[c}d]e)", "((())", ""};
    for (int i = 0; i < 4; i++)
        printf("\"%s\" -> %s\n", tests[i], balanced(tests[i]) ? "balanced" : "unbalanced");
    return 0;
}
```

**Expected output | 期望输出**:
```
peek = 30
pop  = 30
pop  = 20
"(a{b[c]d}e)" -> balanced
"(a{b[c}d]e)" -> unbalanced
"((())" -> unbalanced
"" -> balanced
```

---

## 7. Applications | 应用场景

**English**
- Function call stack (recursion relies on it).
- Expression evaluation (infix → postfix, then evaluate).
- Backtracking (DFS, maze solving).
- Undo/redo in editors.

**中文**
- 函数调用栈（递归依赖它）。
- 表达式求值（中缀转后缀，再求值）。
- 回溯（DFS、迷宫求解）。
- 编辑器的撤销/重做。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `array_stack.c` | Array-based stack with balanced-parentheses demo | 基于数组的栈 + 括号匹配演示 |
| `linked_stack.c` | Linked-list-based stack | 基于链表的栈 |
| `maze_solver.c` | Backtracking / DFS maze solver | 回溯 / DFS 迷宫求解 |
| `day-25-summary.md` | Day 25 notes | 第二十五天学习笔记 |