#ifndef ___V_HANDTRACE_ORTHO_VIEW_H___
#define ___V_HANDTRACE_ORTHO_VIEW_H___

#include <QWidget>
#include <QVector3D>
#include <QVector4D>

#include "CObjectCommunicator.h"

#include "BTracingNode.h"

class VHandTraceOrthoView : public QWidget, public BTerminal
{
    Q_OBJECT

 public:
    VHandTraceOrthoView(QWidget *parent = 0);

 protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);
    void resetImage();
    void procedure(int ID, char *data, int byte);

    struct {
        bool shift;
        bool control;
        bool alt;
    } Modifiers;

 protected:
    typedef struct _STACKIMAGEDATA_FORMAT {
        unsigned char *ptr;
        QList<QVector4D> pointList;
        unsigned char threshold;
        //int dataNo;
        struct {
            int x;
            int y;
            int z;
        } size;
        /*
        struct {
            int x;
            int y;
            int z;
        } translate;
        */
        struct {
            double x;
            double y;
            double z;
        } scale;
        //bool on;
    } STACKIMAGEDATA_FORMAT;
    STACKIMAGEDATA_FORMAT StackImageData;

    struct {
        int x;
        int y;
        int z;
    } PointerStackImage;
    
    QImage *imageXY;
    QImage *imageXZ;
    QImage *imageZY;
    QImage *imageZZ;

    //--------------------------------------------------------------------------
    // node list
    struct _TRACINGNODE_FORMAT {
        QList<BTracingNode> NodeList;
        struct {
           double x;
           double y;
           double z;
        } scale;
        bool on;
        bool subbranchMode;
        BTracingNode curNode;
        bool isCurNodeOn;
    } TracingNodeData;

    typedef struct _NODE2DRAW {
        int no;
        struct {
            double x;
            double y;
        } point;
        double rx;
        double ry;
    } NODE2DRAW;
    QList<NODE2DRAW> NodeList2Draw;

    //--------------------------------------------------------------------------
    // selected plane
    enum EnumSelectedPlane {
        SELECTEDPLANE_XY = 0,
        SELECTEDPLANE_XZ,
        SELECTEDPLANE_ZY,
        SELECTEDPLANE_NUM,
    };
    EnumSelectedPlane SelectedPlane;

 /* signals: */
 /*    void closed(); */

 /* protected: */
 /*    virtual void hideEvent(QHideEvent* /\* event *\/) { emit closed(); } */
};

#endif//___V_HANDTRACE_ORTHO_VIEW_H___
