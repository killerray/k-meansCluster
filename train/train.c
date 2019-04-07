#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include "DealFile.h"
//#include "CalculateDistance.h"
#include "CreateRandomNum.h"
#include "Cluster.h"

int main(int argc,char **argv)
{
	if(6!=argc)
	{
		exit(1);
	}
	unsigned int *TrainSampleClassVec=NULL;				//训练样本对应类别向量
	double **TrainSampleFeatureVec=NULL;				//训练样本特征向量
	//double *DistanceResult=NULL;
	unsigned int * RandomNumVec=NULL;

	double **CenterPoint=NULL;

	TrainSampleFeatureVec=ReadFile(argv[1],atoi(argv[2]),atoi(argv[3]),&TrainSampleClassVec);
	double *pTemp = (double*)malloc(sizeof(double)*atoi(argv[3]));
	memset(pTemp,0,atoi(argv[3])*(sizeof(double)/sizeof(int)));

	RandomNumVec = CreateRandomNum(atoi(argv[2]),atoi(argv[4]));
	//unsigned int RandomNumVec[3]={5,11,23};

	for (unsigned int i = 0; i < atoi(argv[4]); ++i)
	{
		printf("%d\n",RandomNumVec[i]);
	}

	printf("\n");

	CenterPoint = GetClusterCenter(TrainSampleFeatureVec,atoi(argv[2]),atoi(argv[3]),RandomNumVec,atoi(argv[4]),atoi(argv[5]));
	for (unsigned int i = 0; i < atoi(argv[4]) ; ++i)
	{
		for (unsigned int j = 0; j < atoi(argv[3]); ++j)
		{
			printf("%lf\t",CenterPoint[i][j]);
		}
		printf("\n");
	}
	
	
	//for(unsigned int m=0;m!=atoi(argv[2]);++m)
	//{
	//	printf("%lf\n",DistanceResult[m]);
	//}
	//释放特征文件内存
	FreeFile(TrainSampleFeatureVec,atoi(argv[2]),atoi(argv[3]),TrainSampleClassVec);
	//free(DistanceResult);
	//DistanceResult=NULL;
	FreeFile(CenterPoint,atoi(argv[4]),atoi(argv[3]),NULL);
	
	return 0;
}