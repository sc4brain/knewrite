
#include <QtGui>
#include <stdio.h>
#include <math.h>
#include "BExtraction.h"
#include "CObjectCommunicatorID.h"
#include "BCommon.h"
#include "BVoxelProcesses.h"

int scanResult(VoxelClass *voxelData, RodClusterList *clusterList,
               unsigned char threshold,
               unsigned char *outLabeledVoxelData);

BExtraction::BExtraction()
{
    VoxelData = NULL;
    stopped = false;
}

void BExtraction::extract(int iThresholdStart,
                             int iThresholdStop,
                             const char *outputFileName)
{
    int ret;

    if (VoxelData == NULL) {
        printf("BExtraction::extraction VoxelData has not been set\n");
        DATAFORMAT_FAILED_EXTRACTION sendData;
        sprintf(sendData.msg, "invalid VoxelData");
        putData(COMID_FAILED_EXTRACTION, (char *)&sendData, sizeof(sendData));
        return;
    }

    // dprint VoxelData properties
    dprintf("BExtraction::extraction VoxelData size (%d, %d, %d)\n",
            VoxelData->getX(), VoxelData->getY(), VoxelData->getZ());
    dprintf("BExtraction::extarciton start (%f, %f, %f)\n",
            StartPoint.x, StartPoint.y, StartPoint.z);
    dprintf("BExtraction::extarciton threshold = %d\n", Threshold);

    // start Extraction
    QTime extractionTime;
    extractionTime.start();

    // Hemming
    ret = vpHemming(VoxelData);
    if (ret < 0) {
        printf("BExtraction::extraction Hemming failed\n");
        DATAFORMAT_FAILED_EXTRACTION sendData;
        sprintf(sendData.msg, "hemming failed");
        putData(COMID_FAILED_EXTRACTION, (char *)&sendData, sizeof(sendData));
        return;
    }
    dprintf("BExtraction::extarciton Hemming OK\n");

    RodClusterList **clusterList = new RodClusterList*[256];

    int startThreshold;
    int stopThreshold;
    int finishedThreshold = 0;
    if (iThresholdStart == -1) {
        startThreshold = Threshold;
    } else {
        startThreshold = iThresholdStart;
    }
    if (iThresholdStop == -1) {
        stopThreshold = Threshold;
    } else {
        stopThreshold = iThresholdStop;
    }

    for (int i = startThreshold; i <= stopThreshold; i++) {
        
        // check stop operation
        mutex.lock();
        if (stopped) {
            stopped = false;
            mutex.unlock();
            DATAFORMAT_CANCELED_EXTRACTION sendData;
            putData(COMID_CANCELED_EXTRACTION,
                    (char *)&sendData, sizeof(sendData));
            break;
        }
        mutex.unlock();
        VoxelClass *voxelDataBin = new VoxelClass(VoxelData->getX(),
                                                  VoxelData->getY(),
                                                  VoxelData->getZ());
        *voxelDataBin = *VoxelData;

        clusterList[i] = new RodClusterList();

        // Binarization
        ret = vpGray2Binary(VoxelData, voxelDataBin, i);
        dprintf("BExtraction::extarciton Binaly Threshold = %d\n", i);
        if (ret < 0) {
            printf("BExtraction::extraction Binalize failed\n");
            DATAFORMAT_FAILED_EXTRACTION sendData;
            sprintf(sendData.msg, "binalize failed");
            putData(COMID_FAILED_EXTRACTION,
                    (char *)&sendData, sizeof(sendData));
            return;
        }


        // Extraction
        ret = Rodriguez2009ExtractionMethod(voxelDataBin,
                                            StartPoint,
                                            clusterList[i],
                                            &stopped,
                                            &mutex);

        SAFEDELETE(voxelDataBin);

        if (ret < 0) {
            printf("BExtraction::extraction " \
                   "extraction failed with code : %d\n",
                   ret);
            SAFEDELETE(clusterList[i]);
            break;
        }

        ret = Rodriguez2009Smoothing(clusterList[i]);

        if (ret < 0) {
            printf("BExtraction::extraction " \
                   "smoothing failed with code : %d\n",
                   ret);
            break;
        }

        finishedThreshold = i;
    }

    // calc & output extraction properties
    if (finishedThreshold != 0) {

        // when CalcProp == false
        // store extracted data
        if (!CalcProp) {
            clusterList[Threshold]->setScaling(Scale.x, Scale.y, Scale.z);

            unsigned char *voxelDataLabeled = new unsigned char[VoxelData->getX()
                                                                * VoxelData->getY()
                                                                * VoxelData->getZ()];

            DATAFORMAT_FINISHED_EXTRACTION sendData;
            sendData.ptr = (CLUSTERLIST_POINTER)(clusterList[Threshold]);
            sendData.dataNo = DataNo;
            sendData.targetNo = TargetNo;
            sendData.scale.x = Scale.x;
            sendData.scale.y = Scale.y;
            sendData.scale.z = Scale.z;
            // sendData.scan = scan;

            if (scan) {
                dprintf("BExtraction::extarciton scanning start\n");
                scanResult(VoxelData, clusterList[Threshold],
                           Threshold, voxelDataLabeled);
                // sendData.labeledDataPtr = voxelDataLabeled;
                // sendData.scanDataNoToStore = scanDataNoToStore;
                // sendData.size.x = voxelData->getX();
                // sendData.size.y = voxelData->getY();
                // sendData.size.z = voxelData->getZ();
            } else {
                // sendData.labeledDataPtr = NULL;
                // sendData.scanDataNoToStore = -1;
                // sendData.size.x = 0;
                // sendData.size.y = 0;
                // sendData.size.z = 0;
            }
            putData(COMID_FINISHED_EXTRACTION,
                    (char *)&sendData, sizeof(sendData));
            dprintf("BExtraction::extarciton Extraction OK\n");
            dprintf("BExtraction::extraction clusterList = %p\n",
                    clusterList[Threshold]);
            dprintf("BExtraction::extraction ClusterNum = %u\n",
                    clusterList[Threshold]->getClusterNum());

            if (scan) {
                DATAFORMAT_STORE_STACKIMAGE sendData2;
                sendData2.ptr = voxelDataLabeled;
                sendData2.dataNo = scanDataNoToStore;
                sendData2.size.x = VoxelData->getX();
                sendData2.size.y = VoxelData->getY();
                sendData2.size.z = VoxelData->getZ();
                sendData2.scale.x = Scale.x;
                sendData2.scale.y = Scale.y;
                sendData2.scale.z = Scale.z;
                putData(COMID_STORE_STACKIMAGE,
                        (char *)&sendData2, sizeof(sendData2));
            }

            ASAFEDELETE(voxelDataLabeled);
        }
        // if CalcProp == true
        // output prop. data
        else {
            FILE *fp;
            fp = fopen(outputFileName, "w");
            if (fp == NULL) {
                fprintf(stderr, "BExtraction::extraction file open error : %s\n",
                       "ExtractProp.dat");
                DATAFORMAT_FAILED_EXTRACTION sendData;
                sprintf(sendData.msg,
                        "file open error : %s",
                        "ExtractProp.dat");
                putData(COMID_FAILED_EXTRACTION,
                        (char *)&sendData, sizeof(sendData));
                return;
            }
            fprintf(fp, "%s %s %s %s %s %s %s %s %s\n",
                    "THRESHOLD",
                    "CLUSTER#",
                    "VOXEL#",
                    "MAXDIST",
                    "TOTALLENGTH",
                    "AVRDIAM",
                    "DIAMVARIANCE",
                    "AVRVOXELNUM",
                    "VOXELNUMVARIANCE");

            double scalex = VoxelData->getScaleX();
            double scaley = VoxelData->getScaleY();
            double scalez = VoxelData->getScaleZ();
            for (int i = startThreshold; i <= finishedThreshold; i++) {
                unsigned int clusterNum = clusterList[i]->getClusterNum();
                unsigned int voxelNum = 0;
                double avrDiam = 0.;
                unsigned int maxDist
                    = clusterList[i]->getCluster(clusterNum-1)->getDistance();
                double totalLength = 0.;
                for (unsigned int j = 0; j < clusterNum; j++) {
                    RodCluster *curCluster = clusterList[i]->getCluster(j);
                    voxelNum += curCluster->getVoxelNum();
                    avrDiam += curCluster->getDiam();
                    POINT3D curPoint = curCluster->getNode();
                    for (int k = 0; k < curCluster->getChildNum(); k++) {
                        RodCluster *childCluster = curCluster->getChild(k);
                        POINT3D childPoint = childCluster->getNode();
                        double dx = (curPoint.x - childPoint.x) * scalex;
                        double dy = (curPoint.y - childPoint.y) * scaley;
                        double dz = (curPoint.z - childPoint.z) * scalez;
                        totalLength += sqrt(dx * dx + dy * dy + dz * dz);
                    }
                }
                avrDiam /= clusterNum;
                double avrVoxelNum = voxelNum / (double)clusterNum;
                double diamVariance = 0.;
                double voxelNumVariance = 0.;
                for (unsigned int j = 0; j < clusterNum; j++) {
                    RodCluster *curCluster = clusterList[i]->getCluster(j);
                    double dDiam = curCluster->getDiam() - avrDiam;
                    diamVariance += dDiam * dDiam;
                    double dVoxelNum
                        = curCluster->getVoxelNum() - avrVoxelNum;
                    voxelNumVariance += dVoxelNum * dVoxelNum;
                }
                diamVariance /= clusterNum - 1;
                voxelNumVariance /= clusterNum - 1;
                fprintf(fp, "%u %u %d %d %f %f %f %f %f\n",
                        i,
                        clusterNum,
                        voxelNum,
                        maxDist,
                        totalLength,
                        avrDiam,
                        diamVariance,
                        avrVoxelNum,
                        voxelNumVariance
                        );
            }
            fclose(fp);
            int returnNo = StartThreshold / 2 + finishedThreshold / 2;
            clusterList[returnNo]->setScaling(Scale.x, Scale.y, Scale.z);

            DATAFORMAT_FINISHED_EXTRACTION sendData;
            sendData.ptr
                = (CLUSTERLIST_POINTER)(clusterList[returnNo]);
            sendData.dataNo = DataNo;
            sendData.targetNo = TargetNo;
            sendData.scale.x = Scale.x;
            sendData.scale.y = Scale.y;
            sendData.scale.z = Scale.z;

            putData(COMID_FINISHED_EXTRACTION,
                    (char *)&sendData, sizeof(sendData));
            dprintf("BExtraction::extraction clusterList = %p\n",
                    clusterList[returnNo]);
            dprintf("BExtraction::extraction Threshold = %u\n",
                    returnNo);
            dprintf("BExtraction::extraction ClusterNum = %u\n",
                    clusterList[returnNo]->getClusterNum());
            dprintf("BExtraction::extraction property calclation finished\n");
            dprintf("BExtraction::extarction results have been saved :%s\n",
                    FileNameExtractionProperties);
        }
    } else {
        DATAFORMAT_FAILED_EXTRACTION sendData;
        sprintf(sendData.msg, "extraction error");
        putData(COMID_FAILED_EXTRACTION,
                (char *)&sendData, sizeof(sendData));
    }

    for (int i = startThreshold; i <= finishedThreshold; i++) {
        SAFEDELETE(clusterList[i]);
    }
    ASAFEDELETE(clusterList);


    // calc and output calculation time
    int elapsed = extractionTime.elapsed();

    QFile file("TimerResultAuto.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream out(&file);
    out << elapsed/3600000. << " (h)\n";
    out << elapsed/60000. << " (m)\n";
    out << elapsed/1000. << " (s)\n";
    out << elapsed << " (ms)\n";

    int ms = elapsed % 1000;
    elapsed /= 1000;
    int s = elapsed % 60;
    elapsed /= 60;
    int m = elapsed % 60;
    elapsed /= 60;
    int h = elapsed;

    out << "\nh:m:s:ms\n";
    out << h << ":" << m << ":" << s << ":" << ms << "\n\n";

    return;
}

int scanResult(VoxelClass *voxelData, RodClusterList *clusterList,
               unsigned char threshold,
               unsigned char *outLabeledVoxelData)
{
    if (voxelData == NULL) return -1;
    if (clusterList == NULL) return -2;
    if (outLabeledVoxelData == NULL) return -3;

    // if (voxelData->getX() != outLabeledVoxelData->getX()
    //     || voxelData->getY() != outLabeledVoxelData->getY()
    //     || voxelData->getZ() != outLabeledVoxelData->getZ()
    //     ) {
    //     return -4;
    // }

    int sizex = voxelData->getX();
    int sizey = voxelData->getY();
    int sizez = voxelData->getZ();    
    VoxelClass *voxelDataBin = new VoxelClass(sizex, sizey, sizez);
    *voxelDataBin = *voxelData;
    // Binarization
    int ret = vpGray2Binary(voxelData, voxelDataBin, threshold);
    dprintf("scanResult Binaly Threshold = %d\n", threshold);
    if (ret < 0) {
        fprintf(stderr, "scanResult Binalize failed\n");
        return ret;
    }

    VoxelClass *voxelDataExtracted = new VoxelClass(sizex, sizey, sizez);
    for (unsigned int i = 0; i < clusterList->getClusterNum(); i++) {
        RodCluster *curCluster = clusterList->getCluster(i);
        Rodriguez2009VoxelList *curVoxelList = curCluster->getRodriguez2009VoxelList();
        for (unsigned int j = 0; j < curVoxelList->getPointNum(); j++) {
            POINT3D curPoint = curVoxelList->getPoint(j);
            voxelDataExtracted->setData(curPoint.x, curPoint.y, curPoint.z, 255);
        }
    }

    int pageSize = sizex * sizey;
    for (unsigned int i = 0; i < clusterList->getClusterNum(); i++) {
        RodCluster *curCluster = clusterList->getCluster(i);
        POINT3D curNode = curCluster->getNode();
        int scanRange = (ceil(curCluster->getDiam()) * 3 ) / 2;
        int xFrom = curNode.x - scanRange; if (xFrom < 0) xFrom = 0;
        int xTo = curNode.x + scanRange;   if (sizex < xTo) xTo = sizex;
        int yFrom = curNode.y - scanRange; if (yFrom < 0) yFrom = 0;
        int yTo = curNode.y + scanRange;   if (sizey < yTo) yTo = sizey;
        int zFrom = curNode.z - scanRange; if (zFrom < 0) zFrom = 0;
        int zTo = curNode.z + scanRange;   if (sizez < zTo) zTo = sizez;
        // dprintf("[%d] scanResult (%d, %d, %d) - (%d, %d, %d)\n",
        //         i, xFrom, xTo, yFrom, yTo, zFrom, zTo);
        
        for (int z = zFrom; z < zTo; z++) {
            int pageStep = pageSize * z;
            for (int y = yFrom; y < yTo; y++) {
                int overHead = pageStep + sizex * y;
                for (int x = xFrom; x < xTo; x++) {
                    int sfx = overHead + x;
                    unsigned char value
                        = voxelDataExtracted->getData(sfx)
                        || !voxelDataBin->getData(sfx);
                    outLabeledVoxelData[sfx] =  !value * 255;
                }
            }
        }
    }

    SAFEDELETE(voxelDataExtracted);
    SAFEDELETE(voxelDataBin);
}

void BExtraction::procedure(int ID, char *data, int byte)
{
    switch (ID) {
        case COMID_DO_EXTRACTION: {
            DATAFORMAT_DO_EXTRACTION *recvData
                = (DATAFORMAT_DO_EXTRACTION *)data;
            
            dprintf("BExtraction::procedure " \
                    "got DO_EXTRACTION");
            dprintf("BExtraction::procedure " \
                    "ptr = %p, dataNo = %d, targetNo = %d\n",
                    recvData->ptr, recvData->dataNo, recvData->targetNo);
            dprintf("BExtraction::procedure " \
                    "size (%d, %d, %d)\n",
                    recvData->size.x,
                    recvData->size.y,
                    recvData->size.z);
            dprintf("BExtraction::procedure " \
                    "scale (%f, %f, %f)\n",
                    recvData->scale.x,
                    recvData->scale.y,
                    recvData->scale.z);
            dprintf("BExtraction::procedure " \
                    "startPoint (%d, %d, %d)\n",
                    recvData->startPoint.x,
                    recvData->startPoint.y,
                    recvData->startPoint.z);
            dprintf("BExtraction::procedure " \
                    "ROI (%d-%d, %d-%d, %d-%d)\n",
                    recvData->ROI.x.from, recvData->ROI.x.to,
                    recvData->ROI.y.from, recvData->ROI.y.to,
                    recvData->ROI.z.from, recvData->ROI.z.to);
            dprintf("BExtraction::procedure " \
                    "threshold = %d\n", recvData->threshold);
            dprintf("BExtraction::procedure " \
                    "calcProp = %s\n", recvData->calcProp ? "ON" : "OFF");
            if (recvData->calcProp) {
                dprintf("BExtraction::procedure " \
                        "fname = %s\n", recvData->fname);
            }

            StartPoint.x = recvData->startPoint.x;
            StartPoint.y = recvData->startPoint.y;
            StartPoint.z = recvData->startPoint.z;

            Threshold = recvData->threshold;
            CalcProp = recvData->calcProp;
            if (CalcProp) {
                strncpy(FileNameExtractionProperties, recvData->fname, 2047);
                StartThreshold = recvData->startThreshold;
                StopThreshold = recvData->stopThreshold;
            }

            DataNo = recvData->dataNo;
            TargetNo = recvData->targetNo;

            Scale.x = recvData->scale.x;
            Scale.y = recvData->scale.y;
            Scale.z = recvData->scale.z;

            scan = recvData->scan;
            scanDataNoToStore = recvData->scanDataNoToStore;

            SAFEDELETE(VoxelData);
            VoxelData = new VoxelClass(recvData->size.x,
                                       recvData->size.y,
                                       recvData->size.z);

            // int sizex = recvData->size.x;
            // int sizey = recvData->size.y;
            // int sizez = recvData->size.z;

            VoxelData->setScaleX(recvData->scale.x);
            VoxelData->setScaleY(recvData->scale.y);
            VoxelData->setScaleZ(recvData->scale.z);

            /*
            int dataSize = recvData->size.x
                * recvData->size.y
                * recvData->size.z;
            for (int i = 0; i < dataSize; i++) {
                VoxelData->setData(i, recvData->ptr[i]);
            }
            */

            struct {
                RANGE_INT x;
                RANGE_INT y;
                RANGE_INT z;
            } ROI = {
                {
                    recvData->ROI.x.from,
                    recvData->ROI.x.to
                },
                {
                    recvData->ROI.y.from,
                    recvData->ROI.y.to
                },
                {
                    recvData->ROI.z.from,
                    recvData->ROI.z.to
                }
            };
            for (int k = ROI.z.from; k < ROI.z.to; k++) {
                int pageStep = recvData->size.x * recvData->size.y * k;
                for (int j = ROI.y.from; j < ROI.y.to; j++) {
                    int step = pageStep + recvData->size.x * j;
                    for (int i = ROI.x.from; i < ROI.x.to; i++) {
                        VoxelData->setData(step + i, recvData->ptr[step + i]);
                    }
                }
            }

            stopped = false;
            this->start();

            return;
        } // COMID_DO_EXTRACTION

        case COMID_CANCEL_EXTRACTION: {
            DATAFORMAT_CANCEL_EXTRACTION *recvData
                = (DATAFORMAT_CANCEL_EXTRACTION *)data;
            
            dprintf("CExtractedDataController::procedure " \
                    "got CANCEL_EXTRACTION\n");

            this->stop();
            
            return;
        } // COMID_CANCEL_EXTRACTION
    }
}

void BExtraction::stop()
{
    mutex.lock();
    stopped = true;
    mutex.unlock();
}

void BExtraction::run()
{
    if (CalcProp) {
        extract(StartThreshold, StopThreshold, FileNameExtractionProperties);
    } else {
        extract();
    }
}
