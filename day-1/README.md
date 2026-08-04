# Day 1: Basics of C Programming | C 语言基础

> A bilingual (English / 中文) walkthrough of the first day's concepts.
> 本节为第一天的双语概念讲解。

---

## 1. The Canonical "Hello, World" | 经典的 "Hello, World"

```c
#include <stdio.h>

int main()
{
    printf("C is cool!\n");
    return 0;
}
```

**English**
- `#include` is a **preprocessor directive** that makes the contents of `stdio.h` available before compilation.
- `< >` tells the compiler to look for `stdio.h` in the **system** include directory.
- `int` is the **return type** of `main`. The type of the value a function returns precedes its name.
- `main` is the entry point; execution starts here.
- `()` indicates `main` takes no arguments in this form.
- `{}` delimits a **block** of code.
- `printf` prints the character string passed as its argument.
- `;` terminates every C statement.
- `return 0;` signals successful execution.

**中文**
- `#include` 是**预处理指令**，在编译前将 `stdio.h` 的内容引入当前源文件。
- `< >` 表示在**系统**头文件目录中查找 `stdio.h`。
- `int` 是 `main` 的**返回类型**。函数返回值的类型写在函数名之前。
- `main` 是程序的入口，执行从这里开始。
- 此处的 `()` 表示这种形式的 `main` 不接受参数。
- `{}` 用于界定一个**代码块**。
- `printf` 将作为参数传入的字符串输出到标准输出。
- `;` 是每条 C 语句的结束符。
- `return 0;` 表示程序正常结束。

---

## 2. Command-Line Arguments | 命令行参数

```c
int main(int argc, char **argv)
```

**English**

Run the program from the shell as: `ProgramName arg1 arg2 arg3` (args separated by spaces).

- `argc`: the **number** of command-line arguments.
- `argv`: an **argument vector** — a pointer to an array of character-string arguments.

**中文**

在命令行中按如下方式运行程序：`ProgramName arg1 arg2 arg3`（参数以空格分隔）。

- `argc`：命令行参数的**个数**。
- `argv`：**参数向量** —— 指向字符串参数数组的指针。

---

## 3. Output: `printf()` vs `puts()` | 输出函数对比

```c
puts("Print a simple string");
printf("Print a formatted string");
```

**English**

- Inside `printf()`, **format specifiers** (such as `%d`, `%s`) are replaced by the corresponding values supplied as a comma-delimited list.
- The number and type of values must match the format specifiers in the string.

```c
printf("I have been coding in %s for %d years now\n", "C", 2);
```

**中文**

- 在 `printf()` 中，**格式说明符**（如 `%d`、`%s`）会被以逗号分隔的对应值列表依次替换。
- 值的个数与类型必须与字符串中的格式说明符一一对应。

```c
printf("I have been coding in %s for %d years now\n", "C", 2);
```

---

## 4. Comments | 注释

```c
// This is a single-line comment

/* This is a multi-line
   comment that spans
   multiple lines */
```

**English**

Comment your code to improve readability; the compiler ignores everything inside comments.

**中文**

为代码添加注释可以提升可读性；编译器会忽略注释内的所有内容。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `1-hello_world_args.c` | Basic program with command-line arguments | 带命令行参数的基础程序示例 |
| `2-print.c` | Demonstrates `printf()` usage | 演示 `printf()` 的用法 |
| `day1-summary.md` | Day 1 notes | 第一天学习笔记 |