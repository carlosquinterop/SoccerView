#include "DigitalClock.h"

DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent)
{
    setSegmentStyle(Filled);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    QString text = QString::number(GAMETIME);
    display(text);
}

void DigitalClock::startCounting()
{
    timer->start(1000);
    t.start();
}

void DigitalClock::stopCounting()
{
    timer->stop();
}

void DigitalClock::showTime()
{
    //QTime time = QTime::currentTime();
    int remainingTime = GAMETIME - t.elapsed()/1000;
    QString text = QString::number(remainingTime);
    /*if ((t.second() % 2) == 0)
        text[2] = ' ';*/
    display(text);
    if (remainingTime == 0)
      timer->stop();
}