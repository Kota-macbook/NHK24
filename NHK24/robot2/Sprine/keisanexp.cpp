#include<stdio.h>
#include<math.h>

int main(void){
    double x=0;
    int i;
    for(i=0;i<22;i++){
        x+=exp(-1.98*i*0.1);
        printf("i=%d\n",i);
    }
    printf("%lf\n",x);
    return 0;
}