#ifndef DEFAULT_REFERENCE_COUNTER_HPP
#define DEFAULT_REFERENCE_COUNTER_HPP

#include <string>
#include <pthread.h>

#include "NullPointerException.hpp"

namespace Pointer {

  template<class O>
  class DefaultReferenceCounter {
  protected:
    int _counter;
    O *_object;
    pthread_mutex_t *mut;
    
  public:
    DefaultReferenceCounter<O>():_counter(0),_object(0) {}
    
    /** Initialise le ReferenceCounter et cree un mutex
     */
    DefaultReferenceCounter<O>(O &o):_counter(1),_object(&o) {
      pthread_mutex_init(mut,NULL);
    }

    DefaultReferenceCounter<O>(O *o):_counter(1),_object(o) {
      pthread_mutex_init(mut,NULL);
    }

    virtual ~DefaultReferenceCounter() {
      pthread_mutex_destroy(mut);
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

    void lock() {
      pthread_mutex_lock(mut);
    }

    void tryLock() {
      pthread_mutex_trylock(mut);
    }
    
    void unlock() {
      pthread_mutex_unlock(mut);
    } 
    
    O & getObject() throw(NullPointerException) {
      if( _object == 0 )
	throw NullPointerException();
      return *_object;
    }

    const O & getObject() const throw(NullPointerException) {
      if( _object == 0 )
	throw NullPointerException();
      return *_object;
    }
  };
  
};
  
#endif
