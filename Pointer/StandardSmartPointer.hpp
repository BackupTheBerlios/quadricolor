#ifndef StandardSmartPointer_HPP
#define StandardSmartPointer_HPP


namespace Pointer {  
  /**
   * This smart pointer contains basic operations like *, -> on pointers.
   * All the operators manipulating addresses have been withdrawn for security reasons.
   * The StandardSmartPointer is a simple pointer on object that do not enable array creation.
   * This array-operations are available in TabularSmartPointer where there is more information
   * on the memory.
   * This StandardSmartPointer offers to the user the possibility to manage concurrent access
   * thanks to mutex (see lock(), trylock() and unlock()).
   * The possibility to get the ReferenceCounter ancapsulated in the conversion operator.
   * When methods are available in the StandardSmartPointer and the ReferenceCounter, it is advised
   * to choose the ones contained in StandardSmartPointer.
   */
  template<class RC,class O>
  class StandardSmartPointer {
  private:
    RC *rc;
    
  public:
    
    /******************************/
    /*        Constructor         */
    /*                            */
    /* Equivalent to the notation */
    /*    * in pointeurs          */
    /******************************/
    /**
     * Default Constructor
     */
    StandardSmartPointer<RC,O>():rc(0) {}
    
    /**
     * Constructor on ReferenceCounter
     */
    StandardSmartPointer<RC,O>(RC *drc):rc(drc) {
      rc->attach();
    }

    StandardSmartPointer<RC,O>(RC &drc):rc(&drc) {
      rc->attach();
    }

    /**
     * Constructor on Pointer. It should precised the ReferenceCounter to be used.
     * It could be got thanks to the conversion operator.
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
    /*       Destructor         */
    /****************************/
    
    virtual ~StandardSmartPointer() {
      if(rc)
	rc->detach();
    }
  
    
    /****************************/
    /*       MutexFacility      */
    /****************************/
    void lock() const {
      rc->lock();
    }
    
    /**
     * See in the DefautReferenceCounter for return type.
     */
    int tryLock() const {
      return rc->trylock();
    }
    
    /**
     * See in the DefautReferenceCounter for return type.
     */
    int unlock() const {
      return rc->unlock();
    } 
    
    /****************************/
    /* Conversion operators     */
    /****************************/
    
    /** Nous permet de convertir un SmartPointer en ReferenceCounter.
     * Cette méthode nous permet de convertir n'importe quel type de
smartpointer en un autre.
     */
    & operator RC() const {
      return *rc;
    }

    * operator RC() const {
      return rc;
    }
    
    /** Nous permet de convertir un SmartPointer en pointer.
     */
    & operator O() const {
      return rc->getObject();
    }

    * operator O() const {
      return &rc->getObject();
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

    StandardSmartPointer<RC,O> & operator = (O &o) {
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
    
    /** Renvoit directement l'objet sur lequel pointe le Smartpointer par
l'intermediaire du ReferenceCounter.
     * Fonctionne comme l'operateur * des pointeurs.
     * Attention : pas de verification automatique d'accès concurrent, c'est à l'utilisateur de le verifier avec les méthodes lock(),...
     */
    O & operator * () {
      return rc->getObject();
    }
    
    /** Renvoit directement l'objet sur lequel pointe le Smartpointer par
l'intermediaire du ReferenceCounter.
     * Fonctionne comme l'operateur * des pointeurs.
     * A utiliser lorsque le pointeur n'est pas modifié.
     * Attention : pas de verification automatique d'accès concurrent, c'est à l'utilisateur de le verifier avec les méthodes lock(),...
     */
    const O & operator * () const {
      return rc->getObject();
    }
    
    /** Operateur ->
     * Attention : pas de verification automatique d'accès concurrent, c'est à l'utilisateur de le verifier avec les méthodes lock(),...
     */
    O * operator -> () {
      return  &rc->getObject();
    }
    
    /** Operateur -> sans modification de l'objet
     * Attention : pas de verification automatique d'accès concurrent, c'est à l'utilisateur de le verifier avec les méthodes lock(),...
     */
    const O * operator -> () const {
      return  &rc->getObject();
    }
   
  };

};

#endif
