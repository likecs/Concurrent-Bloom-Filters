#include <bits/stdc++.h>
#include <sys/resource.h>
#include <omp.h>

using namespace std;

typedef long long LL;
typedef long double LD;

const int MAX = 100000000;
const int MOD2 = 31;
const int BITS = 16;
const int MAXL = 12;
const int HASHES = 12;
const int LEN = HASHES/2;
const int SZ = MAX * HASHES;

int MOD;
int *type;
string *s;
int primes[HASHES];

long long mulmod(long long a,long long b, long long MOD)
{
	long long q = (long long)(((long double)a*(long double)b)/(long double)MOD);
	long long r = a*b-q*MOD;
	if (r > MOD) r %= MOD;
	if(r < 0) r += MOD;
	return r;
}

long long power(long long b, long long n, long long mod)
{
	long long x=1, p=b;
	while(n)
	{
		if(n&1)
		{
			x = mulmod(x, p, mod);
		}
		p = mulmod(p, p, mod);
		n >>= 1;
	}
	return x;
}

bool rabin_miller(long long p)
{
	if (p < 2) return false;
	if (p != 2 && p % 2 == 0) return false;
	if (p < 8) return true;
	long long s = p-1, val = p-1, a, m, temp;
	while (s % 2 == 0) s >>= 1;
	for (int i = 0; i < 3; ++i)
	{
		a = 1ll*rand()%val + 1ll;
		temp = s;
		m = power(a, temp, p);
		while (temp != (p-1) && m != 1 && m != (p-1))
		{
			m = mulmod(m, m, p);
			temp <<= 1;
		}
		if (m != (p-1) && temp % 2 == 0) return false;
	}
	return true;
}

void initialise()
{
	type = new int[MAX+1];
	assert(type != NULL);
	s = new string[MAX+1];
	assert(s != NULL);
	MOD = SZ;	
	while(1)
	{
		if (rabin_miller(MOD))
		{
			break;
		}
		MOD += 1;
	}
	for(int i = 0; i < HASHES; ++i)
	{
		while(1)
		{
			int num = rand() % MAX;
			if (rabin_miller(num) && num != MOD && num != MOD2)
			{
				primes[i] = num;
				break;
			}
		}
	}
}
