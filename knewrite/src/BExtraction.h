#ifndef ___B_EXTRACTION_H___
#define ___B_EXTRACTION_H___

#include <QThread>
#include <QMutex>

#include "CObjectCommunicator.h"
#include "BRodriguez2009.h"

class BExtraction : public BTerminal, public QThread
{
 public:
    BExtraction();

 protected:

    void extract(int iThresholdStart = -1,
                 int iThresholdFinish = -1,
                 const char * outputFileName = NULL);

    //void scanResult(RodClusterList *clusterList);

    void procedure(int ID, char *data, int byte);

    void stop();
    void run();

    QMutex mutex;
    volatile bool stopped;

 protected:
    VoxelClass *VoxelData;
    POINT3D StartPoint;
    unsigned char Threshold;
    int DataNo;
    int TargetNo;
    struct {
        double x;
        double y;
        double z;
    } Scale;

    bool CalcProp;
    char FileNameExtractionProperties[2048];
    unsigned char StartThreshold;
    unsigned char StopThreshold;

    bool scan;
    int scanDataNoToStore;
};


#endif//___B_EXTRACTION_H___
