#include <stdio.h>
#include <string.h>

int main(void) {
   const int MAX_NUM_WORDS = 20;
   const int MAX_WORD_LENGTH = 10;
   char userValues[MAX_NUM_WORDS][MAX_WORD_LENGTH];
   int numWords;
   char searchCharacter;
   
   scanf("%d", &numWords);
   
   for (int i = 0; i < numWords; i++) {
      scanf("%s", &(userValues[i]));
   }
   
   scanf(" %c", &searchCharacter);
   
   for (int i = 0; i < numWords; i++) {
      if (strchr(userValues[i], searchCharacter) != NULL) {
         printf("%s,", userValues[i]);
      }
   }
   
   printf("\n");

   return 0;
}