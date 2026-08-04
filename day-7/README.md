# Day 7: Structures and Enum | 结构体与枚举

> A bilingual (English / 中文) walkthrough of Day 7.
> 本节为第七天的双语概念讲解。

---

## 1. User-Defined Data Types | 用户自定义数据类型

**English**

Structures in C can hold items of **different** data types, grouping related data into a single record. This differs from arrays, which hold items of the **same** type.

**中文**

C 语言中的结构体可以容纳**不同**数据类型的成员，将相关数据组织成一条记录。这与存放**相同**类型元素的数组不同。

---

## 2. Structures (`struct`) | 结构体

**English**

Syntax:

```c
struct structName {
    dtype1 var1;
    dtype2 var2;
        .
        .
        .
    dtypeN varN;
};
```

- Use the `struct` keyword followed by the structure name `structName`.
- Between the `{}`, give a semicolon-delimited list of member variables.
- Remember to place a `;` after the closing `}`.

**中文**

语法：

```c
struct structName {
    dtype1 var1;
    dtype2 var2;
        .
        .
        .
    dtypeN varN;
};
```

- 使用 `struct` 关键字，后接结构体名 `structName`。
- 在 `{}` 内列出以分号分隔的成员变量。
- 切记在结束的 `}` 之后加上 `;`。

---

### Creating a Variable of `struct` Type | 创建结构体变量

**English**

```c
struct structName structVar;
```

- `structVar` is a variable of type `structName`.
- You cannot omit the `struct` keyword: `structName structVar;` alone is not allowed.

**中文**

```c
struct structName structVar;
```

- `structVar` 是一个 `structName` 类型的变量。
- 不能省略 `struct` 关键字：单独写 `structName structVar;` 是不允许的。

---

### Accessing Members | 访问成员

**English**

```c
structVar.var1;
structVar.var2;
    .
    .
    .
structVar.varN;
```

If you think of a struct as a data record, the members are the fields in that record.

**中文**

```c
structVar.var1;
structVar.var2;
    .
    .
    .
structVar.varN;
```

如果把结构体视作一条数据记录，那么各个成员就是该记录中的字段。

---

## 3. typedef

**English**

To declare `struct` variables the same way you would declare `int`, `float`, or `char` variables, use `typedef`:

```c
typedef struct structName STRUCTNAME;
```

Now you can create variables of type `structName` using:

```c
STRUCTNAME structVar;
```

**中文**

如果想用声明 `int`、`float`、`char` 变量那样的方式来声明 `struct` 变量，可以使用 `typedef`：

```c
typedef struct structName STRUCTNAME;
```

这样就可以用如下方式创建 `structName` 类型的变量：

```c
STRUCTNAME structVar;
```

---

## 4. Enum | 枚举

**English**

Sometimes you work with a fixed set of related values — the 7 days of the week, movie ratings, etc. Instead of naming them `0, 1, 2, ..., 6`, using `Sunday` through `Saturday` improves readability and intuitiveness. This is where `enum` comes in:

```c
enum week { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

enum week today;
```

The named values in an `enum` are called **enumeration constants**. By default they are integers starting from `0` and increment by `1`, unless explicitly assigned.

**中文**

有时你会处理一组固定的相关取值 —— 例如一周的 7 天、电影评分等。与其命名为 `0, 1, 2, ..., 6`，不如直接使用 `Sunday` 到 `Saturday`，这样既提高可读性又直观。这正是 `enum` 的用途：

```c
enum week { Sunday, Monday, Tuesday, Wednesday, Thursday, Friday, Saturday };

enum week today;
```

`enum` 中的命名值称为**枚举常量**。默认情况下它们是从 `0` 开始、依次加 `1` 的整数，除非显式指定。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `struct-ex.c` | Structure declaration and member access | 结构体的声明与成员访问 |
| `enum.c` | Enumeration usage | 枚举的使用示例 |
| `day-7-summary.md` | Day 7 notes | 第七天学习笔记 |