#include <bits/stdc++.h>
using namespace std;

int N, K;
string S;

vector<vector<int>> calc_map(void) {
	vector<vector<int>> dest(N + 1, vector<int>(26, -1));
	for (int i=N-1; i>=0; i--) {
		for (int j=0; j<26; j++) {
			if (S[i] == 'a'+j)
				dest[i][j] = i;
			else
				dest[i][j] = dest[i+1][j];
		}
	}
	return dest;
}

int	main()
{
	cin >> N >> K >> S;
	auto dest = calc_map();
	string sub;
	sub.resize(K);

	int cur = 0;
	for (int i=0; i<K; i++) {
		for (int j=0; j<26; j++) {
			if (dest[cur][j] != -1 && N - dest[cur][j] >= K - i) {
				sub[i] = 'a' + j;
				cur = dest[cur][j] + 1;
				break;
			}
		}
	}
	cout << sub << endl;
	return 0;
}