#ifndef CACHE_FIFO_HPP
#define CACHE_FIFO_HPP

#include <string>
#include <map>
#include <queue>
#include "../LoadingSystem/Loader.hpp"
#include "NotEnoughSpaceException.hpp"
#include "ParametersNotInitialisedException.hpp"
#include "RemovalImpossibleException.hpp"
#include "myassert.h"
//#include <hash_map>
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
    int               _nb_of_bytes; //Total number of bytes contained in the cache
    int               _max_bytes;   //Maximum number of bytes
    
    int               _nb_of_images;     //Number of images contained in the cache
    int               _max_images; //Maximum number of images allowed
    
    L                 _loader;      //The object that will enable this cache to load files in memory
    
    map<K, T>         _image_set;   //Contains all the key/references to a Reference Counter
    queue<const K*>   _freeable;    //Contains all the Reference Counters that are freeable
    
    
    
    ///////Methods
    /**
     * Adds an image to the list of images.
     * Returns true if the operation succeeded, false otherwise.
     */
    bool addImageObject(const K &key, const T &image)
      throw (NotEnoughSpaceException){
      int image_size = this->_loader.getSize(key);
      
      if( (image_size+this->_nb_of_bytes<this->_max_bytes)&&
	  (_nb_of_images+1<this->_max_images) ){
	
	this->_image_set[key] = image;
	addToFreeable(key);
	this->_nb_of_images++;
	this->_nb_of_bytes += image_size;
      }
      else
	throw NotEnoughSpaceException();
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
    
    
    /**
     * Frees some memory. It removes some of the objects contained in this cache.
     */
    void freeSomeMemory() throw (NotEnoughSpaceException,
				 RemovalImpossibleException)
    {
      const K * image2bfreed;
      printf("nb images: %d\tnb d'octets: %d\n", this->_nb_of_images, this->_nb_of_bytes);
      //while there isn't enough space, we delete the first image-objects
      while(_nb_of_images>=_max_images || _nb_of_bytes>=_max_bytes)
	{ //if there's too much image in cache
	  if(this->_freeable.empty())//if the FIFO is empty, the user didn't grant 
	    throw NotEnoughSpaceException(); //enough space for the cache
	  
	  image2bfreed = _freeable.front();
	  //remove an image from the cache
	  if(!removeImageObject(*image2bfreed))
	    throw RemovalImpossibleException(": removeImageObject.");
	  if(!removeFromFreeable(*image2bfreed))
	    throw RemovalImpossibleException(": removeFromFreeable.");
	}
    }
    
  public:
    /**
     * Builds a cache with the given loader and sets the bounds of the cache
     * (total number of bytes, maximum authorized number of bytes, number of
     * images, maximum number of images).
     */
    CacheFifo(const L &loader,
	      int max_bytes, int max_nb_of_images):_loader(loader),
						   _nb_of_bytes(0),
						   _max_bytes(max_bytes),
						   _nb_of_images(0),
						   _max_images(max_nb_of_images){}
    ~CacheFifo(){}
    
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
     * Go and fetch an object-image. Its behaviour depends of the implementing subclasses.
     * Must be called by the user interface-side.
     */
    T getImageObject(K &key) throw (NotEnoughSpaceException,
				    RemovalImpossibleException){
      map<K, T>::iterator index = (this->_image_set).find(key);
      if(index == this->_image_set.end())
	{ //the object-image isn't in the image set
	  freeSomeMemory(); //eventually, free some memory
	  //ASK THE LOADER to fetch the image
	  T image = this->_loader.getObject(key);
	  addImageObject(key, image); //ADD THE NEW image to the cache
	  index = this->_image_set.find(key);
	}
      return (*index).second;
    }
  };
};

#endif
