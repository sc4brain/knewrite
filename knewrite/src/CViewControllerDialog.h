/********************************************************************************
** Form generated from reading UI file 'UIViewControllerDialog.ui'
**
** Created: Sun Jan 30 18:21:32 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CVIEWCONTROLLERDIALOG_H
#define CVIEWCONTROLLERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ViewControllerDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QLabel *LabelViewControlRotation;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_4;
    QLabel *LabelViewControlRotationX;
    QHBoxLayout *horizontalLayout_8;
    QSlider *VerticalSliderViewControlRotationX;
    QSpinBox *SpinBoxViewControlRotationX;
    QPushButton *PushButtonViewControlRotationXYPlane;
    QVBoxLayout *verticalLayout_6;
    QLabel *LabelViewControlRotationY;
    QHBoxLayout *horizontalLayout_10;
    QSlider *VerticalSliderViewControlRotationY;
    QSpinBox *SpinBoxViewControlRotationY;
    QPushButton *PushButtonViewControlRotationYZPlane;
    QVBoxLayout *verticalLayout_5;
    QLabel *LabelViewControlRotationZ;
    QHBoxLayout *horizontalLayout_9;
    QSlider *VerticalSliderViewControlRotationZ;
    QSpinBox *SpinBoxViewControlRotationZ;
    QPushButton *PushButtonViewControlRotationZXPlane;

    void setupUi(QDialog *ViewControllerDialog)
    {
        if (ViewControllerDialog->objectName().isEmpty())
            ViewControllerDialog->setObjectName(QString::fromUtf8("ViewControllerDialog"));
        ViewControllerDialog->resize(190, 248);
        gridLayout = new QGridLayout(ViewControllerDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        LabelViewControlRotation = new QLabel(ViewControllerDialog);
        LabelViewControlRotation->setObjectName(QString::fromUtf8("LabelViewControlRotation"));
        LabelViewControlRotation->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(LabelViewControlRotation);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        LabelViewControlRotationX = new QLabel(ViewControllerDialog);
        LabelViewControlRotationX->setObjectName(QString::fromUtf8("LabelViewControlRotationX"));
        LabelViewControlRotationX->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(LabelViewControlRotationX);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        VerticalSliderViewControlRotationX = new QSlider(ViewControllerDialog);
        VerticalSliderViewControlRotationX->setObjectName(QString::fromUtf8("VerticalSliderViewControlRotationX"));
        VerticalSliderViewControlRotationX->setMaximum(5760);
        VerticalSliderViewControlRotationX->setOrientation(Qt::Vertical);

        horizontalLayout_8->addWidget(VerticalSliderViewControlRotationX);


        verticalLayout_4->addLayout(horizontalLayout_8);

        SpinBoxViewControlRotationX = new QSpinBox(ViewControllerDialog);
        SpinBoxViewControlRotationX->setObjectName(QString::fromUtf8("SpinBoxViewControlRotationX"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SpinBoxViewControlRotationX->sizePolicy().hasHeightForWidth());
        SpinBoxViewControlRotationX->setSizePolicy(sizePolicy);
        SpinBoxViewControlRotationX->setMinimumSize(QSize(50, 0));
        SpinBoxViewControlRotationX->setMaximum(359);

        verticalLayout_4->addWidget(SpinBoxViewControlRotationX);

        PushButtonViewControlRotationXYPlane = new QPushButton(ViewControllerDialog);
        PushButtonViewControlRotationXYPlane->setObjectName(QString::fromUtf8("PushButtonViewControlRotationXYPlane"));
        sizePolicy.setHeightForWidth(PushButtonViewControlRotationXYPlane->sizePolicy().hasHeightForWidth());
        PushButtonViewControlRotationXYPlane->setSizePolicy(sizePolicy);
        PushButtonViewControlRotationXYPlane->setMinimumSize(QSize(50, 0));

        verticalLayout_4->addWidget(PushButtonViewControlRotationXYPlane);


        horizontalLayout_11->addLayout(verticalLayout_4);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        LabelViewControlRotationY = new QLabel(ViewControllerDialog);
        LabelViewControlRotationY->setObjectName(QString::fromUtf8("LabelViewControlRotationY"));
        LabelViewControlRotationY->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(LabelViewControlRotationY);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        VerticalSliderViewControlRotationY = new QSlider(ViewControllerDialog);
        VerticalSliderViewControlRotationY->setObjectName(QString::fromUtf8("VerticalSliderViewControlRotationY"));
        VerticalSliderViewControlRotationY->setMaximum(5760);
        VerticalSliderViewControlRotationY->setOrientation(Qt::Vertical);

        horizontalLayout_10->addWidget(VerticalSliderViewControlRotationY);


        verticalLayout_6->addLayout(horizontalLayout_10);

        SpinBoxViewControlRotationY = new QSpinBox(ViewControllerDialog);
        SpinBoxViewControlRotationY->setObjectName(QString::fromUtf8("SpinBoxViewControlRotationY"));
        sizePolicy.setHeightForWidth(SpinBoxViewControlRotationY->sizePolicy().hasHeightForWidth());
        SpinBoxViewControlRotationY->setSizePolicy(sizePolicy);
        SpinBoxViewControlRotationY->setMinimumSize(QSize(50, 0));
        SpinBoxViewControlRotationY->setMaximum(359);

        verticalLayout_6->addWidget(SpinBoxViewControlRotationY);

        PushButtonViewControlRotationYZPlane = new QPushButton(ViewControllerDialog);
        PushButtonViewControlRotationYZPlane->setObjectName(QString::fromUtf8("PushButtonViewControlRotationYZPlane"));
        sizePolicy.setHeightForWidth(PushButtonViewControlRotationYZPlane->sizePolicy().hasHeightForWidth());
        PushButtonViewControlRotationYZPlane->setSizePolicy(sizePolicy);
        PushButtonViewControlRotationYZPlane->setMinimumSize(QSize(50, 0));

        verticalLayout_6->addWidget(PushButtonViewControlRotationYZPlane);


        horizontalLayout_11->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        LabelViewControlRotationZ = new QLabel(ViewControllerDialog);
        LabelViewControlRotationZ->setObjectName(QString::fromUtf8("LabelViewControlRotationZ"));
        LabelViewControlRotationZ->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(LabelViewControlRotationZ);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        VerticalSliderViewControlRotationZ = new QSlider(ViewControllerDialog);
        VerticalSliderViewControlRotationZ->setObjectName(QString::fromUtf8("VerticalSliderViewControlRotationZ"));
        VerticalSliderViewControlRotationZ->setMaximum(5760);
        VerticalSliderViewControlRotationZ->setOrientation(Qt::Vertical);

        horizontalLayout_9->addWidget(VerticalSliderViewControlRotationZ);


        verticalLayout_5->addLayout(horizontalLayout_9);

        SpinBoxViewControlRotationZ = new QSpinBox(ViewControllerDialog);
        SpinBoxViewControlRotationZ->setObjectName(QString::fromUtf8("SpinBoxViewControlRotationZ"));
        sizePolicy.setHeightForWidth(SpinBoxViewControlRotationZ->sizePolicy().hasHeightForWidth());
        SpinBoxViewControlRotationZ->setSizePolicy(sizePolicy);
        SpinBoxViewControlRotationZ->setMinimumSize(QSize(50, 0));
        SpinBoxViewControlRotationZ->setMaximum(359);

        verticalLayout_5->addWidget(SpinBoxViewControlRotationZ);

        PushButtonViewControlRotationZXPlane = new QPushButton(ViewControllerDialog);
        PushButtonViewControlRotationZXPlane->setObjectName(QString::fromUtf8("PushButtonViewControlRotationZXPlane"));
        sizePolicy.setHeightForWidth(PushButtonViewControlRotationZXPlane->sizePolicy().hasHeightForWidth());
        PushButtonViewControlRotationZXPlane->setSizePolicy(sizePolicy);
        PushButtonViewControlRotationZXPlane->setMinimumSize(QSize(50, 0));

        verticalLayout_5->addWidget(PushButtonViewControlRotationZXPlane);


        horizontalLayout_11->addLayout(verticalLayout_5);


        verticalLayout->addLayout(horizontalLayout_11);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        QWidget::setTabOrder(VerticalSliderViewControlRotationX, VerticalSliderViewControlRotationY);
        QWidget::setTabOrder(VerticalSliderViewControlRotationY, VerticalSliderViewControlRotationZ);
        QWidget::setTabOrder(VerticalSliderViewControlRotationZ, SpinBoxViewControlRotationX);
        QWidget::setTabOrder(SpinBoxViewControlRotationX, SpinBoxViewControlRotationY);
        QWidget::setTabOrder(SpinBoxViewControlRotationY, SpinBoxViewControlRotationZ);
        QWidget::setTabOrder(SpinBoxViewControlRotationZ, PushButtonViewControlRotationXYPlane);
        QWidget::setTabOrder(PushButtonViewControlRotationXYPlane, PushButtonViewControlRotationYZPlane);
        QWidget::setTabOrder(PushButtonViewControlRotationYZPlane, PushButtonViewControlRotationZXPlane);

        retranslateUi(ViewControllerDialog);

        QMetaObject::connectSlotsByName(ViewControllerDialog);
    } // setupUi

    void retranslateUi(QDialog *ViewControllerDialog)
    {
        ViewControllerDialog->setWindowTitle(QApplication::translate("ViewControllerDialog", "View Control Dialog", 0, QApplication::UnicodeUTF8));
        LabelViewControlRotation->setText(QApplication::translate("ViewControllerDialog", "Rotation", 0, QApplication::UnicodeUTF8));
        LabelViewControlRotationX->setText(QApplication::translate("ViewControllerDialog", "X", 0, QApplication::UnicodeUTF8));
        PushButtonViewControlRotationXYPlane->setText(QApplication::translate("ViewControllerDialog", "XY", 0, QApplication::UnicodeUTF8));
        LabelViewControlRotationY->setText(QApplication::translate("ViewControllerDialog", "Y", 0, QApplication::UnicodeUTF8));
        PushButtonViewControlRotationYZPlane->setText(QApplication::translate("ViewControllerDialog", "YZ", 0, QApplication::UnicodeUTF8));
        LabelViewControlRotationZ->setText(QApplication::translate("ViewControllerDialog", "Z", 0, QApplication::UnicodeUTF8));
        PushButtonViewControlRotationZXPlane->setText(QApplication::translate("ViewControllerDialog", "ZX", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ViewControllerDialog: public Ui_ViewControllerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CVIEWCONTROLLERDIALOG_H
