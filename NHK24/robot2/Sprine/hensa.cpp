#include<stdio.h>
#include<math.h>

int main(void){

    const int DataNum=21;
    double t,t2;
    int i,j,k;

    double hensa=0;

    FILE* datatxt=fopen("data.txt","r");
    FILE* writetxt=fopen("write.txt","r");

    double data[DataNum],write[DataNum];

    i=0;
    int ReadNum=0;
    do{
        fscanf(datatxt,"%lf %lf",&t,&data[ReadNum]);

        fscanf(writetxt,"%lf %lf",&t2,&write[ReadNum]);

        printf("%lf,%lf\n",data[ReadNum],write[ReadNum]);

        hensa+=(data[ReadNum]-write[ReadNum])*(data[ReadNum]-write[ReadNum]);

        ReadNum+=1;
        i++;
    }while(i<DataNum);

    hensa/=ReadNum;
    hensa=sqrt(hensa);

    printf("hensa=%lf",hensa);

    fclose(writetxt);
    fclose(datatxt);




    return 0;
}