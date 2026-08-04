# Day 11: Addresses and Indirection — Part 1 | 地址与间接寻址（一）

> A bilingual (English / 中文) walkthrough of Day 11.
> 本节为第十一天的双语概念讲解。

---

## 1. Pointers and Addresses | 指针与地址

**English**

A pointer is a variable that stores the **memory address** of another variable.

```c
int *ptr;
```

This declares `ptr` as a pointer to an integer.

**中文**

指针是存储另一个变量**内存地址**的变量。

```c
int *ptr;
```

此处将 `ptr` 声明为指向整型的指针。

---

## 2. Address-of Operator (`&`) | 取地址运算符

**English**

The `&` operator returns the **address** of a variable.

```c
int a = 10;
int *ptr = &a;
```

**中文**

`&` 运算符返回变量的**地址**。

```c
int a = 10;
int *ptr = &a;
```

---

## 3. Dereferencing Operator (`*`) | 解引用运算符

**English**

The `*` operator accesses the **value** at the address stored in a pointer.

```c
int a = 10;
int *ptr = &a;
printf("%d", *ptr); // prints 10
```

**中文**

`*` 运算符访问指针所存地址处的**值**。

```c
int a = 10;
int *ptr = &a;
printf("%d", *ptr); // 输出 10
```

---

## 4. Passing by Reference | 按引用传递

**English**

You can pass the **address** of a variable to a function, allowing the function to modify the original value. This is also called **pass by reference**.

**中文**

可以将变量的**地址**传给函数，使函数能够修改原始变量的值。这也称为**按引用传递**。

---

## 5. Pointer to Pointer | 指向指针的指针

**English**

A pointer can also store the address of **another pointer**.

```c
int **pp;
```

`pp` is a pointer to a pointer to an integer.

**中文**

指针也可以存储**另一个指针**的地址。

```c
int **pp;
```

`pp` 是一个指向"指向整型的指针"的指针。

---

## 6. Code Example 1: Increment a Value Using a Pointer | 示例 1：用指针递增一个值

```c
#include <stdio.h>

void increment(int *ptr) {
    *ptr = *ptr + 1;
}

int main() {
    int a = 5;
    printf("Before increment: %d\n", a);
    increment(&a);
    printf("After increment: %d\n", a);
    return 0;
}
```

**English**
- `increment()` receives a pointer to `a` and increases its value.
- The original variable `a` is modified in `main()`.

**中文**
- `increment()` 接收指向 `a` 的指针，并对其值加 1。
- `main()` 中的原始变量 `a` 被修改。

---

## 7. Code Example 2: Pointer to Pointer | 示例 2：指向指针的指针

```c
#include <stdio.h>

int main() {
    int a = 10;
    int *p = &a;
    int **pp = &p;

    printf("Value of a: %d\n", a);
    printf("Value via *p: %d\n", *p);
    printf("Value via **pp: %d\n", **pp);

    printf("Address of a: %p\n", &a);
    printf("Address stored in p: %p\n", p);
    printf("Address of p: %p\n", &p);
    printf("Address stored in pp: %p\n", pp);

    return 0;
}
```

**English**
- `*p` accesses the value of `a`.
- `**pp` accesses the value of `a` through a pointer-to-pointer.
- The program prints both values and addresses to help understand the memory relationships.

**中文**
- `*p` 访问 `a` 的值。
- `**pp` 通过指向指针的指针访问 `a` 的值。
- 程序同时输出值和地址，帮助理解内存之间的关系。

---

## 8. Summary | 小结

**English**
- A pointer holds the address of another variable.
- Use the `&` operator to get the address and the `*` operator to access the value at that address.
- Functions can modify variables by receiving their addresses.
- Pointer-to-pointer (`int **pp`) lets you indirectly access or modify pointers.

**中文**
- 指针存放另一个变量的地址。
- 用 `&` 运算符取地址，用 `*` 运算符访问该地址处的值。
- 函数通过接收变量的地址即可修改该变量。
- 指向指针的指针（`int **pp`）可以间接访问或修改指针。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `ptr_examples.c` | Pointer usage examples 1 | 指针用法示例 1 |
| `ptr_examples_1.c` | Pointer usage examples 2 | 指针用法示例 2 |
| `day-11-summary.md` | Day 11 notes | 第十一天学习笔记 |