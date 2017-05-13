#include "global.h"

int bloom_filter[SZ+1];
omp_nest_lock_t lck[SZ+1];

#define SET(x) 				(bloom_filter[x] == 1)
#define MARK(x) 			(bloom_filter[x] = 1)

int main(int argc, char const *argv[])
{
	int NUMTHREADS = atoi(argv[1]);
	const rlim_t Stack_size = 16L * 1024 * 1024;
	struct rlimit lim = {Stack_size, Stack_size};
	if(setrlimit(RLIMIT_STACK, &lim) == -1) assert(false);
	ios_base::sync_with_stdio(false);
	initialise();
	for(int i = 0; i <= SZ; ++i)
	{
		omp_init_nest_lock(&lck[i]);
	}
	int n, cnt = 0;
	cin >> n;
	for(int i = 0; i < n; ++i)
	{
		cin >> type[i] >> s[i];
		if (type[i] == 2)
		{
			cnt += 1;
		}
	}
	cout << cnt << "\n";

	omp_set_num_threads(NUMTHREADS);

	double start = omp_get_wtime();
	#pragma omp parallel for
	for(int i = 0; i < n; ++i)
	{
		if (type[i] == 1)
		{
			int pts[HASHES];
			for(int j = 0; j < HASHES; ++j)
			{
				int addr = 0, p = primes[j];
				long long cur = 1;
				for(int k = s[i].length() - 1; k >= 0; --k)
				{
					addr = (addr + cur * (s[i][k]-'a'+1)) % MOD;
					cur = (cur * p) % MOD;
				}
				addr %= SZ;
				pts[j] = addr;
			}
			sort(pts, pts + HASHES);
			for(int j = 0; j < HASHES; ++j) 
			{
				omp_set_nest_lock(&lck[pts[j]]);
			}
			for(int j = 0; j < HASHES; ++j)
			{
				MARK(pts[j]);
			}
			for(int j = 0; j < HASHES; ++j) 
			{
				omp_unset_nest_lock(&lck[pts[j]]);
			}
		}
		else
		{
			bool found = true;
			for(int j = 0; j < HASHES; j += 2)
			{
				int addr = 0, p = primes[j];
				long long cur = 1;
				for(int k = s[i].length() - 1; k >= 0; --k)
				{
					addr = (addr + cur * (s[i][k]-'a'+1)) % MOD;
					cur = (cur * p) % MOD;
				}
				addr %= SZ;
				if (!SET(addr))
				{
					found = false;
					break;
				}
			}
			/*if (found)
			{
				cout << "1\n";
			}
			else
			{
				cout << "0\n";
			}*/
		}
	}
	double end = omp_get_wtime();
	for(int i = 0; i <= SZ; ++i)
	{
		omp_destroy_nest_lock(&lck[i]);
	}
	cerr << (end - start) << "\n";
	return 0;
}
