/* 
 * File:   Rodriguez2009Cluster.h
 * Author: naska
 *
 * Created on 2010/06/29, 15:03
 */

#ifndef _RODRIGUEZ2009CLUSTER_H
#define	_RODRIGUEZ2009CLUSTER_H

#include "BRodriguez2009VoxelList.h"
#include "BPoint3D.h"

class Rodriguez2009VoxelList;

#define ADJACENT_CLUSTER_NUM 128

class Rodriguez2009Cluster {
	static int instanceNum;
protected:
    unsigned int    init(void);

public:
    Rodriguez2009Cluster();
    Rodriguez2009Cluster(Rodriguez2009Cluster &orig);
    virtual ~Rodriguez2009Cluster();
    virtual Rodriguez2009Cluster &operator=(Rodriguez2009Cluster &orig);

    unsigned int    addVoxel(POINT3D in_Point);

    unsigned int    setClusterNo(unsigned int in_uClusterNo);
                        //{ return m_uClusterNo = in_uClusterNo; }
    unsigned int    getClusterNo(void);// { return m_uClusterNo; }

    unsigned int    setDistance(unsigned int in_uDistance);
                        //{ return m_uDistance = in_uDistance; }
    unsigned int    getDistance(void) { return m_uDistance; }

    unsigned int    getVoxelNum(void) { return m_Voxels->getPointNum(); }
    POINT3D         getVoxel(unsigned int in_No);// { return m_Voxels[in_No]; }
    Rodriguez2009VoxelList* getRodriguez2009VoxelList(void)
    {
        return m_Voxels;
    }
    void setRodriguez2009VoxelList(Rodriguez2009VoxelList *inVoxel)
    {
        *m_Voxels = *inVoxel;
    }

    int             getParentNum(void);// { return m_nCurParentNum; }
    int             getChildNum(void);// { return m_nCurChildNum; }

    int             setParentNum(int in_nNum);// { m_nCurParentNum = in_nNum % 18; }
    int             setChildNum(int in_nNum);// { m_nCurChildNum = in_nNum % 18; }

    // unimplemented
    void            removeParent(Rodriguez2009Cluster *in_Cluster);
    void            removeChild(Rodriguez2009Cluster *in_Cluster);
    void            resettingCenterVoxel(POINT3D point);// { m_Voxels[m_uCenterNo] = point; }

    void            setDiam(double in_Diam) { m_dDiam = in_Diam; }
    double          getDiam(void) { return m_dDiam; }

    Rodriguez2009Cluster*     getParent(int in_nNo);// { return m_Parents[in_nNo % 18]; }
    Rodriguez2009Cluster*     getChild(int in_nNo);// { return m_Children[in_nNo % 18]; }

    void            setParent(int in_nNo, Rodriguez2009Cluster *in_Cluster);
    void            setChild(int in_nNo, Rodriguez2009Cluster *in_Cluster);

    void            addParent(Rodriguez2009Cluster *in_Cluster);
    void            addChild(Rodriguez2009Cluster *in_Cluster);

    POINT3D         getCenter(void);
    unsigned int    getCenterNo(void);
    unsigned int    setCenterNo(unsigned int in_uCenterNo);
    int             calcCenter(void);

    double          calcSize(void);
    void            setNode(POINT3D point) { m_Node = point; }
    POINT3D         getNode(void) { return m_Node; }
    void            setNodeNo(unsigned int inValue) { m_uNodeNo = inValue; }
    unsigned int    getNodeNo(void) { return m_uNodeNo; }

    double          calcScoopingDistance(void);
    double          setScoopingDistance(double inValue) { return m_dScoopingDistance = inValue; }
    double          getScoopingDistance(void) { calcScoopingDistance(); return m_dScoopingDistance; }

protected:
    // added 1/21
    double          m_dDiam;

    unsigned int    m_uDistance;
    unsigned int    m_uClusterNo;
    Rodriguez2009VoxelList       *m_Voxels;
    Rodriguez2009Cluster      *m_Parents[ADJACENT_CLUSTER_NUM];
    Rodriguez2009Cluster      *m_Children[ADJACENT_CLUSTER_NUM];
    int             m_nCurParentNum;
    int             m_nCurChildNum;

    unsigned int    m_uCenterNo;

    POINT3D         m_Node;
    unsigned int    m_uNodeNo;
    double          m_dScoopingDistance;
};
typedef Rodriguez2009Cluster RodCluster;


class Rodriguez2009ClusterList;

#define RODRIGUEZ2009_CLUSTERS_POINTER_ARRAY

#ifdef RODRIGUEZ2009_CLUSTERS_POINTER_ARRAY
#define CLST2P(obj) (obj)
#else
#define CLST2P(obj) (&(obj))
#endif


// reserved word
enum enumRodRW {
	RODRW_CLUSTER_NUM = 0,
	RODRW_DISTANCE,
	RODRW_CHILD_NUM,
	RODRW_PARENT_NUM,
    RODRW_NODE_NO,
    RODRW_SCOOPING_DISTANCE,
    RODRW_NODE,
    RODRW_DIAM,
    RODRW_MEDIAN_POINT,
    RODRW_MEMBER_NUM,
	RODRW_VOXELS,
    RODRW_SCALING,
	RODRWNUM,
};

enum enumRodReadMode {
	RODRM_NORMAL = 0,
    RODRM_CHILD,
    RODRM_PARENT,
	RODRM_VOXELS,
};



class Rodriguez2009ClusterList {
public:
    Rodriguez2009ClusterList(void);
    Rodriguez2009ClusterList(Rodriguez2009ClusterList& orig);
    virtual ~Rodriguez2009ClusterList(void);
    virtual Rodriguez2009ClusterList &operator=(Rodriguez2009ClusterList &orig);

    RodCluster*     getCluster(unsigned int in_No);
    unsigned int    getClusterNum(void) { return m_uClusterNum; }

    unsigned int    addCluster(RodCluster *in_Cluster);

    unsigned int    clearCluster(void);
	int             assembleClusters(void);

    void            nullClear(void);

    POINT3D         getScaling(void) { return m_Scaling; }
    double          getScalingX(void) { return m_Scaling.x; }
    double          getScalingY(void) { return m_Scaling.y; }
    double          getScalingZ(void) { return m_Scaling.z; }
    void            setScaling(double x, double y, double z) { m_Scaling.x = x; m_Scaling.y = y; m_Scaling.z = z; }
    void            setScaling(POINT3D inPoint) {
                        m_Scaling.x = inPoint.x;
                        m_Scaling.y = inPoint.y;
                        m_Scaling.z = inPoint.z;
                    }

    int             print(char *fname);
    int             load(char *fname);
    int             swc_print(char *fname);
    int             swc_load(char *fname); // unimplemented

protected:
#ifdef RODRIGUEZ2009_CLUSTERS_POINTER_ARRAY
    RodCluster      **m_Clusters;
#else
	RodCluster      *m_Clusters;
#endif
    unsigned int    m_uClusterNum;
    POINT3D         m_Scaling;
};
typedef Rodriguez2009ClusterList RodClusterList;


#endif	/* _RODRIGUEZ2009CLUSTER_H */

