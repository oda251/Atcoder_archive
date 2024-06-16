#include <bits/stdc++.h>
using namespace std;

void	print(int *dest);

void	solve(int *dest, int index, int sum)
{
	const static vector<int>	nums = {1, -1};

	if (dest[index] == 0)
	{
		if (sum == 0) print(dest);
		return ;
	}
	for (int n : nums)
	{
		if (sum + n < 0) continue;
		dest[index] = n;
		solve(dest, index + 1, sum + n);
	}
}

void	print(int *dest)
{
	for (int i=0; dest[i]!=0; i++)
	{
		if (dest[i] == 1) cout << "(";
		else cout << ")";
	}
	cout << endl;
}

int	main()
{
	int	N;
	cin >> N;
	if (N % 2 == 1) return (0);

	int	*dest;
	dest = (int *)malloc(sizeof(int) * (N + 1));
	for (int i=0; i<N; i++) dest[i] = 1;
	dest[N] = 0;
	solve(dest, 0, 0);
	free(dest);
}
