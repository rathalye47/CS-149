#include<stdio.h>
#include <string.h>

int main(void) {

   char userText[100];
   char firstName[50];
   char lastName[50];
   
   while (1) {
      printf("Enter input string:\n");
      fgets(userText, 100, stdin);
      
      if (userText[0] == 'q') {
         break;
      }
      
      if (strchr(userText, ',') == NULL) {
         printf("Error: No comma in string.\n\n");
         continue;
      }
      
      int i;
      int j;
      int k = 0;
      
      for (i = 0; userText[i] != ',' && userText[i] != ' '; i++) {
         firstName[i] = userText[i];
      }
      
      firstName[i] = '\0';
      
      for (j = i; j < strlen(userText); j++) {
         if ((userText[j] != ',') && (userText[j] != ' ')) {
            lastName[k] = userText[j];
            k++;
         }
      }
      
      lastName[k] = '\0';
      
      printf("First word: %s\n", firstName);
      printf("Second word: %s\n", lastName);
   }
   
   return 0;
}