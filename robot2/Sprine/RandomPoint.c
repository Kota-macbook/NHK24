#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//#define M_PI 3.14159265358979323846264338327950288


//---------------------------PLEASE CHANGE-------------------------------
//計算用グローバル数
#define   file_map_deta "maps.txt"
#define   file_map_output "maps_ans.txt"
#define   N 9
double    map_checkpoints[N][2];
int       map_jyunban[N];
int       map_output_jyunban[N];
double    best_length;


//乱数用入力定数
// rand_sizeは極端に小さくしないこと、100以上がおすすめ
#define rand_size 200


//ファイル出力用
FILE *log1;
//-----------------------------------------------------------------------






//----------------------------DO NOT CHANGE------------------------------
//乱数用関数宣言
void    rand_Tasu_setup(void);
int     rand_INT(void);
double  rand_DOUBLE(void);
//乱数用変数
int     rand_ransuu[rand_size];
int     rand_count;
int     rand_start;
int     rand_end;
int     rand_make;
int     rand_mae;
int     rand_ato;
double  rand_seed;
double  rand_seed;
//-----------------------------------------------------------------------


int main (void){
	//Taus乱数セットアップ
	rand_Tasu_setup();
	int Num=21;
	int i;
	double X,Y;
	
	FILE* WriteRandTxt=fopen("data2.txt","w");

	for(i=0;i<Num;i++){
		X=10*i/Num;
		Y=15*i/Num;

		fprintf(WriteRandTxt,"%lf	%lf\n",X+rand_DOUBLE(),Y+rand_DOUBLE());
	}
	
	return 0;
}












































//----------------------------DO NOT CHANGE------------------------------

//For Taus Randomize

	//Taus乱数のセットアップ
	void rand_Tasu_setup(void){
		printf("Please enter mode of random.(time(NULL)=1 or seed)\n");
		scanf("%lf",&rand_seed);
		int i;
		
		if (rand_seed==1){
			srand(time(NULL));
		}else {
			srand(rand_seed);
		}
		
		if (rand_size>=400){
			rand_make=200;
			rand_start=0;
			rand_end=199;
		}else {
			rand_make=rand_size/2;
			rand_start=0;
			rand_end=rand_make/2-1;
		}
		
		for (i=0;i<rand_make;i++){
			rand_ransuu[i]=rand();
		}
		
		rand_mae=rand_start;
		rand_ato=rand_end;
		rand_count=rand_make-1;
		
		printf("------Setup of Taus Randomize has finished------\n");
	}






	//Taus整数乱数生成
	int rand_INT(void){
		
		rand_count+=1;
		if(rand_mae==rand_size){
			rand_mae=0;
		}
		if(rand_ato==rand_size){
			rand_ato=0;
		}
		if(rand_count==rand_size){
			rand_count=0;
		}
			
		rand_ransuu[rand_count]=rand_ransuu[rand_mae]^rand_ransuu[rand_ato];
		rand_mae+=1;
		rand_ato+=1;
		
		return rand_ransuu[rand_count];
	}






	//Taus実数乱数生成
	double rand_DOUBLE(void){
		double ranJ;
		ranJ=(double)rand_INT()/RAND_MAX;
		//printf("RanJ=%lf\n",ranJ);
		return ranJ;
	}
//-----------------------------------------------------------------------
