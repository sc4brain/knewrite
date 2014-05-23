
//#define ___RODRIGUEZ2009DEBUG___
//#define ___RODRIGUEZ2009_PRINT___
#define ___RODRIGUEZ2009_26_CONNECTED___
//#define ___RODRIGUEZ2009_18_CONNECTED___
//#define ___RODRIGUEZ2009_6_CONNECTED___
#define ___RODRIGUEZ2009_SCOOPING___


#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <list>
#include "BCommon.h"
#include "BRodriguez2009.h"

#include <QMutex>

#define PI 3.1415926535897932384626

enum enumVoxelState {
    VS_Unlabeled = 0,
    VS_Unvisited,
    VS_Visited,
};

typedef struct _VOXELSIZE {
    unsigned int x;
    unsigned int y;
    unsigned int z;
} VOXELSIZE;

// inData must be binarized

int Rodriguez2009ExtractionMethod(VoxelClass *inData,
                                  POINT3D inStartPoint,
                                  RodClusterList *outClusterList,
                                  volatile bool *cancelFlag,
                                  QMutex *mutex) {
    VOXELSIZE size;
    RodCluster *CurCluster;
    RodClusterList *ClusterList = outClusterList;
    unsigned int uClusterCount = 0;
    unsigned int uCurNodeNo = 0;
    VoxelClass *Data = inData;

    if (outClusterList == NULL) {
        return -1;
    }

    size.x = Data->getX();
    size.y = Data->getY();
    size.z = Data->getZ();

    if (size.x <= inStartPoint.x
        || size.y <= inStartPoint.y
        || size.z <= inStartPoint.z) {
        return -2; // invalid start point
    }

    if (Data->getData(inStartPoint.x,
                      inStartPoint.y,
                      inStartPoint.z) == 0) {
        return -3; // invalid start point
    }

    // set all voxelz as unvisited
    for (unsigned i = 0; i < size.x; i++) {
        for (unsigned j = 0; j < size.y; j++) {
            for (unsigned k = 0; k < size.z; k++) {
                if (Data->getData(i, j, k) != 0) {
                    Data->setData(i, j, k, (unsigned char) VS_Unvisited);
                }
            }
        }
    }

    //ClusterList = new RodClusterList();

    // create first cluster
    CurCluster = new RodCluster;
    CurCluster->setDistance(0);
    CurCluster->setClusterNo(uClusterCount);
    CurCluster->addVoxel(inStartPoint);
    CurCluster->setNode(inStartPoint);
    CurCluster->setNodeNo(++uCurNodeNo);

    Data->setData(inStartPoint, (unsigned char) VS_Visited);

    ClusterList->addCluster(CurCluster);

    bool bExistInPrevIteration = true;
    unsigned int uPrevClusterCount = 1;
    //unsigned int uCurDist = 1;
    // while any clusters exist in previous iteration i - 1
    for (unsigned int i = 1; bExistInPrevIteration; i++) {
#ifdef ___RODRIGUEZ2009_PRINT___
        dprintf("{%u/%d} ", i, bExistInPrevIteration);
#endif
        if (mutex != NULL && cancelFlag != NULL) {
            mutex->lock();
            if (*cancelFlag) {
                SAFEDELETE(ClusterList);
                mutex->unlock();
                return -3;
            }
            mutex->unlock();
        }

        bExistInPrevIteration = false;
#ifdef ___RODRIGUEZ2009_PRINT___
        dprintf(" (%u)", ClusterList->getClusterNum() - uPrevClusterCount);
        dprintf("\n\n[%4d] ", i);
#endif

        uPrevClusterCount = ClusterList->getClusterNum();
        // for every cluster Ci-1,j created in the previous iteration
        for (unsigned int uPrevCurNo = ClusterList->getClusterNum() - 1;
                ClusterList->getCluster(uPrevCurNo)->getDistance() == i - 1;
                uPrevCurNo--) {
            RodCluster *PrevCluster = ClusterList->getCluster(uPrevCurNo);
#ifdef ___RODRIGUEZ2009DEBUG___N
            dprintf("\t\t\tPrev[%3d] VoxelNum:%4d Dist:%3d\n",
                    PrevCluster->getClusterNo(),
                    PrevCluster->getVoxelNum(),
                    PrevCluster->getDistance());
#endif
            //find all unvisited voxels in 26-connected neighborhood of Ci-1,j
            //and mark all found voxels as visited
            VoxelList *VisitedVoxelList = new VoxelList();
            for (unsigned int uCurVoxel = 0;
                    uCurVoxel < PrevCluster->getVoxelNum();
                    uCurVoxel++) {
                unsigned x = (unsigned)PrevCluster->getVoxel(uCurVoxel).x;
                unsigned y = (unsigned)PrevCluster->getVoxel(uCurVoxel).y;
                unsigned z = (unsigned)PrevCluster->getVoxel(uCurVoxel).z;
                for (int dx = -1; dx <= 1; dx++) {
                    for (int dy = -1; dy <= 1; dy++) {
                        for (int dz = -1; dz <= 1; dz++) {
                            if (dx == 0 && dy == 0 && dz == 0) continue;
#ifdef ___RODRIGUEZ2009_18_CONNECTED___
                             // D18 metric
                            if (dx * dy * dz != 0) continue;
#elif defined(___RODRIGUEZ2009_6_CONNECTED___)
                             // D6 metric
                            if (dx * dx + dy * dy + dz * dz == 1) continue;
#endif
                            // D26 metric
                            if (Data->getData(x + dx, y + dy, z + dz)
                                == VS_Unvisited) {
                                Data->setData(x + dx, y + dy, z + dz,
                                              (unsigned char) VS_Visited);
                                VisitedVoxelList->addPoint(POINT3D((x + dx),
                                                                   (y + dy),
                                                                   (z + dz)));
                            }
                        }
                    }
                }
            }
#ifdef ___RODRIGUEZ2009_PRINT___
            dprintf("%d ", VisitedVoxelList->getPointNum());
#endif

            if (VisitedVoxelList->getPointNum() == 0) {
				SAFEDELETE(VisitedVoxelList);
                continue;
			}            

            bExistInPrevIteration = true;

            // for every connected component k of found voxels
            // create cluster Ci,k with voxels of connected component k
            int *pCheckList = new int[VisitedVoxelList->getPointNum()];
            int nGroupNum = Rodriguez2009VoxelClusterize(pCheckList,
                                                         VisitedVoxelList);
            if (nGroupNum < 0) {
                fprintf(stderr, "Rodriguez2009VoxelClusterize... error %d\n",
                        nGroupNum);
            }
            int nValidGroupNum = 0;
            for (int nGroupNo = 0; nGroupNo < nGroupNum; nGroupNo++) {
                CurCluster = new RodCluster();
                uClusterCount++;
                CurCluster->setClusterNo(uClusterCount);
                CurCluster->setDistance(i);
                CurCluster->addParent(PrevCluster);

#ifdef ___RODRIGUEZ2009DEBUG___N
                dprintf(stderr, "#C[%5u] ClusterNo=%5u " \
                        "ParentNum=%d ChildNum=%d\n",
                        CurCluster->getClusterNo(),
                        CurCluster->getClusterNo(),
                        CurCluster->getParentNum(),
                        CurCluster->getChildNum());
#endif

                for (unsigned int uCurVoxel = 0;
                     uCurVoxel < VisitedVoxelList->getPointNum();
                     uCurVoxel++) {
                    if (nGroupNo == pCheckList[uCurVoxel]) {
                        POINT3D point = VisitedVoxelList->getPoint(uCurVoxel);
                        CurCluster->addVoxel(point);
                    }
                }
                if (CurCluster->getVoxelNum() == 0) {
					SAFEDELETE(CurCluster);
                    continue;
				}
                CurCluster->setNodeNo(++uCurNodeNo);
                //uCurNodeNo++;
                ClusterList->addCluster(CurCluster);
                nValidGroupNum++;
            }
#ifdef ___RODRIGUES2009DEBUG___N
            dprintf("\t\tuGroupNum:%d\n", nGroupNum);
#endif
#if 0
            //create cluster Ci,k from voxels of connected component k
            CurCluster = new RodCluster();
            CurCluster->setClusterNo(++uClusterCount);
            CurCluster->setDistance(i);
            CurCluster->setParent(0, PrevCluster);
            CurCluster->addVoxel(VisitedVoxelList->getPoint(0));
            ClusterList->addCluster(CurCluster);

            int uCurCheckNo = pCheckList[0];
            pCheckList[0] = -1;
            unsigned int uNewClusterNum = 1;
            for (unsigned int uCurVoxel = 0;
                    uCurVoxel < VisitedVoxelList->getPointNum();
                    uCurVoxel++) {
                if (uCurCheckNo == pCheckList[uCurVoxel]) {
                    CurCluster->addVoxel(VisitedVoxelList->getPoint(uCurVoxel));
                    pCheckList[uCurVoxel] = -1;
                }


                if (pCheckList[uCurVoxel] != uCurCheckNo) {
                    uCurCheckNo = pCheckList[uCurVoxel];

                    CurCluster = new RodCluster();
                    CurCluster->setClusterNo(++uClusterCount);
                    CurCluster->setDistance(i);
                    CurCluster->setParent(0, PrevCluster);
                    ClusterList->addCluster(CurCluster);
                    uNewClusterNum++;
                }
                CurCluster->addVoxel(VisitedVoxelList->getPoint(uCurVoxel));
            }
#endif

#ifdef ___RODRIGUEZ2009_PRINT___
            //printf(" %5d", nGroupNum, VisitedVoxelList->getPointNum());
#endif


            ASAFEDELETE(pCheckList);

            SAFEDELETE(VisitedVoxelList);

            POINT3D PrevNode = PrevCluster->getNode();

            int uNewClusterNum = (int)nValidGroupNum;
            for (unsigned int uCurClusterNo = ClusterList->getClusterNum() - 1;
                    0 < uNewClusterNum;
                    uNewClusterNum--, uCurClusterNo--) {

                // create node Ni,k at location given by Eq. (1)
                CurCluster = ClusterList->getCluster(uCurClusterNo);
                CurCluster->calcCenter();
                POINT3D NextCenter = CurCluster->getCenter();
                POINT3D NextNode;


#ifdef ___RODRIGUEZ2009DEBUG___N
                dprintf("\n$C[%5u] ClusterNo=%5u " \
                        "ParentNum=%2d ChildNum=%4d\n",
                        CurCluster->getClusterNo(),
                        CurCluster->getClusterNo(),
                        CurCluster->getParentNum(),
                        CurCluster->getChildNum());
#endif


                // !!! original Rod (scooping)
                Rodriguez2009CalcNode(PrevNode, NextCenter, \
                    PrevCluster->calcSize(), CurCluster->calcSize(), \
                    &NextNode);

                // (not scooping)
                //Rodriguez2009CalcNodeWithMedianPoith(CurCluster, &NextNode);

                CurCluster->setNode(NextNode);

                // set scooping distance to the largest distance
                // of any voxel in Ci,k to Ni,k
                CurCluster->calcScoopingDistance();

#ifdef ___RODRIGUEZ2009DEBUG___N
                dprintf("&C[%5u] ClusterNo=%5u " \
                        "ParentNum=%2d ChildNum=%4d\n",
                        CurCluster->getClusterNo(),
                        CurCluster->getClusterNo(),
                        CurCluster->getParentNum(),
                        CurCluster->getChildNum());
#endif

#ifdef ___RODRIGUEZ2009_SCOOPING___

                //printf("ScoopingDistance:%f\n", \
                //    CurCluster->getScoopingDistance());

                // while any connected, unvisited, object voxel
                // within scooping distance from Ni,k
                unsigned uScoopingNum = CurCluster->getVoxelNum();
                while (uScoopingNum != 0) {
                    unsigned uPrevScoopingNum = uScoopingNum;
                    uScoopingNum = 0;
                    for (unsigned uCurVoxelNo = CurCluster->getVoxelNum() - 1;
                            //uCurVoxelNo < CurCluster->getVoxelNum();
                            uPrevScoopingNum > 0;
                            uCurVoxelNo--, uPrevScoopingNum--) {
                        POINT3D point = CurCluster->getVoxel(uCurVoxelNo);
                        unsigned x = (unsigned)point.x;
                        unsigned y = (unsigned)point.y;
                        unsigned z = (unsigned)point.z;
                        //if (x <= 0)
                        //printf("VoxelNum:%d\n", CurCluster->getVoxelNum());
                        for (int dx = -1; dx <= 1; dx++) {
                            for (int dy = -1; dy <= 1; dy++) {
                                for (int dz = -1; dz <= 1; dz++) {
                                    if (!(dx + dy + dz)) continue;
#ifdef ___RODRIGUEZ2009_18_CONNECTED___
                                    if (dx * dy * dz != 0) continue;
#elif defined(___RODRIGUEZ2009_6_CONNECTED___)
                                    if (dx * dx + dy * dy + dz * dz == 1)
                                        continue; // D6 metric
#endif
                                    POINT3D node = CurCluster->getNode();
                                    double nx = x + dx - node.x;
                                    double ny = y + dy - node.y;
                                    double nz = z + dz - node.z;
                                    if (Data->getData(x + dx, y + dy, z + dz) == VS_Unvisited &&
                                            sqrt(nx * nx + ny * ny + nz * nz) < CurCluster->getScoopingDistance()) {
                                        // add voxel to cluster Cxi,k and mark voxel as visited
                                        Data->setData(x + dx, y + dy, z + dz, (unsigned char)VS_Visited);
                                        CurCluster->addVoxel(POINT3D((short) (x + dx),
                                                                     (short) (y + dy),
                                                                     (short) (z + dz)));
                                        uScoopingNum++;
                                    }
                                }
                            }
                        }
                    }

                }
#endif

            }

            if (uPrevCurNo == 0)
                break;
        }
        
#ifdef ___RODRIGUEZ2009DEBUG___N
            dprintf("Dist fin\n");
#endif
    }
#ifdef ___RODRIGUEZ2009DEBUG___N
    dprintf("\n");
    dprintf("all finished\n");
    dprintf("ClusterNum = %d\n", ClusterList->getClusterNum());
#endif

#ifdef ___RODRIGUEZ2009DEBUG___N
    dprintf("set children\n");
#endif
    for (unsigned int i = 0; i < ClusterList->getClusterNum(); i++) {
        RodCluster *CurCluster = ClusterList->getCluster(i);
        if (CurCluster->getParentNum() == 0) continue;
        CurCluster->getParent(0)->addChild(CurCluster);
    }

#ifdef ___RODRIGUEZ2009DEBUG___N
    dprintf("renumbering\n");
#endif
    // renumbering the cluster No
	for (unsigned int i = 0; i < ClusterList->getClusterNum(); i++) {
		RodCluster *CurCluster = ClusterList->getCluster(i);
		CurCluster->setClusterNo(i);
		CurCluster->setNodeNo(i+1);
	}

#ifdef ___RODRIGUEZ2009DEBUG___N
    dprintf("assemble\n");
#endif
	// assemble clusters for sequencial array
	ClusterList->assembleClusters();
	
#ifdef ___RODRIGUEZ2009DEBUG___N
    dprintf("diam\n");
#endif
    // calc diameter
    RayBurst2DforDiam(inData, ClusterList, 1, 30, inData->getScaleX());

#ifdef ___RODRIGUEZ2009DEBUG___
    ClusterList->print("debug_Clusterlist.txt");
#endif
    //SAFEDELETE(ClusterList);

    return 0;
}

int Rodriguez2009CalcNode(POINT3D PrevNode, POINT3D NextCenter,
        double PrevSize, double NextSize,
        POINT3D *outNextNode) {
    if (outNextNode == NULL) return -1;

    double SizeRatio;
    if (NextSize <= PrevSize) {
        SizeRatio = NextSize / PrevSize;
    } else {
        SizeRatio = PrevSize / NextSize;
    }


    double coef = pow(0.5, SizeRatio);

    outNextNode->x = PrevNode.x + coef * (NextCenter.x - PrevNode.x);
    outNextNode->y = PrevNode.y + coef * (NextCenter.y - PrevNode.y);
    outNextNode->z = PrevNode.z + coef * (NextCenter.z - PrevNode.z);

    return 0;
}

int Rodriguez2009CalcNodeWithMedianPoith(RodCluster *inCluster,
                                         POINT3D *outNextNode) {
    POINT3D median;

    median.x = median.y = median.z = 0.;

    unsigned int uVoxelNum = inCluster->getVoxelNum();

    for (unsigned int i = 0; i < uVoxelNum; i++) {
        median.x += inCluster->getVoxel(i).x;
        median.y += inCluster->getVoxel(i).y;
        median.z += inCluster->getVoxel(i).z;
    }

    outNextNode->x = median.x / uVoxelNum;
    outNextNode->y = median.y / uVoxelNum;
    outNextNode->z = median.z / uVoxelNum;

    return 0;
}

int Rodriguez2009VoxelClusterize(int *pCheckList, VoxelList *inVoxelList) {
    if (pCheckList == NULL)
        return -1;
    if (inVoxelList == NULL)
        return -2;
    if (inVoxelList->getPointNum() == 0)
        return -3;
    //if (sizeof(pCheckList)/sizeof(int*) != inVoxelList->getPointNum())
    //    return -4;

    unsigned int uNum = inVoxelList->getPointNum();

    for (unsigned int i = 0; i < uNum; i++) {
        pCheckList[i] = i;
    }

    for (unsigned int i = 0; i < uNum; i++) {
        for (unsigned int j = 0; j < uNum; j++) {
            unsigned int j2 = (j + i); // / uNum
            if(j2 / uNum) continue;
            //unsigned int j2 = CLIP_VALUE_INT((j + i), uNum);
            double dx = inVoxelList->getPoint(j2).x - inVoxelList->getPoint(j).x;
            double dy = inVoxelList->getPoint(j2).y - inVoxelList->getPoint(j).y;
            double dz = inVoxelList->getPoint(j2).z - inVoxelList->getPoint(j).z;
#if defined(___RODRIGUEZ2009_6_CONNECTED___)
            if (dx * dx + dy * dy + dz * dz <= 1.) {
#elif defined(___RODRIGUEZ2009_18_CONNECTED___)
            if (dx * dx + dy * dy + dz * dz <= 2.) {
#else
            if (dx * dx + dy * dy + dz * dz <= 3.) {
#endif
                if (j < j2) {
                    int targetNo = pCheckList[j2];
                    int overwriteNo = pCheckList[j];
                    for (unsigned int k = 0; k < uNum; k++) {
                        if (pCheckList[k] == targetNo)
                            pCheckList[k] = overwriteNo;
                    }
                }//  else {
                //     for (unsigned int k = 0; k < uNum; k++) {
                //         if (pCheckList[k] == pCheckList[j])
                //             pCheckList[k] = pCheckList[j2];
                //     }
                // }
            }
        }
    }

    unsigned int uGroupNum = 1;
    for (unsigned int i = 1; i < uNum; i++) {
        bool isExist = false;
        for (unsigned int j = 1; j < uNum; j++) {
            if (i == pCheckList[j]) {
                pCheckList[j] = uGroupNum;
                isExist = true;
            }
        }
        if (isExist)
            uGroupNum++;
    }

    return uGroupNum;
}

/*!
 * @brief estimate diameters with Rayburst sampling algorithm
 * @param[in] inData 3D image data must be hemmed by 0 intensity
 * @param[in/out] inClusterList Clusters derived from Rodriguez2009ExtractionMethod()
 * @param[in] inThreshold intensity threshold by which the rays are stopped
 * @param[in] inRayDensity the number of rays per 180 degree
 * @param[in] inScale um/pixel for xy
 */
int RayBurst2DforDiam(VoxelClass *inData,
        RodClusterList *inClusterList,
        unsigned char inThreshold,
        unsigned int inRayDensity,
        double inScale) {
    int err = 1;
    if (inData == NULL) return -err++;
    if (inClusterList == NULL) return -err++;
    if (inThreshold == 0) return -err++;
    if (inRayDensity == 0) return -err++;
    if (inScale == 0.) return -err++;
    //if (outClusterList == NULL)     return -err++;

    VoxelClass *Data = inData;
    RodClusterList *ClusterList = inClusterList;

    unsigned int uRaysNum = inRayDensity * 2;

#ifdef ___RODRIGUEZ2009DEBUG___N
    dprintf("RayBurst start\n");
#endif

    for (unsigned int i = 0; i < inClusterList->getClusterNum(); i++) {
#ifdef ___RODRIGUEZ2009DEBUG___N
        dprintf("%d ", i);
#endif
      
        POINT3D CurNode = ClusterList->getCluster(i)->getNode();
        double z = CurNode.z;
        double *pRayLength = new double[uRaysNum];
        for (unsigned int j = 0; j < uRaysNum; j++) {
            double dCurDist = 1.;
            double x = CurNode.x;
            double y = CurNode.y;
            double step = 0.3;
            double theta = j / (double) uRaysNum * 2 * PI;
            double step_x = step * cos(theta); //(PI / inRayDensity * uRaysNum);
            double step_y = step * sin(theta); //PI / inRayDensity * uRaysNum);
            while (1) {
                x += step_x;
                y += step_y;
                if (Data->getData((unsigned int) x, (unsigned int) y, (unsigned int) z) <= inThreshold) break;
                dCurDist += step;
            }
            pRayLength[j] = dCurDist;
        }
        std::vector<double> vPathLength;
        for (unsigned int j = 0; j < inRayDensity; j++) {
            vPathLength.push_back(pRayLength[j] + pRayLength[j + inRayDensity]);
        }

        std::sort(vPathLength.begin(), vPathLength.end());
        //ClusterList->getCluster(i)->setDiam(vPathLength[inRayDensity/2] * inScale);

        int nSfx = inRayDensity / 2;
        double dResult = vPathLength[nSfx] * inScale;
        while (dResult >= 20
               && nSfx > 0) {
            dResult = vPathLength[nSfx] * inScale;
            nSfx /= 2;
        }
        if (dResult >= 20.)
            dResult = 20.;
        if (dResult <= 0.)
            dResult = 0.01;

        ClusterList->getCluster(i)->setDiam(dResult);

#ifdef ___RODRIGUEZ2009_PRINT___
        //printf("Node[%03u], Diam = %f\n", i, vPathLength[inRayDensity/2]);
#endif

        SAFEDELETE(pRayLength);
    }

    return 0;
}

int Rodriguez2009Smoothing(RodClusterList *inClusterList, RodClusterList *outClusterList)
{
    RodClusterList *destClusterList;
    if (inClusterList == 0) {
        return -1;
    }
    if (inClusterList == outClusterList || outClusterList == 0) {
        destClusterList = inClusterList;
    } else {
        destClusterList = outClusterList;
        *destClusterList = *inClusterList;
    }
    for (unsigned int i = 0; i < inClusterList->getClusterNum(); i++) {
        RodCluster *CurCluster = inClusterList->getCluster(i);
	if (CurCluster->getParentNum() != 1) continue;
	RodCluster *ParentCluster = CurCluster->getParent(0);
	if (ParentCluster->getParentNum() != 1) continue;
	RodCluster *ParentParentCluster = ParentCluster->getParent(0);
	if (CurCluster->getChildNum() != 1) continue;
	RodCluster *ChildCluster = CurCluster->getChild(0);
	if (ChildCluster->getChildNum() != 1) continue;
	RodCluster *ChildChildCluster = ChildCluster->getChild(0);
	POINT3D DestPoint = CurCluster->getNode();
        POINT3D ParentPoint = ParentCluster->getNode();
        POINT3D ParentParentPoint = ParentParentCluster->getNode();
        POINT3D ChildPoint = ChildCluster->getNode();
        POINT3D ChildChildPoint = ChildChildCluster->getNode();
        DestPoint.x += ParentPoint.x + ParentParentPoint.x
                + ChildPoint.x + ChildChildPoint.x;
        DestPoint.y += ParentPoint.y + ParentParentPoint.y
                + ChildPoint.y + ChildChildPoint.y;
        DestPoint.z += ParentPoint.z + ParentParentPoint.z
                + ChildPoint.z + ChildChildPoint.z;
        DestPoint.x /= 5.;
        DestPoint.y /= 5.;
        DestPoint.z /= 5.;
        destClusterList->getCluster(i)->setNode(DestPoint);
    }
    return 0;
}

 int Rodriguez2009GetSubbranch(RodClusterList *inClusterList,
                               unsigned int startClusterNo,
                               RodClusterList *outClusterList)
{
    if (inClusterList == NULL) return -1;
    if (outClusterList == NULL) return -2;
    if (inClusterList->getClusterNum() <= startClusterNo) return -3;

    outClusterList->clearCluster();
    
    unsigned int count = 0;
    RodCluster *curCluster = new RodCluster;
    *curCluster = *inClusterList->getCluster(startClusterNo);
    curCluster->setDistance(0);
    std::list<RodCluster*> curParentListRef;
    std::list<RodCluster*> nextParentListRef;
    outClusterList->addCluster(curCluster);
    curParentListRef.push_back(inClusterList->getCluster(startClusterNo));
    std::list<RodCluster*> curParentListDst;
    std::list<RodCluster*> nextParentListDst;
    curParentListDst.push_back(curCluster);

    while (curParentListRef.size()) {
        nextParentListRef.clear();
        nextParentListDst.clear();
        int curParentNum = curParentListRef.size();
        //for (int i = 0; i < curParentNum; i++) {
        std::list<RodCluster *>::iterator itDst = curParentListDst.begin();
        for (std::list<RodCluster*>::iterator itRef = curParentListRef.begin();
             itRef != curParentListRef.end();
             ++itRef) { 
            RodCluster *curParentClusterRef = *itRef;
            RodCluster *curParentClusterDst = *itDst;
            //dprintf("parent %d, child ", curParentClusterRef->getClusterNo());
            for (int j = 0; j < curParentClusterRef->getChildNum(); j++) {
                curCluster = new RodCluster;
                RodCluster *curChildClusterRef = curParentClusterRef->getChild(j);
                curCluster->setDiam(curChildClusterRef->getDiam());
                curCluster->setDistance(curParentClusterRef->getDistance() + 1);
                curCluster->setNode(curChildClusterRef->getNode());
                curCluster->setNodeNo(curChildClusterRef->getNodeNo());
                curCluster->setClusterNo(count);
                curCluster->setNodeNo(count + 1);
                curCluster->addParent(curParentClusterDst);
                curParentClusterDst->addChild(curCluster);
                nextParentListRef.push_back(curChildClusterRef);
                nextParentListDst.push_back(curCluster);
                outClusterList->addCluster(curCluster);
                count++;
            }
            //dprintf("\n");
            itDst++;
        }
        curParentListRef = nextParentListRef;
        curParentListDst = nextParentListDst;
    }

    for (int i = 0; i < outClusterList->getClusterNum(); i++) {
        RodCluster *curCluster = outClusterList->getCluster(i);
        curCluster->setClusterNo(i);
        curCluster->setNodeNo(i+1);
    }
    
    outClusterList->assembleClusters();
    
    return 0;
}

int Rodriguez2009MakeHoc(char *fileName,
                         char *dirName,
                         RodClusterList *inClusterList,
                         char *dendName,
                         VoxelClass *inVoxel,
                         char *suffix)
{

    FILE *fp_write;

    POINT3D Translation(0., 0., 0.);

    RodClusterList *ClusterList = inClusterList;

    unsigned int uClusterNum = inClusterList->getClusterNum();
    unsigned int uDendNum = uClusterNum - 1;
    unsigned int uDendValidNum = 0;

#if 0
    for (unsigned int i = 0; i < uClusterNum; i++) {
        for (unsigned int j = 0; j < ClusterList->getCluster(i)->getChildNum(); j++) {
            ClusterClass *tempCluster = ClusterList->getCluster(i)->getChild(j);
            if (tempCluster->getParent(0)->getClusterNo() != ClusterList->getCluster(i)->getClusterNo()) {
                continue;
            }
            uDendValidNum++;
        }
    }
    unsigned int uCon = 0;

    for (unsigned int i = 0; i < uClusterNum; i++) {
        unsigned int tempChildNum = ClusterList->getCluster(i)->getChildNum();
        for (unsigned int j = 0; j < tempChildNum; j++) {
            ClusterClass *tempChild = ClusterList->getCluster(i)->getChild(j);
            if (tempChild->getParent(0)->getClusterNo() != ClusterList->getCluster(i)->getClusterNo()
                    || tempChild->getDistance() - ClusterList->getCluster(i)->getDistance() > 1)
                continue;
            uCon++;
        }
    }
#endif
    if (dendName == NULL) {
        sprintf(dendName, "dendrite");
    }
    char fname[1024];
    sprintf(fname, "%s%s", dirName, fileName);
    printf("create file : %s", fname);
    fp_write = fopen(fname, "w");
    if (fp_write == NULL) {
        puts("file open error");
        return -1;
    }

    puts("MakeHocFile2()");

    fprintf(fp_write, "\n");
    fprintf(fp_write, "begintemplate Cell_%s\n", dendName);
    fprintf(fp_write, "public init, topol, shape, subsets, geom, biophys, geom_nseg, biophys_inhomo\n");
    fprintf(fp_write, "public synlist, x, y, z, position, connect2target\n");
    fprintf(fp_write, "public dend\n");
    fprintf(fp_write, "public all\n");
    fprintf(fp_write, "public fobj\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "create dend[%u]\n", uDendNum);
    fprintf(fp_write, "\n");
    fprintf(fp_write, "objref synlist\n");
    fprintf(fp_write, "objref fobj\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc init() {\n");

    // topol
    fprintf(fp_write, "\tfobj = new File()\n");
    if (suffix == NULL) {
        fprintf(fp_write, "\tfobj.ropen(\"Data_%s.txt\")\n", dendName);
    } else {
        fprintf(fp_write, "\tfobj.ropen(\"Data_%s_%s.txt\")\n", dendName, suffix);
    }
    fprintf(fp_write, "\ttopol()\n");
    fprintf(fp_write, "\tsubsets()\n");
    fprintf(fp_write, "\tgeom()\n");
    fprintf(fp_write, "\tbiophys()\n");
    fprintf(fp_write, "\tgeom_nseg()\n");
    fprintf(fp_write, "\tsynlist = new List()\n");
    //fprintf(fp_write, "\tsynapses()\n");
    fprintf(fp_write, "\tx = y = z = 0\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");


    //fprintf(fp_write, "xopen(\"$(NEURONHOME)/lib/hoc/noload.hoc\")\n");
    //fprintf(fp_write, "nrnmainmenu()\n");

    //fprintf(fp_write, "\n");

    //fprintf(fp_write, "load_file(\"electrod.hoc\")\n");
    //fprintf(fp_write, "load_file(\"pointman.hoc\")\n");
    //fprintf(fp_write, "load_file(\"stdlib.hoc\")\n");

    //fprintf(fp_write, "\n");

    fprintf(fp_write, "\n");

    fprintf(fp_write, "proc topol() { local from, to, temp\n");
    fprintf(fp_write, "\tshape()\n");
    fprintf(fp_write, "\tfor i = 1, fobj.scanvar() {\n");
    fprintf(fp_write, "\t\tfrom = fobj.scanvar()\n");
    fprintf(fp_write, "\t\tto = fobj.scanvar()\n");
    //fprintf(fp_write, "\t\tconnect dend[from](0), dend[to](1)\n");
    fprintf(fp_write, "\t\tconnect dend[to](1), dend[from](0)\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "}\n");

    fprintf(fp_write, "\n");


    fprintf(fp_write, "tspine = 0\n");
    fprintf(fp_write, "proc chkspine() {\n");
    fprintf(fp_write, "\tif($4 < 0) { nspine = nspine + 1 }\n");
    fprintf(fp_write, "\tpt3dadd($1, $2, $3, abs($4))\n");
    fprintf(fp_write, "}\n");

    fprintf(fp_write, "\n");

    // proc geometry()
    //fprintf(fp_write, "external lambda_f\n");
    fprintf(fp_write, "proc shape() { local i, j, jmax\n");
    fprintf(fp_write, "\tfor i = 0, fobj.scanvar() - 1 {\n");
    fprintf(fp_write, "\t\tdend[fobj.scanvar()] {\n");
    fprintf(fp_write, "\t\t\tpt3dclear()\n");
    fprintf(fp_write, "\t\t\t//jmax = fobj.scanvar()\n");
    fprintf(fp_write, "\t\t\tfor j = 1, 2 {\n");
    fprintf(fp_write, "\t\t\t\tchkspine(fobj.scanvar(), fobj.scanvar(), fobj.scanvar(), fobj.scanvar())\n");
    fprintf(fp_write, "\t\t\t}\n");
    //fprintf(fp_write, "\t\t\tnseg = int((L / (0.1 * lambda_f(100)) + 0.9) / 2) * 2 + 1\n");
    fprintf(fp_write, "\t\t}\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "}\n");

    fprintf(fp_write, "\n");


    fprintf(fp_write, "objref all\n");
    fprintf(fp_write, "proc subsets() { local i\n");
    fprintf(fp_write, "\tobjref all\n");
    fprintf(fp_write, "\tall = new SectionList()\n");
    fprintf(fp_write, "\tfor i = 0, %u - 1 { dend[i] all.append() }\n", uDendNum);
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");

    fprintf(fp_write, "proc geom() {\n");
    fprintf(fp_write, "\tforsec all { }\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");

    fprintf(fp_write, "external lambda_f\n");
    fprintf(fp_write, "proc geom_nseg() {\n");
    fprintf(fp_write, "\tforsec all { nseg = int((L / (0.1 * lambda_f(100)) + .9) / 2) * 2 + 1 }\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");


    fprintf(fp_write, "proc biophys() {\n");
    fprintf(fp_write, "\tforsec all {\n");
    fprintf(fp_write, "\t\tRa = 100\n");
    fprintf(fp_write, "\t\tcm = 1\n");
    fprintf(fp_write, "\t\t\n");
    fprintf(fp_write, "\t\tinsert hh\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");


    fprintf(fp_write, "proc biophys_inhomo() {}\n");
    fprintf(fp_write, "\n");


    fprintf(fp_write, "proc position() {\n");
    fprintf(fp_write, "\tfor i = 0, fobj.scanvar() - 1 {\n");
    fprintf(fp_write, "\tdend[i] for j = 0, n3d() - 1 {\n");
    fprintf(fp_write, "\t\tpt3dchange(j, $1 - x + x3d(j), $2 - y + y3d(j), $3 - z + z3d(j), diam3d(j)) }\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");

    fprintf(fp_write, "obfunc connect2target() { localobj nc //$o1 target point process, optional $o2 returned NetCon\n");
    fprintf(fp_write, "\tdend[$3] nc = new NetCon(&v(1), $o1)\n");
    fprintf(fp_write, "\tnc.threshold = 0\n");
    fprintf(fp_write, "\tnc.delay = 0\n");
    fprintf(fp_write, "\t\n");
    fprintf(fp_write, "\tif (numarg () == 3) { $o2 = nc }\n");
    fprintf(fp_write, "\treturn nc\n");
    fprintf(fp_write, "\t\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");

    fprintf(fp_write, "objref syn_\n");
    fprintf(fp_write, "proc synapses() { local sfx\n");
    fprintf(fp_write, "\tsfx = $1\n");
    fprintf(fp_write, "\tdend[sfx] syn_ = new ExpSyn(0.8) synlist.append(syn_)\n");
    fprintf(fp_write, "\tsyn_.tau = 2\n");
    fprintf(fp_write, "\tsyn_.e = -80\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");


    fprintf(fp_write, "func is_art() { return 0 }\n");


    fprintf(fp_write, "endtemplate Cell_%s\n", dendName);

    fprintf(fp_write, "\n");

    fclose(fp_write);

    char szOutputFileName[256];
    if (suffix != NULL) {
        sprintf(szOutputFileName, "%sData_%s_%s.txt", dirName, dendName, suffix);
    } else {
        sprintf(szOutputFileName, "%sData_%s.txt", dirName, dendName);
    }
    fp_write = fopen(szOutputFileName, "w");


    double dScaleX = 1., dScaleY = 1., dScaleZ = 1.;
    if (inVoxel == NULL) {
        dScaleX = inClusterList->getScalingX();
        dScaleY = inClusterList->getScalingY();
        dScaleZ = inClusterList->getScalingZ();
    } else {
        dScaleX = inVoxel->getScaleX();
        dScaleY = inVoxel->getScaleY();
        dScaleZ = inVoxel->getScaleZ();
    }

    /*
    unsigned int uCompartmentNum = 0;
    for (unsigned int i = 0; i < uDendNum; i++) {
        RodCluster *CurCluster = ClusterList->getCluster(i);
        if (CurCluster->getVoxelNum() == 0) continue;
        if (CurCluster->getParentNum() == 0) continue;
        uCompartmentNum++;
    }
     */


    fprintf(fp_write, "\t%u\n", uDendNum); //uDendNum);

    //uCompartmentNum = 0;
    for (unsigned int i = 0; i < uClusterNum; i++) {
        RodCluster *Child = ClusterList->getCluster(i);
        // if (Child->getVoxelNum() == 0) continue;
        if (Child->getParentNum() == 0) continue;
        RodCluster *Parent = Child->getParent(0);
        POINT3D NodeC = Child->getNode();
        POINT3D NodeP = Parent->getNode();
        //Child->setNodeNo(uCompartmentNum);
        //fprintf(fp_write, "\t\t%u\n", uCompartmentNum++);
        fprintf(fp_write, "\t\t%d\n", Child->getClusterNo() - 1);
        fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n", NodeP.x * dScaleX, NodeP.y * dScaleY, NodeP.z * dScaleZ, Parent->getDiam());
        fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n\n", NodeC.x * dScaleX, NodeC.y * dScaleY, NodeC.z * dScaleZ, Child->getDiam());

    }

#ifdef ___TOPOL_2010_07_23___
    for (unsigned int i = 1; i < uClusterNum; i++) {
        RodCluster *Child = ClusterList->getCluster(i);
        if (Child->getVoxelNum() == 0) continue;
        if (Child->getParentNum() == 0) continue;
        RodCluster *Parent = Child->getParent(0);
        POINT3D NodeC = Child->getNode();
        POINT3D NodeP = Parent->getNode();
        fprintf(fp_write, "\t\t%u\n", Child->getClusterNo());
        fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n", NodeP.x * dScaleX, NodeP.y * dScaleY, NodeP.z * dScaleZ, Parent->getDiam());
        fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n\n", NodeC.x * dScaleX, NodeC.y * dScaleY, NodeC.z * dScaleZ, Child->getDiam());
    }
#endif

#if 0
    POINT3D tempp = ClusterList->getCluster(0)->getVoxel(ClusterList->getCluster(1)->getCenterNo());
    tempp.x += Translation->x;
    tempp.y += Translation->y;
    tempp.z += Translation->z;
    fprintf(fp_write, "\t\t0\n");
    fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n", dScaleCoef_x * tempp.x, dScaleCoef_x * tempp.y, dScaleCoef_x * tempp.z - 2, ClusterList->getCluster(1)->getVoxelNum() * diamCoef);
    fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n", dScaleCoef_x * tempp.x, dScaleCoef_x * tempp.y, dScaleCoef_x * tempp.z, ClusterList->getCluster(1)->getVoxelNum() * diamCoef);
    fprintf(fp_write, "\n");
    //unsigned int tempCount = 0;

    unsigned int ClusterCount = 0;
    for (unsigned int i = 0; i < uClusterNum; i++) {
        ClusterClass *tempClusterFrom = ClusterArray + i;
        unsigned int loopNum = tempClusterFrom->getChildNum();
        POINT3D pointFrom = tempClusterFrom->getVoxel(tempClusterFrom->getCenterNo());
        double temp_x = dScaleCoef_x * (pointFrom.x + Translation->x);
        double temp_y = dScaleCoef_y * (pointFrom.y + Translation->y);
        double temp_z = dScaleCoef_z * (pointFrom.z + Translation->z);
        for (unsigned int j = 0; j < loopNum; j++) {
            ClusterClass *tempClusterTo = tempClusterFrom->getChild(j);
            if (tempClusterFrom->getClusterNo() != tempClusterTo->getParent(0)->getClusterNo())// tempClusterTo->getDistance() - tempClusterFrom->getDistance() > 1)
                continue;
            POINT3D pointTo = tempClusterTo->getVoxel(tempClusterTo->getCenterNo());
            pointTo.x += Translation->x;
            pointTo.y += Translation->y;
            pointTo.z += Translation->z;
            if (pointTo.x < 0 || pointTo.y < 0 || pointTo.z < 0) {
                printf("", tempClusterTo->getCenterNo());
            }
            if (!flag) {
                fprintf(fp_write, "\t\t%u//%u\n", ClusterCount++, tempClusterTo->getClusterNo());
            } else {
                fprintf(fp_write, "\t\t%u\n", tempClusterTo->getClusterNo());
            }

            fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n", temp_x, temp_y, temp_z, tempClusterFrom->getVoxelNum() * diamCoef);

            fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n",
                    dScaleCoef_x * pointTo.x,
                    dScaleCoef_y * pointTo.y,
                    dScaleCoef_z * pointTo.z,
                    tempClusterFrom->getVoxelNum() * diamCoef);
            fprintf(fp_write, "\n");
            //tempCount++;
        }
    }
#endif

    // connect

    unsigned int uConnectNum = 0;

    for (unsigned int i = 0; i < uClusterNum; i++) {
        if (ClusterList->getCluster(i)->getClusterNo() == 0) continue;
        // if (ClusterList->getCluster(i)->getVoxelNum() == 0) continue;
        if (ClusterList->getCluster(i)->getChildNum() == 0) continue;
        for (unsigned int j = 0; j < ClusterList->getCluster(i)->getChildNum(); j++) {
            uConnectNum++;
        }
    }

    fprintf(fp_write, "\t%u\n", uConnectNum); //uDendNum-1);

    for (unsigned int i = 0; i < uClusterNum; i++) {
        if (ClusterList->getCluster(i)->getClusterNo() == 0) continue;
        // if (ClusterList->getCluster(i)->getVoxelNum() == 0) continue;
        if (ClusterList->getCluster(i)->getChildNum() == 0) continue;
        for (unsigned int j = 0; j < ClusterList->getCluster(i)->getChildNum(); j++) {
            fprintf(fp_write, "\t\t%u\t%u\n",
                    ClusterList->getCluster(i)->getClusterNo() - 1,
                    ClusterList->getCluster(i)->getChild(j)->getClusterNo() - 1);
        }
    }

#if 0
    unsigned int tempCount = 0;
    for (unsigned int i = 1; i < uClusterNum; i++) {
        if (ClusterList->getCluster(i)->getChildNum() == 0)
            continue;
        ClusterClass *tempClusterFrom = ClusterList->getCluster(i);
        unsigned int loopNum = tempClusterFrom->getChildNum();
        unsigned int uFrom = tempClusterFrom->getClusterNo();
        for (unsigned int j = 0; j < loopNum; j++) {
            //if (tempClusterFrom->getChild(j)->getChildNum() == 0)
            //	continue;
            //if (tempClusterFrom->getChild(j)->getDistance() - tempClusterFrom->getDistance() > 1)
            //	break;
            if (tempClusterFrom->getChild(j)->getParent(0)->getClusterNo() != tempClusterFrom->getClusterNo()
                    || tempClusterFrom->getChild(j)->getDistance() - tempClusterFrom->getDistance() > 1)
                continue;
            fprintf(fp_write, "\t\t%u\t%u\n", tempClusterFrom->getChild(j)->getClusterNo(), uFrom);
            tempCount++;
        }
    }
    printf("count = %u\n", tempCount);

#endif
    //printf("count = %u\n", tempCount);
    fprintf(fp_write, "\n");

    fprintf(fp_write, "\n");


    fclose(fp_write);

    return 0;
}

int Rodriguez2009MakeHoc4Parallel(char *fname, RodClusterList *inClusterList, char *dendName, VoxelClass *inVoxel) {

    FILE *fp_write;


    POINT3D Translation(0., 0., 0.);

    RodClusterList *ClusterList = inClusterList;

    unsigned int uClusterNum = inClusterList->getClusterNum();
    unsigned int uDendNum = uClusterNum - 1;
    unsigned int uDendValidNum = 0;

#if 0
    for (unsigned int i = 0; i < uClusterNum; i++) {
        for (unsigned int j = 0; j < ClusterList->getCluster(i)->getChildNum(); j++) {
            ClusterClass *tempCluster = ClusterList->getCluster(i)->getChild(j);
            if (tempCluster->getParent(0)->getClusterNo() != ClusterList->getCluster(i)->getClusterNo()) {
                continue;
            }
            uDendValidNum++;
        }
    }
    unsigned int uCon = 0;

    for (unsigned int i = 0; i < uClusterNum; i++) {
        unsigned int tempChildNum = ClusterList->getCluster(i)->getChildNum();
        for (unsigned int j = 0; j < tempChildNum; j++) {
            ClusterClass *tempChild = ClusterList->getCluster(i)->getChild(j);
            if (tempChild->getParent(0)->getClusterNo() != ClusterList->getCluster(i)->getClusterNo()
                    || tempChild->getDistance() - ClusterList->getCluster(i)->getDistance() > 1)
                continue;
            uCon++;
        }
    }
#endif
    if (dendName == NULL) {
        sprintf(dendName, "dendrite");
    }

    printf("create file : %s", fname);
    fp_write = fopen(fname, "w");
    if (fp_write == NULL) {
        puts("file open error");
        return -1;
    }

    puts("MakeHocFile for Parallel ()");


    fprintf(fp_write, "load_file(\"stdlib.hoc\")\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "begintemplate Cell_%s\n", dendName);
    fprintf(fp_write, "public init, topol, shape, subsets, geom, biophys, geom_nseg, biophys_inhomo\n");
    fprintf(fp_write, "public addSectionInput, addSectionOutput\n");
    fprintf(fp_write, "public setPassiveModel, setActiveModel\n");
    fprintf(fp_write, "public synlist, x, y, z, rev, position, connect2target\n");
    fprintf(fp_write, "public dend\n");
    fprintf(fp_write, "public all\n");
    fprintf(fp_write, "public fobj\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "create dend[%u]\n", uDendNum);
    fprintf(fp_write, "\n");
    fprintf(fp_write, "objref synlist\n");
    fprintf(fp_write, "objref synno\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "objref all\n");
    fprintf(fp_write, "objref sectionIn, sectionOut, sectionActive\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "objref fobj\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc init() {\n");
    fprintf(fp_write, "\tfobj = new File()\n");
    fprintf(fp_write, "\tfobj.ropen(\"Data_%s.txt\")\n", dendName);
    fprintf(fp_write, "\tsectionIn = new SectionList()\n");
    fprintf(fp_write, "\tsectionOut = new SectionList()\n");
    fprintf(fp_write, "\tsectionActive = new SectionList()\n");
    fprintf(fp_write, "\tsynlist = new List()\n");
    fprintf(fp_write, "\tsynno = new Vector()\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "\tx = $1\n");
    fprintf(fp_write, "\ty = $2\n");
    fprintf(fp_write, "\tz = $3\n");
    fprintf(fp_write, "\trev = $4\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "\ttopol()\n");
    fprintf(fp_write, "\tsubsets()\n");
    fprintf(fp_write, "\tgeom()\n");
    fprintf(fp_write, "\tbiophys()\n");
    fprintf(fp_write, "\tgeom_nseg()\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc topol() { local from, to, temp\n");
    fprintf(fp_write, "\tshape()\n");
    fprintf(fp_write, "\tfor i = 1, fobj.scanvar() {\n");
    fprintf(fp_write, "\t\tfrom = fobj.scanvar()\n");
    fprintf(fp_write, "\t\tto = fobj.scanvar()\n");
    fprintf(fp_write, "\t\tconnect dend[to](1), dend[from](0)\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc shape() { local i, j, jmax\n");
    fprintf(fp_write, "\tfor i = 0, fobj.scanvar() - 1 {\n");
    fprintf(fp_write, "\t\tdend[fobj.scanvar()] {\n");
    fprintf(fp_write, "\t\t\tpt3dclear()\n");
    fprintf(fp_write, "\t\t\t//jmax = fobj.scanvar()\n");
    fprintf(fp_write, "\t\t\tfor j = 1, 2 {\n");
    fprintf(fp_write, "\t\t\t\tpt3dadd(x + rev * fobj.scanvar(), y + fobj.scanvar(), z + fobj.scanvar(), fobj.scanvar())\n");
    fprintf(fp_write, "\t\t\t}\n");
    fprintf(fp_write, "\t\t}\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc subsets() { local i localobj fobj_subset\n");
    fprintf(fp_write, "\tobjref all\n");
    fprintf(fp_write, "\tall = new SectionList()\n");
    fprintf(fp_write, "\tfor i = 0, %u - 1 { dend[i] all.append() }\n", uDendNum);
    fprintf(fp_write, "\n");
    fprintf(fp_write, "\tfobj_subset = new File()\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "\tfobj_subset.ropen(\"Subset_%s_in.txt\")\n", dendName);
    fprintf(fp_write, "\ti = 0\n");
    fprintf(fp_write, "\twhile (1) {\n");
    fprintf(fp_write, "\t\tvalue = fobj_subset.scanvar()\n");
    fprintf(fp_write, "\t\taddSectionInput(value)\n");
    fprintf(fp_write, "\t\tif (i %% 10 == 0) {\n");
    fprintf(fp_write, "\t\t\tdend[value] { insert hh }\n");
    fprintf(fp_write, "\t\t}\n");
    fprintf(fp_write, "\t\ti += 1\n");
    fprintf(fp_write, "\t\tif (fobj_subset.eof()) { break }\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "\tfobj_subset.close()\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "\tfobj_subset.ropen(\"Subset_%s_out.txt\")\n", dendName);
    fprintf(fp_write, "\twhile (1) {\n");
    fprintf(fp_write, "\t\tvalue = fobj_subset.scanvar()\n");
    fprintf(fp_write, "\t\taddSectionOutput(value)\n");
    fprintf(fp_write, "\t\tif (fobj_subset.eof()) { break }\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "\tfobj_subset.close()\n");
    fprintf(fp_write, "\t\n");
    fprintf(fp_write, "\tfobj_subset.ropen(\"Subset_%s_hh.txt\")\n", dendName);
    fprintf(fp_write, "\twhile (1) {\n");
    fprintf(fp_write, "\t\tvalue = fobj_subset.scanvar()\n");
    fprintf(fp_write, "\t\taddSectionActive(value)\n");
    fprintf(fp_write, "\t\tif (fobj_subset.eof()) { break }\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "\tfobj_subset.close()\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc geom() {\n");
    fprintf(fp_write, "\tforsec all { }\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "external lambda_f\n");
    fprintf(fp_write, "proc geom_nseg() {\n");
    fprintf(fp_write, "\tforsec all { nseg = int((L / (0.1 * lambda_f(100)) + .9) / 2) * 2 + 1 }\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc biophys() {\n");
    fprintf(fp_write, "\tforsec all {\n");
    fprintf(fp_write, "\t\tRa = 100\n");
    fprintf(fp_write, "\t\tcm = 1\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "\tsetPassiveModel()\n");
    fprintf(fp_write, "\tsetActiveModel()\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc biophys_inhomo() {}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc position() {\n");
    fprintf(fp_write, "\tfor i = 0, fobj.scanvar() - 1 {\n");
    fprintf(fp_write, "\tdend[i] for j = 0, n3d() - 1 {\n");
    fprintf(fp_write, "\t\tpt3dchange(j, $1 - x + x3d(j), $2 - y + y3d(j), $3 - z + z3d(j), diam3d(j)) }\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "objref syn_\n");
    fprintf(fp_write, "//syncount = 0\n");
    fprintf(fp_write, "obfunc makeSyn() {\n");
    fprintf(fp_write, "\t/*\n");
    fprintf(fp_write, "\tfor i = 0, syncount - 1 {\n");
    fprintf(fp_write, "\t\tif ($1 == synlistno[i]) return synlist.object(i)\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "\t*/\n");
    fprintf(fp_write, "\tfor i = 0, synno.size-1 {\n");
    fprintf(fp_write, "\t\tif ($1 == synno.x[i]) return synlist.object(i)\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "\t//\tprint $1\n");
    fprintf(fp_write, "\t//\tsynlistno[syncount] = $1\n");
    fprintf(fp_write, "\tsynno.append($1)\n");
    fprintf(fp_write, "//\tsyncount += 1\n");
    fprintf(fp_write, "\tdend[$1] syn_ = new Exp2Syn(0.5) synlist.append(syn_)\n");
    fprintf(fp_write, "\tsyn_.tau1 = $2\n");
    fprintf(fp_write, "\tsyn_.tau2 = $3\n");
    fprintf(fp_write, "\tsyn_.e = $4\n");
    fprintf(fp_write, "\treturn syn_\n");
    fprintf(fp_write, "\t/*\n");
    fprintf(fp_write, "\tdend[$1] syn_ = new Exp2Syn(0.5) synlist.append(syn_)\n");
    fprintf(fp_write, "\tsyn_.tau1 = $2\n");
    fprintf(fp_write, "\tsyn_.tau2 = $3\n");
    fprintf(fp_write, "\tsyn_.e = $4\n");
    fprintf(fp_write, "\treturn syn_\n");
    fprintf(fp_write, "\t*/\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "obfunc makeNetCon() { localobj nc\n");
    fprintf(fp_write, "\t// NetCon(source, target, threshold, delay, weight)\n");
    fprintf(fp_write, "\tprint $1\n");
    fprintf(fp_write, "\tdend[$1] nc = new NetCon(&v(0.5), $o2, $3, $4, $5)\n");
    fprintf(fp_write, "\treturn nc\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "obfunc getRecPoint() { localobj vec\n");
    fprintf(fp_write, "\tvec = new Vector()\n");
    fprintf(fp_write, "\tvec.append(840)\n");
    fprintf(fp_write, "\treturn vec\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc addSectionInput() {\n");
    fprintf(fp_write, "\tdend[$1] sectionIn.append()\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc addSectionOutput() {\n");
    fprintf(fp_write, "\tdend[$1] sectionOut.append()\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc addSectionActive() {\n");
    fprintf(fp_write, "\tdend[$1] sectionActive.append()\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc setPassiveModel() {\n");
    fprintf(fp_write, "\tforsec sectionIn {\n");
    fprintf(fp_write, "\t\tinsert pas\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "proc setActiveModel() {\n");
    fprintf(fp_write, "\tforsec sectionActive {\n");
    fprintf(fp_write, "\t\tinsert hh\n");
    fprintf(fp_write, "\t}\n");
    fprintf(fp_write, "}\n");
    fprintf(fp_write, "\n");
    fprintf(fp_write, "endtemplate Cell_%s\n", dendName);
    fprintf(fp_write, "\n");

    fclose(fp_write);

    char szOutputFileName[256];
    sprintf(szOutputFileName, "Data_%s.txt", dendName);
    fp_write = fopen(szOutputFileName, "w");


    double dScaleX = 1., dScaleY = 1., dScaleZ = 1.;
    if (inVoxel == NULL) {
        dScaleX = inClusterList->getScalingX();
        dScaleY = inClusterList->getScalingY();
        dScaleZ = inClusterList->getScalingZ();
    } else {
        dScaleX = inVoxel->getScaleX();
        dScaleY = inVoxel->getScaleY();
        dScaleZ = inVoxel->getScaleZ();
    }

    /*
    unsigned int uCompartmentNum = 0;
    for (unsigned int i = 0; i < uDendNum; i++) {
        RodCluster *CurCluster = ClusterList->getCluster(i);
        if (CurCluster->getVoxelNum() == 0) continue;
        if (CurCluster->getParentNum() == 0) continue;
        uCompartmentNum++;
    }
     */


    fprintf(fp_write, "\t%u\n", uDendNum); //uDendNum);

    //uCompartmentNum = 0;
    for (unsigned int i = 1; i < uClusterNum; i++) {
        RodCluster *Child = ClusterList->getCluster(i);
        // if (Child->getVoxelNum() == 0) continue;
        if (Child->getParentNum() == 0) continue;
        RodCluster *Parent = Child->getParent(0);
        POINT3D NodeC = Child->getNode();
        POINT3D NodeP = Parent->getNode();
        //Child->setNodeNo(uCompartmentNum);
        //fprintf(fp_write, "\t\t%u\n", uCompartmentNum++);
        fprintf(fp_write, "\t\t%u\n", Child->getClusterNo() - 1);
        fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n", NodeP.x * dScaleX, NodeP.y * dScaleY, NodeP.z * dScaleZ, Parent->getDiam());
        fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n\n", NodeC.x * dScaleX, NodeC.y * dScaleY, NodeC.z * dScaleZ, Child->getDiam());

    }

#ifdef ___TOPOL_2010_07_23___
    for (unsigned int i = 1; i < uClusterNum; i++) {
        RodCluster *Child = ClusterList->getCluster(i);
        // if (Child->getVoxelNum() == 0) continue;
        if (Child->getParentNum() == 0) continue;
        RodCluster *Parent = Child->getParent(0);
        POINT3D NodeC = Child->getNode();
        POINT3D NodeP = Parent->getNode();
        fprintf(fp_write, "\t\t%u\n", Child->getClusterNo());
        fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n", NodeP.x * dScaleX, NodeP.y * dScaleY, NodeP.z * dScaleZ, Parent->getDiam());
        fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n\n", NodeC.x * dScaleX, NodeC.y * dScaleY, NodeC.z * dScaleZ, Child->getDiam());
    }
#endif

#if 0
    POINT3D tempp = ClusterList->getCluster(0)->getVoxel(ClusterList->getCluster(1)->getCenterNo());
    tempp.x += Translation->x;
    tempp.y += Translation->y;
    tempp.z += Translation->z;
    fprintf(fp_write, "\t\t0\n");
    fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n", dScaleCoef_x * tempp.x, dScaleCoef_x * tempp.y, dScaleCoef_x * tempp.z - 2, ClusterList->getCluster(1)->getVoxelNum() * diamCoef);
    fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n", dScaleCoef_x * tempp.x, dScaleCoef_x * tempp.y, dScaleCoef_x * tempp.z, ClusterList->getCluster(1)->getVoxelNum() * diamCoef);
    fprintf(fp_write, "\n");
    //unsigned int tempCount = 0;

    unsigned int ClusterCount = 0;
    for (unsigned int i = 0; i < uClusterNum; i++) {
        ClusterClass *tempClusterFrom = ClusterArray + i;
        unsigned int loopNum = tempClusterFrom->getChildNum();
        POINT3D pointFrom = tempClusterFrom->getVoxel(tempClusterFrom->getCenterNo());
        double temp_x = dScaleCoef_x * (pointFrom.x + Translation->x);
        double temp_y = dScaleCoef_y * (pointFrom.y + Translation->y);
        double temp_z = dScaleCoef_z * (pointFrom.z + Translation->z);
        for (unsigned int j = 0; j < loopNum; j++) {
            ClusterClass *tempClusterTo = tempClusterFrom->getChild(j);
            if (tempClusterFrom->getClusterNo() != tempClusterTo->getParent(0)->getClusterNo())// tempClusterTo->getDistance() - tempClusterFrom->getDistance() > 1)
                continue;
            POINT3D pointTo = tempClusterTo->getVoxel(tempClusterTo->getCenterNo());
            pointTo.x += Translation->x;
            pointTo.y += Translation->y;
            pointTo.z += Translation->z;
            if (pointTo.x < 0 || pointTo.y < 0 || pointTo.z < 0) {
                printf("", tempClusterTo->getCenterNo());
            }
            if (!flag) {
                fprintf(fp_write, "\t\t%u//%u\n", ClusterCount++, tempClusterTo->getClusterNo());
            } else {
                fprintf(fp_write, "\t\t%u\n", tempClusterTo->getClusterNo());
            }

            fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n", temp_x, temp_y, temp_z, tempClusterFrom->getVoxelNum() * diamCoef);

            fprintf(fp_write, "\t\t%f\t%f\t%f\t%f\n",
                    dScaleCoef_x * pointTo.x,
                    dScaleCoef_y * pointTo.y,
                    dScaleCoef_z * pointTo.z,
                    tempClusterFrom->getVoxelNum() * diamCoef);
            fprintf(fp_write, "\n");
            //tempCount++;
        }
    }
#endif

    // connect

    unsigned int uConnectNum = 0;

    for (unsigned int i = 0; i < uClusterNum; i++) {
        if (ClusterList->getCluster(i)->getClusterNo() == 0) continue;
        // if (ClusterList->getCluster(i)->getVoxelNum() == 0) continue;
        if (ClusterList->getCluster(i)->getChildNum() == 0) continue;
        for (unsigned int j = 0; j < ClusterList->getCluster(i)->getChildNum(); j++) {
            uConnectNum++;
        }
    }

    fprintf(fp_write, "\t%u\n", uConnectNum); //uDendNum-1);

    for (unsigned int i = 0; i < uClusterNum; i++) {
        if (ClusterList->getCluster(i)->getClusterNo() == 0) continue;
        // if (ClusterList->getCluster(i)->getVoxelNum() == 0) continue;
        if (ClusterList->getCluster(i)->getChildNum() == 0) continue;
        for (unsigned int j = 0; j < ClusterList->getCluster(i)->getChildNum(); j++) {
            fprintf(fp_write, "\t\t%u\t%u\n",
                    ClusterList->getCluster(i)->getClusterNo() - 1,
                    ClusterList->getCluster(i)->getChild(j)->getClusterNo() - 1);
        }
    }

#if 0
    unsigned int tempCount = 0;
    for (unsigned int i = 1; i < uClusterNum; i++) {
        if (ClusterList->getCluster(i)->getChildNum() == 0)
            continue;
        ClusterClass *tempClusterFrom = ClusterList->getCluster(i);
        unsigned int loopNum = tempClusterFrom->getChildNum();
        unsigned int uFrom = tempClusterFrom->getClusterNo();
        for (unsigned int j = 0; j < loopNum; j++) {
            //if (tempClusterFrom->getChild(j)->getChildNum() == 0)
            //	continue;
            //if (tempClusterFrom->getChild(j)->getDistance() - tempClusterFrom->getDistance() > 1)
            //	break;
            if (tempClusterFrom->getChild(j)->getParent(0)->getClusterNo() != tempClusterFrom->getClusterNo()
                    || tempClusterFrom->getChild(j)->getDistance() - tempClusterFrom->getDistance() > 1)
                continue;
            fprintf(fp_write, "\t\t%u\t%u\n", tempClusterFrom->getChild(j)->getClusterNo(), uFrom);
            tempCount++;
        }
    }
    printf("count = %u\n", tempCount);

#endif
    //printf("count = %u\n", tempCount);
    fprintf(fp_write, "\n");

    fprintf(fp_write, "\n");


    fclose(fp_write);

    return 0;
}

int Rodriguez2009MergeClusterList(RodClusterList *inParent,
                                  unsigned int inParentNodeNo,
                                  RodClusterList *inChild,
                                  unsigned int inChildNodeNo,
                                  RodClusterList *outClusterList)
{
    RodClusterList *tempClusterList = new RodClusterList();
    RodClusterList *outBufClusterList = new RodClusterList();;

    // #. reconstruct the tree structure of inChild
    //      to be rooted in inChildNodeNo(root node)
    // #. add the child as a subbranch bifurcated from inParentNodeNo
    // #. renumbering ClusterNo of all connected clusters

    // outClusterList must be instanciated
    
    // null pointer passed
    if (inParent == NULL || inChild == NULL || outClusterList == NULL)
        return -1;

    // overflow
    if (inParent->getClusterNum() <= inParentNodeNo
        || inChild->getClusterNum() <= inChildNodeNo) {
        return -2;
    }

    // create a copy of child data, since child cluster will be destracted
    RodClusterList *childClusterList = new RodClusterList();
    *childClusterList = *inChild;

    //--------------------------------------------------------------------------
    // reconstruct the tree structure of inChild
    //--------------------------------------------------------------------------
    {
        dprintf("Rodriguez2009MergeClusterList step1\n");
        // 1. start from clusters[inChildNodeNo] ==> add to clusterListToEdit

        // while (clusterListToEdit have member(s))
        //   for every member of clusterListToEdit
        //     2. pop a cluster from clusterListToEdit ==> curCluster
        //     3. if curCluster's "original parent"
        //        (, which will be always allocated at the end of children list),
        //        have a parent, add "original parent" to clusterListNextToEdit.
        //     4. remove curCluster from "original parent"'s children list
        //     5. move "original parent"'s parent to its children list
        //     6. set curCluster as a new parent of "original parent"
        //  7. copy clusterListNextToEdit to clusterListToEdit,
        //     and clear clusterListNextToEdit

        std::vector<RodCluster *> clusterListToEdit;
        std::vector<RodCluster *> clusterListNextToEdit;
    
        RodCluster *startCluster = childClusterList->getCluster(inChildNodeNo);

        if (startCluster->getParentNum() != 0) {
            // 1.
            clusterListToEdit.push_back(childClusterList->getCluster(inChildNodeNo));
            startCluster->addChild(startCluster->getParent(0));
            startCluster->removeParent(startCluster->getParent(0));
        }
        // when ParentNum == 0, the startCluster is originally a root node

        while (clusterListToEdit.size() != 0) {
            for (int i = 0; i < clusterListToEdit.size(); i++) {

                // 2.
                RodCluster *curCluster = clusterListToEdit[i];
                // if (curCluster->getParentNum() == 0) {
                //     fprintf(stderr, "something wrong in algorithm.\n");
                //     continue;
                // }
                int parentNo = curCluster->getChildNum() - 1;
                RodCluster *parentCluster = curCluster->getChild(parentNo);

                // 3.
                if (parentCluster->getParentNum() != 0) {
                    clusterListNextToEdit.push_back(parentCluster);
                }

                // 4.
                parentCluster->removeChild(curCluster);

                // 5.
                parentCluster->addChild(parentCluster->getParent(0));
                parentCluster->removeParent(parentCluster->getParent(0));

                // 6.
                parentCluster->setParent(0, curCluster);
            }

            // 7.
            clusterListToEdit = clusterListNextToEdit;
            clusterListNextToEdit.clear();
        }
    } // end : reconstruct the tree structure of childClusterList


    //--------------------------------------------------------------------------
    // add the child as a subbranch bifurcated from inParentNodeNo
    //--------------------------------------------------------------------------
    {
        dprintf("Rodriguez2009MergeClusterList step2\n");
        *tempClusterList = *inParent;
        RodCluster *branchingPointClst
            = tempClusterList->getCluster(inParentNodeNo);
        branchingPointClst->addChild(childClusterList->getCluster(inChildNodeNo));
        childClusterList->getCluster(inChildNodeNo)->addParent(branchingPointClst);
        for (unsigned int i = 0; i < childClusterList->getClusterNum(); i++) {
            RodCluster *curCluster = childClusterList->getCluster(i);
            tempClusterList->addCluster(curCluster);
        }
    } // end : add the child as a subbranch bifurcated from inParentNodeNo


    //--------------------------------------------------------------------------
    // renumbering ClusterNo of all connected clusters
    //--------------------------------------------------------------------------
    {
        dprintf("Rodriguez2009MergeClusterList step3\n");
        unsigned int count = 0;
        int curDist = 0;
        std::vector<RodCluster *> clusterList;
        std::vector<RodCluster *> clusterListNext;
        clusterList.push_back(tempClusterList->getCluster(0));
        while (clusterList.size() != 0) {
            for (int i = 0; i < clusterList.size(); i++) {
                RodCluster *curCluster = clusterList[i];
                // dprintf("\t [new %5d, old %5d] Dist = %d\n",
                //         count,
                //         curCluster->getClusterNo(),
                //         curDist);
                curCluster->setClusterNo(count);
                curCluster->setNodeNo(count);
                curCluster->setDistance(curDist);
                outBufClusterList->addCluster(curCluster);
                count++;
                for (unsigned int j = 0; j < curCluster->getChildNum(); j++) {
                    clusterListNext.push_back(curCluster->getChild(j));
                }
            }
            clusterList = clusterListNext;
            clusterListNext.clear();
            curDist++;
        }
        clusterList.clear();
        clusterListNext.clear();
    } // end : renumbering ClusterNo of all connected clusters

    dprintf("Rodriguez2009MergeClusterList " \
            "copy outBufClusterList to outClusterList\n");

    // set output cluster list
    *outClusterList = *outBufClusterList;
    double scalex = inParent->getScalingX();
    double scaley = inParent->getScalingY();
    double scalez = inParent->getScalingZ();
    outClusterList->setScaling(scalex, scaley, scalez);
    
    dprintf("Rodriguez2009MergeClusterList " \
            "delete tempClusterList... ");

    delete tempClusterList;

    dprintf("ok\n");

    dprintf("Rodriguez2009MergeClusterList " \
            "delete outBufClusterList... ");
    
    outBufClusterList->nullClear();
    delete outBufClusterList;

    dprintf("ok\n");

    dprintf("Rodriguez2009MergeClusterList " \
            "delete childClusterList... ");

    childClusterList->nullClear();
    delete childClusterList;

    dprintf("ok\n");

    for (unsigned int i = 0; i < outClusterList->getClusterNum(); i++) {
        RodCluster *curCluster = outClusterList->getCluster(i);
        dprintf("Rodriguez2009MergeClusterList %u/%u\n",
                curCluster->getClusterNo(),
                outClusterList->getClusterNum()-1);
    }

    dprintf("Rodriguez2009MergeClusterList " \
            "merge finished, " \
            "ClusterNum = %u, " \
            "Scale (%f, %f, %f)\n",
            outClusterList->getClusterNum(),
            outClusterList->getScalingX(),
            outClusterList->getScalingY(),
            outClusterList->getScalingZ());

    return 0;
}

double calcMeanDistBetween2ClusterList(RodClusterList *clusterList1,
                                       RodClusterList *clusterList2,
                                       double delta)
{
    // dprintf("calcMeanDistBetween2ClusterList %p %p, delta = %f\n",
    //         clusterList1, clusterList2, delta);

    double result = 0.;
    int count = 0;
    for (unsigned int i = 0; i < clusterList1->getClusterNum(); i++) {
        RodCluster *curCluster = clusterList1->getCluster(i);
        POINT3D point1 = curCluster->getNode();

        double min;
        {
            POINT3D tempPoint = clusterList2->getCluster(0)->getNode();
            double dx = point1.x - tempPoint.x;
            double dy = point1.y - tempPoint.y;
            double dz = point1.z - tempPoint.z;
            min = dx * dx + dy * dy + dz * dz;
        }

        double d;
        for (unsigned int j = 1; j < clusterList2->getClusterNum(); j++) {
            POINT3D point2 = clusterList2->getCluster(j)->getNode();
            double dx = point1.x - point2.x;
            double dy = point1.y - point2.y;
            double dz = point1.z - point2.z;
            double d = dx * dx + dy * dy + dz * dz;
            if (d < min) {
                min = d;
            }
        }
        
        if (min < delta) {
            result += min;
            count++;
        }
    }
    return result / count;
}

double calcConsistency(RodClusterList *clusterList1,
                       RodClusterList *clusterList2, 
                       double delta)
{
    unsigned int count = 0;

    //dprintf("calcConsistency %p %p, delta = %f\n", clusterList1, clusterList2, delta);

    for (unsigned int i = 0; i < clusterList1->getClusterNum(); i++) {
        POINT3D point1 = clusterList1->getCluster(i)->getNode();
        for (unsigned int j = 1; j < clusterList2->getClusterNum(); j++) {
            POINT3D point2 = clusterList2->getCluster(j)->getNode();
            double dx = point1.x - point2.x;
            double dy = point1.y - point2.y;
            double dz = point1.z - point2.z;
            double d = dx * dx + dy * dy + dz * dz;
            if (d < delta) {
                count++;
                break;
            }
        }
    }
    return count / (double)clusterList1->getClusterNum();
}

int Rodriguez2009CompareClusterList(RodClusterList *inClusterListP,
                                    RodClusterList *inClusterListQ,
                                    double delta,
                                    double *outDiscrepancy,
                                    double outConsistency[2])
{
    if (inClusterListP == NULL) return -1;
    if (inClusterListQ == NULL) return -2;
    if (outDiscrepancy == NULL) return -3;
    if (outConsistency == NULL) return -4;
    if (inClusterListP->getClusterNum() == 0) return -5;
    if (inClusterListQ->getClusterNum() == 0) return -6;

    double discQP
        = calcMeanDistBetween2ClusterList(inClusterListP, inClusterListQ, delta);

    double discPQ
        = calcMeanDistBetween2ClusterList(inClusterListQ, inClusterListQ, delta);

    double discrepancy = (discQP + discPQ) / 2.;

    double consisPQ = calcConsistency(inClusterListP, inClusterListQ, delta);
    double consisQP = calcConsistency(inClusterListQ, inClusterListP, delta);

    *outDiscrepancy = discrepancy;
    outConsistency[0] = consisPQ;
    outConsistency[1] = consisQP;

    return 0;
}
