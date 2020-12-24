#include<stdio.h>
#include<math.h>

double logarithm(double a){
    //aがlog yのyの部分
    double k=0;
    double b;


    while(1){
        b=(2/(2*k+1))*pow((a-1)/(a+1),2*k+1)+b; //Σだから +=を使う

        if(k>2000){
            break;
        }

        k++;

    }
    b=b*pow(10,6);
    return b; 
}
int main(){
    double y,x,z,l,j; //yが多項式のやつ xは標準ライブラリから引っ張り出した
    long long z1,l1;

    y=3;
    z=logarithm(y);

    printf("logarithm=%7.0lf",z);

    l=log(y)*pow(10,6);
    l1=l;

    printf(" C=%d",l1);



}