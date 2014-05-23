
#include <stdio.h>

#ifdef ___USE_OPENCV___
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#pragma comment(lib, "cv.lib")
#pragma comment(lib, "cxcore.lib")
#pragma comment(lib, "cvaux.lib")
#pragma comment(lib, "highgui.lib")
#endif

#include "BVoxelClass.h"
#include "BCommon.h"

#ifndef NULL
#define NULL	(void *)0
#endif

#ifndef MAX_PATH
#define MAX_PATH 128
#endif

DistanceLabelClass::DistanceLabelClass(int in_X, int in_Y, int in_Z, unsigned int in_initValue)
{
	m_Data = NULL;
	m_nX = 0;
	m_nY = 0;
	m_nZ = 0;
	if (in_X < 0)	return;
	if (in_Y < 0)	return;
	if (in_Z < 0)	return;
	m_nX = in_X;
	m_nY = in_Y;
	m_nZ = in_Z;
	m_uMaxValue = 0;

#ifdef ___DATA_WITH_3D_ARRAY___
	m_Data = new unsigned int**[in_X];
	for (int i = 0; i < in_X; i++) {
		m_Data[i] = new unsigned int*[in_Y];
		for (int j = 0; j < in_Y; j++) {
			m_Data[i][j] = new unsigned int[in_Z];
			for (int k = 0; k < in_Z; k++) {
				m_Data[i][j][k] = in_initValue;
			}
		}
	}
#endif

	unsigned int loop = in_X * in_Y * in_Z;
	m_Data = new unsigned int [in_X * in_Y * in_Z];
	for (unsigned int i = 0; i < loop; i++) {
		m_Data[i] = in_initValue;
	}

}

DistanceLabelClass::~DistanceLabelClass(void)
{
#ifdef ___DATA_WITH_3D_ARRAY___
	for (int i = 0; i < m_nX; i++) {
		for (int j = 0; j < m_nY; j++) {
			SAFEDELETE(m_Data[i][j]);
		}
		ASAFEDELETE(m_Data[i]);
	}
	ASAFEDELETE(m_Data);
#endif
	ASAFEDELETE(m_Data);
}


// int DistanceLabelClass::loadGraphs(const char *in_sFileName, int in_nNum)
// {
// 	IplImage		*img;
// 	char			szFileName[MAX_PATH];
// 	int				nNum = in_nNum;

// 	if (nNum > m_nZ)
// 		nNum = m_nZ;
		

// 	for (int k = 0; k < in_nNum; k++) {
// 		sprintf(szFileName, "%s_%03d.bmp", in_sFileName, k);
// 		if (NULL == (img = cvLoadImage(szFileName, 0))) {
// 			return -1;
// 		}
// 		for (int i = 0; i < m_nX; i++) {
// 			for (int j = 0; j < m_nY; j++) {
// #ifdef ___DATA_WITH_3D_ARRAY___
// 				m_Data[i][j][k] = img->imageData[j * img->widthStep + i];
// #else
// 				m_Data[m_nX * m_nY * k + m_nX * j + i] = img->imageData[j * img->widthStep + i];
// #endif

// 			}
// 		}
// 		cvReleaseImage(&img);
// 	}

// 	return 0;
// }

// int DistanceLabelClass::saveGraphs(const char *in_sFileName, int in_nNum)
// {
// 	IplImage		*img;
// 	char			szFileName[MAX_PATH];
// 	int				nNum = in_nNum;

// 	if (nNum < 0)
// 		nNum = m_nZ;
// 	if (m_nZ < nNum)
// 		nNum = m_nZ;

// 	img = cvCreateImage(cvSize(m_nX, m_nY), 8, 1);
	
// 	for (int k = 0; k < nNum; k++) {
// 		for (int i = 0; i < m_nX; i++) {
// 			for (int j = 0; j < m_nY; j++) {
// #ifdef ___DATA_WITH_3D_ARRAY___
// 				img->imageData[j * img->widthStep + i] = (unsigned char)(m_Data[i][j][k] >> ((sizeof(unsigned int) - sizeof(unsigned char)) * 8));
// #else
// 				img->imageData[j * img->widthStep + i] = (unsigned char)(m_Data[m_nX * m_nY * k + m_nX * j + i] >> ((sizeof(unsigned int) - sizeof(unsigned char)) * 8));
// #endif
// 			}
// 		}
// 		sprintf(szFileName, "%s_%03d.jpg", in_sFileName, k);
// 		cvSaveImage(szFileName, img);
// 	}

// 	cvReleaseImage(&img);

// 	return 0;
// }

int DistanceLabelClass::saveData(const char *in_sFileName)
{
	FILE	*fp;

	fp = fopen(in_sFileName, "w");
	if (fp == NULL) {
		return -1;
	}

	for (int i = 0; i < m_nX; i++) {
		for (int j = 0; j < m_nY; j++) {
			for (int k = 0; k < m_nZ; k++) {
#ifdef ___DATA_WITH_3D_ARRAY___
				fprintf(fp, "%3d,%3d,%3d\t%u\n", i, j, k, m_Data[i][j][k]);
#else
				fprintf(fp, "%3d,%3d,%3d\t%u\n", i, j, k, m_Data[m_nX * m_nY * k + m_nX * j + i]);
#endif
			}
		}
	}

	fclose(fp);

	return 0;
}
