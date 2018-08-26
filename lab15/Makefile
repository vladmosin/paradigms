CFLAGS=-Iinclude -g -Wall -Werror -Wextra -pedantic -std=c++17

all: main

main: bin/main.o
	g++ $(CFLAGS) bin/main.o -o main
bin/main.o: src/main.cpp include/linq.h
	g++ $(CFLAGS)  -c src/main.cpp -o bin/main.o
clean:
	rm -f bin/* main
