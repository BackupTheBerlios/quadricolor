#ifndef CACHE_OLDEST_UNUSED_OUT_HPP
#define CACHE_OLDEST_UNUSED_OUT_HPP

#include <string>
#include <map>
#include <queue>
#include "StandardSmartPointer.hpp"
#include "CacheReferenceCounter.hpp"
#include "Loader.hpp"
#include "NotEnoughSpaceException.hpp"
#include "RemovalImpossibleException.hpp"
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
  class CacheOldestUnusedOut{
  private:
    ///////Attributes
    int       _total_bytes; //Total number of bytes contained in the cache
    int       _max_bytes;   //Maximum number of bytes
    
    int       _nb_of_images;     //Number of images contained in the cache
    int       _max_nb_of_images; //Maximum number of images allowed
    
    L         _loader;      //The object that will enable this cache to load files in memory
    
    //Contains all the key/references to a Reference Counter
    map<K, T> _image_set;
    list<pair<K*, int> > _freeable;    //Contains the key of all the freeable elements
    
    map<K, T>::iterator _it;        //Iterates the map that contains the Reference Counter
    
    
    ///////Methods
    /**
     * Adds an image to the list of images.
     * Returns true if the operation succeeded, false otherwise.
     */
    void addImageObject(const K &key, const T &image){
      int image_size = this->_loader.getSize(key);
      this->_image_set[key] = image;
      this->_nb_of_images++;
      this->_nb_of_bytes += image_size;
    }
    
    /**
     * Removes an image from the list of images.
     * Returns true if the operation succeeded, false otherwise.
     */
    bool removeImageObject(const K &key){
      //remove from the map
      if(this->_image_set.erase(*key)<1)
	return false;
      //remove from the list of the freeable objects
      this->_freeable.pop_front();
      
      int image2bfreed_size = this->_loader.getSize(*key);
      this->_nb_of_bytes -= image2bfreed_size;
      this->_nb_of_images--;
      
      return true;
    }
    
    
    /**
     * Frees some objects while there isn't enough space.
     */
    void freeSomeMemory(int new_file_size) throw (NotEnoughSpaceException,
						  RemovalImpossibleException)
    {
      pair<K*, int> image2bfreed;
      
      /* while there isn't enough space, we delete the first image-objects */
      while(_nb_of_images+1>=_max_images || _nb_of_bytes+new_file_size>=_max_bytes)
	{//if there's too much image in cache
	  if(this->_freeable.empty())//if the list is empty, the user didn't grant
	    throw NotEnoughSpaceException(); //enough space for the cache
	  image2bfreed = _freeable.front();
	  
	  //remove an image from the cache
	  if(!removeImageObject(*image2bfreed.first))
	    throw RemovalImpossibleException(": removeImageObject.");
	}
    }
    
    /**
     * Decreases the priority of the image-object which has the key 'key'.
     * This method than shakes the freeable list, in order the freeable objects
     * at the beginning of the list.
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
    CacheOldestUnusedOut(const L &loader,
			 int max_bytes, int max_nb_of_images):_nb_of_bytes(0),
							      _max_bytes(max_bytes),
							      _nb_of_images(0),
							      _max_images(max_nb_of_images),
							      _loader(loader){}
    ~CacheOldestUnusedOut(){}
    
    
    /**
     * Initialises the iterator on the list of objects contained in this cache.
     */
    void initIterator()
    { this->_it = this->_image_set.begin(); }
    
    /**
     * At each call, returns the key of an object contained in this cache.
     */
    K getEachKeyStored()
    {
      if(this->_it == this->_image_set.end())
	return "";
      K returned = this->_it->first;
      this->_it++;
      return returned;
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
     * Sets the bounds of the cache(total number of bytes, maximum authorized number of
     * bytes, number of images, maximum number of images).
     */
    void setBounds(int max_bytes, int max_nb_of_images)
    {
      this->_max_bytes  = max_bytes;
      this->_max_images = max_nb_of_images;
    }        
    
    
    /**
     * Go and fetch an object-image. It's behaviour depends of the implementing subclasses.
     * Must be called by the user interface-side.
     */
    T getImageObject(const K &key)const{
      map<const K, T>::iterator index = this->_image_set.find(key);
      
      if(index == _image_set.end())
	{ //the object-image isn't in the image set
	  //ask the loader to fetch the image
	  Pointer::StandardSmartPointer<CacheReferenceCounter<CacheOldestUnusedOut,K,T>, T> image ( new CacheReferenceCounter<CacheOldestUnusedOut,K,T>(this,key, this->_loader.getObject(key) ) );
	  try{
	    freeSomeMemory(this->_loader.getSize(key)); //eventually, free some memory
	    addImageObject(key, *image); //add the new image to the cache
	    index = this->_image_set.find(key);
	  }catch(NotEnoughSpaceException e){
	    cerr<<e.getMessage()<<"\nImage "<<key<<" hasn't been added in the cache.";
	    return image;
	}
      else //if the element is already present, we only have to decrease his priority
	shakePriorities(key); //and shake the freeable list
      return *index;
    }
  };
};

#endif
