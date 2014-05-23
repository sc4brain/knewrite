#ifndef ___B_TRACING_NODE_H___
#define ___B_TRACING_NODE_H___

#include <QList>

typedef struct _NODEPOINT {
    double x;
    double y;
    double z;
} NODEPOINT;

class BTracingNode {
 public:
    BTracingNode();
    BTracingNode(BTracingNode *parent, double x, double y, double z);
    ~BTracingNode();

    BTracingNode& operator=(const BTracingNode node);

    /* int getNodeNo() { return NodeNo; } */
    /* double getPointX() { return Point.x; } */
    /* double getPointY() { return Point.y; } */
    /* double getPointZ() { return Point.z; } */
    /* BTracingNode *getParent() { return Parent; } */
    /* BTracingNode *getChild(int i) { return Children.value(i); } */

    /* void setNodeNo(int nodeNo) { NodeNo = nodeNo; } */
    /* void setPoint(double x, double y, double z) { */
    /*     Point.x = x; */
    /*     Point.y = y; */
    /*     Point.z = z; */
    /* } */
    /* void setParent(BTracingNode *parent) { Parent = parent; } */
    /* void appendChild(BTracingNode *child) { Children.append(child); } */

    //protected:
    int NodeNo;
    NODEPOINT Point;
    double Diam;

    int ParentNo;
    QList<int> ChildrenNo;

    // 
    BTracingNode *Parent;
    QList<BTracingNode *> Children;
};

bool sortNodeNoAscending(const BTracingNode &node1, const BTracingNode &node2);
bool sortNodeNoDescending(const BTracingNode &node1, const BTracingNode &node2);
bool sortPointXAscending(const BTracingNode &node1, const BTracingNode &node2);
bool sortPointXDescending(const BTracingNode &node1, const BTracingNode &node2);
bool sortPointYAscending(const BTracingNode &node1, const BTracingNode &node2);
bool sortPointYDescending(const BTracingNode &node1, const BTracingNode &node2);
bool sortPointZAscending(const BTracingNode &node1, const BTracingNode &node2);
bool sortPointZDescending(const BTracingNode &node1, const BTracingNode &node2);
bool sortDiameterAscending(const BTracingNode &node1, const BTracingNode &node2);
bool sortDiameterDescending(const BTracingNode &node1, const BTracingNode &node2);
bool sortParentNoAscending(const BTracingNode &node1, const BTracingNode &node2);
bool sortParentNoDescending(const BTracingNode &node1, const BTracingNode &node2);
bool sortChildrenNoAscending(const BTracingNode &node1, const BTracingNode &node2);
bool sortChildrenNoDescending(const BTracingNode &node1, const BTracingNode &node2);

bool sortPointerNodeNoAscending(const BTracingNode *node1, const BTracingNode *node2);
bool sortPointerNodeNoDescending(const BTracingNode *node1, const BTracingNode *node2);
bool sortPointerPointXAscending(const BTracingNode *node1, const BTracingNode *node2);
bool sortPointerPointXDescending(const BTracingNode *node1, const BTracingNode *node2);
bool sortPointerPointYAscending(const BTracingNode *node1, const BTracingNode *node2);
bool sortPointerPointYDescending(const BTracingNode *node1, const BTracingNode *node2);
bool sortPointerPointZAscending(const BTracingNode *node1, const BTracingNode *node2);
bool sortPointerPointZDescending(const BTracingNode *node1, const BTracingNode *node2);
bool sortPointerDiameterAscending(const BTracingNode *node1, const BTracingNode *node2);
bool sortPointerDiameterDescending(const BTracingNode *node1, const BTracingNode *node2);
bool sortPointerParentNoAscending(const BTracingNode *node1, const BTracingNode *node2);
bool sortPointerParentNoDescending(const BTracingNode *node1, const BTracingNode *node2);
bool sortPointerChildrenNoAscending(const BTracingNode *node1, const BTracingNode *node2);
bool sortPointerChildrenNoDescending(const BTracingNode *node1, const BTracingNode *node2);

#endif//___B_HAND_TRACE_NODE_H___
