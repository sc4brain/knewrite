#ifndef ___V_SHAPE_VIEW_H___
#define ___V_SHAPE_VIEW_H___

//#include <QWidget>

#include <QMap>
#include <QPixmap>
#include <QVector>
#include <QWidget>
#include <QMatrix4x4>
#include <QList>
#include "CObjectCommunicator.h"

class QVector4D;
/*

class QMap;
class QPixmap;
class QVector4D;
class QWidget;
class QMatrix4x4;
class qreal;
*/
class VShapeView : public QWidget, public BTerminal
{
	Q_OBJECT

public:
	VShapeView(QWidget *parent = 0);
	~VShapeView(void);

	void setRotTheta(qreal ThetaX, qreal ThetaY, qreal ThetaZ);

	void setStackImage(int length, QVector4D *data);
	void setExtractionData(int length, QVector4D *data);
	void setData(int length, QVector4D *data);
    void setData(const QList<QVector4D> list);

protected:
	void paintEvent(QPaintEvent *event);
	void updatePix();

	//void resizeEvent(QResizeEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);
	//void wheelEvent(QWheelEvent *event);

	void setRotMatrix(void);

    void procedure(int ID, char *data, int byte);

public slots:
	void rotate(qreal angleX, qreal angleY, qreal angleZ);

protected:
	QVector4D *Data;
	int DataLength;
    struct {
        qreal x;
        qreal y;
        qreal z;
    } Scale;

	qreal rotateThetaX;
	qreal rotateThetaY;
	qreal rotateThetaZ;

	QMatrix4x4 rotationMatrixX;
	QMatrix4x4 rotationMatrixY;
	QMatrix4x4 rotationMatrixZ;

	bool isMouseDown;
	QPointF rotStartPoint;
    
};

#endif//___V_SHAPE_VIEW_H___
