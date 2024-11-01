#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
class Job {
public:
	int D, C;
	ll S;
};
vector<Job> Jobs;
class DPData{
public:
	int daySpend;
	ll score;
};

int	main()
{
	cin >> N;
	Jobs.resize(N);
	int max_d = 0;
	for (int i=0; i<N; i++) {
		Jobs.push_back(Job());
		cin >> Jobs[i].D >> Jobs[i].C >> Jobs[i].S;
		max_d = max(max_d, Jobs[i].D);
	}
	sort(Jobs.begin(), Jobs.end(), [](const Job& a, const Job& b) {
		return a.D < b.D;
	});
	vector<vector<DPData>> dp(N, vector<DPData>(max_d));
	for (int i=0; i<max_d; i++) {
		dp[N-1][i].daySpend = 0;
		dp[N-1][i].score = 0;
	}
	for (int i=0; i<N; i++) {
		for (int j=0; j<max_d; j++) {
			if (j < Jobs[i].D) {
				dp[i][j] = Jobs[i].S;
			} else {
				dp[i][j] = max(dp[i][j], dp[i][j-1]);
			}
		}
	}
	return 0;
}
