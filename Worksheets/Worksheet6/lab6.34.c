#include <stdio.h>
#include <stdbool.h>

bool IsArrayMult10(int inputVals[], int numVals) {
   int count = 0;
   
   for (int i = 0; i < numVals; i++) {
      if (inputVals[i] % 10 == 0) {
         count++;
      }
   }
   
   if (count == numVals) {
      return true;
   }
   
   else {
      return false;
   }
}

bool IsArrayNoMult10(int inputVals[], int numVals) {
   int count = 0;
   
   for (int i = 0; i < numVals; i++) {
      if (inputVals[i] % 10 == 0) {
         count++;
      }
   }
   
   if (count == 0) {
      return true;
   }
   
   else {
      return false;
   }
}
   

int main(void) {

   int listSize;
   scanf("%d", &listSize);
   
   int listValues[listSize];
   
   for (int i = 0; i < listSize; i++) {
      scanf("%d", &(listValues[i]));
   }
   
   if (IsArrayMult10(listValues, listSize)) {
      printf("all multiples of 10\n");
   }
   
   else if (IsArrayNoMult10(listValues, listSize)) {
      printf("no multiples of 10\n");
   }
   
   else {
      printf("mixed values\n");
   }
   
   return 0;
}