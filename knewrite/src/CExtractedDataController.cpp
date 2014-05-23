
#include <QtGui>

#include "CExtractedDataController.h"
#include "CObjectCommunicatorID.h"

#include "BRodriguez2009.h"
#include "BRodriguez2009Cluster.h"

#include "BCommon.h"

#define ANGLE_DIV_NUM 16

#define VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM 10

CExtractedDataController::CExtractedDataController(QWidget *parent) :
    QDialog(parent)
{
// #ifdef ___DEBUG___
//     LineEditFileLoadFilePath->setText("/home/naska/work/Qt/NeuronStructure/generated_tree_structure.txt");
// #endif 

    setupUi(this);
    
    CurExtractedDataNo = 0;
    for (int i = 0; i < MAX_EXTRACTED_DATA_NUM; i++) {
        ExtractedData[i].ptr = NULL;
        ExtractedData[i].translate.x = 0;
        ExtractedData[i].translate.y = 0;
        ExtractedData[i].translate.z = 0;
        ExtractedData[i].scale.x = 0.;
        ExtractedData[i].scale.y = 0.;
        ExtractedData[i].scale.z = 0.;
        ExtractedData[i].on = false;
    }


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

    //--------------------------------------------------------------------------
    // FileSave
    //--------------------------------------------------------------------------
    
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
    connect(LineEditFileSaveFileName, SIGNAL(textEdited(const QString &)),
            this, SLOT(updateFileSaveFilePath()));

    // check if the all properties have been set
	connect(LineEditFileSaveFilePath, SIGNAL(textChanged(const QString &)),
	 		this, SLOT(setFileSaveSaveButtonEnable()));

    ComboBoxFileSaveFileFormat->addItem(QString("Cluster list"), 0);
    ComboBoxFileSaveFileFormat->addItem(QString("swc"), 1);
    ComboBoxFileSaveFileFormat->addItem(QString("hoc template"), 2);

    //--------------------------------------------------------------------------
    // Processing
    //--------------------------------------------------------------------------

    connect(PushButtonProcessingMergeDataMerge, SIGNAL(clicked()),
            this, SLOT(onProcessingMergeDataMergeButtonClicked()));

    connect(SpinBoxProcessingMergeDataParentDataNo,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(updateProcessingMergeDataParentNodeNo()));


    connect(SpinBoxProcessingMergeDataChildDataNo,
            SIGNAL(valueChanged(int)),
            this,
            SLOT(updateProcessingMergeDataChildNodeNo()));

    connect(PushButtonProcessingCompareDataBrowse, SIGNAL(clicked()),
            this, SLOT(onProcessingCompareDataBrowseButtonClicked()));
    connect(PushButtonProcessingCompareDataCompare, SIGNAL(clicked()),
            this, SLOT(onProcessingCompareDataCompareButtonClicked()));

    //--------------------------------------------------------------------------
    // View Control
    //--------------------------------------------------------------------------

    TracingDataSelection = new QItemSelectionModel(&TracingData);

    TableViewViewControlNodeList->setModel(&TracingData);
    TableViewViewControlNodeList->setSelectionModel(TracingDataSelection);
    TableViewViewControlNodeList->horizontalHeader()->setClickable(true);
    TableViewViewControlNodeList->setSortingEnabled(true);
    TableViewViewControlNodeList->setSelectionMode(
        QAbstractItemView::SingleSelection);

    connect(TracingDataSelection, 
            SIGNAL(currentRowChanged(const QModelIndex &,
                                     const QModelIndex &)),
            this, SLOT(sendViewControlCurrentState()));

    // data No
    connect(SpinBoxViewControlDataNo, SIGNAL(valueChanged(int)),
            this, SLOT(onViewControlDataNoSpinBoxChanged()));

    // "show" check box
    connect(CheckBoxViewControlShow, SIGNAL(stateChanged(int)),
            this, SLOT(onViewControlShowCheckBoxClicked()));

    // extraction finished
    connect(this, SIGNAL(extractionFinished()),
            this, SLOT(sendViewControlCurrentState()));

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
    connect(VerticalSliderViewControlTranslationX,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));
    connect(VerticalSliderViewControlTranslationY,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));
    connect(VerticalSliderViewControlTranslationZ,
            SIGNAL(valueChanged(int)),
            this, SLOT(sendViewControlCurrentState()));

    // // rotation x
    // connect(VerticalSliderViewControlRotationX,
    //         SIGNAL(valueChanged(int)),
    //         this, SLOT(updateViewControlRotationXLineEdit()));
    // connect(LineEditViewControlRotationX, SIGNAL(textChanged(const QString &)),
    //         this, SLOT(updateViewControlRotationXSlideBar()));
    
    // // rotation y
    // connect(VerticalSliderViewControlRotationY,
    //         SIGNAL(valueChanged(int)),
    //         this, SLOT(updateViewControlRotationYLineEdit()));
    // connect(LineEditViewControlRotationY, SIGNAL(textChanged(const QString &)),
    //         this, SLOT(updateViewControlRotationYSlideBar()));

    // // rotation z
    // connect(VerticalSliderViewControlRotationZ,
    //         SIGNAL(valueChanged(int)),
    //         this, SLOT(updateViewControlRotationZLineEdit()));
    // connect(LineEditViewControlRotationZ, SIGNAL(textChanged(const QString &)),
    //         this, SLOT(updateViewControlRotationZSlideBar()));

    // // xy plane
    // connect(PushButtonViewControlRotationXYPlane, SIGNAL(clicked()),
    //         this, SLOT(setViewControlRotationXYPlane()));
    // connect(PushButtonViewControlRotationYZPlane, SIGNAL(clicked()),
    //         this, SLOT(setViewControlRotationYZPlane()));
    // connect(PushButtonViewControlRotationZXPlane, SIGNAL(clicked()),
    //         this, SLOT(setViewControlRotationZXPlane()));
    
    // // send to the shape view when the slide bar for [x or y or z] manupilated
    // connect(VerticalSliderViewControlRotationX,
    //         SIGNAL(valueChanged(int)),
    //         this, SLOT(sendViewControlRotation()));
    // connect(VerticalSliderViewControlRotationY,
    //         SIGNAL(valueChanged(int)),
    //         this, SLOT(sendViewControlRotation()));
    // connect(VerticalSliderViewControlRotationZ,
    //         SIGNAL(valueChanged(int)),
    //         this, SLOT(sendViewControlRotation()));

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
    // connect(VerticalSliderViewControlPointerXum,
    //         SIGNAL(valueChanged(int)),
    //         this, SLOT(sendViewControlPointer()));
    // connect(VerticalSliderViewControlPointerYum,
    //         SIGNAL(valueChanged(int)),
    //         this, SLOT(sendViewControlPointer()));
    // connect(VerticalSliderViewControlPointerZum,
    //         SIGNAL(valueChanged(int)),
    //         this, SLOT(sendViewControlPointer()));
    // connect(CheckBoxViewControlPointer,
    //         SIGNAL(stateChanged(int)),
    //         this, SLOT(sendViewControlPointer()));


    // 
    SpinBoxProcessingMergeDataParentDataNo->setMinimum(0);
    SpinBoxProcessingMergeDataChildDataNo->setMinimum(0);
    SpinBoxProcessingMergeDataTargetDataNo->setMinimum(0);
    SpinBoxViewControlDataNo->setMinimum(0);
    SpinBoxProcessingMergeDataParentDataNo->setMaximum(MAX_EXTRACTED_DATA_NUM-1);
    SpinBoxProcessingMergeDataChildDataNo->setMaximum(MAX_EXTRACTED_DATA_NUM-1);
    SpinBoxProcessingMergeDataTargetDataNo->setMaximum(MAX_EXTRACTED_DATA_NUM-1);
    SpinBoxViewControlDataNo->setMaximum(MAX_EXTRACTED_DATA_NUM-1);

    GroupBoxViewControlPointer->hide();
    GroupBoxViewControlTranslation->hide();
}

void CExtractedDataController::reflectCurrentState()
{
    bool on = ExtractedData[CurExtractedDataNo].on;
    CheckBoxViewControlShow->setChecked(on);
    SpinBoxViewControlDataNo->setValue(CurExtractedDataNo);
    int translatex = ExtractedData[CurExtractedDataNo].translate.x;
    int translatey = ExtractedData[CurExtractedDataNo].translate.y;
    int translatez = ExtractedData[CurExtractedDataNo].translate.z;
    VerticalSliderViewControlTranslationX->setValue(translatex);
    VerticalSliderViewControlTranslationY->setValue(translatey);
    VerticalSliderViewControlTranslationZ->setValue(translatez);

    setViewControlNodeList();
}

//------------------------------------------------------------------------------
// File Load
//------------------------------------------------------------------------------
void CExtractedDataController::onFileLoadBrowseButtonClicked()
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

void CExtractedDataController::onFileLoadLoadButtonClicked() 
{
    QString fileName = LineEditFileLoadDirectory->text()
        + QDir::separator() + LineEditFileLoadFileName->text();

    // make data & send message for MExtractedData object(s)
    DATAFORMAT_LOAD_EXTRACTEDDATA sendData;
	strncpy(sendData.fileName, fileName.toStdString().c_str(),
            sizeof(sendData.fileName));
    sendData.dataNo = SpinBoxFileLoadDataNo->value();

    dprintf("CExtractedDataController::onFileLoadLoadButtonClicked" \
            " sendData.fileName : %s\n",
            (sendData.fileName));
    dprintf("CExtractedDataController::onFileLoadLoadButtonClicked" \
            " &sendData = %p, sizeof(sendData) = %lu\n",
            &sendData, sizeof(sendData));

    // send
	putData(COMID_LOAD_EXTRACTEDDATA, (char *)&sendData, sizeof(sendData));
}

void CExtractedDataController::onFileLoadClearButtonClicked() 
{
    // clear all text
    LineEditFileLoadFilePath->setText("");
}

void CExtractedDataController::updateFileLoadFileDirAndName()
{

    // parse file name and directory path
    QString sourceText = LineEditFileLoadFilePath->text();
    QString fileName = QFileInfo(sourceText).fileName();
    QString fileDir = QFileInfo(sourceText).path();

    // set text to FileDir and FileName
    LineEditFileLoadDirectory->setText(fileDir);
    LineEditFileLoadFileName->setText(fileName);
}

void CExtractedDataController::updateFileLoadOutputTextEdit() {
	// QByteArray newData = Process.readAllStandardOutput();
	// QString text = PlainTextEditMessage->toPlainText()
	// 	+ QString::fromLocal8Bit(newData);
	// PlainTextEditMessage->setPlainText(text);
}

void CExtractedDataController::setFileLoadLoadButtonEnable()
{
    // check if the all propaties have been set
	if (LineEditFileLoadFilePath->text().isEmpty()) {
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

void CExtractedDataController::onFileSaveBrowseButtonClicked()
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

void CExtractedDataController::onFileSaveSaveButtonClicked() 
{
	QString filePath = LineEditFileSaveDirectory->text()
        + QDir::separator() + LineEditFileSaveFileName->text();
    QString fileName = LineEditFileSaveFileName->text();
    QString dirName = LineEditFileSaveDirectory->text() + QDir::separator();

    // make data & send message for MExtractedData object(s)
    DATAFORMAT_SAVE_EXTRACTEDDATA sendData;
	strncpy(sendData.filePath, filePath.toStdString().c_str(),
            sizeof(sendData.fileName));
	strncpy(sendData.fileName, fileName.toStdString().c_str(),
            sizeof(sendData.fileName));
	strncpy(sendData.dirName, dirName.toStdString().c_str(),
            sizeof(sendData.dirName));
    sendData.dataNo = SpinBoxFileSaveDataNo->value();
    ENUM_SAVE_EXTRACTEDDATA_OUTPUTTYPE index
        = (ENUM_SAVE_EXTRACTEDDATA_OUTPUTTYPE)ComboBoxFileSaveFileFormat->currentIndex();
    if (index < 0) return;
    sendData.dataFormat = index;

    // char **buf = new char*[OUTPUTTYPE_NUM];
    // buf[OUTPUTTYPE_EXTRACTEDDATA] = "ExtractedData";
    // buf[OUTPUTTYPE_SWC] = "swc";
    // buf[OUTPUTTYPE_HOC] = "hoc";

    dprintf("CExtractedDataController::onFileSaveSaveButtonClicked " \
            "baseName = %s, " \
            "dataNo = %d, " \
            "dataFormat = %d\n",
            (sendData.fileName),
            sendData.dataNo,
            sendData.dataFormat);
    dprintf("CExtractedDataController::onFileSaveSaveButtonClicked" \
            " &sendData = %p, sizeof(sendData) = %lu\n",
            &sendData, sizeof(sendData));

    // ASAFEDELETE(buf);

    // send
	putData(COMID_SAVE_EXTRACTEDDATA, (char *)&sendData, sizeof(sendData));
}

void CExtractedDataController::onFileSaveClearButtonClicked()
{
    // clear all text
    LineEditFileSaveFilePath->setText("");
}

void CExtractedDataController::updateFileSaveFileDirAndName()
{
    // parse file name and directory path
    QString sourceText = LineEditFileSaveFilePath->text();
    QString fileName = QFileInfo(sourceText).fileName();
    QString fileDir = QFileInfo(sourceText).path();

    sourceText.replace(QRegExp("/+"), "/");

    // set text to FileDir and FileName
    LineEditFileSaveDirectory->setText(fileDir);
    LineEditFileSaveFileName->setText(fileName);
}

void CExtractedDataController::updateFileSaveFilePath()
{
    QString fileDir = LineEditFileSaveDirectory->text();
    QString fileName = LineEditFileSaveFileName->text();
    QString filePath = fileDir + "/" + fileName;
    QRegExp rx("/+");
    fileName.replace(rx, "");
    fileDir.replace(rx, "/");
    filePath.replace(rx, "/");

    LineEditFileSaveDirectory->setText(fileDir);
    LineEditFileSaveFileName->setText(fileName);
    LineEditFileSaveFilePath->setText(filePath);
}

void CExtractedDataController::updateFileSaveOutputTextEdit() {
	// QByteArray newData = Process.readAllStandardOutput();
	// QString text = PlainTextEditMessage->toPlainText()
	// 	+ QString::fromLocal8Bit(newData);
	// PlainTextEditMessage->setPlainText(text);
}

void CExtractedDataController::setFileSaveSaveButtonEnable()
{
    // check if the all propaties have been set
	if (LineEditFileSaveFilePath->text().isEmpty()) {
        // save unable yet
		PushButtonFileSaveSave->setEnabled(false);
	} else {
        // save prepared
		PushButtonFileSaveSave->setEnabled(true);
	}
}

//------------------------------------------------------------------------------
// Processing
//------------------------------------------------------------------------------
void CExtractedDataController::onProcessingMergeDataMergeButtonClicked()
{
    int parentDataNo = SpinBoxProcessingMergeDataParentDataNo->value();
    int childDataNo = SpinBoxProcessingMergeDataChildDataNo->value();
    //QString parentNodeNoStr = ComboBoxProcessingMergeDataParentNodeNo->currentText();
    //QString childNodeNoStr = ComboBoxProcessingMergeDataChildNodeNo->currentText();
    //int parentNodeNo = parentNodeNoStr.toInt();
    //int childNodeNo = childNodeNoStr.toInt();
    int parentCurIndex = ComboBoxProcessingMergeDataParentNodeNo->currentIndex();
    int childCurIndex = ComboBoxProcessingMergeDataChildNodeNo->currentIndex();
    int parentNodeNo
        = ComboBoxProcessingMergeDataParentNodeNo->itemData(parentCurIndex).toInt();
    int childNodeNo
        = ComboBoxProcessingMergeDataChildNodeNo->itemData(childCurIndex).toInt();
    int targetDataNo = SpinBoxProcessingMergeDataTargetDataNo->value();

    RodClusterList *parent = (RodClusterList *)ExtractedData[parentDataNo].ptr;
    RodClusterList *child = (RodClusterList *)ExtractedData[childDataNo].ptr;
    RodClusterList *target = new RodClusterList;

    if (parent == NULL || child == NULL || target == NULL) return;

    int ret = Rodriguez2009MergeClusterList(parent, parentNodeNo,
                                            child, childNodeNo,
                                            target);
    
    dprintf("CExtractedDataController::onProcessingMergeDataMergeButtonClicked " \
            "finished\n");

    if (ret < 0) {
        fprintf(stderr,
                "CExtractedDataController:;onProcessingMergeDataMergeButtonClicked " \
                "merge failed\n");
    } else {
        // dprintf("CExtractedDataController::onProcessingMergeDataMergeButtonClicked " \
        //         "ClusterNum : parent = %u, child = %u, merged = %u\n",
        //         parent->getClusterNum(),
        //         child->getClusterNum(),
        //         target->getClusterNum());
        dprintf("CExtractedDataController::onProcessingMergeDataMergeButtonClicked " \
                "send message to store merged data\n");

        DATAFORMAT_STORE_EXTRACTEDDATA sendData;
        sendData.ptr = (CLUSTERLIST_POINTER)target;
        sendData.dataNo = targetDataNo;

        putData(COMID_STORE_EXTRACTEDDATA,
                (char *)&sendData, sizeof(sendData));
    }

    delete target;
}

void CExtractedDataController::updateProcessingMergeDataParentNodeNo()
{
    dprintf("CExtractedDataController::updateProcessingMergeDataParentNodeNo\n");
    int parentDataNo = SpinBoxProcessingMergeDataParentDataNo->value();
    //QStringList stringList;
    RodClusterList *curClusterList
        = (RodClusterList *)(ExtractedData[parentDataNo].ptr);
    if (curClusterList == NULL) return;

    int nodeNum = curClusterList->getClusterNum();
    for (int i = 0; i < nodeNum; i++) {
        //stringList.join(QString::number(i));
        //ComboBoxProcessingMergeDataParentNodeNo->setItemData(i, i);
        ComboBoxProcessingMergeDataParentNodeNo->addItem(QString::number(i), i);
    }
    //ComboBoxProcessingMergeDataParentNodeNo->insertStringList(StringList);
}

void CExtractedDataController::updateProcessingMergeDataChildNodeNo()
{
    dprintf("CExtractedDataController::updateProcessingMergeDataChildNodeNo\n");
    int childDataNo = SpinBoxProcessingMergeDataChildDataNo->value();
    //QStringList stringList;
    RodClusterList *curClusterList
        = (RodClusterList *)(ExtractedData[childDataNo].ptr);
    if (curClusterList == NULL) return;
    int nodeNum = curClusterList->getClusterNum();
    for (int i = 0; i < nodeNum; i++) {
        //stringList.join(QString::number(i));
        //ComboBoxProcessingMergeDataChildNodeNo->setItemData(i, i);
        ComboBoxProcessingMergeDataChildNodeNo->addItem(QString::number(i), i);
    }
    //ComboBoxProcessingMergeDataChildNodeNo->insertStringList(StringList);
}

void CExtractedDataController::onProcessingCompareDataBrowseButtonClicked()
{

    // get file path from file open dialog
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose File"),
                                       "", tr("Text Files (*.txt)"));
    //fileName = fileDialog.selectedFile();
    if (!fileName.isEmpty()) {
        LineEditProcessingCompareDataFilePath->setText(fileName);
    }
}

void CExtractedDataController::onProcessingCompareDataCompareButtonClicked()
{
    int dataNo1 = SpinBoxProcessingCompareDataDataNo1->value();
    int dataNo2 = SpinBoxProcessingCompareDataDataNo2->value();
    QString fileName = LineEditProcessingCompareDataFilePath->text();
	fileName = QDir::convertSeparators(fileName);
    QFile file(fileName, this);
    if (!file.open(QIODevice::WriteOnly))
        return;

    QTextStream out(&file);

    out << "#delta, discrepancy, consisntency12, consistency21\n";

    for (int i = 0; i < 50; i++) {
        double delta = (i + 1);
        double discrepancy;
        double consistency[2];
        // dprintf("CExtractedDataController::onProcessingCompareDataCompareButtonClicked " \
        //         "delta = %f\n", delta);
        int ret = Rodriguez2009CompareClusterList((RodClusterList *)ExtractedData[dataNo1].ptr,
                                                  (RodClusterList *)ExtractedData[dataNo2].ptr,
                                                  delta, &discrepancy, consistency);
        if (ret < 0) {
            fprintf(stderr, "CExtractedDataController::onProcessingCompareDataCompareButtonClicked " \
                    "comparing failed\n");
            file.close();
            return;
        }

        out << delta << ", "
            << discrepancy << ", "
            << consistency[0] << ", "
            << consistency[1] << "\n";
    }

    file.close();
}

//------------------------------------------------------------------------------
// View Control
//------------------------------------------------------------------------------
void CExtractedDataController::onViewControlShowCheckBoxClicked()
{
    dprintf("CExtractedDataController::onViewControlShowCheckBoxClicked " \
            "CurExtractedDataNo = %d\n",
            CurExtractedDataNo);
    ExtractedData[CurExtractedDataNo].on = CheckBoxViewControlShow->isChecked();
    // dprintf("CExtractedDataController::onViewControlShowCheckBoxClicked %d\n",
    //         1);
    reflectCurrentState();
    // dprintf("CExtractedDataController::onViewControlShowCheckBoxClicked %d\n",
    //         2);
    sendViewControlCurrentState();
    // dprintf("CExtractedDataController::onViewControlShowCheckBoxClicked %d\n",
    //         3);
}

void CExtractedDataController::onViewControlDataNoSpinBoxChanged()
{
    int value = SpinBoxViewControlDataNo->value();

    // set current no
    CurExtractedDataNo = value;

    reflectCurrentState();
    
    //setViewControlNodeList();
    
    // DATAFORMAT_REQUEST_EXTRACTEDDATA_POINTER sendData;
    // sendData.dataNo = value;
    // putData(COMID_REQUEST_EXTRACTEDDATA_POINTER,
    //         (char *)&sendData, sizeof(sendData));
    // data should be returned with EXTRACTEDDATA_POINTER message

}

void CExtractedDataController::updateViewControlTranslationXSlideBar()
{
    QString text = LineEditViewControlTranslationX->text();
    int value = text.toInt();
    VerticalSliderViewControlTranslationX->setValue(value);
    ExtractedData[CurExtractedDataNo].translate.x = value;
}

void CExtractedDataController::updateViewControlTranslationXLineEdit()
{
    int value = VerticalSliderViewControlTranslationX->value();
    LineEditViewControlTranslationX->setText(QString::number(value, 10));
    double scale = ExtractedData[CurExtractedDataNo].scale.x;
    dprintf("CExtractedDataController::updateViewControlTranslationXLineEdit " \
            "value = %d, scale = %f\n", value, scale);
    LineEditViewControlTranslationXum->setText(QString::number((int)(value*scale), 10));
}

void CExtractedDataController::updateViewControlTranslationYSlideBar()
{
    QString text = LineEditViewControlTranslationY->text();
    int value = text.toInt();
    VerticalSliderViewControlTranslationY->setValue(value);
    ExtractedData[CurExtractedDataNo].translate.y = value;
}

void CExtractedDataController::updateViewControlTranslationYLineEdit()
{
    int value = VerticalSliderViewControlTranslationY->value();
    LineEditViewControlTranslationY->setText(QString::number(value, 10));
    double scale = ExtractedData[CurExtractedDataNo].scale.y;
    LineEditViewControlTranslationYum->setText(QString::number((int)(value*scale), 10));
}

void CExtractedDataController::updateViewControlTranslationZSlideBar()
{
    QString text = LineEditViewControlTranslationZ->text();
    int value = text.toInt();
    VerticalSliderViewControlTranslationZ->setValue(value);
    ExtractedData[CurExtractedDataNo].translate.z = value;
}

void CExtractedDataController::updateViewControlTranslationZLineEdit()
{
    int value = VerticalSliderViewControlTranslationZ->value();
    LineEditViewControlTranslationZ->setText(QString::number(value, 10));
    double scale = ExtractedData[CurExtractedDataNo].scale.z;
    LineEditViewControlTranslationZum->setText(QString::number((int)(value*scale), 10));
}

void CExtractedDataController::updateViewControlPointerXSlideBar()
{
    QString text = LineEditViewControlPointerXum->text();
    int value = text.toDouble() * VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM;
    VerticalSliderViewControlPointerXum->setValue(value);
    sendViewControlPointer();
}

void CExtractedDataController::updateViewControlPointerXLineEdit()
{
    double value = VerticalSliderViewControlPointerXum->value()
        / (double)VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM;
    dprintf("CExtractedDataController::updateViewControlPointerXLineEdit " \
            "value = %f\n", value);
    LineEditViewControlPointerXum->setText(QString::number(value));
}

void CExtractedDataController::updateViewControlPointerYSlideBar()
{
    QString text = LineEditViewControlPointerYum->text();
    int value = text.toDouble() * VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM;
    VerticalSliderViewControlPointerYum->setValue(value);
    sendViewControlPointer();
}

void CExtractedDataController::updateViewControlPointerYLineEdit()
{
    double value = VerticalSliderViewControlPointerYum->value()
        / (double)VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM;
    dprintf("CExtractedDataController::updateViewControlPointerXLineEdit " \
            "value = %f\n", value);
    LineEditViewControlPointerYum->setText(QString::number(value));
}

void CExtractedDataController::updateViewControlPointerZSlideBar()
{
    QString text = LineEditViewControlPointerZum->text();
    int value = text.toDouble() * VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM;
    VerticalSliderViewControlPointerZum->setValue(value);
    sendViewControlPointer();
}

void CExtractedDataController::updateViewControlPointerZLineEdit()
{
    double value = VerticalSliderViewControlPointerZum->value()
        / (double)VIEW_CONTROL_POINTER_SLIDEBAR_POINT_PER_UM;
    dprintf("CExtractedDataController::updateViewControlPointerXLineEdit " \
            "value = %f\n", value);
    LineEditViewControlPointerZum->setText(QString::number(value));
}

void CExtractedDataController::sendViewControlPointer()
{
    dprintf("CExtractedDataController::sendViewControlPointer\n");
    DATAFORMAT_CHANGE_VIEW_POINTER_EXTRACTEDDATA sendData;
    sendData.x = VerticalSliderViewControlPointerXum->value();
    sendData.y = VerticalSliderViewControlPointerYum->value();
    sendData.z = VerticalSliderViewControlPointerZum->value();
    sendData.on = CheckBoxViewControlPointer->isChecked();

    dprintf("CExtractedDataController::sendViewControlPointer %d\n", 0);

    dprintf("CExtractedDataController::sendViewControlPointer " \
            "send pointer (%f, %f, %f) um, ",
            sendData.x, sendData.y, sendData.z);
    dprintf("CExtractedDataController::sendViewControlPointer " \
            "[%s]\n",
            sendData.on == true ? "ON" : "OFF");

    putData(COMID_CHANGE_VIEW_POINTER_EXTRACTEDDATA,
            (char *)&sendData, sizeof(sendData));
}

// void CExtractedDataController::updateViewControlRotationXSlideBar()
// {
//     QString text = LineEditViewControlRotationX->text();
//     int value = text.toInt() * ANGLE_DIV_NUM;
//     VerticalSliderViewControlRotationX->setValue(value);
// }

// void CExtractedDataController::updateViewControlRotationXLineEdit()
// {
//     int value = VerticalSliderViewControlRotationX->value();
//     LineEditViewControlRotationX->setText(
//         QString::number(value / ANGLE_DIV_NUM, 10));
// }

// void CExtractedDataController::updateViewControlRotationYSlideBar()
// {
//     QString text = LineEditViewControlRotationY->text();
//     int value = text.toInt() * ANGLE_DIV_NUM;
//     VerticalSliderViewControlRotationY->setValue(value);
// }

// void CExtractedDataController::updateViewControlRotationYLineEdit()
// {
//     int value = VerticalSliderViewControlRotationY->value();
//     LineEditViewControlRotationY->setText(
//         QString::number(value / ANGLE_DIV_NUM, 10));
// }

// void CExtractedDataController::updateViewControlRotationZSlideBar()
// {
//     QString text = LineEditViewControlRotationZ->text();
//     int value = text.toInt() * ANGLE_DIV_NUM;
//     VerticalSliderViewControlRotationZ->setValue(value);
// }

// void CExtractedDataController::updateViewControlRotationZLineEdit()
// {
//     int value = VerticalSliderViewControlRotationZ->value();
//     LineEditViewControlRotationZ->setText(
//         QString::number(value / ANGLE_DIV_NUM, 10));
// }

// void CExtractedDataController::setViewControlRotationXYPlane()
// {
//     VerticalSliderViewControlRotationX->setValue(
//         0 * ANGLE_DIV_NUM);
//     VerticalSliderViewControlRotationY->setValue(
//         0 * ANGLE_DIV_NUM);
//     VerticalSliderViewControlRotationZ->setValue(
//         0 * ANGLE_DIV_NUM);
// }

// void CExtractedDataController::setViewControlRotationYZPlane()
// {
//     VerticalSliderViewControlRotationX->setValue(
//         90 * ANGLE_DIV_NUM);
//     VerticalSliderViewControlRotationY->setValue(
//         180 * ANGLE_DIV_NUM);
//     VerticalSliderViewControlRotationZ->setValue(
//         90 * ANGLE_DIV_NUM);
// }

// void CExtractedDataController::setViewControlRotationZXPlane()
// {
//     VerticalSliderViewControlRotationX->setValue(
//         90 * ANGLE_DIV_NUM);
//     VerticalSliderViewControlRotationY->setValue(
//         90 * ANGLE_DIV_NUM);
//     VerticalSliderViewControlRotationZ->setValue(
//         0 * ANGLE_DIV_NUM);
// }


// void CExtractedDataController::sendViewControlRotation()
// {
//     if (ExtractedData[CurExtractedDataNo].ptr == NULL) {
//         printf("Extracted Image has not been loaded\n");
//         return;
//     }
//     DATAFORMAT_CHANGE_VIEW_ROTATION_EXTRACTEDDATA sendData;
//     sendData.rotx = VerticalSliderViewControlRotationX->value();
//     sendData.roty = VerticalSliderViewControlRotationY->value();
//     sendData.rotz = VerticalSliderViewControlRotationZ->value();
//     putData(COMID_CHANGE_VIEW_ROTATION_EXTRACTEDDATA,
//             (char *)&sendData, sizeof(sendData));
// }

void CExtractedDataController::setViewControlNodeList()
{
    dprintf("CExtractedDataController::setViewControlNodeList " \
            "\n");
    RodClusterList *clusterList
        = (RodClusterList *)ExtractedData[CurExtractedDataNo].ptr;

    dprintf("CExtractedDataController::setViewControlNodeList " \
            "clusterList[%d] = %p\n",
            CurExtractedDataNo,
            clusterList);

    if (clusterList == NULL) return;

    unsigned int nodeNum = clusterList->getClusterNum();

    dprintf("CExtractedDataController::setViewControlNodeList " \
            "nodeNum = %d\n", nodeNum);

    if (nodeNum == 0) return;
    
    QList<BTracingNode> nodeList;
    //nodeList.clear();

    // set NodeNo, Point
    for (unsigned int i = 0; i < nodeNum; i++) {
        RodCluster *curCluster = clusterList->getCluster(i);

        BTracingNode *curNode = new BTracingNode;

        curNode->NodeNo = curCluster->getClusterNo();
        curNode->Point.x = curCluster->getNode().x;
        curNode->Point.y = curCluster->getNode().y;
        curNode->Point.z = curCluster->getNode().z;
        curNode->Diam = curCluster->getDiam();

        if (curCluster->getParentNum() == 0) {
            curNode->ParentNo = -1;
        } else {
            curNode->ParentNo = curCluster->getParent(0)->getClusterNo();
        }

        //curNode->ChildrenNo.clear();
        for (unsigned int j = 0; j < curCluster->getChildNum(); j++) {
            RodCluster *curChild = curCluster->getChild(j);
            curNode->ChildrenNo.append(curChild->getClusterNo());
        }
        nodeList.append(*curNode);

        // dprintf("CExtractedDataController::setViewControlNodeList " \
        //         "[%d/%d] NodeNo =  %d, " \
        //         "Point (%f, %f, %f), " \
        //         "Diam = %f\n",
        //         i, nodeNum - 1, curNode->NodeNo,
        //         curNode->Point.x, curNode->Point.y, curNode->Point.z,
        //         curNode->Diam);
    }

    dprintf("CExtractedDataController::setViewControlNodeList " \
            "setNodeList... ");
    TracingData.setNodeList(&nodeList);
    dprintf("ok\n");
    //TableViewViewControlNodeList->setModel(&TracingData);
}

void CExtractedDataController::sendViewControlCurrentState()
{
    DATAFORMAT_SET_VIEW_EXTRACTEDDATA sendData;
    sendData.ptr = ExtractedData[CurExtractedDataNo].ptr;
    if (sendData.ptr == NULL) {
        return;
    }
    sendData.dataNo = CurExtractedDataNo;
    sendData.translate.x = ExtractedData[CurExtractedDataNo].translate.x;
    sendData.translate.y = ExtractedData[CurExtractedDataNo].translate.y;
    sendData.translate.z = ExtractedData[CurExtractedDataNo].translate.z;
    sendData.on = ExtractedData[CurExtractedDataNo].on;
    sendData.draw = true;
    if (sendData.on == true) {
        QModelIndex selectedIndex
            = TableViewViewControlNodeList->currentIndex();
        QModelIndex currentNodeNoIndex
            = TracingData.index(selectedIndex.row(), 0);
        // dprintf("CExtractedDataController::sendViewControlCurrentState " \
        //         "selectedIndex (%d, %d), " \
        //         "currentNodeNoIndex (%d, %d)\n",
        //         selectedIndex.row(), selectedIndex.column(),
        //         currentNodeNoIndex.row(), currentNodeNoIndex.column());
        sendData.selectedNodeNo = TracingData.data(currentNodeNoIndex).toInt();
    } else {
        sendData.selectedNodeNo = -1;
    }

    dprintf("CExtractedDataController::sendViewControlCurrentState " \
            "ptr = %p, " \
            "translation (%d, %d, %d) voxel, " \
            "[%s], " \
            "SelectedNodeNo = %d\n",
            sendData.ptr,
            sendData.translate.x, sendData.translate.y, sendData.translate.z,
            sendData.on ? "ON" : "OFF",
            sendData.selectedNodeNo);

    putData(COMID_SET_VIEW_EXTRACTEDDATA, (char *)&sendData, sizeof(sendData));
}


//------------------------------------------------------------------------------
// Properties
//------------------------------------------------------------------------------
void CExtractedDataController::updateProperties()
{
}

void CExtractedDataController::showEvent(QShowEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_EXTRACTEDDATACONTROLLER;
    sendData.show = this->isVisible();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void CExtractedDataController::hideEvent(QHideEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_EXTRACTEDDATACONTROLLER;
    sendData.show = this->isVisible();
    sendData.minimized = this->isMinimized();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

void CExtractedDataController::closeEvent(QCloseEvent *event)
{
    DATAFORMAT_WINDOW_STATE_CHANGED sendData;
    sendData.windowID = WINID_EXTRACTEDDATACONTROLLER;
    sendData.show = this->isVisible();
    putData(COMID_WINDOW_STATE_CHANGED,
            (char *)&sendData, sizeof(sendData));
}

//------------------------------------------------------------------------------
// Terminal
//------------------------------------------------------------------------------
void CExtractedDataController::procedure(int ID, char *data, int byte)
{
	switch (ID)
        {
        case COMID_FINISHED_EXTRACTION: {
            // !! this massega may be passed from another thread
            DATAFORMAT_FINISHED_EXTRACTION *recvData
                = (DATAFORMAT_FINISHED_EXTRACTION *)data;

            // dataNo : stack image #
            // targetNo : extracted data #
            dprintf("CExtractedDataController::procedure " \
                    "got COMID_FINISHED_EXTRACTION\n");
            dprintf("CExtractedDataController::procedure " \
                    "ptr = %p, dataNo = %d, targetNo = %d\n",
                    recvData->ptr, recvData->dataNo, recvData->targetNo);

            CurExtractedDataNo = recvData->targetNo;

            // ptr will be passed from MExtractedData
            // with STOCK_EXTRACTED_DATA_OK message below

            //     ExtractedData[CurExtractedDataNo].ptr = ###
            ExtractedData[CurExtractedDataNo].scale.x = recvData->scale.x;
            ExtractedData[CurExtractedDataNo].scale.y = recvData->scale.y;
            ExtractedData[CurExtractedDataNo].scale.z = recvData->scale.z;
            ExtractedData[CurExtractedDataNo].on = false;

            DATAFORMAT_STORE_EXTRACTEDDATA sendData;
            sendData.dataNo = recvData->targetNo;
            sendData.ptr = recvData->ptr;
            putData(COMID_STORE_EXTRACTEDDATA,
                    (char *)&sendData, sizeof(sendData));

            return;
        } // COMID_FINISHED_EXTRACTION

        case COMID_STORE_EXTRACTEDDATA_OK: {
            // !! this message may be passed from another thread
            DATAFORMAT_STORE_EXTRACTEDDATA_OK *recvData
                = (DATAFORMAT_STORE_EXTRACTEDDATA_OK *)data;

            dprintf("CExtractedDataController::procedure " \
                    "got STORE_EXTRACTEDDATA_OK\n");
            dprintf("CExtractedDataController::procedure " \
                    "dataNo = %d, ptr = %p\n",
                    recvData->dataNo,
                    recvData->ptr);

            //CurExtractedDataNo = recvData->dataNo;
            ExtractedData[recvData->dataNo].ptr = recvData->ptr;

            /*
            DATAFORMAT_SET_VIEW_EXTRACTEDDATA sendData2;
            sendData2.ptr = ExtractedData[CurExtractedDataNo].ptr;
            sendData2.dataNo = CurExtractedDataNo;
            sendData2.translate.x = ExtractedData[CurExtractedDataNo].translate.x;
            sendData2.translate.y = ExtractedData[CurExtractedDataNo].translate.y;
            sendData2.translate.z = ExtractedData[CurExtractedDataNo].translate.z;
            sendData2.on = ExtractedData[CurExtractedDataNo].on;
            sendData2.draw = false;
            putData(COMID_SET_VIEW_EXTRACTEDDATA, (char *)&sendData2, sizeof(sendData2));
            */
            ExtractedData[recvData->dataNo].on = true;

            //reflectCurrentState();
            //emit extractionFinished();
            
            return;
        } // COMID_STORE_EXTRACTEDDATA_OK

        case COMID_LOAD_EXTRACTEDDATA_OK: {
            DATAFORMAT_LOAD_EXTRACTEDDATA_OK *recvData
                = (DATAFORMAT_LOAD_EXTRACTEDDATA_OK *)data;
            
            dprintf("CExtractedDataController::procedure " \
                    "got COMID_LOAD_EXTRACTEDDATA_OK\n");
            dprintf("CExtractedDataController::procedure " \
                    "ptr = %p, dataNo = %d, scale (%f, %f, %f)\n",
                    recvData->ptr, recvData->dataNo,
                    recvData->scale.x, recvData->scale.y, recvData->scale.z);

            CurExtractedDataNo = recvData->dataNo;

            ExtractedData[CurExtractedDataNo].ptr = recvData->ptr;
            ExtractedData[CurExtractedDataNo].scale.x = recvData->scale.x;
            ExtractedData[CurExtractedDataNo].scale.y = recvData->scale.y;
            ExtractedData[CurExtractedDataNo].scale.z = recvData->scale.z;
            ExtractedData[CurExtractedDataNo].on = true;

            sendViewControlCurrentState();

            return;
        } // COMID_LOAD_EXTRACTEDDATA_OK

        default:
            return;
    }
}
