
#include <stdio.h>

#include "MExtractedData.h"
#include "CObjectCommunicatorID.h"
#include "BRodriguez2009.h"
#include "BCommon.h"

MExtractedData::MExtractedData()
{
    ClusterList = NULL;
}

MExtractedData::~MExtractedData()
{
    SAFEDELETE(ClusterList);
}

void MExtractedData::procedure(int ID, char *data, int byte)
{
    switch (ID) {

        case COMID_STORE_EXTRACTEDDATA: {
            DATAFORMAT_STORE_EXTRACTEDDATA *recvData
                = (DATAFORMAT_STORE_EXTRACTEDDATA *)data;
            
            if (DataNo != recvData->dataNo) return;

            dprintf("MExtractedData::procedure " \
                    "got STORE_EXTRACTED_DATA\n");
            dprintf("MExtractedData::procedure " \
                    "dataNo = %d, ptr = %p\n",
                    recvData->dataNo, recvData->ptr);

            SAFEDELETE(ClusterList);
            dprintf("MExtractedData::procedure SAFEDELETE OK\n");
            ClusterList = new RodClusterList();
            *ClusterList = *((RodClusterList *)(recvData->ptr));

            dprintf("MExtractedData::procedure " \
                    "ClusterNum = %u\n", ClusterList->getClusterNum());

            DATAFORMAT_STORE_EXTRACTEDDATA_OK sendData;
            sendData.dataNo = recvData->dataNo;
            sendData.ptr = (CLUSTERLIST_POINTER)ClusterList;
            putData(COMID_STORE_EXTRACTEDDATA_OK,
                    (char *)&sendData, sizeof(sendData));

            dprintf("MExtractedData::procedure STORE_EXTRACTEDDATA finished\n");

            return;
        } // COMID_STORE_EXTRACTEDDATA

        case COMID_LOAD_EXTRACTEDDATA: {
            DATAFORMAT_LOAD_EXTRACTEDDATA *recvData
                = (DATAFORMAT_LOAD_EXTRACTEDDATA *)data;
            
            if (DataNo != recvData->dataNo) {
                return;
            }

            dprintf("MExtractedData::procedure " \
                    "got LOAD_EXTRACTEDDATA\n");
            dprintf("MExtractedData::procedure " \
                    "fileName = %s, " \
                    "dataNo = %d\n",
                    recvData->fileName,
                    recvData->dataNo);

            SAFEDELETE(ClusterList);
            ClusterList = new RodClusterList;
            int ret = ClusterList->load(recvData->fileName);
            if (ret < 0) {
                fprintf(stderr, "MExtractedData::procedure " \
                       "data load failed\n");
                return;
            }

            DATAFORMAT_LOAD_EXTRACTEDDATA_OK sendData;
            sendData.dataNo = DataNo;
            sendData.ptr = (CLUSTERLIST_POINTER)ClusterList;
            sendData.scale.x = ClusterList->getScalingX();
            sendData.scale.y = ClusterList->getScalingY();
            sendData.scale.z = ClusterList->getScalingZ();
            putData(COMID_LOAD_EXTRACTEDDATA_OK,
                    (char *)&sendData, sizeof(sendData));

            return;
        } // COMID_LOAD_EXTRACTEDDATA

        case COMID_SAVE_EXTRACTEDDATA: {
            DATAFORMAT_SAVE_EXTRACTEDDATA *recvData
                = (DATAFORMAT_SAVE_EXTRACTEDDATA *)data;

            if (DataNo != recvData->dataNo) {
                return;
            }

            dprintf("MExtractedData::procedure " \
                    "got SAVE_EXTRACTEDDATA\n");
            dprintf("MExtractedData::procedure " \
                    "filePath = %s, ", \
                    "fileName = %s, ", \
                    "dirName = %s, ", \
                    "dataNo = %d, " \
                    "dataFormat = %d\n",
                    recvData->filePath,
                    recvData->fileName,
                    recvData->dirName,
                    recvData->dataNo,
                    recvData->dataFormat);

            int ret;
            switch (recvData->dataFormat) 
                {
                case EXTRACTEDDATA_OUTPUTTYPE_CLUSTERLIST:
                    ret = ClusterList->print(recvData->filePath);
                    break;
                case EXTRACTEDDATA_OUTPUTTYPE_SWC:
                    ret = ClusterList->swc_print(recvData->filePath);
                    break;
                case EXTRACTEDDATA_OUTPUTTYPE_HOC:
                    ret = Rodriguez2009MakeHoc(recvData->fileName,
                                               recvData->dirName,
                                               ClusterList,
                                               "CellName");
                    break;
                default:
                    break;
            }
            if (ret < 0) {
                printf("MExtractedData::procedure " \
                       "data save failed\n");
                return;
            }

            DATAFORMAT_SAVE_EXTRACTEDDATA sendData;
            putData(COMID_SAVE_EXTRACTEDDATA,
                    (char *)&sendData, sizeof(sendData));

            return;
        } // COMID_SAVE_EXTRACTEDDATA

        case COMID_REQUEST_EXTRACTEDDATA_POINTER: {
            DATAFORMAT_REQUEST_EXTRACTEDDATA_POINTER *recvData
                = (DATAFORMAT_REQUEST_EXTRACTEDDATA_POINTER *)data;

            if (DataNo != recvData->dataNo) return;

            dprintf("MExtractedData::procedure " \
                    "got REQUEST_EXTRACTEDDATA_POINTER\n");
            dprintf("MExtractedData::procedure " \
                    "dataNo = %d\n", recvData->dataNo);

            DATAFORMAT_EXTRACTEDDATA_POINTER sendData;
            sendData.ptr = (CLUSTERLIST_POINTER)ClusterList;
            sendData.dataNo = DataNo;

            putData(COMID_EXTRACTEDDATA_POINTER,
                    (char *)&sendData, sizeof(sendData));

            return;
        } // COMID_REQUEST_EXTRACTEDDATA_POINTER

        default:
            return;
    }
}
