#include"OpenFile.hpp"

using namespace std;

OpenFile::OpenFile(){
  cout << "Constructeur de OpenFile" << endl; 
}

OpenFile::~OpenFile(){
  cout << "Destructeur de OpenFile" << endl; 
}
  
QString OpenFile::openFileChooser(){
  return QFileDialog::getOpenFileName(".", "*"); 
}

