#ifndef TABULAR_SMART_POINTER_HPP
#define TABULAR_SMART_POINTER_HPP

#include <string>

#include "StandardSmartPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"
#include "InvalidValueException.hpp"

namespace Pointer {
   
  /** Cette classe permet de generer et de gerer un tableau, comme n'importe quel pointeur.
   * Leve une exception: ArrayIndexOutOfBoundsException lorsr de debordement.
   */
  template<class SP,class RC,class O>
  class TabularSmartPointer:public Pointer::StandardSmartPointer<RC,O> {
  private:
    SP *sp; // tableau de SmartPointer
    int pos;
    int taille;

    /** Resize le tableau
     */
    void resize(int index) {
      if( index < 0 )
	throw InvalidValueException();
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
	  ((RC)(this->sp+i))->detach();
	this->taille=0;
      }
      
      if( sp ) {
	this->sp = new SP[tsp.size()];
	for(int i=0;i<tsp.size();i++) {
	  this->sp[i]=tsp.get[i];
	  ((RC)(this->sp+i))->attach();
	}
	this->taille=taille;
      }
      else {
	for(int i=0;i<size();i++)
	  ((RC)(this->sp+i))->detach();
	this->sp=0; this->taille=0; }
    }

    void testIfIsAllowed(int index) throw(Pointer::ArrayIndexOutOfBoundsException) {
      if( pos+index < 0 || pos+index >= taille )
	throw Pointer::ArrayIndexOutOfBoundsException();
    }
    
  public:
    
    /****************************/
    /*       Constructeurs       */
    /****************************/
    
    /** Constructeur:
     * Attention drc doit avoir la taille taille
     * sinon le comportement n'est pas garanti
     */
    TabularSmartPointer<SP,RC,O>(SP *sp,int taille=0):Pointer::StandardSmartPointer<RC,O>((RC)sp),sp(sp),pos(0),taille(taille) {
      if( taille < 0 ) {
	delete this;
	throw Pointer::InvalidValueException();
      }
      for( int i=0;i<taille;i++)
	( (RC)(sp+i) )->attach();
    }
														 
    /** Construit un tableau vide
     * On rajoute des ReferenceCounter avec les methodes add
     */
    TabularSmartPointer<SP,RC,O>():sp(0),pos(0),taille(0) {}


    /****************************/
    /*       Destructeur        */
    /****************************/
    
    virtual ~TabularSmartPointer() {
      for( int i=0;i<size();i++)
	((RC)*get(i)).detach();
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
      this->sp[size()-1]=*sp;
      ((RC)this->sp)->attach();
    }

    /** Ajoute un nouvel element en position index
     */
    void add(SP *sp,int index) {
      if( index < 0 || index > size() )
	throw Pointer::ArrayIndexOutOfBoundsException();
      resize(size()+1);
      for(int i=index;i<size()-1;i++)
	this->sp[i+1]=this->rc[i];
      sp[index]=sp;
      ((RC)this->sp)->attach();
    }
    
    /** Enleve l'element à la position index et diminue la taille du tableau
     */
    void remove(int index) {
      if( index < 0 || index >= size() )
	throw Pointer::ArrayIndexOutOfBoundsException();
      for(int i=index;i<size()-1;i++)
	this->rc[i]=this->rc[i+1];
      resize(size()-1);
      ((RC)rc)->detach();
    }
    
    /** Retourne le SmartPointer à la position index
     * L'operateur [] lui renvoit l'objet wrappe par le SmartPointer
     */
    SP & get(int index) {
      if( index < 0 || index >= size() )
	throw Pointer::ArrayIndexOutOfBoundsException();
      return sp[index];
    }
    
    /****************************/
    /* Operateurs d'affectation */
    /****************************/
    
    /** Permet d'assigner de nouveaux RC à la place des anciens.
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
      return &this[0];
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
	if( sp[i] != ((RC)tsp[i]) )
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
      return ((RC)sp[pos+index])->getObject();
    }

    const O & operator [] (int index) const {
      testIfIsAllowed(pos+index);
      return ((RC)sp[pos+index])->getObject();
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
