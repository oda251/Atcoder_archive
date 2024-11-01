#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int N;
string S;

int	main()
{
	cin >> N >> S;
	const string tgt = "atcoder";

	vector<array<ll, 7>> cnt(N+1);
	for (int i=0; i<7; i++) {
		cnt[N][i] = 0;
	}

	auto prep = [&]() {
		for (int i=S.size() - 1; i>=0; i--) {
			for (int j=0; j<7; j++) {
				cnt[i][j] = cnt[i+1][j];
				if (S[i] == tgt[j]) {
					if (j == 6) {
						cnt[i][j]++;
					} else {
						cnt[i][j] += cnt[i+1][j+1];
						cnt[i][j] %= 1000000007;
					}
				}
			}
		}
	};
	prep();
	cout << cnt[0][0] << endl;
	return 0;
}