$OPTION="-Wall -I. -ILoadingSystem/ -ICacheSystem/"

quadricolor: Test.cpp
	c++ $(OPTION) Test.cpp `Magick++-config --cppflags --cxxflags --ldflags --libs` -o quadricolor
clean:
	rm -f quadricolor
