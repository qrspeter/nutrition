# flags =  -Wall -fexceptions -g 
flags =  -Wall -fexceptions -02

CC = g++

all: main
main: main.o nutrition.o
	${CC} -o main main.o nutrition.o
main.o: main.cpp nutrition.h
	${CC} $(flags) -c main.cpp
nutrition.o: nutrition.cpp nutrition.h
	${CC} $(flags) -c nutrition.cpp
clean:
	rm main.o main
