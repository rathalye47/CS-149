#include <stdio.h>
#include <string.h>

int main(void) {

   char str[51];
   
   while (fgets(str, 50, stdin) != NULL) {
      if (str[strlen(str) - 1] == '\n') {
         str[strlen(str) - 1] = '\0';
      }
      
      if ((strcmp(str, "Done") == 0) || (strcmp(str, "done") == 0) || (strcmp(str, "d") == 0)) {
         return 0;
      }
      
      for (int i = strlen(str) - 1; i >= 0; i--) {
         printf("%c", str[i]);
      }
      
      printf("\n");
   }
      
   return 0;
}
