#include <QtWidgets/QApplication>
#include "SoccerViewer.h"


int main(int argc, char** argv)
{
    QApplication app(argc, argv);
    
    if (argc == 2)
    {
      
      SoccerViewer soccerviewer(atoi(argv[1]));
      soccerviewer.show();
      return app.exec();
    }
    else
    {
      printf("Error: Incorrect number of parameters\nUsage: ./basicmotion camId\n");
      return 1;
    }
    
    
}
