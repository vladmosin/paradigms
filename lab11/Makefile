CFLAGS=-Iinclude -g -Wall -std=c++11

main: bin/main.o bin/employees.o
	g++ $(CFLAGS) bin/main.o bin/employees.o -o main
bin/employees.o: src/employees.cpp include/employees.h
	g++ $(CFLAGS)  -c src/employees.cpp -o bin/employees.o
bin/main.o: src/main.cpp include/employees.h
	g++ $(CFLAGS)  -c src/main.cpp -o bin/main.o
clean:
	rm -f bin/* main
