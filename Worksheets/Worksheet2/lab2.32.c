#include <stdio.h>

int main(void) {
   int currentPrice;
   int lastMonthsPrice;
   
   scanf("%d", &currentPrice);
   scanf("%d", &lastMonthsPrice);
   
   // Outputs a summary listing the price, the change since last month, and the estimated monthly mortgage.
   printf("This house is $%d. The change is $%d since last month.\n", currentPrice, currentPrice - lastMonthsPrice);
   printf("The estimated monthly mortgage is $%lf.\n", (currentPrice * 0.051) / 12);

   return 0;
}
