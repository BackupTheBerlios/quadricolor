#ifndef LOADER_HPP
#define LOADER_HPP
#include <string>
#include <iostream>
#include <qimage.h>
#include <qfile.h>
#include "ImageNotFoundException.hpp"

using namespace std;


namespace loader{
  
  template<class K, class Image_Type, class File_Type>
  class Loader{
    Image_Type _object;
    
  public:
    // Constructor
    Loader(){
      string srcdir("");
      if(getenv("SRCDIR") != 0)
	srcdir = getenv("SRCDIR");         
    }
    
    // Destructor
    virtual ~Loader(){
      //cout << "I'll Be Back" << endl;
    }

    // return the size on the disk of the file with that key.
    int getSize(const K &key){
      File_Type tmp_file(key);
      int tmp_size = tmp_file.size();
      return tmp_size;
    }

    /**
     * Read the file with the specified key and return a reference
     * on this objecy.
     */
    Image_Type& getObject(const K & key) throw (ImageNotFoundException) {
      try {
	//Read Image
	_object = Image_Type(key);	
	
      }catch( exception &error_ ){
	cout << "Caught exception: " << error_.what() << endl;
	throw ImageNotFoundException(key);
      }
      return _object;
    }    
  };
}
#endif
