#ifndef CACHE_OLDEST_UNUSED_OUT_HPP
#define CACHE_OLDEST_UNUSED_OUT_HPP

#include <string.h>
#include "Unable2ShakePriority.hpp"

namespace CacheSystem{
  /**
   * T = smart pointer on the wanted image-object
   * K = key which can identify an image-object
   * L = the type of the loader that will be used
   */
  /**
   * This cache implements a mechanism of cache in which all the image-objects are stored in
   * a sort of priority queue(but the STL's priority queue isn't used). Each image-object
   * in this "queue", possess a priority. When there isn't enough space, the image-object
   * which has the highest priority is removed.
   */
  template <class T, class K, class L>
  class CacheOldestUnusedOut: public CacheSystem::Cache<T, K, L>{
  private:
    ///////Attributes
    int      _total_bytes; //Total number of bytes contained in the cache
    int      _max_bytes;   //Maximum number of bytes
    
    int      _nb_of_images;     //Number of images contained in the cache
    int      _max_nb_of_images; //Maximum number of images allowed
    
    L   _loader;      //The object that will enable this cache to load files in memory
    //Contains all the key/references to a Reference Counter
    hash_map<const K, T, hash<const K> >  _image_set;
    list<pair<K*, int> > _freeable;    //Contains the key of all the freeable elements
    
    ///////Methods
    /**
     * Adds an image to the list of images.
     * Returns true if the operation succeeded, false otherwise.
     */
    bool addImageObject(const K &key, T/* A VERIFIER */ image) throw (NotEnoughSpaceException){
      this->_image_set[key] = image;
      addToFreeable(key);
      return true;
    }
    
    /**
     * Removes an image from the list of images.
     * Returns true if the operation succeeded, false otherwise.
     */
    bool removeImageObject(const K &key){
      if(this->_image_set.erase(key)>=1) return true;
      return false;
    }
    
    /**
     * Adds the image-object to the list of the freeable objects.
     * Returns true if the operation succeeded, false otherwise.
     */
    bool addToFreeable(const K &key){
      pair<K*, int> key_priority = pair<K*, int>(&key, 0); //Default priority = 0, and we need a pointer
      
      //The pairs that are in front of the list are to be freed in priority
      this->_freeable.push_back(key_priority);
      return true;
    }
    
    /**
     * Removes the image-object from the list of the freeable objects.
     * Returns true if the operation succeeded, false otherwise.
     */
    bool removeFromFreeable(){
      this->_freeable.pop_front();
      return true;
    }
    
    /**
     * Frees some objects while there isn't enough space.
     */
    void freeSomeMemory() throw (NotEnoughSpaceException)
    {
      pair<K*, int> image2bfreed;
      
      /* while there isn't enough space, we delete the first image-objects */
      while(_nb_of_images>=_max_nb_of_images || _total_bytes>=_max_bytes)
	{//if there's too much image in cache
	  if(this->_freeable.empty())//if the FIFO is empty, the user didn't grant enough space for the cache
	    throw NotEnoughSpaceException();
	  image2bfreed = _freeable.front();
	  //remove an image from the cache
	  if(!removeImageObject(*image2bfreed.first))
	    throw RemovalImpossibleException(": removeImageObject.");
	  if(!removeFromFreeable())
	    throw RemovalImpossibleException(": removeFromFreeable.");
	}
    }
    
    /**
     * Decreases the priority of the image-object which has the key 'key'.
     * This method than shakes the freeable list, in order the freeable objects
     * at the beginning of the list.
     * TESTABLE ISOLEMENT
     */
    void shakePriorities(const K &key) throw (Unable2ShakePriority)
    {
      list<pair<K*, int> >::iterator it;
      list<pair<K*, int> >::iterator end = _freeable.end();
      list<pair<K*, int> >::iterator it_key = end;
      
      for(it = _freeable.begin(); it != it_key; it++)
	{
	  if(*it->first != key)
	    it->second++; //all the other pairs have their priority increased
	  else
	    it_key = it;//ERREUR POSSIBLE: it risque d'etre augmente=>boucle infinie
	}
      if(it_key != end)
	{
	  it = it_key+1;
	  while(it_key->second==it->second){
	    it->second++;
	    it++;
	  }
	  (it-1)->second++;
	  swap(*(it-1), *it_key);
	  while(end != it){ //increase the priority of the rest of the list
	    it->second++;
	    it++;
	  }
	}
      else
	throw Unable2ShakePriority();
    }
    
  public:
    CacheOldestUnusedOut(const L &loader):_loader(loader){}
    ~CacheOldestUnusedOut(){}
    
    
    /**
     * Go and fetch an object-image. It's behaviour depends of the implementing subclasses.
     * Must be called by the user interface-side.
     */
    T getImageObject(const K &key)const{
      hash_map<const K, T, hash<const K> >::iterator index = this->_image_set.find(key);
      if(index == _image_set.end())
	{//the object-image isn't in the image set
	  freeSomeMemory(); //Free EVENTUALLY some memory
	  //ASK THE LOADER to fetch the image
	  /* VOIR AVEC RODRIGUE S'IL FAUT DONNER LA TAILLE DE L'OBJET A LA METHODE D'AJOUT */
	  addImageObject(key, image); //ADD THE NEW image to the cache
	}
      else //If the element is already present, we only have to decrease his priority
	shakePriorities(key); //and shake the freeable list
      return *index;
    }
  };
};

#endif
