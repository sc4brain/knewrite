
#include <stdio.h>
#include "BStackImageGenerator.h"

// when use opencv to load/save image files
#ifdef ___USE_OPENCV___

#include <cv.h>
#include <cxcore.h>
#include <highgui.h>

#pragma comment(lib, "cv.lib")
#pragma comment(lib, "cxcore.lib")
#pragma comment(lib, "cvaux.lib")
#pragma comment(lib, "highgui.lib")

#else

#include <QtGui>

#endif
// opencv

#include "MStackImage.h"
#include "CObjectCommunicatorID.h"

#include "BCommon.h"

#ifndef MAX_PATH
#define MAX_PATH 1024
#endif

MStackImage::MStackImage(void)
{
	DataArray = NULL;
	Size.x = Size.y = Size.z = 0;
	Scale.x = Scale.y = Scale.z = 0.;

    DataNo = -1;
}

MStackImage::MStackImage(int x, int y, int z)
{
	DataArray = NULL;
	Size.x = 0;
	Size.y = 0;
	Size.z = 0;
	if (x < 0)	return;
	if (y < 0)	return;
	if (z < 0)	return;
	Size.x = x;
	Size.y = y;
	Size.z = z;

	Scale.x = 1.0;
	Scale.y = 1.0;
	Scale.z = 1.0;

	unsigned int loop = x * y * z;
	DataArray = new unsigned char[x * y * z];
	for (unsigned int i = 0; i < loop; i++) {
		DataArray[i] = 0;
	}
}

MStackImage::~MStackImage(void)
{
	ASAFEDELETE(DataArray);
}

MStackImage &MStackImage::operator=(MStackImage &orig)
{
    ASAFEDELETE(DataArray);
    Size.x = orig.getX();
    Size.y = orig.getY();
    Size.z = orig.getZ();
    Scale.x = orig.getScaleX();
    Scale.y = orig.getScaleY();
    Scale.z = orig.getScaleZ();
    unsigned int size = Size.x * Size.y * Size.z;
    DataArray = new unsigned char[size];
    for (unsigned int i = 0; i < size; i++) {
        DataArray[i] = orig.getData(i);
    }

    return *this;
}

unsigned char MStackImage::setData(POINT3D point, unsigned char value)
{
    int x = (int)point.x;
    int y = (int)point.y;
    int z = (int)point.z;

    return DataArray[Size.x * Size.y * z + Size.x * y + x] = value;
}


int MStackImage::loadGraphs(const char *in_sFileName, int in_nNum, bool doMedian)
{
#ifdef ___USE_OPENCV___
	IplImage		*load_img, *img, *gray;
	char			szFileName[MAX_PATH];
	int             nNum = in_nNum;

	if (nNum > Size.z)
		nNum = Size.z;

	for (int k = 0; k < in_nNum; k++) {
		sprintf(szFileName, "%s%03d.bmp", in_sFileName, k);
		if (NULL == (load_img = cvLoadImage(szFileName, 0))) {
			return -1;
		}
		img = load_img;
		if (load_img->nChannels != 1) {
			gray = cvCreateImage(cvGetSize(load_img), IPL_DEPTH_8U, 1);
			cvCvtColor(load_img, gray, CV_BGR2GRAY);
			img = gray;
		}
		if (doMedian) {
			cvSmooth (img, img, CV_MEDIAN, 3, 0, 0, 0);
		}
		for (int i = 0; i < Size.x; i++) {
			for (int j = 0; j < Size.y; j++) {
				DataArray[Size.x * Size.y * k + Size.x * j + i] = img->imageData[j * img->widthStep + i];
			}
		}
		cvReleaseImage(&img);
	}

	return 0;
#else
    QImage loadImg(Size.x, Size.y, QImage::Format_RGB32);
    char szFileName[MAX_PATH];
    int nNum = in_nNum;

    if (nNum > Size.z)
        nNum = Size.z;

    int pageSize = Size.x * Size.y;
    for (int k = 0; k < in_nNum; k++) {
        int pageStep = pageSize * k;
        sprintf(szFileName, "%s%03d.bmp", in_sFileName, k);
        if (loadImg.load(szFileName)) {
            return -1;
        }
        for (int j = 0; j < Size.y; j++) {
            int overHead = pageSize + Size.x * j;
            for (int i = 0; i < Size.x; i++) {
                DataArray[overHead + i] = qGray(loadImg.pixel(i, j));
            }
        }
    }

    return 0;
#endif
}

int MStackImage::saveGraphs(const char *in_sFileName, int in_nNum)
{
#ifdef ___USE_OPENCV___
	IplImage		*img;
	char			szFileName[MAX_PATH];
	int				nNum = in_nNum;

	if (nNum < 0)
		nNum = Size.z;
	if (Size.z < nNum)
		nNum = Size.z;

	img = cvCreateImage(cvSize(Size.x, Size.y), 8, 1);
	
	for (int k = 0; k < nNum; k++) {
		for (int i = 0; i < Size.x; i++) {
			for (int j = 0; j < Size.y; j++) {
				img->imageData[j * img->widthStep + i] = DataArray[Size.x * Size.y * k + Size.x * j + i];
			}
		}
		sprintf(szFileName, "%s_%03d.bmp", in_sFileName, k);
		cvSaveImage(szFileName, img);
	}

	cvReleaseImage(&img);

	return 0;
#else
    QImage saveImg(Size.x, Size.y, QImage::Format_RGB32);
    char szFileName[MAX_PATH];
    int nNum = in_nNum;

	if (nNum < 0)
		nNum = Size.z;
	if (Size.z < nNum)
		nNum = Size.z;

    int pageSize = Size.x * Size.y;
    for (int k = 0; k < nNum; k++) {
        int pageStep = pageSize * k;
        for (int j = 0; j < Size.y; j++) {
            int overHead = pageStep + Size.x * j;
            for (int i = 0; i < Size.x; i++) {
                unsigned int value = DataArray[overHead + i];
                saveImg.setPixel(i, j, qRgb(value, value, value));
            }
        }
		sprintf(szFileName, "%s_%03d.bmp", in_sFileName, k);
        saveImg.save(szFileName);
    }
#endif
}

int MStackImage::saveData(const char *in_sFileName)
{
	FILE	*fp;

	fp = fopen(in_sFileName, "w");
	if (fp == NULL) {
		return -1;
	}

	for (int i = 0; i < Size.x; i++) {
		for (int j = 0; j < Size.y; j++) {
			for (int k = 0; k < Size.z; k++) {
				fprintf(fp, "%3d,%3d,%3d\t%u\n", i, j, k, DataArray[Size.x * Size.y * k + Size.x * j + i]);
			}
		}
	}

	fclose(fp);

	return 0;
}


int MStackImage::load(const char *iBaseName, int iStartSfx)
{
	FILE *fp;
	char fname[MAX_PATH];
	int imageNum = 0;

#ifdef ___USE_OPENCV___
	IplImage *loadImg, *img, *gray;
#else
    QImage loadImg;
#endif

	// check the file name format
	int digit = -1;
	for (int i = 1; i < 10; i++) {
		sprintf(BaseNameFormat, "%s%%0%dd.bmp", iBaseName, i);
		sprintf(fname, BaseNameFormat, 0);
		fp = fopen(fname, "r");
		if (fp != NULL) {
			digit = ImageNumberDigits = i;
			fclose(fp);
			break;
		}
	}

    dprintf("MStackImage::load " \
            "ImageNumberDigits = %d\n", ImageNumberDigits);

	if (digit == -1 || digit >= 10) {
		fprintf(stderr, "invalid ImageNumberDigits : MStackImage::load(%s, %d)\n", iBaseName, iStartSfx);
		return -1;
	}

	// conut the number of images -> imageNum
	for (int i = iStartSfx; ; i++) {
		sprintf(fname, BaseNameFormat, i);
		fp = fopen(fname, "r");
		if (fp == NULL) break;
		imageNum++;
		fclose(fp);
	}

	// get a image size
	sprintf(fname, BaseNameFormat, 0);
#ifdef ___USE_OPENCV___
	if (NULL == (loadImg = cvLoadImage(fname, 0))) {
		fprintf(stderr, "file open error : MStackImage::load(%s, %d)\n", iBaseName, iStartSfx);
		return -2;
	}
	img = loadImg;
	if (loadImg->nChannels != 1) {
		gray = cvCreateImage(cvGetSize(loadImg), IPL_DEPTH_8U, 1);
		cvCvtColor(loadImg, gray, CV_BGR2GRAY);
		img = gray;
	}

	// set the StackImage Size
	Size.x = img->width;
	Size.y = img->height;
	Size.z = imageNum;

	cvReleaseImage(&img);
#else
    if (!loadImg.load(fname)) {
		fprintf(stderr, "file open error : MStackImage::load(%s, %d)\n", iBaseName, iStartSfx);
		return -2;
    }
	Size.x = loadImg.width();
	Size.y = loadImg.height();
	Size.z = imageNum;
#endif

	if (DataArray != NULL) {
		ASAFEDELETE(DataArray);
	}
	DataArray = new unsigned char[Size.x * Size.y * Size.z];

	// load images
	for (int k = 0; k < Size.z; k++) {
		sprintf(fname, BaseNameFormat, k);
#ifdef ___USE_OPENCV___
		if (NULL == (loadImg = cvLoadImage(fname, 0))) {
			fprintf(stderr, "file open error : MStackImage::load(%s, %d)\n", iBaseName, iStartSfx);
			return -3;
		}
		img = loadImg;
		if (loadImg->nChannels != 1) {
			gray = cvCreateImage(cvGetSize(loadImg), IPL_DEPTH_8U, 1);
			cvCvtColor(loadImg, gray, CV_BGR2GRAY);
			img = gray;
		}
		int pageStep = Size.x * Size.y * k;
		for (int j = 0; j < Size.y; j++) {
			int step = pageStep + Size.x * j;
			int imageStep = img->widthStep * j;
			for (int i = 0; i < Size.x; i++) {
				DataArray[step + i] = img->imageData[imageStep + i];
			}
		}
		cvReleaseImage(&img);
#else
        if (!loadImg.load(fname)) {
			fprintf(stderr, "file open error : MStackImage::load(%s, %d)\n", iBaseName, iStartSfx);
			return -3;
        }
		int pageStep = Size.x * Size.y * k;
		for (int j = 0; j < Size.y; j++) {
			int overHead = pageStep + Size.x * j;
			for (int i = 0; i < Size.x; i++) {
				DataArray[overHead + i] = qGray(loadImg.pixel(i, j));
			}
		}
#endif
	}

    return 0;
}

int MStackImage::save(const char *iBaseName)
{
	char			fname[MAX_PATH];
	char            fnameFormat[1024];

#ifdef ___USE_OPENCV___
	IplImage		*img;
	img = cvCreateImage(cvSize(Size.x, Size.y), 8, 1);
#else
    QImage saveImg(Size.x, Size.y, QImage::Format_RGB32);
#endif

    dprintf("MStackImage::save " \
            "ImageNumberDigits = %d\n", ImageNumberDigits);
	sprintf(fnameFormat, "%s%%0%dd.bmp", iBaseName, ImageNumberDigits);

#ifdef ___USE_OPENCV___
    int pageSize = Size.x * Size.y;
	for (int k = 0; k < Size.z; k++) {
		int pageStep = pageSize * k;
		for (int j = 0; j < Size.y; j++) {
			int step = pageStep + Size.x * j;
			int imageStep = img->widthStep * j;
			for (int i = 0; i < Size.x; i++) {
				img->imageData[imageStep + i] = DataArray[step + i];
			}
		}
		sprintf(fname, fnameFormat, k);
		cvSaveImage(fname, img);
	}

	cvReleaseImage(&img);
#else
    int pageSize = Size.x * Size.y;
	for (int k = 0; k < Size.z; k++) {
		int pageStep = pageSize * k;
		for (int j = 0; j < Size.y; j++) {
			int overHead = pageStep + Size.x * j;
			for (int i = 0; i < Size.x; i++) {
                int value = DataArray[overHead + i];
				saveImg.setPixel(i, j, qRgb(value, value, value));
			}
		}
		sprintf(fname, fnameFormat, k);
        saveImg.save(fname);
	}
#endif

	return 0;
}

void MStackImage::reset(unsigned char value)
{
    unsigned int length = Size.x * Size.y * Size.z;
    for (unsigned int i = 0; i < length; i++) {
        DataArray[i] = value;
    }
}

void MStackImage::reset(int x, int y, int z, unsigned char value)
{
    ASAFEDELETE(DataArray);
    Size.x = x;
    Size.y = y;
    Size.z = z;
    DataArray = new unsigned char[x*y*z];
}

int MStackImage::generateData(int type, double params[GENERATE_STACKIMAGE_PARAMNUM])
{
    int ret = 0;
    switch (type)
        {
        case 0:
            if (generate_tree(this, params[0], params[1], params[2], params[3], params[4], 150) < 0)
                ret = -1;
            break;
        case 1:
            if (generate_extraneous_object(this, params[0], params[1], params[2], params[3], params[4]) < 0)
                ret = -1;
            break;
        default:
            break;
        }

    int div = 1;
    for (int i = 0; i <= 10; i++) {
        if (Size.z / div == 0) {
            ImageNumberDigits = i;
            break;
        }
        div *= 10;
    }


    dprintf("MStackImage::generateData " \
            "ImageNumberDigits = %d\n", ImageNumberDigits);

    return ret;
}


/*
MStackImageList::MStackImageList(void)
{
	Num = MAX_STACK_IMAGE_NUM;
}
*/

void MStackImage::procedure(int ID, char *data, int byte)
{
	switch (ID) {

        case COMID_LOAD_STACKIMAGE: {
            DATAFORMAT_LOAD_STACKIMAGE *recvData
                = (DATAFORMAT_LOAD_STACKIMAGE *)data;

            dprintf("MStackImage::procedure DataNo = %d, recv dataNo = %d\n",
                    DataNo, recvData->dataNo);
            dprintf("MStackImage::procedure ID:%d, baseName:%s\n",
                    ID, recvData->baseName);

            if (recvData->dataNo != DataNo) {
                return;
            }

            Scale.x = recvData->scale.x;
            Scale.y = recvData->scale.y;
            Scale.z = recvData->scale.z;

            // load data from a file
            int ret = load(recvData->baseName);
			if (ret < 0) {
                fprintf(stderr, "cannot open file (%d): %s\n", ret, data);
                return;
            }

            DATAFORMAT_LOAD_STACKIMAGE_OK sendData;
            sendData.ptr = DataArray;
            sendData.dataNo = recvData->dataNo;
            sendData.size.x = Size.x;
            sendData.size.y = Size.y;
            sendData.size.z = Size.z;
            sendData.scale.x = Scale.x;
            sendData.scale.y = Scale.y;
            sendData.scale.z = Scale.z;

            dprintf("MStackImage::procedure sendData\n");
            dprintf("MStackImage::procedure ptr = %p\n", sendData.ptr);
            dprintf("MStackImage::procedure size.(x, y, z) = (%d, %d, %d)\n",
                    sendData.size.x, sendData.size.y, sendData.size.z);
            dprintf("MStackImage::procedure scale.(x, y, z) = (%f, %f, %f)\n",
                    sendData.scale.x, sendData.scale.y, sendData.scale.z);
            dprintf("MStackImage::procedure sizeof(sendData) = %d\n",
                    sizeof(sendData));

            putData(COMID_LOAD_STACKIMAGE_OK,
                    (char *)&sendData, sizeof(sendData));

			return;
        } // COMID_LOAD_STACKIMAGE

        case COMID_STORE_STACKIMAGE: {
            DATAFORMAT_STORE_STACKIMAGE *recvData
                = (DATAFORMAT_STORE_STACKIMAGE *)data;

            if (DataNo != recvData->dataNo) {
                return;
            }

            dprintf("MStackImage::procedure " \
                    "got STORE_STACKIMAGE\n");
            dprintf("MStackImage::procedure " \
                    "ptr = %p, " \
                    "dataNo = %d, " \
                    "size (%d, %d, %d), " \
                    "scale (%f, %f, %f)\n",
                    recvData->ptr,
                    recvData->dataNo, 
                    recvData->size.x, 
                    recvData->size.y, 
                    recvData->size.z,
                    recvData->scale.x, 
                    recvData->scale.y, 
                    recvData->scale.z);

            ASAFEDELETE(DataArray);
            Size.x = recvData->size.x;
            Size.y = recvData->size.y;
            Size.z = recvData->size.z;
            int length = Size.x * Size.y * Size.z;
            DataArray = new unsigned char[length];
            unsigned char *dataPtr = recvData->ptr;
            for (int i = 0; i < length; i++) {
                DataArray[i] = dataPtr[i];
            }
            Scale.x = recvData->scale.x;
            Scale.y = recvData->scale.y;
            Scale.z = recvData->scale.z;

            DATAFORMAT_STORE_STACKIMAGE_OK sendData;
            sendData.ptr = DataArray;
            sendData.dataNo = DataNo;
            sendData.size.x = Size.x;
            sendData.size.y = Size.y;
            sendData.size.z = Size.z;
            sendData.scale.x = Scale.x;
            sendData.scale.y = Scale.y;
            sendData.scale.z = Scale.z;

            dprintf("MStackImage::procedure sendData\n");
            dprintf("MStackImage::procedure ptr = %p\n", sendData.ptr);
            dprintf("MStackImage::procedure dataNo = %d\n", sendData.dataNo);
            dprintf("MStackImage::procedure size.(x, y, z) = (%d, %d, %d)\n",
                    sendData.size.x, sendData.size.y, sendData.size.z);
            dprintf("MStackImage::procedure scale.(x, y, z) = (%f, %f, %f)\n",
                    sendData.scale.x, sendData.scale.y, sendData.scale.z);

            putData(COMID_STORE_STACKIMAGE_OK,
                    (char *)&sendData, sizeof(sendData));

            return;
        } // COMID_STORE_STACKIMAGE

        case COMID_SAVE_STACKIMAGE: {
            DATAFORMAT_SAVE_STACKIMAGE *recvData
                = (DATAFORMAT_SAVE_STACKIMAGE *)data;

            if (DataNo != recvData->dataNo) {
                return;
            }

            dprintf("MStackImage::procedure ID:%d, baseName:%s\n",
                    ID, recvData->baseName);

            // struct {
            //     double x;
            //     double y;
            //     double z;
            // } tempScale;
            // tempScale.x = Scale.x;
            // tempScale.y = Scale.y;
            // tempScale.z = Scale.z;
            // Scale.x = recvData->scale.x;
            // Scale.y = recvData->scale.y;
            // Scale.z = recvData->scale.z;

            QDir directory(".");
            if (!directory.mkpath(QString(recvData->dirName))) {
                fprintf(stderr, "cannot create directory : %s\n",
                        recvData->dirName);
                return;
            }

            // save data
			if (save(recvData->baseName) < 0) {
                fprintf(stderr, "cannot open file: %s\n", recvData->baseName);
                return;
            }

            DATAFORMAT_SAVE_STACKIMAGE_OK sendData;
            putData(COMID_SAVE_STACKIMAGE_OK,
                    (char *)&sendData, sizeof(sendData));

            // Scale.x = tempScale.x;
            // Scale.y = tempScale.y;
            // Scale.z = tempScale.z;

            return;
        } // COMID_SAVE_STACKIMAGE

        case COMID_REQUEST_STACKIMAGE_POINTER: {
            DATAFORMAT_REQUEST_STACKIMAGE_POINTER *recvData
                = (DATAFORMAT_REQUEST_STACKIMAGE_POINTER *)data;

            if (recvData->dataNo != DataNo) {
                return;
            }

            dprintf("MStackImage::procedure " \
                    "got REQUEST_STACKIMAGE_POINTER\n");
            dprintf("MStackImage::procedure ID:%d, dataNo:%d\n",
                    ID, recvData->dataNo);
            
            DATAFORMAT_STACKIMAGE_POINTER sendData;
            sendData.ptr = DataArray;
            sendData.dataNo = DataNo;
            sendData.size.x = Size.x;
            sendData.size.y = Size.y;
            sendData.size.z = Size.z;
            sendData.scale.x = Scale.x;
            sendData.scale.y = Scale.y;
            sendData.scale.z = Scale.z;

            dprintf("MStackImage::procedure sendData\n");
            dprintf("MStackImage::procedure ptr = %p\n", sendData.ptr);
            dprintf("MStackImage::procedure size.(x, y, z) = (%d, %d, %d)\n",
                    sendData.size.x, sendData.size.y, sendData.size.z);
            dprintf("MStackImage::procedure scale.(x, y, z) = (%f, %f, %f)\n",
                    sendData.scale.x, sendData.scale.y, sendData.scale.z);
            dprintf("MStackImage::procedure sizeof(sendData) = %d\n",
                    sizeof(sendData));

            putData(COMID_STACKIMAGE_POINTER,
                    (char *)&sendData, sizeof(sendData));

            return;
        } // COMID_REQUEST_STACKIMAGE_POINTER

        case COMID_GENERATE_STACKIMAGE: {
            DATAFORMAT_GENERATE_STACKIMAGE *recvData
                = (DATAFORMAT_GENERATE_STACKIMAGE *)data;

            if (recvData->dataNo != DataNo) {
                return;
            }
            dprintf("MStackImage::procedure " \
                    "got GENERATE_STACKIMAGE\n");
            dprintf("MStackImage::procedure ID:%d, dataNo:%d\n",
                    ID, recvData->dataNo);
            dprintf("MStackImage::procedure type:%d\n",
                    recvData->type);
            int ret = generateData(recvData->type, recvData->params);
            if (ret < 0) {
                dprintf("MStackImage::procedure generating stack image failed\n");
                return;
            }

            dprintf("MStackImage::procedure stack image generated\n");

            // unsigned int length = Size.x * Size.y * Size.z;
            // unsigned int count = 0;
            // for (unsigned int i = 0; i < length; i++) {
            //     count += !!DataArray[i];
            // }
            // dprintf("MStackImage::procedure count = %u\n", count);


            DATAFORMAT_LOAD_STACKIMAGE_OK sendData;
            sendData.ptr = DataArray;
            sendData.dataNo = recvData->dataNo;
            sendData.size.x = Size.x;
            sendData.size.y = Size.y;
            sendData.size.z = Size.z;
            sendData.scale.x = Scale.x;
            sendData.scale.y = Scale.y;
            sendData.scale.z = Scale.z;

            dprintf("MStackImage::procedure sendData\n");
            dprintf("MStackImage::procedure ptr = %p\n", sendData.ptr);
            dprintf("MStackImage::procedure size.(x, y, z) = (%d, %d, %d)\n",
                    sendData.size.x, sendData.size.y, sendData.size.z);
            dprintf("MStackImage::procedure scale.(x, y, z) = (%f, %f, %f)\n",
                    sendData.scale.x, sendData.scale.y, sendData.scale.z);
            dprintf("MStackImage::procedure sizeof(sendData) = %d\n",
                    sizeof(sendData));

            putData(COMID_LOAD_STACKIMAGE_OK,
                    (char *)&sendData, sizeof(sendData));
            // DATAFORMAT_STACKIMAGE_POINTER sendData;
            // sendData.ptr = DataArray;
            // sendData.dataNo = DataNo;
            // sendData.size.x = Size.x;
            // sendData.size.y = Size.y;
            // sendData.size.z = Size.z;
            // sendData.scale.x = Scale.x;
            // sendData.scale.y = Scale.y;
            // sendData.scale.z = Scale.z;

            // dprintf("MStackImage::procedure sendData\n");
            // dprintf("MStackImage::procedure ptr = %p\n", sendData.ptr);
            // dprintf("MStackImage::procedure size.(x, y, z) = (%d, %d, %d)\n",
            //         sendData.size.x, sendData.size.y, sendData.size.z);
            // dprintf("MStackImage::procedure scale.(x, y, z) = (%f, %f, %f)\n",
            //         sendData.scale.x, sendData.scale.y, sendData.scale.z);
            // dprintf("MStackImage::procedure sizeof(sendData) = %d\n",
            //         sizeof(sendData));

            // putData(COMID_STACKIMAGE_POINTER,
            //         (char *)&sendData, sizeof(sendData));            

            return;
        }

        case COMID_REQUEST_STACKIMAGE_POINTER_FOR_HANDTRACE: {
            DATAFORMAT_REQUEST_STACKIMAGE_POINTER_FOR_HANDTRACE *recvData
                = (DATAFORMAT_REQUEST_STACKIMAGE_POINTER_FOR_HANDTRACE *)data;

            if (recvData->dataNo != DataNo) {
                return;
            }

            dprintf("MStackImage::procedure " \
                    "got REQUEST_STACKIMAGE_POINTER_FOR_HANDTRACE\n");
            dprintf("MStackImage::procedure ID:%d, dataNo:%d\n",
                    ID, recvData->dataNo);
            
            DATAFORMAT_HANDTRACE_STACKIMAGE sendData;
            sendData.ptr = DataArray;
            sendData.dataNo = DataNo;
            sendData.size.x = Size.x;
            sendData.size.y = Size.y;
            sendData.size.z = Size.z;
            sendData.scale.x = Scale.x;
            sendData.scale.y = Scale.y;
            sendData.scale.z = Scale.z;

            dprintf("MStackImage::procedure sendData\n");
            dprintf("MStackImage::procedure ptr = %p\n", sendData.ptr);
            dprintf("MStackImage::procedure size.(x, y, z) = (%d, %d, %d)\n",
                    sendData.size.x, sendData.size.y, sendData.size.z);
            dprintf("MStackImage::procedure scale.(x, y, z) = (%f, %f, %f)\n",
                    sendData.scale.x, sendData.scale.y, sendData.scale.z);
            dprintf("MStackImage::procedure sizeof(sendData) = %d\n",
                    sizeof(sendData));

            putData(COMID_HANDTRACE_STACKIMAGE,
                    (char *)&sendData, sizeof(sendData));

            return;
        } // COMID_REQUEST_STACKIMAGE_POINTER_FOR_HANDTRACE

		default:
			return;
	}
}
