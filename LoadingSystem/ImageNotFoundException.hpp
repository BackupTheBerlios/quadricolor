#ifndef IMAGE_NOT_FOUNDEXCEPTION_HPP
#define IMAGE_NOT_FOUNDEXCEPTION_HPP

#include <string.h>
using namespace std;

/**
 * This class is an exception that is thrown whenever it wasn't possible
 * to load an image.
 */
class ImageNotFoundException{
  string pic;
public:
  ImageNotFoundException(string s):pic(s){}
  string getMessage(){ string("Unable to load the specified image ")+pic;}
};

#endif
