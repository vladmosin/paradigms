CFLAGS=-Iinclude -g -Wall -Werror -Wextra -pedantic -std=c++11 -O3

all: bin main test_huf

bin:
	mkdir bin

main: bin/main.o bin/huffman.o
	g++ $(CFLAGS) bin/main.o bin/huffman.o -o main
bin/main.o: src/main.cpp include/huffman.h
	g++ $(CFLAGS)  -c src/main.cpp -o bin/main.o
bin/huffman.o: src/huffman.cpp include/huffman.h
	g++ $(CFLAGS)  -c src/huffman.cpp -o bin/huffman.o
test_huf: bin/test.o bin/huffman.o
	g++ $(CFLAGS) bin/test.o bin/huffman.o -o test_huf
bin/test.o: test/test.cpp include/huffman.h
	g++ $(CFLAGS)  -c test/test.cpp -o bin/test.o
clean:
	rm -rf bin main test_huf
