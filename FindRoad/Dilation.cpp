#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>

void DilateMap(int8_t* Map,int SizeX,int SizeY,int8_t* DilatedMap,int DilateNum);
void ReMakeMap(int8_t* MapDefault,int8_t* ReMap,int MaxMoveX_P,int MaxMoveX_N,int MaxMoveY_P,int MaxMoveY_N,int SizeX,int SizeY,int8_t MapJudge,int8_t MapNoUse,int8_t MapCanUse);

int main(void){
    int i,j,k;

    //膨張処理のサイズ
    int DilateNum=15;

	//マップのサイズの入力

	const int SizeY = 100;
	const int SizeX = 100;

	//map.txtでは
	//const int SizeY = 38;
	//const int SizeX = 43;

	//マップの入力(ここではテキストファイルからとっているが適時変える)。stdint.hで定義されるint8_t型
	FILE* Map=fopen("map3.txt","r");
	if(Map==NULL){
		printf("Can not open map.txt\n");
	}
	int SizeY_read,SizeX_read;
	int8_t* MapDefault=(int8_t*)malloc(SizeX*SizeY*sizeof(int8_t));
	int8_t* ReadMap=MapDefault;
	for(i=0;i<SizeY;i++){
		for(j=0;j<SizeX;j++){
			fscanf(Map,"%d	",&*ReadMap);
			printf("%3d ",*ReadMap);
			ReadMap+=1;
		}
		printf("\n");
	}

    int8_t* DilatedMap=(int8_t*)malloc(SizeX*SizeY*sizeof(int8_t));

    DilateMap(MapDefault,SizeX,SizeY,DilatedMap,DilateNum);

    free(MapDefault);
    free(DilatedMap);
    return 0;
}

void DilateMap(int8_t* MapDefault,int SizeX,int SizeY,int8_t* DilatedMap,int DilateNum){

    int CircleSize=2*DilateNum+1;
    int8_t* CircleArrey=(int8_t*)malloc(CircleSize*CircleSize*sizeof(int8_t));
    int i,j,k;

    int DilateNum_2=DilateNum*DilateNum;

    int8_t* ReadMap;


    printf("Made Circle Arrey.\n");
    ReadMap=CircleArrey;
    for(i=0;i<CircleSize;i++){
        for(j=0;j<CircleSize;j++){
            if((DilateNum-i)*(DilateNum-i)+(DilateNum-j)*(DilateNum-j)<=DilateNum_2){
                *ReadMap=100;
            }else{
                *ReadMap=0;
            }
            printf("%4d   ",*ReadMap);
            ReadMap+=1;
        }
        printf("\n");
    }

    ReadMap=DilatedMap;
    for(i=0;i<SizeY;i++){
        for(j=0;j<SizeX;j++){
            *ReadMap=0;
            ReadMap+=1;
        }
    }

    int ReSizeX=SizeX+2*DilateNum;
    int ReSizeY=SizeY+2*DilateNum;
    int8_t* ReSizedMap=(int8_t*)malloc((SizeX+2*DilateNum)*(SizeY+2*DilateNum)*sizeof(int8_t));
    ReMakeMap(DilatedMap,ReSizedMap,DilateNum,DilateNum,DilateNum,DilateNum,SizeX,SizeY,50,100,0);

    int ReSizeX
    ReadMap=






    free(ReSizedMap);
    free(CircleArrey);

}


void ReMakeMap(int8_t* MapDefault,int8_t* ReMap,int MaxMoveX_P,int MaxMoveX_N,int MaxMoveY_P,int MaxMoveY_N,int SizeX,int SizeY,int8_t MapJudge,int8_t MapNoUse,int8_t MapCanUse){
	int8_t* ReadReMap=ReMap;
	int8_t* ReadDefMap=MapDefault;
	int   i,j,k;
	int ReSizeY=SizeY+MaxMoveY_P+MaxMoveY_N;
	int ReSizeX=SizeX+MaxMoveX_P+MaxMoveX_N;


	for (i = 0; i <MaxMoveY_P; i++){
		for(j=0;j<ReSizeX;j++){
			*ReadReMap = MapNoUse;
			ReadReMap +=1;
		}
	}

	for (i = 0; i < SizeY; i++){
		for(j=0;j<MaxMoveX_P;j++){
			*ReadReMap = MapNoUse;
			ReadReMap+=1;
		}

		for (j =0 ; j < SizeX; j++){
			if(*ReadDefMap>MapJudge||*ReadDefMap==-1){
				*ReadReMap=MapNoUse;
				ReadReMap+=1;
			}else{
				*ReadReMap=MapCanUse;
				ReadReMap+=1;
			}
			ReadDefMap+=1;
		}

		for(j=0;j<MaxMoveX_N;j++){
			*ReadReMap=MapNoUse;
			ReadReMap+=1;
		}
	}

	for (i = 0; i < MaxMoveY_N; i++){
		for(j=0;j<ReSizeX;j++){
			*ReadReMap=MapNoUse;
			ReadReMap+=1;
		}
	}
}