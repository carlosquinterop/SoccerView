#ifndef DigitalClock_H
#define DigitalClock_H


#include <QLCDNumber>
#include <QTimer>
#include <QTime>

#define GAMETIME 90

class DigitalClock : public QLCDNumber
{
    Q_OBJECT

public:
    DigitalClock(QWidget *parent = 0);
    void startCounting();
    void stopCounting();

private:
  QTime t;
  QTimer *timer;
    
private slots:
    void showTime();
    
};

#endif