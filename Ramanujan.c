#include<stdio.h>
#include<math.h>

double an(int n)  //階乗する関数  引数が階乗したいやつ 結果をreturn
{
double factorial = 1.0;
for(int i =1; i <= n; i++){
factorial *=(double)i;
}
return factorial;
}

double calc(){   //ラマヌジャンの円周率計算するところ（πの形にする）

    int i1;
    double a,b,c,k,d,e,f,g,h,i,ans;

    k=0; //大前提
    i1=0;

    while(1){
    a=pow(-1,k);  //(-1)^k

    b=an(4*k);

    c=1123+21460*k;  //(1123+21460*k)

    d=a*b*c; //分子

    e=pow(882,2*k+1);
    
    f=an(k);


    g=pow(4,k);  //4^k
    h=pow(g*f,4);  //((4^k)*k!)^4
    i=e*h; //分母

        ans+=(d/i);
        //printf("a=%lf b=%lf c=%lf d=%lf e=%lf f=%lf g=%lf h=%lf\n",a,b,c,d,e,f,g,h);
        //printf("%d   :  %lf\n",i1,ans);


        if(i1>=10){  //flag
            break;
        }
        i1++;
        k++;
    }

    ans=4*(1/ans); //計算コスト抑えるために4掛ける必要はなさそう（逆数とるのは必須）
    return ans;
}

int main(){
    double a,b;

    //b=4*(1/calc());
    a=calc();


    printf("%0.30lf\n",a);
}