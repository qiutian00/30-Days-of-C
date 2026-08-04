# Day 2: Data Types, Variables, and Constants | 数据类型、变量与常量

> A bilingual (English / 中文) walkthrough of Day 2.
> 本节为第二天的双语概念讲解。

---

## 1. Declaring Variables | 变量声明

**English**

The general syntax for declaring variables:

```c
<data_type> <var_name>;               // variable declaration
<data_type> <var_name> = <value>;    // declaring and assigning a value
```

**中文**

声明变量的一般语法：

```c
<数据类型> <变量名>;                    // 变量声明
<数据类型> <变量名> = <值>;             // 声明的同时赋值
```

---

## 2. Common Data Types | 常用数据类型

**English**

| Type | Description | Format Specifier |
|------|-------------|------------------|
| `int` | integer | `%d` (decimal; use `%kd` for a field width of `k`) |
| `float` | single-precision floating point | `%f` (`%.kf` for `k` digits after the decimal point) |
| `double` | double-precision floating point | `%f` (`%.kf` for `k` digits after the decimal point) |
| `char` | character | `%c` |

**中文**

| 类型 | 说明 | 格式说明符 |
|------|------|-----------|
| `int` | 整型 | `%d`（十进制；`%kd` 指定宽度为 `k`） |
| `float` | 单精度浮点数 | `%f`（`%.kf` 保留小数点后 `k` 位） |
| `double` | 双精度浮点数 | `%f`（`%.kf` 保留小数点后 `k` 位） |
| `char` | 字符型 | `%c` |

---

## 3. Constants | 常量

**English**

When a variable should not be modified during the program, declare it as a constant.

- Using `#define`:

```c
#define ID 204

#define ID 207 // this compiles without errors :/
```

Although you'd like `ID` to be constant, it is not *completely constant* because you can redefine its value.

- Using the `const` keyword:

```c
const int id = 204; // cannot re-define elsewhere
```

The `const` keyword renders `id` a **read-only** variable; any attempt to modify it elsewhere will raise an error.

**中文**

当一个变量在程序运行期间不应被修改时，应将其声明为常量。

- 使用 `#define`：

```c
#define ID 204

#define ID 207 // 此处重定义编译时不会报错 :/
```

虽然希望 `ID` 是常量，但它并不*完全常量*，因为你可以重新定义它的值。

- 使用 `const` 关键字：

```c
const int id = 204; // 无法在别处重新定义
```

`const` 关键字使 `id` 成为**只读变量**；在其他地方尝试修改它将引发错误。

---

## 4. Naming Conventions | 命名规范

**English**

- Names of constants are usually written in **UPPER_CASE**.
- Variable and function names should be **descriptive**.

```c
#define PI 3.14159
```

```c
float calc_total(float bill_amt, float tip_perc)
{
    float total;
    total = bill_amt * (1 + tip_perc * 0.01);
    return total;
}
```

**中文**

- 常量名通常使用**全大写**。
- 变量名与函数名应当**具有描述性**。

```c
#define PI 3.14159
```

```c
float calc_total(float bill_amt, float tip_perc)
{
    float total;
    total = bill_amt * (1 + tip_perc * 0.01);
    return total;
}
```

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `1-calc_total.c` | Demonstrates variables and a function computing a total | 演示变量与求总和的函数 |
| `2-learn-constants.c` | Demonstrates `#define` and `const` constants | 演示 `#define` 与 `const` 常量 |
| `day-2-summary.md` | Day 2 notes | 第二天学习笔记 |