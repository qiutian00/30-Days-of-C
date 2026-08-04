# Day 20: Some More Recursion | 更多递归

> A bilingual (English / 中文) walkthrough of Day 20.
> 本节为第二十天的双语概念讲解。

---

## 1. Overview | 概述

**English**

Day 19 introduced the recursion basics. Today we deepen our understanding with three classic recursive problems of different shapes:

- **Linear recursion** — sum of an array, integer exponentiation.
- **Tail recursion** — a special linear form where the recursive call is the last action.
- **Divide-and-conquer recursion** — Tower of Hanoi, where each step spawns two sub-calls.

**中文**

第十九天介绍了递归基础。今天我们用三种不同形态的经典递归问题加深理解：

- **线性递归** —— 数组求和、整数幂运算。
- **尾递归** —— 一种特殊的线性递归，递归调用是函数的最后一步。
- **分治递归** —— 汉诺塔，每一步生成两个子调用。

---

## 2. Sum of an Array (Linear Recursion) | 数组求和（线性递归）

```c
#include <stdio.h>

int sum(int arr[], int n)
{
    if (n == 0) return 0;                      // base case: empty sub-array
    return arr[n - 1] + sum(arr, n - 1);       // recursive case
}

int main(void)
{
    int a[] = {2, 4, 6, 8, 10};
    printf("sum = %d\n", sum(a, 5));
    return 0;
}
```

**English**
- The problem shrinks by one element on each call.
- Linear recursion: only **one** recursive call per invocation → O(n) time, O(n) stack.

**中文**
- 每次调用将问题规模缩减一个元素。
- 线性递归：每次调用只有**一次**递归调用 → 时间 O(n)，栈空间 O(n)。

---

## 3. Integer Exponentiation (Fast Power) | 整数幂运算（快速幂）

### 3.1 Naive version | 朴素版本

```c
long power(int base, int exp)
{
    if (exp == 0) return 1;                 // base case
    return base * power(base, exp - 1);     // recursive case
}
```

- Time: O(exp). Linear recursion on the exponent.

### 3.2 Fast (divide-and-conquer) version | 快速幂（分治版）

```c
#include <stdio.h>

long power_fast(int base, int exp)
{
    if (exp == 0) return 1;
    long half = power_fast(base, exp / 2);
    if (exp % 2 == 0)
        return half * half;                 // even exponent
    return base * half * half;             // odd exponent
}

int main(void)
{
    printf("2^10 = %ld\n", power_fast(2, 10));
    printf("3^5  = %ld\n", power_fast(3, 5));
    return 0;
}
```

**English**
- Halve the exponent on each call → **O(log exp)** time and **O(log exp)** stack.
- Split by even/odd exponent: `x^(2k) = (x^k)²`, `x^(2k+1) = x * (x^k)²`.

**中文**
- 每次调用将指数减半 → 时间 **O(log exp)**，栈空间 **O(log exp)**。
- 按指数奇偶分两种情形：`x^(2k) = (x^k)²`，`x^(2k+1) = x * (x^k)²`。

---

## 4. Tower of Hanoi (Divide and Conquer) | 汉诺塔（分治递归）

**English**

**Rules**:

1. Move `n` disks from `A` to `C` using `B` as auxiliary.
2. A move carries the top disk from one peg to another.
3. A larger disk may **never** sit on top of a smaller disk.

**Recursive solution**:

- Move the top `n - 1` disks from `A` to **B** using `C`.
- Move the largest disk from `A` to `C`.
- Move the `n - 1` disks from `B` to `C` using `A`.

Number of moves: `T(n) = 2·T(n-1) + 1 = 2ⁿ − 1`.

**中文**

**规则**：

1. 将 `n` 个盘子从 `A` 借助 `B` 移到 `C`。
2. 每次移动将一个柱顶盘子移到另一个柱顶。
3. 大盘子**永远不能**放在小盘子之上。

**递归解法**：

- 将上面的 `n - 1` 个盘子从 `A` 借助 `C` 移到 **B**。
- 将最大的盘子从 `A` 移到 `C`。
- 将那 `n - 1` 个盘子从 `B` 借助 `A` 移到 `C`。

总步数：`T(n) = 2·T(n-1) + 1 = 2ⁿ − 1`。

```c
#include <stdio.h>

void hanoi(int n, char from, char via, char to)
{
    if (n == 0) return;                            // base case
    hanoi(n - 1, from, to, via);                  // step 1: A -> B (via C)
    printf("Move disk %d: %c -> %c\n", n, from, to);  // step 2: largest -> C
    hanoi(n - 1, via, from, to);                  // step 3: B -> C (via A)
}

int main(void)
{
    hanoi(3, 'A', 'B', 'C');
    return 0;
}
```

---

## 5. Tail Recursion (Concept) | 尾递归（概念）

**English**

A call is **tail-recursive** if the recursive call is the **very last** action before return, with no further computation needed. Many compilers transform optimized tail recursion into a loop, reducing stack usage to **O(1)**.

```c
#include <stdio.h>

long fact_tail(int n, long acc)
{
    if (n <= 1) return acc;               // base case returns accumulator
    return fact_tail(n - 1, n * acc);     // tail call: result IS the recursive call
}

int main(void)
{
    printf("5! = %ld\n", fact_tail(5, 1));
    return 0;
}
```

**中文**

若递归调用是返回前的**最后一步**、之后再无额外运算，则称为**尾递归**。许多编译器会将优化后的尾递归转写为循环，使栈空间降为 **O(1)**。

```c
#include <stdio.h>

long fact_tail(int n, long acc)
{
    if (n <= 1) return acc;               // 基本情况返回累加器
    return fact_tail(n - 1, n * acc);     // 尾调用：结果即递归调用
}

int main(void)
{
    printf("5! = %ld\n", fact_tail(5, 1));
    return 0;
}
```

---

## 6. Key Takeaways | 要点

**English**
- Recursion patterns: **linear**, **tail**, **divide-and-conquer**.
- Fast exponentiation halves the problem → O(log exp).
- Tower of Hanoi: classic divide-and-conquer with exponential move count `2ⁿ − 1`.
- Tail recursion can be optimized to constant stack space.

**中文**
- 递归形态：**线性**、**尾递归**、**分治**。
- 快速幂将问题规模减半 → O(log exp)。
- 汉诺塔是经典的分治递归，移动次数为指数级 `2ⁿ − 1`。
- 尾递归可优化为 O(1) 栈空间。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `array_sum.c` | Recursive sum of an array | 数组求和（递归） |
| `power.c` | Fast exponentiation (divide and conquer) | 快速幂（分治递归） |
| `hanoi.c` | Tower of Hanoi | 汉诺塔 |
| `tail_factorial.c` | Tail-recursive factorial | 尾递归阶乘 |
| `day-20-summary.md` | Day 20 notes | 第二十天学习笔记 |