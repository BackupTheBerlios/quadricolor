#ifndef LOADER_HPP
#define LOADER_HPP
#include <string>
#include <iostream>
#include <Magick++.h>
#include "ImageNotFoundException.hpp"

using namespace std;

using namespace Magick;

namespace loader{
  
  template<class K>
  class Loader{
    Image _object;
    
  public:
    // Constructor
    Loader(){
      string srcdir("");
      if(getenv("SRCDIR") != 0)
	srcdir = getenv("SRCDIR");         
    }
    
    virtual ~Loader(){
      cout << "I'll Be Back" << endl;
    }

    int getSize(){
      
    }

    Image& getObject(K key) throw (ImageNotFoundException) {
      try {
	//Read Image
	cout << "On lit l'image ->" << key << "<- " << endl;
	_object.read(key);
	
	// Save to file
	cout << "Writing to "<< key <<".miff"<< endl;
	_object.compressType( RunlengthEncodedCompression );
	_object.write("key_out.miff");
	
      }catch( exception &error_ ){
	cout << "Caught exception: " << error_.what() << endl;
	//throw ImageNotFoundException(key);
      }
      return _object;
    }
    
  };
}
#endif
