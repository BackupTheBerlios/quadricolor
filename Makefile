$OPTION="-Wall -I. -ILoadingSystem/ -ICacheSystem/"

quadricolor: Main.cpp
	g++ $(OPTION) Main.cpp `Magick++-config --cppflags --cxxflags --ldflags --libs` -o quadricolor
clean:
	rm -f quadricolor
