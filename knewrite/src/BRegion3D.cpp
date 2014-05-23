
#include <stdio.h>
#include "BRegion3D.h"

#include "BCommon.h"

//------------------------------------------------------------------------------
// REGION3D
//------------------------------------------------------------------------------
REGION3D::REGION3D()
{
    from = POINT3D(0, 0, 0);
    to = POINT3D(0, 0, 0);
}

bool REGION3D::operator==(REGION3D &region)
{
    if (this->from != region.from
        || this->to != region.to) {
        return false;
    } else {
        return true;
    }
}

bool REGION3D::operator!=(REGION3D &region)
{
    if (this->from != region.from
        || this->to != region.to) {
        return true;
    } else {
        return false;
    }
}


//------------------------------------------------------------------------------
// REGION3DARRAY
//------------------------------------------------------------------------------
REGION3DARRAY::REGION3DARRAY()
{
    RegionNum = 0;
    Regions = NULL;
}

REGION3DARRAY::~REGION3DARRAY()
{
    ASAFEDELETE(Regions);
    RegionNum = 0;
}

REGION3D REGION3DARRAY::getRegion(int No)
{
    if (RegionNum <= No) {
        return REGION3D();
    } else {
        return Regions[No];
    }
}

void REGION3DARRAY::clear()
{
    dprintf("REGION3DARRAY::clear ");
    ASAFEDELETE(Regions);
    RegionNum = 0;
    dprintf("ok\n");
}

int REGION3DARRAY::replaceRegion(int No, REGION3D region)
{
    if (RegionNum <= No) return -1;

    Regions[No] = region;

    return 0;
}

int REGION3DARRAY::deleteRegion(int No)
{
    if (RegionNum <= No) return -1;

    REGION3D *tempRegions = new REGION3D[RegionNum-1];

    int count = 0;
    for (int i = 0; i < RegionNum; i++) {
        if (No == i) continue;
        tempRegions[count++] = Regions[i];
    }

    ASAFEDELETE(Regions);
    RegionNum -= 1;

    Regions = new REGION3D[RegionNum];

    for (int i = 0; i < RegionNum; i++) {
        Regions[i] = tempRegions[i];
    }

    ASAFEDELETE(tempRegions);

    return 0;
}

int REGION3DARRAY::deleteRegion(REGION3D region)
{
    REGION3D *tempRegions = new REGION3D[RegionNum-1];
    
    int count = 0;
    for (int i = 0; i < RegionNum; i++) {
        if (Regions[i] == region) continue;
        tempRegions[count++] = Regions[i];
    }

    ASAFEDELETE(Regions);
    RegionNum -= 1;

    Regions = new REGION3D[RegionNum];

    for (int i = 0; i < RegionNum; i++) {
        Regions[i] = tempRegions[i];
    }

    ASAFEDELETE(tempRegions);

    return 0;
}

int REGION3DARRAY::addRegion(REGION3D region)
{
    REGION3D *tempRegions = new REGION3D[RegionNum+1];

    for (int i = 0; i < RegionNum; i++) {
        tempRegions[i] = Regions[i];
    }

    ASAFEDELETE(Regions);
    RegionNum += 1;

    Regions = new REGION3D[RegionNum];

    for (int i = 0; i < RegionNum-1; i++) {
        Regions[i] = tempRegions[i];
    }
    
    Regions[RegionNum-1] = region;

    ASAFEDELETE(tempRegions);

    return 0;
}


// //------------------------------------------------------------------------------
// // REGION3D_VALUE
// //------------------------------------------------------------------------------
// template<class T> REGION3D_VALUE<T>::REGION3D_VALUE()
// {
//     from = POINT3D(0, 0, 0);
//     to = POINT3D(0, 0, 0);
//     value = T();
// }

// template<class T> bool REGION3D_VALUE<T>::operator==(REGION3D_VALUE<T> &region)
// {
//     if (this->from != region.from
//         || this->to != region.to
//         || this->value != region.values) {
//         return false;
//     } else {
//         return true;
//     }
// }

// template<class T> bool REGION3D_VALUE<T>::operator!=(REGION3D_VALUE<T> &region)
// {
//     if (this->from != region.from
//         || this->to != region.to
//         || this->value != region.value) {
//         return true;
//     } else {
//         return false;
//     }
// }


// //------------------------------------------------------------------------------
// // REGION3DARRAY_VALUE
// //------------------------------------------------------------------------------
// template<class T> REGION3DARRAY_VALUE<T>::REGION3DARRAY_VALUE()
// {
//     RegionNum = 0;
//     Regions = NULL;
// }

// template<class T> REGION3DARRAY_VALUE<T>::~REGION3DARRAY_VALUE()
// {
//     ASAFEDELETE(Regions);
//     RegionNum = 0;
// }

// template<class T> REGION3D_VALUE<T> REGION3DARRAY_VALUE<T>::getRegion(int No)
// {
//     if (RegionNum <= No) {
//         return REGION3D_VALUE<T>();
//     } else {
//         return Regions[No];
//     }
// }

// template<class T> void REGION3DARRAY_VALUE<T>::clear()
// {
//     ASAFEDELETE(Regions);
//     RegionNum = 0;
// }

// template<class T> int REGION3DARRAY_VALUE<T>::replaceRegion(int No, REGION3D_VALUE<T> region)
// {
//     if (RegionNum <= No) return -1;

//     Regions[No] = region;

//     return 0;
// }

// template<class T> int REGION3DARRAY_VALUE<T>::deleteRegion(int No)
// {
//     if (RegionNum <= No) return -1;

//     REGION3D_VALUE<T> *tempRegions = new REGION3D_VALUE<T>[RegionNum-1];

//     int count = 0;
//     for (int i = 0; i < RegionNum; i++) {
//         if (No == i) continue;
//         tempRegions[count++] = Regions[i];
//     }

//     ASAFEDELETE(Regions);
//     RegionNum -= 1;

//     Regions = new REGION3D_VALUE<T>[RegionNum];

//     for (int i = 0; i < RegionNum; i++) {
//         Regions[i] = tempRegions[i];
//     }

//     ASAFEDELETE(tempRegions);

//     return 0;
// }

// template<class T> int REGION3DARRAY_VALUE<T>::deleteRegion(REGION3D_VALUE<T> region)
// {
//     REGION3D_VALUE<T> *tempRegions = new REGION3D_VALUE<T>[RegionNum-1];
    
//     int count = 0;
//     for (int i = 0; i < RegionNum; i++) {
//         if (Regions[i] == region) continue;
//         tempRegions[count++] = Regions[i];
//     }

//     ASAFEDELETE(Regions);
//     RegionNum -= 1;

//     Regions = new REGION3D_VALUE<T>[RegionNum];

//     for (int i = 0; i < RegionNum; i++) {
//         Regions[i] = tempRegions[i];
//     }

//     ASAFEDELETE(tempRegions);

//     return 0;
// }

// template<class T> int REGION3DARRAY_VALUE<T>::addRegion(REGION3D_VALUE<T> region)
// {
//     REGION3D_VALUE<T> *tempRegions = new REGION3D_VALUE<T>[RegionNum+1];

//     for (int i = 0; i < RegionNum; i++) {
//         tempRegions[i] = Regions[i];
//     }

//     ASAFEDELETE(Regions);
//     RegionNum += 1;

//     Regions = new REGION3D_VALUE<T>[RegionNum];

//     for (int i = 0; i < RegionNum-1; i++) {
//         Regions[i] = tempRegions[i];
//     }
    
//     Regions[RegionNum-1] = region;

//     ASAFEDELETE(tempRegions);

//     return 0;
// }
