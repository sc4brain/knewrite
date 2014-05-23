#ifndef ___C_OBJECT_COMMUNICATOR_ID_H___
#define ___C_OBJECT_COMMUNICATOR_ID_H___

// Communication Message IDs
enum EnumObjectCommunicatorId {
    //COMID_BROADCAST = 0,
	COMID_LOAD_STACKIMAGE,
    COMID_LOAD_STACKIMAGE_OK,
    COMID_SAVE_STACKIMAGE,
    COMID_SAVE_STACKIMAGE_OK,
    COMID_STORE_STACKIMAGE,
    COMID_STORE_STACKIMAGE_OK,
    COMID_REQUEST_STACKIMAGE_POINTER,
    COMID_STACKIMAGE_POINTER,
    COMID_GENERATE_STACKIMAGE,
    COMID_GENERATED_STACKIMAGE,
    COMID_SET_VIEW_STACKIMAGE,
    COMID_SET_VIEW_STACKIMAGE_OK,
    COMID_SET_VIEW_STACKIMAGE_ON,
    COMID_CHANGE_VIEW_STACKIMAGE,
    COMID_CHANGE_VIEW_STACKIMAGE_OK,
    COMID_CHANGE_VIEW_THRESHOLD_STACKIMAGE,
    COMID_CHANGE_VIEW_THRESHOLD_STACKIMAGE_OK,
    COMID_CAHNGE_VIEW_TRANSLATION_STACKIMAGE,
    COMID_CAHNGE_VIEW_TRANSLATION_STACKIMAGE_OK,
    COMID_CHANGE_VIEW_POINTER_STACKIMAGE,
    COMID_CHANGE_VIEW_POINTER_STACKIMAGE_OK,
    COMID_CHANGE_VIEW_ROTATION_STACKIMAGE,
    COMID_CHANGE_VIEW_ROTATION_STACKIMAGE_OK,
    COMID_CHANGE_VIEW_COLOR_STACKIMAGE,
    COMID_CURRENT_VIEW_ROTATION,
    COMID_CURRENT_VIEW_ROTATION_OK,
    COMID_REQUEST_BOUNDINGBOX_STACKIMAGE,
    COMID_BOUNDINGBOX_STACKIMAGE,
    COMID_DO_EXTRACTION,
    COMID_CANCEL_EXTRACTION,
    COMID_CANCELED_EXTRACTION,
    COMID_FINISHED_EXTRACTION,
    COMID_FAILED_EXTRACTION,
    COMID_STORE_EXTRACTEDDATA,
    COMID_STORE_EXTRACTEDDATA_OK,
    COMID_LOAD_EXTRACTEDDATA,
    COMID_LOAD_EXTRACTEDDATA_OK,
    COMID_SAVE_EXTRACTEDDATA,
    COMID_SAVE_EXTRACTEDDATA_OK,
    COMID_REQUEST_EXTRACTEDDATA_POINTER,
    COMID_EXTRACTEDDATA_POINTER,
    COMID_SET_VIEW_EXTRACTEDDATA,
    COMID_SET_VIEW_EXTRACTEDDATA_OK,
    COMID_SET_VIEW_EXTRACTEDDATA_ON,
    COMID_CHANGE_VIEW_ROTATION_EXTRACTEDDATA,
    COMID_CHANGE_VIEW_ROTATION_EXTRACTEDDATA_OK,
    COMID_CHANGE_VIEW_POINTER_EXTRACTEDDATA,
    COMID_CHANGE_VIEW_POINTER_EXTRACTEDDATA_OK,
    COMID_CHANGE_VIEW_ROTATION,
    COMID_CHANGE_VIEW_ROTATION_OK,
    COMID_SET_ORTHOVIEW_STACKIMAGE,
    COMID_HANDTRACE_STACKIMAGE,
    COMID_REQUEST_STACKIMAGE_POINTER_FOR_HANDTRACE,
    /* COMID_HANDTRACE_VIEW_STACKIMAGE, */
    COMID_HANDTRACE_VIEW_POINTER,
    COMID_SET_VIEW_TRACINGNODELIST,
    COMID_SET_VIEW_TRACINGNODELIST_OK,
    COMID_SET_VIEW_TRACINGNODELIST_SUBBRANCH,
    COMID_SET_VIEW_TRACINGNODELIST_SUBBRANCH_OK,
    COMID_SET_VIEW_CURRENT_TRACINGNODE,
    COMID_SET_VIEW_CURRENT_TRACINGNODE_OK,
    COMID_NODE_CLICKED_ON_ORTHOVIEW,
    COMID_ORTHOVIEW_KEYBOARD_MANIPULATION,
    COMID_ORTHOVIEW_MOUSE_MANIPULATION,
    COMID_SET_DEFAULTSIZE_ORTHOVIEW,
    COMID_WINDOW_STATE_CHANGED,
};

/*
  VShapeViewGL
        send
                COMID_CURRENT_VIEW_ROTATION
                COMID_CHANGE_VIEW_ROTATION_STACKIMAGE_OK
                COMID_BOUNDINGBOX_STACKIMAGE
                COMID_SET_VIEW_EXTRACTEDDATA_OK
        recv
                COMID_SET_VIEW_STACKIMAGE
                COMID_SET_VIEW_STACKIMAGE_ON
                COMID_CHANGE_VIEW_STACKIMAGE
                COMID_CHANEG_VIEW_THRESHOLD_STACKIMAGE
                COMID_CHANGE_VIEW_ROTATION_STACKIMAGE
                COMID_CHANGE_VIEW_POINTER_STACKIMAGE
                COMID_REQUEST_BOUNDINGBOX_STACKIMAGE
                COMID_SET_VIEW_EXTRCATEDDATA

  MStackImage
        send
                COMID_LOAD_STACKIMAGE_OK
                COMID_SAVE_STACKIMAGE_OK
                COMID_STACKIMAGE_POINTER
        recv
                COMID_LOAD_STACKIMAGE
                COMID_SAVE_STACKIMAGE
                COMID_REQUEST_STACKIMAGE_POINTER

  MExtractedData
        recv
                COMID_STORE_EXTRACTEDDATA
                COMID_LOAD_EXTRACTEDDATA

  CStackImageController
        send
                COMID_LOAD_STACKIMAGE
                COMID_SAVE_STACKIMAGE
                COMID_DO_EXTRACTION
                COMID_CANCEL_EXTRACTION
                COMID_REQUEST_BOUNDINGBOX_STACKIMAGE
                COMID_CHANGE_VIEW_THRESHOLD_STACKIMAGE
                COMID_SET_VIEW_STACKIMAGE
                COMID_REQUEST_BOUNDINGBOX_STACKIMAGE
                COMID_CHANGE_VIEW_POINTER_STACKIMAGE
                COMID_CHANGE_VIEW_ROTATION_STACKIMAGE
        recv
                COMID_LOAD_STACKIMAGE_OK
                COMID_SAVE_STACKIMAGE_OK
                COMID_STACKIMAGE_POINTER
                COMID_CANCELED_EXTRACTION
                COMID_FINISHED_EXTRACTION
                COMID_FAILED_EXTRACTION
                COMID_SET_VIEW_STACKIMAGE_OK
                COMID_CURRENT_VIEW_ROTATION
                COMID_BOUNDINGBOX_STACKIMAGE

  CExtractedDataController
        send
                COMID_LOAD_EXTRACTEDDATA
                COMID_SAVE_EXTRACTEDDATA
                COMID_CHANGE_VIEW_POINTER_EXTRACTEDDATA
                COMID_CHANGE_VIEW_ROTATION_EXTRACTEDDATA
                COMID_SET_VIEW_EXTRACTEDDATA
                COMID_STORE_EXTRACTEDDATA
        recv
                COMID_FINISHED_EXTRACTION
                COMID_LOAD_EXTRACTEDDATA_OK

  BExtraction
        send
                COMID_FAILED_EXTRACTION
                COMID_CANCELED_EXTRACTION
                COMID_FINISHED_EXTRACTION
        recv
                COMID_DO_EXTRACTION
                COMID_CANCEL_EXTRACTION
 */

typedef struct _DATAFORMAT_LOAD_STACKIMAGE {
    //const static int id = COMID_LOAD_STACKIMAGE;
    char baseName[1024];
    int dataNo;
    struct {
        double x;
        double y;
        double z;
    } scale;
} DATAFORMAT_LOAD_STACKIMAGE;

typedef struct _DATAFORMAT_LOAD_STACKIMAGE_OK {
    //const static int id = COMID_LOAD_STACKIMAGE_OK;
    unsigned char *ptr;
    int dataNo;
    struct {
        int x;
        int y;
        int z;
    } size;
    struct {
        double x;
        double y;
        double z;
    } scale;
} DATAFORMAT_LOAD_STACKIMAGE_OK;

typedef struct _DATAFORMAT_STORE_STACKIMAGE {
    //const static int id = COMID_STORE_STACKIMAGE;
    unsigned char *ptr;
    int dataNo;
    struct {
        int x;
        int y;
        int z;
    } size;
    struct {
        double x;
        double y;
        double z;
    } scale;
} DATAFORMAT_STORE_STACKIMAGE;

typedef struct _DATAFORMAT_STORE_STACKIMAGE_OK {
    //const static int id = COMID_STORE_STACKIMAGE_OK;
    unsigned char *ptr;
    int dataNo;
    struct {
        int x;
        int y;
        int z;
    } size;
    struct {
        double x;
        double y;
        double z;
    } scale;
} DATAFORMAT_STORE_STACKIMAGE_OK;

typedef struct _DATAFORMAT_SAVE_STACKIMAGE {
    //const static int id = COMID_SAVE_STACKIMAGE;
    char baseName[1024];
    char dirName[1024];
    int dataNo;
    /* struct { */
    /*     double x; */
    /*     double y; */
    /*     double z; */
    /* } scale; */
} DATAFORMAT_SAVE_STACKIMAGE;

typedef struct _DATAFORMAT_SAVE_STACKIMAGE_OK {
    //const static int id = COMID_SAVE_STACKIMAGE_OK;
    int dataNo;
} DATAFORMAT_SAVE_STACKIMAGE_OK;

typedef struct _DATAFORMAT_REQUEST_STACKIMAGE_POINTER {
    //const static int id = COMID_REQUEST_STACKIMAGE_POINTER;
    int dataNo;    
} DATAFORMAT_REQUEST_STACKIMAGE_POINTER;

typedef struct _DATAFORMAT_STACKIMAGE_POINTER {
    //const static int id = COMID_STACKIMAGE_POINTER;
    unsigned char *ptr;
    int dataNo;
    struct {
        int x;
        int y;
        int z;
    } size;
    struct {
        double x;
        double y;
        double z;
    } scale;
} DATAFORMAT_STACKIMAGE_POINTER;

#define GENERATE_STACKIMAGE_PARAMNUM 5

typedef struct _DATAFORMAT_GENERATE_STACKIMAGE {
    //const static int id = COMID_GENERATED_STACKIMAGE;
    int dataNo;
    int type;
    double params[GENERATE_STACKIMAGE_PARAMNUM];
} DATAFORMAT_GENERATE_STACKIMAGE;

typedef struct _RANGE_INT {
    int from;
    int to;
} RANGE_INT;

typedef char* REGION3DARRAY_POINTER;

typedef struct _DATAFORMAT_SET_VIEW_STACKIMAGE {
    //const static int id = COMID_SET_VIEW_STACKIMAGE;
    unsigned char *ptr;
    unsigned char threshold;
    int dataNo;
    struct {
        int x;
        int y;
        int z;
    } size;
    struct {
        int x;
        int y;
        int z;
    } translate;
    struct {
        double x;
        double y;
        double z;
    } scale;
    struct {
        RANGE_INT x;
        RANGE_INT y;
        RANGE_INT z;
    } ROI;
    REGION3DARRAY_POINTER ptrLCR;
    bool isLCRon;
    bool on;
    bool alphaMode;
    struct {
        int r;
        int g;
        int b;
    } color;
} DATAFORMAT_SET_VIEW_STACKIMAGE;

typedef struct _DATAFORMAT_SET_VIEW_STACKIMAGE_OK {
    //const static int id = COMID_SET_VIEW_STACKIMAGE_OK;
} DATAFORMAT_SET_VIEW_STACKIMAGE_OK;

typedef struct _DATAFORMAT_SET_VIEW_STACKIMAGE_ON {
    //const static int id = COMID_SET_VIEW_STACKIMAGE_ON;
    int dataNo;
    bool on;
} DATAFORMAT_SET_VIEW_STACKIMAGE_ON;

typedef struct _DATAFORMAT_CHANGE_VIEW_STACKIMAGE {
    //const static int id = COMID_CHANGE_VIEW_STACKIMAGE;
    unsigned char *ptr;
    unsigned char threshold;
    int dataNo;
    struct {
        int x;
        int y;
        int z;
    } size;
    struct {
        int x;
        int y;
        int z;
    } translate;
    struct {
        double x;
        double y;
        double z;
    } scale;
    bool on;
} DATAFORMAT_CHANGE_VIEW_STACKIMAGE;

typedef struct _DATAFORMAT_CHANGE_VIEW_THRESHOLD_STACKIMAGE {
    //const static int id = COMID_CHANGE_VIEW_THRESHOLD_STACKIMAGE;
    unsigned char *ptr;
    struct {
        int x;
        int y;
        int z;
    } size;
    unsigned char threshold;
} DATAFORMAT_CHANGE_VIEW_THRESHOLD_STACKIMAGE;

typedef struct _DATAFORMAT_CHANGE_VIEW_THRESHOLD_STACKIMAGE_OK {
    //const static int id = COMID_CHANGE_VIEW_THRESHOLD_STACKIMAGE_OK;
} DATAFORMAT_CHANGE_VIEW_THRESHOLD_STACKIMAGE_OK;

typedef struct _DATAFORMAT_CAHNGE_VIEW_TRANSLATION_STACKIMAGE {
    //const static int id = COMID_CHANGE_VIEW_TRANSLATION_STACKIMAGE;
    double x;
    double y;
    double z;
} DATAFORMAT_CHANGE_VIEW_TRANSLATION_STACKIMAGE;

typedef struct _DATAFORMAT_CHANGE_VIEW_TRANSLATION_STACKIMAGE_OK {
    //const static int id = COMID_CHANGE_VIEW_TRANSLATION_STACKIMAGE_OK;
} DATAFORMAT_CHANGE_VIEW_TRANSLATION_STACKIMAGE_OK;

typedef struct _DATAFORMAT_CHANGE_VIEW_POINTER_STACKIMAGE {
    //const static int id = COMID_CHANGE_VIEW_POINTER_STACKIMAGE;
    double x; // um
    double y;
    double z;
    bool on;
} DATAFORMAT_CHANGE_VIEW_POINTER_STACKIMAGE;

typedef struct _DATAFORMAT_CHANGE_VIEW_POINTER_STACKIMAGE_OK {
    //const static int id = COMID_CHANGE_VIEW_POINTER_STACKIMAGE_OK;
} DATAFORMAT_CHANGE_VIEW_POINTER_STACKIMAGE_OK;

typedef struct _DATAFORMAT_CHANGE_VIEW_ROTATION_STACKIMAGE {
    //const static int id = COMID_CHANGE_VIEW_ROTATION_STACKIMAGE;
    int rotx;
    int roty;
    int rotz;
} DATAFORMAT_CHANGE_VIEW_ROTATION_STACKIMAGE;

typedef struct _DATAFORMAT_CHANGE_VIEW_ROTATION_STACKIMAGE_OK {
    //const static int id = COMID_CHANGE_VIEW_ROTATION_STACKIMAGE_OK;
} DATAFORMAT_CHANGE_VIEW_ROTATION_STACKIMAGE_OK;

typedef struct _DATAFORMAT_CHANGE_VIEW_COLOR_STACKIMAGE {
    //const static int id = COMID_CHANGE_VIEW_COLOR_STACKIMAGE
    int dataNo;
    double r;
    double g;
    double b;
} DATAFORMAT_CHANGE_VIEW_COLOR_STACKIMAGE;

typedef struct _DATAFORMAT_CURRENT_VIEW_ROTATION {
    //const static int id = COMID_CURRENT_VIEW_ROTATION;
    int rotx;
    int roty;
    int rotz;
} DATAFORMAT_CURRENT_VIEW_ROTATION;

typedef struct _DATAFORMAT_CURRENT_VIEW_ROTATION_OK {
    //const static int id = COMID_CURRENT_VIEW_ROTATION_OK;
} DATAFORMAT_CURRENT_VIEW_ROTATION_OK;

typedef struct _DATAFORMAT_REQUEST_BOUNDINGBOX_STACKIMAGE {
    //const static int id = COMID_REQUEST_BOUNDINGBOX_STACKIMAGE;
} DATAFORMAT_REQUEST_BOUNDINGBOX_STACKIMAGE;

typedef struct _DATAFORMAT_BOUNDINGBOX_STACKIMAGE {
    //const static int id = COMID_BOUNDINGBOX_STACKIMAGE;
    struct {
        double x;
        double y;
        double z;
    } min;
    struct {
        double x;
        double y;
        double z;
    } max;
    struct {
        double x;
        double y;
        double z;
    } mean;
} DATAFORMAT_BOUNDINGBOX_STACKIMAGE;

typedef struct _DATAFORMAT_DO_EXTRACTION {
    //const static int id = COMID_DO_EXTRACTION;
    unsigned char *ptr;
    int dataNo;         // stack image data #
    int targetNo;       // extracted data #
    struct {
        int x;
        int y;
        int z;
    } size;
    struct {
        double x;
        double y;
        double z;
    } scale;
    struct {
        int x;
        int y;
        int z;
    } startPoint;
    struct {
        RANGE_INT x;
        RANGE_INT y;
        RANGE_INT z;
    } ROI;
    unsigned char threshold;
    bool calcProp;
    char fname[2048];
    unsigned char startThreshold;
    unsigned char stopThreshold;
    bool scan;
    int scanDataNoToStore;
    //bool doMedian;
} DATAFORMAT_DO_EXTRACTION;

typedef struct _DATAFORMAT_CANCEL_EXTRACTION {
    //const static int id = COMID_CANCEL_EXTRACTION
} DATAFORMAT_CANCEL_EXTRACTION;

typedef struct _DATAFORMAT_CANCELED_EXTRACTION {
    // const static int id = COMID_CANCELED_EXTRACTION
} DATAFORMAT_CANCELED_EXTRACTION;

//------------------------------------------------------------------------------
// Extracted Data
//------------------------------------------------------------------------------

typedef char* CLUSTERLIST_POINTER;
typedef struct _DATAFORMAT_FINISHED_EXTRACTION {
    //const static int id = COMID_FINISHED_EXTRACTION;
    CLUSTERLIST_POINTER ptr;
    int dataNo;         // stack image data #
    int targetNo;       // extracted data #
    struct {
        double x;
        double y;
        double z;
    } scale;
    /* bool scan; */
    /* unsigned char *labeledDataPtr; */
    /* int scanDataNoToStore;    // stack image data # */
    /* struct { */
    /*     int x; */
    /*     int y; */
    /*     int z; */
    /* } size; */
} DATAFORMAT_FINISHED_EXTRACTION;

typedef struct _DATAFORMAT_FAILED_EXTRACTION {
    // const static int id = COMID_FAILED_EXTRACTION;
    char msg[1024];
} DATAFORMAT_FAILED_EXTRACTION;

typedef struct _DATAFORMAT_STORE_EXTRACTEDDATA {
    //const static int id = COMID_STORE_EXTRACTEDDATA;
    int dataNo;
    CLUSTERLIST_POINTER ptr;
} DATAFORMAT_STORE_EXTRACTEDDATA;

typedef struct _DATAFORMAT_STORE_EXTRACTEDDATA_OK {
    //const static int id = COMID_STORE_EXTRACTEDDATA_OK;
    int dataNo;
    CLUSTERLIST_POINTER ptr;
} DATAFORMAT_STORE_EXTRACTEDDATA_OK;

typedef struct _DATAFORMAT_LOAD_EXTRACTEDDATA {
    //const static int id = COMID_LOAD_EXTRACTEDDATA;
    int dataNo;
    char fileName[1024];
} DATAFORMAT_LOAD_EXTRACTEDDATA;

typedef struct _DATAFORMAT_LOAD_EXTRACTEDDATA_OK {
    //const static int id = COMID_LOAD_EXTRACTEDDATA_OK;
    int dataNo;
    CLUSTERLIST_POINTER ptr;
    struct {
        double x;
        double y;
        double z;
    } scale;
} DATAFORMAT_LOAD_EXTRACTEDDATA_OK;

enum ENUM_SAVE_EXTRACTEDDATA_OUTPUTTYPE {
    EXTRACTEDDATA_OUTPUTTYPE_CLUSTERLIST = 0,
    EXTRACTEDDATA_OUTPUTTYPE_SWC,
    EXTRACTEDDATA_OUTPUTTYPE_HOC,
    EXTRACTEDDATA_OUTPUTTYPE_NUM,
};

typedef struct _DATAFORMAT_SAVE_EXTRACTEDDATA {
    //const static int id = COMID_SAVE_EXTRACTEDDATA;
    char filePath[1024];
    char fileName[1024];
    char dirName[1024];
    int dataNo;
    ENUM_SAVE_EXTRACTEDDATA_OUTPUTTYPE dataFormat;
} DATAFORMAT_SAVE_EXTRACTEDDATA;

typedef struct _DATAFORMAT_SAVE_EXTRACTEDDATA_OK {
    //const static int id = COMID_SAVE_EXTRACTEDDATA_OK;
    int dataNo;
} DATAFORMAT_SAVE_EXTRACTEDDATA_OK;

typedef struct _DATAFORMAT_REQUEST_EXTRACTEDDATA_POINTER {
    //const static int id = COMID_REQUEST_EXTRACTEDDATA_POINTER;
    int dataNo;
} DATAFORMAT_REQUEST_EXTRACTEDDATA_POINTER;

typedef struct _DATAFORMAT_EXTRACTEDDATA_POINTER {
    //const static int id = COMID_EXTRACTEDDATA_POINTER;
    CLUSTERLIST_POINTER ptr;
    int dataNo;
} DATAFORMAT_EXTRACTEDDATA_POINTER;

typedef struct _DATAFORMAT_SET_VIEW_EXTRACTEDDATA {
    //const static int id = COMID_SET_VIEW_EXTRACTEDDATA;
    CLUSTERLIST_POINTER ptr;
    int dataNo;
    struct {
        int x;
        int y;
        int z;
    } translate;
    bool on;
    bool draw;
    int selectedNodeNo;
} DATAFORMAT_SET_VIEW_EXTRACTEDDATA;

typedef struct _DATAFORMAT_SET_VIEW_EXTRACTEDDATA_OK {
    //const static int id = COMID_SET_VIEW_EXTRACTEDDATA_OK;
} DATAFORMAT_SET_VIEW_EXTRACTEDDATA_OK;

typedef struct _DATAFORMAT_SET_VIEW_EXTRACTEDDATA_ON {
    //const static int id = COMID_SET_VIEW_EXTRACTEDDATA_ON;
    bool on;
} DATAFORMAT_SET_VIEW_EXTRACTEDDATA_ON;

typedef struct _DATAFORMAT_CHANGE_VIEW_ROTATION_EXTRACTEDDATA {
    //const static int id = COMID_CHANGE_VIEW_ROTATION_EXTRACTEDDATA;
    int rotx;
    int roty;
    int rotz;
} DATAFORMAT_CHANGE_VIEW_ROTATION_EXTRACTEDDATA;

typedef struct _DATAFORMAT_CHANGE_VIEW_ROTATION_EXTRACTEDDATA_OK {
    //const static int id = COMID_CHANGE_VIEW_ROTATION_EXTRACTEDDATA_OK;
} DATAFORMAT_CHANGE_VIEW_ROTATION_EXTRACTEDDATA_OK;

typedef struct _DATAFORMAT_CHANGE_VIEW_POINTER_EXTRACTEDDATA {
    //const static int id = COMID_CHANGE_VIEW_POINTER_EXTRACTEDDATA;
    int x;
    int y;
    int z;
    bool on;
} DATAFORMAT_CHANGE_VIEW_POINTER_EXTRACTEDDATA;

typedef struct _DATAFORMAT_CHANGE_VIEW_POINTER_EXTRACTEDDATA_OK {
    //const static int id = COMID_CHANGE_VIEW_POINTER_EXTRACTEDDATA_OK;
} DATAFORMAT_CHANGE_VIEW_POINTER_EXTRACTEDDATA_OK;

typedef struct _DATAFORMAT_CHANGE_VIEW_ROTATION {
    //const static int id = COMID_CHANGE_VIEW_ROTATION;
    int rotx;
    int roty;
    int rotz;
} DATAFORMAT_CHANGE_VIEW_ROTATION;

typedef struct _DATAFORMAT_CHANGE_VIEW_ROTATION_OK {
    //const static int id = COMID_CHANGE_VIEW_ROTATION_OK;
} DATAFORMAT_CHANGE_VIEW_ROTATION_OK;


//------------------------------------------------------------------------------
// Hand Tracing Data
//------------------------------------------------------------------------------

typedef char* TRACINGNODELIST_POINTER;
typedef char* TRACINGNODE_POINTER;

typedef struct _DATAFORMAT_SET_ORTHOVIEW_STACKIMAGE {
    //const static int id = COMID_SET_SET_ORTHOVIEW_STACKIMAGE;
    unsigned char *ptr;
    int dataNo;
    struct {
        int x;
        int y;
        int z;
    } size;
    struct {
        double x;
        double y;
        double z;
    } scale;
    bool on;
} DATAFORMAT_SET_ORTHOVIEW_STACKIMAGE;

typedef struct _DATAFORMAT_HANDTRACE_STACKIMAGE {
    //const static int id = COMID_SET_HANDTRACE_STACKIMAGE;
    unsigned char *ptr;
    int dataNo;
    struct {
        int x;
        int y;
        int z;
    } size;
    struct {
        double x;
        double y;
        double z;
    } scale;
    bool on;
} DATAFORMAT_HANDTRACE_STACKIMAGE;

typedef struct _DATAFORMAT_REQUEST_STACKIMAGE_POINTER_FOR_HANDTRACE {
    //const static int id = COMID_REQUEST_STACKIMAGE_POINTER_FOR_HANDTRACE;
    int dataNo;    
} DATAFORMAT_REQUEST_STACKIMAGE_POINTER_FOR_HANDTRACE;

/* typedef struct _DATAFORMAT_HANDTRACE_VIEW_STACKIMAGE { */
/*     //const static int id = COMID_SET_HANDTRACE_VIEW_STACKIMAGE; */
/*     unsigned char *ptr; */
/*     struct { */
/*         int x; */
/*         int y; */
/*         int z; */
/*     } size; */
/*     struct { */
/*         double x; */
/*         double y; */
/*         double z; */
/*     } scale; */
/* } DATAFORMAT_HANDTRACE_VIEW_STACKIMAGE; */

typedef struct _DATAFORMAT_HANDTRACE_VIEW_POINTER {
    //const static int id = COMID_HANDTRACE_VIEW_POINTER;
    struct {
        int x;
        int y;
        int z;
    } pointer;
} DATAFORMAT_HANDTRACE_VIEW_POINTER;

typedef struct _DATAFORMAT_SET_VIEW_TRACINGNODELIST {
    //const static int id = COMID_SET_VIEW_TRACINGNODE;
    TRACINGNODELIST_POINTER ptr;
    struct {
        double x;
        double y;
        double z;
    } scale;
    bool on;
    bool subbranchMode;
} DATAFORMAT_SET_VIEW_TRACINGNODELIST;

typedef struct _DATAFORMAT_SET_VIEW_CURRENT_TRACINGNODE {
    //const static int id = COMID_SET_VIEW_CURRENT_TRACINGNODE;
    //TRACINGNODE_POINTER ptr;
    int nodeNo;
    struct {
        int x;
        int y;
        int z;
    } point;
    double diam;
    struct {
       double x;
       double y;
       double z;
    } scale;
    bool on;
} DATAFORMAT_SET_VIEW_CURRENT_TRACINGNODE;

typedef struct _DATAFORMAT_NODE_CLICKED_ON_ORTHOVIEW {
    //const static int id = COMID_NODE_CLICKED_ON_ORTHOVIEW;
    int nodeNo;
} DATAFORMAT_NODE_CLICKED_ON_ORTHOVIEW;

typedef struct _DATAFORMAT_ORTHOVIEW_KEYBOARD_MANIPULATION {
    //const static int id = COMID_ORTHOVIEW_KEYBOARD_MANIPULATION;
    struct {
        int x;
        int y;
        int z;
    } point;
    bool dispNodeList;
    bool addNode;
    double diam;
} DATAFORMAT_ORTHOVIEW_KEYBOARD_MANIPULATION;

typedef struct _DATAFORMAT_ORTHOVIEW_MOUSE_MANIPULATION {
    //const static int id = COMID_ORTHOVIEW_MOUSE_MANIPULATION;
    struct {
        int x;
        int y;
        int z;
    } point;
    bool dispNodeList;
    bool addNode;
    double diam;
} DATAFORMAT_ORTHOVIEW_MOUSE_MANIPULATION;

typedef struct _DATAFORMAT_SET_DEFAULTSIZE_ORTHOVIEW {
    //const static int id =  COMID_SET_DEFAULTSIZE_ORTHOVIEW;
} DATAFORMAT_SET_DEFAULTSIZE_ORTHOVIEW;

typedef struct _DATAFORMAT_WINDOW_STATE_CHANGED {
    //const static int id = COMID_WINDOW_STATE_CHANGED;
    int windowID;
    bool show;
    bool minimized;
} DATAFORMAT_WINDOW_STATE_CHANGED;

#endif//___C_OBJECT_COMMUNICATOR_ID_H___
