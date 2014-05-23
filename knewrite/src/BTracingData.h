#ifndef ___B_TARCING_DATA_H___
#define ___B_TARCING_DATA_H___

#include <QAbstractItemModel>

#include "BTracingNode.h"

class BTracingData : public QAbstractItemModel
{
 public:
    BTracingData(QObject *parent = 0);
    ~BTracingData();

    void setNodeList(QList<BTracingNode> *nodeList);
    
    QList<BTracingNode> *getNodeList();
    QList<BTracingNode> getSubbranch(const QModelIndex &startIndex);

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &child) const;

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role) const;
    QModelIndex selectByData(int column, QVariant data);//return row

 public: // original
    int insertNodeAsChildOf(const QModelIndex &parent,
                            double x, double y, double z, double diam);
    int removeNode(const QModelIndex &targetIndex);
    int removeSubbranch(const QModelIndex &targetIndex);
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
    void setLocalRegion(double fromx, double tox,
                        double fromy, double toy,
                        double fromz, double toz);
    void clearLocalRegion();
    QModelIndex searchNextBranchingPoint(QModelIndex &currentIndex);
    QModelIndex searchPrevBranchingPoint(QModelIndex &currentIndex);
    /* QModelIndex getIndexFromNode(BTracingNode *node); */
 private:
    int removeNode(BTracingNode *targetNode);

 protected:
    void resetRootNode();

 private:
    BTracingNode *nodeFromIndex(const QModelIndex &index) const;
    bool isIncludedInLocalRegion(BTracingNode *node) const;
    BTracingNode *RootNode;
    QList<BTracingNode> NodeList;
    typedef struct {
        struct {
            double x;
            double y;
            double z;
        } from;
        struct {
            double x;
            double y;
            double z;
        } to;
    } LOCAL_REGION;
    LOCAL_REGION *LocalRegion;
};

#endif//___M_TRACING_DATA_H___
