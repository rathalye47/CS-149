#include <stdio.h>

int main(void) {

   // Variables to store values of userNum and x.
   int userNum;
   int x;
   
   // Reads user input.
   scanf("%d", &userNum);
   scanf("%d", &x);
   
   // Performs calculations.
   int result = userNum / x;
   printf("%d ", result);
   result = result / x;
   printf("%d ", result);
   result = result / x;
   printf("%d\n", result);

   return 0;
}