#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
class Job {
public:
	int D, C;
	ll S;
};
vector<Job> jobs;
class DPData{
public:
	int daySpend;
	ll score;

	DPData() : daySpend(0), score(0) {}
	DPData(int d, ll s) : daySpend(d), score(s) {}
};
DPData max(DPData a, DPData b) {
	if (a.score > b.score) return a;
	if (a.score < b.score) return b;
	if (a.daySpend < b.daySpend) return a;
	return b;
}

int	main()
{
	cin >> N;
	jobs.resize(N);
	int max_d = 0;
	for (int i=0; i<N; i++) {
		cin >> jobs[i].D >> jobs[i].C >> jobs[i].S;
		max_d = max(max_d, jobs[i].D);
	}
	sort(jobs.begin(), jobs.end(), [](const Job& a, const Job& b) {
		return a.D < b.D;
	});
	vector<vector<DPData>> dp(N+1, vector<DPData>(max_d + 1));
	for (int i=0; i<N; i++) {
		for (int j=0; j<=max_d; j++) {
			dp[i+1][j] = max(dp[i+1][j], dp[i][j]);
			if (j + jobs[i].C <= jobs[i].D) {
				DPData tmp = dp[i][j];
				tmp.daySpend += jobs[i].C;
				tmp.score += jobs[i].S;
				dp[i+1][j+jobs[i].C] = max(dp[i+1][j+jobs[i].C], tmp);
			}
		}
	}
	ll ans = 0;
	for (int i=0; i<=N; i++) {
		for (int j=0; j<max_d; j++) {
			ans = max(ans, dp[i][j].score);
		}
	}
	cout << ans << endl;
	return 0;
}
