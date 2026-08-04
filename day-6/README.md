# Day 6: Variable Scope and Header Files | 变量作用域与头文件

> A bilingual (English / 中文) walkthrough of Day 6.
> 本节为第六天的双语概念讲解。

---

## 1. Header Files in C | C 语言中的头文件

**English**

Let's parse `#include <stdio.h>`:

- `#include` tells the compiler to make the contents of `stdio.h` available.
- `< >` tells the compiler to search for this file in the location reserved for **standard library** files.

Include a standard library header:

```c
#include <fileName>
```

Include a header file from the current directory / current project:

```c
#include "fileName"
```

### Header files and the C compiler — the process

The preprocessor replaces each `#include` with the contents of the named file **before** actual compilation, so the compiler sees one large translation unit.

**中文**

解析 `#include <stdio.h>`：

- `#include` 告诉编译器将 `stdio.h` 的内容引入当前源文件。
- `< >` 表示在为**标准库**文件保留的目录中查找该文件。

引入标准库头文件：

```c
#include <fileName>
```

引入当前目录或当前项目中的头文件：

```c
#include "fileName"
```

### 头文件与 C 编译器 —— 流程

预处理器会在真正编译**之前**，把每个 `#include` 替换为对应文件的内容，因此编译器实际上看到的是一个大的翻译单元。

---

## 2. Scope of a Variable | 变量的作用域

**English**

The **scope** of a variable is the region of the program in which the variable is accessible.

**中文**

变量的**作用域**是指程序中可以访问该变量的区域。

---

### 2.1 Local Scope — Nested Block | 局部作用域 —— 嵌套块

**English**

```c
{
    /*OUTER BLOCK*/

    {
        /*INNER BLOCK*/
        // contents of the outer block just before this block
        // CAN be accessed here
    }

    // contents of the inner block are NOT accessible here
}
```

An inner block can see variables declared before it in the enclosing (outer) block, but the outer block cannot see variables declared inside an inner block.

**中文**

```c
{
    /*外层块*/

    {
        /*内层块*/
        // 在本块开始之前外层块中声明的内容
        // 在此可以访问
    }

    // 内层块中的内容在此处不可访问
}
```

内层块可以访问其外层块中在此之前声明的变量，但外层块无法访问内层块中声明的变量。

---

### 2.2 Local Scope — Different Blocks | 局部作用域 —— 不同块

**English**

```c
{
    /*BLOCK 1*/
    // contents of BLOCK 2 cannot be accessed here
}

{
    /*BLOCK 2*/
    // contents of BLOCK 1 cannot be accessed here
}
```

Sibling blocks cannot access each other's variables.

**中文**

```c
{
    /*块 1*/
    // 此处无法访问块 2 的内容
}

{
    /*块 2*/
    // 此处无法访问块 1 的内容
}
```

并列的代码块之间无法互相访问彼此的变量。

---

### 2.3 Global Scope | 全局作用域

**English**

```c
// all global variables are declared here
function1()
{
    // all global variables can be accessed inside function1
}
function2()
{
    // all global variables can be accessed inside function2
}
```

Global variables are declared **outside** any function and are visible to every function declared **after** them in the file.

**中文**

```c
// 所有全局变量在此声明
function1()
{
    // 在 function1 内可以访问所有全局变量
}
function2()
{
    // 在 function2 内可以访问所有全局变量
}
```

全局变量声明在**任何函数之外**，对文件中其声明**之后**的所有函数均可见。

---

### 2.4 Static Functions and Static Variables | 静态函数与静态变量

**English**

- A **static variable** inside a function retains its value between calls; it is initialized only once.
- A **static function** or a **static global variable** is visible only within the translation unit (file) in which it is defined — it cannot be referenced from other files via `extern`.

**中文**

- 函数内的**静态变量**（static variable）在多次调用之间保留其值，且只被初始化一次。
- **静态函数**或**静态全局变量**仅在定义它的翻译单元（文件）内可见，无法通过 `extern` 从其他文件引用。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `global-scope.c` | Demonstrates global variables | 演示全局变量 |
| `local-scope-1.c` | Local scope example 1 | 局部作用域示例 1 |
| `local-scope-2.c` | Local scope example 2 | 局部作用域示例 2 |
| `local-scope-3.c` | Local scope example 3 | 局部作用域示例 3 |
| `day-6-summary.md` | Day 6 notes | 第六天学习笔记 |