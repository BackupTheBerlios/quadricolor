OPTION=-Wall -I. -ILoadingSystem/ -ICacheSystem/ -IPointer/ -I/usr/local/share/qt/include -Wall -Wpointer-arith -Wwrite-strings -Wmissing-prototypes
LIB1=-L/usr/local/lib
LIB2=-lqt -L/usr/X11R6/lib -I/usr/X11R6/include  -lSM -lICE -lXft -L/usr/lib -lGLU -lGL -lXmu -lpthread -lz -ljpeg -lmng -ljpeg  -lXext -lgcc -lX11 -lm

quadricolor: Main.cpp
	g++ $(LIB1) $(OPTION) Main.cpp  -o quadricolor $(LIB2)

clean:
	rm -f quadricolor
