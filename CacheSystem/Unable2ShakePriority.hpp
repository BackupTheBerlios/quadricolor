#ifndef UNABLE2SHAKE_PRIORITY_HPP
#define UNABLE2SHAKE_PRIORITY_HPP

#include <string.h>
/**
 * This class is an exception that is thrown whenever it wasn't possible
 * to shake the priority list of all the freeable object-images.
 */
class NotEnoughSpaceException{
public:
  string getMessage(){ return "Unable to shake the freeable list of object-image."; }
};

#endif
