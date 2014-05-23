#ifndef ___C_STACK_IMAGE_CONTROLLER_H___
#define ___C_STACK_IMAGE_CONTROLLER_H___

#include <QDialog>
#include "CStackImageControllerDialog.h"
#include "CObjectCommunicator.h"
#include "CObjectCommunicatorID.h"

#include "BVoxelProcesses.h"
#include "BGlobalDefinitions.h"

class CStackImageController :
    public QDialog,
    public Ui::StackImageControllerDialog,
    public BTerminal
{
    Q_OBJECT

 public:
    CStackImageController(QWidget *parent = 0);

 protected:
    
    int CurStackImageNo;
    struct {
        unsigned char *ptr;
        unsigned char threshold;
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
        REGION3DARRAY LCR; // low contrast region
        bool isLCRon;
        bool on;
        bool alphaMode;
        struct {
            int r;
            int g;
            int b;
        } color;
    } StackImageData[MAX_STACK_IMAGE_NUM];
    
    void reflectCurrentState();

    // sendViewCurrentStateLock
    void sendViewControlCurrentStateLock() {
        SendViewControlCurrentStateLock = true; 
    }
    void sendViewControlCurrentStateUnlock() {
        SendViewControlCurrentStateLock = false;
    }
    bool SendViewControlCurrentStateLock;

    /* unsigned char *StackImageDataPtr[MAX_STACK_IMAGE_NUM]; */
    /* unsigned char StackImageThreshold[MAX_STACK_IMAGE_NUM]; */
    /* unsigned char *CurStackImageDataPtr; */
    /* struct { */
    /*     int x; */
    /*     int y; */
    /*     int z; */
    /* } StackImageSize; */
    /* struct { */
    /*     double x; */
    /*     double y; */
    /*     double z; */
    /* } Scale; */

    CLUSTERLIST_POINTER ClusterList;    

//------------------------------------------------------------------------------
// FileLoad
//------------------------------------------------------------------------------
 protected slots:
	void onFileLoadBrowseButtonClicked(); 
	void onFileLoadLoadButtonClicked(); 
	void onFileLoadClearButtonClicked();
    void updateFileLoadFileDirAndName();
	void updateFileLoadOutputTextEdit();
 private slots:
	void setFileLoadLoadButtonEnable();

//------------------------------------------------------------------------------
// FileSave
//------------------------------------------------------------------------------
 protected slots:
	void onFileSaveBrowseButtonClicked();
	void onFileSaveSaveButtonClicked();
	void onFileSaveClearButtonClicked();
    void updateFileSaveFileDirAndName();
    void updateFileSaveFilePath();
	void updateFileSaveOutputTextEdit();
 private slots:
	void setFileSaveSaveButtonEnable();

//------------------------------------------------------------------------------
// Extraction
//------------------------------------------------------------------------------
 protected slots:
    void onExtractionCurrentDataNoButtonClicked();
    void onExtractionThresholdGetFromViewClicked();
    void onExtractionStartPointGetFromViewClicked();
    void updateExtractionBinaryThresholdLineEdit();
    void updateExtractionBinaryThresholdSlideBar();
	void onExtractionExtractButtonClicked();
	void onExtractionCancelButtonClicked();
    void onExtractionHandTracingClicked();
 private slots:
    void setExtractionExtractButtonEnable();
    void onExtractionFinished();
 protected:
    bool nowExtracting;
 signals:
    void extractionFinished();

//------------------------------------------------------------------------------
// Image Processing
//------------------------------------------------------------------------------
 protected slots:
    void onImageProcessingFindLCRButtonClicked();
    void onImageProcessingGenerateStackImageButtonClicked();
    void onImageProcessingAddNoiseButtonClicked();
    void onImageProcessingBackgroundGenerateButtonClicked();
    void onDangerButtonClicked();
    void onPoisonButtonClicked();
    void onEmergencyButtonClicked();

//------------------------------------------------------------------------------
// View Control
//------------------------------------------------------------------------------
 protected slots:

    void onViewControlShowCheckBoxClicked();
    void onViewControlDataNoSpinBoxChanged();
    /* void onViewControlResetBoundingBoxButtonClicked(); */

    void onViewControlAlphaModeCheckBoxClicked();
    void onViewControlLCRCheckBoxClicked();
    void onViewControlOrthoViewButtonClicked();
    void onViewControlResetOrthoViewSizeButtonClicked();

    void updateViewControlThresholdSlideBar();
    void updateViewControlThresholdLineEdit();
    void sendViewControlThreshold();

    void updateViewControlColorRSlideBar();
    void updateViewControlColorRLineEdit();
    void updateViewControlColorGSlideBar();
    void updateViewControlColorGLineEdit();
    void updateViewControlColorBSlideBar();
    void updateViewControlColorBLineEdit();

    void updateViewControlTranslationXSlideBar();
    void updateViewControlTranslationXLineEdit();
    void updateViewControlTranslationYSlideBar();
    void updateViewControlTranslationYLineEdit();
    void updateViewControlTranslationZSlideBar();
    void updateViewControlTranslationZLineEdit();

    void sendViewControlCurrentState();

    void updateViewControlPointerXSlideBar();
    void updateViewControlPointerXLineEdit();
    void updateViewControlPointerYSlideBar();
    void updateViewControlPointerYLineEdit();
    void updateViewControlPointerZSlideBar();
    void updateViewControlPointerZLineEdit();
    void sendViewControlPointer();

    void updateViewControlROIXSlideBarFrom();
    void updateViewControlROIXSlideBarTo();
    void updateViewControlROIXSpinBoxFrom();
    void updateViewControlROIXSpinBoxTo();
    void updateViewControlROIYSlideBarFrom();
    void updateViewControlROIYSlideBarTo();
    void updateViewControlROIYSpinBoxFrom();
    void updateViewControlROIYSpinBoxTo();
    void updateViewControlROIZSlideBarFrom();
    void updateViewControlROIZSlideBarTo();
    void updateViewControlROIZSpinBoxFrom();
    void updateViewControlROIZSpinBoxTo();

//------------------------------------------------------------------------------
// Properties
//------------------------------------------------------------------------------
 protected:
    void updateProperties();

 protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);

//------------------------------------------------------------------------------
// Terminal
//------------------------------------------------------------------------------
 protected:
    void procedure(int ID, char *data, int byte);
};

#endif//___C_STACK_IMAGE_CONTROLLER_H___
