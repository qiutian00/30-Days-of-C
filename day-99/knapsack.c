#include <stdio.h>

static int max(int a, int b) { return a > b ? a : b; }

/* 0/1 knapsack: maximize value without exceeding capacity W.
   0/1 背包：在不超过容量 W 的前提下使总价值最大。 */
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

int main(void)
{
    int wt[]  = {2, 3, 4};
    int val[] = {3, 4, 5};
    int n = 3;
    int W = 5;

    printf("W = %d, n = %d\n", W, n);
    printf("best value = %d\n", knapsack(W, wt, val, n));   /* expect 7 | 期望 7 */
    return 0;
}
