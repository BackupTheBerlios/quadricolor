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
  string file_name = string(argv[1]);
  cout << file_name << endl;
  CacheFifo<Image, string, Loader<string> > cache = CacheFifo<Image, string, Loader<string> >(l);
  try{
    //Image pic = l.getObject(file_name);
    Image pic = cache.getImageObject(file_name);
    cout << "The size of the image " << file_name << " is " << l.getSize(file_name) << endl;
    pic.display();
  }catch( ImageNotFoundException &e){ cout << e.getMessage() << endl;}
}