#include <stdio.h>
 
double an(int n)
{
double factorial = 1.0;
for(int i =1; i <= n; i++){
factorial *=(double)i;
}
return factorial;
}
int main(){

  double a,b,c;

  a=6.0;

  b=an(a);

  printf("%lf",b);
}