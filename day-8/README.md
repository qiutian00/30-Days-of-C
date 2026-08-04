# Day 8: Working with Files | 文件操作

> A bilingual (English / 中文) walkthrough of Day 8.
> 本节为第八天的双语概念讲解。

---

## 1. Overview | 概述

**English**

File handling in C allows you to read, write, and manipulate files efficiently. The standard library provides functions for handling files through `FILE *` pointers.

**中文**

C 语言的文件操作可以高效地读取、写入和处理文件。标准库提供了一组通过 `FILE *` 指针操作文件的函数。

---

## 2. Opening and Closing Files | 打开与关闭文件

**English**

To work with a file, open it with `fopen()` and **always** close it with `fclose()`:

```c
FILE *file = fopen("filename.txt", "mode");
fclose(file);
```

Modes:

- `"r"`  — Read
- `"w"`  — Write (overwrites the file)
- `"a"`  — Append
- `"rb"`, `"wb"`, `"ab"` — Binary modes

**中文**

操作文件时用 `fopen()` 打开，并**务必**用 `fclose()` 关闭：

```c
FILE *file = fopen("filename.txt", "mode");
fclose(file);
```

打开模式：

- `"r"`  —— 读取
- `"w"`  —— 写入（会覆盖原文件）
- `"a"`  —— 追加
- `"rb"`、`"wb"`、`"ab"` —— 二进制模式

---

## 3. Writing to a File | 写入文件

**English**

Use `fprintf()` or `fwrite()`:

```c
fprintf(file, "Hello, File Handling!");
```

**中文**

使用 `fprintf()` 或 `fwrite()`：

```c
fprintf(file, "Hello, File Handling!");
```

---

## 4. Reading from a File | 读取文件

**English**

Use `fscanf()`, `fgets()`, or `fread()`:

```c
char buffer[100];
fgets(buffer, 100, file);
printf("Read: %s", buffer);
```

**中文**

使用 `fscanf()`、`fgets()` 或 `fread()`：

```c
char buffer[100];
fgets(buffer, 100, file);
printf("Read: %s", buffer);
```

---

## 5. Appending to a File | 追加内容

**English**

Open in `"a"` mode and use `fprintf()`:

```c
fprintf(file, "Appending new data\n");
```

**中文**

以 `"a"` 模式打开，并使用 `fprintf()`：

```c
fprintf(file, "Appending new data\n");
```

---

## 6. Binary File Operations | 二进制文件操作

**English**

Use `fwrite()` and `fread()`:

```c
struct Data { int id; char name[20]; } d;
fwrite(&d, sizeof(struct Data), 1, file);
```

**中文**

使用 `fwrite()` 和 `fread()`：

```c
struct Data { int id; char name[20]; } d;
fwrite(&d, sizeof(struct Data), 1, file);
```

---

## 7. Error Handling | 错误处理

**English**

Always check whether `fopen()` succeeded:

```c
if (file == NULL) {
    printf("Error opening file!\n");
    return 1;
}
```

**中文**

务必检查 `fopen()` 是否成功：

```c
if (file == NULL) {
    printf("Error opening file!\n");
    return 1;
}
```

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `read_file.c` | Reading from a file | 从文件读取数据 |
| `write_file.c` | Writing to a file | 向文件写入数据 |
| `append_to_file.c` | Appending data to a file | 向文件追加数据 |
| `binary_file_example.c` | Binary file read/write | 二进制文件读写示例 |
| `day-8-summary.md` | Day 8 notes | 第八天学习笔记 |