#ifndef ___C_TIMER_H___
#define ___C_TIMER_H___

#include <QDialog>

#include <QTime>
#include <QTimer>
#include <QMutex>

#include "CTimerDialog.h"

class CTimer : public QDialog, public Ui::TimerDialog
{
    Q_OBJECT

 public:
    CTimer(QWidget *parent = 0);

 protected slots:
    void updateTime();
    void onStartStopButtonClicked();
    void onClearButtonClicked();
    void onSaveButtonClicked();

 protected:
    QTimer Timer;
    QMutex mutex;
    QTime CurrentTime;
    int ElapsedTimeBuf;
    bool started;
};

#endif//___C_TIMER_H___
