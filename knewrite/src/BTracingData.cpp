
#include <QtGui>
#include "BTracingData.h"

#include "BCommon.h"

BTracingData::BTracingData(QObject *parent) : QAbstractItemModel(parent)
{
    RootNode = NULL;
    LocalRegion = NULL;
}

BTracingData::~BTracingData()
{
    delete RootNode;
}

void BTracingData::setNodeList(QList<BTracingNode> *nodeList)
{
    delete RootNode;
    RootNode = new BTracingNode;
    NodeList.clear();
    for (int i = 0; i < nodeList->count(); i++) {
        BTracingNode *curNode = new BTracingNode;
        BTracingNode *refNode = &(*nodeList)[i];
        curNode->NodeNo = refNode->NodeNo;
        curNode->Point.x = refNode->Point.x;
        curNode->Point.y = refNode->Point.y;
        curNode->Point.z = refNode->Point.z;
        curNode->Diam = refNode->Diam;
        curNode->ParentNo = refNode->ParentNo;
        curNode->ChildrenNo.clear();
        for (int j = 0; j < refNode->ChildrenNo.count(); j++) {
            curNode->ChildrenNo.append(refNode->ChildrenNo[j]);
        }
        curNode->Parent = RootNode;
        RootNode->Children.append(curNode);
        NodeList.append(*curNode);
    }
    reset();
}

QList<BTracingNode> *BTracingData::getNodeList()
{
    return &NodeList;
}

QList<BTracingNode> BTracingData::getSubbranch(const QModelIndex &startIndex)
{
    BTracingNode *startNode = nodeFromIndex(startIndex);

    if (startNode == NULL) {
        return QList<BTracingNode>();
    }

    QList<BTracingNode> subbranchNodeList;
    subbranchNodeList.push_back(*startNode);

    // list up the subbranch nodes
    QList<BTracingNode *> curNodeList;
    curNodeList.append(startNode);
    while (curNodeList.count() != 0) {
        QList<BTracingNode *> nextNodeList;
        nextNodeList.clear();
        for (int i = 0; i < curNodeList.count(); i++) {
            BTracingNode *curNode = curNodeList[i];
            for (int j = 0; j < curNode->ChildrenNo.count(); j++) {
                int curChildNo = curNode->ChildrenNo[j];
                BTracingNode *curChildNode = &NodeList[curChildNo];
                nextNodeList.append(curChildNode);
                subbranchNodeList.append(*curChildNode);
            }
        }
        curNodeList = nextNodeList;
    }

    return subbranchNodeList;
}

QModelIndex BTracingData::index(int row,
                                  int column,
                                  const QModelIndex &parent) const
{
    if (!RootNode) return QModelIndex();
    BTracingNode *parentNode = nodeFromIndex(parent);
    return createIndex(row, column, parentNode->Children[row]);
}

BTracingNode *BTracingData::nodeFromIndex(const QModelIndex &index) const
{
    if (index.isValid()) {
        return static_cast<BTracingNode *>(index.internalPointer());
    } else {
        return RootNode;
    }
}

bool BTracingData::isIncludedInLocalRegion(BTracingNode *node) const
{
    bool ret = false;
    if (LocalRegion == NULL) return true;
    if (node->Point.x < LocalRegion->from.x
        || LocalRegion->to.x < node->Point.x
        || node->Point.y < LocalRegion->from.y
        || LocalRegion->to.y < node->Point.y
        || node->Point.z < LocalRegion->from.z
        || LocalRegion->to.z < node->Point.z) {
        return false;
    }
    return true;
}

int BTracingData::rowCount(const QModelIndex &parent) const
{
    BTracingNode *parentNode = nodeFromIndex(parent);
    
    if (!parentNode) return 0;
    return parentNode->Children.count();
}

int BTracingData::columnCount(const QModelIndex & /* parent */) const
{
    return 5;
}

QModelIndex BTracingData::parent(const QModelIndex &child) const
{
    BTracingNode *node = nodeFromIndex(child);
    if (!node) {
        return QModelIndex();
    }
    BTracingNode *parentNode = node->Parent;
    if (!parentNode) {
        return QModelIndex();
    }
    BTracingNode *grandParentNode = parentNode->Parent;
    if (!grandParentNode) {
        return QModelIndex();
    }
    
    int row = grandParentNode->Children.indexOf(parentNode);
    return createIndex(row, 0, parentNode);
}

QVariant BTracingData::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();
    
    BTracingNode *node = nodeFromIndex(index);
    if (!node)
        return QVariant();
    //dprintf("BTracingData::data column = %d\n", index.column());
    
    if (!isIncludedInLocalRegion(node))
        return QVariant();

    if (index.column() == 0) { // NodeNo
        //dprintf("BTracingData::data return NodeNo:%d\n", node->NodeNo);
        return node->NodeNo; 
    } else if (index.column() == 1) { // Point
        QString str = "("
            + QString::number(node->Point.x) + ", "
            + QString::number(node->Point.y) + ", "
            + QString::number(node->Point.z) + ")";
        return str;
    } else if (index.column() == 2) { // Diameter
        return node->Diam;
    } else if (index.column() == 3) { // ParentNo
        return node->ParentNo;
    } else if (index.column() == 4) { // ChildrenNo
        QString str = "";
        for (int i = 0; i < node->ChildrenNo.count(); i++) {
            if (i != 0) {
                str = str + ", ";
            }
            str = str + QString::number(node->ChildrenNo[i]);
        }
        return str;
    }
    return QVariant();
}

QVariant BTracingData::headerData(int section,
                                  Qt::Orientation orientation,
                                  int role) const
{
    // dprintf("BTracingData::headerData " \
    //         "called\n");
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        if (section == 0) {
            return tr("NodeNo");
        } else if (section == 1) {
            return tr("Point");
        } else if (section == 2) {
            return tr("Diameter");
        } else if (section == 3) {
            return tr("ParentNo");
        } else if (section == 4) {
            return tr("ChildrenNo");
        }
    }
    return QVariant();
}

QModelIndex BTracingData::selectByData(int column, QVariant data)
{
    switch (column) 
        {
        case 0:
            //int index;
            for (int i = 0; i < NodeList.count(); i++) {
                if (data.toInt() == NodeList[i].NodeNo) {
                    return index(i, 0);
                }
            }
            return QModelIndex();
        case 1:
            return QModelIndex();
        case 2:
            return QModelIndex();
        case 3:
            return QModelIndex();
        case 4:
            return QModelIndex();
        }
}

int BTracingData::insertNodeAsChildOf(const QModelIndex &parentIndex,
                                      double x, double y, double z, double diam)
{
    BTracingNode *parent;
    if (NodeList.count() != 0) {
        parent = nodeFromIndex(parentIndex);
    } else {
        parent = NULL;
        SAFEDELETE(RootNode);
        RootNode = new BTracingNode;
    }

    // dprintf("BTracingData::insertNodeAsChildOf " \
    //         "parent NodeNo = %d, " \
    //         "point (%f, %f, %f), " \
    //         "diam = %f\n",
    //         parent->NodeNo,
    //         parent->Point.x, parent->Point.y, parent->Point.z,
    //         parent->Diam);

    BTracingNode *newNode = new BTracingNode;
    newNode->NodeNo = NodeList.count();
    newNode->Point.x = x;
    newNode->Point.y = y;
    newNode->Point.z = z;
    newNode->Diam = diam;

    if (!parent || NodeList.count() == 0) {
        newNode->ParentNo = -1;
    } else {
        newNode->ParentNo = parent->NodeNo;
        parent->ChildrenNo.append(newNode->NodeNo);
    }

    newNode->Parent = RootNode;

    RootNode->Children.append(newNode);

    qSort(NodeList.begin(), NodeList.end(), sortNodeNoAscending);

    NodeList.append(*newNode);

    resetRootNode();

    reset();

    emit dataChanged(QModelIndex(), QModelIndex());
    return 0;
}

int BTracingData::removeNode(const QModelIndex &targetIndex)
{
    BTracingNode *targetNode = nodeFromIndex(targetIndex);
    return removeNode(targetNode);
}

int BTracingData::removeNode(BTracingNode *targetNode)
{
    int nodeNo = targetNode->NodeNo;

    if (nodeNo == 0) {
        return 1;
    }

    int parentNo = targetNode->ParentNo;
    BTracingNode *parentNode = &NodeList[parentNo];
    int childNum = targetNode->ChildrenNo.count();
    
    if (childNum >= 2) return -1;
    
    parentNode->ChildrenNo.removeOne(nodeNo);
    for (int i = 0; i < childNum; i++) { // now, childNum must be 1
        BTracingNode *curChildNode = &NodeList[targetNode->ChildrenNo[i]];
        int curChildNo = curChildNode->NodeNo;
        curChildNode->ParentNo = parentNo;
        parentNode->ChildrenNo.append(curChildNo);
    }
    
    NodeList.removeAt(nodeNo);
    for (int i = 0; i < NodeList.count(); i++) {
        BTracingNode *curNode = &NodeList[i];
        curNode->NodeNo = i;
        for (int j = 0; j < curNode->ChildrenNo.count(); j++) {
            int value = curNode->ChildrenNo[j];
            if (nodeNo < value) {
                curNode->ChildrenNo.replace(j, value - 1);
            }
        }
        if (nodeNo < curNode->ParentNo) {
            curNode->ParentNo -= 1;
        }
    }

    resetRootNode();
    reset();
    emit dataChanged(QModelIndex(), QModelIndex());
    return 0;
}

int BTracingData::removeSubbranch(const QModelIndex &targetIndex) {
    BTracingNode *startNode = nodeFromIndex(targetIndex);
    int startNodeNo = startNode->NodeNo;

    if (startNodeNo == 0) {
        return 1;
    }

    QList<int> removingNodeNoList;
    removingNodeNoList.push_back(startNodeNo);

    // list up the subbranch nodes => removingNodeNoList
    QList<BTracingNode *> curNodeList;
    curNodeList.append(startNode);
    while (curNodeList.count() != 0) {
        QList<BTracingNode *> nextNodeList;
        nextNodeList.clear();
        for (int i = 0; i < curNodeList.count(); i++) {
            BTracingNode *curNode = curNodeList[i];
            for (int j = 0; j < curNode->ChildrenNo.count(); j++) {
                int curChildNo = curNode->ChildrenNo[j];
                BTracingNode *curChildNode = &NodeList[curChildNo];
                nextNodeList.append(curChildNode);
                removingNodeNoList.append(curChildNo);
            }
        }
        curNodeList = nextNodeList;
    }

    int oldNodeListNum = NodeList.count();

    int removingNum = removingNodeNoList.count();
    
    // sort in descending
    qStableSort(removingNodeNoList.begin(), removingNodeNoList.end(), qGreater<int>());
    
    for (int i = 0; i < removingNum; i++) {
        int curNodeNo = removingNodeNoList.takeFirst();
        NodeList.removeAt(curNodeNo);
    }

    int newNodeListNum = NodeList.count();

    // remapping table, input : oldNo -> output : newNo
    int *numberRemapingList = new int[oldNodeListNum];

    // initialize all elements with -1
    for (int i = 0; i < oldNodeListNum; i++) {
        numberRemapingList[i] = -1;
    }

    for (int i = 0; i < newNodeListNum; i++) {
        BTracingNode *curNode = &NodeList[i];
        int curNodeNo = curNode->NodeNo;
        numberRemapingList[curNodeNo] = i;
    }

    for (int i = 0; i < newNodeListNum; i++) {
        BTracingNode *curNode = &NodeList[i];
        curNode->NodeNo = numberRemapingList[curNode->NodeNo];
        curNode->ParentNo = numberRemapingList[curNode->ParentNo];
        QList<int> newChildrenNo;
        QList<int> *curChildrenNoList = &(curNode->ChildrenNo);
        for (int j = 0; j < curChildrenNoList->count(); j++) {
            int curChildNo = (*curChildrenNoList)[j];
            int newChildNo = numberRemapingList[curChildNo];
            if (newChildNo < 0) continue;
            newChildrenNo.append(newChildNo);
        }
        *curChildrenNoList = newChildrenNo;
    }

    resetRootNode();
    reset();

    emit dataChanged(QModelIndex(), QModelIndex());
    ASAFEDELETE(numberRemapingList);
    return 0;
}

void BTracingData::sort(int column, Qt::SortOrder order)
{
    // dprintf("BTracingData::sort called\n");
    // dprintf("BTracingData::sort column = %d\n", column);
    dprintf("BTracingData::sort " \
            "column = %d, " \
            "order = %d, " \
            "count = %d\n",
            column,
            order,
            NodeList.count());
    if (RootNode == NULL) return;
    // int nodeNum = NodeList.count();
    // if (nodeNum != 0) {
    //     dprintf("BTracingData::sort " \
    //             "LastNode Point (%f, %f, %f), Diam = %f \n",
    //             NodeList[nodeNum - 1].Point.x,
    //             NodeList[nodeNum - 1].Point.y,
    //             NodeList[nodeNum - 1].Point.z,
    //             NodeList[nodeNum - 1].Diam);
    // }
    switch (column) 
        {
        case 0: // NodeNo
            if (order == Qt::AscendingOrder) {
                qSort(NodeList.begin(), NodeList.end(), sortNodeNoAscending);
            } else if (order == Qt::DescendingOrder) {
                qSort(NodeList.begin(), NodeList.end(), sortNodeNoDescending);
            }
            break;
        case 1: // Point
            if (order == Qt::AscendingOrder) {
                qSort(NodeList.begin(), NodeList.end(), sortPointZAscending);
            } else if (order == Qt::DescendingOrder) {
                qSort(NodeList.begin(), NodeList.end(), sortPointZDescending);
            }
            break;
        case 2: // Diameter
            if (order == Qt::AscendingOrder) {
                qSort(NodeList.begin(), NodeList.end(), sortDiameterAscending);
            } else if (order == Qt::DescendingOrder) {
                qSort(NodeList.begin(), NodeList.end(), sortDiameterDescending);
            }
            break;
        case 3: // ParentNo
            if (order == Qt::AscendingOrder) {
                qSort(NodeList.begin(), NodeList.end(), sortParentNoAscending);
            } else if (order == Qt::DescendingOrder) {
                qSort(NodeList.begin(), NodeList.end(), sortParentNoDescending);
            }
            break;
        case 4: // ChildrenNo
            if (order == Qt::AscendingOrder) {
                qSort(NodeList.begin(), NodeList.end(), sortChildrenNoAscending);
            } else if (order == Qt::DescendingOrder) {
                qSort(NodeList.begin(), NodeList.end(), sortChildrenNoDescending);
            }
            break;
    }
    resetRootNode();
    reset();
}

void BTracingData::setLocalRegion(double fromx, double tox,
                                  double fromy, double toy,
                                  double fromz, double toz)
{
    SAFEDELETE(LocalRegion);
    LocalRegion = new LOCAL_REGION();
    LocalRegion->from.x = fromx;
    LocalRegion->from.y = fromy;
    LocalRegion->from.z = fromz;
    LocalRegion->to.x = tox;
    LocalRegion->to.y = toy;
    LocalRegion->to.z = toz;
}

void BTracingData::clearLocalRegion()
{
    SAFEDELETE(LocalRegion);
}

QModelIndex BTracingData::searchNextBranchingPoint(QModelIndex &currentIndex)
{
    BTracingNode *currentNode = nodeFromIndex(currentIndex);

    dprintf("BTracingData::searchNextBranchingPoint " \
            "start %d, (%f, %f, %f), Diam=  %f\n",
            currentNode->NodeNo,
            currentNode->Point.x, currentNode->Point.y, currentNode->Point.z,
            currentNode->Diam);

    while (1) {
        if (currentNode->ChildrenNo.count() == 0
            || currentNode->ChildrenNo.count() >= 2) {
            break;
            }
        currentNode = &NodeList[currentNode->ChildrenNo[0]];
    }

    dprintf("BTracingData::searchNextBranchingPoint " \
            "start %d, (%f, %f, %f), Diam=  %f\n",
            currentNode->NodeNo,
            currentNode->Point.x, currentNode->Point.y, currentNode->Point.z,
            currentNode->Diam);

    return selectByData(0, currentNode->NodeNo);
}

QModelIndex BTracingData::searchPrevBranchingPoint(QModelIndex &currentIndex)
{
    BTracingNode *currentNode = nodeFromIndex(currentIndex);

    dprintf("BTracingData::searchPrevBranchingPoint " \
            "start %d, (%f, %f, %f), Diam=  %f\n",
            currentNode->NodeNo,
            currentNode->Point.x, currentNode->Point.y, currentNode->Point.z,
            currentNode->Diam);

    qSort(NodeList.begin(), NodeList.end(), sortNodeNoAscending);

    if (!(currentNode->ChildrenNo.count() < 2
          || currentNode->ParentNo <= 0)) {
        currentNode = &NodeList[currentNode->ParentNo];
    }
    while (1) {
        if (currentNode->ParentNo <= 0
            || currentNode->ChildrenNo.count() >= 2) {
            break;
        }
        currentNode = &NodeList[currentNode->ParentNo];
    }

    dprintf("BTracingData::searchPrevBranchingPoint " \
            "start %d, (%f, %f, %f), Diam=  %f\n",
            currentNode->NodeNo,
            currentNode->Point.x, currentNode->Point.y, currentNode->Point.z,
            currentNode->Diam);

    return selectByData(0, currentNode->NodeNo);
}

void BTracingData::resetRootNode()
{
    /**/
    // RootNode->Children must be repositioned as same order as the sorted list because
    // the order in TableView reflects the sequence of RootNode->Children.

    RootNode->Children.clear();

    // QList<BTracingNode> nodeList = NodeList;
    // delete RootNode;
    // NodeList = nodeList;
    // RootNode = new BTracingNode;

    for (int i = 0; i < NodeList.count(); i++) {
        // dprintf("BTracingData::sort [%d/%d]\n", i, NodeList.count());
        NodeList[i].Parent = RootNode;
        RootNode->Children.append(&NodeList[i]);
    }
    /**/
}
