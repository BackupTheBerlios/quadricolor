#include <stdio.h>
#include <iostream>
#include <Magick++.h>
#include <string>
#include "LoadingSystem/Loader.hpp"
#include "CacheSystem/CacheFifo.hpp"

using namespace CacheSystem;
using namespace std;
using namespace loader;
using namespace Magick;

int main(int argc, char ** argv)
{
  Loader<string> l;
  if(argc<2)
    {
      fprintf(stderr, "Syntaxe: quadricolor <image file name>\n");
      exit(EXIT_FAILURE);
    }
  string * file_name;
  CacheFifo<Image, string, Loader<string> > cache =
    CacheFifo<Image, string, Loader<string> >(l, 70000, 3);
  Image pic;
  string present_files;
  
  try{
    for(int i=1; i<argc; i++){
      cout <<endl;
      file_name = new string(argv[i]);
      cout <<"Nom du fichier: " <<*file_name <<endl;
      pic = cache.getImageObject(*file_name);
      cout << "The size of the image " << *file_name << " is " << l.getSize(*file_name) << endl;
      cout <<"Les fichiers contenus dans le cache:" <<endl;
      cache.initIterator();
      while((present_files=cache.getEachKeyStored())!="")
	cout<<present_files <<endl;      
      //pic.display();
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
