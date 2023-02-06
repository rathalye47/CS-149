#include <stdio.h>
#include <string.h>
#include <ctype.h>

void RemoveNonAlpha(char userString[], char userStringAlphaOnly[]) {
   int j = 0;
   
   for (int i = 0; i < strlen(userString); i++) {
      if (isalpha(userString[i])) {
         userStringAlphaOnly[j] = userString[i];
         j++;
      }
   }
}

int main(void) {

   const int INPUT_STR_SIZE = 50;
   char userStr[INPUT_STR_SIZE];
   char alphaOnly[INPUT_STR_SIZE];
   
   fgets(userStr, INPUT_STR_SIZE, stdin);
   
   RemoveNonAlpha(userStr, alphaOnly);
   printf("%s", alphaOnly);
   printf("\n");

   return 0;
}