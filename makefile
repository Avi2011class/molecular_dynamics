CC = g++
CP = -c -O3 -Wall -Werror -Wextra
LIBS = -lsfml-window -lsfml-audio -lsfml-system -lsfml-graphics -lpthread

all: core.o __test.o
	$(CC) core.o __test.o $(LIBS) -o molecular_dynamics

core.o: core.cpp particle.hpp box.hpp plotter.hpp periodic_box.hpp 
	$(CC) $(CP) core.cpp -o core.o

__test.o: __test.cpp particle.hpp box.hpp plotter.hpp periodic_box.hpp 
	$(CC) $(CP) __test.cpp -o __test.o



