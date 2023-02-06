#include <stdio.h>
#include <string.h>

int CalcNumCharacters(char* userString, char userChar) {
   int count = 0;
   
   for (int i = 0; i < strlen(userString); i++) {
      if (userString[i] == userChar) {
         count++;
      }
   }
   
   return count;
}

int main(void) {

   char userChar;
   scanf("%c", &userChar);
   
   const int INPUT_STR_SIZE = 50; 
   char userStr[INPUT_STR_SIZE];
   
   scanf("%s", userStr);
   
   int numChars = CalcNumCharacters(userStr, userChar);
   
   if (numChars == 1) {
      printf("%d %c\n", numChars, userChar);
   }
   
   else {
      printf("%d %c's\n", numChars, userChar);
   }

   return 0;
}