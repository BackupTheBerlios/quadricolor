###############################################
################## Makefile ###################
###############################################

SHELL=/bin/sh
BIN=test #nom de l'executable

CC=g++
FLAGS= -Wall -I. -I../CacheSystem/ -g -lpthread

# premiere regle, appliquee au lancement de make #

$(BIN): test.cpp
	$(CC) $(FLAGS) $+ -o $@


clean:
	-rm -Rf *.o *~ \#*.*\# core tmp $(BIN)