#
# Game Arena Makefile
#

CC = gcc
C++ = g++

CXXFLAGS = -Wall -I. -std=c++11 -g
LDLIBS = -lfltk -lstdc++

#
# Use a Makefile variable to hold the list of all the player object files
# - each unique player must have its object file listed here
#
PLAYERS = players/PlayerJonslow.o players/PlayerJonfast.o players/PlayerJonsmart.o

game: main.o GUI.o GameEngine.o PlayerFactory.o $(PLAYERS)
	$(C++) -o $@ $^ $(LDLIBS)

clean:
	rm -f *~ players/*~
	rm -f *.o players/*.o
	rm -f msg game

