# Day 25: Stacks | 栈

## LIFO | 后进先出
- Operations (all O(1)): `push`, `pop`, `peek`, `isEmpty`.
- Single access point: the **top**.

## Implementations | 实现
- **Array**: index `top`; overflow when `top == CAP - 1`; underflow when `top == -1`.
- **Linked list**: head is the top; push = prepend, pop = remove head; no fixed capacity.

## Application | 应用
- Balanced parentheses: push openers; for each closer, pop and verify it matches.
- Also: call stack, expression evaluation, backtracking, undo/redo.

## Balanced-parens check | 括号匹配检查
- Empty stack at end AND every closer matched its opener → balanced.
- `"(a{b[c]d}e)"` → balanced; `"(a{b[c}d]e)"`, `"((())"` → unbalanced.