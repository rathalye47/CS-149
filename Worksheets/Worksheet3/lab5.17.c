#include <stdio.h>
#include <stdlib.h>

int main(void) {
   const int NUM_ELEMENTS = 20;
   int userValues[NUM_ELEMENTS];    // Set of data specified by the user
   int count = 0;
   int i;

   for (i = 0; i < NUM_ELEMENTS; i++) {
      scanf("%d", &(userValues[i]));
      if (userValues[i] < 0) {
         break;
      }
      
      count++;
   }

   if (count > 9) {
      printf("Too many numbers\n");
   }
   
   else {
      printf("Middle item: %d\n", userValues[i/2]);
   }
   
   return 0;
}