#include "../Pointer/DefaultReferenceCounter.hpp"

using namespace Pointer;

namespace CacheSystem {
  template<class C,class T>
  class CacheReferenceCounter : public DefaultReferenceCounter {
  private:
    C * _cache;
  public:
    CacheReferenceCounter<C,T>(C &c,T *t):DefaultReferenceCounter<T>(t) {
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
