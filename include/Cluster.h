#ifndef _CLUSTER_H_
#define _CLUSTER_H_
double **GetClusterCenter(double **pTrainSampleFeatureVec,unsigned int pRow,unsigned int pCol,unsigned int *pRandomInitialCenter,unsigned int pKval,unsigned int pMaxIterationNum);
#endif