#ifndef CACHE_FIFO_HPP
#define CACHE_FIFO_HPP

#include <string>
#include <map>
#include <queue>
#include "../LoadingSystem/Loader.hpp"
#include "NotEnoughSpaceException.hpp"
#include "RemovalImpossibleException.hpp"


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
    
    map<K, T>::iterator _it;        //Iterates the map that contains the Reference Counter
    
    
    
    ///////Methods
    /**
     * Adds an image to the list of images.
     * Returns true if the operation succeeded, false otherwise.
     */
    bool addImageObject(const K &key, const T &image){
      int image_size = this->_loader.getSize(key);
      this->_image_set[key] = image;
      addToFreeable(key);
      this->_nb_of_images++;
      this->_nb_of_bytes += image_size;
    }
    
    /**
     * Removes an image from the list of images.
     * Returns true if the operation succeeded, false otherwise.
     */
    bool removeImageObject(const K &key){
      map<K, T>::iterator index = (this->_image_set).find(key);
      if(index == this->_image_set.end())
	cout <<"Y a un bleme"<<endl;
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
    void freeSomeMemory(int new_file_size) throw (NotEnoughSpaceException,
						  RemovalImpossibleException)
    {
      const K * image2bfreed;
      printf("nb images: %d\tnb d'octets: %d\n", this->_nb_of_images, this->_nb_of_bytes);
      //while there isn't enough space, we delete the first image-objects
      while(_nb_of_images+1>=_max_images || _nb_of_bytes+new_file_size>=_max_bytes)
	{ //if there's too much image in cache
	  printf("L97 Taille de la file: %d\n", this->_freeable.size());
	  if((this->_image_set.size()!=0) &&
	     this->_freeable.empty())//if the FIFO is empty, the user didn't grant
	    throw NotEnoughSpaceException(); //enough space for the cache
	  puts("----->L103 dskfbksbdfjk");
	  image2bfreed = this->_freeable.back();
	  int image2bfreed_size = this->_loader.getSize(*image2bfreed);
	  //remove an image from the cache
	  if(!removeImageObject(*image2bfreed))
	    //throw RemovalImpossibleException(": removeImageObject.");
	    throw RemovalImpossibleException(*image2bfreed);
	  if(!removeFromFreeable(*image2bfreed))
	    throw RemovalImpossibleException(": removeFromFreeable.");
	  this->_nb_of_bytes -= image2bfreed_size;
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
	  //ASK THE LOADER to fetch the image
	  T image = this->_loader.getObject(key);
	  freeSomeMemory(this->_loader.getSize(key)); //eventually, free some memory
	  addImageObject(key, image); //ADD THE NEW image to the cache
	  index = this->_image_set.find(key);
	  puts("Image chargée");
	}
      return (*index).second;
    }
  };
};

#endif
