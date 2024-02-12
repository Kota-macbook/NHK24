#include<stdio.h>
#include<math.h>

double Func_LineX(double time){
    return time*time;
}

double Func_LineY(double time){
    return 2*time;
}

int main(void){
    double XT,YT;
    double TimeSt=2,TimeEn=10;
    double DT=0.1;
    double ReadT;

    FILE* WriteTxt=fopen("write.txt","w");

    ReadT=TimeSt;
    while(ReadT<TimeEn){
        XT=Func_LineX(ReadT);
        YT=Func_LineY(ReadT);
//-------------------------------------------------
        fprintf(WriteTxt,"%lf %lf\n",XT,YT);
//-------------------------------------------------
        ReadT+=DT;
    }
    fclose(WriteTxt);
    return 0;
}