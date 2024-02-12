#include<stdio.h>
#include<math.h>
#include <malloc.h>

double Func_LineX(int ConstNum,double CX[],double time){

    return time;

}

double Func_LineY(int ConstNum,double CY[],double time){
    return -1.120*exp(-1.98*time)+1.485;
}

double Func_LineXDt(int ConstNum,double CX[],double time){
    return 2*time;
}

double Func_LineYDt(int ConstNum,double CY[],double time){
    return 2*time;
}

double Combination(int n, int m){
    return;
}


double* Sprine(int PointNum,double Points[][2],double Consts[][2],double Combination[]){
    int i;
    Combination[0]=1;
    Combination[1]=PointNum;
    Combination[PointNum-1]=1;
    Combination[PointNum-2]=PointNum;
    int HalfPointNum_1=PointNum/2+1;
    
    for(i=2;i<HalfPointNum_1;i++){
        Combination[i]=Combination[i-1]*()
    }




    for(i=0;i<PointNum;i++){
        C[i][0]=PointNum
    }
}

int main(void){
    double XT,YT;
    double YTBef;
    double TimeSt=0,TimeEn=2;
    double DT=0.01;
    double ReadT;

    //離散点の数をPointNumに、N個の離散点の座標をpoints[N][2]に与える。Combination（数学のnCm）とConstsはここでは設定しない（関数でやる）
    //malloc関数を使った後はfree関数でメモリを開放すること。
    int PointNum=20;
    double* Points=(double*)malloc(PointNum*2*sizeof(double));
    double* Consts=(double*)malloc(PointNum*2*sizeof(double));
    double* Combination=(double*)malloc(PointNum*2*sizeof(double));

    FILE* WriteTxt=fopen("write.txt","w");

    ReadT=TimeSt;



    while(ReadT<=TimeEn){

    }

    fclose(WriteTxt);
    free()
    return 0;
}

