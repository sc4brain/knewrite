/* 
 * File:   Rodriguez2009VoxelList.cpp
 * Author: naska
 * 
 * Created on 2010/06/29, 15:10
 */

#include <stdio.h>
#include <new>

#include "BRodriguez2009VoxelList.h"
#include "BCommon.h"

using namespace std;

#ifndef NULL
#define NULL (void *)0;
#endif

int Rodriguez2009VoxelList::instanceNum = 0;

Rodriguez2009VoxelList::Rodriguez2009VoxelList() {
    Points = NULL;
    nPointNum = 0;
	//printf("+%d", ++Rodriguez2009VoxelList::instanceNum);
}

Rodriguez2009VoxelList::Rodriguez2009VoxelList(Rodriguez2009VoxelList& orig) {
    ASAFEDELETE(Points);
    nPointNum = 0;
    unsigned int pointNum = orig.getPointNum();
    nPointNum = pointNum;
    Points = new POINT3D[nPointNum];
    for (unsigned int i = 0; i < nPointNum; i++) {
        Points[i] = orig.getPoint(i);
    }
	//printf("+%d", ++Rodriguez2009VoxelList::instanceNum);
}

Rodriguez2009VoxelList::~Rodriguez2009VoxelList() {
    ASAFEDELETE(Points);
	//printf("-%d", --Rodriguez2009VoxelList::instanceNum);
    nPointNum = 0;
}

Rodriguez2009VoxelList
&Rodriguez2009VoxelList::operator=(Rodriguez2009VoxelList &orig)
{
    ASAFEDELETE(Points);
    nPointNum = 0;

    nPointNum = orig.getPointNum();
    Points = new POINT3D[nPointNum];

    for (unsigned int i = 0; i < nPointNum; i++) {
        Points[i] = orig.getPoint(i);
    }

    return (*this);
}

unsigned int Rodriguez2009VoxelList::addPoint(POINT3D inPoint)
{
    POINT3D *tempPoints = NULL;
    
    if (nPointNum > 0) {
        try {
            tempPoints = new POINT3D[nPointNum];
        } catch(bad_alloc& ba) {
            fprintf(stderr, "Rodriguez2009VoxelList::addPoint() bad_alloc");
            return -1;
        }
    }

    for (unsigned int i = 0; i < nPointNum; i++) {
        tempPoints[i] = Points[i];
    }

    SAFEDELETE(Points);
    Points = new POINT3D[nPointNum+1];

    for (unsigned int i = 0; i < nPointNum; i++) {
        Points[i] = tempPoints[i];
    }
    Points[nPointNum] = inPoint;

    nPointNum++;

    delete[] tempPoints;

    return 0;
}

POINT3D Rodriguez2009VoxelList::getPoint(unsigned int inNo)
{
    if (inNo >= nPointNum) {
        return POINT3D(0, 0, 0);
    }

    return Points[inNo];
}
