
#include <QtGui>

#include "CViewController.h"
#include "CObjectCommunicatorID.h"

#include "BCommon.h"

#define ANGLE_DIV_NUM 16

CViewController::CViewController(QWidget *parent) : QDialog(parent)
{
    setupUi(this);

    // rotation x
    connect(VerticalSliderViewControlRotationX,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlRotationXSpinBox()));
    connect(SpinBoxViewControlRotationX, SIGNAL(valueChanged(const QString &)),
            this, SLOT(updateViewControlRotationXSlideBar()));
    
    // rotation y
    connect(VerticalSliderViewControlRotationY,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlRotationYSpinBox()));
    connect(SpinBoxViewControlRotationY, SIGNAL(valueChanged(const QString &)),
            this, SLOT(updateViewControlRotationYSlideBar()));

    // rotation z
    connect(VerticalSliderViewControlRotationZ,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlRotationZSpinBox()));
    connect(SpinBoxViewControlRotationZ, SIGNAL(valueChanged(const QString &)),
            this, SLOT(updateViewControlRotationZSlideBar()));

    // xy plane
    connect(PushButtonViewControlRotationXYPlane, SIGNAL(clicked()),
            this, SLOT(setViewControlRotationXYPlane()));
    // yz plane
    connect(PushButtonViewControlRotationYZPlane, SIGNAL(clicked()),
            this, SLOT(setViewControlRotationYZPlane()));
    // zx plane
    connect(PushButtonViewControlRotationZXPlane, SIGNAL(clicked()),
            this, SLOT(setViewControlRotationZXPlane()));
    
    // send to the shape view when the slide bar for [x or y or z] manupilated
    connect(VerticalSliderViewControlRotationX,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlRotation()));
    connect(VerticalSliderViewControlRotationY,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlRotation()));
    connect(VerticalSliderViewControlRotationZ,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlRotation()));
}

void CViewController::updateViewControlRotationXSlideBar()
{
    int value = SpinBoxViewControlRotationX->value();
    value *= ANGLE_DIV_NUM;
    VerticalSliderViewControlRotationX->setValue(value);
}

void CViewController::updateViewControlRotationXSpinBox()
{
    int value = VerticalSliderViewControlRotationX->value();
    SpinBoxViewControlRotationX->setValue(value / ANGLE_DIV_NUM);
}

void CViewController::updateViewControlRotationYSlideBar()
{
    int value = SpinBoxViewControlRotationY->value();
    value *= ANGLE_DIV_NUM;
    VerticalSliderViewControlRotationY->setValue(value);
}

void CViewController::updateViewControlRotationYSpinBox()
{
    int value = VerticalSliderViewControlRotationY->value();
    SpinBoxViewControlRotationY->setValue(value / ANGLE_DIV_NUM);
}

void CViewController::updateViewControlRotationZSlideBar()
{
    int value = SpinBoxViewControlRotationZ->value();
    value *= ANGLE_DIV_NUM;
    VerticalSliderViewControlRotationZ->setValue(value);
}

void CViewController::updateViewControlRotationZSpinBox()
{
    int value = VerticalSliderViewControlRotationZ->value();
    SpinBoxViewControlRotationZ->setValue(value / ANGLE_DIV_NUM);
}

void CViewController::setViewControlRotationXYPlane()
{
    VerticalSliderViewControlRotationX->setValue(
        0 * ANGLE_DIV_NUM);
    VerticalSliderViewControlRotationY->setValue(
        0 * ANGLE_DIV_NUM);
    VerticalSliderViewControlRotationZ->setValue(
        0 * ANGLE_DIV_NUM);
}

void CViewController::setViewControlRotationYZPlane()
{
    VerticalSliderViewControlRotationX->setValue(
        90 * ANGLE_DIV_NUM);
    VerticalSliderViewControlRotationY->setValue(
        180 * ANGLE_DIV_NUM);
    VerticalSliderViewControlRotationZ->setValue(
        90 * ANGLE_DIV_NUM);
}

void CViewController::setViewControlRotationZXPlane()
{
    VerticalSliderViewControlRotationX->setValue(
        90 * ANGLE_DIV_NUM);
    VerticalSliderViewControlRotationY->setValue(
        90 * ANGLE_DIV_NUM);
    VerticalSliderViewControlRotationZ->setValue(
        0 * ANGLE_DIV_NUM);
}

void CViewController::sendViewControlRotation()
{
    DATAFORMAT_CHANGE_VIEW_ROTATION sendData;
    sendData.rotx = VerticalSliderViewControlRotationX->value();
    sendData.roty = VerticalSliderViewControlRotationY->value();
    sendData.rotz = VerticalSliderViewControlRotationZ->value();
    putData(COMID_CHANGE_VIEW_ROTATION,
            (char *)&sendData, sizeof(sendData));
}

void CViewController::showEvent(QShowEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_VIEWCONTROLLER;
    sendData.show = this->isVisible();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void CViewController::hideEvent(QHideEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_VIEWCONTROLLER;
    sendData.show = this->isVisible();
    sendData.minimized = this->isMinimized();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void CViewController::closeEvent(QCloseEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_VIEWCONTROLLER;
    sendData.show = this->isVisible();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void CViewController::procedure(int ID, char *data, int byte)
{
    switch (ID) {

        case COMID_CURRENT_VIEW_ROTATION: {
            DATAFORMAT_CURRENT_VIEW_ROTATION *recvData
                = (DATAFORMAT_CURRENT_VIEW_ROTATION *)data;

            // dprintf("CViewController::procedure " \
            //         "got CURRENT_VIEW_ROTATION\n");
            // dprintf("CViewController::procedure " \
            //         "data = %p, size = %d\n", data, byte);
            // dprintf("CViewController::procedure " \
            //         "Rot (%d, %d, %d)\n",
            //         recvData->rotx, recvData->roty, recvData->rotz);

            VerticalSliderViewControlRotationX->setValue(recvData->rotx);
            VerticalSliderViewControlRotationY->setValue(recvData->roty);
            VerticalSliderViewControlRotationZ->setValue(recvData->rotz);
            return;
        } // COMID_CURRENT_VIEW_ROTATION

    }
}


