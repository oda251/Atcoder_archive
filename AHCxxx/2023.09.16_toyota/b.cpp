#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
	string	s;
	int	longest_len = 0;

	cin >> s;
	for (int i=0; i<s.length(); i++)
	{
		for (int j=0; i-j>=0 && i+j<s.length(); j++)
		{
			if (s[i-j] != s[i+j])
				break;
			if (longest_len < 2*j+1)
				longest_len = 2*j+1;
		}
		for (int j=0; i-j>=0 && i+j+1<s.length(); j++)
		{
			if (s[i-j] != s[i+j+1])
				break;
			if (longest_len < 2*j+2)
				longest_len = 2*j+2;
		}
	}
	cout << longest_len << endl;
}
