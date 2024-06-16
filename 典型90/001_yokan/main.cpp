#include<bits/stdc++.h>
using namespace std;

int	main()
{
	int	N, L, K;
	cin >> N >> L >> K;
	vector<int>	A(N + 1);
	int	pre = 0;
	int	next;
	for (int i=0; i<N; i++)
	{
		cin >> next;
		A[i] = next - pre;
		pre = next;
	}
	A[N] = L - pre;
	// import END

	int	left = 1;
	int	right = L / (K + 1) + 1;
	int	sum;
	int	count;
	int	mid;
	while (right - left > 1)
	{
		sum = 0;
		count = 0;
		mid = (left + right) / 2;
		for (int v : A)
		{
			sum += v;
			if (sum >= mid)
			{
				sum = 0;
				count++;
			}
		}
		if (count >= K + 1) left = mid;
		else right = mid;
	}
	cout << left << endl;
}