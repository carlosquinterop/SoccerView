#include "SoccerViewer.h"

SoccerViewer::SoccerViewer(int camId)
{
  
    layout = new QGridLayout();
    flagLayout = new QGridLayout();
    mainLayout = new QGridLayout();
    stadiumLayout = new QGridLayout();
    QWidget *window = new QWidget(); 
    startCountingButton = new QPushButton("Start");
    stopCountingButton = new QPushButton("Stop");
    clock = new DigitalClock();
    camThread = new cameraThread();
    teamAComboBox = new QComboBox();
    teamBComboBox = new QComboBox();
    stadiumComboBox = new QComboBox();
    teamAFlagLabel = new QLabel();
    teamBFlagLabel = new QLabel();
    stadiumLabel = new QLabel();
    teamAFlagPixmap = new QPixmap();
    teamBFlagPixmap = new QPixmap();
    stadiumPixmap = new QPixmap();
    gpsProcess = new QProcess();
        
    teamAComboBox->addItem("Colombia");
    teamAComboBox->addItem("Germany");
    teamAComboBox->addItem("Russia");
    teamAComboBox->addItem("Brazil");
    teamAComboBox->addItem("Spain");
    teamAComboBox->addItem("Netherlands");
    teamAComboBox->setCurrentIndex(0);
    teamAFlagPixmap->load(COLOMBIA);
    teamAFlagLabel->setPixmap(*teamAFlagPixmap);
    
    teamBComboBox->addItem("Colombia");
    teamBComboBox->addItem("Germany");
    teamBComboBox->addItem("Russia");
    teamBComboBox->addItem("Brazil");
    teamBComboBox->addItem("Spain");
    teamBComboBox->addItem("Netherlands");
    teamBComboBox->setCurrentIndex(3);
    teamBFlagPixmap->load(BRAZIL);
    teamBFlagLabel->setPixmap(*teamBFlagPixmap);
    
    stadiumComboBox->addItem("Luzhniki Stadium (Moscow)");
    stadiumComboBox->addItem("Saint Petersburg Stadium (Saint Petersburg)");
    stadiumComboBox->addItem("Fisht Stadium (Sochi)");
    stadiumComboBox->addItem("Ekaterinburg Arena (Ekaterinburg)");
    stadiumComboBox->addItem("Kazan Arena (Kazan)");
    stadiumComboBox->setCurrentIndex(0);
    stadiumPixmap->load(MOSCOW);
    stadiumLabel->setPixmap(*stadiumPixmap);
    
    mainLayout->addLayout(layout, 0, 0);
    mainLayout->addLayout(flagLayout, 1, 0);
    mainLayout->addLayout(stadiumLayout, 2, 0);
    
    layout->addWidget(startCountingButton, 0, 0);
    layout->addWidget(stopCountingButton, 1, 0);
    layout->addWidget(clock, 2, 0);
    
    flagLayout->addWidget(new QLabel("Team A"), 0, 0);
    flagLayout->addWidget(new QLabel("Team B"), 0, 1);
    flagLayout->addWidget(teamAComboBox, 1, 0);
    flagLayout->addWidget(teamBComboBox, 1, 1);
    flagLayout->addWidget(teamAFlagLabel, 2, 0);
    flagLayout->addWidget(teamBFlagLabel, 2, 1);
    
    stadiumLayout->addWidget(new QLabel("Stadium"), 0, 0);
    stadiumLayout->addWidget(stadiumComboBox, 1, 0);
    stadiumLayout->addWidget(stadiumLabel, 2, 0);
    
    window->setLayout(mainLayout);
    setCentralWidget( window );
    
    camThread->setWorkingThread(true);
    camThread->setCamId(camId);
    camThread->start();
    namedWindow("Real time video", WINDOW_NORMAL);
    resizeWindow("Real time video", 100, 200);
    QDesktopWidget dw;
    
    int x=dw.width()*0.3;
    int y=dw.height()*0.99;
    window->setFixedSize(x,y);
    
    stopCountingButton->setEnabled(false);
     
    program = "bladeRF-cli";
    fileName = "scripts/bladerf_Luzhniki.script";
    QStringList arguments;
    arguments << "-s" << fileName;
    gpsProcess->start(program, arguments);
    
    connect(startCountingButton, SIGNAL(clicked()), this, SLOT(showClockButtonPressed()));
    connect(stopCountingButton, SIGNAL(clicked()), this, SLOT(stopCountingButtonPressed()));
    connect(teamAComboBox, SIGNAL(activated(int)), this, SLOT(udpateFlagSlot(int)));
    connect(teamBComboBox, SIGNAL(activated(int)), this, SLOT(udpateFlagSlot(int)));
    connect(stadiumComboBox, SIGNAL(activated(int)), this, SLOT(updateStadiumSlot(int)));
    connect(gpsProcess, SIGNAL(readyReadStandardOutput()),this, SLOT(readyReadStandardOutput()));
}

SoccerViewer::~SoccerViewer()
{
  
}

void SoccerViewer::showClockButtonPressed()
{
    clock->startCounting();
    stopCountingButton->setEnabled(true);
    startCountingButton->setEnabled(false);
}

void SoccerViewer::stopCountingButtonPressed()
{
    clock->stopCounting();
    stopCountingButton->setEnabled(false);
    startCountingButton->setEnabled(true);
}

void SoccerViewer::udpateFlagSlot(int index)
{

    if(teamAComboBox->currentText() == "Colombia")
      teamAFlagPixmap->load(COLOMBIA);
    else if(teamAComboBox->currentText() == "Germany")
      teamAFlagPixmap->load(GERMANY); 
    else if(teamAComboBox->currentText() == "Russia")
      teamAFlagPixmap->load(RUSSIA);   
    else if(teamAComboBox->currentText() == "Brazil")
      teamAFlagPixmap->load(BRAZIL);   
    else if(teamAComboBox->currentText() == "Spain")
      teamAFlagPixmap->load(SPAIN);   
    else if(teamAComboBox->currentText() == "Netherlands")
      teamAFlagPixmap->load(NETHERLANDS); 
    
      teamAFlagLabel->setPixmap(*teamAFlagPixmap);
   
    
     if(teamBComboBox->currentText() == "Colombia")
      teamBFlagPixmap->load(COLOMBIA);
    else if(teamBComboBox->currentText() == "Germany")
      teamBFlagPixmap->load(GERMANY); 
    else if(teamBComboBox->currentText() == "Russia")
      teamBFlagPixmap->load(RUSSIA);   
    else if(teamBComboBox->currentText() == "Brazil")
      teamBFlagPixmap->load(BRAZIL);   
    else if(teamBComboBox->currentText() == "Spain")
      teamBFlagPixmap->load(SPAIN);   
    else if(teamBComboBox->currentText() == "Netherlands")
      teamBFlagPixmap->load(NETHERLANDS); 
    
      teamBFlagLabel->setPixmap(*teamBFlagPixmap);
}

void SoccerViewer::updateStadiumSlot(int index)
{  
  
    gpsProcess->terminate();
    if(stadiumComboBox->currentText() == "Luzhniki Stadium (Moscow)")
    {
      stadiumPixmap->load(MOSCOW);
      fileName = "scripts/bladerf_Luzhniki.script";
    }
    else if(stadiumComboBox->currentText() == "Saint Petersburg Stadium (Saint Petersburg)")
    {
      stadiumPixmap->load(SAINTPETERSBURG);
      fileName = "scripts/bladerf_StPetersburg.script";
    }
    else if(stadiumComboBox->currentText() == "Fisht Stadium (Sochi)")
    {
      stadiumPixmap->load(SOCHI);
      fileName = "scripts/bladerf_Fisht.script";
    }
    else if(stadiumComboBox->currentText() == "Ekaterinburg Arena (Ekaterinburg)")
    {
      stadiumPixmap->load(EKATERINBURG);
      fileName = "scripts/bladerf_Ekaterinburg.script";
    }
    else if(stadiumComboBox->currentText() == "Kazan Arena (Kazan)")
    {
      stadiumPixmap->load(KAZAN);
      fileName = "scripts/bladerf_Kazan.script";
    }
    stadiumLabel->setPixmap(*stadiumPixmap);
   
    QStringList arguments;
    arguments << "-s" << fileName;
    gpsProcess->start(program, arguments);
}


void SoccerViewer::readyReadStandardOutput()
{
    mOutputString = gpsProcess->readAllStandardOutput();
    cout << mOutputString.toStdString() << endl;
}
