#include "ReferenceCounter.hpp"

using namespace Pointer;

namespace CacheSystem {
  template<class K,class T>
  class CacheReferenceCounter : public DefaultReferenceCounter {
  private:
    Cache * _cache;
  public:
    CacheReferenceCounter<K,T>(Cache &c,T *t):DefaultReferenceCounter<T>(t) {
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
