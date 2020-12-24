#include<stdio.h>
#include<math.h>

int main()
{
    double j,ans;
    int i;

    j=1.0;

    for(i=1; i<=1000000; i++){
        if(i%2 == 0){
            //printf("%lf\n",j);
            j=j + (1.0/(2.0*i + 1.0));
        }
        else{
            //printf("%lf\n",j);
            j=j - (1.0/(2.0*i + 1.0));
        }
    }
    ans=j*4;

    printf("%lf",ans);


    return 0;

}