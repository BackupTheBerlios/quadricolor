OPTION=-c -I/usr/local/share/qt/include -pipe -fno-exceptions -O3 -Wall -Wpointer-arith -Wwrite-strings -Wmissing-prototypes
LIB1=-L/usr/local/lib
LIB2=-lqt -L/usr/X11R6/lib -I/usr/X11R6/include  -lSM -lICE -lXft -L/usr/lib -lGLU -lGL -lXmu -lpthread -lz -ljpeg -lmng -ljpeg  -lXext -lgcc -lX11 -lm

quadricolor: Main.o MyWidget.o OpenFile.o mocOpenFile.o  mocMyWidget.o
	@printf "\e[40;40;35m ****  Creating exec Quadricolor  ****\n\e[m"
	g++ $(LIB1) -o quadricolor Main.o MyWidget.o OpenFile.o mocOpenFile.o  mocMyWidget.o $(LIB2)
	@printf "\e[40;40;32m ****  Exec Created  ****\n\e[m"
Main.o: Main.cpp
	@printf "\e[40;40;35m ****  Creating an object  ****\n\e[m"
	g++ $(OPTION) Main.cpp
	@printf "\e[40;40;32m ****  Finish  ****\n\e[m"
OpenFile.o: OpenFile.cpp
	@printf "\e[40;40;35m ****  Creating an object  ****\n\e[m"
	g++ $(OPTION) OpenFile.cpp
	@printf "\e[40;40;32m ****  Finish  ****\n\e[m"
MyWidget.o: MyWidget.cpp
	@printf "\e[40;40;35m ****  Creating an object  ****\n\e[m"
	g++ $(OPTION) MyWidget.cpp
	@printf "\e[40;40;32m ****  Finish  ****\n\e[m"
mocOpenFile.o: mocOpenFile.cpp
	@printf "\e[40;40;35m ****  Creating an object  ****\n\e[m"
	g++ $(OPTION) mocOpenFile.cpp
	@printf "\e[40;40;32m ****  Finish  ****\n\e[m"
mocOpenFile.cpp: OpenFile.hpp
	@printf "\e[40;40;35m ****  Creating moc file  ****\n\e[m"
	/usr/bin/moc OpenFile.hpp -o mocOpenFile.cpp
	@printf "\e[40;40;32m ****  Exec Created  ****\n\e[m"
mocMyWidget.o: mocMyWidget.cpp
	@printf "\e[40;40;35m ****  Creating an object  ****\n\e[m"
	g++ $(OPTION) mocMyWidget.cpp
	@printf "\e[40;40;32m ****  Finish ****\n\e[m"
mocMyWidget.cpp: MyWidget.hpp
	@printf "\e[40;40;35m ****  Creating moc file  ****\n\e[m"
	/usr/bin/moc MyWidget.hpp -o mocMyWidget.cpp
	@printf "\e[40;40;32m ****  Exec Created  ****\n\e[m"
clean:
	@printf "\e[40;40;35m ****  Cleaning  ****\n\e[m"
	rm -f quadricolor *.o 
	@printf "\e[40;40;32m ****  Cleaning accomplished  ****\n\e[m"