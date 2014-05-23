#ifndef ___V_SHAPE_VIEW_GL_H___
#define ___V_SHAPE_VIEW_GL_H___

#include <QtOpenGL/QGLWidget>
#include <QList>
#include <QVector3D>
#include <QVector4D>
#include <QMutex>
#include <QColor>

#include "CObjectCommunicator.h"
#include "CObjectCommunicatorID.h"

#include "BRodriguez2009Cluster.h"
#include "BTracingNode.h"

#include "BRegion3D.h"

#include "BGlobalDefinitions.h"

//#define MAX_DRAWING_POINT_NUM_STACKIMAGE (2 << 18)

class VShapeViewGL : public QGLWidget, public BTerminal
{
    Q_OBJECT

 public:
    VShapeViewGL(QWidget *parent = 0);

 public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    
 signals:
    void xRotationChanged(int angle);
    void yRotationChanged(int angle);
    void zRotationChanged(int angle);

 protected:
    // OpenGL
    void initializeGL();
    void paintGL();
    void display();
    void resizeGL(int width, int height);
    void setOrtho();
    void setObservingPoint();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);
     
 protected:
    //void setData(RodClusterList *extractedData);
    void setBoundingBox();
    void sendCurrentRotation();
    void procedure(int ID, char *data, int byte);

     
 protected:

    enum VIEWMODE {
        VIEWMODE_ORTHOGONAL = 0,
        VIEWMODE_PERSPECTIVE,
    };

    // ortho or perspective
    VIEWMODE ViewMode;

    //--------------------------------------------------------------------------
    // stackimage data
    int CurrentDataNo;
    typedef struct _STACKIMAGEDATA_FORMAT {
        unsigned char *ptr;
        QList<QVector4D> pointList;
        unsigned char threshold;
        int dataNo;
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
        struct {
            RANGE_INT x;
            RANGE_INT y;
            RANGE_INT z;
        } ROI;
        REGION3DARRAY *ptrLCR;
        bool isLCRon;
        bool on;
        //QColor color;
        bool alphaMode;
        struct {
            int r;
            int g;
            int b;
        } color;
    } STACKIMAGEDATA_FORMAT; 
    STACKIMAGEDATA_FORMAT StackImageData[MAX_STACK_IMAGE_NUM];

    struct {
        QVector3D max;
        QVector3D min;
        QVector3D mean;
    } BoundingBox;

    // pointer
    QVector3D PointerStackImage;
    bool PointerOnStackImage;

    //--------------------------------------------------------------------------
    // extracted data
    typedef struct _EXTRACTEDDATA_FORMAT {
        RodClusterList data;
        unsigned int maxDist;
        struct {
            int x;
            int y;
            int z;
        } translate;
        bool on;
        int selectedNodeNo;
    } EXTRACTEDDATA_FORMAT;
    EXTRACTEDDATA_FORMAT ExtractedData[MAX_EXTRACTED_DATA_NUM];

    // pointer
    QVector3D PointerExtractedData;
    bool PointerOnExtractedData;

    //--------------------------------------------------------------------------
    // current view region
    struct {
        double x;
        double y;
        double z;
        double l;
    } curViewRegion;

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
        BTracingNode curNode;
        bool isCurNodeOn;
    } TracingNodeData;

    //--------------------------------------------------------------------------
    // rotation
    QPoint lastPos;
    int RotX;
    int RotY;
    int RotZ;

    //--------------------------------------------------------------------------
    // perspective ! unimplemented
    struct {
        QVector3D point;
        QVector3D lookat;
        QVector3D upper;
    } ObservingPoint;

    // mutex
    QMutex mutex;

 /* signals: */
 /*    void closed(); */

 /* protected: */
 /*    virtual void hideEvent(QHideEvent* /\* event *\/) { emit closed(); } */
};

#endif//___V_SHAPE_VIEW_H___
