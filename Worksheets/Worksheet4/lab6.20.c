#include <stdio.h>

double LapsToMiles(double userLaps) {
   return userLaps * 0.25;
}

int main(void) {

   double numLaps;
   double miles;
   
   scanf("%lf", &numLaps);
   
   miles = LapsToMiles(numLaps);
   printf("%0.2lf\n", miles);

   return 0;
}