#ifndef NOT_ENOUGH_SPACE_EXCEPTION_HPP
#define NOT_ENOUGH_SPACE_EXCEPTION_HPP

#include <string.h>
/**
 * This class is an exception that is thrown whenever there isn't enough space
 * in the cache.
 */
class NotEnoughSpaceException{
public:
  string getMessage(){ return string("Not enough space to load the image in the cache."); }
};

#endif
