#ifndef TabularSmartPointer_HPP
#define TabularSmartPointer_HPP

#include "ReferenceCounter.hpp"
#include "StandardSmartPointer.hpp"

/** On separe TabularSmartPointer et StandardSmartPointer pour des raisons de conception.
 * En effet on ne peut pas utiliserl'operateur [] en tant que constructeur, on est oblig� d'utiliser des constructeurs classiques, qui sont lourd � utiliser dans le cas d'un StandardSmartPointer simple.
 * On a enlever de StandardSmartPointer l'op�rateur [] et tout les op�rateurs sp�cifiques aux tableaux pour des raisons de securit�.
 *
 * Le StandardSmartPointer int�gre des m�thodes pour gerer l'acc�s concurrent sur l'objet wrapp�.
*/


namespace Pointer {
  
  /** Exception genere lors du valeur invalide
   * comme d'une valeur n�gative pour la taille d'un tableau
   */
  class InvalidValueException{
   private :
    string _error_value;
  public:
    InvalidValueException(string error_value=""):_error_value(error_value){}
    string getMessage() { return string("The value to access in the tabular is not valid: probably negative")+_error_value; }
  };
  
  /** Exception genere lors d'un debordement
   */
  class ArrayIndexOutOfBoundsException{
  private :
    string _error_value;
  public:
    ArrayIndexOutOfBoundsException(string error_value=""):_error_value(error_value){}
    string getMessage() { return string("ArrayIndexOutOfBounds")+_error_value; }
  };
  
  /** Cette classe permet de generer et de gerer un tableau, comme n'importe quel pointeur.
   * Leve une exception: ArrayIndexOutOfBoundsException lorsr de debordement.
   */
  template<class SP,class RC,class O>
  class TabularSmartPointer:public Pointer::StandardSmartPointer {
  private:
    SP *sp; // tableau de SmartPointer
    int pos;
    int taille;

    /** Resize le tableau
     */
    void resize(int index) {
      if( index < 0 )
	throw InvalidValueException(index);
      if(sp) {
	SP *tmp = new SP[index];
	int m = (index<taille)?index:taille;
	for(int j=0;j<m;j++)
	  tmp[j]=sp[j];
	sp = tmp;
	taille=index;
      }
      else {
	sp = new SP[index];
	taille=index;
      }
    }

    void copyFrom(TabularSmartPointer & tsp) {
      if( this->sp ) {
	for(int i=0;i<size();i++)
	  ((Pointer::DefaultReferenceCounter)(this->sp+i))->detach();
	this->taille=0;
      }
      
      if( sp ) {
	this->sp = new SP[tsp.size()];
	for(int i=0;i<tsp.size();i++) {
	  this->sp[i]=tsp.get[i];
	  ((Pointer::DefaultReferenceCounter)(this->sp+i))->attach();
	}
	this->taille=taille;
      }
      else {
	for(int i=0;i<size();i++)
	  ((Pointer::DefaultReferenceCounter)(this->sp+i))->detach();
	this->sp=0; this->taille=0; }
    }

    void testIfIsAllowed(int index) throw(ArrayIndexOutOfBoundsException) {
      if( pos+index < 0 || pos+index >= taille )
	throw ArrayIndexOutOfBoundsException(pos+index);
    }
    
  public:
    
    /****************************/
    /*       Constructeurs       */
    /****************************/
    
    /** Constructeur:
     * Attention drc doit avoir la taille taille
     * sinon le comportement n'est pas garanti
     */
    TabularSmartPointer<SP,RC,O>(SP *sp,int taille=0):Pointer::StandardSmartPointer<RC,O>((Pointer::DefaultReferenceCounter<O>)sp),sp(sp),pos(0),taille(taille) {
      if( taille < 0 ) {
	delete this;
	throw InvalidValueException(taille);
      }
      for( int i=0;i<taille;i++)
	( (Pointer::DefaultReferenceCounter<O>)(sp+i) )->attach();
    }
														 
    /** Construit un tableau vide
     * On rajoute des ReferenceCounter avec les methodes add
     */
    TabularSmartPointer<SP,RC,O>():sp(NULL),pos(0),taille(0) {
    }


    /****************************/
    /*       Destructeur        */
    /****************************/
    
    virtual ~TabularSmartPointer() {
      for( int i=0;i<size();i++)
	( (Pointer::DefaultReferenceCounter<O>)(sp+i) )->detach();
    }

    
    /****************************/
    /*  Manipulation du tableau */
    /****************************/

    /** Renvoit le nombre d'elements d'un tableau
     */
    int size() const {
      return taille;
    }

    /** Change la taille du tableau et ajoute un nouvel element en fin de tableau
     */
    void add(SP *sp) {
      resize(size()+1);
      this->sp[size()-1]=sp;
      ((Pointer::DefaultReferenceCounter<O>)this->sp)->attach();
    }

    /** Ajoute un nouvel element en position index
     */
    void add(SP *sp,int index) {
      if( index < 0 || index > size() )
	throw ArrayIndexOutOfBoundsException(index);
      resize(size()+1);
      for(int i=index;i<size()-1;i++)
	this->sp[i+1]=this->rc[i];
      sp[index]=sp;
      ((Pointer::DefaultReferenceCounter<O>)this->sp)->attach();
    }
    
    /** Enleve l'element � la position index et diminue la taille du tableau
     */
    void remove(int index) {
      if( index < 0 || index >= size() )
	throw ArrayIndexOutOfBoundsException(index);
      for(int i=index;i<size()-1;i++)
	this->rc[i]=this->rc[i+1];
      resize(size()-1);
      ((Pointer::DefaultReferenceCounter<O>)rc)->detach();
    }
    
    /** Retourne le SmartPointer � la position index
     * L'operateur [] lui renvoit l'objet wrappe par le SmartPointer
     */
    SP & get(int index) {
      if( index < 0 || index >= size() )
	throw ArrayIndexOutOfBoundsException();
      return sp[index];
    }
    
    /****************************/
    /*  Operateur d'affectation */
    /****************************/
    
    /** Permet d'assigner de nouveaux RC � la place des anciens.
     * Attention il doit y avoir au moins taille RC.
     */
    TabularSmartPointer<SP,RC,O> & operator = (TabularSmartPointer<SP,RC,O> & tsp) {
      copyFrom(drc,taille);

      return *this;
    }
    
    /** Operateur +=
     */
    O * operator += (int address) {
      testIfIsAllowed(address);
      pos+=address;
      return &this[0]
    }
    
    /** Operateur -=
     */
    O * operator -= (int address) {
      testIfIsAllowed(-address);
      pos-=address;      
      return &this[0];
    }

    
    /****************************/
    /* Operateur de comparaison */
    /****************************/
    
    /** Operateur ==
     * On compare les 2 TabularSmartPointer
     */
    bool operator == (TabularSmartPointer & tsp) const {
      if( size() != tsp.size() )
	return false;
      for(int i=0;i<size();i++)
	if( sp[i] != ((Pointer::DefaultReferenceCounter<O>)tsp[i]) )
	  return false;
      return true;
    }
														 
    /** Operateur !=
     */
    bool operator != (TabularSmartPointer & tsp) const {
      return !( this == tsp );
    }
    
    /****************************/
    /* Operateur d'indexation   */
    /****************************/
    
    /** Operateur []
     */
    O & operator [] (int index) {
      testIfIsAllowed(pos+index);
      return ((Pointer::DefaultReferenceCounter<O>)sp[pos+index])->getObject();
    }

    const O & operator [] (int index) const {
      testIfIsAllowed(pos+index);
      return ((Pointer::DefaultReferenceCounter<O>)sp[pos+index])->getObject();
    }


    /****************************/
    /*      Operateurs          */
    /****************************/
    
    /** Operateur +
     */
    O * operator + (int index) {
      return &this[index];
    }

    const O * operator + (int index) const {
      return &this[index];
    }

    /** Operateur -
     */
    O * operator - (int index) {
      return &this[-index];
    }

    const O * operator - (int index) const {
      return &this[-index];
    }
    
    /** Operateur ++
     */
    O * operator ++ () {
      this=&this[1];
      return this;
    }


    /** Operateur --
     */
    O * operator -- () {
      this=&this[-1];
      return this;
    }
   
  };

};

#endif
