#include <stdio.h>
#include <iostream>
#include <string>
#include "LoadingSystem/Loader.hpp"
#include "CacheSystem/CacheFifo.hpp"

using namespace CacheSystem;
using namespace std;
using namespace loader;

int main(int argc, char ** argv)
{
  Loader<QString> l;
  if(argc<2)
    {
      fprintf(stderr, "Syntaxe: quadricolor <image file name>\n");
      exit(EXIT_FAILURE);
    }
  QString * file_name;
  CacheFifo<QImage, QString, Loader<QString> > cache =
    CacheFifo<QImage, QString, Loader<QString> >(l, 70000, 3);
  QImage * pic;
  QString present_files;
  
  try{
    for(int i=1; i<argc; i++){
      cout <<endl;
      file_name = new QString(argv[i]);
      cout <<"Nom du fichier: " <<*file_name <<endl;
      pic = cache.getImageObject(*file_name);
      cout << "The size of the image " << *file_name << " is " << l.getSize(*file_name) << endl;
      cout <<"Les fichiers contenus dans le cache:" <<endl;
      cache.initIterator();
      while((present_files=cache.getEachKeyStored())!="")
	cout<<present_files <<endl;      
      //pic->display();
    }
  }
  catch( ImageNotFoundException &e){ cout << e.getMessage() << endl;}
  catch( NotEnoughSpaceException &e){ cout << e.getMessage() << endl;}
  catch( RemovalImpossibleException &e){ cout << e.getMessage() << endl;}
  cout <<endl <<"Les fichiers contenus dans le cache:" <<endl;
  cache.initIterator();
  while((present_files=cache.getEachKeyStored())!="")
    cout<<present_files <<endl;      
}
