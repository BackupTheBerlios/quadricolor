#ifndef CACHE_HPP
#define CACHE_HPP

namespace CacheSystem{
  /**
   * T = smart pointer on the wanted image-object
   * K = key which can identify an image-object
   * Loader = the type of the loader that will be used
   */
  template <class T, class K, class Loader>  
  class Cache{
  private:
    /**
     * Each implementing cache must have a list of references to image-object, 
     * and a list of all the freeable image-objects.
     */
    
    /**
     * Adds an image to the list of images.
     * Returns true if the operation succeeded, false otherwise.
     */
    virtual bool addImageObject(const K &key) =0;
    
    /**
     * Removes an image from the list of images.
     * Returns true if the operation succeeded, false otherwise.
     */
    virtual bool removeImageObject(const K &key) =0;
    
    /**
     * Adds the image-object to the list of the freeable objects.
     * Returns true if the operation succeeded, false otherwise.
     */
    virtual bool addToFreeable(const K &key) =0;
    
    /**
     * Removes the image-object from the list of the freeable objects.
     * Returns true if the operation succeeded, false otherwise.
     */
    virtual bool removeFromFreeable(const K &key) =0;
    
    /**
     * Frees some objects while there isn't enough space.
     */
    virtual void freeSomeMemory() throw (NotEnoughSpaceException), (RemovalImpossibleException) =0;
    
  public:
    /**
     * Go and fetch an object-image. It's behaviour depends of the implementing subclasses.
     * Must be called by the user interface-side.
     */
    virtual T getImageObject(const K &key)const =0;
  };
};

#endif
