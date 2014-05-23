#ifndef ___B_GLOBAL_DEDINITIONS_H___
#define ___B_GLOBAL_DEDINITIONS_H___

// make sure to orient to max value of the CheckBoxFileLoadDataNo
#define MAX_STACK_IMAGE_NUM 10
#define MAX_EXTRACTED_DATA_NUM MAX_STACK_IMAGE_NUM

#define DEFAULT_STACKIMAGE_THRESHOLD 100

enum WINDOWID {
    WINID_MAINWINDOW = 0,
    WINID_STACKIMAGECONTROLLER,
    WINID_EXTRACTEDDATACONTROLLER,
    WINID_HANDTRACINGTOOL,
    WINID_VIEWCONTROLLER,
    WINID_SHAPEVIEW,
    WINID_ORTHOVIEW,
    WINID_TIMER,
    WINID_NUM,
};

#endif//___B_GLOBAL_DEDINITIONS_H___