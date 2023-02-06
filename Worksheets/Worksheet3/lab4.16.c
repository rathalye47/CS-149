#include <stdio.h>

int main(void) {

   int num;
   int count;
   double average;
   double total;
   
   scanf(" %d", &num);
   int max = num;
   
   while (num >= 0) {
      if (num > max) {
         max = num;
      }
      
      total += num;
      count++;
      scanf(" %d", &num);
   }
   
   average = total / count;
   printf("%d %0.2lf\n", max, average);

   return 0;
}