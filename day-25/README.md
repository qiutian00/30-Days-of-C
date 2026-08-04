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

## 5. Demo | 示例

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

## 6. Applications | 应用场景

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
| `day-25-summary.md` | Day 25 notes | 第二十五天学习笔记 |