# Day 4: Functions, Loops, and Arrays | 函数、循环与数组

> A bilingual (English / 中文) walkthrough of Day 4.
> 本节为第四天的双语概念讲解。

---

## 1. Functions | 函数

**English**

Functions provide:
- **Modularity** — split a program into smaller, manageable pieces.
- **Code reusability** — write once, call many times.
- **Abstraction** — hide implementation details behind an interface.

Function declaration syntax:

```c
<return_type> <function_name>(<parameters>);
// e.g.,
int add(int a, int b);
```

In the function declaration (the *prototype*):
- Parameters listed here are **formal parameters**.
- When the function is called with specific values, those values are the **arguments** (actual parameters).
- Argument values are **copied** into the corresponding parameters.
- If the function returns nothing, specify the return type as `void`.
- A function's return value can be assigned to a variable of a matching data type.

### Arguments are passed by value | 参数按值传递

```c
void add2(int num) { num += 2; }

int main()
{
    int num = 10;
    add2(num);
    printf("num is: %d", num); // prints 10
    return 0;
}
```

Modifying `num` inside `add2()` does **not** alter `num` in `main()`, because it is the *value* of `num` that is passed in.

**中文**

函数提供：
- **模块化** —— 将程序拆分为更小、易于管理的部分。
- **代码复用** —— 一次编写，多处调用。
- **抽象** —— 通过接口隐藏实现细节。

函数声明语法：

```c
<返回类型> <函数名>(<参数>);
// 例如，
int add(int a, int b);
```

在函数声明（即*原型*）中：
- 此处列出的参数是**形式参数**。
- 调用函数时传入的具体值称为**实际参数**（arguments）。
- 实参的值会被**复制**到对应的形参中。
- 若函数不返回任何值，返回类型设为 `void`。
- 函数返回的值可以赋给一个类型匹配的变量。

```c
void add2(int num) { num += 2; }

int main()
{
    int num = 10;
    add2(num);
    printf("num is: %d", num); // 输出 10
    return 0;
}
```

在 `add2()` 内部修改 `num` **不会**影响 `main()` 中的 `num`，因为传入的是 `num` 的*值*。

---

## 2. Switch Statement | switch 语句

**English**

Switch statements are good alternatives to long `if ... else if ... else` ladders.

```c
switch(test)
{
    case case1: /* do this */ break;
    case case2: /* do this */ break;
    case case3: /* do this */ break;
    default:    /* do this */          // optional
}
```

- `test` must be an integer or evaluate to an integer.
- The `break;` statement exits the switch block. Without it, execution **trickles down** to the next `break`, which is rarely intended.
- `default` runs only when no case matches; it is **optional**.

**中文**

switch 语句是冗长的 `if...else if...else` 链的良好替代方案。

```c
switch(test)
{
    case case1: /* 执行此段 */ break;
    case case2: /* 执行此段 */ break;
    case case3: /* 执行此段 */ break;
    default:    /* 执行此段 */          // 可选
}
```

- `test` 必须是整型或可求值为整型。
- `break;` 语句用于退出 switch 块。若省略，执行会**向下穿透**到下一个 `break`，这通常并非预期行为。
- `default` 仅在没有匹配的 case 时执行，且是**可选**的。

---

## 3. Arrays | 数组

**English**

An array is a collection of items of the **same** data type. Declaration syntax:

```c
<data_type> <array_name>[<num_items>];
```

For an array of length `num_items`, valid indices are `0, 1, 2, ..., num_items - 1`.

Initialization options:

```c
int array1[3];
array1[0] = 1; array1[1] = 2; array1[2] = 3;

// OR
int array1[3] = {1, 2, 3};

// OR
int array1[] = {1, 2, 3};
```

**中文**

数组是**相同**数据类型元素的集合。声明语法：

```c
<数据类型> <数组名>[<元素个数>];
```

长度为 `num_items` 的数组，有效下标为 `0, 1, 2, ..., num_items - 1`。

初始化方式：

```c
int array1[3];
array1[0] = 1; array1[1] = 2; array1[2] = 3;

// 或
int array1[3] = {1, 2, 3};

// 或
int array1[] = {1, 2, 3};
```

---

## 4. Strings as Arrays of Chars | 字符串即字符数组

**English**

There is no built-in string data type in C; a string is a null-terminated array of characters.

```c
char my_string[] = {'S','t','r','i','n','g','\0'}; // include the null terminator
char my_string[] = "String";                        // '\0' is appended automatically
```

**中文**

C 没有内置的字符串类型；字符串是以空字符结尾的字符数组。

```c
char my_string[] = {'S','t','r','i','n','g','\0'}; // 需包含空终止符
char my_string[] = "String";                        // 自动追加 '\0'
```

---

## 5. Multi-Dimensional Arrays | 多维数组

**English**

```c
int array1[3][3] = {{1,2,3},{4,5,6},{7,8,9}}; // a 3x3 matrix
```

**中文**

```c
int array1[3][3] = {{1,2,3},{4,5,6},{7,8,9}}; // 3x3 矩阵
```

---

## 6. Loops | 循环

**English**

```c
for (init; check_condition; update) {
    // do this
}

// init counter
while (condition) {
    // do this
    // update counter
}
```

Loop control statements:
- `continue` — skip the rest of the current iteration and start the next.
- `break` — exit the loop immediately.

**中文**

```c
for (初始化; 循环条件; 更新) {
    // 循环体
}

// 初始化计数器
while (条件) {
    // 循环体
    // 更新计数器
}
```

循环控制语句：
- `continue` —— 跳过本次迭代剩余部分，进入下一次迭代。
- `break` —— 立即退出循环。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `functions.c` | Defining and calling functions | 函数的定义与调用 |
| `arrays_loops.c` | Arrays combined with loops | 数组与循环的结合使用 |
| `array2D.c` | Two-dimensional arrays | 二维数组示例 |
| `day-4-summary.md` | Day 4 notes | 第四天学习笔记 |