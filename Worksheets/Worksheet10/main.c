#include<stdio.h>
#include<string.h>

#include "ItemToPurchase.h"

int main(void) {
 
   char c;
   ItemToPurchase item1;
   ItemToPurchase item2;
   
   printf("Item 1\n");
   printf("Enter the item name:\n");
   fgets(item1.itemName, 50, stdin);
   int len1 = strlen(item1.itemName);
   item1.itemName[len1 - 1] = '\0';
   printf("Enter the item price:\n");
   scanf("%d", &(item1.itemPrice));
   printf("Enter the item quantity:\n\n");
   scanf("%d", &(item1.itemQuantity));
   
   c = getchar();
   while(c != '\n' && c != EOF) {
      c = getchar();
   }
   
   printf("Item 2\n");
   printf("Enter the item name:\n");
   fgets(item2.itemName, 50, stdin);
   int len2 = strlen(item2.itemName);
   item2.itemName[len2 - 1] = '\0';
   printf("Enter the item price:\n");
   scanf("%d", &(item2.itemPrice));
   printf("Enter the item quantity:\n\n");
   scanf("%d", &(item2.itemQuantity));
   
   printf("TOTAL COST\n");
   PrintItemCost(item1);
   PrintItemCost(item2);
   printf("\n");
   
   int total = (item1.itemQuantity * item1.itemPrice) + (item2.itemQuantity * item2.itemPrice);
   printf("Total: $%d\n", total);
   
   return 0;
}