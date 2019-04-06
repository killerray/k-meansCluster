#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Cluster.h"
#include "CalculateDistance.h"

typedef struct ClusterCenter
{
	double *pInitialCenter;
	double *pAccumulation;
	unsigned int pAccumulationNum;
	//这个地方可以进行扩展，加个链表记录每一簇具体的样本编号等
}ClusterCenter;

static void AddRow(double *pRow1,double *pRow2,unsigned int pLen)
{
	for (unsigned int i = 0; i < pLen; ++i)
	{
		pRow1[i]+=pRow2[i];
	}
}

static void GetKmeans(ClusterCenter *pClusterVec,unsigned int pKval,unsigned int pCol)
{
	for (unsigned int i = 0; i < pKval; ++i)
	{
		for (unsigned int j = 0; j < pCol; ++j)
		{
			(pClusterVec[i].pAccumulation[j])/=(double)pClusterVec[i].pAccumulationNum;
		}
	}
}

static void RenewClusterCenter(ClusterCenter *pClusterVec,unsigned int pKval,unsigned int pCol)
{
	for (unsigned int i = 0; i < pKval; ++i)
	{
		for (unsigned int j = 0; j < pCol; ++j)
		{
			pClusterVec[i].pInitialCenter[j]=pClusterVec[i].pAccumulation[j];
			pClusterVec[i].pAccumulation[j]=0;
		}
		pClusterVec[i].pAccumulationNum=0;
	}
}

static unsigned int JudgeIterationEnd(ClusterCenter *pClusterVec,unsigned int pKval,unsigned int pCol)
{
	unsigned int pJuageVal1=0;
	double pJuageVal2=0;
		for (unsigned int i = 0; i < pKval; ++i)
		{
			pJuageVal1+=pClusterVec[i].pAccumulationNum;
		}
		if(0==pJuageVal1)
		{
			return 1;
		}
		else
		{
			for (unsigned int i = 0; i < pKval; ++i)
			{
				pJuageVal2=0;
				for (unsigned int j = 0; j < pCol; ++j)
				{
					pJuageVal2+=pow(pClusterVec[i].pAccumulation[j]-pClusterVec[i].pInitialCenter[j],2);
				}
				if(pJuageVal2>0.1)
					return 1;
			}
			return 0;
		}
}
double **GetClusterCenter(double **pTrainSampleFeatureVec,unsigned int pRow,unsigned int pCol,unsigned int *pRandomInitialCenter,unsigned int pKval,unsigned int pMaxIterationNum)
{
	ClusterCenter *pClusterCenterVec = (ClusterCenter *)malloc(sizeof(ClusterCenter)*pKval);
	double **pCenterPointVec = (double **)malloc(sizeof(double *)*pKval);
	for (unsigned int i = 0; i < pKval; ++i)
	{
		double *pTemp1 = (double *)malloc(sizeof(double)*pCol);
		double *pTemp2 = (double *)malloc(sizeof(double)*pCol);
		for (unsigned int j = 0; j < pCol; ++j)
		{
			pTemp1[j]=pTrainSampleFeatureVec[pRandomInitialCenter[i]][j];
			pTemp2[j]=0;
		}
		pClusterCenterVec[i].pInitialCenter=pTemp1;
		pClusterCenterVec[i].pAccumulation=pTemp2;
		pClusterCenterVec[i].pAccumulationNum=0;

		pCenterPointVec[i]=pTemp1;
	}

	/*for (unsigned int i = 0; i < pKval; ++i)
	{
		for (unsigned int j = 0; j < pCol; ++j)
		{
			printf("%lf\t%lf\n",pClusterCenterVec[i].pInitialCenter[j],pClusterCenterVec[i].pAccumulation[j]);
		}
		printf("%d\n",pClusterCenterVec[i].pAccumulationNum);
	}
	return NULL;*/

	unsigned int pIndex=0;

	for (unsigned int k = 0; k < pMaxIterationNum && JudgeIterationEnd(pClusterCenterVec,pKval,pCol); ++k)
	{
		printf("Iteration Times is %d\n",k);
		if(0==k)
		{
			;
		}
		else
		{
			RenewClusterCenter(pClusterCenterVec,pKval,pCol);
		}
		for (unsigned int m = 0; m < pRow; ++m)
		{
			pIndex=CalculateDistanceMT(pCenterPointVec,pKval,pCol,pTrainSampleFeatureVec[m]);
			pClusterCenterVec[pIndex].pAccumulationNum+=1;
			AddRow(pClusterCenterVec[pIndex].pAccumulation,pTrainSampleFeatureVec[m],pCol);
		}
		GetKmeans(pClusterCenterVec,pKval,pCol);
	}
	for (unsigned int n = 0; n < pKval ; ++n)
	{
		printf("num of cluster%d is %d\n",n,pClusterCenterVec[n].pAccumulationNum);
	}

	return pCenterPointVec;
}