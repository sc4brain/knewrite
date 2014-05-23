#ifndef ___B_REGION_3D_H___
#define ___B_REGION_3D_H___

#include "BPoint3D.h"

class REGION3D {
 public:
    REGION3D();

    virtual bool    operator==(REGION3D &region);
    virtual bool    operator!=(REGION3D &region);

    POINT3D from;
    POINT3D to;
    
    union {
        double valued;
    };
};

class REGION3DARRAY {
 public:
    REGION3DARRAY();
    virtual ~REGION3DARRAY();

    virtual int      getRegionNum() { return RegionNum; }
    REGION3D getRegion(int No);

    virtual void     clear();

    virtual int      replaceRegion(int No, REGION3D region);
    virtual int      deleteRegion(int No);
    virtual int      deleteRegion(REGION3D region);

    virtual int      addRegion(REGION3D region);

 protected:
    int       RegionNum;
    REGION3D *Regions;
};

/* template<class T> class REGION3D_VALUE : public REGION3D { */
/*  public: */
/*     REGION3D_VALUE(); */
/*     bool    operator==(REGION3D_VALUE<T> &region); */
/*     bool    operator!=(REGION3D_VALUE<T> &region); */
/*     T       value; */
/* }; */

/* template<class T> class REGION3DARRAY_VALUE : public REGION3DARRAY { */
/*  public: */
/*     REGION3DARRAY_VALUE(); */
/*     ~REGION3DARRAY_VALUE(); */

/*     int      getRegionNum() { return RegionNum; } */
/*     REGION3D_VALUE<T> getRegion(int No); */

/*     void     clear(); */

/*     int      replaceRegion(int No, REGION3D_VALUE<T> region); */
/*     int      deleteRegion(int No); */
/*     int      deleteRegion(REGION3D_VALUE<T> region); */

/*     int      addRegion(REGION3D_VALUE<T> region); */

/*  protected: */
/*     int             RegionNum; */
/*     REGION3D_VALUE<T> *Regions; */
/* }; */

#endif//___B_REGION_3D_H___
