/********************************************************************************
** Form generated from reading UI file 'UIStackImageControllerDialog.ui'
**
** Created: Sun Jan 30 18:21:31 2011
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef CSTACKIMAGECONTROLLERDIALOG_H
#define CSTACKIMAGECONTROLLERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StackImageControllerDialog
{
public:
    QGridLayout *gridLayout_7;
    QTabWidget *Tabs;
    QWidget *TabFileLoad;
    QFormLayout *formLayout_4;
    QGridLayout *GridLayoutFileLoad;
    QLabel *LabelFileLoadFilePath;
    QLineEdit *LineEditFileLoadFilePath;
    QPushButton *PushButtonFileLoadBrowse;
    QLabel *LabelFileLoadDirectory;
    QLabel *LabelFileLoadBaseName;
    QLabel *LabelFileLoadScale;
    QHBoxLayout *HorizontalLayoutFileLoadScale;
    QLineEdit *LineEditFileLoadScaleX;
    QLabel *LabelFileLoadScaleCommaXY;
    QLineEdit *LineEditFileLoadScaleY;
    QLabel *LabelFileLoadScaleYZ;
    QLineEdit *LineEditFileLoadScaleZ;
    QSpacerItem *HorizontalSpacerFileLoadScale;
    QLabel *LabelFileLoadScaleUnit;
    QLineEdit *LineEditFileLoadDirectory;
    QLineEdit *LineEditFileLoadBaseName;
    QLabel *LabelFileLoadLoadTo;
    QHBoxLayout *HorizontalLayoutFileLoadDataNo;
    QLabel *LabelFileLoadStoreToStackImageDataNo;
    QSpinBox *SpinBoxFileLoadDataNo;
    QSpacerItem *HorizontalSpacerFileLoadDataNo;
    QHBoxLayout *HorizontalLayoutFileLoadExecutionButton;
    QSpacerItem *HorizontalSpacerFileLoadBottom;
    QPushButton *PushButtonFileLoadClear;
    QPushButton *PushButtonFileLoadLoad;
    QWidget *TabFileSave;
    QFormLayout *formLayout_3;
    QGridLayout *GridLayoutFileSave;
    QLabel *LabelFileSaveFilePath;
    QLineEdit *LineEditFileSaveFilePath;
    QPushButton *PushButtonFileSaveBrowse;
    QLabel *LabelFileSaveDirectory;
    QLabel *LabelFileSaveBaseName;
    QLineEdit *LineEditFileSaveDirectory;
    QLineEdit *LineEditFileSaveBaseName;
    QHBoxLayout *HorizontalLayoutFileSaveDataNo;
    QSpinBox *SpinBoxFileSaveDataNo;
    QSpacerItem *HorizontalSpacerDataNo;
    QLabel *LabelFileSaveDataNo;
    QHBoxLayout *HorizontalLayoutFileSaveBottom;
    QSpacerItem *HorizontalSpacerFileSaveBottom;
    QPushButton *PushButtonFileSaveClear;
    QPushButton *PushButtonFileSaveSave;
    QWidget *TabExtraction;
    QGridLayout *gridLayout_12;
    QHBoxLayout *HorizontalLayoutExtractionBottom;
    QSpacerItem *HorizontalSpacerExtractionBottom;
    QPushButton *PushButtonExtractionHandTracing;
    QPushButton *PushButtonExtractionCancel;
    QPushButton *PushButtonExtractionExtract;
    QGridLayout *GridLayoutExtraction;
    QLabel *LabelExtractionBinaryThreshold;
    QPushButton *PushButtonExtractionBinaryThresholdGetFromView;
    QLabel *LabelExtractionMedianFilter;
    QCheckBox *CheckBoxExtractionMedianFilter;
    QHBoxLayout *HorizontalLayoutExtractionBinaryThreshold;
    QSlider *HorizontalSliderExtractionBinaryThreshold;
    QLineEdit *LineEditExtractionBinaryThreshold;
    QLabel *LabelExtractionStartPoint;
    QHBoxLayout *HorizontalLayoutExtractionStartPoint;
    QLineEdit *LineEditExtractionStartPointX;
    QLabel *LabelExtractionStartPointCommaXY;
    QLineEdit *LineEditExtractionStartPointY;
    QLabel *LabelExtractionStartPointCommaYZ;
    QLineEdit *LineEditExtractionStartPointZ;
    QPushButton *PushButtonExtractionStartPointGetFromView;
    QLabel *LabelExtractionDataNo;
    QHBoxLayout *HorizontalLayoutExtractionDataNo;
    QSpinBox *SpinBoxExtractionDataNo;
    QSpacerItem *HorizontalSpacerExtractionDataNo;
    QPushButton *PushButtonExtractionCurrentDataNo;
    QLabel *LabelExtractionCalcProp;
    QCheckBox *CheckBoxExtractionCalcProp;
    QLineEdit *LineEditExtractionCalcPropFileName;
    QVBoxLayout *VerticalLayoutExtractionProp;
    QHBoxLayout *HorizontalLayoutExtractionPropStart;
    QLabel *LabelExtractionCalcPropStart;
    QSpinBox *SpinBoxExtractionCalcPropStartThreshold;
    QSpacerItem *HorizontalSpacerExtractionPropStart;
    QHBoxLayout *HorizontalLayoutExtractionPropStop;
    QLabel *LabelExtractionCalcPropStop;
    QSpinBox *SpinBoxExtractionCalcPropStopThreshold;
    QSpacerItem *HorizontalSpacerExtractionPropStop;
    QLabel *LabelExtractionTargetNo;
    QHBoxLayout *HorizontalLayoutExtractionTargetNo;
    QSpinBox *SpinBoxExtractionTargetNo;
    QSpacerItem *HorizontalSpacerExtractionTargetNo;
    QLabel *LabelExtractionROI;
    QCheckBox *CheckBoxExtractionROI;
    QLabel *LabelExtractionDoRescanning;
    QHBoxLayout *HorizontalLayoutExtractionDoRescanning;
    QCheckBox *CheckBoxExtractionDoRescanning;
    QSpacerItem *HorizontalSpacerExtractionDoRescanning1;
    QLabel *label;
    QSpinBox *SpinBoxExtractionDoRescanningStoreNo;
    QSpacerItem *HorizontalSpacerExtractionDoRescanning2;
    QWidget *TabImageProcessing;
    QGridLayout *gridLayout_13;
    QGroupBox *GroupBoxImageProcessingGenerateStackImage;
    QGridLayout *gridLayout_4;
    QGridLayout *GridLayoutImageProcessingGenerateStackImage;
    QLabel *LabelImageProcessingGenerateStackImageParam1;
    QDoubleSpinBox *DoubleSpinBoxImageProcessingGenerateStackImageParam1;
    QLabel *LabelImageProcessingGenerateStackImageParam2;
    QDoubleSpinBox *DoubleSpinBoxImageProcessingGenerateStackImageParam2;
    QLabel *LabelImageProcessingGenerateStackImageParam3;
    QDoubleSpinBox *DoubleSpinBoxImageProcessingGenerateStackImageParam3;
    QLabel *LabelImageProcessingGenerateStackImageParam4;
    QDoubleSpinBox *DoubleSpinBoxImageProcessingGenerateStackImageParam4;
    QComboBox *ComboBoxImageProcessingGenerateStackImageType;
    QSpinBox *SpinBoxImageProcessingGenerateStackImageDataNo;
    QLabel *LabelImageProcessingGenerateStackImageDataNo;
    QLabel *LabelImageProcessingGenerateStackImageType;
    QLabel *LabelImageProcessingGeneratStackImageParam5;
    QDoubleSpinBox *DoubleSpinBoxImageProcessingGenerateStackImageParam5;
    QSpacerItem *HorizontalSpacerImageProcessingGenerateStackImage;
    QPushButton *PushButtonImageProcessingGenerateStackImage;
    QGroupBox *GroupBoxImageProcessingNoise;
    QGridLayout *gridLayout_11;
    QFormLayout *FormLayoutImageProcessingNoise;
    QLabel *LabelImageProcessingNoiseSD;
    QDoubleSpinBox *DoubleSpinBoxImageProcessingNoiseSD;
    QSpinBox *SpinBoxImageProcessingNoiseDataNo;
    QLabel *LabelImageProcessingNoiseDataNo;
    QSpacerItem *HorizontalSpacerImageProcessingNoise;
    QPushButton *PushButtonImageProcessingNoiseAddNoise;
    QGroupBox *GroupBoxImageProcessingBackground;
    QGridLayout *gridLayout_6;
    QFormLayout *FormLayoutImageProcessingBackground;
    QLabel *LabelImageProcessingBackgroundDataNo;
    QSpinBox *SpinBoxImageProcessingBackgroundDataNo;
    QLabel *LabelImageProcessingBackgroundType;
    QComboBox *ComboBoxImageProcessingBackgroundType;
    QHBoxLayout *HorizontalLayoutImageProcessingBackgroundOrigin;
    QLineEdit *LineEditImageProcessingBackgroundOriginX;
    QLabel *LabelImageProcessingBackgroundOriginCommaXY;
    QLineEdit *LineEditImageProcessingBackgroundOriginY;
    QLabel *LabelImageProcessingBackgroundOriginYZ;
    QLineEdit *LineEditImageProcessingBackgroundOriginZ;
    QSpacerItem *HorizontalSpacerImageProcessingBackgroundOrigin;
    QHBoxLayout *HorizontalLayoutImageProcessingBackgroundNormalVector;
    QLineEdit *LineEditImageProcessingBackgroundNormalVectorX;
    QLabel *LabelImageProcessingBackgroundNormalVectorCommaXY;
    QLineEdit *LineEditImageProcessingBackgroundNormalVectorY;
    QLabel *LabelImageProcessingBackgroundNormalVectorYZ;
    QLineEdit *LineEditImageProcessingBackgroundNormalVectorZ;
    QSpacerItem *HorizontalSpacerImageProcessingBackgroundNormalVector;
    QDoubleSpinBox *DoubleSpinBoxImageProcessingBackgroundParameter;
    QLabel *LabelImageProcessingBackgronudOrigin;
    QLabel *LabelImageProcessingBackgronudNormalVector;
    QLabel *LabelImageProcessingBackgronudParameter;
    QDoubleSpinBox *DoubleSpinBoxImageProcessingBackgroundMax;
    QDoubleSpinBox *DoubleSpinBoxImageProcessingBackgroundMin;
    QLabel *LabelImageProcessingBackgroundMax;
    QLabel *LabelImageProcessingBackgroundMin;
    QSpacerItem *HorizontalSpacerImageProcessingBackground;
    QPushButton *PushButtonImageProcessingBackgroundGenerate;
    QGroupBox *GroupBoxImageProcessingFindLowContrastRegion;
    QGridLayout *gridLayout_5;
    QHBoxLayout *HorizontalLayoutImageProcessingLCR;
    QLabel *LabelImageProcessingDataNo;
    QSpinBox *SpinBoxImageProcessingDataNo;
    QSpacerItem *HorizontalSpacerImageProcessingFindLowContrastRegion;
    QPushButton *PushButtonImageProcessingFindLCR;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *PushButtonDanger;
    QPushButton *PushButtonPoison;
    QPushButton *PushButtonEmergency;
    QWidget *TabViewControl;
    QGridLayout *gridLayout_3;
    QHBoxLayout *HorizontalLayoutViewControlUpper;
    QHBoxLayout *HorizontalLayoutViewControlUpperShow;
    QLabel *LabelViewControlDataNo;
    QSpinBox *SpinBoxViewControlDataNo;
    QCheckBox *CheckBoxViewControlShow;
    QCheckBox *CheckBoxViewControlAlphaMode;
    QCheckBox *CheckBoxViewControlLCR;
    QSpacerItem *HorizontalSpacerViewControlUpper;
    QPushButton *PushButtonViewControlOrthoView;
    QPushButton *PushButtonViewControlResetOrthoViewSize;
    QHBoxLayout *HorizontalLayoutViewControlMain;
    QGroupBox *GroupBoxViewControlThreshold;
    QGridLayout *gridLayout_8;
    QSlider *VerticalSliderViewControlThreshold;
    QLineEdit *LineEditViewControlThreshold;
    QGroupBox *GroupBoxViewControlPointer;
    QGridLayout *gridLayout_9;
    QLabel *LabelViewControlPointerX;
    QLabel *LabelViewControlPointerY;
    QLabel *LabelViewControlPointerZ;
    QSlider *VerticalSliderViewControlPointerXum;
    QSlider *VerticalSliderViewControlPointerYum;
    QSlider *VerticalSliderViewControlPointerZum;
    QLineEdit *LineEditViewControlPointerXum;
    QLineEdit *LineEditViewControlPointerYum;
    QLineEdit *LineEditViewControlPointerZum;
    QCheckBox *CheckBoxViewControlPointer;
    QGroupBox *GroupBoxViewControlROI;
    QGridLayout *gridLayout_10;
    QHBoxLayout *HorizontalLayoutViewControlROI;
    QVBoxLayout *VerticalLayoutViewControlROIX;
    QLabel *LabelViewControlROIX;
    QGridLayout *GridLayoutViewControlROIX;
    QSpinBox *SpinBoxViewControlROIXFrom;
    QSpinBox *SpinBoxViewControlROIXTo;
    QHBoxLayout *HorizontalLayoutViewControlROIXFrom;
    QSpacerItem *HorizontalSpacerViewControlROIXFrom1;
    QSlider *VerticalSliderViewControlROIXFrom;
    QSpacerItem *HorizontalSpacerViewControlROIXFrom2;
    QHBoxLayout *HorizontalLayoutViewControlROIXTo;
    QSpacerItem *HorizontalSpacerViewControlROIXTo1;
    QSlider *VerticalSliderViewControlROIXTo;
    QSpacerItem *HorizontalSpacerViewControlROIXTo2;
    QLabel *LabelViewControlROIXFrom;
    QLabel *LabelViewControlROIXTo;
    QVBoxLayout *VerticalLayoutViewControlROIY;
    QLabel *LabelViewControlROIY;
    QGridLayout *GridLayoutViewControlROIY;
    QSpinBox *SpinBoxViewControlROIYFrom;
    QSpinBox *SpinBoxViewControlROIYTo;
    QHBoxLayout *HorizontalLayoutViewControlROIYFrom;
    QSpacerItem *HorizontalSpacerViewControlROIYFrom1;
    QSlider *VerticalSliderViewControlROIYFrom;
    QSpacerItem *HorizontalSpacerViewControlROIYFrom2;
    QHBoxLayout *HorizontalLayoutViewControlROIYTo;
    QSpacerItem *HorizontalSpacerViewControlROIYTo1;
    QSlider *VerticalSliderViewControlROIYTo;
    QSpacerItem *HorizontalSpacerViewControlROIYTo2;
    QLabel *LabelViewControlROIYFrom;
    QLabel *LabelViewControlROIYTo;
    QVBoxLayout *VerticalLayoutViewControlROIZ;
    QLabel *LabelViewControlROIZ;
    QGridLayout *GridLayoutViewControlROIZ;
    QSpinBox *SpinBoxViewControlROIZFrom;
    QSpinBox *SpinBoxViewControlROIZTo;
    QHBoxLayout *VorizontalLayoutViewControlROIZFrom;
    QSpacerItem *HorizontalSpacerViewControlROIZFrom1;
    QSlider *VerticalSliderViewControlROIZFrom;
    QSpacerItem *HorizontalSpacerViewControlROIZFrom2;
    QHBoxLayout *HorizontalLayoutViewControlROIZTo;
    QSpacerItem *HorizontalSpacerViewControlROIZTo1;
    QSlider *VerticalSliderViewControlROIZTo;
    QSpacerItem *HorizontalSpacerViewControlROIZTo2;
    QLabel *LabelViewControlROIZFrom;
    QLabel *LabelViewControlROIZTo;
    QGroupBox *GroupBoxViewControlColor;
    QGridLayout *gridLayout_2;
    QLabel *LabelViewControlColorR;
    QLabel *LabelViewControlColorG;
    QLabel *LabelViewControlColorB;
    QSlider *VerticalSliderViewControlColorR;
    QSlider *VerticalSliderViewControlColorG;
    QSlider *VerticalSliderViewControlColorB;
    QLineEdit *LineEditViewControlColorR;
    QLineEdit *LineEditViewControlColorG;
    QLineEdit *LineEditViewControlColorB;
    QGroupBox *GroupBoxViewControlTranslation;
    QGridLayout *gridLayout;
    QLabel *LabelViewControlTranslationX;
    QLabel *LabelViewControlTranslationY;
    QLabel *LabelViewControlTranslationZ;
    QSlider *VerticalSliderViewControlTranslationX;
    QSlider *VerticalSliderViewControlTranslationY;
    QSlider *VerticalSliderViewControlTranslationZ;
    QLineEdit *LineEditViewControlTranslationY;
    QLineEdit *LineEditViewControlTranslationZ;
    QLineEdit *LineEditViewControlTranslationXum;
    QLineEdit *LineEditViewControlTranslationYum;
    QLineEdit *LineEditViewControlTranslationZum;
    QLineEdit *LineEditViewControlTranslationX;
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

    void setupUi(QWidget *StackImageControllerDialog)
    {
        if (StackImageControllerDialog->objectName().isEmpty())
            StackImageControllerDialog->setObjectName(QString::fromUtf8("StackImageControllerDialog"));
        StackImageControllerDialog->resize(813, 429);
        gridLayout_7 = new QGridLayout(StackImageControllerDialog);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        Tabs = new QTabWidget(StackImageControllerDialog);
        Tabs->setObjectName(QString::fromUtf8("Tabs"));
        Tabs->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Tabs->sizePolicy().hasHeightForWidth());
        Tabs->setSizePolicy(sizePolicy);
        Tabs->setMinimumSize(QSize(640, 380));
        TabFileLoad = new QWidget();
        TabFileLoad->setObjectName(QString::fromUtf8("TabFileLoad"));
        formLayout_4 = new QFormLayout(TabFileLoad);
        formLayout_4->setObjectName(QString::fromUtf8("formLayout_4"));
        formLayout_4->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        GridLayoutFileLoad = new QGridLayout();
        GridLayoutFileLoad->setObjectName(QString::fromUtf8("GridLayoutFileLoad"));
        LabelFileLoadFilePath = new QLabel(TabFileLoad);
        LabelFileLoadFilePath->setObjectName(QString::fromUtf8("LabelFileLoadFilePath"));

        GridLayoutFileLoad->addWidget(LabelFileLoadFilePath, 0, 0, 1, 1);

        LineEditFileLoadFilePath = new QLineEdit(TabFileLoad);
        LineEditFileLoadFilePath->setObjectName(QString::fromUtf8("LineEditFileLoadFilePath"));

        GridLayoutFileLoad->addWidget(LineEditFileLoadFilePath, 0, 2, 1, 1);

        PushButtonFileLoadBrowse = new QPushButton(TabFileLoad);
        PushButtonFileLoadBrowse->setObjectName(QString::fromUtf8("PushButtonFileLoadBrowse"));

        GridLayoutFileLoad->addWidget(PushButtonFileLoadBrowse, 0, 3, 1, 1);

        LabelFileLoadDirectory = new QLabel(TabFileLoad);
        LabelFileLoadDirectory->setObjectName(QString::fromUtf8("LabelFileLoadDirectory"));

        GridLayoutFileLoad->addWidget(LabelFileLoadDirectory, 2, 0, 1, 1);

        LabelFileLoadBaseName = new QLabel(TabFileLoad);
        LabelFileLoadBaseName->setObjectName(QString::fromUtf8("LabelFileLoadBaseName"));

        GridLayoutFileLoad->addWidget(LabelFileLoadBaseName, 3, 0, 1, 1);

        LabelFileLoadScale = new QLabel(TabFileLoad);
        LabelFileLoadScale->setObjectName(QString::fromUtf8("LabelFileLoadScale"));

        GridLayoutFileLoad->addWidget(LabelFileLoadScale, 4, 0, 1, 1);

        HorizontalLayoutFileLoadScale = new QHBoxLayout();
        HorizontalLayoutFileLoadScale->setObjectName(QString::fromUtf8("HorizontalLayoutFileLoadScale"));
        LineEditFileLoadScaleX = new QLineEdit(TabFileLoad);
        LineEditFileLoadScaleX->setObjectName(QString::fromUtf8("LineEditFileLoadScaleX"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(LineEditFileLoadScaleX->sizePolicy().hasHeightForWidth());
        LineEditFileLoadScaleX->setSizePolicy(sizePolicy1);
        LineEditFileLoadScaleX->setMinimumSize(QSize(30, 0));

        HorizontalLayoutFileLoadScale->addWidget(LineEditFileLoadScaleX);

        LabelFileLoadScaleCommaXY = new QLabel(TabFileLoad);
        LabelFileLoadScaleCommaXY->setObjectName(QString::fromUtf8("LabelFileLoadScaleCommaXY"));

        HorizontalLayoutFileLoadScale->addWidget(LabelFileLoadScaleCommaXY);

        LineEditFileLoadScaleY = new QLineEdit(TabFileLoad);
        LineEditFileLoadScaleY->setObjectName(QString::fromUtf8("LineEditFileLoadScaleY"));
        sizePolicy1.setHeightForWidth(LineEditFileLoadScaleY->sizePolicy().hasHeightForWidth());
        LineEditFileLoadScaleY->setSizePolicy(sizePolicy1);
        LineEditFileLoadScaleY->setMinimumSize(QSize(30, 0));

        HorizontalLayoutFileLoadScale->addWidget(LineEditFileLoadScaleY);

        LabelFileLoadScaleYZ = new QLabel(TabFileLoad);
        LabelFileLoadScaleYZ->setObjectName(QString::fromUtf8("LabelFileLoadScaleYZ"));

        HorizontalLayoutFileLoadScale->addWidget(LabelFileLoadScaleYZ);

        LineEditFileLoadScaleZ = new QLineEdit(TabFileLoad);
        LineEditFileLoadScaleZ->setObjectName(QString::fromUtf8("LineEditFileLoadScaleZ"));
        sizePolicy1.setHeightForWidth(LineEditFileLoadScaleZ->sizePolicy().hasHeightForWidth());
        LineEditFileLoadScaleZ->setSizePolicy(sizePolicy1);
        LineEditFileLoadScaleZ->setMinimumSize(QSize(30, 0));

        HorizontalLayoutFileLoadScale->addWidget(LineEditFileLoadScaleZ);

        HorizontalSpacerFileLoadScale = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutFileLoadScale->addItem(HorizontalSpacerFileLoadScale);


        GridLayoutFileLoad->addLayout(HorizontalLayoutFileLoadScale, 4, 2, 1, 1);

        LabelFileLoadScaleUnit = new QLabel(TabFileLoad);
        LabelFileLoadScaleUnit->setObjectName(QString::fromUtf8("LabelFileLoadScaleUnit"));

        GridLayoutFileLoad->addWidget(LabelFileLoadScaleUnit, 4, 3, 1, 1);

        LineEditFileLoadDirectory = new QLineEdit(TabFileLoad);
        LineEditFileLoadDirectory->setObjectName(QString::fromUtf8("LineEditFileLoadDirectory"));
        LineEditFileLoadDirectory->setReadOnly(true);

        GridLayoutFileLoad->addWidget(LineEditFileLoadDirectory, 2, 2, 1, 1);

        LineEditFileLoadBaseName = new QLineEdit(TabFileLoad);
        LineEditFileLoadBaseName->setObjectName(QString::fromUtf8("LineEditFileLoadBaseName"));
        LineEditFileLoadBaseName->setReadOnly(true);

        GridLayoutFileLoad->addWidget(LineEditFileLoadBaseName, 3, 2, 1, 1);

        LabelFileLoadLoadTo = new QLabel(TabFileLoad);
        LabelFileLoadLoadTo->setObjectName(QString::fromUtf8("LabelFileLoadLoadTo"));

        GridLayoutFileLoad->addWidget(LabelFileLoadLoadTo, 5, 0, 1, 1);

        HorizontalLayoutFileLoadDataNo = new QHBoxLayout();
        HorizontalLayoutFileLoadDataNo->setObjectName(QString::fromUtf8("HorizontalLayoutFileLoadDataNo"));
        LabelFileLoadStoreToStackImageDataNo = new QLabel(TabFileLoad);
        LabelFileLoadStoreToStackImageDataNo->setObjectName(QString::fromUtf8("LabelFileLoadStoreToStackImageDataNo"));

        HorizontalLayoutFileLoadDataNo->addWidget(LabelFileLoadStoreToStackImageDataNo);

        SpinBoxFileLoadDataNo = new QSpinBox(TabFileLoad);
        SpinBoxFileLoadDataNo->setObjectName(QString::fromUtf8("SpinBoxFileLoadDataNo"));
        SpinBoxFileLoadDataNo->setMaximum(9);

        HorizontalLayoutFileLoadDataNo->addWidget(SpinBoxFileLoadDataNo);

        HorizontalSpacerFileLoadDataNo = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutFileLoadDataNo->addItem(HorizontalSpacerFileLoadDataNo);


        GridLayoutFileLoad->addLayout(HorizontalLayoutFileLoadDataNo, 5, 2, 1, 1);


        formLayout_4->setLayout(0, QFormLayout::SpanningRole, GridLayoutFileLoad);

        HorizontalLayoutFileLoadExecutionButton = new QHBoxLayout();
        HorizontalLayoutFileLoadExecutionButton->setObjectName(QString::fromUtf8("HorizontalLayoutFileLoadExecutionButton"));
        HorizontalSpacerFileLoadBottom = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutFileLoadExecutionButton->addItem(HorizontalSpacerFileLoadBottom);

        PushButtonFileLoadClear = new QPushButton(TabFileLoad);
        PushButtonFileLoadClear->setObjectName(QString::fromUtf8("PushButtonFileLoadClear"));

        HorizontalLayoutFileLoadExecutionButton->addWidget(PushButtonFileLoadClear);

        PushButtonFileLoadLoad = new QPushButton(TabFileLoad);
        PushButtonFileLoadLoad->setObjectName(QString::fromUtf8("PushButtonFileLoadLoad"));

        HorizontalLayoutFileLoadExecutionButton->addWidget(PushButtonFileLoadLoad);


        formLayout_4->setLayout(1, QFormLayout::SpanningRole, HorizontalLayoutFileLoadExecutionButton);

        Tabs->addTab(TabFileLoad, QString());
        TabFileSave = new QWidget();
        TabFileSave->setObjectName(QString::fromUtf8("TabFileSave"));
        formLayout_3 = new QFormLayout(TabFileSave);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        GridLayoutFileSave = new QGridLayout();
        GridLayoutFileSave->setObjectName(QString::fromUtf8("GridLayoutFileSave"));
        LabelFileSaveFilePath = new QLabel(TabFileSave);
        LabelFileSaveFilePath->setObjectName(QString::fromUtf8("LabelFileSaveFilePath"));

        GridLayoutFileSave->addWidget(LabelFileSaveFilePath, 1, 0, 1, 1);

        LineEditFileSaveFilePath = new QLineEdit(TabFileSave);
        LineEditFileSaveFilePath->setObjectName(QString::fromUtf8("LineEditFileSaveFilePath"));

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
        LineEditFileSaveDirectory->setReadOnly(false);

        GridLayoutFileSave->addWidget(LineEditFileSaveDirectory, 3, 2, 1, 1);

        LineEditFileSaveBaseName = new QLineEdit(TabFileSave);
        LineEditFileSaveBaseName->setObjectName(QString::fromUtf8("LineEditFileSaveBaseName"));
        LineEditFileSaveBaseName->setReadOnly(false);

        GridLayoutFileSave->addWidget(LineEditFileSaveBaseName, 4, 2, 1, 1);

        HorizontalLayoutFileSaveDataNo = new QHBoxLayout();
        HorizontalLayoutFileSaveDataNo->setObjectName(QString::fromUtf8("HorizontalLayoutFileSaveDataNo"));
        SpinBoxFileSaveDataNo = new QSpinBox(TabFileSave);
        SpinBoxFileSaveDataNo->setObjectName(QString::fromUtf8("SpinBoxFileSaveDataNo"));

        HorizontalLayoutFileSaveDataNo->addWidget(SpinBoxFileSaveDataNo);

        HorizontalSpacerDataNo = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutFileSaveDataNo->addItem(HorizontalSpacerDataNo);


        GridLayoutFileSave->addLayout(HorizontalLayoutFileSaveDataNo, 0, 2, 1, 1);

        LabelFileSaveDataNo = new QLabel(TabFileSave);
        LabelFileSaveDataNo->setObjectName(QString::fromUtf8("LabelFileSaveDataNo"));

        GridLayoutFileSave->addWidget(LabelFileSaveDataNo, 0, 0, 1, 1);


        formLayout_3->setLayout(0, QFormLayout::SpanningRole, GridLayoutFileSave);

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


        formLayout_3->setLayout(1, QFormLayout::SpanningRole, HorizontalLayoutFileSaveBottom);

        Tabs->addTab(TabFileSave, QString());
        TabExtraction = new QWidget();
        TabExtraction->setObjectName(QString::fromUtf8("TabExtraction"));
        gridLayout_12 = new QGridLayout(TabExtraction);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        HorizontalLayoutExtractionBottom = new QHBoxLayout();
        HorizontalLayoutExtractionBottom->setObjectName(QString::fromUtf8("HorizontalLayoutExtractionBottom"));
        HorizontalSpacerExtractionBottom = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutExtractionBottom->addItem(HorizontalSpacerExtractionBottom);

        PushButtonExtractionHandTracing = new QPushButton(TabExtraction);
        PushButtonExtractionHandTracing->setObjectName(QString::fromUtf8("PushButtonExtractionHandTracing"));

        HorizontalLayoutExtractionBottom->addWidget(PushButtonExtractionHandTracing);

        PushButtonExtractionCancel = new QPushButton(TabExtraction);
        PushButtonExtractionCancel->setObjectName(QString::fromUtf8("PushButtonExtractionCancel"));
        PushButtonExtractionCancel->setEnabled(false);

        HorizontalLayoutExtractionBottom->addWidget(PushButtonExtractionCancel);

        PushButtonExtractionExtract = new QPushButton(TabExtraction);
        PushButtonExtractionExtract->setObjectName(QString::fromUtf8("PushButtonExtractionExtract"));

        HorizontalLayoutExtractionBottom->addWidget(PushButtonExtractionExtract);


        gridLayout_12->addLayout(HorizontalLayoutExtractionBottom, 1, 0, 1, 1);

        GridLayoutExtraction = new QGridLayout();
        GridLayoutExtraction->setObjectName(QString::fromUtf8("GridLayoutExtraction"));
        LabelExtractionBinaryThreshold = new QLabel(TabExtraction);
        LabelExtractionBinaryThreshold->setObjectName(QString::fromUtf8("LabelExtractionBinaryThreshold"));

        GridLayoutExtraction->addWidget(LabelExtractionBinaryThreshold, 2, 0, 1, 1);

        PushButtonExtractionBinaryThresholdGetFromView = new QPushButton(TabExtraction);
        PushButtonExtractionBinaryThresholdGetFromView->setObjectName(QString::fromUtf8("PushButtonExtractionBinaryThresholdGetFromView"));

        GridLayoutExtraction->addWidget(PushButtonExtractionBinaryThresholdGetFromView, 2, 3, 1, 1);

        LabelExtractionMedianFilter = new QLabel(TabExtraction);
        LabelExtractionMedianFilter->setObjectName(QString::fromUtf8("LabelExtractionMedianFilter"));
        LabelExtractionMedianFilter->setEnabled(false);

        GridLayoutExtraction->addWidget(LabelExtractionMedianFilter, 3, 0, 1, 1);

        CheckBoxExtractionMedianFilter = new QCheckBox(TabExtraction);
        CheckBoxExtractionMedianFilter->setObjectName(QString::fromUtf8("CheckBoxExtractionMedianFilter"));
        CheckBoxExtractionMedianFilter->setEnabled(false);

        GridLayoutExtraction->addWidget(CheckBoxExtractionMedianFilter, 3, 2, 1, 1);

        HorizontalLayoutExtractionBinaryThreshold = new QHBoxLayout();
        HorizontalLayoutExtractionBinaryThreshold->setObjectName(QString::fromUtf8("HorizontalLayoutExtractionBinaryThreshold"));
        HorizontalSliderExtractionBinaryThreshold = new QSlider(TabExtraction);
        HorizontalSliderExtractionBinaryThreshold->setObjectName(QString::fromUtf8("HorizontalSliderExtractionBinaryThreshold"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(HorizontalSliderExtractionBinaryThreshold->sizePolicy().hasHeightForWidth());
        HorizontalSliderExtractionBinaryThreshold->setSizePolicy(sizePolicy2);
        HorizontalSliderExtractionBinaryThreshold->setMaximum(255);
        HorizontalSliderExtractionBinaryThreshold->setOrientation(Qt::Horizontal);

        HorizontalLayoutExtractionBinaryThreshold->addWidget(HorizontalSliderExtractionBinaryThreshold);

        LineEditExtractionBinaryThreshold = new QLineEdit(TabExtraction);
        LineEditExtractionBinaryThreshold->setObjectName(QString::fromUtf8("LineEditExtractionBinaryThreshold"));
        sizePolicy2.setHeightForWidth(LineEditExtractionBinaryThreshold->sizePolicy().hasHeightForWidth());
        LineEditExtractionBinaryThreshold->setSizePolicy(sizePolicy2);
        LineEditExtractionBinaryThreshold->setMaxLength(5);

        HorizontalLayoutExtractionBinaryThreshold->addWidget(LineEditExtractionBinaryThreshold);


        GridLayoutExtraction->addLayout(HorizontalLayoutExtractionBinaryThreshold, 2, 2, 1, 1);

        LabelExtractionStartPoint = new QLabel(TabExtraction);
        LabelExtractionStartPoint->setObjectName(QString::fromUtf8("LabelExtractionStartPoint"));

        GridLayoutExtraction->addWidget(LabelExtractionStartPoint, 7, 0, 1, 1);

        HorizontalLayoutExtractionStartPoint = new QHBoxLayout();
        HorizontalLayoutExtractionStartPoint->setObjectName(QString::fromUtf8("HorizontalLayoutExtractionStartPoint"));
        LineEditExtractionStartPointX = new QLineEdit(TabExtraction);
        LineEditExtractionStartPointX->setObjectName(QString::fromUtf8("LineEditExtractionStartPointX"));
        LineEditExtractionStartPointX->setMinimumSize(QSize(30, 0));

        HorizontalLayoutExtractionStartPoint->addWidget(LineEditExtractionStartPointX);

        LabelExtractionStartPointCommaXY = new QLabel(TabExtraction);
        LabelExtractionStartPointCommaXY->setObjectName(QString::fromUtf8("LabelExtractionStartPointCommaXY"));

        HorizontalLayoutExtractionStartPoint->addWidget(LabelExtractionStartPointCommaXY);

        LineEditExtractionStartPointY = new QLineEdit(TabExtraction);
        LineEditExtractionStartPointY->setObjectName(QString::fromUtf8("LineEditExtractionStartPointY"));
        LineEditExtractionStartPointY->setMinimumSize(QSize(30, 0));

        HorizontalLayoutExtractionStartPoint->addWidget(LineEditExtractionStartPointY);

        LabelExtractionStartPointCommaYZ = new QLabel(TabExtraction);
        LabelExtractionStartPointCommaYZ->setObjectName(QString::fromUtf8("LabelExtractionStartPointCommaYZ"));

        HorizontalLayoutExtractionStartPoint->addWidget(LabelExtractionStartPointCommaYZ);

        LineEditExtractionStartPointZ = new QLineEdit(TabExtraction);
        LineEditExtractionStartPointZ->setObjectName(QString::fromUtf8("LineEditExtractionStartPointZ"));
        LineEditExtractionStartPointZ->setMinimumSize(QSize(30, 0));

        HorizontalLayoutExtractionStartPoint->addWidget(LineEditExtractionStartPointZ);


        GridLayoutExtraction->addLayout(HorizontalLayoutExtractionStartPoint, 7, 2, 1, 1);

        PushButtonExtractionStartPointGetFromView = new QPushButton(TabExtraction);
        PushButtonExtractionStartPointGetFromView->setObjectName(QString::fromUtf8("PushButtonExtractionStartPointGetFromView"));

        GridLayoutExtraction->addWidget(PushButtonExtractionStartPointGetFromView, 7, 3, 1, 1);

        LabelExtractionDataNo = new QLabel(TabExtraction);
        LabelExtractionDataNo->setObjectName(QString::fromUtf8("LabelExtractionDataNo"));

        GridLayoutExtraction->addWidget(LabelExtractionDataNo, 0, 0, 1, 1);

        HorizontalLayoutExtractionDataNo = new QHBoxLayout();
        HorizontalLayoutExtractionDataNo->setObjectName(QString::fromUtf8("HorizontalLayoutExtractionDataNo"));
        SpinBoxExtractionDataNo = new QSpinBox(TabExtraction);
        SpinBoxExtractionDataNo->setObjectName(QString::fromUtf8("SpinBoxExtractionDataNo"));

        HorizontalLayoutExtractionDataNo->addWidget(SpinBoxExtractionDataNo);

        HorizontalSpacerExtractionDataNo = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutExtractionDataNo->addItem(HorizontalSpacerExtractionDataNo);


        GridLayoutExtraction->addLayout(HorizontalLayoutExtractionDataNo, 0, 2, 1, 1);

        PushButtonExtractionCurrentDataNo = new QPushButton(TabExtraction);
        PushButtonExtractionCurrentDataNo->setObjectName(QString::fromUtf8("PushButtonExtractionCurrentDataNo"));
        PushButtonExtractionCurrentDataNo->setEnabled(false);

        GridLayoutExtraction->addWidget(PushButtonExtractionCurrentDataNo, 0, 3, 1, 1);

        LabelExtractionCalcProp = new QLabel(TabExtraction);
        LabelExtractionCalcProp->setObjectName(QString::fromUtf8("LabelExtractionCalcProp"));

        GridLayoutExtraction->addWidget(LabelExtractionCalcProp, 8, 0, 1, 1);

        CheckBoxExtractionCalcProp = new QCheckBox(TabExtraction);
        CheckBoxExtractionCalcProp->setObjectName(QString::fromUtf8("CheckBoxExtractionCalcProp"));

        GridLayoutExtraction->addWidget(CheckBoxExtractionCalcProp, 8, 3, 1, 1);

        LineEditExtractionCalcPropFileName = new QLineEdit(TabExtraction);
        LineEditExtractionCalcPropFileName->setObjectName(QString::fromUtf8("LineEditExtractionCalcPropFileName"));

        GridLayoutExtraction->addWidget(LineEditExtractionCalcPropFileName, 8, 2, 1, 1);

        VerticalLayoutExtractionProp = new QVBoxLayout();
        VerticalLayoutExtractionProp->setObjectName(QString::fromUtf8("VerticalLayoutExtractionProp"));
        HorizontalLayoutExtractionPropStart = new QHBoxLayout();
        HorizontalLayoutExtractionPropStart->setObjectName(QString::fromUtf8("HorizontalLayoutExtractionPropStart"));
        LabelExtractionCalcPropStart = new QLabel(TabExtraction);
        LabelExtractionCalcPropStart->setObjectName(QString::fromUtf8("LabelExtractionCalcPropStart"));

        HorizontalLayoutExtractionPropStart->addWidget(LabelExtractionCalcPropStart);

        SpinBoxExtractionCalcPropStartThreshold = new QSpinBox(TabExtraction);
        SpinBoxExtractionCalcPropStartThreshold->setObjectName(QString::fromUtf8("SpinBoxExtractionCalcPropStartThreshold"));
        SpinBoxExtractionCalcPropStartThreshold->setMaximum(255);

        HorizontalLayoutExtractionPropStart->addWidget(SpinBoxExtractionCalcPropStartThreshold);

        HorizontalSpacerExtractionPropStart = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutExtractionPropStart->addItem(HorizontalSpacerExtractionPropStart);


        VerticalLayoutExtractionProp->addLayout(HorizontalLayoutExtractionPropStart);

        HorizontalLayoutExtractionPropStop = new QHBoxLayout();
        HorizontalLayoutExtractionPropStop->setObjectName(QString::fromUtf8("HorizontalLayoutExtractionPropStop"));
        LabelExtractionCalcPropStop = new QLabel(TabExtraction);
        LabelExtractionCalcPropStop->setObjectName(QString::fromUtf8("LabelExtractionCalcPropStop"));

        HorizontalLayoutExtractionPropStop->addWidget(LabelExtractionCalcPropStop);

        SpinBoxExtractionCalcPropStopThreshold = new QSpinBox(TabExtraction);
        SpinBoxExtractionCalcPropStopThreshold->setObjectName(QString::fromUtf8("SpinBoxExtractionCalcPropStopThreshold"));
        SpinBoxExtractionCalcPropStopThreshold->setMaximum(255);

        HorizontalLayoutExtractionPropStop->addWidget(SpinBoxExtractionCalcPropStopThreshold);

        HorizontalSpacerExtractionPropStop = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutExtractionPropStop->addItem(HorizontalSpacerExtractionPropStop);


        VerticalLayoutExtractionProp->addLayout(HorizontalLayoutExtractionPropStop);


        GridLayoutExtraction->addLayout(VerticalLayoutExtractionProp, 9, 2, 1, 1);

        LabelExtractionTargetNo = new QLabel(TabExtraction);
        LabelExtractionTargetNo->setObjectName(QString::fromUtf8("LabelExtractionTargetNo"));

        GridLayoutExtraction->addWidget(LabelExtractionTargetNo, 1, 0, 1, 1);

        HorizontalLayoutExtractionTargetNo = new QHBoxLayout();
        HorizontalLayoutExtractionTargetNo->setObjectName(QString::fromUtf8("HorizontalLayoutExtractionTargetNo"));
        SpinBoxExtractionTargetNo = new QSpinBox(TabExtraction);
        SpinBoxExtractionTargetNo->setObjectName(QString::fromUtf8("SpinBoxExtractionTargetNo"));

        HorizontalLayoutExtractionTargetNo->addWidget(SpinBoxExtractionTargetNo);

        HorizontalSpacerExtractionTargetNo = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutExtractionTargetNo->addItem(HorizontalSpacerExtractionTargetNo);


        GridLayoutExtraction->addLayout(HorizontalLayoutExtractionTargetNo, 1, 2, 1, 1);

        LabelExtractionROI = new QLabel(TabExtraction);
        LabelExtractionROI->setObjectName(QString::fromUtf8("LabelExtractionROI"));

        GridLayoutExtraction->addWidget(LabelExtractionROI, 4, 0, 1, 1);

        CheckBoxExtractionROI = new QCheckBox(TabExtraction);
        CheckBoxExtractionROI->setObjectName(QString::fromUtf8("CheckBoxExtractionROI"));

        GridLayoutExtraction->addWidget(CheckBoxExtractionROI, 4, 2, 1, 1);

        LabelExtractionDoRescanning = new QLabel(TabExtraction);
        LabelExtractionDoRescanning->setObjectName(QString::fromUtf8("LabelExtractionDoRescanning"));

        GridLayoutExtraction->addWidget(LabelExtractionDoRescanning, 5, 0, 1, 1);

        HorizontalLayoutExtractionDoRescanning = new QHBoxLayout();
        HorizontalLayoutExtractionDoRescanning->setObjectName(QString::fromUtf8("HorizontalLayoutExtractionDoRescanning"));
        CheckBoxExtractionDoRescanning = new QCheckBox(TabExtraction);
        CheckBoxExtractionDoRescanning->setObjectName(QString::fromUtf8("CheckBoxExtractionDoRescanning"));

        HorizontalLayoutExtractionDoRescanning->addWidget(CheckBoxExtractionDoRescanning);

        HorizontalSpacerExtractionDoRescanning1 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutExtractionDoRescanning->addItem(HorizontalSpacerExtractionDoRescanning1);

        label = new QLabel(TabExtraction);
        label->setObjectName(QString::fromUtf8("label"));

        HorizontalLayoutExtractionDoRescanning->addWidget(label);

        SpinBoxExtractionDoRescanningStoreNo = new QSpinBox(TabExtraction);
        SpinBoxExtractionDoRescanningStoreNo->setObjectName(QString::fromUtf8("SpinBoxExtractionDoRescanningStoreNo"));

        HorizontalLayoutExtractionDoRescanning->addWidget(SpinBoxExtractionDoRescanningStoreNo);

        HorizontalSpacerExtractionDoRescanning2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutExtractionDoRescanning->addItem(HorizontalSpacerExtractionDoRescanning2);


        GridLayoutExtraction->addLayout(HorizontalLayoutExtractionDoRescanning, 5, 2, 1, 1);


        gridLayout_12->addLayout(GridLayoutExtraction, 0, 0, 1, 1);

        Tabs->addTab(TabExtraction, QString());
        TabImageProcessing = new QWidget();
        TabImageProcessing->setObjectName(QString::fromUtf8("TabImageProcessing"));
        gridLayout_13 = new QGridLayout(TabImageProcessing);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        GroupBoxImageProcessingGenerateStackImage = new QGroupBox(TabImageProcessing);
        GroupBoxImageProcessingGenerateStackImage->setObjectName(QString::fromUtf8("GroupBoxImageProcessingGenerateStackImage"));
        gridLayout_4 = new QGridLayout(GroupBoxImageProcessingGenerateStackImage);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        GridLayoutImageProcessingGenerateStackImage = new QGridLayout();
        GridLayoutImageProcessingGenerateStackImage->setObjectName(QString::fromUtf8("GridLayoutImageProcessingGenerateStackImage"));
        LabelImageProcessingGenerateStackImageParam1 = new QLabel(GroupBoxImageProcessingGenerateStackImage);
        LabelImageProcessingGenerateStackImageParam1->setObjectName(QString::fromUtf8("LabelImageProcessingGenerateStackImageParam1"));

        GridLayoutImageProcessingGenerateStackImage->addWidget(LabelImageProcessingGenerateStackImageParam1, 2, 0, 1, 1);

        DoubleSpinBoxImageProcessingGenerateStackImageParam1 = new QDoubleSpinBox(GroupBoxImageProcessingGenerateStackImage);
        DoubleSpinBoxImageProcessingGenerateStackImageParam1->setObjectName(QString::fromUtf8("DoubleSpinBoxImageProcessingGenerateStackImageParam1"));
        DoubleSpinBoxImageProcessingGenerateStackImageParam1->setMaximum(255);
        DoubleSpinBoxImageProcessingGenerateStackImageParam1->setValue(0);

        GridLayoutImageProcessingGenerateStackImage->addWidget(DoubleSpinBoxImageProcessingGenerateStackImageParam1, 2, 1, 1, 1);

        LabelImageProcessingGenerateStackImageParam2 = new QLabel(GroupBoxImageProcessingGenerateStackImage);
        LabelImageProcessingGenerateStackImageParam2->setObjectName(QString::fromUtf8("LabelImageProcessingGenerateStackImageParam2"));

        GridLayoutImageProcessingGenerateStackImage->addWidget(LabelImageProcessingGenerateStackImageParam2, 3, 0, 1, 1);

        DoubleSpinBoxImageProcessingGenerateStackImageParam2 = new QDoubleSpinBox(GroupBoxImageProcessingGenerateStackImage);
        DoubleSpinBoxImageProcessingGenerateStackImageParam2->setObjectName(QString::fromUtf8("DoubleSpinBoxImageProcessingGenerateStackImageParam2"));
        DoubleSpinBoxImageProcessingGenerateStackImageParam2->setMaximum(255);
        DoubleSpinBoxImageProcessingGenerateStackImageParam2->setValue(0);

        GridLayoutImageProcessingGenerateStackImage->addWidget(DoubleSpinBoxImageProcessingGenerateStackImageParam2, 3, 1, 1, 1);

        LabelImageProcessingGenerateStackImageParam3 = new QLabel(GroupBoxImageProcessingGenerateStackImage);
        LabelImageProcessingGenerateStackImageParam3->setObjectName(QString::fromUtf8("LabelImageProcessingGenerateStackImageParam3"));

        GridLayoutImageProcessingGenerateStackImage->addWidget(LabelImageProcessingGenerateStackImageParam3, 4, 0, 1, 1);

        DoubleSpinBoxImageProcessingGenerateStackImageParam3 = new QDoubleSpinBox(GroupBoxImageProcessingGenerateStackImage);
        DoubleSpinBoxImageProcessingGenerateStackImageParam3->setObjectName(QString::fromUtf8("DoubleSpinBoxImageProcessingGenerateStackImageParam3"));
        DoubleSpinBoxImageProcessingGenerateStackImageParam3->setMaximum(255);
        DoubleSpinBoxImageProcessingGenerateStackImageParam3->setValue(0);

        GridLayoutImageProcessingGenerateStackImage->addWidget(DoubleSpinBoxImageProcessingGenerateStackImageParam3, 4, 1, 1, 1);

        LabelImageProcessingGenerateStackImageParam4 = new QLabel(GroupBoxImageProcessingGenerateStackImage);
        LabelImageProcessingGenerateStackImageParam4->setObjectName(QString::fromUtf8("LabelImageProcessingGenerateStackImageParam4"));

        GridLayoutImageProcessingGenerateStackImage->addWidget(LabelImageProcessingGenerateStackImageParam4, 5, 0, 1, 1);

        DoubleSpinBoxImageProcessingGenerateStackImageParam4 = new QDoubleSpinBox(GroupBoxImageProcessingGenerateStackImage);
        DoubleSpinBoxImageProcessingGenerateStackImageParam4->setObjectName(QString::fromUtf8("DoubleSpinBoxImageProcessingGenerateStackImageParam4"));
        DoubleSpinBoxImageProcessingGenerateStackImageParam4->setMaximum(255);
        DoubleSpinBoxImageProcessingGenerateStackImageParam4->setValue(0);

        GridLayoutImageProcessingGenerateStackImage->addWidget(DoubleSpinBoxImageProcessingGenerateStackImageParam4, 5, 1, 1, 1);

        ComboBoxImageProcessingGenerateStackImageType = new QComboBox(GroupBoxImageProcessingGenerateStackImage);
        ComboBoxImageProcessingGenerateStackImageType->setObjectName(QString::fromUtf8("ComboBoxImageProcessingGenerateStackImageType"));

        GridLayoutImageProcessingGenerateStackImage->addWidget(ComboBoxImageProcessingGenerateStackImageType, 1, 1, 1, 1);

        SpinBoxImageProcessingGenerateStackImageDataNo = new QSpinBox(GroupBoxImageProcessingGenerateStackImage);
        SpinBoxImageProcessingGenerateStackImageDataNo->setObjectName(QString::fromUtf8("SpinBoxImageProcessingGenerateStackImageDataNo"));

        GridLayoutImageProcessingGenerateStackImage->addWidget(SpinBoxImageProcessingGenerateStackImageDataNo, 0, 1, 1, 1);

        LabelImageProcessingGenerateStackImageDataNo = new QLabel(GroupBoxImageProcessingGenerateStackImage);
        LabelImageProcessingGenerateStackImageDataNo->setObjectName(QString::fromUtf8("LabelImageProcessingGenerateStackImageDataNo"));

        GridLayoutImageProcessingGenerateStackImage->addWidget(LabelImageProcessingGenerateStackImageDataNo, 0, 0, 1, 1);

        LabelImageProcessingGenerateStackImageType = new QLabel(GroupBoxImageProcessingGenerateStackImage);
        LabelImageProcessingGenerateStackImageType->setObjectName(QString::fromUtf8("LabelImageProcessingGenerateStackImageType"));

        GridLayoutImageProcessingGenerateStackImage->addWidget(LabelImageProcessingGenerateStackImageType, 1, 0, 1, 1);

        LabelImageProcessingGeneratStackImageParam5 = new QLabel(GroupBoxImageProcessingGenerateStackImage);
        LabelImageProcessingGeneratStackImageParam5->setObjectName(QString::fromUtf8("LabelImageProcessingGeneratStackImageParam5"));

        GridLayoutImageProcessingGenerateStackImage->addWidget(LabelImageProcessingGeneratStackImageParam5, 6, 0, 1, 1);

        DoubleSpinBoxImageProcessingGenerateStackImageParam5 = new QDoubleSpinBox(GroupBoxImageProcessingGenerateStackImage);
        DoubleSpinBoxImageProcessingGenerateStackImageParam5->setObjectName(QString::fromUtf8("DoubleSpinBoxImageProcessingGenerateStackImageParam5"));
        DoubleSpinBoxImageProcessingGenerateStackImageParam5->setDecimals(3);
        DoubleSpinBoxImageProcessingGenerateStackImageParam5->setMaximum(999.99);
        DoubleSpinBoxImageProcessingGenerateStackImageParam5->setSingleStep(0.1);
        DoubleSpinBoxImageProcessingGenerateStackImageParam5->setValue(0);

        GridLayoutImageProcessingGenerateStackImage->addWidget(DoubleSpinBoxImageProcessingGenerateStackImageParam5, 6, 1, 1, 1);


        gridLayout_4->addLayout(GridLayoutImageProcessingGenerateStackImage, 0, 0, 1, 2);

        HorizontalSpacerImageProcessingGenerateStackImage = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(HorizontalSpacerImageProcessingGenerateStackImage, 1, 0, 1, 1);

        PushButtonImageProcessingGenerateStackImage = new QPushButton(GroupBoxImageProcessingGenerateStackImage);
        PushButtonImageProcessingGenerateStackImage->setObjectName(QString::fromUtf8("PushButtonImageProcessingGenerateStackImage"));

        gridLayout_4->addWidget(PushButtonImageProcessingGenerateStackImage, 1, 1, 1, 1);


        gridLayout_13->addWidget(GroupBoxImageProcessingGenerateStackImage, 0, 0, 2, 1);

        GroupBoxImageProcessingNoise = new QGroupBox(TabImageProcessing);
        GroupBoxImageProcessingNoise->setObjectName(QString::fromUtf8("GroupBoxImageProcessingNoise"));
        gridLayout_11 = new QGridLayout(GroupBoxImageProcessingNoise);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        FormLayoutImageProcessingNoise = new QFormLayout();
        FormLayoutImageProcessingNoise->setObjectName(QString::fromUtf8("FormLayoutImageProcessingNoise"));
        LabelImageProcessingNoiseSD = new QLabel(GroupBoxImageProcessingNoise);
        LabelImageProcessingNoiseSD->setObjectName(QString::fromUtf8("LabelImageProcessingNoiseSD"));

        FormLayoutImageProcessingNoise->setWidget(1, QFormLayout::LabelRole, LabelImageProcessingNoiseSD);

        DoubleSpinBoxImageProcessingNoiseSD = new QDoubleSpinBox(GroupBoxImageProcessingNoise);
        DoubleSpinBoxImageProcessingNoiseSD->setObjectName(QString::fromUtf8("DoubleSpinBoxImageProcessingNoiseSD"));
        DoubleSpinBoxImageProcessingNoiseSD->setMaximum(255);
        DoubleSpinBoxImageProcessingNoiseSD->setValue(1);

        FormLayoutImageProcessingNoise->setWidget(1, QFormLayout::FieldRole, DoubleSpinBoxImageProcessingNoiseSD);

        SpinBoxImageProcessingNoiseDataNo = new QSpinBox(GroupBoxImageProcessingNoise);
        SpinBoxImageProcessingNoiseDataNo->setObjectName(QString::fromUtf8("SpinBoxImageProcessingNoiseDataNo"));

        FormLayoutImageProcessingNoise->setWidget(0, QFormLayout::FieldRole, SpinBoxImageProcessingNoiseDataNo);

        LabelImageProcessingNoiseDataNo = new QLabel(GroupBoxImageProcessingNoise);
        LabelImageProcessingNoiseDataNo->setObjectName(QString::fromUtf8("LabelImageProcessingNoiseDataNo"));

        FormLayoutImageProcessingNoise->setWidget(0, QFormLayout::LabelRole, LabelImageProcessingNoiseDataNo);


        gridLayout_11->addLayout(FormLayoutImageProcessingNoise, 0, 0, 2, 2);

        HorizontalSpacerImageProcessingNoise = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(HorizontalSpacerImageProcessingNoise, 2, 0, 1, 1);

        PushButtonImageProcessingNoiseAddNoise = new QPushButton(GroupBoxImageProcessingNoise);
        PushButtonImageProcessingNoiseAddNoise->setObjectName(QString::fromUtf8("PushButtonImageProcessingNoiseAddNoise"));

        gridLayout_11->addWidget(PushButtonImageProcessingNoiseAddNoise, 2, 1, 1, 1);


        gridLayout_13->addWidget(GroupBoxImageProcessingNoise, 0, 1, 1, 1);

        GroupBoxImageProcessingBackground = new QGroupBox(TabImageProcessing);
        GroupBoxImageProcessingBackground->setObjectName(QString::fromUtf8("GroupBoxImageProcessingBackground"));
        gridLayout_6 = new QGridLayout(GroupBoxImageProcessingBackground);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        FormLayoutImageProcessingBackground = new QFormLayout();
        FormLayoutImageProcessingBackground->setObjectName(QString::fromUtf8("FormLayoutImageProcessingBackground"));
        LabelImageProcessingBackgroundDataNo = new QLabel(GroupBoxImageProcessingBackground);
        LabelImageProcessingBackgroundDataNo->setObjectName(QString::fromUtf8("LabelImageProcessingBackgroundDataNo"));

        FormLayoutImageProcessingBackground->setWidget(0, QFormLayout::LabelRole, LabelImageProcessingBackgroundDataNo);

        SpinBoxImageProcessingBackgroundDataNo = new QSpinBox(GroupBoxImageProcessingBackground);
        SpinBoxImageProcessingBackgroundDataNo->setObjectName(QString::fromUtf8("SpinBoxImageProcessingBackgroundDataNo"));

        FormLayoutImageProcessingBackground->setWidget(0, QFormLayout::FieldRole, SpinBoxImageProcessingBackgroundDataNo);

        LabelImageProcessingBackgroundType = new QLabel(GroupBoxImageProcessingBackground);
        LabelImageProcessingBackgroundType->setObjectName(QString::fromUtf8("LabelImageProcessingBackgroundType"));

        FormLayoutImageProcessingBackground->setWidget(1, QFormLayout::LabelRole, LabelImageProcessingBackgroundType);

        ComboBoxImageProcessingBackgroundType = new QComboBox(GroupBoxImageProcessingBackground);
        ComboBoxImageProcessingBackgroundType->setObjectName(QString::fromUtf8("ComboBoxImageProcessingBackgroundType"));

        FormLayoutImageProcessingBackground->setWidget(1, QFormLayout::FieldRole, ComboBoxImageProcessingBackgroundType);

        HorizontalLayoutImageProcessingBackgroundOrigin = new QHBoxLayout();
        HorizontalLayoutImageProcessingBackgroundOrigin->setObjectName(QString::fromUtf8("HorizontalLayoutImageProcessingBackgroundOrigin"));
        LineEditImageProcessingBackgroundOriginX = new QLineEdit(GroupBoxImageProcessingBackground);
        LineEditImageProcessingBackgroundOriginX->setObjectName(QString::fromUtf8("LineEditImageProcessingBackgroundOriginX"));
        sizePolicy1.setHeightForWidth(LineEditImageProcessingBackgroundOriginX->sizePolicy().hasHeightForWidth());
        LineEditImageProcessingBackgroundOriginX->setSizePolicy(sizePolicy1);
        LineEditImageProcessingBackgroundOriginX->setMinimumSize(QSize(30, 0));

        HorizontalLayoutImageProcessingBackgroundOrigin->addWidget(LineEditImageProcessingBackgroundOriginX);

        LabelImageProcessingBackgroundOriginCommaXY = new QLabel(GroupBoxImageProcessingBackground);
        LabelImageProcessingBackgroundOriginCommaXY->setObjectName(QString::fromUtf8("LabelImageProcessingBackgroundOriginCommaXY"));

        HorizontalLayoutImageProcessingBackgroundOrigin->addWidget(LabelImageProcessingBackgroundOriginCommaXY);

        LineEditImageProcessingBackgroundOriginY = new QLineEdit(GroupBoxImageProcessingBackground);
        LineEditImageProcessingBackgroundOriginY->setObjectName(QString::fromUtf8("LineEditImageProcessingBackgroundOriginY"));
        sizePolicy1.setHeightForWidth(LineEditImageProcessingBackgroundOriginY->sizePolicy().hasHeightForWidth());
        LineEditImageProcessingBackgroundOriginY->setSizePolicy(sizePolicy1);
        LineEditImageProcessingBackgroundOriginY->setMinimumSize(QSize(30, 0));

        HorizontalLayoutImageProcessingBackgroundOrigin->addWidget(LineEditImageProcessingBackgroundOriginY);

        LabelImageProcessingBackgroundOriginYZ = new QLabel(GroupBoxImageProcessingBackground);
        LabelImageProcessingBackgroundOriginYZ->setObjectName(QString::fromUtf8("LabelImageProcessingBackgroundOriginYZ"));

        HorizontalLayoutImageProcessingBackgroundOrigin->addWidget(LabelImageProcessingBackgroundOriginYZ);

        LineEditImageProcessingBackgroundOriginZ = new QLineEdit(GroupBoxImageProcessingBackground);
        LineEditImageProcessingBackgroundOriginZ->setObjectName(QString::fromUtf8("LineEditImageProcessingBackgroundOriginZ"));
        sizePolicy1.setHeightForWidth(LineEditImageProcessingBackgroundOriginZ->sizePolicy().hasHeightForWidth());
        LineEditImageProcessingBackgroundOriginZ->setSizePolicy(sizePolicy1);
        LineEditImageProcessingBackgroundOriginZ->setMinimumSize(QSize(30, 0));

        HorizontalLayoutImageProcessingBackgroundOrigin->addWidget(LineEditImageProcessingBackgroundOriginZ);

        HorizontalSpacerImageProcessingBackgroundOrigin = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutImageProcessingBackgroundOrigin->addItem(HorizontalSpacerImageProcessingBackgroundOrigin);


        FormLayoutImageProcessingBackground->setLayout(2, QFormLayout::FieldRole, HorizontalLayoutImageProcessingBackgroundOrigin);

        HorizontalLayoutImageProcessingBackgroundNormalVector = new QHBoxLayout();
        HorizontalLayoutImageProcessingBackgroundNormalVector->setObjectName(QString::fromUtf8("HorizontalLayoutImageProcessingBackgroundNormalVector"));
        LineEditImageProcessingBackgroundNormalVectorX = new QLineEdit(GroupBoxImageProcessingBackground);
        LineEditImageProcessingBackgroundNormalVectorX->setObjectName(QString::fromUtf8("LineEditImageProcessingBackgroundNormalVectorX"));
        sizePolicy1.setHeightForWidth(LineEditImageProcessingBackgroundNormalVectorX->sizePolicy().hasHeightForWidth());
        LineEditImageProcessingBackgroundNormalVectorX->setSizePolicy(sizePolicy1);
        LineEditImageProcessingBackgroundNormalVectorX->setMinimumSize(QSize(30, 0));

        HorizontalLayoutImageProcessingBackgroundNormalVector->addWidget(LineEditImageProcessingBackgroundNormalVectorX);

        LabelImageProcessingBackgroundNormalVectorCommaXY = new QLabel(GroupBoxImageProcessingBackground);
        LabelImageProcessingBackgroundNormalVectorCommaXY->setObjectName(QString::fromUtf8("LabelImageProcessingBackgroundNormalVectorCommaXY"));

        HorizontalLayoutImageProcessingBackgroundNormalVector->addWidget(LabelImageProcessingBackgroundNormalVectorCommaXY);

        LineEditImageProcessingBackgroundNormalVectorY = new QLineEdit(GroupBoxImageProcessingBackground);
        LineEditImageProcessingBackgroundNormalVectorY->setObjectName(QString::fromUtf8("LineEditImageProcessingBackgroundNormalVectorY"));
        sizePolicy1.setHeightForWidth(LineEditImageProcessingBackgroundNormalVectorY->sizePolicy().hasHeightForWidth());
        LineEditImageProcessingBackgroundNormalVectorY->setSizePolicy(sizePolicy1);
        LineEditImageProcessingBackgroundNormalVectorY->setMinimumSize(QSize(30, 0));

        HorizontalLayoutImageProcessingBackgroundNormalVector->addWidget(LineEditImageProcessingBackgroundNormalVectorY);

        LabelImageProcessingBackgroundNormalVectorYZ = new QLabel(GroupBoxImageProcessingBackground);
        LabelImageProcessingBackgroundNormalVectorYZ->setObjectName(QString::fromUtf8("LabelImageProcessingBackgroundNormalVectorYZ"));

        HorizontalLayoutImageProcessingBackgroundNormalVector->addWidget(LabelImageProcessingBackgroundNormalVectorYZ);

        LineEditImageProcessingBackgroundNormalVectorZ = new QLineEdit(GroupBoxImageProcessingBackground);
        LineEditImageProcessingBackgroundNormalVectorZ->setObjectName(QString::fromUtf8("LineEditImageProcessingBackgroundNormalVectorZ"));
        sizePolicy1.setHeightForWidth(LineEditImageProcessingBackgroundNormalVectorZ->sizePolicy().hasHeightForWidth());
        LineEditImageProcessingBackgroundNormalVectorZ->setSizePolicy(sizePolicy1);
        LineEditImageProcessingBackgroundNormalVectorZ->setMinimumSize(QSize(30, 0));

        HorizontalLayoutImageProcessingBackgroundNormalVector->addWidget(LineEditImageProcessingBackgroundNormalVectorZ);

        HorizontalSpacerImageProcessingBackgroundNormalVector = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutImageProcessingBackgroundNormalVector->addItem(HorizontalSpacerImageProcessingBackgroundNormalVector);


        FormLayoutImageProcessingBackground->setLayout(3, QFormLayout::FieldRole, HorizontalLayoutImageProcessingBackgroundNormalVector);

        DoubleSpinBoxImageProcessingBackgroundParameter = new QDoubleSpinBox(GroupBoxImageProcessingBackground);
        DoubleSpinBoxImageProcessingBackgroundParameter->setObjectName(QString::fromUtf8("DoubleSpinBoxImageProcessingBackgroundParameter"));
        DoubleSpinBoxImageProcessingBackgroundParameter->setMaximum(1000);

        FormLayoutImageProcessingBackground->setWidget(6, QFormLayout::FieldRole, DoubleSpinBoxImageProcessingBackgroundParameter);

        LabelImageProcessingBackgronudOrigin = new QLabel(GroupBoxImageProcessingBackground);
        LabelImageProcessingBackgronudOrigin->setObjectName(QString::fromUtf8("LabelImageProcessingBackgronudOrigin"));

        FormLayoutImageProcessingBackground->setWidget(2, QFormLayout::LabelRole, LabelImageProcessingBackgronudOrigin);

        LabelImageProcessingBackgronudNormalVector = new QLabel(GroupBoxImageProcessingBackground);
        LabelImageProcessingBackgronudNormalVector->setObjectName(QString::fromUtf8("LabelImageProcessingBackgronudNormalVector"));

        FormLayoutImageProcessingBackground->setWidget(3, QFormLayout::LabelRole, LabelImageProcessingBackgronudNormalVector);

        LabelImageProcessingBackgronudParameter = new QLabel(GroupBoxImageProcessingBackground);
        LabelImageProcessingBackgronudParameter->setObjectName(QString::fromUtf8("LabelImageProcessingBackgronudParameter"));

        FormLayoutImageProcessingBackground->setWidget(6, QFormLayout::LabelRole, LabelImageProcessingBackgronudParameter);

        DoubleSpinBoxImageProcessingBackgroundMax = new QDoubleSpinBox(GroupBoxImageProcessingBackground);
        DoubleSpinBoxImageProcessingBackgroundMax->setObjectName(QString::fromUtf8("DoubleSpinBoxImageProcessingBackgroundMax"));
        DoubleSpinBoxImageProcessingBackgroundMax->setMinimum(-255);
        DoubleSpinBoxImageProcessingBackgroundMax->setMaximum(255);

        FormLayoutImageProcessingBackground->setWidget(4, QFormLayout::FieldRole, DoubleSpinBoxImageProcessingBackgroundMax);

        DoubleSpinBoxImageProcessingBackgroundMin = new QDoubleSpinBox(GroupBoxImageProcessingBackground);
        DoubleSpinBoxImageProcessingBackgroundMin->setObjectName(QString::fromUtf8("DoubleSpinBoxImageProcessingBackgroundMin"));
        DoubleSpinBoxImageProcessingBackgroundMin->setMinimum(-255);
        DoubleSpinBoxImageProcessingBackgroundMin->setMaximum(255);

        FormLayoutImageProcessingBackground->setWidget(5, QFormLayout::FieldRole, DoubleSpinBoxImageProcessingBackgroundMin);

        LabelImageProcessingBackgroundMax = new QLabel(GroupBoxImageProcessingBackground);
        LabelImageProcessingBackgroundMax->setObjectName(QString::fromUtf8("LabelImageProcessingBackgroundMax"));

        FormLayoutImageProcessingBackground->setWidget(4, QFormLayout::LabelRole, LabelImageProcessingBackgroundMax);

        LabelImageProcessingBackgroundMin = new QLabel(GroupBoxImageProcessingBackground);
        LabelImageProcessingBackgroundMin->setObjectName(QString::fromUtf8("LabelImageProcessingBackgroundMin"));

        FormLayoutImageProcessingBackground->setWidget(5, QFormLayout::LabelRole, LabelImageProcessingBackgroundMin);


        gridLayout_6->addLayout(FormLayoutImageProcessingBackground, 0, 1, 1, 4);

        HorizontalSpacerImageProcessingBackground = new QSpacerItem(206, 24, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(HorizontalSpacerImageProcessingBackground, 3, 1, 1, 1);

        PushButtonImageProcessingBackgroundGenerate = new QPushButton(GroupBoxImageProcessingBackground);
        PushButtonImageProcessingBackgroundGenerate->setObjectName(QString::fromUtf8("PushButtonImageProcessingBackgroundGenerate"));

        gridLayout_6->addWidget(PushButtonImageProcessingBackgroundGenerate, 3, 4, 1, 1);


        gridLayout_13->addWidget(GroupBoxImageProcessingBackground, 0, 2, 2, 1);

        GroupBoxImageProcessingFindLowContrastRegion = new QGroupBox(TabImageProcessing);
        GroupBoxImageProcessingFindLowContrastRegion->setObjectName(QString::fromUtf8("GroupBoxImageProcessingFindLowContrastRegion"));
        gridLayout_5 = new QGridLayout(GroupBoxImageProcessingFindLowContrastRegion);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        HorizontalLayoutImageProcessingLCR = new QHBoxLayout();
        HorizontalLayoutImageProcessingLCR->setObjectName(QString::fromUtf8("HorizontalLayoutImageProcessingLCR"));
        LabelImageProcessingDataNo = new QLabel(GroupBoxImageProcessingFindLowContrastRegion);
        LabelImageProcessingDataNo->setObjectName(QString::fromUtf8("LabelImageProcessingDataNo"));

        HorizontalLayoutImageProcessingLCR->addWidget(LabelImageProcessingDataNo);

        SpinBoxImageProcessingDataNo = new QSpinBox(GroupBoxImageProcessingFindLowContrastRegion);
        SpinBoxImageProcessingDataNo->setObjectName(QString::fromUtf8("SpinBoxImageProcessingDataNo"));

        HorizontalLayoutImageProcessingLCR->addWidget(SpinBoxImageProcessingDataNo);


        gridLayout_5->addLayout(HorizontalLayoutImageProcessingLCR, 0, 0, 1, 2);

        HorizontalSpacerImageProcessingFindLowContrastRegion = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(HorizontalSpacerImageProcessingFindLowContrastRegion, 1, 0, 1, 1);

        PushButtonImageProcessingFindLCR = new QPushButton(GroupBoxImageProcessingFindLowContrastRegion);
        PushButtonImageProcessingFindLCR->setObjectName(QString::fromUtf8("PushButtonImageProcessingFindLCR"));

        gridLayout_5->addWidget(PushButtonImageProcessingFindLCR, 1, 1, 1, 1);


        gridLayout_13->addWidget(GroupBoxImageProcessingFindLowContrastRegion, 1, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        PushButtonDanger = new QPushButton(TabImageProcessing);
        PushButtonDanger->setObjectName(QString::fromUtf8("PushButtonDanger"));

        horizontalLayout->addWidget(PushButtonDanger);

        PushButtonPoison = new QPushButton(TabImageProcessing);
        PushButtonPoison->setObjectName(QString::fromUtf8("PushButtonPoison"));

        horizontalLayout->addWidget(PushButtonPoison);

        PushButtonEmergency = new QPushButton(TabImageProcessing);
        PushButtonEmergency->setObjectName(QString::fromUtf8("PushButtonEmergency"));

        horizontalLayout->addWidget(PushButtonEmergency);


        gridLayout_13->addLayout(horizontalLayout, 2, 0, 1, 3);

        Tabs->addTab(TabImageProcessing, QString());
        TabViewControl = new QWidget();
        TabViewControl->setObjectName(QString::fromUtf8("TabViewControl"));
        gridLayout_3 = new QGridLayout(TabViewControl);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        HorizontalLayoutViewControlUpper = new QHBoxLayout();
        HorizontalLayoutViewControlUpper->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlUpper"));
        HorizontalLayoutViewControlUpperShow = new QHBoxLayout();
        HorizontalLayoutViewControlUpperShow->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlUpperShow"));
        LabelViewControlDataNo = new QLabel(TabViewControl);
        LabelViewControlDataNo->setObjectName(QString::fromUtf8("LabelViewControlDataNo"));

        HorizontalLayoutViewControlUpperShow->addWidget(LabelViewControlDataNo);

        SpinBoxViewControlDataNo = new QSpinBox(TabViewControl);
        SpinBoxViewControlDataNo->setObjectName(QString::fromUtf8("SpinBoxViewControlDataNo"));
        SpinBoxViewControlDataNo->setMaximum(9);

        HorizontalLayoutViewControlUpperShow->addWidget(SpinBoxViewControlDataNo);

        CheckBoxViewControlShow = new QCheckBox(TabViewControl);
        CheckBoxViewControlShow->setObjectName(QString::fromUtf8("CheckBoxViewControlShow"));

        HorizontalLayoutViewControlUpperShow->addWidget(CheckBoxViewControlShow);

        CheckBoxViewControlAlphaMode = new QCheckBox(TabViewControl);
        CheckBoxViewControlAlphaMode->setObjectName(QString::fromUtf8("CheckBoxViewControlAlphaMode"));

        HorizontalLayoutViewControlUpperShow->addWidget(CheckBoxViewControlAlphaMode);

        CheckBoxViewControlLCR = new QCheckBox(TabViewControl);
        CheckBoxViewControlLCR->setObjectName(QString::fromUtf8("CheckBoxViewControlLCR"));

        HorizontalLayoutViewControlUpperShow->addWidget(CheckBoxViewControlLCR);


        HorizontalLayoutViewControlUpper->addLayout(HorizontalLayoutViewControlUpperShow);

        HorizontalSpacerViewControlUpper = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlUpper->addItem(HorizontalSpacerViewControlUpper);

        PushButtonViewControlOrthoView = new QPushButton(TabViewControl);
        PushButtonViewControlOrthoView->setObjectName(QString::fromUtf8("PushButtonViewControlOrthoView"));

        HorizontalLayoutViewControlUpper->addWidget(PushButtonViewControlOrthoView);

        PushButtonViewControlResetOrthoViewSize = new QPushButton(TabViewControl);
        PushButtonViewControlResetOrthoViewSize->setObjectName(QString::fromUtf8("PushButtonViewControlResetOrthoViewSize"));

        HorizontalLayoutViewControlUpper->addWidget(PushButtonViewControlResetOrthoViewSize);


        gridLayout_3->addLayout(HorizontalLayoutViewControlUpper, 0, 0, 1, 1);

        HorizontalLayoutViewControlMain = new QHBoxLayout();
        HorizontalLayoutViewControlMain->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlMain"));
        GroupBoxViewControlThreshold = new QGroupBox(TabViewControl);
        GroupBoxViewControlThreshold->setObjectName(QString::fromUtf8("GroupBoxViewControlThreshold"));
        sizePolicy.setHeightForWidth(GroupBoxViewControlThreshold->sizePolicy().hasHeightForWidth());
        GroupBoxViewControlThreshold->setSizePolicy(sizePolicy);
        GroupBoxViewControlThreshold->setMinimumSize(QSize(80, 150));
        GroupBoxViewControlThreshold->setFlat(false);
        gridLayout_8 = new QGridLayout(GroupBoxViewControlThreshold);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        VerticalSliderViewControlThreshold = new QSlider(GroupBoxViewControlThreshold);
        VerticalSliderViewControlThreshold->setObjectName(QString::fromUtf8("VerticalSliderViewControlThreshold"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(5);
        sizePolicy3.setHeightForWidth(VerticalSliderViewControlThreshold->sizePolicy().hasHeightForWidth());
        VerticalSliderViewControlThreshold->setSizePolicy(sizePolicy3);
        VerticalSliderViewControlThreshold->setMinimumSize(QSize(0, 50));
        VerticalSliderViewControlThreshold->setMaximum(255);
        VerticalSliderViewControlThreshold->setValue(100);
        VerticalSliderViewControlThreshold->setOrientation(Qt::Vertical);

        gridLayout_8->addWidget(VerticalSliderViewControlThreshold, 0, 0, 1, 1);

        LineEditViewControlThreshold = new QLineEdit(GroupBoxViewControlThreshold);
        LineEditViewControlThreshold->setObjectName(QString::fromUtf8("LineEditViewControlThreshold"));
        sizePolicy1.setHeightForWidth(LineEditViewControlThreshold->sizePolicy().hasHeightForWidth());
        LineEditViewControlThreshold->setSizePolicy(sizePolicy1);
        LineEditViewControlThreshold->setMinimumSize(QSize(40, 0));

        gridLayout_8->addWidget(LineEditViewControlThreshold, 1, 0, 1, 1);


        HorizontalLayoutViewControlMain->addWidget(GroupBoxViewControlThreshold);

        GroupBoxViewControlPointer = new QGroupBox(TabViewControl);
        GroupBoxViewControlPointer->setObjectName(QString::fromUtf8("GroupBoxViewControlPointer"));
        GroupBoxViewControlPointer->setMinimumSize(QSize(190, 150));
        GroupBoxViewControlPointer->setFlat(false);
        gridLayout_9 = new QGridLayout(GroupBoxViewControlPointer);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        LabelViewControlPointerX = new QLabel(GroupBoxViewControlPointer);
        LabelViewControlPointerX->setObjectName(QString::fromUtf8("LabelViewControlPointerX"));
        LabelViewControlPointerX->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(LabelViewControlPointerX, 0, 1, 1, 1);

        LabelViewControlPointerY = new QLabel(GroupBoxViewControlPointer);
        LabelViewControlPointerY->setObjectName(QString::fromUtf8("LabelViewControlPointerY"));
        LabelViewControlPointerY->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(LabelViewControlPointerY, 0, 2, 1, 1);

        LabelViewControlPointerZ = new QLabel(GroupBoxViewControlPointer);
        LabelViewControlPointerZ->setObjectName(QString::fromUtf8("LabelViewControlPointerZ"));
        LabelViewControlPointerZ->setAlignment(Qt::AlignCenter);

        gridLayout_9->addWidget(LabelViewControlPointerZ, 0, 3, 1, 2);

        VerticalSliderViewControlPointerXum = new QSlider(GroupBoxViewControlPointer);
        VerticalSliderViewControlPointerXum->setObjectName(QString::fromUtf8("VerticalSliderViewControlPointerXum"));
        VerticalSliderViewControlPointerXum->setMinimum(-300);
        VerticalSliderViewControlPointerXum->setMaximum(300);
        VerticalSliderViewControlPointerXum->setPageStep(1);
        VerticalSliderViewControlPointerXum->setOrientation(Qt::Vertical);

        gridLayout_9->addWidget(VerticalSliderViewControlPointerXum, 1, 1, 1, 1);

        VerticalSliderViewControlPointerYum = new QSlider(GroupBoxViewControlPointer);
        VerticalSliderViewControlPointerYum->setObjectName(QString::fromUtf8("VerticalSliderViewControlPointerYum"));
        VerticalSliderViewControlPointerYum->setMinimum(-300);
        VerticalSliderViewControlPointerYum->setMaximum(300);
        VerticalSliderViewControlPointerYum->setPageStep(1);
        VerticalSliderViewControlPointerYum->setOrientation(Qt::Vertical);

        gridLayout_9->addWidget(VerticalSliderViewControlPointerYum, 1, 2, 1, 1);

        VerticalSliderViewControlPointerZum = new QSlider(GroupBoxViewControlPointer);
        VerticalSliderViewControlPointerZum->setObjectName(QString::fromUtf8("VerticalSliderViewControlPointerZum"));
        VerticalSliderViewControlPointerZum->setMinimum(-300);
        VerticalSliderViewControlPointerZum->setMaximum(300);
        VerticalSliderViewControlPointerZum->setPageStep(1);
        VerticalSliderViewControlPointerZum->setOrientation(Qt::Vertical);

        gridLayout_9->addWidget(VerticalSliderViewControlPointerZum, 1, 4, 1, 1);

        LineEditViewControlPointerXum = new QLineEdit(GroupBoxViewControlPointer);
        LineEditViewControlPointerXum->setObjectName(QString::fromUtf8("LineEditViewControlPointerXum"));

        gridLayout_9->addWidget(LineEditViewControlPointerXum, 2, 1, 1, 1);

        LineEditViewControlPointerYum = new QLineEdit(GroupBoxViewControlPointer);
        LineEditViewControlPointerYum->setObjectName(QString::fromUtf8("LineEditViewControlPointerYum"));

        gridLayout_9->addWidget(LineEditViewControlPointerYum, 2, 2, 1, 2);

        LineEditViewControlPointerZum = new QLineEdit(GroupBoxViewControlPointer);
        LineEditViewControlPointerZum->setObjectName(QString::fromUtf8("LineEditViewControlPointerZum"));

        gridLayout_9->addWidget(LineEditViewControlPointerZum, 2, 4, 1, 1);

        CheckBoxViewControlPointer = new QCheckBox(GroupBoxViewControlPointer);
        CheckBoxViewControlPointer->setObjectName(QString::fromUtf8("CheckBoxViewControlPointer"));
        CheckBoxViewControlPointer->setChecked(true);

        gridLayout_9->addWidget(CheckBoxViewControlPointer, 0, 0, 1, 1);


        HorizontalLayoutViewControlMain->addWidget(GroupBoxViewControlPointer);

        GroupBoxViewControlROI = new QGroupBox(TabViewControl);
        GroupBoxViewControlROI->setObjectName(QString::fromUtf8("GroupBoxViewControlROI"));
        sizePolicy.setHeightForWidth(GroupBoxViewControlROI->sizePolicy().hasHeightForWidth());
        GroupBoxViewControlROI->setSizePolicy(sizePolicy);
        GroupBoxViewControlROI->setMinimumSize(QSize(330, 150));
        GroupBoxViewControlROI->setFlat(false);
        gridLayout_10 = new QGridLayout(GroupBoxViewControlROI);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        HorizontalLayoutViewControlROI = new QHBoxLayout();
        HorizontalLayoutViewControlROI->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlROI"));
        VerticalLayoutViewControlROIX = new QVBoxLayout();
        VerticalLayoutViewControlROIX->setObjectName(QString::fromUtf8("VerticalLayoutViewControlROIX"));
        LabelViewControlROIX = new QLabel(GroupBoxViewControlROI);
        LabelViewControlROIX->setObjectName(QString::fromUtf8("LabelViewControlROIX"));
        LabelViewControlROIX->setAlignment(Qt::AlignCenter);

        VerticalLayoutViewControlROIX->addWidget(LabelViewControlROIX);

        GridLayoutViewControlROIX = new QGridLayout();
        GridLayoutViewControlROIX->setObjectName(QString::fromUtf8("GridLayoutViewControlROIX"));
        SpinBoxViewControlROIXFrom = new QSpinBox(GroupBoxViewControlROI);
        SpinBoxViewControlROIXFrom->setObjectName(QString::fromUtf8("SpinBoxViewControlROIXFrom"));

        GridLayoutViewControlROIX->addWidget(SpinBoxViewControlROIXFrom, 2, 0, 1, 1);

        SpinBoxViewControlROIXTo = new QSpinBox(GroupBoxViewControlROI);
        SpinBoxViewControlROIXTo->setObjectName(QString::fromUtf8("SpinBoxViewControlROIXTo"));

        GridLayoutViewControlROIX->addWidget(SpinBoxViewControlROIXTo, 2, 1, 1, 1);

        HorizontalLayoutViewControlROIXFrom = new QHBoxLayout();
        HorizontalLayoutViewControlROIXFrom->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlROIXFrom"));
        HorizontalSpacerViewControlROIXFrom1 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlROIXFrom->addItem(HorizontalSpacerViewControlROIXFrom1);

        VerticalSliderViewControlROIXFrom = new QSlider(GroupBoxViewControlROI);
        VerticalSliderViewControlROIXFrom->setObjectName(QString::fromUtf8("VerticalSliderViewControlROIXFrom"));
        VerticalSliderViewControlROIXFrom->setOrientation(Qt::Vertical);

        HorizontalLayoutViewControlROIXFrom->addWidget(VerticalSliderViewControlROIXFrom);

        HorizontalSpacerViewControlROIXFrom2 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlROIXFrom->addItem(HorizontalSpacerViewControlROIXFrom2);


        GridLayoutViewControlROIX->addLayout(HorizontalLayoutViewControlROIXFrom, 1, 0, 1, 1);

        HorizontalLayoutViewControlROIXTo = new QHBoxLayout();
        HorizontalLayoutViewControlROIXTo->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlROIXTo"));
        HorizontalSpacerViewControlROIXTo1 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlROIXTo->addItem(HorizontalSpacerViewControlROIXTo1);

        VerticalSliderViewControlROIXTo = new QSlider(GroupBoxViewControlROI);
        VerticalSliderViewControlROIXTo->setObjectName(QString::fromUtf8("VerticalSliderViewControlROIXTo"));
        VerticalSliderViewControlROIXTo->setOrientation(Qt::Vertical);

        HorizontalLayoutViewControlROIXTo->addWidget(VerticalSliderViewControlROIXTo);

        HorizontalSpacerViewControlROIXTo2 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlROIXTo->addItem(HorizontalSpacerViewControlROIXTo2);


        GridLayoutViewControlROIX->addLayout(HorizontalLayoutViewControlROIXTo, 1, 1, 1, 1);

        LabelViewControlROIXFrom = new QLabel(GroupBoxViewControlROI);
        LabelViewControlROIXFrom->setObjectName(QString::fromUtf8("LabelViewControlROIXFrom"));
        LabelViewControlROIXFrom->setAlignment(Qt::AlignCenter);

        GridLayoutViewControlROIX->addWidget(LabelViewControlROIXFrom, 0, 0, 1, 1);

        LabelViewControlROIXTo = new QLabel(GroupBoxViewControlROI);
        LabelViewControlROIXTo->setObjectName(QString::fromUtf8("LabelViewControlROIXTo"));
        LabelViewControlROIXTo->setAlignment(Qt::AlignCenter);

        GridLayoutViewControlROIX->addWidget(LabelViewControlROIXTo, 0, 1, 1, 1);


        VerticalLayoutViewControlROIX->addLayout(GridLayoutViewControlROIX);


        HorizontalLayoutViewControlROI->addLayout(VerticalLayoutViewControlROIX);

        VerticalLayoutViewControlROIY = new QVBoxLayout();
        VerticalLayoutViewControlROIY->setObjectName(QString::fromUtf8("VerticalLayoutViewControlROIY"));
        LabelViewControlROIY = new QLabel(GroupBoxViewControlROI);
        LabelViewControlROIY->setObjectName(QString::fromUtf8("LabelViewControlROIY"));
        LabelViewControlROIY->setAlignment(Qt::AlignCenter);

        VerticalLayoutViewControlROIY->addWidget(LabelViewControlROIY);

        GridLayoutViewControlROIY = new QGridLayout();
        GridLayoutViewControlROIY->setObjectName(QString::fromUtf8("GridLayoutViewControlROIY"));
        SpinBoxViewControlROIYFrom = new QSpinBox(GroupBoxViewControlROI);
        SpinBoxViewControlROIYFrom->setObjectName(QString::fromUtf8("SpinBoxViewControlROIYFrom"));

        GridLayoutViewControlROIY->addWidget(SpinBoxViewControlROIYFrom, 2, 0, 1, 1);

        SpinBoxViewControlROIYTo = new QSpinBox(GroupBoxViewControlROI);
        SpinBoxViewControlROIYTo->setObjectName(QString::fromUtf8("SpinBoxViewControlROIYTo"));

        GridLayoutViewControlROIY->addWidget(SpinBoxViewControlROIYTo, 2, 1, 1, 1);

        HorizontalLayoutViewControlROIYFrom = new QHBoxLayout();
        HorizontalLayoutViewControlROIYFrom->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlROIYFrom"));
        HorizontalSpacerViewControlROIYFrom1 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlROIYFrom->addItem(HorizontalSpacerViewControlROIYFrom1);

        VerticalSliderViewControlROIYFrom = new QSlider(GroupBoxViewControlROI);
        VerticalSliderViewControlROIYFrom->setObjectName(QString::fromUtf8("VerticalSliderViewControlROIYFrom"));
        VerticalSliderViewControlROIYFrom->setOrientation(Qt::Vertical);

        HorizontalLayoutViewControlROIYFrom->addWidget(VerticalSliderViewControlROIYFrom);

        HorizontalSpacerViewControlROIYFrom2 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlROIYFrom->addItem(HorizontalSpacerViewControlROIYFrom2);


        GridLayoutViewControlROIY->addLayout(HorizontalLayoutViewControlROIYFrom, 1, 0, 1, 1);

        HorizontalLayoutViewControlROIYTo = new QHBoxLayout();
        HorizontalLayoutViewControlROIYTo->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlROIYTo"));
        HorizontalSpacerViewControlROIYTo1 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlROIYTo->addItem(HorizontalSpacerViewControlROIYTo1);

        VerticalSliderViewControlROIYTo = new QSlider(GroupBoxViewControlROI);
        VerticalSliderViewControlROIYTo->setObjectName(QString::fromUtf8("VerticalSliderViewControlROIYTo"));
        VerticalSliderViewControlROIYTo->setOrientation(Qt::Vertical);

        HorizontalLayoutViewControlROIYTo->addWidget(VerticalSliderViewControlROIYTo);

        HorizontalSpacerViewControlROIYTo2 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlROIYTo->addItem(HorizontalSpacerViewControlROIYTo2);


        GridLayoutViewControlROIY->addLayout(HorizontalLayoutViewControlROIYTo, 1, 1, 1, 1);

        LabelViewControlROIYFrom = new QLabel(GroupBoxViewControlROI);
        LabelViewControlROIYFrom->setObjectName(QString::fromUtf8("LabelViewControlROIYFrom"));
        LabelViewControlROIYFrom->setAlignment(Qt::AlignCenter);

        GridLayoutViewControlROIY->addWidget(LabelViewControlROIYFrom, 0, 0, 1, 1);

        LabelViewControlROIYTo = new QLabel(GroupBoxViewControlROI);
        LabelViewControlROIYTo->setObjectName(QString::fromUtf8("LabelViewControlROIYTo"));
        LabelViewControlROIYTo->setAlignment(Qt::AlignCenter);

        GridLayoutViewControlROIY->addWidget(LabelViewControlROIYTo, 0, 1, 1, 1);


        VerticalLayoutViewControlROIY->addLayout(GridLayoutViewControlROIY);


        HorizontalLayoutViewControlROI->addLayout(VerticalLayoutViewControlROIY);

        VerticalLayoutViewControlROIZ = new QVBoxLayout();
        VerticalLayoutViewControlROIZ->setObjectName(QString::fromUtf8("VerticalLayoutViewControlROIZ"));
        LabelViewControlROIZ = new QLabel(GroupBoxViewControlROI);
        LabelViewControlROIZ->setObjectName(QString::fromUtf8("LabelViewControlROIZ"));
        LabelViewControlROIZ->setAlignment(Qt::AlignCenter);

        VerticalLayoutViewControlROIZ->addWidget(LabelViewControlROIZ);

        GridLayoutViewControlROIZ = new QGridLayout();
        GridLayoutViewControlROIZ->setObjectName(QString::fromUtf8("GridLayoutViewControlROIZ"));
        SpinBoxViewControlROIZFrom = new QSpinBox(GroupBoxViewControlROI);
        SpinBoxViewControlROIZFrom->setObjectName(QString::fromUtf8("SpinBoxViewControlROIZFrom"));

        GridLayoutViewControlROIZ->addWidget(SpinBoxViewControlROIZFrom, 2, 0, 1, 1);

        SpinBoxViewControlROIZTo = new QSpinBox(GroupBoxViewControlROI);
        SpinBoxViewControlROIZTo->setObjectName(QString::fromUtf8("SpinBoxViewControlROIZTo"));

        GridLayoutViewControlROIZ->addWidget(SpinBoxViewControlROIZTo, 2, 1, 1, 1);

        VorizontalLayoutViewControlROIZFrom = new QHBoxLayout();
        VorizontalLayoutViewControlROIZFrom->setObjectName(QString::fromUtf8("VorizontalLayoutViewControlROIZFrom"));
        HorizontalSpacerViewControlROIZFrom1 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        VorizontalLayoutViewControlROIZFrom->addItem(HorizontalSpacerViewControlROIZFrom1);

        VerticalSliderViewControlROIZFrom = new QSlider(GroupBoxViewControlROI);
        VerticalSliderViewControlROIZFrom->setObjectName(QString::fromUtf8("VerticalSliderViewControlROIZFrom"));
        VerticalSliderViewControlROIZFrom->setOrientation(Qt::Vertical);

        VorizontalLayoutViewControlROIZFrom->addWidget(VerticalSliderViewControlROIZFrom);

        HorizontalSpacerViewControlROIZFrom2 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        VorizontalLayoutViewControlROIZFrom->addItem(HorizontalSpacerViewControlROIZFrom2);


        GridLayoutViewControlROIZ->addLayout(VorizontalLayoutViewControlROIZFrom, 1, 0, 1, 1);

        HorizontalLayoutViewControlROIZTo = new QHBoxLayout();
        HorizontalLayoutViewControlROIZTo->setObjectName(QString::fromUtf8("HorizontalLayoutViewControlROIZTo"));
        HorizontalSpacerViewControlROIZTo1 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlROIZTo->addItem(HorizontalSpacerViewControlROIZTo1);

        VerticalSliderViewControlROIZTo = new QSlider(GroupBoxViewControlROI);
        VerticalSliderViewControlROIZTo->setObjectName(QString::fromUtf8("VerticalSliderViewControlROIZTo"));
        VerticalSliderViewControlROIZTo->setOrientation(Qt::Vertical);

        HorizontalLayoutViewControlROIZTo->addWidget(VerticalSliderViewControlROIZTo);

        HorizontalSpacerViewControlROIZTo2 = new QSpacerItem(0, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        HorizontalLayoutViewControlROIZTo->addItem(HorizontalSpacerViewControlROIZTo2);


        GridLayoutViewControlROIZ->addLayout(HorizontalLayoutViewControlROIZTo, 1, 1, 1, 1);

        LabelViewControlROIZFrom = new QLabel(GroupBoxViewControlROI);
        LabelViewControlROIZFrom->setObjectName(QString::fromUtf8("LabelViewControlROIZFrom"));
        LabelViewControlROIZFrom->setAlignment(Qt::AlignCenter);

        GridLayoutViewControlROIZ->addWidget(LabelViewControlROIZFrom, 0, 0, 1, 1);

        LabelViewControlROIZTo = new QLabel(GroupBoxViewControlROI);
        LabelViewControlROIZTo->setObjectName(QString::fromUtf8("LabelViewControlROIZTo"));
        LabelViewControlROIZTo->setAlignment(Qt::AlignCenter);

        GridLayoutViewControlROIZ->addWidget(LabelViewControlROIZTo, 0, 1, 1, 1);


        VerticalLayoutViewControlROIZ->addLayout(GridLayoutViewControlROIZ);


        HorizontalLayoutViewControlROI->addLayout(VerticalLayoutViewControlROIZ);


        gridLayout_10->addLayout(HorizontalLayoutViewControlROI, 0, 0, 1, 1);


        HorizontalLayoutViewControlMain->addWidget(GroupBoxViewControlROI);

        GroupBoxViewControlColor = new QGroupBox(TabViewControl);
        GroupBoxViewControlColor->setObjectName(QString::fromUtf8("GroupBoxViewControlColor"));
        GroupBoxViewControlColor->setEnabled(true);
        GroupBoxViewControlColor->setMinimumSize(QSize(30, 150));
        GroupBoxViewControlColor->setFlat(false);
        gridLayout_2 = new QGridLayout(GroupBoxViewControlColor);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        LabelViewControlColorR = new QLabel(GroupBoxViewControlColor);
        LabelViewControlColorR->setObjectName(QString::fromUtf8("LabelViewControlColorR"));
        LabelViewControlColorR->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(LabelViewControlColorR, 0, 0, 1, 1);

        LabelViewControlColorG = new QLabel(GroupBoxViewControlColor);
        LabelViewControlColorG->setObjectName(QString::fromUtf8("LabelViewControlColorG"));
        LabelViewControlColorG->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(LabelViewControlColorG, 0, 1, 1, 1);

        LabelViewControlColorB = new QLabel(GroupBoxViewControlColor);
        LabelViewControlColorB->setObjectName(QString::fromUtf8("LabelViewControlColorB"));
        LabelViewControlColorB->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(LabelViewControlColorB, 0, 2, 1, 1);

        VerticalSliderViewControlColorR = new QSlider(GroupBoxViewControlColor);
        VerticalSliderViewControlColorR->setObjectName(QString::fromUtf8("VerticalSliderViewControlColorR"));
        VerticalSliderViewControlColorR->setMinimum(0);
        VerticalSliderViewControlColorR->setMaximum(255);
        VerticalSliderViewControlColorR->setValue(255);
        VerticalSliderViewControlColorR->setOrientation(Qt::Vertical);

        gridLayout_2->addWidget(VerticalSliderViewControlColorR, 1, 0, 1, 1);

        VerticalSliderViewControlColorG = new QSlider(GroupBoxViewControlColor);
        VerticalSliderViewControlColorG->setObjectName(QString::fromUtf8("VerticalSliderViewControlColorG"));
        VerticalSliderViewControlColorG->setMinimum(0);
        VerticalSliderViewControlColorG->setMaximum(255);
        VerticalSliderViewControlColorG->setValue(255);
        VerticalSliderViewControlColorG->setOrientation(Qt::Vertical);

        gridLayout_2->addWidget(VerticalSliderViewControlColorG, 1, 1, 1, 1);

        VerticalSliderViewControlColorB = new QSlider(GroupBoxViewControlColor);
        VerticalSliderViewControlColorB->setObjectName(QString::fromUtf8("VerticalSliderViewControlColorB"));
        VerticalSliderViewControlColorB->setMinimum(0);
        VerticalSliderViewControlColorB->setMaximum(255);
        VerticalSliderViewControlColorB->setValue(255);
        VerticalSliderViewControlColorB->setOrientation(Qt::Vertical);

        gridLayout_2->addWidget(VerticalSliderViewControlColorB, 1, 2, 1, 1);

        LineEditViewControlColorR = new QLineEdit(GroupBoxViewControlColor);
        LineEditViewControlColorR->setObjectName(QString::fromUtf8("LineEditViewControlColorR"));
        LineEditViewControlColorR->setMaxLength(3);

        gridLayout_2->addWidget(LineEditViewControlColorR, 2, 0, 1, 1);

        LineEditViewControlColorG = new QLineEdit(GroupBoxViewControlColor);
        LineEditViewControlColorG->setObjectName(QString::fromUtf8("LineEditViewControlColorG"));
        LineEditViewControlColorG->setMaxLength(3);

        gridLayout_2->addWidget(LineEditViewControlColorG, 2, 1, 1, 1);

        LineEditViewControlColorB = new QLineEdit(GroupBoxViewControlColor);
        LineEditViewControlColorB->setObjectName(QString::fromUtf8("LineEditViewControlColorB"));
        LineEditViewControlColorB->setMaxLength(3);

        gridLayout_2->addWidget(LineEditViewControlColorB, 2, 2, 1, 1);


        HorizontalLayoutViewControlMain->addWidget(GroupBoxViewControlColor);

        GroupBoxViewControlTranslation = new QGroupBox(TabViewControl);
        GroupBoxViewControlTranslation->setObjectName(QString::fromUtf8("GroupBoxViewControlTranslation"));
        GroupBoxViewControlTranslation->setEnabled(false);
        GroupBoxViewControlTranslation->setMinimumSize(QSize(30, 150));
        GroupBoxViewControlTranslation->setFlat(false);
        gridLayout = new QGridLayout(GroupBoxViewControlTranslation);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        LabelViewControlTranslationX = new QLabel(GroupBoxViewControlTranslation);
        LabelViewControlTranslationX->setObjectName(QString::fromUtf8("LabelViewControlTranslationX"));
        LabelViewControlTranslationX->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(LabelViewControlTranslationX, 0, 0, 1, 1);

        LabelViewControlTranslationY = new QLabel(GroupBoxViewControlTranslation);
        LabelViewControlTranslationY->setObjectName(QString::fromUtf8("LabelViewControlTranslationY"));
        LabelViewControlTranslationY->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(LabelViewControlTranslationY, 0, 1, 1, 1);

        LabelViewControlTranslationZ = new QLabel(GroupBoxViewControlTranslation);
        LabelViewControlTranslationZ->setObjectName(QString::fromUtf8("LabelViewControlTranslationZ"));
        LabelViewControlTranslationZ->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(LabelViewControlTranslationZ, 0, 2, 1, 1);

        VerticalSliderViewControlTranslationX = new QSlider(GroupBoxViewControlTranslation);
        VerticalSliderViewControlTranslationX->setObjectName(QString::fromUtf8("VerticalSliderViewControlTranslationX"));
        VerticalSliderViewControlTranslationX->setMinimum(-300);
        VerticalSliderViewControlTranslationX->setMaximum(300);
        VerticalSliderViewControlTranslationX->setOrientation(Qt::Vertical);

        gridLayout->addWidget(VerticalSliderViewControlTranslationX, 1, 0, 1, 1);

        VerticalSliderViewControlTranslationY = new QSlider(GroupBoxViewControlTranslation);
        VerticalSliderViewControlTranslationY->setObjectName(QString::fromUtf8("VerticalSliderViewControlTranslationY"));
        VerticalSliderViewControlTranslationY->setMinimum(-300);
        VerticalSliderViewControlTranslationY->setMaximum(300);
        VerticalSliderViewControlTranslationY->setOrientation(Qt::Vertical);

        gridLayout->addWidget(VerticalSliderViewControlTranslationY, 1, 1, 1, 1);

        VerticalSliderViewControlTranslationZ = new QSlider(GroupBoxViewControlTranslation);
        VerticalSliderViewControlTranslationZ->setObjectName(QString::fromUtf8("VerticalSliderViewControlTranslationZ"));
        VerticalSliderViewControlTranslationZ->setMinimum(-300);
        VerticalSliderViewControlTranslationZ->setMaximum(300);
        VerticalSliderViewControlTranslationZ->setOrientation(Qt::Vertical);

        gridLayout->addWidget(VerticalSliderViewControlTranslationZ, 1, 2, 1, 1);

        LineEditViewControlTranslationY = new QLineEdit(GroupBoxViewControlTranslation);
        LineEditViewControlTranslationY->setObjectName(QString::fromUtf8("LineEditViewControlTranslationY"));

        gridLayout->addWidget(LineEditViewControlTranslationY, 2, 1, 1, 1);

        LineEditViewControlTranslationZ = new QLineEdit(GroupBoxViewControlTranslation);
        LineEditViewControlTranslationZ->setObjectName(QString::fromUtf8("LineEditViewControlTranslationZ"));

        gridLayout->addWidget(LineEditViewControlTranslationZ, 2, 2, 1, 1);

        LineEditViewControlTranslationXum = new QLineEdit(GroupBoxViewControlTranslation);
        LineEditViewControlTranslationXum->setObjectName(QString::fromUtf8("LineEditViewControlTranslationXum"));

        gridLayout->addWidget(LineEditViewControlTranslationXum, 3, 0, 1, 1);

        LineEditViewControlTranslationYum = new QLineEdit(GroupBoxViewControlTranslation);
        LineEditViewControlTranslationYum->setObjectName(QString::fromUtf8("LineEditViewControlTranslationYum"));

        gridLayout->addWidget(LineEditViewControlTranslationYum, 3, 1, 1, 1);

        LineEditViewControlTranslationZum = new QLineEdit(GroupBoxViewControlTranslation);
        LineEditViewControlTranslationZum->setObjectName(QString::fromUtf8("LineEditViewControlTranslationZum"));

        gridLayout->addWidget(LineEditViewControlTranslationZum, 3, 2, 1, 1);

        LineEditViewControlTranslationX = new QLineEdit(GroupBoxViewControlTranslation);
        LineEditViewControlTranslationX->setObjectName(QString::fromUtf8("LineEditViewControlTranslationX"));

        gridLayout->addWidget(LineEditViewControlTranslationX, 2, 0, 1, 1);


        HorizontalLayoutViewControlMain->addWidget(GroupBoxViewControlTranslation);


        gridLayout_3->addLayout(HorizontalLayoutViewControlMain, 1, 0, 1, 1);

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

        gridLayout_7->addWidget(Tabs, 0, 0, 1, 1);

        QWidget::setTabOrder(Tabs, LineEditFileLoadFilePath);
        QWidget::setTabOrder(LineEditFileLoadFilePath, PushButtonFileLoadBrowse);
        QWidget::setTabOrder(PushButtonFileLoadBrowse, LineEditFileLoadDirectory);
        QWidget::setTabOrder(LineEditFileLoadDirectory, LineEditFileLoadBaseName);
        QWidget::setTabOrder(LineEditFileLoadBaseName, LineEditFileLoadScaleX);
        QWidget::setTabOrder(LineEditFileLoadScaleX, LineEditFileLoadScaleY);
        QWidget::setTabOrder(LineEditFileLoadScaleY, LineEditFileLoadScaleZ);
        QWidget::setTabOrder(LineEditFileLoadScaleZ, SpinBoxFileLoadDataNo);
        QWidget::setTabOrder(SpinBoxFileLoadDataNo, PushButtonFileLoadClear);
        QWidget::setTabOrder(PushButtonFileLoadClear, PushButtonFileLoadLoad);
        QWidget::setTabOrder(PushButtonFileLoadLoad, SpinBoxFileSaveDataNo);
        QWidget::setTabOrder(SpinBoxFileSaveDataNo, LineEditFileSaveFilePath);
        QWidget::setTabOrder(LineEditFileSaveFilePath, PushButtonFileSaveBrowse);
        QWidget::setTabOrder(PushButtonFileSaveBrowse, LineEditFileSaveDirectory);
        QWidget::setTabOrder(LineEditFileSaveDirectory, LineEditFileSaveBaseName);
        QWidget::setTabOrder(LineEditFileSaveBaseName, PushButtonFileSaveClear);
        QWidget::setTabOrder(PushButtonFileSaveClear, PushButtonFileSaveSave);
        QWidget::setTabOrder(PushButtonFileSaveSave, SpinBoxExtractionDataNo);
        QWidget::setTabOrder(SpinBoxExtractionDataNo, PushButtonExtractionCurrentDataNo);
        QWidget::setTabOrder(PushButtonExtractionCurrentDataNo, SpinBoxExtractionTargetNo);
        QWidget::setTabOrder(SpinBoxExtractionTargetNo, HorizontalSliderExtractionBinaryThreshold);
        QWidget::setTabOrder(HorizontalSliderExtractionBinaryThreshold, LineEditExtractionBinaryThreshold);
        QWidget::setTabOrder(LineEditExtractionBinaryThreshold, PushButtonExtractionBinaryThresholdGetFromView);
        QWidget::setTabOrder(PushButtonExtractionBinaryThresholdGetFromView, CheckBoxExtractionMedianFilter);
        QWidget::setTabOrder(CheckBoxExtractionMedianFilter, CheckBoxExtractionROI);
        QWidget::setTabOrder(CheckBoxExtractionROI, CheckBoxExtractionDoRescanning);
        QWidget::setTabOrder(CheckBoxExtractionDoRescanning, SpinBoxExtractionDoRescanningStoreNo);
        QWidget::setTabOrder(SpinBoxExtractionDoRescanningStoreNo, LineEditExtractionStartPointX);
        QWidget::setTabOrder(LineEditExtractionStartPointX, LineEditExtractionStartPointY);
        QWidget::setTabOrder(LineEditExtractionStartPointY, LineEditExtractionStartPointZ);
        QWidget::setTabOrder(LineEditExtractionStartPointZ, PushButtonExtractionStartPointGetFromView);
        QWidget::setTabOrder(PushButtonExtractionStartPointGetFromView, LineEditExtractionCalcPropFileName);
        QWidget::setTabOrder(LineEditExtractionCalcPropFileName, CheckBoxExtractionCalcProp);
        QWidget::setTabOrder(CheckBoxExtractionCalcProp, SpinBoxExtractionCalcPropStartThreshold);
        QWidget::setTabOrder(SpinBoxExtractionCalcPropStartThreshold, SpinBoxExtractionCalcPropStopThreshold);
        QWidget::setTabOrder(SpinBoxExtractionCalcPropStopThreshold, PushButtonExtractionExtract);
        QWidget::setTabOrder(PushButtonExtractionExtract, PushButtonExtractionCancel);
        QWidget::setTabOrder(PushButtonExtractionCancel, PushButtonExtractionHandTracing);
        QWidget::setTabOrder(PushButtonExtractionHandTracing, SpinBoxImageProcessingGenerateStackImageDataNo);
        QWidget::setTabOrder(SpinBoxImageProcessingGenerateStackImageDataNo, ComboBoxImageProcessingGenerateStackImageType);
        QWidget::setTabOrder(ComboBoxImageProcessingGenerateStackImageType, DoubleSpinBoxImageProcessingGenerateStackImageParam1);
        QWidget::setTabOrder(DoubleSpinBoxImageProcessingGenerateStackImageParam1, DoubleSpinBoxImageProcessingGenerateStackImageParam2);
        QWidget::setTabOrder(DoubleSpinBoxImageProcessingGenerateStackImageParam2, DoubleSpinBoxImageProcessingGenerateStackImageParam3);
        QWidget::setTabOrder(DoubleSpinBoxImageProcessingGenerateStackImageParam3, DoubleSpinBoxImageProcessingGenerateStackImageParam4);
        QWidget::setTabOrder(DoubleSpinBoxImageProcessingGenerateStackImageParam4, DoubleSpinBoxImageProcessingGenerateStackImageParam5);
        QWidget::setTabOrder(DoubleSpinBoxImageProcessingGenerateStackImageParam5, PushButtonImageProcessingGenerateStackImage);
        QWidget::setTabOrder(PushButtonImageProcessingGenerateStackImage, SpinBoxImageProcessingNoiseDataNo);
        QWidget::setTabOrder(SpinBoxImageProcessingNoiseDataNo, DoubleSpinBoxImageProcessingNoiseSD);
        QWidget::setTabOrder(DoubleSpinBoxImageProcessingNoiseSD, PushButtonImageProcessingNoiseAddNoise);
        QWidget::setTabOrder(PushButtonImageProcessingNoiseAddNoise, SpinBoxImageProcessingDataNo);
        QWidget::setTabOrder(SpinBoxImageProcessingDataNo, PushButtonImageProcessingFindLCR);
        QWidget::setTabOrder(PushButtonImageProcessingFindLCR, SpinBoxImageProcessingBackgroundDataNo);
        QWidget::setTabOrder(SpinBoxImageProcessingBackgroundDataNo, ComboBoxImageProcessingBackgroundType);
        QWidget::setTabOrder(ComboBoxImageProcessingBackgroundType, LineEditImageProcessingBackgroundOriginX);
        QWidget::setTabOrder(LineEditImageProcessingBackgroundOriginX, LineEditImageProcessingBackgroundOriginY);
        QWidget::setTabOrder(LineEditImageProcessingBackgroundOriginY, LineEditImageProcessingBackgroundOriginZ);
        QWidget::setTabOrder(LineEditImageProcessingBackgroundOriginZ, LineEditImageProcessingBackgroundNormalVectorX);
        QWidget::setTabOrder(LineEditImageProcessingBackgroundNormalVectorX, LineEditImageProcessingBackgroundNormalVectorY);
        QWidget::setTabOrder(LineEditImageProcessingBackgroundNormalVectorY, LineEditImageProcessingBackgroundNormalVectorZ);
        QWidget::setTabOrder(LineEditImageProcessingBackgroundNormalVectorZ, DoubleSpinBoxImageProcessingBackgroundMax);
        QWidget::setTabOrder(DoubleSpinBoxImageProcessingBackgroundMax, DoubleSpinBoxImageProcessingBackgroundMin);
        QWidget::setTabOrder(DoubleSpinBoxImageProcessingBackgroundMin, DoubleSpinBoxImageProcessingBackgroundParameter);
        QWidget::setTabOrder(DoubleSpinBoxImageProcessingBackgroundParameter, PushButtonImageProcessingBackgroundGenerate);
        QWidget::setTabOrder(PushButtonImageProcessingBackgroundGenerate, SpinBoxViewControlDataNo);
        QWidget::setTabOrder(SpinBoxViewControlDataNo, CheckBoxViewControlShow);
        QWidget::setTabOrder(CheckBoxViewControlShow, CheckBoxViewControlAlphaMode);
        QWidget::setTabOrder(CheckBoxViewControlAlphaMode, PushButtonViewControlOrthoView);
        QWidget::setTabOrder(PushButtonViewControlOrthoView, PushButtonViewControlResetOrthoViewSize);
        QWidget::setTabOrder(PushButtonViewControlResetOrthoViewSize, VerticalSliderViewControlThreshold);
        QWidget::setTabOrder(VerticalSliderViewControlThreshold, LineEditViewControlThreshold);
        QWidget::setTabOrder(LineEditViewControlThreshold, CheckBoxViewControlPointer);
        QWidget::setTabOrder(CheckBoxViewControlPointer, VerticalSliderViewControlPointerXum);
        QWidget::setTabOrder(VerticalSliderViewControlPointerXum, VerticalSliderViewControlPointerYum);
        QWidget::setTabOrder(VerticalSliderViewControlPointerYum, VerticalSliderViewControlPointerZum);
        QWidget::setTabOrder(VerticalSliderViewControlPointerZum, LineEditViewControlPointerXum);
        QWidget::setTabOrder(LineEditViewControlPointerXum, LineEditViewControlPointerYum);
        QWidget::setTabOrder(LineEditViewControlPointerYum, LineEditViewControlPointerZum);
        QWidget::setTabOrder(LineEditViewControlPointerZum, VerticalSliderViewControlROIXFrom);
        QWidget::setTabOrder(VerticalSliderViewControlROIXFrom, VerticalSliderViewControlROIXTo);
        QWidget::setTabOrder(VerticalSliderViewControlROIXTo, VerticalSliderViewControlROIYFrom);
        QWidget::setTabOrder(VerticalSliderViewControlROIYFrom, VerticalSliderViewControlROIYTo);
        QWidget::setTabOrder(VerticalSliderViewControlROIYTo, VerticalSliderViewControlROIZFrom);
        QWidget::setTabOrder(VerticalSliderViewControlROIZFrom, VerticalSliderViewControlROIZTo);
        QWidget::setTabOrder(VerticalSliderViewControlROIZTo, SpinBoxViewControlROIXFrom);
        QWidget::setTabOrder(SpinBoxViewControlROIXFrom, SpinBoxViewControlROIXTo);
        QWidget::setTabOrder(SpinBoxViewControlROIXTo, SpinBoxViewControlROIYFrom);
        QWidget::setTabOrder(SpinBoxViewControlROIYFrom, SpinBoxViewControlROIYTo);
        QWidget::setTabOrder(SpinBoxViewControlROIYTo, SpinBoxViewControlROIZFrom);
        QWidget::setTabOrder(SpinBoxViewControlROIZFrom, SpinBoxViewControlROIZTo);
        QWidget::setTabOrder(SpinBoxViewControlROIZTo, VerticalSliderViewControlColorR);
        QWidget::setTabOrder(VerticalSliderViewControlColorR, VerticalSliderViewControlColorG);
        QWidget::setTabOrder(VerticalSliderViewControlColorG, VerticalSliderViewControlColorB);
        QWidget::setTabOrder(VerticalSliderViewControlColorB, LineEditViewControlColorR);
        QWidget::setTabOrder(LineEditViewControlColorR, LineEditViewControlColorG);
        QWidget::setTabOrder(LineEditViewControlColorG, LineEditViewControlColorB);
        QWidget::setTabOrder(LineEditViewControlColorB, VerticalSliderViewControlTranslationX);
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

        retranslateUi(StackImageControllerDialog);

        Tabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(StackImageControllerDialog);
    } // setupUi

    void retranslateUi(QWidget *StackImageControllerDialog)
    {
        StackImageControllerDialog->setWindowTitle(QApplication::translate("StackImageControllerDialog", "Stack Image Controller", 0, QApplication::UnicodeUTF8));
        LabelFileLoadFilePath->setText(QApplication::translate("StackImageControllerDialog", "File Path", 0, QApplication::UnicodeUTF8));
        PushButtonFileLoadBrowse->setText(QApplication::translate("StackImageControllerDialog", "Browse", 0, QApplication::UnicodeUTF8));
        LabelFileLoadDirectory->setText(QApplication::translate("StackImageControllerDialog", "Directory", 0, QApplication::UnicodeUTF8));
        LabelFileLoadBaseName->setText(QApplication::translate("StackImageControllerDialog", "BaseName", 0, QApplication::UnicodeUTF8));
        LabelFileLoadScale->setText(QApplication::translate("StackImageControllerDialog", "Scale", 0, QApplication::UnicodeUTF8));
        LabelFileLoadScaleCommaXY->setText(QApplication::translate("StackImageControllerDialog", ",", 0, QApplication::UnicodeUTF8));
        LabelFileLoadScaleYZ->setText(QApplication::translate("StackImageControllerDialog", ",", 0, QApplication::UnicodeUTF8));
        LabelFileLoadScaleUnit->setText(QApplication::translate("StackImageControllerDialog", "um / voxel", 0, QApplication::UnicodeUTF8));
        LabelFileLoadLoadTo->setText(QApplication::translate("StackImageControllerDialog", "Store to", 0, QApplication::UnicodeUTF8));
        LabelFileLoadStoreToStackImageDataNo->setText(QApplication::translate("StackImageControllerDialog", "StackImadeDataNo", 0, QApplication::UnicodeUTF8));
        PushButtonFileLoadClear->setText(QApplication::translate("StackImageControllerDialog", "Clear", 0, QApplication::UnicodeUTF8));
        PushButtonFileLoadLoad->setText(QApplication::translate("StackImageControllerDialog", "Load", 0, QApplication::UnicodeUTF8));
        Tabs->setTabText(Tabs->indexOf(TabFileLoad), QApplication::translate("StackImageControllerDialog", "File Load", 0, QApplication::UnicodeUTF8));
        LabelFileSaveFilePath->setText(QApplication::translate("StackImageControllerDialog", "File Path", 0, QApplication::UnicodeUTF8));
        PushButtonFileSaveBrowse->setText(QApplication::translate("StackImageControllerDialog", "Browse", 0, QApplication::UnicodeUTF8));
        LabelFileSaveDirectory->setText(QApplication::translate("StackImageControllerDialog", "Directory", 0, QApplication::UnicodeUTF8));
        LabelFileSaveBaseName->setText(QApplication::translate("StackImageControllerDialog", "BaseName", 0, QApplication::UnicodeUTF8));
        LabelFileSaveDataNo->setText(QApplication::translate("StackImageControllerDialog", "Stack Image Data No", 0, QApplication::UnicodeUTF8));
        PushButtonFileSaveClear->setText(QApplication::translate("StackImageControllerDialog", "Clear", 0, QApplication::UnicodeUTF8));
        PushButtonFileSaveSave->setText(QApplication::translate("StackImageControllerDialog", "Save", 0, QApplication::UnicodeUTF8));
        Tabs->setTabText(Tabs->indexOf(TabFileSave), QApplication::translate("StackImageControllerDialog", "File Save", 0, QApplication::UnicodeUTF8));
        PushButtonExtractionHandTracing->setText(QApplication::translate("StackImageControllerDialog", "Manual", 0, QApplication::UnicodeUTF8));
        PushButtonExtractionCancel->setText(QApplication::translate("StackImageControllerDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        PushButtonExtractionExtract->setText(QApplication::translate("StackImageControllerDialog", "Extract", 0, QApplication::UnicodeUTF8));
        LabelExtractionBinaryThreshold->setText(QApplication::translate("StackImageControllerDialog", "Binary Threshold", 0, QApplication::UnicodeUTF8));
        PushButtonExtractionBinaryThresholdGetFromView->setText(QApplication::translate("StackImageControllerDialog", "Ref. View", 0, QApplication::UnicodeUTF8));
        LabelExtractionMedianFilter->setText(QApplication::translate("StackImageControllerDialog", "Median Filter", 0, QApplication::UnicodeUTF8));
        CheckBoxExtractionMedianFilter->setText(QApplication::translate("StackImageControllerDialog", "ON", 0, QApplication::UnicodeUTF8));
        LineEditExtractionBinaryThreshold->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LabelExtractionStartPoint->setText(QApplication::translate("StackImageControllerDialog", "Start Point", 0, QApplication::UnicodeUTF8));
        LineEditExtractionStartPointX->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LabelExtractionStartPointCommaXY->setText(QApplication::translate("StackImageControllerDialog", ",", 0, QApplication::UnicodeUTF8));
        LineEditExtractionStartPointY->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LabelExtractionStartPointCommaYZ->setText(QApplication::translate("StackImageControllerDialog", ",", 0, QApplication::UnicodeUTF8));
        LineEditExtractionStartPointZ->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        PushButtonExtractionStartPointGetFromView->setText(QApplication::translate("StackImageControllerDialog", "Ref. View", 0, QApplication::UnicodeUTF8));
        LabelExtractionDataNo->setText(QApplication::translate("StackImageControllerDialog", "Stack Image Data No", 0, QApplication::UnicodeUTF8));
        PushButtonExtractionCurrentDataNo->setText(QApplication::translate("StackImageControllerDialog", "CurrentData", 0, QApplication::UnicodeUTF8));
        LabelExtractionCalcProp->setText(QApplication::translate("StackImageControllerDialog", "Prop. output file", 0, QApplication::UnicodeUTF8));
        CheckBoxExtractionCalcProp->setText(QApplication::translate("StackImageControllerDialog", "ON", 0, QApplication::UnicodeUTF8));
        LabelExtractionCalcPropStart->setText(QApplication::translate("StackImageControllerDialog", "Start", 0, QApplication::UnicodeUTF8));
        LabelExtractionCalcPropStop->setText(QApplication::translate("StackImageControllerDialog", "Stop", 0, QApplication::UnicodeUTF8));
        LabelExtractionTargetNo->setText(QApplication::translate("StackImageControllerDialog", "Extracted Data No (for Saving)", 0, QApplication::UnicodeUTF8));
        LabelExtractionROI->setText(QApplication::translate("StackImageControllerDialog", "ROI", 0, QApplication::UnicodeUTF8));
        CheckBoxExtractionROI->setText(QApplication::translate("StackImageControllerDialog", "ON", 0, QApplication::UnicodeUTF8));
        LabelExtractionDoRescanning->setText(QApplication::translate("StackImageControllerDialog", "Do Rescanning", 0, QApplication::UnicodeUTF8));
        CheckBoxExtractionDoRescanning->setText(QApplication::translate("StackImageControllerDialog", "Yes", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("StackImageControllerDialog", "Store To", 0, QApplication::UnicodeUTF8));
        Tabs->setTabText(Tabs->indexOf(TabExtraction), QApplication::translate("StackImageControllerDialog", "Extraction", 0, QApplication::UnicodeUTF8));
        GroupBoxImageProcessingGenerateStackImage->setTitle(QApplication::translate("StackImageControllerDialog", "Generate Stack Image", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingGenerateStackImageParam1->setText(QApplication::translate("StackImageControllerDialog", "Param1", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingGenerateStackImageParam2->setText(QApplication::translate("StackImageControllerDialog", "Param2", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingGenerateStackImageParam3->setText(QApplication::translate("StackImageControllerDialog", "Param3", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingGenerateStackImageParam4->setText(QApplication::translate("StackImageControllerDialog", "Param4", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingGenerateStackImageDataNo->setText(QApplication::translate("StackImageControllerDialog", "Stack Image Data No", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingGenerateStackImageType->setText(QApplication::translate("StackImageControllerDialog", "Type", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingGeneratStackImageParam5->setText(QApplication::translate("StackImageControllerDialog", "Param5", 0, QApplication::UnicodeUTF8));
        PushButtonImageProcessingGenerateStackImage->setText(QApplication::translate("StackImageControllerDialog", "Generate", 0, QApplication::UnicodeUTF8));
        GroupBoxImageProcessingNoise->setTitle(QApplication::translate("StackImageControllerDialog", "Noise", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingNoiseSD->setText(QApplication::translate("StackImageControllerDialog", "SD", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingNoiseDataNo->setText(QApplication::translate("StackImageControllerDialog", "Stack Image Data No", 0, QApplication::UnicodeUTF8));
        PushButtonImageProcessingNoiseAddNoise->setText(QApplication::translate("StackImageControllerDialog", "Add Noise", 0, QApplication::UnicodeUTF8));
        GroupBoxImageProcessingBackground->setTitle(QApplication::translate("StackImageControllerDialog", "Background", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingBackgroundDataNo->setText(QApplication::translate("StackImageControllerDialog", "Stack Image Data No", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingBackgroundType->setText(QApplication::translate("StackImageControllerDialog", "Type", 0, QApplication::UnicodeUTF8));
        LineEditImageProcessingBackgroundOriginX->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingBackgroundOriginCommaXY->setText(QApplication::translate("StackImageControllerDialog", ",", 0, QApplication::UnicodeUTF8));
        LineEditImageProcessingBackgroundOriginY->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingBackgroundOriginYZ->setText(QApplication::translate("StackImageControllerDialog", ",", 0, QApplication::UnicodeUTF8));
        LineEditImageProcessingBackgroundOriginZ->setInputMask(QString());
        LineEditImageProcessingBackgroundOriginZ->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LineEditImageProcessingBackgroundNormalVectorX->setInputMask(QString());
        LineEditImageProcessingBackgroundNormalVectorX->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingBackgroundNormalVectorCommaXY->setText(QApplication::translate("StackImageControllerDialog", ",", 0, QApplication::UnicodeUTF8));
        LineEditImageProcessingBackgroundNormalVectorY->setInputMask(QString());
        LineEditImageProcessingBackgroundNormalVectorY->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingBackgroundNormalVectorYZ->setText(QApplication::translate("StackImageControllerDialog", ",", 0, QApplication::UnicodeUTF8));
        LineEditImageProcessingBackgroundNormalVectorZ->setInputMask(QString());
        LineEditImageProcessingBackgroundNormalVectorZ->setText(QApplication::translate("StackImageControllerDialog", "1", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingBackgronudOrigin->setText(QApplication::translate("StackImageControllerDialog", "Origin", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingBackgronudNormalVector->setText(QApplication::translate("StackImageControllerDialog", "Normal Vec.", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingBackgronudParameter->setText(QApplication::translate("StackImageControllerDialog", "Parameter", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingBackgroundMax->setText(QApplication::translate("StackImageControllerDialog", "Max", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingBackgroundMin->setText(QApplication::translate("StackImageControllerDialog", "Min", 0, QApplication::UnicodeUTF8));
        PushButtonImageProcessingBackgroundGenerate->setText(QApplication::translate("StackImageControllerDialog", "Gen. Background", 0, QApplication::UnicodeUTF8));
        GroupBoxImageProcessingFindLowContrastRegion->setTitle(QApplication::translate("StackImageControllerDialog", "Find Low Contrast Region", 0, QApplication::UnicodeUTF8));
        LabelImageProcessingDataNo->setText(QApplication::translate("StackImageControllerDialog", "Stack Image Data No", 0, QApplication::UnicodeUTF8));
        PushButtonImageProcessingFindLCR->setText(QApplication::translate("StackImageControllerDialog", "Find", 0, QApplication::UnicodeUTF8));
        PushButtonDanger->setText(QApplication::translate("StackImageControllerDialog", "!!DANGER(BKG)!!", 0, QApplication::UnicodeUTF8));
        PushButtonPoison->setText(QApplication::translate("StackImageControllerDialog", "!!POISON(NZ)!!", 0, QApplication::UnicodeUTF8));
        PushButtonEmergency->setText(QApplication::translate("StackImageControllerDialog", "!!Emergency(OBJ)!!", 0, QApplication::UnicodeUTF8));
        Tabs->setTabText(Tabs->indexOf(TabImageProcessing), QApplication::translate("StackImageControllerDialog", "Image Processing", 0, QApplication::UnicodeUTF8));
        LabelViewControlDataNo->setText(QApplication::translate("StackImageControllerDialog", "StackImageDataNo", 0, QApplication::UnicodeUTF8));
        CheckBoxViewControlShow->setText(QApplication::translate("StackImageControllerDialog", "Show", 0, QApplication::UnicodeUTF8));
        CheckBoxViewControlAlphaMode->setText(QApplication::translate("StackImageControllerDialog", "Alpha Mode", 0, QApplication::UnicodeUTF8));
        CheckBoxViewControlLCR->setText(QApplication::translate("StackImageControllerDialog", "Contrast Prop.", 0, QApplication::UnicodeUTF8));
        PushButtonViewControlOrthoView->setText(QApplication::translate("StackImageControllerDialog", "Orthoview", 0, QApplication::UnicodeUTF8));
        PushButtonViewControlResetOrthoViewSize->setText(QApplication::translate("StackImageControllerDialog", "Reset Orthview Size", 0, QApplication::UnicodeUTF8));
        GroupBoxViewControlThreshold->setTitle(QApplication::translate("StackImageControllerDialog", "Threshold", 0, QApplication::UnicodeUTF8));
        LineEditViewControlThreshold->setText(QApplication::translate("StackImageControllerDialog", "100", 0, QApplication::UnicodeUTF8));
        GroupBoxViewControlPointer->setTitle(QApplication::translate("StackImageControllerDialog", "Pointer", 0, QApplication::UnicodeUTF8));
        LabelViewControlPointerX->setText(QApplication::translate("StackImageControllerDialog", "X", 0, QApplication::UnicodeUTF8));
        LabelViewControlPointerY->setText(QApplication::translate("StackImageControllerDialog", "Y", 0, QApplication::UnicodeUTF8));
        LabelViewControlPointerZ->setText(QApplication::translate("StackImageControllerDialog", "Z", 0, QApplication::UnicodeUTF8));
        LineEditViewControlPointerXum->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LineEditViewControlPointerYum->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LineEditViewControlPointerZum->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        CheckBoxViewControlPointer->setText(QString());
        GroupBoxViewControlROI->setTitle(QApplication::translate("StackImageControllerDialog", "Region of Interest", 0, QApplication::UnicodeUTF8));
        LabelViewControlROIX->setText(QApplication::translate("StackImageControllerDialog", "X", 0, QApplication::UnicodeUTF8));
        LabelViewControlROIXFrom->setText(QApplication::translate("StackImageControllerDialog", "From", 0, QApplication::UnicodeUTF8));
        LabelViewControlROIXTo->setText(QApplication::translate("StackImageControllerDialog", "To", 0, QApplication::UnicodeUTF8));
        LabelViewControlROIY->setText(QApplication::translate("StackImageControllerDialog", "Y", 0, QApplication::UnicodeUTF8));
        LabelViewControlROIYFrom->setText(QApplication::translate("StackImageControllerDialog", "From", 0, QApplication::UnicodeUTF8));
        LabelViewControlROIYTo->setText(QApplication::translate("StackImageControllerDialog", "To", 0, QApplication::UnicodeUTF8));
        LabelViewControlROIZ->setText(QApplication::translate("StackImageControllerDialog", "Z", 0, QApplication::UnicodeUTF8));
        LabelViewControlROIZFrom->setText(QApplication::translate("StackImageControllerDialog", "From", 0, QApplication::UnicodeUTF8));
        LabelViewControlROIZTo->setText(QApplication::translate("StackImageControllerDialog", "To", 0, QApplication::UnicodeUTF8));
        GroupBoxViewControlColor->setTitle(QApplication::translate("StackImageControllerDialog", "Color", 0, QApplication::UnicodeUTF8));
        LabelViewControlColorR->setText(QApplication::translate("StackImageControllerDialog", "R", 0, QApplication::UnicodeUTF8));
        LabelViewControlColorG->setText(QApplication::translate("StackImageControllerDialog", "G", 0, QApplication::UnicodeUTF8));
        LabelViewControlColorB->setText(QApplication::translate("StackImageControllerDialog", "B", 0, QApplication::UnicodeUTF8));
        LineEditViewControlColorR->setText(QApplication::translate("StackImageControllerDialog", "255", 0, QApplication::UnicodeUTF8));
        LineEditViewControlColorG->setText(QApplication::translate("StackImageControllerDialog", "255", 0, QApplication::UnicodeUTF8));
        LineEditViewControlColorB->setText(QApplication::translate("StackImageControllerDialog", "255", 0, QApplication::UnicodeUTF8));
        GroupBoxViewControlTranslation->setTitle(QApplication::translate("StackImageControllerDialog", "Translation", 0, QApplication::UnicodeUTF8));
        LabelViewControlTranslationX->setText(QApplication::translate("StackImageControllerDialog", "X", 0, QApplication::UnicodeUTF8));
        LabelViewControlTranslationY->setText(QApplication::translate("StackImageControllerDialog", "Y", 0, QApplication::UnicodeUTF8));
        LabelViewControlTranslationZ->setText(QApplication::translate("StackImageControllerDialog", "Z", 0, QApplication::UnicodeUTF8));
        LineEditViewControlTranslationY->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LineEditViewControlTranslationZ->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LineEditViewControlTranslationXum->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LineEditViewControlTranslationYum->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LineEditViewControlTranslationZum->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        LineEditViewControlTranslationX->setText(QApplication::translate("StackImageControllerDialog", "0", 0, QApplication::UnicodeUTF8));
        Tabs->setTabText(Tabs->indexOf(TabViewControl), QApplication::translate("StackImageControllerDialog", "View Control", 0, QApplication::UnicodeUTF8));
        LabelPropertiesImageNum->setText(QApplication::translate("StackImageControllerDialog", "Image #", 0, QApplication::UnicodeUTF8));
        LabelPropertiesImageSize->setText(QApplication::translate("StackImageControllerDialog", "Image Size", 0, QApplication::UnicodeUTF8));
        LabelPropertiesDirectory->setText(QApplication::translate("StackImageControllerDialog", "Directory", 0, QApplication::UnicodeUTF8));
        LabelPropertiesImageName->setText(QApplication::translate("StackImageControllerDialog", "Image Name", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("StackImageControllerDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("StackImageControllerDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("StackImageControllerDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("StackImageControllerDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("StackImageControllerDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("StackImageControllerDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("StackImageControllerDialog", "TextLabel", 0, QApplication::UnicodeUTF8));
        Tabs->setTabText(Tabs->indexOf(TabProperties), QApplication::translate("StackImageControllerDialog", "Properties", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class StackImageControllerDialog: public Ui_StackImageControllerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // CSTACKIMAGECONTROLLERDIALOG_H
