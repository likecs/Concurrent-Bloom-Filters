#include <bits/stdc++.h>

using namespace std;

const int MAX = 100000000;

int type[MAX];
string s[MAX];
set<string> go;

int main()
{
	ios_base::sync_with_stdio(false);
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
	for(int i = 0; i < n; ++i)
	{
		if (type[i] == 1)
		{
			go.insert(s[i]);
		}
		else
		{
			if (go.find(s[i]) == go.end())
			{
				cout << "0\n";
			}
			else
			{
				cout << "1\n";
			}
		}
	}
	return 0;
}
