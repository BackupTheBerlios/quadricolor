#ifndef TABULAR_SMART_POINTER_HPP
#define TABULAR_SMART_POINTER_HPP

#include <string>
#include <vector>

#include "StandardSmartPointer.hpp"
#include "ArrayIndexOutOfBoundsException.hpp"

namespace Pointer {
   
  /** Cette classe permet de generer et de gerer un tableau, comme n'importe
quel pointeur.
   * Leve une exception: ArrayIndexOutOfBoundsException lorsr de debordement.
   */
  template<class SP,class RC,class O>
  class TabularSmartPointer:public Pointer::StandardSmartPointer<RC,O> {
  private:
    vector<SP> tab;// vector de SmartPointer
    int pos;

    void testIfIsAllowed(int index) throw(Pointer::ArrayIndexOutOfBoundsException) {
      if( pos+index < 0 || pos+index >= size() )
	throw Pointer::ArrayIndexOutOfBoundsException(pos+index);
    }
    
  public:
    
    /****************************/
    /*       Constructeurs       */
    /****************************/
    
    /** Construit un tableau vide
     * On rajoute des SmartPointer avec les methodes add
     */
    TabularSmartPointer<SP,RC,O>():tab(),pos(0) {}


    /****************************/
    /*       Destructeur        */
    /****************************/
    
    virtual ~TabularSmartPointer() {
      tab.clear();
    }

    
    /****************************/
    /*  Manipulation du tableau */
    /****************************/

    /** Renvoit le nombre d'elements d'un tableau
     */
    int size() const {
      return tab.size();
    }

    /** Change la taille du tableau et ajoute un nouvel element en fin de
tableau
     */
    void add(RC &rc) {
      tab.push_back(*new SP(rc));
    }

    /** Ajoute un nouvel element en position index
     */
    void add(RC &rc,int index) {
      if( pos+index < 0 || pos+index > size() )
	throw Pointer::ArrayIndexOutOfBoundsException(pos+index);
      tab.insert( tab.begin() + pos + index , *new SP(rc) );
    }
    
    /** Enleve l'element à la position index et diminue la taille du tableau
     */
    void remove(int index) {
      tab.erase( tab.begin() + pos + index );
    }
    
    /** Retourne le ReferenceCounter à la position index
     * L'operateur [] lui renvoit l'objet wrappe par le SmartPointer
     */
    RC & get(int index) {
      return tab[pos+index];
    }
    
    /****************************/
    /* Operateurs d'affectation */
    /****************************/
    
    /** Permet d'assigner de nouveaux RC à la place des anciens.
     * Attention il doit y avoir au moins taille RC.
     */
    TabularSmartPointer<SP,RC,O> & operator = (TabularSmartPointer<SP,RC,O> & tsp) {
      tab.clear();
      pos=0;
      for(int i=0;i<tsp.size();i++)
	add(tsp.get(i));
            
      return *this;
    }

    
    /****************************/
    /*      Operateurs          */
    /****************************/
    
    /** Operateur +
     */
    O & operator + (int index) {
      testIfIsAllowed(index);
      return get(index).getObject();
    }

    const O & operator + (int index) const {
      testIfIsAllowed(index);
      return get(index).getObject();
    }

    /** Operateur -
     */
    O & operator - (int index) {
      testIfIsAllowed(-index);
      return get(-index).getObject();
    }

    const O & operator - (int index) const {
       testIfIsAllowed(-index);
       return get(-index).getObject();
    }
    
    /** Operateur +=
     */
    O & operator += (int address) {
      testIfIsAllowed(address);
      pos+=address;
      return get(0).getObject();
    }
    
    /** Operateur -=
     */
    O & operator -= (int address) {
      testIfIsAllowed(-address);
      pos-=address;      
      return get(0).getObject();
    }

    /** Operateur ++ prefixe
     */
    O & operator ++ () {
      std::cout<<pos<<std::endl;
      testIfIsAllowed(1);
      pos+=1;
      std::cout<<pos<<std::endl;
      return get(0).getObject();
    }

    /** Operateur -- prefixe
     */
    O & operator -- () {
      testIfIsAllowed(-1);
      pos-=1;      
      return get(0).getObject();
    }
    
    /** Operateur ++ suffixe
     */
    O & operator ++ (int) {
      std::cout<<pos<<std::endl;
      testIfIsAllowed(1);
      pos+=1;
      std::cout<<pos<<std::endl;
      return get(0).getObject();
    }


    /** Operateur -- suffixe
     */
    O & operator -- (int) {
      testIfIsAllowed(-1);
      pos-=1;      
      return get(0).getObject();
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
	if( tab[i] != tsp.get(i) )
	  return false;
      return true;
    }
														 
    /** Operateur !=
     */
    bool operator != (TabularSmartPointer & tsp) const {
      return !( *this == tsp );
    }
    

    /****************************/
    /* Operateur d'indexation   */
    /****************************/
    
    /** Operateur []
     */
    O & operator [] (int index) {
      testIfIsAllowed(index);
      return get(index).getObject();
    }

    const O & operator [] (int index) const {
      testIfIsAllowed(index);
      return get(index).getObject();
    }
  };

};

#endif
