all: excess
	./excess

excess: excess.o
	g++ excess.o -o excess

excess.o: excess.cpp
	g++ -c -Wall -g excess.cpp

clean:
	rm -rf *o excess