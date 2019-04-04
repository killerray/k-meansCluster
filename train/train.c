#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include "DealFile.h"
#include "CalculateDistance.h"


int main(int argc,char **argv)
{
	if(4!=argc)
	{
		exit(1);
	}
	unsigned int *TrainSampleClassVec=NULL;				//训练样本对应类别向量
	double **TrainSampleFeatureVec=NULL;				//训练样本特征向量
	double *DistanceResult=NULL;
	
	TrainSampleFeatureVec=ReadFile(argv[1],atoi(argv[2]),atoi(argv[3]),&TrainSampleClassVec);
	double *pTemp = (double*)malloc(sizeof(double)*atoi(argv[3]));
	memset(pTemp,0,atoi(argv[3])*(sizeof(double)/sizeof(int)));
	
	DistanceResult=CalculateDistanceMT(TrainSampleFeatureVec,atoi(argv[2]),atoi(argv[3]),pTemp);
	
	for(unsigned int m=0;m!=atoi(argv[2]);++m)
	{
		printf("%lf\n",DistanceResult[m]);
	}
	//释放特征文件内存
	FreeFile(TrainSampleFeatureVec,atoi(argv[2]),atoi(argv[3]),TrainSampleClassVec);
	free(DistanceResult);
	DistanceResult=NULL;
	
	return 0;
}