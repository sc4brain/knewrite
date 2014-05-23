
#include <QtGui>
#include "VShapeView.h"

#include "CObjectCommunicatorID.h"
#include "BCommon.h"

#ifndef ASAFEDELETE
#define ASAFEDELETE(p) if ((p) != NULL) { delete[] (p); (p) = NULL; }
#endif

VShapeView::VShapeView(QWidget *parent) : QWidget(parent)
{
	Data = NULL;
	DataLength = 0;

	rotateThetaX = 0;
	rotateThetaY = 0;
	rotateThetaZ = 0;

	isMouseDown = false;
	rotStartPoint = QPointF(0, 0);

        //setData(LENGTH, NULL);
}

VShapeView::~VShapeView()
{
    ASAFEDELETE(Data);
	//this->parent()->~QObject();
}

void VShapeView::paintEvent(QPaintEvent */*event*/)
{
	static QPointF AxisX[2] = { QPointF(-200, 0), QPointF(200, 0) };
	static QPointF AxisY[2] = { QPointF(0, -200), QPointF(0, 200) };


	QMatrix4x4 translationMatrix(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

	QMatrix4x4 rotCombMatrix = rotationMatrixZ
			* rotationMatrixY
			* rotationMatrixX;
	QMatrix4x4 combMatrix = translationMatrix * rotCombMatrix;

	QPainter painter(this);

	painter.setWindow(-300, -300, 600, 600);
	painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

	painter.setRenderHint(QPainter::Antialiasing, true);

	QVector4D pointFrom;
	if (Data != NULL) {
		pointFrom = combMatrix * Data[0];
	} else {
		pointFrom = QVector4D(0, 0, 0, 0);
	}
	QVector4D pointTo;

	for (int i = 1; i < DataLength - 1; i++) {
		pointTo = combMatrix * Data[i];
		painter.drawPoint(pointTo.toPoint());
		//painter.drawLine(pointFrom.toPoint(), pointTo.toPoint());
		//pointFrom = pointTo;
	}

	painter.setPen(QPen(Qt::gray, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
	painter.drawLine(rotCombMatrix * AxisX[0], rotCombMatrix * AxisX[1]);
	painter.drawLine(rotCombMatrix * AxisY[0], rotCombMatrix * AxisY[1]);

	//painter.restore();

	//painter.setBrush(QBrush(Qt::black, Qt::Dense3Pattern));
}

void VShapeView::setRotTheta(qreal ThetaX, qreal ThetaY, qreal ThetaZ)
{
	rotateThetaX = ThetaX;
	rotateThetaY = ThetaY;
	rotateThetaZ = ThetaZ;
}

void VShapeView::setData(int length, QVector4D *in_data)
{
	DataLength = length;
    ASAFEDELETE(Data);
	Data = new QVector4D[DataLength];

	QVector4D max, min, mean;

	max = min = in_data[0];
	for (int i = 1; i < length; i++) {
		QVector4D temp = in_data[i];
		if (max.x() < temp.x()) max.setX(temp.x());
		if (max.y() < temp.y()) max.setY(temp.y());
		if (max.z() < temp.z()) max.setZ(temp.z());
		if (min.x() > temp.x()) min.setX(temp.x());
		if (min.y() > temp.y()) min.setY(temp.y());
		if (min.z() > temp.z()) min.setZ(temp.z());
	}
	mean = max/2 + min/2;
	mean.setW(0);

	for (int i = 0; i < DataLength; i++) {
        QVector4D inputVector = in_data[i];
		Data[i].setX(Scale.x * (inputVector.x() - mean.x()));
		Data[i].setY(Scale.y * (inputVector.y() - mean.y()));
		Data[i].setZ(Scale.z * (inputVector.z() - mean.z()));
        Data[i].setW(0);
	}

}

void VShapeView::setData(const QList<QVector4D> list)
{
    dprintf("VShapeView::setData list.length() = %d\n", list.length());
    DataLength = list.length();
    ASAFEDELETE(Data);
    try {
        Data = new QVector4D[DataLength];
    } catch (std::bad_alloc &ba) {
        fprintf(stderr, "VShapeView::setData caught bad_alloc : Data\n");
        exit(1);
    }

	QVector4D max, min, mean;
	max = min = list.value(0);
	for (int i = 1; i < DataLength; i++) {
		QVector4D temp = list.value(i);
		if (max.x() < temp.x()) max.setX(temp.x());
		if (max.y() < temp.y()) max.setY(temp.y());
		if (max.z() < temp.z()) max.setZ(temp.z());
		if (min.x() > temp.x()) min.setX(temp.x());
		if (min.y() > temp.y()) min.setY(temp.y());
		if (min.z() > temp.z()) min.setZ(temp.z());
	}
	mean = max/2 + min/2;
	mean.setW(0);

	for (int i = 0; i < DataLength; i++) {
		Data[i].setX(Scale.x * (list.value(i).x() - mean.x()));
		Data[i].setY(Scale.y * (list.value(i).y() - mean.y()));
		Data[i].setZ(Scale.z * (list.value(i).z() - mean.z()));
        Data[i].setW(0);
	}
}

void VShapeView::updatePix()
{
}

void VShapeView::rotate(qreal angleX, qreal angleY, qreal angleZ)
{
	setRotTheta(angleX, angleY, angleZ);
	update();
}

void VShapeView::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton) {
		isMouseDown = true;
		rotStartPoint = event->posF();
	}
}

void VShapeView::mouseMoveEvent(QMouseEvent *event)
{
	static double rotCoef = 0.2;
	if (isMouseDown) {
		QPointF tempPoint = event->posF();
		rotateThetaX += 3.1415926535 / 180 * (tempPoint.x() - rotStartPoint.x()) * rotCoef;
		rotateThetaY += 3.1415926535 / 180 * (tempPoint.y() - rotStartPoint.y()) * rotCoef;
		setRotMatrix();
		update();
		rotStartPoint = tempPoint;
		//updatePix();
	}
}

void VShapeView::mouseReleaseEvent(QMouseEvent *event)
{
	isMouseDown = false;
}

void VShapeView::keyPressEvent(QKeyEvent *event)
{
	switch (event->key()) {
		default:
			QWidget::keyPressEvent(event);
	}
}

void VShapeView::setRotMatrix()
{

	qreal theta = rotateThetaX;
	qreal SinTheta = sin(theta);
	qreal CosTheta = cos(theta);

	rotationMatrixX = QMatrix4x4(
			CosTheta, -SinTheta, 0, 0,
			SinTheta, CosTheta, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);

	theta = rotateThetaY;
	SinTheta = sin(theta);
	CosTheta = cos(theta);

	rotationMatrixY = QMatrix4x4(
			1, 0, 0, 0,
			0, CosTheta, -SinTheta, 0,
			0, SinTheta, CosTheta, 0,
			0, 0, 0, 1);

	theta = rotateThetaZ;
	SinTheta = sin(theta);
	CosTheta = cos(theta);

	rotationMatrixZ = QMatrix4x4(
			CosTheta, 0, SinTheta, 0,
			0, 1, 0, 0,
			-SinTheta, 0, CosTheta, 0,
			0, 0, 0, 1);
}

void VShapeView::procedure(int ID, char *data, int byte)
{

    switch (ID) {
        case COMID_SET_VIEW_STACKIMAGE: {
            QList<QVector4D> list;
            DATAFORMAT_SET_VIEW_STACKIMAGE *recvData
                = (DATAFORMAT_SET_VIEW_STACKIMAGE *)data;
            dputs("VShapeView::procedure got FILELOADED_STACKIMAGE");
            dprintf("VShapeView::procedure data = %p, size = %d\n",
                    data, byte);
            dprintf("VShapeView::procedure ptr = %p," \
                    " size.(x, y, z) = (%d, %d, %d)\n",
                    recvData->ptr,
                    recvData->size.x, recvData->size.y, recvData->size.z);
            for (int k = 0; k < recvData->size.z; k++) {
                int pageStep = recvData->size.x * recvData->size.y * k;
                for (int j = 0; j < recvData->size.y; j++) {
                    int step = pageStep + recvData->size.x * j;
                    for (int i = 0; i < recvData->size.x; i++) {
                        if (100 < recvData->ptr[step + i]) {
                            list.append(QVector4D(i, j, k, 0));
                        }
                    }
                }
            }
            Scale.x = recvData->scale.x;
            Scale.y = recvData->scale.y;
            Scale.z = recvData->scale.z;
            dputs("VShapeView::procedure receive ok");
            setData(list);
            return;
        }
        default:
            return;
    }
}
