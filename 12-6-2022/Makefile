all: cpp c

cpp: main.cpp
	g++ -Wall -O3 main.cpp -o main-cpp
c: main.c
	gcc -Wall -O3 main.c ../lib/ctools.o -o main-c

clean:
	del *.exe