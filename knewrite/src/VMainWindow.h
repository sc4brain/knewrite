#ifndef ___V_MAIN_WINDOW_H___
#define ___V_MAIN_WINDOW_H___

#include <QMainWindow>
#include <QMdiArea>

#include "VShapeViewGL.h"
#include "VHandTraceOrthoView.h"

#include "MStackImage.h"
#include "MExtractedData.h"

#include "CStackImageController.h"
#include "CExtractedDataController.h"
#include "CHandTracingTool.h"
#include "CViewController.h"
#include "CObjectCommunicator.h"
#include "CTimer.h"

#include "BExtraction.h"

#include "BGlobalDefinitions.h"


class VMainWindow : public QMainWindow, public BTerminal {
Q_OBJECT

public:
	VMainWindow();

protected:
	BDataField               *DataField;

    QWorkspace               *WorkSpace;

    VShapeViewGL             *ShapeViewGL;
    VHandTraceOrthoView      *HandTraceOrthoView;
    
	MStackImage               StackImageList[MAX_STACK_IMAGE_NUM];
    MExtractedData            ExtractedDataList[MAX_EXTRACTED_DATA_NUM];
    
    CStackImageController    *StackImageController;
    CExtractedDataController *ExtractedDataController;
    CViewController          *ViewController;
    CHandTracingTool         *HandTracingTool;
    CTimer                   *Timer;
    
    BExtraction              *ExtractionProcessor;

 protected:
    void                      writeSettings();
    void                      readSettings();
    void                      closeEvent(QCloseEvent *event);
    void                      createActions();
    void                      createMenus();
    void                      createToolBar();
    void                      createStatusBar();

 protected:
    QAction *ExitAction;
    //QList<QAction *> ShowWindows;
    QAction *ActionShowWindowShapeView;
    QAction *ActionShowWindowHandTraceOrthoView;
    QAction *ActionShowWindowStackImageController;
    QAction *ActionShowWindowExtractedDataController;
    QAction *ActionShowWindowViewController;
    QAction *ActionShowWindowHandTracingTool;
    QAction *ActionShowWindowTimer;

    QAction *ActionTileWindow;
    QAction *ActionCascadeWindow;

    QToolBar *ToolBarWindows;

    QMenu *FileMenu;
    QMenu *EditMenu;
    QMenu *ToolsMenu;
    QMenu *WindowsMenu;
    QMenu *HelpMenu;

 private:
    QPushButton              *QuitButton;

//------------------------------------------------------------------------------
// Terminal
//------------------------------------------------------------------------------
 protected:
    void procedure(int ID, char *data, int byte);
};

#endif//___V_MAIN_WINDOW_H___
