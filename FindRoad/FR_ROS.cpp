#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>

//Astarで返す配列の要素数を何個単位にするか。大きいほど動作が早くなるがメモリの無駄が多い。
#define BlockSizeOfArrey 100

void QueAdd(int NowQueNum, int X, int Y, float CostC,float CostAll, int *QueX, int *QueY, float *QueCostC, float* QueCostAll);
void ReMakeMap(int8_t* MapDefault,int8_t* ReMap,int MaxMoveX_P,int MaxMoveX_N,int MaxMoveY_P,int MaxMoveY_N,int SizeX,int SizeY,int8_t MapJudge,int8_t MapNoUse,int8_t MapCanUse);
int* Astar(int* NodeNum,int8_t* MapDefault,int SizeX,int SizeY,float* Start,float* Goal,float OpenNode[][3],int OpenNodeNum,int8_t MapJudge);

//CostHFUNCTION-------------------------------
float FuncCostH(int X,int Y){
	return X+Y;//sqrt(X*X+Y*Y);
}
//---------------------------------------


int main(void){
	int i,j,k;

//入力
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

	//スタートとゴールの座標の入力
	float Start[2]={0,0};
	float Goal[2]={0,100};

	//オープンするノードの設定（入力するか、変えなくてもよい）。ここでは隣接する左右上下斜めを選択している。
    float	OpenNode[][3]=	{{-1		,0		,1		},
                                {1		,0		,1		},
                                {1		,-1		,sqrt(2)	},
                                {0		,-1		,1		},
                                {-1		,-1		,sqrt(2)	},
                                {-1		,1		,sqrt(2)	},
                                {0		,1		,1		},
                                {1		,1		,sqrt(2)	}
                                };



	const int8_t			MapJudge = 50;
	const int			OpenNodeNum=(int)sizeof(OpenNode)/(sizeof(float)*3);

	int* AnsNodes;
    int AnsNodeNum;

	AnsNodes= Astar(&AnsNodeNum,MapDefault,SizeX,SizeY,Start,Goal,OpenNode,OpenNodeNum,MapJudge);

    //処理の成功判定　失敗なら-1が返ってくる
    if(AnsNodeNum==-1){
        printf("Faild to finding road.\n");
        return -1;
    }

	FILE* WriteTxt=fopen("data3.txt","w");
    printf("NodeNum=%d\n",AnsNodeNum);
    for(i=0;i<AnsNodeNum;i++){
        printf("(%d,%d)\n",AnsNodes[2*i],AnsNodes[2*i+1]);
		fprintf(WriteTxt,"%d	%d\n",AnsNodes[2*i],-AnsNodes[2*i+1]);
    }

	//ばぶりトピック名

    free(AnsNodes);
	free(MapDefault);
}


int* Astar(int* AnsNodeNum,int8_t* MapDefault,int SizeX,int SizeY,float* Start,float* Goal,float OpenNode[][3],int OpenNodeNum,int8_t MapJudge){
	int i,j,k;
	// setup---------------------------------------------------------------------
	
	const int8_t 			MapNoUse = 100;
	const int8_t 			MapCanUse = 0;
	const int8_t 			MapOpened = 1;

	//--------------------------------------------------------------------------
	//文字の定義----------------------------------------------------------------
	



	//--------------------------------------------------------------------------
	int			MaxMoveX_P=0,MaxMoveY_P=0;
	int			MaxMoveX_N=0,MaxMoveY_N=0;

	for(i=0;i<OpenNodeNum;i++){
		j=OpenNode[i][0];
		k=OpenNode[i][1];

		if(j>0){
			if(j>MaxMoveX_P){
				MaxMoveX_P=j;
			}
		}else{
			if(abs(j)>MaxMoveX_N){
				MaxMoveX_N=abs(j);
			}
		}

		if(k>0){
			if(k>MaxMoveY_P){
				MaxMoveY_P=k;
			}
		}else{
			if(abs(k)>MaxMoveY_N){
				MaxMoveY_N=abs(k);
			}
		}
	}

    MaxMoveX_P+=1;
    MaxMoveX_N+=1;
    MaxMoveY_P+=1;
    MaxMoveY_N+=1;

	//処理途中のマップの拡張サイズ
	//printf("MaxX,MaxY,PX:%d,PY:%d,NX:%d,NY:%d\n",MaxMoveX_P,MaxMoveY_P,MaxMoveX_N,MaxMoveY_N);



	// input map-----------------------------------------------------------------
	float StartX=Start[0];
	float StartY=Start[0];
	float GoalX=Goal[0];
	float GoalY=Goal[1];
	//----------------------------------------------------------------------------

    //処理の簡単化のためにスタート、ゴールを入れ替える
    float UseForExchange;
    UseForExchange=StartX;
    StartX=GoalX;
    GoalX=UseForExchange;
    UseForExchange=StartY;
    StartY=GoalY;
    GoalY=UseForExchange;

	// ReMake large map------------------------------------------------------------
	int ReSizeY=SizeY+MaxMoveY_P+MaxMoveY_N;
	int ReSizeX=SizeX+MaxMoveX_P+MaxMoveX_N;

	int8_t* ReMap;
	ReMap=(int8_t*)malloc(ReSizeX*ReSizeY*sizeof(int8_t));
    if(ReMap==NULL){
        printf("Can not get memory.\n");
        *AnsNodeNum= -1;
        return 0;
    }

	ReMakeMap(MapDefault,ReMap,MaxMoveX_P,MaxMoveX_N,MaxMoveY_P,MaxMoveY_N,SizeX,SizeY,MapJudge,MapNoUse,MapCanUse);
	int8_t* PrintReadReMap;
	//--------------------------------------------------------------------------------------

//KESU!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//	return 0;

	//マップを拡張したのでスタート、ゴールのx,y座標もずらす。
	int ReStartX=StartX+MaxMoveX_P;
	int ReStartY=StartY+MaxMoveY_P;
	int ReGoalX=GoalX+MaxMoveX_P;
	int ReGoalY=GoalY+MaxMoveY_P;

	//----------------------------------------------------------------------
	// First Setup Node------------------------------------------------------
	int QueMaxNum;
	QueMaxNum = (int)SizeX * SizeY * 2 / 3;
	int NowQueNum = 0;
	int NowQue;

	int* QuesXForFree=(int*)malloc(QueMaxNum*sizeof(int));
	int* QuesYForFree=(int*)malloc(QueMaxNum*sizeof(int));
	float* QuesCostCForFree=(float*)malloc(QueMaxNum*sizeof(float));
	float* QuesCostAllForFree=(float*)malloc(QueMaxNum*sizeof(float));
	float* MapCost=(float*)malloc(ReSizeX*ReSizeY*sizeof(float));
	float* MapCostC=(float*)malloc(ReSizeX*ReSizeY*sizeof(float));
	int* MapLogX=(int*)malloc(ReSizeX*ReSizeY*sizeof(int));
	int* MapLogY=(int*)malloc(ReSizeX*ReSizeY*sizeof(int));

    if(QuesXForFree==NULL){
        printf("Can not get memory.\n");
        *AnsNodeNum= -1;
        return 0;
    }else if(QuesYForFree==NULL){
        printf("Can not get memory.\n");
        *AnsNodeNum= -1;
        return 0;
    }else if(QuesCostCForFree==NULL){
        printf("Can not get memory.\n");
        *AnsNodeNum= -1;
        return 0;
    }else if(QuesCostAllForFree==NULL){
        printf("Can not get memory.\n");
        *AnsNodeNum= -1;
        return 0;
    }else if(MapCost==NULL){
        printf("Can not get memory.\n");
        *AnsNodeNum= -1;
        return 0;
    }else if(MapCostC==NULL){
        printf("Can not get memory.\n");
        *AnsNodeNum= -1;
        return 0;
    }else if(MapLogX==NULL){
        printf("Can not get memory.\n");
        *AnsNodeNum= -1;
        return 0;
    }else if(MapLogY==NULL){
        printf("Can not get memory.\n");
        *AnsNodeNum= -1;
        return 0;
    }

	float* ReadMapCost=MapCost;
	float* ReadMapCostC=MapCostC;

	for(i=0;i<ReSizeY;i++){
		for(j=0;j<ReSizeX;j++){
			*ReadMapCost=INFINITY;
			ReadMapCost+=1;
		}
	}

	int* QuesX=QuesXForFree;
	int* QuesY=QuesYForFree;
	float* QuesCostC=QuesCostCForFree;
	float* QuesCostAll=QuesCostAllForFree;

	//float MapCostC[SizeY + 2][SizeX + 2];
	float CostH;
	float D1,D2;
	float CenterCostC;
	//------------------------------------------------------------------------

	//初期設定：一個目のキューを追加、コストを設定
	D1=(ReStartX-ReGoalX);
	D2=(ReStartY-ReGoalY);
	CostH=FuncCostH(D1,D2);

	QuesX[0]=ReStartX;
	QuesY[0]=ReStartY;
	QuesCostC[0]=0;
	QuesCostAll[0]=CostH;
	ReadMapCost=MapCost+(int)(ReStartY*ReSizeX+ReStartX);
	*ReadMapCost=CostH;
	ReadMapCostC=MapCostC+(int)(ReStartY*ReSizeX+ReStartX);
	*ReadMapCostC=0;

	NowQue=0;
	NowQueNum=1;



	//ReMap[(int)StartY][(int)StartX] = MapOpened;

	// Astar Roop
	int CheckRoop=1;
	int8_t* readMap;
	int8_t* CenterReadMap;
	int CenterX,CenterY;
	int readX,readY;
	float CostC;
	float* CenterReadCost;
	float* CenterReadCostC;
	float CostAll;
	int* ReadLogX;
	int* ReadLogY;
	int* CenterLogX;
	int* CenterLogY;
	int CenterPoint;
	int ReadPoint;

	//int SizeX2=SizeX+2;
	int ForOpenNode;
	k=0;

	while(NowQueNum!=0&&CheckRoop){
		
		CenterCostC=QuesCostC[NowQue];
		CenterX=QuesX[NowQue];
		CenterY=QuesY[NowQue];
		NowQueNum-=1;
		NowQue-=1;

		ReadPoint=CenterY*ReSizeX+CenterX;

		CenterReadMap=ReMap+ReadPoint;
		*CenterReadMap=MapOpened;
		CenterReadCost=MapCost+ReadPoint;
		CenterReadCostC=MapCostC+ReadPoint;

		CenterLogX=MapLogX+ReadPoint;
		CenterLogY=MapLogY+ReadPoint;

		for(i=0;i<OpenNodeNum;i++){
			
			ReadPoint=OpenNode[i][1]*ReSizeX+OpenNode[i][0];

			ReadMapCost=CenterReadCost+ReadPoint;
			readMap=CenterReadMap+ReadPoint;
			ReadLogX=CenterLogX+ReadPoint;
			ReadLogY=CenterLogY+ReadPoint;
			ReadMapCostC=CenterReadCostC+ReadPoint;

			CostC=OpenNode[i][2];
			readX=CenterX+OpenNode[i][0];
			readY=CenterY+OpenNode[i][1];

			D1=(readX-ReGoalX);
			D2=(readY-ReGoalY);
			CostH=FuncCostH(D1,D2);
			CostAll=CostH+CostC+*CenterReadCostC;

			if(*ReadMapCost>CostAll){
				*ReadMapCost=CostAll-CostH;
				*ReadLogX=CenterX;
				*ReadLogY=CenterY;
				*ReadMapCostC=CostC+*CenterReadCostC;
			}
			if ((int)*readMap == MapCanUse){

				QueAdd(NowQueNum, readX, readY, CostC,CostH, QuesX, QuesY, QuesCostC,QuesCostAll);
				NowQueNum+=1;
				NowQue=NowQueNum-1;

				*readMap=MapOpened;
				if (readX == ReGoalX && readY == ReGoalY){
					CheckRoop = 0;
				}
			}
		}
	}
//-------------------------------------------------------------------------------------------------

	int FindGoalsRoop=1;
	int ReadGoalsX,ReadGoalsY;
	int GoalsX,GoalsY;

	

    int* AnsNodes=(int*)malloc(BlockSizeOfArrey*sizeof(int));
    int* ForFreeAnsNodes;
    int SizeOfAnsNodes=BlockSizeOfArrey;//凡ミスでコアダンプが怖いので余裕をもっておく
    if(AnsNodes==NULL){
        printf("Can not get memory.\n");
        *AnsNodeNum=-1;
        return 0;
    }

    int count=0;
	if(CheckRoop){
		printf("Goal Not Found..\n");
		*AnsNodeNum= -1;
	}else{
		printf("Goal Found.\n");
		ReadGoalsX=ReGoalX;
		ReadGoalsY=ReGoalY;
		*(ReMap+(int)(ReGoalY*ReSizeX+ReGoalX))=(int8_t)127;
		//ノードのプロット
        //printf("(%d,%d)\n",ReGoalX,ReGoalY);
        AnsNodes[0]=ReGoalX-MaxMoveX_P;
        AnsNodes[1]=ReGoalY-MaxMoveY_P;
		count+=2;
		while(FindGoalsRoop){
            //次の座標を所得
			GoalsX=*(MapLogX+(int)(ReadGoalsY*ReSizeX+ReadGoalsX));
			GoalsY=*(MapLogY+(int)(ReadGoalsY*ReSizeX+ReadGoalsX));
            //座標を記録
            AnsNodes[count]=GoalsX-MaxMoveX_P;
            AnsNodes[count+1]=GoalsY-MaxMoveY_P;
			count+=2;
			//ノードのプロット
			//printf("(%d,%d)\n",GoalsX,GoalsY);

            //メモリが足らなくなりそうならreallocでメモリを追加、確保に失敗したら強制終了。
            //printf("Count=%d,SizeOfAnsNodes=%d\n",count,SizeOfAnsNodes);
            if(count>SizeOfAnsNodes-2){
                ForFreeAnsNodes=(int*)realloc(AnsNodes,(SizeOfAnsNodes+BlockSizeOfArrey)*sizeof(int));
                if(ForFreeAnsNodes==NULL){
                    free(AnsNodes);
                    printf("can not get memory.\n");
                    *AnsNodeNum=-1;
					break;
                }else{
                    SizeOfAnsNodes+=BlockSizeOfArrey;
                    AnsNodes=ForFreeAnsNodes;
                }
            }
			*(ReMap+(int)(GoalsY*ReSizeX+GoalsX))=(int8_t)127;
			ReadGoalsX=GoalsX;
			ReadGoalsY=GoalsY;
			if(GoalsX==ReStartX&&GoalsY==ReStartY){
				FindGoalsRoop=0;
			}
		}

	}

	//マップのプロット
	PrintReadReMap=ReMap;
	printf("\nSizeReMap:X,Y=%d,%d\n",ReSizeX,ReSizeY);
	for (i = 0; i < ReSizeY; i++){
		for (j = 0; j < ReSizeX ; j++){
			//printf("Num:%d",j);
			printf("%4d", *PrintReadReMap);
			PrintReadReMap+=1;
		}
		printf("\n");
	}


	//ここ以外でfree開放しない、二重開放はほか関数でエラーが出て原因を見つけにくい。
	free(QuesCostAllForFree);
	free(QuesXForFree);
	free(QuesYForFree);
	free(QuesCostCForFree);
	free(ReMap);
	free(MapCost);
	free(MapCostC);
	free(MapLogX);
	free(MapLogY);

	//一回の処理でオープンするノードの数
	//printf("OpenNodeNUm=%d\n",OpenNodeNum);

    *AnsNodeNum=(int)count/2;
    return AnsNodes;

}



	void QueAdd(int NowQueNum, int X,int Y ,float CostC,float CostH,int* QueX,int* QueY,float* QueCostC,float* QueCostAll)
	{
		int i,j,k;
        int NowQue=NowQueNum-1;
		int readX = NowQue;
		int readY = NowQue;
        int count = NowQueNum;
        float AllCost=CostH+CostC;


        do{
			if(count==0){
				//count=-1;
				break;
			}
			if(AllCost>QueCostAll[count-1]){
				QueCostAll[count]=QueCostAll[count-1];
				QueCostC[count]=QueCostC[count-1];
				QueY[count]=QueY[count-1];
				QueX[count]=QueX[count-1];
				count-=1;
			}else{
				break;
			}
        }while(1);


        QueCostAll[count]=AllCost;
        QueCostC[count]=CostC;
        QueX[count]=X;
        QueY[count]=Y;

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