#include <stdio.h>
#include <iostream>
#include <Magick++.h>
#include "LoadingSystem/Loader.hpp"
#include "CacheSystem/Cache.hpp"
#include "CacheSystem/CacheFifo.hpp"

using namespace CacheSystem;
using namespace std;
using namespace loader;

int main(int argc, char ** argv)
{
  Loader<string> L;
  if(argc<2)
    {
      fprintf(stderr, "Syntaxe: quadricolor <image file name>\n");
      exit(EXIT_FAILURE);
    }
  string k = string(argv[1]);
  cout << k << endl;
  try{
    Image pic = L.getObject(k);
    cout << "The size of the image " << k << " is " << L.getSize(k) << endl;
    pic.display();
  }catch( ImageNotFoundException &e){ cout << e.getMessage() << endl;}
}
