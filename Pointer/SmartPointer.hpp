#ifndef SmartPointer_HPP
#define SmartPointer_HPP

#include "ReferenceCounter.hpp"
#include <iostream>

namespace Pointer {

  template<class O>
  class StandardSmartPointer {
  private:
    Pointer::DefaultReferenceCounter<O> *rc;

  public:
    StandardSmartPointer<O>(Pointer::DefaultReferenceCounter<O> *drc) {
      rc=drc;
      rc->attach();
    }

    virtual ~StandardSmartPointer() {
      rc->detach();
    }

    /* Permet d'assigner un nouveau ReferenceCounter au SmartPointer.
     * Renvoit une reference sur le smartpointer ainsi modifié.
     */
    virtual StandardSmartPointer<O> & operator = (Pointer::DefaultReferenceCounter<O> *drc) {
      rc->detach();
      rc=drc;
      rc->attach();
      return *this;
    }

    /* Operateur de conversion.
     * Nous permet de convertir un SmartPointer en ReferenceCounter.
     * Cette méthode nous permet de convertir n'importe quel type de smartpointer en un autre.
     */
    virtual operator Pointer::DefaultReferenceCounter<O>() const {
      return *rc;
    }

    /* Renvoit directement l'objet sur lequel pointe le Smartpointer par l'intermediaire du ReferenceCounter.
     * Fonctionne comme l'operateur * des pointeurs.
     */
    O & operator * () throw(Pointer::NullPointerException) {
      return rc->getObject();
    }
    
    /* Renvoit directement l'objet sur lequel pointe le Smartpointer par l'intermediaire du ReferenceCounter.
     * Fonctionne comme l'operateur * des pointeurs.
     * A utiliser lorsque le pointeur n'est pas modifié
     */
    const O & operator * () const throw(Pointer::NullPointerException) {
      return rc->getObject();
    }
    
    /* Operateur ->
     */
    O * operator -> () throw(Pointer::NullPointerException) {
      return  rc->getObject();
    }

    /* Operateur -> sans modification de l'objet
     */
    const O * operator -> () const throw(Pointer::NullPointerException) {
      return  rc->getObject();
    }
    
    /* Operateur []
     */
    O & operator [] (int index) throw(Pointer::NullPointerException) {
      if( &(rc->getObject()[index]) == 0 )
	throw Pointer::NullPointerException();
      return  rc->getObject()[index];
    }

    const O & operator [] (int index) const throw(Pointer::NullPointerException) {
      if( &(rc->getObject()[index]) == 0 )
	throw Pointer::NullPointerException();
      return  rc->getObject()[index];
    }
    
    /* Operateur +
     */
    O * operator + (int index) throw(Pointer::NullPointerException) {
      return &this[index];
    }

    const O * operator + (int index) const throw(Pointer::NullPointerException) {
      return &this[index];
    }
    
    /* Operateur ++
     */
    O * operator ++ () throw(Pointer::NullPointerException) {
      this=&this[1];
      return this;
    }


    /* Operateur --
     */
    O * operator -- () throw(Pointer::NullPointerException) {
      this=&this[-1];
      return this;
    }

    /* Operateur ==
     */
    bool operator == (Pointer::DefaultReferenceCounter<O> *drc) const {
      return ( rc->getObject() == drc->getObject() );
    }
    
    /* Operateur !=
     */
    bool operator != (Pointer::DefaultReferenceCounter<O> *drc) const {
      return ( rc->getObject() != drc->getObject() );
    }

    /* Operateur +=
     */
    O * operator += (int address) throw(Pointer::NullPointerException) {
      this=&this[address];
      return this;
    }
    
     /* Operateur -=
     */
    O * operator -= (int address) throw(Pointer::NullPointerException) {
      this=&this[-address];
      return this;
    }
    
  };

};

#endif
