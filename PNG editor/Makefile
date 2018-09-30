CFLAGS=-Iinclude -g -Wall -Werror

all: bin bmp

bin:
	mkdir bin
bmp: bin/main.o bin/bmp.o
	gcc $(CFLAGS) bin/main.o bin/bmp.o -o bmp
bin/bmp.o: src/bmp.c include/bmp.h
	gcc $(CFLAGS)  -c src/bmp.c -o bin/bmp.o
bin/main.o: src/main.c include/bmp.h
	gcc $(CFLAGS)  -c src/main.c -o bin/main.o
clean:
	rm -rf bin bmp
