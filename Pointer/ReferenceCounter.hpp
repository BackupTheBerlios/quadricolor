#ifndef ReferenceCounter_HPP
#define ReferenceCounter_HPP

#include <pthread.h>

namespace Pointer {

  class NullPointerException{};
  
  template<class T>
  class DefaultReferenceCounter {
  protected:
    int _counter;
    T *_object;
    pthread_mutex_t *mut;

  public:
    DefaultReferenceCounter<T>(T *t):_counter(1),_object(t) {
      pthread_mutex_init(mut,NULL);
    }

    virtual ~DefaultReferenceCounter() {
      delete _object;
    }
    
    virtual void attach() {
      _counter++;
    }

    virtual void detach() {
      _counter--;
      if(_counter <= 0 )
	delete this;
    }

    T &getObject() throw(NullPointerException) {
      if( _object == 0 )
	throw NullPointerException();
      return *_object;
    }

    const T &getObject() const throw(NullPointerException) {
      if( _object == 0 )
	throw NullPointerException();
      return *_object;
    }
  };
  
};
  
#endif
