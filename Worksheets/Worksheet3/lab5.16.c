#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;         // Number of input integers
   int userVals[NUM_ELEMENTS];          // Array to hold the user's input integers

   scanf("%d", &NUM_ELEMENTS);
   
   for (int i = 0; i < NUM_ELEMENTS; i++) {
      scanf("%d", &(userVals[i]));
   }
   
   for (int i = NUM_ELEMENTS - 1; i >= 0; i--) {
      printf("%d,", userVals[i]);
   }
   
   printf("\n");

   return 0;
}