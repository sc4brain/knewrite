#ifndef ___C_VIEW_CONTROLLER_H__
#define ___C_VIEW_CONTROLLER_H__

#include <QDialog>
#include "CViewControllerDialog.h"
#include "CObjectCommunicator.h"

#include "BGlobalDefinitions.h"

class CViewController :
    public QDialog,
    public Ui::ViewControllerDialog,
    public BTerminal
{
    Q_OBJECT

 public:
    CViewController(QWidget *parent = 0);

 protected slots:
    void updateViewControlRotationXSlideBar();
    void updateViewControlRotationXSpinBox();
    void updateViewControlRotationYSlideBar();
    void updateViewControlRotationYSpinBox();
    void updateViewControlRotationZSlideBar();
    void updateViewControlRotationZSpinBox();
    void setViewControlRotationXYPlane();
    void setViewControlRotationYZPlane();
    void setViewControlRotationZXPlane();
    void sendViewControlRotation();

 protected:
    void showEvent(QShowEvent *event);
    void hideEvent(QHideEvent *event);
    void closeEvent(QCloseEvent *event);

 protected:
    void procedure(int ID, char *data, int byte);
};
#endif//___C_VIEW_CONTROLLER_H__
