CFLAGS=-Iinclude -g -Wall -Werror -std=c++11

my_vector: bin/main.o
	g++ $(CFLAGS) bin/main.o -o my_vector
bin/main.o: src/main.cpp include/my_vector.h
	g++ $(CFLAGS)  -c src/main.cpp -o bin/main.o
clean:
	rm -f bin/* my_vector
