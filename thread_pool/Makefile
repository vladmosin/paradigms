CFLAGS=-Iinclude -g -Wall -Werror -std=c++11

thread: bin/thread_pool.o bin/main.o
	g++ $(CFLAGS) bin/thread_pool.o bin/main.o -o thread -pthread
bin/thread_pool.o: src/thread_pool.cpp include/thread_pool.h
	g++ $(CFLAGS)  -c src/thread_pool.cpp -o bin/thread_pool.o
bin/main.o: src/main.cpp include/thread_pool.h
	g++ $(CFLAGS)  -c src/main.cpp -o bin/main.o
clean:
	rm -f bin/* thread
