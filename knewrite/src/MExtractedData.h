#ifndef ___M_EXTRACTED_DATA_H___
#define ___M_EXTRACTED_DATA_H___

#include "CObjectCommunicator.h"
#include "BRodriguez2009Cluster.h"

class MExtractedData : public BTerminal {
 public:
    MExtractedData();
    ~MExtractedData();

    void setDataNo(int no) { DataNo = no; }
    int getDataNo(void) { return DataNo; }

 protected:
    void procedure(int ID, char *data, int byte);

 protected:
    int DataNo;
    RodClusterList *ClusterList;

};

#endif//___M_EXTRACTED_DATA_H___
