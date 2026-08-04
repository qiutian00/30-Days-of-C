# Day 30: Miscellaneous | 杂项

## Bitwise operators | 位运算符
- `&` AND, `|` OR, `^` XOR, `~` NOT, `<<` left shift, `>>` right shift.
- Idioms: set `x |= (1<<n)`, clear `x &= ~(1<<n)`, toggle `x ^= (1<<n)`, test `x & (1<<n)`.

## Unions | 联合体
- All members share the same starting address; only one is "active" at a time.
- `sizeof(union)` = size of largest member.
- Reinterpreting one member as another is **implementation-defined**.

## Preprocessor | 预处理器
- `#include`, `#define` (constants and function-like macros), `#ifdef/#ifndef/#endif/#if`.
- **Parenthesize** macro args and the body.
- Macros: no type checking, may evaluate args multiple times — prefer `const` and `inline` for safety.