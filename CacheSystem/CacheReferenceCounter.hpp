#ifndef CACHE_REFERENCE_COUNTER_HPP
#define CACHE_REFERENCE_COUNTER_HPP

#include "DefaultReferenceCounter.hpp"

namespace CacheSystem {

  template<class C,class K,class O>
  class CacheReferenceCounter : public Pointer::DefaultReferenceCounter<O> {
  private:
    C * _cache;
    K * _key;
  public:
    CacheReferenceCounter<C,K,O>(C &c,K &k,O *object):Pointer::DefaultReferenceCounter<O>(object),_cache(c),_key(k) {}
    
    virtual ~CacheReferenceCounter() {}
    
    void detach() {
      _counter--;
      if( _counter <= 0 ) {
	_counter++;
	_cache->addToFreeAble(_key);
      }
    }
  };
};

#endif

