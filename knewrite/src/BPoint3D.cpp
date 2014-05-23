
#include "BPoint3D.h"

bool POINT3D::operator==(POINT3D &point)
{
    if (this->x != point.x
        || this->y != point.y
        || this->z != point.z) {
        return false;
    } else {
        return true;
    }
}

bool POINT3D::operator!=(POINT3D &point)
{
    if (this->x != point.x
        || this->y != point.y
        || this->z != point.z) {
        return true;
    } else {
        return false;
    }
}

