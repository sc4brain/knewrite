
#ifndef ___B_VOXEL_PROCESSES_H___
#define ___B_VOXEL_PROCESSES_H___

#include "BVoxelClass.h"
#include "BRegion3D.h"

int		vpGray2Binary(VoxelClass *in_Voxel, VoxelClass *out_Voxel, unsigned char in_ucThreshold);
int		vpHemming(VoxelClass *out_Voxel, int in_width = 1);
int		vpExtractLongestChain(VoxelClass *in_Voxel, VoxelClass *out_Voxel);
int		vpInversion(VoxelClass *in_Voxel, VoxelClass *out_Voxel);

int     vpCalcHist(VoxelClass *in_Voxel, REGION3D region, int hist[256]);
int     vpCalcStatsFromHist(int *data, int dataNum, double *mean, double *variance);
int     vpLowContrastRegion(VoxelClass *in_Voxel, REGION3DARRAY *out_RegionArray, 
                            int divx, int divy, int divz);

int     vpCalcHist(unsigned char *data,
                   int sizex, int sizey, int sizez,
                   int fromx, int fromy, int fromz,
                   int tox, int toy, int toz,
                   int hist[256]);
int     vpLowContrastRegion(unsigned char *data,
                            int sizex, int sizey, int sizez,
                            REGION3DARRAY *out_RegionArray,
                            int divx, int divy, int divz);

int     vpNoiseAdditionGaussian(unsigned char *data,
                                int sizex, int sizey, int sizez,
                                double SD);

int     vpBackgroundAdditionSin(unsigned char *data,
                                int sizex, int sizey, int sizez,
                                double x0, double y0, double z0,
                                double nx, double ny, double nz,
                                int minValue, int maxValue,
                                double omega);

int     vpBackgroundAdditionSphere(unsigned char *data,
                                   int sizex, int sizey, int sizez,
                                   double x0, double y0, double z0, double r,
                                   int maxValue);

#endif//___B_VOXEL_PROCESSES_H___
