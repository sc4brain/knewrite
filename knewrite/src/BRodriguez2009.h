/* 
 * File:   Rodriguez2009.h
 * Author: naska
 *
 * Created on 2010/06/29, 14:25
 */

#ifndef _RODRIGUEZ2009_H
#define	_RODRIGUEZ2009_H

#include "BRodriguez2009VoxelList.h"
#include "BRodriguez2009Cluster.h"
#include "BVoxelClass.h"

#include <QMutex>

/* class POINT3D; */
/* class RodCluster; */
/* class RodClusterList; */
/* class VoxelClass; */
/* class VoxelList; */
//#include "Rodriguez2009Cluster.h"

int Rodriguez2009ExtractionMethod(VoxelClass *inData,
                                  POINT3D inStartPoint,
                                  RodClusterList *outClusterList,
                                  volatile bool *cancelFlag = NULL,
                                  QMutex *mutex = NULL);

int Rodriguez2009CalcNode(POINT3D PrevNode,
                          POINT3D NextCenter,
                          double PrevSize,
                          double NextSize,
                          POINT3D *outNextNode);

int Rodriguez2009CalcNodeWithMedianPoith(RodCluster *inCluster,
                                         POINT3D *outNextNode);

int Rodriguez2009VoxelClusterize(int *pCheckList,
                                 VoxelList *inVoxelList);

int RayBurst2DforDiam(VoxelClass *inData,
                      RodClusterList *inClusterList,
                      unsigned char inThreshold,
                      unsigned int inRayDensity,
                      double inScale);

int Rodriguez2009MakeHoc(char *fileName,
                         char *dirName,
                         RodClusterList *inClusterList,
                         char *dendName,
                         VoxelClass *inData = NULL,
                         char *suffix = NULL);

int Rodriguez2009MakeHoc4Parallel(char *fname,
                                  RodClusterList *inClusterList,
                                  char *dendName,
                                  VoxelClass *inData = NULL);

int Rodriguez2009Smoothing(RodClusterList* inClusterList,
                           RodClusterList* outClusterList = 0);

int Rodriguez2009GetSubbranch(RodClusterList *inClusterList,
                              unsigned int startClusterNo,
                              RodClusterList *outClusterList);

int Rodriguez2009MergeClusterList(RodClusterList *inParent,
                                  unsigned int inParentNodeNo,
                                  RodClusterList *inChild,
                                  unsigned int inChildNodeNo,
                                  RodClusterList *outClusterList
                                  );

int Rodriguez2009CompareClusterList(RodClusterList *inClusterList1,
                                    RodClusterList *inClusterList2,
                                    double delta,
                                    double *outDiscrepancy,
                                    double outConsistency[2]);
                                    

#endif	/* _RODRIGUEZ2009_H */
