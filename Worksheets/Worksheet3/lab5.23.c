#include <stdio.h>
#include <limits.h>

int main(void) {

   const int NUM_ELEMENTS = 20;
   int userValues[NUM_ELEMENTS];
   int numIntegers;
   int i;
   
   scanf("%d", &numIntegers);
   
   for (i = 0; i < numIntegers; i++) {
      scanf("%d", &(userValues[i]));
   }
   
   int min1 = INT_MAX;
   int min2 = INT_MAX;
   
   for (i = 0; i < numIntegers; i++) {
      if (userValues[i] < min1) {
         min2 = min1;
         min1 = userValues[i];
      }
      
      else if ((userValues[i] < min2) && (userValues[i] != min1)) {
         min2 = userValues[i];
      }
   }
   
   printf("%d and %d\n", min1, min2);

   return 0;
}