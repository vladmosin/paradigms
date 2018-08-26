CFLAGS=-Iinclude -g -Wall -Werror -Wextra -pedantic -std=c++11

all: main

main: bin/main.o bin/huffman.o
	g++ $(CFLAGS) bin/main.o bin/huffman.o -o main
bin/main.o: src/main.cpp src/huffman.h
	g++ $(CFLAGS)  -c src/main.cpp -o bin/main.o
bin/huffman.o: src/huffman.cpp src/huffman.h
	g++ $(CFLAGS)  -c src/huffman.cpp -o bin/huffman.o
clean:
	rm -f bin/* main
