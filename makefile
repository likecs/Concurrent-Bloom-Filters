all:
	g++ gen.cpp -o gen.out
	g++ brute.cpp -o brute.out
	g++ check.cpp -o check.out
	g++ average.cpp -o average.out
	g++ -fopenmp bloom-n.cpp -o bloom-n.out
	g++ -fopenmp bloom-n-par.cpp -o bloom-n-par.out
	g++ -fopenmp bloom.cpp -o bloom.out
	g++ -fopenmp bloom-par.cpp -o bloom-par.out

O2:
	g++ gen.cpp -o gen.out
	g++ brute.cpp -o brute.out
	g++ check.cpp -o check.out
	g++ average.cpp -o average.out
	g++ -O2 -fopenmp bloom-n.cpp -o bloom-n.out
	g++ -O2 -fopenmp bloom-n-par.cpp -o bloom-n-par.out
	g++ -O2 -fopenmp bloom.cpp -o bloom.out
	g++ -O2 -fopenmp bloom-par.cpp -o bloom-par.out

clean:
	rm *.out
	rm dummy.txt
	rm dump.txt
	rm inp.txt
	# rm out.txt
	rm res.txt
	rm res2.txt

