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

	double	left = 1;
	double	right = (L / (K + 1)) + 1;
	int			sum;
	int			count;
	double	mid;
	while (right - left >= 1)
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
	// intキャストしないと 5e+08 って出力されてWAになる
	cout << (int) ceil(left) << endl;
}