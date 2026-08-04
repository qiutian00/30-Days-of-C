# Day 18: Problems on Strings | 字符串问题练习

> A bilingual (English / 中文) walkthrough of Day 18.
> 本节为第十八天的双语概念讲解。

---

## 1. Overview | 概述

**English**

This day focuses on **practicing string manipulation** by implementing, from scratch, three common string operations without using `<string.h>`:
1. Compute the **length** of a string.
2. Convert a string to **uppercase**.
3. Convert a string to **lowercase**.

The exercises rely on two fundamentals: the **null terminator** (`'\0'`) that marks the end of a C string, and the **ASCII** encoding where lowercase and uppercase letters differ by a constant offset.

**中文**

本节通过从零开始实现三个常用字符串操作（不使用 `<string.h>`）来**练习字符串处理**：
1. 计算字符串的**长度**。
2. 将字符串转换为**大写**。
3. 将字符串转换为**小写**。

这些练习基于两个基础：标记 C 字符串结束的**空终止符**（`'\0'`），以及**ASCII** 编码中小写字母与大写字母相差一个固定偏移量的事实。

---

## 2. Computing String Length | 计算字符串长度

```c
#include <stdio.h>
#include <ctype.h>

int main()
{
    char my_str[] = "CODING";
    int i;
    for (i = 0; my_str[i] != '\0'; i++);
    printf("Length of string: %d", i);
    return 0;
}
```

**English**
- The loop walks through the array until it reaches the null terminator `'\0'`.
- The final value of `i` is the number of characters **before** the terminator, i.e., the string length.

**中文**
- 循环遍历数组直到遇到空终止符 `'\0'`。
- 结束时 `i` 的值即终止符**之前**的字符数，也就是字符串长度。

---

## 3. Converting to Uppercase | 转大写

```c
#include <stdio.h>
#include <ctype.h>

int main()
{
    char my_str[] = "coding36";
    int i;
    for (i = 0; my_str[i] != '\0'; i++)
    {
        if (isalpha(my_str[i]))
            my_str[i] -= 32;
    }
    printf("Result: %s", my_str);
    return 0;
}
```

**English**
- `isalpha()` checks whether the character is a letter (so digits/punctuation are skipped).
- In ASCII, the difference between a lowercase letter and its uppercase counterpart is `32` (`'a' - 'A' == 32`). Subtracting `32` maps `'a'` to `'A'`, etc.

**中文**
- `isalpha()` 判断字符是否为字母（数字和标点被跳过）。
- 在 ASCII 中，小写字母与其大写形式相差 `32`（`'a' - 'A' == 32`）。减去 `32` 即可将 `'a'` 映射到 `'A'`，依此类推。

> **Tip | 提示**: Prefer the portable functions `toupper()` / `tolower()` from `<ctype.h>` in real code.
> 实际开发中推荐使用 `<ctype.h>` 中可移植的 `toupper()` / `tolower()`。

---

## 4. Converting to Lowercase | 转小写

```c
#include <stdio.h>
#include <ctype.h>

int main()
{
    char my_str[] = "CODING36";
    int i;
    for (i = 0; my_str[i] != '\0'; i++)
    {
        if (isalpha(my_str[i]))
            my_str[i] += 32;
    }
    printf("Result: %s", my_str);
    return 0;
}
```

**English**
- The mirror image of the uppercase version: add `32` to move from uppercase to lowercase.
- `isalpha()` again ensures we only modify alphabetic characters.

**中文**
- 与转大写相反：加 `32` 即从大写变为小写。
- `isalpha()` 同样确保只修改字母字符。

---

## 5. Key Takeaways | 要点

**English**
- C strings are **null-terminated** char arrays; walking until `'\0'` is the canonical traversal pattern.
- ASCII letters in opposite cases differ by `32`; portable code should use `toupper()`/`tolower()`.
- Always be careful to keep within the array bounds — never overwrite the trailing `'\0'`.

**中文**
- C 字符串是**以空字符结尾**的字符数组；遍历到 `'\0'` 是标准的遍历模式。
- ASCII 中大小写字母相差 `32`；可移植代码应使用 `toupper()`/`tolower()`。
- 始终注意不要越过数组边界 —— 切勿覆盖末尾的 `'\0'`。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `strLength.c` | Compute string length without `<string.h>` | 不使用 `<string.h>` 计算字符串长度 |
| `toUpper.c` | Convert a string to uppercase | 将字符串转换为大写 |
| `toLower.c` | Convert a string to lowercase | 将字符串转换为小写 |
| `content.md` | Day 18 notes (to be filled in) | 第十八天学习笔记（待补充） |