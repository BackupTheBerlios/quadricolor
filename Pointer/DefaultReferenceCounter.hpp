#ifndef DEFAULT_REFERENCE_COUNTER_HPP
#define DEFAULT_REFERENCE_COUNTER_HPP

#include <string>
#include <pthread.h>

#include "NullPointerException.hpp"

namespace Pointer {

  /** C'est le ReferenceCounter par defaut, il possède des fonctions de mutex.
   */
  template<class O>
  class DefaultReferenceCounter {
  protected:
    int _counter;
    O *_object;
    pthread_mutex_t mut;
   
  public:
    DefaultReferenceCounter<O>():_counter(0),_object(0) {}
   
    /** Initialise le ReferenceCounter et cree un mutex
     */
    DefaultReferenceCounter<O>(O &o):_counter(0),_object(&o) {
      pthread_mutex_init(&mut,NULL);
    }

    DefaultReferenceCounter<O>(O *o):_counter(0),_object(o) {
      pthread_mutex_init(&mut,NULL);
    }

    virtual ~DefaultReferenceCounter() {
      pthread_mutex_destroy(&mut);
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

    /** Bloque la ressource.
     * Cette fonction est bloquante, c'est a dire que si la ressource est bloqué par une autre ressource, on attend jusqu'à ce qu'elle soit libre.
     */
    void lock() {
      pthread_mutex_lock(&mut);
    }
   
    /** Teste si le SmartPointer est utilise par une autre thread.
     * Elle renvoit : EBUSY (man phtread_mutex_trylock) si le mutex est verrouille, 0 sinon
     */
    int tryLock() {
      return pthread_mutex_trylock(&mut);
    }
   
    /** Debloque le mutex.
     * Renvoit EPERM (man phtread_mutex_unlock) si le mutex n'a pas été verrouillé par la thread appelante, renvoit 0 sinon
     */
    int unlock() {
      return pthread_mutex_unlock(&mut);
    }
   
    /** Retourne l'objet encapsulé.
     * Attention : pas de verification automatique d'accès concurrent, c'est à l'utilisateur de le verifier avec les méthodes lock(),...
     */
    O & getObject() throw(NullPointerException) {
      if( _object == 0 )
  throw NullPointerException();
      return *_object;
      }
   
    /** Attention : pas de verification automatique d'accès concurrent, c'est à l'utilisateur de le verifier avec les méthodes lock(),...
     */
    const O & getObject() const throw(NullPointerException) {
      if( _object == 0 )
throw NullPointerException();
      return *_object;
    }
  };
 
};

#endif
