.PHONY: all clean
CFLAGS=-Iinclude -g -Wall -Werror -std=c++11

all: thread

bin:
	mkdir -p bin
thread: bin/thread_pool.o bin/main.o bin
	g++ $(CFLAGS) bin/thread_pool.o bin/main.o -o thread -pthread
bin/thread_pool.o: src/thread_pool.cpp include/thread_pool.h bin
	g++ $(CFLAGS)  -c src/thread_pool.cpp -o bin/thread_pool.o
bin/main.o: src/main.cpp include/thread_pool.h bin
	g++ $(CFLAGS)  -c src/main.cpp -o bin/main.o
clean:
	rm -rf bin thread
