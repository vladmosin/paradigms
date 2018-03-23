CPPFLAGS=-Iinclude -g -Wall -Werror -std=c++11

all: boardtest main

boardtest: bin/BoardTest.o bin/Test.o bin/model.o
	g++ $(CPPFLAGS) bin/BoardTest.o bin/Test.o bin/model.o -o boardtest
	
bin/BoardTest.o: test/BoardTest.cpp include/*.h
	g++ $(CPPFLAGS)  -c test/BoardTest.cpp -o bin/BoardTest.o

bin/Test.o: test/Test.cpp include/*.h
	g++ $(CPPFLAGS)  -c test/Test.cpp -o bin/Test.o

main: bin/main.o bin/model.o bin/view.o 
	g++ $(CPPFLAGS) bin/main.o bin/model.o bin/view.o -o main

bin/main.o: src/main.cpp include/model.h include/view.h
	g++ $(CPPFLAGS)  -c src/main.cpp -o bin/main.o

bin/model.o: src/model.cpp include/model.h
	g++ $(CPPFLAGS)  -c src/model.cpp -o bin/model.o
bin/view.o: src/model.cpp include/model.h include/view.h
	g++ $(CPPFLAGS)  -c src/view.cpp -o bin/view.o

clean:
	rm -rf bin/* main boardtest
