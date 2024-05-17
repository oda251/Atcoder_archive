#include <bits/stdc++.h>
using namespace std;

constexpr int MOD = 1000000007;
constexpr int LOG = 62;

int	main()
{
	unsigned long long	N;
	int	B, K;
	cin >> N >> B >> K;
	vector<int>	nums(K);
	for (int i=0; i<K; i++) cin >> nums[i];

	vector<int>	ten_mod(LOG, 0);
	ten_mod[0] = 10 % B;
	for (int i=0; i<LOG-1; i++) ten_mod[i+1] = (ten_mod[i] * ten_mod[i]) % B;

	vector<vector<unsigned long long>>	two(LOG, vector<unsigned long long>(B, 0));
	for (int c : nums) two[0][c % B] += 1;
	for (int i=0; i<LOG-1; i++)
	{
		for (int j=0; j<B; j++)
		{
			for (int k=0; k<B; k++)
			{
				two[i+1][(j * ten_mod[i] + k) % B] += (two[i][j] * two[i][k]) % MOD;
				two[i+1][(j * ten_mod[i] + k) % B] %= MOD;
			}
		}
	}

	auto solve = [&](int digit, vector<unsigned long long> &pre_res) -> vector<unsigned long long> {
		vector<unsigned long long>	new_res(B, 0);
		for (int i=0; i<B; i++)
		{
			for (int j=0; j<B; j++)
			{
				int nex = (i * ten_mod[digit] + j) % B;
				new_res[nex] += (pre_res[i] * two[digit][j]) % MOD;
				new_res[nex] %= MOD;
			}
		}
		return (new_res);
	};

	vector<unsigned long long>	result(B, 0);
	result[0] = 1;
	for (int i=0; i<LOG; i++)
	{
		if (N & (1ULL << i))
		{
			result = solve(i, result);
		}
	}
	cout << result[0] << endl;
	return (0);
}