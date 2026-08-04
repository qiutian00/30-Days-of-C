# Day 12: Addresses and Indirection — Part 2 | 地址与间接寻址（二）

> A bilingual (English / 中文) walkthrough of Day 12.
> 本节为第十二天的双语概念讲解。

---

## 1. Pointer Arithmetic | 指针运算

**English**

Pointers can be incremented or decremented to traverse elements in memory. When you add 1 to a pointer, it moves to the **next element** of its base type (i.e., it advances by `sizeof(base_type)` bytes). This is especially useful for iterating over arrays.

**中文**

指针可以自增或自减以遍历内存中的元素。对指针加 1，它会移动到其基类型的**下一个元素**（即前进 `sizeof(基类型)` 个字节），这在遍历数组时尤为有用。

---

## 2. Arrays and Pointers | 数组与指针

**English**

The name of an array is equivalent to a **pointer to its first element**. Accessing array elements via pointers works as follows:

```c
arr[i] == *(arr + i)
```

**中文**

数组名等价于**指向其第一个元素的指针**。通过指针访问数组元素的方式如下：

```c
arr[i] == *(arr + i)
```

---

## 3. Void Pointers | void 指针

**English**

A `void *` pointer can hold the address of **any** data type. It cannot be dereferenced directly — you must first cast it to the correct pointer type. This makes void pointers ideal for writing **generic** functions.

**中文**

`void *` 指针可以存放**任意**数据类型的地址。它不能直接被解引用 —— 必须先转换为正确的指针类型。因此 void 指针非常适合用于编写**通用**函数。

---

## 4. Function Pointers (Introduction) | 函数指针（入门）

**English**

Function pointers store the **address of a function**. They allow calling functions **indirectly**, which is useful for callbacks and dispatch tables.

```c
void greet() {
    printf("Hello\n");
}

void (*fp)() = greet;
fp();  // Calls greet
```

**中文**

函数指针存储**函数的地址**。通过它可以**间接**调用函数，常用于回调和调度表。

```c
void greet() {
    printf("Hello\n");
}

void (*fp)() = greet;
fp();  // 调用 greet
```

---

## 5. Common Pitfalls | 常见陷阱

**English**

- **Uninitialized pointers**: always initialize pointers before use.
- **Dangling pointers**: pointers that refer to freed or invalid memory.
- **Type casting with void pointers**: must cast to the correct type before dereferencing. (More on these problems later.)

**中文**

- **未初始化指针**：使用前务必初始化指针。
- **悬空指针**：指向已释放或无效内存的指针。
- **void 指针的类型转换**：解引用前必须转换为正确类型。（后续会详细讨论这些问题。）

---

## 6. Summary | 小结

**English**
- Pointer arithmetic moves through memory in steps based on the base type's size.
- Arrays and pointers are closely related; an array name is a pointer to the first element.
- Void pointers provide generic pointer functionality but require casting.
- Function pointers enable dynamic and indirect function calls.
- Always be careful with pointer initialization and type correctness.

**中文**
- 指针运算按基类型的大小在内存中移动。
- 数组与指针关系密切；数组名即指向第一个元素的指针。
- void 指针提供通用的指针功能，但使用前需要类型转换。
- 函数指针支持动态和间接的函数调用。
- 务必注意指针的初始化和类型正确性。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `pointer_arith_101.c` | Pointer arithmetic basics | 指针运算基础 |
| `void_ptr_example.c` | void pointer usage | void 指针用法 |
| `fn_ptr_example.c` | function pointer usage | 函数指针用法 |
| `day-12-summary.md` | Day 12 notes | 第十二天学习笔记 |