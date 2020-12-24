#include<stdio.h>
#include<math.h>
//oppai is good
int main()
{
    double j,ans,four;
    int i;
    four=4;

    j=1.0;

    for(i=1.00000; i<=100; i+=1.00){
        if(i%2 == 0){
            printf("%0.20lf\n",j);
            j=j + (1.000/(2.000*(double)i + 1.000));
        }
        else{
            printf("%0.20lf\n",j);
            j=j - (1.0/(2.0*(double)i + 1.0));
        }
    }
    ans=four*j;

    printf("%0.8000lf",ans);


    return 0;

}