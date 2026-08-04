# Day 10: Intro to Pointers | 指针入门

> A bilingual (English / 中文) walkthrough of Day 10.
> 本节为第十天的双语概念讲解。

---

## 1. What is a Pointer? | 什么是指针？

**English**

Pointers are variables that **store memory addresses**. In C you use the `*` operator to declare a pointer and the `&` operator to obtain the address of a variable.

```c
int x = 10;
int *p = &x; // p stores the address of x
```

Use `*p` to access the value at the address stored in `p` — this is called **dereferencing**.

**中文**

指针是一种**存储内存地址**的变量。在 C 中使用 `*` 运算符声明指针，使用 `&` 运算符获取变量的地址。

```c
int x = 10;
int *p = &x; // p 存储 x 的地址
```

使用 `*p` 访问 `p` 所存地址处的值 —— 这称为**解引用**。

---

## 2. Key Concepts | 核心概念

**English**

- `&x` is the **address** of `x`.
- `*p` is the **value** pointed to by `p`.
- `int *p` declares a **pointer to an int**.

**中文**

- `&x` 是 `x` 的**地址**。
- `*p` 是 `p` 所指向的**值**。
- `int *p` 声明一个**指向 int 型的指针**。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `ptr101.c` | Basic pointer usage | 指针基础用法 |
| `day-10-summary.md` | Day 10 notes | 第十天学习笔记 |