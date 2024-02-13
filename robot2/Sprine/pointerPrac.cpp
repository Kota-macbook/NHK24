#include<stdio.h>
#include <malloc.h>

int* Func1(int* XAdr){
    *XAdr=10;
    int* Ar=(int*)malloc(10*sizeof(int));
    return Ar;
}

int main(void){
    int X;
    int* XAdr=&X;

    int* Arrey=Func1(XAdr);

    printf("%d",X);

    free(Arrey);


    return 0;
}