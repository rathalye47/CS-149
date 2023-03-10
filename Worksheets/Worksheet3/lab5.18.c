#include <stdio.h>

int main(void) {
   const int NUM_ELEMENTS = 20;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user
   int numIntegers;
   int threshold;
   
   scanf("%d", &numIntegers);
   
   for (int i = 0; i < numIntegers; i++) {
      scanf("%d", &(userValues[i]));
   }
   
   scanf("%d", &threshold);
   
   for (int i = 0; i < numIntegers; i++) {
      if (userValues[i] <= threshold) {
         printf("%d,", userValues[i]);
      }
   }
   
   printf("\n");

   return 0;
}