# Day 3: Operators, Conditionals, and Reading Strings | 运算符、条件语句与字符串读取

> A bilingual (English / 中文) walkthrough of Day 3.
> 本节为第三天的双语概念讲解。

---

## 1. Common Operators | 常用运算符

**English**

Operators are special symbols that perform operations on operands.

- **Assignment operator** `=` assigns the value on its right to the variable on its left. The data type of the value must match that of the variable.

```c
int my_var = 27;
```

- **Compound assignment** performs the specified arithmetic on `a`, then assigns the result back to `a`:

```c
a += b  // is the same as: a = a + b
a -= b  // is the same as: a = a - b
a *= b  // is the same as: a = a * b
a /= b  // is the same as: a = a / b
```

**中文**

运算符是对操作数执行运算的特殊符号。

- **赋值运算符** `=` 将其右侧的值赋给左侧的变量。值的类型必须与变量的类型匹配。

```c
int my_var = 27;
```

- **复合赋值** 先对 `a` 执行指定运算，再将结果赋回给 `a`：

```c
a += b  // 等价于：a = a + b
a -= b  // 等价于：a = a - b
a *= b  // 等价于：a = a * b
a /= b  // 等价于：a = a / b
```

---

## 2. Increment and Decrement | 自增与自减

**English**

Use `++` / `--` to add or subtract 1 from a variable.

```c
int num = 10;
num++;  // num is now 11
num--;  // num is now 10
```

- **Post-increment** `a++`: the value is used first, then `a` is incremented.
- **Pre-increment** `++a`: `a` is incremented first, then the new value is used.

```c
int a, b;

a = 1;
b = a++; // b is 1, a is 2

a = 1;
b = ++a; // b is 2, a is 2
```

**中文**

使用 `++` / `--` 对变量加 1 或减 1。

```c
int num = 10;
num++;  // num 变为 11
num--;  // num 变为 10
```

- **后置自增** `a++`：先使用 `a` 的值，再将 `a` 加 1。
- **前置自增** `++a`：先将 `a` 加 1，再使用新的值。

```c
int a, b;

a = 1;
b = a++; // b 为 1，a 为 2

a = 1;
b = ++a; // b 为 2，a 为 2
```

---

## 3. Comparison and Logical Operators | 比较与逻辑运算符

**English**

Comparison operators:

```
==   // equals          !=   // not equals
>    // greater than    <    // less than
<=   // less than or equal to
>=   // greater than or equal to
```

Logical operators test the truth value of expressions. C has no dedicated boolean type — all **non-zero** values are treated as **true**, and `0` as **false**.

```c
if (condition1 && condition2) { /* both must be true  */ }
if (condition1 || condition2) { /* either must be true */ }
if (!(condition))             { /* negates the condition */ }
```

**中文**

比较运算符：

```
==   // 等于          !=   // 不等于
>    // 大于          <    // 小于
<=   // 小于等于
>=   // 大于等于
```

逻辑运算符用于测试表达式的真假。C 没有专门的布尔类型 —— 所有**非零**值都视为**真**，`0` 视为**假**。

```c
if (condition1 && condition2) { /* 两个都为真时执行 */ }
if (condition1 || condition2) { /* 任一为真时执行 */ }
if (!(condition))             { /* 对条件取反 */ }
```

---

## 4. Conditionals | 条件语句

**English**

```c
if (condition)
{
    // do this if condition is true
}
else
{
    // do this if condition is false
}
```

**中文**

```c
if (条件)
{
    // 条件为真时执行
}
else
{
    // 条件为假时执行
}
```

---

## 5. Reading String Inputs | 读取字符串输入

**English**

- Why `gets()` is no longer used: `gets()` writes all user input into the target array without bounds checking, so an input longer than the array will overflow into adjacent memory, potentially overwriting other variables. This is a classic **buffer overflow** vulnerability.

```c
char name[10];
gets(name); // DANGEROUS — no length limit
```

- `fgets()` reads at most `max_chars - 1` characters, then appends a null terminator:

```c
fgets(<char_array>, <max_chars>, <input_source>);
```

- **Null-terminated strings**: a `\0` marks the end of a string, so a char array of size `k` can hold at most `k - 1` characters.
- **Caveat**: when more characters than `max_chars` are entered, the excess stays in the input buffer and is read by the next input call. Flush the input buffer before the next `fgets()` to avoid this.

**中文**

- 为什么不再使用 `gets()`：`gets()` 会将用户输入全部写入目标数组而不检查边界，当输入超过数组长度时会溢出到相邻内存，可能覆盖其他变量。这是典型的**缓冲区溢出**漏洞。

```c
char name[10];
gets(name); // 危险 —— 没有长度限制
```

- `fgets()` 最多读取 `max_chars - 1` 个字符，并自动追加空终止符：

```c
fgets(<字符数组>, <最大字符数>, <输入源>);
```

- **空终止字符串**：`\0` 标记字符串的结束，因此大小为 `k` 的字符数组最多只能存放 `k - 1` 个字符。
- **注意事项**：当输入字符数超过 `max_chars` 时，多余的字符会留在输入缓冲区中，被下一次输入调用读取。需要在下一次 `fgets()` 之前清空输入缓冲区来避免这一问题。

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `1-operators.c` | Assignment and arithmetic operators | 赋值与算术运算符 |
| `2-compound-assignment.c` | Compound assignment operators | 复合赋值运算符 |
| `3-pre-post-increment.c` | Pre- and post-increment behavior | 前置与后置自增的行为 |
| `4-logical-ops.c` | Comparison and logical operators | 比较与逻辑运算符 |
| `day-3-summary.md` | Day 3 notes | 第三天学习笔记 |