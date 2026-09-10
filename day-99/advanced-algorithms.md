# 进阶算法专题 | Advanced Algorithm Topics

> Bilingual notes on greedy algorithms, dynamic programming, and the knapsack problem.
> 关于贪心算法、动态规划与背包问题的双语讲解。

---

## 1. 贪心算法 | Greedy Algorithms

**English**

A **greedy algorithm** builds a solution piece by piece, always choosing the option that looks best *right now* (the locally optimal choice), hoping to reach a global optimum. It is simple and fast, but it is correct **only** when the problem has:

- **Greedy-choice property** — a locally optimal choice leads to a globally optimal solution.
- **Optimal substructure** — an optimal solution contains optimal solutions to subproblems.

**中文**

**贪心算法**逐步构造解，每次都选择"当下看起来最优"（局部最优）的选项，希望最终达到全局最优。它简单且高效，但**只有**当问题具有以下性质时才正确：

- **贪心选择性质** —— 局部最优选择能导向全局最优解。
- **最优子结构** —— 最优解包含子问题的最优解。

### Example: Coin Change | 示例：找零钱

```c
/* Greedy coin change — works for "canonical" systems such as US coins.
   贪心找零 —— 适用于诸如美分硬币这类"规范"币值体系。 */
int coins[] = {25, 10, 5, 1};   /* quarter, dime, nickel, penny */
int n = 4;

int greedy_coin_change(int amount)
{
    int count = 0;
    for (int i = 0; i < n; i++) {
        while (amount >= coins[i]) {   /* always take the largest possible coin
                                         总是先取当前最大的硬币 */
            amount -= coins[i];
            count++;
        }
    }
    return count;
}
```

> ⚠️ Greedy is **not always optimal** for coin change: with coins `{1, 3, 4}` and amount `6`, greedy gives `4+1+1` (3 coins) but the optimum is `3+3` (2 coins). This is exactly where dynamic programming is needed.
>
> ⚠️ 贪心对找零**并不总是最优**：当币值为 `{1, 3, 4}`、目标为 `6` 时，贪心得到 `4+1+1`（3 枚），而最优解是 `3+3`（2 枚）。这正是需要动态规划的场景。

Other classic greedy problems: activity selection, Huffman coding, Kruskal's/Prim's MST.

其他经典贪心问题：活动选择、哈夫曼编码、Kruskal/Prim 最小生成树。

---

## 2. 动态规划 | Dynamic Programming (DP)

**English**

**Dynamic programming** solves problems by breaking them into overlapping subproblems and storing their results, so each subproblem is solved only once. It applies when a problem has:

- **Optimal substructure** — the optimal solution can be built from optimal solutions of subproblems.
- **Overlapping subproblems** — the same subproblems are reused many times.

Two equivalent implementations:

1. **Top-down (memoization)** — recursive; cache results in a table.
2. **Bottom-up (tabulation)** — iterative; fill the table in dependency order.

**中文**

**动态规划**将问题拆分为重叠的子问题并保存其结果，使每个子问题只求解一次。当问题具备以下性质时适用：

- **最优子结构** —— 最优解可由子问题的最优解构造。
- **重叠子问题** —— 相同的子问题会被多次复用。

两种等价实现：

1. **自顶向下（记忆化）** —— 递归实现，用表缓存结果。
2. **自底向上（表格法）** —— 迭代实现，按依赖顺序填表。

### Example: Fibonacci | 示例：斐波那契

```c
/* Top-down: memoization | 自顶向下：记忆化 */
int memo[100];
int fib(int n)
{
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];      /* already solved | 已求解 */
    return memo[n] = fib(n - 1) + fib(n - 2);
}

/* Bottom-up: tabulation | 自底向上：表格法 */
int fib_iter(int n)
{
    int dp[100];
    dp[0] = 0; dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}
```

Naive recursion is O(2ⁿ); DP reduces it to **O(n)**.

朴素递归是 O(2ⁿ)；DP 将其降为 **O(n)**。

---

## 3. 背包问题 | Knapsack Problem

**English**

The **0/1 knapsack problem**: given `n` items, each with weight `wt[i]` and value `val[i]`, and a knapsack of capacity `W`, choose a subset of items (each item is taken at most once — "0/1") to maximize total value without exceeding `W`.

This is the canonical DP problem. Let `dp[i][w]` be the maximum value using the first `i` items with capacity `w`. The recurrence:

- If item `i` is **not** taken: `dp[i][w] = dp[i-1][w]`.
- If item `i` **is** taken: `dp[i][w] = val[i-1] + dp[i-1][w - wt[i-1]]` (only when `wt[i-1] <= w`).

**中文**

**0/1 背包问题**：给定 `n` 个物品，每个物品有重量 `wt[i]` 和价值 `val[i]`，以及一个容量为 `W` 的背包，选择物品子集（每件物品至多取一次，即"0/1"），在不超过 `W` 的前提下使总价值最大。

这是最经典的 DP 问题。设 `dp[i][w]` 为使用前 `i` 个物品、容量为 `w` 时的最大价值。递推关系：

- 不取物品 `i`：`dp[i][w] = dp[i-1][w]`。
- 取物品 `i`：`dp[i][w] = val[i-1] + dp[i-1][w - wt[i-1]]`（仅当 `wt[i-1] <= w`）。

```c
int max(int a, int b) { return a > b ? a : b; }

int knapsack(int W, int wt[], int val[], int n)
{
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]],   /* take | 取 */
                               dp[i - 1][w]);                            /* skip | 不取 */
            else
                dp[i][w] = dp[i - 1][w];   /* cannot fit | 放不下 */
        }
    }
    return dp[n][W];
}
```

**Example | 示例**: `W = 5`, `wt = {2, 3, 4}`, `val = {3, 4, 5}` → best value is **7** (take items 1 and 2: `3+4`).

> The space can be optimized to **O(W)** with a 1D array, iterating `w` in reverse. A variant that allows taking fractions of items is the **fractional knapsack**, which *is* solvable greedily (take items by highest value/weight ratio).
>
> 空间可优化到 **O(W)**，用一维数组并**逆序**更新 `w`。允许取物品一部分的变体称为**分数背包**，它*可以*用贪心求解（按价值/重量比从高到低取）。

---

## 4. 对比总结 | Summary & Comparison

| Topic | 思路 | Key idea | 正确性条件 / When to use |
|-------|------|----------|--------------------------|
| 贪心 Greedy | 每步取局部最优 | Choose locally optimal each step | 需贪心选择性质 + 最优子结构 |
| 动态规划 DP | 记录并复用子问题解 | Reuse overlapping subproblems | 需最优子结构 + 重叠子问题 |
| 背包 Knapsack | DP 的经典应用 | Classic application of DP | 0/1 背包用 DP；分数背包用贪心 |

**English takeaway**: Greedy is a heuristic that must be *proven* correct; DP is a general technique that *guarantees* correctness when the two properties hold. Use greedy when it provably works (fast), otherwise reach for DP.

**中文要点**：贪心是一种必须*证明*其正确性的启发式策略；DP 是当两个性质成立时*保证*正确性的通用方法。贪心在可证明有效时优先使用（更快），否则就用 DP。
