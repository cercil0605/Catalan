#include<stdio.h>
#include<math.h>

double an(double n)
{
double factorial = 1.0;
for(int i =1; i <= n; i++){
factorial *=(double)i;
}
return factorial;
}

double calc(){
    int n=1;
    double a,b,c,G;
    G=0;
    a=0;
    b=0;
    c=0;

    while(1){
        a=pow(-1.0,(double)n-1.0)*pow(2.0,8.0*(double)n)*((pow((double)n,2.0)*40.0-24.0*(double)n+3.0))*pow(an(2.0*(double)n),3.0)*pow(an((double)n),2.0);  //分子
        b=pow((double)n,3.0)*(2.0*n-1.0)*pow(an(4.0*n),2.0);   //分母

        if(n>24){
            break;
        }
        //printf("%lf ",a);
        //printf("%lf ",b);

        c+=a/b;  //級数表現のため
        printf("%lf\n",c);

        n++;
    }
    G=c/64.0;
    return G;
}

int main(){
    double a;
    a=calc();
    printf("%0.20lf",a);
    
}