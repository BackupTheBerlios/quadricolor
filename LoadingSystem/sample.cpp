#include <stdio.h>
#include <iostream>
#include <qstring.h>
#include "Loader.hpp"

using namespace std;
using namespace loader;

int main(int argc, char ** argv){
  Loader<QString> L;
  //string k = string("Pictures/feyenord.jpg");
  QString k = QString(argv[1]);
  cout << k << endl;
  
  try{
    QImage pic = L.getObject(k);
    QString tmp = QString("Pictures/feyenord.jpg");
    int size = L.getSize(k);
    cout << "The size of the image  is " << size << endl;
    //pic.display();
  }catch( ImageNotFoundException &e){ cout << e.getMessage() << endl;}
  
}
