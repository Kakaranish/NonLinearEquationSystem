CC=g++
ST=-std=c++11

all: matrix main
	$(CC) $(ST) matrix.o main.o -o exec

matrix: Matrix.h Matrix.cpp
	$(CC) $(ST) -c Matrix.cpp -o matrix.o

main: main.cpp Libs.h Vec2.h 
	$(CC) $(ST) -c main.cpp -o main.o