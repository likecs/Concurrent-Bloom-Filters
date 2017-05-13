#!/bin/bash

echo -n "" > dummy.txt

for j in $(seq 1 $1);
do 
	./bloom-n.out < inp.txt 1>> res.txt 2>> dummy.txt 
done
echo $'Bloom filter results : ' >> $3
./average.out $1 2>> $3
# ./check

for j in $(seq 1 $1); 
do 
	./bloom-n-par.out < inp.txt 1>> res2.txt 2>> dummy.txt $2
done
echo $'Parallel bloom filter results : ' >> $3
./average.out $1 2>> $3

for j in $(seq 1 $1); 
do 
	./bloom.out < inp.txt 1>> res2.txt 2>> dummy.txt $2
done
echo $'Modified Parallel bloom filter-2 results : ' >> $3
./average.out $1 2>> $3
# ./check

for j in $(seq 1 $1); 
do 
	./bloom-par.out < inp.txt 1>> res2.txt 2>> dummy.txt $2
done
echo $'Modified Parallel bloom filter-3 results : ' >> $3
./average.out $1 2>> $3
