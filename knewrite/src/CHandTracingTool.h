#ifndef ___C_HAND_TRACING_TOOL_H___
#define ___C_HAND_TRACING_TOOL_H___

#include <QDialog>
#include <QMoveEvent>

#include "BTracingData.h"

#include "CHandTracingToolDialog.h"
#include "CObjectCommunicator.h"
#include "CObjectCommunicatorID.h"

#include "BRodriguez2009Cluster.h"

#include "BGlobalDefinitions.h"

class CHandTracingTool : 
    public QDialog,
    public Ui::HandTracingToolDialog,
    public BTerminal
{
    Q_OBJECT

 public:
    CHandTracingTool(QWidget *parent = 0);

 protected:
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
    } StackImageData;
    
    typedef struct _EXTRACTEDDATA_FORMAT {
        RodClusterList data;
        unsigned int maxDist;
    } EXTRACTEDDATA_FORMAT;
    EXTRACTEDDATA_FORMAT ExtractedData;

    //QList<BTracingNode> NodeList;
    //BTracingNode *RootNode;
    BTracingData TracingData;
    QItemSelectionModel *TracingDataSelection;
    BTracingNode CurTracingNode;

    BTracingData TracingDataLocal;
    QItemSelectionModel *TracingDataSelectionLocal;

    BTracingData *CurTracingData;

    struct {
        double x;
        double y;
        double z;
    } Pointer;
    
    bool lockUpdateStates;

 protected:
    void keyPressEvent(QKeyEvent *event);

 protected:
    void setNodeList();

 protected slots:
    void onAddButtonClicked();
    void onDeleteButtonClicked();
    void onGetStackImageDataButtonClicked();
    void onGetExtractedDataButtonClicked();
    void onStoreButtonClicked();
    void onStoreSubbranchButtonClicked();
    void onCloseButtonClicked();
    void onShowCheckBoxClicked();
    void onSubbranchModeCheckBoxClicked();
    void onLocalViewModeCheckBoxClicked();
    void onClearNodeListButtonClicked();
    void onDeleteSubbranchButtonClicked();
    void onNextBranchingPointButtonClicked();
    void onPrevBranchingPointButtonClicked();
    void updatePointerXSlideBar();
    void updatePointerXSpinBox();
    void updatePointerYSlideBar();
    void updatePointerYSpinBox();
    void updatePointerZSlideBar();
    void updatePointerZSpinBox();
    void updateDiamSlideBar();
    void updateDiamDoubleSpinBox();

    void updateCurrentNode(const QModelIndex &index);

    void backgroundSave();


 protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);

 protected:
    void sendPointer();
    void sendNodeList2View();
    void sendCurTracingNode();
    void reflectCurrentNode();
    void procedure(int ID, char* data, int byte);
};

#endif//___C_HAND_TRACING_TOOL_H___
