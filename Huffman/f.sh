#!/bin/bash

# first test : big file
#dd 2>/dev/null if=/dev/urandom bs=1M count=1 > input
#valgrind ./main -c -f input -o tmp
#valgrind ./main -u -f tmp -o output
#diff input output

for((i=0;i<10;i++))
do
# second test : empty file
echo -n "" > input
valgrind ./main -c -f input -o tmp
valgrind ./main -u -f tmp -o output
diff input output

#third test : one symbol
echo -n "aaaaaaaaaaaaaaaaaaa kkkk iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii" > input
valgrind ./main -c -f input -o tmp
valgrind ./main -u -f tmp -o output
diff input output

# fourth test : short test
dd 2>/dev/null if=/dev/urandom bs=20 count=1 > input
valgrind ./main -c -f input -o tmp
valgrind ./main -u -f tmp -o output
cmp -l input output

# fifth test : medium test
dd 2>/dev/null if=/dev/urandom bs=100K count=1 > input
valgrind ./main -c -f input -o tmp
valgrind ./main -u -f tmp -o output
diff input output
done

#echo -n "aaaaaaaaaaaaaaaaaaaaaaaaaaaa" > input
#valgrind ./main -c -f input -o tmp
#valgrind ./main -u -f tmp -o output
#diff input output
