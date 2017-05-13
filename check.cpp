#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
	FILE *fp = fopen("out.txt", "r");
	FILE *fp2 = fopen("res.txt", "r");
	int n, n1;
	fscanf(fp, "%d", &n);
	fscanf(fp2, "%d", &n1);
	assert(n == n1);
	int a, b, f = 0;
	for(int i = 0; i < n; ++i) 
	{
		fscanf(fp, "%d", &a);
		fscanf(fp2, "%d", &b);
		if (b == 0)
		{
			if (a != 0)
			{
				cout << "False negatives found\n";
				break;
			}
		}
		else
		{
			if (a == 0)
			{
				f += 1;
			}
		}
	}
	cout << "False positives : " << f << " " << ((double)f / n) << "\n";
	return 0;
}
