#ifndef LOADER_HPP
#define LOADER_HPP
#include <string>
#include <iostream>
#include <qimage.h>
#include <qfile.h>
#include "ImageNotFoundException.hpp"


namespace loader{
  
  template<class K, class Image_Type, class File_Type>
  class Loader{
    Image_Type _object;
    
  public:
    /**
     * Constructor
     */
    Loader(){
      string srcdir("");
      if(getenv("SRCDIR") != 0)
	srcdir = getenv("SRCDIR");         
    }
    
    /**
     * Destructor
     */
    virtual ~Loader(){
    }

    /**
     * returns the size on the disk of the file with that key.
     */
    int getSize(const K &key){
      File_Type tmp_file(key);
      int tmp_size = tmp_file.size();
      return tmp_size;
    }

    /**
     * Reads the file with the specified key and returns a reference
     * on this object.
     */
    Image_Type& getObject(const K & key) throw (ImageNotFoundException) {
      try {
	//reads an Image
	_object = Image_Type(key);
      }catch( exception &error_ ){
	std::cerr << "Caught exception: " << error_.what() << endl;
	throw ImageNotFoundException(key);
      }
      return _object;
    }    
  };
}
#endif







