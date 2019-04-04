#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include "DealFile.h"

typedef struct IntputArg
{
	const double *pCenterPoint;
	double *pOtherPoint;
	double *ret;
	unsigned int pVecLen;
}InputArg;


void *EuclideanDistance(void *arg)
{
	InputArg *pArg = (InputArg *)arg;
	double pTempVal=0;
	for(unsigned int k=0;k!=pArg->pVecLen;++k)
	{
		pTempVal+=pow(pArg->pCenterPoint[k]-pArg->pOtherPoint[k],2);
		//printf("%lf\t%lf\t%lf\n",pArg->pCenterPoint[k],pArg->pOtherPoint[k],pTempVal);
	}
	*(pArg->ret)=pTempVal;
	//printf("\n");
	return NULL;
}
double *CalculateDistanceMT(double **pTrainSampleFeatureVec,unsigned int pRow,unsigned int pCol,const double *pPoint)
{
	double *RetVal =(double *)malloc(sizeof(double)*pRow);
	
	pthread_t * pThreadVec = (pthread_t *)malloc(sizeof(pthread_t)*pRow);
	
	InputArg *ArgVec=(InputArg *)malloc(sizeof(InputArg)*pRow);
	for(unsigned int i=0;i!=pRow;++i)
	{
		
		ArgVec[i].pCenterPoint=pPoint;
		ArgVec[i].pOtherPoint=pTrainSampleFeatureVec[i];
		ArgVec[i].ret=&RetVal[i];
		ArgVec[i].pVecLen=pCol;
		pthread_create(pThreadVec+i,NULL,EuclideanDistance,&ArgVec[i]);
	}
	for(unsigned int j=0;j!=pRow;++j)
	{
		pthread_join(pThreadVec[j],NULL);
	}
	
	free(ArgVec);
	ArgVec=NULL;
	return RetVal;
	
}
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