# Day 30: Miscellaneous | 杂项

> A bilingual (English / 中文) walkthrough of Day 30.
> 本节为第三十天的双语概念讲解。

---

## 1. Overview | 概述

**English**

The final day wraps up with three C topics that didn't fit earlier but are essential in real code:

- **Bitwise operators** — direct manipulation of bits.
- **`union`** — a type whose members share the same storage.
- **The preprocessor** — `#define`, `#include`, conditional compilation, macros.

**中文**

最后一天补上三个之前未涉及、但实际开发中必不可少的 C 主题：

- **位运算符** —— 直接按位操作。
- **`union`（联合体）** —— 多个成员共享同一块存储。
- **预处理器** —— `#define`、`#include`、条件编译、宏。

---

## 2. Bitwise Operators | 位运算符

**English**

| Operator | Name | Example |
|----------|------|---------|
| `&`  | AND  | `0b1100 & 0b1010 == 0b1000` |
| `\|` | OR   | `0b1100 \| 0b1010 == 0b1110` |
| `^`  | XOR  | `0b1100 ^ 0b1010 == 0b0110` |
| `~`  | NOT  | `~0b00001111 == 0b...11110000` |
| `<<` | left shift | `1 << 3 == 8` |
| `>>` | right shift (arithmetic for signed) | `8 >> 2 == 2` |

Common idioms: set a bit (`x |= (1 << n)`), clear (`x &= ~(1 << n)`), toggle (`x ^= (1 << n)`), test (`x & (1 << n)`).

**中文**

| 运算符 | 名称 | 示例 |
|--------|------|------|
| `&`  | 与  | `0b1100 & 0b1010 == 0b1000` |
| `\|` | 或  | `0b1100 \| 0b1010 == 0b1110` |
| `^`  | 异或 | `0b1100 ^ 0b1010 == 0b0110` |
| `~`  | 非  | `~0b00001111 == 0b...11110000` |
| `<<` | 左移 | `1 << 3 == 8` |
| `>>` | 右移（有符号数为算术右移） | `8 >> 2 == 2` |

常用技巧：置位 `x |= (1 << n)`、清零 `x &= ~(1 << n)`、翻转 `x ^= (1 << n)`、测试 `x & (1 << n)`。

```c
#include <stdio.h>

int main(void)
{
    unsigned int x = 0b1100;          /* 12 */

    printf("x       = %u\n", x);
    printf("x & 10  = %u\n", x & 0b1010);
    printf("x | 10  = %u\n", x | 0b1010);
    printf("x ^ 10  = %u\n", x ^ 0b1010);
    printf("x << 2  = %u\n", x << 2);
    printf("x >> 1  = %u\n", x >> 1);

    /* set / clear / toggle / test bit 3 of 0 */
    unsigned int flags = 0;
    flags |=  (1u << 3);   printf("set    bit 3: %u\n", flags);   /* 8  */
    flags ^=  (1u << 3);   printf("toggle bit 3: %u\n", flags);   /* 0  */
    flags |=  (1u << 3);
    flags &= ~(1u << 3);   printf("clear  bit 3: %u\n", flags);   /* 0  */
    return 0;
}
```

---

## 3. Unions | 联合体

**English**

A `union` is like a `struct`, but **all members share the same starting address** — only one member is "active" at a time. The size of a union equals the size of its largest member. Useful for type tagging, interpreting the same bits in different ways, and saving memory.

**中文**

`union` 类似 `struct`，但**所有成员共享同一起始地址** —— 同一时刻只有一个成员是"有效的"。联合体的大小等于其最大成员的大小。常用于类型标签、以不同方式解释同一段比特、节省内存。

```c
#include <stdio.h>

union Value {
    int    i;
    float  f;
    char   bytes[4];
};

int main(void)
{
    union Value v;
    v.f = 1.0f;
    printf("as float: %f\n", v.f);

    v.i = 0x41414141;
    printf("as int  : %d (0x%X)\n", v.i, v.i);
    printf("as bytes: %c%c%c%c\n",
           v.bytes[0], v.bytes[1], v.bytes[2], v.bytes[3]);

    printf("sizeof(union Value) = %zu\n", sizeof(union Value));
    return 0;
}
```

**English**
- Writing through one member and reading another is **implementation-defined** behavior in C, but commonly used for low-level bit inspection.
- `sizeof(union Value)` is the size of the largest member (here, 4 bytes).

**中文**
- 通过一个成员写入、再通过另一个成员读出在 C 中是**实现定义**行为，但常用于底层位检视。
- `sizeof(union Value)` 取最大成员的大小（本例为 4 字节）。

---

## 4. The Preprocessor | 预处理器

**English**

The preprocessor runs **before** the compiler. It handles:

- `#include <file>` / `#include "file"` — paste the contents of a header.
- `#define NAME value` — symbolic constants.
- `#define NAME(params) body` — function-like macros.
- `#ifdef / #ifndef / #endif / #if` — conditional compilation.
- `#pragma` — implementation-specific directives (e.g., `#pragma once`).

**中文**

预处理器在编译器之前运行，负责：

- `#include <file>` / `#include "file"` —— 把头文件内容粘贴进来。
- `#define NAME value` —— 符号常量。
- `#define NAME(参数) 函数体` —— 类函数宏。
- `#ifdef / #ifndef / #endif / #if` —— 条件编译。
- `#pragma` —— 实现相关的指令（如 `#pragma once`）。

```c
#include <stdio.h>

#define PI          3.14159
#define SQUARE(x)   ((x) * (x))     /* always parenthesize macro args! */
#define MAX(a, b)   ((a) > (b) ? (a) : (b))

#if defined(DEBUG)
    #define LOG(msg)  printf("[debug] %s\n", msg)
#else
    #define LOG(msg)  ((void)0)
#endif

int main(void)
{
    printf("PI       = %.5f\n", PI);
    printf("SQUARE(5)= %d\n", SQUARE(5));
    printf("MAX(3,7) = %d\n", MAX(3, 7));
    LOG("hello");
    return 0;
}
```

**English**
- Always **parenthesize** macro parameters and the whole body to avoid operator-precedence surprises.
- Macros have **no type checking** and can evaluate arguments more than once (`MAX(i++, j++)` is dangerous).
- Use `inline` functions in modern C when you need type safety.

**中文**
- 始终给宏参数和整个宏体**加括号**，避免运算符优先级带来的意外。
- 宏**没有类型检查**，且可能多次求值参数（`MAX(i++, j++)` 是危险的）。
- 需要类型安全时，现代 C 建议使用 `inline` 函数。

---

## 5. Key Takeaways | 要点

**English**
- Bitwise operators give full control over individual bits — essential for flags, masks, and low-level I/O.
- Unions share storage between members; great for memory-constrained code and tagged values, but rely on implementation-defined reinterpretation.
- The preprocessor runs before compilation; macros and conditional compilation are powerful but lack type safety — prefer `const` and `inline` where possible.

**中文**
- 位运算符可对每一位进行控制 —— 对标志位、掩码、底层 I/O 至关重要。
- 联合体让多个成员共享存储；适合内存受限场景和带标签的值，但依赖实现定义的重解释。
- 预处理器在编译前运行；宏和条件编译很强大但缺乏类型安全 —— 尽量使用 `const` 和 `inline`。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `bitwise.c` | Bitwise operators demo | 位运算符演示 |
| `union_demo.c` | Union type demo | 联合体演示 |
| `preprocessor.c` | Macros and conditional compilation | 宏与条件编译 |
| `day-30-summary.md` | Day 30 notes | 第三十天学习笔记 |