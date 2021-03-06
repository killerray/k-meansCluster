#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include "CalculateDistance.h"

typedef struct DistanceCalArg
{
	double *pCenterPoint;
	double *pOtherPoint;
	double *pRet;
	unsigned int pVecDimension;
}DistanceCalArg;

void *EuclideanDistance(void *arg)
{
	DistanceCalArg *pArg = (DistanceCalArg *)arg;
	for(unsigned int k=0;k!=pArg->pVecDimension;++k)
	{
		*(pArg->pRet)+=pow(pArg->pCenterPoint[k]-pArg->pOtherPoint[k],2);
		//printf("%lf\t%lf\t%lf\n",pArg->pCenterPoint[k],pArg->pOtherPoint[k],pTempVal);
	}
	//printf("\n");
	return NULL;
}

double Distance(double *pRow1,double *pRow2,unsigned int pRowLen)
{
	double pRetVal=0;
	for(unsigned int k=0;k!=pRowLen;++k)
	{
		pRetVal+=pow(pRow1[k]-pRow2[k],2);
		//printf("%lf\t%lf\t%lf\n",pArg->pCenterPoint[k],pArg->pOtherPoint[k],pTempVal);
	}
	return pRetVal;
}
unsigned int CalculateDistanceMT(double **pTrainSampleFeatureVec,unsigned int pRow,unsigned int pCol,double *pPoint)
{
	double *RetDistanceVal =(double *)malloc(sizeof(double)*pRow); //可以优化，把RetDistanceVal当作参数传进来
	
	/*pthread_t * pThreadVec = (pthread_t *)malloc(sizeof(pthread_t)*pRow);
	
	DistanceCalArg *ArgVec=(DistanceCalArg *)malloc(sizeof(DistanceCalArg)*pRow);
	
	for(unsigned int i=0;i!=pRow;++i)
	{
		ArgVec[i].pCenterPoint=pPoint;
		ArgVec[i].pOtherPoint=pTrainSampleFeatureVec[i];
		ArgVec[i].pRet=&RetDistanceVal[i];
		ArgVec[i].pVecDimension=pCol;
		pthread_create(pThreadVec+i,NULL,EuclideanDistance,&ArgVec[i]);
	}
	for(unsigned int j=0;j!=pRow;++j)
	{
		pthread_join(pThreadVec[j],NULL);
	}
	free(pThreadVec);
	pThreadVec=NULL;
	free(ArgVec);
	ArgVec=NULL;*/
	for (unsigned int i = 0; i < pRow; ++i)
	{
		RetDistanceVal[i]=Distance(pTrainSampleFeatureVec[i],pPoint,pCol);
	}
	unsigned int pMinIndex=0;
	double pMinDistance = RetDistanceVal[0];
	for (unsigned int k = 1; k < pRow; ++k)
	{
		if(RetDistanceVal[k]<pMinDistance)
		{
			pMinDistance = RetDistanceVal[k];
			pMinIndex=k;
		}
	}
	
	//printf("%lf\t%lf\t%lf\tDistance Index is %d\n",RetDistanceVal[0],RetDistanceVal[1],RetDistanceVal[2],pMinIndex);
	free(RetDistanceVal);
	RetDistanceVal=NULL;
	return pMinIndex;
}