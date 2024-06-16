#include <bits/stdc++.h>
using namespace std;

#define YES cout << "Yes" << endl;
#define NO cout << "No" << endl;

struct t_txy
{
	int	t = 0;
	int	x = 0;
	int	y = 0;
};

bool	solve(t_txy now, t_txy next)
{
	int	diff_t = next.t - now.t;
	int	dist = abs(next.y - now.y) + abs(next.x - now.x);

	if (diff_t % 2 != dist % 2) return (false);
	if (dist > diff_t) return (false);
	return (true);
}

int	main()
{
	int	N;
	cin >> N;
	t_txy	now;
	t_txy	next;

	for (int t=1; t<=N; t++)
	{
		cin >> next.t >> next.x >> next.y;
		if (!solve(now, next))
		{
			NO;
			return (0);
		}
		now = next;
	}
	YES;
	return (0);
}