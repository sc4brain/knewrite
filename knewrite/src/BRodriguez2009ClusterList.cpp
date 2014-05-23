//#define ___DEBUG___
//#define ___DEBUG20100817___
//#define ___DEBUG20100819___

#include <stdio.h>
#include <new>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "BCommon.h"
#include "BRodriguez2009Cluster.h"

using namespace std;

#ifndef NULL
#define NULL (void *)0
#endif

Rodriguez2009ClusterList::Rodriguez2009ClusterList()
{
    m_Clusters = NULL;
    m_uClusterNum = 0;
    m_Scaling.x = m_Scaling.y = m_Scaling.z = 1.;
}

Rodriguez2009ClusterList::~Rodriguez2009ClusterList()
{
    // dprintf("Rodriguez2009ClusterList " \
    //         "delete m_Clusters = %p\n", m_Clusters);
    // if (m_Clusters != NULL) {
    //     dprintf("Rodriguez2009ClusterList " \
    //             "delete m_Clusters[0] = %p\n",
    //             m_Clusters[0]);
    // }
#ifdef RODRIGUEZ2009_CLUSTERS_POINTER_ARRAY
    //dprintf("  deleting\n");
    for (unsigned int i = 0; i < m_uClusterNum; i++) {
        //dprintf("  %05d  ", i);
        SAFEDELETE(m_Clusters[i]);
        //dprintf("\r");
    }
    //dprintf("\n");
#endif
	ASAFEDELETE(m_Clusters);
    m_uClusterNum = 0;
}

Rodriguez2009ClusterList::Rodriguez2009ClusterList(Rodriguez2009ClusterList &orig)
{
#ifdef RODRIGUEZ2009_CLUSTERS_POINTER_ARRAY
    for (unsigned int i = 0; i < m_uClusterNum; i++) {
        SAFEDELETE(m_Clusters[i]);
    }

    ASAFEDELETE(m_Clusters);
    m_uClusterNum = orig.getClusterNum();

    m_Clusters = new RodCluster*[m_uClusterNum];
    for (unsigned int i = 0; i < m_uClusterNum; i++) {
        m_Clusters[i] = new RodCluster();
        *m_Clusters[i] = *orig.getCluster(i);
    }
    m_Scaling = orig.getScaling();
#else
	ASAFEDELETE(m_Clusters);
	m_uClusterNum = orig.getClusterNum();
	
	m_Clusters = new RodCluster[m_uClusterNum];
	for (unsigned int i = 0; i < m_uClusterNum; i++) {
		m_Clusters[i] = *orig.getCluster(i);
	}
	m_Scaling = orig.getScaling();
#endif

}

Rodriguez2009ClusterList
&Rodriguez2009ClusterList::operator =(Rodriguez2009ClusterList &orig)
{
#ifdef RODRIGUEZ2009_CLUSTERS_POINTER_ARRAY
    for (unsigned int i = 0; i < m_uClusterNum; i++) {
        SAFEDELETE(m_Clusters[i]);
    }
    ASAFEDELETE(m_Clusters);
    m_uClusterNum = orig.getClusterNum();

    m_Clusters = new RodCluster*[m_uClusterNum];

    // copy all clusters
    for (unsigned int i = 0; i < m_uClusterNum; i++) {
        // dprintf("Rodriguez2009ClusterList::operator = " \
        //         "copying %u/%u : ", i, m_uClusterNum-1);
        m_Clusters[i] = new RodCluster();

        // !!cannot use assignment operation
        // because of pointer list of parents/children
        // m_Parents/m_Children

        // *m_Clusters[i] = *orig.getCluster(i);
        RodCluster *curCluster = m_Clusters[i];
        RodCluster *origCluster = orig.getCluster(i);
        curCluster->setDiam(origCluster->getDiam());
        curCluster->setDistance(origCluster->getDistance());
        curCluster->setClusterNo(origCluster->getClusterNo());
        // dprintf("ClusterNo=%d ", origCluster->getClusterNo());
        curCluster->setRodriguez2009VoxelList(
            origCluster->getRodriguez2009VoxelList());
        // dprintf("VoxelCopyOK ");
        int parentNum = origCluster->getParentNum();
        // dprintf("parentNum=%d ", parentNum);
        curCluster->setParentNum(parentNum);
        if (parentNum != 0) {
            unsigned int parentClusterNo
                = origCluster->getParent(0)->getClusterNo();
            // dprintf("parentClusterNo = %u ", parentClusterNo);
            RodCluster *parentCluster = m_Clusters[parentClusterNo];
            curCluster->setParent(0, parentCluster);
            parentCluster->addChild(curCluster);
        }
        curCluster->setChildNum(0);
        curCluster->setCenterNo(origCluster->getCenterNo());;
        curCluster->setNode(origCluster->getNode());
        curCluster->setNodeNo(origCluster->getNodeNo());
        curCluster->setScoopingDistance(origCluster->getScoopingDistance());
        // dprintf("\n");
    }
    
    m_Scaling = orig.getScaling();

#else
	ASAFEDELETE(m_Clusters);
	m_uClusterNum = orig.getClusterNum();
	
	m_Clusters = new RodCluster[m_uClusterNum];
	for (unsigned int i = 0; i < m_uClusterNum; i++) {
		m_Clusters[i] = *orig.getCluster(i);
	}
	m_Scaling = orig.getScaling();
#endif
    
    return *this;
}

RodCluster* Rodriguez2009ClusterList::getCluster(unsigned int in_No)
{
	if (in_No >= m_uClusterNum) { return NULL; }
#ifdef RODRIGUEZ2009_CLUSTERS_POINTER_ARRAY
    return m_Clusters[in_No];
#else
	return m_Clusters + in_No;
#endif
}

unsigned int Rodriguez2009ClusterList::addCluster(RodCluster *in_Cluster)
{

#ifdef RODRIGUEZ2009_CLUSTERS_POINTER_ARRAY
    RodCluster **tempCluster = NULL;

    if (m_uClusterNum > 0) {
        try {
            tempCluster = new RodCluster*[m_uClusterNum];
        } catch(bad_alloc& ba) {
            fprintf(stderr,
                    "Rodriguez2009ClusterList::addCluster() bad_alloc\n");
            return -1;
        }
    }

    for (unsigned int i = 0; i < m_uClusterNum; i++) {
        tempCluster[i] = m_Clusters[i];
    }

    ASAFEDELETE(m_Clusters);
    m_Clusters = new RodCluster*[m_uClusterNum+1];

    for (unsigned int i = 0; i < m_uClusterNum; i++) {
        m_Clusters[i] = tempCluster[i];
    }
    m_Clusters[m_uClusterNum] = in_Cluster;

    m_uClusterNum++;

	ASAFEDELETE(tempCluster);
#else

	RodCluster *tempCluster = NULL;

	if (m_uClusterNum > 0) {
		try {
			tempCluster = new RodCluster[m_uClusterNum];
		} catch (bad_alloc& ba) {
			fprintf(stderr,
                    "Rodriguez2009ClusterList::addCluster() bad_alloc\n");
			exit(1);
		}
	}

	for (unsigned int i = 0; i < m_uClusterNum; i++) {
		tempCluster[i] = m_Clusters[i];
	}
	ASAFEDELETE(m_Clusters);
	m_Clusters = new RodCluster[m_uClusterNum+1];
	
	for (unsigned int i = 0; i < m_uClusterNum; i++) {
		m_Clusters[i] = tempCluster[i];
	}
	m_Clusters[m_uClusterNum] = *in_Cluster;
	SAFEDELETE(in_Cluster);
	m_uClusterNum++;

	ASAFEDELETE(tempCluster);

#endif

    return 0;
}

unsigned int Rodriguez2009ClusterList::clearCluster(void)
{
#ifdef RODRIGUEZ2009_CLUSTERS_POINTER_ARRAY
    if (m_Clusters != NULL) {
        for (unsigned int i = 0; i < m_uClusterNum; i++) {
			SAFEDELETE(m_Clusters[i]);
        }
        ASAFEDELETE(m_Clusters);
        m_uClusterNum = 0;
    }
#else
	if (m_Clusters != NULL) {
		ASAFEDELETE(m_Clusters);
		m_uClusterNum = 0;
	}
#endif
    return 0;
}

int Rodriguez2009ClusterList::assembleClusters(void)
{	
	if (m_uClusterNum == 0) {
		return 0;
	}
	RodCluster *tempClusters;

	try {
		tempClusters = new RodCluster[m_uClusterNum];
	} catch (bad_alloc& ba) {
		fprintf(stderr,
                "Rodriguez2009ClusterList::assembleClusters() bad_alloc\n");
		exit(1);
	}
	for (unsigned int i = 0; i < m_uClusterNum; i++) {
		tempClusters[i] = *CLST2P(m_Clusters[i]);
	}

	CLST2P(m_Clusters[0])->setParentNum(0);

	int **ParentNoList;
	ParentNoList = new int*[m_uClusterNum];
	for (unsigned int i = 0; i < m_uClusterNum; i++) {
		ParentNoList[i] = new int[ADJACENT_CLUSTER_NUM];
		unsigned int parentNum = CLST2P(m_Clusters[i])->getParentNum();
		for (unsigned int j = 0; j < parentNum; j++) {
			ParentNoList[i][j]
                = (int)CLST2P(m_Clusters[i])->getParent(j)->getClusterNo();
		}
		for (unsigned int j = parentNum; j < ADJACENT_CLUSTER_NUM; j++) {
			ParentNoList[i][j] = -1;
		}
	}

	ASAFEDELETE(m_Clusters);

#ifdef RODRIGUEZ2009_CLUSTERS_POINTER_ARRAY
	m_Clusters = new RodCluster*[m_uClusterNum];
	for (unsigned int i = 0; i < m_uClusterNum; i++) {
		m_Clusters[i] = new RodCluster();
		*m_Clusters[i] = tempClusters[i];
	}
#else
	m_Clusters = new RodCluster[m_uClusterNum];
	for (unsigned int i = 0; i < m_uClusterNum; i++) {
		m_Clusters[i] = tempClusters[i];
	}
#endif

	CLST2P(m_Clusters[0])->setParentNum(0);

	// set connections
	for (unsigned int i = 0; i < m_uClusterNum; i++) {
		RodCluster *CurCluster = CLST2P(m_Clusters[i]);
		CurCluster->setChildNum(0);
		CurCluster->setParentNum(0);
		for (unsigned int j = 0; j < ADJACENT_CLUSTER_NUM; j++) {
			int curParentNo = ParentNoList[i][j];
			if (curParentNo < 0) break;
			RodCluster *CurParent = CLST2P(m_Clusters[curParentNo]);
            CurCluster->addParent(CurParent);
            // add child & count up the # of child
			CurParent->addChild(CurCluster);
            
		}
	}

	for (unsigned int i = 0; i < m_uClusterNum; i++) {
		SAFEDELETE(ParentNoList[i]);
	}
	ASAFEDELETE(ParentNoList);

	ASAFEDELETE(tempClusters);

	return 0;
}

void Rodriguez2009ClusterList::nullClear(void)
{
    //dprintf("Rodriguez2009ClusterList::nullClear\n");
    for (unsigned int i = 0; i < m_uClusterNum; i++) {
        m_Clusters[i] = NULL;
    }
 
    //dprintf("Rodriguez2009ClusterList::nullClear ASAFEDELETE\n");
    ASAFEDELETE(m_Clusters);
    m_uClusterNum = 0;
    //clearCluster();
}

int Rodriguez2009ClusterList::print(char *fname)
{
    FILE *fp_write;
    fp_write = fopen(fname, "w");
    if (fp_write == NULL) {
        fprintf(stderr, "Rodriguez2009ClusterList::print() fopen err\n");
        return -1;
    }

    for (unsigned int i = 0; i < m_uClusterNum; i++) {
        CLST2P(m_Clusters[i]->setNodeNo(m_Clusters[i]->getClusterNo()+1));
    }

	printf("Cluster print: ClusterNum = %u : %d\n", m_uClusterNum);

    fprintf(fp_write, "CLUSTER_NUM:\t%d\n", m_uClusterNum);
    fprintf(fp_write, "SCALING:\t(%f, %f, %f)\n",
            m_Scaling.x, m_Scaling.y, m_Scaling.z);
    for (unsigned int i = 0; i < m_uClusterNum; i++) {

		fprintf(fp_write,"-------------------------------------------------------------------\n");

		fprintf(fp_write, "\t%04d (%u)\n", CLST2P(m_Clusters[i])->getNodeNo(), CLST2P(m_Clusters[i])->getClusterNo());
		fprintf(fp_write, "\t\tDISTANCE:\t%u\n", CLST2P(m_Clusters[i])->getDistance());

		fprintf(fp_write, "\t\tCHILD_NUM:\t%u\n", CLST2P(m_Clusters[i])->getChildNum());
		for (unsigned int j = 0; j < CLST2P(m_Clusters[i])->getChildNum(); j++) {
			//fprintf(fp_write, "\t\t\t%u\n", CLST2P(m_Clusters[i])->getChild(j)->getClusterNo());
			fprintf(fp_write, "\t\t\t%u (%u)\n",
					CLST2P(m_Clusters[i])->getChild(j)->getNodeNo(),
					CLST2P(m_Clusters[i])->getChild(j)->getClusterNo());
		}

		if (i != 0) {
			fprintf(fp_write, "\t\tPARENT_NUM:\t%u\n",
					CLST2P(m_Clusters[i])->getParentNum());
		} else {
			fprintf(fp_write, "\t\tPARENT_NUM:\t%u\n", 0);
		}

		if (i != 0) {
			for (unsigned int j = 0; j < CLST2P(m_Clusters[i])->getParentNum(); j++) {
				fprintf(fp_write, "\t\t\t%u (%u)\n",
						CLST2P(m_Clusters[i])->getParent(j)->getNodeNo(),
						CLST2P(m_Clusters[i])->getParent(j)->getClusterNo());
			}
		}

		fprintf(fp_write, "\t\tNODE_NO:\t%u\n", CLST2P(m_Clusters[i])->getNodeNo());
		fprintf(fp_write, "\t\tSCOOPING_DISTANCE:\t%f\n", CLST2P(m_Clusters[i])->getScoopingDistance());

		POINT3D CurNode = CLST2P(m_Clusters[i])->getNode();
		fprintf(fp_write, "\t\tNODE:\t( %f, %f, %f)\n", CurNode.x, CurNode.y, CurNode.z);
		fprintf(fp_write, "\t\tDIAM:\t %f\n", CLST2P(m_Clusters[i])->getDiam());

#ifdef ___BRODRIGUEZ2009CLUSTERLIST_DEBUG___
		FILE *fp = fopen("error_log.txt", "a");
		fprintf(fp, "%u\n", i);
		fclose(fp);
#endif
		POINT3D MedianPoint = CLST2P(m_Clusters[i])->getCenter();
		fprintf(fp_write, "\t\tMEDIAN_POINT:\t( %f, %f, %f)\n", MedianPoint.x, MedianPoint.y, MedianPoint.z);

		fprintf(fp_write, "\t\tMEMBER_NUM:\t%u\n", CLST2P(m_Clusters[i])->getVoxelNum());
		fprintf(fp_write, "\t\tVOXELS:\n");
		for (unsigned int j = 0; j < CLST2P(m_Clusters[i])->getVoxelNum(); j++) {
			POINT3D	tempPoint = CLST2P(m_Clusters[i])->getVoxel(j);
			fprintf(fp_write, "\t\t\t( %f, %f, %f)\n", tempPoint.x, tempPoint.y, tempPoint.z);
		}
    }
	fflush(fp_write);
    fclose(fp_write);
    
    return 0;
    
}

int Rodriguez2009ClusterList::swc_print(char* fname)
{
    
    FILE *fp_write;
    fp_write = fopen(fname, "w");
    if (fp_write == NULL) {
        fprintf(stderr, "Rodriguez2009ClusterList::swc_print() fopen err\n");
        return -1;
    }
    
    struct tm *date;
    time_t now;
    int year, month, day;
    
    time(&now);
    date = localtime(&now);
    
    year = date->tm_year + 1900;
    month = date->tm_mon + 1;
    day = date->tm_mday;
    
    // header
    fprintf(fp_write, "#ORIGINAL_SOURCE %s\n", "IOSIM");
    fprintf(fp_write, "#CREATURE %s\n", "");
    fprintf(fp_write, "#REGION %s\n", "");
    fprintf(fp_write, "#FIELD/LAYER %s\n", "");
    fprintf(fp_write, "#TYPE %s\n", "");
    fprintf(fp_write, "#CONTRIBUTOR %s\n", "");
    fprintf(fp_write, "#REFERENCE %s\n", "");
    fprintf(fp_write, "#RAW %s\n", "");
    fprintf(fp_write, "#EXTRAS %s\n", "");
    fprintf(fp_write, "#SOMA_AREA %s\n", "");
    fprintf(fp_write, "#SHINKAGE_CORRECTION %f %f %f\n", 1.0, 1.0, 1.0);
    fprintf(fp_write, "#VERSION_NUMBER %s\n", "");
    fprintf(fp_write, "#VERSION_DATE %04d-%02d-%02d\n", year, month, day);
    fprintf(fp_write, "#SCALE %.1f %.1f %.1f\n", 1.0, 1.0, 1.0);
    fprintf(fp_write, "\n");

    for (unsigned int i = 0; i < m_uClusterNum-1; i++) {
        CLST2P(m_Clusters[i])->setNodeNo(i+1);
        RodCluster *pCurParent = CLST2P(m_Clusters[i])->getParent(0);
        unsigned int uCurParentNode = -1;
        if (pCurParent != NULL) {
            uCurParentNode = pCurParent->getNodeNo();
        }
        /*
		  printf(\
		  "%d "\  // No
		  "%d "\  // Type
		  "%f "\  // x
		  "%f "\  // y
		  "%f "\  // z
		  "%f "\  // Radius
		  "%f"\   // Parent
		  "\n",
		  i+1,
		  0,
		  CLST2P(m_Clusters[i])->getNode().x,
		  CLST2P(m_Clusters[i])->getNode().y,
		  CLST2P(m_Clusters[i])->getNode().z,
		  CLST2P(m_Clusters[i])->getDiam()/2,
		  uCurParentNode
		  );
		  * */
        // n T x y z R P
        fprintf(fp_write,
                "%d "  // No
                "%d "  // Type
                "%f "  // x
                "%f "  // y
                "%f "  // z
                "%f "  // Diam
                "%d"   // Parent
                "\n",
                i+1,
                0,
                CLST2P(m_Clusters[i])->getNode().x * m_Scaling.x,
                CLST2P(m_Clusters[i])->getNode().y * m_Scaling.y,
                CLST2P(m_Clusters[i])->getNode().z * m_Scaling.z,
                CLST2P(m_Clusters[i])->getDiam()/2,
                uCurParentNode
                );
    }
    
    fclose(fp_write);
    
    return 0;
}

#define ___NOW_CODING___
#define STR_MAX 512
int Rodriguez2009ClusterList::load(char *fname)
{
#ifdef ___NOW_CODING___
	//----------------------------------------------------------------------
	//
	//----------------------------------------------------------------------
	FILE		 *fp;
	char		**Input	   = NULL;
	int			  line_num = 0;
	char		 *ReservedWord[RODRWNUM];
	int			  rw_num   = RODRWNUM;
	int			  i, j, k;

	unsigned int		uClusterNum;
	unsigned int		uClusterCount = 0;
	unsigned int		uCurChildNum;
	unsigned int		uCurParentNum;
	unsigned int		uCurMemberNum;
	
	char				*sep;
	char				*sep_vector;
	char				*tp;
	int					 temp;
	char				 tempBuf[STR_MAX];
	unsigned int		 uTempCount;	// in order to count current child/parent num
	
	int	ret = 0;
	
	unsigned int		 uCurClusterNo = 0;
	unsigned int		 uCurDistance  = 0;
	RodCluster			*pCurCluster   = NULL;
	int					 nReadMode	   = RODRM_NORMAL;

	//----------------------------------------------------------------------
	// clear Clesters
	//----------------------------------------------------------------------
	clearCluster();

	//----------------------------------------------------------------------
	// Set Reserved Word
	//----------------------------------------------------------------------
	ReservedWord[RODRW_CLUSTER_NUM]		  = "CLUSTER_NUM";
	ReservedWord[RODRW_DISTANCE]          = "DISTANCE";
	ReservedWord[RODRW_CHILD_NUM]         = "CHILD_NUM";
	ReservedWord[RODRW_PARENT_NUM]        = "PARENT_NUM";
	ReservedWord[RODRW_NODE_NO]           = "NODE_NO";
	ReservedWord[RODRW_SCOOPING_DISTANCE] = "SCOOPING_DISTANCE";
	ReservedWord[RODRW_NODE]              = "NODE";
	ReservedWord[RODRW_DIAM]              = "DIAM";
	ReservedWord[RODRW_MEDIAN_POINT]	  = "MEDIAN_POINT";
	ReservedWord[RODRW_MEMBER_NUM]        = "MEMBER_NUM";
	ReservedWord[RODRW_VOXELS]            = "VOXELS";
	ReservedWord[RODRW_SCALING]           = "SCALING";

	//----------------------------------------------------------------------
	// count the number of lines
	//----------------------------------------------------------------------
	for (int i = 0; i < 2; i++) {
		fp = fopen(fname, "r");
		if (fp != NULL) break;
	}
	if (fp == NULL) {
		//printf("Error: file open\n");
		ret = -2;
		goto RodReadClusterData_shutdown;
	}
	line_num = 0;
	while (fgets(tempBuf, STR_MAX, fp) != NULL) {
		line_num++;
	}
	//printf("Line Num = %d\n", line_num);
	fclose(fp);

	//----------------------------------------------------------------------
	// allocate the text loading space
	//----------------------------------------------------------------------
	Input = new char*[line_num];
	for (i = 0; i < line_num; i++) {
		Input[i] = new char[STR_MAX];
	}

	//----------------------------------------------------------------------
	// read file
	//----------------------------------------------------------------------
	fp = fopen(fname, "r");
	if (fp == NULL) {
		//printf("Error: file open\n");
		ret = -3;
		goto RodReadClusterData_shutdown;
	}
	for (i = 0; i < line_num; i++) {
		if (fgets(Input[i], STR_MAX, fp) == NULL)
			break;
		temp = (int)strlen(Input[i]) - 1;
		if (Input[i][temp] == '\n')
			Input[i][temp] = '\0';
	}
	fclose(fp);

	//----------------------------------------------------------------------
	//
	//----------------------------------------------------------------------
	uCurDistance = 0;
	nReadMode = RODRM_NORMAL;
	sep = "\t :";
	sep_vector = "\t :(),";
	for (i = 0; i < line_num; i++) {
 		tp = strtok(Input[i], sep);

		if (tp == NULL) {
			continue;
		}

		if (tp[0] == '-') {
			nReadMode = RODRM_NORMAL;
			continue;
		}

		// CLUSTER_NUM
		if (0 == strcmp(ReservedWord[RODRW_CLUSTER_NUM], tp)) {
			tp = strtok(NULL, sep);
			uClusterNum = atoi(tp);
			if (uClusterNum == 0) {
				ret = -4;
				goto RodReadClusterData_shutdown;
			}
			//m_Clusters = new RodCluster*[uClusterNum];
			//m_uClusterNum = uClusterNum;
			nReadMode = RODRM_NORMAL;
#ifdef ___DEBUG___
			//FILE *fp = fopen("error_log.txt", "a");
			//fprintf(stderr, "\n#################################\n\nClusterNum: %6d\n--------------------\n", uClusterNum);
			//fclose(fp);
#endif
			continue;
		}

		// New cluster start
		if (Input[i-1][0] == '-' && '0' <= tp[0] && tp[0] <= '9') {
			tp = strtok(NULL, sep_vector);
			if (pCurCluster != NULL) {
				pCurCluster = NULL;
			}
			uCurClusterNo = atoi(tp);
			uClusterCount++;
			//printf("tp = %s, uClusterNum = %u, uClusterNo = %u, uClusterCount = %u\n", tp, uClusterNum, uCurClusterNo, uClusterCount);
			
			if (uCurClusterNo >= uClusterNum) {
				break;
			}

			//uCurClusterNo = atoi(tp);
			pCurCluster = new RodCluster();
			pCurCluster->setClusterNo(uCurClusterNo);
			addCluster(pCurCluster);
			nReadMode = RODRM_NORMAL;
			continue;
		}

		// DISTANCE
		if (0 == strcmp(tp, ReservedWord[RODRW_DISTANCE])) {
			tp = strtok(NULL, sep);
			uCurDistance = atoi(tp);

#ifdef ___DEBUG___
			//FILE *fp = fopen("error_log.txt", "a");
			//fprintf(stderr, "distance m_Clusters[%u] = %p: %6d\n", uCurClusterNo, CLST2P(m_Clusters[uCurClusterNo]), uCurDistance);
			//fclose(fp);
#endif
			pCurCluster->setDistance(uCurDistance);

			nReadMode = RODRM_NORMAL;
			continue;
		}
		/*
		// CHILD_NUM
		if (0 == strcmp(tp, ReservedWord[RODRW_CHILD_NUM])) {
		tp = strtok(NULL, sep);
		uCurChildNum = atoi(tp);
		// the number of chldren will set at the time a child is added
		//m_Clusters[uCurClusterNo]->setChildNum(uCurChildNum);
		uTempCount = 0;

		#ifdef ___DEBUG___
		FILE *fp = fopen("error_log.txt", "a");
		fprintf(fp, "child num m_Clusters[%u] = %p: %6d\n", uCurClusterNo, m_Clusters[uCurClusterNo], uCurChildNum);
		fclose(fp);
		#endif

		nReadMode = RODRM_CHILD;
		continue;
		}

		// Set child
		if (nReadMode == RODRM_CHILD) {
		//tp = strtok(NULL, sep);

		pCurCluster->addChild(m_Clusters[atoi(tp)]);

		uTempCount++;
		if (uTempCount >= uCurChildNum) {
		nReadMode = RODRM_NORMAL;
		}

		#ifdef ___DEBUG___
		FILE *fp = fopen("error_log.txt", "a");
		fprintf(fp, "Child No m_Clusters[%u] = %p: %6d\n", uCurClusterNo, m_Clusters[uCurClusterNo], atoi(tp));
		fclose(fp);
		#endif

		continue;
		}
		* */

		// PARENT_NUM
		if (0 == strcmp(tp, ReservedWord[RODRW_PARENT_NUM])) {
			tp = strtok(NULL, sep); // (#)
			uCurParentNum = atoi(tp); // # 
			//m_Clusters[uCurClusterNo]->setParentNum(uCurChildNum);
			nReadMode = RODRM_PARENT;
			continue;
		}

		// set parent
		if (nReadMode == RODRM_PARENT) {
			tp = strtok(NULL, sep_vector);
			pCurCluster->addParent(CLST2P(m_Clusters[atoi(tp)]));

			uTempCount++;
			if (uTempCount >= uCurParentNum) {
				nReadMode = RODRM_NORMAL;
			}

			continue;
		}

		// NODE_NO
		if (0 == strcmp(tp, ReservedWord[RODRW_NODE_NO])) {
			tp = strtok(NULL, sep);
			pCurCluster->setNodeNo(atoi(tp));
			nReadMode = RODRM_NORMAL;
			continue;
		}

		// SCOOPING_DISTANCE
		if (0 == strcmp(tp, ReservedWord[RODRW_SCOOPING_DISTANCE])) {
			tp = strtok(NULL, sep);
			pCurCluster->setScoopingDistance(atof(tp));
			nReadMode = RODRM_NORMAL;
			continue;
		}

		// NODE
		if (0 == strcmp(tp, ReservedWord[RODRW_NODE])) {
			POINT3D tempPoint;
			tp = strtok(NULL, sep_vector);
			tempPoint.x = atof(tp);
			tp = strtok(NULL, sep_vector);
			tempPoint.y = atof(tp);
			tp = strtok(NULL, sep_vector);
			tempPoint.z = atof(tp);

			pCurCluster->setNode(tempPoint);
			nReadMode = RODRM_NORMAL;
			continue;
		}

		// DIAM
		if (0 == strcmp(tp, ReservedWord[RODRW_DIAM])) {
			tp = strtok(NULL, sep);
			pCurCluster->setDiam(atof(tp)); // !!! noted R but it's diam
			nReadMode = RODRM_NORMAL;
			continue;
		}

		// MEDIAN_POINT unavailable
		/*
		  if (0 == strcmp(tp, ReservedWord[RODRW_MEDIAN_POINT])) {
		  POINT3D tempPoint;
		  tp = strtok(NULL, sep_vector);
		  tempPoint.x = atof(tp);
		  tp = strtok(NULL, sep_vector);
		  tempPoint.y = atof(tp);
		  tp = strtok(NULL, sep_vector);
		  tempPoint.z = atof(tp);

		  m_Clusters[uCurClusterNo]-(atoi(tp));
		  nReadMode = RODRM_NORMAL;
		  continue;
		  }
		*/

		// MEMBER_NUM
		if (0 == strcmp(tp, ReservedWord[RODRW_MEMBER_NUM])) {
			tp = strtok(NULL, sep);
			uCurMemberNum = atoi(tp);
			nReadMode = RODRM_NORMAL;
			continue;
		}

		if (0 == strcmp(tp, ReservedWord[RODRW_VOXELS])) {
			uTempCount = 0;
			nReadMode = RODRM_VOXELS;
			continue;
		}

		if (nReadMode == RODRM_VOXELS) {
			POINT3D tempPoint;
			tp = strtok(NULL, sep_vector);
			tempPoint.x = atof(tp);
			tp = strtok(NULL, sep_vector);
			tempPoint.y = atof(tp);
			tp = strtok(NULL, sep_vector);
			tempPoint.z = atof(tp);

			pCurCluster->addVoxel(tempPoint);
			uTempCount++;
			if (uTempCount >= uCurMemberNum) {
				nReadMode = RODRM_NORMAL;
			}
			continue;
		}

		// SCALING
		if (0 == strcmp(tp, ReservedWord[RODRW_SCALING])) {
			POINT3D tempPoint;
			tp = strtok(NULL, sep_vector);
			tempPoint.x = atof(tp);
			tp = strtok(NULL, sep_vector);
			tempPoint.y = atof(tp);
			tp = strtok(NULL, sep_vector);
			tempPoint.z = atof(tp);

			setScaling(tempPoint);
			nReadMode = RODRM_NORMAL;
			continue;
		}

		nReadMode = RODRM_NORMAL;
	}


	if (pCurCluster != NULL) {
		addCluster(pCurCluster);
		pCurCluster = NULL;
	}

	//m_uClusterNum = uCurClusterNo;//+1;
	m_uClusterNum = uClusterCount;

	// renumbering the cluster no
	for (unsigned int i = 0; i < m_uClusterNum; i++) {
		RodCluster *CurCluster = CLST2P(m_Clusters[i]);
		CurCluster->setClusterNo(i);
		CurCluster->setNodeNo(i+1);
		CurCluster->setChildNum(0);
	}

	CLST2P(m_Clusters[0])->setParentNum(0);
	// set children
	for (unsigned int i = 0; i < m_uClusterNum; i++) {
		RodCluster *CurCluster = CLST2P(m_Clusters[i]);
		CurCluster->setChildNum(0);
		//printf("CurCluster = %p\n", CurCluster);
		//printf("\tClusterNo = %d\t", CurCluster->getClusterNo());
		//printf("\tParentNum = %d\n", CurCluster->getParentNum());
		for (unsigned int j = 0; j < CurCluster->getParentNum(); j++) {
			//printf("\tParent(%u) : [%u] -> Child : [%u]\n", j, CurCluster->getParent(j)->getClusterNo(), CurCluster->getClusterNo());
			//printf("\tParent[%u] : ChildNum  = %d\n", CurCluster->getParent(j)->getChildNum());
			CurCluster->getParent(j)->addChild(CurCluster);
		}
	}

	//----------------------------------------------------------------------
	// confirmation
	//----------------------------------------------------------------------
	//print("read_result2.txt");

 RodReadClusterData_shutdown:

	//----------------------------------------------------------------------
	//
	//----------------------------------------------------------------------
	for (i = 0; i < line_num; i++) {
		SAFEDELETE(Input);
	}
	ASAFEDELETE(Input);
#endif//___NOW_CODING___
    return ret;
}
