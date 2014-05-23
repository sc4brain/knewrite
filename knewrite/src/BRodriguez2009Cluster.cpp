/* 
 * File:   Rodriguez2009Cluster.cpp
 * Author: naska
 * 
 * Created on 2010/06/29, 15:03
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "BCommon.h"
#include "BRodriguez2009Cluster.h"
#include "BRodriguez2009VoxelList.h"

//int Rodriguez2009Cluster::instanceNum = 0;

unsigned int Rodriguez2009Cluster::init(void)
{

    return 0;
}

Rodriguez2009Cluster::Rodriguez2009Cluster()
{
    m_dDiam = 0.;
    m_uDistance = 0;
    m_uClusterNo = 0;
    m_Voxels = new Rodriguez2009VoxelList();

    for (int i = 0; i < ADJACENT_CLUSTER_NUM; i++) {
        m_Parents[i] = NULL;
        m_Children[i] = NULL;
    }

    m_nCurParentNum = 0;
    m_nCurChildNum = 0;

    m_uCenterNo = 0;

    m_Node = POINT3D(0, 0, 0);
    m_dScoopingDistance = 0.;
    m_uNodeNo = 0;

	//printf("+%d ", ++Rodriguez2009Cluster::instanceNum);
    //init();
}

Rodriguez2009Cluster::Rodriguez2009Cluster(Rodriguez2009Cluster &orig)
{

	m_dDiam = orig.getDiam();
	m_uDistance = orig.getDistance();
	m_uClusterNo = orig.getClusterNo();

    m_Voxels = orig.getRodriguez2009VoxelList();
    for (int i = 0; i < ADJACENT_CLUSTER_NUM; i++) {
        m_Parents[i] = NULL;
        m_Children[i] = NULL;
    }

    m_nCurParentNum = orig.getParentNum();
    m_nCurChildNum = orig.getChildNum();

    for (int i = 0; i < m_nCurParentNum; i++) {
        m_Parents[i] = orig.getParent(i);
    }
    for (int i = 0; i < m_nCurChildNum; i++) {
        m_Children[i] = orig.getChild(i);
    }

    m_uCenterNo = orig.getCenterNo();

    m_Node = orig.getNode();
    m_dScoopingDistance = orig.getScoopingDistance();
    m_uNodeNo = orig.getNodeNo();
}

Rodriguez2009Cluster::~Rodriguez2009Cluster() {
    if (m_Voxels != NULL)
        delete m_Voxels;
	//printf("-%d ", --Rodriguez2009Cluster::instanceNum);
}

Rodriguez2009Cluster
&Rodriguez2009Cluster::operator=(Rodriguez2009Cluster &orig)
{
	m_dDiam = orig.getDiam();
	m_uDistance = orig.getDistance();
	m_uClusterNo = orig.getClusterNo();

    *m_Voxels = *orig.getRodriguez2009VoxelList();
    for (int i = 0; i < ADJACENT_CLUSTER_NUM; i++) {
        m_Parents[i] = NULL;
        m_Children[i] = NULL;
    }

    m_nCurParentNum = orig.getParentNum();
    m_nCurChildNum = orig.getChildNum();

    for (int i = 0; i < m_nCurParentNum; i++) {
        m_Parents[i] = orig.getParent(i);
    }
    for (int i = 0; i < m_nCurChildNum; i++) {
        m_Children[i] = orig.getChild(i);
    }

    m_uCenterNo = orig.getCenterNo();

    m_Node = orig.getNode();
    m_dScoopingDistance = orig.getScoopingDistance();
    m_uNodeNo = orig.getNodeNo();

    return *this;
}

unsigned int Rodriguez2009Cluster::addVoxel(POINT3D in_Point)
{
    return m_Voxels->addPoint(in_Point);
}

unsigned int Rodriguez2009Cluster::setClusterNo(unsigned int in_uClusterNo)
{
    m_uClusterNo = in_uClusterNo;
}

unsigned int Rodriguez2009Cluster::getClusterNo(void)
{
    return m_uClusterNo;
}

unsigned int Rodriguez2009Cluster::setDistance(unsigned int in_uDistance)
{
    return m_uDistance = in_uDistance;
}

POINT3D Rodriguez2009Cluster::getVoxel(unsigned int in_No)
{
    return m_Voxels->getPoint(in_No);
}

int Rodriguez2009Cluster::getParentNum(void)
{
    return m_nCurParentNum;
}

int Rodriguez2009Cluster::getChildNum(void)
{
    return m_nCurChildNum;
}

int Rodriguez2009Cluster::setParentNum(int in_nNum)
{
	if (in_nNum >= ADJACENT_CLUSTER_NUM) return -1;
	return m_nCurParentNum = in_nNum;
}

int Rodriguez2009Cluster::setChildNum(int in_nNum)
{
	if (in_nNum >= ADJACENT_CLUSTER_NUM) return -1;
	return m_nCurChildNum = in_nNum;
}

void Rodriguez2009Cluster::removeParent(RodCluster* in_Cluster)
{
    unsigned int hitSfx = 0;
    for (unsigned int i = 0; i < m_nCurParentNum; i++) {
        if (m_Parents[i] == in_Cluster) {
            hitSfx = i;
            m_nCurParentNum--;
            break;
        }
    }

    for (unsigned int i = hitSfx; i < m_nCurParentNum; i++) {
        m_Parents[i] = m_Parents[i + 1];
    }
}

void Rodriguez2009Cluster::removeChild(RodCluster* in_Cluster)
{
    unsigned int hitSfx = 0;
    for (unsigned int i = 0; i < m_nCurChildNum; i++) {
        if (m_Children[i] == in_Cluster) {
            hitSfx = i;
            m_nCurChildNum--;
            break;
        }
    }

    for (unsigned int i = hitSfx; i < m_nCurChildNum; i++) {
        m_Children[i] = m_Children[i + 1];
    }
}

void Rodriguez2009Cluster::resettingCenterVoxel(POINT3D point)
{

}

RodCluster* Rodriguez2009Cluster::getParent(int in_nNo)
{
    return m_Parents[in_nNo % ADJACENT_CLUSTER_NUM];
}

RodCluster* Rodriguez2009Cluster::getChild(int in_nNo)
{
    return m_Children[in_nNo % ADJACENT_CLUSTER_NUM];
}

void Rodriguez2009Cluster::setParent(int in_nNo, RodCluster* in_Cluster)
{
    m_Parents[in_nNo % ADJACENT_CLUSTER_NUM] = in_Cluster;
    //m_nCurParentNum++;
}

void  Rodriguez2009Cluster::setChild(int in_nNo, RodCluster* in_Cluster)
{
    m_Children[in_nNo % ADJACENT_CLUSTER_NUM] = in_Cluster;
    //m_nCurChildNum++;
}

void Rodriguez2009Cluster::addParent(RodCluster *in_Cluster)
{
    m_Parents[m_nCurParentNum++] = in_Cluster;
}

void Rodriguez2009Cluster::addChild(RodCluster *in_Cluster)
{
	if (m_nCurChildNum >= ADJACENT_CLUSTER_NUM) {
		fprintf(stderr, "\nRodriguez2009Cluster addChild; Overflow\n");
		fprintf(stderr, "\tm_uClusterNo = %u\n", m_uClusterNo);
		exit(1);
	}
    m_Children[m_nCurChildNum++] = in_Cluster;
}

POINT3D Rodriguez2009Cluster::getCenter()
{
    return m_Voxels->getPoint(getCenterNo());
}

unsigned int Rodriguez2009Cluster::getCenterNo()
{
    return m_uCenterNo;
}

unsigned int Rodriguez2009Cluster::setCenterNo(unsigned int in_uCenterNo)
{
    return m_uCenterNo = in_uCenterNo;
}

// compute the center voxel in this cluster
int Rodriguez2009Cluster::calcCenter()
{
    POINT3D MedianPoint(0, 0, 0);
    unsigned int uPointNum = m_Voxels->getPointNum();

    // calc true median point
    for (int i = 0; i < uPointNum; i++) {
        MedianPoint.x += m_Voxels->getPoint(i).x;
        MedianPoint.y += m_Voxels->getPoint(i).y;
        MedianPoint.z += m_Voxels->getPoint(i).z;
    }
    MedianPoint.x /= uPointNum;
    MedianPoint.y /= uPointNum;
    MedianPoint.z /= uPointNum;

    // choose the most adjacent voxel to the median point.
    double dx0 = m_Voxels->getPoint(0).x - MedianPoint.x;
    double dy0 = m_Voxels->getPoint(0).y - MedianPoint.y;
    double dz0 = m_Voxels->getPoint(0).z - MedianPoint.z;
    double dMinDist = dx0 * dx0 + dy0 * dy0 + dz0 * dz0;
    unsigned int uMinDistNo = 0;

    for (int i = 1; i < uPointNum; i++) {
        double dx = m_Voxels->getPoint(i).x - MedianPoint.x;
        double dy = m_Voxels->getPoint(i).y - MedianPoint.y;
        double dz = m_Voxels->getPoint(i).z - MedianPoint.z;
        double dist = dx * dx + dy * dy + dz * dz;
        if (dMinDist > dist) {
            dMinDist = dist;
            uMinDistNo = i;
        }
    }

    return uMinDistNo;
}

double Rodriguez2009Cluster::calcSize()
{
    double minX = 0, minY = 0, minZ = 0;
    double maxX = 0, maxY = 0, maxZ = 0;

    if (m_Voxels->getPointNum() <= 0) {
        return 0.;
    }

    if (m_Voxels->getPointNum() == 1) {
        return sqrt(3);
    }

    POINT3D curPoint = m_Voxels->getPoint(0);
    minX = maxX = curPoint.x;
    minY = maxY = curPoint.y;
    minZ = maxZ = curPoint.z;

    for (unsigned int i = 1; i < m_Voxels->getPointNum(); i++) {
        curPoint = m_Voxels->getPoint(i);
        if (minX > curPoint.x) minX = curPoint.x;
        if (minY > curPoint.y) minY = curPoint.y;
        if (minZ > curPoint.z) minZ = curPoint.z;
        if (maxX < curPoint.x) maxX = curPoint.x;
        if (maxY < curPoint.y) maxY = curPoint.y;
        if (maxZ < curPoint.z) maxZ = curPoint.z;
    }

    double dx = maxX - minX;
    double dy = maxY - minY;
    double dz = maxZ - minZ;

    return sqrt(dx*dx + dy*dy + dz*dz);
}

double Rodriguez2009Cluster::calcScoopingDistance()
{
    double ret = 0.;

    for (unsigned int i = 0; i < m_Voxels->getPointNum(); i++) {
        double dx = m_Voxels->getPoint(i).x - m_Node.x;
        double dy = m_Voxels->getPoint(i).y - m_Node.y;
        double dz = m_Voxels->getPoint(i).z - m_Node.z;
        double dist = sqrt(dx*dx + dy*dy + dz*dz);
        if (ret < dist) {
            ret = dist;
        }
    }

    return m_dScoopingDistance = ret;
}
