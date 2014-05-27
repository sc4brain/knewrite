/********************************************************************************
** Form generated from reading UI file 'UIHandTracingToolDialog.ui'
**
** Created: Sun Jan 30 18:21:38 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CHANDTRACINGTOOLDIALOG_H
#define CHANDTRACINGTOOLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_HandTracingToolDialog
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *GroupBoxNodeList;
    QFormLayout *formLayout_3;
    QTableView *TableViewNodeList;
    QHBoxLayout *HorizontalLayoutShow;
    QSpacerItem *HorizontalSpacerShow;
    QCheckBox *CheckBoxShow;
    QCheckBox *CheckBoxSubbranchMode;
    QCheckBox *CheckBoxLocalViewMode;
    QPushButton *PushButtonClearNodeList;
    QGroupBox *GroupBoxNodeParameters;
    QGridLayout *gridLayout_2;
    QGridLayout *GridLayoutNodeParameters;
    QVBoxLayout *VerticalLayoutNodeParametersX;
    QLabel *LabelNodeParametersX;
    QSlider *VerticalSliderX;
    QSpinBox *SpinBoxX;
    QVBoxLayout *VerticalLayoutNodeParametersY;
    QLabel *LabelNodeParametersY;
    QSlider *VerticalSliderY;
    QSpinBox *SpinBoxY;
    QVBoxLayout *VerticalLayoutNodeParametersZ;
    QLabel *LabelNodeParametersZ;
    QSlider *VerticalSliderZ;
    QSpinBox *SpinBoxZ;
    QVBoxLayout *VerticalLayoutNodeParametersDiam;
    QLabel *LabelNodeParametersDiam;
    QSlider *VerticalSliderDiam;
    QDoubleSpinBox *DoubleSpinBoxDiam;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *PushButtonAdd;
    QPushButton *PushButtonDelete;
    QSpacerItem *horizontalSpacer;
    QPushButton *PushButtonDeleteSubbranch;
    QHBoxLayout *horizontalLayout;
    QPushButton *PushButtonPrevBranchingPoint;
    QPushButton *PushButtonNextBranchingPoint;
    QVBoxLayout *verticalLayout;
    QGridLayout *GridLayoutDataIO;
    QSpinBox *SpinBoxTargetStoreNo;
    QPushButton *PushButtonStore;
    QSpinBox *SpinBoxExtractedDataNo;
    QPushButton *PushButtonGetExtractedData;
    QSpinBox *SpinBoxStackImageDataNo;
    QPushButton *PushButtonGetStackImageData;
    QSpinBox *SpinBoxStoreSubbranchNo;
    QPushButton *PushButtonStoreSubbranch;
    QSpacerItem *verticalSpacer;
    QGridLayout *gridLayout;
    QSpacerItem *HorizontalSpacerClose;
    QPushButton *PushButtonClose;

    void setupUi(QDialog *HandTracingToolDialog)
    {
        if (HandTracingToolDialog->objectName().isEmpty())
            HandTracingToolDialog->setObjectName(QString::fromUtf8("HandTracingToolDialog"));
        HandTracingToolDialog->resize(573, 582);
        gridLayout_3 = new QGridLayout(HandTracingToolDialog);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        GroupBoxNodeList = new QGroupBox(HandTracingToolDialog);
        GroupBoxNodeList->setObjectName(QString::fromUtf8("GroupBoxNodeList"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(5);
        sizePolicy.setHeightForWidth(GroupBoxNodeList->sizePolicy().hasHeightForWidth());
        GroupBoxNodeList->setSizePolicy(sizePolicy);
        GroupBoxNodeList->setMinimumSize(QSize(0, 120));
        formLayout_3 = new QFormLayout(GroupBoxNodeList);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        TableViewNodeList = new QTableView(GroupBoxNodeList);
        TableViewNodeList->setObjectName(QString::fromUtf8("TableViewNodeList"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(8);
        sizePolicy1.setHeightForWidth(TableViewNodeList->sizePolicy().hasHeightForWidth());
        TableViewNodeList->setSizePolicy(sizePolicy1);
        TableViewNodeList->setMinimumSize(QSize(0, 20));

        formLayout_3->setWidget(1, QFormLayout::FieldRole, TableViewNodeList);

        HorizontalLayoutShow = new QHBoxLayout();
        HorizontalLayoutShow->setObjectName(QString::fromUtf8("HorizontalLayoutShow"));
        HorizontalSpacerShow = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutShow->addItem(HorizontalSpacerShow);

        CheckBoxShow = new QCheckBox(GroupBoxNodeList);
        CheckBoxShow->setObjectName(QString::fromUtf8("CheckBoxShow"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(CheckBoxShow->sizePolicy().hasHeightForWidth());
        CheckBoxShow->setSizePolicy(sizePolicy2);

        HorizontalLayoutShow->addWidget(CheckBoxShow);

        CheckBoxSubbranchMode = new QCheckBox(GroupBoxNodeList);
        CheckBoxSubbranchMode->setObjectName(QString::fromUtf8("CheckBoxSubbranchMode"));

        HorizontalLayoutShow->addWidget(CheckBoxSubbranchMode);

        CheckBoxLocalViewMode = new QCheckBox(GroupBoxNodeList);
        CheckBoxLocalViewMode->setObjectName(QString::fromUtf8("CheckBoxLocalViewMode"));

        HorizontalLayoutShow->addWidget(CheckBoxLocalViewMode);

        PushButtonClearNodeList = new QPushButton(GroupBoxNodeList);
        PushButtonClearNodeList->setObjectName(QString::fromUtf8("PushButtonClearNodeList"));

        HorizontalLayoutShow->addWidget(PushButtonClearNodeList);


        formLayout_3->setLayout(2, QFormLayout::FieldRole, HorizontalLayoutShow);


        gridLayout_3->addWidget(GroupBoxNodeList, 0, 0, 1, 2);

        GroupBoxNodeParameters = new QGroupBox(HandTracingToolDialog);
        GroupBoxNodeParameters->setObjectName(QString::fromUtf8("GroupBoxNodeParameters"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(5);
        sizePolicy3.setVerticalStretch(5);
        sizePolicy3.setHeightForWidth(GroupBoxNodeParameters->sizePolicy().hasHeightForWidth());
        GroupBoxNodeParameters->setSizePolicy(sizePolicy3);
        GroupBoxNodeParameters->setMinimumSize(QSize(100, 200));
        GroupBoxNodeParameters->setMaximumSize(QSize(16777215, 400));
        gridLayout_2 = new QGridLayout(GroupBoxNodeParameters);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        GridLayoutNodeParameters = new QGridLayout();
        GridLayoutNodeParameters->setObjectName(QString::fromUtf8("GridLayoutNodeParameters"));
        VerticalLayoutNodeParametersX = new QVBoxLayout();
        VerticalLayoutNodeParametersX->setObjectName(QString::fromUtf8("VerticalLayoutNodeParametersX"));
        LabelNodeParametersX = new QLabel(GroupBoxNodeParameters);
        LabelNodeParametersX->setObjectName(QString::fromUtf8("LabelNodeParametersX"));
        LabelNodeParametersX->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        VerticalLayoutNodeParametersX->addWidget(LabelNodeParametersX);

        VerticalSliderX = new QSlider(GroupBoxNodeParameters);
        VerticalSliderX->setObjectName(QString::fromUtf8("VerticalSliderX"));
        VerticalSliderX->setOrientation(Qt::Vertical);

        VerticalLayoutNodeParametersX->addWidget(VerticalSliderX);

        SpinBoxX = new QSpinBox(GroupBoxNodeParameters);
        SpinBoxX->setObjectName(QString::fromUtf8("SpinBoxX"));

        VerticalLayoutNodeParametersX->addWidget(SpinBoxX);


        GridLayoutNodeParameters->addLayout(VerticalLayoutNodeParametersX, 0, 1, 1, 1);

        VerticalLayoutNodeParametersY = new QVBoxLayout();
        VerticalLayoutNodeParametersY->setObjectName(QString::fromUtf8("VerticalLayoutNodeParametersY"));
        LabelNodeParametersY = new QLabel(GroupBoxNodeParameters);
        LabelNodeParametersY->setObjectName(QString::fromUtf8("LabelNodeParametersY"));
        LabelNodeParametersY->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        VerticalLayoutNodeParametersY->addWidget(LabelNodeParametersY);

        VerticalSliderY = new QSlider(GroupBoxNodeParameters);
        VerticalSliderY->setObjectName(QString::fromUtf8("VerticalSliderY"));
        VerticalSliderY->setOrientation(Qt::Vertical);

        VerticalLayoutNodeParametersY->addWidget(VerticalSliderY);

        SpinBoxY = new QSpinBox(GroupBoxNodeParameters);
        SpinBoxY->setObjectName(QString::fromUtf8("SpinBoxY"));

        VerticalLayoutNodeParametersY->addWidget(SpinBoxY);


        GridLayoutNodeParameters->addLayout(VerticalLayoutNodeParametersY, 0, 3, 1, 1);

        VerticalLayoutNodeParametersZ = new QVBoxLayout();
        VerticalLayoutNodeParametersZ->setObjectName(QString::fromUtf8("VerticalLayoutNodeParametersZ"));
        LabelNodeParametersZ = new QLabel(GroupBoxNodeParameters);
        LabelNodeParametersZ->setObjectName(QString::fromUtf8("LabelNodeParametersZ"));
        LabelNodeParametersZ->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        VerticalLayoutNodeParametersZ->addWidget(LabelNodeParametersZ);

        VerticalSliderZ = new QSlider(GroupBoxNodeParameters);
        VerticalSliderZ->setObjectName(QString::fromUtf8("VerticalSliderZ"));
        VerticalSliderZ->setOrientation(Qt::Vertical);

        VerticalLayoutNodeParametersZ->addWidget(VerticalSliderZ);

        SpinBoxZ = new QSpinBox(GroupBoxNodeParameters);
        SpinBoxZ->setObjectName(QString::fromUtf8("SpinBoxZ"));

        VerticalLayoutNodeParametersZ->addWidget(SpinBoxZ);


        GridLayoutNodeParameters->addLayout(VerticalLayoutNodeParametersZ, 0, 4, 1, 1);

        VerticalLayoutNodeParametersDiam = new QVBoxLayout();
        VerticalLayoutNodeParametersDiam->setObjectName(QString::fromUtf8("VerticalLayoutNodeParametersDiam"));
        LabelNodeParametersDiam = new QLabel(GroupBoxNodeParameters);
        LabelNodeParametersDiam->setObjectName(QString::fromUtf8("LabelNodeParametersDiam"));
        LabelNodeParametersDiam->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        VerticalLayoutNodeParametersDiam->addWidget(LabelNodeParametersDiam);

        VerticalSliderDiam = new QSlider(GroupBoxNodeParameters);
        VerticalSliderDiam->setObjectName(QString::fromUtf8("VerticalSliderDiam"));
        VerticalSliderDiam->setMaximum(10000);
        VerticalSliderDiam->setSingleStep(10);
        VerticalSliderDiam->setPageStep(100);
        VerticalSliderDiam->setOrientation(Qt::Vertical);

        VerticalLayoutNodeParametersDiam->addWidget(VerticalSliderDiam);

        DoubleSpinBoxDiam = new QDoubleSpinBox(GroupBoxNodeParameters);
        DoubleSpinBoxDiam->setObjectName(QString::fromUtf8("DoubleSpinBoxDiam"));
        DoubleSpinBoxDiam->setMaximum(50);
        DoubleSpinBoxDiam->setSingleStep(0.1);

        VerticalLayoutNodeParametersDiam->addWidget(DoubleSpinBoxDiam);


        GridLayoutNodeParameters->addLayout(VerticalLayoutNodeParametersDiam, 0, 5, 1, 1);


        gridLayout_2->addLayout(GridLayoutNodeParameters, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        PushButtonAdd = new QPushButton(GroupBoxNodeParameters);
        PushButtonAdd->setObjectName(QString::fromUtf8("PushButtonAdd"));

        horizontalLayout_2->addWidget(PushButtonAdd);

        PushButtonDelete = new QPushButton(GroupBoxNodeParameters);
        PushButtonDelete->setObjectName(QString::fromUtf8("PushButtonDelete"));

        horizontalLayout_2->addWidget(PushButtonDelete);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        PushButtonDeleteSubbranch = new QPushButton(GroupBoxNodeParameters);
        PushButtonDeleteSubbranch->setObjectName(QString::fromUtf8("PushButtonDeleteSubbranch"));

        horizontalLayout_2->addWidget(PushButtonDeleteSubbranch);


        gridLayout_2->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        PushButtonPrevBranchingPoint = new QPushButton(GroupBoxNodeParameters);
        PushButtonPrevBranchingPoint->setObjectName(QString::fromUtf8("PushButtonPrevBranchingPoint"));

        horizontalLayout->addWidget(PushButtonPrevBranchingPoint);

        PushButtonNextBranchingPoint = new QPushButton(GroupBoxNodeParameters);
        PushButtonNextBranchingPoint->setObjectName(QString::fromUtf8("PushButtonNextBranchingPoint"));

        horizontalLayout->addWidget(PushButtonNextBranchingPoint);


        gridLayout_2->addLayout(horizontalLayout, 2, 0, 1, 1);


        gridLayout_3->addWidget(GroupBoxNodeParameters, 1, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        GridLayoutDataIO = new QGridLayout();
        GridLayoutDataIO->setObjectName(QString::fromUtf8("GridLayoutDataIO"));
        GridLayoutDataIO->setSizeConstraint(QLayout::SetFixedSize);
        SpinBoxTargetStoreNo = new QSpinBox(HandTracingToolDialog);
        SpinBoxTargetStoreNo->setObjectName(QString::fromUtf8("SpinBoxTargetStoreNo"));

        GridLayoutDataIO->addWidget(SpinBoxTargetStoreNo, 2, 0, 1, 1);

        PushButtonStore = new QPushButton(HandTracingToolDialog);
        PushButtonStore->setObjectName(QString::fromUtf8("PushButtonStore"));

        GridLayoutDataIO->addWidget(PushButtonStore, 2, 1, 1, 1);

        SpinBoxExtractedDataNo = new QSpinBox(HandTracingToolDialog);
        SpinBoxExtractedDataNo->setObjectName(QString::fromUtf8("SpinBoxExtractedDataNo"));

        GridLayoutDataIO->addWidget(SpinBoxExtractedDataNo, 1, 0, 1, 1);

        PushButtonGetExtractedData = new QPushButton(HandTracingToolDialog);
        PushButtonGetExtractedData->setObjectName(QString::fromUtf8("PushButtonGetExtractedData"));

        GridLayoutDataIO->addWidget(PushButtonGetExtractedData, 1, 1, 1, 1);

        SpinBoxStackImageDataNo = new QSpinBox(HandTracingToolDialog);
        SpinBoxStackImageDataNo->setObjectName(QString::fromUtf8("SpinBoxStackImageDataNo"));

        GridLayoutDataIO->addWidget(SpinBoxStackImageDataNo, 0, 0, 1, 1);

        PushButtonGetStackImageData = new QPushButton(HandTracingToolDialog);
        PushButtonGetStackImageData->setObjectName(QString::fromUtf8("PushButtonGetStackImageData"));

        GridLayoutDataIO->addWidget(PushButtonGetStackImageData, 0, 1, 1, 1);

        SpinBoxStoreSubbranchNo = new QSpinBox(HandTracingToolDialog);
        SpinBoxStoreSubbranchNo->setObjectName(QString::fromUtf8("SpinBoxStoreSubbranchNo"));

        GridLayoutDataIO->addWidget(SpinBoxStoreSubbranchNo, 3, 0, 1, 1);

        PushButtonStoreSubbranch = new QPushButton(HandTracingToolDialog);
        PushButtonStoreSubbranch->setObjectName(QString::fromUtf8("PushButtonStoreSubbranch"));

        GridLayoutDataIO->addWidget(PushButtonStoreSubbranch, 3, 1, 1, 1);


        verticalLayout->addLayout(GridLayoutDataIO);

        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Maximum);

        verticalLayout->addItem(verticalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        HorizontalSpacerClose = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(HorizontalSpacerClose, 0, 0, 1, 1);

        PushButtonClose = new QPushButton(HandTracingToolDialog);
        PushButtonClose->setObjectName(QString::fromUtf8("PushButtonClose"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(PushButtonClose->sizePolicy().hasHeightForWidth());
        PushButtonClose->setSizePolicy(sizePolicy4);
        PushButtonClose->setMinimumSize(QSize(50, 0));

        gridLayout->addWidget(PushButtonClose, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);


        gridLayout_3->addLayout(verticalLayout, 1, 1, 1, 1);

        QWidget::setTabOrder(TableViewNodeList, CheckBoxShow);
        QWidget::setTabOrder(CheckBoxShow, CheckBoxSubbranchMode);
        QWidget::setTabOrder(CheckBoxSubbranchMode, CheckBoxLocalViewMode);
        QWidget::setTabOrder(CheckBoxLocalViewMode, PushButtonClearNodeList);
        QWidget::setTabOrder(PushButtonClearNodeList, VerticalSliderX);
        QWidget::setTabOrder(VerticalSliderX, VerticalSliderY);
        QWidget::setTabOrder(VerticalSliderY, VerticalSliderZ);
        QWidget::setTabOrder(VerticalSliderZ, VerticalSliderDiam);
        QWidget::setTabOrder(VerticalSliderDiam, SpinBoxX);
        QWidget::setTabOrder(SpinBoxX, SpinBoxY);
        QWidget::setTabOrder(SpinBoxY, SpinBoxZ);
        QWidget::setTabOrder(SpinBoxZ, DoubleSpinBoxDiam);
        QWidget::setTabOrder(DoubleSpinBoxDiam, PushButtonAdd);
        QWidget::setTabOrder(PushButtonAdd, PushButtonDelete);
        QWidget::setTabOrder(PushButtonDelete, PushButtonDeleteSubbranch);
        QWidget::setTabOrder(PushButtonDeleteSubbranch, SpinBoxStackImageDataNo);
        QWidget::setTabOrder(SpinBoxStackImageDataNo, PushButtonGetStackImageData);
        QWidget::setTabOrder(PushButtonGetStackImageData, SpinBoxExtractedDataNo);
        QWidget::setTabOrder(SpinBoxExtractedDataNo, PushButtonGetExtractedData);
        QWidget::setTabOrder(PushButtonGetExtractedData, SpinBoxTargetStoreNo);
        QWidget::setTabOrder(SpinBoxTargetStoreNo, PushButtonStore);
        QWidget::setTabOrder(PushButtonStore, PushButtonClose);

        retranslateUi(HandTracingToolDialog);

        QMetaObject::connectSlotsByName(HandTracingToolDialog);
    } // setupUi

    void retranslateUi(QDialog *HandTracingToolDialog)
    {
        HandTracingToolDialog->setWindowTitle(QApplication::translate("HandTracingToolDialog", "Manual Tracing Tool", 0));
        GroupBoxNodeList->setTitle(QApplication::translate("HandTracingToolDialog", "Node List", 0));
        CheckBoxShow->setText(QApplication::translate("HandTracingToolDialog", "Show", 0));
        CheckBoxSubbranchMode->setText(QApplication::translate("HandTracingToolDialog", "Subbranch Mode", 0));
        CheckBoxLocalViewMode->setText(QApplication::translate("HandTracingToolDialog", "Local View Mode", 0));
        PushButtonClearNodeList->setText(QApplication::translate("HandTracingToolDialog", "All Clear", 0));
        GroupBoxNodeParameters->setTitle(QApplication::translate("HandTracingToolDialog", "Current Node's Parameters", 0));
        LabelNodeParametersX->setText(QApplication::translate("HandTracingToolDialog", "X", 0));
        LabelNodeParametersY->setText(QApplication::translate("HandTracingToolDialog", "Y", 0));
        LabelNodeParametersZ->setText(QApplication::translate("HandTracingToolDialog", "Z", 0));
        LabelNodeParametersDiam->setText(QApplication::translate("HandTracingToolDialog", "Diam", 0));
        PushButtonAdd->setText(QApplication::translate("HandTracingToolDialog", "Add", 0));
        PushButtonDelete->setText(QApplication::translate("HandTracingToolDialog", "Delete", 0));
        PushButtonDeleteSubbranch->setText(QApplication::translate("HandTracingToolDialog", "Del. Subbranch", 0));
        PushButtonPrevBranchingPoint->setText(QApplication::translate("HandTracingToolDialog", "<", 0));
        PushButtonNextBranchingPoint->setText(QApplication::translate("HandTracingToolDialog", ">", 0));
        PushButtonStore->setText(QApplication::translate("HandTracingToolDialog", "Store Extracted Data", 0));
        PushButtonGetExtractedData->setText(QApplication::translate("HandTracingToolDialog", "Get Extracted Data", 0));
        PushButtonGetStackImageData->setText(QApplication::translate("HandTracingToolDialog", "Get Stack Image Data ", 0));
        PushButtonStoreSubbranch->setText(QApplication::translate("HandTracingToolDialog", "Store Subbranch", 0));
        PushButtonClose->setText(QApplication::translate("HandTracingToolDialog", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class HandTracingToolDialog: public Ui_HandTracingToolDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CHANDTRACINGTOOLDIALOG_H
