#include <qapplication.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qfiledialog.h>
#include "OpenFile.hpp"

int main(int argc, char *argv[]){
  // Main Application
  QApplication app(argc, argv);
  
  // Creation of the main widget
  QWidget *widget = new QWidget();
  widget->setGeometry(400, 300, 170, 110);
  
  // Creation of an instance of open/save object
  OpenFile *opener = new OpenFile();
  
  // Creation of the menu bar
  QMenuBar *menuBar = new QMenuBar(widget); 
  
  // Creation of the file popup menu
  QPopupMenu *file = new QPopupMenu();
  file->insertItem("&Open", opener, SLOT(openFileChooser()));
  file->insertItem("&Exit", &app, SLOT(quit()));

  // Insertion of the popup menus in the menuBar
  menuBar->insertItem("&File", file);
  
  //QObject::connect(file, SIGNAL(activated(int)), &app, SLOT(quit()));

  // Display
  app.setMainWidget(widget);
  widget->show();

  return app.exec();
}
