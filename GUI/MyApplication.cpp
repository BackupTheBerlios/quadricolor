#include "MyApplication.hpp"

namespace GUI{
  MyApplication::MyApplication(QApplication &_app, CacheFifo<QImage, QString, Loader<QString, QImage, QFile> > c):_cache(c){
    QListBox *_listBox;
    MyWidget *_widget;
    OpenFile *_opener;
    QMenuBar *_menuBar;
    QPopupMenu *_file;
  
    _listBox = new QListBox(0);
    _listBox->setFocusPolicy( QWidget::StrongFocus );
    
    // Creation of the main widget
    _widget = new MyWidget(_listBox, _cache);
  
    // Creation of an instance of open/save object
    _opener = new OpenFile(_widget, _cache);
  
    // Creation of the menu bar
    _menuBar = new QMenuBar(_widget); 
  
    // Creation of the file popup menu
    _file = new QPopupMenu();
    _file->insertItem("&Open", _opener, SLOT(openFileChooser()));
    _file->insertItem("&Exit", &_app, SLOT(quit()));

    // Insertion of the popup menus in the menuBar
    _menuBar->insertItem("&File", _file);
    
    // Display
    _app.setMainWidget(_widget);
    _widget->show();
  }

  MyApplication::~MyApplication(){}
}



