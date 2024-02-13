#include<stdio.h>
#include<math.h>
#include <malloc.h>

float Func_LineX(int ConstNum,float CX[],float time){

    return time;

}

float Func_LineY(int ConstNum,float CY[],float time){
    return -1.120*exp(-1.98*time)+1.485;
}

float Func_LineXDt(int ConstNum,float CX[],float time){
    return 2*time;
}

float Func_LineYDt(int ConstNum,float CY[],float time){
    return 2*time;
}

float Combinations(int n, int m){
    return 0;
}


void GetCombinations(int PointNum,int Combinations[]){
    int i;

    //Use mathematical properties of Combinationss
    //
    //nC0=1
    //nC1=n
    //nCm=(n-m+1)*nCm/m
    //nCn-m=nCm
    //
    
    Combinations[0]=1;
    Combinations[1]=PointNum;
    Combinations[PointNum-1]=1;
    Combinations[PointNum-2]=PointNum;

    int HalfPointNum_1=PointNum/2+1;
    int Numerator = PointNum;
    int Denominator=1;
    for(i=2;i<HalfPointNum_1;i++){
        Numerator-=1;
        Denominator+=1;
        Combinations[i]=Combinations[i-1]*Numerator/Denominator;
        Combinations[PointNum-1-i]=Combinations[i];
    }

}

void GetConstsX(int PointNum,float PointsX[],int Combinations[],float ConstsX[]){
    int i;
    for(i=0;i<PointNum;i++){
        ConstsX[i]=PointsX[i]*Combinations[i];
    }

}
void GetConstsY(int PointNum,float PointsY[],int Combinations[],float ConstsY[]){
    int i;
    for(i=0;i<PointNum;i++){
        ConstsY[i]=PointsY[i]*Combinations[i];
    }
}


float BezierX(int PointNum,float PointsX[],int Combinations[],float time){
    return 0;
}
float BezierY(int PointNum,float PointsY[],int Combinations[],float time){
    return 0;
}


int main(void){
    int i,j,k;
    //配列の宣言
    int PointNum=21;
    float* PointsX=(float*)malloc(PointNum*sizeof(float));
    float* PointsY=(float*)malloc(PointNum*sizeof(float));
    int* Combinations=(int*)malloc((PointNum)*sizeof(int));
    float* ConstsX=(float*)malloc(PointNum*sizeof(float));
    float* ConstsY=(float*)malloc(PointNum*sizeof(float));

    int PointIDNum=PointNum-1;

    //Points(離散点)の入力
    //離散点の数をPointNumに、N個の離散点の座標をpoints[N][2]に与える。Combinations（数学のnCm）とCombinationsはここでは設定しない（関数でやる）
    //malloc関数を使った後はfree関数でメモリを開放すること。
    FILE* ReadTxt=fopen("data2.txt","r");

    if(ReadTxt==NULL){
        printf("Can not open data.txt\n");
        return 0;
    }

    printf("Points\n");
    for(i=0;i<PointNum;i++){
        fscanf(ReadTxt,"%f %f",&PointsX[i],&PointsY[i]);
        printf("%15f,%15f\n",PointsX[i],PointsY[i]);
    }


    //二項係数の計算
    GetCombinations(PointNum,Combinations);
    printf("Combinations\n");
    for(i=0;i<PointNum;i++){
        printf("%3dC%3d:%d\n",PointNum,i,Combinations[i]);
    }

    //ベジエ曲線の重み計算
    GetConstsX(PointNum,PointsX,Combinations,ConstsX);
    GetConstsY(PointNum,PointsY,Combinations,ConstsY);

    //ベジエ曲線のプロット
    float XT,YT;
    float TimeSt=0,TimeEn=1;
    float DT=0.01;
    float ReadT;
    float FuncT;

    FILE* WriteTxt=fopen("write2.txt","w");

    if(WriteTxt==NULL){
        printf("Can not open write2.txt\n");
        return 0;
    }

    printf("LOG1\n");

    ReadT=TimeSt;
    while(ReadT<TimeEn){

        XT=0;
        YT=0;
        for(i=0;i<PointNum;i++){
            FuncT=pow(ReadT,i)*pow(1-ReadT,PointNum-i);
            XT+=FuncT*ConstsX[i];
            YT+=FuncT*ConstsY[i];
        }
//-------------------------------------------------
        fprintf(WriteTxt,"%f %f\n",XT,YT);
//-------------------------------------------------
        ReadT+=DT;
    }

    fclose(WriteTxt);
        printf("LOG2\n");
    fclose(ReadTxt);
    printf("LOG2\n");

    free(PointsX);
        printf("LOG2\n");
    free(PointsY);
        printf("LOG2\n");
    free(Combinations);
        printf("LOG2\n");
    free(ConstsX);
        printf("LOG2\n");
    free(ConstsY);
        printf("LOG2\n");
    return 0;
}

