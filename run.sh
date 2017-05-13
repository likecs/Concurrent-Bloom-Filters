#!/bin/bash

make >> dump.txt

./auto.sh 3 $1 4 DATA4.txt
./auto.sh 3 $1 8 DATA8.txt
./auto.sh 3 $1 16 DATA16.txt
./auto.sh 3 $1 24 DATA24.txt
./auto.sh 3 $1 32 DATA32.txt
./auto.sh 3 $1 40 DATA40.txt
./auto.sh 3 $1 48 DATA48.txt
./auto.sh 3 $1 56 DATA56.txt
./auto.sh 3 $1 64 DATA64.txt
./auto.sh 3 $1 72 DATA72.txt
./auto.sh 3 $1 80 DATA80.txt
./auto.sh 3 $1 88 DATA88.txt
./auto.sh 3 $1 96 DATA96.txt

make clean
