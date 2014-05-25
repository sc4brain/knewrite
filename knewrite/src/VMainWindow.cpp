
#include <QtGui>

#include "VMainWindow.h"
#include "CObjectCommunicatorID.h"

#include "BCommon.h"

VMainWindow::VMainWindow()
{

    WorkSpace = new QWorkspace;

    setCentralWidget(WorkSpace);

    //setGeometry(100, 100, 640, 480);

    // Quit Button
    dprintf("Startup : creating QuitButton... ");
    QuitButton = new QPushButton("Force Quit");
    connect(QuitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    dprintf("ok\n");


    // Data Filed (inter-object communicator)
    dprintf("Startup : creating DataField... ");
	DataField = new BDataField();
    dprintf("ok\n");

    this->connectToBDataField(DataField);
    this->addID(COMID_WINDOW_STATE_CHANGED);

    // [M]odels

    dprintf("Startup : creating StackImageList... ");
    for (int i = 0; i < MAX_STACK_IMAGE_NUM; i++) {
        StackImageList[i].setDataNo(i);
        StackImageList[i].connectToBDataField(DataField);
        StackImageList[i].addID(COMID_LOAD_STACKIMAGE);
        StackImageList[i].addID(COMID_STORE_STACKIMAGE);
        StackImageList[i].addID(COMID_SAVE_STACKIMAGE);
        StackImageList[i].addID(COMID_REQUEST_STACKIMAGE_POINTER);
        StackImageList[i].addID(COMID_REQUEST_STACKIMAGE_POINTER_FOR_HANDTRACE);
        StackImageList[i].addID(COMID_GENERATE_STACKIMAGE);
    }
    dprintf("ok\n");

    dprintf("Startup : creating ExtractedDataList... ");
    for (int i = 0; i < MAX_STACK_IMAGE_NUM; i++) {
        ExtractedDataList[i].setDataNo(i);
        ExtractedDataList[i].connectToBDataField(DataField);
        ExtractedDataList[i].addID(COMID_STORE_EXTRACTEDDATA);
        ExtractedDataList[i].addID(COMID_LOAD_EXTRACTEDDATA);
        ExtractedDataList[i].addID(COMID_SAVE_EXTRACTEDDATA);
        ExtractedDataList[i].addID(COMID_REQUEST_EXTRACTEDDATA_POINTER);
    }
    dprintf("ok\n");


    // [V]iew

    dprintf("Startup : creating ShapeViewGL...");
    ShapeViewGL = new VShapeViewGL();
    //setCentralWidget(ShapeViewGL);
    ShapeViewGL->connectToBDataField(DataField);
    ShapeViewGL->addID(COMID_SET_VIEW_STACKIMAGE);
    ShapeViewGL->addID(COMID_SET_VIEW_STACKIMAGE_ON);
    ShapeViewGL->addID(COMID_CHANGE_VIEW_STACKIMAGE);
    //ShapeViewGL->addID(COMID_CHANGE_VIEW_THRESHOLD_STACKIMAGE);
    ShapeViewGL->addID(COMID_CHANGE_VIEW_ROTATION_STACKIMAGE);
    ShapeViewGL->addID(COMID_CHANGE_VIEW_ROTATION);
    ShapeViewGL->addID(COMID_CHANGE_VIEW_POINTER_STACKIMAGE);
    ShapeViewGL->addID(COMID_REQUEST_BOUNDINGBOX_STACKIMAGE);
    ShapeViewGL->addID(COMID_SET_VIEW_EXTRACTEDDATA);
    ShapeViewGL->addID(COMID_SET_VIEW_TRACINGNODELIST);
    ShapeViewGL->addID(COMID_SET_VIEW_CURRENT_TRACINGNODE);
    dprintf("ok\n");

    dprintf("Startup : creating HandTraceOrthoView...");
    HandTraceOrthoView = new VHandTraceOrthoView();
    HandTraceOrthoView->connectToBDataField(DataField);
    HandTraceOrthoView->addID(COMID_SET_ORTHOVIEW_STACKIMAGE);
    HandTraceOrthoView->addID(COMID_SET_DEFAULTSIZE_ORTHOVIEW);
    HandTraceOrthoView->addID(COMID_HANDTRACE_VIEW_POINTER);
    HandTraceOrthoView->addID(COMID_CHANGE_VIEW_POINTER_STACKIMAGE);
    HandTraceOrthoView->addID(COMID_SET_VIEW_TRACINGNODELIST);
    HandTraceOrthoView->addID(COMID_SET_VIEW_CURRENT_TRACINGNODE);
    dprintf("ok\n");


    // [C]ontrollers

    dprintf("Startup : creating StackImageController...");
    StackImageController = new CStackImageController();
    StackImageController->connectToBDataField(DataField);
    StackImageController->addID(COMID_LOAD_STACKIMAGE_OK);
    StackImageController->addID(COMID_STORE_STACKIMAGE_OK);
    StackImageController->addID(COMID_SAVE_STACKIMAGE_OK);
    StackImageController->addID(COMID_STACKIMAGE_POINTER);
    StackImageController->addID(COMID_SET_VIEW_STACKIMAGE_OK);
    StackImageController->addID(COMID_CHANGE_VIEW_STACKIMAGE);
    //StackImageController->addID(COMID_CHANGE_VIEW_THRESHOLD_STACKIMAGE_OK);
    StackImageController->addID(COMID_CHANGE_VIEW_ROTATION_STACKIMAGE_OK);
    StackImageController->addID(COMID_CURRENT_VIEW_ROTATION);
    StackImageController->addID(COMID_BOUNDINGBOX_STACKIMAGE);
    StackImageController->addID(COMID_CANCELED_EXTRACTION);
    StackImageController->addID(COMID_FINISHED_EXTRACTION);
    StackImageController->addID(COMID_FAILED_EXTRACTION);
    StackImageController->addID(COMID_ORTHOVIEW_KEYBOARD_MANIPULATION);
    dprintf("ok\n");

    dprintf("Startup : ExtractedDataController... ");
    ExtractedDataController = new CExtractedDataController();
    ExtractedDataController->connectToBDataField(DataField);
    ExtractedDataController->addID(COMID_FINISHED_EXTRACTION);
    ExtractedDataController->addID(COMID_STORE_EXTRACTEDDATA_OK);
    ExtractedDataController->addID(COMID_LOAD_EXTRACTEDDATA_OK);
    dprintf("ok\n");

    dprintf("Startup : ViewController... ");
    ViewController = new CViewController();
    ViewController->connectToBDataField(DataField);
    ViewController->addID(COMID_CURRENT_VIEW_ROTATION);
    dprintf("ok\n");

    dprintf("Startup : creating HandTracingTool...");
    HandTracingTool = new CHandTracingTool();
    HandTracingTool->connectToBDataField(DataField);
    HandTracingTool->addID(COMID_HANDTRACE_STACKIMAGE);
    HandTracingTool->addID(COMID_EXTRACTEDDATA_POINTER);
    HandTracingTool->addID(COMID_NODE_CLICKED_ON_ORTHOVIEW);
    HandTracingTool->addID(COMID_ORTHOVIEW_KEYBOARD_MANIPULATION);
    HandTracingTool->addID(COMID_ORTHOVIEW_MOUSE_MANIPULATION);
    dprintf("ok\n");

    dprintf("Startup : creating Timer...");
    Timer = new CTimer();
    dprintf("ok\n")

    // Backend(s)

    dprintf("Startup : creating ExtractionProcessor...");
    ExtractionProcessor = new BExtraction();
    ExtractionProcessor->connectToBDataField(DataField);
    ExtractionProcessor->addID(COMID_DO_EXTRACTION);
    ExtractionProcessor->addID(COMID_CANCEL_EXTRACTION);
    dprintf("ok\n");


    // set to workspace
    WorkSpace->addWindow(QuitButton);
    WorkSpace->addWindow(ShapeViewGL);
    WorkSpace->addWindow(HandTraceOrthoView);

    WorkSpace->addWindow(StackImageController);
    WorkSpace->addWindow(ExtractedDataController);
    WorkSpace->addWindow(ViewController);
    WorkSpace->addWindow(HandTracingTool);
    WorkSpace->addWindow(Timer);

    // 
    createActions();
    createMenus();
    createToolBar();
    createStatusBar();

    readSettings();

    // show windows
    QuitButton->show();
    ShapeViewGL->hide();
    HandTraceOrthoView->hide();
    StackImageController->show();
    ExtractedDataController->hide();
    ViewController->hide();
    HandTracingTool->hide();
    Timer->hide();
}


VMainWindow::~VMainWindow()
{
    SAFEDELETE(ShapeViewGL);
    SAFEDELETE(HandTraceOrthoView);
    SAFEDELETE(StackImageController);
    SAFEDELETE(ExtractedDataController);
    SAFEDELETE(ViewController);
    SAFEDELETE(HandTracingTool);
    SAFEDELETE(Timer);
    SAFEDELETE(ExtractionProcessor);
    SAFEDELETE(DataField);
    SAFEDELETE(WorkSpace);
}

void VMainWindow::writeSettings()
{
    QSettings settings("NasKage", "Neurowalker");
    QRect rect;
    settings.beginGroup("Geometry");
    rect = geometry();
    settings.setValue("MainWindow", rect);
    dprintf("VMainWindow::writeSettings rect (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());
    rect = ShapeViewGL->parentWidget()->frameGeometry();
    settings.setValue("ShapeViewGL", rect);
    dprintf("ShapeViewGL::writeSettings rect (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());
    rect = HandTraceOrthoView->parentWidget()->frameGeometry();
    settings.setValue("HandTraceOrthoView", rect);
    dprintf("HandTraceOrthoView::writeSettings rect (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());
    rect = StackImageController->parentWidget()->frameGeometry();
    settings.setValue("StackImageController", rect);
    dprintf("StackImageController::writeSettings rect (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());
    rect = ExtractedDataController->parentWidget()->frameGeometry();
    settings.setValue("ExtractedDataController", rect);
    dprintf("ExtractedDataController::writeSettings rect (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());
    rect = ViewController->parentWidget()->frameGeometry();
    settings.setValue("ViewController", rect);
    dprintf("ViewController::writeSettings rect (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());
    rect = HandTracingTool->parentWidget()->frameGeometry();
    settings.setValue("HandTracingTool", rect);
    dprintf("HandTracingTool::writeSettings rect (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());
    rect = Timer->parentWidget()->frameGeometry();
    settings.setValue("Timer", rect);
    dprintf("Timer::writeSettings rect (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());
    settings.endGroup();
}

void VMainWindow::readSettings()
{
    QSettings settings("NasKage", "Neurowalker");

    int x, y, width, height;
    settings.beginGroup("Geometry");
    QRect rect = settings.value("MainWindow",
                                QRect(200, 200, 640, 480)).toRect();
    move(rect.topLeft());
    resize(rect.size());
    
    x = 800; y = 0; width = 512; height = 512;
    rect = settings.value("ShapeViewGL",
                          QRect(x, y, width, height)).toRect();
    ShapeViewGL->parentWidget()->move(rect.topLeft());
    ShapeViewGL->parentWidget()->resize(rect.size());
    dprintf("VMainWindow::readSettings " \
            "ShapeViewGL (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());

    x = 500; y = 100; width = 512; height = 512;
    rect = settings.value("HandTraceOrthoView",
                          QRect(x, y, width, height)).toRect();
    HandTraceOrthoView->parentWidget()->move(rect.topLeft());
    HandTraceOrthoView->parentWidget()->resize(rect.size());
    dprintf("VMainWindow::readSettings " \
            "HandTraceOrthoView (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());

    x = 0; y = 0; width = 830; height = 510;
    rect = settings.value("StackImageController",
                          QRect(x, y, width, height)).toRect();
    StackImageController->parentWidget()->move(rect.topLeft());
    StackImageController->parentWidget()->resize(rect.size());
    dprintf("VMainWindow::readSettings " \
            "StackImageController (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());

    x = 500; y = 100; width = 622; height = 512;
    rect = settings.value("ExtractedDataController",
                             QRect(x, y, width, height)).toRect();
    ExtractedDataController->parentWidget()->move(rect.topLeft());
    ExtractedDataController->parentWidget()->resize(rect.size());
    dprintf("VMainWindow::readSettings " \
            "ExtractedDataController (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());

    x = 500; y = 400; width = 300; height = 362;
    rect = settings.value("ViewController",
                          QRect(x, y, width, height)).toRect();
    ViewController->parentWidget()->move(rect.topLeft());
    ViewController->parentWidget()->resize(rect.size());
    dprintf("VMainWindow::readSettings " \
            "ViewController (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());

    x = 300; y = 200; width = 803; height = 563;
    rect = settings.value("HandTracingTool",
                          QRect(x, y, width, height)).toRect();
    HandTracingTool->parentWidget()->move(rect.topLeft());
    HandTracingTool->parentWidget()->resize(rect.size());
    dprintf("VMainWindow::readSettings " \
            "HandTracingTool (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());

    x = 300; y = 200; width = 285; height = 90;
    rect = settings.value("Timer",
                          QRect(x, y, width, height)).toRect();
    Timer->parentWidget()->move(rect.topLeft());
    Timer->parentWidget()->resize(rect.size());
    dprintf("VMainWindow::readSettings " \
            "Timer (%d, %d, %d, %d)\n",
            rect.x(), rect.y(), rect.width(), rect.height());
    settings.endGroup();

}

void VMainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox msgBox;
    msgBox.setText("App will be down");
    msgBox.setInformativeText("Do you want to save windows' geometry?");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    int ret = msgBox.exec();

    switch (ret) {
        case QMessageBox::Save:
            // Save was clicked
            dprintf("VMainWindow::closeEvent writeSettings...\n");
            writeSettings();
            event->accept();
            break;
        case QMessageBox::Discard:
            // Don't Save was clicked
            event->accept();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            // Cancel was clicked
            break;
        default:
            // should never be reached
            fprintf(stderr, "VMainWindow::closeEvent invalid operation\n");
            exit(-1);
    }
}

void VMainWindow::createActions()
{
    ExitAction = new QAction(tr("&Exit"), this);
    ExitAction->setShortcut(tr("Ctrl+Q"));
    ExitAction->setStatusTip(tr("Quit application"));
    connect(ExitAction, SIGNAL(triggered()), this, SLOT(close()));
    
    ActionShowWindowShapeView = new QAction(tr("ShapeViewGL"), this);
	ActionShowWindowShapeView->setShortcut(tr("Ctrl+Shift+V"));
	ActionShowWindowShapeView->setStatusTip(tr("toggl on/off "));
	ActionShowWindowShapeView->setCheckable(true);
	ActionShowWindowShapeView->setIcon(QIcon("icon/V.png"));
	connect(ActionShowWindowShapeView, SIGNAL(toggled(bool)), ShapeViewGL, SLOT(setVisible(bool)));
	//connect(ShapeViewGL, SIGNAL(closed()), ActionShowWindowShapeView, SLOT(toggle()));
	ActionShowWindowShapeView->setChecked(false);

    ActionShowWindowHandTraceOrthoView = new QAction(tr("HandTraceOrthoView"), this);
	ActionShowWindowHandTraceOrthoView->setShortcut(tr("Ctrl+Shift+O"));
	ActionShowWindowHandTraceOrthoView->setStatusTip(tr("toggl on/off "));
	ActionShowWindowHandTraceOrthoView->setCheckable(true);
    ActionShowWindowHandTraceOrthoView->setIcon(QIcon("icon/O.png"));
	connect(ActionShowWindowHandTraceOrthoView, SIGNAL(toggled(bool)), HandTraceOrthoView, SLOT(setVisible(bool)));
	//connect(HandTraceOrthoView, SIGNAL(closed()), ActionShowWindowHandTraceOrthoView, SLOT(toggle()));
	ActionShowWindowHandTraceOrthoView->setChecked(false);

    ActionShowWindowStackImageController = new QAction(tr("StackImageController"), this);
	ActionShowWindowStackImageController->setShortcut(tr("Ctrl+Shift+S"));
	ActionShowWindowStackImageController->setStatusTip(tr("toggl on/off "));
	ActionShowWindowStackImageController->setCheckable(true);
    ActionShowWindowStackImageController->setIcon(QIcon("icon/S.png"));
	connect(ActionShowWindowStackImageController, SIGNAL(toggled(bool)), StackImageController, SLOT(setVisible(bool)));
	connect(StackImageController, SIGNAL(finished(int)), ActionShowWindowStackImageController, SLOT(toggle()));
	ActionShowWindowStackImageController->setChecked(false);

    ActionShowWindowExtractedDataController = new QAction(tr("ExtractedDataController"), this);
	ActionShowWindowExtractedDataController->setShortcut(tr("Ctrl+Shift+E"));
	ActionShowWindowExtractedDataController->setStatusTip(tr("toggl on/off "));
	ActionShowWindowExtractedDataController->setCheckable(true);
    ActionShowWindowExtractedDataController->setIcon(QIcon("icon/E.png"));
	connect(ActionShowWindowExtractedDataController, SIGNAL(toggled(bool)), ExtractedDataController, SLOT(setVisible(bool)));
	connect(ExtractedDataController, SIGNAL(finished(int)), ActionShowWindowExtractedDataController, SLOT(toggle()));
	ActionShowWindowExtractedDataController->setChecked(false);

    ActionShowWindowViewController = new QAction(tr("ViewController"), this);
	ActionShowWindowViewController->setShortcut(tr("Ctrl+Shift+R"));
	ActionShowWindowViewController->setStatusTip(tr("toggl on/off "));
	ActionShowWindowViewController->setCheckable(true);
    ActionShowWindowViewController->setIcon(QIcon("icon/R.png"));
	connect(ActionShowWindowViewController, SIGNAL(toggled(bool)), ViewController, SLOT(setVisible(bool)));
	connect(ViewController, SIGNAL(finished(int)), ActionShowWindowViewController, SLOT(toggle()));
	ActionShowWindowViewController->setChecked(false);

    ActionShowWindowHandTracingTool = new QAction(tr("HandTracingTool"), this);
	ActionShowWindowHandTracingTool->setShortcut(tr("Ctrl+Shift+H"));
	ActionShowWindowHandTracingTool->setStatusTip(tr("toggl on/off "));
	ActionShowWindowHandTracingTool->setCheckable(true);
    ActionShowWindowHandTracingTool->setIcon(QIcon("icon/M.png"));
	connect(ActionShowWindowHandTracingTool, SIGNAL(toggled(bool)), HandTracingTool, SLOT(setVisible(bool)));
	connect(HandTracingTool, SIGNAL(finished(int)), ActionShowWindowHandTracingTool, SLOT(toggle()));
	ActionShowWindowHandTracingTool->setChecked(false);

    ActionShowWindowTimer = new QAction(tr("Timer"), this);
	ActionShowWindowTimer->setShortcut(tr("Ctrl+Shift+T"));
	ActionShowWindowTimer->setStatusTip(tr("toggl on/off "));
	ActionShowWindowTimer->setCheckable(true);
    ActionShowWindowTimer->setIcon(QIcon("icon/T.png"));
	connect(ActionShowWindowTimer, SIGNAL(toggled(bool)), Timer, SLOT(setVisible(bool)));
	connect(Timer, SIGNAL(finished(int)), ActionShowWindowTimer, SLOT(toggle()));
	ActionShowWindowTimer->setChecked(false);

    // ActionTileWindow = new QAction(tr("Tile Window"), this);
    // ActionTileWindow->
}

void VMainWindow::createMenus()
{
    FileMenu = menuBar()->addMenu(tr("&File"));
    FileMenu->addSeparator();
    FileMenu->addAction(ExitAction);
    // WindowMenu = menuBar()->addMenu(tr("&Window"));
    // WindowMenu->addAction(ActionWindowTile);
    // WindowMenu->addAction(ActionWindowCascade);
}

void VMainWindow::createToolBar()
{
    ToolBarWindows = addToolBar(tr("&Windows"));
    ToolBarWindows->addAction(ActionShowWindowStackImageController);
    ToolBarWindows->addAction(ActionShowWindowExtractedDataController);
    ToolBarWindows->addAction(ActionShowWindowHandTracingTool);
    ToolBarWindows->addAction(ActionShowWindowViewController);
    ToolBarWindows->addSeparator();
    ToolBarWindows->addAction(ActionShowWindowShapeView);
    ToolBarWindows->addAction(ActionShowWindowHandTraceOrthoView);
    ToolBarWindows->addSeparator();
    ToolBarWindows->addAction(ActionShowWindowTimer);
}

void VMainWindow::createStatusBar()
{
    statusBar();
}


//------------------------------------------------------------------------------
// Terminal
//------------------------------------------------------------------------------
void VMainWindow::procedure(int ID, char *data, int byte)
{
    
	switch (ID) {

        case COMID_WINDOW_STATE_CHANGED: {
            DATAFORMAT_WINDOW_STATE_CHANGED *recvData
                = (DATAFORMAT_WINDOW_STATE_CHANGED *)data;
            dprintf("VMainWindow::procedure " \
                    "got WINDOW_STATE_CHANGED\n");
            dprintf("VMainWindow::procedure " \
                    "ID = %d, [%s]\n",
                    recvData->windowID,
                    recvData->show ? "ON" : "OFF");

            //if (recvData->minimized && !recvData->show) return;
            bool show = recvData->show;
            switch (recvData->windowID)
                {
                case WINID_STACKIMAGECONTROLLER:
                    ActionShowWindowStackImageController->setChecked(show);
                    break;
                case WINID_EXTRACTEDDATACONTROLLER:
                    ActionShowWindowExtractedDataController->setChecked(show);
                    break;
                case WINID_HANDTRACINGTOOL:
                    ActionShowWindowHandTracingTool->setChecked(show);
                    break;
                case WINID_VIEWCONTROLLER:
                    ActionShowWindowViewController->setChecked(show);
                    break;
                case WINID_SHAPEVIEW:
                    ActionShowWindowShapeView->setChecked(show);
                    break;
                case WINID_ORTHOVIEW:
                    ActionShowWindowHandTraceOrthoView->setChecked(show);
                    break;
                case WINID_TIMER:
                    ActionShowWindowTimer->setChecked(show);
                    break;
            }

            return;
        } // COMID_WINDOW_STATE_CHANGED

        default:
            return;
    }
}
