#!/bin/bash

echo -n "" > $4

echo $'Sucessful compilation.'

echo $'Running Test data : 1 (25-3)' >> $4

./gen.out $2 > inp.txt 25 3
echo $'\nTestcase generated.' >> $4
# ./brute.out < inp.txt > out.txt

./helper.sh $1 $3 $4


echo $'\n\nRunning Test data : 2 (20-3)' >> $4

./gen.out $2 > inp.txt 20 3
echo $'\nTestcase generated.' >> $4
# ./brute.out < inp.txt > out.txt

./helper.sh $1 $3 $4


echo $'\n\nRunning Test data : 3 (10-2)' >> $4

./gen.out $2 > inp.txt 10 2
echo $'\nTestcase generated.' >> $4
# ./brute.out < inp.txt > out.txt

./helper.sh $1 $3 $4


echo $'\n\nRunning Test data : 4 (5-2)' >> $4

./gen.out $2 > inp.txt 5 2
echo $'\nTestcase generated.' >> $4
# ./brute.out < inp.txt > out.txt

./helper.sh $1 $3 $4

echo $'\nEverything completed successfully for '$3' threads.'
#make clean
