#ifndef StandardSmartPointer_HPP
#define StandardSmartPointer_HPP


namespace Pointer {

  /** Ce SmartPointer contient les opérateurs de base *, -> des pointeurs.
   * Tout les opérateurs permettant de manipuler les adresses on été retirés pour des raisons de sécurité.
   * Le StandardSmartPointer est un pointeur simple qui ne permet pas de créer des tableaux.
   * Ces opérateurs sont disponibles dans TabularSmartPointer où l'on a plus d'information sur la mémoire.
   *
   * Ce StandardSmartPointer offre à l'utilisateur la possibilité de gerer les accès concurrents à l'aide d'un mutex (voir lock(), trylock() et unlock()).
   *
   * On a la possibilté de recuperer le ReferenceCounter encapsulé par l'opérateur de conversion.
   * Lorsque des méthodes sont disponibles à la fois dans le StandardSmartPointer et dans le ReferenceCounter, il est conseillé de choisir celles du StandardSmartPointer.
   */
  template<class RC,class O>
  class StandardSmartPointer {
  private:
    RC *rc;
    
  public:
    
    /****************************/
    /*       Constructeur       */
    /*                          */
    /* Equivalent à la notation */
    /*  * ds pointeurs          */
    /****************************/
    /** Constructeur par defaut
     */
    StandardSmartPointer<RC,O>():rc(0) {}
    
    /** Constructeur sur ReferenceCounter
     */
    StandardSmartPointer<RC,O>(RC *drc):rc(drc) {
      rc->attach();
    }

    StandardSmartPointer<RC,O>(RC &drc):rc(&drc) {
      rc->attach();
    }

    /** Constructeur sur Pointer, il faut prèciser le ReferenceCounter à
utiliser.
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
      if(rc)
	rc->detach();
    }
  
    
    /****************************/
    /*       MutexFacility      */
    /****************************/
    void lock() const {
      rc->lock();
    }
    
    /** voir dans le DefautReferenceCounter pour le type de retour.
     */
    int tryLock() const {
      return rc->trylock();
    }
    
    /** voir dans le DefautReferenceCounter pour le type de retour.
     */
    int unlock() const {
      return rc->unlock();
    } 
    
    /****************************/
    /* Operateurs de conversion  */
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
