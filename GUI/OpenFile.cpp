#include"OpenFile.hpp"

namespace GUI{
  OpenFile::OpenFile(MyWidget *w):widget(w){}
  
  OpenFile::~OpenFile(){}
  
  void OpenFile::openFileChooser(){
    QString file = QFileDialog::getOpenFileName(".", "*");
    widget->add(file);
  }
}



