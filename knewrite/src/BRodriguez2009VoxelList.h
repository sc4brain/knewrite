/* 
 * File:   Rodriguez2009VoxelList.h
 * Author: naska
 *
 * Created on 2010/06/29, 15:10
 */

#ifndef _RODRIGUEZ2009VOXELLIST_H
#define	_RODRIGUEZ2009VOXELLIST_H

#include "BPoint3D.h"

class Rodriguez2009VoxelList {
	static int instanceNum;
public:
    Rodriguez2009VoxelList();
    Rodriguez2009VoxelList(Rodriguez2009VoxelList& orig);
    virtual ~Rodriguez2009VoxelList();
    virtual Rodriguez2009VoxelList &operator= (Rodriguez2009VoxelList &orig);

    virtual unsigned int addPoint(POINT3D inPoint);
    virtual POINT3D getPoint(unsigned int inNo);
    virtual unsigned int getPointNum(void) { return nPointNum; }
protected:
    POINT3D *Points;
    unsigned int nPointNum;

};

typedef Rodriguez2009VoxelList VoxelList;

#endif	/* _RODRIGUEZ2009VOXELLIST_H */

