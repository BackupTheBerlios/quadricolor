#ifndef StandardSmartPointer_HPP
#define StandardSmartPointer_HPP

namespace Pointer {

  template<class RC,class O>
  class StandardSmartPointer {
  private:
    RC *rc;
    
  public:
    
    /****************************/
    /*       Constructeur       */
    /****************************/
    
    /** Constructeur sur ReferenceCounter
     */
    StandardSmartPointer<RC,O>(RC *drc):rc(drc) {
      rc->attach();
    }

    StandardSmartPointer<RC,O>(RC &drc):rc(drc) {
      rc->attach();
    }

    /** Constructeur sur Pointer, il faut prèciser le ReferenceCounter à utiliser.
     * On pourra le recuperer grâce à l'operateur de conversion.
     */
    StandardSmartPointer<RC,O>(O *o) {
      rc = RC(o);
      rc->attach();
    }

    StandardSmartPointer<RC,O>(O &o) {
      rc = RC(o);
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
    /* Operateurs de conversion  */
    /****************************/
    
    /** Nous permet de convertir un SmartPointer en ReferenceCounter.
     * Cette méthode nous permet de convertir n'importe quel type de smartpointer en un autre.
     */
    operator RC() const {
      return *rc;
    }

    /** Nous permet de convertir un SmartPointer en pointer.
     */
    operator O() const {
      return rc->getObject();
    }

    /****************************/
    /*  Operateurs d'affectation */
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

    /** Permet d'assigner un nouveau pointer au SmartPointer.
     * Renvoit une reference sur le smartpointer ainsi modifié.
     */
    StandardSmartPointer<RC,O> & operator = (O *o) {
      rc->detach();
      rc = RC(o);
      rc->attach();
      return *this;
    }
    
    /****************************/
    /* Operateur de comparaison */
    /****************************/
    
    /** Operateur ==
     */
    bool operator == (RC &drc) const {
      return ( rc->getObject() == drc.getObject() );
    }
    
    /** Operateur !=
     */
    bool operator != (RC &drc) const {
      return ( rc->getObject() != drc.getObject() );
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
