# Day 20: Some More Recursion | 更多递归

## Recursion Patterns | 递归形态
- **Linear**: one recursive call per invocation (array sum, naive power).
- **Tail**: recursive call is the last action; can be optimized to O(1) stack.
- **Divide-and-conquer**: splits into multiple sub-problems (fast power, Hanoi).

## Topics | 主题
- `sum(arr, n) = arr[n-1] + sum(arr, n-1)`, base `n == 0 -> 0`. O(n).
- Fast power: halve the exponent; `x^(2k) = (x^k)^2`, `x^(2k+1) = x*(x^k)^2`. O(log exp).
- Tail-recursive factorial with an accumulator.
- Tower of Hanoi: `T(n) = 2*T(n-1) + 1 = 2^n - 1` moves.

## Complexity | 复杂度
| Problem | Time | Stack |
|---------|------|-------|
| Array sum | O(n) | O(n) |
| Naive power | O(exp) | O(exp) |
| Fast power | O(log exp) | O(log exp) |
| Hanoi (moves) | O(2^n) | O(n) |