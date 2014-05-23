/********************************************************************************
** Form generated from reading UI file 'UIWindowSwitcher.ui'
**
** Created: Thu Dec 9 21:44:35 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CWINDOWSWITCHER_H
#define CWINDOWSWITCHER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowSwitcher
{
public:
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *PushButtonStackImageController;
    QPushButton *PushButtonExtractedDataController;
    QPushButton *PushButtonHandtraceController;
    QPushButton *PushButtonShapeView;
    QPushButton *PushButtonOrthoView;

    void setupUi(QWidget *WindowSwitcher)
    {
        if (WindowSwitcher->objectName().isEmpty())
            WindowSwitcher->setObjectName(QString::fromUtf8("WindowSwitcher"));
        WindowSwitcher->resize(567, 86);
        gridLayoutWidget = new QWidget(WindowSwitcher);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(0, 0, 561, 81));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        PushButtonStackImageController = new QPushButton(gridLayoutWidget);
        PushButtonStackImageController->setObjectName(QString::fromUtf8("PushButtonStackImageController"));

        gridLayout->addWidget(PushButtonStackImageController, 0, 0, 1, 1);

        PushButtonExtractedDataController = new QPushButton(gridLayoutWidget);
        PushButtonExtractedDataController->setObjectName(QString::fromUtf8("PushButtonExtractedDataController"));

        gridLayout->addWidget(PushButtonExtractedDataController, 0, 1, 1, 1);

        PushButtonHandtraceController = new QPushButton(gridLayoutWidget);
        PushButtonHandtraceController->setObjectName(QString::fromUtf8("PushButtonHandtraceController"));

        gridLayout->addWidget(PushButtonHandtraceController, 0, 2, 1, 1);

        PushButtonShapeView = new QPushButton(gridLayoutWidget);
        PushButtonShapeView->setObjectName(QString::fromUtf8("PushButtonShapeView"));

        gridLayout->addWidget(PushButtonShapeView, 1, 0, 1, 1);

        PushButtonOrthoView = new QPushButton(gridLayoutWidget);
        PushButtonOrthoView->setObjectName(QString::fromUtf8("PushButtonOrthoView"));

        gridLayout->addWidget(PushButtonOrthoView, 1, 2, 1, 1);


        retranslateUi(WindowSwitcher);

        QMetaObject::connectSlotsByName(WindowSwitcher);
    } // setupUi

    void retranslateUi(QWidget *WindowSwitcher)
    {
        WindowSwitcher->setWindowTitle(QApplication::translate("WindowSwitcher", "Form", 0, QApplication::UnicodeUTF8));
        PushButtonStackImageController->setText(QApplication::translate("WindowSwitcher", "Stack Image Controller", 0, QApplication::UnicodeUTF8));
        PushButtonExtractedDataController->setText(QApplication::translate("WindowSwitcher", "Extracted Data Controller", 0, QApplication::UnicodeUTF8));
        PushButtonHandtraceController->setText(QApplication::translate("WindowSwitcher", "Handtrace Controller", 0, QApplication::UnicodeUTF8));
        PushButtonShapeView->setText(QApplication::translate("WindowSwitcher", "Shape View", 0, QApplication::UnicodeUTF8));
        PushButtonOrthoView->setText(QApplication::translate("WindowSwitcher", "Ortho View", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WindowSwitcher: public Ui_WindowSwitcher {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CWINDOWSWITCHER_H
