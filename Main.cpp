#include "MyApplication.hpp"

using namespace GUI;

int main(int argc, char *argv[]){
  Loader<QString, QImage, QFile> l;
  
  CacheFifo<QImage, QString, Loader<QString, QImage, QFile> > cache =
    CacheFifo<QImage, QString, Loader<QString, QImage, QFile> >(l, 700000, 3);
  
  // Main Application
  QApplication app(argc, argv);
  MyApplication application(app, cache);
  
  return app.exec();
}
