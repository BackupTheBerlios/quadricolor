#ifndef IMAGE_NOT_FOUNDEXCEPTION_HPP
#define IMAGE_NOT_FOUNDEXCEPTION_HPP

#include <qstring.h>
using namespace std;

/**
 * This class is an exception that is thrown whenever it wasn't possible
 * to load an image.
 */
class ImageNotFoundException{
  QString pic;
public:
  ImageNotFoundException(QString s):pic(s){}
  QString getMessage(){ return QString("Unable to load the specified image ")+pic;}
};

#endif
