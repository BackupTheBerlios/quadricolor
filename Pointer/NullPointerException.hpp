#ifndef NULL_POINTER_EXCEPTION_HPP
#define NULL_POINTER_EXCEPTION_HPP

#include <string>

namespace Pointer {

  class NullPointerException {
  private :
    string _error_location;
  public:
    NullPointerException(string
error_location=string("")):_error_location(error_location){}
    string getMessage() { return "The pointer is Null"+_error_location; }
  };
};
  
#endif
