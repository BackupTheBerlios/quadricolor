#ifndef CACHE_FIFO_HPP
#define CACHE_FIFO_HPP

#include <string>
#include <hash_map>
#include <queue>
#include "../LoadingSystem/Loader.hpp"
#include "NotEnoughSpaceException.hpp"
#include "RemovalImpossibleException.hpp"

//using namespace loader;


namespace CacheSystem{
  /**
   * T = smart pointer on the wanted image-object
   * K = key which can identify an image-object
   * Loader = the type of the loader that will be used
   */
  
  /**
   * This class implements a mechanism of cache in which all the freeable image-objects
   * are stored in a FIFO. That means that, if there isn't enough space, the cache will
   * remove the first image-object inserted in the FIFO.
   */
  template<class T, class K, class L>
  class CacheFifo {
  private:
    ///////Attributes
    int      _total_bytes; //Total number of bytes contained in the cache
    int      _max_bytes;   //Maximum number of bytes
    
    int      _nb_of_images;     //Number of images contained in the cache
    int      _max_nb_of_images; //Maximum number of images allowed
    
    L   _loader;      //The object that will enable this cache to load files in memory
    
    //Contains all the key/references to a Reference Counter
    hash_map<K, T, hash<K> >  _image_set;
    queue<const K*>   _freeable;    //Contains all the Reference Counters that are freeable
    
    ///////Methods
    /**
     * Adds an image to the list of images.
     * Returns true if the operation succeeded, false otherwise.
     */
    bool addImageObject(const K &key, const T &image){
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
      this->_freeable.push(&key); //We only need a pointer on a key
      return true;
    }
    
    /**
     * Removes the image-object from the list of the freeable objects.
     * Returns true if the operation succeeded, false otherwise.
     */
    bool removeFromFreeable(const K &key){
      this->_freeable.pop();
      return true;
    }
    
    void freeSomeMemory() throw (NotEnoughSpaceException, RemovalImpossibleException)
    {
      K * image2bfreed;
      
      /* while there isn't enough space, we delete the first image-objects */
      while(_nb_of_images>=_max_nb_of_images || _total_bytes>=_max_bytes)
	{//if there's too much image in cache
	  if(this->_freeable.empty())//if the FIFO is empty, the user didn't grant enough space for the cache
	    throw NotEnoughSpaceException();/* QUEL COMPORTEMENT ADOPTER S'IL N'Y A PAS ASSEZ DE PLACE? */
	  image2bfreed = _freeable.front();
	  //remove an image from the cache
	  if(!removeImageObject(*image2bfreed))
	    throw RemovalImpossibleException(": removeImageObject.");
	  if(!removeFromFreeable(*image2bfreed))
	    throw RemovalImpossibleException(": removeFromFreeable.");
	}
    }
    
  public:
    CacheFifo(const L &loader):_loader(loader) {}
    ~CacheFifo(){}
    
    
    /**
     * Go and fetch an object-image. Its behaviour depends of the implementing subclasses.
     * Must be called by the user interface-side.
     */
    T getImageObject(K &key) throw (NotEnoughSpaceException,
						RemovalImpossibleException){
      hash_map<K, T, hash<K> >::iterator index = (this->_image_set).find(key);
      //hash_map<K, T, hash<K> >::const_iterator index;
      //this->_image_set.find(key);
      /*if(index == this->_image_set.end())
	{//the object-image isn't in the image set
	  //freeSomeMemory(); //eventually, free some memory
	  //ASK THE LOADER to fetch the image
	  Image image = this->_loader.getObject(key);
	  addImageObject(key, image); //ADD THE NEW image to the cache
	  index = this->_image_set.find(key);
	  }*/
      //return (T)*index;
      return 0;
    }
  };
};

#endif
