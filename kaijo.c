#include <stdio.h>
 
double an(double n)
{
double factorial = 1.0;
for(int i =1; i <= n; i++){  //引数と回数がいっちするまで
factorial *=(double)i;  //factorial=i*factorial
}
return factorial;
}
int main(){

  double a,b,c;

  a=6.0;

  b=an(a);

  printf("%lf",b);
}