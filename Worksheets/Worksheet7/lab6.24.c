#include <stdio.h>

void SwapValues(int* userVal1, int* userVal2, int* userVal3, int* userVal4) {
   int temp;
   temp = *userVal1;
   *userVal1 = *userVal2;
   *userVal2 = temp;
   
   int temp2;
   temp2 = *userVal3;
   *userVal3 = *userVal4;
   *userVal4 = temp2;
}

int main(void) {
   
   int userVal1;
   int userVal2;
   int userVal3;
   int userVal4;

   scanf("%d", &userVal1);
   scanf("%d", &userVal2);
   scanf("%d", &userVal3);
   scanf("%d", &userVal4);
   
   SwapValues(&userVal1, &userVal2, &userVal3, &userVal4);
   
   printf("%d %d %d %d\n", userVal1, userVal2, userVal3, userVal4);
   
   return 0;
}