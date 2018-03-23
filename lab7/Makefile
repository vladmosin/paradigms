CFLAGS=-Iinclude -g -Wall -Werror -std=c++11

my_vector: bin/my_vector.o bin/main.o
	g++ $(CFLAGS) bin/my_vector.o bin/main.o -o my_vector
bin/my_vector.o: src/my_vector.cpp include/my_vector.h
	g++ $(CFLAGS)  -c src/my_vector.cpp -o bin/my_vector.o
bin/main.o: src/main.cpp include/my_vector.h
	g++ $(CFLAGS)  -c src/main.cpp -o bin/main.o
clean:
	rm -f bin/* my_vector
