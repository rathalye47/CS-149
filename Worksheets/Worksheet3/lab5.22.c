#include <stdio.h>

int main(void) {

   const int NUM_ELEMENTS = 20;
   int userValues[NUM_ELEMENTS];
   int numIntegers;
   int lowerBound;
   int upperBound;
   
   scanf("%d", &numIntegers);
   
   for (int i = 0; i < numIntegers; i++) {
      scanf("%d", &(userValues[i]));
   }
   
   scanf("%d", &lowerBound);
   scanf("%d", &upperBound);
   
   for (int i = 0; i < numIntegers; i++) {
      if ((userValues[i] >= lowerBound) && (userValues[i] <= upperBound)) {
         printf("%d,", userValues[i]);
      }
   }
   
   printf("\n");

   return 0;
}