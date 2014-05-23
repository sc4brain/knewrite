#ifndef ___C_EXTRACTED_DATA_CONTROLLER_H___
#define ___C_EXTRACTED_DATA_CONTROLLER_H___

#include <QDialog>

#include "CExtractedDataControllerDialog.h"
#include "CObjectCommunicator.h"
#include "CObjectCommunicatorID.h"

#include "BTracingData.h"

#include "BGlobalDefinitions.h"

class CExtractedDataController :
    public QDialog,
    public Ui::ExtractedDataControllerDialog,
    public BTerminal
{
    Q_OBJECT

 public:
    CExtractedDataController(QWidget *parent = 0);

 protected:
    int CurExtractedDataNo;
    struct {
        CLUSTERLIST_POINTER ptr;
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
    } ExtractedData[MAX_EXTRACTED_DATA_NUM];

    void reflectCurrentState();
          

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
// Processing
//------------------------------------------------------------------------------
 protected slots:
    void onProcessingMergeDataMergeButtonClicked();
    void updateProcessingMergeDataParentNodeNo();
    void updateProcessingMergeDataChildNodeNo();

    void onProcessingCompareDataBrowseButtonClicked();
    void onProcessingCompareDataCompareButtonClicked();

//------------------------------------------------------------------------------
// View Control
//------------------------------------------------------------------------------
 protected slots:

    void onViewControlShowCheckBoxClicked();
    void onViewControlDataNoSpinBoxChanged();

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

    /* void updateViewControlRotationXSlideBar(); */
    /* void updateViewControlRotationXLineEdit(); */
    /* void updateViewControlRotationYSlideBar(); */
    /* void updateViewControlRotationYLineEdit(); */
    /* void updateViewControlRotationZSlideBar(); */
    /* void updateViewControlRotationZLineEdit(); */
    /* void setViewControlRotationXYPlane(); */
    /* void setViewControlRotationYZPlane(); */
    /* void setViewControlRotationZXPlane(); */
    /* void sendViewControlRotation(); */

    //void sendSelectedNode2View();
 signals:
    void extractionFinished();
    

 protected:
    void setViewControlNodeList();

 protected:
    BTracingData TracingData;
    QItemSelectionModel *TracingDataSelection;

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

#endif//___C_EXTRACTED_DATA_CONTROLLER_H___
