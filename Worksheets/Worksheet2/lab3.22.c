#include <stdio.h>

int main(void) {

   int num1;
   int num2;
   int num3;
   
   // Reads user input.
   scanf("%d", &num1);
   scanf("%d", &num2);
   scanf("%d", &num3);
   
   // Algorithm to find the smallest integer out of 3 integers.
   if ((num1 < num2) && (num1 < num3)) {
      printf("%d\n", num1);
   }
   
   else if ((num2 < num1) && (num2 < num3)) {
      printf("%d\n", num2);
   }
   
   else {
      printf("%d\n", num3);
   }

   return 0;
}