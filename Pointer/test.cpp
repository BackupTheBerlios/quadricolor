#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

#include "StandardSmartPointer.hpp"
#include "TabularSmartPointer.hpp"
#include "DefaultReferenceCounter.hpp"
#include "CacheReferenceCounter.hpp"

using namespace Pointer;
using namespace std;

class Test {
public :
  void test() {
    cout<<"test"<<endl;
  }
};

void testPhread(void *p) {
  StandardSmartPointer<DefaultReferenceCounter<int>,int> *smp = (StandardSmartPointer<DefaultReferenceCounter<int>,int> *) p;
  int n = rand()%10;
  cout<<"on veut mettre: "<<n<<" dans "<<smp<<" "<<*smp<<endl;
  smp->lock();
  *(*smp)=n;
  cout<<*smp<<endl;
  smp->unlock();
}

int main(void)
{
  srand(time(NULL));
  
  StandardSmartPointer<DefaultReferenceCounter<int>,int> p(new DefaultReferenceCounter<int>( new int(9)));
  StandardSmartPointer<DefaultReferenceCounter<int>,int> p1(new DefaultReferenceCounter<int>( new int(2)));
  StandardSmartPointer<DefaultReferenceCounter<int>,int> p2(new DefaultReferenceCounter<int>( new int(5)));
  StandardSmartPointer<DefaultReferenceCounter<Test>,Test> p3(new DefaultReferenceCounter<Test>( new Test()));
  StandardSmartPointer<DefaultReferenceCounter<Test>,Test> p4(new DefaultReferenceCounter<Test>( new Test()));
  
  TabularSmartPointer< StandardSmartPointer<DefaultReferenceCounter<int>,int> , DefaultReferenceCounter<int> , int > tabsp;

  TabularSmartPointer< StandardSmartPointer<DefaultReferenceCounter<int>,int> , DefaultReferenceCounter<int> , int > tabsp2;

  TabularSmartPointer< StandardSmartPointer<DefaultReferenceCounter<Test>,Test> , DefaultReferenceCounter<Test> , Test > tabsp3;

  tabsp.add(p);
  tabsp.add(p2);
  
  tabsp2.add(p2);
  tabsp2.add(p);
  
  tabsp3.add(p3);
  tabsp3.add(p4);
  
  // test sur SmartPointer et de nouvel assignement
  cout<<"/*****************/"<<endl<<"/*  SmartPointer */"<<endl<<"/*****************/"<<endl;
  cout<<"p1 initial (2): "<<*p1<<endl;
  *p1=3;
  cout<<"p1 après affectation à 3: "<<*p1<<endl;
  
  // tests de conversion
  p1=p2;
  cout<<"p1 après affectation à p2(5): "<<*p1<<endl;
  
  cout<<"p1 casté en int: "<<(int)p1 <<endl<<endl;
  
  // test d'affectation sur tableau
  cout<<"/***********************/"<<endl<<"/* TabularSmartPointer */"<<endl<<"/***********************/"<<endl;
  cout<<"1er case de tabsp p(9):"<< tabsp[0] <<endl;
  tabsp+=1;
  cout<<"nouvel 1er case de tabsp p2(5):"<<tabsp[0]<<endl;
	      
  cout<<"test si tabsp == tabsp2 (false): "<< (tabsp==tabsp2) <<endl;
		      
  tabsp=tabsp2;
  cout<<"test si tabsp == tabsp2 (true): "<< (tabsp==tabsp2) <<endl;
  cout<<"tabsp2 ds tabsp:" <<endl;
  for(int i=0;i<tabsp.size();i++)
    cout<<"\t\t"<< tabsp[i] <<endl;
  
  cout<<"taspb+1 (9): "<<(tabsp+1)<<endl;
  cout<<"tabsp++ (9): "<<(tabsp++)<<endl;
  tabsp--;

  cout<<"assignation à 5 de la 1er case: "<< (tabsp[0]=5) <<endl;
  
  cout<<"tabsp3++ : "<<&(tabsp3++)<<" "<<&(*p4)<<endl;

  // test de thread
  cout<<"/********************/"<<endl<<"/*  Test de Thread  */"<<endl<<"/********************/"<<endl;
  pthread_t thread1,thread2;

  pthread_create(&thread1,NULL,(void *(*) (void *)) &testPhread,(void *) &p1);
  pthread_create(&thread2,NULL,(void *(*) (void *)) &testPhread,(void *) &p2);
  
  return 1;
}
