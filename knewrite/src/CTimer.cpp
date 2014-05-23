
#include <QtGui>
#include "CTimer.h"

CTimer::CTimer(QWidget *parent) : QDialog(parent)
{
    setupUi(this);

    started = false;

    LcdNumber->display(QString("00:00:00"));

    connect(PushButtonStartStop, SIGNAL(clicked()),
            this, SLOT(onStartStopButtonClicked()));
    connect(PushButtonClear, SIGNAL(clicked()),
            this, SLOT(onClearButtonClicked()));
    connect(PushButtonSave, SIGNAL(clicked()),
            this, SLOT(onSaveButtonClicked()));

    connect(&Timer, SIGNAL(timeout()),
            this, SLOT(updateTime()));
}

void CTimer::updateTime()
{
    mutex.lock();
    int elapsed = ElapsedTimeBuf + CurrentTime.elapsed();
    mutex.unlock();
    int ms = elapsed % 1000;
    elapsed /= 1000;
    int s = elapsed % 60;
    elapsed /= 60;
    int m = elapsed % 60;
    elapsed /= 60;
    int h = elapsed;
    QTime tempTime(h, m, s, ms);
    LcdNumber->display(tempTime.toString("hh:mm:ss"));   
}

void CTimer::onStartStopButtonClicked()
{
    if (started) {
        mutex.lock();
        ElapsedTimeBuf += CurrentTime.elapsed();
        started = false;
        mutex.unlock();
        Timer.stop();
        PushButtonStartStop->setText(QString("Start"));
    } else {
        mutex.lock();
        CurrentTime.start();
        started = true;
        mutex.unlock();
        Timer.start(1000);
        PushButtonStartStop->setText(QString("Pause"));
    }
}

void CTimer::onClearButtonClicked()
{
    mutex.lock();
    ElapsedTimeBuf = 0;
    CurrentTime.restart();
    mutex.unlock();
    updateTime();
}

void CTimer::onSaveButtonClicked()
{
    QFile file("TimerResult.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    
    mutex.lock();
    int elapsed = ElapsedTimeBuf + CurrentTime.elapsed();
    mutex.unlock();

    QTextStream out(&file);

    out << elapsed/3600000. << " (h)\n";
    out << elapsed/60000. << " (m)\n";
    out << elapsed/1000. << " (s)\n";
    out << elapsed << " (ms)\n";

    int ms = elapsed % 1000;
    elapsed /= 1000;
    int s = elapsed % 60;
    elapsed /= 60;
    int m = elapsed % 60;
    elapsed /= 60;
    int h = elapsed;

    out << "\nh:m:s:ms\n";
    out << h << ":" << m << ":" << s << ":" << ms << "\n\n";

    file.close();
}
