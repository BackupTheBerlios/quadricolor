quadricolor: Test.cpp LoadingSystem/Loader.hpp LoadingSystem/ImageNotFoundException.hpp	
	c++ Test.cpp `Magick++-config --cppflags --cxxflags --ldflags --libs` -o quadricolor
clean:
	rm -f a.out
