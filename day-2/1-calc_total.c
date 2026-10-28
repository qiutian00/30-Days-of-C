#include <stdio.h>

int main() 
{
	double sub_total;
	double tax;
	double grand_total;
	double tax_rate;

	tax_rate = 0.25;
	sub_total = 250;
	tax = sub_total * tax_rate;
	grand_total = sub_total + tax;

	printf("The tax on %.2f is %.2f, so the grand total is %.2f.\n", sub_total, tax, grand_total);

	int i;
	int j;
	j = i + 10;
	printf("j = %d\n", j);

	int price = 0;
	printf("Enter the price of the item: ");
	scanf("%d", &price);

	int change = 1000 - price;
	printf("change = %d\n", change);

	return 0;
}

