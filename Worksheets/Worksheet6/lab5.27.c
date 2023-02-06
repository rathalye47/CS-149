#include <stdio.h>
#include <string.h>

int main(void) {

   char str[51];
   char str2[51];
   int j = 0;
   
   while (fgets(str, 50, stdin) != NULL) {
      for (int i = 0; i < strlen(str); i++) {
         if (str[i] != ' ') {
            str2[j] = str[i];
            j++;
         }
      }
   }
   
   if (str2[strlen(str2) - 1] == '\n') {
      str2[strlen(str2) - 1] = '\0';
   }
   
   int i = 0;
   int k = strlen(str2) - 1;
   
   if (strlen(str2) == 1) {
      printf("palindrome: %s", str);
      return 0;
   }
   
   while (i != k && i < strlen(str2) && k > -1) {
      if (str2[i] != str2[k]) {
         printf("not a palindrome: %s\n", str);
         return 0;
      }
      
      i++;
      k--;
   }
      
   printf("palindrome: %s\n", str);
      
   return 0;
}