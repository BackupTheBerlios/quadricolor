#ifndef CACHE_REFERENCE_COUNTER_HPP
#define CACHE_REFERENCE_COUNTER_HPP

#include "DefaultReferenceCounter.hpp"

namespace CacheSystem {

  template<class C,class O>
  class CacheReferenceCounter : public Pointer::DefaultReferenceCounter<O> {
  private:
    C * _cache;
  public:
    CacheReferenceCounter<C,O>(C &c,O *object):Pointer::DefaultReferenceCounter<O>(object) {
      this->_cache=c;
    }
    
    virtual ~CacheReferenceCounter() {}
    
    void detach() {
      _counter--;
      if( _counter <= 0 ) {
	_counter++;
	_cache->addToFreeAble(K);
      }
    }
  };
};

#endif

