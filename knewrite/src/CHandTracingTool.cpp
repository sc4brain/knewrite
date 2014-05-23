
#include <QtGui>

#include "CHandTracingTool.h"
#include "BCommon.h"
#include "BRodriguez2009.h"

#define HANDTRACING_SLIDER_POINT_PER_UM 10
#define HANDTRACING_SLIDER_DIAM_PER_UM 100

CHandTracingTool::CHandTracingTool(QWidget *parent) : QDialog(parent)
{
    setupUi(this);

    //RootNode = new BTracingNode;
    TableViewNodeList->setModel(&TracingData);
    TableViewNodeList->horizontalHeader()->setClickable(true);
    TableViewNodeList->setSortingEnabled(true);

    CurTracingData = &TracingData;
    CurTracingNode.NodeNo = 0;

    TracingDataSelection = new QItemSelectionModel(&TracingData);

    TableViewNodeList->setSelectionModel(TracingDataSelection);

    connect(TracingDataSelection, 
            SIGNAL(currentRowChanged(const QModelIndex &,
                                     const QModelIndex &)),
            this, SLOT(updateCurrentNode(const QModelIndex &)));

    // TracingDataSelectionLocal = new QItemSelectionModel(&TracingDataLocal);
    // connect(TracingDataSelectionLocal, 
    //         SIGNAL(currentRowChanged(const QModelIndex &,
    //                                  const QModelIndex &)),
    //         this, SLOT(updateCurrentNode(const QModelIndex &)));

    lockUpdateStates = false;

    connect(PushButtonAdd, SIGNAL(clicked()),
            this, SLOT(onAddButtonClicked()));
    connect(PushButtonDelete, SIGNAL(clicked()),
            this, SLOT(onDeleteButtonClicked()));

    connect(PushButtonDeleteSubbranch, SIGNAL(clicked()), 
            this, SLOT(onDeleteSubbranchButtonClicked()));

    connect(PushButtonNextBranchingPoint, SIGNAL(clicked()), 
            this, SLOT(onNextBranchingPointButtonClicked()));
    connect(PushButtonPrevBranchingPoint, SIGNAL(clicked()), 
            this, SLOT(onPrevBranchingPointButtonClicked()));

    connect(PushButtonGetStackImageData, SIGNAL(clicked()),
            this, SLOT(onGetStackImageDataButtonClicked()));
    connect(PushButtonGetExtractedData, SIGNAL(clicked()),
            this, SLOT(onGetExtractedDataButtonClicked()));
    connect(PushButtonStore, SIGNAL(clicked()),
            this, SLOT(onStoreButtonClicked()));
    connect(PushButtonStoreSubbranch, SIGNAL(clicked()),
            this, SLOT(onStoreSubbranchButtonClicked()));
    connect(PushButtonClose, SIGNAL(clicked()),
            this, SLOT(onCloseButtonClicked()));
    connect(SpinBoxX, SIGNAL(valueChanged(int)),
            this, SLOT(updatePointerXSlideBar()));
    connect(SpinBoxY, SIGNAL(valueChanged(int)),
            this, SLOT(updatePointerYSlideBar()));
    connect(SpinBoxZ, SIGNAL(valueChanged(int)),
            this, SLOT(updatePointerZSlideBar()));
    connect(VerticalSliderX, SIGNAL(valueChanged(int)),
            this, SLOT(updatePointerXSpinBox()));
    connect(VerticalSliderY, SIGNAL(valueChanged(int)),
            this, SLOT(updatePointerYSpinBox()));
    connect(VerticalSliderZ, SIGNAL(valueChanged(int)),
            this, SLOT(updatePointerZSpinBox()));
    connect(DoubleSpinBoxDiam, SIGNAL(valueChanged(double)),
            this, SLOT(updateDiamSlideBar()));
    connect(VerticalSliderDiam, SIGNAL(valueChanged(int)),
            this, SLOT(updateDiamDoubleSpinBox()));

    connect(CheckBoxShow, SIGNAL(stateChanged(int)),
            this, SLOT(onShowCheckBoxClicked()));

    connect(CheckBoxSubbranchMode, SIGNAL(stateChanged(int)),
            this, SLOT(onSubbranchModeCheckBoxClicked()));

    connect(CheckBoxLocalViewMode, SIGNAL(stateChanged(int)),
            this, SLOT(onLocalViewModeCheckBoxClicked()));

    connect(PushButtonClearNodeList, SIGNAL(clicked()),
            this, SLOT(onClearNodeListButtonClicked()));

    connect(&TracingData, SIGNAL(dataChanged(const QModelIndex &, const QModelIndex &)),
            this, SLOT(backgroundSave()));

    // connect(TableViewNodeList, SIGNAL(clicked(const QModelIndex &)),
    //         this, SLOT(updateCurrentNode(const QModelIndex &)));
    // connect(&TracingData, SIGNAL(rowsMoved(const QModelIndex &, int, int,
    //                                       const QModelIndex &, int)),
    //         this, SLOT(updateCurrentNode(const QModelIndex &)));

    // connect(TableViewNodeList->horizontalHeader(),
    //         SIGNAL(sectionClicked(int)),
    //         TableViewNodeList,
    //         SLOT(sortByColumn(int)));
}

void CHandTracingTool::keyPressEvent(QKeyEvent *event)
{
    return;
    dprintf("CHandTracingTool::keyPressEvent %d\n", event->key());
    switch (event->key())
        {
        case Qt::Key_Up:
            VerticalSliderY->setValue(VerticalSliderY->value() + 1);
            break;
        case Qt::Key_Down:
            VerticalSliderY->setValue(VerticalSliderY->value() - 1);
            break;
        case Qt::Key_Left:
            VerticalSliderX->setValue(VerticalSliderX->value() - 1);
            break;
        case Qt::Key_Right:
            VerticalSliderX->setValue(VerticalSliderX->value() + 1);
            break;
        case Qt::Key_PageUp:
            VerticalSliderZ->setValue(VerticalSliderZ->value() + 1);
            break;
        case Qt::Key_PageDown:
            VerticalSliderZ->setValue(VerticalSliderZ->value() - 1);
            break;
        case Qt::Key_Enter:
            //if (event->modifiers() & Qt::ShiftModifier) {
            onAddButtonClicked();
            //}
            break;
        case Qt::Key_Delete:
            onDeleteButtonClicked();
            break;
        case Qt::Key_V:
            CheckBoxShow->toggle();
            break;
        default:
            QWidget::keyPressEvent(event);
            break;
        }
}

// void CHandTracingTool::moveEvent(QMoveEvent *event)
// {
//     dprintf("CHandTracingTool::moveEvent " \
//             "(%d, %d)\n",
//             event->pos().x(), event-pos().y()); 
// }

void CHandTracingTool::setNodeList()
{
    // reset list
    //qDeleteAll(NodeList);
    //NodeList.clear();
    //RootNode->Children.clear();

    //BTracingNode *rootNode = new BTracingNode;
    unsigned int nodeNum = ExtractedData.data.getClusterNum();

    // dprintf("CHandTracingTool::setNodeList nodeNum = %d\n", nodeNum);

    QList<BTracingNode> nodeList;
    nodeList.clear();

    // set NodeNo, Point
    for (unsigned int i = 0; i < nodeNum; i++) {
        RodCluster *curCluster = ExtractedData.data.getCluster(i);
        // dprintf("CHandTracingTool::setNodeList curCluster = %p\n",
        //         curCluster);
        BTracingNode *curNode = new BTracingNode;
        
        // dprintf("CHandTracingTool::setNodeList curNode = %p\n", curNode);

        curNode->NodeNo = curCluster->getClusterNo();
        curNode->Point.x = curCluster->getNode().x;
        curNode->Point.y = curCluster->getNode().y;
        curNode->Point.z = curCluster->getNode().z;
        curNode->Diam = curCluster->getDiam();
        // dprintf("\t [%d/%d] (%f, %f, %f)\n",
        //         curNode->NodeNo,
        //         nodeNum,
        //         curNode->Point.x,
        //         curNode->Point.y,
        //         curNode->Point.z);

        if (curCluster->getParentNum() == 0) {
            curNode->ParentNo = -1;
        } else {
            curNode->ParentNo = curCluster->getParent(0)->getClusterNo();
        }

        curNode->ChildrenNo.clear();
        for (unsigned int j = 0; j < curCluster->getChildNum(); j++) {
            RodCluster *curChild = curCluster->getChild(j);
            curNode->ChildrenNo.append(curChild->getClusterNo());
        }
        nodeList.append(*curNode);
    }

    //
    // for (unsigned int i = 0; i < nodeNum; i++) {
    //     BTracingNode *curNode = &nodeList[i];
    //     curNode->Parent = rootNode;
    //     rootNode->Children.append(curNode);
    // }

    //TableViewNodeList->sortByColumn(2, Qt::AscendingOrder);
    
    TracingData.setNodeList(&nodeList);
    TableViewNodeList->setModel(&TracingData);
    TableViewNodeList->setSelectionModel(TracingDataSelection);
    TableViewNodeList->sortByColumn(0, Qt::AscendingOrder);
    TableViewNodeList->setSelectionMode(
        QAbstractItemView::SingleSelection);
    // TableViewNodeList->horizontalHeader()->setClickable(true);
    // TableViewNodeList->setSortingEnabled(true);
    //TableViewNodeList->reset();

    sendNodeList2View();
}

void CHandTracingTool::onAddButtonClicked()
{
    QModelIndex modelIndex = TableViewNodeList->currentIndex();
    double x = SpinBoxX->value();
    double y = SpinBoxY->value();
    double z = SpinBoxZ->value();
    double diam = DoubleSpinBoxDiam->value();

    TracingData.insertNodeAsChildOf(modelIndex, x, y, z, diam);
    //TableViewNodeList->reset();
    // dprintf("CHandTracingTool::onAddButtonClicked "
    //         "Point (%f, %f, %f), Diam = %f added\n",
    //         NodeList[NodeList.count()-1]->Point.x,
    //         NodeList[NodeList.count()-1]->Point.y,
    //         NodeList[NodeList.count()-1]->Point.z,
    //         NodeList[NodeList.count()-1]->Diam);

    //TableViewNodeList->sortByColumn(0, Qt::AscendingOrder);
    TableViewNodeList->scrollToBottom();
    dprintf("CHandTracingTool::onAddButtonClicked " \
            "scroll to bottom\n");
    //TableViewNodeList->moveCursor(QAbstractItemView::MoveEnd, Qt::NoModifier);
    QModelIndex bottomIndex
        = TracingData.index(TracingData.rowCount(TableViewNodeList->rootIndex())-1, 0);
    dprintf("CHandTracingTool::onAddButtonClicked " \
            "bottomIndex\n");
    TableViewNodeList->setCurrentIndex(bottomIndex);

    dprintf("CHandTracingTool::onAddButtonClicked " \
            "sendNodeList2View()\n");

    CurTracingNode.NodeNo = TracingData.rowCount() - 1;

    sendNodeList2View();
}

void CHandTracingTool::onDeleteButtonClicked()
{
    QModelIndex modelIndex = TableViewNodeList->currentIndex();
    int curRow = modelIndex.row();
    TracingData.removeNode(modelIndex);
    dprintf("CHandTracingTool::onDeleteButtonClicked row = %d\n", curRow);
    dprintf("CHandTracingTool::onDeleteButtonClicked rowCount = %d\n",
            TracingData.rowCount());

    if (curRow == TracingData.rowCount()) {
        int count = TracingData.rowCount(TableViewNodeList->rootIndex())-1;
        //dprintf("CHandTracingTool::onDeleteButtonClicked count = %d\n", count);
        QModelIndex bottomIndex = TracingData.index(count, 0);
        TableViewNodeList->setCurrentIndex(bottomIndex);
    } else {
        QModelIndex nextIndex = TracingData.index(curRow, 0);
        TableViewNodeList->setCurrentIndex(nextIndex);
        dprintf("CHandTracingTool::onDeleteButtonClicked %d\n", 2);
    }

    CurTracingNode.NodeNo = TableViewNodeList->currentIndex().row();

    sendNodeList2View();
}

void CHandTracingTool::onNextBranchingPointButtonClicked()
{
    QModelIndex currentIndex = TableViewNodeList->currentIndex();
    QModelIndex nextIndex = TracingData.searchNextBranchingPoint(currentIndex);
    TableViewNodeList->setCurrentIndex(nextIndex);
    sendNodeList2View();
}

void CHandTracingTool::onPrevBranchingPointButtonClicked()
{
    QModelIndex currentIndex = TableViewNodeList->currentIndex();
    QModelIndex prevIndex = TracingData.searchPrevBranchingPoint(currentIndex);
    TableViewNodeList->setCurrentIndex(prevIndex);
    sendNodeList2View();
}

void CHandTracingTool::onGetStackImageDataButtonClicked()
{
    DATAFORMAT_REQUEST_STACKIMAGE_POINTER_FOR_HANDTRACE sendData;
    sendData.dataNo = SpinBoxStackImageDataNo->value();
    putData(COMID_REQUEST_STACKIMAGE_POINTER_FOR_HANDTRACE,
            (char *)&sendData, sizeof(sendData));
}

void CHandTracingTool::onGetExtractedDataButtonClicked()
{
    DATAFORMAT_REQUEST_EXTRACTEDDATA_POINTER sendData;
    sendData.dataNo = SpinBoxExtractedDataNo->value();
    putData(COMID_REQUEST_EXTRACTEDDATA_POINTER,
            (char *)&sendData, sizeof(sendData));
}

void CHandTracingTool::onStoreButtonClicked()
{
    // create temporary cluster list
    RodClusterList *clusterList = new RodClusterList();

    QList<BTracingNode> *nodeList = TracingData.getNodeList();

    dprintf("CHandTracingTool::onStoreButtonClicked " \
            "NodeNum = %d\n", nodeList->count());

    // set clusters' parameters
    for (int i = 0; i < nodeList->count(); i++) {
        RodCluster *curCluster = new RodCluster;
        BTracingNode *curNode = &(*nodeList)[i];
        curCluster->setParentNum(0);
        curCluster->setChildNum(0);
        //curCluster->setClusterNo(curNode->NodeNo);
        curCluster->setClusterNo(i);
        POINT3D point(curNode->Point.x, curNode->Point.y, curNode->Point.z);
        curCluster->setNode(point);
        curCluster->setNodeNo(curNode->NodeNo > 0 ? curNode->NodeNo : 0);
        //curCluster->setNodeNo(i+1);
        curCluster->setDiam(curNode->Diam);
        clusterList->addCluster(curCluster);
    }

    // set relationship
    for (int i = 0; i < nodeList->count(); i++) {
        RodCluster *curCluster = clusterList->getCluster(i);
        BTracingNode *curNode = &(*nodeList)[i];
        if (curNode->ParentNo >= 0) {
            for (int j = 0; j < clusterList->getClusterNum(); j++) {
                RodCluster *curParentCluster = clusterList->getCluster(j);
                if (curNode->ParentNo == curParentCluster->getNodeNo()) {
                    curCluster->addParent(curParentCluster);
                }
            }
        }
        for (int j = 0; j < curNode->ChildrenNo.count(); j++) {
            int childNo = curNode->ChildrenNo[j];
            RodCluster *curChild = clusterList->getCluster(childNo);
            curChild->setDistance(curCluster->getDistance() + 1);
            curCluster->addChild(curChild);
        }
    }

    for (int i = 0; i < clusterList->getClusterNum(); i++) {
        RodCluster *curCluster = clusterList->getCluster(i);
        if (curCluster->getParentNum() == 0) continue;
        unsigned int childClusterNo = curCluster->getClusterNo();
        unsigned int parentClusterNo = curCluster->getParent(0)->getClusterNo();
        if (childClusterNo < parentClusterNo) {
            dprintf("###!!!### child %d, parent %d\n",
                    childClusterNo,
                    parentClusterNo);
            exit(-1);
        }
    }

    // clusterList->print("testCluster.txt");
    // dprintf("CHandTracingTool::onStoreButtonClicked " \
    //         "clusterList = %p\n", clusterList);

    // set scaling
    clusterList->setScaling(StackImageData.scale.x,
                            StackImageData.scale.y,
                            StackImageData.scale.z);

    // store data
    DATAFORMAT_STORE_EXTRACTEDDATA sendData;
    sendData.ptr = (CLUSTERLIST_POINTER)(clusterList);
    sendData.dataNo = SpinBoxTargetStoreNo->value();
    putData(COMID_STORE_EXTRACTEDDATA,
            (char *)&sendData, sizeof(sendData));

    // delete temporary cluster list
    SAFEDELETE(clusterList);
}
 
void CHandTracingTool::onStoreSubbranchButtonClicked()
{
    // create temporary cluster list
    RodClusterList *clusterList = new RodClusterList();

    QModelIndex currentIndex = TableViewNodeList->currentIndex();
    
    QList<BTracingNode> nodeListSubbranch = TracingData.getSubbranch(currentIndex);

    int startNodeNo = nodeListSubbranch[0].NodeNo;

    dprintf("startNodeNo = %d\n", startNodeNo);

    QList<BTracingNode> nodeList = *TracingData.getNodeList();


    // set clusters' parameters
    for (int i = 0; i < nodeList.count(); i++) {
        RodCluster *curCluster = new RodCluster;
        BTracingNode *curNode = &nodeList[i];
        curCluster->setParentNum(0);
        curCluster->setChildNum(0);
        curCluster->setClusterNo(curNode->NodeNo);
        curCluster->setClusterNo(i);
        POINT3D point(curNode->Point.x, curNode->Point.y, curNode->Point.z);
        curCluster->setNode(point);
        curCluster->setNodeNo(curNode->NodeNo > 0 ? curNode->NodeNo : 0);
        //curCluster->setNodeNo(i+1);
        curCluster->setDiam(curNode->Diam);
        clusterList->addCluster(curCluster);
    }

    // set relationship
    for (int i = 0; i < nodeList.count(); i++) {
        //dprintf("%d ", i);
        RodCluster *curCluster = clusterList->getCluster(i);
        BTracingNode *curNode = &nodeList[i];
        if (curNode->ParentNo >= 0) {
            for (int j = 0; j < clusterList->getClusterNum(); j++) {
                RodCluster *curParentCluster = clusterList->getCluster(j);
                if (curNode->ParentNo == curParentCluster->getNodeNo()) {
                    curCluster->addParent(curParentCluster);
                }
            }
        }
        //dprintf("# \n");
        for (int j = 0; j < curNode->ChildrenNo.count(); j++) {
            int childNo = curNode->ChildrenNo[j];
            RodCluster *curChild = clusterList->getCluster(childNo);
            curChild->setDistance(curCluster->getDistance() + 1);
            curCluster->addChild(curChild);
        }
    }

    for (int i = 0; i < clusterList->getClusterNum(); i++) {
        RodCluster *curCluster = clusterList->getCluster(i);
        if (curCluster->getParentNum() == 0) continue;
        unsigned int childClusterNo = curCluster->getClusterNo();
        unsigned int parentClusterNo = curCluster->getParent(0)->getClusterNo();
        if (childClusterNo < parentClusterNo) {
            dprintf("###!!!### child %d, parent %d\n",
                    childClusterNo,
                    parentClusterNo);
            exit(-1);
        }
    }

    RodClusterList sendClusterList;
    if (Rodriguez2009GetSubbranch(clusterList, startNodeNo, &sendClusterList) < 0) {
        QMessageBox msgBox;
        msgBox.setText("storing subbranch failed");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        int ret = msgBox.exec();
        return;
    }

    // set scaling
    if (StackImageData.scale.x < 0
        || StackImageData.scale.y < 0
        || StackImageData.scale.z < 0) {
        sendClusterList.setScaling(1, 1, 1);
    } else {
        sendClusterList.setScaling(StackImageData.scale.x,
                                StackImageData.scale.y,
                                StackImageData.scale.z);
    }

    // store data
    DATAFORMAT_STORE_EXTRACTEDDATA sendData;
    sendData.ptr = (CLUSTERLIST_POINTER)(&sendClusterList);
    sendData.dataNo = SpinBoxStoreSubbranchNo->value();
    putData(COMID_STORE_EXTRACTEDDATA,
            (char *)&sendData, sizeof(sendData));

    // delete temporary cluster list
    SAFEDELETE(clusterList);
}   

void CHandTracingTool::onCloseButtonClicked()
{
}

void CHandTracingTool::onShowCheckBoxClicked()
{
    sendNodeList2View();
}

void CHandTracingTool::onSubbranchModeCheckBoxClicked()
{
    sendNodeList2View();
}

void CHandTracingTool::onLocalViewModeCheckBoxClicked()
{
    bool localViewMode = CheckBoxLocalViewMode->isChecked();
    if (localViewMode) {
        double x = CurTracingNode.Point.x;
        double y = CurTracingNode.Point.y;
        double z = CurTracingNode.Point.z;
        double range = 50.;
        TracingData.setLocalRegion(x - range, x + range,
                                    y - range, y + range,
                                    z - range, z + range);
    } else {
        TracingData.clearLocalRegion();
    }
    TableViewNodeList->reset();
}

void CHandTracingTool::onClearNodeListButtonClicked()
{
    QMessageBox msgBox;
    msgBox.setText("Do you really want to clear the node list?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    switch (ret) {
        case QMessageBox::Yes:
            {
                QList<BTracingNode> nodeList;
                nodeList.clear();
                TracingData.setNodeList(&nodeList);
                break;
            }
        case QMessageBox::Cancel:
            break;
        default:
            fprintf(stderr, "CHandTracingTool::onClearNodeListButtonClicked " \
                    "invalid operation\n");
            exit(-1);
    }
}

void CHandTracingTool::onDeleteSubbranchButtonClicked()
{
    QMessageBox msgBox;
    msgBox.setText("Do you really want to delete branches rooted this node?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    switch (ret) {
        case QMessageBox::Yes:
            {
                QModelIndex modelIndex = TableViewNodeList->currentIndex();
                int ret = TracingData.removeSubbranch(modelIndex);
                if (ret < 0) {
                    dprintf("CHandTracingTool::onDeleteSubbranchButtonClicked " \
                            "removeSubbranch failed with code %d\n", ret);
                } else {
                    sendNodeList2View();
                }
                break;
            }
        case QMessageBox::Cancel:
            break;
        default:
            fprintf(stderr, "CHandTracingTool::onClearNodeListButtonClicked " \
                    "invalid operation\n");
            exit(-1);
    }
}

void CHandTracingTool::updatePointerXSlideBar()
{
    if (lockUpdateStates) return;
    int value = SpinBoxX->value();
    VerticalSliderX->setValue(value);
    CurTracingNode.Point.x = value;
    sendPointer();
    sendCurTracingNode();
}

void CHandTracingTool::updatePointerXSpinBox()
{
    if (lockUpdateStates) return;
    int value = VerticalSliderX->value();
    SpinBoxX->setValue(value);
}

void CHandTracingTool::updatePointerYSlideBar()
{
    if (lockUpdateStates) return;
    int value = SpinBoxY->value();
    VerticalSliderY->setValue(value);
    CurTracingNode.Point.y = value;
    sendPointer();
    sendCurTracingNode();
}

void CHandTracingTool::updatePointerYSpinBox()
{
    if (lockUpdateStates) return;
    int value = VerticalSliderY->value();
    SpinBoxY->setValue(value);
}

void CHandTracingTool::updatePointerZSlideBar()
{
    if (lockUpdateStates) return;
    int value = SpinBoxZ->value();
    VerticalSliderZ->setValue(value);
    CurTracingNode.Point.z = value;
    sendPointer();
    sendCurTracingNode();
}

void CHandTracingTool::updatePointerZSpinBox()
{
    if (lockUpdateStates) return;
    int value = VerticalSliderZ->value();
    SpinBoxZ->setValue(value);
}

void CHandTracingTool::updateDiamSlideBar()
{
    if (lockUpdateStates) return;
    double value = DoubleSpinBoxDiam->value();
    VerticalSliderDiam->setValue((int)(value * HANDTRACING_SLIDER_DIAM_PER_UM));
    CurTracingNode.Diam = value;
    sendCurTracingNode();
}

void CHandTracingTool::updateDiamDoubleSpinBox()
{
    if (lockUpdateStates) return;
    int value = VerticalSliderDiam->value();
    DoubleSpinBoxDiam->setValue(value / (double)HANDTRACING_SLIDER_DIAM_PER_UM);
}

void CHandTracingTool::updateCurrentNode(const QModelIndex &index)
{
    int nodeNo = CurTracingData->data(index.sibling(index.row(), 0)).toInt();
    QString str = CurTracingData->data(index.sibling(index.row(), 1)).toString();
    QRegExp sep("[(, )]+");
    double x = str.section(sep, 0, 0, QString::SectionSkipEmpty).toDouble();
    double y = str.section(sep, 1, 1, QString::SectionSkipEmpty).toDouble();
    double z = str.section(sep, 2, 2, QString::SectionSkipEmpty).toDouble();
    double diam = CurTracingData->data(index.sibling(index.row(), 2)).toDouble();
    dprintf("CHandTracingTool::updateCurrentNode " \
            "nodeNo = %d, point (%f, %f, %f), diam = %f\n",
            nodeNo, x, y, z, diam);

    CurTracingNode.NodeNo = nodeNo;
    CurTracingNode.Point.x = x;
    CurTracingNode.Point.y = y;
    CurTracingNode.Point.z = z;
    CurTracingNode.Diam = diam;
    
    lockUpdateStates = true;
    reflectCurrentNode();
    lockUpdateStates = false;
    
    sendNodeList2View();
    sendPointer();
    sendCurTracingNode();
}

void CHandTracingTool::backgroundSave()
{
    // create temporary cluster list
    RodClusterList *clusterList = new RodClusterList();

    QList<BTracingNode> *nodeList = TracingData.getNodeList();

    dprintf("CHandTracingTool::backgroundSave " \
            "auto saving... ");

    // set clusters' parameters
    for (int i = 0; i < nodeList->count(); i++) {
        RodCluster *curCluster = new RodCluster;
        BTracingNode *curNode = &(*nodeList)[i];
        curCluster->setParentNum(0);
        curCluster->setChildNum(0);
        //curCluster->setClusterNo(curNode->NodeNo);
        curCluster->setClusterNo(i);
        POINT3D point(curNode->Point.x, curNode->Point.y, curNode->Point.z);
        curCluster->setNode(point);
        curCluster->setNodeNo(curNode->NodeNo > 0 ? curNode->NodeNo : 0);
        //curCluster->setNodeNo(i+1);
        curCluster->setDiam(curNode->Diam);
        clusterList->addCluster(curCluster);
    }

    // set relationship
    for (int i = 0; i < nodeList->count(); i++) {
        RodCluster *curCluster = clusterList->getCluster(i);
        BTracingNode *curNode = &(*nodeList)[i];
        if (curNode->ParentNo >= 0) {
            for (int j = 0; j < clusterList->getClusterNum(); j++) {
                RodCluster *curParentCluster = clusterList->getCluster(j);
                if (curNode->ParentNo == curParentCluster->getNodeNo()) {
                    curCluster->addParent(curParentCluster);
                }
            }
        }
        for (int j = 0; j < curNode->ChildrenNo.count(); j++) {
            int childNo = curNode->ChildrenNo[j];
            RodCluster *curChild = clusterList->getCluster(childNo);
            curChild->setDistance(curCluster->getDistance() + 1);
            curCluster->addChild(curChild);
        }
    }

    for (int i = 0; i < clusterList->getClusterNum(); i++) {
        RodCluster *curCluster = clusterList->getCluster(i);
        if (curCluster->getParentNum() == 0) continue;
        unsigned int childClusterNo = curCluster->getClusterNo();
        unsigned int parentClusterNo = curCluster->getParent(0)->getClusterNo();
        if (childClusterNo < parentClusterNo) {
            dprintf("###!!!### child %d, parent %d\n",
                    childClusterNo,
                    parentClusterNo);
            exit(-1);
        }
    }

    // clusterList->print("testCluster.txt");
    // dprintf("CHandTracingTool::onStoreButtonClicked " \
    //         "clusterList = %p\n", clusterList);

    // set scaling
    clusterList->setScaling(StackImageData.scale.x,
                            StackImageData.scale.y,
                            StackImageData.scale.z);

    clusterList->print("###AutoSaved###.txt");
    SAFEDELETE(clusterList);

    dprintf(" ok\n");
}

void CHandTracingTool::sendPointer()
{
    int valuex = VerticalSliderX->value();
    int valuey = VerticalSliderY->value();
    int valuez = VerticalSliderZ->value();

    DATAFORMAT_HANDTRACE_VIEW_POINTER sendData;
    sendData.pointer.x = valuex;
    sendData.pointer.y = valuey;
    sendData.pointer.z = valuez;
    
    putData(COMID_HANDTRACE_VIEW_POINTER,
            (char *)&sendData, sizeof(sendData));

    DATAFORMAT_CHANGE_VIEW_POINTER_STACKIMAGE sendData2;
    sendData2.x = valuex * StackImageData.scale.x;
    sendData2.y = valuey * StackImageData.scale.y;
    sendData2.z = valuez * StackImageData.scale.z;
    sendData2.on = true;

    putData(COMID_CHANGE_VIEW_POINTER_STACKIMAGE,
            (char *)&sendData2, sizeof(sendData2));
}

void CHandTracingTool::sendNodeList2View()
{
    bool subbranchMode = CheckBoxSubbranchMode->isChecked();

    QList<BTracingNode> nodeList;
    if (subbranchMode) {
        QModelIndex modelIndex = TableViewNodeList->currentIndex();
        nodeList = TracingData.getSubbranch(modelIndex);
    } else {
        nodeList = *TracingData.getNodeList();
        // for (int i = 0; i < tempNodeList->count(); i++) {
        //     nodeList.append((*tempNodeList)[i]);
        // }
    }

    bool on = CheckBoxShow->isChecked();

    DATAFORMAT_SET_VIEW_TRACINGNODELIST sendData;
    sendData.ptr = (TRACINGNODELIST_POINTER)&nodeList;
    sendData.scale.x = StackImageData.scale.x;
    sendData.scale.y = StackImageData.scale.y;
    sendData.scale.z = StackImageData.scale.z;
    sendData.on = on;
    sendData.subbranchMode = subbranchMode;
    putData(COMID_SET_VIEW_TRACINGNODELIST,
            (char *)&sendData, sizeof(sendData));
}

void CHandTracingTool::sendCurTracingNode()
{
    DATAFORMAT_SET_VIEW_CURRENT_TRACINGNODE sendData;
    //sendData.ptr = (TRACINGNODE_POINTER)&CurTracingNode;
    sendData.nodeNo = CurTracingNode.NodeNo;
    sendData.point.x = CurTracingNode.Point.x;
    sendData.point.y = CurTracingNode.Point.y;
    sendData.point.z = CurTracingNode.Point.z;
    sendData.diam = CurTracingNode.Diam;
    sendData.scale.x = StackImageData.scale.x;
    sendData.scale.y = StackImageData.scale.y;
    sendData.scale.z = StackImageData.scale.z;
    sendData.on = true;

    putData(COMID_SET_VIEW_CURRENT_TRACINGNODE,
            (char *)&sendData, sizeof(sendData));
}

void CHandTracingTool::reflectCurrentNode()
{
    SpinBoxX->setValue((int)CurTracingNode.Point.x);
    SpinBoxY->setValue((int)CurTracingNode.Point.y);
    SpinBoxZ->setValue((int)CurTracingNode.Point.z);
    DoubleSpinBoxDiam->setValue(CurTracingNode.Diam);
    VerticalSliderX->setValue((int)CurTracingNode.Point.x);
    VerticalSliderY->setValue((int)CurTracingNode.Point.y);
    VerticalSliderZ->setValue((int)CurTracingNode.Point.z);
    VerticalSliderDiam->setValue((int)(CurTracingNode.Diam
                                       * HANDTRACING_SLIDER_DIAM_PER_UM));
}

void CHandTracingTool::showEvent(QShowEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_HANDTRACINGTOOL;
    sendData.show = this->isVisible();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void CHandTracingTool::hideEvent(QHideEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_HANDTRACINGTOOL;
    sendData.show = this->isVisible();
    sendData.minimized = this->isMinimized();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void CHandTracingTool::closeEvent(QCloseEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_HANDTRACINGTOOL;
    sendData.show = this->isVisible();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void CHandTracingTool::procedure(int ID, char *data, int byte)
{
    switch (ID) {
        
        case COMID_HANDTRACE_STACKIMAGE: {
            DATAFORMAT_HANDTRACE_STACKIMAGE *recvData
                = (DATAFORMAT_HANDTRACE_STACKIMAGE *)data;
            
            dprintf("CHandTracingTool::procedure " \
                    "got HANDTRACE_STACKIMAGE\n");

            StackImageData.ptr = recvData->ptr;
            StackImageData.size.x = recvData->size.x;
            StackImageData.size.y = recvData->size.y;
            StackImageData.size.z = recvData->size.z;
            StackImageData.scale.x = recvData->scale.x;
            StackImageData.scale.y = recvData->scale.y;
            StackImageData.scale.z = recvData->scale.z;

            VerticalSliderX->setMinimum(0);
            VerticalSliderX->setMaximum(StackImageData.size.x - 1);
            VerticalSliderY->setMinimum(0);
            VerticalSliderY->setMaximum(StackImageData.size.y - 1);
            VerticalSliderZ->setMinimum(0);
            VerticalSliderZ->setMaximum(StackImageData.size.z - 1);
            SpinBoxX->setMinimum(0);
            SpinBoxX->setMaximum(StackImageData.size.x - 1);
            SpinBoxY->setMinimum(0);
            SpinBoxY->setMaximum(StackImageData.size.y - 1);
            SpinBoxZ->setMinimum(0);
            SpinBoxZ->setMaximum(StackImageData.size.z - 1);


            DATAFORMAT_SET_ORTHOVIEW_STACKIMAGE sendData;
            sendData.ptr = StackImageData.ptr;
            sendData.size.x = StackImageData.size.x;
            sendData.size.y = StackImageData.size.y;
            sendData.size.z = StackImageData.size.z;
            sendData.scale.x = StackImageData.scale.x;
            sendData.scale.y = StackImageData.scale.y;
            sendData.scale.z = StackImageData.scale.z;
            putData(COMID_SET_ORTHOVIEW_STACKIMAGE,
                    (char *)&sendData, sizeof(sendData));

            // DATAFORMAT_HANDTRACE_VIEW_STACKIMAGE sendData;
            // sendData.ptr = StackImageData.ptr;
            // sendData.size.x = StackImageData.size.x;
            // sendData.size.y = StackImageData.size.y;
            // sendData.size.z = StackImageData.size.z;
            // sendData.scale.x = StackImageData.scale.x;
            // sendData.scale.y = StackImageData.scale.y;
            // sendData.scale.z = StackImageData.scale.z;
            
            // putData(COMID_HANDTRACE_VIEW_STACKIMAGE,
            //         (char *)&sendData, sizeof(sendData));
            this->parentWidget()->show();
            this->show();

            return;
        } // COMID_HANDTRACE_STACKIMAGE

        case COMID_EXTRACTEDDATA_POINTER: {
            DATAFORMAT_EXTRACTEDDATA_POINTER *recvData
                = (DATAFORMAT_EXTRACTEDDATA_POINTER *)data;

            dprintf("CHandTracingTool::procedure " \
                    "got EXTRACTEXDDATA_POINTER\n");
            dprintf("CHandTracingTool::procedure " \
                    "ptr = %p, dataNo = %d\n",
                    recvData->ptr, recvData->dataNo);

            if (recvData->ptr == NULL) {
                printf("CHandTracingTool::procedure " \
                       "NULL pointer passed\n");
                return;
            }

            ExtractedData.data = *((RodClusterList *)recvData->ptr);

            dprintf("CHandTracingTool::procedure " \
                    "ClusterNum = %u\n",
                    ExtractedData.data.getClusterNum());

            this->setNodeList();

            return;
        } // COMID_EXTRACTEDDATA_POINTER

        case COMID_NODE_CLICKED_ON_ORTHOVIEW: {
            DATAFORMAT_NODE_CLICKED_ON_ORTHOVIEW *recvData
                = (DATAFORMAT_NODE_CLICKED_ON_ORTHOVIEW *)data;
            dprintf("CHandTracingTool::procedure " \
                    "got NODE_CLICKED_ON_ORTHOVIEW\n");
            dprintf("CHandTracingTool::procedure " \
                    "nodeNo = %d\n", recvData->nodeNo);

            QModelIndex curIndex = TracingData.selectByData(0, recvData->nodeNo);
            TableViewNodeList->setCurrentIndex(curIndex);

            // TableViewNodeList->sortByColumn(0, Qt::AscendingOrder);
            // TableViewNodeList->setSelectionMode(QAbstractItemView::SingleSelection);
            //updateCurrentNode();

            return;
        }

        case COMID_ORTHOVIEW_KEYBOARD_MANIPULATION: {
            DATAFORMAT_ORTHOVIEW_KEYBOARD_MANIPULATION *recvData
                = (DATAFORMAT_ORTHOVIEW_KEYBOARD_MANIPULATION *)data;

            // dprintf("CHandTracingTool::procedure " \
            //         "got ORTHOVIEW_KEYBOARD_MANIPULATION\n");

            CurTracingNode.Point.x = recvData->point.x;
            CurTracingNode.Point.y = recvData->point.y;
            CurTracingNode.Point.z = recvData->point.z;
            CurTracingNode.Diam = recvData->diam;
    
            lockUpdateStates = true;
            reflectCurrentNode();
            lockUpdateStates = false;
    
            sendNodeList2View();
            sendPointer();
            sendCurTracingNode();

            CheckBoxShow->setChecked(recvData->dispNodeList);
            if (recvData->addNode) {
                onAddButtonClicked();
            }

            return;
        } // COMID_ORTHOVIEW_KEYBOARD_MANIPULATION

        case COMID_ORTHOVIEW_MOUSE_MANIPULATION: {
            DATAFORMAT_ORTHOVIEW_MOUSE_MANIPULATION *recvData
                = (DATAFORMAT_ORTHOVIEW_MOUSE_MANIPULATION *)data;

            // dprintf("CHandTracingTool::procedure " \
            //         "got ORTHOVIEW_MOUSE_MANIPULATION\n");

            CurTracingNode.Point.x = recvData->point.x;
            CurTracingNode.Point.y = recvData->point.y;
            CurTracingNode.Point.z = recvData->point.z;
            CurTracingNode.Diam = recvData->diam;
    
            lockUpdateStates = true;
            reflectCurrentNode();
            lockUpdateStates = false;
    
            sendNodeList2View();
            sendPointer();
            sendCurTracingNode();

            CheckBoxShow->setChecked(recvData->dispNodeList);
            if (recvData->addNode) {
                onAddButtonClicked();
            }

            return;
        } // COMID_ORTHOVIEW_MOUSE_MANIPULATION

        default:
            return;
    }
}
