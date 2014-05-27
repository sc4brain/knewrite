/********************************************************************************
** Form generated from reading UI file 'UITimerDialog.ui'
**
** Created: Wed Jan 26 15:37:28 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CTIMERDIALOG_H
#define CTIMERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TimerDialog
{
public:
    QGridLayout *gridLayout;
    QLCDNumber *LcdNumber;
    QPushButton *PushButtonStartStop;
    QPushButton *PushButtonClear;
    QPushButton *PushButtonSave;

    void setupUi(QDialog *TimerDialog)
    {
        if (TimerDialog->objectName().isEmpty())
            TimerDialog->setObjectName(QString::fromUtf8("TimerDialog"));
        TimerDialog->resize(285, 90);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TimerDialog->sizePolicy().hasHeightForWidth());
        TimerDialog->setSizePolicy(sizePolicy);
        TimerDialog->setMinimumSize(QSize(285, 90));
        TimerDialog->setMaximumSize(QSize(285, 90));
        gridLayout = new QGridLayout(TimerDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        LcdNumber = new QLCDNumber(TimerDialog);
        LcdNumber->setObjectName(QString::fromUtf8("LcdNumber"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(LcdNumber->sizePolicy().hasHeightForWidth());
        LcdNumber->setSizePolicy(sizePolicy1);
        LcdNumber->setNumDigits(13);
        LcdNumber->setSegmentStyle(QLCDNumber::Filled);

        gridLayout->addWidget(LcdNumber, 0, 0, 1, 3);

        PushButtonStartStop = new QPushButton(TimerDialog);
        PushButtonStartStop->setObjectName(QString::fromUtf8("PushButtonStartStop"));

        gridLayout->addWidget(PushButtonStartStop, 1, 0, 1, 1);

        PushButtonClear = new QPushButton(TimerDialog);
        PushButtonClear->setObjectName(QString::fromUtf8("PushButtonClear"));

        gridLayout->addWidget(PushButtonClear, 1, 1, 1, 1);

        PushButtonSave = new QPushButton(TimerDialog);
        PushButtonSave->setObjectName(QString::fromUtf8("PushButtonSave"));

        gridLayout->addWidget(PushButtonSave, 1, 2, 1, 1);


        retranslateUi(TimerDialog);

        QMetaObject::connectSlotsByName(TimerDialog);
    } // setupUi

    void retranslateUi(QDialog *TimerDialog)
    {
        TimerDialog->setWindowTitle(QApplication::translate("TimerDialog", "Timer", 0));
        PushButtonStartStop->setText(QApplication::translate("TimerDialog", "Start", 0));
        PushButtonClear->setText(QApplication::translate("TimerDialog", "Clear", 0));
        PushButtonSave->setText(QApplication::translate("TimerDialog", "Save", 0));
    } // retranslateUi

};

namespace Ui {
    class TimerDialog: public Ui_TimerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CTIMERDIALOG_H
