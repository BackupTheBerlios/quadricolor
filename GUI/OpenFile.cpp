#include"OpenFile.hpp"
#include <stdio.h>
#include <iostream>

using namespace std;

OpenFile::OpenFile(MyWidget *w):widget(w){
  cout << "Constructeur de OpenFile" << endl; 
}

OpenFile::~OpenFile(){
  cout << "Destructeur de OpenFile" << endl; 
}
  
void OpenFile::openFileChooser(){
  QString file = QFileDialog::getOpenFileName(".", "*");
  widget->add(file);
}




