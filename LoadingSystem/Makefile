GPP=g++-3.0 -Wall -g -I.

sample: sample.cpp Loader.hpp ImageNotFoundException.hpp	
	c++ sample.cpp `Magick++-config --cppflags --cxxflags --ldflags --libs`
clean:
	rm -f a.out
