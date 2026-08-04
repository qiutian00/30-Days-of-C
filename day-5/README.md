# Day 5: Strings in C | C 语言中的字符串

> A bilingual (English / 中文) walkthrough of Day 5.
> 本节为第五天的双语概念讲解。

---

## 1. Strings as Arrays of Chars | 字符串即字符数组

**English**

There is no built-in string data type in C. A string is a **null-terminated** array of characters.

```c
char my_string[] = {'S','t','r','i','n','g','\0'}; // must include the null terminator
char my_string[] = "String";                        // '\0' is appended automatically
```

**中文**

C 没有内置的字符串类型。字符串是**以空字符结尾**的字符数组。

```c
char my_string[] = {'S','t','r','i','n','g','\0'}; // 必须包含空终止符
char my_string[] = "String";                        // 自动追加 '\0'
```

---

## 2. Declaring Strings | 字符串声明

```c
char str1[] = "string1";
char *str2  = "string2";
```

**English**

- The value of the array name `str1` is the address of the first char in `str1` — the starting location of the string.
- `str2` is a pointer to an array of chars; it points to the starting address of the char array.
- Thus `str1 == &str1` (as an integer), but `str2 != &str2`. The address of `str2` is a separate memory location — a pointer variable holds the address of another variable.

**中文**

- 数组名 `str1` 的值就是 `str1` 中第一个字符的地址 —— 字符串的起始位置。
- `str2` 是指向字符数组的指针，指向该字符数组的起始地址。
- 因此 `str1 == &str1`（作为整型），但 `str2 != &str2`。`str2` 的地址是另一块独立的内存位置 —— 指针变量存放的是另一个变量的地址。

---

## 3. Strings and Functions | 字符串与函数

**English**

Passing strings to functions:

```c
void func(char anystring[]) { /* ... */ }
// OR
void func(char *anystring)  { /* ... */ }
```

Returning a string from a function: set the return type to `char *`:

```c
char *this_func(params) {
    /* statements */
    return <any_string>;
}
```

**中文**

将字符串传给函数：

```c
void func(char anystring[]) { /* ... */ }
// 或
void func(char *anystring)  { /* ... */ }
```

从函数返回字符串：将返回类型设为 `char *`：

```c
char *this_func(params) {
    /* 语句 */
    return <某字符串>;
}
```

---

## 4. String vs Char | 字符串与字符的区别

**English**

```c
'a'   // a single character
"a"   // a string literal — it points to the beginning of an array of chars in memory
```

**中文**

```c
'a'   // 单个字符
"a"   // 字符串字面量 —— 指向内存中一个字符数组的起始位置
```

---

## 5. Declaring Strings on the Heap | 在堆上声明字符串

**English**

- All local variables declared inside a function are allocated on the **stack** and are destroyed once the function exits.
- `malloc()` allocates memory on the **heap**, which persists even after the function returns (until you `free()` it).

```c
s = (char *)malloc(num_chars);                              // char is 1 byte
s = (char *)malloc(num_elts * sizeof(<dtype>));             // general form
```

**中文**

- 函数内声明的局部变量分配在**栈**上，函数结束后即被销毁。
- `malloc()` 在**堆**上分配内存，即使函数返回后该内存依然存在（直到你调用 `free()`）。

```c
s = (char *)malloc(num_chars);                              // char 占 1 字节
s = (char *)malloc(num_elts * sizeof(<dtype>));             // 通用形式
```

---

## 6. String Functions | 字符串函数

**English**

Include `<string.h>` to use built-in string functions:

| Function | Syntax | Description |
|----------|--------|-------------|
| `strlen()` | `strlen(<str>)` | Returns the length of `<str>` |
| `strcat()` | `strcat(<to_this>,<add_this>)` | Concatenates two strings |
| `strncat()` | `strncat(<to_this>,<add_this>,n)` | Concatenates first `n` chars of `<add_this>` to `<to_this>` |
| `strcpy()` | `strcpy(<dest>,<src>)` | Copies `<src>` into `<dest>` |
| `strncpy()` | `strncpy(<dest>,<src>,n)` | Copies first `n` chars of `<src>` to `<dest>` |
| `strstr()` | `strstr(this,pattern)` | Returns a pointer to the start of `pattern` if found |

> **Note**: Always ensure the destination string has enough memory to hold the result.

**中文**

包含 `<string.h>` 以使用内置字符串函数：

| 函数 | 语法 | 说明 |
|------|------|------|
| `strlen()` | `strlen(<str>)` | 返回 `<str>` 的长度 |
| `strcat()` | `strcat(<to_this>,<add_this>)` | 拼接两个字符串 |
| `strncat()` | `strncat(<to_this>,<add_this>,n)` | 将 `<add_this>` 前 `n` 个字符拼接到 `<to_this>` |
| `strcpy()` | `strcpy(<dest>,<src>)` | 将 `<src>` 复制到 `<dest>` |
| `strncpy()` | `strncpy(<dest>,<src>,n)` | 将 `<src>` 前 `n` 个字符复制到 `<dest>` |
| `strstr()` | `strstr(this,pattern)` | 若找到 `pattern`，返回指向其起始位置的指针 |

> **注意**：使用字符串函数时，务必确保目标字符串有足够的内存存放结果。

---

## 7. Character Functions | 字符函数

**English**

Include `<ctype.h>` to test or transform single characters:

| Function | Checks for |
|----------|-----------|
| `isalnum()` | An alphabetic letter or a digit |
| `isalpha()` | An alphabetic letter |
| `isblank()` | A space or tab character |
| `iscntrl()` | A control character |
| `isdigit()` | A digit |
| `isgraph()` | Any printing character except a space |
| `islower()` | A lowercase letter |
| `isprint()` | Any printing character including a space |
| `ispunct()` | A printing character that is not a space or alphanumeric |
| `isspace()` | A whitespace character (`' '`, `'\n'`, `'\t'`, `'\v'`, `'\r'`, `'\f'`) |
| `isupper()` | An uppercase letter |
| `isxdigit()` | A hexadecimal digit |

**中文**

包含 `<ctype.h>` 以测试或转换单个字符：

| 函数 | 检测内容 |
|------|---------|
| `isalnum()` | 字母或数字 |
| `isalpha()` | 字母 |
| `isblank()` | 空格或制表符 |
| `iscntrl()` | 控制字符 |
| `isdigit()` | 数字 |
| `isgraph()` | 除空格外的可打印字符 |
| `islower()` | 小写字母 |
| `isprint()` | 含空格的可打印字符 |
| `ispunct()` | 既非空格也非字母数字的可打印字符 |
| `isspace()` | 空白字符（`' '`、`'\n'`、`'\t'`、`'\v'`、`'\r'`、`'\f'`） |
| `isupper()` | 大写字母 |
| `isxdigit()` | 十六进制数字 |

---

## Files in this Directory | 本目录文件

| File | Description | 说明 |
|------|-------------|------|
| `declare_str.c` | Declaring strings two ways | 两种字符串声明方式 |
| `string-ex.c` | Basic string operations | 基本字符串操作 |
| `null-terminated-str.c` | Null-terminated string behavior | 空终止字符串行为示例 |
| `char_count.c` | Count characters in a string | 统计字符串中的字符数 |
| `return_str.c` | Returning a string from a function | 从函数返回字符串 |
| `day-5-summary.md` | Day 5 notes | 第五天学习笔记 |