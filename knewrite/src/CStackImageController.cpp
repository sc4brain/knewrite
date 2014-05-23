
#include <QtGui>

#include "CStackImageController.h"
#include "CObjectCommunicatorID.h"

#include "BCommon.h"

#define ANGLE_DIV_NUM 16

#define VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM 10

CStackImageController::CStackImageController(QWidget *parent) : QDialog(parent)
{

	setupUi(this);

    int CurStackImageNo = 0;
    for (int i = 0; i < MAX_STACK_IMAGE_NUM; i++) {
        StackImageData[i].ptr = NULL;
        StackImageData[i].threshold = DEFAULT_STACKIMAGE_THRESHOLD;
        StackImageData[i].size.x = 0;
        StackImageData[i].size.y = 0;
        StackImageData[i].size.z = 0;
        StackImageData[i].scale.x = 0.;
        StackImageData[i].scale.y = 0.;
        StackImageData[i].scale.z = 0.;
        StackImageData[i].ROI.x.from = 0.;
        StackImageData[i].ROI.y.from = 0.;
        StackImageData[i].ROI.z.from = 0.;
        StackImageData[i].ROI.x.to = 0.;
        StackImageData[i].ROI.y.to = 0.;
        StackImageData[i].ROI.z.to = 0.;
        StackImageData[i].isLCRon = false;
        StackImageData[i].on = false;
        StackImageData[i].alphaMode = false;
        StackImageData[i].color.r = 255;
        StackImageData[i].color.g = 255;
        StackImageData[i].color.b = 255;
    }

    SendViewControlCurrentStateLock = false;

    //--------------------------------------------------------------------------
    // FileLoad
    //--------------------------------------------------------------------------

    // browse
    connect(PushButtonFileLoadBrowse, SIGNAL(clicked()),
			this, SLOT(onFileLoadBrowseButtonClicked()));

    // load
	connect(PushButtonFileLoadLoad, SIGNAL(clicked()),
			this, SLOT(onFileLoadLoadButtonClicked()));

    // clear
	connect(PushButtonFileLoadClear, SIGNAL(clicked()),
			this, SLOT(onFileLoadClearButtonClicked()));

    // parse file dir and name
    connect(LineEditFileLoadFilePath, SIGNAL(textChanged(const QString &)),
            this, SLOT(updateFileLoadFileDirAndName()));

    // check if the all properties have been set
	connect(LineEditFileLoadFilePath, SIGNAL(textChanged(const QString &)),
	 		this, SLOT(setFileLoadLoadButtonEnable()));
	connect(LineEditFileLoadScaleX, SIGNAL(textChanged(const QString &)),
	 		this, SLOT(setFileLoadLoadButtonEnable()));
	connect(LineEditFileLoadScaleY, SIGNAL(textChanged(const QString &)),
	 		this, SLOT(setFileLoadLoadButtonEnable()));
	connect(LineEditFileLoadScaleZ, SIGNAL(textChanged(const QString &)),
	 		this, SLOT(setFileLoadLoadButtonEnable()));


    //--------------------------------------------------------------------------
    // FileSave
    //-------------------------------------------------------------------------
    
    // browse
    connect(PushButtonFileSaveBrowse, SIGNAL(clicked()),
			this, SLOT(onFileSaveBrowseButtonClicked()));

    // load
	connect(PushButtonFileSaveSave, SIGNAL(clicked()),
			this, SLOT(onFileSaveSaveButtonClicked()));

    // clear
	connect(PushButtonFileSaveClear, SIGNAL(clicked()),
			this, SLOT(onFileSaveClearButtonClicked()));

    // parse file dir and name
    connect(LineEditFileSaveFilePath, SIGNAL(textChanged(const QString &)),
            this, SLOT(updateFileSaveFileDirAndName()));
    connect(LineEditFileSaveDirectory, SIGNAL(textEdited(const QString &)),
            this, SLOT(updateFileSaveFilePath()));
    connect(LineEditFileSaveBaseName, SIGNAL(textEdited(const QString &)),
            this, SLOT(updateFileSaveFilePath()));

    // check if the all properties have been set
	connect(LineEditFileSaveFilePath, SIGNAL(textChanged(const QString &)),
	 		this, SLOT(setFileSaveSaveButtonEnable()));
	// connect(LineEditFileSaveScaleX, SIGNAL(textChanged(const QString &)),
	//  		this, SLOT(setFileSaveSaveButtonEnable()));
	// connect(LineEditFileSaveScaleY, SIGNAL(textChanged(const QString &)),
	//  		this, SLOT(setFileSaveSaveButtonEnable()));
	// connect(LineEditFileSaveScaleZ, SIGNAL(textChanged(const QString &)),
	//  		this, SLOT(setFileSaveSaveButtonEnable()));


    //--------------------------------------------------------------------------
    // Extraction
    //-------------------------------------------------------------------------

    // Current Data No button
    connect(PushButtonExtractionCurrentDataNo, SIGNAL(clicked()),
            this, SLOT(onExtractionCurrentDataNoButtonClicked()));

    // update threshold

    // LineEdit
    connect(HorizontalSliderExtractionBinaryThreshold,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateExtractionBinaryThresholdLineEdit()));
    // SlideBar
    connect(LineEditExtractionBinaryThreshold,
            SIGNAL(textChanged(const QString &)),
            this, SLOT(updateExtractionBinaryThresholdSlideBar()));

    // Threshold setting button
    connect(PushButtonExtractionBinaryThresholdGetFromView,
            SIGNAL(clicked()),
            this, SLOT(onExtractionThresholdGetFromViewClicked()));

    // Start Point setting button
    connect(PushButtonExtractionStartPointGetFromView,
            SIGNAL(clicked()),
            this, SLOT(onExtractionStartPointGetFromViewClicked()));

    // Extract button
    connect(PushButtonExtractionExtract, SIGNAL(clicked()),
            this, SLOT(onExtractionExtractButtonClicked()));

    connect(PushButtonExtractionHandTracing, SIGNAL(clicked()),
            this, SLOT(onExtractionHandTracingClicked()));

    // extractionfinished 
    connect(this, SIGNAL(extractionFinished()),
            this, SLOT(onExtractionFinished()));

    //--------------------------------------------------------------------------
    // Image Processing
    //--------------------------------------------------------------------------
    connect(PushButtonImageProcessingFindLCR, SIGNAL(clicked()),
            this, SLOT(onImageProcessingFindLCRButtonClicked()));
    connect(PushButtonImageProcessingGenerateStackImage, SIGNAL(clicked()),
            this, SLOT(onImageProcessingGenerateStackImageButtonClicked()));
    connect(PushButtonImageProcessingNoiseAddNoise, SIGNAL(clicked()),
            this, SLOT(onImageProcessingAddNoiseButtonClicked()));
    connect(PushButtonImageProcessingBackgroundGenerate, SIGNAL(clicked()),
            this, SLOT(onImageProcessingBackgroundGenerateButtonClicked()));
    connect(PushButtonDanger, SIGNAL(clicked()),
            this, SLOT(onDangerButtonClicked()));
    connect(PushButtonPoison, SIGNAL(clicked()),
            this, SLOT(onPoisonButtonClicked()));
    connect(PushButtonEmergency, SIGNAL(clicked()),
            this, SLOT(onEmergencyButtonClicked()));

    ComboBoxImageProcessingGenerateStackImageType->addItem(QString("Tree"), 0);
    ComboBoxImageProcessingGenerateStackImageType->addItem(QString("Extraneous Object"), 1);

    ComboBoxImageProcessingBackgroundType->addItem(QString("Sin"), 0);
    ComboBoxImageProcessingBackgroundType->addItem(QString("Sphere"), 1);

    //--------------------------------------------------------------------------
    // View Control
    //--------------------------------------------------------------------------

    // data No
    connect(SpinBoxViewControlDataNo, SIGNAL(valueChanged(int)),
            this, SLOT(onViewControlDataNoSpinBoxChanged()));

    // "show" check box
    connect(CheckBoxViewControlShow, SIGNAL(stateChanged(int)),
            this, SLOT(onViewControlShowCheckBoxClicked()));

    // alpha mode check box
    connect(CheckBoxViewControlAlphaMode, SIGNAL(stateChanged(int)),
            this, SLOT(onViewControlAlphaModeCheckBoxClicked()));

    // LCR on/off check box
    connect(CheckBoxViewControlLCR, SIGNAL(stateChanged(int)),
            this, SLOT(onViewControlLCRCheckBoxClicked()));

    // ortho view
    connect(PushButtonViewControlOrthoView, SIGNAL(clicked()),
            this, SLOT(onViewControlOrthoViewButtonClicked()));
    connect(PushButtonViewControlResetOrthoViewSize, SIGNAL(clicked()),
            this, SLOT(onViewControlResetOrthoViewSizeButtonClicked()));

    // threshold
    connect(VerticalSliderViewControlThreshold,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlThresholdLineEdit()));
    connect(LineEditViewControlThreshold, SIGNAL(textChanged(const QString &)),
            this, SLOT(updateViewControlThresholdSlideBar()));

    // // reset bounding box button
    // connect(PushButtonViewControlResetBoundingBox, SIGNAL(clicked()),
    //         this, SLOT(onViewControlResetBoundingBoxButtonClicked()));

    // color r
    connect(VerticalSliderViewControlColorR,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlColorRLineEdit()));
    connect(LineEditViewControlColorR,
            SIGNAL(textChanged(const QString &)),
            this, SLOT(updateViewControlColorRSlideBar()));

    // color g
    connect(VerticalSliderViewControlColorG,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlColorGLineEdit()));
    connect(LineEditViewControlColorG,
            SIGNAL(textChanged(const QString &)),
            this, SLOT(updateViewControlColorGSlideBar()));

    // color b
    connect(VerticalSliderViewControlColorB,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlColorBLineEdit()));
    connect(LineEditViewControlColorB,
            SIGNAL(textChanged(const QString &)),
            this, SLOT(updateViewControlColorBSlideBar()));

    // send view color
    connect(VerticalSliderViewControlColorB,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));
    connect(VerticalSliderViewControlColorG,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));
    connect(VerticalSliderViewControlColorB,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));

    // hide translation
    GroupBoxViewControlTranslation->hide();
    
    // translation x
    connect(VerticalSliderViewControlTranslationX,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlTranslationXLineEdit()));
    connect(LineEditViewControlTranslationX,
            SIGNAL(textChanged(const QString &)),
            this, SLOT(updateViewControlTranslationXSlideBar()));

    // translation y
    connect(VerticalSliderViewControlTranslationY,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlTranslationYLineEdit()));
    connect(LineEditViewControlTranslationY,
            SIGNAL(textChanged(const QString &)),
            this, SLOT(updateViewControlTranslationYSlideBar()));

    // translation z
    connect(VerticalSliderViewControlTranslationZ,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlTranslationZLineEdit()));
    connect(LineEditViewControlTranslationZ,
            SIGNAL(textChanged(const QString &)),
            this, SLOT(updateViewControlTranslationZSlideBar()));

    // send the value to the shape view when the slide bar manipulated
    connect(VerticalSliderViewControlThreshold,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));
    connect(VerticalSliderViewControlTranslationX,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));
    connect(VerticalSliderViewControlTranslationY,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));
    connect(VerticalSliderViewControlTranslationZ,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));

    // pointer x
    connect(VerticalSliderViewControlPointerXum,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlPointerXLineEdit()));
    connect(LineEditViewControlPointerXum, SIGNAL(textChanged(const QString &)),
            this, SLOT(updateViewControlPointerXSlideBar()));
    
    // pointer y
    connect(VerticalSliderViewControlPointerYum,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlPointerYLineEdit()));
    connect(LineEditViewControlPointerYum, SIGNAL(textChanged(const QString &)),
            this, SLOT(updateViewControlPointerYSlideBar()));

    // pointer z
    connect(VerticalSliderViewControlPointerZum,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlPointerZLineEdit()));
    connect(LineEditViewControlPointerZum, SIGNAL(textChanged(const QString &)),
            this, SLOT(updateViewControlPointerZSlideBar()));


    // send the pointing data when the slide [x or y or z or ON/OFF] manupilated
    connect(VerticalSliderViewControlPointerXum,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlPointer()));
    connect(VerticalSliderViewControlPointerYum,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlPointer()));
    connect(VerticalSliderViewControlPointerZum,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlPointer()));
    connect(CheckBoxViewControlPointer,
            SIGNAL(stateChanged(int)),
            this, SLOT(sendViewControlPointer()));


    // ROI x from
    connect(VerticalSliderViewControlROIXFrom,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlROIXSpinBoxFrom()));
    connect(SpinBoxViewControlROIXFrom,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlROIXSlideBarFrom()));

    // ROI y from
    connect(VerticalSliderViewControlROIYFrom,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlROIYSpinBoxFrom()));
    connect(SpinBoxViewControlROIYFrom,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlROIYSlideBarFrom()));

    // ROI z from
    connect(VerticalSliderViewControlROIZFrom,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlROIZSpinBoxFrom()));
    connect(SpinBoxViewControlROIZFrom,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlROIZSlideBarFrom()));

    // ROI x to
    connect(VerticalSliderViewControlROIXTo,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlROIXSpinBoxTo()));
    connect(SpinBoxViewControlROIXTo,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlROIXSlideBarTo()));

    // ROI y to
    connect(VerticalSliderViewControlROIYTo,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlROIYSpinBoxTo()));
    connect(SpinBoxViewControlROIYTo,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlROIYSlideBarTo()));

    // ROI z to
    connect(VerticalSliderViewControlROIZTo,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlROIZSpinBoxTo()));
    connect(SpinBoxViewControlROIZTo,
            SIGNAL(valueChanged(int)),
            this, SLOT(updateViewControlROIZSlideBarTo()));

    // send ROI
    connect(VerticalSliderViewControlROIXFrom,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));
    connect(VerticalSliderViewControlROIYFrom,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));
    connect(VerticalSliderViewControlROIZFrom,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));
    connect(VerticalSliderViewControlROIXTo,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));
    connect(VerticalSliderViewControlROIYTo,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));
    connect(VerticalSliderViewControlROIZTo,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));

#ifdef ___SETTING_FOR_DEBUG___
    // LineEditFileLoadFilePath->setText("/home/naska/NData/ExtractionSampleData/raw/raw000/bmp/raw000_");
    // LineEditFileLoadScaleX->setText("1");
    // LineEditFileLoadScaleY->setText("1");
    // LineEditFileLoadScaleZ->setText("1");
    // LineEditFileLoadFilePath->setText("/home/naska/NData/LSMs/" \
    //                                   "1056/data/Morphology/bmp/" \
    //                                   "merged/AND_0_5/saveData_000.bmp");
    LineEditFileLoadScaleX->setText("0.62");
    LineEditFileLoadScaleY->setText("0.62");
    LineEditFileLoadScaleZ->setText("1.44");


    // LineEditFileSaveFilePath->setText("/home/naska/NData/ExtractionSampleData/" \
    //                                   "raw/raw_");

#if 0
    LineEditExtractionBinaryThreshold->setText("100");
    HorizontalSliderExtractionBinaryThreshold->setValue(100);
    LineEditExtractionStartPointX->setText("170");
    LineEditExtractionStartPointY->setText("256");
    LineEditExtractionStartPointZ->setText("34");
#else
    LineEditExtractionBinaryThreshold->setText("6");
    HorizontalSliderExtractionBinaryThreshold->setValue(5);
    LineEditExtractionStartPointX->setText("390.8");
    LineEditExtractionStartPointY->setText("158.3");
    LtineEditExtractionStartPointZ->setText("79.1");
#endif

    DoubleSpinBoxImageProcessingGenerateStackImageParam1->setValue(5);
    DoubleSpinBoxImageProcessingGenerateStackImageParam2->setValue(100);
    DoubleSpinBoxImageProcessingGenerateStackImageParam3->setValue(7);
    DoubleSpinBoxImageProcessingGenerateStackImageParam4->setValue(0.7);
    DoubleSpinBoxImageProcessingGenerateStackImageParam5->setValue(0.2);
#endif
} // CStackImageController::CStackImageController()

void CStackImageController::reflectCurrentState()
{
    this->SendViewControlCurrentStateLock = true;

    bool on = StackImageData[CurStackImageNo].on;
    CheckBoxViewControlShow->setChecked(on);
    bool alphaMode = StackImageData[CurStackImageNo].alphaMode;
    CheckBoxViewControlAlphaMode->setChecked(alphaMode);
    bool isLCRon = StackImageData[CurStackImageNo].isLCRon;
    CheckBoxViewControlLCR->setChecked(isLCRon);
    SpinBoxViewControlDataNo->setValue(CurStackImageNo);
    int threshold = StackImageData[CurStackImageNo].threshold;
    VerticalSliderViewControlThreshold->setValue(threshold);
    int translatex = StackImageData[CurStackImageNo].translate.x;
    int translatey = StackImageData[CurStackImageNo].translate.y;
    int translatez = StackImageData[CurStackImageNo].translate.z;
    VerticalSliderViewControlTranslationX->setValue(translatex);
    VerticalSliderViewControlTranslationY->setValue(translatey);
    VerticalSliderViewControlTranslationZ->setValue(translatez);
    double scalex = StackImageData[CurStackImageNo].scale.x;
    double scaley = StackImageData[CurStackImageNo].scale.y;
    double scalez = StackImageData[CurStackImageNo].scale.z;
    // LineEditFileSaveScaleX->setText(QString::number(scalex));
    // LineEditFileSaveScaleY->setText(QString::number(scaley));
    // LineEditFileSaveScaleZ->setText(QString::number(scalez));

    int sizex = StackImageData[CurStackImageNo].size.x;
    int sizey = StackImageData[CurStackImageNo].size.y;
    int sizez = StackImageData[CurStackImageNo].size.z;
    VerticalSliderViewControlROIXFrom->setMinimum(0);
    VerticalSliderViewControlROIXTo->setMinimum(0);
    VerticalSliderViewControlROIYFrom->setMinimum(0);
    VerticalSliderViewControlROIYTo->setMinimum(0);
    VerticalSliderViewControlROIZFrom->setMinimum(0);
    VerticalSliderViewControlROIZTo->setMinimum(0);
    VerticalSliderViewControlROIXFrom->setMaximum(sizex - 1);
    VerticalSliderViewControlROIXTo->setMaximum(sizex - 1);
    VerticalSliderViewControlROIYFrom->setMaximum(sizey - 1);
    VerticalSliderViewControlROIYTo->setMaximum(sizey - 1);
    VerticalSliderViewControlROIZFrom->setMaximum(sizez - 1);
    VerticalSliderViewControlROIZTo->setMaximum(sizez - 1);
    int ROIXFrom = StackImageData[CurStackImageNo].ROI.x.from;
    int ROIYFrom = StackImageData[CurStackImageNo].ROI.y.from;
    int ROIZFrom = StackImageData[CurStackImageNo].ROI.z.from;
    int ROIXTo = StackImageData[CurStackImageNo].ROI.x.to;
    int ROIYTo = StackImageData[CurStackImageNo].ROI.y.to;
    int ROIZTo = StackImageData[CurStackImageNo].ROI.z.to;
    SpinBoxViewControlROIXFrom->setMinimum(0);
    SpinBoxViewControlROIXTo->setMinimum(0);
    SpinBoxViewControlROIYFrom->setMinimum(0);
    SpinBoxViewControlROIYTo->setMinimum(0);
    SpinBoxViewControlROIZFrom->setMinimum(0);
    SpinBoxViewControlROIZTo->setMinimum(0);
    SpinBoxViewControlROIXFrom->setMaximum(sizex - 1);
    SpinBoxViewControlROIXTo->setMaximum(sizex - 1);
    SpinBoxViewControlROIYFrom->setMaximum(sizey - 1);
    SpinBoxViewControlROIYTo->setMaximum(sizey - 1);
    SpinBoxViewControlROIZFrom->setMaximum(sizez - 1);
    SpinBoxViewControlROIZTo->setMaximum(sizez - 1);
    dprintf("CStackImageController::reflectCurrentState " \
            "ROI (%d-%d, %d-%d, %d-%d)\n",
            ROIXFrom, ROIXTo,
            ROIYFrom, ROIYTo,
            ROIZFrom, ROIZTo);
    VerticalSliderViewControlROIXFrom->setValue(ROIXFrom);
    VerticalSliderViewControlROIYFrom->setValue(ROIYFrom);
    VerticalSliderViewControlROIZFrom->setValue(ROIZFrom);
    VerticalSliderViewControlROIXTo->setValue(ROIXTo);
    VerticalSliderViewControlROIYTo->setValue(ROIYTo);
    VerticalSliderViewControlROIZTo->setValue(ROIZTo);
    int r = StackImageData[CurStackImageNo].color.r;
    int g = StackImageData[CurStackImageNo].color.g;
    int b = StackImageData[CurStackImageNo].color.b;

    this->SendViewControlCurrentStateLock = false;
}

//------------------------------------------------------------------------------
// File Load
//------------------------------------------------------------------------------
void CStackImageController::onFileLoadBrowseButtonClicked()
{    
    // get file path
	QString initialName = LineEditFileLoadFilePath->text();
	if (initialName.isEmpty()) {
		initialName = QDir::homePath();
	}

    // get file path from file open dialog
	QString fileName =
		QFileDialog::getOpenFileName(this, tr("Choose File"),
									 initialName);
	fileName = QDir::convertSeparators(fileName);
	if (!fileName.isEmpty()) {
		LineEditFileLoadFilePath->setText(fileName);
		//PushButtonFileLoadLoad->setEnabled(true);
	}
}

void CStackImageController::onFileLoadLoadButtonClicked() 
{
    // baseName = directory + base file name
    QString baseName = LineEditFileLoadDirectory->text()
        + QDir::separator() + LineEditFileLoadBaseName->text();

    // make data & send message for MStackImage object(s)
    DATAFORMAT_LOAD_STACKIMAGE sendData;
	strncpy(sendData.baseName, baseName.toStdString().c_str(),
            sizeof(sendData.baseName));
    sendData.dataNo = SpinBoxFileLoadDataNo->value();
    sendData.scale.x = LineEditFileLoadScaleX->text().toDouble();
    sendData.scale.y = LineEditFileLoadScaleY->text().toDouble();
    sendData.scale.z = LineEditFileLoadScaleZ->text().toDouble();

    dprintf("CStackImageController::onFileLoadLoadButtonClicked " \
            "sendData.baseName : %s, danaNo = %d\n",
            sendData.baseName, sendData.dataNo);
    dprintf("CStackImageController::onFileLoadLoadButtonClicked " \
            "&sendData = %p, sizeof(sendData) = %lu\n",
            &sendData, sizeof(sendData));

    // send
	putData(COMID_LOAD_STACKIMAGE, (char *)&sendData, sizeof(sendData));
}

void CStackImageController::onFileLoadClearButtonClicked() 
{
    // clear all text
    LineEditFileLoadFilePath->setText("");
    LineEditFileLoadScaleX->setText("");
    LineEditFileLoadScaleY->setText("");
    LineEditFileLoadScaleZ->setText("");
}

void CStackImageController::updateFileLoadFileDirAndName()
{

    // parse file name and directory path
    QString sourceText = LineEditFileLoadFilePath->text();
    QString fileName = QFileInfo(sourceText).fileName();
    QString fileDir = QFileInfo(sourceText).path();

    // get the base name of the file
    //
    //       fileName : "myimage_000.bmp"
    //    => baseName : "myimage_"
    //
    QString baseName = fileName;
	QRegExp rx("[0-9]+.bmp");
	baseName.replace(rx, "");

    // set text to FileDir and FileName
    LineEditFileLoadDirectory->setText(fileDir);
    LineEditFileLoadBaseName->setText(baseName);
}

void CStackImageController::updateFileLoadOutputTextEdit() {
	// QByteArray newData = Process.readAllStandardOutput();
	// QString text = PlainTextEditMessage->toPlainText()
	// 	+ QString::fromLocal8Bit(newData);
	// PlainTextEditMessage->setPlainText(text);
}

void CStackImageController::setFileLoadLoadButtonEnable()
{
    // check if the all propaties have been set
	if (LineEditFileLoadFilePath->text().isEmpty()
        || LineEditFileLoadScaleX->text().isEmpty()
        || LineEditFileLoadScaleY->text().isEmpty()
        || LineEditFileLoadScaleZ->text().isEmpty()) {
        // load unable yet
		PushButtonFileLoadLoad->setEnabled(false);
	} else {
        // load prepared
		PushButtonFileLoadLoad->setEnabled(true);
	}
}


//------------------------------------------------------------------------------
// File Save
//------------------------------------------------------------------------------

void CStackImageController::onFileSaveBrowseButtonClicked()
{
    // get file path
	QString initialName = LineEditFileSaveFilePath->text();
	if (initialName.isEmpty()) {
		initialName = QDir::homePath();
	}

    // get file path from file open dialog
	QString fileName =
		QFileDialog::getOpenFileName(this, tr("Choose File"),
									 initialName);
	fileName = QDir::convertSeparators(fileName);
	if (!fileName.isEmpty()) {
		LineEditFileSaveFilePath->setText(fileName);
	}
}

void CStackImageController::onFileSaveSaveButtonClicked() 
{
    // baseName = directory + base file name
	// QString baseName = LineEditFileSaveDirectory->text()
    //     + QDir::separator() + LineEditFileSaveBaseName->text();
    QString dirName = LineEditFileSaveDirectory->text() + QDir::separator();
    QString baseName = dirName + LineEditFileSaveBaseName->text();

    // make data & send message for MStackImage object(s)
    DATAFORMAT_SAVE_STACKIMAGE sendData;
	strncpy(sendData.baseName, baseName.toStdString().c_str(),
            sizeof(sendData.baseName));
	strncpy(sendData.dirName, dirName.toStdString().c_str(),
            sizeof(sendData.dirName));
    // sendData.scale.x = LineEditFileSaveScaleX->text().toDouble();
    // sendData.scale.y = LineEditFileSaveScaleY->text().toDouble();
    // sendData.scale.z = LineEditFileSaveScaleZ->text().toDouble();
    sendData.dataNo = SpinBoxFileSaveDataNo->value();
    
    dprintf("CStackImageController::onFileSaveSaveButtonClicked" \
            " sendData.baseName : %s\n",
            (sendData.baseName));
    dprintf("CStackImageController::onFileSaveSaveButtonClicked" \
            " sendData.dirName : %s\n",
            (sendData.dirName));
    dprintf("CStackImageController::onFileSaveSaveButtonClicked" \
            " &sendData = %p, sizeof(sendData) = %lu\n",
            &sendData, sizeof(sendData));

    // send
	putData(COMID_SAVE_STACKIMAGE, (char *)&sendData, sizeof(sendData));
}

void CStackImageController::onFileSaveClearButtonClicked() 
{
    // clear all text
    LineEditFileSaveFilePath->setText("");
    // LineEditFileSaveScaleX->setText("");
    // LineEditFileSaveScaleY->setText("");
    // LineEditFileSaveScaleZ->setText("");
}

void CStackImageController::updateFileSaveFileDirAndName()
{
    // parse file name and directory path
    QString sourceText = LineEditFileSaveFilePath->text();
    QString fileName = QFileInfo(sourceText).fileName();
    QString fileDir = QFileInfo(sourceText).path();

    sourceText.replace(QRegExp("/+"), "/");

    // get the base name of the file
    //
    //       fileName : "myimage_000.bmp"
    //    => baseName : "myimage_"
    //
    QString baseName = fileName;
	QRegExp rx("[0-9]+.bmp");
	baseName.replace(rx, "");

    // set text to FileDir and FileName
    LineEditFileSaveDirectory->setText(fileDir);
    LineEditFileSaveBaseName->setText(baseName);
}

void CStackImageController::updateFileSaveFilePath()
{
    QString fileDir = LineEditFileSaveDirectory->text();
    QString fileName = LineEditFileSaveBaseName->text();
    QString filePath = fileDir + "/" + fileName;
    QRegExp rx("/+");
    filePath.replace(rx, "/");
    fileDir.replace(rx, "/");
    fileName.replace(rx, "");

    LineEditFileSaveDirectory->setText(fileDir);
    LineEditFileSaveBaseName->setText(fileName);
    LineEditFileSaveFilePath->setText(filePath);
}

void CStackImageController::updateFileSaveOutputTextEdit() {
	// QByteArray newData = Process.readAllStandardOutput();
	// QString text = PlainTextEditMessage->toPlainText()
	// 	+ QString::fromLocal8Bit(newData);
	// PlainTextEditMessage->setPlainText(text);
}

void CStackImageController::setFileSaveSaveButtonEnable()
{
    // check if the all propaties have been set
	if (LineEditFileSaveFilePath->text().isEmpty()
        // || LineEditFileSaveScaleX->text().isEmpty()
        // || LineEditFileSaveScaleY->text().isEmpty()
        // || LineEditFileSaveScaleZ->text().isEmpty()
        ) {
        // save unable yet
		PushButtonFileSaveSave->setEnabled(false);
	} else {
        // save prepared
		PushButtonFileSaveSave->setEnabled(true);
	}
}

//------------------------------------------------------------------------------
// Extraction
//------------------------------------------------------------------------------
void CStackImageController::onExtractionCurrentDataNoButtonClicked()
{
    int value = SpinBoxViewControlDataNo->value();
    SpinBoxExtractionDataNo->setValue(value);
}

void CStackImageController::onExtractionThresholdGetFromViewClicked()
{
    int value = VerticalSliderViewControlThreshold->value();
    LineEditExtractionBinaryThreshold->setText(QString::number(value, 10));

    //needless
    //HorizontalSliderExtractionBinaryThreshold->setValue(value);
}

void CStackImageController::onExtractionStartPointGetFromViewClicked()
{
    LineEditExtractionStartPointX->setText(LineEditViewControlPointerXum->text());
    LineEditExtractionStartPointY->setText(LineEditViewControlPointerYum->text());
    LineEditExtractionStartPointZ->setText(LineEditViewControlPointerZum->text());
}

void CStackImageController::updateExtractionBinaryThresholdLineEdit()
{
    int value = HorizontalSliderExtractionBinaryThreshold->value();
    LineEditExtractionBinaryThreshold->setText(QString::number(value, 10));
}

void CStackImageController::updateExtractionBinaryThresholdSlideBar()
{
    QString text = LineEditExtractionBinaryThreshold->text();
    int value = text.toInt();
    HorizontalSliderExtractionBinaryThreshold->setValue(value);
}

void CStackImageController::onExtractionExtractButtonClicked()
{
    DATAFORMAT_DO_EXTRACTION sendData;
    int stackImageDataNo = SpinBoxExtractionDataNo->value();
    sendData.ptr = StackImageData[stackImageDataNo].ptr;
    sendData.dataNo = stackImageDataNo;
    int targetNo = SpinBoxExtractionTargetNo->value();
    sendData.targetNo = targetNo;
    sendData.size.x = StackImageData[stackImageDataNo].size.x;
    sendData.size.y = StackImageData[stackImageDataNo].size.y;
    sendData.size.z = StackImageData[stackImageDataNo].size.z;
    sendData.scale.x = StackImageData[stackImageDataNo].scale.x;
    sendData.scale.y = StackImageData[stackImageDataNo].scale.y;
    sendData.scale.z = StackImageData[stackImageDataNo].scale.z;
    double startx = LineEditExtractionStartPointX->text().toDouble();
    double starty = LineEditExtractionStartPointY->text().toDouble();
    double startz = LineEditExtractionStartPointZ->text().toDouble();
    int translatex = StackImageData[stackImageDataNo].translate.x;
    int translatey = StackImageData[stackImageDataNo].translate.y;
    int translatez = StackImageData[stackImageDataNo].translate.z;
    double scalex = StackImageData[stackImageDataNo].scale.x;
    double scaley = StackImageData[stackImageDataNo].scale.y;
    double scalez = StackImageData[stackImageDataNo].scale.z;
    startx = (int)(startx / scalex - translatex);
    starty = (int)(starty / scaley - translatey);
    startz = (int)(startz / scalez - translatez);
    sendData.startPoint.x = startx;
    sendData.startPoint.y = starty;
    sendData.startPoint.z = startz;
    bool activateROI = CheckBoxExtractionROI->isChecked();
    if (activateROI) {
        sendData.ROI.x.from = StackImageData[stackImageDataNo].ROI.x.from;
        sendData.ROI.y.from = StackImageData[stackImageDataNo].ROI.y.from;
        sendData.ROI.z.from = StackImageData[stackImageDataNo].ROI.z.from;
        sendData.ROI.x.to = StackImageData[stackImageDataNo].ROI.x.to;
        sendData.ROI.y.to = StackImageData[stackImageDataNo].ROI.y.to;
        sendData.ROI.z.to = StackImageData[stackImageDataNo].ROI.z.to;
    } else {
        sendData.ROI.x.from = 0;
        sendData.ROI.y.from = 0;
        sendData.ROI.z.from = 0;
        sendData.ROI.x.to = StackImageData[stackImageDataNo].size.x - 1;
        sendData.ROI.y.to = StackImageData[stackImageDataNo].size.y - 1;
        sendData.ROI.z.to = StackImageData[stackImageDataNo].size.z - 1;
    }
    unsigned char threshold
        = HorizontalSliderExtractionBinaryThreshold->value();
    sendData.threshold = threshold;
    sendData.calcProp = CheckBoxExtractionCalcProp->isChecked();
    strncpy(sendData.fname,
            LineEditExtractionCalcPropFileName->text().toStdString().c_str(),
            sizeof(sendData.fname)-1);
    unsigned char startThreshold
        = SpinBoxExtractionCalcPropStartThreshold->value();
    unsigned char stopThreshold
        = SpinBoxExtractionCalcPropStopThreshold->value();
    sendData.startThreshold = startThreshold;
    sendData.stopThreshold = stopThreshold;
    
    bool scan = CheckBoxExtractionDoRescanning->isChecked();
    int scanDataNoToStore = SpinBoxExtractionDoRescanningStoreNo->value();
    sendData.scan = scan;
    sendData.scanDataNoToStore = scanDataNoToStore;
    
    dprintf("CStackImageController::onExtractionExtractButtonClicked " \
            "size (%d, %d, %d), scale (%f, %f, %f), " \
            "start (%f, %f, %f), " \
            "ROI (%d-%d, %d-%d, %d-%d) [%s], " \
            "threshold = %d, " \
            "calcProp = %s, fname = %s, " \
            "start = %d, stop = %d, " \
            "scan = %s -> [%d]\n",
            StackImageData[stackImageDataNo].size.x,
            StackImageData[stackImageDataNo].size.y,
            StackImageData[stackImageDataNo].size.z,
            StackImageData[stackImageDataNo].scale.x,
            StackImageData[stackImageDataNo].scale.y,
            StackImageData[stackImageDataNo].scale.z,
            startx, starty, startz,
            StackImageData[stackImageDataNo].ROI.x.from,
            StackImageData[stackImageDataNo].ROI.x.to,
            StackImageData[stackImageDataNo].ROI.y.from,
            StackImageData[stackImageDataNo].ROI.y.to,
            StackImageData[stackImageDataNo].ROI.z.from,
            StackImageData[stackImageDataNo].ROI.z.to,
            activateROI ? "ON" : "OFF",
            threshold,
            sendData.calcProp ? "ON" : "OFF",
            sendData.fname,
            sendData.startThreshold, sendData.stopThreshold,
            sendData.scan ? "YES" : "NO", sendData.scanDataNoToStore);

    PushButtonExtractionCancel->setEnabled(true);
    PushButtonExtractionExtract->setEnabled(false);
    nowExtracting = true;

    putData(COMID_DO_EXTRACTION, (char *)&sendData, sizeof(sendData));
}

void CStackImageController::onExtractionCancelButtonClicked()
{
    // clear all
    //LineEditExtractionBinaryThreshold->setText("");
    //CheckBoxExtractionMedianFilter->setCheckState(Qt::Unchecked);
    DATAFORMAT_CANCEL_EXTRACTION sendData;
    putData(COMID_CANCEL_EXTRACTION, (char *)&sendData, sizeof(sendData));
}

void CStackImageController::onExtractionHandTracingClicked()
{
    DATAFORMAT_SET_ORTHOVIEW_STACKIMAGE sendData;
    int dataNo = SpinBoxExtractionDataNo->value();
    sendData.ptr = StackImageData[dataNo].ptr;
    sendData.size.x = StackImageData[dataNo].size.x;
    sendData.size.y = StackImageData[dataNo].size.y;
    sendData.size.z = StackImageData[dataNo].size.z;
    sendData.scale.x = StackImageData[dataNo].scale.x;
    sendData.scale.y = StackImageData[dataNo].scale.y;
    sendData.scale.z = StackImageData[dataNo].scale.z;
    putData(COMID_SET_ORTHOVIEW_STACKIMAGE,
            (char *)&sendData, sizeof(sendData));

    DATAFORMAT_HANDTRACE_STACKIMAGE sendData2;
    sendData2.ptr = StackImageData[dataNo].ptr;
    sendData2.size.x = StackImageData[dataNo].size.x;
    sendData2.size.y = StackImageData[dataNo].size.y;
    sendData2.size.z = StackImageData[dataNo].size.z;
    sendData2.scale.x = StackImageData[dataNo].scale.x;
    sendData2.scale.y = StackImageData[dataNo].scale.y;
    sendData2.scale.z = StackImageData[dataNo].scale.z;
    putData(COMID_HANDTRACE_STACKIMAGE,
            (char *)&sendData2, sizeof(sendData2));
}

void CStackImageController::setExtractionExtractButtonEnable()
{
    // check for performing flags
    if (LineEditExtractionBinaryThreshold->text().isEmpty()
        || nowExtracting == true) {
        PushButtonExtractionExtract->setEnabled(false);
    } else {
        PushButtonExtractionExtract->setEnabled(true);
    }
}

void CStackImageController::onExtractionFinished()
{
    QMessageBox msgBox;
    msgBox.setText("Extraction has been finished");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
}

//------------------------------------------------------------------------------
// Image Processing
//------------------------------------------------------------------------------
void CStackImageController::onImageProcessingFindLCRButtonClicked()
{
    int dataNo = SpinBoxImageProcessingDataNo->value();
    unsigned char *curVoxelData = StackImageData[dataNo].ptr;

    if (curVoxelData == NULL) return;

    int sizex = StackImageData[dataNo].size.x;
    int sizey = StackImageData[dataNo].size.y;
    int sizez = StackImageData[dataNo].size.z;
    dprintf("CStackImageController::onImageProcessingFindLCRButtonClicked " \
            "dataNo = %d, "
            "curVoxelData = %p, " \
            "size (%d, %d, %d)\n",
            dataNo,
            curVoxelData,
            sizex, sizey, sizez
            );
    int unitBoxLength = 50;
    double scalex = StackImageData[dataNo].scale.x;
    double scaley = StackImageData[dataNo].scale.y;
    double scalez = StackImageData[dataNo].scale.z;
    int divNumX = sizex * scalex / unitBoxLength;
    int divNumY = sizey * scaley / unitBoxLength;
    int divNumZ = sizez * scalez / unitBoxLength;
    vpLowContrastRegion(curVoxelData,
                        sizex, sizey, sizez,
                        &StackImageData[CurStackImageNo].LCR,
                        divNumX, divNumY, divNumZ);

    sendViewControlCurrentState();
}

void CStackImageController::onImageProcessingGenerateStackImageButtonClicked()
{
    int dataNo = SpinBoxImageProcessingGenerateStackImageDataNo->value();
    int type = ComboBoxImageProcessingGenerateStackImageType->currentIndex();
    double param1 = DoubleSpinBoxImageProcessingGenerateStackImageParam1->value();
    double param2 = DoubleSpinBoxImageProcessingGenerateStackImageParam2->value();
    double param3 = DoubleSpinBoxImageProcessingGenerateStackImageParam3->value();
    double param4 = DoubleSpinBoxImageProcessingGenerateStackImageParam4->value();
    double param5 = DoubleSpinBoxImageProcessingGenerateStackImageParam5->value();
    //unsigned char *curVoxelData = StackImageData[dataNo].ptr;

    //if (curVoxelData == NULL) return;

    // int sizex = StackImageData[dataNo].size.x;
    // int sizey = StackImageData[dataNo].size.y;
    // int sizez = StackImageData[dataNo].size.z;
    // dprintf("CStackImageController::" \
    //         "onImageProcessingGenerateStackImageButtonClicked " \
    //         "dataNo = %d, "
    //         "curVoxelData = %p, " \
    //         "size (%d, %d, %d)\n",
    //         dataNo,
    //         curVoxelData,
    //         sizex, sizey, sizez
    //         );

    DATAFORMAT_GENERATE_STACKIMAGE sendData;
    sendData.dataNo = dataNo;
    sendData.type = type;
    sendData.params[0] = param1;
    sendData.params[1] = param2;
    sendData.params[2] = param3;
    sendData.params[3] = param4;
    sendData.params[4] = param5;
    putData(COMID_GENERATE_STACKIMAGE,
            (char *)&sendData, sizeof(sendData));
}

void CStackImageController::onImageProcessingAddNoiseButtonClicked()
{
    int dataNo = SpinBoxImageProcessingNoiseDataNo->value();
    double SD = DoubleSpinBoxImageProcessingNoiseSD->value();

    unsigned char *curVoxelData = StackImageData[dataNo].ptr;

    if (curVoxelData == NULL) return;

    int sizex = StackImageData[dataNo].size.x;
    int sizey = StackImageData[dataNo].size.y;
    int sizez = StackImageData[dataNo].size.z;
    dprintf("CStackImageController::onImageProcessingAddNoiseButtonClicked " \
            "dataNo = %d, "
            "curVoxelData = %p, " \
            "size (%d, %d, %d)\n",
            dataNo,
            curVoxelData,
            sizex, sizey, sizez
            );
    vpNoiseAdditionGaussian(curVoxelData,
                            sizex, sizey, sizez,
                            SD);

    sendViewControlCurrentState();    
}


void CStackImageController::onImageProcessingBackgroundGenerateButtonClicked()
{
    int dataNo = SpinBoxImageProcessingBackgroundDataNo->value();
    int type = ComboBoxImageProcessingBackgroundType->currentIndex();
    double x0 = LineEditImageProcessingBackgroundOriginX->text().toDouble();
    double y0 = LineEditImageProcessingBackgroundOriginY->text().toDouble();
    double z0 = LineEditImageProcessingBackgroundOriginZ->text().toDouble();
    double nx = LineEditImageProcessingBackgroundNormalVectorX->text().toDouble();
    double ny = LineEditImageProcessingBackgroundNormalVectorY->text().toDouble();
    double nz = LineEditImageProcessingBackgroundNormalVectorZ->text().toDouble();
    double max = DoubleSpinBoxImageProcessingBackgroundMax->value();
    double min = DoubleSpinBoxImageProcessingBackgroundMin->value();
    double parameter = DoubleSpinBoxImageProcessingBackgroundParameter->value();

    unsigned char *curVoxelData = StackImageData[dataNo].ptr;

    if (curVoxelData == NULL) return;

    int sizex = StackImageData[dataNo].size.x;
    int sizey = StackImageData[dataNo].size.y;
    int sizez = StackImageData[dataNo].size.z;
    dprintf("CStackImageController::onImageProcessingBackgroundButtonClicked " \
            "dataNo = %d, "
            "curVoxelData = %p, " \
            "size (%d, %d, %d)\n",
            dataNo,
            curVoxelData,
            sizex, sizey, sizez
            );

    switch (type) {
        case 0: // sin
            vpBackgroundAdditionSin(curVoxelData,
                                    sizex, sizey, sizez,
                                    x0, y0, z0,
                                    nx, ny, nz,
                                    (int)min, (int)max,
                                    parameter);
            break;
        case 1: // sphere
            vpBackgroundAdditionSphere(curVoxelData,
                                       sizex, sizey, sizez,
                                       x0, y0, z0, parameter,
                                       (int)max);
            break;
    }

    sendViewControlCurrentState(); 
}

void CStackImageController::onDangerButtonClicked()
{
    int dataNo = SpinBoxImageProcessingBackgroundDataNo->value();

    unsigned char *curVoxelData = StackImageData[dataNo].ptr;

    if (curVoxelData == NULL) return;

    int sizex = StackImageData[dataNo].size.x;
    int sizey = StackImageData[dataNo].size.y;
    int sizez = StackImageData[dataNo].size.z;
    
    // sin
    vpBackgroundAdditionSin(curVoxelData,
                            sizex, sizey, sizez,
                            0, 0, 0,
                            0, 0, 1,
                            -50, 0,
                            0.01);
    vpBackgroundAdditionSphere(curVoxelData,
                               sizex, sizey, sizez,
                               getRandNormal(200, 10),
                               getRandNormal(256, 10),
                               getRandNormal(400, 10),
                               getRandNormal(100, 10),
                               getRandNormal(150, 10));
    vpBackgroundAdditionSin(curVoxelData,
                            sizex, sizey, sizez,
                            0, 0, 0,
                            0, 0, 1,
                            30, 30,
                            0.0);
    sendViewControlCurrentState();
}

void CStackImageController::onPoisonButtonClicked()
{
    int dataNo = SpinBoxImageProcessingNoiseDataNo->value();

    unsigned char *curVoxelData = StackImageData[dataNo].ptr;

    if (curVoxelData == NULL) return;

    int sizex = StackImageData[dataNo].size.x;
    int sizey = StackImageData[dataNo].size.y;
    int sizez = StackImageData[dataNo].size.z;
    
    // sin
    vpBackgroundAdditionSin(curVoxelData,
                            sizex, sizey, sizez,
                            0, 0, 0,
                            0, 0, 1,
                            30, 30,
                            0.0);
    vpNoiseAdditionGaussian(curVoxelData,
                            sizex, sizey, sizez,
                            20.);
    sendViewControlCurrentState();
}

void CStackImageController::onEmergencyButtonClicked()
{
    int dataNo = SpinBoxImageProcessingGenerateStackImageDataNo->value();

    unsigned char *curVoxelData = StackImageData[dataNo].ptr;

    if (curVoxelData == NULL) return;

    int sizex = StackImageData[dataNo].size.x;
    int sizey = StackImageData[dataNo].size.y;
    int sizez = StackImageData[dataNo].size.z;
    

    DATAFORMAT_GENERATE_STACKIMAGE sendData;
    sendData.dataNo = dataNo;
    sendData.type = 1; // extraneous object
    sendData.params[0] = 300;
    sendData.params[1] = getRandNormal(10, 3);
    sendData.params[2] = getRandNormal(45, 45);
    sendData.params[3] = getRandNormal(45, 45);
    sendData.params[4] = getRandNormal(150, 100);
    putData(COMID_GENERATE_STACKIMAGE,
            (char *)&sendData, sizeof(sendData));
}

//------------------------------------------------------------------------------
// View Control
//------------------------------------------------------------------------------
void CStackImageController::onViewControlShowCheckBoxClicked()
{
    StackImageData[CurStackImageNo].on = CheckBoxViewControlShow->isChecked();
    sendViewControlCurrentStateLock();
    reflectCurrentState();
    sendViewControlCurrentStateUnlock();
    sendViewControlCurrentState();
    // DATAFORMAT_SET_VIEW_STACKIMAGE_ON sendData;
    // sendData.on = CheckBoxViewControlShow->isChecked();
    // putData(COMID_SET_VIEW_STACKIMAGE_ON, 
    //         (char *)&sendData, sizeof(sendData));
}

void CStackImageController::onViewControlDataNoSpinBoxChanged()
{
    int value = SpinBoxViewControlDataNo->value();

    // set current no
    CurStackImageNo = value;

    sendViewControlCurrentStateLock();
    reflectCurrentState();
    sendViewControlCurrentStateUnlock();

    // set current view control parameters
    // double curThreshold = StackImageData[CurStackImageNo].threshold;
    // VerticalSliderViewControlThreshold->setValue(curThreshold);
    
    // DATAFORMAT_REQUEST_STACKIMAGE_POINTER sendData;
    // sendData.dataNo = value;
    // putData(COMID_REQUEST_STACKIMAGE_POINTER,
    //         (char *)&sendData, sizeof(sendData));
    // data should be returned with STACKIMAGE_POINTER message

}

// void CStackImageController::onViewControlResetBoundingBoxButtonClicked()
// {
//     // request bounding box of the stack image
//     // the values will return with 
//     // "COMID_BOUNDINGBOX_STACKIMAGE" message
//     DATAFORMAT_REQUEST_BOUNDINGBOX_STACKIMAGE sendData;
//     putData(COMID_REQUEST_BOUNDINGBOX_STACKIMAGE,
//             (char *)&sendData, sizeof(sendData));
// }

void CStackImageController::onViewControlAlphaModeCheckBoxClicked()
{
    StackImageData[CurStackImageNo].alphaMode
        = CheckBoxViewControlAlphaMode->isChecked();
    sendViewControlCurrentStateLock();
    reflectCurrentState();
    sendViewControlCurrentStateUnlock();
    sendViewControlCurrentState();
}

void CStackImageController::onViewControlLCRCheckBoxClicked()
{
    StackImageData[CurStackImageNo].isLCRon = CheckBoxViewControlLCR->isChecked();
    sendViewControlCurrentStateLock();
    reflectCurrentState();
    sendViewControlCurrentStateUnlock();
    sendViewControlCurrentState();
    // DATAFORMAT_SET_VIEW_STACKIMAGE_ON sendData;
    // sendData.on = CheckBoxViewControlShow->isChecked();
    // putData(COMID_SET_VIEW_STACKIMAGE_ON, 
    //         (char *)&sendData, sizeof(sendData));
}

void CStackImageController::onViewControlOrthoViewButtonClicked()
{
    DATAFORMAT_SET_ORTHOVIEW_STACKIMAGE sendData;
    int dataNo = CurStackImageNo;
    sendData.ptr = StackImageData[dataNo].ptr;
    sendData.size.x = StackImageData[dataNo].size.x;
    sendData.size.y = StackImageData[dataNo].size.y;
    sendData.size.z = StackImageData[dataNo].size.z;
    sendData.scale.x = StackImageData[dataNo].scale.x;
    sendData.scale.y = StackImageData[dataNo].scale.y;
    sendData.scale.z = StackImageData[dataNo].scale.z;
    putData(COMID_SET_ORTHOVIEW_STACKIMAGE,
            (char *)&sendData, sizeof(sendData));
}

void CStackImageController::onViewControlResetOrthoViewSizeButtonClicked()
{
    DATAFORMAT_SET_DEFAULTSIZE_ORTHOVIEW sendData;
    putData(COMID_SET_DEFAULTSIZE_ORTHOVIEW, (char *)&sendData, sizeof(sendData));
}

void CStackImageController::updateViewControlThresholdSlideBar()
{
    QString text = LineEditViewControlThreshold->text();
    int value = text.toInt();
    VerticalSliderViewControlThreshold->setValue(value);
    StackImageData[CurStackImageNo].threshold = value;
}

void CStackImageController::updateViewControlThresholdLineEdit()
{
    int value = VerticalSliderViewControlThreshold->value();
    LineEditViewControlThreshold->setText(QString::number(value, 10));
    StackImageData[CurStackImageNo].threshold = value;
}

void CStackImageController::sendViewControlThreshold()
{
    if (StackImageData[CurStackImageNo].ptr == NULL) {
        printf("Stack Image has not been loaded\n");
        return;
    }
    DATAFORMAT_CHANGE_VIEW_THRESHOLD_STACKIMAGE sendData;
    sendData.ptr = StackImageData[CurStackImageNo].ptr;
    sendData.size.x = StackImageData[CurStackImageNo].size.x;
    sendData.size.y = StackImageData[CurStackImageNo].size.y;
    sendData.size.z = StackImageData[CurStackImageNo].size.z;
    sendData.threshold = StackImageData[CurStackImageNo].threshold;
    putData(COMID_CHANGE_VIEW_THRESHOLD_STACKIMAGE,
            (char *)&sendData, sizeof(sendData));
}

void CStackImageController::updateViewControlColorRSlideBar()
{
    QString text = LineEditViewControlColorR->text();
    int value = text.toInt();
    VerticalSliderViewControlColorR->setValue(value);
    StackImageData[CurStackImageNo].color.r = value;
}

void CStackImageController::updateViewControlColorRLineEdit()
{
    int value = VerticalSliderViewControlColorR->value();
    LineEditViewControlColorR->setText(QString::number(value, 10));
}

void CStackImageController::updateViewControlColorGSlideBar()
{
    QString text = LineEditViewControlColorG->text();
    int value = text.toInt();
    VerticalSliderViewControlColorG->setValue(value);
    StackImageData[CurStackImageNo].color.g = value;
}

void CStackImageController::updateViewControlColorGLineEdit()
{
    int value = VerticalSliderViewControlColorG->value();
    LineEditViewControlColorG->setText(QString::number(value, 10));
}

void CStackImageController::updateViewControlColorBSlideBar()
{
    QString text = LineEditViewControlColorB->text();
    int value = text.toInt();
    VerticalSliderViewControlColorB->setValue(value);
    StackImageData[CurStackImageNo].color.b = value;
}

void CStackImageController::updateViewControlColorBLineEdit()
{
    int value = VerticalSliderViewControlColorB->value();
    LineEditViewControlColorB->setText(QString::number(value, 10));
}

void CStackImageController::updateViewControlTranslationXSlideBar()
{
    QString text = LineEditViewControlTranslationX->text();
    int value = text.toInt();
    VerticalSliderViewControlTranslationX->setValue(value);
    StackImageData[CurStackImageNo].translate.x = value;
}

void CStackImageController::updateViewControlTranslationXLineEdit()
{
    int value = VerticalSliderViewControlTranslationX->value();
    LineEditViewControlTranslationX->setText(QString::number(value, 10));
    double scale = StackImageData[CurStackImageNo].scale.x;
    dprintf("CStackImageController::updateViewControlTranslationXLineEdit " \
            "value = %d, scale = %f\n", value, scale);
    LineEditViewControlTranslationXum->setText(QString::number((int)(value*scale), 10));
}

void CStackImageController::updateViewControlTranslationYSlideBar()
{
    QString text = LineEditViewControlTranslationY->text();
    int value = text.toInt();
    VerticalSliderViewControlTranslationY->setValue(value);
    StackImageData[CurStackImageNo].translate.y = value;
}

void CStackImageController::updateViewControlTranslationYLineEdit()
{
    int value = VerticalSliderViewControlTranslationY->value();
    LineEditViewControlTranslationY->setText(QString::number(value, 10));
    double scale = StackImageData[CurStackImageNo].scale.y;
    LineEditViewControlTranslationYum->setText(QString::number((int)(value*scale), 10));
}

void CStackImageController::updateViewControlTranslationZSlideBar()
{
    QString text = LineEditViewControlTranslationZ->text();
    int value = text.toInt();
    VerticalSliderViewControlTranslationZ->setValue(value);
    StackImageData[CurStackImageNo].translate.z = value;
}

void CStackImageController::updateViewControlTranslationZLineEdit()
{
    int value = VerticalSliderViewControlTranslationZ->value();
    LineEditViewControlTranslationZ->setText(QString::number(value, 10));
    double scale = StackImageData[CurStackImageNo].scale.z;
    LineEditViewControlTranslationZum->setText(QString::number((int)(value*scale), 10));
}

void CStackImageController::sendViewControlCurrentState()
{
    if (SendViewControlCurrentStateLock == true) return;

    DATAFORMAT_SET_VIEW_STACKIMAGE sendData;
    sendData.ptr = StackImageData[CurStackImageNo].ptr;
    sendData.threshold = StackImageData[CurStackImageNo].threshold;
    sendData.dataNo = CurStackImageNo;
    sendData.size.x = StackImageData[CurStackImageNo].size.x;
    sendData.size.y = StackImageData[CurStackImageNo].size.y;
    sendData.size.z = StackImageData[CurStackImageNo].size.z;
    sendData.translate.x = StackImageData[CurStackImageNo].translate.x;
    sendData.translate.y = StackImageData[CurStackImageNo].translate.y;
    sendData.translate.z = StackImageData[CurStackImageNo].translate.z;
    sendData.scale.x = StackImageData[CurStackImageNo].scale.x;
    sendData.scale.y = StackImageData[CurStackImageNo].scale.y;
    sendData.scale.z = StackImageData[CurStackImageNo].scale.z;
    sendData.ROI.x.from = StackImageData[CurStackImageNo].ROI.x.from;
    sendData.ROI.x.to = StackImageData[CurStackImageNo].ROI.x.to;
    sendData.ROI.y.from = StackImageData[CurStackImageNo].ROI.y.from;
    sendData.ROI.y.to = StackImageData[CurStackImageNo].ROI.y.to;
    sendData.ROI.z.from = StackImageData[CurStackImageNo].ROI.z.from;
    sendData.ROI.z.to = StackImageData[CurStackImageNo].ROI.z.to;
    sendData.ptrLCR
        = (REGION3DARRAY_POINTER)&StackImageData[CurStackImageNo].LCR;
    sendData.isLCRon = StackImageData[CurStackImageNo].isLCRon;
    sendData.on = StackImageData[CurStackImageNo].on;
    sendData.alphaMode = StackImageData[CurStackImageNo].alphaMode;
    sendData.color.r = StackImageData[CurStackImageNo].color.r;
    sendData.color.g = StackImageData[CurStackImageNo].color.g;
    sendData.color.b = StackImageData[CurStackImageNo].color.b;

    dprintf("CStackImageController::sendViewControlCurrentState " \
            "No = %d, " \
            "ptr = %p, " \
            "threshold = %d, " \
            "size (%d, %d, %d) " \
            "translation (%d, %d, %d) voxel, " \
            "scale (%f, %f, %f), " \
            "ROI (%d-%d, %d-%d, %d-%d), " \
            "ptrLCR %p [%s], " \
            "alphaMode [%s], " \
            "[%s]," \
            "color (%d, %d, %d)\n",
            CurStackImageNo,
            sendData.ptr,
            sendData.threshold,
            sendData.size.x, sendData.size.y, sendData.size.z,
            sendData.translate.x, sendData.translate.y, sendData.translate.z,
            sendData.scale.x, sendData.scale.y, sendData.scale.z,
            sendData.ROI.x.from, sendData.ROI.x.to,
            sendData.ROI.y.from, sendData.ROI.y.to,
            sendData.ROI.z.from, sendData.ROI.z.to,
            sendData.ptrLCR,
            sendData.isLCRon ? "ON" : "OFF",
            sendData.alphaMode ? "ON" : "OFF",
            sendData.on ? "VISIBLE" : "INVISIBLE",
            sendData.color.r, sendData.color.g, sendData.color.b);

    putData(COMID_SET_VIEW_STACKIMAGE, (char *)&sendData, sizeof(sendData));

    DATAFORMAT_REQUEST_BOUNDINGBOX_STACKIMAGE sendData2;
    putData(COMID_REQUEST_BOUNDINGBOX_STACKIMAGE,
            (char *)&sendData2, sizeof(sendData2));
}

void CStackImageController::updateViewControlPointerXSlideBar()
{
    QString text = LineEditViewControlPointerXum->text();
    int value = text.toDouble() * VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM;
    VerticalSliderViewControlPointerXum->setValue(value);
}

void CStackImageController::updateViewControlPointerXLineEdit()
{
    double value = VerticalSliderViewControlPointerXum->value()
        / (double)VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM;
    dprintf("CStackImageController::updateViewControlPointerXLineEdit " \
            "value = %f\n", value);
    LineEditViewControlPointerXum->setText(QString::number(value));
}

void CStackImageController::updateViewControlPointerYSlideBar()
{
    QString text = LineEditViewControlPointerYum->text();
    int value = text.toDouble() * VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM;
    VerticalSliderViewControlPointerYum->setValue(value);
}

void CStackImageController::updateViewControlPointerYLineEdit()
{
    double value = VerticalSliderViewControlPointerYum->value()
        / (double)VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM;
    dprintf("CStackImageController::updateViewControlPointerXLineEdit " \
            "value = %f\n", value);
    LineEditViewControlPointerYum->setText(QString::number(value));
}

void CStackImageController::updateViewControlPointerZSlideBar()
{
    QString text = LineEditViewControlPointerZum->text();
    int value = text.toDouble() * VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM;
    VerticalSliderViewControlPointerZum->setValue(value);
}

void CStackImageController::updateViewControlPointerZLineEdit()
{
    double value = VerticalSliderViewControlPointerZum->value()
        / (double)VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM;
    dprintf("CStackImageController::updateViewControlPointerXLineEdit " \
            "value = %f\n", value);
    LineEditViewControlPointerZum->setText(QString::number(value));
}

void CStackImageController::sendViewControlPointer()
{
    DATAFORMAT_CHANGE_VIEW_POINTER_STACKIMAGE sendData;
    sendData.x = VerticalSliderViewControlPointerXum->value()
        / (VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM);
    sendData.y = VerticalSliderViewControlPointerYum->value()
        / (VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM);
    sendData.z = VerticalSliderViewControlPointerZum->value()
        / (VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM);
    sendData.on = CheckBoxViewControlPointer->isChecked();

    dprintf("CStackImageController::sendViewControlPointer " \
            "send pointer (%f, %f, %f) um [%s]\n",
            sendData.x, sendData.y, sendData.z,
            (sendData.on == true ? "ON" : "OFF"));

    putData(COMID_CHANGE_VIEW_POINTER_STACKIMAGE,
            (char *)&sendData, sizeof(sendData));
}

void CStackImageController::updateViewControlROIXSlideBarFrom()
{
    int value = SpinBoxViewControlROIXFrom->value();
    VerticalSliderViewControlROIXFrom->setValue(value);
    if (VerticalSliderViewControlROIXTo->value() < value) {
        VerticalSliderViewControlROIXTo->setValue(value);
    }
    StackImageData[CurStackImageNo].ROI.x.from = value;
}

void CStackImageController::updateViewControlROIXSlideBarTo()
{
    int value = SpinBoxViewControlROIXTo->value();
    VerticalSliderViewControlROIXTo->setValue(value);
    if (VerticalSliderViewControlROIXFrom->value() > value) {
        VerticalSliderViewControlROIXFrom->setValue(value);
    }
    StackImageData[CurStackImageNo].ROI.x.to = value;
}

void CStackImageController::updateViewControlROIXSpinBoxFrom()
{
    int value = VerticalSliderViewControlROIXFrom->value();
    SpinBoxViewControlROIXFrom->setValue(value);
}

void CStackImageController::updateViewControlROIXSpinBoxTo()
{
    int value = VerticalSliderViewControlROIXTo->value();
    SpinBoxViewControlROIXTo->setValue(value);
}

void CStackImageController::updateViewControlROIYSlideBarFrom()
{
    int value = SpinBoxViewControlROIYFrom->value();
    VerticalSliderViewControlROIYFrom->setValue(value);
    if (VerticalSliderViewControlROIYTo->value() < value) {
        VerticalSliderViewControlROIYTo->setValue(value);
    }
    StackImageData[CurStackImageNo].ROI.y.from = value;
}

void CStackImageController::updateViewControlROIYSlideBarTo()
{
    int value = SpinBoxViewControlROIYTo->value();
    VerticalSliderViewControlROIYTo->setValue(value);
    if (VerticalSliderViewControlROIYFrom->value() > value) {
        VerticalSliderViewControlROIYFrom->setValue(value);
    }
    StackImageData[CurStackImageNo].ROI.y.to = value;
}

void CStackImageController::updateViewControlROIYSpinBoxFrom()
{
    int value = VerticalSliderViewControlROIYFrom->value();
    SpinBoxViewControlROIYFrom->setValue(value);
}

void CStackImageController::updateViewControlROIYSpinBoxTo()
{
    int value = VerticalSliderViewControlROIYTo->value();
    SpinBoxViewControlROIYTo->setValue(value);
}

void CStackImageController::updateViewControlROIZSlideBarFrom()
{
    int value = SpinBoxViewControlROIZFrom->value();
    VerticalSliderViewControlROIZFrom->setValue(value);
    if (VerticalSliderViewControlROIZTo->value() < value) {
        VerticalSliderViewControlROIZTo->setValue(value);
    }
    StackImageData[CurStackImageNo].ROI.z.from = value;
}

void CStackImageController::updateViewControlROIZSlideBarTo()
{
    int value = SpinBoxViewControlROIZTo->value();
    VerticalSliderViewControlROIZTo->setValue(value);
    if (VerticalSliderViewControlROIZFrom->value() > value) {
        VerticalSliderViewControlROIZFrom->setValue(value);
    }
    StackImageData[CurStackImageNo].ROI.z.to = value;
}

void CStackImageController::updateViewControlROIZSpinBoxFrom()
{
    int value = VerticalSliderViewControlROIZFrom->value();
    SpinBoxViewControlROIZFrom->setValue(value);
}

void CStackImageController::updateViewControlROIZSpinBoxTo()
{
    int value = VerticalSliderViewControlROIZTo->value();
    SpinBoxViewControlROIZTo->setValue(value);
}

//------------------------------------------------------------------------------
// Properties
//------------------------------------------------------------------------------
void CStackImageController::updateProperties()
{
    
}

void CStackImageController::showEvent(QShowEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_STACKIMAGECONTROLLER;
    sendData.show = this->isVisible();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void CStackImageController::hideEvent(QHideEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_STACKIMAGECONTROLLER;
    sendData.show = this->isVisible();
    sendData.minimized = this->isMinimized();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void CStackImageController::closeEvent(QCloseEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_STACKIMAGECONTROLLER;
    sendData.show = this->isVisible();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

//------------------------------------------------------------------------------
// Terminal
//------------------------------------------------------------------------------
void CStackImageController::procedure(int ID, char *data, int byte)
{
	switch (ID) {

        case COMID_LOAD_STACKIMAGE_OK: {
            // send recieved stack data to shape viewer
            DATAFORMAT_LOAD_STACKIMAGE_OK *recvData
                = (DATAFORMAT_LOAD_STACKIMAGE_OK *)data;

            dprintf("CStackImageController::procedure " \
                    "got LOAD_STACKIMAGE_OK\n");
            // dprintf("CStackImageController::procedure " \
            //         "data = %p, size = %d\n", data, byte);
            dprintf("CStackImageController::procedure " \
                    "ptr = %p, dataNo = %d, size (%d, %d, %d), " \
                    "scale (%f, %f, %f)\n",
                    recvData->ptr,
                    recvData->dataNo,
                    recvData->size.x,
                    recvData->size.y,
                    recvData->size.z,
                    recvData->scale.x,
                    recvData->scale.y,
                    recvData->scale.z);

            // set current state
            CurStackImageNo = recvData->dataNo;
            StackImageData[CurStackImageNo].ptr = recvData->ptr;
            StackImageData[CurStackImageNo].size.x = recvData->size.x;
            StackImageData[CurStackImageNo].size.y = recvData->size.y;
            StackImageData[CurStackImageNo].size.z = recvData->size.z;
            // int translatex = VerticalSliderViewControlTranslationX->value();
            // int translatey = VerticalSliderViewControlTranslationY->value();
            // int translatez = VerticalSliderViewControlTranslationZ->value();
            StackImageData[CurStackImageNo].translate.x = 0;
            StackImageData[CurStackImageNo].translate.y = 0;
            StackImageData[CurStackImageNo].translate.z = 0;
            StackImageData[CurStackImageNo].scale.x = recvData->scale.x;
            StackImageData[CurStackImageNo].scale.y = recvData->scale.y;
            StackImageData[CurStackImageNo].scale.z = recvData->scale.z;
            StackImageData[CurStackImageNo].ROI.x.from = 0;
            StackImageData[CurStackImageNo].ROI.x.to
                = StackImageData[CurStackImageNo].size.x - 1;
            StackImageData[CurStackImageNo].ROI.y.from = 0;
            StackImageData[CurStackImageNo].ROI.y.to
                = StackImageData[CurStackImageNo].size.y - 1;
            StackImageData[CurStackImageNo].ROI.z.from = 0;
            StackImageData[CurStackImageNo].ROI.z.to
                = StackImageData[CurStackImageNo].size.z - 1;
            bool on = CheckBoxViewControlShow->isChecked();
            StackImageData[CurStackImageNo].on = on;
            
            sendViewControlCurrentStateLock();
            reflectCurrentState();
            sendViewControlCurrentStateUnlock();

            sendViewControlCurrentStateLock();
            VerticalSliderViewControlROIXFrom->setValue(0);
            VerticalSliderViewControlROIYFrom->setValue(0);
            VerticalSliderViewControlROIZFrom->setValue(0);
            VerticalSliderViewControlROIXTo->setValue(recvData->size.x - 1);
            VerticalSliderViewControlROIYTo->setValue(recvData->size.y - 1);
            VerticalSliderViewControlROIZTo->setValue(recvData->size.z - 1);
            sendViewControlCurrentStateUnlock();

            sendViewControlCurrentState();
            
            // request bounding box of the stack image
            // the values will return with 
            // "COMID_BOUNDINGBOX_STACKIMAGE" message
            DATAFORMAT_REQUEST_BOUNDINGBOX_STACKIMAGE sendData2;
            putData(COMID_REQUEST_BOUNDINGBOX_STACKIMAGE,
                    (char *)&sendData2, sizeof(sendData2));

            // set view control
            CheckBoxViewControlShow->setChecked(true);
            SpinBoxExtractionDataNo->setValue(CurStackImageNo);

            return;
        } // COMID_LOAD_STACKIMAGE_OK

        case COMID_STORE_STACKIMAGE_OK: {
            // send recieved stack data to shape viewer
            DATAFORMAT_STORE_STACKIMAGE_OK *recvData
                = (DATAFORMAT_STORE_STACKIMAGE_OK *)data;

            dprintf("CStackImageController::procedure " \
                    "got STORE_STACKIMAGE_OK\n");
            dprintf("CStackImageController::procedure " \
                    "ptr = %p, dataNo = %d, size (%d, %d, %d), " \
                    "scale (%f, %f, %f)\n",
                    recvData->ptr,
                    recvData->dataNo,
                    recvData->size.x,
                    recvData->size.y,
                    recvData->size.z,
                    recvData->scale.x,
                    recvData->scale.y,
                    recvData->scale.z);

            // set current state
            int dataNo = recvData->dataNo;
            StackImageData[dataNo].ptr = recvData->ptr;
            StackImageData[dataNo].size.x = recvData->size.x;
            StackImageData[dataNo].size.y = recvData->size.y;
            StackImageData[dataNo].size.z = recvData->size.z;
            // int translatex = VerticalSliderViewControlTranslationX->value();
            // int translatey = VerticalSliderViewControlTranslationY->value();
            // int translatez = VerticalSliderViewControlTranslationZ->value();
            StackImageData[dataNo].translate.x = 0;
            StackImageData[dataNo].translate.y = 0;
            StackImageData[dataNo].translate.z = 0;
            StackImageData[dataNo].scale.x = recvData->scale.x;
            StackImageData[dataNo].scale.y = recvData->scale.y;
            StackImageData[dataNo].scale.z = recvData->scale.z;
            StackImageData[dataNo].ROI.x.from = 0;
            StackImageData[dataNo].ROI.x.to
                = StackImageData[dataNo].size.x - 1;
            StackImageData[dataNo].ROI.y.from = 0;
            StackImageData[dataNo].ROI.y.to
                = StackImageData[dataNo].size.y - 1;
            StackImageData[dataNo].ROI.z.from = 0;
            StackImageData[dataNo].ROI.z.to
                = StackImageData[dataNo].size.z - 1;
            //bool on = CheckBoxViewControlShow->isChecked();
            StackImageData[dataNo].on = false;
            
            //sendViewControlCurrentStateLock();
            //reflectCurrentState();
            //sendViewControlCurrentStateUnlock();

            // sendViewControlCurrentStateLock();
            // VerticalSliderViewControlROIXFrom->setValue(0);
            // VerticalSliderViewControlROIYFrom->setValue(0);
            // VerticalSliderViewControlROIZFrom->setValue(0);
            // VerticalSliderViewControlROIXTo->setValue(recvData->size.x - 1);
            // VerticalSliderViewControlROIYTo->setValue(recvData->size.y - 1);
            // VerticalSliderViewControlROIZTo->setValue(recvData->size.z - 1);
            // sendViewControlCurrentStateUnlock();

            // sendViewControlCurrentState();
            
            // request bounding box of the stack image
            // the values will return with 
            // "COMID_BOUNDINGBOX_STACKIMAGE" message
            // DATAFORMAT_REQUEST_BOUNDINGBOX_STACKIMAGE sendData2;
            // putData(COMID_REQUEST_BOUNDINGBOX_STACKIMAGE,
            //         (char *)&sendData2, sizeof(sendData2));

            // set view control
            //CheckBoxViewControlShow->setChecked(true);
            //SpinBoxExtractionDataNo->setValue(dataNo);

            return;
        } // COMID_STORE_STACKIMAGE_OK

        case COMID_SAVE_STACKIMAGE_OK: {
            dprintf("CStackImageController::procedure " \
                    "got SAVE_STACKIMAGE_OK\n");
            // dprintf("CStackImageController::procedure " \
            //         "data = %p, size = %d\n", data, byte);
            return;
        } // COMID_SAVE_STACKIMAGE_OK

        case COMID_STACKIMAGE_POINTER: {
            DATAFORMAT_STACKIMAGE_POINTER *recvData
                = (DATAFORMAT_STACKIMAGE_POINTER *)data;

            dprintf("CStackImageController::procedure " \
                    "got STACKIMAGE_POINTE\n");
            dprintf("CStackImageController::procedure " \
                    "ptr = %p, dataNo = %d, size (%d, %d, %d), " \
                    "scale (%f, %f, %f)\n",
                    recvData->ptr,
                    recvData->dataNo,
                    recvData->size.x,
                    recvData->size.y,
                    recvData->size.z,
                    recvData->scale.x,
                    recvData->scale.y,
                    recvData->scale.z);


            // set current state
            CurStackImageNo = recvData->dataNo;
            StackImageData[CurStackImageNo].ptr = recvData->ptr;
            StackImageData[CurStackImageNo].size.x = recvData->size.x;
            StackImageData[CurStackImageNo].size.y = recvData->size.y;
            StackImageData[CurStackImageNo].size.z = recvData->size.z;
            StackImageData[CurStackImageNo].scale.x = recvData->scale.x;
            StackImageData[CurStackImageNo].scale.y = recvData->scale.y;
            StackImageData[CurStackImageNo].scale.z = recvData->scale.z;

            // DATAFORMAT_SET_VIEW_STACKIMAGE sendData;
            // sendData.ptr = StackImageData[CurStackImageNo].ptr;
            // sendData.size.x = StackImageData[CurStackImageNo].size.x;
            // sendData.size.y = StackImageData[CurStackImageNo].size.y;
            // sendData.size.z = StackImageData[CurStackImageNo].size.z;
            // sendData.translate.x = 0;
            // sendData.translate.y = 0;
            // sendData.translate.z = 0;
            // sendData.scale.x = StackImageData[CurStackImageNo].scale.x;
            // sendData.scale.y = StackImageData[CurStackImageNo].scale.y;
            // sendData.scale.z = StackImageData[CurStackImageNo].scale.z;
            // putData(COMID_SET_VIEW_STACKIMAGE,
            //         (char *)&sendData, sizeof(sendData));

            return;
        } // COMID_REQUEST_STACKIMAGE_POINTER

        case COMID_CANCELED_EXTRACTION: {
            dprintf("CStackImageController::procedure " \
                    "got CANCELED_EXTRACTION\n");
            nowExtracting = false;
            PushButtonExtractionCancel->setEnabled(false);
            PushButtonExtractionExtract->setEnabled(true);
            return;
        } // COMID_CANCELED_EXTRACTION

        case COMID_FINISHED_EXTRACTION: {
            dprintf("CStackImageController::procedure " \
                    "got FINISHED_EXTRACTION\n");
            nowExtracting = false;

            emit extractionFinished();
            PushButtonExtractionCancel->setEnabled(false);
            PushButtonExtractionExtract->setEnabled(true);
            return;
        } // COMID_FINISHED_EXTRACTION

        case COMID_FAILED_EXTRACTION: {
            DATAFORMAT_FAILED_EXTRACTION *recvData
                = (DATAFORMAT_FAILED_EXTRACTION *)data;
            
            dprintf("CStackImageController::procedure " \
                    "got FAILED_EXTRACTION");
            dprintf("CStackImageController::procedure " \
                    "error message : %s\n", recvData->msg);

            nowExtracting = false;
            PushButtonExtractionCancel->setEnabled(false);
            PushButtonExtractionExtract->setEnabled(true);

            return;
        } // COMID_FAILED_EXTRACTION

        case COMID_CHANGE_VIEW_POINTER_STACKIMAGE: {
            DATAFORMAT_CHANGE_VIEW_POINTER_STACKIMAGE *recvData
                = (DATAFORMAT_CHANGE_VIEW_POINTER_STACKIMAGE *)data;

            dprintf("CStackImageController::procedure " \
                    "got CHANGE_VIEW_POINTER_STACKIMAGE\n");

            return;
        } // COMID_CHANGE_VIEW_POINTER_STACKIMAGE

        case COMID_SET_VIEW_STACKIMAGE_OK: {
            dprintf("CStackImageController::procedure " \
                    "got SET_VIEW_STACKIMAGE_OK\n");
            // dprintf("CStackImageController::procedure " \
            //         "data = %p, size = %d\n", data, byte);
            return;
        } // COMID_SET_VIEW_STACKIMAGE_OK

        case COMID_BOUNDINGBOX_STACKIMAGE: {
            DATAFORMAT_BOUNDINGBOX_STACKIMAGE *recvData
                = (DATAFORMAT_BOUNDINGBOX_STACKIMAGE *)data;

            dprintf("CStackImageController::procedure " \
                    "got BOUNDINGBOX_STACKIMAGE\n");
            // dprintf("CStackImageController::procedure " \
            //         "data = %p, size = %d\n", data, byte);
            dprintf("CStackImageController::procedure " \
                    "min (%.1f, %.1f, %.1f), " \
                    "max (%.1f, %.1f, %.1f), " \
                    "mean (%.1f, %.1f, %.1f)\n",
                    recvData->min.x, recvData->min.y, recvData->min.z,
                    recvData->max.x, recvData->max.y, recvData->max.z,
                    recvData->mean.x, recvData->mean.y, recvData->mean.z);

            // int curPointerX = VerticalSliderViewControlPointerXum;
            // int curPointerY = VerticalSliderViewControlPointerYum;
            // int curPointerZ = VerticalSliderViewControlPointerZum;

            sendViewControlCurrentStateLock();
            VerticalSliderViewControlPointerXum->setMinimum(0);
            VerticalSliderViewControlPointerYum->setMinimum(0);
            VerticalSliderViewControlPointerZum->setMinimum(0);
            VerticalSliderViewControlPointerXum->setMaximum(
                (recvData->max.x - 1) * VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM);
            VerticalSliderViewControlPointerYum->setMaximum(
                (recvData->max.y - 1) * VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM);
            VerticalSliderViewControlPointerZum->setMaximum(
                (recvData->max.z - 1) * VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM);
            sendViewControlCurrentStateUnlock();
            // VerticalSliderViewControlPointerXum->setValue(0);
            // VerticalSliderViewControlPointerYum->setValue(0);
            // VerticalSliderViewControlPointerZum->setValue(0);

            return;
        } // COMID_BOUNDINGBOX_STACKIMAGE

        case COMID_ORTHOVIEW_KEYBOARD_MANIPULATION: {
            DATAFORMAT_ORTHOVIEW_KEYBOARD_MANIPULATION *recvData
                = (DATAFORMAT_ORTHOVIEW_KEYBOARD_MANIPULATION *)data;

            // dprintf("CHandTracingTool::procedure " \
            //         "got ORTHOVIEW_KEYBOARD_MANIPULATION\n");

            //sendViewControlCurrentStateLock();
            LineEditViewControlPointerXum->setText(QString::number(recvData->point.x));
            LineEditViewControlPointerYum->setText(QString::number(recvData->point.y));
            LineEditViewControlPointerZum->setText(QString::number(recvData->point.z));
            //reflectCurrentState();
            //sendViewControlCurrentStateUnlock();

            return;
        } // COMID_ORTHOVIEW_KEYBOARD_MANIPULATION

		default:
			return;
	}

    
}
