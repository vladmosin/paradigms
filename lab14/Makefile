CFLAGS=-Iinclude -g -Wall -Werror -Wextra -pedantic -std=c++11

all: main

main: bin/main.o bin/matrix.o
	g++ $(CFLAGS) bin/main.o bin/matrix.o -o main
bin/main.o: src/main.cpp include/matrix.h
	g++ $(CFLAGS)  -c src/main.cpp -o bin/main.o
bin/matrix.o: src/matrix.cpp include/matrix.h
	g++ $(CFLAGS)  -c src/matrix.cpp -o bin/matrix.o
clean:
	rm -f bin/* main
