#include <stdio.h>
#include <iostream>
#include <Magick++.h>
#include "Loader.hpp"

using namespace std;
using namespace loader;

int main(int /*argc*/, char ** argv){
  Loader<string> L;
  //string k = string("Pictures/feyenord.jpg");
  string k = string(argv[1]);
  cout << k << endl;
  try{
    Image pic = L.getObject(k);
    cout << "The size of the image " << k << " is " << L.getSize(k) << endl;
    pic.display();
  }catch( ImageNotFoundException &e){ cout << e.getMessage() << endl;}
}
