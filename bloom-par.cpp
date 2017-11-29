#include "global.h"

long long powers[HASHES][MAXL];
unsigned long long bloom_filter[(SZ>>6)+1];
omp_nest_lock_t lck[(SZ>>6)+1];

#define SET(x) 				(bloom_filter[x>>6]&(1ull<<(x&63)))
#define MARK(x) 			(bloom_filter[x>>6]|=(1ull<<(x&63)))

int main(int argc, char const *argv[])
{
	int NUMTHREADS = atoi(argv[1]);
	const rlim_t Stack_size = 16L * 1024 * 1024;
	struct rlimit lim = {Stack_size, Stack_size};
	if(setrlimit(RLIMIT_STACK, &lim) == -1) assert(false);
	ios_base::sync_with_stdio(false);
	initialise();
	for(int i = 0; i <= (SZ>>6); ++i)
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
	for(int i = 0; i < HASHES; ++i)
	{
		powers[i][0] = 1;
		if (i % 2 == 0)
		{	
			for(int j = 1; j < MAXL; ++j)
			{
				powers[i][j] = (powers[i][j-1] * primes[i]) % MOD;
			}
		}
		else
		{	
			for(int j = 1; j < MAXL; ++j)
			{
				powers[i][j] = (powers[i][j-1] * primes[i]) % MOD2;
			}
		}
	}
	#pragma omp parallel for 
	for(int i = 0; i < n; ++i)
	{
		if (type[i] == 1)
		{
			int U, addr1, addr2;
			pair<int,int> go, pts[LEN];
			for(int j = 0; j < HASHES; j += 2)
			{
				addr1 = 0;
				addr2 = 0;
				for(int k = s[i].length() - 1, _k = 0; k >= 0; --k, ++_k)
				{
					addr1 = (addr1 + powers[j][_k] * (s[i][k]-'a'+1)) % MOD;
					addr2 = (addr2 + powers[j+1][_k] * (s[i][k]-'a'+1)) % MOD2;
				}
				addr1 %= SZ;
				U = ((addr1 + BITS - 1) / BITS) * BITS;
				addr2 %= BITS;
				addr2 += addr1;
				if (addr2 > U)
				{
					addr2 -= BITS;
				}
				go = make_pair(addr1, addr2);
				int l = (j/2) - 1;
				while(l >= 0 && pts[l] > go)
				{
					pts[l+1] = pts[l];
					l -= 1;
				}
				pts[l+1] = go;
			}
			for(int j = 0; j < LEN; ++j) 
			{
				omp_set_nest_lock(&lck[pts[j].first>>6]);
			}
			for(int j = 0; j < LEN; ++j)
			{
				MARK(pts[j].first);
				MARK(pts[j].second);
			}
			for(int j = 0; j < LEN; ++j)
			{
				omp_unset_nest_lock(&lck[pts[j].first>>6]);
			}
		}
		else
		{
			bool found = true;
			int addr1, addr2;
			for(int j = 0; j < HASHES; j += 2)
			{
				//primary hash
				addr1 = 0;
				for(int k = s[i].length() - 1, _k = 0; k >= 0; --k, ++_k)
				{
					addr1 = (addr1 + powers[j][_k] * (s[i][k]-'a'+1)) % MOD;
				}
				addr1 %= SZ;
				if (!SET(addr1))
				{
					found = false;
					break;
				}
				int U = ((addr1 + BITS - 1) / BITS) * BITS;
				//secondary hash
				addr2 = 0;
				for(int k = s[i].length() - 1, _k = 0; k >= 0; --k, ++_k)
				{
					addr2 = (addr2 + powers[j+1][_k] * (s[i][k]-'a'+1)) % MOD2;
				}
				addr2 %= BITS;
				addr2 += addr1;
				if (addr2 > U)
				{
					addr2 -= BITS;
				}
				if (!SET(addr2))
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
	for(int i = 0; i <= (SZ>>6); ++i)
	{
		omp_destroy_nest_lock(&lck[i]);
	}
	cerr << (end - start) << "\n";
	return 0;
}
