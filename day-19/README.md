# Day 19: Intro to Recursion | 递归入门

> A bilingual (English / 中文) walkthrough of Day 19.
> 本节为第十九天的双语概念讲解。

---

## 1. What is Recursion? | 什么是递归？

**English**

Recursion is a technique in which a function **calls itself** to solve a smaller instance of the same problem. Every recursive function must have:

- A **base case** — the condition that stops the recursion.
- A **recursive case** — the function calls itself with a smaller/simpler input that moves toward the base case.

Without a correct base case, the call stack grows until a **stack overflow** occurs.

**中文**

递归是一种让函数**调用自身**以求解同类更小规模子问题的技术。每个递归函数必须包含：

- **基本情况** —— 终止递归的条件。
- **递归情况** —— 函数以更小/更简单的输入调用自身，逐步逼近基本情况。

基本情况不正确时，调用栈不断增长，最终引发**栈溢出**。

---

## 2. The Call Stack | 调用栈

**English**

Each recursive call pushes a new **stack frame** (containing its parameters and locals). When the base case returns, the frames are popped in reverse order, and results are combined on the way back.

**中文**

每次递归调用都会压入一个新的**栈帧**（包含其参数与局部变量）。当基本情况返回后，栈帧按相反顺序弹出，结果在回溯过程中合并。

---

## 3. Factorial | 阶乘

**English**

Definition: `n! = n * (n-1)!`, with `0! = 1` as the base case.

```c
#include <stdio.h>

long factorial(int n)
{
    if (n <= 1)        // base case
        return 1;
    return n * factorial(n - 1);   // recursive case
}

int main(void)
{
    for (int i = 0; i <= 6; i++)
        printf("%d! = %ld\n", i, factorial(i));
    return 0;
}
```

**中文**

定义：`n! = n * (n-1)!`，其中 `0! = 1` 是基本情况。

```c
#include <stdio.h>

long factorial(int n)
{
    if (n <= 1)        // 基本情况
        return 1;
    return n * factorial(n - 1);   // 递归情况
}

int main(void)
{
    for (int i = 0; i <= 6; i++)
        printf("%d! = %ld\n", i, factorial(i));
    return 0;
}
```

---

## 4. Fibonacci | 斐波那契

**English**

Definition: `F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2)`.

> **Note**: this naive recursion has **exponential** time complexity O(2ⁿ) because it recomputes the same sub-problems many times. We'll optimize it later with memoization or iteration.

```c
#include <stdio.h>

int fib(int n)
{
    if (n == 0) return 0;          // base case
    if (n == 1) return 1;          // base case
    return fib(n - 1) + fib(n - 2); // recursive case
}

int main(void)
{
    for (int i = 0; i < 10; i++)
        printf("%d ", fib(i));
    printf("\n");
    return 0;
}
```

**中文**

定义：`F(0) = 0, F(1) = 1, F(n) = F(n-1) + F(n-2)`。

> **注意**：这种朴素递归时间复杂度为**指数级** O(2ⁿ)，因为会重复计算同一子问题。后续可用备忘录（记忆化）或迭代来优化。

```c
#include <stdio.h>

int fib(int n)
{
    if (n == 0) return 0;          // 基本情况
    if (n == 1) return 1;          // 基本情况
    return fib(n - 1) + fib(n - 2); // 递归情况
}

int main(void)
{
    for (int i = 0; i < 10; i++)
        printf("%d ", fib(i));
    printf("\n");
    return 0;
}
```

---

## 5. Countdown — Tracing the Stack | 倒计时 —— 追踪调用栈

```c
#include <stdio.h>

void countdown(int n)
{
    printf("enter countdown(%d)\n", n);
    if (n == 0) {            // base case
        printf("liftoff!\n");
        return;
    }
    countdown(n - 1);       // recursive case
    printf("exit countdown(%d)\n", n);
}

int main(void)
{
    countdown(3);
    return 0;
}
```

**English**

Run it and observe: the `enter` messages are printed on the way **down** (in call order), while the `exit` messages are printed on the way **back up** (in return order). This neatly illustrates the call stack behavior.

**中文**

运行后会看到：`enter` 信息是**向下**调用时打印的（按调用顺序），而 `exit` 信息是**向上**回溯时打印的（按返回顺序），清晰地展示了调用栈的行为。

---

## 6. Key Takeaways | 要点

**English**
- Recursion = base case + recursive case converging toward the base case.
- Each call adds a stack frame; too many calls cause stack overflow.
- Naive recursion can be exponentially slow; memoization or iteration helps.

**中文**
- 递归 = 基本情况 + 逐步逼近基本情况的递归情况。
- 每次调用都会压入一个栈帧；调用过多会导致栈溢出。
- 朴素递归可能呈指数级慢；可用记忆化或迭代优化。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `factorial.c` | Recursive factorial | 递归实现阶乘 |
| `fibonacci.c` | Recursive Fibonacci (naive) | 朴素递归斐波那契 |
| `countdown.c` | Tracing the call stack | 追踪调用栈的倒计时示例 |
| `day-19-summary.md` | Day 19 notes | 第十九天学习笔记 |