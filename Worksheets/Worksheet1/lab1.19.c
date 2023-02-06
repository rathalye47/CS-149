#include <stdio.h>

int main(void) {
   int userNum;
   
   printf("Enter integer:\n");
   scanf("%d\n", &userNum);
   printf("You entered: %d\n", userNum);
   printf("%d squared is %d\n", userNum, userNum * userNum);
   printf("And %d cubed is %d!!\n", userNum, userNum * userNum * userNum);
   
   int userNum2;
   printf("Enter another integer:\n");
   scanf("%d\n", &userNum2);
   printf("%d + %d is %d\n", userNum, userNum2, userNum + userNum2);
   printf("%d * %d is %d\n", userNum, userNum2, userNum * userNum2);
   
   return 0;
}