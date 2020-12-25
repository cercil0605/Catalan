#include<stdio.h>
#include<math.h>

double zeta(double s){  //戻り値が答え

    int n=1;
    double ans,a,b;
    a=0;

    while(1){

        if(n>=20000){  //回数増やすほど精度が増す（？）
            break;
        }
        b=pow((double)n,s);
        a=(1.0000/b)+a;
        //printf("%lf  %lf\n",b,a);
        n++;
    }
    return a;
}

double calc(){  //ゼータ関数の計算も応用したカタラン定数を求める計算
    double a,b,c;
    int k;
    k=0;

    while(1){

        if(k>=20000){  //この回数でこの数→0.91596559425534807000000000000000000000000000000000
            break;
        }
        a+=(zeta(2*(double)k+1)*(double)k)/(pow(4,2*(double)k));
        k++;
    }
    b=1.000-a;
    return b;
}

int main(){
    double g;
    g=calc();

    printf("%0.50lf",g);
}

