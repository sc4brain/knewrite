#ifndef ___B_POINT_3D_H___
#define ___B_POINT_3D_H___

#define POINT3D_DOUBLE

class POINT3D {
 public:
	POINT3D(void)	{	x = y = z = 0; }
	POINT3D(short in_x, short in_y, short in_z) {
		x = in_x;
		y = in_y;
		z = in_z;
	}

    bool operator==(POINT3D &point);
    bool operator!=(POINT3D &point);

#if defined(POINT3D_DOUBLE)
	double		x;
	double		y;
	double		z;
#else
	short		x;
	short		y;
	short		z;
#endif

};

#endif//___B_POINT_3D_H___
