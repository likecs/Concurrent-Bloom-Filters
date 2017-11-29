#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
	FILE *fp = fopen("dummy.txt", "r");
	int lines = atoi(argv[1]);
	double x, sum = 0;
	for(int i = 1; i <= lines; ++i) {
		fscanf(fp, "%lf", &x);
		sum += x;
	}
	cerr << (sum/lines) << "\n";
	fclose(fp);
	fp = fopen("dummy.txt", "w");
	fclose(fp);
	return 0;
}
