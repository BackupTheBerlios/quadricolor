#ifndef REMOVAL_IMPOSSIBLE_EXCEPTION_HPP
#define REMOVAL_IMPOSSIBLE_EXCEPTION_HPP

#include <string.h>
/**
 * This class is an exception that is thrown whenever there isn't enough space
 * in the cache.
 */
class RemovalImpossibleException{
  string _error_location;
public:
  RemovalImpossibleException(string error_location=string(".")):_error_location(error_location){}
  string getMessage()
  { return string("Unable to remove the image from the cache system")+_error_location; }
};

#endif
