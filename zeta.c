#include<stdio.h>
#include<math.h>

double zeta(double s){  //戻り値が答え

    int n=1;
    double a,b;
    a=0;

    while(1){

        if(n>=2000){
            break;
        }
        b=pow((double)n,s);
        a=(1.0000/b)+a;
        printf("%lf  %lf\n",b,a);
        n++;
    }
    return a;
}
int main(){
    double a,b;
    a=3;
    b=zeta(a);

    printf("%lf",b);
}