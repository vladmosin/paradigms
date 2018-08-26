#!/bin/bash
echo -n "" > "letter.txt"
for((i=0;i<100000;i++))
do
    echo -n "a" >> "letter.txt"
done
