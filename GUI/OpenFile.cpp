#include"OpenFile.hpp"

namespace GUI{
  OpenFile::OpenFile(MyWidget *w, CacheFifo<QImage, QString, Loader<QString, QImage, QFile> > c):_widget(w), _cache(c){}
  
  OpenFile::~OpenFile(){}
  
  void OpenFile::openFileChooser(){
    QString file = QFileDialog::getOpenFileName(".", "*");
    if( file != 0 ){
      _widget->add(file);
      _widget->paint(*_cache.getImageObject(new QString(file)));
    }
  }
}



