# Day 15: Working with Pointers Carefully | 谨慎地使用指针

> A bilingual (English / 中文) walkthrough of Day 15.
> 本节为第十五天的双语概念讲解。

---

## 1. Overview | 概述

**English**

Pointers are powerful but easy to misuse. This day focuses on the common **pitfalls** of pointer usage and how to use pointers **safely** and correctly — a critical topic in C programming.

**中文**

指针功能强大但极易误用。本节聚焦于指针使用中的常见**陷阱**以及如何**安全**、正确地使用指针 —— 这是 C 语言中至关重要的主题。

---

## 2. Common Pointer Pitfalls | 常见指针陷阱

**English**

- **Uninitialized pointers**: reading or dereferencing a pointer before it has been assigned a valid address leads to undefined behavior.
- **Dangling pointers**: a pointer that still references memory after it has been `free()`d or after the pointed-to variable has gone out of scope.
- **Null pointers**: always check whether a pointer is `NULL` (e.g., from `malloc()`) before dereferencing it.
- **Pointer arithmetic errors**: going beyond the bounds of an array leads to out-of-bounds access.
- **Double free**: calling `free()` on the same block twice corrupts the allocator's data structures.
- **Memory leaks**: forgetting to `free()` memory that is no longer needed.
- **Type mismatches**: dereferencing a `void *` (or a wrongly typed pointer) without a correct cast yields incorrect results.

**中文**

- **未初始化指针**：在赋予有效地址前读取或解引用指针会导致未定义行为。
- **悬空指针**：在内存被 `free()` 释放、或所指向变量已离开作用域后，指针仍指向该内存。
- **空指针**：解引用指针（如 `malloc()` 的返回值）前务必检查其是否为 `NULL`。
- **指针运算越界**：超出数组范围即造成越界访问。
- **重复释放**：对同一块内存调用两次 `free()` 会破坏分配器的数据结构。
- **内存泄漏**：忘记释放不再使用的内存。
- **类型不匹配**：对 `void *`（或类型错误的指针）未正确转换就解引用，会得到错误结果。

---

## 3. Safe Pointer Practices | 安全使用指针的实践

**English**

- Initialize pointers at declaration — to `NULL` if you don't yet have a valid address.
- Check for `NULL` before dereferencing, especially for values returned by `malloc`/`calloc`/`realloc`.
- After `free(p)`, set `p = NULL;` so that a later accidental `free(p)` is a harmless no-op.
- Keep pointer arithmetic within array bounds; prefer `size_t` for sizes and indices.
- Use `const` qualifiers to prevent unintended modifications through a pointer.
- Always pair each `malloc`/`calloc`/`realloc` with exactly one `free`.

**中文**

- 声明指针时就初始化 —— 若暂无有效地址，先置为 `NULL`。
- 解引用前检查是否为 `NULL`，尤其是 `malloc`/`calloc`/`realloc` 的返回值。
- `free(p)` 之后执行 `p = NULL;`，这样后续误调 `free(p)` 也不会有副作用。
- 指针运算保持在数组边界内；大小与下标优先使用 `size_t` 类型。
- 使用 `const` 限定符避免通过指针意外修改数据。
- 每个 `malloc`/`calloc`/`realloc` 都要恰好对应一次 `free`。

---

## 4. Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `day-15-summary.md` | Day 15 notes (to be filled in) | 第十五天学习笔记（待补充） |