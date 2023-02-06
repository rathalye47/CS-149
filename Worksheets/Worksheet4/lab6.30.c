#include <stdio.h>

int MaxNumber(int num1, int num2, int num3, int num4) {
   if ((num1 >= num2) && (num1 >= num3) && (num1 >= num4)) {
      return num1;
   }
   
   else if ((num2 >= num1) && (num2 >= num3) && (num2 >= num4)) {
      return num2;
   }
   
   else if ((num3 >= num1) && (num3 >= num2) && (num3 >= num4)) {
      return num3;
   }
   
   else {
      return num4;
   }
}

int MinNumber(int num1, int num2, int num3, int num4) {
   if ((num1 <= num2) && (num1 <= num3) && (num1 <= num4)) {
      return num1;
   }
   
   else if ((num2 <= num1) && (num2 <= num3) && (num2 <= num4)) {
      return num2;
   }
   
   else if ((num3 <= num1) && (num3 <= num2) && (num3 <= num4)) {
      return num3;
   }
   
   else {
      return num4;
   }
}
   
int main(void) {

   int num1;
   int num2;
   int num3;
   int num4;
   int max;
   int min;
   
   scanf("%d", &num1);
   scanf("%d", &num2);
   scanf("%d", &num3);
   scanf("%d", &num4);
   
   max = MaxNumber(num1, num2, num3, num4);
   min = MinNumber(num1, num2, num3, num4);
   
   printf("Maximum is %d\n", max);
   printf("Minimum is %d\n", min);

   return 0;
}