#ifndef SoccerViewer_H
#define SoccerViewer_H

#include <QMainWindow>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QAction>
#include "cameraThread.h"
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QPixmap>

#include <QDesktopWidget>
#include "DigitalClock.h"
#include <QProcess>

#define COLOMBIA "img/colombiaFlag"
#define GERMANY "img/germanyFlag"
#define RUSSIA "img/russiaFlag"
#define BRAZIL "img/brazilFlag"
#define SPAIN "img/spainFlag"
#define NETHERLANDS "img/netherlandsFlag"

#define MOSCOW "img/luzhnikiStadium" 
#define SAINTPETERSBURG "img/stpetersburgnew"
#define SOCHI "img/fisht"
#define EKATERINBURG "img/ekaterinburgarena"
#define KAZAN "img/kazan"

class SoccerViewer : public QMainWindow
{
    Q_OBJECT

public:
    SoccerViewer(int camId);
    virtual ~SoccerViewer();
    
private:
    cameraThread *camThread;
    QPushButton *startCountingButton, *stopCountingButton;
    QGridLayout *layout, *flagLayout, *stadiumLayout, *mainLayout;
    DigitalClock *clock;
    QComboBox *teamAComboBox, *teamBComboBox, *stadiumComboBox;
    QPixmap *teamAFlagPixmap, *teamBFlagPixmap, *stadiumPixmap;
    QLabel *teamAFlagLabel, *teamBFlagLabel, *stadiumLabel;
    QProcess *gpsProcess;
    QString fileName;
    QString program;
    QString mOutputString;
    
private slots:
    void showClockButtonPressed();
    void stopCountingButtonPressed();
    void udpateFlagSlot(int index);
    void updateStadiumSlot(int index);
    void readyReadStandardOutput();
};

#endif // SoccerViewer_H
