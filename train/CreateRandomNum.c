#include<stdio.h>
#include<stdlib.h> 
#include<time.h>
#include <string.h>
static unsigned int rand_number(unsigned int pRange)
{
	return rand()%pRange;
}
unsigned int * CreateRandomNum(unsigned int pRange,unsigned int pNum)
{
	srand((int)time(NULL));//产生随机数的种子
	unsigned int *RandVec =(unsigned int *)malloc(sizeof(unsigned int)*pNum);
	memset(RandVec,0,pNum);
	for(unsigned int i=0;i<pNum;++i)
	{
		RandVec[i]=rand_number(pRange);//产生随机数  
	}
	return RandVec;
} 

