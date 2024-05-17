#include <bits/stdc++.h>
using namespace std;
using Graph = vector<vector<int>>;

void	calc_distance(int to_look, Graph &g, vector<int> &dist_list, int dist);

pair<int, int>	get_distant(int start, Graph &g, int N)
{
	vector<int> dist_list(N, -1);
	dist_list[start] = 0;

	calc_distance(start, g, dist_list, 0);
	int	max_dist = 0;
	int	distant = 0;
	for (int i=0; i<N; i++)
	{
		if (max_dist < dist_list[i])
		{
			max_dist = dist_list[i];
			distant = i;
		}
	}
	// for (int i=0; i<N; i++)
	// {
	// 	cout << i << ": " << dist_list[i] << endl;
	// }
	return (pair(distant, max_dist));
}

void	calc_distance(int to_look, Graph &g, vector<int> &dist_list, int dist)
{
	dist++;
	for (int dest : g[to_look])
	{
		if (dist_list[dest] == -1)
		{
			dist_list[dest] = dist;
			calc_distance(dest, g, dist_list, dist);
		}
	}
}

int main()
{
	int N;
	cin >> N;
	Graph g(N);

	for (int i=0; i<N - 1; i++)
	{
		int	a, b;
		cin >> a >> b; a--; b--;
		g[a].push_back(b);
		g[b].push_back(a);
	}
	cout << get_distant(get_distant(0, g, N).first, g, N).second + 1 << endl;
	return (0);
}
