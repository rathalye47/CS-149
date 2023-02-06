#include <stdio.h>
#include <math.h>

int main(void) {
   double x;
   double y;
   double z;
   
   // Reads user input.
   scanf("%lf", &x);
   scanf("%lf", &y);
   scanf("%lf", &z);

   // Outputs x to the power of z.
   double result1 = pow(x, z);
   printf("%0.2lf ", result1);
   
   // Outputs x to the power of (y to the power of 2).
   double result2 = pow(x, (pow(y, 2)));
   printf("%0.2lf ", result2);
   
   // Outputs the absolute value of y.
   double result3 = fabs(y);
   printf("%0.2lf ", result3);
   
   // Outputs the square root of (xy to the power of z).
   double result4 = sqrt(pow(x * y, z));
   printf("%0.2lf\n", result4);
   
   return 0;
}