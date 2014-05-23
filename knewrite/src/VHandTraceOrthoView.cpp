
#include <QtGui>
#include <math.h>

#include "VHandTraceOrthoView.h"

#include "CObjectCommunicatorID.h"
#include "BGlobalDefinitions.h"
#include "BCommon.h"

VHandTraceOrthoView::VHandTraceOrthoView(QWidget *parent) : QWidget(parent)
{
    StackImageData.ptr = NULL;
    StackImageData.threshold = 0;
    StackImageData.size.x = 0;
    StackImageData.size.y = 0;
    StackImageData.size.z = 0;
    StackImageData.scale.x = 0;
    StackImageData.scale.y = 0;
    StackImageData.scale.z = 0;

    PointerStackImage.x = 0;
    PointerStackImage.y = 0;
    PointerStackImage.z = 0;

    Modifiers.shift = false;
    Modifiers.control = false;
    Modifiers.alt = false;

    imageXY = NULL;
    imageXZ = NULL;
    imageZY = NULL;
    imageZZ = NULL;

    SelectedPlane = SELECTEDPLANE_XY;

    setFocusPolicy(Qt::ClickFocus);
}

void VHandTraceOrthoView::paintEvent(QPaintEvent * /* event */)
{
    if (StackImageData.ptr == NULL) {
        return;
    }
    int sizex = StackImageData.size.x;
    int sizey = StackImageData.size.y;
    int sizez = StackImageData.size.z;
    int pointerx = PointerStackImage.x;
    int pointery = PointerStackImage.y;
    int pointerz = PointerStackImage.z;
    QPainter painter(this);
    painter.save();
    painter.fillRect(0, 0, this->width()-1, this->height()-1, QColor(.1, .1, .1));


    // transform
    QSizeF allImageSize(sizex + sizez,
                        sizey + sizez);
    QRect rect = this->parentWidget()->geometry();
    // dprintf("VHandTraceOrthoView::paintEvent " \
    //         "allImageSize (%f, %f), " \
    //         "windowSize (%d, %d)\n", 
    //         allImageSize.width(), allImageSize.height(),
    //         rect.width(), rect.height());
    QTransform transform;
    transform.scale(this->parentWidget()->width() / allImageSize.width(),
                    this->parentWidget()->height() / allImageSize.height());
    painter.setWorldTransform(transform);


    // draw stack images
    painter.drawImage(0, 0, *imageXZ);
    painter.drawImage(0, sizez, *imageXY);
    painter.drawImage(sizex, 0, *imageZZ);
    painter.drawImage(sizex, sizez, *imageZY);

    QPen penSeparator(QColor(100, 100, 100));
    int penPointerAlpha = 130;
    QPen penPointerR(QColor(0x83, 0x26, 0x26, penPointerAlpha));
    QPen penPointerG(QColor(0x4A, 0x78, 0x00, penPointerAlpha));
    QPen penPointerB(QColor(0x1E, 0x37, 0xA6, penPointerAlpha));
    // QPen penPointerR(QColor(0x63, 0x26, 0x26, penPointerAlpha));
    // QPen penPointerG(QColor(0x4A, 0x58, 0x00, penPointerAlpha));
    // QPen penPointerB(QColor(0x1E, 0x37, 0x86, penPointerAlpha));
    penPointerR.setWidth(1);
    penPointerG.setWidth(1);
    penPointerB.setWidth(1);


    // separator
    painter.setPen(penSeparator);
    painter.drawLine(0, sizez - 1, sizex + sizez - 1, sizez - 1);
    painter.drawLine(sizex, 0, sizex, sizez + sizey - 1);

    // TracingNode
    if (TracingNodeData.on) {
        double coefH = 360. / (double)TracingNodeData.NodeList.count();
        double alpha = 140;
        for (int i = 0; i < NodeList2Draw.count(); i++) {
            NODE2DRAW *curNode = &NodeList2Draw[i];
            double h = coefH * curNode->no;
            double r, g, b;
            hsv2rgb(h, 0.7, 0.9, &r, &g, &b);
            QColor color(int(r * 256), int(g * 256), int(b * 256), alpha);
            QBrush brushCurNode(color);
            QPen penCurNode(color);
            penCurNode.setWidth(1);
            painter.setPen(penCurNode);
            painter.setBrush(brushCurNode);
            // dprintf("VHandTraceOrthoView::paintEvent " \
            //         "point (%f, %f), r (%f, %f)\n",
            //         curNode->point.x, curNode->point.y,
            //         curNode->rx, curNode->ry
            //         );
            painter.drawEllipse(QPointF(curNode->point.x, curNode->point.y),
                                curNode->rx, curNode->ry);
        }
        painter.setBrush(QBrush(Qt::NoBrush));
    }

    if (TracingNodeData.isCurNodeOn == true) {
        int intensity = 250;
        int alpha = 140;
        QPen penCurNode(QColor(intensity, 0, 0, alpha));
        penCurNode.setWidth(1);
        painter.setPen(penCurNode);
        double rx = TracingNodeData.curNode.Diam / 2. / TracingNodeData.scale.x;
        double ry = TracingNodeData.curNode.Diam / 2. / TracingNodeData.scale.y;
        double rz = TracingNodeData.curNode.Diam / 2. / TracingNodeData.scale.z;
        QPointF pointXZ(pointerx, sizez - pointerz - 1);
        QPointF pointXY(pointerx, sizez + sizey- pointery - 1);
        QPointF pointZY(sizex + pointerz, sizez + sizey- pointery - 1);
        painter.drawEllipse(pointXZ, rx, rz);
        painter.drawEllipse(pointXY, rx, ry);
        painter.drawEllipse(pointZY, rz, ry);
    }

    // pointer x
    painter.setPen(penPointerG);
    painter.drawLine(pointerx, sizey + sizez - 1, pointerx, sizez);
    painter.setPen(penPointerB);
    painter.drawLine(pointerx, sizez - 1, pointerx, 0);

    // pointer y
    painter.setPen(penPointerR);
    painter.drawLine(0, sizey + sizez - pointery - 1,
                     sizex - 1, sizey + sizez - pointery - 1);
    painter.setPen(penPointerB);
    painter.drawLine(sizex, sizey + sizez - pointery - 1,
                     sizex + sizez - 1, sizey + sizez - pointery - 1);
    
    // pointer z
    painter.setPen(penPointerR);
    painter.drawLine(0, sizez - pointerz - 1,
                     sizex - 1, sizez - pointerz - 1);
    painter.setPen(penPointerG);
    painter.drawLine(sizex + pointerz, sizey + sizez - 1,
                     sizex + pointerz, sizez);

    // selected plane
    // QPen penSelectedPlane(QColor(0x83, 0x26, 0x26, penPointerAlpha));
    // penSelectedPlane.setWidth(2);
    // painter.setPen(penSelectedPlane);
    // switch (SelectedPlane) 
    //     {
    //     case SELECTEDPLANE_XY:
    //         painter.drawLine(0, sizez, 0, sizez + sizey - 1);
    //         painter.drawLine(sizex - 1, sizez, sizex - 1, sizez + sizey - 1);
    //         painter.drawLine(0, sizez, sizex - 1, sizez);
    //         painter.drawLine(0, sizez + sizey - 1, sizex - 1, sizez + sizey - 1);
    //         break;
    //     case SELECTEDPLANE_XZ:
    //         painter.drawLine(0, 0, 0, sizez - 1);
    //         painter.drawLine(sizex - 1, 0, sizex - 1, sizez - 1);
    //         painter.drawLine(0, 0, sizex - 1, 0);
    //         painter.drawLine(0, sizez - 1, sizex - 1, sizez - 1);
    //         break;
    //     case SELECTEDPLANE_ZY:
    //         painter.drawLine(sizex, sizez, sizex, sizez + sizey - 1);
    //         painter.drawLine(sizex + sizez - 1, sizez, sizex + sizez - 1, sizez + sizey - 1);
    //         painter.drawLine(sizex, sizez, sizex + sizez - 1, sizez);
    //         painter.drawLine(sizex, sizez + sizey - 1, sizex + sizez - 1, sizez + sizey - 1);
    //         break;
    //     }

        
    painter.restore();
    //dprintf("VHandTraceOrthoView::paintEvent restore\n");
} // paintEvent

void VHandTraceOrthoView::mousePressEvent(QMouseEvent *event)
{
    //dprintf("VHandTraceOrthoView::mousePressEvent\n");

    if (TracingNodeData.isCurNodeOn
        && event->button() == Qt::LeftButton
        && !Modifiers.control) {

        double x = event->posF().x();
        double y = event->posF().y();
        // dprintf("VHandTraceOrthoView::mouseEvent " \
        //         "window (%d, %d), parent (%d, %d)\n",
        //         this->width(), this->height(),
        //         this->parentWidget()->width(), this->parentWidget()->height());
        // dprintf("VHandTraceOrthoView::mouseEvent " \
        //         "(%f, %f) -> ", x, y);
        x = x / this->parentWidget()->width() * (StackImageData.size.x + StackImageData.size.z);
        y = y / this->parentWidget()->height() * (StackImageData.size.y + StackImageData.size.z);
        // dprintf("(%f, %f) -> ", x, y);

        // bool regionBottom = StackImageData.size.z < y;
        // if (regionBottom) {
        //     y -= StackImageData.size.z;
        //     y = StackImageData.size.y - y + StackImageData.size.z;
        // }
        // dprintf("(%f, %f)\n", x, y);

        for (int i = 0; i < NodeList2Draw.count(); i++) {
            //bool regionLeft = x <= StackImageData.size.x;
            NODE2DRAW *curNode = &NodeList2Draw[i];
            // dprintf("VHandTraceOrthoView::mouseEvent "\
            //         "curcNode (%f, %f) [%f, %f]\n",
            //         curNode->point.x, curNode->point.y,
            //         curNode->rx, curNode->ry);
            double dx2 = x - curNode->point.x;
            dx2 *= dx2;
            double rx2 = curNode->rx * curNode->rx;
            if (rx2 < dx2) continue;
            double dy2 = y - curNode->point.y;
            dy2 *= dy2;
            double ry2 = curNode->ry * curNode->ry;
            if (ry2 < dy2) continue;
            DATAFORMAT_NODE_CLICKED_ON_ORTHOVIEW sendData;
            sendData.nodeNo = curNode->no;
            putData(COMID_NODE_CLICKED_ON_ORTHOVIEW, 
                    (char *)&sendData, sizeof(sendData));
            return;
        }

        // bool regionLeft = x <= StackImageData.size.x;
        // bool regionBottom = StackImageData.size.z < y;

        // if (regionLeft) {
        //     if (regionBottom) { // xy plane
        //         y -= StackImageData.size.z;
        //         y = StackImageData.size.y - y;
        //         for (int i = 0; i < NodeList2Draw.count(); i++) {
        //             NODE2DRAW *curNode = &NodeList2Draw[i];
        //             double dx2 = x - curNode->point.x;
        //             dx2 *= dx2;
        //             double rx2 = curNode->rx * curNode->rx;
        //             if (rx2 < dx2) continue;
        //             double dy2 = y - curNode->point.y;
        //             dy2 *= dy2;
        //             double ry2 = curNode->ry * curNode->ry;
        //             if (ry2 < dy2) continue;
        //             DATAFORMAT_NODE_CLICKED_ON_ORTHOVIEW sendData;
        //             sendData.nodeNo = curNode.no;
        //             putData(COMID_NODE_CLICKED_ON_ORTHOVIEW, 
        //                     (char *)&sendData, sizeof(sendData));
        //             return;
        //         }
        //         return;
        //     } else { //xz plane

        //     }   
        // } else {
        //     if (regionBottom) { // zy plane
            
        //     }
        // }
    } // select node


    if (TracingNodeData.isCurNodeOn
        && event->button() == Qt::LeftButton
        && Modifiers.control) {

        DATAFORMAT_ORTHOVIEW_KEYBOARD_MANIPULATION sendData;
        sendData.point.x = PointerStackImage.x;
        sendData.point.y = PointerStackImage.y;
        sendData.point.z = PointerStackImage.z;
        sendData.dispNodeList = TracingNodeData.on;
        sendData.addNode = false;
        sendData.diam = TracingNodeData.curNode.Diam;



        double x = event->posF().x();
        double y = event->posF().y();
        x = x / this->parentWidget()->width() * (StackImageData.size.x + StackImageData.size.z);
        y = y / this->parentWidget()->height() * (StackImageData.size.y + StackImageData.size.z);

        if (x < StackImageData.size.x && StackImageData.size.z < y) { // XY plane
            sendData.point.x = x;
            sendData.point.y = StackImageData.size.y - (y - StackImageData.size.z);
        }
        if (x < StackImageData.size.x && y < StackImageData.size.z){ // XZ plane
            sendData.point.x = x;
            sendData.point.z = StackImageData.size.z - y;
        }
        if (StackImageData.size.x < x && StackImageData.size.z < y) { // ZY plane
            sendData.point.y = StackImageData.size.y - (y - StackImageData.size.z);
            sendData.point.z = x - StackImageData.size.x;
        }

        putData(COMID_ORTHOVIEW_MOUSE_MANIPULATION,
                (char *)&sendData, sizeof(sendData));
    }
}

void VHandTraceOrthoView::keyPressEvent(QKeyEvent *event)
{
    //dprintf("VHandTraceOrthoView::keyPressEvent %d\n", event->key());

    if (StackImageData.ptr == NULL) {
        return;
    }

    DATAFORMAT_ORTHOVIEW_KEYBOARD_MANIPULATION sendData;
    sendData.point.x = PointerStackImage.x;
    sendData.point.y = PointerStackImage.y;
    sendData.point.z = PointerStackImage.z;
    sendData.dispNodeList = TracingNodeData.on;
    sendData.addNode = false;
    sendData.diam = TracingNodeData.curNode.Diam;

    double pointerStep = 1.;
    double diamStep = 0.1;

    switch (event->key())
        {
        case Qt::Key_W:
        case Qt::Key_Up:
            if (event->modifiers() == Qt::ControlModifier) {
                sendData.point.z += pointerStep;
            } else {
                sendData.point.y += pointerStep;
            }
            break;
            // switch (SelectedPlane)
            //     {
            //     case SELECTEDPLANE_XY: sendData.point.y += pointerStep; break;
            //     case SELECTEDPLANE_XZ: sendData.point.z += pointerStep; break;
            //     case SELECTEDPLANE_ZY: sendData.point.y += pointerStep; break;
            //     }
            // break;
        case Qt::Key_S:
        case Qt::Key_Down:
            if (event->modifiers() == Qt::ControlModifier) {
                sendData.point.z -= pointerStep;
            } else {
                sendData.point.y -= pointerStep;
            }
            break;
            // switch (SelectedPlane)
            //     {
            //     case SELECTEDPLANE_XY: sendData.point.y -= pointerStep; break;
            //     case SELECTEDPLANE_XZ: sendData.point.z -= pointerStep; break;
            //     case SELECTEDPLANE_ZY: sendData.point.y -= pointerStep; break;
            //     }
            // break;
        case Qt::Key_A:
        case Qt::Key_Left:
            sendData.point.x -= pointerStep;
            break;
            // switch (SelectedPlane)
            //     {
            //     case SELECTEDPLANE_XY: sendData.point.x -= pointerStep; break;
            //     case SELECTEDPLANE_XZ: sendData.point.x -= pointerStep; break;
            //     case SELECTEDPLANE_ZY: sendData.point.z -= pointerStep; break;
            //     }
            // break;
        case Qt::Key_D:
        case Qt::Key_Right:
            sendData.point.x += pointerStep;
            break;
            // switch (SelectedPlane)
            //     {
            //     case SELECTEDPLANE_XY: sendData.point.x += pointerStep; break;
            //     case SELECTEDPLANE_XZ: sendData.point.x += pointerStep; break;
            //     case SELECTEDPLANE_ZY: sendData.point.z += pointerStep; break;
            //     }
            // break;
        case Qt::Key_PageUp:
            sendData.diam += diamStep;
            break;
        case Qt::Key_PageDown:
            sendData.diam -= diamStep;
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            sendData.addNode = true;
            break;
        case Qt::Key_V:
            sendData.dispNodeList = !sendData.dispNodeList;
            break;
        // case Qt::Key_Tab:
        //     if (Qt::ShiftModifier & event->modifiers()) {
        //         SelectedPlane = (EnumSelectedPlane)((SelectedPlane - 1) % SELECTEDPLANE_NUM);
        //     } else {
        //         SelectedPlane = (EnumSelectedPlane)((SelectedPlane + 1) % SELECTEDPLANE_NUM);
        //     }
        //     this->update();
        //     return;
        case Qt::Key_Shift:
            Modifiers.shift = true;
            break;
        case Qt::Key_Control:
            Modifiers.control = true;
            break;
        case Qt::Key_Alt:
            Modifiers.alt = true;
            break;
        default:
            QWidget::keyPressEvent(event);
            return;
        }
    putData(COMID_ORTHOVIEW_KEYBOARD_MANIPULATION,
            (char *)&sendData, sizeof(sendData));
}

void VHandTraceOrthoView::keyReleaseEvent(QKeyEvent *event)
{
    if (StackImageData.ptr == NULL) {
        return;
    }

    switch (event->key())
        {
        case Qt::Key_Shift:
            Modifiers.shift = false;
            break;
        case Qt::Key_Control:
            Modifiers.control = false;
            break;
        case Qt::Key_Alt:
            Modifiers.alt = false;
            break;
        default:
            QWidget::keyPressEvent(event);
            return;
        }
}

void VHandTraceOrthoView::resetImage()
{
    unsigned char *data = StackImageData.ptr;

    if (data == NULL) return;

    int sizex = StackImageData.size.x;
    int sizey = StackImageData.size.y;
    int sizez = StackImageData.size.z;
    int pointerx = PointerStackImage.x;
    int pointery = PointerStackImage.y;
    int pointerz = PointerStackImage.z;    

    // dprintf("VHandTraceOrthoView::resetImage " \
    //         "data = %p, size (%d, %d, %d), pointer (%d, %d, %d)\n",
    //         data,
    //         sizex, sizey, sizez,
    //         pointerx, pointery, pointerz);

    {// XY plane
        int pageMargin = sizex * sizey * pointerz;
        for (int j = 0; j < sizey; j++) {
            int lineMargin = sizex * j;
            int y = sizey - j - 1;
            for (int i = 0; i < sizex; i++) {
                unsigned char value = data[pageMargin + lineMargin + i];
                imageXY->setPixel(i, y,
                                  QColor(value, value, value).rgb());
            }
        }
    }

    {// XZ plane
        int lineMargin = sizex * pointery;
        for (int k = 0; k < sizez; k++) {
            int pageMargin = sizex * sizey * k;
            int y = sizez - k - 1;
            for (int i = 0; i < sizex; i++) {
                unsigned char value = data[pageMargin + lineMargin + i];
                imageXZ->setPixel(i, y,
                                  QColor(value, value, value).rgb());
            }
        }
    }

    {// ZY plane
        for (int k = 0; k < sizez; k++) {
            int pageMarginPlusIndex = sizex * sizey * k + pointerx;
            for (int j = 0; j < sizey; j++) {
                int lineMargin = sizex * j;
                int value = data[pageMarginPlusIndex + lineMargin];
                imageZY->setPixel(k, sizey - 1 - j,
                                  QColor(value, value, value).rgb());
            }
        }
    }

    imageZZ->fill(0);

    {// node list
        NodeList2Draw.clear();
        int count = TracingNodeData.NodeList.count();
        // dprintf("VHandTraceOrthoView::resetImage " \
        //         "count = %d\n", count);
        for (int i = 0; i < count; i++) {
            BTracingNode *curNode = &(TracingNodeData.NodeList[i]);

            double distFromXYplane = pointerz - curNode->Point.z;
            if (distFromXYplane < 0) distFromXYplane *= -1;
            double distFromXZplane = pointery - curNode->Point.y;
            if (distFromXZplane < 0) distFromXZplane *= -1;
            double distFromZYplane = pointerx - curNode->Point.x;
            if (distFromZYplane < 0) distFromZYplane *= -1;

            double r = curNode->Diam / 2.;

            if (distFromXYplane < r) {
                double drawR = sqrt(r * r - distFromXYplane * distFromXYplane);
                NODE2DRAW addNode = {
                    curNode->NodeNo,
                    {
                        curNode->Point.x,
                        sizez + sizey - curNode->Point.y - 1
                    },
                    drawR / TracingNodeData.scale.x,
                    drawR / TracingNodeData.scale.y,
                };
                NodeList2Draw.append(addNode);
                // dprintf("VHandTraceOrthoView::resetImage " \
                //         "addNode [%d], point (%f, %f), r (%f, %f)\n",
                //         addNode.no, addNode.point.x, addNode.point.y,
                //         addNode.rx, addNode.ry);
            }

            if (distFromXZplane < r) {
                double drawR = sqrt(r * r - distFromXZplane * distFromXZplane);
                NODE2DRAW addNode = {
                    curNode->NodeNo,
                    {
                        curNode->Point.x,
                        sizez - curNode->Point.z - 1
                    },
                    drawR / TracingNodeData.scale.x,
                    drawR / TracingNodeData.scale.z
                };
                NodeList2Draw.append(addNode);
                // dprintf("VHandTraceOrthoView::resetImage " \
                //         "addNode [%d], point (%f, %f), r (%f, %f)\n",
                //         addNode.no, addNode.point.x, addNode.point.y,
                //         addNode.rx, addNode.ry);
            }

            if (distFromZYplane < r) {
                double drawR = sqrt(r * r - distFromZYplane * distFromZYplane);
                NODE2DRAW addNode = {
                    curNode->NodeNo,
                    {
                        (double)sizex + curNode->Point.z,
                        (double)sizez + sizey - curNode->Point.y - 1
                    },
                    drawR / TracingNodeData.scale.z,
                    drawR / TracingNodeData.scale.y
                };
                NodeList2Draw.append(addNode);
                // dprintf("VHandTraceOrthoView::resetImage " \
                //         "addNode [%d], point (%f, %f), r (%f, %f)\n",
                //         addNode.no, addNode.point.x, addNode.point.y,
                //         addNode.rx, addNode.ry);
            }
        }
        // dprintf("VHandTraceOrthoView::resetImage " \
        //         "NodeList2Draw.count() = %d\n", NodeList2Draw.count());
    }

    this->update();
}

void VHandTraceOrthoView::showEvent(QShowEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_ORTHOVIEW;
    sendData.show = this->isVisible();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void VHandTraceOrthoView::hideEvent(QHideEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_ORTHOVIEW;
    sendData.show = this->isVisible();
    sendData.minimized = this->isMinimized();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void VHandTraceOrthoView::closeEvent(QCloseEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_ORTHOVIEW;
    sendData.show = this->isVisible();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void VHandTraceOrthoView::procedure(int ID, char* data, int byte)
{
    switch (ID) {
        
        case COMID_SET_ORTHOVIEW_STACKIMAGE: {
            DATAFORMAT_SET_ORTHOVIEW_STACKIMAGE *recvData
                = (DATAFORMAT_SET_ORTHOVIEW_STACKIMAGE *)data;

            dprintf("VHandTraceOrthoView::procedure " \
                    "got COMID_SET_ORTHOVIEW_STACKIMAGE\n");
            dprintf("VHandTraceOrthoView::procedure " \
                    "ptr = %p, " \
                    "size (%d, %d, %d), " \
                    "scale (%f, %f, %f)\n",
                    recvData->ptr,
                    recvData->size.x, recvData->size.y, recvData->size.z,
                    recvData->scale.x, recvData->scale.y, recvData->scale.z);

            StackImageData.ptr = recvData->ptr;
            StackImageData.size.x = recvData->size.x;
            StackImageData.size.y = recvData->size.y;
            StackImageData.size.z = recvData->size.z;
            StackImageData.scale.x = recvData->scale.x;
            StackImageData.scale.y = recvData->scale.y;
            StackImageData.scale.z = recvData->scale.z;
            
            int width = StackImageData.size.x + StackImageData.size.z;
            int height = StackImageData.size.y + StackImageData.size.z;
            this->parentWidget()->resize(width, height);

            SAFEDELETE(imageXY);
            SAFEDELETE(imageXZ);
            SAFEDELETE(imageZY);
            SAFEDELETE(imageZZ);

            imageXY = new QImage(StackImageData.size.x,
                                 StackImageData.size.y,
                                 QImage::Format_RGB32);
            imageXZ = new QImage(StackImageData.size.x,
                                 StackImageData.size.y,
                                 QImage::Format_RGB32);
            imageZY = new QImage(StackImageData.size.z,
                                 StackImageData.size.y,
                                 QImage::Format_RGB32);
            imageZZ = new QImage(StackImageData.size.z,
                                 StackImageData.size.z,
                                 QImage::Format_RGB32);

            this->resetImage();
            this->parentWidget()->show();
            this->show();

            return;
        } // COMID_HANDTRACE_STACKIMAGE

        case COMID_CHANGE_VIEW_POINTER_STACKIMAGE: {
            DATAFORMAT_CHANGE_VIEW_POINTER_STACKIMAGE *recvData
                = (DATAFORMAT_CHANGE_VIEW_POINTER_STACKIMAGE *)data;
            // dprintf("VHandTraceOrthoView::procedure " \
            //       "got CHANGE_VIEW_POINTER_STACKIMAGE\n");
            // dprintf("VShapeViewGL::procedure data = %p, size = %d\n",
            //         data, byte);
            // dprintf("VHandTraceOrthoView::procedure point (%f, %f, %f) um : %s\n",
            //         recvData->x, recvData->y, recvData->z,
            //         (recvData->on == true ? "ON" : "OFF"));

            PointerStackImage.x = recvData->x;
            PointerStackImage.y = recvData->y;
            PointerStackImage.z = recvData->z;

            // redraw
            this->resetImage();

            return;
        } // COMID_CHANGE_VIEW_POINTER_STACKIMAGE

        case COMID_HANDTRACE_VIEW_POINTER: {
            DATAFORMAT_HANDTRACE_VIEW_POINTER *recvData
                = (DATAFORMAT_HANDTRACE_VIEW_POINTER *)data;

            // dprintf("VHandTraceOrthoView::procedure " \
            //         "got HANDTRACE_POINTER\n");
            // dprintf("VHandTraceOrthoView::procedure " \
            //         "pointer (%d, %d, %d)\n",
            //         recvData->pointer.x,
            //         recvData->pointer.y,
            //         recvData->pointer.z);

            PointerStackImage.x = recvData->pointer.x;
            PointerStackImage.y = recvData->pointer.y;
            PointerStackImage.z = recvData->pointer.z;

            this->resetImage();

            return;
        } // COMID_HANDTRACE_VIEW_POINTER

        case COMID_SET_VIEW_TRACINGNODELIST: {
            DATAFORMAT_SET_VIEW_TRACINGNODELIST *recvData
                = (DATAFORMAT_SET_VIEW_TRACINGNODELIST *)data;

            // dprintf("VHandTraceOrthoView::procedure " \
            //         "got SET_VIEW_TRACINGNODELIST\n");
            // dprintf("VHandTraceOrthoView::procedure " \
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
            TracingNodeData.subbranchMode = recvData->subbranchMode;
            
            // double mean = 0;
            // for (int i = 0; i < TracingNodeData.NodeList.count(); i++) {
            //         mean += TracingNodeData.NodeList[i].Diam;
            // }
            // mean /=  TracingNodeData.NodeList.count();
            // dprintf("VHandTraceOrthoView::procedure " \
            //         "count = %d\n", TracingNodeData.NodeList.count());

            this->resetImage();

            return;
        }

        case COMID_SET_VIEW_CURRENT_TRACINGNODE: {
            DATAFORMAT_SET_VIEW_CURRENT_TRACINGNODE *recvData
                = (DATAFORMAT_SET_VIEW_CURRENT_TRACINGNODE *)data;

            // dprintf("VHandTraceOrthoView::procedure " \
            //         "got SET_VIEW_CURRENT_TRACINGNODE\n");

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

            // dprintf("VHandTraceOrthoView::procedure curNode " \
            //         "No = %d, " \
            //         "Point (%d, %d, %d), " \
            //         "Diam = %f, " \
            //         "Scale (%f, %f, %f) \n",
            //         recvData->nodeNo,
            //         recvData->point.x,
            //         recvData->point.y,
            //         recvData->point.z,
            //         recvData->diam,
            //         recvData->scale.x,
            //         recvData->scale.y,
            //         recvData->scale.z);

            this->resetImage();

            return ;
        } // COMID_SET_VIEW_CURRENT_TRACINGNODE

        case COMID_SET_DEFAULTSIZE_ORTHOVIEW: {
            DATAFORMAT_SET_DEFAULTSIZE_ORTHOVIEW *recvData
                = (DATAFORMAT_SET_DEFAULTSIZE_ORTHOVIEW *)data;

            dprintf("VHandTraceOrthoView::procedure " \
                    "got SET_DEFAULTSIZE_ORTHOVIEW\n");
            
            if (StackImageData.ptr != NULL) {
                double width = StackImageData.size.x + StackImageData.size.z;
                double height = StackImageData.size.y + StackImageData.size.z;
                this->parentWidget()->resize(width, height);
            }

            this->update();

            return;
        } // COMID_


        default:
            return;
    }
}

