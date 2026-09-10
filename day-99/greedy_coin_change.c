#include <stdio.h>

/* Greedy coin change — works for "canonical" systems such as US coins.
   贪心找零 —— 适用于诸如美分硬币这类"规范"币值体系。 */
int coins[] = {25, 10, 5, 1};   /* quarter, dime, nickel, penny
                                   25、10、5、1 美分 */
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

int main(void)
{
    int amounts[] = {41, 99, 63, 1};
    for (int i = 0; i < 4; i++)
        printf("amount = %d -> %d coins\n", amounts[i], greedy_coin_change(amounts[i]));
    return 0;
}
