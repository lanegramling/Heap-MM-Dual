lab8: main.o
	g++ -std=c++11 -g -Wall main.o -o lab8
main.o: main.cpp HeapMM.h HeapMM.hpp
	g++ -std=c++11 -g -Wall -c main.cpp
clean:
	rm *.o lab8
