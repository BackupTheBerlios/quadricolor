#ifndef INVALID_VALUE_EXCEPTION_HPP
#define INVALID_VALUE_EXCEPTION_HPP

#include <string>

namespace Pointer {
  
  /** Exception genere lors du valeur invalide
   * comme d'une valeur négative pour la taille d'un tableau
   */
  class InvalidValueException {
  private :
    string _error_value;
  public:
    InvalidValueException(string error_value=string("")):_error_value(error_value) {}
    string getMessage() { return string("The value to access in the tabular is not valid: probably negative")+_error_value; }
  };
};

#endif
