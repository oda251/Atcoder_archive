#include <bits/stdc++.h>
using namespace std;
using ll = long long;

#define INF LLONG_MAX
#define range(index, a, b) for(ll index=a; i<b; i++)
#define rrange(index, a, b) for(ll index=a; i>=b; i--)
#define all(a) (a).begin(), (a).end()
#define YesNo(bool) if(bool){cout<<"Yes"<<endl;}else{cout<<"No"<<endl;}
#define YESNO(bool) if(bool){cout<<"YES"<<endl;}else{cout<<"NO"<<endl;}
#define yesno(bool) if(bool){cout<<"yes"<<endl;}else{cout<<"no"<<endl;}

int	calc_shortest(vector<string> S, int M, char c,int shortest)
{
	vector<int> r = {0, 1, 2};
	bool f = true;
	while (f)
	{
		int	t = -1;
		int	detected = 0;

		for (int index: r)
		{
			for (int i=t+1; i<3*M; i++)
			{
				if (S[index][i%M] == c)
				{
					t = i;
					detected++;
					break;
				}
			}
		}
		if (detected == 3 && t < shortest)
			shortest = t;
		f = next_permutation(r.begin(), r.end());
	}
	return shortest;
}

int main() {
	int M;
	cin >> M;
	vector<string> S(3);
	for (int i=0; i<3; i++)
		cin >> S[i];
	int shortest = INT_MAX;

	for (char c='0'; c<='9'; c++)
		shortest = calc_shortest(S, M, c, shortest);
	if (shortest == INT_MAX)
		cout << -1 << endl;
	else
		cout << shortest << endl;
	return 0;
}
