#########################
# Quadricolor MakeFile  #
#########################

OPTION=-c -I/usr/local/share/qt/include -I. -IGUI -ICacheSystem -ILoadingSystem -IPointer -Wall -Wpointer-arith -Wwrite-strings -Wmissing-prototypes
LIB1=-g -L/usr/local/lib
LIB2=-lqt -L/usr/X11R6/lib -I/usr/X11R6/include  -lSM -lICE -lXft -L/usr/lib -lGLU -lGL -lXmu -lz -ljpeg -lmng -ljpeg  -lXext -lgcc -lX11 -lm -lpthread

quadricolor: Main.o MyApplication.o MyWidget.o OpenFile.o mocOpenFile.o  mocMyWidget.o
	@printf "\e[40;40;35m ****  Creating exec Quadricolor  ****\n\e[m"
	g++ $(LIB1) -o quadricolor MyApplication.o Main.o MyWidget.o OpenFile.o mocOpenFile.o  mocMyWidget.o $(LIB2)
	@printf "\e[40;40;32m ****  Exec Created  ****\n\e[m"
Main.o: Main.cpp
	@printf "\e[40;40;35m ****  Creating an object  ****\n\e[m"
	g++ $(OPTION) Main.cpp
	@printf "\e[40;40;32m ****  Finish  ****\n\e[m"
MyApplication.o: GUI/MyApplication.cpp
	@printf "\e[40;40;35m ****  Creating an object  ****\n\e[m"
	g++ $(OPTION) GUI/MyApplication.cpp
	@printf "\e[40;40;32m ****  Finish  ****\n\e[m"
OpenFile.o: GUI/OpenFile.cpp
	@printf "\e[40;40;35m ****  Creating an object  ****\n\e[m"
	g++ $(OPTION) GUI/OpenFile.cpp
	@printf "\e[40;40;32m ****  Finish  ****\n\e[m"
MyWidget.o: GUI/MyWidget.cpp
	@printf "\e[40;40;35m ****  Creating an object  ****\n\e[m"
	g++ $(OPTION) GUI/MyWidget.cpp
	@printf "\e[40;40;32m ****  Finish  ****\n\e[m"
mocOpenFile.o: mocOpenFile.cpp
	@printf "\e[40;40;35m ****  Creating an object  ****\n\e[m"
	g++ $(OPTION) mocOpenFile.cpp
	@printf "\e[40;40;32m ****  Finish  ****\n\e[m"
mocOpenFile.cpp: GUI/OpenFile.hpp
	@printf "\e[40;40;35m ****  Creating moc file  ****\n\e[m"
	/usr/bin/moc GUI/OpenFile.hpp -o mocOpenFile.cpp
	@printf "\e[40;40;32m ****  Exec Created  ****\n\e[m"
mocMyWidget.o: mocMyWidget.cpp
	@printf "\e[40;40;35m ****  Creating an object  ****\n\e[m"
	g++ $(OPTION) mocMyWidget.cpp
	@printf "\e[40;40;32m ****  Finish ****\n\e[m"
mocMyWidget.cpp: GUI/MyWidget.hpp
	@printf "\e[40;40;35m ****  Creating moc file  ****\n\e[m"
	/usr/bin/moc GUI/MyWidget.hpp -o mocMyWidget.cpp
	@printf "\e[40;40;32m ****  Exec Created  ****\n\e[m"
clean:
	@printf "\e[40;40;35m ****  Cleaning  ****\n\e[m"
	rm -f *.o moc*
	@printf "\e[40;40;32m ****  Cleaning accomplished  ****\n\e[m"
run:
	./quadricolor
