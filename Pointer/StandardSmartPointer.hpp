#ifndef StandardSmartPointer_HPP
#define StandardSmartPointer_HPP

#include "ReferenceCounter.hpp"

namespace Pointer {

  template<class RC,class O>
  class StandardSmartPointer {
  private:
    RC *rc;
    
  public:
    
    /****************************/
    /*       Constructeur       */
    /****************************/
    
    /** Constructeur
     */
    StandardSmartPointer<RC,O>(RC *drc):rc(drc) {
      rc->attach();
    }


    /****************************/
    /*       Destructeur        */
    /****************************/
    
    virtual ~StandardSmartPointer() {
      rc->detach();
    }
  
    
    /****************************/
    /*       MutexFacility      */
    /****************************/
    void lock() const {
      rc->lock();
    }

    void tryLock() const {
      rc->trylock();
    }
    
    void unlock() const {
      rc->unlock();
    } 
    
    /****************************/
    /* Operateur de conversion  */
    /****************************/
    
    /** Nous permet de convertir un SmartPointer en ReferenceCounter.
     * Cette méthode nous permet de convertir n'importe quel type de smartpointer en un autre.
     */
    operator Pointer::DefaultReferenceCounter<O>() const {
      return *rc;
    }


    /****************************/
    /*  Operateur d'affectation */
    /****************************/
    
    /** Permet d'assigner un nouveau ReferenceCounter au SmartPointer.
     * Renvoit une reference sur le smartpointer ainsi modifié.
     */
    StandardSmartPointer<RC,O> & operator = (RC *drc) {
      rc->detach();
      rc=drc;
      rc->attach();
      return *this;
    }
    
    /****************************/
    /* Operateur de comparaison */
    /****************************/
    
    /** Operateur ==
     */
    bool operator == (Pointer::DefaultReferenceCounter<O> *drc) const {
      return ( rc->getObject() == drc->getObject() );
    }
    
    /** Operateur !=
     */
    bool operator != (Pointer::DefaultReferenceCounter<O> *drc) const {
      return ( rc->getObject() != drc->getObject() );
    }

    
    /****************************/
    /*  Operateurs d'accès      */
    /****************************/
    
    /** Renvoit directement l'objet sur lequel pointe le Smartpointer par l'intermediaire du ReferenceCounter.
     * Fonctionne comme l'operateur * des pointeurs.
     */
    O & operator * () {
      return rc->getObject();
    }
    
    /** Renvoit directement l'objet sur lequel pointe le Smartpointer par l'intermediaire du ReferenceCounter.
     * Fonctionne comme l'operateur * des pointeurs.
     * A utiliser lorsque le pointeur n'est pas modifié
     */
    const O & operator * () const {
      return rc->getObject();
    }
    
    /** Operateur ->
     */
    O * operator -> () {
      return  rc->getObject();
    }

    /** Operateur -> sans modification de l'objet
     */
    const O * operator -> () const {
      return  rc->getObject();
    }
   
  };

};

#endif
