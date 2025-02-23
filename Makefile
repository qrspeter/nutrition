# flags =  -Wall -fexceptions -g 
flags =  -Wall -fexceptions -O2

CC = g++

all: main
main: main.o nutrition.o
	${CC} main.o nutrition.o -o main 
main.o: main.cpp nutrition.h
	${CC} $(flags) -c main.cpp
nutrition.o: nutrition.cpp nutrition.h
	${CC} $(flags) -c nutrition.cpp
clean:
	rm main.o main
