#include <stdio.h>

#define MAXN 100

/* Top-down: memoization | 自顶向下：记忆化 */
static int memo[MAXN];

static void init_memo(void)
{
    for (int i = 0; i < MAXN; i++) memo[i] = -1;   /* -1 means "not solved yet"
                                                       -1 表示"尚未求解" */
}

int fib(int n)
{
    if (n <= 1) return n;
    if (memo[n] != -1) return memo[n];      /* already solved | 已求解 */
    return memo[n] = fib(n - 1) + fib(n - 2);
}

/* Bottom-up: tabulation | 自底向上：表格法 */
int fib_iter(int n)
{
    int dp[MAXN];
    dp[0] = 0; dp[1] = 1;
    for (int i = 2; i <= n; i++)
        dp[i] = dp[i - 1] + dp[i - 2];
    return dp[n];
}

int main(void)
{
    init_memo();
    for (int i = 0; i <= 10; i++)
        printf("fib(%2d) = %3d (recursive)  %3d (iterative)\n",
               i, fib(i), fib_iter(i));
    return 0;
}
