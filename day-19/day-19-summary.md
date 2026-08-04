# Day 19: Intro to Recursion | 递归入门

## Key Idea | 核心思想
- Recursion: a function calls itself on a smaller sub-problem.
- Must have a **base case** to stop; otherwise → stack overflow.

## Anatomy | 结构
```
 recurse(n)
   if (base case) return <value>;
   return combine(n, recurse(n - step));
```

## Topics | 主题
- Factorial: `n! = n * (n-1)!`, `0! = 1`.
- Fibonacci (naive): `F(n) = F(n-1) + F(n-2)`, exponential O(2ⁿ).
- Countdown: trace call/return order to visualize the stack.

## Pitfalls | 陷阱
- Missing / unreachable base case → stack overflow.
- Repeated sub-problems (e.g. naive Fibonacci) → exponential time; fix with memoization or iteration.

## Complexity | 复杂度
| Problem | Time | Space (stack) |
|---------|------|---------------|
| Factorial | O(n) | O(n) |
| Fibonacci (naive) | O(2ⁿ) | O(n) |