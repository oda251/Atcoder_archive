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

vector<int> get_same(vector<int> t_list, int N)
{
	vector<int> same;
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<N; j++)
		{
			if (i == j)
				continue;
			if (t_list[i] == t_list[j])
				same.push_back(j);
		}
		if (!same.empty())
		{
			same.push_back(i);
			break;
		}
	}
	return same;
}

int	calc_shortest(vector<string> S, int N, int M, char c,int shortest)
{
	vector<int> t_list(N, -1);
	for (int i=0; i<N; i++)
	{
		for (int j=0; j<M; j++)
		{
			if (S[i][j] == c)
			{
				t_list[i] = j;
				break;
			}
			return shortest;
		}
	}
	vector<int> same;
	same = get_same(t_list, N);
	return shortest;
}

int main() {
	int N, M;
	cin >> N >> M;
	vector<string> S(N);
	for (int i=0; i<N; i++)
		cin >> S[i];
	int shortest = INT_MAX;

	for (char c='0'; c<='9'; c++)
		shortest = calc_shortest(S, N, M, c, shortest);
	if (shortest == INT_MAX)
		cout << -1 << endl;
	else
		cout << shortest << endl;
	return 0;
}
