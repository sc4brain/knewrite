
#include <stdio.h>
#include <math.h>
#include <string.h>

#include "BVoxelProcesses.h"
#include "BCommon.h"

int vpGray2Binary(VoxelClass *in_Voxel,
                VoxelClass *out_Voxel,
                unsigned char in_ucThreshold)
{
	// if (in_Voxel == NULL)						return -1;
	// if (out_Voxel == NULL)						return -2;

	// if (in_Voxel->getX() != out_Voxel->getX())	return -3;
	// if (in_Voxel->getY() != out_Voxel->getY())	return -4;
	// if (in_Voxel->getZ() != out_Voxel->getZ())	return -5;

	// int x = in_Voxel->getX();
	// int y = in_Voxel->getY();
	// int z = in_Voxel->getZ();
	unsigned char threshold = in_ucThreshold;
    if (threshold == 0) {
        return -1;
    }
    int length = in_Voxel->getX() * in_Voxel->getY() * in_Voxel->getZ();
    for (int i = 0; i < length; i++) {
        out_Voxel->setData(i, (!!(in_Voxel->getData(i) / threshold)) * 255);
    }

	// for (int i = 0; i < x; i++) {
	// 	for (int j = 0; j < y; j++) {
	// 		for (int k = 0; k < z; k++) {
	// 			if (in_Voxel->getData(i, j, k) > threshold)
	// 				out_Voxel->setData(i, j, k, 255);
	// 			else
	// 				out_Voxel->setData(i, j, k, 0);
	// 		}
	// 	}
	// }

	return 0;
}

//-------------------------------------------------------------------------------------------------
//
//	int Inversion()
//
//		反転
//
int vpInversion(VoxelClass *in_Voxel, VoxelClass *out_Voxel)
{
	
	if (in_Voxel == NULL)						return -1;
	if (out_Voxel == NULL)						return -2;

	if (in_Voxel->getX() != out_Voxel->getX())	return -3;
	if (in_Voxel->getY() != out_Voxel->getY())	return -4;
	if (in_Voxel->getZ() != out_Voxel->getZ())	return -5;
	int x = in_Voxel->getX();
	int y = in_Voxel->getY();
	int z = in_Voxel->getZ();

	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			for (int k = 0; k < z; k++) {
				out_Voxel->setData(i, j, k, 255 - in_Voxel->getData(i,j,k));
			}
		}
	}

	return 0;
}

// Voxelの表面の値を０にする
// in_widthは未実装
int vpHemming(VoxelClass *out_Voxel, int in_width)
{
	if (out_Voxel == NULL)						return -2;

	int x = out_Voxel->getX();
	int y = out_Voxel->getY();
	int z = out_Voxel->getZ();

	// x-y平面を０に
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			out_Voxel->setData(i, j, 0, 0);
			out_Voxel->setData(i, j, z-1, 0);
		}
	}
	// y-z平面を０に
	for (int j = 0; j < y; j++) {
		for (int k = 0; k < z; k++) {
			out_Voxel->setData(0, j, k, 0);
			out_Voxel->setData(x-1, j, k, 0);
		}
	}

	// z-x平面を０に
	for (int i = 0; i < x; i++) {
		for (int k = 0; k < z; k++) {
			out_Voxel->setData(i, 0, k, 0);
			out_Voxel->setData(i, y-1, k, 0);
		}
	}

	return 0;
}


int vpExtractLongestChain(VoxelClass *in_Voxel, VoxelClass *out_Voxel)
{
	if (in_Voxel == NULL)						return -1;
	if (out_Voxel == NULL)						return -2;

	if (in_Voxel->getX() != out_Voxel->getX())	return -3;
	if (in_Voxel->getY() != out_Voxel->getY())	return -4;
	if (in_Voxel->getZ() != out_Voxel->getZ())	return -5;

	int			size_x = in_Voxel->getX();
	int			size_y = in_Voxel->getY();
	int			size_z = in_Voxel->getZ();
	POINT3D		*LabeledVox;
	POINT3D		*LabeledVoxNext;
	int			nLabeledCount = 0;
	int			nLabeledNum = size_x*size_y*size_z;
	int			nLabelNo = 1;

	int			nMaxLabelNum = 0;
	int			nMaxLabelNo = 0;

	DistanceLabelClass temp_VoxelLabel(size_x, size_y, size_z, 0);
	DistanceLabelClass *VoxelLabel = &temp_VoxelLabel;

	vpHemming(in_Voxel);

	//in_Voxel->saveGraphs("img_debug\\output");

	LabeledVox = new POINT3D[nLabeledNum];
	LabeledVoxNext = new POINT3D[nLabeledNum];
	for (int i = 0; i < nLabeledNum; i++) {
		LabeledVox[i].x = LabeledVox[i].y = LabeledVox[i].z = 0;
		LabeledVoxNext[i].x = LabeledVoxNext[i].y = LabeledVoxNext[i].z = 0;
	}

	//DistanceLabelClass	*VoxelLabel = new DistanceLabelClass(size_x, size_y, size_z);

	//nLabelNo = 255;
	for (int i = 1; i < size_x-1; i++) {
		for (int j = 1; j < size_y-1; j++) {
			for (int k = 1; k < size_z-1; k++) {
				nLabeledCount = 0;
				// 値が零でなく且つラベリングされていない点を見つけたら
				if (in_Voxel->getData(i, j, k) && !VoxelLabel->getData(i, j, k)) {
					LabeledVox[nLabeledCount].x = i;
					LabeledVox[nLabeledCount].y = j;
					LabeledVox[nLabeledCount].z = k;
					VoxelLabel->setData(i, j, k, nLabelNo);
					nLabeledCount++;
					//
					int localCount = nLabeledCount;
					while (1) {
						int loopNum = localCount;
						localCount = 0;

						//	周りに値が零でない点があるか調べる
						for (int count = 0; count < loopNum; count++) {
#if defined (POINT3D_DOUBLE)
							double x = LabeledVox[count].x;
							double y = LabeledVox[count].y;
							double z = LabeledVox[count].z;
#else
							int x = LabeledVox[count].x;
							int y = LabeledVox[count].y;
							int z = LabeledVox[count].z;
#endif

							if (in_Voxel->getData(x+1, y, z) && !VoxelLabel->getData(x+1, y, z)) { LabeledVoxNext[localCount++] = POINT3D(x+1, y, z); VoxelLabel->setData(x+1, y, z, nLabelNo); }
							if (in_Voxel->getData(x, y+1, z) && !VoxelLabel->getData(x, y+1, z)) { LabeledVoxNext[localCount++] = POINT3D(x, y+1, z); VoxelLabel->setData(x, y+1, z, nLabelNo); }
							if (in_Voxel->getData(x, y, z+1) && !VoxelLabel->getData(x, y, z+1)) { LabeledVoxNext[localCount++] = POINT3D(x, y, z+1); VoxelLabel->setData(x, y, z+1, nLabelNo); }
							if (in_Voxel->getData(x-1, y, z) && !VoxelLabel->getData(x-1, y, z)) { LabeledVoxNext[localCount++] = POINT3D(x-1, y, z); VoxelLabel->setData(x-1, y, z, nLabelNo); }
							if (in_Voxel->getData(x, y-1, z) && !VoxelLabel->getData(x, y-1, z)) { LabeledVoxNext[localCount++] = POINT3D(x, y-1, z); VoxelLabel->setData(x, y-1, z, nLabelNo); }
							if (in_Voxel->getData(x, y, z-1) && !VoxelLabel->getData(x, y, z-1)) { LabeledVoxNext[localCount++] = POINT3D(x, y, z-1); VoxelLabel->setData(x, y, z-1, nLabelNo); }

							/*
							// 18近傍
							if (in_Voxel->getData(x+1, y+1, z) && !VoxelLabel->getData(x+1, y+1, z)) { LabeledVoxNext[localCount++] = POINT3D(x+1, y+1, z); VoxelLabel->setData(x+1, y+1, z, nLabelNo); }
							if (in_Voxel->getData(x+1, y, z+1) && !VoxelLabel->getData(x+1, y, z+1)) { LabeledVoxNext[localCount++] = POINT3D(x+1, y, z+1); VoxelLabel->setData(x+1, y, z+1, nLabelNo); }
							if (in_Voxel->getData(x+1, y-1, z) && !VoxelLabel->getData(x+1, y-1, z)) { LabeledVoxNext[localCount++] = POINT3D(x+1, y-1, z); VoxelLabel->setData(x+1, y-1, z, nLabelNo); }
							if (in_Voxel->getData(x+1, y, z-1) && !VoxelLabel->getData(x+1, y, z-1)) { LabeledVoxNext[localCount++] = POINT3D(x+1, y, z-1); VoxelLabel->setData(x+1, y, z-1, nLabelNo); }
							if (in_Voxel->getData(x, y+1, z+1) && !VoxelLabel->getData(x, y+1, z+1)) { LabeledVoxNext[localCount++] = POINT3D(x, y+1, z+1); VoxelLabel->setData(x, y+1, z+1, nLabelNo); }
							if (in_Voxel->getData(x, y+1, z-1) && !VoxelLabel->getData(x, y+1, z-1)) { LabeledVoxNext[localCount++] = POINT3D(x, y+1, z-1); VoxelLabel->setData(x, y+1, z-1, nLabelNo); }
							if (in_Voxel->getData(x, y-1, z+1) && !VoxelLabel->getData(x, y-1, z+1)) { LabeledVoxNext[localCount++] = POINT3D(x, y-1, z+1); VoxelLabel->setData(x, y-1, z+1, nLabelNo); }
							if (in_Voxel->getData(x, y-1, z-1) && !VoxelLabel->getData(x, y-1, z-1)) { LabeledVoxNext[localCount++] = POINT3D(x, y-1, z-1); VoxelLabel->setData(x, y-1, z-1, nLabelNo); }
							if (in_Voxel->getData(x-1, y+1, z) && !VoxelLabel->getData(x-1, y+1, z)) { LabeledVoxNext[localCount++] = POINT3D(x-1, y+1, z); VoxelLabel->setData(x-1, y+1, z, nLabelNo); }
							if (in_Voxel->getData(x-1, y, z+1) && !VoxelLabel->getData(x-1, y, z+1)) { LabeledVoxNext[localCount++] = POINT3D(x-1, y, z+1); VoxelLabel->setData(x-1, y, z+1, nLabelNo); }
							if (in_Voxel->getData(x-1, y-1, z) && !VoxelLabel->getData(x-1, y-1, z)) { LabeledVoxNext[localCount++] = POINT3D(x-1, y-1, z); VoxelLabel->setData(x-1, y-1, z, nLabelNo); }
							if (in_Voxel->getData(x-1, y, z-1) && !VoxelLabel->getData(x-1, y, z-1)) { LabeledVoxNext[localCount++] = POINT3D(x-1, y, z-1); VoxelLabel->setData(x-1, y, z-1, nLabelNo); }
							
							// 26近傍
							if (in_Voxel->getData(x+1, y+1, z+1) && !VoxelLabel->getData(x+1, y+1, z+1)) { LabeledVoxNext[localCount++] = POINT3D(x+1, y+1, z+1); VoxelLabel->setData(x+1, y+1, z+1, nLabelNo); }
							if (in_Voxel->getData(x+1, y+1, z-1) && !VoxelLabel->getData(x+1, y+1, z-1)) { LabeledVoxNext[localCount++] = POINT3D(x+1, y+1, z-1); VoxelLabel->setData(x+1, y+1, z-1, nLabelNo); }
							if (in_Voxel->getData(x+1, y-1, z+1) && !VoxelLabel->getData(x+1, y-1, z+1)) { LabeledVoxNext[localCount++] = POINT3D(x+1, y-1, z+1); VoxelLabel->setData(x+1, y-1, z+1, nLabelNo); }
							if (in_Voxel->getData(x+1, y-1, z-1) && !VoxelLabel->getData(x+1, y-1, z-1)) { LabeledVoxNext[localCount++] = POINT3D(x+1, y-1, z-1); VoxelLabel->setData(x+1, y+1, z-1, nLabelNo); }
							if (in_Voxel->getData(x-1, y+1, z+1) && !VoxelLabel->getData(x-1, y+1, z+1)) { LabeledVoxNext[localCount++] = POINT3D(x-1, y+1, z+1); VoxelLabel->setData(x-1, y+1, z+1, nLabelNo); }
							if (in_Voxel->getData(x-1, y+1, z-1) && !VoxelLabel->getData(x-1, y+1, z-1)) { LabeledVoxNext[localCount++] = POINT3D(x-1, y+1, z-1); VoxelLabel->setData(x-1, y+1, z-1, nLabelNo); }
							if (in_Voxel->getData(x-1, y-1, z+1) && !VoxelLabel->getData(x-1, y-1, z+1)) { LabeledVoxNext[localCount++] = POINT3D(x-1, y-1, z+1); VoxelLabel->setData(x-1, y-1, z+1, nLabelNo); }
							if (in_Voxel->getData(x-1, y-1, z-1) && !VoxelLabel->getData(x-1, y-1, z-1)) { LabeledVoxNext[localCount++] = POINT3D(x-1, y-1, z-1); VoxelLabel->setData(x-1, y-1, z-1, nLabelNo); }
							*/
						}

						//VoxelLabel->saveGraphs("img_debug\\output");
						nLabeledCount += localCount;
						if (nLabeledNum <= nLabeledCount) {
							puts("error: over flow");
							getchar();
						}
						// 隣接するVoxelが増えていなければ
						if (localCount == 0) {
							break;
						}
						for (int count = 0; count < localCount; count++) {
							LabeledVox[count] = LabeledVoxNext[count];
						}
					}
					// 最大の鎖かどうか調べる
					if (nMaxLabelNum < nLabeledCount) {
						nMaxLabelNum = nLabeledCount;
						nMaxLabelNo = nLabelNo;
						//printf("nMaxLabelNum:%d (%d)\n", nMaxLabelNum, nMaxLabelNo);
					}
					nLabelNo++;
					nLabeledCount = 0;
				}
			}
		}
	}

	for (int i = 0; i < size_x; i++) {
		for (int j = 0; j < size_y; j++) {
			for (int k = 0; k < size_z; k++) {
				if (VoxelLabel->getData(i, j, k) == nMaxLabelNo)
					out_Voxel->setData(i, j, k, 255);
				else
					out_Voxel->setData(i, j, k, 0);
			}
		}
	}

	//delete VoxelLabel;

    ASAFEDELETE(LabeledVox);
    ASAFEDELETE(LabeledVoxNext);

	return 0;
}
int vpCalcStatsFromHist(int *data, int dataNum, double *outMean, double *outVariance)
{
    double sum = 0.;
    int count = 0;
    for (int i = 0; i < dataNum; i++) {
        sum += i * data[i];
        count += data[i];
    }
    double mean = sum / count;

    if (mean <= 0.) {
        *outMean = *outVariance = -1.;
        return 0;
    }

    sum = 0;
    for (int i = 0; i < dataNum; i++) {
        double temp = data[i] - mean;
        sum += temp * temp;
    }
    double variance = sum / (count - 1);

    *outMean = mean;
    *outVariance = variance;

    return 0;
}

int vpLowContrastRegion(VoxelClass *in_Voxel, REGION3DARRAY *out_RegionArray,
                        int divx, int divy, int divz)
{
    if (in_Voxel == NULL) return -1;
    if (out_RegionArray == NULL) return -2;

    {
        int count = 0;
        int size = in_Voxel->getX() * in_Voxel->getY() * in_Voxel->getZ();
        for (int i = 0; i < size; i++) {
            count += !!in_Voxel->getData(i);
        }
        dprintf("vpLowContrastRegion count = %d\n", count);
    }

    int sizex = in_Voxel->getX();
    int sizey = in_Voxel->getY();
    int sizez = in_Voxel->getZ();
    int size = sizex * sizey * sizez;
    unsigned char *data = new unsigned char[size];
    for (int i = 0; i < size; i++) {
        data[i] = in_Voxel->getData(i);
    }
    
    int ret = vpLowContrastRegion(data,
                                  sizex, sizey, sizez,
                                  out_RegionArray,
                                  divx, divy, divz);

    ASAFEDELETE(data);
    return ret;    
}

int vpCalcHist(unsigned char *data,
               int sizex, int sizey, int sizez,
               int fromx, int fromy, int fromz,
               int tox, int toy, int toz,
               int hist[256])
{
    for (int i = 0; i < 256; i++) {
        hist[i] = 0;
    }

    // dprintf("vpCalcHist " \
    //         "region (%d-%d, %d-%d, %d-%d)\n",
    //         fromx, tox,
    //         fromy, toy,
    //         fromz, toz
    //         );
    
    int size = sizex * sizey * sizez;
    int lineSize = sizex;
    int pageSize = lineSize * sizey;
    for (int k = fromz; k < toz; k++) {
        int pageStep = k * pageSize;
        for (int j = fromy; j < toy; j++) {
            int overhead = pageStep + j * lineSize;
            for (int i = fromx; i < tox; i++) {
                unsigned char value = data[overhead + i];
                hist[CLIP_VALUE_INT(value, 256)]++;
            }
        }
    }

    return 0;
}



int vpLowContrastRegion(unsigned char *data,
                        int sizex, int sizey, int sizez,
                        REGION3DARRAY *out_RegionArray,
                        int divx, int divy, int divz)
{
    // !!parameter for judging low/high contrast
    double threshold = 50;

    // dprintf("vpLowContrastRegion " \
    //         "data = %p, " \
    //         "size (%d, %d, %d), " \
    //         "output Region ptr = %p, " \
    //         "div (%d, %d, %d)\n",
    //         data,
    //         sizex, sizey, sizez,
    //         out_RegionArray,
    //         divx, divy, divz);

    int segmentSizex = sizex / divx;
    int segmentSizey = sizey / divy;
    int segmentSizez = sizez / divz;
    
    int *separationX = new int[divx+1];
    int *separationY = new int[divy+1];
    int *separationZ = new int[divz+1];

    for (int i = 0; i < divx+1; i++) {
        separationX[i] = segmentSizex * i;
    }
    for (int i = 0; i < divy+1; i++) {
        separationY[i] = segmentSizey * i;
    }
    for (int i = 0; i < divz+1; i++) {
        separationZ[i] = segmentSizez * i;
    }

    out_RegionArray->clear();
    //REGION3D curRegion;
    for (int i = 0; i < divx; i++) {
        // curRegion.from.x = separationX[i];
        // curRegion.to.x = separationX[i+1];
        int fromx = separationX[i];
        int tox = separationX[i+1];
        for (int j = 0; j < divy; j++) {
            // curRegion.from.y = separationY[j];
            // curRegion.to.y = separationY[j+1];
            int fromy = separationY[j];
            int toy = separationY[j+1];
            for (int k = 0; k < divz; k++) {
                dprintf("vpLowContrastRegion " \
                        "Region(%d, %d, %d), ",
                        i, j, k);
                // curRegion.from.z = separationZ[k];
                // curRegion.to.z = separationZ[k+1];
                int fromz = separationZ[k];
                int toz = separationZ[k+1];
                int hist[256];
                dprintf("CalcHist ");
                vpCalcHist(data,
                           sizex, sizey, sizez,
                           fromx, fromy, fromz,
                           tox, toy, toz,
                           hist);
                dprintf("ok, ");
                double mean;
                double variance;
                dprintf("CalcStats ");
                vpCalcStatsFromHist(hist, 256, &mean, &variance);
                dprintf("ok, ");
                REGION3D curRegion;
                curRegion.from.x = fromx;
                curRegion.from.y = fromy;
                curRegion.from.z = fromz;
                curRegion.to.x = tox;
                curRegion.to.y = toy;
                curRegion.to.z = toz;
                if (mean < 0) {
                    curRegion.valued = -1.;
                    dprintf("Mean = %f, V = %f, CV = %f\n",
                            mean, variance, 0.);
                } else {
                    curRegion.valued = sqrt(variance) / mean;
                    dprintf("Mean = %f, V = %f, CV = %f\n",
                            mean, variance, sqrt(variance) / mean);
                }
                out_RegionArray->addRegion(curRegion);
            }
        }
    }

    ASAFEDELETE(separationX);
    ASAFEDELETE(separationY);
    ASAFEDELETE(separationZ);
    
    return 0;
}

int vpNoiseAdditionGaussian(unsigned char *data,
                            int sizex, int sizey, int sizez,
                            double SD)
{
    unsigned int length = sizex * sizey * sizez;
    dprintf("vpNoiseAdditionGaussian start\n");
    char buf[256];
    int count = 0;
    int dispCycle = length / 100;
    for (unsigned int i = 0; i < length; i++) {
        if (count++ / dispCycle) {
            sprintf(buf, "[%10u / %10u(%3.0f%%)]", i, length, i / (double)(length - 1) * 100);
            dprintf("\r");
            dprintf(buf);
            count = 0;
        }
        // int barLength = (int)(i / (double)length * 4000);
        // for (int j = 0; j < barLength; j++) {
        //     strcat(buf, "-");
        // }
        // strcat(buf, ">");
        // for (int j = barLength; j < 40; j++) {
        //     strcat(buf, " ");
        // }
        // strcat(buf, "|");
        double noiseAddedValue = getRandNormal(data[i], SD);
        if (noiseAddedValue < 0) {
            data[i] = 0;
        } else if (255 < noiseAddedValue) {
             data[i] = 255;
        } else {
            data[i] = (unsigned char)noiseAddedValue;
        }
    }
    //printf("\r[100%%]---------------------------------------->");
    printf("\nvpNoiseAdditionGaussian finished\n");
    return 0;
}

int vpBackgroundAdditionSin(unsigned char *data,
                            int sizex, int sizey, int sizez,
                            double x0, double y0, double z0,
                            double nx, double ny, double nz,
                            int minValue, int maxValue,
                            double omega)
{
    if (data == NULL) {
        return -1;
    }
    if (!sizex || !sizey || !sizez) {
        return -2;
    }

    double amplitude = maxValue / 2. - minValue / 2.;
    double shift = maxValue / 2. + minValue / 2.;

    unsigned int length = sizex * sizey * sizez;
    double delta = -(nx * x0 + ny * y0 + nz * z0);
    double nx2 = nx * nx;
    double ny2 = ny * ny;
    double nz2 = nz * nz;
    double n_length = sqrt(nx2 + ny2 + nz2);
    int pageSize = sizex * sizey;
    for (int k = 0; k < sizez; k++) {
        int pageStep = pageSize * k;
        double dz = k - z0;
        for (int j = 0; j < sizey; j++) {
            int overHead = pageStep + sizex * j;
            double dy = j - y0;
            for (int i = 0; i < sizex; i++) {
                // background will be the max value when d = PI/2/omega
                double d = (nx * i + ny * j + nz * k + delta);//
                if (d < 0) d /= -n_length;
                else d /= n_length;
                double dx = i - x0;
                double discriminant = dx * nx + dy * ny + dz * nz;
                if (discriminant < 0) d *= -1;
                int value = amplitude * sin(omega * d) + shift + data[overHead + i];
                value = POSITIVE_PASS(value);
                data[overHead + i] = (unsigned char)CLIP_VALUE_INT(value, 256);
            }
        }
    }

    return 0;
}

int vpBackgroundAdditionSphere(unsigned char *data,
                               int sizex, int sizey, int sizez,
                               double x0, double y0, double z0, double r,
                               int maxValue)
{
    if (data == NULL) {
        return -1;
    }
    if (!sizex || !sizey || !sizez) {
        return -2;
    }

    struct {
        struct {
            int x;
            int y;
            int z;
        } from;
        struct {
            int x;
            int y;
            int z;
        } to;
    } range = {
        {
            (int)(x0 - r),
            (int)(y0 - r),
            (int)(z0 - r),
        },
        {
            (int)(x0 + r),
            (int)(y0 + r),
            (int)(z0 + r),
        },
    };
    if (range.from.x < 0) range.from.x = 0;
    if (range.from.y < 0) range.from.y = 0;
    if (range.from.z < 0) range.from.z = 0;
    if (sizex < range.to.x) range.to.x = sizex;
    if (sizey < range.to.y) range.to.y = sizey;
    if (sizez < range.to.z) range.to.z = sizez;

    dprintf("vpBackgroundAdditionSphere " \
            "data = %p, " \
            "size (%d, %d, %d), " \
            "origin (%f, %f, %f), " \
            "r = %f, " \
            "maxValue = %d\n",
            data, sizex, sizey, sizez,
            x0, y0, z0,
            r, maxValue);

    double rr = r * r;

    double maxDividedWithR = maxValue / r;

    int pageSize = sizex * sizey;
    for (int k = range.from.z; k < range.to.z; k++) {
        int pageStep = pageSize * k;
        double dz = k - z0;
        double dz2 = dz * dz;
        for (int j = range.from.y; j < range.to.y; j++) {
            int overHead = pageStep + sizex * j;
            double dy = j - y0;
            double sum = dy * dy + dz2;
            for (int i = range.from.x; i < range.to.x; i++) {
                double dx = i - x0;
                double dx2 = dx * dx;
                if (dx2 + sum < rr) {
                    double d = sqrt(dx2 + sum);
                    int value = data[overHead + i] - maxDividedWithR * d + maxValue;
                    value = POSITIVE_PASS(value);
                    data[overHead + i] = (unsigned char)CLIP_VALUE_INT(value, 256);
                }
            }
        }
    }

    return 0;
}
