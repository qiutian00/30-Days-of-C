# Day 9: Intro to Memory Allocation | 内存分配入门

> A bilingual (English / 中文) walkthrough of Day 9.
> 本节为第九天的双语概念讲解。

---

## 1. Overview | 概述

**English**

Memory allocation in C allows dynamic allocation and deallocation of memory at runtime using functions from `<stdlib.h>`.

**中文**

C 语言通过 `<stdlib.h>` 中的函数，可以在运行时动态分配和释放内存。

---

## 2. Memory Allocation Functions | 内存分配函数

### a) `malloc`

**English**

- Syntax: `ptr = (type*)malloc(size_in_bytes);`
- Allocates **uninitialized** memory.
- Returns `NULL` if allocation fails.

**中文**

- 语法：`ptr = (type*)malloc(size_in_bytes);`
- 分配**未初始化**的内存。
- 分配失败时返回 `NULL`。

---

### b) `calloc`

**English**

- Syntax: `ptr = (type*)calloc(num_elements, size_of_each);`
- Allocates memory and **initializes it to zero**.
- Returns `NULL` if allocation fails.

**中文**

- 语法：`ptr = (type*)calloc(num_elements, size_of_each);`
- 分配内存并**将其初始化为零**。
- 分配失败时返回 `NULL`。

---

### c) `realloc`

**English**

- Syntax: `ptr = (type*)realloc(ptr, new_size_in_bytes);`
- **Resizes** previously allocated memory.
- Can return `NULL` if resizing fails.

**中文**

- 语法：`ptr = (type*)realloc(ptr, new_size_in_bytes);`
- **调整**之前已分配内存的大小。
- 调整失败时可能返回 `NULL`。

---

### d) `free`

**English**

- Syntax: `free(ptr);`
- Releases dynamically allocated memory.
- Set `ptr = NULL;` after freeing to avoid a **dangling pointer**.

**中文**

- 语法：`free(ptr);`
- 释放动态分配的内存。
- 释放后应将 `ptr` 设为 `NULL`，以避免产生**悬空指针**。

---

## 3. Common Issues | 常见问题

**English**

- **Memory leaks (内存泄漏)**: forgetting to `free()` memory.
- **Dangling pointers (悬空指针)**: using memory after it has been `free()`d.
- **Double free (重复释放)**: calling `free()` on memory that has already been freed.

**中文**

- **内存泄漏**：忘记调用 `free()` 释放内存。
- **悬空指针**：在内存被 `free()` 之后仍继续使用。
- **重复释放**：对已经释放过的内存再次调用 `free()`。

---

## 4. Best Practices | 最佳实践

**English**

- Always check whether memory allocation succeeded.
- Free memory when it is no longer needed.
- Use `calloc` when you need zero-initialized memory.
- Set pointers to `NULL` after freeing them.

**中文**

- 务必检查内存分配是否成功。
- 内存不再使用时应及时释放。
- 当需要零初始化的内存时使用 `calloc`。
- 释放内存后把指针置为 `NULL`。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `malloc_example.c` | Using `malloc` | `malloc` 使用示例 |
| `calloc_example.c` | Using `calloc` | `calloc` 使用示例 |
| `realloc_example.c` | Using `realloc` | `realloc` 使用示例 |
| `using_free.c` | Releasing memory with `free` | 用 `free` 释放内存 |
| `day-9-summary.md` | Day 9 notes | 第九天学习笔记 |