/********************************************************************************
** Form generated from reading UI file 'UIExtractedDataControllerDialog.ui'
**
** Created: Sun Jan 30 18:21:35 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CEXTRACTEDDATACONTROLLERDIALOG_H
#define CEXTRACTEDDATACONTROLLERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExtractedDataControllerDialog
{
public:
    QGridLayout *gridLayout_15;
    QTabWidget *Tabs;
    QWidget *TabFileLoad;
    QGridLayout *gridLayout_7;
    QGridLayout *GridLayoutFileLoad;
    QLabel *LabelFileLoadFilePath;
    QLineEdit *LineEditFileLoadFilePath;
    QPushButton *PushButtonFileLoadBrowse;
    QLabel *LabelFileLoadDirectory;
    QLabel *LabelFileLoadBaseName;
    QLineEdit *LineEditFileLoadDirectory;
    QLineEdit *LineEditFileLoadFileName;
    QLabel *LabelFileLoadLoadTo;
    QHBoxLayout *HorizontalLayoutFileLoadStoreTo;
    QLabel *LabelFileLoadEXtractedDataNo;
    QSpinBox *SpinBoxFileLoadDataNo;
    QSpacerItem *HorizontalSpacerFileLoadStoreTo;
    QHBoxLayout *HorizontalLayoutFileLoad;
    QSpacerItem *HorizontalSpacerFileLoadBottom;
    QPushButton *PushButtonFileLoadClear;
    QPushButton *PushButtonFileLoadLoad;
    QSpacerItem *VerticalSpacerFileLoad;
    QWidget *TabFileSave;
    QGridLayout *gridLayout_8;
    QSpacerItem *VerticalSpacerFileSave;
    QHBoxLayout *HorizontalLayoutFileSaveBottom;
    QSpacerItem *HorizontalSpacerFileSaveBottom;
    QPushButton *PushButtonFileSaveClear;
    QPushButton *PushButtonFileSaveSave;
    QGridLayout *GridLayoutFileSave;
    QLabel *LabelFileSaveFilePath;
    QLineEdit *LineEditFileSaveFilePath;
    QPushButton *PushButtonFileSaveBrowse;
    QLabel *LabelFileSaveDirectory;
    QLabel *LabelFileSaveBaseName;
    QLineEdit *LineEditFileSaveDirectory;
    QLineEdit *LineEditFileSaveFileName;
    QHBoxLayout *HorizontalLayoutFileSaveDataNo;
    QSpinBox *SpinBoxFileSaveDataNo;
    QSpacerItem *HorizontalSpacerFileSaveDataNo;
    QLabel *LabelFileSaveSaveFrom;
    QLabel *LabelFileSaveFileFormat;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *ComboBoxFileSaveFileFormat;
    QSpacerItem *horizontalSpacer;
    QWidget *TabProcessing;
    QGridLayout *gridLayout_2;
    QGroupBox *GroupBoxProcessingMergeData;
    QGridLayout *gridLayout_3;
    QGridLayout *GridLayoutProcessingMergeData;
    QLabel *LabelProcessingMergeDataParent;
    QLabel *LabelProcessingMergeDataChild;
    QGridLayout *GridLayoutProcessingMergeDataChild;
    QSpinBox *SpinBoxProcessingMergeDataChildDataNo;
    QComboBox *ComboBoxProcessingMergeDataChildNodeNo;
    QLabel *LabelProcessingMergeDataChildDataNo;
    QLabel *LabelProcessingMergeDataChildNodeNo;
    QLabel *LabelProcessingMergeDataTarget;
    QGridLayout *GridLayoutProcessingMergeDataParent;
    QSpinBox *SpinBoxProcessingMergeDataParentDataNo;
    QComboBox *ComboBoxProcessingMergeDataParentNodeNo;
    QLabel *LabelProcessingMergeDataParentDataNo;
    QLabel *LabelProcessingMergeDataParentNodeNo;
    QVBoxLayout *verticalLayout_3;
    QLabel *LabelProcessingMergeDataTargetToSaveExtractedDataNo;
    QSpinBox *SpinBoxProcessingMergeDataTargetDataNo;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *HorizontalSpacerProcessingMergeData;
    QPushButton *PushButtonProcessingMergeDataMerge;
    QGroupBox *GroupBoxProcessingCompareData;
    QGridLayout *gridLayout;
    QFormLayout *FormLayoutProcessingCompareData;
    QLabel *LabelProcessingCompareDataDataNo1;
    QLabel *LabelProcessingCompareDataDataNo2;
    QHBoxLayout *HorizontalLayoutProcessingCompareDataData1;
    QSpinBox *SpinBoxProcessingCompareDataDataNo1;
    QSpacerItem *HorizontalSpacerProcessingCompareDataDataNo1;
    QHBoxLayout *HorizontalLayoutProcessingCompareDataDataNo2;
    QSpinBox *SpinBoxProcessingCompareDataDataNo2;
    QSpacerItem *HorizontalSpacerProcessingCompareDataDataNo2;
    QLabel *LabelProcessingCompareDataFilePath;
    QHBoxLayout *horizontalLayout;
    QLineEdit *LineEditProcessingCompareDataFilePath;
    QPushButton *PushButtonProcessingCompareDataBrowse;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *PushButtonProcessingCompareDataCompare;
    QSpacerItem *VerticalSpacerProcessig;
    QWidget *TabViewControl;
    QGridLayout *gridLayout_14;
    QHBoxLayout *horizontalLayout_8;
    QHBoxLayout *HorizontalLayoutViewControlUpper;
    QLabel *LabelViewControlDataNo;
    QSpinBox *SpinBoxViewControlDataNo;
    QCheckBox *CheckBoxViewControlShow;
    QSpacerItem *HorizontalSpacerViewControlMore;
    QPushButton *PushButtonViewControlMore;
    QHBoxLayout *HorizontalLayoutViewControlMain;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_13;
    QTableView *TableViewViewControlNodeList;
    QGroupBox *GroupBoxViewControlPointer;
    QGridLayout *gridLayout_12;
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout_7;
    QLabel *LabelViewControlPointerX;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_14;
    QSlider *VerticalSliderViewControlPointerXum;
    QSpacerItem *horizontalSpacer_15;
    QLineEdit *LineEditViewControlPointerXum;
    QVBoxLayout *verticalLayout_8;
    QLabel *LabelViewControlPointerY;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_16;
    QSlider *VerticalSliderViewControlPointerYum;
    QSpacerItem *horizontalSpacer_17;
    QLineEdit *LineEditViewControlPointerYum;
    QVBoxLayout *verticalLayout_9;
    QLabel *LabelViewControlPointerZ;
    QHBoxLayout *horizontalLayout_16;
    QSpacerItem *horizontalSpacer_18;
    QSlider *VerticalSliderViewControlPointerZum;
    QSpacerItem *horizontalSpacer_19;
    QLineEdit *LineEditViewControlPointerZum;
    QVBoxLayout *verticalLayout;
    QCheckBox *CheckBoxViewControlPointer;
    QSpacerItem *verticalSpacer_4;
    QGroupBox *GroupBoxViewControlTranslation;
    QGridLayout *gridLayout_11;
    QHBoxLayout *HorizontalLayoutViewControlTranslation;
    QVBoxLayout *VerticalLayoutViewControlTranslationX;
    QLabel *LabelViewControlTranslationX;
    QHBoxLayout *HorizontalLayoutViewControlTranslationX;
    QSpacerItem *HorizontalSpacerViewControlTranslationX1;
    QSlider *VerticalSliderViewControlTranslationX;
    QSpacerItem *HorizontalSpacerViewControlTranslationX2;
    QLineEdit *LineEditViewControlTranslationX;
    QLineEdit *LineEditViewControlTranslationXum;
    QVBoxLayout *verticalLayout_14;
    QLabel *LabelViewControlTranslationY;
    QHBoxLayout *HorizontalLayoutViewControleTranslationY;
    QSpacerItem *HorizontalSpacerViewControlTranslationY1;
    QSlider *VerticalSliderViewControlTranslationY;
    QSpacerItem *HorizontalSpacerViewControlTranslationY2;
    QLineEdit *LineEditViewControlTranslationY;
    QLineEdit *LineEditViewControlTranslationYum;
    QVBoxLayout *VerticalLayoutViewControlTranslationZ;
    QLabel *LabelViewControlTranslationZ;
    QHBoxLayout *HorizontalLayoutViewControlTranslationZ;
    QSpacerItem *HorizontalSpacerViewControlTranslationZ1;
    QSlider *VerticalSliderViewControlTranslationZ;
    QSpacerItem *HorizontalSpacerViewControlTranslationZ2;
    QLineEdit *LineEditViewControlTranslationZ;
    QLineEdit *LineEditViewControlTranslationZum;
    QWidget *TabProperties;
    QWidget *gridLayoutWidget_4;
    QGridLayout *GridLayoutProperties;
    QLabel *LabelPropertiesImageNum;
    QLabel *LabelPropertiesImageSize;
    QLabel *LabelPropertiesDirectory;
    QLabel *LabelPropertiesImageName;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *LineEditPropertiesImageNum;
    QLineEdit *LineEditPropertiesImageSize;
    QLineEdit *LineEditPropertiesDirectory;
    QLineEdit *LineEditPropertiesImageName;

    void setupUi(QWidget *ExtractedDataControllerDialog)
    {
        if (ExtractedDataControllerDialog->objectName().isEmpty())
            ExtractedDataControllerDialog->setObjectName(QString::fromUtf8("ExtractedDataControllerDialog"));
        ExtractedDataControllerDialog->resize(818, 476);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ExtractedDataControllerDialog->sizePolicy().hasHeightForWidth());
        ExtractedDataControllerDialog->setSizePolicy(sizePolicy);
        gridLayout_15 = new QGridLayout(ExtractedDataControllerDialog);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        Tabs = new QTabWidget(ExtractedDataControllerDialog);
        Tabs->setObjectName(QString::fromUtf8("Tabs"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(Tabs->sizePolicy().hasHeightForWidth());
        Tabs->setSizePolicy(sizePolicy1);
        Tabs->setMinimumSize(QSize(400, 300));
        Tabs->setMaximumSize(QSize(800, 16777215));
        TabFileLoad = new QWidget();
        TabFileLoad->setObjectName(QString::fromUtf8("TabFileLoad"));
        gridLayout_7 = new QGridLayout(TabFileLoad);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        GridLayoutFileLoad = new QGridLayout();
        GridLayoutFileLoad->setObjectName(QString::fromUtf8("GridLayoutFileLoad"));
        LabelFileLoadFilePath = new QLabel(TabFileLoad);
        LabelFileLoadFilePath->setObjectName(QString::fromUtf8("LabelFileLoadFilePath"));

        GridLayoutFileLoad->addWidget(LabelFileLoadFilePath, 0, 0, 1, 1);

        LineEditFileLoadFilePath = new QLineEdit(TabFileLoad);
        LineEditFileLoadFilePath->setObjectName(QString::fromUtf8("LineEditFileLoadFilePath"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(LineEditFileLoadFilePath->sizePolicy().hasHeightForWidth());
        LineEditFileLoadFilePath->setSizePolicy(sizePolicy2);

        GridLayoutFileLoad->addWidget(LineEditFileLoadFilePath, 0, 1, 1, 1);

        PushButtonFileLoadBrowse = new QPushButton(TabFileLoad);
        PushButtonFileLoadBrowse->setObjectName(QString::fromUtf8("PushButtonFileLoadBrowse"));

        GridLayoutFileLoad->addWidget(PushButtonFileLoadBrowse, 0, 2, 1, 1);

        LabelFileLoadDirectory = new QLabel(TabFileLoad);
        LabelFileLoadDirectory->setObjectName(QString::fromUtf8("LabelFileLoadDirectory"));

        GridLayoutFileLoad->addWidget(LabelFileLoadDirectory, 2, 0, 1, 1);

        LabelFileLoadBaseName = new QLabel(TabFileLoad);
        LabelFileLoadBaseName->setObjectName(QString::fromUtf8("LabelFileLoadBaseName"));

        GridLayoutFileLoad->addWidget(LabelFileLoadBaseName, 3, 0, 1, 1);

        LineEditFileLoadDirectory = new QLineEdit(TabFileLoad);
        LineEditFileLoadDirectory->setObjectName(QString::fromUtf8("LineEditFileLoadDirectory"));
        sizePolicy2.setHeightForWidth(LineEditFileLoadDirectory->sizePolicy().hasHeightForWidth());
        LineEditFileLoadDirectory->setSizePolicy(sizePolicy2);
        LineEditFileLoadDirectory->setReadOnly(true);

        GridLayoutFileLoad->addWidget(LineEditFileLoadDirectory, 2, 1, 1, 1);

        LineEditFileLoadFileName = new QLineEdit(TabFileLoad);
        LineEditFileLoadFileName->setObjectName(QString::fromUtf8("LineEditFileLoadFileName"));
        sizePolicy2.setHeightForWidth(LineEditFileLoadFileName->sizePolicy().hasHeightForWidth());
        LineEditFileLoadFileName->setSizePolicy(sizePolicy2);
        LineEditFileLoadFileName->setReadOnly(true);

        GridLayoutFileLoad->addWidget(LineEditFileLoadFileName, 3, 1, 1, 1);

        LabelFileLoadLoadTo = new QLabel(TabFileLoad);
        LabelFileLoadLoadTo->setObjectName(QString::fromUtf8("LabelFileLoadLoadTo"));

        GridLayoutFileLoad->addWidget(LabelFileLoadLoadTo, 4, 0, 1, 1);

        HorizontalLayoutFileLoadStoreTo = new QHBoxLayout();
        HorizontalLayoutFileLoadStoreTo->setObjectName(QString::fromUtf8("HorizontalLayoutFileLoadStoreTo"));
        LabelFileLoadEXtractedDataNo = new QLabel(TabFileLoad);
        LabelFileLoadEXtractedDataNo->setObjectName(QString::fromUtf8("LabelFileLoadEXtractedDataNo"));

        HorizontalLayoutFileLoadStoreTo->addWidget(LabelFileLoadEXtractedDataNo);

        SpinBoxFileLoadDataNo = new QSpinBox(TabFileLoad);
        SpinBoxFileLoadDataNo->setObjectName(QString::fromUtf8("SpinBoxFileLoadDataNo"));

        HorizontalLayoutFileLoadStoreTo->addWidget(SpinBoxFileLoadDataNo);

        HorizontalSpacerFileLoadStoreTo = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutFileLoadStoreTo->addItem(HorizontalSpacerFileLoadStoreTo);


        GridLayoutFileLoad->addLayout(HorizontalLayoutFileLoadStoreTo, 4, 1, 1, 1);


        gridLayout_7->addLayout(GridLayoutFileLoad, 0, 0, 1, 1);

        HorizontalLayoutFileLoad = new QHBoxLayout();
        HorizontalLayoutFileLoad->setObjectName(QString::fromUtf8("HorizontalLayoutFileLoad"));
        HorizontalSpacerFileLoadBottom = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutFileLoad->addItem(HorizontalSpacerFileLoadBottom);

        PushButtonFileLoadClear = new QPushButton(TabFileLoad);
        PushButtonFileLoadClear->setObjectName(QString::fromUtf8("PushButtonFileLoadClear"));

        HorizontalLayoutFileLoad->addWidget(PushButtonFileLoadClear);

        PushButtonFileLoadLoad = new QPushButton(TabFileLoad);
        PushButtonFileLoadLoad->setObjectName(QString::fromUtf8("PushButtonFileLoadLoad"));

        HorizontalLayoutFileLoad->addWidget(PushButtonFileLoadLoad);


        gridLayout_7->addLayout(HorizontalLayoutFileLoad, 2, 0, 1, 1);

        VerticalSpacerFileLoad = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(VerticalSpacerFileLoad, 1, 0, 1, 1);

        Tabs->addTab(TabFileLoad, QString());
        TabFileSave = new QWidget();
        TabFileSave->setObjectName(QString::fromUtf8("TabFileSave"));
        gridLayout_8 = new QGridLayout(TabFileSave);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        VerticalSpacerFileSave = new QSpacerItem(20, 196, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(VerticalSpacerFileSave, 1, 0, 1, 1);

        HorizontalLayoutFileSaveBottom = new QHBoxLayout();
        HorizontalLayoutFileSaveBottom->setObjectName(QString::fromUtf8("HorizontalLayoutFileSaveBottom"));
        HorizontalSpacerFileSaveBottom = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutFileSaveBottom->addItem(HorizontalSpacerFileSaveBottom);

        PushButtonFileSaveClear = new QPushButton(TabFileSave);
        PushButtonFileSaveClear->setObjectName(QString::fromUtf8("PushButtonFileSaveClear"));

        HorizontalLayoutFileSaveBottom->addWidget(PushButtonFileSaveClear);

        PushButtonFileSaveSave = new QPushButton(TabFileSave);
        PushButtonFileSaveSave->setObjectName(QString::fromUtf8("PushButtonFileSaveSave"));

        HorizontalLayoutFileSaveBottom->addWidget(PushButtonFileSaveSave);


        gridLayout_8->addLayout(HorizontalLayoutFileSaveBottom, 2, 0, 1, 1);

        GridLayoutFileSave = new QGridLayout();
        GridLayoutFileSave->setObjectName(QString::fromUtf8("GridLayoutFileSave"));
        LabelFileSaveFilePath = new QLabel(TabFileSave);
        LabelFileSaveFilePath->setObjectName(QString::fromUtf8("LabelFileSaveFilePath"));

        GridLayoutFileSave->addWidget(LabelFileSaveFilePath, 1, 0, 1, 1);

        LineEditFileSaveFilePath = new QLineEdit(TabFileSave);
        LineEditFileSaveFilePath->setObjectName(QString::fromUtf8("LineEditFileSaveFilePath"));
        sizePolicy2.setHeightForWidth(LineEditFileSaveFilePath->sizePolicy().hasHeightForWidth());
        LineEditFileSaveFilePath->setSizePolicy(sizePolicy2);

        GridLayoutFileSave->addWidget(LineEditFileSaveFilePath, 1, 2, 1, 1);

        PushButtonFileSaveBrowse = new QPushButton(TabFileSave);
        PushButtonFileSaveBrowse->setObjectName(QString::fromUtf8("PushButtonFileSaveBrowse"));

        GridLayoutFileSave->addWidget(PushButtonFileSaveBrowse, 1, 3, 1, 1);

        LabelFileSaveDirectory = new QLabel(TabFileSave);
        LabelFileSaveDirectory->setObjectName(QString::fromUtf8("LabelFileSaveDirectory"));

        GridLayoutFileSave->addWidget(LabelFileSaveDirectory, 3, 0, 1, 1);

        LabelFileSaveBaseName = new QLabel(TabFileSave);
        LabelFileSaveBaseName->setObjectName(QString::fromUtf8("LabelFileSaveBaseName"));

        GridLayoutFileSave->addWidget(LabelFileSaveBaseName, 4, 0, 1, 1);

        LineEditFileSaveDirectory = new QLineEdit(TabFileSave);
        LineEditFileSaveDirectory->setObjectName(QString::fromUtf8("LineEditFileSaveDirectory"));
        sizePolicy2.setHeightForWidth(LineEditFileSaveDirectory->sizePolicy().hasHeightForWidth());
        LineEditFileSaveDirectory->setSizePolicy(sizePolicy2);
        LineEditFileSaveDirectory->setReadOnly(false);

        GridLayoutFileSave->addWidget(LineEditFileSaveDirectory, 3, 2, 1, 1);

        LineEditFileSaveFileName = new QLineEdit(TabFileSave);
        LineEditFileSaveFileName->setObjectName(QString::fromUtf8("LineEditFileSaveFileName"));
        sizePolicy2.setHeightForWidth(LineEditFileSaveFileName->sizePolicy().hasHeightForWidth());
        LineEditFileSaveFileName->setSizePolicy(sizePolicy2);
        LineEditFileSaveFileName->setReadOnly(false);

        GridLayoutFileSave->addWidget(LineEditFileSaveFileName, 4, 2, 1, 1);

        HorizontalLayoutFileSaveDataNo = new QHBoxLayout();
        HorizontalLayoutFileSaveDataNo->setObjectName(QString::fromUtf8("HorizontalLayoutFileSaveDataNo"));
        SpinBoxFileSaveDataNo = new QSpinBox(TabFileSave);
        SpinBoxFileSaveDataNo->setObjectName(QString::fromUtf8("SpinBoxFileSaveDataNo"));

        HorizontalLayoutFileSaveDataNo->addWidget(SpinBoxFileSaveDataNo);

        HorizontalSpacerFileSaveDataNo = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutFileSaveDataNo->addItem(HorizontalSpacerFileSaveDataNo);


        GridLayoutFileSave->addLayout(HorizontalLayoutFileSaveDataNo, 0, 2, 1, 1);

        LabelFileSaveSaveFrom = new QLabel(TabFileSave);
        LabelFileSaveSaveFrom->setObjectName(QString::fromUtf8("LabelFileSaveSaveFrom"));

        GridLayoutFileSave->addWidget(LabelFileSaveSaveFrom, 0, 0, 1, 1);

        LabelFileSaveFileFormat = new QLabel(TabFileSave);
        LabelFileSaveFileFormat->setObjectName(QString::fromUtf8("LabelFileSaveFileFormat"));

        GridLayoutFileSave->addWidget(LabelFileSaveFileFormat, 5, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        ComboBoxFileSaveFileFormat = new QComboBox(TabFileSave);
        ComboBoxFileSaveFileFormat->setObjectName(QString::fromUtf8("ComboBoxFileSaveFileFormat"));

        horizontalLayout_3->addWidget(ComboBoxFileSaveFileFormat);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        GridLayoutFileSave->addLayout(horizontalLayout_3, 5, 2, 1, 1);


        gridLayout_8->addLayout(GridLayoutFileSave, 0, 0, 1, 1);

        Tabs->addTab(TabFileSave, QString());
        TabProcessing = new QWidget();
        TabProcessing->setObjectName(QString::fromUtf8("TabProcessing"));
        gridLayout_2 = new QGridLayout(TabProcessing);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        GroupBoxProcessingMergeData = new QGroupBox(TabProcessing);
        GroupBoxProcessingMergeData->setObjectName(QString::fromUtf8("GroupBoxProcessingMergeData"));
        sizePolicy.setHeightForWidth(GroupBoxProcessingMergeData->sizePolicy().hasHeightForWidth());
        GroupBoxProcessingMergeData->setSizePolicy(sizePolicy);
        GroupBoxProcessingMergeData->setMaximumSize(QSize(16777215, 150));
        gridLayout_3 = new QGridLayout(GroupBoxProcessingMergeData);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        GridLayoutProcessingMergeData = new QGridLayout();
        GridLayoutProcessingMergeData->setObjectName(QString::fromUtf8("GridLayoutProcessingMergeData"));
        LabelProcessingMergeDataParent = new QLabel(GroupBoxProcessingMergeData);
        LabelProcessingMergeDataParent->setObjectName(QString::fromUtf8("LabelProcessingMergeDataParent"));

        GridLayoutProcessingMergeData->addWidget(LabelProcessingMergeDataParent, 0, 0, 1, 1);

        LabelProcessingMergeDataChild = new QLabel(GroupBoxProcessingMergeData);
        LabelProcessingMergeDataChild->setObjectName(QString::fromUtf8("LabelProcessingMergeDataChild"));

        GridLayoutProcessingMergeData->addWidget(LabelProcessingMergeDataChild, 0, 1, 1, 1);

        GridLayoutProcessingMergeDataChild = new QGridLayout();
        GridLayoutProcessingMergeDataChild->setObjectName(QString::fromUtf8("GridLayoutProcessingMergeDataChild"));
        SpinBoxProcessingMergeDataChildDataNo = new QSpinBox(GroupBoxProcessingMergeData);
        SpinBoxProcessingMergeDataChildDataNo->setObjectName(QString::fromUtf8("SpinBoxProcessingMergeDataChildDataNo"));

        GridLayoutProcessingMergeDataChild->addWidget(SpinBoxProcessingMergeDataChildDataNo, 1, 0, 1, 1);

        ComboBoxProcessingMergeDataChildNodeNo = new QComboBox(GroupBoxProcessingMergeData);
        ComboBoxProcessingMergeDataChildNodeNo->setObjectName(QString::fromUtf8("ComboBoxProcessingMergeDataChildNodeNo"));

        GridLayoutProcessingMergeDataChild->addWidget(ComboBoxProcessingMergeDataChildNodeNo, 1, 1, 1, 1);

        LabelProcessingMergeDataChildDataNo = new QLabel(GroupBoxProcessingMergeData);
        LabelProcessingMergeDataChildDataNo->setObjectName(QString::fromUtf8("LabelProcessingMergeDataChildDataNo"));

        GridLayoutProcessingMergeDataChild->addWidget(LabelProcessingMergeDataChildDataNo, 0, 0, 1, 1);

        LabelProcessingMergeDataChildNodeNo = new QLabel(GroupBoxProcessingMergeData);
        LabelProcessingMergeDataChildNodeNo->setObjectName(QString::fromUtf8("LabelProcessingMergeDataChildNodeNo"));

        GridLayoutProcessingMergeDataChild->addWidget(LabelProcessingMergeDataChildNodeNo, 0, 1, 1, 1);


        GridLayoutProcessingMergeData->addLayout(GridLayoutProcessingMergeDataChild, 1, 1, 1, 1);

        LabelProcessingMergeDataTarget = new QLabel(GroupBoxProcessingMergeData);
        LabelProcessingMergeDataTarget->setObjectName(QString::fromUtf8("LabelProcessingMergeDataTarget"));

        GridLayoutProcessingMergeData->addWidget(LabelProcessingMergeDataTarget, 0, 2, 1, 1);

        GridLayoutProcessingMergeDataParent = new QGridLayout();
        GridLayoutProcessingMergeDataParent->setObjectName(QString::fromUtf8("GridLayoutProcessingMergeDataParent"));
        SpinBoxProcessingMergeDataParentDataNo = new QSpinBox(GroupBoxProcessingMergeData);
        SpinBoxProcessingMergeDataParentDataNo->setObjectName(QString::fromUtf8("SpinBoxProcessingMergeDataParentDataNo"));

        GridLayoutProcessingMergeDataParent->addWidget(SpinBoxProcessingMergeDataParentDataNo, 1, 0, 1, 1);

        ComboBoxProcessingMergeDataParentNodeNo = new QComboBox(GroupBoxProcessingMergeData);
        ComboBoxProcessingMergeDataParentNodeNo->setObjectName(QString::fromUtf8("ComboBoxProcessingMergeDataParentNodeNo"));

        GridLayoutProcessingMergeDataParent->addWidget(ComboBoxProcessingMergeDataParentNodeNo, 1, 1, 1, 1);

        LabelProcessingMergeDataParentDataNo = new QLabel(GroupBoxProcessingMergeData);
        LabelProcessingMergeDataParentDataNo->setObjectName(QString::fromUtf8("LabelProcessingMergeDataParentDataNo"));

        GridLayoutProcessingMergeDataParent->addWidget(LabelProcessingMergeDataParentDataNo, 0, 0, 1, 1);

        LabelProcessingMergeDataParentNodeNo = new QLabel(GroupBoxProcessingMergeData);
        LabelProcessingMergeDataParentNodeNo->setObjectName(QString::fromUtf8("LabelProcessingMergeDataParentNodeNo"));

        GridLayoutProcessingMergeDataParent->addWidget(LabelProcessingMergeDataParentNodeNo, 0, 1, 1, 1);


        GridLayoutProcessingMergeData->addLayout(GridLayoutProcessingMergeDataParent, 1, 0, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        LabelProcessingMergeDataTargetToSaveExtractedDataNo = new QLabel(GroupBoxProcessingMergeData);
        LabelProcessingMergeDataTargetToSaveExtractedDataNo->setObjectName(QString::fromUtf8("LabelProcessingMergeDataTargetToSaveExtractedDataNo"));

        verticalLayout_3->addWidget(LabelProcessingMergeDataTargetToSaveExtractedDataNo);

        SpinBoxProcessingMergeDataTargetDataNo = new QSpinBox(GroupBoxProcessingMergeData);
        SpinBoxProcessingMergeDataTargetDataNo->setObjectName(QString::fromUtf8("SpinBoxProcessingMergeDataTargetDataNo"));

        verticalLayout_3->addWidget(SpinBoxProcessingMergeDataTargetDataNo);


        GridLayoutProcessingMergeData->addLayout(verticalLayout_3, 1, 2, 1, 1);


        gridLayout_3->addLayout(GridLayoutProcessingMergeData, 0, 0, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(197, 78, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        HorizontalSpacerProcessingMergeData = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(HorizontalSpacerProcessingMergeData, 1, 0, 1, 1);

        PushButtonProcessingMergeDataMerge = new QPushButton(GroupBoxProcessingMergeData);
        PushButtonProcessingMergeDataMerge->setObjectName(QString::fromUtf8("PushButtonProcessingMergeDataMerge"));

        gridLayout_3->addWidget(PushButtonProcessingMergeDataMerge, 1, 1, 1, 1);


        gridLayout_2->addWidget(GroupBoxProcessingMergeData, 0, 0, 1, 1);

        GroupBoxProcessingCompareData = new QGroupBox(TabProcessing);
        GroupBoxProcessingCompareData->setObjectName(QString::fromUtf8("GroupBoxProcessingCompareData"));
        gridLayout = new QGridLayout(GroupBoxProcessingCompareData);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        FormLayoutProcessingCompareData = new QFormLayout();
        FormLayoutProcessingCompareData->setObjectName(QString::fromUtf8("FormLayoutProcessingCompareData"));
        LabelProcessingCompareDataDataNo1 = new QLabel(GroupBoxProcessingCompareData);
        LabelProcessingCompareDataDataNo1->setObjectName(QString::fromUtf8("LabelProcessingCompareDataDataNo1"));

        FormLayoutProcessingCompareData->setWidget(0, QFormLayout::LabelRole, LabelProcessingCompareDataDataNo1);

        LabelProcessingCompareDataDataNo2 = new QLabel(GroupBoxProcessingCompareData);
        LabelProcessingCompareDataDataNo2->setObjectName(QString::fromUtf8("LabelProcessingCompareDataDataNo2"));

        FormLayoutProcessingCompareData->setWidget(1, QFormLayout::LabelRole, LabelProcessingCompareDataDataNo2);

        HorizontalLayoutProcessingCompareDataData1 = new QHBoxLayout();
        HorizontalLayoutProcessingCompareDataData1->setObjectName(QString::fromUtf8("HorizontalLayoutProcessingCompareDataData1"));
        SpinBoxProcessingCompareDataDataNo1 = new QSpinBox(GroupBoxProcessingCompareData);
        SpinBoxProcessingCompareDataDataNo1->setObjectName(QString::fromUtf8("SpinBoxProcessingCompareDataDataNo1"));

        HorizontalLayoutProcessingCompareDataData1->addWidget(SpinBoxProcessingCompareDataDataNo1);

        HorizontalSpacerProcessingCompareDataDataNo1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutProcessingCompareDataData1->addItem(HorizontalSpacerProcessingCompareDataDataNo1);


        FormLayoutProcessingCompareData->setLayout(0, QFormLayout::FieldRole, HorizontalLayoutProcessingCompareDataData1);

        HorizontalLayoutProcessingCompareDataDataNo2 = new QHBoxLayout();
        HorizontalLayoutProcessingCompareDataDataNo2->setObjectName(QString::fromUtf8("HorizontalLayoutProcessingCompareDataDataNo2"));
        SpinBoxProcessingCompareDataDataNo2 = new QSpinBox(GroupBoxProcessingCompareData);
        SpinBoxProcessingCompareDataDataNo2->setObjectName(QString::fromUtf8("SpinBoxProcessingCompareDataDataNo2"));

        HorizontalLayoutProcessingCompareDataDataNo2->addWidget(SpinBoxProcessingCompareDataDataNo2);

        HorizontalSpacerProcessingCompareDataDataNo2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutProcessingCompareDataDataNo2->addItem(HorizontalSpacerProcessingCompareDataDataNo2);


        FormLayoutProcessingCompareData->setLayout(1, QFormLayout::FieldRole, HorizontalLayoutProcessingCompareDataDataNo2);

        LabelProcessingCompareDataFilePath = new QLabel(GroupBoxProcessingCompareData);
        LabelProcessingCompareDataFilePath->setObjectName(QString::fromUtf8("LabelProcessingCompareDataFilePath"));

        FormLayoutProcessingCompareData->setWidget(2, QFormLayout::LabelRole, LabelProcessingCompareDataFilePath);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        LineEditProcessingCompareDataFilePath = new QLineEdit(GroupBoxProcessingCompareData);
        LineEditProcessingCompareDataFilePath->setObjectName(QString::fromUtf8("LineEditProcessingCompareDataFilePath"));

        horizontalLayout->addWidget(LineEditProcessingCompareDataFilePath);

        PushButtonProcessingCompareDataBrowse = new QPushButton(GroupBoxProcessingCompareData);
        PushButtonProcessingCompareDataBrowse->setObjectName(QString::fromUtf8("PushButtonProcessingCompareDataBrowse"));

        horizontalLayout->addWidget(PushButtonProcessingCompareDataBrowse);


        FormLayoutProcessingCompareData->setLayout(2, QFormLayout::FieldRole, horizontalLayout);


        gridLayout->addLayout(FormLayoutProcessingCompareData, 0, 0, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(324, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(325, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        PushButtonProcessingCompareDataCompare = new QPushButton(GroupBoxProcessingCompareData);
        PushButtonProcessingCompareDataCompare->setObjectName(QString::fromUtf8("PushButtonProcessingCompareDataCompare"));

        gridLayout->addWidget(PushButtonProcessingCompareDataCompare, 1, 1, 1, 1);


        gridLayout_2->addWidget(GroupBoxProcessingCompareData, 1, 0, 1, 1);

        VerticalSpacerProcessig = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(VerticalSpacerProcessig, 2, 0, 1, 1);

        Tabs->addTab(TabProcessing, QString());
        TabViewControl = new QWidget();
        TabViewControl->setObjectName(QString::fromUtf8("TabViewControl"));
        gridLayout_14 = new QGridLayout(TabViewControl);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        HorizontalLayoutViewControlUpper = new QHBoxLayout();
        HorizontalLayoutViewControlUpper->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlUpper"));
        LabelViewControlDataNo = new QLabel(TabViewControl);
        LabelViewControlDataNo->setObjectName(QString::fromUtf8("LabelViewControlDataNo"));

        HorizontalLayoutViewControlUpper->addWidget(LabelViewControlDataNo);

        SpinBoxViewControlDataNo = new QSpinBox(TabViewControl);
        SpinBoxViewControlDataNo->setObjectName(QString::fromUtf8("SpinBoxViewControlDataNo"));
        SpinBoxViewControlDataNo->setMaximum(9);

        HorizontalLayoutViewControlUpper->addWidget(SpinBoxViewControlDataNo);

        CheckBoxViewControlShow = new QCheckBox(TabViewControl);
        CheckBoxViewControlShow->setObjectName(QString::fromUtf8("CheckBoxViewControlShow"));

        HorizontalLayoutViewControlUpper->addWidget(CheckBoxViewControlShow);


        horizontalLayout_8->addLayout(HorizontalLayoutViewControlUpper);

        HorizontalSpacerViewControlMore = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(HorizontalSpacerViewControlMore);

        PushButtonViewControlMore = new QPushButton(TabViewControl);
        PushButtonViewControlMore->setObjectName(QString::fromUtf8("PushButtonViewControlMore"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(PushButtonViewControlMore->sizePolicy().hasHeightForWidth());
        PushButtonViewControlMore->setSizePolicy(sizePolicy3);
        PushButtonViewControlMore->setCheckable(true);
        PushButtonViewControlMore->setChecked(false);
        PushButtonViewControlMore->setDefault(false);

        horizontalLayout_8->addWidget(PushButtonViewControlMore);


        gridLayout_14->addLayout(horizontalLayout_8, 0, 0, 1, 1);

        HorizontalLayoutViewControlMain = new QHBoxLayout();
        HorizontalLayoutViewControlMain->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlMain"));
        groupBox_4 = new QGroupBox(TabViewControl);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy4.setHorizontalStretch(6);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy4);
        gridLayout_13 = new QGridLayout(groupBox_4);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        TableViewViewControlNodeList = new QTableView(groupBox_4);
        TableViewViewControlNodeList->setObjectName(QString::fromUtf8("TableViewViewControlNodeList"));

        gridLayout_13->addWidget(TableViewViewControlNodeList, 0, 0, 1, 1);


        HorizontalLayoutViewControlMain->addWidget(groupBox_4);

        GroupBoxViewControlPointer = new QGroupBox(TabViewControl);
        GroupBoxViewControlPointer->setObjectName(QString::fromUtf8("GroupBoxViewControlPointer"));
        GroupBoxViewControlPointer->setEnabled(false);
        QSizePolicy sizePolicy5(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy5.setHorizontalStretch(2);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(GroupBoxViewControlPointer->sizePolicy().hasHeightForWidth());
        GroupBoxViewControlPointer->setSizePolicy(sizePolicy5);
        gridLayout_12 = new QGridLayout(GroupBoxViewControlPointer);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        LabelViewControlPointerX = new QLabel(GroupBoxViewControlPointer);
        LabelViewControlPointerX->setObjectName(QString::fromUtf8("LabelViewControlPointerX"));
        LabelViewControlPointerX->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(LabelViewControlPointerX);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalSpacer_14 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_14);

        VerticalSliderViewControlPointerXum = new QSlider(GroupBoxViewControlPointer);
        VerticalSliderViewControlPointerXum->setObjectName(QString::fromUtf8("VerticalSliderViewControlPointerXum"));
        VerticalSliderViewControlPointerXum->setMinimum(-300);
        VerticalSliderViewControlPointerXum->setMaximum(300);
        VerticalSliderViewControlPointerXum->setOrientation(Qt::Vertical);

        horizontalLayout_14->addWidget(VerticalSliderViewControlPointerXum);

        horizontalSpacer_15 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_15);


        verticalLayout_7->addLayout(horizontalLayout_14);

        LineEditViewControlPointerXum = new QLineEdit(GroupBoxViewControlPointer);
        LineEditViewControlPointerXum->setObjectName(QString::fromUtf8("LineEditViewControlPointerXum"));

        verticalLayout_7->addWidget(LineEditViewControlPointerXum);


        horizontalLayout_13->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        LabelViewControlPointerY = new QLabel(GroupBoxViewControlPointer);
        LabelViewControlPointerY->setObjectName(QString::fromUtf8("LabelViewControlPointerY"));
        LabelViewControlPointerY->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(LabelViewControlPointerY);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalSpacer_16 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_16);

        VerticalSliderViewControlPointerYum = new QSlider(GroupBoxViewControlPointer);
        VerticalSliderViewControlPointerYum->setObjectName(QString::fromUtf8("VerticalSliderViewControlPointerYum"));
        VerticalSliderViewControlPointerYum->setMinimum(-300);
        VerticalSliderViewControlPointerYum->setMaximum(300);
        VerticalSliderViewControlPointerYum->setOrientation(Qt::Vertical);

        horizontalLayout_15->addWidget(VerticalSliderViewControlPointerYum);

        horizontalSpacer_17 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_17);


        verticalLayout_8->addLayout(horizontalLayout_15);

        LineEditViewControlPointerYum = new QLineEdit(GroupBoxViewControlPointer);
        LineEditViewControlPointerYum->setObjectName(QString::fromUtf8("LineEditViewControlPointerYum"));

        verticalLayout_8->addWidget(LineEditViewControlPointerYum);


        horizontalLayout_13->addLayout(verticalLayout_8);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        LabelViewControlPointerZ = new QLabel(GroupBoxViewControlPointer);
        LabelViewControlPointerZ->setObjectName(QString::fromUtf8("LabelViewControlPointerZ"));
        LabelViewControlPointerZ->setAlignment(Qt::AlignCenter);

        verticalLayout_9->addWidget(LabelViewControlPointerZ);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        horizontalSpacer_18 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_18);

        VerticalSliderViewControlPointerZum = new QSlider(GroupBoxViewControlPointer);
        VerticalSliderViewControlPointerZum->setObjectName(QString::fromUtf8("VerticalSliderViewControlPointerZum"));
        VerticalSliderViewControlPointerZum->setMinimum(-300);
        VerticalSliderViewControlPointerZum->setMaximum(300);
        VerticalSliderViewControlPointerZum->setOrientation(Qt::Vertical);

        horizontalLayout_16->addWidget(VerticalSliderViewControlPointerZum);

        horizontalSpacer_19 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_16->addItem(horizontalSpacer_19);


        verticalLayout_9->addLayout(horizontalLayout_16);

        LineEditViewControlPointerZum = new QLineEdit(GroupBoxViewControlPointer);
        LineEditViewControlPointerZum->setObjectName(QString::fromUtf8("LineEditViewControlPointerZum"));

        verticalLayout_9->addWidget(LineEditViewControlPointerZum);


        horizontalLayout_13->addLayout(verticalLayout_9);


        gridLayout_12->addLayout(horizontalLayout_13, 0, 3, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        CheckBoxViewControlPointer = new QCheckBox(GroupBoxViewControlPointer);
        CheckBoxViewControlPointer->setObjectName(QString::fromUtf8("CheckBoxViewControlPointer"));
        CheckBoxViewControlPointer->setChecked(true);

        verticalLayout->addWidget(CheckBoxViewControlPointer);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        gridLayout_12->addLayout(verticalLayout, 0, 0, 1, 1);


        HorizontalLayoutViewControlMain->addWidget(GroupBoxViewControlPointer);

        GroupBoxViewControlTranslation = new QGroupBox(TabViewControl);
        GroupBoxViewControlTranslation->setObjectName(QString::fromUtf8("GroupBoxViewControlTranslation"));
        GroupBoxViewControlTranslation->setEnabled(false);
        sizePolicy5.setHeightForWidth(GroupBoxViewControlTranslation->sizePolicy().hasHeightForWidth());
        GroupBoxViewControlTranslation->setSizePolicy(sizePolicy5);
        gridLayout_11 = new QGridLayout(GroupBoxViewControlTranslation);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        HorizontalLayoutViewControlTranslation = new QHBoxLayout();
        HorizontalLayoutViewControlTranslation->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlTranslation"));
        VerticalLayoutViewControlTranslationX = new QVBoxLayout();
        VerticalLayoutViewControlTranslationX->setObjectName(QString::fromUtf8("VerticalLayoutViewControlTranslationX"));
        LabelViewControlTranslationX = new QLabel(GroupBoxViewControlTranslation);
        LabelViewControlTranslationX->setObjectName(QString::fromUtf8("LabelViewControlTranslationX"));
        LabelViewControlTranslationX->setAlignment(Qt::AlignCenter);

        VerticalLayoutViewControlTranslationX->addWidget(LabelViewControlTranslationX);

        HorizontalLayoutViewControlTranslationX = new QHBoxLayout();
        HorizontalLayoutViewControlTranslationX->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlTranslationX"));
        HorizontalSpacerViewControlTranslationX1 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlTranslationX->addItem(HorizontalSpacerViewControlTranslationX1);

        VerticalSliderViewControlTranslationX = new QSlider(GroupBoxViewControlTranslation);
        VerticalSliderViewControlTranslationX->setObjectName(QString::fromUtf8("VerticalSliderViewControlTranslationX"));
        VerticalSliderViewControlTranslationX->setMinimum(-300);
        VerticalSliderViewControlTranslationX->setMaximum(300);
        VerticalSliderViewControlTranslationX->setOrientation(Qt::Vertical);

        HorizontalLayoutViewControlTranslationX->addWidget(VerticalSliderViewControlTranslationX);

        HorizontalSpacerViewControlTranslationX2 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlTranslationX->addItem(HorizontalSpacerViewControlTranslationX2);


        VerticalLayoutViewControlTranslationX->addLayout(HorizontalLayoutViewControlTranslationX);

        LineEditViewControlTranslationX = new QLineEdit(GroupBoxViewControlTranslation);
        LineEditViewControlTranslationX->setObjectName(QString::fromUtf8("LineEditViewControlTranslationX"));

        VerticalLayoutViewControlTranslationX->addWidget(LineEditViewControlTranslationX);

        LineEditViewControlTranslationXum = new QLineEdit(GroupBoxViewControlTranslation);
        LineEditViewControlTranslationXum->setObjectName(QString::fromUtf8("LineEditViewControlTranslationXum"));

        VerticalLayoutViewControlTranslationX->addWidget(LineEditViewControlTranslationXum);


        HorizontalLayoutViewControlTranslation->addLayout(VerticalLayoutViewControlTranslationX);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        LabelViewControlTranslationY = new QLabel(GroupBoxViewControlTranslation);
        LabelViewControlTranslationY->setObjectName(QString::fromUtf8("LabelViewControlTranslationY"));
        LabelViewControlTranslationY->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(LabelViewControlTranslationY);

        HorizontalLayoutViewControleTranslationY = new QHBoxLayout();
        HorizontalLayoutViewControleTranslationY->setObjectName(QString::fromUtf8("HorizontalLayoutViewControleTranslationY"));
        HorizontalSpacerViewControlTranslationY1 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControleTranslationY->addItem(HorizontalSpacerViewControlTranslationY1);

        VerticalSliderViewControlTranslationY = new QSlider(GroupBoxViewControlTranslation);
        VerticalSliderViewControlTranslationY->setObjectName(QString::fromUtf8("VerticalSliderViewControlTranslationY"));
        VerticalSliderViewControlTranslationY->setMinimum(-300);
        VerticalSliderViewControlTranslationY->setMaximum(300);
        VerticalSliderViewControlTranslationY->setOrientation(Qt::Vertical);

        HorizontalLayoutViewControleTranslationY->addWidget(VerticalSliderViewControlTranslationY);

        HorizontalSpacerViewControlTranslationY2 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControleTranslationY->addItem(HorizontalSpacerViewControlTranslationY2);


        verticalLayout_14->addLayout(HorizontalLayoutViewControleTranslationY);

        LineEditViewControlTranslationY = new QLineEdit(GroupBoxViewControlTranslation);
        LineEditViewControlTranslationY->setObjectName(QString::fromUtf8("LineEditViewControlTranslationY"));

        verticalLayout_14->addWidget(LineEditViewControlTranslationY);

        LineEditViewControlTranslationYum = new QLineEdit(GroupBoxViewControlTranslation);
        LineEditViewControlTranslationYum->setObjectName(QString::fromUtf8("LineEditViewControlTranslationYum"));

        verticalLayout_14->addWidget(LineEditViewControlTranslationYum);


        HorizontalLayoutViewControlTranslation->addLayout(verticalLayout_14);

        VerticalLayoutViewControlTranslationZ = new QVBoxLayout();
        VerticalLayoutViewControlTranslationZ->setObjectName(QString::fromUtf8("VerticalLayoutViewControlTranslationZ"));
        LabelViewControlTranslationZ = new QLabel(GroupBoxViewControlTranslation);
        LabelViewControlTranslationZ->setObjectName(QString::fromUtf8("LabelViewControlTranslationZ"));
        LabelViewControlTranslationZ->setAlignment(Qt::AlignCenter);

        VerticalLayoutViewControlTranslationZ->addWidget(LabelViewControlTranslationZ);

        HorizontalLayoutViewControlTranslationZ = new QHBoxLayout();
        HorizontalLayoutViewControlTranslationZ->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlTranslationZ"));
        HorizontalSpacerViewControlTranslationZ1 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlTranslationZ->addItem(HorizontalSpacerViewControlTranslationZ1);

        VerticalSliderViewControlTranslationZ = new QSlider(GroupBoxViewControlTranslation);
        VerticalSliderViewControlTranslationZ->setObjectName(QString::fromUtf8("VerticalSliderViewControlTranslationZ"));
        VerticalSliderViewControlTranslationZ->setMinimum(-300);
        VerticalSliderViewControlTranslationZ->setMaximum(300);
        VerticalSliderViewControlTranslationZ->setOrientation(Qt::Vertical);

        HorizontalLayoutViewControlTranslationZ->addWidget(VerticalSliderViewControlTranslationZ);

        HorizontalSpacerViewControlTranslationZ2 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlTranslationZ->addItem(HorizontalSpacerViewControlTranslationZ2);


        VerticalLayoutViewControlTranslationZ->addLayout(HorizontalLayoutViewControlTranslationZ);

        LineEditViewControlTranslationZ = new QLineEdit(GroupBoxViewControlTranslation);
        LineEditViewControlTranslationZ->setObjectName(QString::fromUtf8("LineEditViewControlTranslationZ"));

        VerticalLayoutViewControlTranslationZ->addWidget(LineEditViewControlTranslationZ);

        LineEditViewControlTranslationZum = new QLineEdit(GroupBoxViewControlTranslation);
        LineEditViewControlTranslationZum->setObjectName(QString::fromUtf8("LineEditViewControlTranslationZum"));

        VerticalLayoutViewControlTranslationZ->addWidget(LineEditViewControlTranslationZum);


        HorizontalLayoutViewControlTranslation->addLayout(VerticalLayoutViewControlTranslationZ);


        gridLayout_11->addLayout(HorizontalLayoutViewControlTranslation, 0, 0, 1, 1);


        HorizontalLayoutViewControlMain->addWidget(GroupBoxViewControlTranslation);


        gridLayout_14->addLayout(HorizontalLayoutViewControlMain, 1, 0, 1, 1);

        Tabs->addTab(TabViewControl, QString());
        TabProperties = new QWidget();
        TabProperties->setObjectName(QString::fromUtf8("TabProperties"));
        gridLayoutWidget_4 = new QWidget(TabProperties);
        gridLayoutWidget_4->setObjectName(QString::fromUtf8("gridLayoutWidget_4"));
        gridLayoutWidget_4->setGeometry(QRect(10, 10, 531, 401));
        GridLayoutProperties = new QGridLayout(gridLayoutWidget_4);
        GridLayoutProperties->setObjectName(QString::fromUtf8("GridLayoutProperties"));
        GridLayoutProperties->setContentsMargins(0, 0, 0, 0);
        LabelPropertiesImageNum = new QLabel(gridLayoutWidget_4);
        LabelPropertiesImageNum->setObjectName(QString::fromUtf8("LabelPropertiesImageNum"));

        GridLayoutProperties->addWidget(LabelPropertiesImageNum, 0, 1, 1, 1);

        LabelPropertiesImageSize = new QLabel(gridLayoutWidget_4);
        LabelPropertiesImageSize->setObjectName(QString::fromUtf8("LabelPropertiesImageSize"));

        GridLayoutProperties->addWidget(LabelPropertiesImageSize, 1, 1, 1, 1);

        LabelPropertiesDirectory = new QLabel(gridLayoutWidget_4);
        LabelPropertiesDirectory->setObjectName(QString::fromUtf8("LabelPropertiesDirectory"));

        GridLayoutProperties->addWidget(LabelPropertiesDirectory, 2, 1, 1, 1);

        LabelPropertiesImageName = new QLabel(gridLayoutWidget_4);
        LabelPropertiesImageName->setObjectName(QString::fromUtf8("LabelPropertiesImageName"));

        GridLayoutProperties->addWidget(LabelPropertiesImageName, 3, 1, 1, 1);

        label_5 = new QLabel(gridLayoutWidget_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        GridLayoutProperties->addWidget(label_5, 4, 1, 1, 1);

        label_6 = new QLabel(gridLayoutWidget_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        GridLayoutProperties->addWidget(label_6, 5, 1, 1, 1);

        label_7 = new QLabel(gridLayoutWidget_4);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        GridLayoutProperties->addWidget(label_7, 6, 1, 1, 1);

        label_8 = new QLabel(gridLayoutWidget_4);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        GridLayoutProperties->addWidget(label_8, 7, 1, 1, 1);

        label_9 = new QLabel(gridLayoutWidget_4);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        GridLayoutProperties->addWidget(label_9, 8, 1, 1, 1);

        label_10 = new QLabel(gridLayoutWidget_4);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        GridLayoutProperties->addWidget(label_10, 9, 1, 1, 1);

        label_11 = new QLabel(gridLayoutWidget_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        GridLayoutProperties->addWidget(label_11, 10, 1, 1, 1);

        LineEditPropertiesImageNum = new QLineEdit(gridLayoutWidget_4);
        LineEditPropertiesImageNum->setObjectName(QString::fromUtf8("LineEditPropertiesImageNum"));

        GridLayoutProperties->addWidget(LineEditPropertiesImageNum, 0, 2, 1, 1);

        LineEditPropertiesImageSize = new QLineEdit(gridLayoutWidget_4);
        LineEditPropertiesImageSize->setObjectName(QString::fromUtf8("LineEditPropertiesImageSize"));

        GridLayoutProperties->addWidget(LineEditPropertiesImageSize, 1, 2, 1, 1);

        LineEditPropertiesDirectory = new QLineEdit(gridLayoutWidget_4);
        LineEditPropertiesDirectory->setObjectName(QString::fromUtf8("LineEditPropertiesDirectory"));

        GridLayoutProperties->addWidget(LineEditPropertiesDirectory, 2, 2, 1, 1);

        LineEditPropertiesImageName = new QLineEdit(gridLayoutWidget_4);
        LineEditPropertiesImageName->setObjectName(QString::fromUtf8("LineEditPropertiesImageName"));

        GridLayoutProperties->addWidget(LineEditPropertiesImageName, 3, 2, 1, 1);

        Tabs->addTab(TabProperties, QString());

        gridLayout_15->addWidget(Tabs, 0, 0, 1, 1);

        QWidget::setTabOrder(Tabs, LineEditFileLoadFilePath);
        QWidget::setTabOrder(LineEditFileLoadFilePath, PushButtonFileLoadBrowse);
        QWidget::setTabOrder(PushButtonFileLoadBrowse, LineEditFileLoadDirectory);
        QWidget::setTabOrder(LineEditFileLoadDirectory, LineEditFileLoadFileName);
        QWidget::setTabOrder(LineEditFileLoadFileName, SpinBoxFileLoadDataNo);
        QWidget::setTabOrder(SpinBoxFileLoadDataNo, PushButtonFileLoadClear);
        QWidget::setTabOrder(PushButtonFileLoadClear, PushButtonFileLoadLoad);
        QWidget::setTabOrder(PushButtonFileLoadLoad, SpinBoxFileSaveDataNo);
        QWidget::setTabOrder(SpinBoxFileSaveDataNo, LineEditFileSaveFilePath);
        QWidget::setTabOrder(LineEditFileSaveFilePath, PushButtonFileSaveBrowse);
        QWidget::setTabOrder(PushButtonFileSaveBrowse, LineEditFileSaveDirectory);
        QWidget::setTabOrder(LineEditFileSaveDirectory, LineEditFileSaveFileName);
        QWidget::setTabOrder(LineEditFileSaveFileName, ComboBoxFileSaveFileFormat);
        QWidget::setTabOrder(ComboBoxFileSaveFileFormat, PushButtonFileSaveSave);
        QWidget::setTabOrder(PushButtonFileSaveSave, PushButtonFileSaveClear);
        QWidget::setTabOrder(PushButtonFileSaveClear, SpinBoxProcessingMergeDataParentDataNo);
        QWidget::setTabOrder(SpinBoxProcessingMergeDataParentDataNo, ComboBoxProcessingMergeDataParentNodeNo);
        QWidget::setTabOrder(ComboBoxProcessingMergeDataParentNodeNo, SpinBoxProcessingMergeDataChildDataNo);
        QWidget::setTabOrder(SpinBoxProcessingMergeDataChildDataNo, ComboBoxProcessingMergeDataChildNodeNo);
        QWidget::setTabOrder(ComboBoxProcessingMergeDataChildNodeNo, SpinBoxViewControlDataNo);
        QWidget::setTabOrder(SpinBoxViewControlDataNo, CheckBoxViewControlShow);
        QWidget::setTabOrder(CheckBoxViewControlShow, TableViewViewControlNodeList);
        QWidget::setTabOrder(TableViewViewControlNodeList, PushButtonViewControlMore);
        QWidget::setTabOrder(PushButtonViewControlMore, CheckBoxViewControlPointer);
        QWidget::setTabOrder(CheckBoxViewControlPointer, VerticalSliderViewControlPointerXum);
        QWidget::setTabOrder(VerticalSliderViewControlPointerXum, VerticalSliderViewControlPointerYum);
        QWidget::setTabOrder(VerticalSliderViewControlPointerYum, VerticalSliderViewControlPointerZum);
        QWidget::setTabOrder(VerticalSliderViewControlPointerZum, LineEditViewControlPointerXum);
        QWidget::setTabOrder(LineEditViewControlPointerXum, LineEditViewControlPointerYum);
        QWidget::setTabOrder(LineEditViewControlPointerYum, LineEditViewControlPointerZum);
        QWidget::setTabOrder(LineEditViewControlPointerZum, VerticalSliderViewControlTranslationX);
        QWidget::setTabOrder(VerticalSliderViewControlTranslationX, VerticalSliderViewControlTranslationY);
        QWidget::setTabOrder(VerticalSliderViewControlTranslationY, VerticalSliderViewControlTranslationZ);
        QWidget::setTabOrder(VerticalSliderViewControlTranslationZ, LineEditViewControlTranslationX);
        QWidget::setTabOrder(LineEditViewControlTranslationX, LineEditViewControlTranslationY);
        QWidget::setTabOrder(LineEditViewControlTranslationY, LineEditViewControlTranslationZ);
        QWidget::setTabOrder(LineEditViewControlTranslationZ, LineEditViewControlTranslationXum);
        QWidget::setTabOrder(LineEditViewControlTranslationXum, LineEditViewControlTranslationYum);
        QWidget::setTabOrder(LineEditViewControlTranslationYum, LineEditViewControlTranslationZum);
        QWidget::setTabOrder(LineEditViewControlTranslationZum, LineEditPropertiesImageNum);
        QWidget::setTabOrder(LineEditPropertiesImageNum, LineEditPropertiesImageSize);
        QWidget::setTabOrder(LineEditPropertiesImageSize, LineEditPropertiesDirectory);
        QWidget::setTabOrder(LineEditPropertiesDirectory, LineEditPropertiesImageName);

        retranslateUi(ExtractedDataControllerDialog);
        QObject::connect(PushButtonViewControlMore, SIGNAL(toggled(bool)), GroupBoxViewControlPointer, SLOT(setVisible(bool)));
        QObject::connect(PushButtonViewControlMore, SIGNAL(toggled(bool)), GroupBoxViewControlTranslation, SLOT(setVisible(bool)));

        Tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ExtractedDataControllerDialog);
    } // setupUi

    void retranslateUi(QWidget *ExtractedDataControllerDialog)
    {
        ExtractedDataControllerDialog->setWindowTitle(QApplication::translate("ExtractedDataControllerDialog", "Extracted Data Controller", 0));
        LabelFileLoadFilePath->setText(QApplication::translate("ExtractedDataControllerDialog", "File Path", 0));
        PushButtonFileLoadBrowse->setText(QApplication::translate("ExtractedDataControllerDialog", "Browse", 0));
        LabelFileLoadDirectory->setText(QApplication::translate("ExtractedDataControllerDialog", "Directory", 0));
        LabelFileLoadBaseName->setText(QApplication::translate("ExtractedDataControllerDialog", "FileName", 0));
        LabelFileLoadLoadTo->setText(QApplication::translate("ExtractedDataControllerDialog", "Store to", 0));
        LabelFileLoadEXtractedDataNo->setText(QApplication::translate("ExtractedDataControllerDialog", "Extracted Data No", 0));
        PushButtonFileLoadClear->setText(QApplication::translate("ExtractedDataControllerDialog", "Clear", 0));
        PushButtonFileLoadLoad->setText(QApplication::translate("ExtractedDataControllerDialog", "Load", 0));
        Tabs->setTabText(Tabs->indexOf(TabFileLoad), QApplication::translate("ExtractedDataControllerDialog", "File Load", 0));
        PushButtonFileSaveClear->setText(QApplication::translate("ExtractedDataControllerDialog", "Clear", 0));
        PushButtonFileSaveSave->setText(QApplication::translate("ExtractedDataControllerDialog", "Save", 0));
        LabelFileSaveFilePath->setText(QApplication::translate("ExtractedDataControllerDialog", "File Path", 0));
        PushButtonFileSaveBrowse->setText(QApplication::translate("ExtractedDataControllerDialog", "Browse", 0));
        LabelFileSaveDirectory->setText(QApplication::translate("ExtractedDataControllerDialog", "Directory", 0));
        LabelFileSaveBaseName->setText(QApplication::translate("ExtractedDataControllerDialog", "File Name", 0));
        LabelFileSaveSaveFrom->setText(QApplication::translate("ExtractedDataControllerDialog", "Extracted Data No", 0));
        LabelFileSaveFileFormat->setText(QApplication::translate("ExtractedDataControllerDialog", "File Format", 0));
        Tabs->setTabText(Tabs->indexOf(TabFileSave), QApplication::translate("ExtractedDataControllerDialog", "File Save", 0));
        GroupBoxProcessingMergeData->setTitle(QApplication::translate("ExtractedDataControllerDialog", "Merge Data", 0));
        LabelProcessingMergeDataParent->setText(QApplication::translate("ExtractedDataControllerDialog", "Parent", 0));
        LabelProcessingMergeDataChild->setText(QApplication::translate("ExtractedDataControllerDialog", "Child", 0));
        LabelProcessingMergeDataChildDataNo->setText(QApplication::translate("ExtractedDataControllerDialog", "ExtractedDataNo", 0));
        LabelProcessingMergeDataChildNodeNo->setText(QApplication::translate("ExtractedDataControllerDialog", "NodeNo", 0));
        LabelProcessingMergeDataTarget->setText(QApplication::translate("ExtractedDataControllerDialog", "Target to save", 0));
        LabelProcessingMergeDataParentDataNo->setText(QApplication::translate("ExtractedDataControllerDialog", "ExtractedDataNo", 0));
        LabelProcessingMergeDataParentNodeNo->setText(QApplication::translate("ExtractedDataControllerDialog", "NodeNo", 0));
        LabelProcessingMergeDataTargetToSaveExtractedDataNo->setText(QApplication::translate("ExtractedDataControllerDialog", "ExtractedDataNo", 0));
        PushButtonProcessingMergeDataMerge->setText(QApplication::translate("ExtractedDataControllerDialog", "Merge", 0));
        GroupBoxProcessingCompareData->setTitle(QApplication::translate("ExtractedDataControllerDialog", "Compare Data", 0));
        LabelProcessingCompareDataDataNo1->setText(QApplication::translate("ExtractedDataControllerDialog", "Data No 1", 0));
        LabelProcessingCompareDataDataNo2->setText(QApplication::translate("ExtractedDataControllerDialog", "Data No 2", 0));
        LabelProcessingCompareDataFilePath->setText(QApplication::translate("ExtractedDataControllerDialog", "Output File", 0));
        PushButtonProcessingCompareDataBrowse->setText(QApplication::translate("ExtractedDataControllerDialog", "Browse", 0));
        PushButtonProcessingCompareDataCompare->setText(QApplication::translate("ExtractedDataControllerDialog", "Compare", 0));
        Tabs->setTabText(Tabs->indexOf(TabProcessing), QApplication::translate("ExtractedDataControllerDialog", "Processing", 0));
        LabelViewControlDataNo->setText(QApplication::translate("ExtractedDataControllerDialog", "ExtractedDataNo", 0));
        CheckBoxViewControlShow->setText(QApplication::translate("ExtractedDataControllerDialog", "Show", 0));
        PushButtonViewControlMore->setText(QApplication::translate("ExtractedDataControllerDialog", "&More", 0));
        groupBox_4->setTitle(QApplication::translate("ExtractedDataControllerDialog", "NodeList", 0));
        GroupBoxViewControlPointer->setTitle(QApplication::translate("ExtractedDataControllerDialog", "Pointer", 0));
        LabelViewControlPointerX->setText(QApplication::translate("ExtractedDataControllerDialog", "X", 0));
        LineEditViewControlPointerXum->setText(QApplication::translate("ExtractedDataControllerDialog", "0", 0));
        LabelViewControlPointerY->setText(QApplication::translate("ExtractedDataControllerDialog", "Y", 0));
        LineEditViewControlPointerYum->setText(QApplication::translate("ExtractedDataControllerDialog", "0", 0));
        LabelViewControlPointerZ->setText(QApplication::translate("ExtractedDataControllerDialog", "Z", 0));
        LineEditViewControlPointerZum->setText(QApplication::translate("ExtractedDataControllerDialog", "0", 0));
        CheckBoxViewControlPointer->setText(QString());
        GroupBoxViewControlTranslation->setTitle(QApplication::translate("ExtractedDataControllerDialog", "Translation", 0));
        LabelViewControlTranslationX->setText(QApplication::translate("ExtractedDataControllerDialog", "X", 0));
        LineEditViewControlTranslationX->setText(QApplication::translate("ExtractedDataControllerDialog", "0", 0));
        LineEditViewControlTranslationXum->setText(QApplication::translate("ExtractedDataControllerDialog", "0", 0));
        LabelViewControlTranslationY->setText(QApplication::translate("ExtractedDataControllerDialog", "Y", 0));
        LineEditViewControlTranslationY->setText(QApplication::translate("ExtractedDataControllerDialog", "0", 0));
        LineEditViewControlTranslationYum->setText(QApplication::translate("ExtractedDataControllerDialog", "0", 0));
        LabelViewControlTranslationZ->setText(QApplication::translate("ExtractedDataControllerDialog", "Z", 0));
        LineEditViewControlTranslationZ->setText(QApplication::translate("ExtractedDataControllerDialog", "0", 0));
        LineEditViewControlTranslationZum->setText(QApplication::translate("ExtractedDataControllerDialog", "0", 0));
        Tabs->setTabText(Tabs->indexOf(TabViewControl), QApplication::translate("ExtractedDataControllerDialog", "View Control", 0));
        LabelPropertiesImageNum->setText(QApplication::translate("ExtractedDataControllerDialog", "Cluster #", 0));
        LabelPropertiesImageSize->setText(QApplication::translate("ExtractedDataControllerDialog", "Voxel #", 0));
        LabelPropertiesDirectory->setText(QApplication::translate("ExtractedDataControllerDialog", "Directory", 0));
        LabelPropertiesImageName->setText(QApplication::translate("ExtractedDataControllerDialog", "File Name", 0));
        label_5->setText(QApplication::translate("ExtractedDataControllerDialog", "TextLabel", 0));
        label_6->setText(QApplication::translate("ExtractedDataControllerDialog", "TextLabel", 0));
        label_7->setText(QApplication::translate("ExtractedDataControllerDialog", "TextLabel", 0));
        label_8->setText(QApplication::translate("ExtractedDataControllerDialog", "TextLabel", 0));
        label_9->setText(QApplication::translate("ExtractedDataControllerDialog", "TextLabel", 0));
        label_10->setText(QApplication::translate("ExtractedDataControllerDialog", "TextLabel", 0));
        label_11->setText(QApplication::translate("ExtractedDataControllerDialog", "TextLabel", 0));
        Tabs->setTabText(Tabs->indexOf(TabProperties), QApplication::translate("ExtractedDataControllerDialog", "Properties", 0));
    } // retranslateUi

};

namespace Ui {
    class ExtractedDataControllerDialog: public Ui_ExtractedDataControllerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CEXTRACTEDDATACONTROLLERDIALOG_H
