#ifndef ARRAY_INDEX_OUT_OF_BOUNDS_EXCEPTION_HPP
#define ARRAY_INDEX_OUT_OF_BOUNDS_EXCEPTION_HPP

#include <string>

namespace Pointer {
  
  /** Exception genere lors d'un debordement
   */
  class ArrayIndexOutOfBoundsException{
  private :
    string _error_value;
  public:
    ArrayIndexOutOfBoundsException(string error_value=string("")):_error_value(error_value){}
    string getMessage() { return string("ArrayIndexOutOfBounds")+_error_value; }
  };
};

#endif
