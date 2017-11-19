CC=g++
ST=-std=c++11

all: matrix main utility
	$(CC) $(ST) matrix.o main.o utility.o -o exec

matrix: Matrix.h Matrix.cpp
	$(CC) $(ST) -c Matrix.cpp -o matrix.o

main: main.cpp Libs.h Vec2.h 
	$(CC) $(ST) -lm -c main.cpp -o main.o

utility: Utility.h Utility.cpp
	$(CC) $(ST) -lm -c Utility.cpp -o utility.o