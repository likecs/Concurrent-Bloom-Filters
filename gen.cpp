#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
	srand(unsigned(time(NULL)));
	int n = atoi(argv[1]);
	int add_param = atoi(argv[2]);
	int query_param = atoi(argv[3]);

	cout << n << "\n";
	//set<string> dict;
	vector<string> dict2;

	int _n = n/add_param;

	/*
	1 denotes addtion of element
	2 denotes find for element
	*/

	for(int i = 0; i < _n; ++i)
	{
		int len = rand()%6 + 5;
		string temp = "";
		cout << "1 ";
		for(int j = 0; j < len; ++j)
		{
			temp += rand()%26 + 'a';
			cout << temp[temp.length()-1];
		}
		cout << "\n";
		//dict.insert(temp);
		dict2.push_back(temp);
	}

	for(int i = 0; i < (add_param-1)*_n; ++i)
	{
		int go = rand() % (add_param-1);
		if (go <= 1)
		{
			int len = rand()%6 + 5;
			string temp = "";
			cout << "1 ";
			for(int j = 0; j < len; ++j)
			{
				temp += rand()%26 + 'a';
				cout << temp[temp.length()-1];
			}
			cout << "\n";
			//dict.insert(temp);
			dict2.push_back(temp);
		}
		else
		{
			cout << "2 ";
			if (rand()%query_param == 0)
			{
				int pos = rand() % dict2.size();
				cout << dict2[pos] << "\n";
			}
			else
			{
				int len = rand()%6 + 5;
				string temp = "";
				for(int j = 0; j < len; ++j)
				{
					temp += rand()%26 + 'a';
				}
				cout << temp << "\n";
				/*while(1)
				{
					int l = rand()%6 + 5;
					temp = "";
					for(int j = 0; j < len; ++j)
					{
						temp += rand()%26 + 'a';
					}
					if (dict.find(temp) == dict.end())
					{
						cout << temp << "\n";
						break;
					}
				}*/
			}
		}
	}
	return 0;
}
