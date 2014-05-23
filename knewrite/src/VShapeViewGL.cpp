
#include <QtGui>
#include <QtOpenGL/QGLWidget>
#include <math.h>
#include "VShapeViewGL.h"

#include "CObjectCommunicatorID.h"
#include "BCommon.h"

#define ANGLE_DIV_NUM 16

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * ANGLE_DIV_NUM;
    while (angle > 360 * ANGLE_DIV_NUM)
        angle -= 360 * ANGLE_DIV_NUM;
}

VShapeViewGL::VShapeViewGL(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    //ViewMode = VIEWMODE_PERSPECTIVE;
    ViewMode = VIEWMODE_ORTHOGONAL;

    for (int i = 0; i < MAX_STACK_IMAGE_NUM; i++) {
        StackImageData[i].ptr = NULL;
        StackImageData[i].threshold = DEFAULT_STACKIMAGE_THRESHOLD;
        StackImageData[i].dataNo = 0;
        StackImageData[i].size.x = 0;
        StackImageData[i].size.y = 0;
        StackImageData[i].size.z = 0;
        StackImageData[i].translate.x = 0;
        StackImageData[i].translate.y = 0;
        StackImageData[i].translate.z = 0;
        StackImageData[i].scale.x = 0.;
        StackImageData[i].scale.y = 0.;
        StackImageData[i].scale.z = 0.;
        StackImageData[i].isLCRon = false;
        StackImageData[i].on = false;
        //StackImageData[i].color = QColor(1., 1., 1.);
        StackImageData[i].color.r = 1.;
        StackImageData[i].color.g = 1.;
        StackImageData[i].color.b = 1.;
    }

    PointerStackImage = QVector3D(0, 0, 0);
    PointerOnStackImage = false;

    for (int i = 0; i < MAX_EXTRACTED_DATA_NUM; i++) {
        ExtractedData[i].maxDist = 0;
        ExtractedData[i].on = false;
    }

    PointerExtractedData = QVector3D(0, 0, 0);
    PointerOnExtractedData = false;

    BoundingBox.max = QVector3D(0, 0, 0);
    BoundingBox.min = QVector3D(0, 0, 0);

    RotX = RotY = RotZ = 0;

    ObservingPoint.point = QVector3D(0, 0, 0);
    ObservingPoint.lookat = QVector3D(0, 0, 0);


    setFocusPolicy(Qt::ClickFocus);
}


void VShapeViewGL::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != RotX) {
        RotX = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void VShapeViewGL::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != RotY) {
        RotY = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void VShapeViewGL::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != RotZ) {
        RotZ = angle;
        emit xRotationChanged(angle);
        updateGL();
    }
}

void VShapeViewGL::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);

    // glEnable(GL_LIGHTING);
    // glEnable(GL_LIGHT0);
    // glEnable(GL_MULTISAMPLE);
    // static GLfloat lightPosition[4] = { 0., 0., 300.0, 1.0 };
    // glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

    glClearColor(0.1, 0.1, 0.1, 0);
}

void VShapeViewGL::paintGL()
{
    static int count = 0;
    printf("paintGL [%4d] ROT(%d, %d, %d)\r", count++, RotX, RotY, RotZ);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    //glTranslatef(0.0, 0.0, 0.0);
    this->display();
}

void VShapeViewGL::display()
{
    double centerx = BoundingBox.mean.x();
    double centery = BoundingBox.mean.y();
    double centerz = BoundingBox.mean.z();

    if (ViewMode == VIEWMODE_ORTHOGONAL) {
        glTranslatef(centerx,
                     centery,
                     centerz);

        glRotatef(RotX / ANGLE_DIV_NUM, 1.0, 0.0, 0.0);
        glRotatef(RotY / ANGLE_DIV_NUM, 0.0, 1.0, 0.0);
        glRotatef(RotZ / ANGLE_DIV_NUM, 0.0, 0.0, 1.0);

        glTranslatef(-centerx,
                     -centery,
                     -centerz);
    }

    double maxx = BoundingBox.max.x();
    double maxy = BoundingBox.max.y();
    double maxz = BoundingBox.max.z();
    double minx = BoundingBox.min.x();
    double miny = BoundingBox.min.y();
    double minz = BoundingBox.min.z();

    double intensity = 1.;
    
    //--------------------------------------------------------------------------
    // draw axis
    //--------------------------------------------------------------------------

    intensity = 1.;
    glColor3d(intensity, intensity, intensity);

    QVector3D origin(0., 0., 0.);
    glLineWidth(1.);
    glBegin(GL_LINES);
    glColor3d(intensity, intensity, intensity);

    // x : red
    glColor3d(0x63 / 255., 0x26 / 255., 0x26 / 255.);
    glVertex3d(minx,
               origin.y(),
               origin.z());
    glVertex3d(maxx,
               origin.y(),
               origin.z());

    // y : green
    glColor3d(0x4A / 255., 0x58 / 255., 0x00 / 255.);
    glVertex3d(origin.x(),
               miny,
               origin.z());
    glVertex3d(origin.x(),
               maxy,
               origin.z());

    // z : blue
    glColor3d(0x1E / 255., 0x37 / 255., 0x86 / 255.);
    glVertex3d(origin.x(),
               origin.y(),
               minz);
    glVertex3d(origin.x(),
               origin.y(),
               maxz);
    glEnd();
    glLineWidth(1.);

    //--------------------------------------------------------------------------
    // draw bounding box
    //--------------------------------------------------------------------------
    intensity = 0.4;
    glColor3d(intensity, intensity, intensity);

    glBegin(GL_LINE_LOOP);
    glVertex3d(minx, miny, minz);
    glVertex3d(maxx, miny, minz);
    glVertex3d(maxx, maxy, minz);
    glVertex3d(minx, maxy, minz);
    glEnd();
    
    glBegin(GL_LINE_LOOP);
    glVertex3d(minx, miny, maxz);
    glVertex3d(maxx, miny, maxz);
    glVertex3d(maxx, maxy, maxz);
    glVertex3d(minx, maxy, maxz);
    glEnd();

    glBegin(GL_LINES);
    glVertex3d(minx, miny, minz);
    glVertex3d(minx, miny, maxz);
    glVertex3d(maxx, miny, minz);
    glVertex3d(maxx, miny, maxz);
    glVertex3d(maxx, maxy, minz);
    glVertex3d(maxx, maxy, maxz);
    glVertex3d(minx, maxy, minz);
    glVertex3d(minx, maxy, maxz);
    glEnd();


    //--------------------------------------------------------------------------
    // draw scale bar
    //--------------------------------------------------------------------------

    intensity = 1.;
    glColor3d(intensity, intensity, intensity);

    double scaleBarSize = 50; // um
    // QVector3D scaleBarOrigin(BoundingBox.min.x() + scaleBarSize * 1.1,
    //                          BoundingBox.min.y() + scaleBarSize * 1.1,
    //                          BoundingBox.min.z() + scaleBarSize * 1.1);
    QVector3D scaleBarOrigin(scaleBarSize * 1.1,
                             scaleBarSize * 1.1,
                             scaleBarSize * 1.1);
    glLineWidth(2.);
    glBegin(GL_LINES);
    glColor3d(intensity, intensity, intensity);

    // x : red
    glColor3d(0x63 / 255., 0x26 / 255., 0x26 / 255.);
    glVertex3d(scaleBarOrigin.x(),
               scaleBarOrigin.y(),
               scaleBarOrigin.z());
    glVertex3d(scaleBarOrigin.x() + scaleBarSize,
               scaleBarOrigin.y(),
               scaleBarOrigin.z());

    // y : green
    glColor3d(0x4A / 255., 0x58 / 255., 0x00 / 255.);
    glVertex3d(scaleBarOrigin.x(),
               scaleBarOrigin.y(),
               scaleBarOrigin.z());
    glVertex3d(scaleBarOrigin.x(),
               scaleBarOrigin.y() + scaleBarSize,
               scaleBarOrigin.z());

    // z : blue
    glColor3d(0x1E / 255., 0x37 / 255., 0x86 / 255.);
    glVertex3d(scaleBarOrigin.x(),
               scaleBarOrigin.y(),
               scaleBarOrigin.z());
    glVertex3d(scaleBarOrigin.x(),
               scaleBarOrigin.y(),
               scaleBarOrigin.z() + scaleBarSize);
    glEnd();
    glLineWidth(1.);


    //--------------------------------------------------------------------------
    // draw pointer
    //--------------------------------------------------------------------------

    if (PointerOnStackImage == true) {
        glBegin(GL_LINES);
        
        // x : red
        glColor3d(0x63 / 255., 0x26 / 255., 0x26 / 255.);
        glVertex3d(0,
                   PointerStackImage.y(),
                   PointerStackImage.z());
        glVertex3d(BoundingBox.max.x(),
                   PointerStackImage.y(),
                   PointerStackImage.z());

        // y : green
        glColor3d(0x4A / 255., 0x58 / 255., 0x00 / 255.);
        glVertex3d(PointerStackImage.x(),
                   0,
                   PointerStackImage.z());
        glVertex3d(PointerStackImage.x(),
                   BoundingBox.max.y(),
                   PointerStackImage.z());

        // z : blue
        glColor3d(0x1E / 255., 0x37 / 255., 0x86 / 255.);
        glVertex3d(PointerStackImage.x(),
                   PointerStackImage.y(),
                   0);
        glVertex3d(PointerStackImage.x(),
                   PointerStackImage.y(),
                   BoundingBox.max.z());
        glEnd();
    }


    //--------------------------------------------------------------------------
    // draw stack data
    //--------------------------------------------------------------------------

    // for (int i = 0; i < MAX_STACK_IMAGE_NUM; i++) {
    //     STACKIMAGEDATA_FORMAT *curImage = StackImageData + i;
    //     int pageStep = curImage->size.x * curImage->size.y;
    //     int lineStep = curImage->size.x;
    //     if (curImage->ptr == NULL) continue;
    //     int length = pageStep * curImage->size.z;
    //     for (int j = 0; j < length; j++) {
    //         unsigned char value = curImage->ptr[j];
    //         glPointSize(value / 256.);
    //         int z = j / pageStep;
    //         int r = j % pageStep;
    //         int y = r / lineStep;
    //         int x = r % lineStep;
    //         glVertex3d(x, y, z);
    //     }
    // }

    glPointSize(1.);
    for (int i = 0; i < MAX_STACK_IMAGE_NUM; i++) {

        STACKIMAGEDATA_FORMAT *curImage = StackImageData + i;
        if (curImage->on == false) continue;

        double scalex = curImage->scale.x;
        double scaley = curImage->scale.y;
        double scalez = curImage->scale.z;

        //----------------------------------------------------------------------
        // stack image data
        //----------------------------------------------------------------------
        glLineWidth(1.);
        glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_DST_ALPHA);
        glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
        glBegin(GL_POINTS);
        glPointSize(1.);
        
        if (curImage->alphaMode) {
            for (int j = 0; j < curImage->pointList.length(); j++) {
                QVector4D vector = curImage->pointList.value(j);
                //intensity = vector.w();
                //intensity = 1.;
                //glColor4f(intensity, intensity, intensity, vector.w());
                double r = curImage->color.r / 255.;
                double g = curImage->color.g / 255.;
                double b = curImage->color.b / 255.;
                glColor4f(r, g, b, vector.w());

                glVertex3d(vector.x(), vector.y(), vector.z());
            }
        } else {
            for (int j = 0; j < curImage->pointList.length(); j++) {
                QVector4D vector = curImage->pointList.value(j);
                // intensity = 1.;
                // glColor3d(intensity, intensity, intensity);
                //glPointSize(vector.w());
                double r = curImage->color.r / 255.;
                double g = curImage->color.g / 255.;
                double b = curImage->color.b / 255.;
                //glColor4f(r, g, b, vector.w());
                glColor4f(r, g, b, 1.);
                glVertex3d(vector.x(), vector.y(), vector.z());
            }
        }
        glEnd();
        glDisable(GL_BLEND);
        // draw stack data end
        //----------------------------------------------------------------------


        //----------------------------------------------------------------------
        // contrast view
        //----------------------------------------------------------------------

        if (curImage->isLCRon == false) continue;
        
        if (1 || curImage->alphaMode) {
            glEnable(GL_BLEND);
            //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//GL_DST_ALPHA);
            glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
        }

        // calc. normalizing coef.
        double maxCV = 0;
        //double meanCV = 0.;
        //int countCV = 0;
        for (int j = 0; j < curImage->ptrLCR->getRegionNum(); j++) {
            double value = curImage->ptrLCR->getRegion(j).valued;
            if (0 < value) {
                //meanCV += value;
                if (maxCV < value) {
                    maxCV = value;
                }
                //countCV++;
            }
        }
        //meanCV /= countCV;

        glLineWidth(1.);
        glBegin(GL_LINES);
        for (int j = 0; j < curImage->ptrLCR->getRegionNum(); j++) {
            REGION3D curRegion = curImage->ptrLCR->getRegion(j);
            if (curRegion.valued < 0) continue;
            double intensity = 1. - log(curRegion.valued) / log(maxCV);
            //double intensity = curRegion.valued - meanCV;
            if (1 < intensity) intensity = 1.;
            double h = 360. * (1. - intensity);
            double r, g, b;
            //hsv2rgb(0.1, 0.7, intensity * 0.7, &r, &g, &b);
            hsv2rgb(h, 0.7, intensity * 0.7, &r, &g, &b);
            //glColor3d(intensity, intensity, intensity);
            //glColor3d(r, g, b);
            glColor4f(r, g, b, intensity);
            curRegion.from.x *= scalex;
            curRegion.from.y *= scaley;
            curRegion.from.z *= scalez;
            curRegion.to.x *= scalex;
            curRegion.to.y *= scaley;
            curRegion.to.z *= scalez;
            glVertex3d(curRegion.from.x + 1, curRegion.from.y + 1, curRegion.from.z + 1);
            glVertex3d(curRegion.to.x - 1, curRegion.from.y + 1, curRegion.from.z + 1);
            glVertex3d(curRegion.from.x + 1, curRegion.from.y + 1, curRegion.from.z + 1);
            glVertex3d(curRegion.from.x + 1, curRegion.to.y - 1, curRegion.from.z + 1);
            glVertex3d(curRegion.to.x - 1, curRegion.from.y + 1, curRegion.from.z + 1);
            glVertex3d(curRegion.to.x - 1, curRegion.to.y - 1, curRegion.from.z + 1);
            glVertex3d(curRegion.from.x + 1, curRegion.to.y - 1, curRegion.from.z + 1);
            glVertex3d(curRegion.to.x - 1, curRegion.to.y - 1, curRegion.from.z + 1);

            glVertex3d(curRegion.from.x + 1, curRegion.from.y + 1, curRegion.to.z - 1);
            glVertex3d(curRegion.to.x - 1, curRegion.from.y + 1, curRegion.to.z - 1);
            glVertex3d(curRegion.from.x + 1, curRegion.from.y + 1, curRegion.to.z - 1);
            glVertex3d(curRegion.from.x + 1, curRegion.to.y - 1, curRegion.to.z - 1);
            glVertex3d(curRegion.to.x - 1, curRegion.from.y + 1, curRegion.to.z - 1);
            glVertex3d(curRegion.to.x - 1, curRegion.to.y - 1, curRegion.to.z - 1);
            glVertex3d(curRegion.from.x + 1, curRegion.to.y - 1, curRegion.to.z - 1);
            glVertex3d(curRegion.to.x - 1, curRegion.to.y - 1, curRegion.to.z - 1);

            glVertex3d(curRegion.from.x + 1, curRegion.from.y + 1, curRegion.from.z + 1);
            glVertex3d(curRegion.from.x + 1, curRegion.from.y + 1, curRegion.to.z - 1);
            glVertex3d(curRegion.to.x - 1, curRegion.from.y + 1, curRegion.from.z + 1);
            glVertex3d(curRegion.to.x - 1, curRegion.from.y + 1, curRegion.to.z - 1);
            glVertex3d(curRegion.from.x + 1, curRegion.to.y - 1, curRegion.from.z + 1);
            glVertex3d(curRegion.from.x + 1, curRegion.to.y - 1, curRegion.to.z - 1);
            glVertex3d(curRegion.to.x - 1, curRegion.to.y - 1, curRegion.from.z + 1);
            glVertex3d(curRegion.to.x - 1, curRegion.to.y - 1, curRegion.to.z - 1);
        }
        glEnd();

        if (1 || curImage->alphaMode) {
            glDisable(GL_BLEND);
        }
    }


    //--------------------------------------------------------------------------
    // draw extracted data
    //--------------------------------------------------------------------------
    
    glColor3d(0x8E / 255., 0x5B / 255., 0x1E / 255);
    
    //static GLfloat extractedColor[] = { 0x8E / 255., 0x5B / 255., 0x1E / 255, 1.0 };
    //glMaterialfv(GL_FRONT, GL_DIFFUSE, extractedColor);

    for (int i = 0; i < MAX_EXTRACTED_DATA_NUM; i++) {
        EXTRACTEDDATA_FORMAT *curData = ExtractedData + i;
        if (curData->on == true) {
            /**/
            RodClusterList *curClusterList = &curData->data;
            struct {
                qreal x;
                qreal y;
                qreal z;
            } scale;
            scale.x = curClusterList->getScalingX();
            scale.y = curClusterList->getScalingY();
            scale.z = curClusterList->getScalingZ();
            double coefH = 359. / (double)curData->maxDist;
            glBegin(GL_LINES);
            for (unsigned int i = 0; i < curClusterList->getClusterNum(); i++) {
                RodCluster *curCluster = curClusterList->getCluster(i);
                POINT3D pointFrom = curCluster->getNode();
                //double h = coefH * curCluster->getDistance();
                double h = 360 * pointFrom.z / (BoundingBox.max.z() - BoundingBox.min.z());
                double r, g, b;
                hsv2rgb(h, 0.75, 0.6, &r, &g, &b);
                glColor3d(r, g, b);
                for (unsigned int j = 0; j < curCluster->getChildNum(); j++) {
                    POINT3D pointTo = curCluster->getChild(j)->getNode();
                    glVertex3d(pointFrom.x * scale.x,
                               pointFrom.y * scale.y,
                               pointFrom.z * scale.z);
                    glVertex3d(pointTo.x * scale.x,
                               pointTo.y * scale.y,
                               pointTo.z * scale.z);
                }
            }
            glEnd();
        } // draw extracted data end
    }
    glColor3d(1, 1, 1);

    // selected node
    //dprintf("VShapeViewGL::display drawing selected node... ");
    //glColor3d(1., 0., 0.);
    for (int i = 0; i < MAX_EXTRACTED_DATA_NUM; i++) {
        EXTRACTEDDATA_FORMAT *curData = ExtractedData + i;
        if (curData->on == true) {
            /**/
            int selectedNodeNo = curData->selectedNodeNo;
            RodClusterList *curClusterList = &curData->data;
            RodCluster *curCluster = curClusterList->getCluster(selectedNodeNo);
            struct {
                qreal x;
                qreal y;
                qreal z;
            } scale;
            scale.x = curClusterList->getScalingX();
            scale.y = curClusterList->getScalingY();
            scale.z = curClusterList->getScalingZ();
            double h = 360. * curCluster->getDistance() / (double)curData->maxDist;
            double r, g, b;
            hsv2rgb(h, 0.75, 0.6, &r, &g, &b);
            glColor3d(r, g, b);
            glPointSize(curCluster->getDiam());
            glBegin(GL_POINTS);
            glVertex3d(curCluster->getNode().x * scale.x,
                       curCluster->getNode().y * scale.y,
                       curCluster->getNode().z * scale.z);
            glEnd();
        }
    }
    glColor3d(1, 1, 1);
    //dprintf("ok\n");


    //--------------------------------------------------------------------------
    // draw TracingNode data 
    //--------------------------------------------------------------------------
    if (TracingNodeData.on) {
        struct {
            double x;
            double y;
            double z;
        } scaleTracingNode = {
            TracingNodeData.scale.x,
            TracingNodeData.scale.y,
            TracingNodeData.scale.z,
        };
        //glColor3d(1., 0., 0.);
        double coefH = 360. / TracingNodeData.NodeList.count();
        for (int i = 0; i < TracingNodeData.NodeList.count(); i++) {
            double h = coefH * i;
            double r, g, b;
            hsv2rgb(h, 0.75, 0.6, &r, &g, &b);
            glColor3d(r, g, b);
            glPointSize(TracingNodeData.NodeList[i].Diam);
            glBegin(GL_POINTS);
            glVertex3d(TracingNodeData.NodeList[i].Point.x * scaleTracingNode.x,
                       TracingNodeData.NodeList[i].Point.y * scaleTracingNode.y,
                       TracingNodeData.NodeList[i].Point.z * scaleTracingNode.z);
            glEnd();
        }
        glColor3d(1, 1, 1);
    }

    if (TracingNodeData.isCurNodeOn) {
        struct {
            double x;
            double y;
            double z;
        } scaleTracingNode = {
            TracingNodeData.scale.x,
            TracingNodeData.scale.y,
            TracingNodeData.scale.z,
        };
        glPointSize(TracingNodeData.curNode.Diam);
        glColor3d(0.9, 0, 0);
        glBegin(GL_POINTS);
        glVertex3d(TracingNodeData.curNode.Point.x * scaleTracingNode.x,
                   TracingNodeData.curNode.Point.y * scaleTracingNode.y,
                   TracingNodeData.curNode.Point.z * scaleTracingNode.z);
        glEnd();
    }

    glFlush();
}

void VShapeViewGL::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    switch (ViewMode)
        {
        case VIEWMODE_ORTHOGONAL:
            this->setOrtho();
            break;
        case VIEWMODE_PERSPECTIVE:
            this->setObservingPoint();
            break;
        }
}

void VShapeViewGL::setOrtho()
{
    if (ViewMode != VIEWMODE_ORTHOGONAL) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    struct {
        qreal x;
        qreal y;
        qreal z;
    } size;

    struct {
        qreal x;
        qreal y;
        qreal z;
    } center;

    size.x = BoundingBox.max.x() - BoundingBox.min.x();
    size.y = BoundingBox.max.y() - BoundingBox.min.y();
    size.z = BoundingBox.max.z() - BoundingBox.min.z();
    double dx2 = size.x * size.x;
    double dy2 = size.y * size.y;
    double dz2 = size.z * size.z;
    double l = sqrt(dx2 + dy2 + dz2) / 2;
    double margin = 50.;
    center.x = BoundingBox.mean.x();
    center.y = BoundingBox.mean.y();
    center.z = BoundingBox.mean.z();

    curViewRegion.x = center.x;
    curViewRegion.y = center.y;
    curViewRegion.z = center.z;
    curViewRegion.l = l;

    dprintf("VShapeViewGL::setOrtho " \
            "size (%f, %f, %f), l = %f, center (%f, %f, %f)\n",
            size.x, size.y, size.z, l, center.x, center.y, center.z);
    glOrtho(center.x - l - margin, center.x + l + margin,
            center.y - l - margin, center.y + l + margin,
            -center.z - l - margin, -center.z + l + margin);
    // glFrustum(center.x - l - margin, center.x + l + margin,
    //         center.y - l - margin, center.y + l + margin,
    //         -center.z - l - margin, -center.z + l + margin);
    // glTranslatef(center.x, center.y, center.z);
    glMatrixMode(GL_MODELVIEW);
}

void VShapeViewGL::setObservingPoint()
{
    if (ViewMode != VIEWMODE_PERSPECTIVE) return;
    //glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(60.0, this->width() / this->height(), 1.0, 500.0);
    glFrustum(BoundingBox.min.x(), BoundingBox.max.x(),
              BoundingBox.min.y(), BoundingBox.max.y(),
              1, 2000);
    double theta = RotX / ANGLE_DIV_NUM / 180. * PI;
    double phai = RotY / ANGLE_DIV_NUM / 180. * PI;
    double l = cos(phai);
    QVector3D lookAt(l * cos(theta), l * sin(theta), sin(phai));
    ObservingPoint.lookat = ObservingPoint.point + lookAt;
    ObservingPoint.upper = QVector3D(sin(phai) * cos(theta),
                                     sin(phai) * sin(theta),
                                     cos(phai));
    // gluLookAt(ObservingPoint.point.x(),
    //           ObservingPoint.point.y(),
    //           ObservingPoint.point.z(),
    //           ObservingPoint.lookat.x(),
    //           ObservingPoint.lookat.y(),
    //           ObservingPoint.lookat.z(),
    //           ObservingPoint.upper.x(),
    //           ObservingPoint.upper.y(),
    //           ObservingPoint.upper.z());
    glTranslatef(BoundingBox.mean.x(),
                 BoundingBox.mean.y(),
                 BoundingBox.mean.z() * 2);
    dprintf("VShapeViewGL::setObservingPoint " \
            "point (%f, %f, %f), lookat (%f, %f, %f)\n",
            ObservingPoint.point.x(),
            ObservingPoint.point.y(),
            ObservingPoint.point.z(),
            ObservingPoint.lookat.x(),
            ObservingPoint.lookat.y(),
            ObservingPoint.lookat.z());
    //glMatrixMode(GL_MODELVIEW);
}

void VShapeViewGL::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
}

void VShapeViewGL::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton) {
        setXRotation(RotX + 8 * dy);
        setYRotation(RotY + 8 * dx);
    } else if (event->buttons() & Qt::RightButton) {
        setXRotation(RotX + 8 * dy);
        setZRotation(RotZ + 8 * dx);
    }
    lastPos = event->pos();

    sendCurrentRotation();
}

void VShapeViewGL::keyPressEvent(QKeyEvent *event)
{
    dprintf("VShapeViewGL::keyPressEvent " \
            "key %c\n", event->key());
    //if (ViewMode != VIEWMODE_PERSPECTIVE) return;
    double coef = 20.;
    QVector3D distance = ObservingPoint.lookat - ObservingPoint.point;
    distance.normalize();
    double margin = 50.;
    switch (event->key())
        {
        // case ',':
        //     ObservingPoint.point += coef * distance;
        //     break;
        // case 'A':
        //     break;
        // case 'O':
        //     ObservingPoint.point -= coef * distance;
        //     break;
        case Qt::Key_Up:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            curViewRegion.y -= 10;
            glOrtho(curViewRegion.x - curViewRegion.l - margin,
                    curViewRegion.x + curViewRegion.l + margin,
                    curViewRegion.y - curViewRegion.l - margin,
                    curViewRegion.y + curViewRegion.l + margin,
                    -curViewRegion.z - curViewRegion.l - margin,
                    -curViewRegion.z + curViewRegion.l + margin);
            glMatrixMode(GL_MODELVIEW);
            this->glDraw();
            break;
        case Qt::Key_Down:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            curViewRegion.y += 10;
            glOrtho(curViewRegion.x - curViewRegion.l - margin,
                    curViewRegion.x + curViewRegion.l + margin,
                    curViewRegion.y - curViewRegion.l - margin,
                    curViewRegion.y + curViewRegion.l + margin,
                    -curViewRegion.z - curViewRegion.l - margin,
                    -curViewRegion.z + curViewRegion.l + margin);
            glMatrixMode(GL_MODELVIEW);
            this->glDraw();
            break;
        case Qt::Key_Left:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            curViewRegion.x += 10;
            glOrtho(curViewRegion.x - curViewRegion.l - margin,
                    curViewRegion.x + curViewRegion.l + margin,
                    curViewRegion.y - curViewRegion.l - margin,
                    curViewRegion.y + curViewRegion.l + margin,
                    -curViewRegion.z - curViewRegion.l - margin,
                    -curViewRegion.z + curViewRegion.l + margin);
            glMatrixMode(GL_MODELVIEW);
            this->glDraw();
            break;
        case Qt::Key_Right:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            curViewRegion.x -= 10;
            glOrtho(curViewRegion.x - curViewRegion.l - margin,
                    curViewRegion.x + curViewRegion.l + margin,
                    curViewRegion.y - curViewRegion.l - margin,
                    curViewRegion.y + curViewRegion.l + margin,
                    -curViewRegion.z - curViewRegion.l - margin,
                    -curViewRegion.z + curViewRegion.l + margin);
            glMatrixMode(GL_MODELVIEW);
            this->glDraw();
            break;
        case Qt::Key_PageUp:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            curViewRegion.l -= 50;
            glOrtho(curViewRegion.x - curViewRegion.l - margin,
                    curViewRegion.x + curViewRegion.l + margin,
                    curViewRegion.y - curViewRegion.l - margin,
                    curViewRegion.y + curViewRegion.l + margin,
                    -curViewRegion.z - curViewRegion.l - margin,
                    -curViewRegion.z + curViewRegion.l + margin);
            glMatrixMode(GL_MODELVIEW);
            this->glDraw();
            break;
        case Qt::Key_PageDown:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            curViewRegion.l += 50;
            glOrtho(curViewRegion.x - curViewRegion.l - margin,
                    curViewRegion.x + curViewRegion.l + margin,
                    curViewRegion.y - curViewRegion.l - margin,
                    curViewRegion.y + curViewRegion.l + margin,
                    -curViewRegion.z - curViewRegion.l - margin,
                    -curViewRegion.z + curViewRegion.l + margin);
            glMatrixMode(GL_MODELVIEW);
            this->glDraw();
            break;
        case Qt::Key_R:
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            double sizex = BoundingBox.max.x() - BoundingBox.min.x();
            double sizey = BoundingBox.max.y() - BoundingBox.min.y();
            double sizez = BoundingBox.max.z() - BoundingBox.min.z();
            double dx2 = sizex * sizex;
            double dy2 = sizey * sizey;
            double dz2 = sizez * sizez;
            double l = sqrt(dx2 + dy2 + dz2) / 2;
            double margin = 50.;
            double centerx = BoundingBox.mean.x();
            double centery = BoundingBox.mean.y();
            double centerz = BoundingBox.mean.z();
            curViewRegion.x = centerx;
            curViewRegion.y = centery;
            curViewRegion.z = centerz;
            curViewRegion.l = l;
            glOrtho(centerx - l - margin, centerx + l + margin,
                    centery - l - margin, centery + l + margin,
                    -centerz - l - margin, -centerz + l + margin);
            glMatrixMode(GL_MODELVIEW);
            this->glDraw();
            break;
        }
    setObservingPoint();
}

// void VShapeViewGL::setData(RodClusterList *extractedData)
// {
//     // it's possible to be called from other threads
//     mutex.lock();
//     dprintf("VShapeViewGL::setData extractedData->getClusterNum() = %u\n",
//             extractedData->getClusterNum());
//     ExtractedData = *extractedData;

//     unsigned int sfx = ExtractedData.getClusterNum() - 1;
//     ExtractedDataMaxDist = ExtractedData.getCluster(sfx)->getDistance();
    
//     ExtractedDataOn = true;
//     mutex.unlock();
// }

void VShapeViewGL::sendCurrentRotation()
{
    DATAFORMAT_CURRENT_VIEW_ROTATION sendData;
    sendData.rotx = RotX;
    sendData.roty = RotY;
    sendData.rotz = RotZ;
    putData(COMID_CURRENT_VIEW_ROTATION, (char *)&sendData, sizeof(sendData));
}

void VShapeViewGL::setBoundingBox()
{
    dprintf("VShapeViewGL::setBoundingBox starts\n");
    int maxx = 0;
    int maxy = 0;
    int maxz = 0;
    int minx = 0;
    int miny = 0;
    int minz = 0;
    for (int i = 0; i < MAX_STACK_IMAGE_NUM; i++) {
        // dprintf("VShapeViewGL::setBoundingBox [%2d/%2d]\n", i, MAX_STACK_IMAGE_NUM);
        STACKIMAGEDATA_FORMAT *curImage = StackImageData + i;
        if (curImage->ptr == NULL) continue;
        // dprintf("VShapeViewGL::setBoundingBox " \
        //         "StackImageData[%d]->ptr = %p\n", i, curImage->ptr);
        double value = curImage->size.x + curImage->translate.x;
        value *= curImage->scale.x;
        if (maxx < value) { maxx = value; }
        value = curImage->size.y + curImage->translate.y;
        value *= curImage->scale.y;
        if (maxy < value) { maxy = value; }
        value = curImage->size.z + curImage->translate.z;
        value *= curImage->scale.z;
        if (maxz < value) { maxz = value; }
        value = curImage->size.x + curImage->translate.x;
        value *= curImage->scale.x;
        if (minx > value) { minx = value; }
        value = curImage->size.y + curImage->translate.y;
        value *= curImage->scale.y;
        if (miny > value) { miny = value; }
        value = curImage->size.z + curImage->translate.z;
        value *= curImage->scale.z;
        if (minz > value) { minz = value; }
    }
    for (int i = 0; i < MAX_EXTRACTED_DATA_NUM; i++) {
        EXTRACTEDDATA_FORMAT *curExtractedData = ExtractedData + i;
        if (curExtractedData == NULL) continue;

        unsigned int clusterNum = curExtractedData->data.getClusterNum();
        struct {
            double x;
            double y;
            double z;
        } scale = {
            curExtractedData->data.getScalingX(),
            curExtractedData->data.getScalingY(),
            curExtractedData->data.getScalingZ()
        };
        for (int j = 0; j < clusterNum; j++) {
            RodCluster *curCluster = curExtractedData->data.getCluster(j);
            POINT3D point = curCluster->getNode();
            if (maxx < point.x * scale.x) {
                maxx = point.x * scale.x;
            }
            if (maxy < point.y * scale.y) {
                maxy = point.y * scale.y;
            }
            if (maxz < point.z * scale.z) {
                maxz = point.z * scale.z;
            }
            if (point.x * scale.x < minx) {
                minx = point.x * scale.x;
            }
            if (point.y * scale.y < miny) {
                miny = point.y * scale.y;
            }
            if (point.z * scale.z < minz) {
                minz = point.z * scale.z;
            }
        }
    }
    BoundingBox.max = QVector3D(maxx, maxy, maxz);
    BoundingBox.min = QVector3D(minx, miny, minz);
    BoundingBox.mean = QVector3D(maxx/2 + minx/2, maxy/2 + miny/2, maxz/2 + minz/2);
    dprintf("VShapeViewGL::setBoundingBox " \
            "max (%f, %f, %f), min (%f, %f, %f), mean (%f, %f, %f)\n",
            BoundingBox.max.x(), BoundingBox.max.y(), BoundingBox.max.z(),
            BoundingBox.min.x(), BoundingBox.min.y(), BoundingBox.min.z(),
            BoundingBox.mean.x(), BoundingBox.mean.y(), BoundingBox.mean.z());
}

void VShapeViewGL::showEvent(QShowEvent *event)
{
    dprintf("VShapeViewGL::showEvent\n");
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_SHAPEVIEW;
    sendData.show = this->isVisible();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void VShapeViewGL::hideEvent(QHideEvent *event)
{
    dprintf("VShapeViewGL::hideEvent\n");
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_SHAPEVIEW;
    sendData.show = this->isVisible();
    sendData.minimized = this->isMinimized();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void VShapeViewGL::closeEvent(QCloseEvent *event)
{
    dprintf("VShapeViewGL::closeEvent\n");
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_SHAPEVIEW;
    sendData.show = this->isVisible();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void VShapeViewGL::procedure(int ID, char *data, int byte)
{
    switch (ID) {
        case COMID_SET_VIEW_STACKIMAGE: {
            DATAFORMAT_SET_VIEW_STACKIMAGE *recvData
                = (DATAFORMAT_SET_VIEW_STACKIMAGE *)data;

            dprintf("VShapeViewGL::procedure got SET_VIEW_STACKIMAGE\n");
            dprintf("VShapeViewGL::procedure " \
                    "ptr = %p, thresold = %d, dataNo = %d, " \
                    "size = (%d, %d, %d) " \
                    "translate = (%d, %d, %d) " \
                    "scale = (%f, %f, %f), " \
                    "ROI = (%d-%d, %d-%d, %d-%d), " \
                    "ptrLCR %p [%s], " \
                    "[%s]\n",
                    recvData->ptr, recvData->threshold, recvData->dataNo,
                    recvData->size.x, recvData->size.y, recvData->size.z,
                    recvData->translate.x, recvData->translate.y, recvData->translate.z,
                    recvData->scale.x, recvData->scale.y, recvData->scale.z,
                    recvData->ROI.x.from, recvData->ROI.x.to,
                    recvData->ROI.y.from, recvData->ROI.y.to,
                    recvData->ROI.z.from, recvData->ROI.z.to,
                    recvData->ptrLCR,
                    recvData->isLCRon ? "ON" : "OFF",
                    recvData->on ? "VISIBLE" : "INVISIBLE");

            if (recvData->ptr == NULL) {
                return;
            }
            
            int dataNo = recvData->dataNo;
            StackImageData[dataNo].ptr = recvData->ptr;
            StackImageData[dataNo].threshold = recvData->threshold;
            StackImageData[dataNo].dataNo = recvData->dataNo;
            StackImageData[dataNo].size.x = recvData->size.x;
            StackImageData[dataNo].size.y = recvData->size.y;
            StackImageData[dataNo].size.z = recvData->size.z;
            StackImageData[dataNo].translate.x = recvData->translate.x;
            StackImageData[dataNo].translate.y = recvData->translate.y;
            StackImageData[dataNo].translate.z = recvData->translate.z;
            StackImageData[dataNo].scale.x = recvData->scale.x;
            StackImageData[dataNo].scale.y = recvData->scale.y;
            StackImageData[dataNo].scale.z = recvData->scale.z;
            StackImageData[dataNo].ROI.x.from = recvData->ROI.x.from;
            StackImageData[dataNo].ROI.x.to = recvData->ROI.x.to;
            StackImageData[dataNo].ROI.y.from = recvData->ROI.y.from;
            StackImageData[dataNo].ROI.y.to = recvData->ROI.y.to;
            StackImageData[dataNo].ROI.z.from = recvData->ROI.z.from;
            StackImageData[dataNo].ROI.z.to = recvData->ROI.z.to;
            StackImageData[dataNo].ptrLCR = (REGION3DARRAY *)recvData->ptrLCR;
            StackImageData[dataNo].isLCRon = recvData->isLCRon;
            StackImageData[dataNo].on = recvData->on;
            StackImageData[dataNo].alphaMode = recvData->alphaMode;
            StackImageData[dataNo].color.r = recvData->color.r;
            StackImageData[dataNo].color.g = recvData->color.g;
            StackImageData[dataNo].color.b = recvData->color.b;
            
            CurrentDataNo = dataNo;

            // unsigned char max = 0;
            // int length = recvData->size.x
            //     * recvData->size.y
            //     * recvData->size.z;
            // for (int i = 0; i < length; i++) {
            //     if (max < recvData->ptr[i]) {
            //         max = recvData->ptr[i];
            //     }
            // }
            // dprintf("VShapeViewGL::procedure max = %u\n", max);

            //QList<QVector3D> list;
            // Scale.x = recvData->scale.x;
            // Scale.y = recvData->scale.y;
            // Scale.z = recvData->scale.z;
            // sizex = recvData->size.x * Scale.x;
            // sizey = recvData->size.y * Scale.y;
            // sizez = recvData->size.z * Scale.z;

            unsigned char threshold = StackImageData[CurrentDataNo].threshold;

            struct {
                qreal x;
                qreal y;
                qreal z;
            } scale = {
                StackImageData[CurrentDataNo].scale.x,
                StackImageData[CurrentDataNo].scale.y,
                StackImageData[CurrentDataNo].scale.z
            };
            struct {
                int x;
                int y;
                int z;
            } translate = {
                StackImageData[CurrentDataNo].translate.x,
                StackImageData[CurrentDataNo].translate.y,
                StackImageData[CurrentDataNo].translate.z
            };
            struct {
                RANGE_INT x;
                RANGE_INT y;
                RANGE_INT z;
            } ROI = {
                {
                    StackImageData[CurrentDataNo].ROI.x.from,
                    StackImageData[CurrentDataNo].ROI.x.to
                },
                {
                    StackImageData[CurrentDataNo].ROI.y.from,
                    StackImageData[CurrentDataNo].ROI.y.to
                },
                {
                    StackImageData[CurrentDataNo].ROI.z.from,
                    StackImageData[CurrentDataNo].ROI.z.to
                }
            };
            StackImageData[CurrentDataNo].pointList.clear();

            int pageSize = recvData->size.x * recvData->size.y;
            // unsigned int count = 0;
                                                                   
            // for (int k = ROI.z.from; k <= ROI.z.to; k++) {
            //     int pageStep = pageSize * k;
            //     for (int j = ROI.y.from; j <= ROI.y.to; j++) {
            //         int step = pageStep + recvData->size.x * j;
            //         for (int i = ROI.x.from; i <= ROI.x.to; i++) {
            //             unsigned char value = recvData->ptr[step + i];
            //             if (threshold < value) {
            //                 count++;
            //             }
            //         }
            //     }
            // }

            ///unsigned int count = 0;
            for (int k = ROI.z.from; k <= ROI.z.to; k++) {
                int pageStep = pageSize * k;
                for (int j = ROI.y.from; j <= ROI.y.to; j++) {
                    int step = pageStep + recvData->size.x * j;
                    for (int i = ROI.x.from; i <= ROI.x.to; i++) {
                        unsigned char value = recvData->ptr[step + i];
                        if (threshold < value) {
                            int x = i + translate.x;
                            int y = j + translate.y;
                            int z = k + translate.z;
                            //count++;
                            StackImageData[CurrentDataNo].pointList.append(
                                QVector4D(x * scale.x,
                                          //(recvData->size.y - y - 1) * scale.y,
                                          y * scale.y,
                                          z * scale.z,
                                          value / 256.));
                        }
                    }
                }
            }
            // int thinningStep = StackImageData[CurrentDataNo].pointList.count()
            //     / MAX_DRAWING_POINT_NUM_STACKIMAGE;
            // if (1 < thinningStep) {
            //     for (int i = StackImageData[CurrentDataNo].pointList.count() - 1; 0 <= i; i-=thinningStep) {
            //         //if (getRandUniform() < thinningCoef) continue;
            //         StackImageData[CurrentDataNo].pointList.removeAt(i);
            //     }
            // }

            dprintf("VShapeViewGL::procedure pointList.count() = %d\n",
                    StackImageData[CurrentDataNo].pointList.count());

            setBoundingBox();
            
            if (ViewMode == VIEWMODE_ORTHOGONAL) this->setOrtho();

            ObservingPoint.point.setX(BoundingBox.mean.x());
            ObservingPoint.point.setY(BoundingBox.mean.y());
            ObservingPoint.point.setZ(BoundingBox.max.z() * 2);
            ObservingPoint.lookat.setX(BoundingBox.mean.x());
            ObservingPoint.lookat.setY(BoundingBox.mean.y());
            ObservingPoint.lookat.setZ(0.0);

            if (ViewMode == VIEWMODE_PERSPECTIVE) this->setObservingPoint();

            dprintf("VShapeViewGL::procedure receive ok\n");

            //setData();
            
            // redraw
            this->glDraw();

            return;
        } // COMID_SET_VIEW_STACKIMAGE

        case COMID_SET_VIEW_STACKIMAGE_ON: {
            DATAFORMAT_SET_VIEW_STACKIMAGE_ON *recvData
                = (DATAFORMAT_SET_VIEW_STACKIMAGE_ON *)data;

            dprintf("VShapeViewGL::procedure " \
                    "got SET_VIEW_STACKIMAGE_ON\n");
            dprintf("VShapeViewGL::procedure " \
                    "on = %d\n", recvData->on);
            
            StackImageData[recvData->dataNo].on = recvData->on;

            this->glDraw();
            
            return;
        } // COMID_SET_VIEW_STACKIMAGE

        case COMID_CHANGE_VIEW_STACKIMAGE: {
            DATAFORMAT_CHANGE_VIEW_STACKIMAGE *recvData
                = (DATAFORMAT_CHANGE_VIEW_STACKIMAGE *)data;
            

            dprintf("VShapeViewGL::procedure " \
                    "got CHANGE_VIEW_STACKIMAGE\n");

            // CurrentDataNo = recvData->dataNo;
            // StackImageData[CurrentDataNo].ptr = recvData->ptr;
            // StackImageData[CurrentDataNo].threshold = recvData->threshold;
            // StackImageData[CurrentDataNo].size.x = recvData->size.x;
            // StackImageData[CurrentDataNo].size.y = recvData->size.y;
            // StackImageData[CurrentDataNo].size.z = recvData->size.z;
            // StackImageData[CurrentDataNo].translate.x = recvData->translate.x;
            // StackImageData[CurrentDataNo].translate.y = recvData->translate.y;
            // StackImageData[CurrentDataNo].translate.z = recvData->translate.z;
            // StackImageData[CurrentDataNo].scale.x = recvData->scale.x;
            // StackImageData[CurrentDataNo].scale.y = recvData->scale.y;
            // StackImageData[CurrentDataNo].scale.z = recvData->scale.z;
            // StackImageData[CurrentDataNo].on = recvData->on;
            // for (int k = 0; k < recvData->size.z; k++) {
            //     int pageStep = recvData->size.x * recvData->size.y * k;
            //     for (int j = 0; j < recvData->size.y; j++) {
            //         int step = pageStep + recvData->size.x * j;
            //         for (int i = 0; i < recvData->size.x; i++) {
            //             unsigned char value = recvData->ptr[step + i];
            //             if (StackDataThreshold < value) {
            //                 StackImageData[CurrentDataNo].pointList.append(
            //                     QVector4D(i * Scale.x,
            //                               j * Scale.y,
            //                               k * Scale.z,
            //                               value / 256.));
            //             }
            //         }
            //     }
            // }

            // setBoundingBox();
            // setOrtho();            
            // this->glDraw();
            
            return;
        } // COMID_CHANGE_VIEW_STACKIMAGE

        case COMID_CHANGE_VIEW_THRESHOLD_STACKIMAGE: {
            QList<QVector3D> list;
            DATAFORMAT_CHANGE_VIEW_THRESHOLD_STACKIMAGE *recvData
                = (DATAFORMAT_CHANGE_VIEW_THRESHOLD_STACKIMAGE *)data;
            dprintf("VShapeViewGL::procedure " \
                  "got CHANGE_VIEW_THRESHOLD_STACKIMAGE\n");

            // // dprintf("VShapeViewGL::procedure data = %p, size = %d\n",
            // //         data, byte);
            // dprintf("VShapeViewGL::procedure threshold = %u\n",
            //         recvData->threshold);

            // // set threshold for viewing stack image
            // StackDataThreshold = recvData->threshold;

            // // set data list
            // for (int k = 0; k < recvData->size.z; k++) {
            //     int pageStep = recvData->size.x * recvData->size.y * k;
            //     for (int j = 0; j < recvData->size.y; j++) {
            //         int step = pageStep + recvData->size.x * j;
            //         for (int i = 0; i < recvData->size.x; i++) {
            //             if (StackDataThreshold < recvData->ptr[step + i]) {
            //                 list.append(QVector3D(i * Scale.x,
            //                                       j * Scale.y,
            //                                       k * Scale.z));
            //             }
            //         }
            //     }
            // }
            // setData(list);

            // // return recieved message
            // DATAFORMAT_CHANGE_VIEW_THRESHOLD_STACKIMAGE_OK sendData;
            // putData(COMID_CHANGE_VIEW_THRESHOLD_STACKIMAGE_OK,
            //         (char *)&sendData, sizeof(sendData));

            // // redraw
            // this->glDraw();
            // dprintf("VShapeViewGL::procedure threshold set");

            return;
        } // COMID_CHANGE_VIEW_THRESHOLD_STACKIMAGE

        case COMID_CHANGE_VIEW_ROTATION_STACKIMAGE: {
            DATAFORMAT_CHANGE_VIEW_ROTATION_STACKIMAGE *recvData
                = (DATAFORMAT_CHANGE_VIEW_ROTATION_STACKIMAGE *)data;
            dprintf("VShapeViewGL::procedure " \
                  "got CHANGE_VIEW_ROTATION_SATCKIMAGE\n");
            // dprintf("VShapeViewGL::procedure data = %p, size = %d\n",
            //         data, byte);
            dprintf("VShapeViewGL::procedure rot (%d, %d, %d)\n",
                    recvData->rotx, recvData->roty, recvData->rotz);

            // set rotation
            RotX = recvData->rotx;
            RotY = recvData->roty;
            RotZ = recvData->rotz;

            // return recieved message
            DATAFORMAT_CHANGE_VIEW_ROTATION_STACKIMAGE_OK sendData;
            putData(COMID_CHANGE_VIEW_ROTATION_STACKIMAGE_OK,
                    (char *)&sendData, sizeof(sendData));

            // redraw
            this->glDraw();

            // 
            sendCurrentRotation();

            return;
        } // COMID_CHANGE_VIEW_ROTATION_STACKIMAGE

        case COMID_CHANGE_VIEW_ROTATION: {
            DATAFORMAT_CHANGE_VIEW_ROTATION *recvData
                = (DATAFORMAT_CHANGE_VIEW_ROTATION *)data;
            // dprintf("VShapeViewGL::procedure " \
            //       "got CHANGE_VIEW_ROTATION\n");
            // dprintf("VShapeViewGL::procedure data = %p, size = %d\n",
            //         data, byte);
            dprintf("VShapeViewGL::procedure rot (%3.0f, %3.0f, %3.0f)\r",
                    recvData->rotx / (double)ANGLE_DIV_NUM,
                    recvData->roty / (double)ANGLE_DIV_NUM,
                    recvData->rotz / (double)ANGLE_DIV_NUM);

            // set rotation
            RotX = recvData->rotx;
            RotY = recvData->roty;
            RotZ = recvData->rotz;

            // return recieved message
            DATAFORMAT_CHANGE_VIEW_ROTATION_OK sendData;
            putData(COMID_CHANGE_VIEW_ROTATION_OK,
                    (char *)&sendData, sizeof(sendData));

            // redraw
            this->glDraw();

            //
            sendCurrentRotation();

            return;
        } // COMID_CHANGE_VIEW_ROTATION

        case COMID_CHANGE_VIEW_POINTER_STACKIMAGE: {
            DATAFORMAT_CHANGE_VIEW_POINTER_STACKIMAGE *recvData
                = (DATAFORMAT_CHANGE_VIEW_POINTER_STACKIMAGE *)data;
            // dprintf("VShapeViewGL::procedure " \
            //       "got CHANGE_VIEW_POINTER_STACKIMAGE\n");
            // dprintf("VShapeViewGL::procedure data = %p, size = %d\n",
            //         data, byte);
            // dprintf("VShapeViewGL::procedure point (%f, %f, %f) um : %s\n",
            //         recvData->x, recvData->y, recvData->z,
            //         (recvData->on == true ? "ON" : "OFF"));
            PointerStackImage.setX(recvData->x);
            PointerStackImage.setY(recvData->y);
            PointerStackImage.setZ(recvData->z);
            PointerOnStackImage = recvData->on;

            // redraw
            this->glDraw();

            return;
        } // COMID_CHANGE_VIEW_POINTER_STACKIMAGE

        case COMID_CHANGE_VIEW_COLOR_STACKIMAGE: {
            DATAFORMAT_CHANGE_VIEW_COLOR_STACKIMAGE *recvData
                = (DATAFORMAT_CHANGE_VIEW_COLOR_STACKIMAGE *)data;
            
            // dprintf("VShapeViewGL::procedure " \
            //         "got CHANGE_VIEW_COLOR_STACKIMAGE\n");
            // dprintf("VShapeViewGL::procedure " \
            //         "dataNo = %d, color (%f, %f, %f)\n",
            //         recvData->dataNo,
            //         recvData->r, recvData->g, recvData->b);
            
            StackImageData[recvData->dataNo].color.r = recvData->r;
            StackImageData[recvData->dataNo].color.g = recvData->g;
            StackImageData[recvData->dataNo].color.b = recvData->b;

            this->glDraw();

            return;
        } // COMID_CHANGE_VIEW_COLOR_STACKIMAGE

        case COMID_REQUEST_BOUNDINGBOX_STACKIMAGE: {
            DATAFORMAT_REQUEST_BOUNDINGBOX_STACKIMAGE *recvData
                = (DATAFORMAT_REQUEST_BOUNDINGBOX_STACKIMAGE *)data;
            dprintf("VShapeViewGL::procedure " \
                  "got REQUEST_BOUNDINGBOX_STACKIMAGE\n");
            // dprintf("VShapeViewGL::procedure data = %p, size = %d\n",
            //         data, byte);

            DATAFORMAT_BOUNDINGBOX_STACKIMAGE sendData;
            sendData.min.x = BoundingBox.min.x();
            sendData.min.y = BoundingBox.min.y();
            sendData.min.z = BoundingBox.min.z();
            sendData.max.x = BoundingBox.max.x();
            sendData.max.y = BoundingBox.max.y();
            sendData.max.z = BoundingBox.max.z();
            sendData.mean.x = BoundingBox.mean.x();
            sendData.mean.y = BoundingBox.mean.y();
            sendData.mean.z = BoundingBox.mean.z();
            putData(COMID_BOUNDINGBOX_STACKIMAGE,
                    (char *)&sendData, sizeof(sendData));
            return;
        } // COMID_REQUEST_BOUNDINGBOX_STACKIMAGE

        case COMID_SET_VIEW_EXTRACTEDDATA: {
            // this message is possible to be sent from another thread

            DATAFORMAT_SET_VIEW_EXTRACTEDDATA *recvData
                = (DATAFORMAT_SET_VIEW_EXTRACTEDDATA *)data;
            
            dprintf("VShapeViewGL::procedure " \
                    "got SET_VIEW_EXTRACTEDDATA\n");
            dprintf("VShapeViewGL::procedure " \
                    "ptr = %p, " \
                    "dataNo = %d, " \
                    "translate (%d, %d, %d), " \
                    "[%s/%s], " \
                    "selectedNode = %d\n",
                    recvData->ptr,
                    recvData->dataNo,
                    recvData->translate.x,
                    recvData->translate.y,
                    recvData->translate.z,
                    recvData->draw ? "DRAW" : "-",
                    recvData->on ? "ON" : "OFF",
                    recvData->selectedNodeNo);
            
            int dataNo = recvData->dataNo;
            if (recvData->ptr != NULL) {
                // dprintf("VShapeViewGL::procedure " \
                //         "set data\n");
                ExtractedData[dataNo].data = *((RodClusterList *)recvData->ptr);
            
                // dprintf("VShapeViewGL::procedure " \
                //         "set maxDist\n");
                int sfx = ExtractedData[dataNo].data.getClusterNum() - 1;
                dprintf("VShapeViewGL::procedure " \
                        "ClutserNum = %u, sfx = %d\n",
                        ExtractedData[dataNo].data.getClusterNum(),
                        sfx);
                unsigned int maxDist = 0;
                for (unsigned int i = 0; i < ExtractedData[dataNo].data.getClusterNum(); i++) {
                    unsigned int curDist = ExtractedData[dataNo].data.getCluster(i)->getDistance();
                    if (maxDist < curDist) {
                        maxDist = curDist;
                    }
                }
                ExtractedData[dataNo].maxDist = maxDist;
            
                // dprintf("VShapeViewGL::procedure " \
                //         "set translation\n");
                ExtractedData[dataNo].translate.x = recvData->translate.x;
                ExtractedData[dataNo].translate.y = recvData->translate.y;
                ExtractedData[dataNo].translate.z = recvData->translate.z;
                // dprintf("VShapeViewGL::procedure " \
                //         "set on/off\n");
                ExtractedData[dataNo].on = recvData->on;
                ExtractedData[dataNo].selectedNodeNo = recvData->selectedNodeNo;
            
                setBoundingBox();
            
                if (ViewMode == VIEWMODE_ORTHOGONAL) this->setOrtho();
                
                DATAFORMAT_SET_VIEW_EXTRACTEDDATA_OK sendData;
                putData(COMID_SET_VIEW_EXTRACTEDDATA_OK,
                        (char *)&sendData, sizeof(sendData));

                // dprintf("VShapeViewGL::procedure " \
                //         "sent SET_VIEW_EXTRACTEDDATA_OK\n");

                if (recvData->draw) {
                    this->glDraw();
                }
            } else {
                fprintf(stderr,
                        "VShapeViewGL::procedure null pointer " \
                        "for extracted data has been passed\n");
            }
            return;
        } // COMID_SET_VIEW_EXTRACTEDDATA

        case COMID_SET_VIEW_TRACINGNODELIST: {
            DATAFORMAT_SET_VIEW_TRACINGNODELIST *recvData
                = (DATAFORMAT_SET_VIEW_TRACINGNODELIST *)data;

            // dprintf("VShapeViewGL::procedure " \
            //         "got SET_VIEW_TRACINGNODELIST\n");
            // dprintf("VShapeViewGL::procedure " \
            //         "ptr = %p\n", recvData->ptr);

            QList<BTracingNode> *nodeList = ((QList<BTracingNode> *)recvData->ptr);
            TracingNodeData.NodeList.clear();
            for (int i = 0; i < nodeList->count(); i++) {
                TracingNodeData.NodeList.append((*nodeList)[i]);
            }
            TracingNodeData.scale.x = recvData->scale.x;
            TracingNodeData.scale.y = recvData->scale.y;
            TracingNodeData.scale.z = recvData->scale.z;
            TracingNodeData.on = recvData->on;
            
            // double mean = 0;
            // for (int i = 0; i < TracingNodeData.NodeList.count(); i++) {
            //         mean += TracingNodeData.NodeList[i].Diam;
            // }
            // mean /=  TracingNodeData.NodeList.count();
            // dprintf("VShapeViewGL::procedure " \
            //         "count = %d\n", TracingNodeData.NodeList.count());
            // dprintf("VShapeViewGL::procedure " \
            //         "mean = %f\n", mean);
            // int nodeNum = TracingNodeData.NodeList.count();
            // dprintf("VShapeViewGL::procedure " \
            //         "LastNode Point (%f, %f, %f), Diam = %f\n",
            //         TracingNodeData.NodeList[nodeNum-1].Point.x,
            //         TracingNodeData.NodeList[nodeNum-1].Point.y,
            //         TracingNodeData.NodeList[nodeNum-1].Point.z,
            //         TracingNodeData.NodeList[nodeNum-1].Diam);

            this->glDraw();

            return;
        }

        case COMID_SET_VIEW_CURRENT_TRACINGNODE: {
            DATAFORMAT_SET_VIEW_CURRENT_TRACINGNODE *recvData
                = (DATAFORMAT_SET_VIEW_CURRENT_TRACINGNODE *)data;

            dprintf("VShapeViewGL::procedure " \
                    "got SET_VIEW_CURRENT_TRACINGNODE\n");

            //BTracingNode *recvNode = (BTracingNode *)recvData->ptr;
            
            TracingNodeData.curNode.NodeNo = recvData->nodeNo;
            TracingNodeData.curNode.Point.x = recvData->point.x;
            TracingNodeData.curNode.Point.y = recvData->point.y;
            TracingNodeData.curNode.Point.z = recvData->point.z;
            TracingNodeData.scale.x = recvData->scale.x;
            TracingNodeData.scale.y = recvData->scale.y;
            TracingNodeData.scale.z = recvData->scale.z;
            TracingNodeData.curNode.Diam = recvData->diam;
            TracingNodeData.isCurNodeOn = recvData->on;

            dprintf("VSapeViewGL::procedure curNode " \
                    "No = %d, " \
                    "Point (%d, %d, %d), " \
                    "Diam = %f, " \
                    "Scale (%f, %f, %f) \n",
                    recvData->nodeNo,
                    recvData->point.x,
                    recvData->point.y,
                    recvData->point.z,
                    recvData->diam,
                    recvData->scale.x,
                    recvData->scale.y,
                    recvData->scale.z);

            this->glDraw();

            return ;
        } // COMID_SET_VIEW_CURRENT_TRACINGNODE

            
    }
}
