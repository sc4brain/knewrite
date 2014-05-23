
#include "BTracingNode.h"

#include "BCommon.h"

BTracingNode::BTracingNode()
{
    NodeNo = 0;
    Point.x = 0.;
    Point.y = 0.;
    Point.z = 0.;
    Diam = 0.;

    ParentNo = 0;

    Parent = NULL;
}

BTracingNode::BTracingNode(BTracingNode *parent, double x, double y, double z)
{
    Parent = parent;
    Parent->Children.append(this);
    //NodeNo = nodeNo;
    Point.x = x;
    Point.y = y;
    Point.z = z;
}

BTracingNode::~BTracingNode()
{
    ChildrenNo.clear();
    // for (int i = 0; i < Children.size(); i++) {
    //     SAFEDELETE(Children[i]);
    // }
    //qDeleteAll(Children);
    //Children.clear();
}

BTracingNode& BTracingNode::operator=(const BTracingNode node)
{
    NodeNo = node.NodeNo;
    Point.x = node.Point.x;
    Point.y = node.Point.y;
    Point.z = node.Point.z;
    Diam = node.Diam;
    ParentNo = node.ParentNo;
    ChildrenNo = node.ChildrenNo;
    Parent = node.Parent;
    Children = node.Children;
    return *this;
}

bool sortNodeNoAscending(const BTracingNode &node1, const BTracingNode &node2)
{
    return node1.NodeNo < node2.NodeNo;
}

bool sortNodeNoDescending(const BTracingNode &node1, const BTracingNode &node2)
{
    return node1.NodeNo > node2.NodeNo;
}

bool sortPointXAscending(const BTracingNode &node1, const BTracingNode &node2)
{
    return node1.Point.x < node2.Point.x;
}

bool sortPointXDescending(const BTracingNode &node1, const BTracingNode &node2)
{
    return node1.Point.x > node2.Point.x;
}

bool sortPointYAscending(const BTracingNode &node1, const BTracingNode &node2)
{
    return node1.Point.y < node2.Point.y;
}

bool sortPointYDescending(const BTracingNode &node1, const BTracingNode &node2)
{
    return node1.Point.y > node2.Point.y;
}

bool sortPointZAscending(const BTracingNode &node1, const BTracingNode &node2)
{
    return node1.Point.z < node2.Point.z;
}

bool sortPointZDescending(const BTracingNode &node1, const BTracingNode &node2)
{
    return node1.Point.z > node2.Point.z;
}

bool sortDiameterAscending(const BTracingNode &node1, const BTracingNode &node2)
{
    return node1.Diam < node2.Diam;
}

bool sortDiameterDescending(const BTracingNode &node1, const BTracingNode &node2)
{
    return node1.Diam > node2.Diam;
}

bool sortParentNoAscending(const BTracingNode &node1, const BTracingNode &node2)
{
    return node1.ParentNo < node2.ParentNo;
}

bool sortParentNoDescending(const BTracingNode &node1, const BTracingNode &node2)
{
    return node1.ParentNo > node2.ParentNo;
}

bool sortChildrenNoAscending(const BTracingNode &node1, const BTracingNode &node2)
{
    int childNo1 = -1;
    if (node1.ChildrenNo.count()) {
        childNo1 = node1.ChildrenNo[0];
    }
    int childNo2 = -1;
    if (node1.ChildrenNo.count()) {
        childNo2 = node2.ChildrenNo[0];
    }
    return childNo1 < childNo2;
}

bool sortChildrenNoDescending(const BTracingNode &node1, const BTracingNode &node2)
{
    int childNo1 = -1;
    if (node1.ChildrenNo.count()) {
        childNo1 = node1.ChildrenNo[0];
    }
    int childNo2 = -1;
    if (node1.ChildrenNo.count()) {
        childNo2 = node2.ChildrenNo[0];
    }
    return childNo1 > childNo2;
}



bool sortPointerNodeNoAscending(const BTracingNode *node1, const BTracingNode *node2)
{
    return node1->NodeNo < node2->NodeNo;
}

bool sortPointerNodeNoDescending(const BTracingNode *node1, const BTracingNode *node2)
{
    return node1->NodeNo > node2->NodeNo;
}

bool sortPointerPointXAscending(const BTracingNode *node1, const BTracingNode *node2)
{
    return node1->Point.x < node2->Point.x;
}

bool sortPointerPointXDescending(const BTracingNode *node1, const BTracingNode *node2)
{
    return node1->Point.x > node2->Point.x;
}

bool sortPointerPointYAscending(const BTracingNode *node1, const BTracingNode *node2)
{
    return node1->Point.y < node2->Point.y;
}

bool sortPointerPointYDescending(const BTracingNode *node1, const BTracingNode *node2)
{
    return node1->Point.y > node2->Point.y;
}

bool sortPointerPointZAscending(const BTracingNode *node1, const BTracingNode *node2)
{
    return node1->Point.z < node2->Point.z;
}

bool sortPointerPointZDescending(const BTracingNode *node1, const BTracingNode *node2)
{
    return node1->Point.z > node2->Point.z;
}

bool sortPointerDiameterAscending(const BTracingNode *node1, const BTracingNode *node2)
{
    return node1->Diam < node2->Diam;
}

bool sortPointerDiameterDescending(const BTracingNode *node1, const BTracingNode *node2)
{
    return node1->Diam > node2->Diam;
}

bool sortPointerParentNoAscending(const BTracingNode *node1, const BTracingNode *node2)
{
    return node1->ParentNo < node2->ParentNo;
}

bool sortPointerParentNoDescending(const BTracingNode *node1, const BTracingNode *node2)
{
    return node1->ParentNo > node2->ParentNo;
}

bool sortPointerChildrenNoAscending(const BTracingNode *node1, const BTracingNode *node2)
{
    int childNo1 = -1;
    if (node1->ChildrenNo.count()) {
        childNo1 = node1->ChildrenNo[0];
    }
    int childNo2 = -1;
    if (node1->ChildrenNo.count()) {
        childNo2 = node2->ChildrenNo[0];
    }
    return childNo1 < childNo2;
}

bool sortPointerChildrenNoDescending(const BTracingNode *node1, const BTracingNode *node2)
{
    int childNo1 = -1;
    if (node1->ChildrenNo.count()) {
        childNo1 = node1->ChildrenNo[0];
    }
    int childNo2 = -1;
    if (node1->ChildrenNo.count()) {
        childNo2 = node2->ChildrenNo[0];
    }
    return childNo1 > childNo2;
}

