#include <bits/stdc++.h>
using namespace std;

int	main()
{
	int	N;
	int	result = 0;

	cin >> N;
	vector<int>	nums(N);
	for (int i=0; i<N; i++) cin >> nums[i];
	sort(nums.begin(), nums.end(), [](int a, int b){ return a >= b; });
	for (int i=0; i<N; i++)
	{
		if (i % 2 == 0) result += nums[i];
		else result -= nums[i];
	}
	cout << result << endl;
}